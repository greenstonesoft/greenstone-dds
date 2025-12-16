/**************************************************************
* @file Latency.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2025
* All rights reserved
**************************************************************/

#ifndef LATENCY_586b7204b4377df7a2a4bda4a9503736_H
#define LATENCY_586b7204b4377df7a2a4bda4a9503736_H

#include <stdint.h>
#include <vector>
#include <array>
#include <map>
#include <string>
#include "swiftdds/dcps/SwiftDdsExport.h"
#include "swiftdds/rtps/DdsOptionalMember.h"




/**
* @class Latency
* @brief A class as the datatype for data exchange.
* @note
*/

class Latency
{
public:
	static constexpr bool IS_KEY_DEFINED = false;
	static constexpr uint32_t DATA_SIZE = 0U;
	static constexpr bool IS_DATA_PADDING = true;
	static constexpr bool IS_ID_DEFINED = false;

	Latency();
	~Latency() = default;
	Latency(Latency const &x) = default;
	Latency(Latency &&x) = default;
	Latency& operator=(Latency const &x) = default;
	Latency& operator=(Latency &&x) = default;

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
	void set_key_val(Latency const* const _data) noexcept;



	void key(int32_t const _key);
	int32_t key() const;
	int32_t& key();

	void index(uint32_t const _index);
	uint32_t index() const;
	uint32_t& index();

	void length(uint32_t const _length);
	uint32_t length() const;
	uint32_t& length();

	void message(std::string const &_message);
	void message(std::string &&_message);
	std::string const& message() const;
	std::string& message();





private:
	int32_t m_key;
	uint32_t m_index;
	uint32_t m_length;
	std::string m_message;

};


#endif	// LATENCY_586b7204b4377df7a2a4bda4a9503736_H

