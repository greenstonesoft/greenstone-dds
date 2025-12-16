/**************************************************************
* @file HelloworldTopicDataType.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2025
* All rights reserved
**************************************************************/

#include "HelloworldTopicDataType.h"
#include "swiftdds/rtps/CdrSize.h"

HelloWorldTopicDataType::HelloWorldTopicDataType() : TopicDataType()
{
	set_name("HelloWorldTopicDataType");
}
HelloWorldTopicDataType::~HelloWorldTopicDataType()
{

}
bool HelloWorldTopicDataType::serialize(DdsCdr& cdr, void *data, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value)
{
	HelloWorld* pData = static_cast<HelloWorld*>(data);
	cdr.serialize(*pData);
	void *addr{nullptr};
	data_value->length(cdr.get_buf(&addr));
	data_value->value(static_cast<octet *>(addr));
	return true;
}
bool HelloWorldTopicDataType::deserialize(DdsCdr& cdr, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, void *data)
{
	HelloWorld* pData = static_cast<HelloWorld*>(data);
	cdr.set_buf(reinterpret_cast<void*>(data_value->value()), data_value->length());
	cdr.deserialize(*pData);
	return true;
}
// The func of getKey is non-thread-safe
bool HelloWorldTopicDataType::get_key(void* data, InstanceHandle_t* ihandle) noexcept
{
	if (!HelloWorld::is_key_defined())
	{
		return false;
	}
	HelloWorld* pData = static_cast<HelloWorld*>(data);
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
bool HelloWorldTopicDataType::get_key(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, InstanceHandle_t* ihandle) noexcept
{
	if (!HelloWorld::is_key_defined())
	{
		return false;
	}
	HelloWorld *data = new HelloWorld{};
	DdsCdr cdr;
	deserialize(cdr,data_value,reinterpret_cast<void*>(data));
	get_key(reinterpret_cast<void*>(data),ihandle);

	delete data;

	return true;
}
bool HelloWorldTopicDataType::init_data_ptr(void* data) noexcept
{
	if (data == nullptr)
	{
		return false;
	}
	new(data)HelloWorld;

	return true;
}
uint32_t HelloWorldTopicDataType::get_cdr_serialized_size(void *data) noexcept
{
	if (data == nullptr)
	{
		return 0U;
	}
	HelloWorld* pData = static_cast<HelloWorld*>(data);
	uint32_t max_size = pData->max_align_size(4U);

	return greenstone::dds::CdrUtil::alignment_bytes(max_size, 4U);
}
bool HelloWorldTopicDataType::is_with_key() noexcept
{
	return HelloWorld::is_key_defined();
}
bool HelloWorldTopicDataType::is_plain_types() noexcept
{
	return HelloWorld::is_plain_types();
}
void* HelloWorldTopicDataType::create_data_resource() noexcept
{
	HelloWorld* pData = new HelloWorld;

	return pData;
}
void HelloWorldTopicDataType::release_data_resource(void *data) noexcept
{
	if (data == nullptr)
	{
		return;
	}
	HelloWorld* pData = reinterpret_cast<HelloWorld*>(data);
	delete pData;
	pData = nullptr;
}
greenstone::dds::SerializedPayloadHeader const HelloWorldTopicDataType::get_serialized_payload_header() noexcept
{
	return HelloWorld::get_serialized_payload_header();
}

void* const HelloWorldTopicDataType::get_key_value_data(void * const data) noexcept
{
	if(!is_with_key())
	{
		return nullptr;
	}
	HelloWorld* pData = reinterpret_cast<HelloWorld*>(data);
	HelloWorld* newData = new HelloWorld{};
	newData->set_key_val(pData);

	return newData;
}

void* const HelloWorldTopicDataType::get_key_value_data(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value) noexcept
{
	if(!is_with_key())
	{
		return nullptr;
	}
	HelloWorld *data = new HelloWorld{};
	DdsCdr cdr;
	deserialize(cdr,data_value,reinterpret_cast<void*>(data));

	void* newData = get_key_value_data(data);

	delete data;

	return newData;
}

void HelloWorldTopicDataType::copy_key_value_to_data(void const *const key_data, void *const data) noexcept
{
	if(!is_with_key())
	{
		return;
	}
	HelloWorld* pData = reinterpret_cast<HelloWorld*>(data);
	HelloWorld const* const keyData = reinterpret_cast<HelloWorld const* const>(key_data);
	pData->set_key_val(keyData);
}

uint32_t HelloWorldTopicDataType::data_size_of() noexcept
{
	return sizeof(HelloWorld);
}

