/**************************************************************
* @file TypeDefs.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_TYPE_DEFS_API_H_
#define GSTONE_TYPE_DEFS_API_H_ 1

#include <cstdint>
#include <array>
#include <vector>
#include <cstring>
#include <bitset>
#include <stdexcept>
#include <cmath>
#include <algorithm>

#include "dcps/PITypes.h"
#include "dcps/DeclExport.h"
#include "dcps/DdsBaseTypes.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace xtypes
{
    
    using MemberId = guint32_t;
    using EquivalenceKind = octet;

    guint32_t const MEMBER_ID_INVALID { 0X0FFFFFFFU };
    guint32_t const INDEX_INVALID { UINT32_MAX };
    guint32_t const MAX_STRING_LENGTH { 255U };
    guint32_t const MAX_BITMASK_LENGTH { 64U };
    guint32_t const MAX_ELEMENTS_COUNT { 100U };
    guint32_t const BOUND_UNLIMITED { 0U };

    octet const EK_MINIMAL { 0xF1U }; // 0x1111 0001
    octet const EK_COMPLETE { 0xF2U }; // 0x1111 0010
    octet const EK_BOTH { 0xF3U }; // 0x1111 0011

    guint16_t const MEMBER_FLAG_LIMIT { 16U };
    guint16_t const MEMBER_FLAG_TRY_CONSTRUCT1 { 0U };
    guint16_t const MEMBER_FLAG_TRY_CONSTRUCT2 { 1U };
    guint16_t const MEMBER_FLAG_IS_EXTERNAL { 2U };
    guint16_t const MEMBER_FLAG_IS_OPTIONAL { 3U };
    guint16_t const MEMBER_FLAG_IS_MUST_UNDERSTAND { 4U };
    guint16_t const MEMBER_FLAG_IS_KEY { 5U };
    guint16_t const MEMBER_FLAG_IS_DEFAULT { 6U };

    guint16_t const TYPE_FLAG_LIMIT { 16U };
    guint16_t const TYPE_FLAG_IS_FINAL { 0U };
    guint16_t const TYPE_FLAG_IS_APPENDABLE { 1U };
    guint16_t const TYPE_FLAG_IS_MUTABLE { 2U };
    guint16_t const TYPE_FLAG_IS_NESTED { 3U };
    guint16_t const TYPE_FLAG_IS_AUTOID_HASH { 4U };

    // The name of some element (e.g. type, type member, module)
    // Valid characters are alphanumeric plus the "_" cannot start with digit
    gint64_t const MEMBER_NAME_MAX_LENGTH { 256L };
    using MemberName = gstring_t;

    // Qualified type name includes the name of containing modules
    // using "::" as separator. No leading "::". E.g. "MyModule::MyType"
    gint64_t const TYPE_NAME_MAX_LENGTH { 256L };
    using QualifiedTypeName = gstring_t;

    // First 4 bytes of MD5 of of a member name converted to bytes
    // using UTF-8 encoding and without a 'nul' terminator.
    // Example: the member name "color" has NameHash {0x70, 0xDD, 0xA5, 0xDF}
    guint8_t const NAME_HASH_LIMIT { 4U }; 
    using NameHash = std::array<uint8_t, NAME_HASH_LIMIT>;

    // Long Bound of a collection type
    using LBound = guint32_t;
    using LBoundSeq = std::vector<LBound>;
    LBound const INVALID_LBOUND { 0U };

    // Short Bound of a collection type
    using SBound = octet;
    using SBoundSeq = std::vector<SBound>;
    SBound const INVALID_SBOUND { 0U };

    octet const TI_STRING8_SMALL { 0x70U };
    octet const TI_STRING8_LARGE { 0x71U };
    octet const TI_STRING16_SMALL { 0x72U };
    octet const TI_STRING16_LARGE { 0x73U };
    octet const TI_PLAIN_SEQUENCE_SMALL { 0x80U };
    octet const TI_PLAIN_SEQUENCE_LARGE { 0x81U };
    octet const TI_PLAIN_ARRAY_SMALL { 0x90U };
    octet const TI_PLAIN_ARRAY_LARGE { 0x91U };
    octet const TI_PLAIN_MAP_SMALL { 0xA0U };
    octet const TI_PLAIN_MAP_LARGE { 0xA1U };
    octet const TI_STRONGLY_CONNECTED_COMPONENT { 0xB0U };
    /**
     * @brief This function converts a string object into a wide string object.
     * @param [in] s The string object to be converted.
     * @return gu16string_t The wide string object where the result returned.
     */
    inline gu16string_t wstring_from_bytes(gstring_t const &s)
    {
        if (s.empty())
        {
            return ( gu16string_t {} );
        }
        size_t const length { s.size() };
        gu16string_t result;
        result.resize(length);
        for (size_t i { 0U }; i < length; i++)
        {
            result[i] = static_cast<gchar16_t>(s[i]);
        }
        return result;
    }
    /**
     * @brief This function converts a wide string object into a string object.
     * @param [in] ws The wide string object to be converted.
     * @return gstring_t The string object where the result returned.
     */
    inline gstring_t wstring_to_bytes(gu16string_t const &ws)
    {
        if (ws.empty())
        {
            return ( gstring_t {} );
        }
        size_t const length { ws.size() };
        gstring_t result;
        result.resize(length);
        for (size_t i { 0U }; i < length; i++)
        {
            result[i] = static_cast<gchar_t>(ws[i]);
        }
        return result;
    }
    /**
     * @brief This function tell you if two 32-bit floating point value is equal or not.
     * @param [in] lv One float value to compare.
     * @param [in] rv Another float value to compare.
     * @return true If two float value is same. 
     */
    inline gbool_t float_is_equal_32(gfloat32_t const lv, gfloat32_t const rv) noexcept
    {
        gfloat32_t const epsilon { std::numeric_limits<gfloat32_t>::epsilon() };
        return std::fabs(lv - rv) <= epsilon;
    }
    /**
     * @brief This function tell you if two 64-bit floating point value is equal or not.
     * @param [in] lv One float value to compare.
     * @param [in] rv Another float value to compare.
     * @return true If two float value is same. 
     */
    inline gbool_t float_is_equal_64(gfloat64_t const lv, gfloat64_t const rv) noexcept
    {
        gfloat64_t const epsilon { std::numeric_limits<gfloat64_t>::epsilon() };
        return std::fabs(lv - rv) <= epsilon;
    }
    /**
     * @brief This function tell you if two 128-bit floating point value is equal or not.
     * @param [in] lv One float value to compare.
     * @param [in] rv Another float value to compare.
     * @return true If two float value is same. 
     */
    inline gbool_t float_is_equal_128(gfloat128_t const lv, gfloat128_t const rv) noexcept
    {
        gfloat128_t const epsilon { std::numeric_limits<gfloat128_t>::epsilon() }; 
        return std::fabs(lv - rv) <= epsilon;
    }
} // namespace xtypes
} // namespace dds

__GS_DDS4CPP_END_DECLS

#endif // GSTONE_TYPE_DEFS_API_H_

