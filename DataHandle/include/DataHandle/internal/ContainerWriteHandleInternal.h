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

template <typename Container>
datarw::ContainerWriteHandle<Container>::ContainerWriteHandle(IsByteContainer<Container>& container, const bool copyData /* = false */)
: DataWriteHandle()
, m_copyData(copyData)
, m_container(copyData ? container : Container())
, m_containerRef(copyData ? m_container : container)
{}

template <typename Container>
datarw::ContainerWriteHandle<Container>::ContainerWriteHandle(const IsByteContainer<Container>& container)
: DataWriteHandle()
, m_copyData(true)
, m_container(container)
, m_containerRef(m_container)
{}

template <typename Container>
datarw::ContainerWriteHandle<Container>::ContainerWriteHandle(IsByteContainer<Container>&& container)
: DataWriteHandle()
, m_copyData(true)
, m_container(container)
, m_containerRef(m_container)
{}

template <typename Container>
datarw::ContainerWriteHandle<Container>::ContainerWriteHandle(ContainerWriteHandle&& r)
: DataWriteHandle()
, m_copyData(r.m_copyData)
, m_container(m_copyData ? std::move(r.m_container) : Container())
, m_containerRef(m_copyData ? std::ref(m_container) : r.m_containerRef)
{}

template <typename Container>
datarw::ContainerWriteHandle<Container>& datarw::ContainerWriteHandle<Container>::operator=(ContainerWriteHandle&& r)
{
    DataWriteHandle::operator=(std::move(r));
    
    m_copyData = r.m_copyData;
    m_container = m_copyData ? std::move(r.m_container) : Container();
    m_containerRef = m_copyData ? std::ref(m_container) : r.m_containerRef;
    
    return *this;
}

template <typename Container>
const datarw::IsByteContainer<Container>& datarw::ContainerWriteHandle<Container>::getContainer()
{
    return m_containerRef;
}

template <typename Container>
void datarw::ContainerWriteHandle<Container>::writeDataImpl(const void* data, const datarw::Range& range)
{
    Container& containerRef = m_containerRef.get();
    containerRef.resize(std::max(static_cast<size_t>(range.position + range.length), containerRef.size()));
    
    const typename Container::value_type* dataPtr = static_cast<const typename Container::value_type*>(data);
    std::copy(dataPtr, dataPtr + static_cast<size_t>(range.length), containerRef.begin() + static_cast<size_t>(range.position));
}

template <typename Container>
uint64_t datarw::ContainerWriteHandle<Container>::getDataSizeImpl()
{
    return m_containerRef.get().size();
}
