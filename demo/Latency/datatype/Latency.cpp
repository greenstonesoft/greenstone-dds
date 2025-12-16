/**************************************************************
* @file Latency.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2025
* All rights reserved
**************************************************************/

#include "Latency.h"
#include "swiftdds/rtps/CdrSize.h"
//#include <iostream>

Latency::Latency()
{
	m_key = 0;
	m_index = 0;
	m_length = 0;

}

DdsCdr& Latency::serialize(DdsCdr &cdr) const
{
	cdr.serialize(m_key);
	cdr.serialize(m_index);
	cdr.serialize(m_length);
	cdr.serialize(m_message);

	return cdr;
}
uint32_t Latency::serialize(void *const data, char *const payload_buf, uint32_t const payload_len)
{
	if((data == nullptr) || (payload_buf == nullptr) || (payload_len == 0U))
	{
		return 0U;
	}
	greenstone::dds::SerializedPayloadHeader const header{get_serialized_payload_header()};
	memcpy(payload_buf, &header, 4U);
	DdsCdr cdr;
	cdr.set_buf(payload_buf, payload_len);
	cdr.move_length(payload_len-4U);
	Latency* pData = static_cast<Latency*>(data);
	cdr.serialize(*pData);
	void *addr{nullptr};
	return cdr.get_buf(&addr);
}

DdsCdr& Latency::deserialize(DdsCdr &cdr)
{
	cdr.deserialize(m_key);
	cdr.deserialize(m_index);
	cdr.deserialize(m_length);
	cdr.deserialize(m_message);

	return cdr;
}
bool Latency::deserialize(char *const payload_buf, uint32_t const payload_len, void *const data)
{
	Latency* pData = static_cast<Latency*>(data);
	DdsCdr cdr;
	cdr.set_buf(payload_buf, payload_len);
	cdr.deserialize(*pData);
	return true;
}

bool Latency::is_key_defined()
{
	return false;

}
void Latency::serialize_key(DdsCdr &cdr) const
{

}
void Latency::serialize_key(char **buf,unsigned int *len)
{

}
bool Latency::is_key_serialize_by_cdr()
{
	return false;

}
bool Latency::is_plain_types()
{
	return false;
}
uint32_t Latency::max_align_size(uint32_t const _cur_al) const
{
	uint32_t maxSize = _cur_al;
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_key);
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_index);
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_length);
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_message);
	return maxSize;

}
greenstone::dds::SerializedPayloadHeader const Latency::get_serialized_payload_header()
{
	static greenstone::dds::SerializedPayloadHeader const header {{0x00,0x01},{0x00,0x00}};    // PLAIN_CDR, LITTLE_ENDIAN
	return header;

}
void Latency::set_key_val(Latency const* const _data) noexcept
{

}
void Latency::key(int32_t const _key)
{
	m_key = _key;
}
int32_t Latency::key() const
{
	return m_key;
}
int32_t& Latency::key()
{
	return m_key;
}

void Latency::index(uint32_t const _index)
{
	m_index = _index;
}
uint32_t Latency::index() const
{
	return m_index;
}
uint32_t& Latency::index()
{
	return m_index;
}

void Latency::length(uint32_t const _length)
{
	m_length = _length;
}
uint32_t Latency::length() const
{
	return m_length;
}
uint32_t& Latency::length()
{
	return m_length;
}

void Latency::message(std::string const &_message)
{
	m_message = _message;
}
void Latency::message(std::string &&_message)
{
	m_message = std::move(_message);
}
std::string const& Latency::message() const
{
	return m_message;
}
std::string& Latency::message()
{
	return m_message;
}

