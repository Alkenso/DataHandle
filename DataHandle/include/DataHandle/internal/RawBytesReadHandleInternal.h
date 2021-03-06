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

datarw::RawBytesReadHandle::RawBytesReadHandle(const void* ptr, const uint64_t sizeInBytes, bool copyData /* = false */)
: DataReadHandle()
, m_copyData(copyData)
, m_bufferData(copyData ? datarw::ByteBuffer({ reinterpret_cast<const unsigned char*>(ptr), reinterpret_cast<const unsigned char*>(ptr) + sizeInBytes }) : datarw::ByteBuffer())
, m_constPtr(copyData ? m_bufferData.data() : reinterpret_cast<const unsigned char*>(ptr))
, m_size(sizeInBytes)
{
    if (!m_constPtr && m_size)
    {
        throw std::invalid_argument("Data pointer should not be null");
    }
}

datarw::RawBytesReadHandle::RawBytesReadHandle(RawBytesReadHandle&& r)
: DataReadHandle()
, m_copyData(r.m_copyData)
, m_bufferData(std::move(r.m_bufferData))
, m_constPtr(m_copyData ? m_bufferData.data() : r.m_constPtr)
, m_size(r.m_size)
{}

datarw::RawBytesReadHandle& datarw::RawBytesReadHandle::operator=(RawBytesReadHandle&& r)
{
    DataReadHandle::operator=(std::move(r));
    m_copyData = r.m_copyData;
    m_bufferData = std::move(r.m_bufferData);
    m_constPtr = m_copyData ? m_bufferData.data() : r.m_constPtr;
    m_size = r.m_size;
    
    return *this;
}

void datarw::RawBytesReadHandle::peekDataImpl(const Range& range, void* buffer)
{
    std::copy(m_constPtr + static_cast<size_t>(range.position), m_constPtr + static_cast<size_t>(range.position + range.length), static_cast<unsigned char*>(buffer));
}

uint64_t datarw::RawBytesReadHandle::getDataSizeImpl()
{
    return m_size;
}
