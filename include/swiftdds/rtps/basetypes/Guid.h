/**************************************************************
 * @file Guid.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_RTPS_BASETYPES_GUID_API_H
#define GSTONE_RTPS_BASETYPES_GUID_API_H

#include <array>
#include <cstring>
#include <string>
#include <type_traits>

#include "swiftdds/rtps/basetypes/EntityId.h"
#include "swiftdds/rtps/basetypes/GuidPrefix.h"
#include "swiftdds/dcps/PITypes.h"
#include "swiftdds/dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace rtps {

constexpr size_t GUID_SIZE {16UL};

/**
 * @class GUID
 * @brief Type used to hold globally-unique RTPS-entity identifiers.
 */
class GS_DDS4CPP_API GUID final
{
public:
    /**
     * @brief Construct a new GUID object.
     */
    GUID() noexcept = default;

    /**
     * @brief Construct a new GUID object.
     * @param [in] prefix The prefix of the new guid.
     * @param [in] entity_id The entity id of the new guid.
     */
    GUID(rtps::GuidPrefix_t const &prefix, rtps::EntityId_t const &the_entity_id)
    noexcept : m_guidPrefix {prefix}, m_entityId {the_entity_id}
    {
    }

    /**
     * @brief The copy constructor for EntityId_t.
     */
    GUID(GUID const &) noexcept = default;

    /**
     * @brief The copy assignment operator.
     * @return GUID& Reference of the locally GUID object.
     */
    GUID &operator=(GUID const &) &noexcept = default;

    /**
     * @brief Construct a new GUID object.
     */
    GUID(GUID &&) noexcept = default;

    /**
     * @brief The move assignment operator.
     * @return GUID& Reference of the locally GUID object.
     */
    GUID &operator=(GUID &&) noexcept = default;

    /**
     * @brief Destroy the GUID object.
     */
    ~GUID() = default;

    /**
     * @brief Compare two Duration objects for equality.
     * @param [in] lhs Lhs parameter.
     * @param [in] rhs Rhs parameter.
     * @return gbool_t Whether lhs is equal to rhs.
     * @retval true Lhs is equal to rhs.
     * @retval false Lhs is inequal to rhs.
     */
    friend inline bool operator==(GUID const &lhs, GUID const &rhs) noexcept
    {
        return (lhs.m_guidPrefix == rhs.m_guidPrefix && lhs.m_entityId == rhs.m_entityId);
    }

    /**
     * @brief Compare two GUID objects.
     * @param [in] lhs Lhs parameter.
     * @param [in] rhs Rhs parameter.
     * @return gbool_t Whether lhs little than rhs.
     * @retval true lhs is little than rhs.
     * @retval false lhs isn't little than rhs.
     */
    friend inline gbool_t operator<(GUID const &lhs, GUID const &rhs) noexcept
    {
        return std::memcmp(&lhs, &rhs, sizeof(rhs)) < 0;
    }

    /**
     * @brief Convert to a Octet16.
     * @param [in,out] oct An Obtet16 used to store result.
     */
    inline void to_octet16(octet oct[GUID_SIZE]) const noexcept
    {
        memcpy(oct, m_guidPrefix.value().data(), sizeof(m_guidPrefix.value()));
        memcpy(oct + sizeof(m_guidPrefix.value()), m_entityId.entity_key().data(), sizeof(m_entityId.entity_key()));
        oct[GUID_SIZE - 1U] = m_entityId.entity_kind();
    }

    /**
     * @brief Convert to a octet array.
     * @param [in,out] oct An array used to store result.
     */
    inline void to_octet16(std::array<octet, GUID_SIZE> &oct) const noexcept
    {
        memcpy(oct.data(), m_guidPrefix.value().data(), sizeof(m_guidPrefix.value()));
        memcpy(oct.data() + sizeof(m_guidPrefix.value()), m_entityId.entity_key().data(),
               sizeof(m_entityId.entity_key()));
        oct[GUID_SIZE - 1U] = m_entityId.entity_kind();
    }

