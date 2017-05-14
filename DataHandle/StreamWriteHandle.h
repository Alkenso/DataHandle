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
#include <DataHandle/StreamHandleBase.h>

namespace datarw
{
    class StreamWriteHandle : public StreamHandleBase<datarw::DataWriteHandle, std::ostream>
    {
    public:
        explicit StreamWriteHandle(std::ostream& stream, const bool streamIsDirty = false);
        
    private:
        virtual void insertDataImpl(const unsigned char* data, const Range& range) override;
    };
}
