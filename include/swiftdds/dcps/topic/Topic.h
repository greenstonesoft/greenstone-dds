/**************************************************************
* @file Topic.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_TOPIC_API_H
#define GSTONE_TOPIC_API_H 1

#include "swiftdds/dcps/core/Entity.h"
#include "swiftdds/dcps/core/ForwardDeclaration.h"
#include "swiftdds/dcps/topic/TopicListener.h"
#include "swiftdds/dcps/core/Status.h"
#include "swiftdds/dcps/topic/TopicQos.h"
#include "swiftdds/dcps/topic/TopicDescription.h"


__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
    namespace topic {
        class TopicDelegate;
    }
}

namespace dds
{
namespace topic
{
    /**
     * @class Topic
     * @brief Topic is the most basic description of the data to be published and subscribed.
     *        A Topic is identified by its name, which must be unique in the whole Domain. In addition (by virtue of extending TopicDescription)
     *        it fully specifies the type of the data that can be communicated when publishing or subscribing to the Topic.
     */
    class GS_DDS4CPP_API Topic : public dds::core::Entity, public dds::topic::TopicDescription
    {
    public:
        /**
         * @brief Nno-parameter constructer of the Topic class is deleted.
         */
        Topic() = delete;

        /**
         * @brief Constructer of the Topic class.
         * @param [in] a_delegate Pointer to TopicDelegate.
         */
        Topic(gstone::topic::TopicDelegate* const a_delegate) noexcept;

        /**
         * @brief Deconstructer of the Topic class.
         */
        ~Topic() override = default;

        /**
         * @brief This function is used to set the QoS policies of the Entity.
         * @param [in] in_qos The TopicQos object to be set to.
         * @return DDS::ReturnCode_t.
         * @retval RETCODE_OK Successfully set the QoS policies of the Entity.
         * @retval RETCODE_IMMUTABLE_POLICY Supported QoS, certain policies are "immutable;" they can only be set at Entity creation time, or
         *         before the entity is made enabled. If set_qos is invoked after the Entity is enabled and it attempts to change the value of an
         *         "immutable" policy, the operation will fail and it returns IMMUTABLE_POLICY.
         * @retval RETCODE_INCONSISTENT_POLICY Supported QoS also describes that certain values of QoS policies can be incompatible with the
         *         settings of the other policies. The set_qos operation will also fail if it specifies a set of values that once combined with the
         *         existing values would result in an inconsistent set of policies. In this case, the return value is INCONSISTENT_POLICY.
         * @retval RETCODE_UNSUPPORTED If the application supplies a non-default value for a QoS policy that is not supported by the implementation
         *         of the service, the set_qos operation will fail and return UNSUPPORTED.
         */
        DDS::ReturnCode_t set_qos(TopicQos const& in_qos);

        /**
         * @brief This function allows access to the existing set of QoS policies for the Entity.
         * @param [in,out] out_qos The TopicQos object get from Topic object.
         * @return DDS::ReturnCode_t.
         * @retval RETCODE_OK Successfully access to the existing set of QoS policies for the Entity.
         */
        DDS::ReturnCode_t get_qos(TopicQos& out_qos) const;

        /**
         * @brief This function allows the application to retrieve the INCONSISTENT_TOPIC status of the Topic.
         * @param [in,out] status Status to be retrieved.
         * @return DDS::ReturnCode_t.
         * @retval RETCODE_OK Successfully get the INCONSISTENT_TOPIC status of the Topic.
         */
        DDS::ReturnCode_t get_inconsistent_topic_status(dds::core::InconsistentTopicStatus& status);

        /**
         * @brief This function installs a Listener on the Entity.
         * @param [in] listener The listener object to be set to.
         * @param [in] mask StatusMask that holds statuses the listener responds to.
         * @return DDS::ReturnCode_t.
         * @retval RETCODE_OK The Entity is enabled.
         * @retval RETCODE_PRECONDITION_NOT_MET The Entity is not enabled.
         */
        DDS::ReturnCode_t set_listener(dds::core::Listener* listener, DDS::StatusMask mask) noexcept override;

        /**
         * @brief This function allows access to the existing Listener attached to the Entity.
         * @return The listener attached to the Entity.
         */
        dds::core::Listener* get_listener() noexcept override;

        /**
         * @brief This function allows access to the StatusCondition associated with the Entity.
         * @return Pointer to the StatusCondition associated with the Entity.
         */
        dds::core::StatusCondition* get_statuscondition() noexcept override;

        /**
         * @brief This operation retrieves the list of communication statuses in the Entity that are 'triggered'.
         * @return Communication statuses in the Entity that are 'triggered'.
         */
        DDS::StatusMask get_status_changes() noexcept override;

        /**
         * @brief This function enables the Entity.
         * @return DDS::ReturnCode
         * @retval RETCODE_OK The enable operation is idempotent. Calling enable on an already enabled Entity returns OK and has no effect.
         * @retval RETCODE_NOT_ENABLED Other operations may explicitly state that they may be called on disabled entities return the error NOT_ENABLED.
         * @retval RETCODE_PRECONDITION_NOT_MET Calling enable on an Entity whose factory is not enabled will fail and return PRECONDITION_NOT_MET
         */
        DDS::ReturnCode_t enable() noexcept override;

        /**
         * @brief This function returns the InstanceHandle that represents the Entity.
         * @return The InstanceHandle
         */
        gstone::rtps::InstanceHandle_t get_instance_handle() noexcept override;

        /**
         * @brief This function returns the DomainParticipant to which the Topic belongs.
         * @return Pointer to the DomainParticipant.
         */
        dds::domain::DomainParticipant* get_participant() const noexcept override;

        /**
         * @brief This function get the TopicDelegate object.
         * @return Pointer to the TopicDelegate.
         */
        gstone::topic::TopicDelegate* get_delegate() const noexcept;

    protected:
        /**
         * @brief Constructor of the class Topic by another Topic object.
         * @param [in] other Const reference of a Topic object.
         */
        Topic(Topic const& other) = default;

        /**
         * @brief Move constructor of the class Topic by another Topic object.
         * @param [in] other Rvalue reference of a Topic object.
         */
        Topic(Topic&& other) = default;

        /**
         * @brief Assign a Topic object to the locally Topic object.
         * @param [in] other Const reference of this Topic object.
         * @return Reference of this Topic object.
         */
        Topic& operator=(Topic const& other) = default;

        /**
         * @brief Move assignment of the class Topic
         * @param [in] other Rvalue reference of this Topic object.
         * @return Reference of this Topic object.
         */
        Topic& operator=(Topic&& other) = default;

    private:
        gstone::topic::TopicDelegate* m_delegate;
    };
}/*topic*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_TOPIC_API_H*/
