//
//  ContainerWriteHandleInternal.h
//  DataHandle
//
//  Created by Alkenso on 5/9/17.
//
//

#pragma once

template <typename Container>
datarw::ContainerWriteHandle<Container>::ContainerWriteHandle()
: m_container()
, m_containerRef(m_container)
{}

template <typename Container>
datarw::ContainerWriteHandle<Container>::ContainerWriteHandle(Container& container, const bool copyData /* = false */)
: m_container(copyData ? container : Container())
, m_containerRef(copyData ? m_container : container)
{}

template <typename Container>
datarw::ContainerWriteHandle<Container>::ContainerWriteHandle(const Container& container)
: m_container(container)
, m_containerRef(m_container)
{}

template <typename Container>
datarw::ContainerWriteHandle<Container>::ContainerWriteHandle(Container&& container)
: m_container(container)
, m_containerRef(m_container)
{}

template <typename Container>
const Container& datarw::ContainerWriteHandle<Container>::getContainer()
{
    return m_containerRef;
}

template <typename Container>
void datarw::ContainerWriteHandle<Container>::writeDataImpl(const unsigned char* data, const datarw::Range& range)
{
    m_containerRef.resize(std::max(static_cast<size_t>(range.position + range.length), m_containerRef.size()));
    std::copy(data, data + static_cast<size_t>(range.length), m_containerRef.begin() + static_cast<size_t>(range.position));
}

template <typename Container>
uint64_t datarw::ContainerWriteHandle<Container>::getDataSizeImpl()
{
    return m_containerRef.size();
}
