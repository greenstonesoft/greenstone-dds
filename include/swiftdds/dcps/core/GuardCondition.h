/**************************************************************
* @file GuardCondition.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_GUARD_CONDITION_API_H
#define GSTONE_GUARD_CONDITION_API_H 1

#include "swiftdds/dcps/DeclExport.h"
#include "swiftdds/dcps/core/Condition.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace core {
class GuardConditionDelegate;
class WaitSetDelegate;
} /*core*/
} /*gstone*/

namespace dds {
namespace core {
/**
* @class GuardCondition
* @brief A GuardCondition object is a specific Condition whose trigger_value is completely under the control of the application.
* @note  GuardCondition has no factory. It is created as an object directly by the natural means in each language binding.
*/
class GS_DDS4CPP_API GuardCondition : public dds::core::Condition
{
public:
    /**
     * @brief Construct a new GuardCondition object with default parameter.
     */
    GuardCondition() noexcept;

    /**
     * @brief Construct a new GuardCondition object with copying GuardCondition object.
     * @param [in] a_guard_condition A new GuardCondition object is created by copying this GuardCondition object.
     */
    GuardCondition(GuardCondition const & a_guard_condition) = default;

    /**
     * @brief Construct a new Base Status object with moving GuardCondition object.
     * @param [in] a_guard_condition A new GuardCondition object is created by moving this GuardCondition object.
     */
    GuardCondition(GuardCondition && a_guard_condition) = default;

    /**
     * @brief Copy a GuardCondition object with a GuardCondition object.
     * @param [in] a_guard_condition The GuardCondition object that need to copy.
     * @return GuardCondition object that after copying.
     */
    GuardCondition &operator=(GuardCondition const & a_guard_condition) = default;

    /**
     * @brief Move a GuardCondition object with a GuardCondition object.
     * @param [in] a_guard_condition The GuardCondition object that need to move.
     * @return GuardCondition object that after moving.
     */
    GuardCondition &operator=(GuardCondition && a_guard_condition) = default;

    /**
     * @brief Destroy the GuardCondition object.
     */
    ~GuardCondition() noexcept override;

    /**
     * @brief This operation gets the trigger value object
     * @return Gets the trigger value object result.
     * @retval true Getting successfully.
     * @retval false Getting failed.
     */
    gbool_t get_trigger_value() const noexcept override;

    /**
     * @brief This operation sets the trigger value object.
     * @param [in] value The trigger value object.
     * @return DDS state code.
     * @retval RETCODE_OK Setting the trigger value object successfully.
     */
    DDS::ReturnCode_t set_trigger_value(gbool_t const value) noexcept;
private:
    gstone::core::GuardConditionDelegate* m_delegate{ nullptr };
};
} /*core*/
} /*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_GUARDCONDITION_API_H*/
