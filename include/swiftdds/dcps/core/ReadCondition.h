/**************************************************************
* @file ReadCondition.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_READCONDITION_API_H
#define GSTONE_READCONDITION_API_H 1

#include "swiftdds/dcps/core/Condition.h"
#include "swiftdds/dcps/DeclExport.h"
#include "swiftdds/dcps/core/ForwardDeclaration.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace core {
class ReadConditionDelegate;
} /*core*/
} /*gstone*/

namespace dds {
namespace core {
/**
* @class ReadCondition
* @brief ReadCondition objects are conditions specifically dedicated to read operations and attached to one DataReader.
* @note More than one ReadCondition may be attached to the same DataReader.
*/
class GS_DDS4CPP_API ReadCondition : public dds::core::Condition
{
public:
    /**
     * @brief Do not use this operation to construct a new ReadCondition object with default parameter.
     */
    ReadCondition() = delete;

    /**
     * @brief Construct a new ReadCondition object attached to one DataReader.
     * @param [in] DataReader*    The pointer of DataReader object.
     * @param [in] SampleStateMask   The mask of sample.
     * @param [in] ViewStateMask     The mask of view.
     * @param [in] InstanceStateMask The mask of instance.
     */
    ReadCondition(dds::sub::DataReader*, DDS::SampleStateMask, DDS::ViewStateMask, DDS::InstanceStateMask);

    /**
     * @brief Construct a new ReadCondition object with copying ReadCondition object.
     * @param [in] a_read_condition A new ReadCondition object is created by copying this ReadCondition object.
     */
    ReadCondition(ReadCondition const & a_read_condition) = default;

    /**
     * @brief Construct a new Base Status object with moving ReadCondition object.
     * @param [in] a_read_condition A new ReadCondition object is created by moving this ReadCondition object.
     */
    ReadCondition(ReadCondition && a_read_condition) = default;

    /**
     * @brief Copy a ReadCondition object with a ReadCondition object.
     * @param [in] a_read_condition The ReadCondition object that need to copy.
     * @return ReadCondition object that after copying.
     */
    ReadCondition &operator=(ReadCondition const & a_read_condition) = default;

    /**
     * @brief Move a ReadCondition object with a ReadCondition object.
     * @param [in] a_read_condition The ReadCondition object that need to move.
     * @return ReadCondition object that after moving.
     */
    ReadCondition &operator=(ReadCondition && a_read_condition) = default;

    /**
     * @brief Destroy the ReadCondition object.
     */
    ~ReadCondition() noexcept override;

    /**
     * @brief This operation gets the trigger value object.
     * @return Gets the trigger value object result.
     * @retval true Getting successfully.
     * @retval false Getting failed. 
     */
    gbool_t get_trigger_value() const noexcept override;

    /**
     * @brief This operation returns the DataReader associated with the ReadCondition.
     * @return The DataReader associated with the ReadCondition.
     */
    virtual dds::sub::DataReader* get_datareader() const noexcept;

    /**
     * @brief This operation notices entity to wake up according to StatusCondition.
     */
    gvoid_t notify(DDS::SampleStateKind const sampleKind, DDS::InstanceStateKind const instanceKind, DDS::ViewStateKind const viewKind) const noexcept;

    /**
     * @brief This operation returns the set of sample-states that are taken into account to determine the trigger_value of the ReadCondition.
     * @return The sample-states that are taken into account to determine the trigger_value of the ReadCondition. 
     */
    virtual DDS::SampleStateMask get_sample_state_mask() const noexcept;

    /**
     * @brief This operation returns the set of view-states that are taken into account to determine the trigger_value of the ReadCondition.
     * @return The view-states that are taken into account to determine the trigger_value of the ReadCondition. 
     */
    virtual DDS::ViewStateMask get_view_state_mask() const noexcept;

    /**
     * @brief This operation returns the set of instance-states that are taken into account to determine the trigger_value of the ReadCondition.
     * @return The instance-states that are taken into account to determine the trigger_value of the ReadCondition. 
     */
    virtual DDS::InstanceStateMask get_instance_state_mask() const noexcept;
private:
    gstone::core::ReadConditionDelegate *m_delegate;
};
} /*core*/
} /*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_READCONDITION_API_H*/
