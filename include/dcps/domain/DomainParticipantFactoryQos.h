/**************************************************************
* @file DomainParticipantFactoryQos.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#ifndef GSTONE_DOMAINPARTICIPANTFACTORYQOS_API_H
#define GSTONE_DOMAINPARTICIPANTFACTORYQOS_API_H 1

#include "dcps/qos/QosPolicy.h"
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace domain
{
    /**
    * @class DomainParticipantFactoryQos
    * @brief This class is QoS policies supported by a DomainParticipantFactory entity.
    */
    class GS_DDS4CPP_API DomainParticipantFactoryQos
    {
        public:
            /**
            * @brief Constructor of the class DomainParticipantFactoryQos.
            */
            DomainParticipantFactoryQos()=default;
            
            /**
            * @brief Assign a DomainParticipantFactoryQos object to the locally DomainParticipantFactoryQos object.
            * @param [in] a_info Const reference of a DomainParticipantFactoryQos object.
            * @return Reference of the locally DomainParticipantFactoryQos object.
            */
            DomainParticipantFactoryQos& operator=( DomainParticipantFactoryQos const& a_info) = default;
            
            /**
            * @brief Constructor of the class DomainParticipantFactoryQos by another DomainParticipantFactoryQos object.
            * @param [in] a_info Const reference of a DomainParticipantFactoryQos object.
            */
            DomainParticipantFactoryQos( DomainParticipantFactoryQos const& a_info) = default;
            
            /**
            * @brief Don't use move constructor of the class DomainParticipantFactoryQos.
            * @param [in] a_info Rvalue reference of a DomainParticipantFactoryQos object.
            */
            DomainParticipantFactoryQos( DomainParticipantFactoryQos && a_info) = delete;
            
            /**
            * @brief Don't use move assignment of the class DomainParticipantFactoryQos.
            * @param [in] a_info Rvalue reference of this DomainParticipantFactoryQos object.
            * @return Reference of this DomainParticipantFactoryQos object.
            */
            DomainParticipantFactoryQos &operator=(DomainParticipantFactoryQos &&a_info) = delete;
            
            /**
            * @brief Destructor of the class DomainParticipantFactoryQos.
            */
            virtual ~DomainParticipantFactoryQos()=default;
            
            /**
            * @brief Set the EntityFactoryQosPolicy of the locally DomainParticipantFactoryQos.
            * @param [in] a_qos_policy Const reference of a EntityFactoryQosPolicy object.
            */
            inline gvoid_t entity_factory(dds::qos::EntityFactoryQosPolicy const &a_qos_policy) noexcept
            {
                m_entityFactory = a_qos_policy;
            }
            
            /**
            * @brief Retrieve the EntityFactoryQosPolicy of the locally DomainParticipantFactoryQos.
            * @return Const reference of the locally DomainParticipantFactoryQos' EntityFactoryQosPolicy object.
            */
            inline dds::qos::EntityFactoryQosPolicy const &entity_factory() const noexcept
            {
                return m_entityFactory;
            }
        private:
            dds::qos::EntityFactoryQosPolicy m_entityFactory;
    };
}/*domain*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_DOMAINPARTICIPANTFACTORYQOS_API_H*/
