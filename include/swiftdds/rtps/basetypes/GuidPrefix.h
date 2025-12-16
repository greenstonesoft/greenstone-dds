/**************************************************************
 * @file GuidPrefix.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_RTPS_BASETYPES_GUID_PREFIX_H
#define GSTONE_RTPS_BASETYPES_GUID_PREFIX_H

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <sstream>

#include "swiftdds/dcps/PITypes.h"
#include "swiftdds/dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace rtps {

/**
 * @class GuidPrefix_t
 * @brief Type used to hold the prefix of the globally-unique RTPS-entity identifiers.
 */
class GS_DDS4CPP_API GuidPrefix_t final
{
public:
    /* Length of GuidPrefix_t. */
    static constexpr size_t PREFIX_LENGTH {12UL};
    
    /**
     * @brief The default constructor for GuidPrefix_t.
     */
    constexpr GuidPrefix_t() noexcept : m_value {0U} {}

    /**
     * @brief Construct a new GuidPrefix_t object.
     */
    explicit constexpr GuidPrefix_t(std::array<octet, PREFIX_LENGTH> const &val) noexcept : m_value {val} {}

    /**
     * @brief Destroy the GuidPrefix_t object.
     */
    ~GuidPrefix_t() = default;
    
    /**
     * @brief The copy constructor for GuidPrefix_t.
     */
    constexpr GuidPrefix_t(GuidPrefix_t const &) noexcept = default;

    /**
     * @brief The copy assignment operator.
     * @return GuidPrefix_t& Reference of the locally GuidPrefix_t object.
     */
    GuidPrefix_t &operator=(GuidPrefix_t const &) noexcept = default;
    
    /**
     * @brief Compare two GuidPrefix_t objects.
     * @param [in] lhs Lhs parameter.
     * @param [in] rhs Rhs parameter.
     * @return gbool_t Whether lhs little than rhs.
     * @retval true lhs is little than rhs.
     * @retval false lhs isn't little than rhs.
     */
    friend inline gbool_t operator<(GuidPrefix_t const &lhs, GuidPrefix_t const &rhs) noexcept
    {
        return lhs.m_value < rhs.m_value;
    }
    
    /**
     * @brief Compare two GuidPrefix_t objects for equality.
     * @param [in] lhs Lhs parameter.
     * @param [in] rhs Rhs parameter.
     * @return gbool_t Whether lhs is equal to rhs.
     * @retval true Lhs is equal to rhs.
     * @retval false Lhs is inequal to rhs.
     */
    friend inline gbool_t operator==(GuidPrefix_t const &lhs, GuidPrefix_t const &rhs) noexcept
    {
        return (memcmp(lhs.value().data(), rhs.value().data(), GuidPrefix_t::PREFIX_LENGTH) == 0);
    }
    
    /**
     * @brief Compare two GuidPrefix_t objects for inequality.
     * @param [in] lhs Lhs parameter.
     * @param [in] rhs Rhs parameter.
     * @return gbool_t Whether lhs is inequal to rhs.
     * @retval true Lhs is inequal to rhs.
     * @retval false Lhs is equal to rhs.
     */
    friend inline gbool_t operator!=(GuidPrefix_t const &lhs, GuidPrefix_t const &rhs) noexcept
    {
        return !(lhs == rhs);
    }
    
    /**
     * @brief Get value of this object.
     * @return std::array<octet, PREFIX_LENGTH> const& The value of this object.
     */
    inline std::array<octet, PREFIX_LENGTH> const &value() const noexcept
    {
        return m_value;
    }

    /**
     * @brief Set value of this object.
     * @param [in] val Value used to set.
     */
    inline void value(std::array<octet, PREFIX_LENGTH> const &val) noexcept
    {
        m_value = val;
    }
private:
    GuidPrefix_t(GuidPrefix_t &&other) noexcept = delete;
    inline GuidPrefix_t &operator=(GuidPrefix_t &&rhs) noexcept = delete;

    std::array<octet, PREFIX_LENGTH> m_value;
};

/* The unknown guid prefix. */
constexpr GuidPrefix_t GUIDPREFIX_UNKNOWN{};
}  /*rtps*/

/**
 * @brief Print a GuidPrefix_t.
 * @param [in] out An output stream.
 * @param [in] prefix A GuidPrefix_t object.
 * @return std::ostream& 
 */
inline std::ostream &operator<<(std::ostream &out, rtps::GuidPrefix_t const &prefix) noexcept
{
    static constexpr size_t STEP {2UL};
    static constexpr size_t TERMINAL_CHAR {1UL};
    static constexpr size_t BUF_SIZE {rtps::GuidPrefix_t::PREFIX_LENGTH * STEP + TERMINAL_CHAR};
    std::array<gchar_t, BUF_SIZE> _value {};
    for (size_t i {0UL}; i < rtps::GuidPrefix_t::PREFIX_LENGTH; i++)
    {
       sprintf(&_value[i * STEP], "%02x", prefix.value()[i]);
    }
    out << _value.data();
    return out;
}

} /*gstone*/

__GS_DDS4CPP_END_DECLS

#endif /*GSTONE_RTPS_BASETYPES_GUID_PREFIX_H*/
