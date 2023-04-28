/**************************************************************
 * @file CdrBuffer.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
 **************************************************************/
#ifndef GSTONE_CDRBUFFER_API_H
#define GSTONE_CDRBUFFER_API_H 1


#include "dcps/PITypes.h"
#include "ErrorInfo.h"
#include "dcps/DeclExport.h"


__GS_DDS4CPP_BEGIN_DECLS

namespace gstone
{
namespace rtps
{
// The max length for prepared buffer.
constexpr guint32_t MAXMEMLEN  { 1024*1024*1024U };



/**
* @class CdrBuffer
* @brief This class implements the controlling the cached buffer.
* @note The buffer is used by cdr.
*/
class GS_DDS4CPP_API CdrBuffer final
{
public:
	/**
	 * @brief Default Constructor for cdrBuffer.
	*/
	CdrBuffer() noexcept = default;

	/**
	 * @brief Defualt destructor for cdrBuffer
	*/
	~CdrBuffer() noexcept;
	
	/**
	 * @brief Get the Buf object.
	 * @param [in,out] buf The pointer for buffer.
	 * @return guint32_t 
	 * @retval the buffer length.
	 * @note no exception.
	*/
	guint32_t get_buf(gchar_t** const buf) const noexcept;

	/**
	 * @brief Set the Buf object.
	 * @param [in] buf buffer address.
	 * @param [in] len buffer length.
	 * @note no exception.
	*/
	gvoid_t set_buf(gvoid_t * const buf, guint32_t const len) noexcept;

	/**
	 * @brief Padding the buffer.
	 * @param [in] count the padding size.
	 * @note no exception.
	*/
	gvoid_t padding(guint32_t const count) noexcept;

	/**
	 * @brief Jumping the buffer's current position.
	 * @param [in] count the jumping size.
	*/
	gvoid_t jumping(guint32_t const count) noexcept;

	/**
	 * @brief Get the buffer's length
	 * @return guint32_t 
	 * @retval 0 for invalid length information
	 * @retval othres for valid length description
	 * @note no expctiopn 
	*/
	inline guint32_t length() const noexcept
	{
		return m_nLength;
	}

	/**
	 * @brief Forward the length value.
	 * @param [in] len the forwarding size.
	 * @note no exception.
	*/
	inline gvoid_t forward_length(guint32_t const len) noexcept
	{
		m_nLength -= len;
	}

	/**
	 * @brief Forward the position value.
	 * @param [in] len the forwarding size.
	 * @note  no exception.
	*/
	inline gvoid_t forward_position(guint32_t const len) noexcept
	{
		m_nPos -= len;
	}

	/**
	 * @brief Get the captured value.
	 * @return guint32_t 
	 * @retval the real captured value.
	 * @note no exception.
	*/
	inline guint32_t capture() const noexcept
	{
		return m_nCapture;
	}

	/**
	 * @brief Release the buffer.
	 * @note no exception.
	*/
	gvoid_t release() noexcept;

	/**
	 * @brief Reset the buffer's inforamtion .
	 * @note no exception.
	*/
	gvoid_t reset() noexcept;

	/**
	 * @brief Set the buffer's position.
	 * @param [in] pos the position's value.
	 * @note no exception.
	*/
	gvoid_t set_pos(guint32_t const pos) noexcept
	{
		m_nPos = pos;
	}

	/**
	 * @brief Resize the buffer.
	 * @param [in] len the resized size.
	 * @return gbool_t 
	 * @retval true resize succeed.
	 * @retval false resize fail.
	 * @note no exception.
	*/
	gbool_t resize(guint32_t const len) noexcept;

	/**
	 * @brief Serialize the common data.
	 * @param [in] data the serializing data.
	 * @note no exception.
	*/
	template <typename T> gvoid_t serialize( T const& data) noexcept(noexcept(T()))
	{
		guint32_t const dataLen { (static_cast<guint32_t>(sizeof(data)))};
		if ((m_nPos + dataLen) > m_nCapture)
		{
			if(resize(m_nPos + dataLen))
			{
			}
		}
		buffer_copy(m_pBuffer, m_nPos, &data, dataLen);
		m_nPos += dataLen;
		m_nLength += dataLen;
	}

