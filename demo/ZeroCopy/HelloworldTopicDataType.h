/**************************************************************
* @file HelloworldTopicDataType.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#ifndef HELLOWORLD_TOPICDATATYPE_H
#define HELLOWORLD_TOPICDATATYPE_H

#include "dcps/SwiftDdsExport.h"

#include "Helloworld.h"


/**
* @class HelloworldTopicDataType
* @brief A class used as the topic during data exchange.
* @note
*/

class HelloworldTopicDataType : public greenstone::dds::TopicDataType
{
public:
	using InstanceHandle_t = greenstone::dds::InstanceHandle_t;

	HelloworldTopicDataType();
	virtual ~HelloworldTopicDataType();

	bool serialize(DdsCdr& cdr, void *data, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value);
	bool deserialize(DdsCdr& cdr, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, void* data);

	// The func of getKey is non-thread-safe
	bool get_key(void* data, InstanceHandle_t* ihandle);
	bool get_key(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, InstanceHandle_t* ihandle);
	bool init_data_ptr(void* data);
	uint32_t get_cdr_serialized_size(void *data);
	bool is_with_key();
	bool is_plain_types();
	void* create_data_resource();
	void release_data_resource(void *data);

};

#endif	// HELLOWORLD_TOPICDATATYPE_H
