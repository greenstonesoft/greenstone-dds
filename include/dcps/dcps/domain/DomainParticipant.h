/**************************************************************
* @file DomainParticipant.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#ifndef GSTONE_DOMAINPARTICIPANT_API_H
#define GSTONE_DOMAINPARTICIPANT_API_H 1

#include "dcps/DdsBaseTypes.h"
#include "dcps/core/Entity.h"
#include "dcps/domain/DomainParticipantQos.h"
#include "dcps/pub/Publisher.h"
#include "dcps/sub/Subscriber.h"
#include "dcps/topic/Topic.h"
#include "dcps/core/ForwardDeclaration.h"
#include "dcps/topic/TopicDescription.h"
#include "dcps/topic/ContentFilteredTopic.h"
#include "dcps/topic/MultiTopic.h"
#include "dcps/sub/SubscriberQos.h"
#include "dcps/sub/DataReaderQos.h"
#include "dcps/pub/PublisherQos.h"
#include "dcps/pub/DataWriterQos.h"
#include "dcps/topic/TopicQos.h"
#include "dcps/topic/ParticipantBuiltinTopicData.h"
#include "dcps/topic/TopicBuiltinTopicData.h"


__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace domain {
    class DomainParticipantDelegate;
}/*domain*/
}/*gstone*/

namespace dds
{
namespace domain
{
    /**
    * @class RemoteParticipantStatus
    * @brief Enum class for existing status of a remote participant.
    */
    enum class RemoteParticipantStatus: gint32_t
    {
        ONLINE = 0U,
        OFFLINE
    };

    /**
    * @class RemoteParticipantInfo
    * @brief This class stores some necessary information of a remote participant.
    */
    class RemoteParticipantInfo
    {
    public:
        /**
        * @brief Don't use Constructor of the class RemoteParticipantInfo.
        */
        RemoteParticipantInfo() = delete;

        /**
        * @brief Don't use constructor of the class RemoteParticipantInfo by another RemoteParticipantInfo object.
        * @param [in] a_info Const reference of a RemoteParticipantInfo object.
        */
        RemoteParticipantInfo( RemoteParticipantInfo const & a_info) = delete;

        /**
        * @brief Don't use assign a RemoteParticipantInfo object to the locally RemoteParticipantInfo object.
        * @param [in] a_info Const reference of a RemoteParticipantInfo object.
        * @return Reference of the locally RemoteParticipantInfo object.
        */
        RemoteParticipantInfo &operator=(RemoteParticipantInfo const &a_info) = delete;

        /**
        * @brief Don't use move constructor of the class RemoteParticipantInfo.
        * @param [in] a_info Rvalue reference of a RemoteParticipantInfo object.
        */
        RemoteParticipantInfo( RemoteParticipantInfo const && a_info) = delete;

        /**
        * @brief Don't use move assignment of the class RemoteParticipantInfo.
        * @param [in] a_info Rvalue reference of this RemoteParticipantInfo object.
        * @return Reference of this RemoteParticipantInfo object.
        */
        RemoteParticipantInfo &operator=(RemoteParticipantInfo const &&a_info) = delete;

        /**
        * @brief Don't use Constructor of the class RemoteParticipantInfo.
        * @param [in] a_guid Const reference of a GUID object.
        * @param [in] a_status Const reference of a RemoteParticipantStatus object.
        * @param [in] a_data Const reference of a ParticipantBuiltinTopicData object.
        */
        RemoteParticipantInfo(gstone::rtps::GUID const &a_guid,
                              RemoteParticipantStatus const &a_status,
                              dds::topic::ParticipantBuiltinTopicData const &a_data);

        /**
        * @brief Destructor of the class RemoteParticipantInfo.
        */
        virtual ~RemoteParticipantInfo()=default;

        /**
        * @brief This function retrieves InstanceHandle of a RemoteParticipantInfo object.
        * @return The InstanceHandle object.
        */
        inline gstone::rtps::InstanceHandle_t const &instance_handle() const noexcept
        {
            return m_instanceHandle;
        }
        
        /**
         * @brief This function assigns the locally InstanceHandle to the parameter InstanceHandle.
         * @param [in] a_instance Reference of an InstanceHandle object.
         */ 
        inline gvoid_t instanceHanlde(gstone::rtps::InstanceHandle &a_instance) const noexcept
        {
            a_instance = m_instanceHandle;
        }

