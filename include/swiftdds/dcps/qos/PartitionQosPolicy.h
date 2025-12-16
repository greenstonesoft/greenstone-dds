/**************************************************************
* @file PartitionQosPolicy.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/

#ifndef GSTONE_QOSPOLICY_PARTITION_H
#define GSTONE_QOSPOLICY_PARTITION_H 1

#include "swiftdds/dcps/qos/QosPolicy.h"

namespace dds
{
namespace qos
{
    /**
    * @brief This policy allows the introduction of a logical partition concept inside the "physical" partition induced by a domain.
    */
    class GS_DDS4CPP_API PartitionQosPolicy : public QosPolicy
    {
    public:
        PartitionQosPolicy() : QosPolicy{ "Partition" }, m_value{} {}

        /**
        * @brief This function serializies PartitionQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_value);
            return;
        }

        /**
        * @brief This function deserializies PartitionQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_value);
            return;
        }

        /**
        * @brief This function get partion value.
        * @return a sequence of string means partion value.
        */
        inline std::vector<std::string> const& value() const noexcept
        {
            return m_value;
        }

        /**
        * @brief This function set pation value.
        * @param [in] value_t A sequence of string representing the partion value to be set to.
        */
        inline void value(std::vector<std::string> const& value_t) noexcept {
            m_value = value_t;
        }

        /**
        * @brief This function add a partion value to partion value sequence.
        * @param [in] val String of the partion value to be added to.
        */
        inline void addValue(std::string const& val) noexcept
        {
            m_value.emplace_back(val);
        }

        /**
         * @brief Compare two PartitionQosPolicy objects for equailty.
         * @param [in] l_partition_qos Const Reference of the left PartitionQosPolicy object.
         * @param [in] r_partition_qos Const Reference of the right PartitionQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(PartitionQosPolicy const& l_partition_qos, PartitionQosPolicy const& r_partition_qos) noexcept
        {
            if (l_partition_qos.value() == r_partition_qos.value())
            {
                return true;
            }
            return false;
        }

    private:
        std::vector<std::string> m_value;
    };
}
}

#endif
