//
//  StreamWriteHandle.cpp
//  DataHandle
//
//  Created by Alkenso on 5/5/17.
//
//

#include "StreamWriteHandle.h"

namespace
{
    void Seek(std::ostream& s, int64_t pos, std::ios::seekdir dir)
    {
        s.seekp(pos, dir);
    }
    
    int64_t Tell(std::ostream& s)
    {
        return s.tellp();
    }
}

datarw::StreamWriteHandle::StreamWriteHandle(std::ostream& stream, const bool streamIsDirty /* = false */)
: StreamHandleBase<datarw::DataWriteHandle, std::ostream>(stream, Seek, Tell, streamIsDirty)
{}

void datarw::StreamWriteHandle::insertDataImpl(const unsigned char* data, const Range& range)
{
    resetStreamIfNeeded(false, range.position);
    
    m_stream.write(reinterpret_cast<const char*>(data), range.length);
}
