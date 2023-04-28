/**************************************************************
* @file Helloworld.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <stdint.h>
#include <vector>
#include <array>
#include <map>
#include <string>
#include "dcps/SwiftDdsExport.h"



/**
* @class Helloworld
* @brief A class as the datatype for data exchange.
* @note
*/

class Helloworld
{
public:
	Helloworld();
	~Helloworld();
	Helloworld(const Helloworld &x);
	Helloworld(Helloworld &&x);
	Helloworld& operator=(const Helloworld &x);
	Helloworld& operator=(Helloworld &&x);

	DdsCdr& serialize(DdsCdr &cdr) const;
	DdsCdr& deserialize(DdsCdr &cdr);

	static bool is_key_defined();
	void serialize_key(DdsCdr &cdr) const;

	void serialize_key(char **buf,unsigned int *len);
	bool is_key_serialize_by_cdr();
	static bool is_plain_types();
	uint32_t max_align_size(uint32_t const _cur_al) const;



	void id(unsigned short _id);
	unsigned short id() const;
	unsigned short& id();

	void index(uint32_t _index);
	uint32_t index() const;
	uint32_t& index();

	void message(const std::string &_message);
	void message(std::string &&_message);
	const std::string& message() const;
	std::string& message();



private:
	unsigned short m_id;
	uint32_t m_index;
	std::string m_message;

	greenstone::dds::SerializedPayloadHeader m_payloadHeader;
};


#endif	// HELLOWORLD_H