        /**
         * @brief This function sets InstanceHandle of a RemoteParticipantInfo object.
         * @param [in] a_instance Const reference of an InstanceHandle object.
         */ 
        inline gvoid_t instanceHanlde(gstone::rtps::InstanceHandle const &a_instance) noexcept
        {
            if(m_instanceHandle != a_instance)
            {
                m_instanceHandle = a_instance;
            }

        }

        /**
        * @brief This function retrieves RemoteParticipantStatus of a RemoteParticipantInfo object.
        * @return The RemoteParticipantStatus object.
        */
        inline RemoteParticipantStatus const &status() const noexcept
        {
            return m_status;
        }

        /**
         * @brief This function assigns the locally RemoteParticipantStatus to the parameter RemoteParticipantStatus.
         * @param [in] a_status Reference of a RemoteParticipantStatus object.
         */ 
        inline gvoid_t status(RemoteParticipantStatus &a_status) const noexcept
        {
            if(a_status != m_status)
            {
                a_status = m_status;
            }

        }

        /**
         * @brief This function sets RemoteParticipantStatus of a RemoteParticipantInfo object.
         * @param [in] a_status Const reference of a RemoteParticipantStatus object.
         */  
        inline gvoid_t status(RemoteParticipantStatus const &a_status) noexcept
        {
            m_status = a_status;
        }

        /**
        * @brief This function retrieves ParticipantBuiltinTopicData of a RemoteParticipantInfo object.
        * @return The ParticipantBuiltinTopicData object.
        */ 
        inline dds::topic::ParticipantBuiltinTopicData const &data() const noexcept
        {
            return m_data;
        }

        /**
         * @brief This function sets ParticipantBuiltinTopicData of a RemoteParticipantInfo object.
         * @param [in] a_data Const reference of a ParticipantBuiltinTopicData object.
         */
        inline gvoid_t data(dds::topic::ParticipantBuiltinTopicData const &a_data)
        {
            m_data = a_data;
        }

    private:
        gstone::rtps::InstanceHandle_t m_instanceHandle;
        RemoteParticipantStatus m_status;
        dds::topic::ParticipantBuiltinTopicData m_data;
    };

    /**
		* @class DomainParticipant
		* @brief A factory and container for the Publisher, Subscriber, Topic, and MultiTopic Entity objects.
        * @details It represents the participation of the application on a communication plane that isolates 
        * applications running on the same set of physical computers from each other. A domain establishes a 
        * virtual network linking all applications that share the same domainId and isolating them from applications 
        * running on different domains. In this way, several independent distributed applications can coexist in 
        * the same physical network without interfering, or even being aware of each other. \n
        * It provides administration services in the domain, offering operations that allow the application to ignore 
        * locally any information about a given participant (DDSDomainParticipant::ignore_participant), publication 
        * (DDSDomainParticipant::ignore_publication), subscription (DDSDomainParticipant::ignore_subscription()) or 
        * topic (DDSDomainParticipant::ignore_topic()).
		*/
    class GS_DDS4CPP_API DomainParticipant : public dds::core::Entity
    {
    public:
        /**
         * @brief This operation is used to set the QoS policies of the DomainParticipant.
         * @param [in] a_qos Const reference of a DomainParticipantQos object.
         * @return Return RETCODE_OK.
         */ 
        DDS::ReturnCode_t set_qos(DomainParticipantQos const& a_qos) noexcept;

        /**
         * @brief This operation retrieves the QoS policies of the DomainParticipant.
         * @param [in,out] a_qos Reference of a DomainParticipantQos object.
         * @return Return RETCODE_OK.
         */ 
        DDS::ReturnCode_t get_qos(DomainParticipantQos& a_qos) const noexcept;

        /**
         * @brief This operation creates a Publisher.
         * @param [in] a_qos_policy Reference of a PublisherQos object.
         * @param [in] a_listener Const pointer of a PublisherListener object.
         * @param [in] a_mask Communication status mask.
         * @return Return a pointer of a newly created Publisher.
         */ 
        dds::pub::Publisher* create_publisher(dds::pub::PublisherQos& a_qos_policy, dds::pub::PublisherListener* const a_listener, DDS::StatusMask const a_mask) noexcept;
        
