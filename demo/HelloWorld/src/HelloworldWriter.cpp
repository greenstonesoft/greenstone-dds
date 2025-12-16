/**************************************************************
* @file HelloworldWriter.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#include "HelloworldWriter.h"
#include "ConfigParser.h"

HelloworldWriter::HelloworldWriter() 
    : m_participant(nullptr), 
      m_participantListener(new GeneralParticipantListener()), 
      m_topic(nullptr), 
      m_publisher(nullptr), 
      m_writer(nullptr), 
      m_writerListener(new MyDataWriterListener())
{
}

HelloworldWriter::~HelloworldWriter()
{
    delete m_writerListener;
    delete m_participantListener;
}

bool HelloworldWriter::init(const std::string& topicName)
{
    // Create participant
    m_participant = ConfigParser::get_instance()->get_participant_from_json(
        "participant_pub_cfg", nullptr, m_mask);
    if (m_participant == nullptr)
    {
        return false;
    }

    // Create topic
    m_participant->register_type(&m_helloworldTopicType);
	std::string topicTypeName = m_helloworldTopicType.get_name();
    m_topic = ConfigParser::get_instance()->get_topic_from_json(
        "topic_cfg", m_participant, topicName, topicTypeName, nullptr, m_mask);

    // Create publisher
    m_publisher = ConfigParser::get_instance()->get_publisher_from_json(
        "publisher_cfg", m_participant, nullptr, m_mask);
    if (m_publisher == nullptr)
    {
        return false;
    }

    // Create datawriter
    m_writer = ConfigParser::get_instance()->get_writer_from_json(
        "writer_cfg", m_publisher, m_topic, m_writerListener, m_mask);
    if (m_writer == nullptr)
    {
        return false;
    }

    return true;
}

void HelloworldWriter::destroy()
{
    if (m_publisher->delete_datawriter(m_writer) != greenstone::dds::ReturnCode_t::RETCODE_OK)
    {
        std::cout << "Delete writer error" << std::endl;
    }
    if (m_participant->delete_publisher(m_publisher) != greenstone::dds::ReturnCode_t::RETCODE_OK)
    {
        std::cout << "Delete publisher error" << std::endl;
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

void HelloworldWriter::run(
    const uint32_t& sensorId, 
    const uint32_t& numOfInstances, 
    const uint32_t& dataSize, 
    const uint32_t& sampleCount, 
    const uint32_t& sleepTime, 
    const uint32_t& finalSleep, 
    const bool& wait)
{
    if (wait)
    {
        std::cout << "\nWaiting for listeners to be matched..." << std::endl;

        while (!(m_writerListener->get_number_of_matched() > 0)) 
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        std::cout << "Listeners have been matched successfully." << std::endl;
    }
        
    std::cout << "Sending data..." << std::endl; 
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    for (uint32_t i = 1; i <= sampleCount; i++)
    {   
        // User can modify the data to be written here
        m_helloworld.id(sensorId + (i - 1) % numOfInstances);
		m_helloworld.index(i);
        m_helloworld.message().resize(dataSize, 'a');

        // Send data
        if (m_writer->write(&m_helloworld, m_handle) == greenstone::dds::ReturnCode_t::RETCODE_OK)
        {
            std::cout << "[ID: " << m_helloworld.id()
                      << "; Index: " << m_helloworld.index()
                      << "; Message size: " << m_helloworld.message().size()
                      << " B] SENT" << std::endl;
        }
        else
        {
            std::cout << "[ID: " << m_helloworld.id()
                      << "; Index: " << m_helloworld.index()
                      << "; Message size: " << m_helloworld.message().size()
                      << " B] SENT FAILED!" << std::endl;
        }

        // Sleep for a period
        if (sleepTime > 0)
        {        
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(finalSleep));

    destroy();
}
