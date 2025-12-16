/**************************************************************
* @file ConfigParser.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
*  All rights reserved
**************************************************************/

#include "ConfigParser.h"

namespace {
    const std::map<std::string, greenstone::dds::DurabilityQosPolicyKind> DURABILITY_QOS_POLICY_MAP = {
        std::pair<std::string, greenstone::dds::DurabilityQosPolicyKind>(
            "VOLATILE_DURABILITY_QOS", greenstone::dds::DurabilityQosPolicyKind::VOLATILE_DURABILITY_QOS),
        std::pair<std::string, greenstone::dds::DurabilityQosPolicyKind>(
            "TRANSIENT_LOCAL_DURABILITY_QOS", greenstone::dds::DurabilityQosPolicyKind::TRANSIENT_LOCAL_DURABILITY_QOS),
        std::pair<std::string, greenstone::dds::DurabilityQosPolicyKind>(
            "TRANSIENT_DURABILITY_QOS", greenstone::dds::DurabilityQosPolicyKind::TRANSIENT_DURABILITY_QOS),
        std::pair<std::string, greenstone::dds::DurabilityQosPolicyKind>(
            "PERSISTENT_DURABILITY_QOS", greenstone::dds::DurabilityQosPolicyKind::PERSISTENT_DURABILITY_QOS)
    };

    const std::map<std::string, greenstone::dds::HistoryQosPolicyKind> HISTORY_QOS_POLICY_MAP = {
        std::pair<std::string, greenstone::dds::HistoryQosPolicyKind>(
            "KEEP_LAST_HISTORY_QOS", greenstone::dds::HistoryQosPolicyKind::KEEP_LAST_HISTORY_QOS),
        std::pair<std::string, greenstone::dds::HistoryQosPolicyKind>(
            "KEEP_ALL_HISTORY_QOS", greenstone::dds::HistoryQosPolicyKind::KEEP_ALL_HISTORY_QOS)
    };

    const std::map<std::string, greenstone::dds::ReliabilityQosPolicyKind> RELIABILITY_QOS_POLICY_MAP = {
        std::pair<std::string, greenstone::dds::ReliabilityQosPolicyKind>(
            "RELIABLE_RELIABILITY_QOS", greenstone::dds::ReliabilityQosPolicyKind::RELIABLE_RELIABILITY_QOS),
        std::pair<std::string, greenstone::dds::ReliabilityQosPolicyKind>(
            "BEST_EFFORT_RELIABILITY_QOS", greenstone::dds::ReliabilityQosPolicyKind::BEST_EFFORT_RELIABILITY_QOS)
    };

    const std::map<std::string, greenstone::dds::OwnershipQosPolicyKind> OWNERSHIP_QOS_POLICY_MAP = {
        std::pair<std::string, greenstone::dds::OwnershipQosPolicyKind>(
            "SHARED_OWNERSHIP_QOS", greenstone::dds::OwnershipQosPolicyKind::SHARED_OWNERSHIP_QOS),
        std::pair<std::string, greenstone::dds::OwnershipQosPolicyKind>(
            "EXCLUSIVE_OWNERSHIP_QOS", greenstone::dds::OwnershipQosPolicyKind::EXCLUSIVE_OWNERSHIP_QOS)
    };

    const std::map<std::string, greenstone::dds::LivelinessQosPolicyKind> LIVELINESS_QOS_POLICY_MAP = {
        std::pair<std::string, greenstone::dds::LivelinessQosPolicyKind>(
            "AUTOMATIC_LIVELINESS_QOS", greenstone::dds::LivelinessQosPolicyKind::AUTOMATIC_LIVELINESS_QOS),
        std::pair<std::string, greenstone::dds::LivelinessQosPolicyKind>(
            "MANUAL_BY_PARTICIPANT_LIVELINESS_QOS", greenstone::dds::LivelinessQosPolicyKind::MANUAL_BY_PARTICIPANT_LIVELINESS_QOS),
        std::pair<std::string, greenstone::dds::LivelinessQosPolicyKind>(
            "MANUAL_BY_TOPIC_LIVELINESS_QOS", greenstone::dds::LivelinessQosPolicyKind::MANUAL_BY_TOPIC_LIVELINESS_QOS)
    };

    const std::map<std::string, greenstone::dds::DestinationOrderQosPolicyKind> DESTINATION_ORDER_QOS_POLICY_MAP = {
        std::pair<std::string, greenstone::dds::DestinationOrderQosPolicyKind>(
            "BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS", 
            greenstone::dds::DestinationOrderQosPolicyKind::BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS),
        std::pair<std::string, greenstone::dds::DestinationOrderQosPolicyKind>(
            "BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS", 
            greenstone::dds::DestinationOrderQosPolicyKind::BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS)
    };

    const std::map<std::string, greenstone::dds::RecvMode_t> RECV_MODE_MAP = {
        std::pair<std::string, greenstone::dds::RecvMode_t>("true", greenstone::dds::RecvMode_t::SynchRecvMode),
        std::pair<std::string, greenstone::dds::RecvMode_t>("false", greenstone::dds::RecvMode_t::AsyncRecvMode)};
}

