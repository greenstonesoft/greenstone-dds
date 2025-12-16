/**************************************************************
* @file ZeroCopyTopicDataType.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2025
* All rights reserved
**************************************************************/

#include "ZeroCopyTopicDataType.h"
#include "swiftdds/rtps/CdrSize.h"

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
	cdr.serialize(*pData);
	void *addr{nullptr};
	data_value->length(cdr.get_buf(&addr));
	data_value->value(static_cast<octet *>(addr));
	return true;
}
bool ZeroCopyTopicDataType::deserialize(DdsCdr& cdr, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, void *data)
{
	ZeroCopy* pData = static_cast<ZeroCopy*>(data);
	cdr.set_buf(reinterpret_cast<void*>(data_value->value()), data_value->length());
	cdr.deserialize(*pData);
	return true;
}
// The func of getKey is non-thread-safe
bool ZeroCopyTopicDataType::get_key(void* data, InstanceHandle_t* ihandle) noexcept
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
bool ZeroCopyTopicDataType::get_key(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, InstanceHandle_t* ihandle) noexcept
{
	if (!ZeroCopy::is_key_defined())
	{
		return false;
	}
	ZeroCopy *data = new ZeroCopy{};
	DdsCdr cdr;
	deserialize(cdr,data_value,reinterpret_cast<void*>(data));
	get_key(reinterpret_cast<void*>(data),ihandle);

	delete data;

	return true;
}
bool ZeroCopyTopicDataType::init_data_ptr(void* data) noexcept
{
	if (data == nullptr)
	{
		return false;
	}
	new(data)ZeroCopy;

	return true;
}
uint32_t ZeroCopyTopicDataType::get_cdr_serialized_size(void *data) noexcept
{
	if (data == nullptr)
	{
		return 0U;
	}
	ZeroCopy* pData = static_cast<ZeroCopy*>(data);
	uint32_t max_size = pData->max_align_size(4U);

	return greenstone::dds::CdrUtil::alignment_bytes(max_size, 4U);
}
bool ZeroCopyTopicDataType::is_with_key() noexcept
{
	return ZeroCopy::is_key_defined();
}
bool ZeroCopyTopicDataType::is_plain_types() noexcept
{
	return ZeroCopy::is_plain_types();
}
void* ZeroCopyTopicDataType::create_data_resource() noexcept
{
	ZeroCopy* pData = new ZeroCopy;

	return pData;
}
void ZeroCopyTopicDataType::release_data_resource(void *data) noexcept
{
	if (data == nullptr)
	{
		return;
	}
	ZeroCopy* pData = reinterpret_cast<ZeroCopy*>(data);
	delete pData;
	pData = nullptr;
}
greenstone::dds::SerializedPayloadHeader const ZeroCopyTopicDataType::get_serialized_payload_header() noexcept
{
	return ZeroCopy::get_serialized_payload_header();
}

void* const ZeroCopyTopicDataType::get_key_value_data(void * const data) noexcept
{
	if(!is_with_key())
	{
		return nullptr;
	}
	ZeroCopy* pData = reinterpret_cast<ZeroCopy*>(data);
	ZeroCopy* newData = new ZeroCopy{};
	newData->set_key_val(pData);

	return newData;
}

void* const ZeroCopyTopicDataType::get_key_value_data(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value) noexcept
{
	if(!is_with_key())
	{
		return nullptr;
	}
	ZeroCopy *data = new ZeroCopy{};
	DdsCdr cdr;
	deserialize(cdr,data_value,reinterpret_cast<void*>(data));

	void* newData = get_key_value_data(data);

	delete data;

	return newData;
}

void ZeroCopyTopicDataType::copy_key_value_to_data(void const *const key_data, void *const data) noexcept
{
	if(!is_with_key())
	{
		return;
	}
	ZeroCopy* pData = reinterpret_cast<ZeroCopy*>(data);
	ZeroCopy const* const keyData = reinterpret_cast<ZeroCopy const* const>(key_data);
	pData->set_key_val(keyData);
}

uint32_t ZeroCopyTopicDataType::data_size_of() noexcept
{
	return sizeof(ZeroCopy);
}

