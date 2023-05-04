/**************************************************************
* @file Entity.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_TENTITY_API_H
#define GSTONE_TENTITY_API_H 1

#include "dcps/core/Listener.h"
#include "dcps/core/ForwardDeclaration.h"
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds {
namespace core {
/**
* @class Entity
* @brief This class is the abstract base class for all the DCPS objects that support QoS policies, a listener and a status condition.
* @note Derive classes(DomainParticipant, Topic, Publisher, DataWriter, Subscriber, DataReader).
*/
class GS_DDS4CPP_API Entity
{
public:
    /**
     * @brief Construct a new Entity object with default parameter.
     */
    Entity() = default;

    /**
     * @brief Destroy the Entity object.
     */
    virtual ~Entity() noexcept = default;

    /**
     * @brief This operation installs a Listener on the Entity.
     * @param [in] listener The listener needs to be installed.
     * @param [in] mask The listener will only be invoked on the changes of communication status indicated by the specified mask.
     * @return DDS state code. 
     * @retval RETCODE_OK This operation sets listener successfully.
     * @note It is permitted to use ‘nil’ as the value of the listener.
     * Only one listener can be attached to each Entity.
     * This operation must be provided by each of the derived Entity classes.
     */
    virtual DDS::ReturnCode_t set_listener(dds::core::Listener *listener, DDS::StatusMask mask) = 0;

    /**
     * @brief This operation allows access to the existing Listener attached to the Entity.
     * @return The existing Listener attached to the Entity.
     * @note This operation must be provided by each of the derived Entity classes.
     */
    virtual dds::core::Listener *get_listener() = 0;

    /**
     * @brief This operation allows access to the StatusCondition associated with the Entity.
     * @return The StatusCondition associated with the Entity. 
     * @note This operation must be provided by each of the derived Entity classes.
     */
    virtual dds::core::StatusCondition* get_statuscondition() = 0;

    /**
     * @brief This operation retrieves the list of communication statuses in the Entity that are ‘triggered.’
     * @return The list of statuses whose value has changed since the last time. 
     * @note This operation must be provided by each of the derived Entity classes.
     */
    virtual DDS::StatusMask get_status_changes() = 0;

    /**
     * @brief This operation enables the Entity.
     * @return DDS state code. 
     * @retval RETCODE_OK This operation enables entity successfully.
     * @note This operation must be provided by each of the derived Entity classes.
     */
    virtual DDS::ReturnCode_t enable() = 0;

    /**
     * @brief This operation returns the InstanceHandle_t that represents the Entity.
     * @return The InstanceHandle_t that represents the Entity. 
     * @note This operation must be provided by each of the derived Entity classes.
     */
    virtual gstone::rtps::InstanceHandle_t get_instance_handle() = 0;

protected:
    /**
     * @brief Construct a new Entity object with copying Entity object.
     * @param [in] an_entity A new Entity object is created by copying this Entity object.
     */
    Entity(Entity const& an_entity) = default;

    /**
     * @brief Construct a new Base Status object with moving Entity object.
     * @param [in] an_entity A new Entity object is created by moving this Entity object.
     */
    Entity(Entity&& an_entity) = default;

    /**
     * @brief Copy a Entity object with a Entity object.
     * @param [in] an_entity The Entity object that need to copy.
     * @return Entity object that after copying.
     */
    Entity& operator=(Entity const& an_entity) = default;

    /**
     * @brief Move a Entity object with a Entity object.
     * @param [in] an_entity The Entity object that need to move.
     * @return Entity object that after moving.
     */
    Entity& operator=(Entity&& an_entity) = default;
};
using Entity_ptr = Entity *;
} /*core*/
} /*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_TENTITY_API_H*/
