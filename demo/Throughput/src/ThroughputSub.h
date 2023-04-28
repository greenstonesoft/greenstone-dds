/**************************************************************
* @file ThroughputSub.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
*  All rights reserved
**************************************************************/

#ifndef THROUGHPUT_SUB_H
#define THROUGHPUT_SUB_H

#include "ConfigParser.h"
#include "Throughput.h"
#include "ThroughputTopicDataType.h"
#include "GeneralListeners.h"
#include "dcps/SwiftDdsExport.h"
#include "ThroughputSubBase.h"

/**
* @class ThroughputSub
* @brief This class receive samples and calculate throughput.
* @note
*/

class ThroughputSub : public ThroughputSubBase
{
public:
	
	ThroughputSub(bool verbose, std::string& topicName);

	~ThroughputSub();

    // wait match and end with unmatch
	void test();

private:
    // a class of readerlistener
	class SubReaderListener : public GeneralReaderListener
	{
	public:
		SubReaderListener(ThroughputSub* up, greenstone::dds::DataWriter* writer);
		~SubReaderListener();

        // receive data and calculate throughput
		void on_data_available(greenstone::dds::DataReader* reader) noexcept;
	private:
		ThroughputSub* m_up;
		greenstone::dds::DataWriter* m_writerEcho;
		Throughput m_msg;
        greenstone::dds::SampleInfo m_info;
		greenstone::dds::InstanceHandle_t m_handle;
	};

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
	GeneralWriterListener* m_writerListener;
    SubReaderListener* m_readerListener;
};

#endif // THROUGHPUT_SUB_H
