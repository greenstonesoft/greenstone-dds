/**************************************************************
* @file TransportConfigFactory.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_ADDITIONAL_TRANSPORT_FACTORY_H
#define GSTONE_ADDITIONAL_TRANSPORT_FACTORY_H 1

#include "swiftdds/rtps/TransportConfig/TransportConfig.h"
#include "swiftdds/rtps/TransportConfig/RpmATransportConfig.h"
#include "swiftdds/rtps/TransportConfig/RpmRTransportConfig.h"
#include "swiftdds/rtps/TransportConfig/ShmTransportConfig.h"
#include "swiftdds/rtps/TransportConfig/TcpTransportConfig.h"
#include "swiftdds/rtps/TransportConfig/Tcpv6TransportConfig.h"
#include "swiftdds/rtps/TransportConfig/Udpv6TransportConfig.h"
#include "swiftdds/rtps/TransportConfig/CoreShmATransportConfig.h"
#include "swiftdds/rtps/TransportConfig/CoreShmRTransportConfig.h"

namespace gstone
{
namespace rtps
{

class TransportConfigFactory final
{
public:
    TransportConfigFactory() = default;
    ~TransportConfigFactory() = default;

    // TransportConfigFactory* getInstance() noexcept
    // {
    //     static TransportConfigFactory sInstance{};
    //     return &sInstance;
    // }

    static std::shared_ptr<TransportConfig> create_transport_config(gint32_t kind, guint32_t port, gchar_t const *const addr)
    {

        /* notice : 
         * LOCATOR_KIND_SHM's port only be 0.
         */
        std::shared_ptr<TransportConfig> transport{nullptr};
        switch (kind)
        {
        case LOCATOR_KIND_CORE_SHM_A:
        {
            transport = std::make_shared<CoreShmATransportConfig>(kind, port, addr);
        }
        break;
        case LOCATOR_KIND_CORE_SHM_R:
        {
            transport = std::make_shared<CoreShmRTransportConfig>(kind, port, addr);
        }
        break;
        case LOCATOR_KIND_RPMSG_A:
        {
            transport = std::make_shared<RpmATransportConfig>(kind, port, addr);
        }
        break;
        case LOCATOR_KIND_RPMSG_R:
        {
            transport = std::make_shared<RpmRTransportConfig>(kind, port, addr);
        }
        break;
        case LOCATOR_KIND_SHM:
        {
            transport = std::make_shared<ShmTransportConfig>(kind, 0U, addr);
        }
        break;
        case LOCATOR_KIND_TCPv4:
        {
            transport = std::make_shared<TcpTransportConfig>(kind, port, addr);
        }
        break;
        case LOCATOR_KIND_TCPv6:
        {
            transport = std::make_shared<Tcpv6TransportConfig>(kind, port, addr);
        }
        break;
        case LOCATOR_KIND_UDPv6:
        {
            transport = std::make_shared<Udpv6TransportConfig>(kind, port, addr);
        }
        break;
        default:
        {
        }
        break;
        }

        return transport;
    }

private:
    constexpr TransportConfigFactory(TransportConfigFactory const &) = delete;
    constexpr TransportConfigFactory(TransportConfigFactory &&) = delete;
    TransportConfigFactory &operator=(TransportConfigFactory const &) = delete;
    TransportConfigFactory &operator=(TransportConfigFactory &&) = delete;

};

}
}

#endif
