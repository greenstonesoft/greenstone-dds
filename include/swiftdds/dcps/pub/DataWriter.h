/**************************************************************
* @file DataWriter.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/

#ifndef GSTONE_DATAWRITER_API_H
#define GSTONE_DATAWRITER_API_H 1

#include "swiftdds/dcps/core/Entity.h"
#include "swiftdds/dcps/core/Status.h"
#include "swiftdds/dcps/topic/Topic.h"
#include "swiftdds/dcps/core/ForwardDeclaration.h"
#include "swiftdds/dcps/core/CoreTypes.h"
#include "swiftdds/dcps/pub/DataWriterQos.h"
#include "swiftdds/dcps/topic/SubscriptionBuiltinTopicData.h"

#include "swiftdds/dcps/original/OriginalData.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace pub {
    class DataWriterDelegate;
}/*pub*/
}/*gstone*/

namespace dds
{
namespace pub
{
/**
* @class DataWriter
* @brief This class is the object Allows an application to set the value of the data to be published under a given DDSTopic.
* @details A DataWriter is attached to exactly one Publisher that acts as a factory for it.A DataWriter is bound to exactly 
* one Topic and therefore to exactly one data type. The Topic must exist prior to the DataWriter's creation.
*/
class GS_DDS4CPP_API DataWriter : public dds::core::Entity
{
public:
    /**
    * @brief Don't use the default constructor of the class DataWriter.
    */
    DataWriter() = delete;
    
    /**
    * @brief Constructor of the class DataWriter by another DataWriter object.
    * @param [in] a_delegate Const DataWriterDelegate* object.
    */
    DataWriter(gstone::pub::DataWriterDelegate* const a_delegate) noexcept;
    
    /**
    * @brief Destructor of the class Publisher.
    */
    ~DataWriter() override = default;

    /**
    * @brief This function sets the DataWriter's DataWriterQos.
    * @param [in] a_qos Const reference of a DataWriterQos object.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_OK It is successful to set qos.
    * @retval RETCODE_IMMUTABLE_POLICY If set_qos is invoked after the Entity is enabled and it attempts to 
    * change the value of an "immutable" policy, the operation will fail and it returns IMMUTABLE_POLICY.
    * @retval RETCODE_INCONSISTENT_POLICY The set_qos operation will also fail if it specifies a set of values that 
    * once combined with the existing values would result in an inconsistent set of policies. In this case, the return 
    * value is INCONSISTENT_POLICY.
    */
    DDS::ReturnCode_t set_qos(DataWriterQos const &a_qos);
    
    /**
    * @brief This function retrieves the DataWriter's DataWriterQos.
    * @param [in,out] a_qos Reference of a DataWriterQos object.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_OK It is successful to get qos.
    */
    DDS::ReturnCode_t get_qos(DataWriterQos &a_qos) const;
    
    /**
    * @brief This function informs the Service that the application will be modifying a particular instance.
    * @details This operation should be invoked prior to calling any operation that modifies the instance. 
    * such as write, write_w_timestamp, dispose and dispose_w_timestamp.
    * @param [in] a_data Const pointer of void, that is the pointer of user data for retrieving gstone::rtps::InstanceHandle_t by get_key.
    * @return Return gstone::rtps::InstanceHandle_t.
    * @retval InstanceHandle_t The Instance_handle has been registered and return it.
    * @retval DDS::HANDLE_NIL When it is out of resources limits or other errors, it will return DDS::HANDLE_NIL.
    */
    gstone::rtps::InstanceHandle_t register_instance(void* const a_data);
    
    /**
    * @brief This function is same as register_instance, but its parameter 'source_timestamp' potentially affects the 
    * relative order in which readers observe events from multiple writers.
    * @param [in] a_data Const pointer of void, that is the pointer of user data for retrieving gstone::rtps::InstanceHandle_t by get_key.
    * @return Return gstone::rtps::InstanceHandle_t.
    * @retval InstanceHandle_t The Instance_handle has been registered and return it.
    * @retval DDS::HANDLE_NIL When it is out of resources limits or other errors, it will return DDS::HANDLE_NIL.
    * @todo
    */
    gstone::rtps::InstanceHandle_t register_instance_w_timestamp(void* const a_data, DDS::Time_t const &a_timestamp);
    
