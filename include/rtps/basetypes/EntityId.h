/**************************************************************
 * @file EntityId.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_RTPS_BASETYPES_ENTITYID_H
#define GSTONE_RTPS_BASETYPES_ENTITYID_H

#include <array>
#include <cstddef>
#include <cstring>
#include <limits>
#include <ostream>

#include "dcps/PITypes.h"
#include "dcps/DeclExport.h"
#include "rtps/DdsCdr.h"

namespace gstone {
namespace rtps {

constexpr size_t ENTITYID_SIZE{ 4UL };
constexpr size_t KEY_SIZE{ 3UL };
constexpr size_t KEY_INDEX0{ 0UL };
constexpr size_t KEY_INDEX1{ 1UL };
constexpr size_t KEY_INDEX2{ 2UL };
constexpr size_t KEY_INDEX3{ 3UL };
constexpr octet KEY_MASK{ 0xFFU };
constexpr octet KIND_MASK{ 0xFFU };
constexpr octet BUILTIN_KIND_MASK{ 0xF0U };
constexpr octet BUILTIN_KIND{ 0xC0U };
constexpr size_t OFFSET_24{ 24UL };
constexpr size_t OFFSET_16{ 16UL };
constexpr size_t OFFSET_8{ 8UL };
/**
 * @class EntityId_t
 * @brief Type used to hold the suffix part of the globally-unique RTPS-entity identifiers.
 */
class GS_DDS4CPP_API EntityId_t final
{
public:
    /**
     * @brief The default constructor for EntityId_t.
     */
    constexpr EntityId_t() noexcept : m_entityKey {0U}, m_entityKind {0U} {}

    /**
     * @brief Construct a new EntityId_t object.
     * @param [in] key Key of the new EntityId_t object.
     * @param [in] kind Kind of the new EntityId_t object.
     */
    constexpr EntityId_t(std::array<octet, KEY_SIZE> const &key, octet const kind) noexcept
        : m_entityKey {key}, m_entityKind {kind}
    {
    }

    /**
     * @brief Construct a new EntityId_t object.
     * @param [in] value Value of the new object.
     */
    constexpr explicit EntityId_t(guint32_t const value) noexcept
        : EntityId_t {static_cast<guint32_t>(value >> OFFSET_8),
                      static_cast<octet>(value & std::numeric_limits<octet>::max())}
    {
    }

    /**
     * @brief Construct a new EntityId_t object.
     * @param [in] value Key of the new EntityId_t object.
     * @param [in] kind Kind of the new EntityId_t object.
     */
    constexpr EntityId_t(guint32_t const value, octet const kind) noexcept
        : m_entityKey {static_cast<octet>((value >> OFFSET_16) & KEY_MASK),
                       static_cast<octet>((value >> OFFSET_8) & KEY_MASK), static_cast<octet>(value & KEY_MASK)},
          m_entityKind {static_cast<octet>(kind & KIND_MASK)}
    {
    }

    /**
     * @brief The copy constructor for EntityId_t.
     */
    constexpr EntityId_t(EntityId_t const &) noexcept = default;

    /**
     * @brief The copy assignment operator.
     * @return EntityId_t& Reference of the locally EntityId_t object.
     */
    EntityId_t &operator=(EntityId_t const &) noexcept = default;

    /**
     * @brief The move constructor for EntityId_t.
     */
    constexpr EntityId_t(EntityId_t &&) noexcept = default;

    /**
     * @brief The move assignment operator.
     * @return EntityId_t& Reference of the locally EntityId_t object.
     */
    EntityId_t &operator=(EntityId_t &&) noexcept = default;

    /**
     * @brief Destroy the EntityId_t object.
     */
    ~EntityId_t() = default;

    /**
     * @brief Get uint value.
     * @return guint32_t The uint value.
     */
    inline guint32_t uint_value() const noexcept
    {
        guint32_t result {m_entityKind};
        result |= static_cast<guint32_t>(m_entityKey[KEY_INDEX0]) << OFFSET_24;
        result |= static_cast<guint32_t>(m_entityKey[KEY_INDEX1]) << OFFSET_16;
        result |= static_cast<guint32_t>(m_entityKey[KEY_INDEX2]) << OFFSET_8;

        return result;
    }

    /**
     * @brief Compare two EntityId_t objects for equality.
     * @param [in] lhs Lhs parameter.
     * @param [in] rhs Rhs parameter.
     * @return gbool_t Whether lhs is equal to rhs.
     * @retval true Lhs is equal to rhs.
     * @retval false Lhs is inequal to rhs.
     */
    friend inline gbool_t operator==(EntityId_t const &lhs, EntityId_t const &rhs) noexcept
    {
        gbool_t const isSameKey{memcmp(lhs.entity_key().data(), rhs.entity_key().data(), KEY_SIZE) == 0};
        gbool_t const isSameKind{lhs.entity_kind() == rhs.entity_kind()};
        return isSameKey && isSameKind;
    }

    /**
     * @brief Compare two EntityId_t objects for inequality.
     * @param [in] lhs Lhs parameter
     * @param [in] rhs Rhs parameter
     * @return gbool_t Whether lhs is inequal to rhs.
     * @retval true Lhs is inequal to rhs.
     * @retval false Lhs is equal to rhs.
     */
    friend inline gbool_t operator!=(EntityId_t const &lhs, EntityId_t const &rhs) noexcept
    {
        return !(lhs == rhs);
    }

