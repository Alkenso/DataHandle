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

#pragma once

#include <ostream>

#include <DataHandle/DataWriteHandle.h>
#include <DataHandle/internal/StreamHandleBase.h>

namespace datarw
{
    class StreamWriteHandle : public StreamHandleBase<datarw::DataWriteHandle, std::ostream>
    {
    public:
        explicit StreamWriteHandle(std::ostream& stream, const bool streamIsDirty = false);
        
    private:
        virtual void writeDataImpl(const unsigned char* data, const Range& range) final;
        
    private:
        virtual void seek(std::ostream& stream, const int64_t pos, const std::ios::seekdir dir) final;
        virtual int64_t tell(std::ostream& stream) final;
    };
}
