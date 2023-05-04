/**************************************************************
* @file WaitSetTopicDataType.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#include "WaitSetTopicDataType.h"

WaitSetTopicDataType::WaitSetTopicDataType() : TopicDataType()
{
	set_name("WaitSetTopicDataType");
}
WaitSetTopicDataType::~WaitSetTopicDataType()
{

}
bool WaitSetTopicDataType::serialize(DdsCdr& cdr, void *data, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value)
{
	WaitSet* pData = static_cast<WaitSet*>(data);
	pData->serialize(cdr);
	void *addr{nullptr};
	data_value->length(cdr.get_buf(&addr));
	data_value->value(static_cast<octet *>(addr));
	return true;
}
bool WaitSetTopicDataType::deserialize(DdsCdr& cdr, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, void *data)
{
	WaitSet* pData = static_cast<WaitSet*>(data);
	cdr.set_buf(reinterpret_cast<void*>(data_value->value()), data_value->length());
	pData->deserialize(cdr);
	return true;
}
// The func of getKey is non-thread-safe
bool WaitSetTopicDataType::get_key(void* data, InstanceHandle_t* ihandle)
{
	if (!WaitSet::is_key_defined())
	{
		return false;
	}
	WaitSet* pData = static_cast<WaitSet*>(data);
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
bool WaitSetTopicDataType::get_key(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, InstanceHandle_t* ihandle)
{
	if (!WaitSet::is_key_defined())
	{
		return false;
	}
	WaitSet data;
	DdsCdr cdr;
	deserialize(cdr,data_value,reinterpret_cast<void*>(&data));
	get_key(reinterpret_cast<void*>(&data),ihandle);
	return true;
}
bool WaitSetTopicDataType::init_data_ptr(void* data)
{
	if (data == nullptr)
	{
		return false;
	}
	new(data)WaitSet;

	return true;
}
uint32_t WaitSetTopicDataType::get_cdr_serialized_size(void *data)
{
	if (data == nullptr)
	{
		return 0U;
	}
	WaitSet* pData = static_cast<WaitSet*>(data);

	return pData->max_align_size(0U);
}
bool WaitSetTopicDataType::is_with_key()
{
	return WaitSet::is_key_defined();
}
bool WaitSetTopicDataType::is_plain_types()
{
	return WaitSet::is_plain_types();
}
void* WaitSetTopicDataType::create_data_resource()
{
	WaitSet* pData = new WaitSet;

	return pData;
}
void WaitSetTopicDataType::release_data_resource(void *data)
{
	if (data == nullptr)
	{
		return;
	}
	WaitSet* pData = reinterpret_cast<WaitSet*>(data);
	delete pData;
	pData = nullptr;
}
