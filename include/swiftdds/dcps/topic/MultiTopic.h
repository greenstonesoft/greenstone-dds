/**************************************************************
* @file MutiTopic.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_MULTITOPIC_API_H
#define GSTONE_MULTITOPIC_API_H 1

#include "swiftdds/dcps/topic/Topic.h"
#include "swiftdds/dcps/topic/TopicDescription.h"
#include "swiftdds/dcps/core/CoreTypes.h"
#include "swiftdds/dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace topic
{
    class MultiTopic;
    /**
     * @class MultiTopic
     * @brief MultiTopic is a specialization of TopicDescription that allows subscriptions to combine/filter/rearrange data coming from 
     *        several topics
     */
    class GS_DDS4CPP_API MultiTopic : public dds::topic::TopicDescription
    {
    public:
        /**
         * @brief Constructer of the MultiTopic class.
         */
        MultiTopic() = default;
        
        /**
         * @brief Constructor of the class MultiTopic by another Publisher object.
         * @param [in] other Const reference of a MultiTopic object.
         */
        MultiTopic(MultiTopic const& other) = default;
        
        /**
         * @brief Move constructor of the class MultiTopic.
         * @param [in] other Rvalue reference of this MultiTopic object.
         */
        MultiTopic(MultiTopic&& other) = default;
        
        /**
         * @brief Assign a MultiTopic object to the current MultiTopic object.
         * @param [in] ohter Const reference of a MultiTopic object.
         * @return Reference of this MultiTopic object.
         */
        MultiTopic& operator=(MultiTopic const& other) = default;
        
        /**
         * @brief Move assignment of the class MultiTopic.
         * @param [in] other Rvalue reference of this MultiTopic object.
         * @return Reference of this MultiTopic object.
         */
        MultiTopic& operator=(MultiTopic&& other) = default;

        /**
         * @brief This operation returns the expression_parameters associated with the MultiTopic.
         * @param [in,out] expression_parameters A sequence of strings that give values to the 'parameters' (i.e., "%n" tokens) in the filter_expression
         * @return Return RETCODE_OK if success.
         * @retval Successfully returns the expression_parameters associated with the MultiTopic.
         * @todo
         */
        virtual DDS::ReturnCode_t get_expression_parameters(dds::core::StringSeq& expression_parameters) = 0;
        
        /**
         * @brief This function changes the expression_parameters associated with the MultiTopic.
         * @param [in] expression_parameters A sequence of strings that give values to the 'parameters' (i.e., "%n" tokens) in the filter_expression
         * @return Return RETCODE_OK if success.
         * @retval RETCODE_OK Successfully changes the expression_parameters associated with the MultiTopic.
         * @todo
         */
        virtual DDS::ReturnCode_t set_expression_parameters(dds::core::StringSeq& expression_parameters) = 0;
    protected:
        /**
         * @brief Destructer of the MultiTopic class.
         */
        ~MultiTopic() override = default;
    private:
        std::string m_subscriptions;
    };
}/*topic*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_MULTITOPIC_API_H*/
