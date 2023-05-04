/**************************************************************
* @file WaitSet.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#include "WaitSet.h"
#include "rtps/CdrSize.h"
//#include <iostream>

WaitSet::WaitSet()
{
	m_id = 0;
	m_index = 0;

	m_payloadHeader.representation_identifier[0] = 1;
	m_payloadHeader.representation_identifier[1] = 0;
	m_payloadHeader.representation_options[0] = 0;
	m_payloadHeader.representation_options[1] = 0;
}
WaitSet::~WaitSet()
{
}
WaitSet::WaitSet(const WaitSet &x)
{
	m_id = x.m_id;
	m_index = x.m_index;
	m_message = x.m_message;

	m_payloadHeader = x.m_payloadHeader;
}
WaitSet::WaitSet(WaitSet &&x)
{
	m_id = x.m_id;
	m_index = x.m_index;
	m_message = std::move(x.m_message);

	m_payloadHeader = x.m_payloadHeader;
}
WaitSet& WaitSet::operator=(const WaitSet &x)
{
	m_payloadHeader = x.m_payloadHeader;

	m_id = x.m_id;
	m_index = x.m_index;
	m_message = x.m_message;
	return *this;

}
WaitSet& WaitSet::operator=(WaitSet &&x)
{
	m_payloadHeader = x.m_payloadHeader;
	m_id = x.m_id;
	m_index = x.m_index;
	m_message = std::move(x.m_message);
	return *this;

}

DdsCdr& WaitSet::serialize(DdsCdr &cdr) const
{
	cdr.serialize(m_id);
	cdr.serialize(m_index);
	cdr.serialize(m_message);

	return cdr;
}
DdsCdr& WaitSet::deserialize(DdsCdr &cdr)
{
	cdr.deserialize(m_id);
	cdr.deserialize(m_index);
	cdr.deserialize(m_message);

	return cdr;
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
void WaitSet::id(unsigned short _id)
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

void WaitSet::index(uint32_t _index)
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

void WaitSet::message(const std::string &_message)
{
	m_message = _message;
}
void WaitSet::message(std::string &&_message)
{
	m_message = std::move(_message);
}
const std::string& WaitSet::message() const
{
	return m_message;
}
std::string& WaitSet::message()
{
	return m_message;
}

