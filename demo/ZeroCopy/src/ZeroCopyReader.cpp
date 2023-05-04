/**************************************************************
* @file ZeroCopyReader.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#include "ZeroCopyReader.h"
#include "ConfigParser.h"

void ZeroCopyReader::MyDataReaderListener::on_data_available(greenstone::dds::DataReader* reader) noexcept
{
    // User can modify the logic here for data received
    greenstone::dds::LoanableTypeData<ZeroCopy> loandata;
    greenstone::dds::SampleInfo info;

    if (reader->take_next_sample(loandata, info) == greenstone::dds::ReturnCode_t::RETCODE_OK)
    {
        if (info.valid_data)
        {
            ++m_received;
            ZeroCopy& zeroCopy = loandata.to_user_type();
            std::cout << "[ID: " << zeroCopy.id()
                      << "; Index: " << zeroCopy.index()
                      << "; Received: " << m_received
                      << "; Message size: " << strlen(zeroCopy.message().data())
                      << " B] RECEIVED" << std::endl;
        }
        reader->return_loan(loandata, info);
    }
}

ZeroCopyReader::ZeroCopyReader()
    : m_participant(nullptr), 
      m_topic(nullptr), 
      m_subscriber(nullptr), 
      m_reader(nullptr), 
      m_readerListener(new MyDataReaderListener())
{
}

ZeroCopyReader::~ZeroCopyReader()
{
    delete m_readerListener;
}

bool ZeroCopyReader::init(const std::string& topicName)
{
    // Create participant
    m_participant = ConfigParser::get_instance()->get_participant_from_json(
        "participant_sub_cfg", nullptr, m_mask);
    if (m_participant == nullptr)
    {
        return false;
    }

    // Create topic
    m_participant->register_type(&m_zeroCopyTopicType);
    std::string topicTypeName = m_zeroCopyTopicType.get_name();
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

void ZeroCopyReader::destroy()
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

void ZeroCopyReader::run(const uint32_t& recvLimit)
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
