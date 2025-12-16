/**************************************************************
* @file CoreShmATransportConfig.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_CORESHMA_ADDITIONAL_TRANSPORT_H
#define GSTONE_CORESHMA_ADDITIONAL_TRANSPORT_H 1

#include "swiftdds/rtps/TransportConfig/TransportConfig.h"

namespace gstone
{
namespace rtps
{

class CoreShmATransportConfig final : public TransportConfig
{
    public:
        CoreShmATransportConfig() = default;
        CoreShmATransportConfig(gint32_t const kind, guint32_t const port, gchar_t const *const addr) 
            : TransportConfig{kind, port, addr} {}
        constexpr CoreShmATransportConfig(CoreShmATransportConfig const &) noexcept = delete;
        constexpr CoreShmATransportConfig(CoreShmATransportConfig &&) = delete;
        CoreShmATransportConfig &operator=(CoreShmATransportConfig const &) = delete;
        CoreShmATransportConfig &operator=(CoreShmATransportConfig &&) = delete;
        ~CoreShmATransportConfig() final = default;
    private:
};

}
}

#endif