    /**
    * @brief This operation reverses the action of register_instance.
    * @param [in] a_data A const pointer used for retrieving gstone::rtps::InstanceHandle_t by get_key.
    * @param [in] a_handle A const InstanceHandle_t used for didentifying the instance.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_OK  It is successful to unregister instance.
    * @retval RETCODE_BAD_PARAMETER If the handle does not correspond to an existing instance the behavior is in general unspecified, 
    * but if detectable by the Service implementation, the operation shall fail and return the error-code BAD_PARAMETER.
    * @retval RETCODE_TIMEOUT When it is out of resources limits, it will return TIMEOUT.
    * @retval RETCODE_PRECONDITION_NOT_MET If the handle corresponds to an existing instance but does not correspond to the same instance 
    * referred by the 'instance' parameter, the behavior is in general unspecified, but if detectable by the Service implementation, 
    * the operation shall fail and return the error-code PRECONDITION_NOT_MET.
    */
    DDS::ReturnCode_t unregister_instance(void* const a_data, gstone::rtps::InstanceHandle_t const a_handle);
    
    /**
    * @brief This operation reverses the action of register_instance_w_timestamp.
    * @param [in] a_data A const pointer used for retrieving gstone::rtps::InstanceHandle_t by get_key.
    * @param [in] a_handle A const InstanceHandle_t used for didentifying the instance.
    * @param [in] a_timestamp A const Time_t used for timestamp.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_OK  It is successful to unregister instance.
    * @retval RETCODE_BAD_PARAMETER If the handle does not correspond to an existing instance the behavior is in general unspecified, 
    * but if detectable by the Service implementation, the operation shall fail and return the error-code BAD_PARAMETER.
    * @retval RETCODE_TIMEOUT When it is out of resources limits, it will return TIMEOUT.
    * @retval RETCODE_PRECONDITION_NOT_MET If the handle corresponds to an existing instance but does not correspond to the same instance 
    * referred by the 'instance' parameter, the behavior is in general unspecified, but if detectable by the Service implementation, 
    * the operation shall fail and return the error-code PRECONDITION_NOT_MET.
    * @todo
    */
    DDS::ReturnCode_t unregister_instance_w_timestamp(void * const a_data, gstone::rtps::InstanceHandle_t const a_handle,
                                                              DDS::Time_t const &a_timestamp) noexcept;
    /**
    * @brief This function can be used to retrieve the instance key that corresponds to an instance_handle.
    * @param [in,out] a_data Pointer of void used for storing key value.
    * @param [in] a_handle InstanceHandle_t used for decoding key value.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_BAD_PARAMETER This function may return BAD_PARAMETER if the InstanceHandle_t a_handle does not correspond 
    * to an existing data object known to the DataWriter.
    * @retval RETCODE_OK It is successful to get key value.
    * @todo
    */
    DDS::ReturnCode_t get_key_value(void * const a_data, gstone::rtps::InstanceHandle_t const &a_handle) noexcept;
    
    /**
    * @brief This function finds registered instance handle by an instance data.
    * @details This operation does not register the instance in question.
    * @param [in] a_data Pointer of an instance data.
    * @return Return InstanceHandle_t or HANDLE_NIL.
    * @retval HANDLE_NIL If the instance has not been previously registered, or if for any other reason the Service is 
    * unable to provide an instance handle, the Service will return the special value HANDLE_NIL.
    */
    gstone::rtps::InstanceHandle_t lookup_instance(void* const a_data);
    
