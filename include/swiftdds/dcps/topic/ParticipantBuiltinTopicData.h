/**************************************************************
* @file ParticipantBuiltinTopicData.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_PARTICIPANTBUILTINTOPICDATA_H
#define GSTONE_PARTICIPANTBUILTINTOPICDATA_H 1

#include "swiftdds/rtps/basetypes/BuiltinTopicKey.h"
#include "swiftdds/dcps/qos/UserDataQosPolicy.h"

// include the security data
#include "swiftdds/dcps/qos/PropertyQosPolicy.h"
#include "swiftdds/rtps/Token.h"
#include "swiftdds/rtps/ParticipantSecurityInfo.h"
#include "swiftdds/rtps/EndpointSecurityInfo.h"


namespace dds
{
namespace topic
{
    /**
     * @class ParticipantBuiltinTopicData
     * @brief Information on a DomainParticipant that has been discovered on the network.
     * @details Data associated with the built-in topic. It contains QoS policies and additional information that apply to the remote DomainParticipant.
     */
    class GS_DDS4CPP_API ParticipantBuiltinTopicData
    {
    public:
        /**
         * @brief Constructer of the ParticipantBuiltinTopicData class.
         */
        ParticipantBuiltinTopicData() = default;
        
        /**
         * @brief Constructor of the class ParticipantBuiltinTopicData by another Publisher object.
         * @param [in] other Const reference of a ParticipantBuiltinTopicData object.
         */
        ParticipantBuiltinTopicData(ParticipantBuiltinTopicData const& other) = default;
        
        /**
         * @brief Move constructor of the class ParticipantBuiltinTopicData.
         * @param [in] other Rvalue reference of this ParticipantBuiltinTopicData object.
         */
        ParticipantBuiltinTopicData(ParticipantBuiltinTopicData&& other) = default;
        
        /**
         * @brief Assign a ParticipantBuiltinTopicData object to the current ParticipantBuiltinTopicData object.
         * @param [in] ohter Const reference of a ParticipantBuiltinTopicData object.
         * @return Reference of this ParticipantBuiltinTopicData object.
         */
        ParticipantBuiltinTopicData& operator=(ParticipantBuiltinTopicData const& other) = default;
        
        /**
         * @brief Move assignment of the class ParticipantBuiltinTopicData.
         * @param [in] other Rvalue reference of this ParticipantBuiltinTopicData object.
         * @return Reference of this ParticipantBuiltinTopicData object.
         */
        ParticipantBuiltinTopicData& operator=(ParticipantBuiltinTopicData&& other) = default;
        
        /**
         * @brief Deconstructer of the class ParticipantBuiltinTopicData.
         */
        virtual ~ParticipantBuiltinTopicData() = default;

        /**
         * @brief This function get the builtin topic key.
         * @return Builtin topic key 
         */
        inline gstone::rtps::BuiltinTopicKey_t const& key() const noexcept
        {
            return m_key;
        }

        /**
         * @brief This function get the UserDataQosPolicy.
         * @return UserDataQosPolicy 
         */
        inline dds::qos::UserDataQosPolicy const& user_data() const noexcept
        {
            return m_userData;
        }

        /**
         * @brief This function set the builtin topic key.
         * @param [in] a_key Builtin topic key to be set to
         */
        inline void key(gstone::rtps::BuiltinTopicKey_t const& a_key) noexcept
        {
            m_key = a_key;
        }

        /**
         * @brief This function set the UserDataQosPolicy.
         * @param [in] user_data_t UserDataQosPolicy to be set to
         */
        inline void user_data(dds::qos::UserDataQosPolicy const& user_data_t) noexcept
        {
            m_userData = user_data_t;
        }

        /**
         * @brief This function deserializies UserDataQosPolicy object with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The id
         */
        inline gvoid_t deserialize_user_data(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_userData, id);
        }

        /**
         * @brief This function get the indentity token.
         * @return Const reference of the indentity token.
         */
        inline gstone::security::IdentityToken const& identity_token() const noexcept
        {
            return m_identityToken;
        }
        
        /**
         * @brief This function get the property.
         * @return Const reference of the property.
         */
        inline dds::qos::PropertyQosPolicy const& property() const noexcept
        {
            return m_property;
        }
        
        /**
         * @brief This function get the permissions token.
         * @return Const reference of the permissions token.
         */
        inline gstone::security::PermissionsToken const& permissions_token() const noexcept
        {
            return m_permissionsToken;
        }
        
        /**
         * @brief This function get the security info.
         * @return Const reference of the security info.
         */
        inline gstone::security::ParticipantSecurityInfo const& security_info() const noexcept
        {
            return m_securityInfo;
        }
        
        /**
         * @brief This function get the indentity status token.
         * @return Const reference of the indentity status token.
         */
        inline gstone::security::IdentityStatusToken const& identity_status_token() const noexcept
        {
            return m_identityStatusToken;
        }

        /**
         * @brief This function set the identity token.
         * @param [in] identity_token_t Const reference of the indentity token to be set to.
         */
        inline void identity_token(gstone::security::IdentityToken const& identity_token_t) noexcept
        {
            m_identityToken = identity_token_t;
        }
        
        /**
         * @brief This function set the property.
         * @param [in] property_t Const reference of the property to be set to.
         */
        inline void property(dds::qos::PropertyQosPolicy const& property_t) noexcept
        {
            m_property = property_t;
        }
        
        /**
         * @brief This function set the permissions token.
         * @param [in] permissions_token_t Const reference of the permissions token to be set to.
         */
        inline void permissions_token(gstone::security::PermissionsToken const& permissions_token_t) noexcept
        {
            m_permissionsToken = permissions_token_t;
        }
        
        /**
         * @brief This function set the security info.
         * @param [in] security_info_t Const reference of the security info to be set to.
         */
        inline void security_info(gstone::security::ParticipantSecurityInfo const& security_info_t) noexcept
        {
            m_securityInfo = security_info_t;
        }
        
        /**
         * @brief This function set the identity status token.
         * @param [in] identity_status_token_t Const reference of the identity status token to be set to.
         */
        inline void identity_status_token(gstone::security::IdentityStatusToken const& identity_status_token_t) noexcept
        {
            m_identityStatusToken = identity_status_token_t;
        }

        /**
         * @brief Compare two ParticipantBuiltinTopicData objects for equailty.
         * @@param [in] f1_data Const Reference of the left ParticipantBuiltinTopicData object.
         * @@param [in] f2_data Const Reference of the right ParticipantBuiltinTopicData object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(ParticipantBuiltinTopicData const &f1_data, ParticipantBuiltinTopicData const &f2_data) noexcept
        {
            gbool_t const key_ret{f1_data.key() == f2_data.key()};

            return ((key_ret));
        }
        
        /**
         * @brief Compare two ParticipantBuiltinTopicData objects for inequailty.
         * @@param [in] f1_data Const Reference of the left ParticipantBuiltinTopicData object.
         * @@param [in] f2_data Const Reference of the right ParticipantBuiltinTopicData object.
         * @return Return true if inequality, else return false. 
         */
        inline friend gbool_t operator!=(ParticipantBuiltinTopicData const &f1_data, ParticipantBuiltinTopicData const &f2_data) noexcept
        {
            return !(f1_data == f2_data);
        }

    private:
        gstone::rtps::BuiltinTopicKey_t m_key;

        dds::qos::UserDataQosPolicy m_userData;
        //@security-7.4.1.4
        //@id(0x1001)
        gstone::security::IdentityToken m_identityToken;
        //@id(0x0059)
        dds::qos::PropertyQosPolicy m_property;
        //@id(0x1002)
        gstone::security::PermissionsToken m_permissionsToken;
        //@id(0x1005)
        gstone::security::ParticipantSecurityInfo m_securityInfo;
        gstone::security::IdentityStatusToken m_identityStatusToken;
    };
}/*topic*/
}/*dds*/

#endif
