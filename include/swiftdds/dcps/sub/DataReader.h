/**************************************************************
* @file DataReader.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_DATAREADER_API_H
#define GSTONE_DATAREADER_API_H 1

#include "swiftdds/dcps/core/Entity.h"
#include "swiftdds/dcps/core/Status.h"
#include "swiftdds/dcps/sub/DataReaderListener.h"
#include "swiftdds/dcps/core/ForwardDeclaration.h"
#include "swiftdds/dcps/core/StatusCondition.h"
#include "swiftdds/dcps/core/ReadCondition.h"
#include "swiftdds/dcps/core/QueryCondition.h"
#include "swiftdds/dcps/core/CoreTypes.h"
#include "swiftdds/dcps/topic/TopicDescription.h"
#include "swiftdds/dcps/sub/DataReaderQos.h"

#include "swiftdds/dcps/topic/PublicationBuiltinTopicData.h"
#include "swiftdds/dcps/sub/LoanableTypeData.h"
#include "swiftdds/dcps/sub/SamplesCollectionBase.h"
#include "swiftdds/dcps/original/OriginalData.h"
#include <mutex>

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace sub {
    class DataReaderDelegate;
} /* sub */
} /* gstone */

namespace dds
{
namespace sub
{
    /**
     * @class DataReader
     * @brief A DataReader allows the application to declare the data it wishes to receive (i.e., make a subscription) and
     * to access the data received by the attached Subscriber.
     */
    class GS_DDS4CPP_API DataReader : public dds::core::Entity
    {
    public:
        /**
         * @brief Construct a new Data Reader object
         * @param [in] reader_delegate reader delegate
         */
        DataReader(gstone::sub::DataReaderDelegate* const reader_delegate) noexcept;
        
        /**
         * @brief Destroy the Data Reader object
         */
        ~DataReader() override = default;

        //data operation information for applicaton
        /**
         * @brief Get the unread cache count object
         * @return unread cache count
         */
        guint64_t const get_unread_cache_count() noexcept;
        
        /**
         * @brief Get the untaken cache count object
         * @return untaken cache count
         */
        guint64_t const get_untaken_cache_count() noexcept;
        
        /**
         * @brief Set the qos object
         * @param [in] in_qos reader's qos
         * @return Return Code
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         */
        DDS::ReturnCode_t set_qos(DataReaderQos const& in_qos) noexcept;
        
        /**
         * @brief Get the qos object
         * @param [in,out] out_qos reader's qos
         * @return Return Code
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         */
        DDS::ReturnCode_t get_qos(DataReaderQos& out_qos) const noexcept;
        
        /**
         * @brief This operation accesses a collection of Data values from the DataReader.
         * @param [in,out] data_value pointer of message data
         * @param [in,out] sample_info vector of SampleInfo
         * @param [in] max_samples read size
         * @param [in] sample_state Sample State Mask
         * @param [in] view_state View State Mask
         * @param [in] instance_state Instance State Mask
         * @return Return Code
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_NOT_ENABLED reader is unenable
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER parameters are illegal.
         */
        DDS::ReturnCode_t read(
            dds::sub::SamplesCollectionBase& data_values,
            dds::core::SampleInfoSeq &sample_info,
            gint32_t const max_samples = 1,
            DDS::SampleStateMask const sample_state = DDS::ANY_SAMPLE_STATE,
            DDS::ViewStateMask const view_state = DDS::ANY_VIEW_STATE,
            DDS::InstanceStateMask const instance_state = DDS::ANY_INSTANCE_STATE) noexcept;

        /**
         * @brief This operation accesses a collection of data-samples from the DataReader and a
         * corresponding collection of SampleInfo structures
         * @param [in,out] data_values The received data
         * @param [in,out] sample_infos The list of Sample Info
         * @param [in] max_samples The size of taking
         * @param [in] sample_state Sample State Mask
         * @param [in] view_state View State Mask
         * @param [in] instance_state Instance State Mask
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_NOT_ENABLED reader is unenable
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER parameters are illegal.
         */
        DDS::ReturnCode_t take(
            dds::sub::SamplesCollectionBase  &data_values,
            dds::core::SampleInfoSeq  &sample_infos,
            guint64_t const max_samples = static_cast<guint64_t>(UINT64_MAX),
            DDS::SampleStateMask const sample_state = DDS::ANY_SAMPLE_STATE,
            DDS::ViewStateMask const view_state = DDS::ANY_VIEW_STATE,
            DDS::InstanceStateMask const instance_state = DDS::ANY_INSTANCE_STATE) noexcept;
        
