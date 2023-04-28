/**************************************************************
* @file DomainParticipantListener.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_DOMAINPARTICIPANTLISTENER_API_H
#define GSTONE_DOMAINPARTICIPANTLISTENER_API_H 1

#include "dcps/pub/PublisherListener.h"
#include "dcps/sub/SubscriberListener.h"
#include "dcps/topic/TopicListener.h"
#include "dcps/xtypes/DynamicType.h"
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace xtypes
{
    class TypeIdentifier;
    class TypeObject;
}
}

namespace dds
{
namespace domain
{
    class DomainParticipant;
    /**
    * @class DomainParticipantListener
    * @brief This class is DDSListener for DDSDomainParticipant status.
    */
    class GS_DDS4CPP_API DomainParticipantListener: 
        public dds::pub::PublisherListener,
        public dds::sub::SubscriberListener,
        public dds::topic::TopicListener
    {

        public:
            /**
            * @brief A callback used for building dynamic type when discoverying a remote DataReader or DataWriter using dynamic type in EDP. 
            * @param [in] a_dp A pointer of the locally DomainParticipant.
            * @param [in] a_topic_name A string used for type name in TypeDescriptor.
            * @param [in] a_id Const pointer of TypeIdentifier used for finding kind in TypeDescriptor.
            * @param [in] a_object Const Pointer of TypeObject.
            * @param [in] a_dynamic_type Const Reference of DynamicType_ptr.
            */
            virtual gvoid_t on_type_discovery(
                DomainParticipant *a_dp,
                std::string const& a_topic_name,
                dds::xtypes::TypeIdentifier const *a_id, 
                dds::xtypes::TypeObject const *a_object,
                dds::xtypes::DynamicType_ptr const &a_dynamic_type) noexcept;
            
            /**
            * @brief A callback used for the locally DomainParticipant discoverys a remote DomainParticipant is online or offline.
            * @param [in] a_participant A pointer of the locally DomainParticipant.
            * @param [in] a_remoteInfo Const Reference of RemoteParticipantInfo.
            */
            virtual gvoid_t on_participant_matched(
                dds::domain::DomainParticipant* a_participant, 
                dds::domain::RemoteParticipantInfo const &a_remoteInfo) noexcept;

            /**
            * @brief Don't use the constructor of the class DomainParticipantListener by another DomainParticipantListener object.
            * @param [in] a_info Const reference of a DomainParticipantListener object.
            */
            DomainParticipantListener( DomainParticipantListener const& a_info) = delete;
            
            /**
            * @brief Don't use assignment operator overload.
            * @param [in] a_info Const reference of a DomainParticipantListener object.
            * @return Reference of the locally DomainParticipantListener object.
            */
            DomainParticipantListener &operator=(DomainParticipantListener const &a_info) = delete;
            
            /**
            * @brief Don't use move constructor of the class DomainParticipantListener.
            * @param [in] a_info Rvalue reference of a DomainParticipantListener object.
            */
            DomainParticipantListener( DomainParticipantListener const && a_info) = delete;
            
            /**
            * @brief Don't use move assignment of the class DomainParticipantListener.
            * @param [in] a_info Rvalue reference of this DomainParticipantListener object.
            * @return Reference of this DomainParticipantListener object.
            */
            DomainParticipantListener &operator=(DomainParticipantListener const &&a_info) = delete;
            
            /**
            * @brief Constructor of the class DomainParticipantListener.
            */
            DomainParticipantListener() = default;
            
            /**
            * @brief Destructor of the class DomainParticipantListener.
            */
            ~DomainParticipantListener() override = default;
    };
}/*domain*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_DOMAINPARTICIPANTLISTENER_API_H*/
