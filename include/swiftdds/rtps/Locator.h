/**************************************************************
 * @file Locator.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_RTPS_LOCATOR_H
#define GSTONE_RTPS_LOCATOR_H

#include <algorithm>
#include <array>
#include <functional>
#include <vector>
#include <string>

#include "swiftdds/dcps/PITypes.h"
#include "swiftdds/rtps/DdsCdr.h"
#include "swiftdds/dcps/DeclExport.h"
#include "swiftdds/rtps/LocatorKind.h"

namespace gstone {
namespace rtps {

/**
 * @class Locator_t
 * @brief Type used to represent the addressing information needed to send a message to an RTPS Endpoint using one of
 * the supported transports.
 */
class GS_DDS4CPP_API Locator_t final
{
public:
    /* Address size. */
    static constexpr size_t ADDRESS_SIZE {16UL};

    /**
     * @brief The default constructor for Locator_t.
     */
    constexpr Locator_t() noexcept : m_kind {LOCATOR_KIND_UDPv4}, m_port {LOCATOR_PORT_INVALID}, m_address {} {}

    /**
     * @brief The copy constructor for Locator_t.
     */
    constexpr Locator_t(Locator_t const &) noexcept = default;

    /**
     * @brief The move constructor for Locator_t.
     */
    constexpr Locator_t(Locator_t &&) = default;

    /**
     * @brief Construct a new Locator_t object.
     * @param [in] the_kind The kind of the new Locator_t object.
     * @param [in] the_port The port of the new Locator_t object.
     * @param [in] the_address The address of the new Locator_t object.
     */
    Locator_t(gint32_t const the_kind, guint32_t const the_port, std::array<octet, ADDRESS_SIZE> const &the_address) noexcept
        : m_kind {the_kind}, m_port {the_port}, m_address {the_address}
    {
    }

    /**
     * @brief Construct a new Locator_t object.
     * @param [in] the_kind The kind of the new Locator_t object.
     * @param [in] the_port The port of the new Locator_t object.
     * @param [in] the_address The address of the new Locator_t object.
     */
    Locator_t(gint32_t const the_kind, guint32_t const the_port, gchar_t const *const the_address) noexcept;

    /**
     * @brief Destroy the Locator_t object.
     */
    ~Locator_t() = default;

    /**
     * @brief The copy assignment operator.
     * @return Locator_t& Reference of the locally Locator_t object.
     */
    Locator_t &operator=(Locator_t const &) = default;

    /**
     * @brief The move assignment operator.
     * @return Locator_t& Reference of the locally Locator_t object.
     */
    Locator_t &operator=(Locator_t &&) = default;

    /**
     * @brief The getter of Locator_t::kind.
     * @return gint32_t Kind of this Locator_t object.
     */
    inline gint32_t kind() const noexcept
    {
        return m_kind;
    }

    /**
     * @brief The setter of Locator_t::kind.
     * @param [in] the_kind The kind used to set.
     */
    inline void kind(gint32_t const the_kind) noexcept
    {
        m_kind = the_kind;
    }
    
    /**
     * @brief The getter of Locator_t::port.
     * @return guint32_t Port of this Locator_t object.
     */
    inline guint32_t port() const noexcept
    {
        return m_port;
    }

    /**
     * @brief The setter of Locator_t::port.
     * @param [in] the_port The port used to set.
     */
    inline void port(guint32_t const the_port) noexcept
    {
        m_port = the_port;
    }

    /**
     * @brief The getter of Locator_t::port.
     * @return std::array<octet, ADDRESS_SIZE> const&
     */
    inline std::array<octet, ADDRESS_SIZE> const &address() const noexcept
    {
        return m_address;
    }

    /**
     * @brief Set address of this locator.
     * @param [in] an_address address used to set.
     */
    inline void address(std::array<octet, ADDRESS_SIZE> const &an_address) noexcept
    {
        m_address = an_address;
    }

    /**
     * @brief Compare two Locator_t objects for equality.
     * @param [in] lhs Lhs parameter.
     * @param [in] rhs Rhs parameter.
     * @return gbool_t Whether lhs equal to rhs.
     * @retval true Lhs is equal to rhs.
     * @retval false Lhs is inequal to rhs.
     */
    friend inline gbool_t operator==(Locator_t const &lhs, Locator_t const &rhs) noexcept
    {
        gbool_t const isSameAddress{memcmp(lhs.m_address.data(), rhs.m_address.data(), ADDRESS_SIZE) == 0};
        return isSameAddress && (lhs.m_kind == rhs.m_kind) && (lhs.m_port == rhs.m_port);
    }

    /**
     * @brief Compare two EntityId_t objects.
     * @param [in] lhs Lhs parameter
     * @param [in] rhs Rhs parameter
     * @return gbool_t Whether lhs little than rhs.
     * @retval true Lhs is little than rhs.
     * @retval false Lhs isn't little than rhs.
     */
    friend inline gbool_t operator<(Locator_t const &lhs, Locator_t const &rhs) noexcept
    {
        return lhs.hashcode() < rhs.hashcode();
    }

    /**
     * @brief Check whether the given kind is a compatibility net protocol.
     * @param [in] test_kind A special locator kind.
     * @return gbool_t Whether the given kind is a compatibility net protocol.
     * @retval true The given kind is a compatibility net protocol.
     * @retval false The given kind isn't a compatibility net protocol.
     */
    gbool_t is_compatibility_net_protocol(gint32_t const test_kind) const noexcept;

    /**
     * @brief Serialize the Locator object.
     * @param [in] cdr A DdsCdr object reference.
     */
    gvoid_t serialize(DdsCdr &cdr) const noexcept;

    /**
     * @brief Deserialize a Locator_t object.
     * @param [in] cdr A DdsCdr object reference.
     */
    gvoid_t deserialize(DdsCdr &cdr) noexcept;

    /**
     * @brief Get the object's hash code.
     * @return size_t The object's hash code.
     */
    size_t hashcode() const noexcept;
private:
    gint32_t m_kind;
    guint32_t m_port;
    std::array<octet, ADDRESS_SIZE> m_address;
};

/**
 * @brief LocatorList is used to specify a list of locators.
 */
using LocatorList = std::vector<Locator_t>;
using LocatorList_t = LocatorList;

} /*rtps*/
} /*gstone*/

namespace std {

template <>
struct hash<gstone::rtps::Locator_t> final
{
    inline std::size_t operator()(gstone::rtps::Locator_t const &loc) const noexcept
    {
        return loc.hashcode();
    }
};

} /*std*/

#endif /*GSTONE_RTPS_LOCATOR_H*/
