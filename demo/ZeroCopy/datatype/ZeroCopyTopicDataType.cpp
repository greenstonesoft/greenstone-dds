/**************************************************************
* @file ZeroCopyTopicDataType.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#include "ZeroCopyTopicDataType.h"

ZeroCopyTopicDataType::ZeroCopyTopicDataType() : TopicDataType()
{
	set_name("ZeroCopyTopicDataType");
}
ZeroCopyTopicDataType::~ZeroCopyTopicDataType()
{

}
bool ZeroCopyTopicDataType::serialize(DdsCdr& cdr, void *data, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value)
{
	ZeroCopy* pData = static_cast<ZeroCopy*>(data);
	pData->serialize(cdr);
	void *addr{nullptr};
	data_value->length(cdr.get_buf(&addr));
	data_value->value(static_cast<octet *>(addr));
	return true;
}
bool ZeroCopyTopicDataType::deserialize(DdsCdr& cdr, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, void *data)
{
	ZeroCopy* pData = static_cast<ZeroCopy*>(data);
	cdr.set_buf(reinterpret_cast<void*>(data_value->value()), data_value->length());
	pData->deserialize(cdr);
	return true;
}
// The func of getKey is non-thread-safe
bool ZeroCopyTopicDataType::get_key(void* data, InstanceHandle_t* ihandle)
{
	if (!ZeroCopy::is_key_defined())
	{
		return false;
	}
	ZeroCopy* pData = static_cast<ZeroCopy*>(data);
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
bool ZeroCopyTopicDataType::get_key(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, InstanceHandle_t* ihandle)
{
	if (!ZeroCopy::is_key_defined())
	{
		return false;
	}
	ZeroCopy data;
	DdsCdr cdr;
	deserialize(cdr,data_value,reinterpret_cast<void*>(&data));
	get_key(reinterpret_cast<void*>(&data),ihandle);
	return true;
}
bool ZeroCopyTopicDataType::init_data_ptr(void* data)
{
	if (data == nullptr)
	{
		return false;
	}
	new(data)ZeroCopy;

	return true;
}
uint32_t ZeroCopyTopicDataType::get_cdr_serialized_size(void *data)
{
	if (data == nullptr)
	{
		return 0U;
	}
	ZeroCopy* pData = static_cast<ZeroCopy*>(data);

	return pData->max_align_size(0U);
}
bool ZeroCopyTopicDataType::is_with_key()
{
	return ZeroCopy::is_key_defined();
}
bool ZeroCopyTopicDataType::is_plain_types()
{
	return ZeroCopy::is_plain_types();
}
void* ZeroCopyTopicDataType::create_data_resource()
{
	ZeroCopy* pData = new ZeroCopy;

	return pData;
}
void ZeroCopyTopicDataType::release_data_resource(void *data)
{
	if (data == nullptr)
	{
		return;
	}
	ZeroCopy* pData = reinterpret_cast<ZeroCopy*>(data);
	delete pData;
	pData = nullptr;
}
