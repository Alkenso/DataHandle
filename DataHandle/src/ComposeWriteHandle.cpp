//
//  ComposeWriteHandle.m
//  DataHandle
//
//  Created by alk on 5/22/17.
//
//

#include "ComposeWriteHandle.h"

datarw::ComposeWriteHandle::ComposeWriteHandle(std::initializer_list<std::reference_wrapper<DataWriteHandle>> writers)
: datarw::DataWriteHandle()
, m_writers(writers)
{}

uint64_t datarw::ComposeWriteHandle::getDataSizeImpl()
{
    uint64_t maxWriterSize = 0;
    for (DataWriteHandle& writer : m_writers)
    {
        maxWriterSize = std::max(maxWriterSize, writer.getDataSize());
    }
    
    return maxWriterSize;
}

void datarw::ComposeWriteHandle::writeDataImpl(const unsigned char* data, const Range& range)
{
    for (DataWriteHandle& writer : m_writers)
    {
        writer.writeData(data, range.length, range.position);
    }
}
