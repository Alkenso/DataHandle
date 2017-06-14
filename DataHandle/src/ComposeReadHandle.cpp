/*
 * Copyright (c) 2017 Alkenso (Vashurkin Vladimir)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "ComposeReadHandle.h"

namespace
{
    bool FindReadRange(const std::vector<datarw::Range>& readerRanges, const datarw::Range& readRange, size_t& firstReaderIdx, size_t& lastReaderIdx)
    {
        const uint64_t readerCount = readerRanges.size();
        const uint64_t readRangeBegin = readRange.position;
        const uint64_t readRangeEnd = readRangeBegin + readRange.length;
        
        bool firstIsSet = false;
        for (size_t i = 0; i < readerCount; i++)
        {
            const uint64_t readerBegin = readerRanges[i].position;
            const uint64_t readerEnd = readerBegin + readerRanges[i].length;
            
            if (!firstIsSet && (readRangeBegin >= readerBegin) && (readRangeBegin < readerEnd))
            {
                firstIsSet = true;
                firstReaderIdx = i;
                lastReaderIdx = i;
            }
            else if (firstIsSet && (readRangeEnd >= readerBegin) && (readRangeEnd <= readerEnd))
            {
                lastReaderIdx = i;
            }
        }
        
        return firstIsSet;
    }
}

datarw::ComposeReadHandle::ComposeReadHandle(std::initializer_list<std::reference_wrapper<DataReadHandle>> readers)
: DataReadHandle()
, m_readers(readers)
, m_readerRanges(readers.size())
{
    updateReaderRanges();
}

uint64_t datarw::ComposeReadHandle::getDataSizeImpl()
{
    return updateReaderRanges();
}

void datarw::ComposeReadHandle::peekDataImpl(const datarw::Range& range, unsigned char* buffer)
{
    size_t firstReaderIdx = 0;
    size_t lastReaderIdx = 0;
    if (!FindReadRange(m_readerRanges, range, firstReaderIdx, lastReaderIdx))
    {
        throw std::out_of_range("Unable to read combined data out of range.");
    }
    
    DataReadHandle& firstReader = m_readers[firstReaderIdx];
    const Range& firstReaderRange = m_readerRanges[firstReaderIdx];
    
    Range firstRange;
    firstRange.position = range.position - firstReaderRange.position;
    firstRange.length = std::min(range.length, firstReaderRange.length - firstRange.position);
    firstReader.peekData(firstRange, buffer);
    
    if (firstReaderIdx >= lastReaderIdx)
    {
        return;
    }
    
    uint64_t readSize = firstRange.length;
    for (size_t i = firstReaderIdx + 1; i < lastReaderIdx; i++) // All intermediate pieces
    {
        DataReadHandle& reader = m_readers[i];
        reader.readAllData(buffer + readSize);
        readSize += m_readerRanges[i].length;
    }

    Range lastRange;
    lastRange.position = 0;
    lastRange.length = range.position + range.length - m_readerRanges[lastReaderIdx].position;
    
    DataReadHandle& lastReader = m_readers[lastReaderIdx];
    lastReader.peekData(lastRange, buffer + readSize);
}

uint64_t datarw::ComposeReadHandle::updateReaderRanges()
{
    const size_t readerCount = m_readers.size();
    
    uint64_t offset = 0;
    for (size_t i = 0; i < readerCount; i++)
    {
        const uint64_t dataSize = m_readers[i].get().getDataSize();
        m_readerRanges[i].position = offset;
        m_readerRanges[i].length = dataSize;
        
        offset += dataSize;
    }
    
    return offset;
}
