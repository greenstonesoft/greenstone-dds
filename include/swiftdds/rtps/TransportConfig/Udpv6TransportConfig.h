/**************************************************************
* @file Udpv6TransportConfig.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_UDPV6_ADDITIONAL_TRANSPORT_H
#define GSTONE_UDPV6_ADDITIONAL_TRANSPORT_H 1

#include "swiftdds/rtps/TransportConfig/TransportConfig.h"

namespace gstone
{
namespace rtps
{

class Udpv6TransportConfig final : public TransportConfig
{
    public:
        Udpv6TransportConfig() = default;
        Udpv6TransportConfig(gint32_t const kind, guint32_t const port, gchar_t const *const addr) 
            : TransportConfig{kind, port, addr} {}
        constexpr Udpv6TransportConfig(Udpv6TransportConfig const &) noexcept = delete;
        constexpr Udpv6TransportConfig(Udpv6TransportConfig &&) = delete;
        Udpv6TransportConfig &operator=(Udpv6TransportConfig const &) = delete;
        Udpv6TransportConfig &operator=(Udpv6TransportConfig &&) = delete;
        ~Udpv6TransportConfig() final = default;
    private:
};

}
}

#endif
