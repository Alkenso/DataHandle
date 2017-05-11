//
//  StreamReadHandle.h
//  DataHandle
//
//  Created by alk on 5/5/17.
//
//

#pragma once

#include <istream>

#include "DataReadHandle.h"
#include "StreamHandleBase.h"

namespace datarw
{
    class StreamReadHandle : public StreamHandleBase<datarw::DataReadHandle, std::istream>
    {
    public:
        explicit StreamReadHandle(std::istream& stream, const bool streamIsDirty = false);

    private:
        virtual void peekDataImpl(const Range& range, unsigned char* buffer) override;
    };
}
