/**************************************************************
 * @file InstanceHandle.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_RTPS_INSTANCEHANDLE_H
#define GSTONE_RTPS_INSTANCEHANDLE_H 

#include <string>
#include <vector>

#include "dcps/DeclExport.h"
#include "rtps/basetypes/Guid.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {

namespace rtps {

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
        memset(value, 0, 16);
    }

    /**
     * @brief Destroy the Instance Handle object
     */
    ~InstanceHandle() = default;

    /**
     * @brief Construct a new Instance Handle object
     * @param [in] a_value 
     */
    InstanceHandle(octet16 a_value) noexcept
    {
        memcpy(this->value, a_value, 16);
    }

    /**
     * @brief Construct a new Instance Handle object
     * @param [in] int_value 
     */
    InstanceHandle(gint32_t int_value) noexcept
    {
        memset(value, 0, 16);
        memcpy(this->value, &int_value, sizeof(int));
    }

    /**
     * @brief Construct a new Instance Handle object
     * @param [in] guid 
     */
    InstanceHandle(gstone::rtps::GUID const &guid) noexcept
    {
        memcpy(value, (octet *)guid.guid_prefix().value().data(), 12);
        memcpy(&value[12], (octet *)guid.entity_id().entity_key().data(), 3);
        value[15] = guid.entity_id().entity_kind();
    }

    /**
     * @brief Construct a new Instance Handle object
     * @param [in] instance_handle 
     */
    InstanceHandle(InstanceHandle const &instance_handle) noexcept
    {
        memcpy(value, instance_handle.value, 16);
    }

    /**
     * @brief 
     * @param [in] instance_handle 
     * @return InstanceHandle& 
     */
    InstanceHandle &operator=(InstanceHandle const &instance_handle)
    {
        if (this != &instance_handle)
        {
            memcpy(value, instance_handle.value, 16);
        }

        return *this;
    }

    /**
     * @brief 
     * @param [in] handle 
     * @param [in] other 
     * @return gbool_t 
     */
    inline friend gbool_t operator==(InstanceHandle const &handle, InstanceHandle const &other)
    {
        return memcmp(other.value, handle.value, sizeof(other.value)) == 0;
    }
    
    /**
     * @brief 
     * @param [in] handle 
     * @param [in] other 
     * @return gbool_t 
     */
    inline friend gbool_t operator!=(InstanceHandle const &handle, InstanceHandle const &other)
    {
        return !(other == handle);
    }

    /**
     * @brief 
     * @param [in] a_value 
     * @param [in] the_len 
     * @return guint64_t 
     */
    inline guint64_t BKDRHash(gchar_t const *const a_value, gint32_t const the_len)
    {
        uint64_t hash = 0ul;
        uint64_t seed = 131313ul;
        for (int i = 0; i < the_len; i++)
        {
            hash = hash * seed + *(a_value + i);
        }
        return hash;
    }

    /**
     * @brief Construct a new Instance Handle object
     * @param [in] buf 
     * @param [in] len 
     */
    InstanceHandle(gvoid_t const *const buf, guint32_t len)
    {
        memset(value, 0, 16);
        if (len <= sizeof(this->value))
        {
            memcpy(this->value, buf, len);
        }
        else
        {
            guint64_t hash = BKDRHash(static_cast<gchar_t const *>(buf), len);
            memcpy(value, &hash, sizeof hash);
        }
    }

    inline friend GS_DDS4CPP_API std::ostream &operator<<(std::ostream &out, InstanceHandle const &handle);
};

using InstanceHandle_t = InstanceHandle;
std::ostream &operator<<(std::ostream &out, InstanceHandle const &handle)
{
    out << std::hex;
    for (unsigned int i = 0; i < sizeof handle.value; i++)
    {
        out << int(handle.value[i]) << " - ";
    }
    out << std::dec;
    return out;
}

GS_DDS4CPP_API inline bool operator<(InstanceHandle_t const &h1, InstanceHandle_t const &h2)
{
    return memcmp(h1.value, h2.value, 16) < 0;
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
        std::string buf(sizeof(handle.value) + 1, '\0');
        memcpy(const_cast<char *>(buf.data()), handle.value, sizeof(handle.value));

        return std::hash<std::string> {}(buf);
    }
};
} /*std*/

__GS_DDS4CPP_END_DECLS

#endif /*GSTONE_RTPS_INSTANCEHANDLE_API_H*/
