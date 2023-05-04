/**************************************************************
* @file WaitSet.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_WAITSET_API_H
#define GSTONE_WAITSET_API_H 1

#include <vector>
#include "dcps/DdsBaseTypes.h"
#include "dcps/core/Condition.h"
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace core {
class WaitSetDelegate;
}  /*core*/
}  /*gstone*/

namespace dds {
namespace core {
using ConditionSeq = std::vector<dds::core::Condition*>;
/**
* @class WaitSet
* @brief A WaitSet object allows an application to wait until one or more of the attached Condition objects has a trigger_value of TRUE or else until the timeout expires.
* @note WaitSet has no factory. It is created as an object directly by the natural means in each language binding.
*/
class GS_DDS4CPP_API WaitSet
{
public:
    /**
     * @brief Construct a new WaitSet object with default parameter.
     */
    WaitSet();

    /**
     * @brief Destroy the WaitSet object.
     */
    virtual ~WaitSet() = default;

    /**
     * @brief Construct a new WaitSet object with copying WaitSet object.
     * @param [in] WaitSet A new WaitSet object is created by copying this WaitSet object.
     */
    WaitSet(WaitSet const &) = default;

    /**
     * @brief Construct a new Base Status object with moving WaitSet object.
     * @param [in] WaitSet A new WaitSet object is created by moving this WaitSet object.
     */
    WaitSet(WaitSet &&) = default;

    /**
     * @brief Copy a WaitSet object with a WaitSet object.
     * @param [in] WaitSet The WaitSet object that need to copy.
     * @return WaitSet object that after copying.
     */
    WaitSet &operator=(WaitSet const &) = default;

    /**
     * @brief Move a WaitSet object with a WaitSet object.
     * @param [in] WaitSet The WaitSet object that need to copy.
     * @return WaitSet object that after moving.
     */
    WaitSet &operator=(WaitSet &&) = default;

    /**
     * @brief This operation detaches a condition from the WaitSet.
     * @param [in] a_condition The condition that need to be detached.
     * @return DDS state code. 
     * @retval RETCODE_OK                   Detaching a condition from the WaitSet successfully.
     * @retval RETCODE_PRECONDITION_NOT_MET Detaching a condition from the WaitSet failed.
     */
    DDS::ReturnCode_t detach_condition(dds::core::Condition const* const a_condition);

    /**
     * @brief This operation attaches a condition to the WaitSet.
     * @param [in] a_condition The condition that need to be attach.
     * @return DDS status code. 
     * @retval RETCODE_OK            Attaching a condition to the WaitSet successfully.
     * @retval RETCODE_BAD_PARAMETER Inputing a_condition is NULL.
     * @note Adding a condition that is already attached to the WaitSet has no effect.
     */
    DDS::ReturnCode_t attach_condition(dds::core::Condition* const a_condition);

    /**
     * @brief This operation allows an application thread to wait for the occurrence of certain conditions.
     * @param [in] active_conditions The condition that had been attached.
     * @param [in] timeout The maximum duration for the wait.
     * @return DDS status code. 
     * @retval RETCODE_OK                   Waitting for the occurrence of certain conditions successfully.
     * @retval RETCODE_BAD_PARAMETER        The value of timeout less 1ms.
     * @retval RETCODE_NO_DATA              The condition is empty.
     * @retval RETCODE_PRECONDITION_NOT_MET Already having a thread blocking on it.
     * @retval RETCODE_TIMEOUT              Waitting timeout for the occurrence of certain conditions.
     * @note If the wait operation is invoked on a WaitSet that already has a thread blocking on it, 
     * the operation will return immediately with the value PRECONDITION_NOT_MET.
     */
    DDS::ReturnCode_t wait(ConditionSeq &active_conditions, gstone::rtps::Duration_t const &timeout);

    /**
     * @brief This operation retrieves the list of attached conditions.
     * @param [in,out] attached_conditions The list of attached conditions receives the return value.
     * @return DDS status code. 
     * @retval RETCODE_OK Retrieves the list of attached conditions successfully.
     * @note The attached conditions will assign to attached_conditions.
     */
    DDS::ReturnCode_t get_conditions(ConditionSeq &attached_conditions);
private:
    std::shared_ptr<gstone::core::WaitSetDelegate> m_delegate;
};
} /*core*/
} /*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_WAITSET_API_H*/
