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

#include "ComposeWriteHandle.h"

datarw::ComposeWriteHandle::ComposeWriteHandle(std::initializer_list<std::reference_wrapper<DataWriteHandle>> writers)
: datarw::DataWriteHandle()
, m_writers(writers)
{}

datarw::ComposeWriteHandle::ComposeWriteHandle(ComposeWriteHandle&& r)
: datarw::DataWriteHandle(std::move(r))
, m_writers(std::move(r.m_writers))
{}

datarw::ComposeWriteHandle& datarw::ComposeWriteHandle::operator=(ComposeWriteHandle&& r)
{
    DataWriteHandle::operator=(std::move(r));
    m_writers = std::move(r.m_writers);

    return *this;
}

uint64_t datarw::ComposeWriteHandle::getDataSizeImpl()
{
    uint64_t maxWriterSize = 0;
    for (DataWriteHandle& writer : m_writers)
    {
        maxWriterSize = std::max(maxWriterSize, writer.getDataSize());
    }
    
    return maxWriterSize;
}

void datarw::ComposeWriteHandle::writeDataImpl(const void* data, const Range& range)
{
    for (DataWriteHandle& writer : m_writers)
    {
        writer.writeData(data, range.length, range.position);
    }
}