    /**
     * @brief Is a builtin entity id.
     * @return gbool_t Whether is builtin.
     * @retval true This is is a builtin entity id.
     * @retval false This is isn't a builtin entity id.
     */
    inline gbool_t is_buildin() const noexcept
    {
        return (m_entityKind & BUILTIN_KIND_MASK) == BUILTIN_KIND;
    }
    /**
     * @brief Whether this entity id is unknown.
     * @return gbool_t Whether is unknown.
     * @retval true This is is a unknown entity id.
     * @retval false This is isn't a unknown entity id.
     */
    inline gbool_t is_unknown() const noexcept
    {
        return (0U == uint_value());
    }

    /**
     * @brief Serialize this object.
     * @param [in] cdr A DdsCdr object reference.
     */
    inline gvoid_t serialize(DdsCdr &cdr) const noexcept
    {
        cdr.serialize(m_entityKey);
        cdr.serialize(m_entityKind);
    }

    /**
     * @brief Deserialize a EntityId_t object.
     * @param [in] cdr A DdsCdr object reference.
     */
    inline gvoid_t deserialize(DdsCdr &cdr) noexcept
    {
        cdr.deserialize(m_entityKey);
        cdr.deserialize(m_entityKind);
    }

    /**
     * @brief Get EntityId_t::key.
     * @return std::array<octet, KEY_SIZE> const& The key of this EntityId_t object.
     */
    inline std::array<octet, KEY_SIZE> const &entity_key() const noexcept
    {
        return m_entityKey;
    }

    /**
     * @brief Set EntityId_t::key.
     * @param [in] key Key used to set.
     */
    inline void entity_key(std::array<octet, KEY_SIZE> const &key) noexcept
    {
        m_entityKey = key;
    }

    /**
     * @brief Get EntityId_t::kind.
     * @return octet The kind of this EntityId_t object.
     */
    inline octet entity_kind() const noexcept
    {
        return m_entityKind;
    }

    /**
     * @brief Set EntityId_t::key.
     * @param [in] kind Kind used to set.
     */
    inline void entity_kind(octet const kind) noexcept
    {
        m_entityKind = kind;
    }
private:
    std::array<octet, KEY_SIZE> m_entityKey;
    octet m_entityKind;
};

/**
 * @brief The Unknown EntityId_t.
 */
constexpr EntityId_t ENTITYID_UNKNOWN {};

/**
 * The GroupDigest_t is computed from an EntityIdSet_t by first computing a 128 bit MD5 Digest (IETF RFC
 * 1321) applied to the CDR Big-Endian serialization of the structure EntityIdSet_t. The GroupDigest_t is the
 * leading 4 octets of the MD5 Digest.
 * The empty group is represented by a zero value of the GroupDigest_t. It is not computed as the hash of the
 * serialized empty sequence.
 */
using GroupDigest = EntityId_t;
using GroupDigest_t = GroupDigest;

} /*rtps*/

/**
 * @brief Print an EntityId_t object.
 * @param [in] out An output stream.
 * @param [in] entityId An Entity_t object.
 * @return std::ostream& Reference of the output stream.
 */
inline std::ostream &operator<<(std::ostream &out, rtps::EntityId_t const &entityId) noexcept
{
    static constexpr size_t KEY_SIZE {3UL};
    static constexpr size_t KEY_INDEX0 {0UL};
    static constexpr size_t KEY_INDEX1 {1UL};
    static constexpr size_t KEY_INDEX2 {2UL};
    static constexpr size_t OFFSET_24 {24UL};
    static constexpr size_t OFFSET_16 {16UL};
    static constexpr size_t OFFSET_8 {8UL};
    std::array<octet, KEY_SIZE> const &entityKey {entityId.entity_key()};
    guint32_t const key {
        (static_cast<guint32_t>(entityKey[KEY_INDEX0]) << OFFSET_24) |
        (static_cast<guint32_t>(entityKey[KEY_INDEX1]) << OFFSET_16) |
        (static_cast<guint32_t>(entityKey[KEY_INDEX2]) << OFFSET_8)};
    out << "kind:0x" << std::hex << static_cast<gint32_t>(entityId.entity_kind()) << ", key:0x" << key << std::dec;
    return out;
}

}  /*gstone*/

namespace std {

/**
 * @brief Hasher for gstone::rtps::EntityId_t.
 */
template <>
struct hash<gstone::rtps::EntityId_t> final
{
    /**
     * @brief Caulate hash code for a gstone::rtps::EntityId_t object.
     * @param [in] obj A gstone::rtps::EntityId_t object.
     * @return std::size_t The hash code.
     */
    GS_DDS4CPP_API std::size_t operator()(gstone::rtps::EntityId_t const &obj) const noexcept
    {
        constexpr size_t ENTITYID_SIZE {4UL};
        
        constexpr size_t KEY_INDEX0 {0UL};
        constexpr size_t KEY_INDEX1 {1UL};
        constexpr size_t KEY_INDEX2 {2UL};
        constexpr size_t KEY_INDEX3 {3UL};
        
        std::array<octet, ENTITYID_SIZE> value;
        value[KEY_INDEX3] = 0U;
        value[KEY_INDEX2] = obj.entity_key()[KEY_INDEX0];
        value[KEY_INDEX1] = obj.entity_key()[KEY_INDEX1];
        value[KEY_INDEX0] = obj.entity_key()[KEY_INDEX2];
        void *const ptr {static_cast<void *>(value.data())};
        return static_cast<std::size_t>(*static_cast<uint32_t const *>(ptr));
    }
};

}  /*std*/

#endif /*GSTONE_RTPS_BASETYPES_ENTITYID_H*/
