/**************************************************************
* @file Subscriber.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_SUBSCRIBER_API_H
#define GSTONE_SUBSCRIBER_API_H 1

#include "swiftdds/dcps/core/Entity.h"
#include "swiftdds/dcps/core/Listener.h"
#include "swiftdds/dcps/core/CoreTypes.h"
#include "swiftdds/dcps/core/ForwardDeclaration.h"
#include "swiftdds/dcps/sub/SubscriberListener.h"
#include "swiftdds/dcps/sub/DataReader.h"
#include "swiftdds/dcps/sub/DataReaderQos.h"
#include "swiftdds/dcps/topic/TopicQos.h"
#include "swiftdds/dcps/sub/SubscriberQos.h"


__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace sub {
    class SubscriberDelegate;
} /* sub */
} /* gstone */

namespace dds
{
namespace sub
{
    /**
    * @class Subscriber
    * @brief A Subscriber is the object responsible for the actual reception of the data resulting from its subscriptions
    */
    class GS_DDS4CPP_API Subscriber : public dds::core::Entity
    {
    public:

        /**
         * @brief Construct a new Subscriber object
         * @param [in] sub_delegate The delegate of subscriber
         */
        Subscriber(gstone::sub::SubscriberDelegate* const sub_delegate) noexcept;
        
        /**
         * @brief Destroy the Subscriber object
         */
        ~Subscriber() override = default;

        /**
         * @brief By virtue of extending Entity, a Subscriber can be given QoS at creation time or later by using the set_qos operation.
         * @param [in] a_qos The qos of subscriber
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         */
        DDS::ReturnCode_t set_qos(SubscriberQos const &a_qos) noexcept;
        
        /**
         * @brief Allows access to the values of the QoS.
         * @param [in,out] a_qos The qos of subscriber
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         */
        DDS::ReturnCode_t get_qos(SubscriberQos& a_qos) const noexcept;
        
        /**
         * @brief This operation creates a DataReader. The returned DataReader will be attached and belong to the Subscriber.
         * @param [in] a_topic The topic of reader
         * @param [in] a_qos The qos of reader
         * @param [in] a_listener The listener of reader
         * @param [in] mask The mask of listener
         * @return dds::sub::DataReader* The pointer of datareader
         */
        dds::sub::DataReader* create_datareader(dds::topic::TopicDescription* const a_topic, DataReaderQos &a_qos, dds::sub::DataReaderListener* const a_listener, DDS::StatusMask const mask) noexcept;
        
        /**
         * @brief This operation deletes a DataReader that belongs to the Subscriber. 
         * @param [in] a_datareader The reader need to be deleted.
         * @return DDS::ReturnCode_t If the DataReader does not belong to the Subscriber,
         * the operation returns the error PRECONDITION_NOT_MET.
         */
        DDS::ReturnCode_t delete_datareader(dds::sub::DataReader* const a_datareader) noexcept;
        
        /**
         * @brief This operation retrieves a previously-created DataReader belonging to the Subscriber that is attached
         * to a Topic with a matching topic_name.
         * @param [in] topic_name The topic of reader
         * @return dds::sub::DataReader* If no such DataReader exists, the operation will return 'nil.'
         */
        dds::sub::DataReader* lookup_datareader(std::string const &topic_name) noexcept;
        
        /**
         * @brief This operation indicates that the application is about to access the data samples in any of
         * the DataReader objects attached to the Subscriber.
         * @return DDS::ReturnCode_t
         * @retval RETCODE_OK no error
         * @retval PRECONDITION_NOT_MET In the aforementioned case, the operation begin_access must be called
         * prior to calling any of the sample-accessing operations, namely: get_datareaders on the Subscriber
         * and read, take, read_w_condition, take_w_condition on any DataReader.
         * Otherwise the sample-accessing operations will return the error PRECONDITION_NOT_MET. Once the application
         * has finished accessing the data samples it must call end_access.
         */
        DDS::ReturnCode_t begin_access() const noexcept;
        
        /**
         * @brief Indicates that the application has finished accessing the data samples in DataReader objects
         * managed by the Subscriber.
         * @return DDS::ReturnCode_t 
         * @retval RETCODE_OK no error
         * @retval PRECONDITION_NOT_MET After calling end_access the application should no longer access any of
         * the Data or SampleInfo elements returned from the sample-accessing operations. This call must close
         * a previous call to begin_access otherwise the operation will return the error PRECONDITION_NOT_MET.
         */
        DDS::ReturnCode_t end_access() const noexcept;
        
        /**
         * @brief This operation allows the application to access the DataReader objects that contain samples
         * with the specified sample_states, view_states, and instance_states.
         * @return DDS::ReturnCode_t
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         */
        DDS::ReturnCode_t get_datareaders(DataReaderSeq &readers, DDS::SampleStateMask const sample_states, DDS::ViewStateMask const view_states, DDS::InstanceStateMask const instance_states) const noexcept;
        
