/**************************************************************
* @file Helloworld.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#include "Helloworld.h"
#include "rtps/CdrSize.h"
//#include <iostream>

Helloworld::Helloworld()
{
	m_id = 0;
	m_index = 0;
	m_message = {};

	m_payloadHeader.representation_identifier[0] = 1;
	m_payloadHeader.representation_identifier[1] = 0;
	m_payloadHeader.representation_options[0] = 0;
	m_payloadHeader.representation_options[1] = 0;
}
Helloworld::~Helloworld()
{
}
Helloworld::Helloworld(const Helloworld &x)
{
	m_id = x.m_id;
	m_index = x.m_index;
	m_message = x.m_message;

	m_payloadHeader = x.m_payloadHeader;
}
Helloworld::Helloworld(Helloworld &&x)
{
	m_id = x.m_id;
	m_index = x.m_index;
	m_message = std::move(x.m_message);

	m_payloadHeader = x.m_payloadHeader;
}
Helloworld& Helloworld::operator=(const Helloworld &x)
{
	m_payloadHeader = x.m_payloadHeader;

	m_id = x.m_id;
	m_index = x.m_index;
	m_message = x.m_message;
	return *this;

}
Helloworld& Helloworld::operator=(Helloworld &&x)
{
	m_payloadHeader = x.m_payloadHeader;
	m_id = x.m_id;
	m_index = x.m_index;
	m_message = std::move(x.m_message);
	return *this;

}

DdsCdr& Helloworld::serialize(DdsCdr &cdr) const
{
	cdr.serialize(m_id);
	cdr.serialize(m_index);
	cdr.serialize(m_message);

	return cdr;
}
DdsCdr& Helloworld::deserialize(DdsCdr &cdr)
{
	cdr.deserialize(m_id);
	cdr.deserialize(m_index);
	cdr.deserialize(m_message);

	return cdr;
}
bool Helloworld::is_key_defined()
{
	return true;

}
void Helloworld::serialize_key(DdsCdr &cdr) const
{
	cdr.serialize(m_id);

}
void Helloworld::serialize_key(char **buf,unsigned int *len)
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
bool Helloworld::is_key_serialize_by_cdr()
{
	return false;

}
bool Helloworld::is_plain_types()
{
	return true;
}
uint32_t Helloworld::max_align_size(uint32_t const _cur_al) const
{
	uint32_t maxSize = _cur_al;
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_id);
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_index);
	maxSize = greenstone::dds::CdrUtil::alignment(maxSize, m_message);
	return maxSize;

}
void Helloworld::id(unsigned short _id)
{
	m_id = _id;
}
unsigned short Helloworld::id() const
{
	return m_id;
}
unsigned short& Helloworld::id()
{
	return m_id;
}

void Helloworld::index(uint32_t _index)
{
	m_index = _index;
}
uint32_t Helloworld::index() const
{
	return m_index;
}
uint32_t& Helloworld::index()
{
	return m_index;
}

void Helloworld::message(const std::array<char,61000> &_message)
{
	m_message = _message;
}
void Helloworld::message(std::array<char,61000> &&_message)
{
	m_message = std::move(_message);
}
const std::array<char,61000>& Helloworld::message() const
{
	return m_message;
}
std::array<char,61000>& Helloworld::message()
{
	return m_message;
}

