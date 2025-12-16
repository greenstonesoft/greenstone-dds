/**************************************************************
* @file CoreShmRTransportConfig.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_CORESHMR_ADDITIONAL_TRANSPORT_H
#define GSTONE_CORESHMR_ADDITIONAL_TRANSPORT_H 1

#include "swiftdds/rtps/TransportConfig/TransportConfig.h"

namespace gstone
{
namespace rtps
{

class CoreShmRTransportConfig final : public TransportConfig
{
    public:
        CoreShmRTransportConfig() = default;
        CoreShmRTransportConfig(gint32_t const kind, guint32_t const port, gchar_t const *const addr) 
            : TransportConfig{kind, port, addr} {}
        constexpr CoreShmRTransportConfig(CoreShmRTransportConfig const &) noexcept = delete;
        constexpr CoreShmRTransportConfig(CoreShmRTransportConfig &&) = delete;
        CoreShmRTransportConfig &operator=(CoreShmRTransportConfig const &) = delete;
        CoreShmRTransportConfig &operator=(CoreShmRTransportConfig &&) = delete;
        ~CoreShmRTransportConfig() final = default;
    private:
};

}
}

#endif
