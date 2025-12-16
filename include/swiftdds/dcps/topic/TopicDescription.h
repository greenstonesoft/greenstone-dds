/**************************************************************
* @file TopicDescription.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_TOPICDESCRIPTION_API_H
#define GSTONE_TOPICDESCRIPTION_API_H 1

#include "swiftdds/dcps/DdsBaseTypes.h"
#include "swiftdds/dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
    namespace domain
    {
        class DomainParticipant;
    }
}

namespace dds
{
namespace topic
{
    /**
     * @class TopicDescription
     * @brief This class is an abstract class. It is the base class for Topic, ContentFilteredTopic, and TopicDescription.
     *        TopicDescription represents the fact that both publications and subscriptions are tied to a single data-type.
     */
    class GS_DDS4CPP_API TopicDescription
    {
    public:
        /**
         * @brief Constructer of the class TopicDescription.
         */
        TopicDescription() = default;
        /**
         * @brief Destructer of the class TopicDescription.
         */
        virtual ~TopicDescription() = default;

        /**
         * @brief This function returns the DomainParticipant to which the TopicDescription belongs.
         * @return Pointer to the DomainParticipant to which the TopicDescription belongs. 
         */
        virtual dds::domain::DomainParticipant* get_participant() const noexcept;

        /**
         * @brief This function get the name used to create the TopicDescription.
         * @return The name used to create the TopicDescription.
         */
        inline gstring_t get_name() const
        {
            return this->m_name;
        }

        /**
         * @brief This function set the name used to create the TopicDescription.
         * @param [in] a_name Const reference of the name used to create the TopicDescription to be set to.
         */
        inline void set_name(gstring_t const& a_name)
        {
            m_name = a_name;
        }

        /**
         * @brief This function set the type_name used to create the TopicDescription.
         * @param [in] a_type_name Const reference of the type_name used to create the TopicDescription to be set to.
         */
        inline void set_type_name(gstring_t const& a_type_name)
        {
            m_typeName = a_type_name;
        }

        /**
         * @brief This function get the type_name used to create the TopicDescription.
         * @return The type_name used to create the TopicDescription.
         */
        inline gstring_t get_type_name() const
        {
            return this->m_typeName;
        }

    protected:
        /**
         * @brief Constructor of the class TopicDescription by another Publisher object.
         * @param [in] other Const reference of a TopicDescription object.
         */
        TopicDescription(TopicDescription const& other) = default;
        
        /**
         * @brief Move constructor of the class TopicDescription.
         * @param [in] other Rvalue reference of this TopicDescription object.
         */
        TopicDescription(TopicDescription&& other) = default;
        
        /**
         * @brief Assign a TopicDescription object to the current TopicDescription object.
         * @param [in] ohter Const reference of a TopicDescription object.
         * @return Reference of this TopicDescription object.
         */
        TopicDescription& operator=(TopicDescription const& other) = default;
        
        /**
         * @brief Move assignment of the class TopicDescription.
         * @param [in] other Rvalue reference of this TopicDescription object.
         * @return Reference of this TopicDescription object.
         */
        TopicDescription& operator=(TopicDescription&& other) = default;

    private:
        gstring_t m_name;
        gstring_t m_typeName;
    };
}/*topic*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_TOPICDESCRIPTION_API_H*/
