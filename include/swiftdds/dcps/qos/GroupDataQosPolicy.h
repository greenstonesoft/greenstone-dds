/**************************************************************
* @file GroupDataQosPolicy.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/

#ifndef GSTONE_QOSPOLICY_GROUPDATA_H
#define GSTONE_QOSPOLICY_GROUPDATA_H 1

#include "swiftdds/dcps/qos/QosPolicy.h"

namespace dds
{
namespace qos
{
    /**
    * @brief This QoS allow the application to attach additional information to the created Publisher or Subscriber.
    */
    class GS_DDS4CPP_API GroupDataQosPolicy : public QosPolicy
    {
    public:
        GroupDataQosPolicy() : QosPolicy{ "GroupData" }, m_value{} {}

        /**
        * @brief This function serializies GroupDataQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_value);
            return;
        }

        /**
        * @brief This function deserializies GroupDataQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_value);
            return;
        }

        /**
        * @brief This function get group data value.
        * @return A sequence of octets representing group data value.
        */
        inline std::vector<octet> const& value() const noexcept 
        {
            return m_value;
        }

        /**
        * @brief This function set group data value.
        * @param [in] value_t A sequence of octets means the group data value to be set to.
        */
        inline void value(std::vector<octet> const& value_t) noexcept
        {
            m_value = value_t;
        }

        /**
         * @brief Compare two GroupDataQosPolicy objects for equailty.
         * @param [in] l_groupData_qos Const Reference of the left GroupDataQosPolicy object.
         * @param [in] r_groupData_qos Const Reference of the right GroupDataQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(GroupDataQosPolicy const& l_groupData_qos, GroupDataQosPolicy const& r_groupData_qos)noexcept
        {
            if (l_groupData_qos.value() == r_groupData_qos.value())
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
