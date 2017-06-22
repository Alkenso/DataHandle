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
datarw::ContainerReadHandle<Container>::ContainerReadHandle(const IsByteContainer<Container>& container, bool copyData)
: DataReadHandle()
, m_copyData(copyData)
, m_container(copyData ? container : Container())
, m_containerRef(copyData ? m_container : container)
{}

template <typename Container>
datarw::ContainerReadHandle<Container>::ContainerReadHandle(IsByteContainer<Container>&& container)
: DataReadHandle()
, m_copyData(true)
, m_container(container)
, m_containerRef(m_container)
{}


template <typename Container>
datarw::ContainerReadHandle<Container>::ContainerReadHandle(ContainerReadHandle&& r)
: DataReadHandle()
, m_copyData(r.m_copyData)
, m_container(m_copyData ? std::move(r.m_container) : Container())
, m_containerRef(m_copyData ? std::cref(m_container) : r.m_containerRef)
{}

template <typename Container>
datarw::ContainerReadHandle<Container>& datarw::ContainerReadHandle<Container>::operator=(ContainerReadHandle&& r)
{
    DataReadHandle::operator=(std::move(r));
    
    m_copyData = r.m_copyData;
    m_container = m_copyData ? std::move(r.m_container) : Container();
    m_containerRef = m_copyData ? std::cref(m_container) : r.m_containerRef;
    
    return *this;
}

template <typename Container>
void datarw::ContainerReadHandle<Container>::peekDataImpl(const Range& range, void* buffer)
{
    const Container& containerRef = m_containerRef.get();
    std::copy(containerRef.begin() + static_cast<size_t>(range.position), containerRef.begin() + static_cast<size_t>(range.position + range.length), static_cast<typename Container::value_type*>(buffer));
}

template <typename Container>
uint64_t datarw::ContainerReadHandle<Container>::getDataSizeImpl()
{
    return m_containerRef.get().size();
}
