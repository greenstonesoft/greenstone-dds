/**************************************************************
* @file TopicListener.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_TOPICLISTENER_API_H
#define GSTONE_TOPICLISTENER_API_H 1

#include "dcps/core/Listener.h"
#include "dcps/core/Status.h"
#include "dcps/core/ForwardDeclaration.h"


__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace topic
{
    class Topic;
    /**
     * @class TopicListener
     * @brief The TopicListener class is used for user to implement specific callbacks to certain actions.
     */
    class GS_DDS4CPP_API TopicListener : virtual public dds::core::Listener
    {
    public:

        /**
         * @brief Constructer of the Topic class.
         */
        TopicListener() = default;

        /**
         * @brief Destructer of the Topic class.
         */
        ~TopicListener() override = default;

        /**
         * @brief Constructor of the class TopicListener by another Publisher object.
         * @param [in] other Const reference of a TopicListener object.
         */
        TopicListener(TopicListener const& other) = default;

        /**
         * @brief Move constructor of the class TopicListener.
         * @param [in] other Rvalue reference of this TopicListener object.
         */
        TopicListener(TopicListener && other) = default;
        
        /**
         * @brief Don't use assign a TopicListener object to the current TopicListener object.
         * @param [in] ohter Const reference of a TopicListener object.
         * @return Reference of this TopicListener object.
         */
        TopicListener& operator=(TopicListener const& other) = delete;
        
        /**
         * @brief Don't use move assignment of the class TopicListener.
         * @param [in] other Rvalue reference of this TopicListener object.
         * @return Reference of this TopicListener object.
         */
        TopicListener& operator=(TopicListener && other) = delete;

        /**
         * @brief This function to be implemented by the user containing the actions to be performed when another topic exists with the
         *        same name but different characteristics.
         * @param [in] topic_t The related Topic object
         * @param [in] status Const reference of the inconsistent topic status.
         */
        virtual void on_inconsistent_topic(dds::topic::Topic* topic_t, dds::core::InconsistentTopicStatus const& status) noexcept;
    };
}/*topic*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_TOPICLISTENER_API_H*/