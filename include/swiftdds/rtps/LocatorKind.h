/**************************************************************
 * @file LocatorKind.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_RTPS_LOCATOR_KIND_H
#define GSTONE_RTPS_LOCATOR_KIND_H

#include "swiftdds/dcps/PITypes.h"

namespace gstone {
namespace rtps {

/* Invalid Locator Kind. */
constexpr gint32_t LOCATOR_KIND_INVALID {-1};

/* Reserved Locator Kind. */
constexpr gint32_t LOCATOR_KIND_RESERVED {0};

/* UDPv4 Locator Kind */
constexpr gint32_t LOCATOR_KIND_UDPv4 {1};

/* UDPv6 Locator Kind. */
constexpr gint32_t LOCATOR_KIND_UDPv6 {2};

/* Invalid Locator Port. */
constexpr guint32_t LOCATOR_PORT_INVALID {0U};

/* TCPv4 Locator Kind. */
constexpr gint32_t LOCATOR_KIND_TCPv4 {4};

/* TCPv6 Locator Kind. */
constexpr gint32_t LOCATOR_KIND_TCPv6 {8};

/* Shared Memory Locator Kind. */
constexpr gint32_t LOCATOR_KIND_SHM {16};

/* RpMsg-a Locator Kind. */
constexpr gint32_t LOCATOR_KIND_RPMSG_A {32};

/* RpMsg-r Locator Kind. */
constexpr gint32_t LOCATOR_KIND_RPMSG_R {64};

/* CoreShm-a Locator Kind. */
constexpr gint32_t LOCATOR_KIND_CORE_SHM_A {128};

/* CoreShm-r Locator Kind. */
constexpr gint32_t LOCATOR_KIND_CORE_SHM_R {256};


/* Transport Kind. */
enum class TransportKind_t : gint32_t
{
    TRANSPORT_KIND_UDPv4   = 1,
    TRANSPORT_KIND_UDPv6   = 2,
    TRANSPORT_KIND_TCPv4   = 4,
    TRANSPORT_KIND_TCPv6   = 8,
    TRANSPORT_KIND_SHM     = 16,
    TRANSPORT_KIND_RPMSG_A = 32,
    TRANSPORT_KIND_RPMSG_R = 64,
    TRANSPORT_KIND_CORE_SHM_A = 128,
    TRANSPORT_KIND_CORE_SHM_R = 256,
};

} /*rtps*/
} /*gstone*/

#endif /*GSTONE_RTPS_LOCATOR_KIND_H*/
