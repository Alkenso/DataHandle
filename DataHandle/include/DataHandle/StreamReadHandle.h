//
//  StreamReadHandle.h
//  DataHandle
//
//  Created by Alkenso on 5/5/17.
//
//

#pragma once

#include <istream>

#include <DataHandle/DataReadHandle.h>
#include <DataHandle/internal/StreamHandleBase.h>

namespace datarw
{
    class StreamReadHandle : public StreamHandleBase<datarw::DataReadHandle, std::istream>
    {
    public:
        explicit StreamReadHandle(std::istream& stream, const bool streamIsDirty = false);

    private:
        virtual void peekDataImpl(const Range& range, unsigned char* buffer) final;
        
    private:
        virtual void seek(std::istream& stream, const int64_t pos, const std::ios::seekdir dir) final;
        virtual int64_t tell(std::istream& stream) final;
    };
}
