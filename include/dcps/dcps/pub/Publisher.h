/**************************************************************
* @file Publisher.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#ifndef GSTONE_TPUBLISHER_API_H
#define GSTONE_TPUBLISHER_API_H 1

#include "dcps/core/Entity.h"
#include "dcps/core/Listener.h"
#include "dcps/core/ForwardDeclaration.h"
#include "dcps/core/CoreTypes.h"
#include "dcps/pub/PublisherListener.h"
#include "dcps/pub/DataWriter.h"
#include "dcps/pub/DataWriterQos.h"
#include "dcps/topic/TopicQos.h"
#include "dcps/pub/PublisherQos.h"


__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace pub {
    class PublisherDelegate;
}/*pub*/
}/*gstone*/

namespace dds
{
namespace pub
{
    /**
    * @class Publisher
    * @brief This class is the object responsible for the actual dissemination of publications.
    * @details The Publisher acts on the behalf of one or several DataWriter objects that belong to it.
    */
    class GS_DDS4CPP_API Publisher : public dds::core::Entity
    {
    public:
        /**
        * @brief Don't use constructor of the class Publisher.
        */
        Publisher() = delete;
        
        /**
        * @brief Constructor of the class Publisher by another Publisher object.
        * @param [in] a_pub_delegate Const PublisherDelegate* object.
        */
        Publisher(gstone::pub::PublisherDelegate* const a_pub_delegate) noexcept;
        
        /**
        * @brief Destructor of the class Publisher.
        */
        ~Publisher() override = default;

        /**
        * @brief This function sets the Publisher's PublisherQos.
        * @param [in] a_qos Const reference of a PublisherQos object.
        * @return Return DDS::ReturnCode_t.
        * @retval RETCODE_OK  The existing set of policies are changed if the set_qos operation succeeds.
        * This is indicated by the OK return value.
        */
        DDS::ReturnCode_t set_qos(PublisherQos const& a_qos) noexcept;
        
        /**
        * @brief This function retrieves the Publisher's PublisherQos.
        * @param [in,out] a_qos Reference of a PublisherQos object.
        * @return Return DDS::ReturnCode_t.
        * @retval RETCODE_OK This operation successed to get the existing set of QoS policies for the publisher.
        */
        DDS::ReturnCode_t get_qos(PublisherQos& a_qos) const noexcept;
        
        /**
        * @brief This function creates a DataWriter.
        * @param [in] a_topic A const Topic* object.
        * @param [in] a_qos Reference of a DataWriterQos object.
        * @param [in] a_listener Const pointer of a DataWriterListener object.
        * @param [in] a_mask Communication status mask.
        * @return Return DataWriter* or nullptr.
        */
        dds::pub::DataWriter* create_datawriter(dds::topic::Topic* const a_topic,
            DataWriterQos &a_qos, dds::pub::DataWriterListener* const a_listener, DDS::StatusMask const a_mask);
        
        /**
        * @brief This function deletes a DataWriter.
        * @param [in] a_datawriter A const DataWriter* object to delete.
        * @return Return DDS::ReturnCode_t.
        * @retval RETCODE_PRECONDITION_NOT_MET If delete_datawriter is called on a different Publisher, the operation 
        * will have no effect and it will return RETCODE_PRECONDITION_NOT_MET; possible error codes returned in 
        * addition to the standard ones: RETCODE_PRECONDITION_NOT_MET.
        * @retval RETCODE_OK   It is successful to delete a DataWriter that belongs to the Publisher.
        */
        DDS::ReturnCode_t delete_datawriter(dds::pub::DataWriter* const a_datawriter);
        
        /**
        * @brief This function retrieves a previously created DataWriter belonging to the Publisher that is 
        * attached to a Topic with a matching topic_name.
        * @param [in] a_topic_name A Topic's topic_name.
        * @return Return dds::pub::DataWriter*.
        * @retval DataWriter* If multiple DataWriter attached to the Publisher satisfy this condition, then the operation 
        * will return one of them. It is not specified which one.
        * @retval nullptr  If no such DataWriter exists, the operation will return nullptr.
        */
        dds::pub::DataWriter* lookup_datawriter(std::string const &a_topic_name);
        
