/**************************************************************
 * @file PITypes.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_PITYPES_H
#define GSTONE_PITYPES_H 1

// all types should follow the type definition in RTPS and DCPS specifications
#include <stdint.h>
#include <string>

using gvoid_t	= void;
using gbool_t	= bool;
using guchar_t	= unsigned char;
using gchar_t	= char;
using guint8_t	= unsigned char;
using guint16_t = unsigned short;
using gint16_t	= short;
using guint32_t = uint32_t;
using gint32_t	= int32_t;
using guint64_t = uint64_t;
using gint64_t  = int64_t;
using gstring_t = std::string;
using gchar16_t = char16_t;
using gu16string_t = std::u16string;
using gfloat32_t = float;
using gfloat64_t = double;
using gfloat128_t = long double;

using octet = guint8_t;
using octet4 = octet[4];
using octet16 = octet[16];
using gsize_t = std::size_t;

using sec_octet_t = guchar_t;

/* for windows */
using gpid_t = gint32_t;
using gHANDLE = gvoid_t *;

/*      source           alias        size */
//typedef void           gvoid_t;
//typedef bool           gbool_t;   // 1 byte
//typedef unsigned char  guchar_t;  // 1 byte
//typedef char           gchar_t;   // 1 byte
//typedef unsigned char  guint8_t;  // 1 byte
//typedef unsigned short guint16_t; // 2 bytes
//typedef short		     gint16_t;  // 2 bytes
//typedef unsigned int   guint32_t; // 4 bytes
//typedef int            gint32_t;  // 4 bytes
//typedef uint32_t       guint32_t; // 4 bytes
//typedef int32_t        gint32_t;  // 4 bytes
//typedef uint64_t       guint64_t; // 8 bytes
//typedef int64_t        gint64_t;  // 8 bytes
//typedef std::string    gstring_t;

#endif
