//
//  DataWriteHandleInternal.h
//  DataHandle
//
//  Created by Alkenso on 5/9/17.
//
//

#pragma once
    
template <typename Data, typename>
void datarw::DataWriteHandle::insertData(const Data* data, const uint64_t dataSize, const uint64_t offset)
{
    insertDataInternal(reinterpret_cast<const unsigned char*>(data), dataSize, offset, false);
}

template <typename Buffer, typename>
void datarw::DataWriteHandle::insertData(const Buffer& buffer, int64_t offset)
{
    insertData(buffer.data(), buffer.size(), offset);
}

template <typename Data, typename>
void datarw::DataWriteHandle::writeData(const Data* data, const uint64_t dataSize)
{
    insertDataInternal(reinterpret_cast<const unsigned char*>(data), dataSize, 0, true);
}

template <typename Buffer, typename>
void datarw::DataWriteHandle::writeData(const Buffer& buffer)
{
    writeData(buffer.data(), buffer.size());
}

template<typename T>
void datarw::DataWriteHandle::insertValue(const T& value, const int64_t offset)
{
    insertData(reinterpret_cast<const unsigned char*>(&value), sizeof(T), offset);
}

template<typename T>
void datarw::DataWriteHandle::writeValue(const T& value)
{
    writeData(reinterpret_cast<const unsigned char*>(&value), sizeof(T));
}

template<typename T>
void datarw::DataWriteHandle::insertValueBE(const T& value, const int64_t offset)
{
    insertValue<T>(utils::ReverseValueByteOrder(value), offset);
}

template<typename T>
void datarw::DataWriteHandle::writeValueBE(const T& value)
{
    writeValue<T>(utils::ReverseValueByteOrder(value));
}
