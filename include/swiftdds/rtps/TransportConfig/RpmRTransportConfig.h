/**************************************************************
* @file RpmRTransportConfig.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_RPMR_ADDITIONAL_TRANSPORT_H
#define GSTONE_RPMR_ADDITIONAL_TRANSPORT_H 1

#include "swiftdds/rtps/TransportConfig/TransportConfig.h"

namespace gstone
{
namespace rtps
{

class RpmRTransportConfig final : public TransportConfig
{
    public:
        RpmRTransportConfig() = default;
        RpmRTransportConfig(gint32_t const kind, guint32_t const port, gchar_t const *const addr) 
            : TransportConfig{kind, port, addr} {}
        constexpr RpmRTransportConfig(RpmRTransportConfig const &) noexcept = delete;
        constexpr RpmRTransportConfig(RpmRTransportConfig &&) = delete;
        RpmRTransportConfig &operator=(RpmRTransportConfig const &) = delete;
        RpmRTransportConfig &operator=(RpmRTransportConfig &&) = delete;
        ~RpmRTransportConfig() final = default;
    private:
};

}
}

#endif
