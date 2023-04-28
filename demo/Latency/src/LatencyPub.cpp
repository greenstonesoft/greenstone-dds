/**************************************************************
* @file LatencyPub.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
*  All rights reserved
**************************************************************/

#include "LatencyPub.h"

LatencyPub::PubReaderListener::PubReaderListener(LatencyPub* up) :
    m_up(up)
{
}

LatencyPub::PubReaderListener::~PubReaderListener()
{
}

void LatencyPub::PubReaderListener::on_data_available(greenstone::dds::DataReader* reader) noexcept
{
    if (reader->take_next_sample(&m_msgEcho, m_info) == greenstone::dds::ReturnCode_t::RETCODE_OK)
    {
        m_up->m_t2 = std::chrono::steady_clock::now();

        {
            std::unique_lock<std::mutex> lock(m_up->m_mutex);
            m_up->m_ack = true;
        }
        m_up->m_cv.notify_one();

        if (m_up->m_verbose)
        {
            std::cout << "Echo message with index of " << m_msgEcho.index() << " received." << std::endl;
        }
    }
}

LatencyPub::LatencyPub(bool verbose, std::string& topicName) :
    LatencyPubBase(verbose),
    m_participant(nullptr), 
    m_topic(nullptr), 
    m_topicEcho(nullptr),
    m_publisher(nullptr), 
    m_writer(nullptr),
    m_subscriber(nullptr),
    m_reader(nullptr),
    m_writerListener(new GeneralWriterListener()),
    m_readerListener(new PubReaderListener(this))
{
    //CREATE THE PARTICIPANT
    m_participant = ConfigParser::get_instance()->get_participant_from_json(
        "participant_pub_cfg", nullptr, m_mask);

    //REGISTER THE TYPE
    m_participant->register_type(&m_msgTopicType);

    //CREATE THE TOPIC
    std::string topicEchoName = topicName + "_Echo";
	std::string topicTypeName = "LatencyTopicDataType";
    m_topic = m_participant->create_topic(
        topicName, topicTypeName, m_topicQos, nullptr, m_mask);
    m_topicEcho = m_participant->create_topic(
        topicEchoName, topicTypeName, m_topicQos, nullptr, m_mask);

    //CREATE THE PUBLISHER
    m_publisher = ConfigParser::get_instance()->get_publisher_from_json(
        "publisher_cfg", m_participant, nullptr, m_mask);

    //CREATE THE WRITER
    m_writer = ConfigParser::get_instance()->get_writer_from_json(
        "writer_cfg", m_publisher, m_topic, m_writerListener, m_mask);

    //CREATE THE SUBSCRIBER
    m_subscriber = ConfigParser::get_instance()->get_subscriber_from_json(
        "subscriber_cfg", m_participant, nullptr, m_mask);

    //CREATE THE READER
    m_reader = ConfigParser::get_instance()->get_reader_from_json(
        "reader_cfg", m_subscriber, m_topicEcho, m_readerListener, m_mask);
}

LatencyPub::~LatencyPub()
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

void LatencyPub::publish()
{
    while (m_writer->write(&m_msg, m_handle) != greenstone::dds::ReturnCode_t::RETCODE_OK)
    {
        std::cout << "Resending message..." << std::endl;
    }

    if (m_verbose)
    {
        std::cout << "Message with index of " << m_msg.index() << " sent." << std::endl;
    }
}

void LatencyPub::test(
    const std::vector<std::pair<uint32_t, uint32_t>>& payloads, 
    int sleepTime, bool printDetails)
{
    std::cout << "Waiting for listeners to be matched..." << std::endl;

    while (!(m_writerListener->get_number_of_matched() > 0 && m_readerListener->get_number_of_matched() > 0))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "Listeners have been matched successfully.\n\nStarting latency test..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    bool stop = false;
    for (auto it = payloads.begin(); it != payloads.end(); ++it) 
    {
        m_payloadSize = it->first;
        m_payloadCount = it->second;

        std::vector<double> latencyData(m_payloadCount, 0.0);

        m_msg.key(0);
        m_msg.length(m_payloadSize);
        m_msg.message().resize(m_payloadSize - 12, 'a');

        for (uint32_t i = 0; i < m_payloadCount; ++i) 
        {
            m_msg.index(i);
            m_t1 = std::chrono::steady_clock::now();
            publish();

            {
                std::unique_lock<std::mutex> lock(m_mutex);
                if (!m_cv.wait_for(lock, std::chrono::seconds(600), [&]() {return m_ack;}))
                {
                    std::cout << "Echo message has not been received for 600 seconds." << std::endl;
                    stop = true;
                    break;
                }
                m_ack = false;
            }

            m_deltaT = std::chrono::duration_cast<std::chrono::microseconds>(m_t2 - m_t1).count();
            latencyData[i] = m_deltaT / 2.0;
            m_sampleCnt++;

            if (sleepTime >= 1)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
            }
        }

        if (stop)
        {
            break;
        }
        
        m_result = TestStatistics::cal_result(latencyData);
        print_latency_result();
        m_sampleCnt = 0;

        if (printDetails)
        {
            for (auto& perData : latencyData)
            {
                std::cout << "Test Details: [" << m_payloadSize << "] " << perData << std::endl;
            }
        }
    }

    if (!stop)
    {
        std::cout << "Latency test completed normally.\n" << std::endl;
    }
    else
    {
        std::cout << "Latency test completed abnormally.\n" << std::endl;
    } 
}
