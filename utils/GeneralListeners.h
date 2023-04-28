/**************************************************************
* @file GeneralListeners.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
*  All rights reserved
**************************************************************/

#ifndef GENERAL_LISTENERS_H
#define GENERAL_LISTENERS_H

#include <atomic>
#include "dcps/SwiftDdsExport.h"

/**
* @class GeneralParticipantListener
* @brief This class wraps a listener inheriting DomainParticipantListener.
* @note
*/

class GeneralParticipantListener : public greenstone::dds::DomainParticipantListener
{
public:
    // Constructor of GeneralParticipantListener
	GeneralParticipantListener() {};
    
    // Destructor of GeneralParticipantListener
	virtual ~GeneralParticipantListener() {};
    
    // Callback function on_participant_matched
	gvoid_t on_participant_matched(
                greenstone::dds::DomainParticipant* a_participant, 
                greenstone::dds::RemoteParticipantInfo const &a_remoteInfo) noexcept override;

    // Get number of matched participants
	uint32_t get_number_of_matched() const
	{
		return m_matched;
	}

protected:
    // Number of matched participants
	std::atomic_int m_matched {0};
};

/**
* @class GeneralReaderListener
* @brief This class wraps a listener inheriting DataReaderListener.
* @note
*/

class GeneralReaderListener : public greenstone::dds::DataReaderListener
{
public:
	// Constructor of GeneralReaderListener
	GeneralReaderListener() {}

	// Destructor of GeneralReaderListener
	virtual ~GeneralReaderListener() {}

	// Callback function on_subscription_matched
	void on_subscription_matched(
		greenstone::dds::DataReader* reader,
        greenstone::dds::SubscriptionMatchedStatus const& status) noexcept override;

	// Callback function on_data_available
	void on_data_available(greenstone::dds::DataReader* reader) noexcept override {}

	// Callback function on_liveliness_changed
	void on_liveliness_changed(
		greenstone::dds::DataReader* reader,
        greenstone::dds::LivelinessChangedStatus const& status) noexcept override;

	// Callback function on_requested_incompatible_qos
	void on_requested_incompatible_qos(
		greenstone::dds::DataReader* reader, 
		greenstone::dds::RequestedIncompatibleQosStatus const& status) noexcept override;

	// Callback function on_requested_deadline_missed
	void on_requested_deadline_missed(
		greenstone::dds::DataReader* reader, 
		greenstone::dds::RequestedDeadlineMissedStatus const& status) noexcept override;

	// Callback function on_sample_rejected
	void on_sample_rejected(
		greenstone::dds::DataReader* reader,
        greenstone::dds::SampleRejectedStatus const& status) noexcept override;

	// Callback function on_sample_lost
	void on_sample_lost(
		greenstone::dds::DataReader* reader,
        greenstone::dds::SampleLostStatus const& status) noexcept override;

	// Get number of matched DataWriters
	uint32_t get_number_of_matched() const
	{
		return m_matched;
	}

protected:
	// Number of matched DataWriters
    std::atomic_int m_matched {0};

private:
    const char* SAMPLE_REJECTED_REASONS[4] = {
        "NOT_REJECTED",
        "REJECTED_BY_INSTANCES_LIMIT",
        "REJECTED_BY_SAMPLES_LIMIT",
        "REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT"};
};

/**
* @class GeneralWriterListener
* @brief This class wraps a listener inheriting DataWriterListener.
* @note
*/

class GeneralWriterListener : public greenstone::dds::DataWriterListener
{
public:
	// Constructor of GeneralWriterListener
	GeneralWriterListener() {}

	// Destructor of GeneralWriterListener
	virtual ~GeneralWriterListener() {}

	// Callback function on_publication_matched
	void on_publication_matched(
		greenstone::dds::DataWriter* a_writer,
        greenstone::dds::PublicationMatchedStatus const &a_status) noexcept override;

	// Callback function on_liveliness_lost
	void on_liveliness_lost(
		greenstone::dds::DataWriter* a_dataWriter, 
		greenstone::dds::LivelinessLostStatus const &a_status) noexcept override;

	// Callback function on_offered_incompatible_qos
	void on_offered_incompatible_qos(
		greenstone::dds::DataWriter* a_writer,
		greenstone::dds::OfferedIncompatibleQosStatus const &a_status) noexcept override;

	// Callback function on_offered_deadline_missed
	void on_offered_deadline_missed(
		greenstone::dds::DataWriter* a_dataWriter,
		greenstone::dds::OfferedDeadlineMissedStatus const &a_status) noexcept override;

	// Get number of matched DataReaders
	uint32_t get_number_of_matched() const
	{
		return m_matched;
	}

protected:
	// number of matched DataReaders
	std::atomic_int m_matched {0};
};

#endif // GENERAL_LISTENERS_H
