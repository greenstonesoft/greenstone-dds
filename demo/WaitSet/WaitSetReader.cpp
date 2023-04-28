/**************************************************************
* @file WaitSetReader.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#include "WaitSetReader.h"
#include "ConfigParser.h"

WaitSetReader::WaitSetReader()
    : m_participant(nullptr),
      m_topic(nullptr),
      m_subscriber(nullptr),
      m_reader(nullptr)
{
}

WaitSetReader::~WaitSetReader()
{
}

bool WaitSetReader::init(const std::string& topicName)
{
    // Create participant
    m_participant = ConfigParser::get_instance()->get_participant_from_json(
        "participant_sub_cfg", nullptr, m_mask);
    if (m_participant == nullptr)
    {
        return false;
    }

    // Create topic
    m_participant->register_type(&m_helloworldTopicType);
    std::string topic_type_name = m_helloworldTopicType.get_name();
    m_topic = ConfigParser::get_instance()->get_topic_from_json(
        "topic_cfg", m_participant, topicName, topic_type_name, nullptr, m_mask);

    // Create subscriber
    m_subscriber = ConfigParser::get_instance()->get_subscriber_from_json(
        "subscriber_cfg", m_participant, nullptr,  m_mask);
    if (m_subscriber == nullptr)
    {
        return false;
    }

    // Create datareader
    m_reader = ConfigParser::get_instance()->get_reader_from_json(
        "reader_cfg", m_subscriber, m_topic, nullptr,  m_mask);
    if (m_reader == nullptr)
    {
        return false;
    }

    return true;
}

void WaitSetReader::destroy()
{
    if (m_subscriber->delete_datareader(m_reader) != greenstone::dds::ReturnCode_t::RETCODE_OK)
    {
        std::cout << "Delete reader error" << std::endl;
    }
    if (m_participant->delete_subscriber(m_subscriber) != greenstone::dds::ReturnCode_t::RETCODE_OK)
    {
        std::cout << "Delete subscriber error" << std::endl;
    }
    if (m_participant->delete_topic(m_topic) != greenstone::dds::ReturnCode_t::RETCODE_OK)
    {
        std::cout << "Delete topic error" << std::endl;
    }
    if (greenstone::dds::DomainParticipantFactory::get_instance()->delete_participant(m_participant) != greenstone::dds::ReturnCode_t::RETCODE_OK)
    {
        std::cout << "Delete participant error" << std::endl;
    }
}

void WaitSetReader::run(const uint32_t& recvLimit)
{    
    greenstone::dds::WaitSet waitset;
    greenstone::dds::StatusCondition* readerStatusCondition = m_reader->get_statuscondition();
    readerStatusCondition->set_enabled_statuses(
	greenstone::dds::StatusKind::DATA_AVAILABLE_STATUS | greenstone::dds::StatusKind::SUBSCRIPTION_MATCHED_STATUS);
    waitset.attach_condition(readerStatusCondition);
    greenstone::dds::ConditionSeq activeConditions;
    
    uint32_t received = 0;
    while (received < recvLimit)
    {    
        waitset.wait(activeConditions, greenstone::dds::Duration_t().duration_infinite());
        greenstone::dds::StatusMask statusChanges = m_reader->get_status_changes();

        if (statusChanges & greenstone::dds::StatusKind::SUBSCRIPTION_MATCHED_STATUS)
        {
            greenstone::dds::SubscriptionMatchedStatus subscription_matched_status;
            m_reader->get_subscription_matched_status(subscription_matched_status);
            if (subscription_matched_status.current_count() == 0)
            {
                break;
            }
        }

        if (statusChanges & greenstone::dds::StatusKind::DATA_AVAILABLE_STATUS)
        {
            // Retrieve data
            Helloworld helloworld;
            greenstone::dds::SampleInfo info;

            if (m_reader->take_next_sample(&helloworld, info) == greenstone::dds::ReturnCode_t::RETCODE_OK)
            {
                if (info.valid_data)
                {
                    ++received;
                    std::cout << "[ID: " << helloworld.id() 
                              << "; Index: " << helloworld.index() 
                              << "; Received: " << received
                              << "; Message size: " << helloworld.message().size() 
                              << " B] RECEIVED" << std::endl;
                }
            }
        }
    }

    destroy();
}