gbool_t ConfigParser::load_config_file(const std::string& configPath)
{
    std::ifstream jsonfile(configPath);
    try
    {
        jsonfile >> m_j;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    jsonfile.close();
    m_initialized = true;
    return true;
}

ParticipantQosPtr ConfigParser::get_participant_qos_from_json(const char* participantConfigName)
{
    if (!m_initialized)
    {
        std::cout << "Please run LoadCfgFile() for initialization first!" << std::endl;
        return nullptr;
    }

    if (!(m_j.contains("domain_participant_qos")))
    {
        std::cout << "domain_participant_qos not found in json file!" << std::endl;
        return nullptr;
    }

    if (!(m_j["domain_participant_qos"].contains(participantConfigName)))
    {
        std::cout << participantConfigName << " not found in domain_participant_qos in json file!" << std::endl;
        return nullptr;
    }

    ParticipantQosPtr participantQos = std::make_shared<greenstone::dds::DomainParticipantQos>();
    greenstone::dds::ParticipantAttributes participantAttr;
    greenstone::dds::SEDPAttributes sedpAttr;

    auto jSub = m_j["domain_participant_qos"][participantConfigName];

    // participantAttr.use_builtin_transports(true);
    // participantAttr.spdp_attributes().metatraffic_unicast_locators().push_back(get_locator_from_address("127.0.0.1"));

    participantAttr.async_thread_size(get_number<guint32_t>(3, jSub, "async_thread_size"));
    
    participantAttr.shared_memory_size(get_number<guint32_t>(100 * 1024 * 1024, jSub, "shared_memory_size"));
    participantAttr.spdp_attributes().domain_id(get_number<guint32_t>(10, jSub, "domain_id"));
    // localhost into spdp_attributes.metatraffic_unicast_locators
    gstone::rtps::LocatorList_t temp = get_locator_list(
        participantAttr.spdp_attributes().metatraffic_unicast_locators(), jSub, "local_host");
    for (size_t i = 0; i < temp.size(); i++)
    {
        participantAttr.spdp_attributes().add_meta_unicast_locator(temp[i]);
    }
    
    participantAttr.spdp_attributes().default_remote_unicast_locators(get_locator_list(
        participantAttr.spdp_attributes().default_remote_unicast_locators(), jSub, "remote_unicast_list"));

    // unicast_list into unicast_transport_list
    gstone::rtps::LocatorList_t tmp;
    tmp = get_locator_list(tmp, jSub, "transport_locator_list");
    for (size_t i = 0; i < tmp.size(); i++)
    {
        char addr[tmp[i].ADDRESS_SIZE];
        for (size_t j = 0; j < tmp[i].ADDRESS_SIZE; j++)
        {
            addr[j] = (char) tmp[i].address()[j];
        }
        
        participantAttr.add_unicast_transport(tmp[i].kind(), tmp[i].port(), addr);
    }

    participantAttr.default_multicast_locatorlist(get_locator_list(
        participantAttr.default_multicast_locatorlist(), jSub, "multicast_list"));
    participantAttr.participant_id(get_number<guint32_t>(10, jSub, "participant_id"));
    participantAttr.spdp_attributes().lease_duration(get_duration(greenstone::dds::Duration_t(30000), jSub, "lease_duration"));
    participantAttr.recv_mode(
        get_enum<greenstone::dds::RecvMode_t>(
            greenstone::dds::RecvMode_t::AsyncRecvMode, jSub, RECV_MODE_MAP, "RecvMode", "recv_sync"));
    participantAttr.used_wlp(get_bool(false, jSub, "useWLP"));
    participantAttr.enable_monitoring(get_bool(false, jSub, "enable_monitoring"));
    // participantAttr.spdp_attributes().domain_tag(get_string("DefaultTag", jSub, "domain_tag"));
    
    sedpAttr.heartbeat_period(get_duration(greenstone::dds::Duration_t(2000), jSub, "heartbeat_period"));
    participantAttr.sedp_attributes(sedpAttr);

    participantQos->rtps_participant_attributes(participantAttr);
    greenstone::dds::EntityFactoryQosPolicy entityFactory;
    entityFactory.autoenable_created_entities(get_bool(true, jSub, "entity_factory", "autoenable_created_entities"));
    participantQos->entity_factory(entityFactory);
    greenstone::dds::UserDataQosPolicy userData;
    userData.value(get_qos_data(userData.value(), jSub, "user_data", "value"));
    participantQos->user_data(userData);
    if (jSub.contains("enable_security") && jSub["enable_security"].get<bool>())
    {
        set_security_qos(participantQos);
    }

    return participantQos;
}

PublisherQosPtr ConfigParser::get_publisher_qos_from_json(const char* publisherConfigName)
{
    if (!m_initialized)
    {
        std::cout << "Please run LoadCfgFile() for initialization first!" << std::endl;
        return nullptr;
    }

    PublisherQosPtr pubQos = std::make_shared<greenstone::dds::PublisherQos>();

    if (m_j.contains("publisher_qos") && m_j["publisher_qos"].contains(publisherConfigName))
    {
        auto jSub = m_j["publisher_qos"][publisherConfigName];

        greenstone::dds::GroupDataQosPolicy groupData;
        groupData.value(get_qos_data(groupData.value(), jSub, "group_data", "value"));
        pubQos->group_data(groupData);

        greenstone::dds::EntityFactoryQosPolicy entityFactory;
        entityFactory.autoenable_created_entities(
            get_bool(true, jSub, "entity_factory", "autoenable_created_entities"));
        pubQos->entity_factory(entityFactory);

        greenstone::dds::PartitionQosPolicy partitionQos;
        partitionQos.value(get_string_sequence(partitionQos.value(), jSub, "partition", "value"));
        pubQos->partition(partitionQos);
    }

    return pubQos;
}

SubscriberQosPtr ConfigParser::get_subscriber_qos_from_json(const char* subscriberConfigName)
{
    if (!m_initialized)
    {
        std::cout << "Please run LoadCfgFile() for initialization first!" << std::endl;
        return nullptr;
    }

    SubscriberQosPtr subQos = std::make_shared<greenstone::dds::SubscriberQos>();

    if (m_j.contains("subscriber_qos") && m_j["subscriber_qos"].contains(subscriberConfigName))
    {
        auto jSub = m_j["subscriber_qos"][subscriberConfigName];

        greenstone::dds::GroupDataQosPolicy groupData;
        groupData.value(get_qos_data(groupData.value(), jSub, "group_data", "value"));
        subQos->group_data(groupData);

        greenstone::dds::EntityFactoryQosPolicy entityFactory;
        entityFactory.autoenable_created_entities(
            get_bool(true, jSub, "entity_factory", "autoenable_created_entities"));
        subQos->entity_factory(entityFactory);

        greenstone::dds::PartitionQosPolicy partitionQos;
        partitionQos.value(get_string_sequence(partitionQos.value(), jSub, "partition", "value"));
        subQos->partition(partitionQos);
    }

    return subQos;
}

WriterQosPtr ConfigParser::get_writer_qos_from_json(const char* writerConfigName)
{
    if (!m_initialized)
    {
        std::cout << "Please run LoadCfgFile() for initialization first!" << std::endl;
        return nullptr;
    }

    if (!(m_j.contains("writer_qos")))
    {
        std::cout << "writer_qos not found in json file!" << std::endl;
        return nullptr;
    }

    if (!(m_j["writer_qos"].contains(writerConfigName)))
    {
        std::cout << writerConfigName << " not found in writer_qos in json file!" << std::endl;
        return nullptr;
    }

    WriterQosPtr writerQos = std::make_shared<greenstone::dds::DataWriterQos>();

    auto jSub = m_j["writer_qos"][writerConfigName];

    greenstone::dds::ResourceLimitsQosPolicy resourceLimits;
    resourceLimits.max_samples(get_number<uint32_t>(50, jSub, "resource_limits", "max_samples"));
    resourceLimits.max_instances(get_number<uint32_t>(1, jSub, "resource_limits", "max_instances"));
    resourceLimits.max_samples_per_instance(
        get_number<uint32_t>(50, jSub, "resource_limits", "max_samples_per_instance"));
    writerQos->resource_limits(resourceLimits);

    greenstone::dds::DurabilityQosPolicy durability;
    durability.kind(
        get_enum<greenstone::dds::DurabilityQosPolicyKind>(
            greenstone::dds::DurabilityQosPolicyKind::VOLATILE_DURABILITY_QOS, jSub, 
            DURABILITY_QOS_POLICY_MAP, "Durability", "durability", "kind"));
    writerQos->durability(durability);

    greenstone::dds::HistoryQosPolicy history;
    history.kind(
        get_enum<greenstone::dds::HistoryQosPolicyKind>(
            greenstone::dds::HistoryQosPolicyKind::KEEP_ALL_HISTORY_QOS, jSub, 
            HISTORY_QOS_POLICY_MAP, "History", "history", "kind"));
    history.depth(get_number<uint32_t>(1, jSub, "history", "depth"));
    writerQos->history(history);

    greenstone::dds::ReliabilityQosPolicy reliability;
    reliability.kind(
        get_enum<greenstone::dds::ReliabilityQosPolicyKind>(
            greenstone::dds::ReliabilityQosPolicyKind::RELIABLE_RELIABILITY_QOS, jSub, 
            RELIABILITY_QOS_POLICY_MAP, "Reliability", "reliability", "kind"));
    reliability.max_blocking_time(
        get_duration(greenstone::dds::Duration_t(100), jSub, "reliability", "max_blocking_time"));
    writerQos->reliability(reliability);

    greenstone::dds::FlowControlQosPolicy flow_ctrl;
    flow_ctrl.limits(
        get_number<uint32_t>(0U, jSub, "flow_ctrl", "limits")
    );
    flow_ctrl.period(
        get_number<uint32_t>(0U, jSub, "flow_ctrl", "period")
    );

    greenstone::dds::OwnershipQosPolicy ownership;
    ownership.kind(
        get_enum<greenstone::dds::OwnershipQosPolicyKind>(
            greenstone::dds::OwnershipQosPolicyKind::SHARED_OWNERSHIP_QOS, jSub, 
            OWNERSHIP_QOS_POLICY_MAP, "Ownership", "ownership", "kind"));
    writerQos->ownership(ownership);

    greenstone::dds::OwnershipStrengthQosPolicy ownershipStrength;
    ownershipStrength.value(get_number<uint32_t>(0, jSub, "ownership_strength", "value"));
    writerQos->ownership_strength(ownershipStrength);

    greenstone::dds::LivelinessQosPolicy liveliness;
    liveliness.kind(
        get_enum<greenstone::dds::LivelinessQosPolicyKind>(
            greenstone::dds::LivelinessQosPolicyKind::AUTOMATIC_LIVELINESS_QOS, jSub, 
            LIVELINESS_QOS_POLICY_MAP, "Liveliness", "liveliness", "kind"));
    liveliness.lease_duration(
        get_duration(greenstone::dds::Duration_t().duration_infinite(), jSub, "liveliness", "lease_duration"));
    writerQos->liveliness(liveliness);

    greenstone::dds::DeadlineQosPolicy deadline;
    deadline.period(get_duration(greenstone::dds::Duration_t().duration_infinite(), jSub, "deadline", "period"));
    writerQos->deadline(deadline);

    greenstone::dds::LifespanQosPolicy lifespan;
    lifespan.duration(get_duration(greenstone::dds::Duration_t().duration_infinite(), jSub, "lifespan", "duration"));
    writerQos->life_span(lifespan);

    greenstone::dds::LatencyBudgetQosPolicy latencyBudget;
    latencyBudget.duration(
        get_duration(greenstone::dds::Duration_t().duration_zero(), jSub, "latency_budget", "duration"));
    writerQos->latency_budget(latencyBudget);

    greenstone::dds::TransportPriorityQosPolicy transportPriority;
    transportPriority.value(get_number<uint32_t>(0, jSub, "transport_priority", "value"));
    writerQos->transport_priority(transportPriority);

    greenstone::dds::DestinationOrderQosPolicy destinationOrder;
    destinationOrder.kind(
        get_enum<greenstone::dds::DestinationOrderQosPolicyKind>(
            greenstone::dds::DestinationOrderQosPolicyKind::BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS, jSub, 
            DESTINATION_ORDER_QOS_POLICY_MAP, "DestinationOrder", "destination_order", "kind"));
    writerQos->destination_order(destinationOrder);

    greenstone::dds::WriterDataLifecycleQosPolicy writerDataLifecycle;
    writerDataLifecycle.autodispose_unregistered_instances(
        get_bool(true, jSub, "writer_data_lifecycle", "autodispose_unregistered_instances"));
    writerQos->writer_data_lifecycle(writerDataLifecycle);

    greenstone::dds::UserDataQosPolicy userData;
    userData.value(get_qos_data(userData.value(), jSub, "user_data", "value"));
    writerQos->user_data(userData);

    greenstone::dds::DataWriterAttributes datawriterAttr;
    if (get_bool(false, jSub, "attributes", "only_recv_by_udp")) {
        datawriterAttr.only_recv_by_udp(true);
    } else {
        datawriterAttr.only_recv_by_udp(false);
    }
    std::vector<std::string> tmp;
    tmp = get_string_sequence(tmp, jSub, "attributes", "prefer_transport_kind");
    if (tmp.size() == 0)
    {
        // datawriterAttr.push_back_prefer_transport_kind(gstone::rtps::TransportKind_t::TRANSPORT_KIND_CORE_SHM_R);
        // datawriterAttr.push_back_prefer_transport_kind(gstone::rtps::TransportKind_t::TRANSPORT_KIND_RPMSG_R);
        // datawriterAttr.push_back_prefer_transport_kind(gstone::rtps::TransportKind_t::TRANSPORT_KIND_SHM);
    } else {
        for (size_t i = 0; i < tmp.size(); i++)
        {
            std::string kind_string = tmp[i];
            // std::cout << "writer kind " << kind_string <<std::endl;
            if (kind_string == "TRANSPORT_KIND_UDPv4" || kind_string == "UDPv4")
            {
                datawriterAttr.push_back_prefer_transport_kind(gstone::rtps::TransportKind_t::TRANSPORT_KIND_UDPv4);
            }
            else if (kind_string == "TRANSPORT_KIND_TCPv4" || kind_string == "TCPv4")
            {
                datawriterAttr.push_back_prefer_transport_kind(gstone::rtps::TransportKind_t::TRANSPORT_KIND_TCPv4);
            }
            else if (kind_string == "TRANSPORT_KIND_RPMSG_R" || kind_string == "TRANSPORT_KIND_RPMSG" || kind_string == "RPMSG_R" || kind_string == "RPMSG")
            {
                datawriterAttr.push_back_prefer_transport_kind(gstone::rtps::TransportKind_t::TRANSPORT_KIND_RPMSG_R);
            }
            else if (kind_string == "TRANSPORT_KIND_CORE_SHM_R" || kind_string == "TRANSPORT_KIND_CORE_SHM" || kind_string == "CORE_SHM" || kind_string == "CORESHM")
            {
                datawriterAttr.push_back_prefer_transport_kind(gstone::rtps::TransportKind_t::TRANSPORT_KIND_CORE_SHM_R);
            }
            else if (kind_string == "TRANSPORT_KIND_SHM" || kind_string == "SHM")
            {
                datawriterAttr.push_back_prefer_transport_kind(gstone::rtps::TransportKind_t::TRANSPORT_KIND_SHM);
            }
        }
    }
    
    // datawriterAttr.is_stateful(get_bool(true, jSub, "attributes", "stateful"));
    datawriterAttr.push_mode(get_bool(true, jSub, "attributes", "push_mode"));
    datawriterAttr.is_sync(get_bool(true, jSub, "attributes", "sync"));
    // datawriterAttr.comm_kind(get_number<uint32_t>(1, jSub, "attributes", "comm_kind"));
    // datawriterAttr.is_auto_op(get_bool(true, jSub, "attributes", "auto_op"));
    datawriterAttr.heartbeat_period(get_number<uint32_t>(4, jSub, "attributes", "heartbeat_period"));
    datawriterAttr.nack_response_delay(get_number<uint32_t>(1, jSub, "attributes", "nack_response_delay"));
    datawriterAttr.nack_supper_ression_duration(
        get_number<uint32_t>(1, jSub, "attributes", "nack_suppression_duration"));
    datawriterAttr.history_cache_capacity(
        get_number<uint32_t>(100, jSub, "attributes", "history_cache_capacity"));
    datawriterAttr.max_frag_size(get_number<uint32_t>(65500, jSub, "attributes", "max_frag_size"));
    datawriterAttr.max_shm_frag_size(get_number<uint32_t>(34603008, jSub, "attributes", "max_shm_frag_size"));
    // datawriterAttr.data_channel_flow_ctl_band_width(
    //     get_number<uint32_t>(0, jSub, "attributes", "channel_flow_ctrl"));
    // datawriterAttr.flow_ctl_window_unit(
    //     get_number<uint32_t>(75, jSub, "attributes", "flow_ctl_window_unit"));
    datawriterAttr.hb_with_data_per_seq_num(
        get_number<uint32_t>(10, jSub, "attributes", "hbWithDataPerSeqNum"));
    datawriterAttr.batch_size(get_number<uint32_t>(10, jSub, "attributes", "batchSize"));
    datawriterAttr.enable_zero_copy(get_bool(false, jSub, "attributes", "enableZeroCopy"));
    datawriterAttr.zero_copy_memory_size(
        get_number<uint32_t>(104857600, jSub, "attributes", "zeroCopyMemorySize"));
    datawriterAttr.enable_group_send(get_bool(false, jSub, "attributes", "enableGroupSend"));
    datawriterAttr.enable_ts(get_bool(false, jSub, "attributes", "enableTs"));

    writerQos->attributes(datawriterAttr);

    return writerQos;
}

ReaderQosPtr ConfigParser::get_reader_qos_from_json(const char* readerConfigName)
{
    if (!m_initialized)
    {
        std::cout << "Please run LoadCfgFile() for initialization first!" << std::endl;
        return nullptr;
    }

    if (!(m_j.contains("reader_qos")))
    {
        std::cout << "reader_qos not found in json file!" << std::endl;
        return nullptr;
    }

    if (!(m_j["reader_qos"].contains(readerConfigName)))
    {
        std::cout << readerConfigName << " not found in reader_qos in json file!" << std::endl;
        return nullptr;
    }

    ReaderQosPtr readerQos = std::make_shared<greenstone::dds::DataReaderQos>();

    auto jSub = m_j["reader_qos"][readerConfigName];

    greenstone::dds::ResourceLimitsQosPolicy resourceLimits;
    resourceLimits.max_samples(get_number<uint32_t>(50, jSub, "resource_limits", "max_samples"));
    resourceLimits.max_instances(get_number<uint32_t>(1, jSub, "resource_limits", "max_instances"));
    resourceLimits.max_samples_per_instance(
        get_number<uint32_t>(50, jSub, "resource_limits", "max_samples_per_instance"));
    readerQos->resource_limits(resourceLimits);

    greenstone::dds::DurabilityQosPolicy durability;
    durability.kind(
        get_enum<greenstone::dds::DurabilityQosPolicyKind>(
            greenstone::dds::DurabilityQosPolicyKind::VOLATILE_DURABILITY_QOS, jSub, 
            DURABILITY_QOS_POLICY_MAP, "Durability", "durability", "kind"));
    readerQos->durability(durability);

    greenstone::dds::HistoryQosPolicy history;
    history.kind(
        get_enum<greenstone::dds::HistoryQosPolicyKind>(
            greenstone::dds::HistoryQosPolicyKind::KEEP_ALL_HISTORY_QOS, jSub, 
            HISTORY_QOS_POLICY_MAP, "History", "history", "kind"));
    history.depth(get_number<uint32_t>(1, jSub, "history", "depth"));
    readerQos->history(history);

    greenstone::dds::ReliabilityQosPolicy reliability;
    reliability.kind(
        get_enum<greenstone::dds::ReliabilityQosPolicyKind>(
            greenstone::dds::ReliabilityQosPolicyKind::RELIABLE_RELIABILITY_QOS, jSub, 
            RELIABILITY_QOS_POLICY_MAP, "Reliability", "reliability", "kind"));
    readerQos->reliability(reliability);

    greenstone::dds::OwnershipQosPolicy ownership;
    ownership.kind(
        get_enum<greenstone::dds::OwnershipQosPolicyKind>(
            greenstone::dds::OwnershipQosPolicyKind::SHARED_OWNERSHIP_QOS, jSub, 
            OWNERSHIP_QOS_POLICY_MAP, "Ownership", "ownership", "kind"));
    readerQos->ownership(ownership);

    greenstone::dds::LivelinessQosPolicy liveliness;
    liveliness.kind(
        get_enum<greenstone::dds::LivelinessQosPolicyKind>(
            greenstone::dds::LivelinessQosPolicyKind::AUTOMATIC_LIVELINESS_QOS, jSub, 
            LIVELINESS_QOS_POLICY_MAP, "Liveliness", "liveliness", "kind"));
    liveliness.lease_duration(
        get_duration(greenstone::dds::Duration_t().duration_infinite(), jSub, "liveliness", "lease_duration"));
    readerQos->liveliness(liveliness);

    greenstone::dds::DeadlineQosPolicy deadline;
    deadline.period(get_duration(greenstone::dds::Duration_t().duration_infinite(), jSub, "deadline", "period"));
    readerQos->deadline(deadline);

    greenstone::dds::LatencyBudgetQosPolicy latencyBudget;
    latencyBudget.duration(
        get_duration(greenstone::dds::Duration_t().duration_zero(), jSub, "latency_budget", "duration"));
    readerQos->latency_budget(latencyBudget);

    greenstone::dds::DestinationOrderQosPolicy destinationOrder;
    destinationOrder.kind(
        get_enum<greenstone::dds::DestinationOrderQosPolicyKind>(
            greenstone::dds::DestinationOrderQosPolicyKind::BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS, jSub, 
            DESTINATION_ORDER_QOS_POLICY_MAP, "DestinationOrder", "destination_order", "kind"));
    readerQos->destination_order(destinationOrder);

    greenstone::dds::TimeBasedFilterQosPolicy timeBasedFilter;
    timeBasedFilter.minimum_separation(
        get_duration(greenstone::dds::Duration_t().duration_zero(), jSub, "time_based_filter", "minimum_separation"));
    readerQos->time_based_filter(timeBasedFilter);

    greenstone::dds::ReaderDataLifecycleQosPolicy readerDataLifecycle;
    readerDataLifecycle.autopurge_disposed_samples_delay(
        get_duration(
            greenstone::dds::Duration_t().duration_infinite(), jSub, 
            "reader_data_lifecycle", "autopurge_disposed_samples_delay"));
    readerDataLifecycle.autopurge_nowriter_samples_delay(
        get_duration(
            greenstone::dds::Duration_t().duration_infinite(), jSub, 
            "reader_data_lifecycle", "autopurge_nowriter_samples_delay"));
    readerQos->reader_data_lifecycle(readerDataLifecycle);

    greenstone::dds::UserDataQosPolicy userData;
    userData.value(get_qos_data(userData.value(), jSub, "user_data", "value"));
    readerQos->user_data(userData);

    greenstone::dds::DataReaderAttributes datareaderAttr;
    if (get_bool(false, jSub, "attributes", "only_recv_by_udp")) {
        datareaderAttr.only_recv_by_udp(true);
    } else {
        datareaderAttr.only_recv_by_udp(false);
    }
    std::vector<std::string> tmp;
    tmp = get_string_sequence(tmp, jSub, "attributes", "prefer_transport_kind");
    if (tmp.size() == 0)
    {
        // datareaderAttr.push_back_prefer_transport_kind(gstone::rtps::TransportKind_t::TRANSPORT_KIND_CORE_SHM_R);
        // datareaderAttr.push_back_prefer_transport_kind(gstone::rtps::TransportKind_t::TRANSPORT_KIND_RPMSG_R);
        // datareaderAttr.push_back_prefer_transport_kind(gstone::rtps::TransportKind_t::TRANSPORT_KIND_SHM);
    } else {
        for (size_t i = 0; i < tmp.size(); i++)
        {
            
            std::string kind_string = tmp[i];
            // std::cout << "reader kind " << kind_string <<std::endl;
            if (kind_string == "TRANSPORT_KIND_UDPv4" || kind_string == "UDPv4")
            {
                datareaderAttr.push_back_prefer_transport_kind(gstone::rtps::TransportKind_t::TRANSPORT_KIND_UDPv4);
            }
            else if (kind_string == "TRANSPORT_KIND_TCPv4" || kind_string == "TCPv4")
            {
                datareaderAttr.push_back_prefer_transport_kind(gstone::rtps::TransportKind_t::TRANSPORT_KIND_TCPv4);
            }
            else if (kind_string == "TRANSPORT_KIND_RPMSG_R" || kind_string == "TRANSPORT_KIND_RPMSG" || kind_string == "RPMSG_R" || kind_string == "RPMSG")
            {
                datareaderAttr.push_back_prefer_transport_kind(gstone::rtps::TransportKind_t::TRANSPORT_KIND_RPMSG_R);
            }
            else if (kind_string == "TRANSPORT_KIND_CORE_SHM_R" || kind_string == "TRANSPORT_KIND_CORE_SHM" || kind_string == "CORE_SHM" || kind_string == "CORESHM")
            {
                datareaderAttr.push_back_prefer_transport_kind(gstone::rtps::TransportKind_t::TRANSPORT_KIND_CORE_SHM_R);
            }
            else if (kind_string == "TRANSPORT_KIND_SHM" || kind_string == "SHM")
            {
                datareaderAttr.push_back_prefer_transport_kind(gstone::rtps::TransportKind_t::TRANSPORT_KIND_SHM);
            }
        }
    }    
    // datareaderAttr.comm_kind(get_number<uint32_t>(1, jSub, "attributes", "comm_kind"));
    // datareaderAttr.is_auto_op(get_bool(true, jSub, "attributes", "auto_op"));
    datareaderAttr.heartbeat_response_delay(
        get_duration(greenstone::dds::Duration_t(1), jSub, "attributes", "heartbeat_response_delay"));
    datareaderAttr.heartbeat_suppression_duration(
        get_duration(greenstone::dds::Duration_t(1), jSub, "attributes", "heartbeat_suppression_duration"));
    datareaderAttr.ack_with_data_per_seq_num(
        get_number<uint32_t>(10, jSub, "attributes", "ack_with_data_per_seq_num"));

    readerQos->attributes(datareaderAttr);

    return readerQos;
}

TopicQosPtr ConfigParser::get_topic_qos_from_json(const char* topicConfigName)
{
    if (!m_initialized)
    {
        std::cout << "Please run LoadCfgFile() for initialization first!" << std::endl;
        return nullptr;
    }

    TopicQosPtr topicQos = std::make_shared<greenstone::dds::TopicQos>();
    if (m_j.contains("topic_qos") && m_j["topic_qos"].contains(topicConfigName))
    {
        auto jSub = m_j["topic_qos"][topicConfigName];
        if (jSub.contains("topic_data"))
        {
            greenstone::dds::TopicDataQosPolicy topicData;
            topicData.value(get_qos_data(topicData.value(), jSub, "topic_data", "value"));
            topicQos->topic_data(topicData);
        }
    }

    return topicQos;
}

greenstone::dds::DomainParticipant* ConfigParser::get_participant_from_json(
    const char* participantConfigName,
    greenstone::dds::DomainParticipantListener* listener,
    const greenstone::dds::StatusMask& mask,
    const gbool_t& autoenableParticipant)
{
    greenstone::dds::DomainParticipantFactoryQos domainParticipantFactoryQos;
    greenstone::dds::EntityFactoryQosPolicy entityFactory;
    entityFactory.autoenable_created_entities(autoenableParticipant);
    domainParticipantFactoryQos.entity_factory(entityFactory);
    greenstone::dds::DomainParticipantFactory::get_instance()->set_qos(domainParticipantFactoryQos);
    
    ParticipantQosPtr participantQos = get_participant_qos_from_json(participantConfigName);
    greenstone::dds::DomainParticipant* dpPtr = 
        greenstone::dds::DomainParticipantFactory::get_instance()->create_participant(
            participantQos->rtps_participant_attributes().spdp_attributes().domain_id(), 
            *participantQos, listener, mask);
    return dpPtr;
}

greenstone::dds::Publisher* ConfigParser::get_publisher_from_json(
    const char* publisherConfigName,
    greenstone::dds::DomainParticipant* domainParticipant,
    greenstone::dds::PublisherListener* listener,
    const greenstone::dds::StatusMask& mask)
{
    PublisherQosPtr pubQos = get_publisher_qos_from_json(publisherConfigName);
    greenstone::dds::Publisher* pubPtr = domainParticipant->create_publisher(*pubQos, nullptr, mask);
    return pubPtr;
}

greenstone::dds::Subscriber* ConfigParser::get_subscriber_from_json(
    const char* subscriberConfigName,
    greenstone::dds::DomainParticipant* domainParticipant,
    greenstone::dds::SubscriberListener *listener,
    const greenstone::dds::StatusMask& mask)
{
    SubscriberQosPtr subQos = get_subscriber_qos_from_json(subscriberConfigName);
    greenstone::dds::Subscriber* subPtr = domainParticipant->create_subscriber(*subQos, nullptr, mask);
    return subPtr;
}

greenstone::dds::DataWriter* ConfigParser::get_writer_from_json(
    const char* writerConfigName,
    greenstone::dds::Publisher* publisher,
    greenstone::dds::Topic* topic,
    greenstone::dds::DataWriterListener* listener,
    const greenstone::dds::StatusMask& mask)
{
    WriterQosPtr writerQos = get_writer_qos_from_json(writerConfigName);
    greenstone::dds::DataWriter* writerPtr = publisher->create_datawriter(topic, *writerQos, listener, mask);
    return writerPtr;
}

greenstone::dds::DataReader* ConfigParser::get_reader_from_json(
    const char* readerConfigName,
    greenstone::dds::Subscriber* subscriber,
    greenstone::dds::Topic* topic,
    greenstone::dds::DataReaderListener* listener,
    const greenstone::dds::StatusMask& mask)
{
    ReaderQosPtr readerQos = get_reader_qos_from_json(readerConfigName);
    greenstone::dds::DataReader* readerPtr = subscriber->create_datareader(topic, *readerQos, listener, mask);
    return readerPtr;
}

greenstone::dds::Topic* ConfigParser::get_topic_from_json(
    const char* topicConfigName,
    greenstone::dds::DomainParticipant* domainParticipant,
    const std::string& topicName,
    const std::string& topicTypeName,
    greenstone::dds::TopicListener* listener,
    const greenstone::dds::StatusMask& mask)
{
    TopicQosPtr topicQos = get_topic_qos_from_json(topicConfigName);
    greenstone::dds::Topic* topicPtr = domainParticipant->create_topic(
        topicName, topicTypeName, *topicQos, listener, mask);
    return topicPtr;
}

greenstone::dds::Locator_t ConfigParser::get_locator_from_address(const std::string& addr)
{
    gint32_t kind;
    std::string ip;
    uint32_t port;

    auto pos1 = addr.find("@");
    if (pos1 == addr.npos)
    {
        kind = greenstone::dds::LOCATOR_KIND_UDPv4;
        pos1 = 0;
    }
    else
    {
        std::string kind_string = addr.substr(0, pos1);
        if (kind_string == "LOCATOR_KIND_UDPv4" || kind_string == "UDPv4")
        {
            kind = greenstone::dds::LOCATOR_KIND_UDPv4;
        }
        else if (kind_string == "LOCATOR_KIND_TCPv4" || kind_string == "TCPv4")
        {
            kind = greenstone::dds::LOCATOR_KIND_TCPv4;
        }
        else if (kind_string == "LOCATOR_KIND_RPMSG_A" || kind_string == "LOCATOR_KIND_RPMSG" || kind_string == "RPMSG_A" || kind_string == "RPMSG")
        {
            kind = greenstone::dds::LOCATOR_KIND_RPMSG_A;
        }
        else if (kind_string == "LOCATOR_KIND_CORE_SHM_A" || kind_string == "LOCATOR_KIND_CORE_SHM" || kind_string == "CORE_SHM" || kind_string == "CORESHM")
        {
            kind = greenstone::dds::LOCATOR_KIND_CORE_SHM_A;
        }
        else if (kind_string == "LOCATOR_KIND_SHM" || kind_string == "SHM")
        {
            kind = greenstone::dds::LOCATOR_KIND_SHM;
        }
        pos1++;
    }

    auto pos2 = addr.find(":");
    if (pos2 == addr.npos)
    {
        ip = addr.substr(pos1);
        port = 0;
    }
    else
    {
        ip = addr.substr(pos1, pos2 - pos1);
        port = atoi(addr.substr(pos2 + 1).c_str());
    }
    // std::cout << "unicast: kind=" << kind << ", ip=" << ip << ", port=" << port << std::endl;

    return greenstone::dds::Locator_t(kind, port, (char*) ip.c_str());
}

greenstone::dds::LocatorList_t ConfigParser::get_locator_list(
    greenstone::dds::LocatorList_t defaultValue, 
    json& jLocator, 
    const std::string& key1, 
    const std::string& key2)
{
    json jValue;
    greenstone::dds::LocatorList_t ret = defaultValue; 
    if (jLocator.contains(key1) && (key2 == ""))
    {
        jValue = jLocator[key1];
    }
    else if (jLocator.contains(key1) && jLocator[key1].contains(key2))
    {
        jValue = jLocator[key1][key2];
    }
    else
    {
        return ret;
    }

    if (jValue.is_string())
    {
        ret.push_back(get_locator_from_address(jValue.get<std::string>()));
    }
    else if (jValue.is_array())
    {
        for (std::string &locator : jValue.get<std::vector<std::string>>())
        {
            ret.push_back(get_locator_from_address(locator));
        }
    }

    return ret;
}

greenstone::dds::Duration_t ConfigParser::get_duration(
    greenstone::dds::Duration_t defaultValue, 
    json& jDuration, 
    const std::string& key1, 
    const std::string& key2)
{
    json jValue;
    greenstone::dds::Duration_t ret = defaultValue;
    if (jDuration.contains(key1) && (key2 == ""))
    {
        jValue = jDuration[key1];
    }
    else if (jDuration.contains(key1) && jDuration[key1].contains(key2))
    {
        jValue = jDuration[key1][key2];
    }
    else
    {
        return ret;
    }
    if (jValue.is_string())
    {
        std::string duration = jValue.get<std::string>();
        if (duration == "Inf" || duration == "inf") 
        {
            ret = greenstone::dds::Duration_t().duration_infinite();
            return ret;
        }
    }
    else if (jValue.is_number())
    {
        uint32_t duration = jValue.get<uint32_t>();
        ret = greenstone::dds::Duration_t(duration);
        return ret;
    }
    else
    {
        std::cout << "Invalid duration setting" << std::endl;
    }
    return ret;
}

gbool_t ConfigParser::get_bool(
    gbool_t defaultValue, 
    json& jBool, 
    const std::string& key1, 
    const std::string& key2)
{
    json jValue;
    gbool_t ret = defaultValue;
    if (jBool.contains(key1) && (key2 == ""))
    {
        jValue = jBool[key1];
    }
    else if (jBool.contains(key1) && jBool[key1].contains(key2))
    {
        jValue = jBool[key1][key2];
    }
    else
    {
        return ret;
    }
    ret = jValue.get<bool>();
    return ret;
}

std::vector<octet> ConfigParser::get_qos_data(
    std::vector<octet> defaultValue, 
    json& jData, 
    const std::string& key1, 
    const std::string& key2)
{
    json jValue;
    std::vector<octet> ret = defaultValue;
    if (jData.contains(key1) && jData[key1].contains(key2))
    {
        jValue = jData[key1][key2];
    }
    else
    {
        return ret;
    }
    std::string str = jValue.get<std::string>();
    for (auto e : str)
    {
        ret.push_back(e);
    }
    return ret;
}

std::string ConfigParser::get_string(
    std::string defaultValue, 
    json& jString, 
    const std::string& key1, 
    const std::string& key2)
{
    json jValue;
    std::string ret = defaultValue;
    if (jString.contains(key1) && (key2 == ""))
    {
        jValue = jString[key1];
    }
    else if (jString.contains(key1) && jString[key1].contains(key2))
    {
        jValue = jString[key1][key2];
    }
    else
    {
        return ret;
    }
    if (jValue.is_string()) {
        ret = jValue.get<std::string>();
    }
    return ret;
}

std::vector<std::string> ConfigParser::get_string_sequence(
    std::vector<std::string> defaultValue, 
    json& jSeq, 
    const std::string& key1, 
    const std::string& key2)
{
    json jValue;
    std::vector<std::string> ret = defaultValue;
    if (jSeq.contains(key1) && jSeq[key1].contains(key2))
    {
        jValue = jSeq[key1][key2];
    }
    else
    {
        return ret;
    }
    ret = jValue.get<std::vector<std::string>>();
    return ret;
}

template <typename T>
std::array<T, 100> ConfigParser::get_number_sequence(
    T defaultValue,
    json& jseq,
    const std::string& key1)
{
    std::array<T, 100> tempArray;
    tempArray.fill(defaultValue);
    if (jseq.contains(key1))
    {
        for (size_t seqSize = 0; seqSize < jseq[key1].get<std::vector<T>>().size() && seqSize < 100; seqSize++)
        {
            if (seqSize == 0)
            {
                tempArray.fill(jseq[key1].get<std::vector<T>>()[0]);
            }
            else
            {
                tempArray[seqSize] = jseq[key1].get<std::vector<T>>()[seqSize];
            }
        }      
    }
    // std::cout << key1 << ": " << std::endl; 
    // for (size_t i = 0; i < 20; i++)
    // {
    //     std::cout << tempArray[i] << std::endl;
    // }
    
    return tempArray;
}

void ConfigParser::set_security_qos(ParticipantQosPtr qos)
{
    // Configure Authentication
    greenstone::dds::PropertyQosPolicy propertyQos = qos->property();
    gstone::PropertySeq propertySeq = propertyQos.value();
    propertySeq.emplace_back("dds.sec.auth.plugin", "builtin.PKI-DH");
    propertySeq.emplace_back("dds.sec.auth.identity_ca", "file:../../certs1/maincacert.pem");
    propertySeq.emplace_back("dds.sec.auth.identity_certificate", "file:../../certs1/partcert.pem");
    propertySeq.emplace_back("dds.sec.auth.private_key", "file:../../certs1/partkey.pem");
    propertySeq.emplace_back("dds.sec.auth.password", ""); // password is ignored if private key is set

    // Configure Access Control
    propertySeq.emplace_back("dds.sec.access.plugin", "builtin.Access-Permissions");
    propertySeq.emplace_back("dds.sec.access.permissions_ca", "file:../../certs1/maincacert.pem");
    propertySeq.emplace_back("dds.sec.access.governance", "file:../../certs1/governance.smime");
    propertySeq.emplace_back("dds.sec.access.permissions", "file:../../certs1/permissions.smime");

    // Configure Cryptography
    propertySeq.emplace_back("dds.sec.crypto.plugin", "builtin.AES-GCM_GMAC");
}
