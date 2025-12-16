/**************************************************************
 * @file InstanceHandle.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_RTPS_INSTANCEHANDLE_H
#define GSTONE_RTPS_INSTANCEHANDLE_H 

#include <string>
#include <vector>

#include "swiftdds/dcps/DeclExport.h"
#include "swiftdds/rtps/basetypes/Guid.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {

namespace rtps {

static constexpr size_t HANDLE_LEN {16U};
/**
 * @class InstanceHandle
 * @brief Type used to represent the identity of a data-object whose changes in value are communicated by the RTPS
 * protocol.
 */
class GS_DDS4CPP_API InstanceHandle final
{
public:
    octet16 value;

    /**
     * @brief Construct a new Instance Handle object
     */
    InstanceHandle()
    {
        memset(&value, 0, HANDLE_LEN);
    }

    /**
     * @brief Destroy the Instance Handle object
     */
    ~InstanceHandle() = default;

    /**
     * @brief Construct a new Instance Handle object
     * @param [in] a_value 
     */
    explicit InstanceHandle(octet16 const a_value) noexcept
    {
        memcpy(&this->value, a_value, HANDLE_LEN);
    }

    /**
     * @brief Construct a new Instance Handle object
     * @param [in] int_value 
     */
    explicit InstanceHandle(gint32_t const int_value) noexcept
    {
        memset(&value, 0, HANDLE_LEN);
        memcpy(&this->value, &int_value, sizeof(gint32_t));
    }

    /**
     * @brief Construct a new Instance Handle object
     * @param [in] guid 
     */
    InstanceHandle(gstone::rtps::GUID const &guid) noexcept
    {
        static constexpr size_t _KEY_SIZE {3U};
        static constexpr size_t _PRE_SIZE {12U};
        memcpy(&value, static_cast<void *>(const_cast<octet*>(guid.guid_prefix().value().data())), _PRE_SIZE);
        memcpy(&value[_PRE_SIZE], static_cast<void *>(const_cast<octet*>(guid.entity_id().entity_key().data())), _KEY_SIZE);
        value[_KEY_SIZE + _PRE_SIZE] = guid.entity_id().entity_kind();
    }

    /**
     * @brief Construct a new Instance Handle object
     * @param [in] instance_handle 
     */
    InstanceHandle(InstanceHandle const &instance_handle) noexcept
    {
        memcpy(&value, &instance_handle.value, HANDLE_LEN);
    }

        /**
     * @brief Construct a new Instance Handle object
     * @param [in] instance_handle 
     */
    InstanceHandle(InstanceHandle &&instance_handle) noexcept =default;

    /**
     * @brief The copy assignment operator
     * @param [in] instance_handle 
     * @return InstanceHandle& 
     */
    InstanceHandle &operator=(InstanceHandle const &instance_handle) & noexcept
    {
        if (this != &instance_handle)
        {
            memcpy(&value, &instance_handle.value, HANDLE_LEN);
        }

        return *this;
    }

    /**
     * @brief The move assignment operator
     * @param [in] instance_handle 
     * @return InstanceHandle& 
     */
    InstanceHandle &operator=(InstanceHandle &&instance_handle) noexcept =default;

    /**
     * @brief 
     * @param [in] handle 
     * @param [in] other 
     * @return gbool_t 
     */
    inline friend gbool_t operator==(InstanceHandle const &handle, InstanceHandle const &other) noexcept
    {
        return memcmp(&other.value, &handle.value, sizeof(other.value)) == 0;
    }
    
    /**
     * @brief 
     * @param [in] handle 
     * @param [in] other 
     * @return gbool_t 
     */
    inline friend gbool_t operator!=(InstanceHandle const &handle, InstanceHandle const &other) noexcept
    {
        return !(other == handle);
    }

    /**
     * @brief 
     * @param [in] a_value 
     * @param [in] the_len 
     * @return guint64_t 
     */
    static inline guint64_t BKDRHash(gchar_t const *const a_value, gint32_t const the_len) noexcept
    {
        uint64_t hash {0UL};
        uint64_t const seed {131313UL};
        for (gint32_t i {0}; i < the_len; i++)
        {
            hash = hash * seed + static_cast<uint64_t>(*(a_value + i));
        }
        return hash;
    }

    /**
     * @brief Construct a new Instance Handle object
     * @param [in] buf 
     * @param [in] len 
     */
    InstanceHandle(gvoid_t const *const buf, guint32_t const len) noexcept
    {
        memset(&value, 0, HANDLE_LEN);
        if (len <= sizeof(this->value))
        {
            memcpy(&this->value, buf, static_cast<size_t>(len));
        }
        else
        {
            guint64_t const hash {BKDRHash(static_cast<gchar_t const *>(buf), static_cast<gint32_t>(len))};
            memcpy(&value, &hash, sizeof(hash));
        }
    }

    inline friend GS_DDS4CPP_API std::ostream &operator<<(std::ostream &out, InstanceHandle const &handle);
};

using InstanceHandle_t = InstanceHandle;
std::ostream &operator<<(std::ostream &out, InstanceHandle const &handle)
{
    out << std::hex;
    for (guint32_t i {0U}; i < sizeof(handle.value); i++)
    {
        out << static_cast<gint32_t>(handle.value[i]) << " - ";
    }
    out << std::dec;
    return out;
}

GS_DDS4CPP_API inline bool operator<(InstanceHandle_t const &h1, InstanceHandle_t const &h2) noexcept
{
    return memcmp(&h1.value, &h2.value, HANDLE_LEN) < 0;
}

using InstanceHandleSeq = std::vector<InstanceHandle>;
} /*rtps*/
} /*gstone*/

namespace std {
template <>
struct hash<gstone::rtps::InstanceHandle>
{
    GS_DDS4CPP_API std::size_t operator()(gstone::rtps::InstanceHandle const &handle) const
    {
        std::string const buf((sizeof(handle.value)) + 1U, '\0');
        memcpy(const_cast<gchar_t *>(buf.data()), &handle.value, sizeof(handle.value));

        return std::hash<std::string> {}(buf);
    }
};
} /*std*/

__GS_DDS4CPP_END_DECLS

#endif /*GSTONE_RTPS_INSTANCEHANDLE_API_H*/
