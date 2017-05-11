//
//  StreamReadHandle.cpp
//  DataHandle
//
//  Created by Alkenso on 5/5/17.
//
//

#include "StreamReadHandle.h"

namespace
{
    void Seek(std::istream& s, int64_t pos, std::ios::seekdir dir)
    {
        s.seekg(pos, dir);
    }
    
    int64_t Tell(std::istream& s)
    {
        return s.tellg();
    }
}

datarw::StreamReadHandle::StreamReadHandle(std::istream& stream, const bool streamIsDirty /* = false */)
: StreamHandleBase<datarw::DataReadHandle, std::istream>(stream, Seek, Tell, streamIsDirty)
{}

void datarw::StreamReadHandle::peekDataImpl(const Range& range, unsigned char* buffer)
{
    resetStreamIfNeeded(false, range.position);
    
    m_stream.read(reinterpret_cast<char*>(buffer), range.length);
}
