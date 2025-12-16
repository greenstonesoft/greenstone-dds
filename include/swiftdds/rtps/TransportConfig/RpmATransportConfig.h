/**************************************************************
* @file RpmATransportConfig.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_RPMA_ADDITIONAL_TRANSPORT_H
#define GSTONE_RPMA_ADDITIONAL_TRANSPORT_H 1

#include "swiftdds/rtps/TransportConfig/TransportConfig.h"

namespace gstone
{
namespace rtps
{

class RpmATransportConfig final : public TransportConfig
{
    public:
        RpmATransportConfig() = default;
        RpmATransportConfig(gint32_t const kind, guint32_t const port, gchar_t const *const addr) 
            : TransportConfig{kind, port, addr} {}
        constexpr RpmATransportConfig(RpmATransportConfig const &) noexcept = delete;
        constexpr RpmATransportConfig(RpmATransportConfig &&) = delete;
        RpmATransportConfig &operator=(RpmATransportConfig const &) = delete;
        RpmATransportConfig &operator=(RpmATransportConfig &&) = delete;
        ~RpmATransportConfig() final = default;
    private:
};

}
}

#endif
