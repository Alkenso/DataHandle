//
//  DataReadHandle.cpp
//  DataHandle
//
//  Created by Alkenso on 5/5/17.
//
//

#include "DataReadHandle.h"

datarw::DataReadHandle::DataReadHandle()
: DataHandleBase()
, m_sizePosition(0)
, m_sizePositionIsSet(false)
, m_currentPosition(0)
, m_usePositionIsSet(false)
{}

uint64_t datarw::DataReadHandle::getDataSize()
{
    if (!m_sizePositionIsSet)
    {
        m_sizePosition = getDataSizeImpl();
        m_sizePositionIsSet = true;
    }
    
    return m_sizePosition;
}

void datarw::DataReadHandle::skipNextBytes(const uint64_t skipSize)
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

void datarw::DataReadHandle::peekDataInternal(const Range& range, unsigned char* buffer, const bool usePosition)
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

void datarw::DataReadHandle::readNextDataInternal(const uint64_t dataSize, unsigned char* buffer)
{
    peekDataInternal(Range(0, dataSize), buffer, true);
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
