/**************************************************************
* @file TypeKind.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_TYPE_KIND_API_H_
#define GSTONE_TYPE_KIND_API_H_ 1

#include <string>

#include "dcps/PITypes.h"
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace xtypes
{
    using TypeKind = guint8_t;
    // Primitive TKs
    TypeKind const TK_NONE { 0x0U };
    TypeKind const TK_BOOLEAN { 0x01U };
    TypeKind const TK_BYTE { 0x02U };
    TypeKind const TK_INT16 { 0x03U };
    TypeKind const TK_INT32 { 0x04U };
    TypeKind const TK_INT64 { 0x05U };
    TypeKind const TK_UINT16 { 0x06U };
    TypeKind const TK_UINT32 { 0x07U };
    TypeKind const TK_UINT64 { 0x08U };
    TypeKind const TK_FLOAT32 { 0x09U };
    TypeKind const TK_FLOAT64 { 0x0AU };
    TypeKind const TK_FLOAT128 { 0x0BU };
    TypeKind const TK_INT8 { 0x0CU };
    TypeKind const TK_UINT8 { 0x0DU };
    TypeKind const TK_CHAR8 { 0x10U };
    TypeKind const TK_CHAR16 { 0x11U };
    // String TKs
    TypeKind const TK_STRING8 { 0x20U };
    TypeKind const TK_STRING16 { 0x21U };
    // Constructed/Named types
    TypeKind const TK_ALIAS { 0x30U };
    // Enumerated TKs
    TypeKind const TK_ENUM { 0x40U };
    TypeKind const TK_BITMASK { 0x41U };
    // Structured TKs
    TypeKind const TK_ANNOTATION { 0x50U };
    TypeKind const TK_STRUCTURE { 0x51U };
    TypeKind const TK_UNION { 0x52U };
    TypeKind const TK_BITSET { 0x53U };
    // Collection TKs
    TypeKind const TK_SEQUENCE { 0x60U };
    TypeKind const TK_ARRAY { 0x61U };
    TypeKind const TK_MAP { 0x62U };
    // Autoid kind
    enum class AutoidKind : gint32_t
    {
        SEQUENTIAL, 
        HASH
    };
} //namespace xtypes
} //namespace dds

__GS_DDS4CPP_END_DECLS

#endif // GSTONE_TYPE_KIND_API_H_

