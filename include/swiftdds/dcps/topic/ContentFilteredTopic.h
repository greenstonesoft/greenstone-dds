/**************************************************************
* @file ContentFilteredTopic.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_CONTENTFILTEREDTOPIC_API_H
#define GSTONE_CONTENTFILTEREDTOPIC_API_H 1

#include "swiftdds/dcps/topic/TopicDescription.h"
#include "swiftdds/dcps/topic/Topic.h"
#include "swiftdds/dcps/core/CoreTypes.h"
#include "swiftdds/dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace topic
{
    class ContentFilteredTopic;

    /**
     * @class ContentFilteredTopic
     * @brief ContentFilteredTopic is a specialization of TopicDescription that allows for content-based subscriptions.
     *        ContentFilteredTopic describes a more sophisticated subscription that indicates the subscriber does not want to necessarily see 
     *        all values of each instance published under the Topic. Rather, it wants to see only the values whose contents satisfy certain 
     *        criteria. This class therefore can be used to request content-based subscriptions.
     */
    class GS_DDS4CPP_API ContentFilteredTopic : public dds::topic::TopicDescription
    {
    public:

        /**
         * @brief Constructer of the ContentFilteredTopic class.
         */
        ContentFilteredTopic() = default;
        
        /**
         * @brief Constructor of the class ContentFilteredTopic by another Publisher object.
         * @param [in] other Const reference of a ContentFilteredTopic object.
         */
        ContentFilteredTopic(ContentFilteredTopic const& other) = default;
        
        /**
         * @brief Move constructor of the class ContentFilteredTopic.
         * @param [in] other Rvalue reference of this ContentFilteredTopic object.
         */
        ContentFilteredTopic(ContentFilteredTopic&& other) = default;
        
        /**
         * @brief Assign a ContentFilteredTopic object to the current ContentFilteredTopic object.
         * @param [in] ohter Const reference of a ContentFilteredTopic object.
         * @return Reference of this ContentFilteredTopic object.
         */
        ContentFilteredTopic& operator=(ContentFilteredTopic const& other) = default;
        
        /**
         * @brief Move assignment of the class ContentFilteredTopic.
         * @param [in] other Rvalue reference of this ContentFilteredTopic object.
         * @return Reference of this ContentFilteredTopic object.
         */
        ContentFilteredTopic& operator=(ContentFilteredTopic&& other) = default;
        
        /**
         * @brief This function returns the Topic associated with the ContentFilteredTopic.
         * @return Pointer to the related topic.
         * @todo
         */
        virtual dds::topic::Topic* get_related_topic() = 0;

        /**
         * @brief This function returns the expression_parameters associated with the ContentFilteredTopic.
         * @param [in,out] expression_parameters A sequence of strings that give values to the 'parameters' (i.e., "%n" tokens) in the filter_expression.
         * @return Return RETCODE_OK if success.
         * @retval Successfully returns the expression_parameters associated with the ContentFilteredTopic.
         * @todo
         */
        virtual DDS::ReturnCode_t get_expression_parameters(dds::core::StringSeq& expression_parameters) = 0;

        /**
         * @brief This function changes the expression_parameters associated with the ContentFilteredTopic.
         * @param [in] expression_parameters A sequence of strings that give values to the 'parameters' (i.e., "%n" tokens) in the filter_expression.
         * @return Return RETCODE_OK if success.
         * @retval Successfully changes the expression_parameters associated with the ContentFilteredTopic.
         * @todo
         */
        virtual DDS::ReturnCode_t set_expression_parameters(dds::core::StringSeq& expression_parameters) = 0;
    protected:
        /**
         * @brief Destructer of the ContentFilteredTopic class.
         */
        ~ContentFilteredTopic() override = default;
    };
}/*topic*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_CONTENTFILTEREDTOPIC_API_H*/
