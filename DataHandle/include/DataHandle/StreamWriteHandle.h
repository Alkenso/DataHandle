//
//  StreamWriteHandle.h
//  DataHandle
//
//  Created by Alkenso on 5/5/17.
//
//

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
