/**************************************************************
* @file QosPolicyCount.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_QOSPOLICYCOUNT_H
#define GSTONE_QOSPOLICYCOUNT_H 1

#include <vector>
#include "dcps/DdsBaseTypes.h"
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace qos
{
    class QosPolicyCount;
    using QosPolicyCountSeq = std::vector<QosPolicyCount>;

    /**
     * @class QosPolicyCount
     * @brief This class holds a counter for qos policy id
     */
    class GS_DDS4CPP_API QosPolicyCount final
    {
    public:
        /**
         * @brief Constructer of the QosPolicyCount class
         * @param [in] policyId_t The qos policy id
         * @param [in] count_t The count of this policy id
         */
        QosPolicyCount(DDS::QosPolicyId_t const policyId_t, gint32_t const count_t) noexcept :m_policyId{ policyId_t }, m_count{ count_t } {}

        /**
         * @brief Copy constructer of the QosPolicyCount class
         * @param [in] other Const reference of the QosPolicyCount object to copied
         */
        QosPolicyCount(QosPolicyCount const& other) noexcept :m_policyId{ other.policy_id() }, m_count{ other.count() } {}

        /**
         * @brief Move constructer of the QosPolicyCount class
         * @param [in] other Rvalue reference of the QosPolicyCount object to moved
         */
        QosPolicyCount(QosPolicyCount&& other) = default;

        /**
         * @brief Assign a QosPolicyCount object to the locally QosPolicyCount object.
         * @param [in] other Const reference of this QosPolicyCount object.
         * @return Reference of this QosPolicyCount object.
         */
        QosPolicyCount& operator=(QosPolicyCount const& other) = default;

        /**
         * @brief Move assignment of the class QosPolicyCount
         * @param [in] other Rvalue reference of this QosPolicyCount object.
         * @return Reference of this QosPolicyCount object.
         */
        QosPolicyCount& operator=(QosPolicyCount&& other) = default;

        /**
         * @brief Destructer of the QosPolicyCount class
         */
        ~QosPolicyCount() = default;


        /**
         * @brief This function get the policy id
         * @return The qos policy id 
         */
        inline DDS::QosPolicyId_t policy_id() const  noexcept { return this->m_policyId; }

        /**
         * @brief This function get the count
         * @return The count of this qos policy id 
         */
        inline gint32_t count() const  noexcept { return this->m_count; }


        /**
         * @brief This function set the policy id
         * @param [in] policy_id_t The policy id to be set to
         */
        inline void policy_id(DDS::QosPolicyId_t const& policy_id_t) noexcept
        {
            m_policyId = policy_id_t;
        }

        /**
         * @brief This function set the count
         * @param [in] count_t The count to be set to
         */
        inline void count(gint32_t const& count_t) noexcept
        {
            m_count = count_t;
        }

        /**
         * @brief Compare two QosPolicyCount objects for equailty.
         * @param [in] l_qos_policy_count Const Reference of the left QosPolicyCount object.
         * @param [in] r_qos_policy_count Const Reference of the right QosPolicyCount object.
         * @return Return true if equality, else return false. 
         */
        inline friend bool operator ==(QosPolicyCount const& l_qos_policy_count, QosPolicyCount const& r_qos_policy_count) noexcept
        {
            return (l_qos_policy_count.policy_id() == r_qos_policy_count.policy_id()) && (l_qos_policy_count.count() == r_qos_policy_count.count());
        }

    private:
        DDS::QosPolicyId_t m_policyId;
        gint32_t m_count;
    };
}/*qos*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_QOSPOLICYCOUNT_H*/
