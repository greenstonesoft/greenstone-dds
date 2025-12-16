/**************************************************************
* @file ZeroCopy.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2025
* All rights reserved
**************************************************************/

#include "ZeroCopy.h"
#include "swiftdds/rtps/CdrSize.h"
//#include <iostream>

ZeroCopy::ZeroCopy()
{
	m_id = 0;
	m_index = 0;

}

DdsCdr& ZeroCopy::serialize(DdsCdr &cdr) const
{
	cdr.serialize(m_id);
	cdr.serialize(m_index);
	cdr.serialize(m_message);

	return cdr;
}
uint32_t ZeroCopy::serialize(void *const data, char *const payload_buf, uint32_t const payload_len)
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
	ZeroCopy* pData = static_cast<ZeroCopy*>(data);
	cdr.serialize(*pData);
	void *addr{nullptr};
	return cdr.get_buf(&addr);
}

DdsCdr& ZeroCopy::deserialize(DdsCdr &cdr)
{
	cdr.deserialize(m_id);
	cdr.deserialize(m_index);
	cdr.deserialize(m_message);

	return cdr;
}
bool ZeroCopy::deserialize(char *const payload_buf, uint32_t const payload_len, void *const data)
{
	ZeroCopy* pData = static_cast<ZeroCopy*>(data);
	DdsCdr cdr;
	cdr.set_buf(payload_buf, payload_len);
	cdr.deserialize(*pData);
	return true;
}

bool ZeroCopy::is_key_defined()
{
	return true;

}
void ZeroCopy::serialize_key(DdsCdr &cdr) const
{
	cdr.serialize(m_id);

}
void ZeroCopy::serialize_key(char **buf,unsigned int *len)
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
bool ZeroCopy::is_key_serialize_by_cdr()
{
	return false;

}
bool ZeroCopy::is_plain_types()
{
	return true;
}
uint32_t ZeroCopy::max_align_size(uint32_t const _cur_al) const
{
	uint32_t maxSize = _cur_al;
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_id);
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_index);
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_message);
	return maxSize;

}
greenstone::dds::SerializedPayloadHeader const ZeroCopy::get_serialized_payload_header()
{
	static greenstone::dds::SerializedPayloadHeader const header {{0x00,0x01},{0x00,0x00}};    // PLAIN_CDR, LITTLE_ENDIAN
	return header;

}
void ZeroCopy::set_key_val(ZeroCopy const* const _data) noexcept
{
	this->m_id = _data->m_id;

}
void ZeroCopy::id(unsigned short const _id)
{
	m_id = _id;
}
unsigned short ZeroCopy::id() const
{
	return m_id;
}
unsigned short& ZeroCopy::id()
{
	return m_id;
}

void ZeroCopy::index(uint32_t const _index)
{
	m_index = _index;
}
uint32_t ZeroCopy::index() const
{
	return m_index;
}
uint32_t& ZeroCopy::index()
{
	return m_index;
}

void ZeroCopy::message(std::array<char,61000> const &_message)
{
	m_message = _message;
}
void ZeroCopy::message(std::array<char,61000> &&_message)
{
	m_message = std::move(_message);
}
std::array<char,61000> const& ZeroCopy::message() const
{
	return m_message;
}
std::array<char,61000>& ZeroCopy::message()
{
	return m_message;
}

