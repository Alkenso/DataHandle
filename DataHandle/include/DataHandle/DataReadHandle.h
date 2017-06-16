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

#include <DataHandle/internal/DataHandleBase.h>

namespace datarw
{
    class DataReadHandle : public DataHandleBase
    {
    public:
        virtual ~DataReadHandle() {}
        
        uint64_t getDataSize();
        
        template <TYPE_RAW_BYTES(Data)>
        void peekData(const Range& range, Data* data);
        template <TYPE_BYTE_BUFFER(Buffer)>
        void peekData(const Range& range, Buffer& buffer);
        template <TYPE_BYTE_BUFFER(Buffer)>
        void peekAppendData(const Range& range, Buffer& buffer);
        template <TYPE_BYTE_BUFFER(Result)>
        Result peekData(const Range& range);
        
        template <TYPE_RAW_BYTES(Data)>
        void readData(const uint64_t dataSize, Data* data);
        template <TYPE_BYTE_BUFFER(Buffer)>
        void readData(const uint64_t dataSize, Buffer& buffer);
        template <TYPE_BYTE_BUFFER(Buffer)>
        void appendData(const uint64_t dataSize, Buffer& buffer);
        template <TYPE_BYTE_BUFFER(Result)>
        Result readData(const uint64_t dataSize);
        
        template <TYPE_RAW_BYTES(Data)>
        void readAllData(Data* data);
        template <TYPE_BYTE_BUFFER(Buffer)>
        void readAllData(Buffer& buffer);
        template <TYPE_BYTE_BUFFER(Buffer)>
        void appendAllData(Buffer& buffer);
        template <TYPE_BYTE_BUFFER(Result)>
        Result readAllData();
        
        template<typename T>
        T peekValueLE(int64_t offset);
        template<typename T>
        T peekValueFromCurrentLE(int64_t offset);
        template<typename T>
        T readValueLE();
        
        template<typename T>
        T peekValueBE(int64_t offset);
        template<typename T>
        T peekValueFromCurrentBE(int64_t offset);
        template<typename T>
        T readValueBE();
        
        void skipBytes(const uint64_t skipSize);
        uint64_t getRemainingSize();
        bool enshureRemainingSize(uint64_t expectedRemainingSize);
        
    protected:
        DataReadHandle();
        DataReadHandle(DataReadHandle&& r) = default;
        DataReadHandle& operator=(DataReadHandle&& r) = default;
        
        virtual uint64_t tellPosition() final;
        
    private:
        virtual uint64_t getDataSizeImpl() override = 0 ;
        virtual void peekDataImpl(const Range& range, unsigned char* buffer) = 0;
        virtual void seekPositionOptimized(const uint64_t position) override;
        
    private:
        void peekDataInternal(const Range& range, unsigned char* buffer, const bool usePosition);
        void readDataInternal(const uint64_t dataSize, unsigned char* buffer);
        uint64_t seekPosition(const uint64_t offset, const bool usePosition, const bool seekForce = false);
        
        template<typename T>
        T peekValue(int64_t offset, const bool reverseByteOrder);
        template<typename T>
        T peekValueFromCurrent(int64_t offset, const bool reverseByteOrder);
        template<typename T>
        T readValue(const bool reverseByteOrder);
        
    private:
        uint64_t m_sizePosition;
        uint64_t m_sizePositionIsSet;
        uint64_t m_currentPosition;
        bool m_usePositionIsSet;
    };
}

#include <DataHandle/internal/DataReadHandleInternal.h>
