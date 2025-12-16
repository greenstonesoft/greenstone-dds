/**************************************************************
* @file GeneralListeners.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
*  All rights reserved
**************************************************************/

#include "GeneralListeners.h"

namespace {
    const std::map<greenstone::dds::QosPolicyId_t, std::string> QOS_POLICY_NAMES = {
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::INVALID_QOS_POLICY_ID, ""),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::USERDATA_QOS_POLICY_ID, "USERDATA_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::DURABILITY_QOS_POLICY_ID, "DURABILITY_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::PRESENTATION_QOS_POLICY_ID, "PRESENTATION_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::DEADLINE_QOS_POLICY_ID, "DEADLINE_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::LATENCYBUDGET_QOS_POLICY_ID, "LATENCYBUDGET_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::OWNERSHIP_QOS_POLICY_ID, "OWNERSHIP_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::OWNERSHIPSTRENGTH_QOS_POLICY_ID, "OWNERSHIPSTRENGTH_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::LIVELINESS_QOS_POLICY_ID, "LIVELINESS_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::TIMEBASEDFILTER_QOS_POLICY_ID, "TIMEBASEDFILTER_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::PARTITION_QOS_POLICY_ID, "PARTITION_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::RELIABILITY_QOS_POLICY_ID, "RELIABILITY_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::DESTINATIONORDER_QOS_POLICY_ID, "DESTINATIONORDER_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::HISTORY_QOS_POLICY_ID, "HISTORY_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::RESOURCELIMITS_QOS_POLICY_ID, "RESOURCELIMITS_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::ENTITYFACTORY_QOS_POLICY_ID, "ENTITYFACTORY_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::WRITERDATALIFECYCLE_QOS_POLICY_ID, "WRITERDATALIFECYCLE_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::READERDATALIFECYCLE_QOS_POLICY_ID, "READERDATALIFECYCLE_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::TOPICDATA_QOS_POLICY_ID, "TOPICDATA_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::GROUPDATA_QOS_POLICY_ID, "GROUPDATA_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::TRANSPORTPRIORITY_QOS_POLICY_ID, "TRANSPORTPRIORITY_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::LIFESPAN_QOS_POLICY_ID, "LIFESPAN_QOS_POLICY_NAME"),
        std::pair<greenstone::dds::QosPolicyId_t, std::string>(
            greenstone::dds::DURABILITYSERVICE_QOS_POLICY_ID, "DURABILITYSERVICE_POLICY_NAME")};
}

gvoid_t GeneralParticipantListener::on_participant_matched(
    greenstone::dds::DomainParticipant* participant, 
    dds::topic::ParticipantBuiltinTopicData const &a_remoteData, 
    greenstone::dds::RemoteParticipantInfo const &remoteInfo) noexcept
{
    std::cout << "on participant matched.\n" << std::endl;
    // auto userData = remoteInfo.data().user_data().value();
    // if (userData.size() == 0)
    // {        
    //     if (remoteInfo.status() == greenstone::dds::RemoteParticipantStatus::ONLINE)
    //     {
    //         m_matched++;
    //         std::cout << "[GSDDS on_participant_matched] A new participant with ID of " 
    //                   << remoteInfo.instance_handle() << " has been matched." << std::endl;
    //     } 
    //     else if (remoteInfo.status() == greenstone::dds::RemoteParticipantStatus::OFFLINE) 
    //     {
    //         m_matched--;
    //         std::cout << "[GSDDS on_participant_matched] A participant with ID of " 
    //                   << remoteInfo.instance_handle() << " just left and has been unmatched." << std::endl;
    //     }
    // }
    // else
    // {
    //     if (remoteInfo.status() == greenstone::dds::RemoteParticipantStatus::ONLINE)
    //     {
    //         m_matched++;
    //         std::cout << "[GSDDS on_participant_matched] A new participant with ID of " 
    //                   << remoteInfo.instance_handle() << " and Info of ";
    //         for (auto& e : userData)
    //         {
    //             std::cout << e;
    //         }
    //         std::cout << " has been matched." << std::endl;
    //     } 
    //     else if (remoteInfo.status() == greenstone::dds::RemoteParticipantStatus::OFFLINE) 
    //     {
    //         m_matched--;
    //         std::cout << "[GSDDS on_participant_matched] A participant with ID of " 
    //                   << remoteInfo.instance_handle() << " and Info of ";
    //         for (auto& e : userData)
    //         {
    //             std::cout << e;
    //         }
    //         std::cout << " just left and has been unmatched." << std::endl;
    //     }
    // }
}

void GeneralReaderListener::on_subscription_matched(
    greenstone::dds::DataReader* reader,
    greenstone::dds::SubscriptionMatchedStatus const& status) noexcept
{
    if (status.current_count_change() == 1)
    {
        m_matched++;
        std::cout << "[GSDDS on_subscription_matched] A new datawriter publishing " 
                  << reader->get_topicdescription()->get_name() << " has been matched." << std::endl;
    }
    else
    {
        m_matched--;
        std::cout << "[GSDDS on_subscription_matched] A datawriter publishing " 
                  << reader->get_topicdescription()->get_name() << " just left and has been unmatched." << std::endl;
    }
}