	/**
	 * @brief Serialize the pointer data.
	 * @param [in] value the data address.
	 * @param [in] len the data length.
	 * @note no exception.
	*/
	template<typename VALUE, typename LEN> gvoid_t serialize( VALUE const* const value,  LEN const len) noexcept(std::is_nothrow_constructible<VALUE>::value)
	{
		guint32_t const dataLen { ((static_cast<guint32_t>(sizeof(VALUE))) * (static_cast<guint32_t>(len))) };
		if ((m_nPos + dataLen) > m_nCapture)
		{
			if(resize(m_nPos + dataLen))
			{
				
			}
		}
		buffer_copy(m_pBuffer, m_nPos, value, dataLen);
		m_nPos += dataLen;
		m_nLength += dataLen;
	}

	/**
	 * @brief Deserialize the common data.
	 * @param [in,out] data the reference data.
	 * @note no exception.
	*/
	template<typename T> gvoid_t deserialize(T& data) noexcept
	{
		guint32_t const dataLen { static_cast<guint32_t>(sizeof(data)) };
		if ((m_nPos + dataLen) > m_nLength)
		{

			ErrorInfo::getInstance()->setLastErrorInfo(ERROR_DESERIALIZE_OUTOFBUFLEN, "deserialize error.");
			return;
		}
		buffer_copy(&data, m_pBuffer, m_nPos, dataLen);
		m_nPos += dataLen;
	}

	/**
	 * @brief Deserialize the pointer data.
	 * @param [in,out] value the data address.
	 * @param [in] len the data length.
	 * @note no exception.
	*/
	template<typename VALUE, typename LEN> gvoid_t deserialize(VALUE * const value,  LEN const len) noexcept
	{
		guint32_t const dataLen { len * (static_cast<guint32_t>(sizeof(VALUE))) };
		if ((m_nPos + dataLen) > m_nLength)
		{
			ErrorInfo::getInstance()->setLastErrorInfo(ERROR_DESERIALIZE_OUTOFBUFLEN, "deserialize error.");
			return;
		}
		buffer_copy(value, m_pBuffer, m_nPos, dataLen);
		m_nPos += dataLen;
	}
	
	/**
	 * @brief Copy buffer.
	 * @param [in,out] dst the destination data address.
	 * @param [in] pos data begining position for destination data.
	 * @param [in] src the source data address.
	 * @param [in] count the count for copy.
	 * @note  no exception.
	*/
	static gvoid_t buffer_copy(gvoid_t *const dst, guint32_t const pos, gvoid_t const *const src, guint32_t const count) noexcept;

	/**
	 * @brief Copy buffer
	 * @param [in,out] dst the destination data address
	 * @param [in] src the source data address
	 * @param [in] pos data begining position for the source data
	 * @param [in] count the count for copy
	 * @note  no exception
	*/
	static gvoid_t buffer_copy(gvoid_t *const dst, gvoid_t const *const src, guint32_t const pos, guint32_t const count) noexcept;

private:

	/**
	 * @brief Default constructor for CdrBuffer object,which is decleared deletion.
	*/
	CdrBuffer(CdrBuffer const& buffer) = delete;
	
	/**
	 * @brief Default constructor for CdrBuffer object,which is decleared deletion.
	 * @return CdrBuffer& 
	*/
	CdrBuffer& operator=(CdrBuffer const& buffer) = delete;

	/**
	 * @brief Default constructor for CdrBuffer object,which is decleared deletion.
	*/
	CdrBuffer(CdrBuffer && buffer) = delete;

	/**
	 * @brief Default constructor for CdrBuffer object,which is decleared deletion.
	 * @return CdrBuffer& 
	*/
	CdrBuffer &operator=(CdrBuffer && buffer) = delete;


	// Pointer to the raw buffer.
	gchar_t* m_pBuffer { nullptr };

	// Current capatured position.
	guint32_t m_nCapture { 0U };


	// Current processed postion.
	guint32_t m_nPos { 0U };

	// The length of the buffer.
	guint32_t m_nLength { 0U };


};

}/*rtps*/
}/*gstone*/
__GS_DDS4CPP_END_DECLS

#endif /*GSTONE_RTPS_CDRBUFFER_API_H*/
