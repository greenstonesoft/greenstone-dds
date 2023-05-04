/**************************************************************
* @file Condition.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_CONDITION_API_H
#define GSTONE_CONDITION_API_H 1

#include "dcps/DdsBaseTypes.h"
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace core {
class ConditionDelegate;
class WaitSetDelegate;
} /*core*/
} /*gstone*/

namespace dds {
namespace core {
/**
* @class Condition
* @brief A Condition is a root class for all the conditions that may be attached to a WaitSet.
* @note A Condition has a trigger_value that can be TRUE or FALSE and is set automatically by the Service.
*/
class GS_DDS4CPP_API Condition
{
public:
    /**
     * @brief Construct a new Condition object with default parameter.
     */
    Condition() = default;

    /**
     * @brief Destroy the Condition object.
     */
    virtual ~Condition() noexcept = default;

    /**
     * @brief This operation retrieves the trigger_value of the Condition.
     * @return Getting the trigger_value of the Condition result.
     * @retval true Getting the trigger_value of the Condition successfully.
     * @retval false Getting the trigger_value of the Condition failed.
     * @note The trigger_value is set automatically by the Service.
     */
    virtual gbool_t get_trigger_value() const noexcept = 0;

    /**
     * @brief This operation gets the ConditionDelegate of the Condition.
     * @return The ConditionDelegate of the Condition. 
     * @note ConditionDelegate is used for specific implementation.
     */
    inline std::shared_ptr<gstone::core::ConditionDelegate> delegate() const noexcept
    {
        return m_delegate;
    };

    /**
     * @brief This operation sets the ConditionDelegate of the Condition.
     * @param [in] value The ConditionDelegate of the Condition.
     * @note ConditionDelegate is used for specific implementation.
     */
    inline gvoid_t delegate(std::shared_ptr<gstone::core::ConditionDelegate> const value) noexcept
    {
        m_delegate = value;
    }

protected:
    /**
     * @brief Construct a new Condition object with copying Condition object.
     * @param [in] a_condition A new Condition object is created by copying this Condition object.
     */
    Condition(Condition const& a_condition) = default;

    /**
     * @brief Construct a new Base Status object with moving Condition object.
     * @param [in] a_condition A new Condition object is created by moving this Condition object.
     */
    Condition(Condition && a_condition) = default;

    /**
     * @brief Copy a Condition object with a Condition object.
     * @param [in] a_condition The Condition object that need to copy.
     * @return Condition object that after copying.
     */
    Condition& operator=(Condition const& a_condition) = default;

    /**
     * @brief Move a Condition object with a Condition object.
     * @param [in] a_condition The Condition object that need to move.
     * @return Condition object that after moving.
     */
    Condition& operator=(Condition && a_condition) = default;

private:
    std::shared_ptr<gstone::core::ConditionDelegate> m_delegate;
};
} /*core*/
} /*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_CONDITION_API_H*/
