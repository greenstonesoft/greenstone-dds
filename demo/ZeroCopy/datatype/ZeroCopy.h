/**************************************************************
* @file ZeroCopy.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2025
* All rights reserved
**************************************************************/

#ifndef ZEROCOPY_a94dff104bde555d97c7e483cae30da8_H
#define ZEROCOPY_a94dff104bde555d97c7e483cae30da8_H

#include <stdint.h>
#include <vector>
#include <array>
#include <map>
#include <string>
#include "swiftdds/dcps/SwiftDdsExport.h"
#include "swiftdds/rtps/DdsOptionalMember.h"




/**
* @class ZeroCopy
* @brief A class as the datatype for data exchange.
* @note
*/

class ZeroCopy
{
public:
	static constexpr bool IS_KEY_DEFINED = true;
	static constexpr uint32_t DATA_SIZE = sizeof(unsigned short) + sizeof(uint32_t) + sizeof(std::array<char,61000>);
	static constexpr bool IS_DATA_PADDING = true;
	static constexpr bool IS_ID_DEFINED = false;

	ZeroCopy();
	~ZeroCopy() = default;
	ZeroCopy(ZeroCopy const &x) = default;
	ZeroCopy(ZeroCopy &&x) = default;
	ZeroCopy& operator=(ZeroCopy const &x) = default;
	ZeroCopy& operator=(ZeroCopy &&x) = default;

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
	void set_key_val(ZeroCopy const* const _data) noexcept;



	void id(unsigned short const _id);
	unsigned short id() const;
	unsigned short& id();

	void index(uint32_t const _index);
	uint32_t index() const;
	uint32_t& index();

	void message(std::array<char,61000> const &_message);
	void message(std::array<char,61000> &&_message);
	std::array<char,61000> const& message() const;
	std::array<char,61000>& message();





private:
	unsigned short m_id;
	uint32_t m_index;
	std::array<char,61000> m_message;

};


#endif	// ZEROCOPY_a94dff104bde555d97c7e483cae30da8_H

