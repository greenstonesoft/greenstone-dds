/**************************************************************
* @file PublisherQos.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/

#ifndef GSTONE_PUBLISHERQOS_API_H
#define GSTONE_PUBLISHERQOS_API_H 1

#include "swiftdds/dcps/qos/QosPolicy.h"
#include "swiftdds/dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace pub
{
    /**
    * @class PublisherQos
    * @brief This class is a collection of QoS policies supported by a DDSPublisher entity.
    */
    class GS_DDS4CPP_API PublisherQos
    {
    public:
        /**
        * @brief Constructor of the class PublisherQos.
        */
        PublisherQos() = default;
        
        /**
        * @brief Destructor of the class PublisherQos.
        */
        virtual ~PublisherQos() = default;
        
        /**
        * @brief Constructor of the class PublisherQos by another PublisherQos object.
        * @param [in] a_info Const reference of a PublisherQos object.
        */
        PublisherQos(PublisherQos const&a_info) = default;
        
        /**
        * @brief Assign a PublisherQos object to the current PublisherQos object.
        * @param [in] a_info Const reference of a PublisherQos object.
        * @return Reference of this PublisherQos object.
        */
        PublisherQos& operator=(PublisherQos const&a_info) = default;
        
        /**
        * @brief Move constructor of the class PublisherQos.
        * @param [in] a_info Rvalue reference of this PublisherQos object.
        */
        PublisherQos(PublisherQos&&a_info) = default;
        
        /**
        * @brief Move assignment of the class PublisherQos.
        * @param [in] a_info Rvalue reference of this PublisherQos object.
        * @return Reference of this PublisherQos object.
        */
        PublisherQos& operator=(PublisherQos&&a_info) = default;

        /**
        * @brief This function gets PresentationQosPolicy of the Publisher.
        * @return Const reference of a PresentationQosPolicy object.
        */
        dds::qos::PresentationQosPolicy const& presentation() const noexcept 
        {
            return m_presentation;
        }
        
        /**
        * @brief This function gets PartitionQosPolicy of the Publisher.
        * @return Const reference of a PartitionQosPolicy object.
        */
        dds::qos::PartitionQosPolicy const& partition() const noexcept 
        {
            return m_partition;
        }
        
        /**
        * @brief This function gets GroupDataQosPolicy of the Publisher.
        * @return Const reference of a GroupDataQosPolicy object.
        */
        dds::qos::GroupDataQosPolicy const& group_data() const noexcept 
        {
            return m_groupData;
        }
        
        /**
        * @brief This function gets EntityFactoryQosPolicy of the Publisher.
        * @return Const reference of a EntityFactoryQosPolicy object.
        */
        dds::qos::EntityFactoryQosPolicy const& entity_factory() const noexcept 
        {
            return m_entityFactory;
        }
        
        /**
        * @brief This function sets PresentationQosPolicy of the Publisher. 
        * @param [in] a_presentation Const reference of a PresentationQosPolicy object.
        */
        void presentation(dds::qos::PresentationQosPolicy const& a_presentation) noexcept 
        {
            m_presentation = a_presentation;
        }
        
        /**
        * @brief This function sets PartitionQosPolicy of the Publisher. 
        * @param [in] a_partition Const reference of a PartitionQosPolicy object.
        */
        void partition(dds::qos::PartitionQosPolicy const& a_partition) noexcept 
        {
            m_partition = a_partition;
        }
        
        /**
        * @brief This function sets GroupDataQosPolicy of the Publisher. 
        * @param [in] a_group_data Const reference of a GroupDataQosPolicy object.
        */
        void group_data(dds::qos::GroupDataQosPolicy const& a_group_data) noexcept 
        {
            m_groupData = a_group_data;
        }
        
        /**
        * @brief This function sets EntityFactoryQosPolicy of the Publisher. 
        * @param [in] a_entity_factory Const reference of a EntityFactoryQosPolicy object.
        */
        void entity_factory(dds::qos::EntityFactoryQosPolicy const& a_entity_factory) noexcept 
        {
            m_entityFactory = a_entity_factory;
        }

    private:
        dds::qos::PresentationQosPolicy m_presentation;
        dds::qos::PartitionQosPolicy m_partition;
        dds::qos::GroupDataQosPolicy m_groupData;
        dds::qos::EntityFactoryQosPolicy m_entityFactory;
    };
}/*pub*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_PUBLISHERQOS_API_H*/