        /**
         * @brief This operation accesses via 'read' the samples that match the criteria specified in the ReadCondition.
         * @param [in,out] data_value The received data
         * @param [in,out] sample_info The list of Sample Info
         * @param [in] max_samples The size of taking
         * @param [in] a_condition The ReadCondition
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER parameters are illegal.
         */
        DDS::ReturnCode_t read_w_condition(
            dds::sub::SamplesCollectionBase &data_values,
            dds::core::SampleInfoSeq &sample_info,
            gint32_t const max_samples,
            dds::core::ReadCondition const * const a_condition) noexcept;
        
        /**
         * @brief This operation is analogous to read_w_condition except it accesses samples via the 'take' operation.
         * @param [in,out] data_value The received data
         * @param [in,out] sample_info The list of Sample Info
         * @param [in] max_samples The size of taking
         * @param [in] a_condition The ReadCondition
         * @return DDS::ReturnCode_t 
         * @retval return value description
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER parameters are illegal.
         */
        DDS::ReturnCode_t take_w_condition(
            dds::sub::SamplesCollectionBase &data_values,
            dds::core::SampleInfoSeq &sample_info,
            gint32_t const max_samples,
            dds::core::ReadCondition const * const a_condition) noexcept;
        
        /**
         * @brief This operation copies the next, non-previously accessed Data value from the DataReader;
         * the operation also copies the corresponding SampleInfo. 
         * @param [in,out] data_value The received data
         * @param [in,out] sample_info The Sample Info
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER parameters are illegal.
         */
        DDS::ReturnCode_t read_next_sample(void* const data_value, dds::core::SampleInfo& sample_info) noexcept;
        
        /**
         * @brief This operation copies the next, non-previously accessed Data value from the DataReader
         * and 'removes' it from the DataReader so it is no longer accessible.
         * @param [in,out] data_value The received data
         * @param [in,out] sample_info The Sample Info
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER parameters are illegal.
         */
        DDS::ReturnCode_t take_next_sample(void* const data_value, dds::core::SampleInfo& sample_info) noexcept;

        /**
         * @brief This operation copies the next, non-previously accessed Data value from the DataReader.
         * @param [in,out] data_value The received data
         * @param [in,out] sample_info The Sample Info
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER parameters are illegal.
         */
        DDS::ReturnCode_t read_next_sample(dds::sub::LoanableData& data_value, dds::core::SampleInfo& sample_info) noexcept;

        DDS::ReturnCode_t take_next_sample_original(DDS::OriginalData &data, dds::core::SampleInfo& sample_info) noexcept;

        /**
         * @brief This operation copies the next, non-previously accessed Data value from the DataReader
         * and 'removes' it from the DataReader so it is no longer accessible.
         * @param [in,out] data_value The received data
         * @param [in,out] sample_info The Sample Info
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER parameters are illegal.
         */
        DDS::ReturnCode_t take_next_sample(dds::sub::LoanableData& data_value, dds::core::SampleInfo& sample_info) noexcept;
        
        /**
         * @brief This operation accesses a collection of Data values from the DataReader. 
         * @param [in,out] data_value The received data
         * @param [in,out] sample_info The list of Sample Info
         * @param [in] max_samples The size of taking
         * @param [in] handle The handle of instance
         * @param [in] sample_state The Sample State Mask
         * @param [in] view_state The View State Mask
         * @param [in] instance_state The Instance State Mask
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER parameters are illegal.
         */
        DDS::ReturnCode_t read_instance(
            dds::sub::SamplesCollectionBase &data_values,
            dds::core::SampleInfoSeq &sample_info,
            gint32_t const max_samples = 1,
            gstone::rtps::InstanceHandle_t const handle = DDS::HANDLE_NIL,
            DDS::SampleStateMask const sample_state = DDS::ANY_SAMPLE_STATE,
            DDS::ViewStateMask const view_state = DDS::ANY_VIEW_STATE,
            DDS::InstanceStateMask const instance_state = DDS::ANY_INSTANCE_STATE) noexcept;
        
