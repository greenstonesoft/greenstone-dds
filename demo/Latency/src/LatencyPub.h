/**************************************************************
* @file LatencyPub.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
*  All rights reserved
**************************************************************/

#ifndef LATENCY_PUB_H
#define LATENCY_PUB_H

#include "ConfigParser.h"
#include "Latency.h"
#include "LatencyTopicDataType.h"
#include "GeneralListeners.h"
#include "dcps/SwiftDdsExport.h"
#include "LatencyPubBase.h"

/**
* @class LatencyPub
* @brief This class is a pub class which publish samples and receive data from 
* subscriber, then calculate latency between the two node.
* @note
*/

class LatencyPub : public LatencyPubBase
{
public:

	LatencyPub(bool verbose, std::string& topicName);

	~LatencyPub();

    // publish data
	void publish();

    // publish data and calculate latency
	void test(
        const std::vector<std::pair<uint32_t, uint32_t>>& payloads, 
        int sleepTime, bool printDetails);

private:

    // a class of readerlistener 
	class PubReaderListener : public GeneralReaderListener
    {
	public:
		PubReaderListener(LatencyPub* up);
		~PubReaderListener();

		// receive data from sub node and notify test function pub
		void on_data_available(greenstone::dds::DataReader* reader) noexcept;
	private:
		LatencyPub* m_up;
		Latency m_msgEcho;
		greenstone::dds::SampleInfo m_info;
	};

	Latency m_msg;
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
	greenstone::dds::InstanceHandle_t m_handle;
	GeneralWriterListener* m_writerListener;
    PubReaderListener* m_readerListener;
};

#endif // LATENCY_PUB_H
