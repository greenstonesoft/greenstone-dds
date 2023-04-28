/**************************************************************
 * @file LocatorKind.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_RTPS_LOCATOR_KIND_H
#define GSTONE_RTPS_LOCATOR_KIND_H

#include "dcps/PITypes.h"

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

} /*rtps*/
} /*gstone*/

#endif /*GSTONE_RTPS_LOCATOR_KIND_H*/