        /**
         * @brief This operation accesses a collection of Data values from the DataReader.
         * @param [in,out] data_value The received data
         * @param [in,out] sample_info The list of Sample Info
         * @param [in] max_samples The size of taking
         * @param [in] handle The handle of instance
         * @param [in] sample_state The Sample State Mask
         * @param [in] view_state The View State Mask
         * @param [in] instance_state The Instance State Mask
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER parameters are illegal.
         */
        DDS::ReturnCode_t take_instance(
            dds::sub::SamplesCollectionBase& data_values,
            dds::core::SampleInfoSeq &sample_info,
            gint32_t const max_samples = 1,
            gstone::rtps::InstanceHandle_t const handle = DDS::HANDLE_NIL,
            DDS::SampleStateMask const sample_state = DDS::ANY_SAMPLE_STATE,
            DDS::ViewStateMask const view_state = DDS::ANY_VIEW_STATE,
            DDS::InstanceStateMask const instance_state = DDS::ANY_INSTANCE_STATE) noexcept;
        
        /**
         * @brief This operation accesses a collection of Data values from the DataReader where all
         * the samples belong to a single instance.
         * @param [in,out] data_value The received data
         * @param [in,out] sample_info The list of Sample Info
         * @param [in] max_samples The size of taking
         * @param [in] previous_handle The last read handle of instance
         * @param [in] sample_state The Sample State Mask
         * @param [in] view_state The View State Mask
         * @param [in] instance_state The Instance State Mask
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER parameters are illegal.
         */
        DDS::ReturnCode_t read_next_instance(
            dds::sub::SamplesCollectionBase& data_values,
            dds::core::SampleInfoSeq &sample_info,
            gint32_t const max_samples = 1,
            gstone::rtps::InstanceHandle_t const previous_handle = DDS::HANDLE_NIL,
            DDS::SampleStateMask const sample_state = DDS::ANY_SAMPLE_STATE,
            DDS::ViewStateMask const view_state = DDS::ANY_VIEW_STATE,
            DDS::InstanceStateMask const instance_state = DDS::ANY_INSTANCE_STATE) noexcept;
        
        /**
         * @brief This operation accesses a collection of Data values from the DataReader
         * and 'removes' them from the DataReader.
         * @param [in,out] data_value The received data
         * @param [in,out] sample_info The list of Sample Info
         * @param [in] max_samples The size of taking
         * @param [in] previous_handle The last read handle
         * @param [in] sample_state The Sample State Mask
         * @param [in] view_state The View State Mask
         * @param [in] instance_state The Instance State Mask
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER parameters are illegal.
         */
        DDS::ReturnCode_t take_next_instance(
            dds::sub::SamplesCollectionBase& data_values,
            dds::core::SampleInfoSeq &sample_info,
            gint32_t const max_samples = 1,
            gstone::rtps::InstanceHandle_t const previous_handle = DDS::HANDLE_NIL,
            DDS::SampleStateMask const sample_state = DDS::ANY_SAMPLE_STATE,
            DDS::ViewStateMask const view_state = DDS::ANY_VIEW_STATE,
            DDS::InstanceStateMask const instance_state = DDS::ANY_INSTANCE_STATE) noexcept;
        
        /**
         * @brief This operation accesses a collection of Data values from the DataReader. 
         * @param [in,out] data_value The received data
         * @param [in,out] sample_info The list of Sample Info
         * @param [in] max_samples The size of taking
         * @param [in] previous_handle The last read handle
         * @param [in] a_condition The ReadCondition
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER parameters are illegal.
         */
        DDS::ReturnCode_t read_next_instance_w_condition(
            dds::sub::SamplesCollectionBase& data_values,
            dds::core::SampleInfoSeq &sample_info,
            gint32_t const max_samples,
            gstone::rtps::InstanceHandle_t const previous_handle,
            dds::core::ReadCondition const* const a_condition) noexcept;
        
