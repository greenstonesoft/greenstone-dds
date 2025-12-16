/**************************************************************
* @file LatencySub.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
*  All rights reserved
**************************************************************/

#ifndef LATENCY_SUB_H
#define LATENCY_SUB_H

#include "ConfigParser.h"
#include "Latency.h"
#include "LatencyTopicDataType.h"
#include "GeneralListeners.h"
#include "swiftdds/dcps/SwiftDdsExport.h"
#include "LatencySubBase.h"

/**
* @class LatencySub
* @brief This class is a sub class which subscribe samples and resend the samples to publisher.
* @note
*/

class LatencySub : public LatencySubBase
{
public:

    LatencySub(bool verbose, std::string& topicName);
    
    ~LatencySub();

    // wait match and end with unmatch
    void test();

private:

    // a class of readerlistener 
	class SubReaderListener : public GeneralReaderListener
    {
    public:
		SubReaderListener(LatencySub* up, greenstone::dds::DataWriter* writer);
		~SubReaderListener();

        // receive data and resend to publisher
		void on_data_available(greenstone::dds::DataReader* reader) noexcept override;
	private:
		LatencySub* m_up;
		greenstone::dds::DataWriter* m_writerEcho;
		Latency m_msg;
        greenstone::dds::SampleInfo m_info;
		greenstone::dds::InstanceHandle_t m_handle;
	};

    LatencyTopicDataType m_msgTopicType;

	greenstone::dds::DomainParticipant* m_participant;
	greenstone::dds::Topic* m_topic;
	greenstone::dds::Topic* m_topicEcho;
	greenstone::dds::TopicQos m_topicQos;
	greenstone::dds::Publisher* m_publisher;
	greenstone::dds::DataWriter* m_writer;
	greenstone::dds::Subscriber* m_subscriber;
	greenstone::dds::DataReader* m_reader;
	greenstone::dds::StatusMask m_mask {greenstone::dds::AllStatusMask};
	GeneralWriterListener* m_writerListener;
    SubReaderListener* m_readerListener;
};

#endif // LATENCY_SUB_H
