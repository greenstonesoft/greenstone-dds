/**************************************************************
* @file WaitsetWriter.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#ifndef WAITSET_WRITER_H
#define WAITSET_WRITER_H

#include "HelloworldTopicDataType.h"
#include "dcps/SwiftDdsExport.h"

/**
* @class WaitSetWriter
* @brief A wrapper class publishing HelloWorld topic.
* @note
*/

class WaitSetWriter
{
public:

    WaitSetWriter();

    ~WaitSetWriter();

    // Initialize DDS entities for publishing Helloworld topic
    bool init(const std::string& topicName);

    // Destroy DDS entities
    void destroy();

    // Publish data using WaitSet
    void run(const uint32_t& sensorId, 
        const uint32_t& numOfInstances, 
        const uint32_t& dataSize, 
        const uint32_t& sampleCount, 
        const uint32_t& sleepTime, 
        const uint32_t& finalSleep, 
        const bool& wait);

private:

    // Instance of HelloWorld and HelloWorldTopicDataType
    Helloworld m_helloworld;
    HelloworldTopicDataType m_helloworldTopicType;

    // DDS entities for the DataWriter
    greenstone::dds::DomainParticipant* m_participant;
    greenstone::dds::DomainParticipantListener* m_participantListener;
    greenstone::dds::Topic* m_topic;
    greenstone::dds::Publisher* m_publisher;
    greenstone::dds::DataWriter* m_writer;
    greenstone::dds::StatusMask m_mask {greenstone::dds::AllStatusMask};
    greenstone::dds::InstanceHandle_t m_handle;
};

#endif  // WAITSET_WRITER_H
