/*
 * Copyright (c) 2017 Alkenso (Vashurkin Vladimir)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "StreamWriteHandle.h"

datarw::StreamWriteHandle::StreamWriteHandle(std::ostream& stream, const bool streamIsDirty /* = false */)
: StreamHandleBase<datarw::DataWriteHandle, std::ostream>(stream, streamIsDirty)
{}

datarw::StreamWriteHandle::StreamWriteHandle(StreamWriteHandle&& r)
: StreamHandleBase<datarw::DataWriteHandle, std::ostream>(std::move(r))
{}

datarw::StreamWriteHandle& datarw::StreamWriteHandle::operator=(StreamWriteHandle&& r)
{
    StreamHandleBase<datarw::DataWriteHandle, std::ostream>::operator=(std::move(r));

    return *this;
}

void datarw::StreamWriteHandle::writeDataImpl(const void* data, const Range& range)
{
    resetStreamIfNeeded(false, range.position);
    
    const char* dataPtr = static_cast<const char*>(data);
    m_stream.get().write(reinterpret_cast<const char*>(dataPtr), range.length);
}

void datarw::StreamWriteHandle::seek(std::ostream& stream, const int64_t pos, const std::ios::seekdir dir)
{
    stream.seekp(pos, dir);
}

int64_t datarw::StreamWriteHandle::tell(std::ostream& stream)
{
    return stream.tellp();
}