        /**
         * @brief This operation accesses a collection of Data values from the DataReader
         * and 'removes' them from the DataReader.
         * @param [in,out] data_value The received data
         * @param [in,out] sample_info The list of Sample Info
         * @param [in] max_samples The size of taking
         * @param [in] previous_handle The last read handle
         * @param [in] a_condition The ReadCondition
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER parameters are illegal.
         */
        DDS::ReturnCode_t take_next_instance_w_condition(
            dds::sub::SamplesCollectionBase& data_values,
            dds::core::SampleInfoSeq &sample_info,
            gint32_t const max_samples,
            gstone::rtps::InstanceHandle_t const previous_handle,
            dds::core::ReadCondition const* const a_condition) noexcept;
        
        /**
         * @brief This operation indicates to the DataReader that the application is done accessing the 
         * collection of data_values and sample_infos obtained by some earlier invocation of read or take on the DataReader.
         * @param [in,out] data_value The buffer of data
         * @param [in,out] sample_info The Sample Info
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong.
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER parameter is illegal.
         * @retval DDS::ReturnCode_t::RETCODE_NOT_ENABLED reader is unenable.
         */
        DDS::ReturnCode_t return_loan(dds::sub::LoanableData &data_value, dds::core::SampleInfo const &sample_info) const noexcept;
        
        /**
         * @brief This operation indicates to the DataReader that the application is done accessing the collection of
         * data_values and sample_infos obtained by some earlier invocation of read or take on the DataReader.
         * @param [in,out] data_values The buffer of data
         * @param [in,out] sample_infos The list of Sample Info
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong.
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER parameter is illegal.
         * @retval DDS::ReturnCode_t::RETCODE_NOT_ENABLED reader is unenable.
         */
        DDS::ReturnCode_t return_loan(dds::sub::SamplesCollectionBase& data_values,
            dds::core::SampleInfoSeq& sample_infos) const noexcept;
        
        /**
         * @brief This operation can be used to retrieve the instance key that corresponds to an instance_handle. 
         * @param [in,out] key_holder The instance key
         * @param [in] handle The instance handle
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong.
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER parameter is illegal.
         */
        DDS::ReturnCode_t get_key_value(void* const key_holder, gstone::rtps::InstanceHandle_t const handle) const  noexcept;
        
        /**
         * @brief This operation takes as a parameter an instance and returns a handle that can be used in
         * subsequent operations that accept an instance handle as an argument. 
         * @param [in,out] instance The data of an instance
         * @return gstone::rtps::InstanceHandle_t 
         */
        gstone::rtps::InstanceHandle_t lookup_instance(void* const instance) const noexcept;
        
        /**
         * @brief This operation creates a ReadCondition. The returned ReadCondition will be attached and belong to the DataReader.
         * @param [in] sample_states The SampleState Mask
         * @param [in] view_states The View State Mask
         * @param [in] instance_states The Instance State Mask
         * @return dds::core::ReadCondition* The pointer of ReadCondition
         */
        dds::core::ReadCondition* create_readcondition(DDS::SampleStateMask const sample_states,
            DDS::ViewStateMask const view_states,
            DDS::InstanceStateMask const instance_states) noexcept;
        
        /**
         * @brief This operation deletes a ReadCondition attached to the DataReader. 
         * @param [in] condition The condition is needed to be deleted.
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong.
         * @retval DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET condition is illegal.
         */
        DDS::ReturnCode_t delete_readcondition(dds::core::ReadCondition* const condition) noexcept;
        
