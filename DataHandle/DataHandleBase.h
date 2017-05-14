//
//  DataHandleBase.h
//  DataHandle
//
//  Created by Alkenso on 5/9/17.
//
//

#pragma once

#include <DataHandle/DataTypes.h>

namespace datarw
{
    class DataHandleBase
    {
    public:
        virtual ~DataHandleBase() {}
        
        uint64_t getDataSize();
        
        /* Enable data source changes support if underlying data size might be changed during working with it.
         * Warning: enabling this option can significantly decrease performance with some data sources. */
        void setSupportExternalDataSourceChanges(const bool support);
        bool getSupportExternalDataSourceChanges();
        
    protected:
        DataHandleBase();
        uint64_t seekPosition(const uint64_t offset, const bool usePosition, const bool seekForce = false);
        uint64_t tellPosition();
        
    private:
        virtual uint64_t getDataSizeImpl() = 0;
        
        /* Some data sources (e.g. streams, files) have native implementation of seeking / reading consistent data.
         * Overriding 'seekPositionOptimized' allows derived classes to ignore range.position in 'peekDataImpl' implementation.
         * That allows native seek implmenetation to be called only when needed. */
        virtual void seekPositionOptimized(const uint64_t position);
        
    private:
        uint64_t m_currentPosition;
        uint64_t m_sizePosition;
        uint64_t m_sizePositionIsSet;
        bool m_supportExternalDataSourceChanges;
        bool m_usePositionIsSet;
    };
    
    namespace utils
    {
        template<typename T>
        T ReverseValueByteOrder(T value)
        {
            uint8_t* valuePtr = reinterpret_cast<uint8_t*>(&value);
            std::reverse(valuePtr, valuePtr + sizeof(value));
            
            return value;
        }
    }
}
