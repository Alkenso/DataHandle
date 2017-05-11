//
//  DataHandleUtils.h
//  DataHandle
//
//  Created by Alkenso on 5/5/17.
//
//

#pragma once

#include "DataTypes.h"

namespace datarw
{
    namespace utils
    {
        template<typename T>
        T ReverseValueByteOrder(T value)
        {
            uint8_t* valuePtr = reinterpret_cast<uint8_t*>(&value);
            std::reverse(valuePtr, valuePtr + sizeof(value));
            
            return value;
        }
        
        bool RangesIntersects(const datarw::Range& range1, const datarw::Range& range2);
        datarw::Range RangesIntersection(const datarw::Range& range1, const datarw::Range& range2);
        bool RangesAreEqual(const datarw::Range& range1, const datarw::Range& range2);
        datarw::Range RangeWithAdditionalOffset(const datarw::Range& range, int64_t offset);
    }
}
