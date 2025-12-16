/**************************************************************
* @file TcpTransportConfig.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_TCP_ADDITIONAL_TRANSPORT_H
#define GSTONE_TCP_ADDITIONAL_TRANSPORT_H 1

#include "swiftdds/rtps/TransportConfig/TransportConfig.h"

namespace gstone
{
namespace rtps
{

class TcpTransportConfig final : public TransportConfig
{
    public:
        TcpTransportConfig() = default;
        TcpTransportConfig(gint32_t const kind, guint32_t const port, gchar_t const *const addr) 
            : TransportConfig{kind, port, addr} {}
        constexpr TcpTransportConfig(TcpTransportConfig const &) noexcept = delete;
        constexpr TcpTransportConfig(TcpTransportConfig &&) = delete;
        TcpTransportConfig &operator=(TcpTransportConfig const &) = delete;
        TcpTransportConfig &operator=(TcpTransportConfig &&) = delete;
        ~TcpTransportConfig() final = default;
    private:
};

}
}

#endif
