/**************************************************************
* @file Tcpv6TransportConfig.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_TCPV6_ADDITIONAL_TRANSPORT_H
#define GSTONE_TCPV6_ADDITIONAL_TRANSPORT_H 1

#include "swiftdds/rtps/TransportConfig/TransportConfig.h"

namespace gstone
{
namespace rtps
{

class Tcpv6TransportConfig final : public TransportConfig
{
    public:
        Tcpv6TransportConfig() = default;
        Tcpv6TransportConfig(gint32_t const kind, guint32_t const port, gchar_t const *const addr) 
            : TransportConfig{kind, port, addr} {}
        constexpr Tcpv6TransportConfig(Tcpv6TransportConfig const &) noexcept = delete;
        constexpr Tcpv6TransportConfig(Tcpv6TransportConfig &&) = delete;
        Tcpv6TransportConfig &operator=(Tcpv6TransportConfig const &) = delete;
        Tcpv6TransportConfig &operator=(Tcpv6TransportConfig &&) = delete;
        ~Tcpv6TransportConfig() final = default;
    private:
};

}
}

#endif