void GeneralReaderListener::on_liveliness_changed(
    greenstone::dds::DataReader* reader,
    greenstone::dds::LivelinessChangedStatus const& status) noexcept
{
    std::cout << "[GSDDS on_liveliness_changed] topic: " << reader->get_topicdescription()->get_name()
              << "; alive_count: " << status.alive_count()
              << "; alive_count_change: " << status.alive_count_change()
              << "; not_alive_count: " << status.not_alive_count()
              << "; not_alive_count_change: " << status.not_alive_count_change()
              << "; last_publication_handle: " << status.last_publication_handle() << std::endl;
}

void GeneralReaderListener::on_requested_incompatible_qos(
    greenstone::dds::DataReader* reader, 
    greenstone::dds::RequestedIncompatibleQosStatus const& status) noexcept
{
    std::cout << "[GSDDS on_requested_incompatible_qos] topic: " << reader->get_topicdescription()->get_name()
                << "; incompatible_qos_policy_name: " << QOS_POLICY_NAMES.at(status.last_policy_id())
                << "; total_count: " << status.total_count()
                << "; total_count_change: " << status.total_count_change() << std::endl;
    for (greenstone::dds::QosPolicyCount policy : status.policies())
    {
        std::cout << "|----policy_name: " << QOS_POLICY_NAMES.at(policy.policy_id()) 
                  << ", count: " << policy.count() << "." << std::endl;
    }
}

void GeneralReaderListener::on_requested_deadline_missed(
    greenstone::dds::DataReader* reader, 
    greenstone::dds::RequestedDeadlineMissedStatus const& status) noexcept
{
    std::cout << "[GSDDS on_offered_deadline_missed] topic: " << reader->get_topicdescription()->get_name()
                << "; total_count: " << status.total_count()
                << "; total_count_change: " << status.total_count_change()
                << "; last_instance_handle: " << status.last_instance_handle() << std::endl;
}
void GeneralReaderListener::on_sample_rejected(
    greenstone::dds::DataReader* reader,
    greenstone::dds::SampleRejectedStatus const& status) noexcept
{
    std::cout << "[GSDDS on_sample_rejected] topic: " << reader->get_topicdescription()->get_name()
              << "; total_count: " << status.total_count()
              << "; total_count_change: " << status.total_count_change()
              << "; last_reason: " << SAMPLE_REJECTED_REASONS[status.last_reason()]
              << "; last_instance_handle: " << status.last_instance_handle() << std::endl;
};

// void GeneralReaderListener::on_sample_lost(
//     greenstone::dds::DataReader* reader,
//     greenstone::dds::SampleLostStatus const& status) noexcept
// {
//     std::cout << "[GSDDS on_sample_lost] topic: " << reader->get_topicdescription()->get_name()
//               << "; total_count: " << status.total_count()
//               << "; total_count_change: " << status.total_count_change() << std::endl;
// };

void GeneralWriterListener::on_publication_matched(
    greenstone::dds::DataWriter* writer,
    greenstone::dds::PublicationMatchedStatus const &status) noexcept
{
    if (status.current_count_change() == 1)
    {
        m_matched++;
        std::cout << "[GSDDS on_publication_matched] A new datareader subscribing " 
                  << writer->get_topic()->get_name() << " has been matched." << std::endl;
    }
    else
    {
        m_matched--;
        std::cout << "[GSDDS on_publication_matched] A datareader subscribing " 
                  << writer->get_topic()->get_name() << " just left and has been unmatched." << std::endl;
    }
}

void GeneralWriterListener::on_liveliness_lost(
		greenstone::dds::DataWriter* writer, 
		greenstone::dds::LivelinessLostStatus const &status) noexcept
{
    std::cout << "[GSDDS on_liveliness_lost] topic: " << writer->get_topic()->get_name()
              << "; total_count: " << status.total_count() << "; total_count_change: "
              << status.total_count_change() << std::endl;
}

void GeneralWriterListener::on_offered_incompatible_qos(
    greenstone::dds::DataWriter* writer,
    greenstone::dds::OfferedIncompatibleQosStatus const &status) noexcept
{
    std::cout << "[GSDDS on_offered_incompatible_qos] topic: " << writer->get_topic()->get_name()
              << "; incompatible_qos_policy_name: " << QOS_POLICY_NAMES.at(status.last_policy_id())
              << "; total_count: " << status.total_count()
              << "; total_count_change: " << status.total_count_change() << std::endl;
    for (greenstone::dds::QosPolicyCount policy : status.policies())
    {
        std::cout << "----policy_name: " << QOS_POLICY_NAMES.at(policy.policy_id()) << ", count: " 
                  << policy.count() << "." << std::endl;
    }
}

void GeneralWriterListener::on_offered_deadline_missed(
    greenstone::dds::DataWriter* writer,
    greenstone::dds::OfferedDeadlineMissedStatus const &status) noexcept
{
    std::cout << "[GSDDS on_offered_deadline_missed] topic: " << writer->get_topic()->get_name()
              << "; total_count: " << status.total_count()
              << "; total_count_change: " << status.total_count_change()
              << "; last_instance_handle: " << status.last_instance_handle() << std::endl;
}
