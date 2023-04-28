/**************************************************************
 * @file SerializedPayloadHeader.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_RTPS_SERIALIZEDPAYLOADHEADER_API_H
#define GSTONE_RTPS_SERIALIZEDPAYLOADHEADER_API_H

#include <array>
#include <cstddef>

#include "dcps/DeclExport.h"
#include "dcps/PITypes.h"

namespace gstone {
namespace rtps {

/* Classic CDR representation with Big Endian encoding. */
constexpr guint16_t CDR_BE {0x0000U};

/* Classic CDR representation with Little Endian encoding. */
constexpr guint16_t CDR_LE {0x0001U};

/* ParameterList with Big Endian encoding. */
constexpr guint16_t PL_CDR_BE {0x0002U};

/* ParameterList with Little Endian encoding. */
constexpr guint16_t PL_CDR_LE {0x0003U};

/* Plain CDR representation (version2) with Big Endian encoding. */
constexpr guint16_t CDR2_BE {0x0010U};

/* Plain CDR representation (version2) with Little Endian encoding. */
constexpr guint16_t CDR2_LE {0x0011U};

/* Extended CDR representation (version2) for MUTABLE types with Big Endian encoding. A generalization of ParameterList. */
constexpr guint16_t PL_CDR2_BE {0x0012U};

/* Extended CDR representation (version2) for MUTABLE types with Little Endian encoding. A generalization of ParameterList. */
constexpr guint16_t PL_CDR2_LE {0x0013U};

/* Extended CDR representation (version2) for APPENDABLE types with Big Endian encoding. */
constexpr guint16_t D_CDR_BE {0x0014U};

/* Extended CDR representation (version2) for APPENDABLE types with Little Endian encoding. */
constexpr guint16_t D_CDR_LE {0x0015U};

/* Allows the specification of large member ID and/or data length values. */
constexpr guint16_t PID_EXTENDED {0x3F01U};

/* Indicates the end of the parameter list data structure. */
constexpr guint16_t PID_LIST_END {0x3F02U};

/* All consumers of this Data Representation shall ignore parameters with this ID. */
constexpr guint16_t PID_IGNORE {0x3F03U};

/* Begin of the OMG reversed pids. */
constexpr guint16_t PID_OMG_REVERSED_BEGIN {0x3F04U};

/* End of the OMG reversed pids. */
constexpr guint16_t PID_OMG_REVERSED_END {0x3FFFU};

/* The maximum value of pid. */
constexpr guint16_t PID_MAX_VALUE {0xFFFFU};

/*  */
constexpr guint16_t PID_FLAG_M {0x4000U};

/*  */
constexpr guint16_t PID_EXTENDED_LEN {0x8U};

/*  */
constexpr guint16_t PID_AUTO_ID {0x2000U};

/*  */
constexpr size_t REPRESENTATION_IDENTIFIER_SIZE {2UL};

/*  */
constexpr size_t REPRESENTATION_OPTIONS_SIZE {2UL};


using RepresentationIdentifier = std::array<octet, REPRESENTATION_IDENTIFIER_SIZE>;
using RepresentationOptions = std::array<octet, REPRESENTATION_OPTIONS_SIZE>;

/**
 * @class SerializedPayloadHeader
 * @brief The SerializedPayloadHeader occupies the first four octets of the SerializedPayload.
 */
struct GS_DDS4CPP_API SerializedPayloadHeader final
{
    RepresentationIdentifier representation_identifier;
    RepresentationOptions representation_options;
};

} /*rtps*/
} /*gstone*/

#endif /*GSTONE_RTPS_SERIALIZEDPAYLOADHEADER_API_H*/
