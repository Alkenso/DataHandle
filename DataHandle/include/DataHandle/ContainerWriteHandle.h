//
//  ContainerWriteHandle.h
//  DataHandle
//
//  Created by Alkenso on 5/9/17.
//
//

#pragma once

#include <DataHandle/DataWriteHandle.h>

namespace datarw
{
    template <typename Container>
    class ContainerWriteHandle : public DataWriteHandle
    {
    public:
        ContainerWriteHandle();
        explicit ContainerWriteHandle(Container& container, const bool copyData = false);
        explicit ContainerWriteHandle(const Container& container);
        explicit ContainerWriteHandle(Container&& container);

        const Container& getContainer();

    private:
        virtual void insertDataImpl(const unsigned char* data, const datarw::Range& range);
        virtual uint64_t getDataSizeImpl();

    private:
        Container m_container;
        Container& m_containerRef;
    };
    
    using VectorWriteHandle = ContainerWriteHandle<datarw::ByteBuffer>;
    using StringWriteHandle = ContainerWriteHandle<std::string>;
}

#include <DataHandle/internal/ContainerWriteHandleInternal.h>
