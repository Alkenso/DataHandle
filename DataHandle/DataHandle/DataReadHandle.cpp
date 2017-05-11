#include "DataReadHandle.h"

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
    seekPosition(range.length, usePosition);
}

void datarw::DataReadHandle::readNextDataInternal(const uint64_t dataSize, unsigned char* buffer)
{
    peekDataInternal(Range(0, dataSize), buffer, true);
}