    /**
     * @brief Convert from an octet array.
     * @param [in] oct An octet array used to get values.
     */
    void from_octet16(octet const oct[GUID_SIZE]) noexcept
    {
        std::array<octet, rtps::GuidPrefix_t::PREFIX_LENGTH> const prefix {
            *static_cast<std::array<octet, rtps::GuidPrefix_t::PREFIX_LENGTH> const *>(static_cast<void const *>(oct))};
        m_guidPrefix.value(prefix);
        
        constexpr size_t _KEY_SIZE {3UL};
        std::array<octet, _KEY_SIZE> const key {
            *static_cast<std::array<octet, _KEY_SIZE> const *>(
                static_cast<void const *>(&oct[rtps::GuidPrefix_t::PREFIX_LENGTH]))};
        m_entityId.entity_key(key);
        m_entityId.entity_kind(oct[GUID_SIZE - 1U]);
    }

    /**
     * @brief Convert from an octet array.
     * @param [in] oct An octet array used to get values.
     */
    inline void from_octet16(std::array<octet, GUID_SIZE> const &oct) noexcept
    {
        from_octet16(oct.data());
    }

    /**
     * @brief Get prefix of this guid.
     * @return rtps::GuidPrefix_t const& The guid prefix.
     */
    inline rtps::GuidPrefix_t const &guid_prefix() const noexcept
    {
        return m_guidPrefix;
    }

    /**
     * @brief Set prefix of this guid.
     * @param [in] prefix Prefix used to set.
     */
    inline void guid_prefix(rtps::GuidPrefix_t const &prefix) noexcept
    {
        m_guidPrefix = prefix;
    }

    /**
     * @brief Get entity id of this guid.
     * @return rtps::EntityId_t const& The entity id.
     */
    inline rtps::EntityId_t const &entity_id() const noexcept
    {
        return m_entityId;
    }

    /**
     * @brief Set entity id of this guid.
     * @param [in] an_id Entity id used to set.
     */
    inline void entity_id(rtps::EntityId_t const &an_id) noexcept
    {
        m_entityId = an_id;
    }
private:
    rtps::GuidPrefix_t m_guidPrefix;
    rtps::EntityId_t m_entityId;
};

} /*core*/

/**
 * @brief Print a rtps::GUID object.
 * @param [in] out An output stream.
 * @param [in] guid A rtps::GUID object.
 * @return std::ostream& Reference of the output stream.
 */
inline std::ostream &operator<<(std::ostream &out, rtps::GUID const &guid) noexcept
{
    out << "prefix: " << guid.guid_prefix() << ", entityId:" << guid.entity_id();
    return out;
}

/* The unknown guid. */
constexpr gstone::rtps::GUID GUID_UNKNOWN {};

} /*gstone*/

namespace std {

/**
 * @brief Hasher for gstone::rtps::GUID.
 */
template <>
struct hash<gstone::rtps::GUID> final
{
    /**
     * @brief Caulate hash code for a gstone::rtps::GUID object.
     * @param [in] obj A gstone::rtps::GUID object.
     * @return std::size_t The hash code.
     */
    GS_DDS4CPP_API std::size_t operator()(gstone::rtps::GUID const &obj) const
        noexcept(noexcept(std::string(std::declval<gchar_t const *>())))
    {
        std::string const guidPrefix {
            static_cast<gchar_t const *>(static_cast<const void *>(obj.guid_prefix().value().data())), gstone::rtps::GuidPrefix_t::PREFIX_LENGTH};
        std::string const entityKey {
            static_cast<gchar_t const *>(static_cast<const void *>(obj.entity_id().entity_key().data())), gstone::rtps::KEY_SIZE};

        return hash<string>()(guidPrefix + entityKey);
    }
};

} /*std*/

__GS_DDS4CPP_END_DECLS

#endif /*GSTONE_RTPS_BASETYPES_GUID_API_H*/
