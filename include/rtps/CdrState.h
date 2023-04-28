/**************************************************************
 * @file CdrState.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
 **************************************************************/
#ifndef GSTONE_CDRSTATE_API_H
#define GSTONE_CDRSTATE_API_H 1

#include <cstdint>
#include "dcps/DeclExport.h"
#include "dcps/PITypes.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone
{
namespace rtps
{

/**
 * @class CdrEndian
 * @brief define the endian type
*/ 
enum class CdrEndian : gint32_t
{
	CDR_LITTLE_ENDIAN = 0,
	CDR_BIG_ENDIAN = 1
};

/**
 * @class CdrEncoding
 * @brief define the encapsulation type
*/ 
enum class CdrEncoding : gint32_t
{
	CDR_ENCODING = 0,
	PLCDR_ENCODING = 1
};

/**
 * @class CdrEversion
 * @brief define the version information
*/ 
enum class CdrEversion : gint32_t
{
	VERSION_NONE = 0x00,
	VERSION1 = 0x01,
	VERSION2 = 0x02
};

constexpr guint32_t ALIGN_ENCODING_4 {4U};
constexpr guint32_t ALIGN_ENCODING_8 {8U};

/**
 * @class CdrState
 * @brief used to preserve the cdr state
 * @note working for cdr
*/ 
class GS_DDS4CPP_API CdrState final
{
public:

	/**
	 * @brief default constructor for CdrState object
	 * @note no exception
	*/
	CdrState() noexcept;

	/**
	 * @brief default move copy constructor for CdrState object,which had declared deletion
	 * @param [in] state done complete object
	*/
	CdrState(CdrState const && state) = delete;

	/**
	 * @brief default move assgin constructor for CdrState object,which declared deletion
	 * @param [in] state assgined object
	 * @return CdrState& 
	 * @note had delete
	*/
	CdrState &operator=(CdrState const &&state) = delete;

	/**
	 * @brief default destuctor for CdrState object
	*/
	~CdrState() noexcept = default;

	/**
	 * @brief default construtor  for CdrState object
	 * @param [in] state done complete object
	*/
	CdrState(CdrState const& state) = default;

	/**
	 * @brief default assign constructor for CdrState object
	 * @param [in] state assign object
	 * @return CdrState& 
	*/
	CdrState& operator=(CdrState const& state) & noexcept = default;

	/**
	 * @brief init the state object
	 * @param [in] endian cdr endian flag
	 * @param [in] version  cdr version
	 * @param [in] encoding encapsulation flag
	 * @note no exception
	*/
	gvoid_t init(CdrEndian const endian, CdrEversion const version, CdrEncoding const encoding = CdrEncoding::CDR_ENCODING) noexcept;

	/**
	 * @brief get the Encoding object
	 * @return CdrEncoding
	 * @retval return the current encoding flag
	 * @note no exception
	*/
	inline CdrEncoding get_encoding() const noexcept
	{
		return m_encoding;
	}

	/**
	 * @brief assign the current offset
	 * @param [in] offset_index new offset value
	 * @note no exception
	*/
	inline gvoid_t reset_offset(guint32_t const offset_index) noexcept
	{
		m_offset = offset_index;
	}

	/**
	 * @brief change the current offset
	 * @param [in] step new offset value
	 * @note no exception
	*/
	gvoid_t update_offset(guint32_t const step) noexcept;

	/**
	 * @brief get the current offset
	 * @return guint32_t 
	 * @retval not negative done offset
	 * @note no exception
	*/
	inline guint32_t cur_offset(gvoid_t) const noexcept
	{
		return m_offset;
	}

	/**
	 * @brief check the encoding type
	 * @param [in] encoding_flag the checking type
	 * @return gbool_t 
	 * @retval true if checking type matched with done type
	 * @retval false if checking fail
	 * @note no exception
	*/
	gbool_t check_encoding(CdrEncoding const encoding_flag) const noexcept;

	/**
	 * @brief set the max-alignment
	 * @param [in] new_align the new alignement value
	 * @note no exception
	*/
	gvoid_t update_maxalign(guint32_t const new_align) noexcept;

	/**
	 * @brief get the padding size
	 * @param [in] count the data size
	 * @return guint32_t 
	 * @retval return not negative padding size
	 * @note no exception
	*/
	guint32_t padding_size(guint32_t const count) const noexcept;

	/**
	 * @brief get the align size
	 * @param [in] encoding_flag the cdr type
	 * @param [in] t_value four bytes aligned flag
	 * @param [in] f_value eight bytes aligned flag
	 * @return guint32_t 
	 * @retval return not negative aligned size
	 * @note no exception
	*/
	guint32_t align_size(CdrEncoding const encoding_flag, guint32_t const t_value = ALIGN_ENCODING_4, guint32_t const f_value = ALIGN_ENCODING_8) const noexcept;

	/**
	 * @brief check endiness
	 * @return gbool_t
	 * @retval true if little-endian
	 * @retval false if big-endian
	 * @note no exception
	*/
	gbool_t check_endian() const noexcept;

private:

	// endiness const flag
	CdrEndian m_endian{CdrEndian::CDR_LITTLE_ENDIAN};

	// current endiness flag
	CdrEndian m_cendian{CdrEndian::CDR_LITTLE_ENDIAN};

	// current offset
	guint32_t m_offset{0U};

	// cdr version
	CdrEversion m_eversion{CdrEversion::VERSION1};

	// max alignemnt
	guint32_t m_maxalign{ALIGN_ENCODING_8};

	// encapsulation flag
	CdrEncoding m_encoding{CdrEncoding::CDR_ENCODING};
};

}/*rtps*/
}/*gstone*/

__GS_DDS4CPP_END_DECLS

#endif /*GSTONE_RTPS_CDRSTATE_API_H*/