        /**
         * @brief This operation creates a QueryCondition.
         * @param [in] sample_states The Sample State Mask
         * @param [in] view_states The View State Mask
         * @param [in] instance_state The Instance State Mask
         * @param [in] query_expression The expression of sql
         * @param [in] query_parameter The parameter of sql
         * @return dds::core::QueryCondition* 
         */
        dds::core::QueryCondition* create_querycondition(DDS::SampleStateMask const sample_states,
            DDS::ViewStateMask const view_states,
            DDS::InstanceStateMask const instance_state,
            std::string const &query_expression,
            dds::core::StringSeq const &query_parameter) const noexcept;
        
        /**
         * @brief This operation allows access to the SAMPLE_LOST communication status.
         * @param [in,out] status The Sample Lost Status
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong.
         */
        DDS::ReturnCode_t get_sample_lost_status(dds::core::SampleLostStatus& status) noexcept;
        
        /**
         * @brief This operation allows access to the SAMPLE_REJECTED communication status.
         * @param [in,out] status The Sample Rejected Status
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong.
         */
        DDS::ReturnCode_t get_sample_rejected_status(dds::core::SampleRejectedStatus& status) noexcept;
        
        /**
         * @brief This operation allows access to the LIVELINESS_CHANGED communication status.
         * @param [in,out] status The Liveliness Changed Status
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong.
         */
        DDS::ReturnCode_t get_liveliness_changed_status(dds::core::LivelinessChangedStatus& status) noexcept;
        
        /**
         * @brief This operation allows access to the REQUESTED_DEADLINE_MISSED communication status. 
         * @param [in,out] status The Requested Deadline Missed Status
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong.
         */
        DDS::ReturnCode_t get_requested_deadline_missed_status(dds::core::RequestedDeadlineMissedStatus& status) noexcept;
        
        /**
         * @brief This operation allows access to the REQUESTED_INCOMPATIBLE_QOS communication status.
         * @param [in,out] status The Requested Incompatible Qos Status
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong.
         */
        DDS::ReturnCode_t get_requested_incompatible_qos_status(dds::core::RequestedIncompatibleQosStatus& status) noexcept;
        
        /**
         * @brief This operation allows access to the SUBSCRIPTION_MATCHED communication status. 
         * @param [in,out] status The Subscription Matched Status
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong.
         */
        DDS::ReturnCode_t get_subscription_matched_status(dds::core::SubscriptionMatchedStatus& status) noexcept;
        
        /**
         * @brief This operation returns the TopicDescription associated with the DataReader. 
         * @return dds::topic::TopicDescription* const 
         */
        dds::topic::TopicDescription* const get_topicdescription() const noexcept;
        
        /**
         * @brief This operation returns the Subscriber to which the DataReader belongs.
         * @return dds::sub::Subscriber* const 
         */
        dds::sub::Subscriber* const get_subscriber() const noexcept;
        
        /**
         * @brief This operation deletes all the entities that were created by means of the "create" operations on the DataReader.
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong.
         * @retval DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET reader's condition isn't empty.
         */
        DDS::ReturnCode_t delete_contained_entities() noexcept;
        
        /**
         * @brief This operation is intended only for DataReader entities that have a non-VOLATILE PERSISTENCE QoS kind.
         * @param [in] max_wait The duration of the waiting time.
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong.
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER max_wait < 1.
         */
        DDS::ReturnCode_t wait_for_historical_data(gstone::rtps::Duration_t const max_wait) const noexcept;
        
        /**
         * @brief This operation retrieves information on a publication that is currently "associated" with
         * the DataReader; that is, a publication with a matching Topic and compatible QoS that the application
         * has not indicated should be "ignored" by means of theDomainParticipant ignore_publication operation.
         * @param [in,out] data_value the result of PublicationBuiltinTopicData
         * @param [in] handle the handle of matched publication
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong.
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER handle can't be found.
         */
        DDS::ReturnCode_t get_matched_publication_data(dds::topic::PublicationBuiltinTopicData& data_value, gstone::rtps::InstanceHandle_t const handle) noexcept;
        