        /**
         * @brief This operation deletes an existing Publisher.
         * @param [in] a_publisher The pointer of the Publisher to delete.
         * @return Return DDS::ReturnCode_t.
         * @retval RETCODE_OK or It is successful to delete publisher.
         * @retval RETCODE_PRECONDITION_NOT_MET  If delete_publisher is called on a different DomainParticipant, the operation 
         * will have no effect and it will return PRECONDITION_NOT_MET.If delete_publisher is called on a Publisher with existing 
         * DataWriter object, it will return PRECONDITION_NOT_MET.
         */ 
        DDS::ReturnCode_t delete_publisher(dds::pub::Publisher const* const a_publisher) noexcept;
        
        /**
         * @brief This operation creates a Subscriber.
         * @param [in] a_qos_policy Reference of a SubscriberQos object.
         * @param [in] a_listener Const pointer of a SubscriberListener object.
         * @param [in] a_mask Communication status mask.
         * @return Return a pointer of a newly created Subscriber.
         */ 
        dds::sub::Subscriber* create_subscriber(dds::sub::SubscriberQos& a_qos_policy, dds::sub::SubscriberListener* const a_listener, DDS::StatusMask const a_mask) noexcept;
        
        /**
         * @brief This operation deletes an existing Sublisher.
         * @param [in] a_sublisher The pointer of the Sublisher to delete.
         * @return Return DDS::ReturnCode_t.
         * @retval RETCODE_OK It is successful to delete subscriber.
         * @retval RETCODE_PRECONDITION_NOT_MET  If the delete_subscriber operation is called on a Subscriber with 
         * existing DataReader objects, it will return PRECONDITION_NOT_MET.If delete_subscriber is called on a different 
         * DomainParticipant, the operation will have no effect and it will return PRECONDITION_NOT_MET.
         */ 
        DDS::ReturnCode_t delete_subscriber(dds::sub::Subscriber const* const a_subscriber) noexcept;
        
        /**
         * @brief This operation creates a Topic.
         * @details The Topic is bound to a type described by the type_name argument. Prior to creating a
         * Topic the type must have been registered with the Service.
         * @param [in] a_topic_name Topic's name
         * @param [in] a_type_name The name of type registed by register_type.
         * @param [in] a_topic_qos Topic's qos
         * @param [in] a_listener Topic's listener
         * @param [in] a_mask Communication status mask.
         * @return Return a pointer of a newly created Topic or nullptr.
         */ 
        dds::topic::Topic* create_topic(gstring_t const& a_topic_name, gstring_t const& a_type_name,
            dds::topic::TopicQos& a_topic_qos,
            dds::topic::TopicListener* const a_listener = nullptr, DDS::StatusMask const a_mask = DDS::EmptyStatusMask) noexcept;
        
        /**
         * @brief The function registers a TopicDataType or a DynamicTopicDataType.
         * @param [in] a_type Const pointer of a TopicDataType object.
         * @return Return DDS::ReturnCode_t.
         * @retval RETCODE_OK It is successful to register type.
         * @retval RETCODE_PRECONDITION_NOT_MET It is a pre-condition error to use the same type_name to register two different 
         * TypeSupport with the same DomainParticipant. If an application attempts this, the operation will fail and 
         * return PRECONDITION_NOT_MET.
         * @retval RETCODE_ERROR If a_type's name is empty or it fails to create a dynamic topic, it returns RETCODE_ERROR.
         */ 
        DDS::ReturnCode_t register_type(dds::topic::TopicDataType* const a_type) noexcept;
        
        /**
         * @brief This function checks whether or not existing a TopicDataType or a DynamicTopicDataType using type.
         * @param [in] a_type Const reference of a TopicDataType object.
         * @return Return true or false.
         * @retval true  If there is a Type used a_type existing, it will return true.
         * @retval false If there is not a Type used a_type existing, it will return true.
         */ 
        gbool_t is_type_registered(dds::topic::TopicDataType const *const a_type) noexcept;
        
