/**************************************************************
* @file TopicQos.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_TOPICQOS_API_H
#define GSTONE_TOPICQOS_API_H 1

//#include "../core/EntityQos.h"
#include "dcps/qos/QosPolicy.h"
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace topic
{
    /**
     * @class TopicQos
     * @brief The TopicQos class contains all the possible Qos that can be set for a determined Topic. 
     */
    class GS_DDS4CPP_API TopicQos final
    {
    public:
        /**
         * @brief Constructer of the TopicQos class.
         */
        TopicQos() = default;

        /**
         * @brief Destructer of the TopicQos class.
         */
        ~TopicQos() = default;

        /**
         * @brief Constructor of the class TopicQos by another TopicQos object.
         * @param [in] other Const reference of a TopicQos object.
         */
        TopicQos(TopicQos const& other) = default;

        /**
         * @brief Move constructor of the class TopicQos by another TopicQos object.
         * @param [in] other Rvalue reference of a TopicQos object.
         */
        TopicQos(TopicQos&& other) = default;

        /**
         * @brief Assign a TopicQos object to the locally TopicQos object.
         * @param [in] other Const reference of this TopicQos object.
         * @return Reference of this TopicQos object.
         */
        TopicQos& operator=(TopicQos const& other) = default;

        /**
         * @brief Move assignment of the class TopicQos.
         * @param [in] other Rvalue reference of this TopicQos object.
         * @return Reference of this TopicQos object.
         */
        TopicQos& operator=(TopicQos&& other) = default;

        /**
         * @brief This function get the EntityFactoryQosPolicy object from TopicQos.
         * @return Const reference of EntityFactoryQosPolicy.
         */
        inline dds::qos::EntityFactoryQosPolicy const& entity_factory() const noexcept
        {
            return m_entityFactory;
        }

        /**
         * @brief This function get the TopicDataQosPolicy object from TopicQos.
         * @return Const reference of TopicDataQosPolicy.
         */
        inline dds::qos::TopicDataQosPolicy const& topic_data() const noexcept
        {
            return m_topicData;
        }

        /**
         * @brief This function get the DurabilityQosPolicy object from TopicQos.
         * @return Const reference of DurabilityQosPolicy.
         */
        inline dds::qos::DurabilityQosPolicy const& durability() const noexcept
        {
            return m_durability;
        }

        /**
         * @brief This function get the DurabilityServiceQosPolicy object from TopicQos.
         * @return Const reference of DurabilityServiceQosPolicy.
         */
        inline dds::qos::DurabilityServiceQosPolicy const& durability_service() const noexcept
        {
            return m_durabilityService;
        }

        /**
         * @brief This function get the DeadlineQosPolicy object from TopicQos.
         * @return Const reference of DeadlineQosPolicy.
         */
        inline dds::qos::DeadlineQosPolicy const& deadline() const noexcept
        {
            return m_deadline;
        }

        /**
         * @brief This function get the LatencyBudgetQosPolicy object from TopicQos.
         * @return Const reference of LatencyBudgetQosPolicy.
         */
        inline dds::qos::LatencyBudgetQosPolicy const& latency_budget() const noexcept
        {
            return m_latencyBudget;
        }

        /**
         * @brief This function get the LivelinessQosPolicy object from TopicQos.
         * @return Const reference of LivelinessQosPolicy.
         */
        inline dds::qos::LivelinessQosPolicy const& liveliness() const noexcept
        {
            return m_liveliness;
        }

        /**
         * @brief This function get the ReliabilityQosPolicy object from TopicQos.
         * @return Const reference of ReliabilityQosPolicy.
         */
        inline dds::qos::ReliabilityQosPolicy const& reliability() const noexcept
        {
            return m_reliability;
        }

        /**
         * @brief This function get the DestinationOrderQosPolicy object from TopicQos.
         * @return Const reference of DestinationOrderQosPolicy.
         */
        inline dds::qos::DestinationOrderQosPolicy const& destination_order() const noexcept
        {
            return m_destinationOrder;
        }

        /**
         * @brief This function get the HistoryQosPolicy object from TopicQos.
         * @return Const reference of HistoryQosPolicy.
         */
        inline dds::qos::HistoryQosPolicy const& history() const noexcept
        {
            return m_history;
        }

        /**
         * @brief This function get the ResourceLimitsQosPolicy object from TopicQos.
         * @return Const reference of ResourceLimitsQosPolicy.
         */
        inline dds::qos::ResourceLimitsQosPolicy const& resource_limits() const noexcept
        {
            return m_resourceLimits;
        }

        /**
         * @brief This function get the TransportPriorityQosPolicy object from TopicQos.
         * @return Const reference of TransportPriorityQosPolicy.
         */
        inline dds::qos::TransportPriorityQosPolicy const& transport_priority() const noexcept
        {
            return m_transportPriority;
        }

        /**
         * @brief This function get the LifespanQosPolicy object from TopicQos.
         * @return Const reference of LifespanQosPolicy.
         */
        inline dds::qos::LifespanQosPolicy const& lifespan() const noexcept
        {
            return m_lifespan;
        }

        /**
         * @brief This function get the OwnershipQosPolicy object from TopicQos.
         * @return Const reference of OwnershipQosPolicy.
         */
        inline dds::qos::OwnershipQosPolicy const& ownership() const noexcept
        {
            return m_ownership;
        }

        /**
         * @brief This function set the EntityFactoryQosPolicy object to TopicQos.
         * @param [in] entity_factory_t Const reference of EntityFactoryQosPolicy to be set to.
         */
        inline void entity_factory(dds::qos::EntityFactoryQosPolicy const& entity_factory_t) noexcept
        {
            m_entityFactory = entity_factory_t;
        }

        /**
         * @brief This function set the TopicDataQosPolicy object to TopicQos.
         * @param [in] topic_data_t Const reference of TopicDataQosPolicy to be set to.
         */
        inline void topic_data(dds::qos::TopicDataQosPolicy const& topic_data_t) noexcept
        {
            m_topicData = topic_data_t;
        }

        /**
         * @brief This function set the DurabilityQosPolicy object to TopicQos.
         * @param [in] durability_t Const reference of DurabilityQosPolicy to be set to.
         */
        inline void durability(dds::qos::DurabilityQosPolicy const& durability_t) noexcept
        {
            m_durability = durability_t;
        }

        /**
         * @brief This function set the DurabilityServiceQosPolicy object to TopicQos.
         * @param [in] durability_service_t Const reference of DurabilityServiceQosPolicy to be set to.
         */
        inline void durability_service(dds::qos::DurabilityServiceQosPolicy const& durability_service_t) noexcept
        {
            m_durabilityService = durability_service_t;
        }

        /**
         * @brief This function set the DeadlineQosPolicy object to TopicQos.
         * @param [in] deadline_t Const reference of DeadlineQosPolicy to be set to.
         */
        inline void deadline(dds::qos::DeadlineQosPolicy const& deadline_t) noexcept
        {
            m_deadline = deadline_t;
        }

        /**
         * @brief This function set the LatencyBudgetQosPolicy object to TopicQos.
         * @param [in] latency_budget_t Const reference of LatencyBudgetQosPolicy to be set to.
         */
        inline void latency_budget(dds::qos::LatencyBudgetQosPolicy const& latency_budget_t) noexcept
        {
            m_latencyBudget = latency_budget_t;
        }

        /**
         * @brief This function set the LivelinessQosPolicy object to TopicQos.
         * @param [in] liveliness_t Const reference of LivelinessQosPolicy to be set to.
         */
        inline void liveliness(dds::qos::LivelinessQosPolicy const& liveliness_t) noexcept
        {
            m_liveliness = liveliness_t;
        }

        /**
         * @brief This function set the ReliabilityQosPolicy object to TopicQos.
         * @param [in] reliability_t Const reference of ReliabilityQosPolicy to be set to.
         */
        inline void reliability(dds::qos::ReliabilityQosPolicy const& reliability_t) noexcept
        {
            m_reliability = reliability_t;
        }

        /**
         * @brief This function set the DestinationOrderQosPolicy object to TopicQos.
         * @param [in] destination_order_t Const reference of DestinationOrderQosPolicy to be set to.
         */
        inline void destination_order(dds::qos::DestinationOrderQosPolicy const& destination_order_t) noexcept
        {
            m_destinationOrder = destination_order_t;
        }

        /**
         * @brief This function set the HistoryQosPolicy object to TopicQos.
         * @param [in] history_t Const reference of HistoryQosPolicy to be set to.
         */
        inline void history(dds::qos::HistoryQosPolicy const& history_t) noexcept
        {
            m_history = history_t;
        }

        /**
         * @brief This function set the ResourceLimitsQosPolicy object to TopicQos.
         * @param [in] resource_limits_t Const reference of ResourceLimitsQosPolicy to be set to.
         */
        inline void resource_limits(dds::qos::ResourceLimitsQosPolicy const& resource_limits_t) noexcept
        {
            m_resourceLimits = resource_limits_t;
        }

        /**
         * @brief This function set the TransportPriorityQosPolicy object to TopicQos.
         * @param [in] transport_priority_t Const reference of TransportPriorityQosPolicy to be set to.
         */
        inline void transport_priority(dds::qos::TransportPriorityQosPolicy const& transport_priority_t) noexcept
        {
            m_transportPriority = transport_priority_t;
        }

        /**
         * @brief This function set the LifespanQosPolicy object to TopicQos.
         * @param [in] lifespan_t Const reference of LifespanQosPolicy to be set to.
         */
        inline void lifespan(dds::qos::LifespanQosPolicy const& lifespan_t) noexcept
        {
            m_lifespan = lifespan_t;
        }

        /**
         * @brief This function set the OwnershipQosPolicy object to TopicQos.
         * @param [in] ownership_t Const reference of OwnershipQosPolicy to be set to.
         */
        inline void ownership(dds::qos::OwnershipQosPolicy const& ownership_t) noexcept
        {
            m_ownership = ownership_t;
        }

        /**
         * @brief Compare two TopicQos objects for equailty.
         * @param [in] t1 Const Reference of the left TopicQos object.
         * @param [in] t2 Const Reference of the right TopicQos object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(TopicQos const &t1, TopicQos const &t2) noexcept
        {
            gbool_t const entity_ret{t1.entity_factory() == t2.entity_factory()};

            return ((entity_ret));
        }

        /**
         * @brief Compare two TopicQos objects for inequailty.
         * @param [in] t1 Const Reference of the left TopicQos object.
         * @param [in] t2 Const Reference of the right TopicQos object.
         * @return Return true if inequality, else return false. 
         */
        inline friend gbool_t operator!=(TopicQos const &t1, TopicQos const &t2) noexcept
        {
            return !(t1 == t2);
        }
    private:
        dds::qos::EntityFactoryQosPolicy m_entityFactory;
        dds::qos::TopicDataQosPolicy m_topicData;
        dds::qos::DurabilityQosPolicy m_durability;
        dds::qos::DurabilityServiceQosPolicy m_durabilityService;
        dds::qos::DeadlineQosPolicy m_deadline;
        dds::qos::LatencyBudgetQosPolicy m_latencyBudget;
        dds::qos::LivelinessQosPolicy m_liveliness;
        dds::qos::ReliabilityQosPolicy m_reliability;
        dds::qos::DestinationOrderQosPolicy m_destinationOrder;
        dds::qos::HistoryQosPolicy m_history;
        dds::qos::ResourceLimitsQosPolicy m_resourceLimits;
        dds::qos::TransportPriorityQosPolicy m_transportPriority;
        dds::qos::LifespanQosPolicy m_lifespan;
        dds::qos::OwnershipQosPolicy m_ownership;
    };
}/*topic*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_TOPICQOS_API_H*/
