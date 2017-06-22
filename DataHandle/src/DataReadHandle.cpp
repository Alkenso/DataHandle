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

#include "DataReadHandle.h"

datarw::DataReadHandle::DataReadHandle()
: m_sizePosition(0)
, m_sizePositionIsSet(false)
, m_currentPosition(0)
, m_usePositionIsSet(false)
{}


datarw::DataReadHandle::DataReadHandle(DataReadHandle&& r)
: m_sizePosition(r.m_sizePosition)
, m_sizePositionIsSet(r.m_sizePositionIsSet)
, m_currentPosition(r.m_currentPosition)
, m_usePositionIsSet(r.m_usePositionIsSet)
{}

datarw::DataReadHandle& datarw::DataReadHandle::operator=(DataReadHandle&& r)
{
    m_sizePosition = r.m_sizePosition;
    m_sizePositionIsSet = r.m_sizePositionIsSet;
    m_currentPosition = r.m_currentPosition;
    m_usePositionIsSet = r.m_usePositionIsSet;

    return *this;
}

uint64_t datarw::DataReadHandle::getDataSize()
{
    if (!m_sizePositionIsSet)
    {
        m_sizePosition = getDataSizeImpl();
        m_sizePositionIsSet = true;
    }
    
    return m_sizePosition;
}

void datarw::DataReadHandle::peekData(const Range& range, void* data)
{
    peekDataInternal(range, reinterpret_cast<unsigned char*>(data), false);
}

void datarw::DataReadHandle::readData(const uint64_t dataSize, void* data)
{
    readDataInternal(dataSize, reinterpret_cast<unsigned char*>(data));
}

void datarw::DataReadHandle::readAllData(void* data)
{
    peekData(datarw::Range(0, getDataSize()), data);
}

void datarw::DataReadHandle::skipBytes(const uint64_t skipSize)
{
    seekPosition(skipSize, true, true);
}

uint64_t datarw::DataReadHandle::getRemainingSize()
{
    return getDataSize() - tellPosition();
}

bool datarw::DataReadHandle::enshureRemainingSize(uint64_t expectedRemainingSize)
{
    return getRemainingSize() >= expectedRemainingSize;
}

void datarw::DataReadHandle::seekPositionOptimized(const uint64_t)
{}

void datarw::DataReadHandle::peekDataInternal(const Range& range, void* buffer, const bool usePosition)
{
    if (!range.length)
    {
        return;
    }
    if (!buffer)
    {
        throw std::invalid_argument("Unable to read data into null");
    }
    if (getDataSize() < (range.position + range.length + (usePosition ? tellPosition() : 0)))
    {
        throw std::out_of_range("Unable to read data. Requested data is out of range");
    }
    
    const uint64_t currentPosition = seekPosition(range.position, usePosition);
    peekDataImpl(Range(currentPosition, range.length), buffer);
    
    if (usePosition)
    {
        m_currentPosition += range.length;
    }
}

void datarw::DataReadHandle::readDataInternal(const uint64_t sizeInBytes, void* buffer)
{
    peekDataInternal(Range(0, sizeInBytes), buffer, true);
}

uint64_t datarw::DataReadHandle::seekPosition(const uint64_t position, const bool usePosition, const bool seekForce /* = false */)
{
    uint64_t newPosition = position;
    if (usePosition)
    {
        m_currentPosition += position;
        newPosition = m_currentPosition;
    }
    
    if (seekForce || !m_usePositionIsSet || !usePosition)
    {
        seekPositionOptimized(newPosition);
    }
    m_usePositionIsSet = usePosition;
    
    return newPosition;
}

uint64_t datarw::DataReadHandle::tellPosition()
{
    return m_currentPosition;
}
