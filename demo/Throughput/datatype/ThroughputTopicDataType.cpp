/**************************************************************
* @file ThroughputTopicDataType.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2025
* All rights reserved
**************************************************************/

#include "ThroughputTopicDataType.h"
#include "swiftdds/rtps/CdrSize.h"

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
	cdr.serialize(*pData);
	void *addr{nullptr};
	data_value->length(cdr.get_buf(&addr));
	data_value->value(static_cast<octet *>(addr));
	return true;
}
bool ThroughputTopicDataType::deserialize(DdsCdr& cdr, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, void *data)
{
	Throughput* pData = static_cast<Throughput*>(data);
	cdr.set_buf(reinterpret_cast<void*>(data_value->value()), data_value->length());
	cdr.deserialize(*pData);
	return true;
}
// The func of getKey is non-thread-safe
bool ThroughputTopicDataType::get_key(void* data, InstanceHandle_t* ihandle) noexcept
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
bool ThroughputTopicDataType::get_key(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, InstanceHandle_t* ihandle) noexcept
{
	if (!Throughput::is_key_defined())
	{
		return false;
	}
	Throughput *data = new Throughput{};
	DdsCdr cdr;
	deserialize(cdr,data_value,reinterpret_cast<void*>(data));
	get_key(reinterpret_cast<void*>(data),ihandle);

	delete data;

	return true;
}
bool ThroughputTopicDataType::init_data_ptr(void* data) noexcept
{
	if (data == nullptr)
	{
		return false;
	}
	new(data)Throughput;

	return true;
}
uint32_t ThroughputTopicDataType::get_cdr_serialized_size(void *data) noexcept
{
	if (data == nullptr)
	{
		return 0U;
	}
	Throughput* pData = static_cast<Throughput*>(data);
	uint32_t max_size = pData->max_align_size(4U);

	return greenstone::dds::CdrUtil::alignment_bytes(max_size, 4U);
}
bool ThroughputTopicDataType::is_with_key() noexcept
{
	return Throughput::is_key_defined();
}
bool ThroughputTopicDataType::is_plain_types() noexcept
{
	return Throughput::is_plain_types();
}
void* ThroughputTopicDataType::create_data_resource() noexcept
{
	Throughput* pData = new Throughput;

	return pData;
}
void ThroughputTopicDataType::release_data_resource(void *data) noexcept
{
	if (data == nullptr)
	{
		return;
	}
	Throughput* pData = reinterpret_cast<Throughput*>(data);
	delete pData;
	pData = nullptr;
}
greenstone::dds::SerializedPayloadHeader const ThroughputTopicDataType::get_serialized_payload_header() noexcept
{
	return Throughput::get_serialized_payload_header();
}

void* const ThroughputTopicDataType::get_key_value_data(void * const data) noexcept
{
	if(!is_with_key())
	{
		return nullptr;
	}
	Throughput* pData = reinterpret_cast<Throughput*>(data);
	Throughput* newData = new Throughput{};
	newData->set_key_val(pData);

	return newData;
}

void* const ThroughputTopicDataType::get_key_value_data(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value) noexcept
{
	if(!is_with_key())
	{
		return nullptr;
	}
	Throughput *data = new Throughput{};
	DdsCdr cdr;
	deserialize(cdr,data_value,reinterpret_cast<void*>(data));

	void* newData = get_key_value_data(data);

	delete data;

	return newData;
}

void ThroughputTopicDataType::copy_key_value_to_data(void const *const key_data, void *const data) noexcept
{
	if(!is_with_key())
	{
		return;
	}
	Throughput* pData = reinterpret_cast<Throughput*>(data);
	Throughput const* const keyData = reinterpret_cast<Throughput const* const>(key_data);
	pData->set_key_val(keyData);
}

uint32_t ThroughputTopicDataType::data_size_of() noexcept
{
	return sizeof(Throughput);
}

