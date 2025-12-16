/**************************************************************
* @file Property.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_PROPERTY_H
#define GSTONE_PROPERTY_H 1

#include <string>
#include <vector>

#include "swiftdds/dcps/PITypes.h"
#include "swiftdds/dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace rtps {
class DdsCdr;
} /*rtps*/
} /*gstone*/

namespace gstone {
namespace rtps{
/**
* @class Property
* @brief The DDS-Security specification uses Property_t sequences as a generic data type to configure the 
* security plugins, pass metadata and provide an extensible mechanism for vendors to configure the 
* behavior of their plugins without breaking portability or interoperability.
* @note This class is used for the DDS-Security specification.
*/
class GS_DDS4CPP_API Property
{
public:
    /**
     * @brief Construct a new Property object
     * @param [in] a_name      The a_name may be used for information interpretation.
     * @param [in] a_value     The a_value may be used for information value associated with the a_name.
     * @param [in] a_propagate The a_propagate may be used for information exchange over the network.
     * @note The type of value is gstring_t
     */
    Property(gstring_t const &a_name, gstring_t const &a_value, gbool_t const &a_propagate = false)
        : m_name {a_name}, m_value {a_value}, m_propagate {a_propagate}
    {
    }

    /**
     * @brief Construct a new Property object
     * @param [in] a_name      The a_name may be used for information interpretation.
     * @param [in] a_data      The a_data may be used for information value associated with the a_name.
     * @param [in] a_len       The a_len may be used for the length of a_data.
     * @param [in] a_propagate The a_propagate may be used for information exchange over the network.
     * @note The type of a_data is guint8_t.
     */
    Property(gstring_t const &a_name, guint8_t const *const a_data, gint32_t const &a_len, gbool_t const a_propagate = true)
        : m_name {a_name}, m_value {a_data, &a_data[a_len]}, m_propagate {a_propagate}
    {

    }

    /**
     * @brief Construct a new Property object with default parameter.
     */
    Property() = default;

    /**
     * @brief Construct a new Property object with copying Property object.
     * @param [in] a_property A new Property object is created by copying this Property object.
     */
    Property(Property const & a_property) = default;

    /**
     * @brief Construct a new Base Status object with moving Property object.
     * @param [in] a_property A new Property object is created by moving this Property object.
     */
    Property(Property && a_property) = default;

    /**
     * @brief Copy a Property object with a Property object.
     * @param [in] a_property The Property object that need to copy.
     * @return Property object that after copying.
     */
    Property &operator=(Property const & a_property) = default;

    /**
     * @brief Move a Property object with a Property object.
     * @param [in] a_property The Property object that need to move. 
     * @return Property object that after moving.
     */
    Property &operator=(Property && a_property) = default;

    /**
     * @brief Destroy the Property object.
     */
    virtual ~Property() = default;

    /**
     * @brief This operation gets name property.
     * @return The name property of class Property.
     * @note Return value is const.
     */
    inline gstring_t const & name() const noexcept
    {
        return m_name;
    }

    /**
     * @brief This operation sets name property.
     * @param [in] str The name property of class Property.
     * @note Input value is const
     */
    inline gvoid_t name(gstring_t const &str) noexcept
    {
        m_name = str;
    }

    /**
     * @brief This operation gets value property associated with the name.
     * @return The value property of class Property.
     * @note Return value is const.
     */
    inline gstring_t  const & value() const noexcept
    {
        return m_value;
    }

    /**
     * @brief This operation sets value property associated with the name.
     * @param [in] str The value property of class Property.
     * @note Input value is const.
     */
    inline gvoid_t value(gstring_t const &str) noexcept
    {
        m_value = str;
    }

    /**
     * @brief This operation gets propagate property.
     * @return The propagate property of class Property. 
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
     * @param [in] v The propagate property of class Property.
     * @note Input value is const.The name and value information exchange over the network if this return true indicate.
     */
    inline gvoid_t propagate(gbool_t const v) noexcept
    {
        m_propagate = v;
    }

    /**
     * @brief Serialize the name and value information if propagate property is true.
     * @param[in,out] a_cdr Serialized data that exchanging over the network.
     * @note Only name and value will be serialized.
     */
    DdsCdr& serialize(rtps::DdsCdr &a_cdr)const noexcept;

    /**
     * @brief Deserialize the name and value information if propagate property is true.
     * @param[in,out] a_cdr Deserialized data that exchanging over the network.
     * @note Only name and value will be deserialized.
     */
    DdsCdr& deserialize(rtps::DdsCdr &a_cdr)noexcept;
private:
    // attributes.
    gstring_t m_name;
    gstring_t m_value;
    gbool_t m_propagate;
};


}/*rtps*/
using Property = rtps::Property;
using PropertySeq = std::vector<Property>;
} /*gstone*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_PROPERTY_H*/