        /**
         * @brief This operation invokes the operation on_data_available on the DataReaderListener objects
         * @return DDS::ReturnCode_t
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         */
        DDS::ReturnCode_t notify_datareaders() const noexcept;
        
        /**
         * @brief This operation returns the DomainParticipant to which the Subscriber belongs.
         * @return dds::domain::DomainParticipant* The pointer of DomainParticipant
         */
        dds::domain::DomainParticipant* get_participant() const noexcept;
        
        /**
         * @brief This operation deletes all the entities that were created by means of the "create"
         * operations on the Subscriber. That is, it deletes all contained DataReader objects. 
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET contained_entities is empty
         */
        DDS::ReturnCode_t delete_contained_entities() noexcept;
        
        /**
         * @brief This operation sets a default value of the DataReader QoS policies which will be
         * used for newly created DataReader entities in the case where the QoS policies are defaulted
         * in the create_datareader operation.
         * @param [in] a_qos The default qos of reader
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         */
        DDS::ReturnCode_t set_default_datareader_qos(DataReaderQos const &a_qos) noexcept;
        
        /**
         * @brief This operation retrieves the default value of the DataReader QoS, that is,
         * the QoS policies which will be used for newly created DataReader entities in the case
         * where the QoS policies are defaulted in the create_datareader operation.
         * @param [in,out] a_qos The default qos of reader
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         */
        DDS::ReturnCode_t get_default_datareader_qos(DataReaderQos& a_qos) const noexcept;
        
        /**
         * @brief This operation copies the policies in the a_topic_qos to the corresponding
         * policies in the a_datareader_qos (replacing values in the a_datareader_qos, if present).
         * @param [in] a_datareader_qos The qos of datareader
         * @param [in] a_topic_qos The qos of topic
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_BAD_PARAMETER reliability is Unequal
         */
        DDS::ReturnCode_t copy_from_topic_qos(DataReaderQos &a_datareader_qos, dds::topic::TopicQos const &a_topic_qos) const noexcept;
        
        /**
         * @brief By virtue of extending Entity, a Subscriber can be attached to a Listener at
         * creation time or later by using the set_listener operation.
         * @param [in] listener The listener of reader
         * @param [in] mask The mask of listener
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET reader is unenable
         */
        DDS::ReturnCode_t set_listener(dds::core::Listener* listener, DDS::StatusMask mask) noexcept override;
        
        /**
         * @brief Allows access to the attached SubscriberListener.
         * @return dds::core::Listener* The pointer of listener.
         */
        dds::core::Listener* get_listener() noexcept override;
        
        /**
         * @brief This operation allows access to the StatusCondition associated with the Entity.
         * @return dds::core::StatusCondition* The pointer of StatusCondition
         */
        dds::core::StatusCondition* get_statuscondition() noexcept override;
        
        /**
         * @brief This operation retrieves the list of communication statuses in the Entity that are 'triggered.' 
         * @return DDS::StatusMask The masks are 'triggered
         */
        DDS::StatusMask get_status_changes() noexcept override;
        
        /**
         * @brief This operation enables the Entity. Entity objects can be created either enabled or disabled. 
         * @return DDS::ReturnCode_t 
         * @retval DDS::ReturnCode_t::RETCODE_OK nothing wrong
         * @retval DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET reader is already enable
         */
        DDS::ReturnCode_t enable() noexcept override;
        
        /**
         * @brief This operation returns the InstanceHandle_t that represents the Entity.
         * @return gstone::rtps::InstanceHandle_t The InstanceHandle that represents the Entity.
         */
        gstone::rtps::InstanceHandle_t get_instance_handle() noexcept override;

    protected:
        /**
         * @brief This function is deleted.
         */
        Subscriber() = delete;
        
        /**
         * @brief Copy-Construct a new Subscriber object
         * @param [in] other 
         */
        Subscriber(Subscriber const& other) = default;
        
        /**
         * @brief Move-Construct a new Subscriber object
         * @param [in] other 
         */
        Subscriber(Subscriber&& other) = default;
        
        /**
         * @brief Assign a Subscriber object to the locally Subscriber object.
         * @param [in] other. reference of a Subscriber object.
         * @return Reference of the locally Subscriber object.
         */
        Subscriber& operator=(Subscriber const& other) = default;
        
        /**
         * @brief Assign a Subscriber object to the locally Subscriber object.
         * @param [in] other. reference of a Subscriber object.
         * @return Reference of the locally Subscriber object.
         */
        Subscriber& operator=(Subscriber&& other) = default;

    private:
        //std::shared_ptr<gstone::sub::SubscriberDelegate> m_sub;
        gstone::sub::SubscriberDelegate* m_delegate;
    };
} /* sub */
} /* dds */

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_SUBSCRIBER_API_H*/
