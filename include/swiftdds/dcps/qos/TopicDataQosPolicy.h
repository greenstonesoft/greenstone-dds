/**************************************************************
* @file TopicDataQosPolicy.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/

#ifndef GSTONE_QOSPOLICY_TOPICDATA_H
#define GSTONE_QOSPOLICY_TOPICDATA_H 1

#include "swiftdds/dcps/qos/QosPolicy.h"

namespace dds
{
namespace qos
{
    /**
    * @brief This QoS allow the application to attach additional information to the created Topic such that when a remote 
    *        application discovers their existence it can examine the information and use it in an application-defined way.
    */
    class GS_DDS4CPP_API TopicDataQosPolicy : public QosPolicy
    {
    public:
        TopicDataQosPolicy() : QosPolicy{ "TopicData" }, m_value{} {}

        /**
        * @brief This function serializies TopicDataQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_value);
            return;
        }

        /**
        * @brief This function deserializies TopicDataQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_value);
            return;
        }

        /**
        * @brief This function get topic data value.
        * @return A sequence of octets means topic data value.
        */
        inline std::vector<octet> const& value() const noexcept
        {
            return m_value;
        }

        /**
        * @brief This function set topic data value.
        * @param [in] value_t A sequence of octets means the topic data value to be set to.
        */
        inline void value(std::vector<octet> const& value_t) noexcept
        {
            m_value = value_t;
        }

        /**
         * @brief Compare two TopicDataQosPolicy objects for equailty.
         * @param [in] l_topicData_qos Const Reference of the left TopicDataQosPolicy object.
         * @param [in] r_topicData_qos Const Reference of the right TopicDataQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(TopicDataQosPolicy const& l_topicData_qos, TopicDataQosPolicy const& r_topicData_qos) noexcept
        {
            if (l_topicData_qos.value() == r_topicData_qos.value())
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
