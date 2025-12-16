/**************************************************************
* @file Helloworld.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2025
* All rights reserved
**************************************************************/

#include "Helloworld.h"
#include "swiftdds/rtps/CdrSize.h"
//#include <iostream>

HelloWorld::HelloWorld()
{
	m_id = 0;
	m_index = 0;

}

DdsCdr& HelloWorld::serialize(DdsCdr &cdr) const
{
	cdr.serialize(m_id);
	cdr.serialize(m_index);
	cdr.serialize(m_message);

	return cdr;
}
uint32_t HelloWorld::serialize(void *const data, char *const payload_buf, uint32_t const payload_len)
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
	HelloWorld* pData = static_cast<HelloWorld*>(data);
	cdr.serialize(*pData);
	void *addr{nullptr};
	return cdr.get_buf(&addr);
}

DdsCdr& HelloWorld::deserialize(DdsCdr &cdr)
{
	cdr.deserialize(m_id);
	cdr.deserialize(m_index);
	cdr.deserialize(m_message);

	return cdr;
}
bool HelloWorld::deserialize(char *const payload_buf, uint32_t const payload_len, void *const data)
{
	HelloWorld* pData = static_cast<HelloWorld*>(data);
	DdsCdr cdr;
	cdr.set_buf(payload_buf, payload_len);
	cdr.deserialize(*pData);
	return true;
}

bool HelloWorld::is_key_defined()
{
	return true;

}
void HelloWorld::serialize_key(DdsCdr &cdr) const
{
	cdr.serialize(m_id);

}
void HelloWorld::serialize_key(char **buf,unsigned int *len)
{
	static greenstone::dds::SerializedPayloadHeader payloadHeader{{0x00,0x01},{0x00,0x00}};
	if(is_key_serialize_by_cdr())
	{
		DdsCdr cdr;
		cdr.init(payloadHeader);
		serialize_key(cdr);
		*len = cdr.get_buf(reinterpret_cast<void**>(buf));
	}
	else
	{
		*buf = reinterpret_cast<char*>(&m_id);
		*len = sizeof(unsigned short);
	}

}
bool HelloWorld::is_key_serialize_by_cdr()
{
	return false;

}
bool HelloWorld::is_plain_types()
{
	return false;
}
uint32_t HelloWorld::max_align_size(uint32_t const _cur_al) const
{
	uint32_t maxSize = _cur_al;
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_id);
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_index);
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_message);
	return maxSize;

}
greenstone::dds::SerializedPayloadHeader const HelloWorld::get_serialized_payload_header()
{
	static greenstone::dds::SerializedPayloadHeader const header {{0x00,0x01},{0x00,0x00}};    // PLAIN_CDR, LITTLE_ENDIAN
	return header;

}
void HelloWorld::set_key_val(HelloWorld const* const _data) noexcept
{
	this->m_id = _data->m_id;

}
void HelloWorld::id(unsigned short const _id)
{
	m_id = _id;
}
unsigned short HelloWorld::id() const
{
	return m_id;
}
unsigned short& HelloWorld::id()
{
	return m_id;
}

void HelloWorld::index(uint32_t const _index)
{
	m_index = _index;
}
uint32_t HelloWorld::index() const
{
	return m_index;
}
uint32_t& HelloWorld::index()
{
	return m_index;
}

void HelloWorld::message(std::string const &_message)
{
	m_message = _message;
}
void HelloWorld::message(std::string &&_message)
{
	m_message = std::move(_message);
}
std::string const& HelloWorld::message() const
{
	return m_message;
}
std::string& HelloWorld::message()
{
	return m_message;
}

