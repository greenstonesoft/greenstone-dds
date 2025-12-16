/**************************************************************
* @file HelloworldReader.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#include "HelloworldReader.h"
#include "ConfigParser.h"

void HelloworldReader::MyDataReaderListener::on_data_available(greenstone::dds::DataReader* reader) noexcept
{
    // User can modify the logic here for data received
    HelloWorld helloworld;
    greenstone::dds::SampleInfo info;
    
    if (reader->take_next_sample(&helloworld, info) == greenstone::dds::ReturnCode_t::RETCODE_OK)
    {
        if (info.valid_data)
        {
            ++m_received;
            std::cout << "[ID: " << helloworld.id()
                      << "; Index: " << helloworld.index()
                      << "; Received: " << m_received
                      << "; Message size: " << helloworld.message().size() 
                      << " B] RECEIVED" << std::endl;
        }
    }
}

HelloworldReader::HelloworldReader()
    : m_participant(nullptr),
      m_participantListener(new GeneralParticipantListener()),
      m_topic(nullptr),
      m_subscriber(nullptr),
      m_reader(nullptr),
      m_readerListener(new MyDataReaderListener())
{
}

HelloworldReader::~HelloworldReader()
{
    delete m_readerListener;
    delete m_participantListener;
}

bool HelloworldReader::init(const std::string& topicName)
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
	std::string topicTypeName = m_helloworldTopicType.get_name();
    m_topic = ConfigParser::get_instance()->get_topic_from_json(
        "topic_cfg", m_participant, topicName, topicTypeName, nullptr, m_mask);

    // Create subscriber
    m_subscriber = ConfigParser::get_instance()->get_subscriber_from_json(
        "subscriber_cfg", m_participant, nullptr, m_mask);
    if (m_subscriber == nullptr)
    {
        return false;
    }

    // Create datareader
    m_reader = ConfigParser::get_instance()->get_reader_from_json(
        "reader_cfg", m_subscriber, m_topic, m_readerListener, m_mask);
    if (m_reader == nullptr)
    {
        return false;
    }

    return true;
}

void HelloworldReader::destroy()
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

void HelloworldReader::run(const uint32_t& recvLimit)
{
    std::cout << "\nWaiting for listeners to be matched..." << std::endl;

    while (!(m_readerListener->get_number_of_matched() > 0))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    while ((m_readerListener->get_number_of_matched() > 0) && (m_readerListener->m_received < recvLimit))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    destroy();
}