        /**
         * @brief This function checks whether or not existing a TopicDataType or a DynamicTopicDataType using type_name.
         * @param [in] a_type_name type_name
         * @return Return true or false.
         * @retval true  If there is a Type named a_type_name existing, it will return true.
         * @retval false If there is not a Type named a_type_name existing, it will return true.
         */ 
        gbool_t is_type_registered(gstring_t const& a_type_name) noexcept;
        
        /**
         * @brief This function unregisters a TopicDataType or a DynamicTopicDataType by type_name.
         * @param [in] a_type_name TopicDataType's type_name or DynamicTopicDataType's name.
         * @return Return DDS::ReturnCode_t.
         * @retval RETCODE_OK It is successful to unregister type.
         * @retval RETCODE_PRECONDITION_NOT_MET If the unregister_type operation is called on a TopicType with any of these existing 
         * objects attached to it, it will return PRECONDITION_NOT_MET.
         */ 
        DDS::ReturnCode_t unregister_type(gstring_t const& a_type_name) noexcept;
        
        /**
         * @brief This operation deletes a Topic.
         * @details The delete_topic operation must be called on the same DomainParticipant object used to create the Topic.
         * The deletion of a Topic is not allowed if there are any existing DataReader, DataWriter, ContentFilteredTopic, 
         * or MultiTopic objects that are using the Topic.
         * @param [in] a_topic Const pointer of a Topic object.
         * @return RETURN DDS::ReturnCode_t.
         * @retval RETCODE_OK  It is successful to delete topic.
         * @retval RETCODE_PRECONDITION_NOT_MET  If the delete_topic operation is called on a Topic with any of these existing 
         * objects attached to it, it will return PRECONDITION_NOT_MET.
         */ 
        DDS::ReturnCode_t delete_topic(dds::topic::Topic const* const a_topic) noexcept;
        
        /**
         * @brief This operation creates a ContentFilteredTopic.
         * @param [in] a_name Name of the newly create ContentFilteredTopic.
         * @param [in] a_related_topic Const pointer of a Topic object, being subscribed to.
         * @param [in] a_filter_expression The filtering content.
         * @param [in] a_expression A string used for filter.
         * @return Return nullptr.
         * @todo
         */ 
        dds::topic::ContentFilteredTopic* create_contentfilteredtopic(gstring_t const& a_name,
            dds::topic::Topic const *const a_related_topic, gstring_t const& a_filter_expression, dds::core::StringSeq const& a_expression) noexcept;
        
        /**
         * @brief This operation deletes a ContentFilteredTopic.
         * @param [in] a_content_filter_topic Const pointer of a ContentFilteredTopic object.
         * @return Return DDS::ReturnCode_t.
         * @retval RETCODE_BAD_PARAMETER If a_content_filter_topic is nullptr, it returns RETCODE_BAD_PARAMETER.
         * @retval RETCODE_OK It is successful to delete contentfilteredtopic.
         * @todo
         */ 
        DDS::ReturnCode_t delete_contentfilteredtopic(dds::topic::ContentFilteredTopic const *const a_content_filter_topic) noexcept;
        
        /**
         * @brief This operation creates a MultiTopic. 
         * @param [in] a_name Name of the newly create DDSMultiTopic.
         * @param [in] a_type_name  Specify the resulting type.
         * @param [in] a_subscription_expression Content being subscribed to.
         * @param [in] a_expression A string used for filter.
         * @return Return nullptr.
         * @todo
         */ 
        dds::topic::MultiTopic* create_multitopic(gstring_t const& a_name, gstring_t const& a_type_name,
            gstring_t const& a_subscription_expression, dds::core::StringSeq const& a_expression) noexcept;
        
        /**
         * @brief This operation deletes a MultiTopic.
         * @param [in] a_multi_topic Const reference of a MultiTopic object.
         * @return Return DDS::ReturnCode_t.
         * @retval RETCODE_BAD_PARAMETER If a_multi_topic is nullptr, it returns RETCODE_BAD_PARAMETER.
         * @retval RETCODE_OK  It is successful to delete multitopic.
         * @todo
         */ 
        DDS::ReturnCode_t delete_multitopic(dds::topic::MultiTopic const *const a_multi_topic) noexcept;
        
