/**************************************************************
* @file QueryCondition.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_QUERYCONDITION_API_H
#define GSTONE_QUERYCONDITION_API_H 1

#include <vector>
#include "swiftdds/dcps/DeclExport.h"
#include "swiftdds/dcps/core/Condition.h"
#include "swiftdds/dcps/core/CoreTypes.h"
#include "swiftdds/dcps/core/ForwardDeclaration.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace core {
class QueryConditionDelegate;
} /*core*/
} /*gstone*/

namespace dds {
namespace core {
/**
* @class QueryCondition
* @brief QueryCondition objects are specialized ReadCondition objects that allow the application to also specify a filter on the locally available data.
*/
class GS_DDS4CPP_API QueryCondition : public dds::core::Condition
{
public:
    /**
     * @brief Do not use this operation to construct a new QueryCondition object with default parameter.
     */
    QueryCondition() = delete;

    /**
     * @brief Construct a new QueryCondition object.
     * @param [in] reader            The pointer of DataReader object.
     * @param [in] sample_mask       The mask of sample.
     * @param [in] view_mask         The mask of view.
     * @param [in] instance_mask     The mask of instance.
     * @param [in] query_expression  The expression of query.
     * @param [in] query_parameters  The parameters of query.
     */
    QueryCondition(dds::sub::DataReader* reader, DDS::SampleStateMask sample_mask, DDS::ViewStateMask view_mask,
                   DDS::InstanceStateMask instance_mask, std::string const &query_expression,
                   dds::core::StringSeq const &query_parameters);

    /**
     * @brief Construct a new QueryCondition object with copying QueryCondition object.
     * @param [in] a_query_condition A new QueryCondition object is created by copying this QueryCondition object.
     */
    QueryCondition(QueryCondition const & a_query_condition) = default;

    /**
     * @brief Construct a new Base Status object with moving QueryCondition object.
     * @param [in] a_query_condition A new QueryCondition object is created by moving this QueryCondition object.
     */
    QueryCondition(QueryCondition && a_query_condition) = default;

    /**
     * @brief Copy a QueryCondition object with a QueryCondition object.
     * @param [in] a_query_condition The QueryCondition object that need to copy.
     * @return QueryCondition object that after copying.
     */
    QueryCondition &operator=(QueryCondition const & a_query_condition) = default;

    /**
     * @brief Move a QueryCondition object with a QueryCondition object.
     * @param [in] a_query_condition The QueryCondition object that need to move.
     * @return QueryCondition object that after moving.
     */
    QueryCondition &operator=(QueryCondition && a_query_condition) = default;

    /**
     * @brief Destroy the QueryCondition object
     */
    ~QueryCondition() noexcept override;

    /**
     * @brief This operation gets the trigger value object.
     * @return Gets the trigger value object result.
     * @retval true Getting successfully.
     * @retval false Getting failed.
     */
    gbool_t get_trigger_value() const noexcept override;

    /**
     * @brief This operation gets the datareader object.
     * @return The datareader object.
     */
    dds::sub::DataReader* get_datareader() const noexcept;

    /**
     * @brief This operation gets the sample state mask object.
     * @return The sample state mask object.
     */
    DDS::SampleStateMask get_sample_state_mask() const noexcept;

    /**
     * @brief This operation gets the view state mask object.
     * @return The view state mask object.
     */
    DDS::ViewStateMask get_view_state_mask() const noexcept;

    /**
     * @brief This operation gets the instance state mask object.
     * @return The instance state mask object.
     */
    DDS::InstanceStateMask get_instance_state_mask() const noexcept;

    /**
     * @brief This operation returns the query_expression associated with the QueryCondition.
     * @return The query_expression associated with the QueryCondition.
     */
    std::string get_query_expression() const noexcept;

    /**
     * @brief This operation returns the query_parameters associated with the QueryCondition.
     * @param [in] query_parameters The query_parameters associated with the QueryCondition.
     * @return DDS state code.
     * @retval RETCODE_OK Getting the query_parameters associated with the QueryCondition successfully.
     */
    DDS::ReturnCode_t get_query_parameters(dds::core::StringSeq &query_parameters) const noexcept;

    /**
     * @brief This operation changes the query_parameters associated with the QueryCondition.
     * @param [in] query_parameters The query_parameters associated with the QueryCondition.
     * @return DDS state code. 
     * @retval RETCODE_OK Setting the query_parameters associated with the QueryCondition successfully.
     */
    DDS::ReturnCode_t set_query_parameters(dds::core::StringSeq const &query_parameters) const noexcept;
private:
    gstone::core::QueryConditionDelegate* m_delegate;
};
} /*core*/
} /*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_QUERYCONDITION_API_H*/
