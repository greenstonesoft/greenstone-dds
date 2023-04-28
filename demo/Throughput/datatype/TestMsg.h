/**************************************************************
* @file TestMsg.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#ifndef TESTMSG_H
#define TESTMSG_H

#include <stdint.h>
#include <vector>
#include <array>
#include <map>
#include <string>
#include "dcps/SwiftDdsExport.h"



/**
* @class TestMsg
* @brief A class as the datatype for data exchange.
* @note
*/

class TestMsg
{
public:
	TestMsg();
	~TestMsg();
	TestMsg(const TestMsg &x);
	TestMsg(TestMsg &&x);
	TestMsg& operator=(const TestMsg &x);
	TestMsg& operator=(TestMsg &&x);

	DdsCdr& serialize(DdsCdr &cdr) const;
	DdsCdr& deserialize(DdsCdr &cdr);

	static bool is_key_defined();
	void serialize_key(DdsCdr &cdr) const;

	void serialize_key(char **buf,unsigned int *len);
	bool is_key_serialize_by_cdr();
	static bool is_plain_types();
	uint32_t max_align_size(uint32_t const _cur_al) const;



	void key(int32_t _key);
	int32_t key() const;
	int32_t& key();

	void index(uint32_t _index);
	uint32_t index() const;
	uint32_t& index();

	void length(uint32_t _length);
	uint32_t length() const;
	uint32_t& length();

	void message(const std::string &_message);
	void message(std::string &&_message);
	const std::string& message() const;
	std::string& message();



private:
	int32_t m_key;
	uint32_t m_index;
	uint32_t m_length;
	std::string m_message;

	greenstone::dds::SerializedPayloadHeader m_payloadHeader;
};


#endif	// TESTMSG_H