        /**
         * @brief The operation find_topic gives access to an existing (or ready to exist) enabled Topic, based on its name.
         * @param [in] a_topic_name The name of the Topic.
         * @param [in] a_time_out timeout, return nullptr if the operation times-out.
         * @return Return Topic* or nullptr.
         * @retval nullptr If it dose not find a Topic* has a_topic_name, it returns nullptr.
         */ 
        dds::topic::Topic* find_topic(gstring_t const& a_topic_name, gstone::rtps::Duration_t const a_time_out) noexcept;
        
        /**
         * @brief The operation lookup_topicdescription gives access to an existing locally-created TopicDescription, based on its name.
         * @param [in] a_name The name of the TopicDescription.
         * @return Return a pointer of TopicDescription or nullptr.
         * @retval nullptr If it dose not find a TopicDescription has a_name, it returns nullptr.
         */ 
        dds::topic::TopicDescription* lookup_topicdescription(gstring_t const& a_name) noexcept;
        
        /**
         * @brief This operation allows access to the built-in Subscriber.
         * @return Return nullptr.
         * @todo
         */ 
        dds::sub::Subscriber* get_builtin_subscriber() const noexcept;
        
        /**
         * @brief This operation allows an application to instruct the Service to locally ignore a remote domain participant.
         * @details This means it will ignore any Topic, publication, or subscription that originates on that domain participant.
         * @param [in] a_handle Const reference of InstanceHandle_t, the handle of the participant to ignore.
         * @return Return DDS::ReturnCode_t. 
         * @retval RETCODE_BAD_PARAMETER If a_handle is HANDLE_NIL, it returns RETCODE_BAD_PARAMETER.
         * @retval RETCODE_OK It is successful to ignore participant.
         * @todo
         */ 
        DDS::ReturnCode_t ignore_participant(gstone::rtps::InstanceHandle_t const& a_handle) noexcept;
        
        /**
         * @brief This operation allows an application to instruct the Service to locally ignore a Topic.
         * @details This means it will locally ignore any publication or subscription to the Topic.
         * This operation can be used to save local resources when the application knows that it will never 
         * publish or subscribe to data under certain topics.
         * @param [in] a_handle Const reference of InstanceHandle_t, the handle of the topic to ignore.
         * @return Return DDS::ReturnCode_t. 
         * @retval RETCODE_BAD_PARAMETER If a_handle is HANDLE_NIL, it returns RETCODE_BAD_PARAMETER.
         * @retval RETCODE_OK It is successful to ignore topic.
         * @todo
         */ 
        DDS::ReturnCode_t ignore_topic(gstone::rtps::InstanceHandle_t const& a_handle) noexcept;
        
        /**
         * @brief This operation allows an application to instruct the Service to locally ignore a remote DataWriter.
         * @details Any data written related to that publication will be ignored.
         * @param [in] a_handle Const reference of InstanceHandle_t, the handle of the DataWriter to ignore.
         * @return Return DDS::ReturnCode_t. 
         * @retval RETCODE_BAD_PARAMETER If a_handle is HANDLE_NIL, it returns RETCODE_BAD_PARAMETER.
         * @retval RETCODE_OK It is successful to ignore publication.
         * @todo
         */ 
        DDS::ReturnCode_t ignore_publication(gstone::rtps::InstanceHandle_t const& a_handle) noexcept;
        
        /**
         * @brief This operation allows an application to instruct the Service to locally ignore a remote DataReader.
         * @details Any data received related to that subscription will be ignored.
         * @param [in] a_handle Const reference of InstanceHandle_t, the handle of the DataReader to ignore.
         * @return Return DDS::ReturnCode_t. 
         * @retval RETCODE_BAD_PARAMETER If a_handle is HANDLE_NIL, it returns RETCODE_BAD_PARAMETER.
         * @retval RETCODE_OK It is successful to ignore subscription.
         * @todo
         */ 
        DDS::ReturnCode_t ignore_subscription(gstone::rtps::InstanceHandle_t const& a_handle) noexcept;
        
        /**
         * @brief This operation retrieves the domain_id used to create the DomainParticipant.
         * @return return DomainId.
         */ 
        DDS::DomainId_t get_domain_id()  const noexcept;
        
