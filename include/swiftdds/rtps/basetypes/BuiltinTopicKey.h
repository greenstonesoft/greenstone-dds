/**************************************************************
 * @file BuiltinTopicKey.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_RTPS_BASETYPES_BUILTINTOPICKEY_H
#define GSTONE_RTPS_BASETYPES_BUILTINTOPICKEY_H

#include <array>
#include <cstddef>

#include "swiftdds/dcps/PITypes.h"
#include "swiftdds/dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace rtps {

/**
 * @class BuiltinTopicKey_t
 * @brief DCPS key to distinguish entries.
 */
class BuiltinTopicKey_t final
{
public:
    /* size_t Size of the BuiltinTopicKey_t. */
    static constexpr size_t BUILTIN_TOPIC_KEY_SIZE {16U};

    /**
     * @brief The default constructor for BuiltinTopicKey_t.
     */
    constexpr BuiltinTopicKey_t() noexcept : m_value {} {}

    /**
     * @brief The copy constructor for BuiltinTopicKey_t.
     */
    BuiltinTopicKey_t(BuiltinTopicKey_t const &) = default;

    /**
     * @brief Construct a new BuiltinTopicKey_t object.
     * @param [in] val Value used to initialize the object.
     */
    explicit BuiltinTopicKey_t(std::array<octet, BUILTIN_TOPIC_KEY_SIZE> const &val) noexcept : m_value {val} {}

    /**
     * @brief Destroy the BuiltinTopicKey_t object.
     */
    ~BuiltinTopicKey_t() = default;
   
    /**
     * @brief The copy assignment operator.
     * @return BuiltinTopicKey_t& Reference of the locally DomainParticipantQos object.
     */
    BuiltinTopicKey_t &operator=(BuiltinTopicKey_t const &) = default;

    /**
     * @brief Construct a new BuiltinTopicKey_t object.
     */
    BuiltinTopicKey_t(BuiltinTopicKey_t &&) = default;

    /**
     * @brief The move assignment operator.
     * @return BuiltinTopicKey_t& Reference of the locally BuiltinTopicKey_t object.
     */
    BuiltinTopicKey_t &operator=(BuiltinTopicKey_t &&) = default;

    /**
     * @brief The move assignment operator.
     * @return std::array<octet, BUILTIN_TOPIC_KEY_SIZE> const& return the real value.
     */
    inline std::array<octet, BUILTIN_TOPIC_KEY_SIZE> const &value() const noexcept
    {
        return m_value;
    }

    /**
     * @brief Set the value of this object.
     * @param [in] val The value used to set.
     */
    inline void value(std::array<octet, BUILTIN_TOPIC_KEY_SIZE> const &val) noexcept
    {
        m_value = val;
    }

    /**
     * @brief Compare two Locator_t objects for equality.
     * @param [in] lhs Lhs parameter.
     * @param [in] rhs Rhs parameter.
     * @return gbool_t Whether lhs is equal to rhs.
     * @retval true Lhs is equal to rhs.
     * @retval false Lhs is inequal to rhs.
     */
    friend gbool_t operator==(BuiltinTopicKey_t const &lhs, BuiltinTopicKey_t const &rhs) noexcept
    {
        return (lhs.value() == rhs.value());
    }

    /**
     * @brief Compares two Locator_t objects for inequality.
     * @param [in] lhs Lhs parameter.
     * @param [in] rhs Rhs parameter.
     * @return gbool_t Whether lhs is inequal to rhs.
     * @retval true Lhs is inequal to rhs.
     * @retval false Lhs is equal to rhs.
     */
    friend gbool_t operator!=(BuiltinTopicKey_t const &lhs, BuiltinTopicKey_t const &rhs) noexcept
    {
        return !(lhs == rhs);
    }
private:
    std::array<octet, BUILTIN_TOPIC_KEY_SIZE> m_value;
};

} /*rtps*/
} /*gstone*/

__GS_DDS4CPP_END_DECLS

#endif /*GSTONE_RTPS_BASETYPES_BUILTINTOPICKEY_H*/