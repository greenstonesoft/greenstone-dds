/**************************************************************
* @file LatencyTopicDataType.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#include "LatencyTopicDataType.h"

LatencyTopicDataType::LatencyTopicDataType() : TopicDataType()
{
	set_name("LatencyTopicDataType");
}
LatencyTopicDataType::~LatencyTopicDataType()
{

}
bool LatencyTopicDataType::serialize(DdsCdr& cdr, void *data, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value)
{
	Latency* pData = static_cast<Latency*>(data);
	pData->serialize(cdr);
	void *addr{nullptr};
	data_value->length(cdr.get_buf(&addr));
	data_value->value(static_cast<octet *>(addr));
	return true;
}
bool LatencyTopicDataType::deserialize(DdsCdr& cdr, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, void *data)
{
	Latency* pData = static_cast<Latency*>(data);
	cdr.set_buf(reinterpret_cast<void*>(data_value->value()), data_value->length());
	pData->deserialize(cdr);
	return true;
}
// The func of getKey is non-thread-safe
bool LatencyTopicDataType::get_key(void* data, InstanceHandle_t* ihandle)
{
	if (!Latency::is_key_defined())
	{
		return false;
	}
	Latency* pData = static_cast<Latency*>(data);
	unsigned int length;
	char *buf = nullptr;
	pData->serialize_key(&buf,&length);
	if (length > 16)
	{
		greenstone::dds::UtilHelper::generate_digest(buf,length,reinterpret_cast<char*>(ihandle->value));
	}
	else
	{
		memcpy(ihandle->value, buf, length);
	}
	if (buf && pData->is_key_serialize_by_cdr())
	{
		delete buf;
		buf = nullptr;
	}
	return true;
}
bool LatencyTopicDataType::get_key(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, InstanceHandle_t* ihandle)
{
	if (!Latency::is_key_defined())
	{
		return false;
	}
	Latency data;
	DdsCdr cdr;
	deserialize(cdr,data_value,reinterpret_cast<void*>(&data));
	get_key(reinterpret_cast<void*>(&data),ihandle);
	return true;
}
bool LatencyTopicDataType::init_data_ptr(void* data)
{
	if (data == nullptr)
	{
		return false;
	}
	new(data)Latency;

	return true;
}
uint32_t LatencyTopicDataType::get_cdr_serialized_size(void *data)
{
	if (data == nullptr)
	{
		return 0U;
	}
	Latency* pData = static_cast<Latency*>(data);

	return pData->max_align_size(0U);
}
bool LatencyTopicDataType::is_with_key()
{
	return Latency::is_key_defined();
}
bool LatencyTopicDataType::is_plain_types()
{
	return Latency::is_plain_types();
}
void* LatencyTopicDataType::create_data_resource()
{
	Latency* pData = new Latency;

	return pData;
}
void LatencyTopicDataType::release_data_resource(void *data)
{
	if (data == nullptr)
	{
		return;
	}
	Latency* pData = reinterpret_cast<Latency*>(data);
	delete pData;
	pData = nullptr;
}
