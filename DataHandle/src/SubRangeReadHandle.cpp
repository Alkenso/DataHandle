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

#include "SubRangeReadHandle.h"

datarw::SubRangeReadHandle::SubRangeReadHandle(DataReadHandle& parentReader, Range dataRange)
: DataReadHandle()
, m_parentReader(parentReader)
, m_dataRange(dataRange)
{
    if ((dataRange.position + dataRange.length) > parentReader.getDataSize())
    {
        throw std::out_of_range("Data could be out of range");
    }
}

datarw::SubRangeReadHandle::SubRangeReadHandle(DataReadHandle& parentReader, const uint64_t additionalOffset, const bool relativeToParent /* = false */)
: DataReadHandle()
, m_parentReader(parentReader)
, m_dataRange()
{
    uint64_t subPosition = additionalOffset;
    if (relativeToParent)
    {
        subPosition += parentReader.getDataSize() - parentReader.getRemainingSize(); 
    }
    
    const uint64_t totalDataSize = parentReader.getDataSize();
    if (totalDataSize < subPosition)
    {
        throw std::out_of_range("Data could be out of range");
    }
    m_dataRange = datarw::Range(subPosition, totalDataSize - subPosition);
}

datarw::SubRangeReadHandle::SubRangeReadHandle(SubRangeReadHandle&& r)
: DataReadHandle(std::move(r))
, m_parentReader(std::move(r.m_parentReader))
, m_dataRange(std::move(r.m_dataRange))
{}

datarw::SubRangeReadHandle& datarw::SubRangeReadHandle::operator=(SubRangeReadHandle&& r)
{
    DataReadHandle::operator=(std::move(r));
    m_parentReader = std::move(r.m_parentReader);
    m_dataRange = std::move(r.m_dataRange);

    return *this;
}

void datarw::SubRangeReadHandle::peekDataImpl(const Range& range, void* buffer)
{
    const Range subRange(range.position + m_dataRange.position, range.length);
    m_parentReader.get().peekData(subRange, buffer);
}

uint64_t datarw::SubRangeReadHandle::getDataSizeImpl()
{
    return m_dataRange.length;
}
