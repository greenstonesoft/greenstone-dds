/**************************************************************
* @file HelloworldTopicDataType.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#include "HelloworldTopicDataType.h"

HelloworldTopicDataType::HelloworldTopicDataType() : TopicDataType()
{
	set_name("HelloworldTopicDataType");
}
HelloworldTopicDataType::~HelloworldTopicDataType()
{

}
bool HelloworldTopicDataType::serialize(DdsCdr& cdr, void *data, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value)
{
	Helloworld* pData = static_cast<Helloworld*>(data);
	pData->serialize(cdr);
	void *addr{nullptr};
	data_value->length(cdr.get_buf(&addr));
	data_value->value(static_cast<octet *>(addr));
	return true;
}
bool HelloworldTopicDataType::deserialize(DdsCdr& cdr, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, void *data)
{
	Helloworld* pData = static_cast<Helloworld*>(data);
	cdr.set_buf(reinterpret_cast<void*>(data_value->value()), data_value->length());
	pData->deserialize(cdr);
	return true;
}
// The func of getKey is non-thread-safe
bool HelloworldTopicDataType::get_key(void* data, InstanceHandle_t* ihandle)
{
	if (!Helloworld::is_key_defined())
	{
		return false;
	}
	Helloworld* pData = static_cast<Helloworld*>(data);
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
bool HelloworldTopicDataType::get_key(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, InstanceHandle_t* ihandle)
{
	if (!Helloworld::is_key_defined())
	{
		return false;
	}
	Helloworld data;
	DdsCdr cdr;
	deserialize(cdr,data_value,reinterpret_cast<void*>(&data));
	get_key(reinterpret_cast<void*>(&data),ihandle);
	return true;
}
bool HelloworldTopicDataType::init_data_ptr(void* data)
{
	if (data == nullptr)
	{
		return false;
	}
	new(data)Helloworld;

	return true;
}
uint32_t HelloworldTopicDataType::get_cdr_serialized_size(void *data)
{
	if (data == nullptr)
	{
		return 0U;
	}
	Helloworld* pData = static_cast<Helloworld*>(data);

	return pData->max_align_size(0U);
}
bool HelloworldTopicDataType::is_with_key()
{
	return Helloworld::is_key_defined();
}
bool HelloworldTopicDataType::is_plain_types()
{
	return Helloworld::is_plain_types();
}
void* HelloworldTopicDataType::create_data_resource()
{
	Helloworld* pData = new Helloworld;

	return pData;
}
void HelloworldTopicDataType::release_data_resource(void *data)
{
	if (data == nullptr)
	{
		return;
	}
	Helloworld* pData = reinterpret_cast<Helloworld*>(data);
	delete pData;
	pData = nullptr;
}