    /**
    * @brief This function This operation modifies the value of a data instance.
    * @param [in] a_data_ptr A pointer of data to write.
    * @param [in] a_handle A const InstanceHandle_t used for didentifying the instance.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_BAD_PARAMETER  If the handle does not correspond to an existing instance the behavior is in general 
    * unspecified, but if detectable by the Service implementation, the operation shall fail and return the error-code BAD_PARAMETER.
    * @retval RETCODE_PRECONDITION_NOT_MET If the handle corresponds to an existing instance but does not correspond to the same 
    * instance referred by the 'data' parameter, the behavior is in general unspecified, but if detectable by the Service 
    * implementation, the operation shall fail and return the error-code PRECONDITION_NOT_MET.
    * @retval RETCODE_TIMEOUT If max_blocking_time elapses before the DataWriter is able to store the modification without exceeding 
    * the limits, the write operation will fail and return TIMEOUT.
    * @retval RETCODE_OUT_OF_RESOURCES The RESOURCE_LIMITS are exceeded and return OUT_OF_RESOURCES.
    * @retval RETCODE_OK  A return value of OK indicates that it successfully writes.
    */
    DDS::ReturnCode_t write(void* const a_data_ptr, gstone::rtps::InstanceHandle_t const a_handle = DDS::HANDLE_NIL);
    
    /**
    * @brief This operation performs the same function as write except that it also provides the value for the source_timestamp 
    * that is made vailable to DataReader objects by means of the source_timestamp attribute inside the SampleInfo.
    * @param [in] a_data A const pointer of data to write.
    * @param [in] a_handle A const InstanceHandle_t used for didentifying the instance.
    * @param [in] a_timestamp A const Time_t used for timestamp.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_BAD_PARAMETER  If the handle does not correspond to an existing instance the behavior is in general 
    * unspecified, but if detectable by the Service implementation, the operation shall fail and return the error-code BAD_PARAMETER.
    * @retval RETCODE_PRECONDITION_NOT_MET If the handle corresponds to an existing instance but does not correspond to the same 
    * instance referred by the 'data' parameter, the behavior is in general unspecified, but if detectable by the Service 
    * implementation, the operation shall fail and return the error-code PRECONDITION_NOT_MET.
    * @retval RETCODE_TIMEOUT If max_blocking_time elapses before the DataWriter is able to store the modification without exceeding 
    * the limits, the write operation will fail and return TIMEOUT.
    * @retval RETCODE_OUT_OF_RESOURCES The RESOURCE_LIMITS are exceeded and return OUT_OF_RESOURCES.
    * @retval RETCODE_OK  A return value of OK indicates that it successfully writes.
    * @todo
    */
    DDS::ReturnCode_t write_w_timestamp(void * const a_data, gstone::rtps::InstanceHandle_t const a_handle, DDS::Time_t const &a_timestamp) noexcept;
    
    /**
    * @brief This operation adds a sample to mLoanPtrVec.
    * @param [in] a_sample A pointer used for a sample data.
    * @param [in] a_size A const guint32_t used for the sample data's size.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_OK   A return value of OK indicates that it successfully adds.
    * @retval RETCODE_BAD_PARAMETER   This operation may return RETCODE_BAD_PARAMETER if 'a_sample' is nullptr.
    * @retval RETCODE_NOT_ENABLED  When writer's entity_factory set false, it will return NOT_ENABLED.
    */
    DDS::ReturnCode_t loan_sample(void *&a_sample, guint32_t const a_size);
    
    /**
    * @brief This operation returns a sample from mLoanPtrVec.
    * @param [in] a_sample A pointer used for retrieving sample data.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_OK   A return value of OK indicates that it successfully retrieves.
    * @retval RETCODE_BAD_PARAMETER   This operation may return RETCODE_BAD_PARAMETER if _sample is nullptr.
    */
    DDS::ReturnCode_t return_loan(void *&a_sample);
    
    /**
    * @brief This operation requests the middleware to delete the data (the actual deletion is postponed 
    * until there is no more use for that data in the whole system).
    * @param [in] a_data A const pointer used for identifying the instance.
    * @param [in] a_handle A const InstanceHandle_t registered by register_instance.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_OK.   A return value of OK indicates that it successfully dispose.
    * @retval RETCODE_OUT_OF_RESOURCES   This operation may return OUT_OF_RESOURCES under the same circumstances described for the write operation.
    * @retval RETCODE_TIMEOUT  When it is out of resources limits, it will return TIMEOUT.
    * @retval RETCODE_BAD_PARAMETER When the parameter is bad and return BAD_PARAMETER.
    * @retval RETCODE_UNSUPPORTED The handle is not registered or other error, it will return UNSUPPORTED.
    */
    DDS::ReturnCode_t dispose(void* const a_data, gstone::rtps::InstanceHandle_t const a_handle = DDS::HANDLE_NIL) noexcept;
    
