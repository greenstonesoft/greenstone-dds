/**************************************************************
* @file ThroughputPub.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
*  All rights reserved
**************************************************************/

#ifndef THROUGHPUT_PUB_H
#define THROUGHPUT_PUB_H

#include "ConfigParser.h"
#include "Throughput.h"
#include "ThroughputTopicDataType.h"
#include "GeneralListeners.h"
#include "dcps/SwiftDdsExport.h"
#include "ThroughputPubBase.h"

/**
* @class ThroughputPub
* @brief This class send samples to subscriber.
* @note
*/

class ThroughputPub : public ThroughputPubBase
{
public:

	ThroughputPub(bool verbose, std::string& topicName);

	~ThroughputPub();

    // publish data
	void publish();

    // the main function of test throughput
	void test(const std::vector<std::pair<uint32_t, uint32_t>>& payloads, int sleepTime);

private:

    // a class of readerlistener 
	class PubReaderListener : public GeneralReaderListener
	{
	public:
		explicit PubReaderListener(ThroughputPub* up);
		~PubReaderListener();

        // receive samples and notify send data
		void on_data_available(greenstone::dds::DataReader* reader) noexcept;
	private:
		ThroughputPub* m_up;
		Throughput m_msg;
		greenstone::dds::SampleInfo m_info;
	};

	Throughput m_msg;
	ThroughputTopicDataType m_msgTopicType;

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

#endif  // THROUGHPUT_PUB_H