        /**
        * @brief This function indicates to the Service that the application is about to make multiple modifications using 
        * DataWriter objects belonging to the Publisher.
        * @details It is a hint to the Service so it can optimize its performance by e.g., holding the dissemination of the 
        * modifications and then batching them.
        * @return Return DDS::ReturnCode_t.
        * @retval RETCODE_OK  It is successful to suspend  Publications.
        * @todo
        */
        DDS::ReturnCode_t suspend_publications() const noexcept;
        
        /**
        * @brief This function indicates to the Service that the application has completed the multiple changes initiated 
        * by the previous suspend_publications.
        * @return Return DDS::ReturnCode_t.
        * @retval RETCODE_OK  It is successful to resume Publications.
        * @retval RETCODE_PRECONDITION_NOT_MET The call to resume_publications must match a previous call to suspend_publications. 
        * Otherwise the operation will return the error RETCODE_PRECONDITION_NOT_MET.
        * @todo
        */
        DDS::ReturnCode_t resume_publications() const noexcept;
        
        /**
        * @brief This function requests that the application will begin a ‘coherent set’ of modifications using DataWriter objects 
        * attached to the Publisher.
        * @details The ‘coherent set’ will be completed by a matching call to end_coherent_changes.
        * @return Return DDS::ReturnCode_t.
        * @retval RETCODE_OK It is successful to begin coherent changes.
        * @todo
        */
        DDS::ReturnCode_t begin_coherent_changes() const noexcept;
        
        /**
        * @brief This function terminates the ‘coherent set’ initiated by the matching call to begin_coherent_ changes. 
        * @return Return DDS::ReturnCode_t.
        * @retval RETCODE_OK It is successful to end coherent changes.
        * @retval RETCODE_PRECONDITION_NOT_MET  If there is no matching call to begin_coherent_ changes, the operation will return 
        * the error PRECONDITION_NOT_MET; Possible error codes returned in addition to the standard ones: PRECONDITION_NOT_MET.
        * @todo
        */
        DDS::ReturnCode_t end_coherent_changes() const noexcept;
        
        /**
        * @brief This function blocks the calling thread until either all data written by the reliable DataWriter entities 
        * is acknowledged by all matched reliable DataReader entities, or else the duration specified by the max_wait 
        * parameter elapses, whichever happens first.
        * @return Return DDS::ReturnCode_t.
        * @retval RETCODE_OK  All the samples written have been acknowledged by all reliable matched data readers.
        * @retval RETCODE_TIMEOUT  max_wait elapsed before all the data was acknowledged.
        */
        DDS::ReturnCode_t wait_for_acknowledgements() const noexcept;
        
        /**
        * @brief This function returns the DomainParticipant to which the Publisher belongs.
        * @return Return DomainParticipant* which the publisher belongs.
        */
        dds::domain::DomainParticipant* get_participant() const noexcept;
        
        /**
        * @brief This function deletes all the entities that were created by means of the “create” operations on the Publisher.
        * @return Return DDS::ReturnCode_t.
        * @retval RETCODE_PRECONDITION_NOT_MET  There is any of the contained entities is in a state where it cannot be deleted.
        * @retval RETCODE_OK  It is successful to delete contained entities.
        */
        DDS::ReturnCode_t delete_contained_entities();
        
        /**
        * @brief This function sets the default DataWriterQos values for this DomainParticipant.
        * @param [in] a_qos Const reference of a DataWriterQos object.
        * @return Return DDS::ReturnCode_t.
        * @retval RETCODE_OK It is successful to set default datawriter qos.
        * @retval RETCODE_INCONSISTENT_POLICY This operation will check that the resulting policies are self consistent; if they are not, 
        * the operation will have no effect and return INCONSISTENT_POLICY.
        */
        DDS::ReturnCode_t set_default_datawriter_qos(DataWriterQos const &a_qos) noexcept;
        
