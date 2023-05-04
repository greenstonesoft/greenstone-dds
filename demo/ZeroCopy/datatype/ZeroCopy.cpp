/**************************************************************
* @file ZeroCopy.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#include "ZeroCopy.h"
#include "rtps/CdrSize.h"
//#include <iostream>

ZeroCopy::ZeroCopy()
{
	m_id = 0;
	m_index = 0;
	m_message = {};

	m_payloadHeader.representation_identifier[0] = 1;
	m_payloadHeader.representation_identifier[1] = 0;
	m_payloadHeader.representation_options[0] = 0;
	m_payloadHeader.representation_options[1] = 0;
}
ZeroCopy::~ZeroCopy()
{
}
ZeroCopy::ZeroCopy(const ZeroCopy &x)
{
	m_id = x.m_id;
	m_index = x.m_index;
	m_message = x.m_message;

	m_payloadHeader = x.m_payloadHeader;
}
ZeroCopy::ZeroCopy(ZeroCopy &&x)
{
	m_id = x.m_id;
	m_index = x.m_index;
	m_message = std::move(x.m_message);

	m_payloadHeader = x.m_payloadHeader;
}
ZeroCopy& ZeroCopy::operator=(const ZeroCopy &x)
{
	m_payloadHeader = x.m_payloadHeader;

	m_id = x.m_id;
	m_index = x.m_index;
	m_message = x.m_message;
	return *this;

}
ZeroCopy& ZeroCopy::operator=(ZeroCopy &&x)
{
	m_payloadHeader = x.m_payloadHeader;
	m_id = x.m_id;
	m_index = x.m_index;
	m_message = std::move(x.m_message);
	return *this;

}

DdsCdr& ZeroCopy::serialize(DdsCdr &cdr) const
{
	cdr.serialize(m_id);
	cdr.serialize(m_index);
	cdr.serialize(m_message);

	return cdr;
}
DdsCdr& ZeroCopy::deserialize(DdsCdr &cdr)
{
	cdr.deserialize(m_id);
	cdr.deserialize(m_index);
	cdr.deserialize(m_message);

	return cdr;
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
	if(is_key_serialize_by_cdr())
	{
		DdsCdr cdr;
		cdr.init(m_payloadHeader);
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
void ZeroCopy::id(unsigned short _id)
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

void ZeroCopy::index(uint32_t _index)
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

void ZeroCopy::message(const std::array<char,61000> &_message)
{
	m_message = _message;
}
void ZeroCopy::message(std::array<char,61000> &&_message)
{
	m_message = std::move(_message);
}
const std::array<char,61000>& ZeroCopy::message() const
{
	return m_message;
}
std::array<char,61000>& ZeroCopy::message()
{
	return m_message;
}