    /**
    * @brief This operation performs the same functions as dispose except that the application provides the value for 
    * the source_timestamp that is made available to DataReader objects by means of the source_timestamp attribute inside the SampleInfo.
    * @param [in] a_data A const pointer used for identifying the instance.
    * @param [in] a_handle A const InstanceHandle_t registered by register_instance.
    * @param [in] a_timestamp A const Time_t used for timestamp.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_OK.   A return value of OK indicates that it successfully dispose.
    * @retval RETCODE_PRECONDITION_NOT_MET   This operation may return PRECONDITION_NOT_MET under the same circumstances described for the dispose operation.
    * @retval RETCODE_TIMEOUT  When it is out of resources limits, it will return TIMEOUT.
    * @retval RETCODE_BAD_PARAMETER When the parameter is bad and return BAD_PARAMETER.
    * @retval RETCODE_UNSUPPORTED The handle is not registered or other error, it will return UNSUPPORTED.
    * @todo
    */
    DDS::ReturnCode_t dispose_w_timestamp(void * const a_data, gstone::rtps::InstanceHandle_t const a_handle,
                                                  DDS::Time_t const &a_timestamp) noexcept;
    /**
    * @brief This operation is intended to be used only if the DataWriter has RELIABILITY QoS kind set to RELIABLE.
    * @param [in] a_max_wait A const gstone::rtps::Duration_t used for waiting for max time.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_OK A return value of OK indicates that all the samples written have been acknowledged by all 
    * reliable matched data readers
    * @retval RETCODE_TIMEOUT A return value of TIMEOUT indicates that max_wait elapsed before all the data was acknowledged.
    */
    DDS::ReturnCode_t wait_for_acknowledgements(gstone::rtps::Duration_t const a_max_wait) noexcept;
    
    /**
    * @brief This function accesses to the LIVELINESS_LOST communication status.
    * @param [in,out] a_status Reference of LivelinessLostStatus retrieving the LIVELINESS_LOST communication status.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_OK It is successful to get LIVELINESS_LOST communication status.
    */
    DDS::ReturnCode_t get_liveliness_lost_status(dds::core::LivelinessLostStatus &a_status);
    
    /**
    * @brief This function accesses to the OFFERED_DEADLINE_MISSED communication status.
    * @param [in,out] a_status Reference of OfferedDeadlineMissedStatus retrieving the OFFERED_DEADLINE_MISSED communication status.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_OK It is successful to get OFFERED_DEADLINE_MISSED communication status.
    */
    DDS::ReturnCode_t get_offered_deadline_missed_status(
        dds::core::OfferedDeadlineMissedStatus &a_status);
    
    /**
    * @brief This function accesses to the OFFERED_INCOMPATIBLE_QOS communication status.
    * @param [in,out] a_status Reference of OfferedIncompatibleQosStatus retrieving the OFFERED_INCOMPATIBLE_QOS communication status.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_OK It is successful to get OFFERED_INCOMPATIBLE_QOS communication status.
    */
    DDS::ReturnCode_t get_offered_incompatible_qos_status(
        dds::core::OfferedIncompatibleQosStatus &a_status);
    
    /**
    * @brief This function accesses to the PUBLICATION_MATCHED communication status.
    * @param [in,out] a_status Reference of PublicationMatchedStatus retrieving the PUBLICATION_MATCHED communication status.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_OK It is successful to get PUBLICATION_MATCHED communication status.
    */
    DDS::ReturnCode_t get_publication_matched_status(dds::core::PublicationMatchedStatus &a_status);
    
    /**
    * @brief This function returns the Topic associated with the DataWriter.
    * @return Return Topic* or nullptr.
    */
    dds::topic::Topic* const get_topic() const noexcept;
    
    /**
    * @brief This function  returns the Publisher to which the DataWriter belongs.
    * @return Return a pointer of Publisher or nullptr.
    */
    dds::pub::Publisher* const get_publisher() const noexcept;
    
