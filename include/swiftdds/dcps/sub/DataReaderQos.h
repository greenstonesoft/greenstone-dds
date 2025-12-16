/**************************************************************
* @file DataReaderAttributes.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_DATAREADERQOS_API_H
#define GSTONE_DATAREADERQOS_API_H 1

#include "swiftdds/dcps/qos/UserDataQosPolicy.h"
#include "swiftdds/dcps/qos/TimeBasedFilterQosPolicy.h"
#include "swiftdds/dcps/qos/LivelinessQosPolicy.h"
#include "swiftdds/rtps/Locator.h"
#include "swiftdds/dcps/qos/PropertyQosPolicy.h"
#include "swiftdds/dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace sub
{
    guint64_t const DEFAULT_HEARTBEAT_RESPONSE_DELAY{ 1U };
    guint64_t const DEFAULT_HEARTBEAT_SUPPRESSION_DURATION{ 1U };
    guint64_t const DEFAULT_REDUNDANT_ACK_PERIOD{ 200U };
    guint32_t const DEFAULT_ACK_PER_SEQ_NUM{ 10U };

    /**
     * @class DataReaderAttributes
     * @brief a part of reader's qos
     */
    class GS_DDS4CPP_API DataReaderAttributes final
    {
    public:
        /**
         * @brief Construct a new Data Reader Attributes object
         */
        DataReaderAttributes() noexcept
        {
            m_heartbeatResponseDelay.set_millisecond(DEFAULT_HEARTBEAT_RESPONSE_DELAY);
            m_heartbeatSuppressionDuration.set_millisecond(DEFAULT_HEARTBEAT_SUPPRESSION_DURATION);
            //m_sendRedundantAck = false;
            //m_redundantAckPeriod = DEFAULT_REDUNDANT_ACK_PERIOD;
            //m_ackWithDataPerSeqNum = 0U;
        }
        
        /**
         * @brief Getter fo heartbeat_response_delay
         * @return gstone::rtps::Duration_t The value of heartbeat_response_delay
         */
        inline gstone::rtps::Duration_t const& heartbeat_response_delay() const noexcept 
        {
            return m_heartbeatResponseDelay;
        }
        
        /**
         * @brief  Getter fo heartbeat_suppression_duration
         * @return gstone::rtps::Duration_t const& The value of heartbeat_suppression_duration
         */
        inline gstone::rtps::Duration_t const& heartbeat_suppression_duration() const noexcept 
        {
            return m_heartbeatSuppressionDuration;
        }
        
        /**
         * @brief Getter of ack_with_data_per_seq_num
         * @return guint32_t const& The value of ack_with_data_per_seq_num
         */
        inline guint32_t const& ack_with_data_per_seq_num() const noexcept
        {
            return m_ackWithDataPerSeqNum;
        }

        /**
         * @brief Getter of pre_emptive_acknack_duration
         * @return gstone::rtps::Duration_t The value of pre_emptive_acknack_duration
         */
        inline gstone::rtps::Duration_t const& pre_emptive_acknack_duration() const noexcept 
        {
            return m_preEmptiveAckNackDuration;
        }
        
        /**
         * @brief Setter of heartbeat_response_delay
         * @param [in] delay The value of heartbeat_response_delay
         */
        inline void heartbeat_response_delay(gstone::rtps::Duration_t const& delay) noexcept
        {
            m_heartbeatResponseDelay = delay;
        }
        
        /**
         * @brief Setter of heartbeat_suppression_duration
         * @param [in] duration The value of heartbeat_suppression_duration
         */
        inline void heartbeat_suppression_duration(gstone::rtps::Duration_t const& duration) noexcept
        {
            m_heartbeatSuppressionDuration = duration;
        }
        
        /**
         * @brief Setter of ackWithDataPerSeqNum
         * @param [in] ack The value of ackWithDataPerSeqNum
         */
        inline void ack_with_data_per_seq_num(guint32_t const& ack) noexcept 
        {
            m_ackWithDataPerSeqNum = ack;
        }

        /**
        * @brief Setting only recv by udp
        * @param [in] value true - only recv by udp
        */
        inline void only_recv_by_udp(bool const value) noexcept
        {
            m_onlyRecvByUdp = value;
        }

        /**
        * @brief Is only recv by udp?
        */
        inline bool only_recv_by_udp() const noexcept
        {
            return m_onlyRecvByUdp;
        }

        /**
        * @brief Reader's max recv size
        * @param [in] value 0 - no limits
        */
        inline void recv_max_frag_size(guint32_t const value) noexcept
        {
            m_recvMaxFragSize = value;
        }

        /**
        * @brief Reader's max recv size
        */
        inline guint32_t recv_max_frag_size() const noexcept
        {
            return m_recvMaxFragSize;
        }

        /**
        * @brief Push back prefer transport order
        * @param [in] kind Transport Kind
        */
        inline void push_back_prefer_transport_kind(gstone::rtps::TransportKind_t const kind) noexcept
        {
            m_preferTransportOrder.push_back(kind);
        }

        /**
        * @brief Clear prefer transport order
        */
        inline void clear_back_prefer_transport_kind() noexcept
        {
            m_preferTransportOrder.clear();
        }

        /**
        * @brief Query prefer transport order
        */
        inline std::vector<gstone::rtps::TransportKind_t> prefer_transport_order() const noexcept
        {
            return m_preferTransportOrder;
        }

        /**
         * @brief Setter of pre_emptive_acknack_duration
         * @param [in] _duration The value of pre_emptive_acknack_duration
         */
        inline void pre_emptive_acknack_duration(gstone::rtps::Duration_t const& _duration) noexcept
        {
            m_preEmptiveAckNackDuration = _duration;
        }

    private:
        bool m_onlyRecvByUdp{false};
        guint32_t m_recvMaxFragSize{0U};
        std::vector<gstone::rtps::TransportKind_t> m_preferTransportOrder{};
        gstone::rtps::Duration_t m_heartbeatResponseDelay{};
        gstone::rtps::Duration_t m_heartbeatSuppressionDuration{};

        guint32_t m_ackWithDataPerSeqNum{ DEFAULT_ACK_PER_SEQ_NUM };

        gstone::rtps::Duration_t m_preEmptiveAckNackDuration{gstone::rtps::Duration::duration_infinite()};
    };

    /**
     * @class DataReaderQos
     * @brief The qos of data reader
     */
    class GS_DDS4CPP_API DataReaderQos
    {
    public:
        /**
         * @brief Construct a new Data Reader Qos object
         */
        DataReaderQos()
        {
            m_reliability.kind(dds::qos::ReliabilityQosPolicyKind::BEST_EFFORT_RELIABILITY_QOS);
            m_resourceLimits.max_instances(0);
            m_resourceLimits.max_samples(0);
            m_resourceLimits.max_samples_per_instance(0);
        }
        
        /**
         * @brief Destroy the Data Reader Qos object
         */
        virtual ~DataReaderQos() = default;
        
        /**
         * @brief Copy-Construct a new DataReaderQos object
         * @param [in] other Another DataReaderQos
         */
        DataReaderQos(DataReaderQos const& other) = default;
        
        /**
         * @brief Assign a DataReaderQos object to the locally DataReaderQos object.
         * @param [in] other. reference of a DataReaderQos object.
         * @return Reference of the locally DataReaderQos object.
         */
        DataReaderQos& operator=(DataReaderQos const& other) = default;
        
        /**
         * @brief Move-Construct a new DataReaderQos object
         * @param [in] other Another DataReaderQos
         */
        DataReaderQos(DataReaderQos&& other) = default;
        
        /**
         * @brief Assign a DataReaderQos object to the locally DataReaderQos object.
         * @param [in] other. reference of a DataReaderQos object.
         * @return Reference of the locally DataReaderQos object.
         */
        DataReaderQos& operator=(DataReaderQos&& other) = default;

        /**
         * @brief Getter of durability
         * @return dds::qos::DurabilityQosPolicy const& The value of durability
         */
        inline dds::qos::DurabilityQosPolicy const& durability() const noexcept
        {
            return m_durability;
        }
        
        /**
         * @brief Getter of deadline
         * @return dds::qos::DeadlineQosPolicy const& The value of deadline
         */
        inline dds::qos::DeadlineQosPolicy const& deadline() const noexcept 
        {
            return m_deadline;
        }
        
        /**
         * @brief Getter of latency_budget
         * @return dds::qos::LatencyBudgetQosPolicy const& The value of latency_budget
         */
        inline dds::qos::LatencyBudgetQosPolicy const& latency_budget() const noexcept {
            return m_latencyBudget;
        }
        
        /**
         * @brief Getter of liveliness
         * @return dds::qos::LivelinessQosPolicy const& The value of liveliness
         */
        inline dds::qos::LivelinessQosPolicy const& liveliness() const noexcept 
        {
            return m_liveliness;
        }
        
        /**
         * @brief Getter of reliability
         * @return dds::qos::ReliabilityQosPolicy const& The value of reliability
         */
        inline dds::qos::ReliabilityQosPolicy const& reliability() const noexcept 
        {
            return m_reliability;
        }
        
        /**
         * @brief Getter of destination_order
         * @return dds::qos::DestinationOrderQosPolicy const& The value of destination_order
         */
        inline dds::qos::DestinationOrderQosPolicy const& destination_order() const noexcept
        {
            return m_destinationOrder;
        }
        
        /**
         * @brief Getter of history
         * @return dds::qos::HistoryQosPolicy const& The value of history
         */
        inline dds::qos::HistoryQosPolicy const& history() const noexcept 
        {
            return m_history;
        }
        
        /**
         * @brief Getter of resource_limits
         * @return dds::qos::ResourceLimitsQosPolicy const& The value of resource_limits
         */
        inline dds::qos::ResourceLimitsQosPolicy const& resource_limits() const noexcept
        {
            return m_resourceLimits;
        }
        
        /**
         * @brief Getter of user_data
         * @return dds::qos::UserDataQosPolicy const& The value of user_data
         */
        inline dds::qos::UserDataQosPolicy const& user_data() const noexcept
        {
            return m_userData;
        }
        
        /**
         * @brief Getter of ownership
         * @return dds::qos::OwnershipQosPolicy const& The value of ownership
         */
        inline dds::qos::OwnershipQosPolicy const& ownership() const noexcept 
        {
            return m_ownership;
        }
        
        /**
         * @brief Getter of time_based_filter
         * @return dds::qos::TimeBasedFilterQosPolicy const& The value of time_based_filter
         */
        inline dds::qos::TimeBasedFilterQosPolicy const& time_based_filter() const noexcept
        {
            return m_timeBasedFilter;
        }
        
        /**
         * @brief Getter of reader_data_lifecycle
         * @return dds::qos::ReaderDataLifecycleQosPolicy const& The value of reader_data_lifecycle
         */
        inline dds::qos::ReaderDataLifecycleQosPolicy const& reader_data_lifecycle() const noexcept 
        {
            return m_readerDataLifecycle;
        }
        
        /**
         * @brief Getter of thread_schedule
         * @return dds::qos::ThreadScheduleQosPolicy const& The value of thread_schedule
         */
        inline dds::qos::ThreadScheduleQosPolicy const& thread_schedule() const noexcept
        {
            return m_threadSchedule;
        }
        
        /**
         * @brief Getter of flow_control
         * @return dds::qos::FlowControlQosPolicy const& The value of flow_control
         */
        inline dds::qos::FlowControlQosPolicy const& flow_control() const noexcept
        {
            return m_flowControl;
        }

        inline dds::qos::DisablePositiveACKsQosPolicy const& disable_positive_acks() const noexcept
        {
            return m_disablePositiveACKs;
        }

        /**
         * @brief Setter of durability
         * @param [in] durability_t The value of durability
         */
        inline void durability(dds::qos::DurabilityQosPolicy const& durability_t) noexcept 
        {
            m_durability = durability_t;
        }
        
        /**
         * @brief Setter of deadline
         * @param [in] deadline_t The value of deadline
         */
        inline void deadline(dds::qos::DeadlineQosPolicy const& deadline_t) noexcept 
        {
            m_deadline = deadline_t;
        }
        
        /**
         * @brief Setter of latency_budget
         * @param [in] latency_budget_t The value of latency_budget
         */
        inline void latency_budget(dds::qos::LatencyBudgetQosPolicy const& latency_budget_t) noexcept 
        {
            m_latencyBudget = latency_budget_t;
        }
        
        /**
         * @brief Setter of liveliness
         * @param [in] liveliness_t The value of liveliness
         */
        inline void liveliness(dds::qos::LivelinessQosPolicy const& liveliness_t) noexcept 
        {
            m_liveliness = liveliness_t;
        }
        
        /**
         * @brief Setter of reliability
         * @param [in] reliability_t The value of reliability
         */
        inline void reliability(dds::qos::ReliabilityQosPolicy const& reliability_t) noexcept 
        {
            m_reliability = reliability_t;
        }
        
        /**
         * @brief Setter of destination_order
         * @param [in] destination_order_t The value of destination_order
         */
        inline void destination_order(dds::qos::DestinationOrderQosPolicy const& destination_order_t) noexcept 
        {
            m_destinationOrder = destination_order_t;
        }
        
        /**
         * @brief Setter of history
         * @param [in] history_t The value of history
         */
        inline void history(dds::qos::HistoryQosPolicy const& history_t) noexcept 
        {
            m_history = history_t;
        }
        
        /**
         * @brief Setter of resource_limits
         * @param [in] resource_limits_t The value of resource_limits
         */
        inline void resource_limits(dds::qos::ResourceLimitsQosPolicy const& resource_limits_t) noexcept 
        {
            m_resourceLimits = resource_limits_t;
        }
        
        /**
         * @brief Setter of user_data
         * @param [in] user_data_t The value of user_data
         */
        inline void user_data(dds::qos::UserDataQosPolicy const& user_data_t) noexcept 
        {
            m_userData = user_data_t;
        }
        
        /**
         * @brief Setter of ownership
         * @param [in] ownership_t The value of ownership
         */
        inline void ownership(dds::qos::OwnershipQosPolicy const& ownership_t) noexcept 
        {
            m_ownership = ownership_t;
        }
        
        /**
         * @brief Setter of time_based_filter
         * @param [in] time_based_filter_t The value of time_based_filter
         */
        inline void time_based_filter(dds::qos::TimeBasedFilterQosPolicy const& time_based_filter_t) noexcept 
        {
            m_timeBasedFilter = time_based_filter_t;
        }
        
        /**
         * @brief Setter of reader_data_lifecycle
         * @param [in] reader_data_lifecycle_t The value of reader_data_lifecycle
         */
        inline void reader_data_lifecycle(dds::qos::ReaderDataLifecycleQosPolicy const& reader_data_lifecycle_t) noexcept 
        {
            m_readerDataLifecycle = reader_data_lifecycle_t;
        }
        
        /**
         * @brief Setter of thread_schedule
         * @param [in] thread_schedule_t The value of thread_schedule
         */
        inline void thread_schedule(dds::qos::ThreadScheduleQosPolicy const& thread_schedule_t) noexcept 
        {
            m_threadSchedule = thread_schedule_t;
        }
        
        /**
         * @brief Setter of flow control.
         * @param [in] flow_control_t The value of flow_control
         */
        inline void flow_control(dds::qos::FlowControlQosPolicy const& flow_control_t) noexcept 
        {
            m_flowControl = flow_control_t;
        }

        inline void disable_positive_acks(dds::qos::DisablePositiveACKsQosPolicy const& val) noexcept 
        {
            m_disablePositiveACKs = val;
        }

        /**
         * @brief Getter of attributes
         * @return DataReaderAttributes const& The value of attributes
         */
        DataReaderAttributes const& attributes() const noexcept 
        {
            return m_attributes;
        }
        
        /**
         * @brief Getter of property
         * @return dds::qos::PropertyQosPolicy const& The value of property
         */
        dds::qos::PropertyQosPolicy const& property() const noexcept 
        {
            return m_property;
        }
        
        /**
         * @brief Setter of property
         * @param [in] attributes_t The value of attributes
         */
        inline void attributes(DataReaderAttributes const& attributes_t) noexcept 
        {
            m_attributes = attributes_t;
        }
        
        /**
         * @brief Setter of property
         * @param [in] property_t The value of property
         */
        inline void property(dds::qos::PropertyQosPolicy const& property_t) noexcept 
        {
            m_property = property_t;
        }
    private:
        dds::qos::DurabilityQosPolicy m_durability{};
        dds::qos::DeadlineQosPolicy m_deadline{};
        dds::qos::LatencyBudgetQosPolicy m_latencyBudget{};
        dds::qos::LivelinessQosPolicy m_liveliness{};
        dds::qos::ReliabilityQosPolicy m_reliability{};
        dds::qos::DestinationOrderQosPolicy m_destinationOrder{};
        dds::qos::HistoryQosPolicy m_history{};
        dds::qos::ResourceLimitsQosPolicy m_resourceLimits{};
        dds::qos::UserDataQosPolicy m_userData{};
        dds::qos::OwnershipQosPolicy m_ownership{};
        dds::qos::TimeBasedFilterQosPolicy m_timeBasedFilter{};
        dds::qos::ReaderDataLifecycleQosPolicy m_readerDataLifecycle{};
        dds::qos::ThreadScheduleQosPolicy m_threadSchedule{};
        dds::qos::FlowControlQosPolicy m_flowControl{};
        dds::qos::DisablePositiveACKsQosPolicy m_disablePositiveACKs{};

        DataReaderAttributes m_attributes{};

        dds::qos::PropertyQosPolicy m_property{};
    };
} /* sub */
} /* dds */

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_DATAREADERQOS_API_H*/
