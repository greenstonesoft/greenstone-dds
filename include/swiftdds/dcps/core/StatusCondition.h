/**************************************************************
* @file StatusCondition.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_StatusCondition_API_H
#define GSTONE_StatusCondition_API_H 1

#include "swiftdds/dcps/core/Entity.h"
#include "swiftdds/dcps/DeclExport.h"
#include "swiftdds/dcps/core/Condition.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace core {
class StatusConditionDelegate;
class EntityDelegate;
} /*core*/
} /*gstone*/

namespace dds {
namespace core {
/**
* @class StatusCondition
* @brief A StatusCondition object is a specific Condition that is associated with each Entity.
*/
class GS_DDS4CPP_API StatusCondition : public dds::core::Condition
{
public:
    /**
     * @brief Do not use this operation to construct a new StatusCondition object with default parameter.
     */
    StatusCondition() = delete;

    /**
     * @brief Construct a new StatusCondition object with entity object.
     * @param [in] Entity The entity that the StatusCondition associated.
     */
    StatusCondition(dds::core::Entity_ptr);

    /**
     * @brief Destroy the StatusCondition object.
     */
    ~StatusCondition() noexcept override;

    /**
     * @brief Construct a new StatusCondition object with copying StatusCondition object.
     * @param [in] a_status_condition A new StatusCondition object is created by copying this StatusCondition object.
     */
    StatusCondition(StatusCondition const & a_status_condition) = default;

    /**
     * @brief Construct a new Base Status object with moving StatusCondition object.
     * @param [in] a_status_condition A new StatusCondition object is created by moving this StatusCondition object.
     */
    StatusCondition(StatusCondition && a_status_condition) = default;

    /**
     * @brief Copy a StatusCondition object with a StatusCondition object.
     * @param [in] a_status_condition The StatusCondition object that need to copy.
     * @return StatusCondition object that after copying.
     */
    StatusCondition &operator=(StatusCondition const & a_status_condition) = default;

    /**
     * @brief Move a StatusCondition object with a StatusCondition object.
     * @param [in] a_status_condition The StatusCondition object that need to move.
     * @return StatusCondition object that after moving.
     */
    StatusCondition &operator=(StatusCondition && a_status_condition) = default;

    /**
     * @brief This operation gets the trigger value object
     * @return Gets the trigger value object result.
     * @retval true Getting successfully.
     * @retval false Getting failed. 
     */
    gbool_t get_trigger_value() const noexcept override;

    /**
     * @brief This operation defines the list of communication statuses that are taken into account to determine the trigger_value of the StatusCondition.
     * @param [in] mask The statuses that are taken into account to determine the trigger_value of the StatusCondition.
     * @return DDS state code. 
     * @retval RETCODE_OK Setting successfully. 
     */
    DDS::ReturnCode_t set_enabled_statuses(DDS::StatusMask const &mask) noexcept;

    /**
     * @brief This operation retrieves the list of communication statuses that are taken into account to determine the trigger_value of the StatusCondition.
     * @return The statuses that are taken into account to determine the trigger_value of the StatusCondition. 
     */
    DDS::StatusMask get_enabled_statuses() const noexcept;

    /**
     * @brief This operation returns the Entity associated with the StatusCondition.
     * @return The Entity associated with the StatusCondition. 
     */
    dds::core::Entity_ptr get_entity() const noexcept;

    /**
     * @brief This operation notices entity to wake up according to StatusCondition.
     */
    gvoid_t notify() const noexcept;

    /**
     * @brief Get entity type.
     */
    DDS::EntityType kind() const noexcept {return m_kind;}

    /**
     * @brief Set entity type.
     */
    gvoid_t kind(DDS::EntityType const type) noexcept {m_kind = type;}
private:
    DDS::EntityType m_kind;
    gstone::core::StatusConditionDelegate *m_delegate;
};
} /*core*/
} /*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_StatusCondition_API_H*/
