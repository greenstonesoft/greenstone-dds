/**************************************************************
* @file WaitSetTopicDataType.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2025
* All rights reserved
**************************************************************/

#include "WaitSetTopicDataType.h"
#include "swiftdds/rtps/CdrSize.h"

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
	cdr.serialize(*pData);
	void *addr{nullptr};
	data_value->length(cdr.get_buf(&addr));
	data_value->value(static_cast<octet *>(addr));
	return true;
}
bool WaitSetTopicDataType::deserialize(DdsCdr& cdr, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, void *data)
{
	WaitSet* pData = static_cast<WaitSet*>(data);
	cdr.set_buf(reinterpret_cast<void*>(data_value->value()), data_value->length());
	cdr.deserialize(*pData);
	return true;
}
// The func of getKey is non-thread-safe
bool WaitSetTopicDataType::get_key(void* data, InstanceHandle_t* ihandle) noexcept
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
bool WaitSetTopicDataType::get_key(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, InstanceHandle_t* ihandle) noexcept
{
	if (!WaitSet::is_key_defined())
	{
		return false;
	}
	WaitSet *data = new WaitSet{};
	DdsCdr cdr;
	deserialize(cdr,data_value,reinterpret_cast<void*>(data));
	get_key(reinterpret_cast<void*>(data),ihandle);

	delete data;

	return true;
}
bool WaitSetTopicDataType::init_data_ptr(void* data) noexcept
{
	if (data == nullptr)
	{
		return false;
	}
	new(data)WaitSet;

	return true;
}
uint32_t WaitSetTopicDataType::get_cdr_serialized_size(void *data) noexcept
{
	if (data == nullptr)
	{
		return 0U;
	}
	WaitSet* pData = static_cast<WaitSet*>(data);
	uint32_t max_size = pData->max_align_size(4U);

	return greenstone::dds::CdrUtil::alignment_bytes(max_size, 4U);
}
bool WaitSetTopicDataType::is_with_key() noexcept
{
	return WaitSet::is_key_defined();
}
bool WaitSetTopicDataType::is_plain_types() noexcept
{
	return WaitSet::is_plain_types();
}
void* WaitSetTopicDataType::create_data_resource() noexcept
{
	WaitSet* pData = new WaitSet;

	return pData;
}
void WaitSetTopicDataType::release_data_resource(void *data) noexcept
{
	if (data == nullptr)
	{
		return;
	}
	WaitSet* pData = reinterpret_cast<WaitSet*>(data);
	delete pData;
	pData = nullptr;
}
greenstone::dds::SerializedPayloadHeader const WaitSetTopicDataType::get_serialized_payload_header() noexcept
{
	return WaitSet::get_serialized_payload_header();
}

void* const WaitSetTopicDataType::get_key_value_data(void * const data) noexcept
{
	if(!is_with_key())
	{
		return nullptr;
	}
	WaitSet* pData = reinterpret_cast<WaitSet*>(data);
	WaitSet* newData = new WaitSet{};
	newData->set_key_val(pData);

	return newData;
}

void* const WaitSetTopicDataType::get_key_value_data(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value) noexcept
{
	if(!is_with_key())
	{
		return nullptr;
	}
	WaitSet *data = new WaitSet{};
	DdsCdr cdr;
	deserialize(cdr,data_value,reinterpret_cast<void*>(data));

	void* newData = get_key_value_data(data);

	delete data;

	return newData;
}

void WaitSetTopicDataType::copy_key_value_to_data(void const *const key_data, void *const data) noexcept
{
	if(!is_with_key())
	{
		return;
	}
	WaitSet* pData = reinterpret_cast<WaitSet*>(data);
	WaitSet const* const keyData = reinterpret_cast<WaitSet const* const>(key_data);
	pData->set_key_val(keyData);
}

uint32_t WaitSetTopicDataType::data_size_of() noexcept
{
	return sizeof(WaitSet);
}