        /**
         * @brief This operation deletes all the entities that were created by means of the “create” 
         * operations on the DomainParticipant.
         * @details It deletes all contained Publisher, Subscriber, Topic, ContentFilteredTopic, and MultiTopic.
         * @return Return DDS::ReturnCode_t.
         * @retval RETCODE_BAD_PARAMETER The operation will return PRECONDITION_NOT_MET if the any of the contained 
         * entities is in a state where it cannot be deleted.
         * @retval RETCODE_OK It is successful to delete contained entities.
         */ 
        DDS::ReturnCode_t delete_contained_entities() noexcept;
        
        /**
         * @brief This operation manually asserts the liveliness of the DomainParticipant.
         * @details This is used in combination with the LIVELINESS QoS policy to indicate to the Service that 
         * the entity remains active.This operation needs to only be used if the DomainParticipant contains DataWriter 
         * entities with the LIVELINESS set to MANUAL_BY_PARTICIPANT and it only affects the liveliness of those DataWriter 
         * entities. The use of assert_liveliness is only needed if the application is not writing data regularly.
         * @return Return RETCODE_OK.
         */ 
        DDS::ReturnCode_t assert_liveliness() noexcept;
        
        /**
         * @brief This function sets a default value of the Publisher QoS policies.
         * @details the QoS policies which will be used for newly created Publisher entities in the case where the QoS 
         * policies are defaulted in the create_publisher operation.
         * @param [in] a_qos_policy Const reference of a PublisherQos object.
         * @return Return RETCODE_OK.
         */ 
        DDS::ReturnCode_t set_default_publisher_qos(dds::pub::PublisherQos const& a_qos_policy) noexcept;
        
        /**
         * @brief This function retrieves the default value of the Publisher QoS.
         * @details The QoS policies which will be used for newly created Publisher entities in the case where the QoS 
         * policies are defaulted in the create_publisher operation.
         * @param [in,out] a_qos_policy Reference of a PublisherQos object.
         * @return Return RETCODE_OK.
         */ 
        DDS::ReturnCode_t get_default_publisher_qos(dds::pub::PublisherQos& a_qos_policy) const noexcept;
        
        /**
         * @brief This function sets a default value of the Subscriber QoS policies.
         * @details The QoS policies which will be used for newly created Subscriber entities in the case where the QoS 
         * policies are defaulted in the create_subscriber operation.
         * @param [in] a_qos_policy Const reference of a SubscriberQos object.
         * @return Return RETCODE_OK.
         */ 
        DDS::ReturnCode_t set_default_subscriber_qos(dds::sub::SubscriberQos const& a_qos_policy) noexcept;
        
        /**
         * @brief   This function retrieves the default value of the Subscriber Qos.
         * @details The QoS policies which will be used for newly created Subscriber entities 
         *          in the case where the QoS policies are defaulted in the create_subscriber operation.
         * @param   [in,out] a_qos_policy Reference of a SubscriberQos object.
         * @return  return RETCODE_OK.
         */ 
        DDS::ReturnCode_t get_default_subscriber_qos(dds::sub::SubscriberQos& a_qos_policy) const noexcept;
        
        /**
         * @brief This function sets a default value of the Topic Qos.
         * @details The Topic Qos that will be used for newly created Topic entities in the case where the 
         * QoS policies are defaulted in the create_topic operation.
         * @param [in] a_qos_policy Const reference of a TopicQos object.
         * @return Return RETCODE_OK.
         */ 
        DDS::ReturnCode_t set_default_topic_qos(dds::topic::TopicQos const& a_qos_policy) noexcept;
        
        /**
         * @brief This function retrieves the default value of the Topic QoS.
         * @details The Topic Qos that will be used for newly created Topic entities in the case where the 
         * QoS policies are defaulted in the create_topic operation.
         * @param [in,out] a_qos_policy Reference of a TopicQos object.
         * @return Return RETCODE_OK.
         */ 
        DDS::ReturnCode_t get_default_topic_qos(dds::topic::TopicQos& a_qos_policy) const noexcept;
        
        /**
         * @brief This function retrieves the list of DomainParticipant that have been discovered in the domain.
         * @details These participants must be in the same domain as the participant on which this operation
         * is invoked and must not have been "ignored" by means of the DomainParticipant ignore_participant.
         * @param [in,out] handles Reference of a HandleSeq object.
         * @return Return DDS::ReturnCode_t.
         * @retval RETCODE_BAD_PARAMETER If the DomainParticipant's rtps participant is nullptr, it returns RETCODE_BAD_PARAMETER.
         * @retval RETCODE_OK It is successful to get discovered participant data.
         */ 
        DDS::ReturnCode_t get_discovered_participants(dds::core::HandleSeq& handles) const noexcept;
        
