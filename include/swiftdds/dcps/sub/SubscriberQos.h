/**************************************************************
* @file SubscriberQos.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_SUBSCRIBERQOS_API_H
#define GSTONE_SUBSCRIBERQOS_API_H 1

#include "swiftdds/dcps/qos/QosPolicy.h"
#include "swiftdds/dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace sub
{
    /**
     * @class SubscriberQos
     * @brief The qos of subscriber
     */
    class GS_DDS4CPP_API SubscriberQos
    {
    public:
        /**
         * @brief Construct a new Subscriber Qos object
         */
        SubscriberQos() = default;
        
        /**
         * @brief Destroy the Subscriber Qos object
         */
        virtual ~SubscriberQos() = default;
        
        /**
         * @brief Construct a new Subscriber Qos object
         * @param [in] other. reference of a SubscriberQos object.
         */
        SubscriberQos(SubscriberQos const& other) = default;
        
        /**
         * @brief Assign a SubscriberQos object to the locally SubscriberQos object.
         * @param [in] other. reference of a SubscriberQos object.
         * @return Reference of the locally SubscriberQos object.
         */
        SubscriberQos& operator=(SubscriberQos const& other) = default;
        
        /**
         * @brief Assign a SubscriberQos object to the locally SubscriberQos object.
         * @param [in] other. reference of a SubscriberQos object.
         * @return Reference of the locally SubscriberQos object.
         */
        SubscriberQos(SubscriberQos&& other) = default;
        
        /**
         * @brief Assign a SubscriberQos object to the locally SubscriberQos object.
         * @param [in] other. reference of a SubscriberQos object.
         * @return Reference of the locally SubscriberQos object.
         */
        SubscriberQos& operator=(SubscriberQos&& other) = default;

        /**
         * @brief getter of presentation
         * @return dds::qos::PresentationQosPolicy const& 
         */
        inline dds::qos::PresentationQosPolicy const& presentation() const noexcept 
        {
            return m_presentation;
        }
        
        /**
         * @brief getter of partition
         * @return dds::qos::PartitionQosPolicy const& 
         */
        inline dds::qos::PartitionQosPolicy const& partition() const noexcept
        {
            return m_partition;
        }
        
        /**
         * @brief getter of group_data
         * @return dds::qos::GroupDataQosPolicy const& 
         */
        inline dds::qos::GroupDataQosPolicy const& group_data() const noexcept 
        {
            return m_groupData;
        }
        
        /**
         * @brief getter of entity_factory
         * @return dds::qos::EntityFactoryQosPolicy const& 
         */
        inline dds::qos::EntityFactoryQosPolicy const& entity_factory() const noexcept 
        {
            return m_entityFactory;
        }
        
        /**
         * @brief setter of presentation
         * @param [in] presentation_t The value to set.
         */
        inline void presentation(dds::qos::PresentationQosPolicy const& presentation_t) noexcept 
        {
            m_presentation = presentation_t;
        }
        
        /**
         * @brief setter of partition
         * @param [in] partition_t The value to set.
         */
        inline void partition(dds::qos::PartitionQosPolicy const& partition_t) noexcept 
        {
            m_partition = partition_t;
        }
        
        /**
         * @brief setter of group_data
         * @param [in] group_data_t The value to set.
         */
        inline void group_data(dds::qos::GroupDataQosPolicy const& group_data_t) noexcept 
        {
            m_groupData = group_data_t;
        }
        
        /**
         * @brief setter of entity_factory
         * @param [in] entity_factory_t The value to set.
         */
        inline void entity_factory(dds::qos::EntityFactoryQosPolicy const& entity_factory_t) noexcept 
        {
            m_entityFactory = entity_factory_t;
        }
        
        /**
         * @brief  Compares two SubscriberQos objects for equality.
         * @param  [in] f1_qos Const reference of a SubscriberQos object.
         * @param  [in] f2_qos Const reference of another SubscriberQos object.
         * @return Return gbool_t.
         * @retval true   Two SubscriberQos compared are equal.
         * @retval false  Two SubscriberQos compared are not equal.
         */
        inline friend gbool_t operator==(SubscriberQos const &f1_qos, SubscriberQos const &f2_qos) noexcept
        {
            gbool_t const present_ret{f1_qos.presentation() == f2_qos.presentation()};
            gbool_t const entity_ret{f1_qos.entity_factory() == f2_qos.entity_factory()};
            return ((present_ret) && (entity_ret));
        }
        
        /**
         * @brief  Compares two SubscriberQos objects for inequality.
         * @param  [in] f1_qos Const reference of a SubscriberQos object.
         * @param  [in] f2_qos Const reference of another SubscriberQos object.
         * @return Return gbool_t.
         * @retval true   Two SubscriberQos compared are not equal.
         * @retval false  Two SubscriberQos compared are equal.
         */
        inline friend gbool_t operator!=(SubscriberQos const &f1_qos, SubscriberQos const &f2_qos) noexcept
        {
            return !(f1_qos == f2_qos);
        }

    private:
        dds::qos::PresentationQosPolicy m_presentation;
        dds::qos::PartitionQosPolicy m_partition;
        dds::qos::GroupDataQosPolicy m_groupData;
        dds::qos::EntityFactoryQosPolicy m_entityFactory;

    };
} /* sub */
} /* dds */

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_SUBSCRIBERQOS_API_H*/