    /**
    * @brief This function manually asserts the liveliness of the DataWriter.
    * @details This is used in combination with the LIVELINESS QoS policy to indicate to the Service that the entity remains active. \n
    * This operation need only be used if the LIVELINESS setting is either MANUAL_BY_PARTICIPANT or MANUAL_BY_TOPIC. Otherwise, it has no effect.
    * @return Return DDS::ReturnCode_t
    * @retval RETCODE_NOT_ENABLED  When writer's entity_factory set false, it will return NOT_ENABLED.
    * @retval RETCODE_OK It is successful to assert liveliness.
    */
    DDS::ReturnCode_t assert_liveliness() noexcept;
    
    /**
    * @brief This function retrieves information on a subscription that is currently "associated" with the DataWriter.
    * @details The subscription that has a matching Topic and compatible QoS that the application has not indicated 
    * should be "ignored" by means of the DomainParticipant ignore_subscription operation.
    * @param [in,out] a_data Reference of HandleSeq used for retrieving a subscription's information.
    * @param [in] a_handle A const InstanceHandle_t used for specifing a subscription.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_OK It is successful to get matched subscription data.
    * @retval RETCODE_BAD_PARAMETER When the parameter is bad and return BAD_PARAMETER.
    * @retval RETCODE_UNSUPPORTED  The operation may also fail if the infrastructure does not hold the information necessary 
    * to fill in the subscription_data. In this case the operation will return UNSUPPORTED.
    */
    DDS::ReturnCode_t get_matched_subscription_data(dds::topic::SubscriptionBuiltinTopicData &a_data,
                                                            gstone::rtps::InstanceHandle_t const a_handle);
    
    /**
    * @brief This function retrieves the list of subscriptions currently "associated" with the DataWriter.
    * @details Subscriptions that have a matching Topic and compatible QoS that the application has not indicated 
    * should be "ignored" by means of the DomainParticipant ignore_subscription operation.
    * @param [in,out] handles Reference of HandleSeq used for retrieving the list of subscriptions.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_OK It is successful to get matched subscriptions.
    */
    DDS::ReturnCode_t get_matched_subscriptions(dds::core::HandleSeq &handles);
    
    /**
    * @brief This function returns the count of the readers which are matched.
    * @return The count of the readers.
    */
    guint32_t get_matched_subscriptions_count() const noexcept;

    /**
    * @brief This function gets statistic information about losting packets of data has the key 
    * same as the parameter 'handle' because of ResourceQos and HistoryQos.
    * @param [in] a_handle Const reference of InstanceHandle_t used for specifing a DataWriter.
    * @param [in,out] a_info Reference of WriterLostPacketStatisticInfo used for retrieving statistic information.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_NOT_ENABLED When the writer's entity_factory is false, it will return NOT_ENABLED.
    * @retval RETCODE_OK It is successful to get lost packet statistic.
    */
    DDS::ReturnCode_t get_lost_packet_statistic(gstone::rtps::InstanceHandle_t const &a_handle,
                                                        dds::core::WriterLostPacketStatisticInfo &a_info) noexcept;
    
    /**
    * @brief This function gets statistic information about losting packets of all data wrote by this DataWriter 
    * because of ResourceQos and HistoryQos.
    * @param [in,out] a_info Reference of WriterLostPacketStatisticInfo used for retrieving statistic information.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_NOT_ENABLED When the writer's entity_factory is false, it will return NOT_ENABLED.
    * @retval RETCODE_OK It is successful to get lost packet statistic.
    */
    DDS::ReturnCode_t get_lost_packet_statistic(dds::core::WriterLostPacketStatisticInfo &a_info) noexcept;
    
    /**
    * @brief This function installs this DataWriter's Listener and communication status mask.
    * @param [in] a_listener A pointer of Listener used for assigning to the DataWriter's Listener.
    * @param [in] a_mask Communication status mask used for assigning to the DataWriter's status mask.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_BAD_PARAMETER If 'a_listener' is nullptr or this DataWrite's listener is nullptr, it will
    * return RETCODE_BAD_PARAMETER.
    * @retval RETCODE_OK  It is successful to set listener.
    */
    DDS::ReturnCode_t set_listener(dds::core::Listener* a_listener, DDS::StatusMask a_mask) noexcept override;
    
