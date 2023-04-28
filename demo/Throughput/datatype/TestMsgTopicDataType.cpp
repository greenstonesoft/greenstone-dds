/**************************************************************
* @file TestMsgTopicDataType.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#include "TestMsgTopicDataType.h"

TestMsgTopicDataType::TestMsgTopicDataType() : TopicDataType()
{
	set_name("TestMsgTopicDataType");
}
TestMsgTopicDataType::~TestMsgTopicDataType()
{

}
bool TestMsgTopicDataType::serialize(DdsCdr& cdr, void *data, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value)
{
	TestMsg* pData = static_cast<TestMsg*>(data);
	pData->serialize(cdr);
	void *addr{nullptr};
	data_value->length(cdr.get_buf(&addr));
	data_value->value(static_cast<octet *>(addr));
	return true;
}
bool TestMsgTopicDataType::deserialize(DdsCdr& cdr, std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, void *data)
{
	TestMsg* pData = static_cast<TestMsg*>(data);
	cdr.set_buf(reinterpret_cast<void*>(data_value->value()), data_value->length());
	pData->deserialize(cdr);
	return true;
}
// The func of getKey is non-thread-safe
bool TestMsgTopicDataType::get_key(void* data, InstanceHandle_t* ihandle)
{
	if (!TestMsg::is_key_defined())
	{
		return false;
	}
	TestMsg* pData = static_cast<TestMsg*>(data);
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
bool TestMsgTopicDataType::get_key(std::shared_ptr<greenstone::dds::SerializedPayload_t> data_value, InstanceHandle_t* ihandle)
{
	if (!TestMsg::is_key_defined())
	{
		return false;
	}
	TestMsg data;
	DdsCdr cdr;
	deserialize(cdr,data_value,reinterpret_cast<void*>(&data));
	get_key(reinterpret_cast<void*>(&data),ihandle);
	return true;
}
bool TestMsgTopicDataType::init_data_ptr(void* data)
{
	if (data == nullptr)
	{
		return false;
	}
	new(data)TestMsg;

	return true;
}
uint32_t TestMsgTopicDataType::get_cdr_serialized_size(void *data)
{
	if (data == nullptr)
	{
		return 0U;
	}
	TestMsg* pData = static_cast<TestMsg*>(data);

	return pData->max_align_size(0U);
}
bool TestMsgTopicDataType::is_with_key()
{
	return TestMsg::is_key_defined();
}
bool TestMsgTopicDataType::is_plain_types()
{
	return TestMsg::is_plain_types();
}
void* TestMsgTopicDataType::create_data_resource()
{
	TestMsg* pData = new TestMsg;

	return pData;
}
void TestMsgTopicDataType::release_data_resource(void *data)
{
	if (data == nullptr)
	{
		return;
	}
	TestMsg* pData = reinterpret_cast<TestMsg*>(data);
	delete pData;
	pData = nullptr;
}
