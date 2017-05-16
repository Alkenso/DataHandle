//
//  RawBytesReadHandleInternal.h
//  DataHandle
//
//  Created by Alkenso on 5/5/17.
//
//

#pragma once

template <typename T>
datarw::RawBytesReadHandle::RawBytesReadHandle(const T* ptr, const uint64_t sizeInBytes, bool copyData /* = false */)
: DataReadHandle()
, m_bufferData(copyData ? datarw::ByteBuffer({ reinterpret_cast<const unsigned char*>(ptr), reinterpret_cast<const unsigned char*>(ptr) + sizeInBytes }) : datarw::ByteBuffer())
, m_constPtr(copyData ? m_bufferData.data() : ptr)
, m_size(sizeInBytes)
{
    if (!m_constPtr)
    {
        throw std::invalid_argument("Data pointer should not be null");
    }
}

void datarw::RawBytesReadHandle::peekDataImpl(const Range& range, unsigned char* buffer)
{
    std::copy(m_constPtr + static_cast<size_t>(range.position), m_constPtr + static_cast<size_t>(range.position + range.length), buffer);
}

uint64_t datarw::RawBytesReadHandle::getDataSizeImpl()
{
    return m_size;
}