    /**
    * @brief This function accesses to the existing Listener attached to the DataWriter.
    * @return Return a pointer of Listener, is the locally DataWriter's Listener.
    */
    dds::core::Listener* get_listener() noexcept override;
    
    /**
    * @brief This function accesses to the existing StatusCondition attached to the DataWriter.
    * @return Return StatusCondition*.
    */
    dds::core::StatusCondition* get_statuscondition() noexcept override;
    
    /**
    * @brief This function retrieves the communication statuses mask in the DataWriter that are 'triggered'.
    * @details The statuses mask whose value has changed since the last time the application read the status.
    * @return Return communication statuses mask.
    */
    DDS::StatusMask get_status_changes() noexcept override;
    
    /**
    * @brief This function enables the DataWriter.
    * @details It's useful when setting the value of the ENTITY_FACTORY Qos policy.
    * @return Return DDS::ReturnCode_t.
    * @retval RETCODE_PRECONDITION_NOT_MET   Calling enable on an Entity whose factory is not enabled will fail and return PRECONDITION_NOT_MET.
    * @retval RETCODE_OK   It is successful to enable DataWriter.
    */
    DDS::ReturnCode_t enable() noexcept override;
    
    /**
    * @brief This function returns the InstanceHandle_t that represents the DataWriter.
    * @return Return InstanceHandle_t.
    */
    gstone::rtps::InstanceHandle_t get_instance_handle() noexcept override;

#ifdef ENABLE_HIBERNATE
    /**
     * @brief This function hibernates this DataWriter and makes it become offline. 
     * @return Return true.
     */ 
    gbool_t hibernate();
    /**
     * @brief This function enables this DataWriter. 
     * @return gbool_t
     * @retval true  If this DataWriter's rtps writer is not nullptr, it returns true. 
     * @retval false If this DataWriter's rtps writer is nullptr, it returns false.
     */ 
    gbool_t wakeup();
#endif

// operation for writing buffer directly
    DDS::ReturnCode_t write_f_buffer(
        std::shared_ptr<gstone::rtps::SerializedPayload_t> const payload, 
        gstone::rtps::InstanceHandle_t &handle);

    DDS::ReturnCode_t register_instance_f_buffer(
        gstone::rtps::InstanceHandle_t const &handle);

    DDS::ReturnCode_t unregister_instance_f_buffer(
        gstone::rtps::InstanceHandle_t &handle);
    
    DDS::ReturnCode_t dispose_f_buffer(
        gstone::rtps::InstanceHandle_t &handle);

    DDS::ReturnCode_t write_original(DDS::OriginalData data, gstone::rtps::InstanceHandle_t handle);

    DDS::ReturnCode_t write_original_w_timestamp(DDS::OriginalData data, gstone::rtps::InstanceHandle_t handle, DDS::Time_t const &a_timestamp);

protected:
    /**
    * @brief Constructor of the class DataWriter by another DataWriter object.
    * @param [in] a_info Const reference of a DataWriter object.
    */
    DataWriter(DataWriter const&a_info) = default;
    
    /**
    * @brief Assign a DataWriter object to the locally DataWriter object.
    * @param [in] a_info Const reference of a DataWriter object.
    * @return Reference of the DataWriter object.
    */
    DataWriter& operator=(DataWriter const&a_info) = default;
    
    /**
    * @brief Move constructor of the class DataWriter.
    * @param [in] a_info Rvalue reference of a DataWriter object.
    */
    DataWriter(DataWriter&&a_info) = default;
    
    /**
    * @brief Move assignment of the class DataWriter.
    * @param [in] a_info Rvalue reference of a DataWriter object.
    * @return Reference of the DataWriter object.
    */
    DataWriter& operator=(DataWriter&&a_info) = default;

private:
    gstone::pub::DataWriterDelegate* m_delegate;
};
}/*pub*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_DATAWRITER_API_H*/
