//
//  ParallelWriteHandle.m
//  DataHandle
//
//  Created by alk on 5/22/17.
//
//

#import "ParallelWriteHandle.h"

datarw::ParallelWriteHandle::ParallelWriteHandle(std::initializer_list<std::reference_wrapper<DataWriteHandle>> writers)
: datarw::DataWriteHandle()
, m_writers(writers)
{}

uint64_t datarw::ParallelWriteHandle::getDataSizeImpl()
{
    uint64_t maxWriterSize = 0;
    for (DataWriteHandle& writer : m_writers)
    {
        maxWriterSize = std::max(maxWriterSize, writer.getDataSize());
    }
    
    return maxWriterSize;
}

void datarw::ParallelWriteHandle::insertDataImpl(const unsigned char* data, const Range& range)
{
    for (DataWriteHandle& writer : m_writers)
    {
        writer.insertData(data, range.length, range.position);
    }
}
