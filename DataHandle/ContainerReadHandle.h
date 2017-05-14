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
    
    template <typename Container>
    datarw::ContainerReadHandle<Container>::ContainerReadHandle(const Container& bufferData, bool copyData)
    : DataReadHandle()
    , m_bufferData(copyData ? bufferData : Container())
    , m_bufferDataRef(copyData ? m_bufferData : bufferData)
    {}
    
    template <typename Container>
    datarw::ContainerReadHandle<Container>::ContainerReadHandle(Container&& bufferData)
    : DataReadHandle()
    , m_bufferData(bufferData)
    , m_bufferDataRef(m_bufferData)
    {}
    
    template <typename Container>
    void datarw::ContainerReadHandle<Container>::peekDataImpl(const Range& range, unsigned char* buffer)
    {
        std::copy(m_bufferDataRef.begin() + static_cast<size_t>(range.position), m_bufferDataRef.begin() + static_cast<size_t>(range.position + range.length), buffer);
    }
    
    template <typename Container>
    uint64_t datarw::ContainerReadHandle<Container>::getDataSizeImpl()
    {
        return m_bufferDataRef.size();
    }
    
    using VectorReadHandle = ContainerReadHandle<datarw::ByteBuffer>;
    using StringReadHandle = ContainerReadHandle<std::string>;
}