        /**
         * @brief This function retrieves information on a DomainParticipant that has been discovered on the network.
         * @details The participant must be in the same domain as the participant on which this operation
         * is invoked and must not have been "ignored" by means of the DomainParticipant ignore_participant.
         * @param [in,out] a_data Reference of a ParticipantBuiltinTopicData object.
         * @param [in] a_handle Const reference of a InstanceHandle_t object.
         * @return Return DDS::ReturnCode_t.
         * @retval RETCODE_BAD_PARAMETER If the DomainParticipant's rtps participant is nullptr, it returns RETCODE_BAD_PARAMETER.
         * If it does not find a DomainParticipant has 'a_handle', it returns RETCODE_BAD_PARAMETER.
         * @retval RETCODE_OK It is successful to get discovered participant data.
         */ 
        DDS::ReturnCode_t get_discovered_participant_data(dds::topic::ParticipantBuiltinTopicData& a_data, gstone::rtps::InstanceHandle_t const& a_handle) const noexcept;
        
        /**
         * @brief This function retrieves the list of Topics that have been discovered in the domain.
         * @details These topics must have been created by a participant in the same domain as the participant on which 
         * this operation is invoked and must not have been "ignored" by means of the DomainParticipant ignore_topic.
         * @param [in] handles Reference of a InstanceHandleSeq object.
         * @return Return DDS::ReturnCode_t.
         * @retval RETCODE_OK It is successful to get discovered topics.
         * @retval RETCODE_PRECONDITION_NOT_MET  The topic_handle must correspond to such a topic. Otherwise, 
         * the operation will fail and return PRECONDITION_NOT_MET.
         * @todo
         */ 
        DDS::ReturnCode_t get_discovered_topics(gstone::rtps::InstanceHandleSeq& handles) const noexcept;
        
        /**
         * @brief This function retrieves information on a Topic that has been discovered on the network.
         * @details The topic must have been created by a participant in the same domain as the participant on which 
         * this operation is invoked and must not have been "ignored" by means of the DomainParticipant ignore_topic.
         * @param [in,out] a_data Reference of a TopicBuiltinTopicData object. 
         * @param [in] a_handle Const reference of a InstanceHandle_t object. 
         * @return Return DDS::ReturnCode_t.
         * @retval RETCODE_BAD_PARAMETER If a_handle is HANDLE_NIL, it returns false.
         * @retval RETCODE_OK It is successful to get discovered topic data.
         * @todo
         */ 
        DDS::ReturnCode_t get_discovered_topic_data(dds::topic::TopicBuiltinTopicData& a_data, gstone::rtps::InstanceHandle_t const& a_handle) const noexcept;
        
        /**
         * @brief This function checks whether or not the given _handle represents an Entity that was 
         * created from the DomainParticipant.
         * @param [in] a_handle Const reference of a InstanceHandle_t object. 
         * @return Return gbool_t.
         * @retval false If a_handle is HANDLE_NIL, it returns false.
         * @todo
         */ 
        gbool_t contains_entity(gstone::rtps::InstanceHandle_t const& a_handle) const noexcept;
        
        /**
         * @brief This function gets the current time.
         * @details The value of the time that the service uses to time-stamp data-writers and to set the 
         * reception-timestamp for the data-updates it receives.
         * @param [in,out]  a_current_time Time_t, retrieves time value.
         * @return Return DDS::ReturnCode_t.
         * @retval RETCODE_BAD_PARAMETER If a_current_time is smaller than 1, it returns RETCODE_BAD_PARAMETER.
         * @retval RETCODE_OK  It is successful to get current time.
         * @todo
         */ 
        DDS::ReturnCode_t get_current_time(DDS::Time_t& a_current_time) const noexcept;

#ifdef ENABLE_HIBERNATE
        /**
         * @brief This function hibernates all entities created by this DomainParticipant. 
         * @return Return true.
         */ 
        gbool_t hibernate();
        /**
         * @brief This function wakeups all entities created by this DomainParticipant. 
         * @return gbool_t
         * @retval true  It is successful to wakeup all entities created by this DomainParticipant. 
         * @retval false If this DomainParticipant is not enabled after being wakeuped, it returns false.
         */ 
        gbool_t wakeup();
#endif

