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

#include <functional>
#include <DataHandle/DataWriteHandle.h>

namespace datarw
{
    template <typename Container>
    class ContainerWriteHandle : public DataWriteHandle
    {
    public:
        explicit ContainerWriteHandle(IsByteContainer<Container>& container, const bool copyData = false);
        explicit ContainerWriteHandle(const IsByteContainer<Container>& container = {});
        explicit ContainerWriteHandle(IsByteContainer<Container>&& container);
        
        ContainerWriteHandle(ContainerWriteHandle&& r);
        ContainerWriteHandle& operator=(ContainerWriteHandle&& r);

        const IsByteContainer<Container>& getContainer();

    private:
        virtual void writeDataImpl(const void* data, const datarw::Range& range) final;
        virtual uint64_t getDataSizeImpl() final;

    private:
        bool m_copyData;
        IsByteContainer<Container> m_container;
        std::reference_wrapper<Container> m_containerRef;
    };
    
    using VectorWriteHandle = ContainerWriteHandle<datarw::ByteBuffer>;
    using StringWriteHandle = ContainerWriteHandle<std::string>;
}

#include <DataHandle/internal/ContainerWriteHandleInternal.h>
