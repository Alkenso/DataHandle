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

#include <string>
#include <mutex>

#include <DataHandle/internal/DataHandleBase.h>

namespace datarw
{
    class DataWriteHandle : public DataHandleBase
    {
    public:
        virtual ~DataWriteHandle() {}
        
        uint64_t getDataSize();
        
        template <TYPE_RAW_BYTES(Data)>
        void writeData(const Data* data, const uint64_t dataSize, const uint64_t offset);
        template <TYPE_BYTE_BUFFER(Buffer)>
        void writeData(const Buffer& buffer, uint64_t offset);
        void writeString(const std::string& str, uint64_t offset, const bool withNullTerminator = false);
        
        template <TYPE_RAW_BYTES(Data)>
        void writeData(const Data* data, const uint64_t dataSize);
        template <TYPE_BYTE_BUFFER(Buffer)>
        void writeData(const Buffer& buffer);
        void writeString(const std::string& str, const bool withNullTerminator = false);
        
        template<typename T>
        void writeValueLE(const T& value, const uint64_t offset);
        template<typename T>
        void writeValueLE(const T& value);
        
        template<typename T>
        void writeValueBE(const T& value, const uint64_t offset);
        template<typename T>
        void writeValueBE(const T& value);
        
    protected:
        DataWriteHandle();
        virtual uint64_t tellPosition() final;
        
    private:
        virtual uint64_t getDataSizeImpl() override = 0;
        virtual void writeDataImpl(const unsigned char* data, const Range& range) = 0;
        virtual void seekPositionOptimized(const uint64_t position) override;
        
    private:
        void insertDataInternal(const unsigned char* data, const uint64_t dataSize, const uint64_t offset, const bool usePosition);
        uint64_t seekPosition(const uint64_t offset, const bool usePosition);
        void initPosition();
        
        template<typename T>
        void writeValue(const T& value, const uint64_t offset, const bool reverseByteOrder);
        template<typename T>
        void writeValue(const T& value, const bool reverseByteOrder);
        
    private:
        uint64_t m_position;
        bool m_usePositionIsSet;
        std::once_flag m_inited;
    };
}

#include <DataHandle/internal/DataWriteHandleInternal.h>
