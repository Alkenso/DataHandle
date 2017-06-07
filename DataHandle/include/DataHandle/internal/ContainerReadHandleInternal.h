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
