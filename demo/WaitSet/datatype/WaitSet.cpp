/**************************************************************
* @file WaitSet.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2025
* All rights reserved
**************************************************************/

#include "WaitSet.h"
#include "swiftdds/rtps/CdrSize.h"
//#include <iostream>

WaitSet::WaitSet()
{
	m_id = 0;
	m_index = 0;

}

DdsCdr& WaitSet::serialize(DdsCdr &cdr) const
{
	cdr.serialize(m_id);
	cdr.serialize(m_index);
	cdr.serialize(m_message);

	return cdr;
}
uint32_t WaitSet::serialize(void *const data, char *const payload_buf, uint32_t const payload_len)
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
	WaitSet* pData = static_cast<WaitSet*>(data);
	cdr.serialize(*pData);
	void *addr{nullptr};
	return cdr.get_buf(&addr);
}

DdsCdr& WaitSet::deserialize(DdsCdr &cdr)
{
	cdr.deserialize(m_id);
	cdr.deserialize(m_index);
	cdr.deserialize(m_message);

	return cdr;
}
bool WaitSet::deserialize(char *const payload_buf, uint32_t const payload_len, void *const data)
{
	WaitSet* pData = static_cast<WaitSet*>(data);
	DdsCdr cdr;
	cdr.set_buf(payload_buf, payload_len);
	cdr.deserialize(*pData);
	return true;
}

bool WaitSet::is_key_defined()
{
	return true;

}
void WaitSet::serialize_key(DdsCdr &cdr) const
{
	cdr.serialize(m_id);

}
void WaitSet::serialize_key(char **buf,unsigned int *len)
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
bool WaitSet::is_key_serialize_by_cdr()
{
	return false;

}
bool WaitSet::is_plain_types()
{
	return false;
}
uint32_t WaitSet::max_align_size(uint32_t const _cur_al) const
{
	uint32_t maxSize = _cur_al;
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_id);
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_index);
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_message);
	return maxSize;

}
greenstone::dds::SerializedPayloadHeader const WaitSet::get_serialized_payload_header()
{
	static greenstone::dds::SerializedPayloadHeader const header {{0x00,0x01},{0x00,0x00}};    // PLAIN_CDR, LITTLE_ENDIAN
	return header;

}
void WaitSet::set_key_val(WaitSet const* const _data) noexcept
{
	this->m_id = _data->m_id;

}
void WaitSet::id(unsigned short const _id)
{
	m_id = _id;
}
unsigned short WaitSet::id() const
{
	return m_id;
}
unsigned short& WaitSet::id()
{
	return m_id;
}

void WaitSet::index(uint32_t const _index)
{
	m_index = _index;
}
uint32_t WaitSet::index() const
{
	return m_index;
}
uint32_t& WaitSet::index()
{
	return m_index;
}

void WaitSet::message(std::string const &_message)
{
	m_message = _message;
}
void WaitSet::message(std::string &&_message)
{
	m_message = std::move(_message);
}
std::string const& WaitSet::message() const
{
	return m_message;
}
std::string& WaitSet::message()
{
	return m_message;
}

