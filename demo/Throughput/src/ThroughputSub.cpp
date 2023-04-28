/**************************************************************
* @file ThroughputSub.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
*  All rights reserved
**************************************************************/

#include "ThroughputSub.h"

ThroughputSub::SubReaderListener::SubReaderListener(ThroughputSub* up, greenstone::dds::DataWriter* writer) :
    m_up(up),
    m_writerEcho(writer)
{
}

ThroughputSub::SubReaderListener::~SubReaderListener()
{
}

void ThroughputSub::SubReaderListener::on_data_available(greenstone::dds::DataReader* reader) noexcept
{
    if (reader->take_next_sample(&m_msg, m_info) == greenstone::dds::ReturnCode_t::RETCODE_OK)
    {
        ++m_up->m_sampleCnt;
        if (m_up->m_verbose)
        {
            std::cout << "Message with index of " << m_msg.index() << " received.  " << m_up->m_sampleCnt << std::endl;
        }
        
        if (m_msg.index() == 1)
        {
            m_up->m_payloadCount = std::stoi(m_msg.message());

            m_msg.message("");
            while (m_writerEcho->write(&m_msg, m_handle) != greenstone::dds::ReturnCode_t::RETCODE_OK)
            {
                std::cout << "Resending START command..." << std::endl;
            }

            if (m_up->m_verbose)
            {
                std::cout << "START command sent." << std::endl;
            }
        }
        else if (m_msg.index() == 0)
        {
            m_up->m_t2 = std::chrono::steady_clock::now();
            m_up->m_deltaT = std::chrono::duration_cast<std::chrono::microseconds>(m_up->m_t2 - m_up->m_t1).count();
            m_up->m_throughput = (m_up->m_sampleCnt - 2) * ( sizeof(m_msg.key()) + sizeof(m_msg.index()) + sizeof(m_msg.length()) + m_msg.message().size() ) * 8 * 1000000 / m_up->m_deltaT / 1000.0 /1000.0;
            m_up->m_payloadSize = m_msg.length();
            m_up->print_throughput_result();

            m_up->m_sampleCnt = 0;

            m_msg.message("");
            while (m_writerEcho->write(&m_msg, m_handle) != greenstone::dds::ReturnCode_t::RETCODE_OK)
            {
                std::cout << "Resending notification message..." << std::endl;
            }

            if (m_up->m_verbose)
            {
                std::cout << "Notification message sent." << std::endl;
            }
        }
        else if (m_msg.index() == 2)
        {
            m_up->m_t1 = std::chrono::steady_clock::now();
        }
    }
}

ThroughputSub::ThroughputSub(bool verbose, std::string& topicName) :
    ThroughputSubBase(verbose),
    m_participant(nullptr), 
    m_topic(nullptr), 
    m_topicEcho(nullptr),
    m_publisher(nullptr), 
    m_writer(nullptr),
    m_subscriber(nullptr),
    m_reader(nullptr),
    m_writerListener(new GeneralWriterListener())
{
    //CREATE THE PARTICIPANT
    m_participant = ConfigParser::get_instance()->get_participant_from_json(
        "participant_sub_cfg", nullptr, m_mask);

    //REGISTER THE TYPE
    m_participant->register_type(&m_msgTopicType);

    //CREATE THE TOPIC
    std::string topicEchoName = topicName + "_Echo";
	std::string topicTypeName = "ThroughputTopicDataType";
    m_topic = m_participant->create_topic(
        topicName, topicTypeName, m_topicQos, nullptr, m_mask);
    m_topicEcho = m_participant->create_topic(
        topicEchoName, topicTypeName, m_topicQos, nullptr, m_mask);

    //CREATE THE PUBLISHER
    m_publisher = ConfigParser::get_instance()->get_publisher_from_json(
        "publisher_cfg", m_participant, nullptr, m_mask);

    //CREATE THE WRITER
    m_writer = ConfigParser::get_instance()->get_writer_from_json(
        "writer_cfg", m_publisher, m_topicEcho, m_writerListener, m_mask);

    //CREATE THE SUBSCRIBER
    m_subscriber = ConfigParser::get_instance()->get_subscriber_from_json(
        "subscriber_cfg", m_participant, nullptr, m_mask);

    //CREATE THE READER
    m_readerListener = new SubReaderListener(this, m_writer);
    m_reader = ConfigParser::get_instance()->get_reader_from_json(
        "reader_cfg", m_subscriber, m_topic, m_readerListener, m_mask);
}

ThroughputSub::~ThroughputSub()
{
    delete m_writerListener;
    delete m_readerListener;

    m_publisher->delete_datawriter(m_writer);
    m_subscriber->delete_datareader(m_reader);
    m_participant->delete_publisher(m_publisher);
    m_participant->delete_subscriber(m_subscriber);
    m_participant->delete_topic(m_topic);
    m_participant->delete_topic(m_topicEcho);

    greenstone::dds::DomainParticipantFactory::get_instance()->delete_participant(m_participant);
}

void ThroughputSub::test()
{
    std::cout << "Waiting for listeners to be matched..." << std::endl;

    while (!(m_writerListener->get_number_of_matched() > 0 && m_readerListener->get_number_of_matched() > 0))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "Listeners have been matched successfully.\n\nThroughput test is ongoing..." << std::endl; 

    while (!(m_writerListener->get_number_of_matched() == 0 && m_readerListener->get_number_of_matched() == 0))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "Throughput test is over.\n" << std::endl;
}
