//
//  DataWriteHandleInternal.h
//  DataHandle
//
//  Created by Alkenso on 5/9/17.
//
//

#pragma once
    
template <TYPE_RAW_BYTES_IMPL(Data)>
void datarw::DataWriteHandle::writeData(const Data* data, const uint64_t dataSize, const uint64_t offset)
{
    insertDataInternal(reinterpret_cast<const unsigned char*>(data), dataSize, offset, false);
}

template <TYPE_BYTE_BUFFER_IMPL(Buffer)>
void datarw::DataWriteHandle::writeData(const Buffer& buffer, uint64_t offset)
{
    writeData(buffer.data(), buffer.size(), offset);
}

template <TYPE_RAW_BYTES_IMPL(Data)>
void datarw::DataWriteHandle::writeData(const Data* data, const uint64_t dataSize)
{
    insertDataInternal(reinterpret_cast<const unsigned char*>(data), dataSize, 0, true);
}

template <TYPE_BYTE_BUFFER_IMPL(Buffer)>
void datarw::DataWriteHandle::writeData(const Buffer& buffer)
{
    writeData(buffer.data(), buffer.size());
}

template<typename T>
void datarw::DataWriteHandle::writeValueLE(const T& value, const uint64_t offset)
{
    writeValue<T>(value, offset, IS_BIG_ENDIAN);
}

template<typename T>
void datarw::DataWriteHandle::writeValueLE(const T& value)
{
    writeValue<T>(value, IS_BIG_ENDIAN);
}

template<typename T>
void datarw::DataWriteHandle::writeValueBE(const T& value, const uint64_t offset)
{
    writeValue<T>(value, offset, !IS_BIG_ENDIAN);
}

template<typename T>
void datarw::DataWriteHandle::writeValueBE(const T& value)
{
    writeValue<T>(value, !IS_BIG_ENDIAN);
}

template<typename T>
void datarw::DataWriteHandle::writeValue(const T& value, const uint64_t offset, const bool reverseByteOrder)
{
    const T& theValue = reverseByteOrder ? utils::ReverseValueByteOrder<T>(value) : value;
    writeData(reinterpret_cast<const unsigned char*>(&theValue), sizeof(T), offset);
}

template<typename T>
void datarw::DataWriteHandle::writeValue(const T& value, const bool reverseByteOrder)
{
    const T& theValue = reverseByteOrder ? utils::ReverseValueByteOrder<T>(value) : value;
    writeData(reinterpret_cast<const unsigned char*>(&theValue), sizeof(T));
}
