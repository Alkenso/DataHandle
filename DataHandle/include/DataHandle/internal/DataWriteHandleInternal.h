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
