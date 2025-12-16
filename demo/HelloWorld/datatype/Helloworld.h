/**************************************************************
* @file Helloworld.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2025
* All rights reserved
**************************************************************/

#ifndef HELLOWORLD_a9c2833f9abc58f4c147f9f3717c8d60_H
#define HELLOWORLD_a9c2833f9abc58f4c147f9f3717c8d60_H

#include <stdint.h>
#include <vector>
#include <array>
#include <map>
#include <string>
#include "swiftdds/dcps/SwiftDdsExport.h"
#include "swiftdds/rtps/DdsOptionalMember.h"




/**
* @class HelloWorld
* @brief A class as the datatype for data exchange.
* @note
*/

class HelloWorld
{
public:
	static constexpr bool IS_KEY_DEFINED = true;
	static constexpr uint32_t DATA_SIZE = 0U;
	static constexpr bool IS_DATA_PADDING = true;
	static constexpr bool IS_ID_DEFINED = false;

	HelloWorld();
	~HelloWorld() = default;
	HelloWorld(HelloWorld const &x) = default;
	HelloWorld(HelloWorld &&x) = default;
	HelloWorld& operator=(HelloWorld const &x) = default;
	HelloWorld& operator=(HelloWorld &&x) = default;

	DdsCdr& serialize(DdsCdr &cdr) const;
	static uint32_t serialize(void *const data, char *const payload_buf, uint32_t const payload_len);

	DdsCdr& deserialize(DdsCdr &cdr);
	static bool deserialize(char *const payload_buf, uint32_t const payload_len, void *const data);

	static bool is_key_defined();
	void serialize_key(DdsCdr &cdr) const;

	void serialize_key(char **buf,unsigned int *len);
	bool is_key_serialize_by_cdr();
	static bool is_plain_types();
	uint32_t max_align_size(uint32_t const _cur_al) const;
	static greenstone::dds::SerializedPayloadHeader const get_serialized_payload_header();
	void set_key_val(HelloWorld const* const _data) noexcept;



	void id(unsigned short const _id);
	unsigned short id() const;
	unsigned short& id();

	void index(uint32_t const _index);
	uint32_t index() const;
	uint32_t& index();

	void message(std::string const &_message);
	void message(std::string &&_message);
	std::string const& message() const;
	std::string& message();





private:
	unsigned short m_id;
	uint32_t m_index;
	std::string m_message;

};


#endif	// HELLOWORLD_a9c2833f9abc58f4c147f9f3717c8d60_H

