/**************************************************************
 * @file SerializedPayload.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_RTPS_SERIALIZEDPAYLOAD_H
#define GSTONE_RTPS_SERIALIZEDPAYLOAD_H

#include <memory>

#include "swiftdds/dcps/PITypes.h"
#include "swiftdds/dcps/DeclExport.h"

namespace gstone {
namespace rtps {

/**
 * @class SerializedPayload
 * @brief A SerializedPayload SubmessageElement contains the serialized representation of either value of an
 * application- defined data-object or the value of the key that uniquely identifies the data-object.
 */
class GS_DDS4CPP_API SerializedPayload final
{
public:
    /**
     * @brief The minimum length of a payload.
     */
    static constexpr guint32_t MIN_LENGTH {0U};

    /**
     * @brief Construct a new Serialized Payload object
     * @param [in] free_mem
     */
    explicit SerializedPayload(bool const free_mem = true) noexcept;

    /**
     * @brief Construct a new Serialized Payload object
     */
    SerializedPayload(guint32_t const, octet const *const) noexcept;

    /**
     * @brief Construct a new Serialized Payload object
     */
    explicit SerializedPayload(octet *const, bool const = true) noexcept;

    /**
     * @brief Construct a new Serialized Payload object
     * @param [in] sp
     */
    SerializedPayload(SerializedPayload const &sp) noexcept;

    /**
     * @brief
     * @param [in] sp
     * @return SerializedPayload&
     */
    SerializedPayload &operator=(SerializedPayload const &sp) &noexcept;

    /**
     * @brief Destroy the Serialized Payload object
     */
    ~SerializedPayload() noexcept;

    /**
     * @brief
     * @return guint32_t
     */
    inline guint32_t length() const noexcept
    {
        return m_length;
    }

    /**
     * @brief
     * @param [in] _length
     */
    inline void length(guint32_t const _length) noexcept
    {
        m_length = _length;
    }

    /**
     * @brief
     * @return octet*
     */
    inline octet *value() const noexcept
    {
        return m_value;
    }

    /**
     * @brief
     * @param [in] _value
     */
    inline void value(octet *const _value) noexcept
    {
        m_value = _value;
    }

    /**
     * @brief
     * @return true
     * @return false
     */
    inline bool need_free_mem() const noexcept
    {
        return m_needFreeMem;
    }

    /**
     * @brief
     * @param [in] _need_free_mem
     */
    inline void need_free_mem(bool const _need_free_mem) noexcept
    {
        m_needFreeMem = _need_free_mem;
    }

    /**
     * @brief
     * @return true
     * @return false
     */
    inline bool is_zero_copy() const noexcept
    {
        return m_isZeroCopyPtr;
    }

    /**
     * @brief
     * @param [in] _is_zero_copy
     */
    inline void is_zero_copy(bool const _is_zero_copy) noexcept
    {
        m_isZeroCopyPtr = _is_zero_copy;
    }

    /**
     * @brief
     * @return true
     * @return false
     */
    inline bool is_new() const noexcept
    {
        return m_isNew;
    }

    /**
     * @brief
     * @param [in] new_flag
     */
    inline void is_new(bool const new_flag) noexcept
    {
        m_isNew = new_flag;
    }
private:
    inline SerializedPayload(guint32_t const _length, octet *const _value, bool const _need_free,
                             bool const _is_zero_copy) noexcept;

    SerializedPayload(SerializedPayload &&sp) noexcept = delete;
    SerializedPayload &operator=(SerializedPayload &&sp) &noexcept = delete;

    guint32_t m_length;
    octet *m_value;
    bool m_needFreeMem;
    bool m_isZeroCopyPtr;
    bool m_isNew;
};
using SerializedPayload_t = SerializedPayload;

}
}

#endif /*GSTONE_RTPS_SERIALIZEDPAYLOAD_H*/
