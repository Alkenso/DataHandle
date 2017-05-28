//
//  StreamWriteHandle.cpp
//  DataHandle
//
//  Created by Alkenso on 5/5/17.
//
//

#include "StreamWriteHandle.h"

datarw::StreamWriteHandle::StreamWriteHandle(std::ostream& stream, const bool streamIsDirty /* = false */)
: StreamHandleBase<datarw::DataWriteHandle, std::ostream>(stream, streamIsDirty)
{}

void datarw::StreamWriteHandle::writeDataImpl(const unsigned char* data, const Range& range)
{
    resetStreamIfNeeded(false, range.position);
    
    m_stream.write(reinterpret_cast<const char*>(data), range.length);
}

void datarw::StreamWriteHandle::seek(std::ostream& stream, const int64_t pos, const std::ios::seekdir dir)
{
    stream.seekp(pos, dir);
}

int64_t datarw::StreamWriteHandle::tell(std::ostream& stream)
{
    return stream.tellp();
}
