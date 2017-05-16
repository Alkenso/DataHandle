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

void datarw::DataWriteHandle::insertString(const std::string& str, int64_t offset, const bool withNullTerminator /* = false */)
{
    insertData(reinterpret_cast<const unsigned char*>(str.data()), str.size(), offset);
    if (withNullTerminator)
    {
        insertData(g_nullTerminator, str.size() + offset);
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

void datarw::DataWriteHandle::insertDataInternal(const unsigned char* data, const uint64_t dataSize, const uint64_t offset, const bool usePosition)
{
    std::call_once(m_inited, [this]()
                   {
                       seekPosition(getDataSize(), true);
                   });
    
    if (!dataSize)
    {
        return;
    }
    if (!data)
    {
        throw std::invalid_argument("Unable to write null data");
    }
    
    const uint64_t currentPosition = seekPosition(offset, usePosition);
    insertDataImpl(data, Range(currentPosition, dataSize));
    seekPosition(dataSize, usePosition);
}
