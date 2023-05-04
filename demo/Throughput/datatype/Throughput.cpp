/**************************************************************
* @file Throughput.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#include "Throughput.h"
#include "rtps/CdrSize.h"
//#include <iostream>

Throughput::Throughput()
{
	m_key = 0;
	m_index = 0;
	m_length = 0;

	m_payloadHeader.representation_identifier[0] = 1;
	m_payloadHeader.representation_identifier[1] = 0;
	m_payloadHeader.representation_options[0] = 0;
	m_payloadHeader.representation_options[1] = 0;
}
Throughput::~Throughput()
{
}
Throughput::Throughput(const Throughput &x)
{
	m_key = x.m_key;
	m_index = x.m_index;
	m_length = x.m_length;
	m_message = x.m_message;

	m_payloadHeader = x.m_payloadHeader;
}
Throughput::Throughput(Throughput &&x)
{
	m_key = x.m_key;
	m_index = x.m_index;
	m_length = x.m_length;
	m_message = std::move(x.m_message);

	m_payloadHeader = x.m_payloadHeader;
}
Throughput& Throughput::operator=(const Throughput &x)
{
	m_payloadHeader = x.m_payloadHeader;

	m_key = x.m_key;
	m_index = x.m_index;
	m_length = x.m_length;
	m_message = x.m_message;
	return *this;

}
Throughput& Throughput::operator=(Throughput &&x)
{
	m_payloadHeader = x.m_payloadHeader;
	m_key = x.m_key;
	m_index = x.m_index;
	m_length = x.m_length;
	m_message = std::move(x.m_message);
	return *this;

}

DdsCdr& Throughput::serialize(DdsCdr &cdr) const
{
	cdr.serialize(m_key);
	cdr.serialize(m_index);
	cdr.serialize(m_length);
	cdr.serialize(m_message);

	return cdr;
}
DdsCdr& Throughput::deserialize(DdsCdr &cdr)
{
	cdr.deserialize(m_key);
	cdr.deserialize(m_index);
	cdr.deserialize(m_length);
	cdr.deserialize(m_message);

	return cdr;
}
bool Throughput::is_key_defined()
{
	return true;

}
void Throughput::serialize_key(DdsCdr &cdr) const
{
	cdr.serialize(m_key);

}
void Throughput::serialize_key(char **buf,unsigned int *len)
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
bool Throughput::is_key_serialize_by_cdr()
{
	return false;

}
bool Throughput::is_plain_types()
{
	return false;
}
uint32_t Throughput::max_align_size(uint32_t const _cur_al) const
{
	uint32_t maxSize = _cur_al;
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_key);
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_index);
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_length);
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_message);
	return maxSize;

}
void Throughput::key(int32_t _key)
{
	m_key = _key;
}
int32_t Throughput::key() const
{
	return m_key;
}
int32_t& Throughput::key()
{
	return m_key;
}

void Throughput::index(uint32_t _index)
{
	m_index = _index;
}
uint32_t Throughput::index() const
{
	return m_index;
}
uint32_t& Throughput::index()
{
	return m_index;
}

void Throughput::length(uint32_t _length)
{
	m_length = _length;
}
uint32_t Throughput::length() const
{
	return m_length;
}
uint32_t& Throughput::length()
{
	return m_length;
}

void Throughput::message(const std::string &_message)
{
	m_message = _message;
}
void Throughput::message(std::string &&_message)
{
	m_message = std::move(_message);
}
const std::string& Throughput::message() const
{
	return m_message;
}
std::string& Throughput::message()
{
	return m_message;
}

