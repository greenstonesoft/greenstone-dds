/**************************************************************
* @file ZeroCopyReader.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#ifndef ZEROCOPY_READER_H
#define ZEROCOPY_READER_H

#include "GeneralListeners.h"
#include "ZeroCopyTopicDataType.h"

/**
* @class ZeroCopyReader
* @brief A wrapper class subscribing ZeroCopy topic.
* @note
*/

class ZeroCopyReader
{
public:

    ZeroCopyReader();

    ~ZeroCopyReader();

    // Initialize DDS entities for subscribing ZeroCopy topic
    bool init(const std::string& topicName);

    // Destroy DDS entities
    void destroy();

    // Subscribe data using ZeroCopy
    void run(const uint32_t& recvLimit);

private:

    // Instance of ZeroCopyTopicDataType
    ZeroCopyTopicDataType m_zeroCopyTopicType;

    // DDS entities for the DataReader
    greenstone::dds::DomainParticipant* m_participant;
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

#endif  // ZEROCOPY_READER_H
