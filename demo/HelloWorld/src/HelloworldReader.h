/**************************************************************
* @file HelloworldReader.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#ifndef HELLOWORLD_READER_H
#define HELLOWORLD_READER_H

#include "GeneralListeners.h"
#include "HelloworldTopicDataType.h"

/**
* @class HelloworldReader
* @brief A wrapper class subscribing Helloworld topic.
* @note
*/

class HelloworldReader
{
public:

    HelloworldReader();

    ~HelloworldReader();

    // Initialize DDS entities for subscribing Helloworld topic
    bool init(const std::string& topicName);

    // Destroy DDS entities
    void destroy();

    // Subscribe data
    void run(const uint32_t& recvLimit);

private:

    // Instance of HelloworldTopicDataType
    HelloWorldTopicDataType m_helloworldTopicType;

    // DDS entities for the DataReader
    greenstone::dds::DomainParticipant* m_participant;
    greenstone::dds::DomainParticipantListener* m_participantListener;
    greenstone::dds::Topic* m_topic;
    greenstone::dds::Subscriber* m_subscriber;
    greenstone::dds::DataReader* m_reader;
    greenstone::dds::StatusMask m_mask {greenstone::dds::AllStatusMask};

    // A child class of GeneralReaderListener
    class MyDataReaderListener : public GeneralReaderListener
    {
    public:
        MyDataReaderListener() {}
        ~MyDataReaderListener() {}
        void on_data_available(greenstone::dds::DataReader* reader) noexcept override;
    public:
        uint32_t m_received {0};
    }* m_readerListener;
};

#endif  // HELLOWORLD_READER_H