        /**
         * @brief This function sets the DomainParticipant's listener and status mask.
         * @param [in] a_listener A pointer of the Listener.
         * @param [in] a_mask StatusMask.
         * @return DDS::ReturnCode_t.
         * @retval RETCODE_OK It is successful to set listener.
         * @retval RETCODE_PRECONDITION_NOT_MET If the DomainParticipant was enabled, it returns RETCODE_PRECONDITION_NOT_MET.
         */ 
        DDS::ReturnCode_t set_listener(dds::core::Listener* a_listener, DDS::StatusMask a_mask) noexcept override;
        
        /**
         * @brief This function gets the DomainParticipant's listener.
         * @return The DomainParticipant's listener.
         */ 
        dds::core::Listener* get_listener() noexcept override;
        
        /**
         * @brief This function gets the StatusCondition associated with the Entity.
         * @details The returned condition can then be add to a WaitSet so that the application can wait for 
         * specific status chagnes that affect the Entity.
         * @return The StatusCondition* associated with the Entity.
         */ 
        dds::core::StatusCondition* get_statuscondition() noexcept override;
        
        /**
         * @brief This function retrieves communication statuses mask in the Entity that are 'triggered'.
         * @details When the entity is first created or if the entity is disabled, all communication
         * statuses are in the 'untriggered' state so the mask returned by the function will be empty.
         * @return Communication statuses mask in the Entity that are 'triggered'.
         */ 
        DDS::StatusMask get_status_changes() noexcept override;
        
        /**
         * @brief This function enables the DomainParticipant.
         * @details This operation is used by ENTITY_FACTORY Qos policy. Entity objects can be enabled or 
         * disabled when using ENTITY_FACTORY Qos policy.
         * @return DDS::ReturnCode_t.
         * @retval RETCODE_OK   It is successful to enable.
         * @retval RETCODE_ERROR  If the DomainParticipant is uninitialized, it returns RETCODE_ERROR.
         */ 
        DDS::ReturnCode_t enable() noexcept override;
        
        /**
         * @brief This function gets the InstanceHandle_t of a DomainParticipant.
         * @return The InstanceHandle_t of a DomainParticipant.
         */ 
        gstone::rtps::InstanceHandle_t get_instance_handle() noexcept override;

        /**
        * @brief Don't use Constructor of the class DomainParticipant.
        */
        DomainParticipant() = delete;
        
        /**
        * @brief Don't use constructor of the class DomainParticipant by a DomainParticipantDelegate*.
        * @param [in] a_delegate A const DomainParticipantDelegate*.
        */
        DomainParticipant(gstone::domain::DomainParticipantDelegate* const _delegate) noexcept;
        
        /**
        * @brief Don't use constructor of the class DomainParticipant by another DomainParticipant object.
        * @param [in] a_info Const reference of a DomainParticipant object.
        */
        DomainParticipant(DomainParticipant const& a_info) = delete;
        
        /**
        * @brief Don't use assign a DomainParticipant object to the locally DomainParticipant object.
        * @param [in] a_info Const reference of a DomainParticipant object.
        * @return Reference of the locally DomainParticipant object.
        */
        DomainParticipant& operator=(DomainParticipant const& a_info) = delete;
        
        /**
        * @brief Don't use move constructor of the class DomainParticipant.
        * @param [in] a_info Rvalue reference of a DomainParticipant object.
        */
        DomainParticipant(DomainParticipant const&& a_info) = delete;
        
        /**
        * @brief Don't use move assignment of the class DomainParticipant.
        * @param [in] a_info Rvalue reference of this DomainParticipant object.
        * @return Reference of this DomainParticipant object.
        */
        DomainParticipant& operator=(DomainParticipant const&& a_info) = delete;
        
        /**
        * @brief Destructor of the class DomainParticipant.
        */
        ~DomainParticipant() noexcept override = default;

    private:
        gstone::domain::DomainParticipantDelegate* m_delegate;
    };
}/*domain*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_DOMAINPARTICIPANT_API_H*/
