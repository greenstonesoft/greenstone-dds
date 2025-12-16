/**
Author: zbf
Date: 2020/12/23
Desc: 
*/
#ifndef GSTONE_ERRORINFO_API_H
#define GSTONE_ERRORINFO_API_H 1

#include <cstring>
#include <array>

#include "swiftdds/dcps/DeclExport.h"
#include "swiftdds/dcps/PITypes.h"





__GS_DDS4CPP_BEGIN_DECLS

namespace gstone
{
namespace rtps
{

constexpr guint32_t ERROR_NONE { 0U };

/* general error code  [-1, -10)*/
constexpr guint32_t ERROR_FAILED { 1001U };

constexpr guint32_t ERROR_OUT_OF_MEMORY { 1002U };

constexpr guint32_t ERROR_ENCODING_ERROR { 1003U };


/* serialize error code [-10, -100)*/
constexpr guint32_t ERROR_SERIALIZE_FAILED { 1010U };

constexpr guint32_t ERROR_SERIALIZE_ID2PID_FAILED { 1011U };

constexpr guint32_t ERROR_SERIALIZE_ID2EMEMBERHEADER_FAILED { 1012U };

constexpr guint32_t ERROR_PID_RESERVED_OMG { 1013U };

constexpr guint32_t ERROR_PID_OUT_RANGE { 1014U };


/* deserialize error code [-100, -200]*/
constexpr guint32_t ERROR_DESERIALIZE_FAILED { 1100U };

constexpr guint32_t ERROR_DESERIALIZE_OUTOFBUFLEN { 1101U };

constexpr guint32_t MAX_ARRAY_LEN { 1024U };

class GS_DDS4CPP_API ErrorInfo 
{
public:
	static ErrorInfo* getInstance() noexcept;

	virtual ~ErrorInfo() noexcept;

	gvoid_t getLastErrorInfo(guint32_t& errorNo, gchar_t* const errorInfo) noexcept;

	gvoid_t setLastErrorInfo(gchar_t const* const filename, gint32_t const line,
		guint32_t const errorNo, gchar_t const* const errorInfo, gbool_t const isPrint = true) noexcept;
	
	gvoid_t setLastErrorInfo(guint32_t const errorNo, gchar_t const * const errorInfo, gbool_t const isPrint = true) noexcept;

private:
	guint32_t m_nErrorNo {0U};
	std::array<gchar_t, MAX_ARRAY_LEN> m_szErrorInfo{};
	static ErrorInfo* m_pInstance;

	ErrorInfo() noexcept;

	ErrorInfo( ErrorInfo const& error) = delete;
	ErrorInfo& operator=( ErrorInfo const& error) = delete;
	ErrorInfo( ErrorInfo const && _cdr) = delete;
	ErrorInfo &operator=(ErrorInfo const &&_cdr) = delete;
};

}
}
__GS_DDS4CPP_END_DECLS

#endif /*GSTONE_RTPS_ERRORINFO_API_H*/
