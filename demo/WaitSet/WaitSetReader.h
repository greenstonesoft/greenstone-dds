/**************************************************************
* @file WaitSetReader.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#ifndef WAITSET_READER_H
#define WAITSET_READER_H

#include "HelloworldTopicDataType.h"
#include "dcps/SwiftDdsExport.h"

/**
* @class WaitSetReader
* @brief A wrapper class subscribing HelloWorld topic.
* @note
*/
class WaitSetReader
{
public:

    WaitSetReader();

    ~WaitSetReader();

    // Initialize DDS entities for subscribing Helloworld topic
    bool init(const std::string& topicName);

    // Destroy DDS entities
    void destroy();

    // Subscribe data using WaitSet
    void run(const uint32_t& recvLimit);

private:
    
    // Instance of HelloworldTopicDataType
    HelloworldTopicDataType m_helloworldTopicType;

    // Define DDS entities for the DataReader
    greenstone::dds::DomainParticipant* m_participant;
    greenstone::dds::Topic* m_topic;
    greenstone::dds::Subscriber* m_subscriber;
    greenstone::dds::DataReader* m_reader;
    greenstone::dds::StatusMask m_mask {greenstone::dds::AllStatusMask};
};

#endif  // WAITSET_READER_H
