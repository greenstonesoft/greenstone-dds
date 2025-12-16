/**************************************************************
* @file DomainParticipantFactoryQos.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/

#ifndef GSTONE_DOMAINPARTICIPANTFACTORYQOS_API_H
#define GSTONE_DOMAINPARTICIPANTFACTORYQOS_API_H 1

#include "swiftdds/dcps/qos/QosPolicy.h"
#include "swiftdds/dcps/DeclExport.h"

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

            /**
            * @brief Set the FlowControlQosPolicy of the locally DomainParticipantFactoryQos.
            * @param [in] a_qos_policy Const reference of a FlowControlQosPolicy object.
            */
            inline gvoid_t flow_control(dds::qos::FlowControlQosPolicy const &a_qos_policy) noexcept
            {
                m_flowControl = a_qos_policy;
            }
            
            /**
            * @brief Retrieve the FlowControlQosPolicy of the locally DomainParticipantFactoryQos.
            * @return Const reference of the locally DomainParticipantFactoryQos' FlowControlQosPolicy object.
            */
            inline dds::qos::FlowControlQosPolicy const &flow_control() const noexcept
            {
                return m_flowControl;
            }

            /**
            * @brief Set the ThreadInstanceConfigQosPolicy of the locally DomainParticipantFactoryQos.
            * @param [in] a_qos_policy Const reference of a ThreadInstanceConfigQosPolicy object.
            */
            inline gvoid_t thread_instance_config(dds::qos::ThreadInstanceConfigQosPolicy const &a_qos_policy) noexcept
            {
                m_threadInstanceConfig = a_qos_policy;
            }
            
            /**
            * @brief Retrieve the ThreadInstanceConfigQosPolicy of the locally DomainParticipantFactoryQos.
            * @return Const reference of the locally DomainParticipantFactoryQos' ThreadInstanceConfigQosPolicy object.
            */
            inline dds::qos::ThreadInstanceConfigQosPolicy const &thread_instance_config() const noexcept
            {
                return m_threadInstanceConfig;
            }

            /**
            * @brief Set the NetworkPortRangeQosPolicy of the locally DomainParticipantFactoryQos.
            * @param [in] a_qos_policy Const reference of a NetworkPortRangeQosPolicy object.
            */
            inline gvoid_t network_port_range(dds::qos::NetworkPortRangeQosPolicy const &a_qos_policy) noexcept
            {
                m_networkPortRange = a_qos_policy;
            }
            
            /**
            * @brief Retrieve the NetworkPortRangeQosPolicy of the locally DomainParticipantFactoryQos.
            * @return Const reference of the locally DomainParticipantFactoryQos' NetworkPortRangeQosPolicy object.
            */
            inline dds::qos::NetworkPortRangeQosPolicy const &network_port_range() const noexcept
            {
                return m_networkPortRange;
            }

        private:
            dds::qos::EntityFactoryQosPolicy m_entityFactory;
            dds::qos::FlowControlQosPolicy m_flowControl;
            dds::qos::ThreadInstanceConfigQosPolicy m_threadInstanceConfig;
            dds::qos::NetworkPortRangeQosPolicy m_networkPortRange;
    };
}/*domain*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_DOMAINPARTICIPANTFACTORYQOS_API_H*/
