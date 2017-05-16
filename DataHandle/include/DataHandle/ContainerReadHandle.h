//
//  ContainerReadHandle.h
//  DataHandle
//
//  Created by Alkenso on 5/9/17.
//
//

#pragma once

#include <string>

#include <DataHandle/DataReadHandle.h>

namespace datarw
{
    template <typename Container>
    class ContainerReadHandle : public DataReadHandle
    {
    public:
        explicit ContainerReadHandle(const Container& bufferData, bool copyData = false);
        explicit ContainerReadHandle(Container&& bufferData);

    private:
        virtual void peekDataImpl(const Range& range, unsigned char* buffer);
        virtual uint64_t getDataSizeImpl();

    private:
        const Container m_bufferData;
        const Container& m_bufferDataRef;
    };
    
    using VectorReadHandle = ContainerReadHandle<datarw::ByteBuffer>;
    using StringReadHandle = ContainerReadHandle<std::string>;
}

#include <DataHandle/internal/ContainerReadHandleInternal.h>
