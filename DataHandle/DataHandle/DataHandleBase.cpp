//
//  DataHandleBase.cpp
//  DataHandle
//
//  Created by alk on 5/9/17.
//
//

#include "DataHandleBase.h"

datarw::DataHandleBase::DataHandleBase()
: m_currentPosition(0)
, m_sizePosition(0)
, m_sizePositionIsSet(false)
, m_supportExternalDataSourceChanges(false)
, m_usePositionIsSet(false)
{}

uint64_t datarw::DataHandleBase::getDataSize()
{
    if (m_supportExternalDataSourceChanges)
    {
        return getDataSizeImpl();
    }
    
    if (!m_sizePositionIsSet)
    {
        m_sizePosition = getDataSizeImpl();
        m_sizePositionIsSet = true;
    }
    
    return m_sizePosition;
}

void datarw::DataHandleBase::setSupportExternalDataSourceChanges(const bool support)
{
    m_supportExternalDataSourceChanges = support;
    m_sizePositionIsSet = false;
}

bool datarw::DataHandleBase::getSupportExternalDataSourceChanges()
{
    return m_supportExternalDataSourceChanges;
}

uint64_t datarw::DataHandleBase::seekPosition(const uint64_t position, const bool usePosition, const bool seekForce /* = false */)
{
    uint64_t newPosition = position;
    if (usePosition)
    {
        m_currentPosition += position;
        newPosition = m_currentPosition;
    }
    
    if (seekForce || !m_usePositionIsSet || !usePosition)
    {
        seekPositionOptimized(newPosition);
        m_usePositionIsSet = usePosition;
    }
    
    return newPosition;
}

uint64_t datarw::DataHandleBase::tellPosition()
{
    return m_currentPosition;
}

void datarw::DataHandleBase::seekPositionOptimized(const uint64_t)
{}
