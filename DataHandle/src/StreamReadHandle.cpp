//
//  StreamReadHandle.cpp
//  DataHandle
//
//  Created by Alkenso on 5/5/17.
//
//

#include "StreamReadHandle.h"

datarw::StreamReadHandle::StreamReadHandle(std::istream& stream, const bool streamIsDirty /* = false */)
: StreamHandleBase<datarw::DataReadHandle, std::istream>(stream, streamIsDirty)
{}

void datarw::StreamReadHandle::peekDataImpl(const Range& range, unsigned char* buffer)
{
    resetStreamIfNeeded(false, range.position);
    
    m_stream.read(reinterpret_cast<char*>(buffer), range.length);
}

void datarw::StreamReadHandle::seek(std::istream& stream, const int64_t pos, const std::ios::seekdir dir)
{
    stream.seekg(pos, dir);
}

int64_t datarw::StreamReadHandle::tell(std::istream& stream)
{
    return stream.tellg();
}
