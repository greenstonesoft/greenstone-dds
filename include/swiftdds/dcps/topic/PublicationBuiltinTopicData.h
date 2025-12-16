/**************************************************************
* @file PublicationBuiltinTopicData.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef PUBLICATIONBUILTINTOPICDATA_H
#define PUBLICATIONBUILTINTOPICDATA_H 1

#include "swiftdds/rtps/basetypes/BuiltinTopicKey.h"
#include "swiftdds/dcps/qos/UserDataQosPolicy.h"
#include "swiftdds/dcps/qos/TopicDataQosPolicy.h"
#include "swiftdds/dcps/qos/GroupDataQosPolicy.h"
#include "swiftdds/dcps/qos/PartitionQosPolicy.h"
#include "swiftdds/dcps/qos/TimeBasedFilterQosPolicy.h"
#include "swiftdds/dcps/qos/LivelinessQosPolicy.h"
#include "swiftdds/rtps/EndpointSecurityInfo.h"
#include "swiftdds/rtps/DdsOptionalMember.h"

#include <array>

namespace dds {
namespace topic {
    guint32_t const PUB_SECURITY_INFO_LENGTH{ 2U };     ///< Length of PublicationBuiltinTopicData's security info.
    /**
     * @class PublicationBuiltinTopicData
     * @brief Information on a publication that is currently "associated" with the DataReader. that is, a publication with a matching Topic and 
     *        compatible QoS that the application has not indicated should be "ignored" by means of the DomainParticipant ignore_publication operation.

     */
    class GS_DDS4CPP_API PublicationBuiltinTopicData
    {
    public:
        /**
         * @brief Constructer of the PublicationBuiltinTopicData class.
         */
        PublicationBuiltinTopicData() { m_reliability.kind(dds::qos::ReliabilityQosPolicyKind::RELIABLE_RELIABILITY_QOS); }
        
        /**
         * @brief Constructor of the class PublicationBuiltinTopicData by another Publisher object.
         * @param [in] other Const reference of a PublicationBuiltinTopicData object.
         */
        PublicationBuiltinTopicData(PublicationBuiltinTopicData const& other) = default;
        
        /**
         * @brief Move constructor of the class PublicationBuiltinTopicData.
         * @param [in] other Rvalue reference of this PublicationBuiltinTopicData object.
         */
        PublicationBuiltinTopicData(PublicationBuiltinTopicData&& other) = default;
        
        /**
         * @brief Assign a PublicationBuiltinTopicData object to the current PublicationBuiltinTopicData object.
         * @param [in] other Const reference of a PublicationBuiltinTopicData object.
         * @return Reference of this PublicationBuiltinTopicData object.
         */
        PublicationBuiltinTopicData& operator=(PublicationBuiltinTopicData const& other) = default;
        
        /**
         * @brief Move assignment of the class PublicationBuiltinTopicData.
         * @param [in] other Rvalue reference of this PublicationBuiltinTopicData object.
         * @return Reference of this PublicationBuiltinTopicData object.
         */
        PublicationBuiltinTopicData& operator=(PublicationBuiltinTopicData&& other) = default;
        
        /**
         * @brief Deconstructer of the class PublicationBuiltinTopicData.
         */
        virtual ~PublicationBuiltinTopicData() = default;

        /**
         * @brief This function get the builtin topic key.
         * @return Builtin topic key
         */
        inline gstone::rtps::BuiltinTopicKey_t const& key() const noexcept
        {
            return m_key;
        }

        /**
         * @brief This function set the builtin topic key.
         * @param [in] value Builtin topic key to be set to
         */
        inline gvoid_t key(gstone::rtps::BuiltinTopicKey_t const& value) noexcept
        {
            m_key = value;
        }

        /**
         * @brief This function get the builtin participant topic key.
         * @return Builtin participant topic key
         */
        inline gstone::rtps::BuiltinTopicKey_t const& participant_key() const noexcept
        {
            return m_participantKey;
        }

        /**
         * @brief This function set the builtin participant topic key.
         * @param [in] value Builtin participant topic key to be set to
         */
        inline gvoid_t participant_key(gstone::rtps::BuiltinTopicKey_t const& value) noexcept
        {
            m_participantKey = value;
        }

        /**
         * @brief This function set the builtin participant topic key.
         * @param [in] value Const reference of the GUID of builtin participant topic key to be set to
         */
        inline gvoid_t participant_key(gstone::rtps::GUID const& value) noexcept
        {
            std::array<octet, gstone::rtps::BuiltinTopicKey_t::BUILTIN_TOPIC_KEY_SIZE> key_;
            value.to_octet16(key_);
            m_participantKey.value(key_);
        }

        /**
         * @brief This function get the topic name.
         * @return Const reference of the topic name
         */
        inline std::string const& topic_name() const noexcept
        {
            return m_topicName;
        }

        /**
         * @brief This function set the topic name.
         * @param [in] value Const reference of the topic name to be set to
         */
        inline gvoid_t topic_name(std::string const& value) noexcept
        {
            m_topicName = value;
        }

        /**
         * @brief This function get the type name.
         * @return Const reference of the type name
         */
        inline std::string const& type_name() const noexcept
        {
            return m_typeName;
        }

        /**
         * @brief This function set the type name.
         * @param [in] value Const reference of the type name to be set to
         */
        inline gvoid_t type_name(std::string const& value) noexcept
        {
            m_typeName = value;
        }

        /**
         * @brief This function get the UserDataQosPolicy.
         * @return Const reference of the UserDataQosPolicy
         */
        inline dds::qos::UserDataQosPolicy const& user_data() const noexcept
        {
            return m_userData;
        }

        /**
         * @brief This function set the UserDataQosPolicy.
         * @param [in] value Const reference of the UserDataQosPolicy to be set to
         */
        inline gvoid_t user_data(dds::qos::UserDataQosPolicy const& value) noexcept
        {
            m_userData = value;
        }

        /**
         * @brief This function get the TopicDataQosPolicy.
         * @return Const reference of the TopicDataQosPolicy
         */
        inline dds::qos::TopicDataQosPolicy const& topic_data() const noexcept
        {
            return m_topicData;
        }

        /**
         * @brief This function set the TopicDataQosPolicy.
         * @param [in] value Const reference of the TopicDataQosPolicy to be set to
         */
        inline gvoid_t topic_data(dds::qos::TopicDataQosPolicy const& value) noexcept
        {
            m_topicData = value;
        }

        /**
         * @brief This function get the GroupDataQosPolicy.
         * @return Const reference of the GroupDataQosPolicy
         */
        inline dds::qos::GroupDataQosPolicy const& group_data() const noexcept
        {
            return m_groupData;
        }

        /**
         * @brief This function set the GroupDataQosPolicy.
         * @param [in] value Const reference of the GroupDataQosPolicy to be set to
         */
        inline gvoid_t group_data(dds::qos::GroupDataQosPolicy const& value) noexcept
        {
            m_groupData = value;
        }

        /**
         * @brief This function get the DurabilityQosPolicy.
         * @return Const reference of the DurabilityQosPolicy
         */
        inline dds::qos::DurabilityQosPolicy const& durability() const noexcept
        {
            return m_durability;
        }

        /**
         * @brief This function set the DurabilityQosPolicy.
         * @param [in] value Const reference of the DurabilityQosPolicy to be set to
         */
        inline gvoid_t durability(dds::qos::DurabilityQosPolicy const& value) noexcept
        {
            m_durability = value;
        }

        /**
         * @brief This function get the DurabilityServiceQosPolicy.
         * @return Const reference of the DurabilityServiceQosPolicy
         */
        inline dds::qos::DurabilityServiceQosPolicy const& durability_service() const noexcept
        {
            return m_durabilityService;
        }

        /**
         * @brief This function set the DurabilityServiceQosPolicy.
         * @param [in] value Const reference of the DurabilityServiceQosPolicy to be set to
         */
        inline gvoid_t durability_service(dds::qos::DurabilityServiceQosPolicy const& value) noexcept
        {
            m_durabilityService = value;
        }

        /**
         * @brief This function get the DeadlineQosPolicy.
         * @return Const reference of the DeadlineQosPolicy
         */
        inline dds::qos::DeadlineQosPolicy const& deadline() const noexcept
        {
            return m_deadline;
        }

        /**
         * @brief This function set the DeadlineQosPolicy.
         * @param [in] value Const reference of the DeadlineQosPolicy to be set to
         */
        inline gvoid_t deadline(dds::qos::DeadlineQosPolicy const& value) noexcept
        {
            m_deadline = value;
        }

        /**
         * @brief This function get the LatencyBudgetQosPolicy.
         * @return Const reference of the LatencyBudgetQosPolicy
         */
        inline dds::qos::LatencyBudgetQosPolicy const& latency_budget() const noexcept
        {
            return m_latencyBudget;
        }

        /**
         * @brief This function set the LatencyBudgetQosPolicy.
         * @param [in] value Const reference of the LatencyBudgetQosPolicy to be set to
         */
        inline gvoid_t latency_budget(dds::qos::LatencyBudgetQosPolicy const& value) noexcept
        {
            m_latencyBudget = value;
        }

        /**
         * @brief This function get the LivelinessQosPolicy.
         * @return Const reference of the LivelinessQosPolicy
         */
        inline dds::qos::LivelinessQosPolicy const& liveliness() const noexcept
        {
            return m_liveliness;
        }

        /**
         * @brief This function set the LivelinessQosPolicy.
         * @param [in] value Const reference of the LivelinessQosPolicy to be set to
         */
        inline gvoid_t liveliness(dds::qos::LivelinessQosPolicy const& value) noexcept
        {
            m_liveliness = value;
        }

        /**
         * @brief This function get the ReliabilityQosPolicy.
         * @return Const reference of the ReliabilityQosPolicy
         */
        inline dds::qos::ReliabilityQosPolicy const& reliability() const noexcept
        {
            return m_reliability;
        }

        /**
         * @brief This function set the ReliabilityQosPolicy.
         * @param [in] value Const reference of the ReliabilityQosPolicy to be set to
         */
        inline gvoid_t reliability(dds::qos::ReliabilityQosPolicy const& value) noexcept
        {
            m_reliability = value;
        }

        /**
         * @brief This function get the LifespanQosPolicy.
         * @return Const reference of the LifespanQosPolicy
         */
        inline dds::qos::LifespanQosPolicy const& lifespan() const noexcept
        {
            return m_lifespan;
        }

        /**
         * @brief This function set the LifespanQosPolicy.
         * @param [in] value Const reference of the LifespanQosPolicy to be set to
         */
        inline gvoid_t lifespan(dds::qos::LifespanQosPolicy const& value) noexcept
        {
            m_lifespan = value;
        }

        /**
         * @brief This function get the TimeBasedFilterQosPolicy.
         * @return Const reference of the TimeBasedFilterQosPolicy
         */
        inline dds::qos::TimeBasedFilterQosPolicy const& time_based_filter() const noexcept
        {
            return m_timeBasedFilter;
        }

        /**
         * @brief This function set the TimeBasedFilterQosPolicy.
         * @param [in] value Const reference of the TimeBasedFilterQosPolicy to be set to
         */
        inline gvoid_t time_based_filter(dds::qos::TimeBasedFilterQosPolicy const& value) noexcept
        {
            m_timeBasedFilter = value;
        }

        /**
         * @brief This function get the OwnershipQosPolicy.
         * @return Const reference of the OwnershipQosPolicy
         */
        inline dds::qos::OwnershipQosPolicy const& ownership() const noexcept
        {
            return m_ownership;
        }

        /**
         * @brief This function set the OwnershipQosPolicy.
         * @param [in] value Const reference of the OwnershipQosPolicy to be set to
         */
        inline gvoid_t ownership(dds::qos::OwnershipQosPolicy const& value) noexcept
        {
            m_ownership = value;
        }

        /**
         * @brief This function get the OwnershipStrengthQosPolicy.
         * @return Const reference of the OwnershipStrengthQosPolicy
         */
        inline dds::qos::OwnershipStrengthQosPolicy const& ownership_strength() const noexcept
        {
            return m_ownershipStrength;
        }

        /**
         * @brief This function set the OwnershipStrengthQosPolicy.
         * @param [in] value Const reference of the OwnershipStrengthQosPolicy to be set to
         */
        inline gvoid_t ownership_strength(dds::qos::OwnershipStrengthQosPolicy const& value) noexcept
        {
            m_ownershipStrength = value;
        }

        /**
         * @brief This function get the DestinationOrderQosPolicy.
         * @return Const reference of the DestinationOrderQosPolicy
         */
        inline dds::qos::DestinationOrderQosPolicy const& destination_order() const noexcept
        {
            return m_destinationOrder;
        }

        /**
         * @brief This function set the DestinationOrderQosPolicy.
         * @param [in] value Const reference of the DestinationOrderQosPolicy to be set to
         */
        inline gvoid_t destination_order(dds::qos::DestinationOrderQosPolicy const& value) noexcept
        {
            m_destinationOrder = value;
        }

        /**
         * @brief This function get the PresentationQosPolicy.
         * @return Const reference of the PresentationQosPolicy
         */
        inline dds::qos::PresentationQosPolicy const& presentation() const noexcept
        {
            return m_presentation;
        }

        /**
         * @brief This function set the PresentationQosPolicy.
         * @param [in] value Const reference of the PresentationQosPolicy to be set to
         */
        inline gvoid_t presentation(dds::qos::PresentationQosPolicy const& value) noexcept
        {
            m_presentation = value;
        }

        /**
         * @brief This function get the PartitionQosPolicy.
         * @return Const reference of the PartitionQosPolicy
         */
        inline dds::qos::PartitionQosPolicy const& partition() const noexcept
        {
            return m_partition;
        }

        /**
         * @brief This function set the PartitionQosPolicy.
         * @param [in] value Const reference of the PartitionQosPolicy to be set to
         */
        inline gvoid_t partition(dds::qos::PartitionQosPolicy const& value) noexcept
        {
            m_partition = value;
        }

        /**
         * @brief This function get the FlowControlQosPolicy.
         * @return Const reference of the FlowControlQosPolicy
         */
        inline dds::qos::FlowControlQosPolicy const& flow_control() const noexcept
        {
            return m_flowControl;
        }

        /**
         * @brief This function set the FlowControlQosPolicy.
         * @param [in] value Const reference of the FlowControlQosPolicy to be set to
         */
        inline gvoid_t flow_control(dds::qos::FlowControlQosPolicy const& value) noexcept
        {
            m_flowControl = value;
        }

        inline dds::qos::DisablePositiveACKsQosPolicy const& disable_positive_acks() const noexcept
        {
            return m_disablePositiveACKs;
        }

        inline gvoid_t disable_positive_acks(dds::qos::DisablePositiveACKsQosPolicy const& value) noexcept
        {
            m_disablePositiveACKs = value;
        }

        /**
         * @brief This function get the security info.
         * @return Const reference of the security info
         */
        inline gstone::security::EndpointSecurityInfo const& security_info() const noexcept
        {
            return m_securityInfo;
        }

        /**
         * @brief This function set the security info.
         * @param [in] value Const reference of the security info to be set to
         */
        inline gvoid_t security_info(gstone::security::EndpointSecurityInfo const& value) noexcept
        {
            m_securityInfo = value;
        }

        /**
         * @brief This function set the HistoryQosPolicy.
         * @param [in] value Const reference of the HistoryQosPolicy to be set to
         */
        inline gvoid_t history(dds::qos::HistoryQosPolicy const &value) noexcept
        {
            m_history = value;
        }

        /**
         * @brief This function get the HistoryQosPolicy.
         * @return Const reference of the HistoryQosPolicy
         */
        inline gstone::rtps::DdsOptionalMember<dds::qos::HistoryQosPolicy> const& history() const noexcept
        {
            return m_history;
        }

        /**
         * @brief This function deserialize builtin topic key with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_key(DdsCdr& cdr, guint16_t const id) noexcept
        {
            std::array<octet, gstone::rtps::BuiltinTopicKey_t::BUILTIN_TOPIC_KEY_SIZE> key_;
            cdr.deserialize(key_, id);
            m_key.value(key_);
        }

        /**
         * @brief This function deserialize builtin participant topic key with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_participant_key(DdsCdr& cdr, guint16_t const id) noexcept
        {
            std::array<octet, gstone::rtps::BuiltinTopicKey_t::BUILTIN_TOPIC_KEY_SIZE> key_;
            cdr.deserialize(key_, id);
            m_participantKey.value(key_);
        }

        /**
         * @brief This function deserialize builtin topic name with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_topic_name(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_topicName, id);
        }

        /**
         * @brief This function deserialize builtin type key with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_type_name(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_typeName, id);
        }

        /**
         * @brief This function deserialize the UserDataPolicy with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_user_data(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_userData, id);
        }

        /**
         * @brief This function deserialize the TopicDataQosPolicy with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_topic_data(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_topicData, id);
        }

        /**
         * @brief This function deserialize the GroupDataQosPolicy with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_group_data(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_groupData, id);
        }

        /**
         * @brief This function deserialize the DurabilityQosPolicy  with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_durability(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_durability, id);
        }

        /**
         * @brief This function deserialize the DeadlineQosPolicy with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_deadline(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_deadline, id);
        }

        /**
         * @brief This function deserialize the LatencyBudgetQosPolicy with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_latency_budget(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_latencyBudget, id);
        }

        /**
         * @brief This function deserialize the LivelinessQosPolicy with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_liveliness(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_liveliness, id);
        }

        /**
         * @brief This function deserialize the ReliabilityQosPolicy with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_reliability(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_reliability, id);
        }

        /**
         * @brief This function deserialize the LifespanQosPolicy with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_lifespan(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_lifespan, id);
        }

        /**
         * @brief This function deserialize the TimeBasedFilterQosPolicy with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_time_based_filter(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_timeBasedFilter, id);
        }

        /**
         * @brief This function deserialize the OwnershipQosPolicy with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_ownership(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_ownership, id);
        }

        /**
         * @brief This function deserialize the OwnershipStrengthQosPolicy with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_ownership_strength(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_ownershipStrength, id);
        }

        /**
         * @brief This function deserialize the DestinationOrderQosPolicy with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_destination_order(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_destinationOrder, id);
        }

        /**
         * @brief This function deserialize the PartitionQosPolicy with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_partition(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_partition, id);
        }

        /**
         * @brief This function deserialize the FlowControlQosPolicy with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_flow_control(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_flowControl, id);
        }

        inline gvoid_t deserialize_disable_positive_ack(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_disablePositiveACKs, id);
        }

        /**
         * @brief This function deserialize security_info with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_security_info(DdsCdr& cdr, guint16_t const id) noexcept
        {
            std::array<uint32_t, PUB_SECURITY_INFO_LENGTH> t;
            //uint32_t t[PUB_SECURITY_INFO_LENGTH];
            uint32_t const s{ sizeof(t) };
            cdr.deserialize(t.data(), s, id);
            //cdr.deserialize(reinterpret_cast<octet *>(&t), s, id);
            m_securityInfo.endpoint_security_attributes = t[0U];
            m_securityInfo.plugin_endpoint_security_attributes = t[1U];
        }

        /**
         * @brief This function deserialize the PresentationQosPolicy with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_presentation(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_presentation, id);
        }

        /**
         * @brief This function deserialize the HistoryQosPolicy with CDR deserialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id The parameter id.
         */
        inline gvoid_t deserialize_history(DdsCdr& cdr, guint16_t const id) noexcept
        {
            cdr.deserialize(m_history, id);
        }

    private:
        gstone::rtps::BuiltinTopicKey_t m_key;
        gstone::rtps::BuiltinTopicKey_t m_participantKey;
        std::string m_topicName;
        std::string m_typeName;

        /* optional qos */
        dds::qos::UserDataQosPolicy m_userData;
        dds::qos::TopicDataQosPolicy m_topicData;
        dds::qos::GroupDataQosPolicy m_groupData;

        dds::qos::DurabilityQosPolicy m_durability;
        dds::qos::DurabilityServiceQosPolicy m_durabilityService;
        dds::qos::DeadlineQosPolicy m_deadline;
        dds::qos::LatencyBudgetQosPolicy m_latencyBudget;
        dds::qos::LivelinessQosPolicy m_liveliness;
        dds::qos::ReliabilityQosPolicy m_reliability;
        dds::qos::LifespanQosPolicy m_lifespan;
        dds::qos::TimeBasedFilterQosPolicy m_timeBasedFilter;
        dds::qos::OwnershipQosPolicy m_ownership;
        dds::qos::OwnershipStrengthQosPolicy m_ownershipStrength;
        dds::qos::DestinationOrderQosPolicy m_destinationOrder;
        dds::qos::PresentationQosPolicy m_presentation;
        dds::qos::PartitionQosPolicy m_partition;
        dds::qos::FlowControlQosPolicy m_flowControl;
        dds::qos::DisablePositiveACKsQosPolicy m_disablePositiveACKs;

        gstone::security::EndpointSecurityInfo m_securityInfo;
        gstone::rtps::DdsOptionalMember<dds::qos::HistoryQosPolicy> m_history;
    };
}/*topic*/
}/*dds*/

#endif
