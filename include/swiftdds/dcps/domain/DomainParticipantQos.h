/**************************************************************
* @file DomainParticipantQos.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_DOMAINPARTICIPANTQOS_API_H
#define GSTONE_DOMAINPARTICIPANTQOS_API_H 1

#include "swiftdds/dcps/qos/UserDataQosPolicy.h"
#include "swiftdds/rtps/ParticipantAttributes.h"
#include "swiftdds/dcps/qos/PropertyQosPolicy.h"
#include "swiftdds/dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace domain
{
    /**
    * @class DomainParticipantQos
    * @brief This class is QoS policies supported by a DDSDomainParticipant entity.
    */
    class GS_DDS4CPP_API DomainParticipantQos
    {
        public:
            /**
            * @brief Retrieve UserDataQosPolicy in the locally DomainParticipantQos.
            * @return Constant reference of the UserDataQosPolicy object.
            */
            inline dds::qos::UserDataQosPolicy const &user_data() const noexcept
            {
                return m_userData;
            }
            
            /**
            * @brief Set UserDataQosPolicy in the locally DomainParticipantQos.
            * @param [in] a_data Const reference of a UserDataQosPolicy object.
            */
            inline gvoid_t user_data(dds::qos::UserDataQosPolicy const &a_data) noexcept
            {
                m_userData = a_data;
            }
            
            /**
            * @brief Retrieve EntityFactoryQosPolicy in the locally DomainParticipantQos.
            * @return Constant reference of the EntityFactoryQosPolicy object.
            */
            inline dds::qos::EntityFactoryQosPolicy const &entity_factory() const noexcept
            {
                return m_entityFactory;
            }
            
            /**
            * @brief Set EntityFactoryQosPolicy in the locally DomainParticipantQos.
            * @param [in] a_qos_policy Const reference of a EntityFactoryQosPolicy object.
            */
            inline gvoid_t entity_factory(dds::qos::EntityFactoryQosPolicy const &a_qos_policy) noexcept
            {
                m_entityFactory = a_qos_policy;
            }
            
            /**
            * @brief Retrieve EntityNameQosPolicy in the locally DomainParticipantQos.
            * @return Constant reference of the EntityNameQosPolicy object.
            */
            inline dds::qos::EntityNameQosPolicy const &entity_name() const noexcept
            {
                return m_entityName;
            }
            
            /**
            * @brief Set EntityNameQosPolicy in the locally DomainParticipantQos.
            * @param [in] a_qos_policy Const reference of a EntityNameQosPolicy object.
            */
            inline gvoid_t entity_name(dds::qos::EntityNameQosPolicy const &a_qos_policy) noexcept
            {
                m_entityName = a_qos_policy;
            }
            
            /**
            * @brief Retrieve ParticipantAttributes in the locally DomainParticipantQos.
            * @return Constant reference of the ParticipantAttributes object.
            */
            inline gstone::rtps::ParticipantAttributes const &rtps_participant_attributes() const noexcept
            {
                return m_rtpsParticipantAttributes;
            }
            
            /**
            * @brief Retrieve ParticipantAttributes in the locally DomainParticipantQos.
            * @return Reference of the ParticipantAttributes object.
            */
            inline gstone::rtps::ParticipantAttributes &rtps_participant_attributes() noexcept
            {
                return m_rtpsParticipantAttributes;
            }
            
            /**
            * @brief Set ParticipantAttributes in the locally DomainParticipantQos.
            * @param [in] a_participant_attr Const reference of a ParticipantAttributes object.
            */
            inline gvoid_t rtps_participant_attributes(gstone::rtps::ParticipantAttributes const &a_participant_attr) noexcept
            {
                m_rtpsParticipantAttributes = a_participant_attr;
            }
            
            /**
            * @brief Retrieve PropertyQosPolicy in the locally DomainParticipantQos.
            * @return Constant reference of the PropertyQosPolicy object.
            */
            inline dds::qos::PropertyQosPolicy const &property() const noexcept
            {
                return m_property;
            }
            
            /**
            * @brief Set PropertyQosPolicy in the locally DomainParticipantQos.
            * @param [in] a_property Const reference of a PropertyQosPolicy object.
            */
            inline gvoid_t property(dds::qos::PropertyQosPolicy const &a_property) noexcept
            {
                m_property = a_property;
            }

            /**
            * @brief Compares two DomainParticipantQos objects for equality.
            * @param [in] a_f1_qos Const reference of a DomainParticipantQos object.
            * @param [in] a_f2_qos Const reference of another DomainParticipantQos object.
            * @return Return gbool_t.
            * @retval true  Two DomainParticipantQoses compared are equal.
            * @retval false Two DomainParticipantQoses compared are not equal.
            */
            friend gbool_t operator==(DomainParticipantQos const& a_f1_qos, DomainParticipantQos const& a_f2_qos) noexcept
            {
                gbool_t const user_ret{a_f1_qos.user_data() == a_f2_qos.user_data()};
                gbool_t const entity_ret{a_f1_qos.entity_factory() == a_f2_qos.entity_factory()};
                if ((user_ret) && (entity_ret))
                {
                    return true;
                }
                return false;
            }
            
            /**
            * @brief Compares two DomainParticipantQos objects for inequality.
            * @param [in] a_f1_qos Const reference of a DomainParticipantQos object.
            * @param [in] a_f2_qos Const reference of another DomainParticipantQos object.
            * @return Return gbool_t.
            * @retval true   Two DomainParticipantQoses compared are not equal.
            * @retval false  Two DomainParticipantQoses compared are equal.
            */
            friend gbool_t operator!=(DomainParticipantQos const& a_f1_qos, DomainParticipantQos const& a_f2_qos) noexcept
            {
                return !(a_f1_qos == a_f2_qos);
            }
            
            /**
            * @brief Constructor of the class DomainParticipantQos.
            */
            DomainParticipantQos() = default;
            
            /**
            * @brief Destructor of the class DomainParticipantQos.
            */
            virtual ~DomainParticipantQos() noexcept = default;
            
            /**
            * @brief Constructor of the class DomainParticipantQos by another DomainParticipantQos object.
            * @param [in] a_info Const reference of a DomainParticipantQos object.
            */
            DomainParticipantQos(DomainParticipantQos const&a_info) = default;
            
            /**
            * @brief Assign a DomainParticipantQos object to the locally DomainParticipantQos object.
            * @param [in] a_info Const reference of a DomainParticipantQos object.
            * @return Reference of the locally DomainParticipantQos object.
            */
            DomainParticipantQos& operator=(DomainParticipantQos const&a_info) = default;
            
            /**
            * @brief Move constructor of the class DomainParticipantQos.
            * @param [in] a_info Rvalue reference of a DomainParticipantQos object.
            */
            DomainParticipantQos(DomainParticipantQos &&a_info) = default;
            
            /**
            * @brief Move assignment of the class DomainParticipantQos.
            * @param [in] a_info Rvalue reference of this DomainParticipantQos object.
            * @return Reference of this DomainParticipantQos object.
            */
            DomainParticipantQos& operator=(DomainParticipantQos &&a_info) = default;

        private:
            dds::qos::UserDataQosPolicy m_userData;
            dds::qos::EntityFactoryQosPolicy m_entityFactory;
            dds::qos::EntityNameQosPolicy m_entityName;
            gstone::rtps::ParticipantAttributes m_rtpsParticipantAttributes;
            dds::qos::PropertyQosPolicy m_property;
    };
}/*domain*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_DOMAINPARTICIPANTQOS_API_H*/
