/**************************************************************
 * @file UtilHelper.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_RTPS_UTILHELPER_H
#define GSTONE_RTPS_UTILHELPER_H

#include "swiftdds/dcps/DeclExport.h"
#include "swiftdds/dcps/PITypes.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace rtps {
/**
 * @class UtilHelper
 * @brief Collection of some helpful functions.
 */
class GS_DDS4CPP_API UtilHelper final
{
public:
    /* The length of digest. */
    static constexpr guint32_t DIGEST_LENGTH {16U};

    /**
     * @brief Generate the digest os a buffer.
     * @param [in] a_buffer The buffer holding data.
     * @param [in] the_len Length of the data.
     * @param [in,out] the_digest The generated digest.
     * @param [in] the_digest_len The length of digest.
     * @return guint32_t
     */
    static guint32_t generate_digest(gchar_t const *const a_buffer, guint32_t const the_len, gchar_t *const the_digest,
                                     guint32_t const the_digest_len = DIGEST_LENGTH);
};
} /*rtps*/
} /*gstone*/

__GS_DDS4CPP_END_DECLS

#endif /*GSTONE_RTPS_UTILHELPER_H*/
