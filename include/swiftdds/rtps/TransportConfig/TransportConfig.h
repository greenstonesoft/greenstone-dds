/**************************************************************
* @file TransportConfig.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_ADDITIONAL_TRANSPORT_H
#define GSTONE_ADDITIONAL_TRANSPORT_H 1

#include "swiftdds/dcps/PITypes.h"
#include "swiftdds/rtps/LocatorKind.h"
#include <array>
#include <list>
#include <memory>
#include <cstring>

namespace gstone
{
namespace rtps
{

constexpr size_t ADDRESS_SIZE {16UL};

static constexpr std::array<gchar_t,ADDRESS_SIZE> MCU_R10_ADDR {"MCU_R10"};
static constexpr std::array<gchar_t,ADDRESS_SIZE> MAIN_R20_ADDR {"MAIN_R20"};
static constexpr std::array<gchar_t,ADDRESS_SIZE> MAIN_R21_ADDR {"MAIN_R21"};
static constexpr std::array<gchar_t,ADDRESS_SIZE> MAIN_R30_ADDR {"MAIN_R30"};
static constexpr std::array<gchar_t,ADDRESS_SIZE> MAIN_R31_ADDR {"MAIN_R31"};

static constexpr guint32_t PROC_ID_0 {0U};
static constexpr guint32_t PROC_ID_2 {2U};
static constexpr guint32_t PROC_ID_3 {3U};
static constexpr guint32_t PROC_ID_4 {4U};
static constexpr guint32_t PROC_ID_5 {5U};

class TransportConfig
{
    public:
        TransportConfig() = default;
        TransportConfig(gint32_t const the_kind, guint32_t const the_port, gchar_t const *const the_addr)
            : m_kind{the_kind}
            , m_port{the_port}
            , m_address{}
        {
            if(the_addr != nullptr)
            {
                size_t const length {std::string::traits_type::length(the_addr)};
                if (length <= ADDRESS_SIZE)
                {
                    if((the_kind == LOCATOR_KIND_RPMSG_A) || (the_kind == LOCATOR_KIND_RPMSG_R) || (the_kind == LOCATOR_KIND_CORE_SHM_A) || (the_kind == LOCATOR_KIND_CORE_SHM_R))
                    {
                        guint32_t r_proc_id {0U};
                        std::array<gchar_t,ADDRESS_SIZE> tmp_addr{};
                        memcpy(tmp_addr.data(), the_addr, length);
                        guint32_t const tmp_proc_id {*static_cast<guint32_t *>(static_cast<gvoid_t*>(tmp_addr.data()))};
                        if((tmp_addr == MCU_R10_ADDR) || (tmp_proc_id == PROC_ID_0))
                        {
                            r_proc_id = PROC_ID_0;
                        }
                        else if((tmp_addr == MAIN_R20_ADDR) || (tmp_proc_id == PROC_ID_2))
                        {
                            r_proc_id = PROC_ID_2;
                        }
                        else if((tmp_addr == MAIN_R21_ADDR) || (tmp_proc_id == PROC_ID_3))
                        {
                            r_proc_id = PROC_ID_3;
                        }
                        else if((tmp_addr == MAIN_R30_ADDR) || (tmp_proc_id == PROC_ID_4))
                        {
                            r_proc_id = PROC_ID_4;
                        }
                        else if((tmp_addr == MAIN_R31_ADDR) || (tmp_proc_id == PROC_ID_5))
                        {
                            r_proc_id = PROC_ID_5;
                        }
                        else
                        {
                        }
                        memcpy(m_address.data(), &r_proc_id, sizeof(guint32_t));
                    }
                    else
                    {
                        memcpy(m_address.data(), the_addr, length);
                    }
                }
            }
        }
        constexpr TransportConfig(TransportConfig const &) = delete;
        constexpr TransportConfig(TransportConfig &&) = delete;
        TransportConfig &operator=(TransportConfig const &) = delete;
        TransportConfig &operator=(TransportConfig &&) = delete;
        virtual ~TransportConfig() = default;

        gint32_t const& kind() const noexcept
        {
            return m_kind;
        }

        guint32_t const& port() const noexcept
        {
            return m_port;
        }

        void update_port(guint32_t const the_port) noexcept
        {
            m_port = the_port;
        }

        std::array<octet, ADDRESS_SIZE> const& addr() const noexcept
        {
            return m_address;
        }

        inline void update_addr(std::array<octet, ADDRESS_SIZE> const &new_addr) noexcept
        {
            m_address = new_addr;
        }

    private:
        gint32_t m_kind{LOCATOR_KIND_INVALID};
        guint32_t m_port{0U};
        std::array<octet, ADDRESS_SIZE> m_address{};
};

//using Transport_t = TransportConfig;
using TransportList_t = std::list<std::shared_ptr<TransportConfig> >;

}
}

#endif
