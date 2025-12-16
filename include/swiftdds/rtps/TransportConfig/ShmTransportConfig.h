/**************************************************************
* @file ShmTransportConfig.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_SHM_ADDITIONAL_TRANSPORT_H
#define GSTONE_SHM_ADDITIONAL_TRANSPORT_H 1

#include "swiftdds/rtps/TransportConfig/TransportConfig.h"

namespace gstone
{
namespace rtps
{

class ShmTransportConfig final : public TransportConfig
{
    public:
        ShmTransportConfig() = default;
        ShmTransportConfig(gint32_t const kind, guint32_t const port, gchar_t const *const addr) 
            : TransportConfig{kind, port, addr} {}
        constexpr ShmTransportConfig(ShmTransportConfig const &) noexcept = delete;
        constexpr ShmTransportConfig(ShmTransportConfig &&) = delete;
        ShmTransportConfig &operator=(ShmTransportConfig const &) = delete;
        ShmTransportConfig &operator=(ShmTransportConfig &&) = delete;
        ~ShmTransportConfig() final = default;
    private:
};

}
}

#endif
