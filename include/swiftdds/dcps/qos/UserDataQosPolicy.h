/**************************************************************
* @file UserDataQosPolicy.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/

#ifndef GSTONE_QOSPOLICY_USERDATA_H
#define GSTONE_QOSPOLICY_USERDATA_H 1

#include "swiftdds/dcps/qos/QosPolicy.h"

namespace dds
{
namespace qos
{
    /**
    * @brief This QoS allow the application to attach additional information to the created Entity objects such that when 
    *        a remote application discovers their existence it can access that information and use it for its own purposes.
    */
    class GS_DDS4CPP_API UserDataQosPolicy : public QosPolicy
    {
    public:
        UserDataQosPolicy() : QosPolicy{ "UserData" }, m_value{} {}

        /**
        * @brief This function serializies UserDataQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_value);
            return;
        }

        /**
        * @brief This function deserializies UserDataQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_value);
            return;
        }

        /**
        * @brief This function get user data value.
        * @return Const reference of a sequence of octets representing user data value.
        */
        inline std::vector<octet> const& value() const noexcept
        {
            return m_value;
        }

        /**
        * @brief This function set user data value.
        * @param [in] value_t A sequence of octets representing the user data value to be set to.
        */
        inline void value(std::vector<octet> const& value_t) noexcept
        {
            m_value = value_t;
        }

        /**
         * @brief Compare two UserDataQosPolicy objects for equailty.
         * @param [in] l_userData_qos Const Reference of the left UserDataQosPolicy object.
         * @param [in] r_userData_qos Const Reference of the right UserDataQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(UserDataQosPolicy const& l_userData_qos, UserDataQosPolicy const& r_userData_qos) noexcept
        {
            if (l_userData_qos.value() == r_userData_qos.value())
            {
                return true;
            }
            return false;
        }

    private:
        std::vector<octet> m_value;
    };
}
}

#endif
