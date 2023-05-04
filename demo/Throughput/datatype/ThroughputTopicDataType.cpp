/**************************************************************
* @file ThroughputTopicDataType.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#include "ThroughputTopicDataType.h"

ThroughputTopicDataType::ThroughputTopicDataType() : TopicDataType()
{
	set_name("ThroughputTopicDataType");
}
ThroughputTopicDataType::~ThroughputTopicDataType()
{

}
bool ThroughputTopicDataType::serialize(DdsCdr& cdr, void *data, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value)
{
	Throughput* pData = static_cast<Throughput*>(data);
	pData->serialize(cdr);
	void *addr{nullptr};
	data_value->length(cdr.get_buf(&addr));
	data_value->value(static_cast<octet *>(addr));
	return true;
}
bool ThroughputTopicDataType::deserialize(DdsCdr& cdr, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, void *data)
{
	Throughput* pData = static_cast<Throughput*>(data);
	cdr.set_buf(reinterpret_cast<void*>(data_value->value()), data_value->length());
	pData->deserialize(cdr);
	return true;
}
// The func of getKey is non-thread-safe
bool ThroughputTopicDataType::get_key(void* data, InstanceHandle_t* ihandle)
{
	if (!Throughput::is_key_defined())
	{
		return false;
	}
	Throughput* pData = static_cast<Throughput*>(data);
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
bool ThroughputTopicDataType::get_key(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, InstanceHandle_t* ihandle)
{
	if (!Throughput::is_key_defined())
	{
		return false;
	}
	Throughput data;
	DdsCdr cdr;
	deserialize(cdr,data_value,reinterpret_cast<void*>(&data));
	get_key(reinterpret_cast<void*>(&data),ihandle);
	return true;
}
bool ThroughputTopicDataType::init_data_ptr(void* data)
{
	if (data == nullptr)
	{
		return false;
	}
	new(data)Throughput;

	return true;
}
uint32_t ThroughputTopicDataType::get_cdr_serialized_size(void *data)
{
	if (data == nullptr)
	{
		return 0U;
	}
	Throughput* pData = static_cast<Throughput*>(data);

	return pData->max_align_size(0U);
}
bool ThroughputTopicDataType::is_with_key()
{
	return Throughput::is_key_defined();
}
bool ThroughputTopicDataType::is_plain_types()
{
	return Throughput::is_plain_types();
}
void* ThroughputTopicDataType::create_data_resource()
{
	Throughput* pData = new Throughput;

	return pData;
}
void ThroughputTopicDataType::release_data_resource(void *data)
{
	if (data == nullptr)
	{
		return;
	}
	Throughput* pData = reinterpret_cast<Throughput*>(data);
	delete pData;
	pData = nullptr;
}
