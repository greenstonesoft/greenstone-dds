/**************************************************************
* @file BinaryProperty.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_BINARYPROPERTY_H
#define GSTONE_BINARYPROPERTY_H 1

#include <string>
#include <vector>

#include "dcps/PITypes.h"
#include "dcps/DeclExport.h"


__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace rtps {
class DdsCdr;
} /*rtps*/
} /*gstone*/

namespace gstone {
namespace rtps{
/**
* @class BinaryProperty
* @brief Sequences of BinaryProperty_t are used as a generic data type to configure the plugins, pass 
* metadata and provide an extensible mechanism for vendors to configure the behavior of their plugins without breaking portability or interoperability.
* @note This class is used for the DDS-Security specification.
*/
class GS_DDS4CPP_API BinaryProperty final
{
public:
    /**
     * @brief Construct a new Binary Property object.
     * @param [in] a_name      The a_name may be used for information interpretation.
     * @param [in] a_data      The a_data may be used for information value associated with the a_name.
     * @param [in] a_len       The a_len may be used for the length of a_data.
     * @param [in] a_propagate The a_propagate may be used for information exchange over the network.
     * @note The type of a_data is gchar_t
     */
    BinaryProperty(gstring_t const &a_name, gchar_t const * const a_data, gint32_t const &a_len,
                   gbool_t const a_propagate = true) noexcept
        : m_name {a_name}, m_propagate {a_propagate}, m_value {}
    {
        this->m_value.assign(a_data, &a_data[a_len]);
    }

    /**
     * @brief Construct a new Binary Property object.
     * @param [in] a_name      The a_name may be used for information interpretation.
     * @param [in] a_data      The a_data may be used for information value associated with the a_name.
     * @param [in] a_len       The a_len may be used for the length of a_data.
     * @param [in] a_propagate The a_propagate may be used for information exchange over the network.
     * @note The type of a_data is guint8_t
     */
    BinaryProperty(gstring_t const &a_name, guint8_t const * const a_data, gint32_t const &a_len,
                   gbool_t const a_propagate = true) noexcept
        : m_name {a_name}, m_propagate {a_propagate}, m_value {}
    {
        this->value(a_data, a_len);
    }

    /**
     * @brief Construct a new Binary Property object.
     * @param [in] a_name      The a_name may be used for information interpretation.
     * @param [in] a_data      The a_data may be used for information value associated with the a_name.
     * @param [in] a_propagate The a_propagate may be used for information exchange over the network.
     * @note The type of value is gstring_t
     */
    BinaryProperty(gstring_t const &a_name, gstring_t const &a_data, gbool_t const a_propagate = true) noexcept
        : m_name {a_name}, m_propagate {a_propagate}, m_value {a_data.begin(), a_data.end()}
    {
    }

    /**
     * @brief Construct a new Binary Property object.
     * @param [in] a_name      The a_name may be used for information interpretation.
     * @param [in] a_data      The a_data may be used for information value associated with the a_name.
     * @param [in] a_propagate The a_propagate may be used for information exchange over the network.
     * @note The type of value std::vector<guint8_t>
     */
    BinaryProperty(gstring_t const &a_name, std::vector<guint8_t> const &a_data, gbool_t const a_propagate = true) noexcept
        : m_name {a_name}, m_propagate {a_propagate}, m_value {a_data}
    {
    }

    /**
     * @brief Construct a new BinaryProperty object with default parameter.
     */
    BinaryProperty() = default;

    /**
     * @brief Construct a new BinaryProperty object with copying BinaryProperty object.
     * @param [in] a_binary_property A new BinaryProperty object is created by copying this BinaryProperty object.
     */
    BinaryProperty(BinaryProperty const & a_binary_property) = default;

    /**
     * @brief Construct a new Base Status object with moving BinaryProperty object.
     * @param [in] a_binary_property A new BinaryProperty object is created by moving this BinaryProperty object.
     */
    BinaryProperty(BinaryProperty && a_binary_property) = default;

    /**
     * @brief Copy a BinaryProperty object with a BinaryProperty object.
     * @param [in] a_binary_property The BinaryProperty object that need to copy. 
     * @return BinaryProperty object that after copying.
     */
    BinaryProperty &operator=(BinaryProperty const & a_binary_property) = default;

    /**
     * @brief Move a BinaryProperty object with a BinaryProperty object.
     * @param [in] a_binary_property The BinaryProperty object that need to move. 
     * @return BinaryProperty object that after moving.
     */
    BinaryProperty &operator=(BinaryProperty && a_binary_property) = default;

    /**
     * @brief Destroy the BinaryProperty object.
     */
    ~BinaryProperty() noexcept = default;
    
    /**
     * @brief This operation sets value property associated with the name. 
     * @param [in] a_data The value property of class BinaryProperty.
     * @param [in] a_len  The length of value.
     * @note Input value is guint8_t const.
     */
    inline gvoid_t value(guint8_t const *const a_data, gint32_t const &a_len)
    {
        this->m_value.assign(a_data, &a_data[a_len]);
    }
    
    /**
     * @brief This operation sets value property associated with the name. 
     * @param [in] data The value property of class BinaryProperty.
     * @note Input value is std::vector<sec_octet_t> const.
     */
    inline gvoid_t value(std::vector<sec_octet_t> const &data) noexcept
    {
        m_value = data;
    }

    /**
     * @brief This operation gets value property associated with the name.
     * @return The value property associated with the name.
     * @note Return value is const.
     */
    inline std::vector<sec_octet_t> const *value() const noexcept
    {
        return &m_value;
    }

    /**
     * @brief This operation gets name property of class BinaryProperty.
     * @return The name property of class BinaryProperty. 
     * @note Return value is const.
     */
    inline gstring_t const &name() const noexcept
    {
        return m_name;
    }

    /**
     * @brief This operation sets name property.
     * @param [in] str The name property of class BinaryProperty.
     * @note Input value is const
     */
    inline gvoid_t name(gstring_t const &str) noexcept
    {
        m_name = str;
    }

    /**
     * @brief This operation gets propagate property.
     * @return The propagate property of class BinaryProperty. 
     * @retval true The name and value information need exchange over the network.
     * @retval false The name and value information do not need exchange over the network.
     * @note Return value is const.The name and value information exchange over the network if this return true indicate.
     */
    inline gbool_t propagate() const noexcept
    {
        return m_propagate;
    }

    /**
     * @brief This operation sets propagate property.
     * @param [in] v The propagate property of class BinaryProperty. 
     * @note Input value is const.The name and value information exchange over the network if this return true indicate.
     */
    inline gvoid_t propagate(gbool_t const v) noexcept
    {
        m_propagate = v;
    }
    /**
     * @brief Serialize the name and value information if propagate property is true.
     * @param [in,out] a_cdr Serialized data that exchanging over the network. 
     * @note Only name and value will be serialized.
     */
    gvoid_t serialize(rtps::DdsCdr &a_cdr) const noexcept;

    /**
     * @brief Deserialize the name and value information if propagate property is true.
     * @param [in,out] a_cdr Deserialized data that exchanging over the network. 
     * @note Only name and value will be deserialized.
     */
    gvoid_t deserialize(rtps::DdsCdr &a_cdr) noexcept;
private:
    gstring_t m_name;
    gbool_t m_propagate;
    std::vector<sec_octet_t> m_value;
};


}/*rtps*/
using BinaryProperty = rtps::BinaryProperty;
using BinaryPropertySeq = std::vector<BinaryProperty>;
} /*gstone*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_BINARYPROPERTY_H*/
