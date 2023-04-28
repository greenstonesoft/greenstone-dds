/**************************************************************
* @file DataWriterQos.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#ifndef GSTONE_DATAWRITERQOS_API_H
#define GSTONE_DATAWRITERQOS_API_H 1

#include "dcps/qos/QosPolicy.h"
#include "dcps/PITypes.h"
#include "dcps/qos/PropertyQosPolicy.h"
#include "rtps/Locator.h"
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace pub
{
    guint32_t const MAX_UDP_DATA_SIZE {65507U};                            ///< Max size of UDP data.
    guint32_t const DEFAULT_BATCH_SIZE {10U};                              ///< Default value of DataWriterAttributes's m_batchSize.
    guint32_t const DEFAULT_HEARTBEAT_PERIOD {10U};                        ///< Default value of DataWriterAttributes's m_heartbeatPeriod.
    guint32_t const DEFAULT_NACK_RESPONSE_DELAY {1U};                      ///< Default value of DataWriterAttributes's m_nackResponseDelay.
    guint32_t const DEFAULT_NACK_SUPPER_RESSION_DURATION {1U};             ///< Default value of DataWriterAttributes's m_nackSupperRessionDuration.
    guint32_t const DEFAULT_HISTORY_CACHE_CAPACITY {50U};                  ///< Default value of DataWriterAttributes's m_historyCacheCapacity.
    guint32_t const DEFAULT_DATA_CHANNEL_FLOW_CTL_BAND_WIDTH {0U};         ///< Default value of DataWriterAttributes's m_dataChannelFlowCtlBandWidth.
    guint32_t const DEFAULT_FLOW_CTL_THRESHOLD {0U};                       ///< Default value of DataWriterAttributes's m_flowCtlThreshold.
    guint32_t const DEFAULT_HB_WITH_DATA_PER_SEQ_NUM {10U};                ///< Default value of DataWriterAttributes's m_hbWithDataPerSeqNum.
    guint32_t const DEFAULT_READER_ACTIVE_DURATION {10000U};               ///< Default value of DataWriterAttributes's m_readerActiveDuration.
    guint32_t const DEFAULT_MAX_SHM_FRAG_SIZE {33U * 1024U * 1024U};       ///< Default value of DataWriterAttributes's m_maxShmFragSize.
    guint32_t const DEFAULT_ZERO_COPY_MEMROY_SIZE {100U * 1024U * 1024U};  ///< Default value of DataWriterAttributes's m_zeroCopyMemorySize.
    
    /**
    * @class DataWriterAttributes
    * @brief This class is a collection of a DataWriter's configurable attributes.
    */
    class GS_DDS4CPP_API DataWriterAttributes final
    {
    public:
        /**
        * @brief This function gets the value of 'is_stateful' parameter.
        * @return Return true or false.
        * @retval true  The DataWriter is a stateful DataWriter.
        * @retval false The DataWriter is a stateless DataWriter.
        */
        inline gbool_t const& is_stateful() const noexcept 
        {
            return m_isStateful;
        }
        
        /**
        * @brief This function gets the value of 'm_isWithKey' parameter.
        * @return Return true or false.
        * @retval true  It will transports the InstanceHandle of the DataWriter in the EDP by inlineqos.
        * @retval false It won't transports the InstanceHandle of the DataWriter in the EDP by inlineqos.
        */
        inline gbool_t const& is_with_key() const noexcept 
        {
            return m_isWithKey;
        }
        
        /**
        * @brief This function gets the value of 'm_pushMode' parameter.
        * @return Return true or false.
        * @retval true  If pushMode==true, then the Writer will push changes to the reader.
        * @retval false If pushMode==false, changes will only be announced via heartbeats and only be sent as response to the 
        * request of a reader only be announced via heartbeats and only be sent as response to the request of a reader.
        */
        inline gbool_t const& push_mode() const noexcept 
        {
            return m_pushMode;
        }
        
        /**
        * @brief This function gets the value of 'm_isSync' parameter.
        * @return Return true or false.
        * @retval true   It will send a change immediately after putting it to push list.
        * @retval false  It won't send a change immediately after putting it to push list.
        */
        inline gbool_t const& is_sync() const noexcept 
        {
            return m_isSync;
        }
        
        /**
        * @brief This function gets the value of 'm_commKind' parameter.
        * @return Return gint32_t.
        * @retval Its value is in LocatorKind.h.
        */
        inline gint32_t const& comm_kind() const noexcept
        {
            return m_commKind;
        }
        
        /**
        * @brief This function gets the value of 'm_isAutoOp' parameter.
        * @return Return true or false.
        * @retval true  It will switch to shm automatically when EDP finds endpoints is in the same host.
        * @retval false Noting.
        */
        inline gbool_t const& is_auto_op() const noexcept
        {
            return m_isAutoOp;
        }
        
        /**
        * @brief This function gets the value of 'm_batchSize' parameter.
        * @return Return guint32_t.
        * @retval It will send 'm_batchSize' changes batchly per Push handle.
        */
        inline guint32_t const& batch_size() const noexcept
        {
            return m_batchSize;
        }
        
        /**
        * @brief This function gets the value of 'm_maxFragSize' parameter.
        * @return Return guint32_t.
        * @retval It's the size of max fragment.
        */
        inline guint32_t const& max_frag_size() const noexcept 
        {
            return m_maxFragSize;
        }
        
        /**
        * @brief This function gets the value of 'm_heartbeatPeriod' parameter.
        * @return Return guint32_t.
        * @retval Protocol tuning parameter that allows the RTPS Writer to repeatedly announce the availability of 
        * data by sending a Heartbeat Message.
        */
        inline guint32_t const& heartbeat_period() const noexcept 
        {
            return m_heartbeatPeriod;
        }
        
        /**
        * @brief This function gets the value of 'm_nackResponseDelay' parameter.
        * @return Return guint32_t.
        * @retval Protocol tuning parameter that allows the RTPS Writer to delay the response to a request for data 
        * from a negative acknowledgment.
        */
        inline guint32_t const& nack_response_delay() const noexcept 
        {
            return m_nackResponseDelay;
        }
        
        /**
        * @brief This function gets the value of 'm_nackSupperRessionDuration' parameter.
        * @return Return guint32_t.
        * @retval Protocol tuning parameter that allows the RTPS Writer to ignore requests for data from negative 
        * acknowledgments that arrive ‘too soon’ after the corresponding change is sent.
        */
        inline guint32_t const& nack_supper_ression_duration() const noexcept 
        {
            return m_nackSupperRessionDuration;
        }
        
        /**
        * @brief This function gets the value of 'm_historyCacheCapacity' parameter.
        * @return Return guint32_t.
        * @retval It's the size of RTPS Writer's historycache.
        */
        inline guint32_t const& history_cache_capacity() const noexcept 
        {
            return m_historyCacheCapacity;
        }
        
        /**
        * @brief This function gets the value of 'm_dataChannelFlowCtlBandWidth' parameter.
        * @return Return guint32_t.
        * @retval It's the band width of the flow control.
        */
        inline guint32_t const& data_channel_flow_ctl_band_width() const noexcept
        {
            return m_dataChannelFlowCtlBandWidth;
        }
        
        /**
        * @brief This function gets the value of 'm_flowCtlThreshold' parameter.
        * @return Return guint32_t.
        * @retval It's the threshold of the flow control.
        */
        inline guint32_t const& flow_ctl_threshold() const noexcept
        {
            return m_flowCtlThreshold;
        }
        
        /**
        * @brief This function gets the value of 'm_hbWithDataPerSeqNum' parameter.
        * @return Return guint32_t.
        * @retval It represents that sending a heartbeat per sending 'm_hbWithDataPerSeqNum' changes.
        */
        inline guint32_t const& hb_with_data_per_seq_num() const noexcept 
        {
            return m_hbWithDataPerSeqNum;
        }
        
        /**
        * @brief This function gets the value of 'm_readerActiveDuration' parameter.
        * @return Return guint32_t.
        * @retval If the writer receives a DataReader's acknack from last received is smaller than 'm_readerActiveDuration',
        * DataReader is active. Otherwhise DataReader is inactive.
        */
        inline guint32_t const& reader_active_duration() const noexcept 
        {
            return m_readerActiveDuration;
        }
        
        /**
        * @brief This function gets the value of 'm_maxShmFragSize' parameter.
        * @return Return guint32_t.
        * @retval It's the size of max fragment in shm.
        */
        inline guint32_t const& max_shm_frag_size() const noexcept
        {
            return m_maxShmFragSize;
        }
        
        /**
        * @brief This function gets the value of 'm_enableZeroCopy' parameter.
        * @return Return true or false.
        * @return true  It enables zero copy.
        * @return false It disables zero copy.
        */
        inline gbool_t const& enable_zero_copy() const noexcept
        {
            return m_enableZeroCopy;
        }
        
        /**
        * @brief This function gets the value of 'm_zeroCopyMemorySize' parameter.
        * @return Return guint32_t.
        * @retval It's the size of memory used for zero copy.
        */
        inline guint32_t const& zero_copy_memory_size() const noexcept
        {
            return m_zeroCopyMemorySize;
        }
        
        /**
        * @brief This function gets the value of 'm_zeroCopyMemorySize' parameter.
        * @return Return true or false.
        * @return true  It enables timestamp message data.
        * @return false It disables timestamp message data.
        */
        inline gbool_t const& enable_ts() const noexcept 
        {
            return m_enableTs;
        }
        
        /**
        * @brief This function gets the value of 'm_enableGroupSend' parameter.
        * @return Return true or false.
        * @retval true  It enables group send.
        * @retval false It disables group send.
        */
        inline gbool_t const& enable_group_send() const noexcept
        {
            return m_enableGroupSend;
        }
        
        /**
        * @brief This function sets the value of 'is_stateful' parameter.
        * @param [in] a_is_stateful Const reference of a gbool_t.
        */
        inline void is_stateful(gbool_t const& a_is_stateful) noexcept
        {
            m_isStateful = a_is_stateful;
        }
        
        /**
        * @brief This function sets the value of 'm_isWithKey' parameter.
        * @param [in] a_is_with_key Const reference of a gbool_t.
        */
        inline void is_with_key(gbool_t const& a_is_with_key) noexcept 
        {
            m_isWithKey = a_is_with_key;
        }
        
        /**
        * @brief This function sets the value of 'm_pushMode' parameter.
        * @param [in] a_push_mode Const reference of a gbool_t.
        */
        inline void push_mode(gbool_t const& a_push_mode) noexcept 
        {
            m_pushMode = a_push_mode;
        }
        
        /**
        * @brief This function sets the value of 'm_isSync' parameter.
        * @param [in] a_is_sync Const reference of a gbool_t.
        */
        inline void is_sync(gbool_t const& a_is_sync) noexcept 
        {
            m_isSync = a_is_sync;
        }
        
        /**
        * @brief This function sets the value of 'm_commKind' parameter.
        * @param [in] a_comm_kind Const reference of a gint32_t.
        */
        inline void comm_kind(gint32_t const& a_comm_kind) noexcept 
        {
            m_commKind = a_comm_kind;
        }
        
        /**
        * @brief This function sets the value of 'm_isAutoOp' parameter.
        * @param [in] a_is_auto_op Const reference of a gbool_t.
        */
        inline void is_auto_op(gbool_t const& a_is_auto_op) noexcept 
        {
            m_isAutoOp = a_is_auto_op;
        }
        
        /**
        * @brief This function sets the value of 'm_batchSize' parameter.
        * @param [in] a_batch_size Const reference of a guint32_t.
        */
        inline void batch_size(guint32_t const& a_batch_size) noexcept 
        {
            m_batchSize = a_batch_size;
        }
        
        /**
        * @brief This function sets the value of 'm_maxFragSize' parameter.
        * @param [in] a_max_frag_size Const reference of a guint32_t.
        */
        inline void max_frag_size(guint32_t const& a_max_frag_size) noexcept 
        {
            m_maxFragSize = a_max_frag_size;
        }
        
        /**
        * @brief This function sets the value of 'm_heartbeatPeriod' parameter.
        * @param [in] a_heartbeat_period Const reference of a guint32_t.
        */
        inline void heartbeat_period(guint32_t const& a_heartbeat_period) noexcept 
        {
            m_heartbeatPeriod = a_heartbeat_period;
        }
        
        /**
        * @brief This function sets the value of 'm_nackResponseDelay' parameter.
        * @param [in] a_nack_response_delay Const reference of a guint32_t.
        */
        inline void nack_response_delay(guint32_t const& a_nack_response_delay) noexcept 
        {
            m_nackResponseDelay = a_nack_response_delay;
        }
        
        /**
        * @brief This function sets the value of 'm_nackSupperRessionDuration' parameter.
        * @param [in] a_nack_supperression_Duration Const reference of a guint32_t.
        */
        inline void nack_supper_ression_duration(guint32_t const& a_nack_supperression_Duration) noexcept 
        {
            m_nackSupperRessionDuration = a_nack_supperression_Duration;
        }
        
        /**
        * @brief This function sets the value of 'm_historyCacheCapacity' parameter.
        * @param [in] a_history_cache_capacity Const reference of a guint32_t.
        */
        inline void history_cache_capacity(guint32_t const& a_history_cache_capacity) noexcept 
        {
            m_historyCacheCapacity = a_history_cache_capacity;
        }
        
        /**
        * @brief This function sets the value of 'm_dataChannelFlowCtlBandWidth' parameter.
        * @param [in] a_datachannel_flowctl_bandWidth Const reference of a guint32_t.
        */
        inline void data_channel_flow_ctl_band_width(guint32_t const& a_datachannel_flowctl_bandWidth) noexcept 
        {
            m_dataChannelFlowCtlBandWidth = a_datachannel_flowctl_bandWidth;
        }
        
        /**
        * @brief This function sets the value of 'm_flowCtlThreshold' parameter.
        * @param [in] a_flowctl_threshold Const reference of a guint32_t.
        */
        inline void flow_ctl_threshold(guint32_t const& a_flowctl_threshold) noexcept 
        {
            m_flowCtlThreshold = a_flowctl_threshold;
        }
        
        /**
        * @brief This function sets the value of 'm_hbWithDataPerSeqNum' parameter.
        * @param [in] a_hb_with_data_per_seqnum Const reference of a guint32_t.
        */
        inline void hb_with_data_per_seq_num(guint32_t const& a_hb_with_data_per_seqnum) noexcept 
        {
            m_hbWithDataPerSeqNum = a_hb_with_data_per_seqnum;
        }
        
        /**
        * @brief This function sets the value of 'm_readerActiveDuration' parameter.
        * @param [in] a_reader_active_duration Const reference of a guint32_t.
        */
        inline void reader_active_duration(guint32_t const& a_reader_active_duration) noexcept 
        {
            m_readerActiveDuration = a_reader_active_duration;
        }
        
        /**
        * @brief This function sets the value of 'm_maxShmFragSize' parameter.
        * @param [in] a_max_shm_frag_size Const reference of a guint32_t.
        */
        inline void max_shm_frag_size(guint32_t const& a_max_shm_frag_size) noexcept 
        {
            m_maxShmFragSize = a_max_shm_frag_size;
        }
        
        /**
        * @brief This function sets the value of 'm_enableZeroCopy' parameter.
        * @param [in] a_enable_zero_copy Const reference of a gbool_t.
        */
        inline void enable_zero_copy(gbool_t const& a_enable_zero_copy) noexcept 
        {
            m_enableZeroCopy = a_enable_zero_copy;
        }
        
        /**
        * @brief This function sets the value of 'm_zeroCopyMemorySize' parameter.
        * @param [in] a_zero_copy_memory_size Const reference of a guint32_t.
        */
        inline void zero_copy_memory_size(guint32_t const& a_zero_copy_memory_size) noexcept 
        {
            m_zeroCopyMemorySize = a_zero_copy_memory_size;
        }
        
        /**
        * @brief This function sets the value of 'm_enableTs' parameter.
        * @param [in] a_enable_ts Const reference of a gbool_t.
        */
        inline void enable_ts(gbool_t const& a_enable_ts) noexcept 
        {
            m_enableTs = a_enable_ts;
        }
        
        /**
        * @brief This function sets the value of 'm_enableGroupSend' parameter.
        * @param [in] a_enable_group_send Const reference of a gbool_t.
        */
        inline void enable_group_send(gbool_t const& a_enable_group_send) noexcept 
        {
            m_enableGroupSend = a_enable_group_send;
        }

        /**
        * @brief Constructor of the class DataWriterAttributes.
        */
        DataWriterAttributes() = default;

    private:
        gbool_t m_isStateful{ true };
        gbool_t m_isWithKey{ false };
        gbool_t m_pushMode{ true };
        gbool_t m_isSync{ false };
        gint32_t m_commKind{ gstone::rtps::LOCATOR_KIND_UDPv4 };
        gbool_t m_isAutoOp{ false };
        guint32_t m_batchSize{ DEFAULT_BATCH_SIZE };
        guint32_t m_maxFragSize{ MAX_UDP_DATA_SIZE };
        guint32_t m_heartbeatPeriod{ DEFAULT_HEARTBEAT_PERIOD };
        guint32_t m_nackResponseDelay{ DEFAULT_NACK_RESPONSE_DELAY };
        guint32_t m_nackSupperRessionDuration{ DEFAULT_NACK_SUPPER_RESSION_DURATION };
        guint32_t m_historyCacheCapacity{ DEFAULT_HISTORY_CACHE_CAPACITY };
        guint32_t m_dataChannelFlowCtlBandWidth{ DEFAULT_DATA_CHANNEL_FLOW_CTL_BAND_WIDTH };
        guint32_t m_flowCtlThreshold{ DEFAULT_FLOW_CTL_THRESHOLD };
        guint32_t m_hbWithDataPerSeqNum{ DEFAULT_HB_WITH_DATA_PER_SEQ_NUM };
        guint32_t m_readerActiveDuration{ DEFAULT_READER_ACTIVE_DURATION };
        guint32_t m_maxShmFragSize{ DEFAULT_MAX_SHM_FRAG_SIZE };
        gbool_t m_enableZeroCopy{ false };
        guint32_t m_zeroCopyMemorySize{ DEFAULT_ZERO_COPY_MEMROY_SIZE };
        gbool_t m_enableTs{ false };
        gbool_t m_enableGroupSend{ false };
    };

    dds::qos::QosPolicyLong_t const DEFAULT_MAX_INSTANCE {10};              ///< Default value of ResourceLimitsQosPolicy's max_instance.
    dds::qos::QosPolicyLong_t const DEFAULT_MAX_SAMPLES {1000};             ///< Default value of ResourceLimitsQosPolicy's max_samples.
    dds::qos::QosPolicyLong_t const DEFAULT_MAX_SAMPLES_PER_INSTANCE {100}; ///< Default value of ResourceLimitsQosPolicy's max_samples_per_instance.
    
    /**
    * @class DataWriterQos
    * @brief This class is a collection of a DataWriter's qos policies.
    */
    class GS_DDS4CPP_API DataWriterQos
    {
    public:
        /**
        * @brief Constructor of the class DataWriterQos.
        */
        DataWriterQos()
        {
            m_durability.kind(dds::qos::DurabilityQosPolicyKind::VOLATILE_DURABILITY_QOS);
            m_reliability.kind(dds::qos::ReliabilityQosPolicyKind::RELIABLE_RELIABILITY_QOS);
            m_destinationOrder.kind(dds::qos::DestinationOrderQosPolicyKind::BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS);
            m_lifeSpan.duration({ 0, 0 });
        }
        
        /**
        * @brief Destructor of the class DataWriterQos.
        */
        virtual ~DataWriterQos() = default;
        
        /**
        * @brief Constructor of the class DataWriterQos by another DataWriterQos object.
        * @param [in] a_info Const reference of a DataWriterQos object.
        */
        DataWriterQos(DataWriterQos const&a_info) = default;
        
        /**
        * @brief Assign a DataWriterQos object to the current DataWriterQos object.
        * @param [in] a_info Const reference of a DataWriterQos object.
        * @return Reference of this DataWriterQos object.
        */
        DataWriterQos& operator=(DataWriterQos const&a_info) = default;
        
        /**
        * @brief Don't use move constructor of the class DataWriterQos.
        * @param [in] a_info Rvalue reference of this DataWriterQos object.
        */
        DataWriterQos(DataWriterQos&&a_info) = default;
        
        /**
        * @brief Don't use move assignment of the class DataWriterQos.
        * @param [in] a_info Rvalue reference of this DataWriterQos object.
        * @return Reference of this DataWriterQos object.
        */
        DataWriterQos& operator=(DataWriterQos&&a_info) = default;

        /**
        * @brief This function gets the value of the DurabilityQosPolicy.
        * @return Return dds::qos::DurabilityQosPolicy.
        */
        inline dds::qos::DurabilityQosPolicy const& durability() const noexcept 
        {
            return m_durability;
        }
        
        /**
        * @brief This function gets the value of the DurabilityServiceQosPolicy.
        * @return Return dds::qos::DurabilityServiceQosPolicy.
        */
        inline dds::qos::DurabilityServiceQosPolicy const& durability_service() const noexcept
        {
            return m_durabilityService;
        }
        
        /**
        * @brief This function gets the value of the DeadlineQosPolicy.
        * @return Return dds::qos::DeadlineQosPolicy.
        */
        inline dds::qos::DeadlineQosPolicy const& deadline() const noexcept 
        {
            return m_deadline;
        }
        
        /**
        * @brief This function gets the value of the LatencyBudgetQosPolicy.
        * @return Return dds::qos::LatencyBudgetQosPolicy.
        */
        inline dds::qos::LatencyBudgetQosPolicy const& latency_budget() const noexcept
        {
            return m_latencyBudget;
        }
        
        /**
        * @brief This function gets the value of the LivelinessQosPolicy.
        * @return Return dds::qos::LivelinessQosPolicy.
        */
        inline dds::qos::LivelinessQosPolicy const& liveliness() const noexcept 
        {
            return m_liveliness;
        }
        
        /**
        * @brief This function gets the value of the ReliabilityQosPolicy.
        * @return Return dds::qos::ReliabilityQosPolicy.
        */
        inline dds::qos::ReliabilityQosPolicy const& reliability() const noexcept 
        {
            return m_reliability;
        }
        
        /**
        * @brief This function gets the value of the DestinationOrderQosPolicy.
        * @return Return dds::qos::DestinationOrderQosPolicy.
        */
        inline dds::qos::DestinationOrderQosPolicy const& destination_order() const noexcept 
        {
            return m_destinationOrder;
        }
        
        /**
        * @brief This function gets the value of the HistoryQosPolicy.
        * @return Return dds::qos::HistoryQosPolicy.
        */
        inline dds::qos::HistoryQosPolicy const& history() const noexcept
        {
            return m_history;
        }
        
        /**
        * @brief This function gets the value of the ResourceLimitsQosPolicy.
        * @return Return dds::qos::ResourceLimitsQosPolicy.
        */
        inline dds::qos::ResourceLimitsQosPolicy const& resource_limits() const noexcept
        {
            return m_resourceLimits;
        }
        
        /**
        * @brief This function gets the value of the TransportPriorityQosPolicy.
        * @return Return dds::qos::TransportPriorityQosPolicy.
        */
        inline dds::qos::TransportPriorityQosPolicy const& transport_priority() const noexcept 
        {
            return m_transportPriority;
        }
        /**
        * @brief This function gets the value of the LifespanQosPolicy.
        * @return Return dds::qos::LifespanQosPolicy.
        */
        
        inline dds::qos::LifespanQosPolicy const& life_span() const noexcept
        {
            return m_lifeSpan;
        }
        
        /**
        * @brief This function gets the value of the UserDataQosPolicy.
        * @return Return dds::qos::UserDataQosPolicy.
        */
        inline dds::qos::UserDataQosPolicy const& user_data() const noexcept
        {
            return m_userData;
        }
        
        /**
        * @brief This function gets the value of the OwnershipQosPolicy.
        * @return Return dds::qos::OwnershipQosPolicy.
        */
        inline dds::qos::OwnershipQosPolicy const& ownership() const noexcept
        {
            return m_ownership;
        }
        
        /**
        * @brief This function gets the value of the OwnershipStrengthQosPolicy.
        * @return Return dds::qos::OwnershipStrengthQosPolicy.
        */
        dds::qos::OwnershipStrengthQosPolicy const& ownership_strength() const noexcept 
        {
            return m_ownershipStrength;
        }
        
        /**
        * @brief This function gets the value of the WriterDataLifecycleQosPolicy.
        * @return Return dds::qos::WriterDataLifecycleQosPolicy.
        */
        inline dds::qos::WriterDataLifecycleQosPolicy const& writer_data_lifecycle() const noexcept
        {
            return m_writerDataLifecycle;
        }
        
        /**
        * @brief This function gets the value of the ThreadScheduleQosPolicy.
        * @return Return dds::qos::ThreadScheduleQosPolicy.
        */
        inline dds::qos::ThreadScheduleQosPolicy const& thread_schedule() const noexcept
        {
            return m_threadSchedule;
        }
        
        /**
        * @brief This function sets the value of the DurabilityQosPolicy.
        * @param [in] a_durability Const reference of a DurabilityQosPolicy object.
        */
        inline void durability(dds::qos::DurabilityQosPolicy const& a_durability) noexcept
        {
            m_durability = a_durability;
        }
        
        /**
        * @brief This function sets the value of the DurabilityServiceQosPolicy.
        * @param [in] a_durability_service Const reference of a DurabilityServiceQosPolicy object.
        */
        inline void durability_service(dds::qos::DurabilityServiceQosPolicy const& a_durability_service) noexcept 
        {
            m_durabilityService = a_durability_service;
        }
        
        /**
        * @brief This function sets the value of the DeadlineQosPolicy.
        * @param [in] a_deadline Const reference of a DeadlineQosPolicy object.
        */
        inline void deadline(dds::qos::DeadlineQosPolicy const& a_deadline) noexcept
        {
            m_deadline = a_deadline;
        }
        
        /**
        * @brief This function sets the value of the LatencyBudgetQosPolicy.
        * @param [in] a_latency_budget Const reference of a LatencyBudgetQosPolicy object.
        */
        inline void latency_budget(dds::qos::LatencyBudgetQosPolicy const& a_latency_budget) noexcept
        {
            m_latencyBudget = a_latency_budget;
        }
        
        /**
        * @brief This function sets the value of the LivelinessQosPolicy.
        * @param [in] a_liveliness Const reference of a LivelinessQosPolicy object.
        */
        inline void liveliness(dds::qos::LivelinessQosPolicy const& a_liveliness) noexcept
        {
            m_liveliness = a_liveliness;
        }
        
        /**
        * @brief This function sets the value of the ReliabilityQosPolicy.
        * @param [in] a_reliability Const reference of a ReliabilityQosPolicy object.
        */
        inline void reliability(dds::qos::ReliabilityQosPolicy const& a_reliability) noexcept
        {
            m_reliability = a_reliability;
        }
        
        /**
        * @brief This function sets the value of the DestinationOrderQosPolicy.
        * @param [in] a_destination_order Const reference of a DestinationOrderQosPolicy object.
        */
        inline void destination_order(dds::qos::DestinationOrderQosPolicy const& a_destination_order) noexcept
        {
            m_destinationOrder = a_destination_order;
        }
        
        /**
        * @brief This function sets the value of the HistoryQosPolicy.
        * @param [in] a_history Const reference of a HistoryQosPolicy object.
        */
        inline void history(dds::qos::HistoryQosPolicy const& a_history) noexcept 
        {
            m_history = a_history;
        }
        
        /**
        * @brief This function sets the value of the ResourceLimitsQosPolicy.
        * @param [in] a_resource_limits Const reference of a ResourceLimitsQosPolicy object.
        */
        inline void resource_limits(dds::qos::ResourceLimitsQosPolicy const& a_resource_limits) noexcept 
        {
            m_resourceLimits = a_resource_limits;
        }
        /**
        * @brief This function sets the value of the TransportPriorityQosPolicy.
        * @param [in] a_transport_priority Const reference of a TransportPriorityQosPolicy object.
        */
        inline void transport_priority(dds::qos::TransportPriorityQosPolicy const& a_transport_priority) noexcept
        {
            m_transportPriority = a_transport_priority;
        }
        
        /**
        * @brief This function sets the value of the LifespanQosPolicy.
        * @param [in] a_life_span Const reference of a LifespanQosPolicy object.
        */
        inline void life_span(dds::qos::LifespanQosPolicy const& a_life_span) noexcept
        {
            m_lifeSpan = a_life_span;
        }
        
        /**
        * @brief This function sets the value of the UserDataQosPolicy.
        * @param [in] a_user_data Const reference of a UserDataQosPolicy object.
        */
        inline void user_data(dds::qos::UserDataQosPolicy const& a_user_data) noexcept
        {
            m_userData = a_user_data;
        }
        
        /**
        * @brief This function sets the value of the OwnershipQosPolicy.
        * @param [in] a_ownership Const reference of a OwnershipQosPolicy object.
        */
        inline void ownership(dds::qos::OwnershipQosPolicy const& a_ownership) noexcept 
        {
            m_ownership = a_ownership;
        }
        
        /**
        * @brief This function sets the value of the OwnershipStrengthQosPolicy.
        * @param [in] a_ownership_strength Const reference of a OwnershipStrengthQosPolicy object.
        */
        inline void ownership_strength(dds::qos::OwnershipStrengthQosPolicy const& a_ownership_strength) noexcept 
        {
            m_ownershipStrength = a_ownership_strength;
        }
        
        /**
        * @brief This function sets the value of the WriterDataLifecycleQosPolicy.
        * @param [in] a_writer_data_lifecycle Const reference of a WriterDataLifecycleQosPolicy object.
        */
        inline void writer_data_lifecycle(dds::qos::WriterDataLifecycleQosPolicy const& a_writer_data_lifecycle) noexcept 
        {
            m_writerDataLifecycle = a_writer_data_lifecycle;
        }
        
        /**
        * @brief This function sets the value of the ThreadScheduleQosPolicy.
        * @param [in] a_thread_schedule Const reference of a ThreadScheduleQosPolicy object.
        */
        inline void thread_schedule(dds::qos::ThreadScheduleQosPolicy const& a_thread_schedule) noexcept 
        {
            m_threadSchedule = a_thread_schedule;
        }

        /**
        * @brief This function gets the value of the DataWriterAttributes.
        * @return Return DataWriterAttributes.
        */
        DataWriterAttributes const& attributes() const noexcept 
        {
            return m_attributes;
        }
        
        /**
        * @brief This function gets the value of the PropertyQosPolicy.
        * @return Return dds::qos::PropertyQosPolicy.
        */
        dds::qos::PropertyQosPolicy const& property() const noexcept 
        {
            return m_property;
        }
        
        /**
        * @brief This function sets the value of the DataWriterAttributes.
        * @param [in] a_attributes Const reference of a DataWriterAttributes object.
        */
        void attributes(DataWriterAttributes const& a_attributes) noexcept 
        {
            m_attributes = a_attributes;
        }
        
        /**
        * @brief This function sets the value of the PropertyQosPolicy.
        * @param [in] a_property Const reference of a PropertyQosPolicy object.
        */
        void property(dds::qos::PropertyQosPolicy const& a_property) noexcept 
        {
            m_property = a_property;
        }

    private:
        dds::qos::DurabilityQosPolicy m_durability{};
        dds::qos::DurabilityServiceQosPolicy m_durabilityService{};
        dds::qos::DeadlineQosPolicy m_deadline{};
        dds::qos::LatencyBudgetQosPolicy m_latencyBudget{};
        dds::qos::LivelinessQosPolicy m_liveliness{};
        dds::qos::ReliabilityQosPolicy m_reliability{};
        dds::qos::DestinationOrderQosPolicy m_destinationOrder{};
        dds::qos::HistoryQosPolicy m_history{};
        dds::qos::ResourceLimitsQosPolicy m_resourceLimits{};
        dds::qos::TransportPriorityQosPolicy m_transportPriority{};
        dds::qos::LifespanQosPolicy m_lifeSpan{};
        dds::qos::UserDataQosPolicy m_userData{};
        dds::qos::OwnershipQosPolicy m_ownership{};
        dds::qos::OwnershipStrengthQosPolicy m_ownershipStrength{};
        dds::qos::WriterDataLifecycleQosPolicy m_writerDataLifecycle{};
        dds::qos::ThreadScheduleQosPolicy m_threadSchedule{};
        DataWriterAttributes m_attributes{};
        dds::qos::PropertyQosPolicy m_property{};
    };
}/*pub*/
}/*dds*/
__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_DATAWRITERQOS_API_H*/
