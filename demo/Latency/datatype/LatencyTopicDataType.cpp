/**************************************************************
* @file LatencyTopicDataType.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2025
* All rights reserved
**************************************************************/

#include "LatencyTopicDataType.h"
#include "swiftdds/rtps/CdrSize.h"

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
	cdr.serialize(*pData);
	void *addr{nullptr};
	data_value->length(cdr.get_buf(&addr));
	data_value->value(static_cast<octet *>(addr));
	return true;
}
bool LatencyTopicDataType::deserialize(DdsCdr& cdr, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, void *data)
{
	Latency* pData = static_cast<Latency*>(data);
	cdr.set_buf(reinterpret_cast<void*>(data_value->value()), data_value->length());
	cdr.deserialize(*pData);
	return true;
}
// The func of getKey is non-thread-safe
bool LatencyTopicDataType::get_key(void* data, InstanceHandle_t* ihandle) noexcept
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
bool LatencyTopicDataType::get_key(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, InstanceHandle_t* ihandle) noexcept
{
	if (!Latency::is_key_defined())
	{
		return false;
	}
	Latency *data = new Latency{};
	DdsCdr cdr;
	deserialize(cdr,data_value,reinterpret_cast<void*>(data));
	get_key(reinterpret_cast<void*>(data),ihandle);

	delete data;

	return true;
}
bool LatencyTopicDataType::init_data_ptr(void* data) noexcept
{
	if (data == nullptr)
	{
		return false;
	}
	new(data)Latency;

	return true;
}
uint32_t LatencyTopicDataType::get_cdr_serialized_size(void *data) noexcept
{
	if (data == nullptr)
	{
		return 0U;
	}
	Latency* pData = static_cast<Latency*>(data);
	uint32_t max_size = pData->max_align_size(4U);

	return greenstone::dds::CdrUtil::alignment_bytes(max_size, 4U);
}
bool LatencyTopicDataType::is_with_key() noexcept
{
	return Latency::is_key_defined();
}
bool LatencyTopicDataType::is_plain_types() noexcept
{
	return Latency::is_plain_types();
}
void* LatencyTopicDataType::create_data_resource() noexcept
{
	Latency* pData = new Latency;

	return pData;
}
void LatencyTopicDataType::release_data_resource(void *data) noexcept
{
	if (data == nullptr)
	{
		return;
	}
	Latency* pData = reinterpret_cast<Latency*>(data);
	delete pData;
	pData = nullptr;
}
greenstone::dds::SerializedPayloadHeader const LatencyTopicDataType::get_serialized_payload_header() noexcept
{
	return Latency::get_serialized_payload_header();
}

void* const LatencyTopicDataType::get_key_value_data(void * const data) noexcept
{
	if(!is_with_key())
	{
		return nullptr;
	}
	Latency* pData = reinterpret_cast<Latency*>(data);
	Latency* newData = new Latency{};
	newData->set_key_val(pData);

	return newData;
}

void* const LatencyTopicDataType::get_key_value_data(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value) noexcept
{
	if(!is_with_key())
	{
		return nullptr;
	}
	Latency *data = new Latency{};
	DdsCdr cdr;
	deserialize(cdr,data_value,reinterpret_cast<void*>(data));

	void* newData = get_key_value_data(data);

	delete data;

	return newData;
}

void LatencyTopicDataType::copy_key_value_to_data(void const *const key_data, void *const data) noexcept
{
	if(!is_with_key())
	{
		return;
	}
	Latency* pData = reinterpret_cast<Latency*>(data);
	Latency const* const keyData = reinterpret_cast<Latency const* const>(key_data);
	pData->set_key_val(keyData);
}

uint32_t LatencyTopicDataType::data_size_of() noexcept
{
	return sizeof(Latency);
}