        /**
        * @brief This function retrieves the default DataWriterQos values for this DomainParticipant.
        * @param [in,out] a_qos Reference of a DataWriterQos object.
        * @return Return DDS::ReturnCode_t.
        * @retval RETCODE_OK It is successful to get default datawriter qos.
        */
        DDS::ReturnCode_t get_default_datawriter_qos(DataWriterQos& a_qos) const noexcept;
        
        /**
        * @brief This function Copies the policies in the TopicQos to the corresponding policies in the DataWriterQos.
        * @param [in,out] a_datawriter_qos Reference of a DataWriterQos object.
        * @param [in] a_topic_qos Const reference of a TopicQos object.
        * @return Return DDS::ReturnCode_t.
        * @retval RETCODE_NOT_ENABLED If DataWriterQos' ReliabilityQosPolicy is not same as TopicQos' ReliabilityQosPolicy the function will return RETCODE_NOT_ENABLED.
        * @retval RETCODE_OK It is successful to copy the policies.
        * @todo
        */
        DDS::ReturnCode_t copy_from_topic_qos(DataWriterQos const &a_datawriter_qos, dds::topic::TopicQos const &a_topic_qos) const noexcept;
        
        /**
        * @brief This function installs this Publisher's Listener and communication status mask.
        * @param [in] a_listener A pointer of Listener.
        * @param [in] a_mask Communication status mask.
        * @return Return DDS::ReturnCode_t.
        * @retval RETCODE_PRECONDITION_NOT_MET Calling enable on an Entity whose factory is not enabled will fail and return PRECONDITION_NOT_MET.
        * @retval RETCODE_OK It is successful to set listener.
        */
        DDS::ReturnCode_t set_listener(dds::core::Listener* a_listener, DDS::StatusMask a_mask) noexcept override;
        
        /**
        * @brief This function accesses to the existing Listener attached to the Publisher.
        * @return Return a pointer of Listener.
        */
        dds::core::Listener* get_listener() noexcept override;
        
        /**
        * @brief This function accesses to the existing StatusCondition attached to the Publisher.
        * @return Return StatusCondition*.
        */
        dds::core::StatusCondition* get_statuscondition() noexcept override;
        
        /**
        * @brief This function retrieves the communication statuses mask in the Publisher that are 'triggered'.
        * @details The statuses mask whose value has changed since the last time the application read the status.
        * @return Return communication statuses mask.
        */
        DDS::StatusMask get_status_changes() noexcept override;
        
        /**
        * @brief This function enables the Publisher used for ENTITY_FACTORY Qos policy.
        * @return Return DDS::ReturnCode_t.
        * @retval RETCODE_OK It is successful to enable publisher.
        * @retval RETCODE_PRECONDITION_NOT_MET Calling enable on an Entity whose factory is not enabled will fail 
        * and return PRECONDITION_NOT_MET.
        */
        DDS::ReturnCode_t enable() noexcept override;
        
        /**
        * @brief This function returns the InstanceHandle_t that represents the Publisher.
        * @return Return InstanceHandle_t.
        */
        gstone::rtps::InstanceHandle_t get_instance_handle() noexcept override;

    protected:
        /**
        * @brief Constructor of the class Publisher by another Publisher object.
        * @param [in] a_info Const reference of a Publisher object.
        */
        Publisher(Publisher const&a_info) = default;
        
        /**
        * @brief Assign a Publisher object to the locally Publisher object.
        * @param [in] a_info Const reference of a Publisher object.
        * @return Reference of the Publisher object.
        */
        Publisher& operator=(Publisher const&a_info) = default;
        
        /**
        * @brief Move constructor of the class Publisher.
        * @param [in] a_info Rvalue reference of a Publisher object.
        */
        Publisher(Publisher&&a_info) = default;
        
        /**
        * @brief Move assignment of the class Publisher.
        * @param [in] a_info Rvalue reference of a Publisher object.
        * @return Reference of the Publisher object.
        */
        Publisher& operator=(Publisher&&a_info) = default;

    private:
        gstone::pub::PublisherDelegate* m_delegate;
    };
}/*pub*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_TPUBLISHER_API_H*/
