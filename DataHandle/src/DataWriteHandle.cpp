//
//  DataWriteHandle.cpp
//  DataHandle
//
//  Created by Alkenso on 5/5/17.
//
//

#include "DataWriteHandle.h"

namespace
{
    const datarw::ByteBuffer g_nullTerminator = { 0x00 };
}

datarw::DataWriteHandle::DataWriteHandle()
: m_position(0)
, m_usePositionIsSet(false)
{}

uint64_t datarw::DataWriteHandle::tellPosition()
{
    return m_position;
}

uint64_t datarw::DataWriteHandle::getDataSize()
{
    initPosition();
    
    return m_position;
}

void datarw::DataWriteHandle::writeString(const std::string& str, int64_t offset, const bool withNullTerminator /* = false */)
{
    writeData(reinterpret_cast<const unsigned char*>(str.data()), str.size(), offset);
    if (withNullTerminator)
    {
        writeData(g_nullTerminator, str.size() + offset);
    }
}

void datarw::DataWriteHandle::writeString(const std::string& str, const bool withNullTerminator /* = false */)
{
    writeData(str.data(), str.size());
    if (withNullTerminator)
    {
        writeData(g_nullTerminator);
    }
}

void datarw::DataWriteHandle::seekPositionOptimized(const uint64_t)
{}

void datarw::DataWriteHandle::insertDataInternal(const unsigned char* data, const uint64_t dataSize, const uint64_t offset, const bool usePosition)
{
    if (!dataSize)
    {
        return;
    }
    if (!data)
    {
        throw std::invalid_argument("Unable to write null data");
    }
    
    initPosition();
    
    const uint64_t currentPosition = seekPosition(offset, usePosition);
    writeDataImpl(data, Range(currentPosition, dataSize));
    m_position = std::max(m_position, currentPosition + dataSize);
}

uint64_t datarw::DataWriteHandle::seekPosition(const uint64_t offset, const bool usePosition)
{
    uint64_t newPosition = offset;
    if (usePosition)
    {
        m_position += offset;
        newPosition = m_position;
    }
    
    if (!m_usePositionIsSet || !usePosition)
    {
        seekPositionOptimized(newPosition);
    }
    m_usePositionIsSet = usePosition;
    
    return newPosition;
}

void datarw::DataWriteHandle::initPosition()
{
    std::call_once(m_inited, [this]()
                   {
                       m_position = getDataSizeImpl();
                   });
}
