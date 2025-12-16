/**************************************************************
* @file HelloworldTopicDataType.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2025
* All rights reserved
**************************************************************/

#ifndef HELLOWORLDTOPICDATATYPE_a9c2833f9abc58f4c147f9f3717c8d60_H
#define HELLOWORLDTOPICDATATYPE_a9c2833f9abc58f4c147f9f3717c8d60_H

#include "swiftdds/dcps/SwiftDdsExport.h"

#include "Helloworld.h"




/**
* @class HelloWorldTopicDataType
* @brief A class used as the topic during data exchange.
* @note
*/

class HelloWorldTopicDataType : public greenstone::dds::TopicDataType
{
public:
	using InstanceHandle_t = greenstone::dds::InstanceHandle_t;

	HelloWorldTopicDataType();
	virtual ~HelloWorldTopicDataType();

	bool serialize(DdsCdr& cdr, void *data, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value);
	bool deserialize(DdsCdr& cdr, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, void* data);

	// The func of getKey is non-thread-safe
	bool get_key(void* data, InstanceHandle_t* ihandle) noexcept;
	bool get_key(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, InstanceHandle_t* ihandle) noexcept;
	bool init_data_ptr(void* data) noexcept;
	uint32_t get_cdr_serialized_size(void *data) noexcept;
	bool is_with_key() noexcept;
	bool is_plain_types() noexcept;
	void* create_data_resource() noexcept;
	void release_data_resource(void *data) noexcept;
	greenstone::dds::SerializedPayloadHeader const get_serialized_payload_header() noexcept;
	void* const get_key_value_data(void * const data) noexcept;
	void* const get_key_value_data(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value) noexcept;
	void copy_key_value_to_data(void const *const key_data, void *const data) noexcept;
	uint32_t data_size_of() noexcept;

};

#endif	// HELLOWORLDTOPICDATATYPE_a9c2833f9abc58f4c147f9f3717c8d60_H

