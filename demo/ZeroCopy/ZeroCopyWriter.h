/**************************************************************
* @file ZeroCopyWriter.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#ifndef ZEROCOPY_WRITER_H
#define ZEROCOPY_WRITER_H

#include "GeneralListeners.h"
#include "HelloworldTopicDataType.h"

/**
* @class ZeroCopyWriter
* @brief A wrapper class publishing Helloworld topic.
* @note
*/

class ZeroCopyWriter 
{
public:

    ZeroCopyWriter();

    ~ZeroCopyWriter();

    // Initialize DDS entities for publishing Helloworld topic
    bool init(const std::string& topicName);

    // Destroy DDS entities
    void destroy();

    // Publish data using ZeroCopy
    void run(
        const uint32_t& sensorId, 
        const uint32_t& numOfInstances, 
        const uint32_t& dataSize, 
        const uint32_t& sampleCount, 
        const uint32_t& sleepTime, 
        const uint32_t& finalSleep, 
        const bool& wait);

private:

    // Instance of Helloworld and HelloworldTopicDataType
    Helloworld* m_helloworld;
    HelloworldTopicDataType m_helloworldTopicType;

    // DDS entities for the datawriter
    greenstone::dds::DomainParticipant* m_participant;
    greenstone::dds::Topic* m_topic;
    greenstone::dds::Publisher* m_publisher;
    greenstone::dds::DataWriter* m_writer;
    greenstone::dds::StatusMask m_mask {greenstone::dds::AllStatusMask};
    greenstone::dds::InstanceHandle_t m_handle;

    // A child class of GeneralWriterListener
    class MyDataWriterListener : public GeneralWriterListener
    {
    public:
        MyDataWriterListener() {}
        ~MyDataWriterListener() {}
    }* m_writerListener;
};

#endif  // ZEROCOPY_WRITER_H
