/**************************************************************
* @file TestMsg.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#include "TestMsg.h"
#include "rtps/CdrSize.h"
//#include <iostream>

TestMsg::TestMsg()
{
	m_key = 0;
	m_index = 0;
	m_length = 0;

	m_payloadHeader.representation_identifier[0] = 1;
	m_payloadHeader.representation_identifier[1] = 0;
	m_payloadHeader.representation_options[0] = 0;
	m_payloadHeader.representation_options[1] = 0;
}
TestMsg::~TestMsg()
{
}
TestMsg::TestMsg(const TestMsg &x)
{
	m_key = x.m_key;
	m_index = x.m_index;
	m_length = x.m_length;
	m_message = x.m_message;

	m_payloadHeader = x.m_payloadHeader;
}
TestMsg::TestMsg(TestMsg &&x)
{
	m_key = x.m_key;
	m_index = x.m_index;
	m_length = x.m_length;
	m_message = std::move(x.m_message);

	m_payloadHeader = x.m_payloadHeader;
}
TestMsg& TestMsg::operator=(const TestMsg &x)
{
	m_payloadHeader = x.m_payloadHeader;

	m_key = x.m_key;
	m_index = x.m_index;
	m_length = x.m_length;
	m_message = x.m_message;
	return *this;

}
TestMsg& TestMsg::operator=(TestMsg &&x)
{
	m_payloadHeader = x.m_payloadHeader;
	m_key = x.m_key;
	m_index = x.m_index;
	m_length = x.m_length;
	m_message = std::move(x.m_message);
	return *this;

}

DdsCdr& TestMsg::serialize(DdsCdr &cdr) const
{
	cdr.serialize(m_key);
	cdr.serialize(m_index);
	cdr.serialize(m_length);
	cdr.serialize(m_message);

	return cdr;
}
DdsCdr& TestMsg::deserialize(DdsCdr &cdr)
{
	cdr.deserialize(m_key);
	cdr.deserialize(m_index);
	cdr.deserialize(m_length);
	cdr.deserialize(m_message);

	return cdr;
}
bool TestMsg::is_key_defined()
{
	return true;

}
void TestMsg::serialize_key(DdsCdr &cdr) const
{
	cdr.serialize(m_key);

}
void TestMsg::serialize_key(char **buf,unsigned int *len)
{
	if(is_key_serialize_by_cdr())
	{
		DdsCdr cdr;
		cdr.init(m_payloadHeader);
		serialize_key(cdr);
		*len = cdr.get_buf(reinterpret_cast<void**>(buf));
	}
	else
	{
		*buf = reinterpret_cast<char*>(&m_key);
		*len = sizeof(int32_t);
	}

}
bool TestMsg::is_key_serialize_by_cdr()
{
	return false;

}
bool TestMsg::is_plain_types()
{
	return false;
}
uint32_t TestMsg::max_align_size(uint32_t const _cur_al) const
{
	uint32_t maxSize = _cur_al;
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_key);
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_index);
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_length);
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_message);
	return maxSize;

}
void TestMsg::key(int32_t _key)
{
	m_key = _key;
}
int32_t TestMsg::key() const
{
	return m_key;
}
int32_t& TestMsg::key()
{
	return m_key;
}

void TestMsg::index(uint32_t _index)
{
	m_index = _index;
}
uint32_t TestMsg::index() const
{
	return m_index;
}
uint32_t& TestMsg::index()
{
	return m_index;
}

void TestMsg::length(uint32_t _length)
{
	m_length = _length;
}
uint32_t TestMsg::length() const
{
	return m_length;
}
uint32_t& TestMsg::length()
{
	return m_length;
}

void TestMsg::message(const std::string &_message)
{
	m_message = _message;
}
void TestMsg::message(std::string &&_message)
{
	m_message = std::move(_message);
}
const std::string& TestMsg::message() const
{
	return m_message;
}
std::string& TestMsg::message()
{
	return m_message;
}