        /**
         * @brief This operation retrieves the list of publications currently "associated" with the DataReader;
         * that is, publications that have a matching Topic and compatible QoS that the application has not indicated
         * should be "ignored" by means of the DomainParticipant ignore_ publication operation.
         * @param [in,out] hanldes matched publications' handles
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK reader is enable.
         */
        DDS::ReturnCode_t get_matched_publications(dds::core::HandleSeq& hanldes) noexcept;
        // DDS::ReturnCode_t get_lost_packet_statistic(gstone::rtps::InstanceHandle_t const& handle, dds::core::ReaderLostPacketStatisticInfo& info) const noexcept;
        
        /**
         * @brief Get the lost packet statistic
         * @param [in,out] info the lost packet statistic
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK reader is enable.
         * @retval DDS::ReturnCode_t::RETCODE_NOT_ENABLED reader is unenable.
         * @retval DDS::ReturnCode_t::RETCODE_UNSUPPORTED reader is unsupported.
         */
        DDS::ReturnCode_t get_lost_packet_statistic(dds::core::ReaderLostPacketStatisticInfo& info) noexcept;
        
        /**
         * @brief By virtue of extending Entity, a DataReader can be attached to a Listener
         * at creation time or later by using the set_listener operation. The Listener attached must extend DataReaderListener.
         * @param [in] listener the attached DataReaderListener
         * @param [in] mask the attached StatusMask
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK reader is enable.
         * @retval DDS::ReturnCode_t::RETCODE_ERROR reader is unenable.
         */
        DDS::ReturnCode_t set_listener(dds::core::Listener * listener, DDS::StatusMask mask) noexcept override;
        
        /**
         * @brief Allows access to the attached DataReaderListener.
         * @return dds::core::Listener* 
         */
        dds::core::Listener* get_listener() noexcept override;
        
        /**
         * @brief This operation allows access to the StatusCondition associated with the Entity.
         * @return dds::core::StatusCondition* 
         */
        dds::core::StatusCondition* get_statuscondition() noexcept override;
        
        /**
         * @brief This operation retrieves the list of communication statuses in the Entity that are 'triggered.'
         * That is, the list of statuses whose value has changed since the last time the application read the status. 
         * @return DDS::StatusMask 
         */
        DDS::StatusMask get_status_changes() noexcept override;
        
        /**
         * @brief This operation enables the Entity. Entity objects can be created either enabled or disabled. 
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK reader is enable.
         * @retval DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET sub is unenable.
         * @retval DDS::ReturnCode_t::RETCODE_ERROR can't create rtps reader.
         */
        DDS::ReturnCode_t enable() noexcept override;
        
        /**
         * @brief This operation returns the InstanceHandle_t that represents the Entity.
         * @return gstone::rtps::InstanceHandle_t 
         */
        gstone::rtps::InstanceHandle_t get_instance_handle() noexcept override;

#ifdef ENABLE_HIBERNATE
        /**
         * @brief start hibernate
         * @return gbool_t 
         */
        gbool_t hibernate();
        /**
         * @brief stop hibernate
         * @return gbool_t 
         */
        gbool_t wakeup();
#endif
    protected:
        /**
         * @brief This function is deleted.
         */
        DataReader() = delete;
        
        /**
         * @brief Copy-Construct a new Data Reader object
         * @param [in] other. reference of a DataReader object.
         */
        DataReader(DataReader const& other) = default;
        
        /**
         * @brief Move-Construct a new Data Reader object
         * @param [in] other. reference of a DataReader object.
         */
        DataReader(DataReader&& other) = default;
        
        /**
         * @brief Assign a DataReader object to the locally DataReader object.
         * @param [in] other. reference of a DataReader object.
         * @return Reference of the locally DataReader object.
         */
        DataReader& operator=(DataReader const& other) = default;
        
        /**
         * @brief Move a DataReader object to the locally DataReader object.
         * @param [in] other. reference of a DataReader object.
         * @return Reference of the locally DataReader object.
         */
        DataReader& operator=(DataReader&& other) = default;

    private:
        gstone::sub::DataReaderDelegate* m_delegate;
    };

    using DataReaderSeq = std::vector<DataReader*>;
} /* sub */
} /* dds */

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_DATAREADER_API_H*/
