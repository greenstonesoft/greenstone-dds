/**************************************************************
 * @file DdsCdr.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
 * All rights reserved
 **************************************************************/

#ifndef GSTONE_DDSCDR_API_H
#define GSTONE_DDSCDR_API_H 1

#include <functional>
#include <utility>
#include <vector>
#include <map>
#include <memory>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

#include "swiftdds/rtps/CdrState.h"
#include "swiftdds/rtps/CdrBuffer.h"
#include "swiftdds/rtps/SerializedPayloadHeader.h"
#include "swiftdds/dcps/DeclExport.h"
#include "swiftdds/dcps/PITypes.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace rtps {
class DdsCdrImpl;

/**
 * @class DdsCdr
 * @brief define the serialize and deserialize interfaces
 */
class GS_DDS4CPP_API DdsCdr
{
public:
    CdrState const &aux_get_cdr_state() const noexcept
    {
        return get_cdr_state();
    }

    gvoid_t aux_set_cdr_state(CdrState const &new_state) const noexcept
    {
        set_cdr_state(new_state);
    }

    gvoid_t aux_move_length(guint32_t const len) const noexcept
    {
        move_length(len);
    }

    gvoid_t aux_move_position(guint32_t const len) const noexcept
    {
        move_position(len);
    }
public:
    /**
     * @brief default constructor for DdsCdr object
     */
    DdsCdr();

    /**
     * @brief default destructor for DdsCdr object
     */
    virtual ~DdsCdr() noexcept = default;

    /**
     * @brief init the cdr object
     * @param [in] sp_header the initialization header information
     * @param [in] init_buffer_size the initialization size
     * @return gvoid_t
     */
    gvoid_t init(SerializedPayloadHeader const &sp_header, guint32_t const init_buffer_size = 0U) const noexcept;

    /**
     * @brief init the cdr object
     * @param [in] sp_header the initialization header information
     * @param [in] buf the buffer address
     * @param [in] len the buffer length
     * @return gvoid_t
     */
    gvoid_t init(SerializedPayloadHeader const &sp_header, gvoid_t *const buf, guint32_t const buffer_size) const noexcept;

    /**
     * @brief get the serialized buffer
     * @param [in,out] buf the buffer address
     * @return guint32_t
     * @retval return the buffer length
     * @note no exception
     */
    guint32_t get_buf(gvoid_t **const buf) noexcept;

    /**
     * @brief get the buffer size
     * @return guint32_t
     * @retval return the buffer length
     * @note no exception
     */
    guint32_t get_buffer_size() const noexcept;

    /**
     * @brief set the cdr's work buffer inforamtion
     * @param [in] buf the buffer address
     * @param [in] len the buffer length
     * @note no exception
     */
    gvoid_t set_buf(gvoid_t *const buf, guint32_t const len) const noexcept;

    /**
     * @brief set the cdr's work buffer inforamtion with header
     * @param [in] buf the buffer address
     * @param [in] len the buffer length
     * @param [in] header the payload header information
     * @note no exception
     */
    gvoid_t set_buf(gvoid_t *const buf, guint32_t const len, SerializedPayloadHeader const &header) noexcept;

    /**
     * @brief release the cdr
     * @note no exception
     */
    gvoid_t release() const noexcept;

    /**
     * @brief get the error information
     * @param [in,out] error_no error number
     * @param [in,out] error_info error description
     * @note no exception
     */
    gvoid_t get_last_error_info(guint32_t &error_no, gchar_t *const error_info) const noexcept;

    /**
     * @brief get the Encoding object
     * @return CdrEncoding
     * @retval return the current encoding information
     * @note no exception
     */
    CdrEncoding get_encoding() const noexcept;

    /**
     * @brief get the CdrEversion object
     * @return CdrEversion
     * @retval return the current eversion information
     * @note no exception
     */
    CdrEversion get_eversion() const noexcept;

    /**
     * @brief jump the specific steps
     * @param [in] step the steps count
     * @note no exception
     */
    gvoid_t jumping(guint32_t const step) const noexcept;

    /**
     * @brief padding the specific bytes
     * @param [in] count the padding count
     * @note no exception
     */
    gvoid_t padding(guint32_t const count) const noexcept;

    /**
     * @brief set the length offset
     * @param [in] len the offset count
     * @note no exception
     */
    gvoid_t length_offset(guint32_t const len) const noexcept;

    /**
     * @brief forword move the length index
     * @param [in] len the move count
     * @note no exception
     */
    gvoid_t move_length(guint32_t const len) const noexcept;

    /**
     * @brief forward move the position index
     * @param [in] len the move count
     * @note no exception
     */
    gvoid_t move_position(guint32_t const len) const noexcept;

    /**
     * @brief set the offset state
     * @param [in] count offset count
     * @note no exception
     */
    gvoid_t state_offset(guint32_t const count) const noexcept;

    /**
     * @brief read the pid and size information,which is a auxiliary extended function
     * @param [in,out] pid the parameter id
     * @param [in,out] size the length informaton
     * @return gbool_t
     * @retval return true if read secceed,otherwise return false
     * @note no exception
     */
    gbool_t read_pid_and_size_ex(guint16_t &pid, guint32_t &size) const noexcept;

    /**
     * @brief serialize unsigned char type data
     * @param [in] data the dealed data
     * @note no exception
     */
    gvoid_t serialize(guchar_t const data) noexcept;

    /**
     * @brief deserialize unsigned char type data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(guchar_t &data) noexcept;

    /**
     * @brief serialize unsigned char type data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(guchar_t const data, guint16_t const id) noexcept;

    /**
     * @brief deserialize unsigned char type data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(guchar_t &data, guint16_t const id) noexcept;

    /**
     * @brief serialize boolean type data
     * @param [in] data the dealed data
     * @note no exception
     */
    gvoid_t serialize(gbool_t const data) noexcept;

    /**
     * @brief deserialize boolean type data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(gbool_t &data) noexcept;

    /**
     * @brief serialize boolean type data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gbool_t const data, guint16_t const id) noexcept;

    /**
     * @brief deserialize boolean type data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gbool_t &data, guint16_t const id) noexcept;

    /**
     * @brief serialize char type data
     * @param [in] data the dealed data
     * @note no exception
     */
    gvoid_t serialize(gchar_t const data) noexcept;

    /**
     * @brief deserialize char type data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(gchar_t &data) noexcept;

    /**
     * @brief serialize char type data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gchar_t const data, guint16_t const id) noexcept;

    /**
     * @brief deserialize char type data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gchar_t &data, guint16_t const id) noexcept;

    /**
     * @brief serialize char(16 bytes) type data
     * @param [in] data the dealed data
     * @note no exception
     */
    gvoid_t serialize(gchar16_t const data) noexcept;

    /**
     * @brief deserialize char(16 bytes) type data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(gchar16_t &data) noexcept;

    /**
     * @brief serialize char(16 bytes) type data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gchar16_t const data, guint16_t const id) noexcept;

    /**
     * @brief deserialize char(16 bytes) type data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gchar16_t &data, guint16_t const id) noexcept;

    /**
     * @brief serialize int(16 bytes) type data
     * @param [in] data the dealed data
     * @note no exception
     */
    gvoid_t serialize(gint16_t const data) noexcept;

    /**
     * @brief deserialize int(16 bytes) type data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(gint16_t &data) noexcept;

    /**
     * @brief serialize int(16 bytes) type data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gint16_t const data, guint16_t const id) noexcept;

    /**
     * @brief deserialize int(16 bytes) type data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gint16_t &data, guint16_t const id) noexcept;

    /**
     * @brief serialize unsigned int(16 bytes) type data
     * @param [in] data the dealed data
     * @note no exception
     */
    gvoid_t serialize(guint16_t const data) noexcept;

    /**
     * @brief deserialize unsigned int(16 bytes) type data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(guint16_t &data) noexcept;

    /**
     * @brief serialize unsigned int(16 bytes) type data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(guint16_t const data, guint16_t const id) noexcept;

    /**
     * @brief deserialize unsigned int(16 bytes) type data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(guint16_t &data, guint16_t const id) noexcept;

    /**
     * @brief serialize int(32 bytes) type data
     * @param [in] data the dealed data
     * @note no exception
     */
    gvoid_t serialize(gint32_t const data) noexcept;

    /**
     * @brief deserialize int(32 bytes) type data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(gint32_t &data) noexcept;

    /**
     * @brief serialize int(32 bytes) type data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gint32_t const data, guint16_t const id) noexcept;

    /**
     * @brief deserialize int(32 bytes) type data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gint32_t &data, guint16_t const id) noexcept;

    /**
     * @brief serialize unsigned int(32 bytes) type data
     * @param [in] data the dealed data
     * @note no exception
     */
    gvoid_t serialize(guint32_t const data) noexcept;

    /**
     * @brief deserialize unsigned int(32 bytes) type data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(guint32_t &data) noexcept;

    /**
     * @brief serialize unsigned int(32 bytes) type data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(guint32_t const data, guint16_t const id) noexcept;

    /**
     * @brief deserialize unsigned int(32 bytes) type data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(guint32_t &data, guint16_t const id) noexcept;

    /**
     * @brief serialize int(64 bytes) type data
     * @param [in] data the dealed data
     * @note no exception
     */
    gvoid_t serialize(gint64_t const data) noexcept;

    /**
     * @brief deserialize int(64 bytes) type data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(gint64_t &data) noexcept;

    /**
     * @brief serialize int(64 bytes) type data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gint64_t const data, guint16_t const id) noexcept;

    /**
     * @brief deserialize int(64 bytes) type data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gint64_t &data, guint16_t const id) noexcept;

    /**
     * @brief serialize unsigned int(64 bytes) type data
     * @param [in] data the dealed data
     * @note no exception
     */
    gvoid_t serialize(guint64_t const data) noexcept;

    /**
     * @brief deserialize unsigned int(64 bytes) type data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(guint64_t &data) noexcept;

    /**
     * @brief serialize unsigned int(64 bytes) type data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(guint64_t const data, guint16_t const id) noexcept;

    /**
     * @brief deserialize unsigned int(64 bytes) type data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(guint64_t &data, guint16_t const id) noexcept;

    /**
     * @brief serialize float(32 bytes) type data
     * @param [in] data the dealed data
     * @note no exception
     */
    gvoid_t serialize(gfloat32_t const data) noexcept;

    /**
     * @brief deserialize float(32 bytes) type data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(gfloat32_t &data) noexcept;

    /**
     * @brief serialize float(32 bytes) type data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gfloat32_t const data, guint16_t const id) noexcept;

    /**
     * @brief deserialize float(32 bytes) type data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gfloat32_t &data, guint16_t const id) noexcept;

    /**
     * @brief serialize float(64 bytes) type data
     * @param [in] data the dealed data
     * @note no exception
     */
    gvoid_t serialize(gfloat64_t const data) noexcept;

    /**
     * @brief deserialize float(64 bytes) type data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(gfloat64_t &data) noexcept;

    /**
     * @brief serialize float(64 bytes) type data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gfloat64_t const data, guint16_t const id) noexcept;

    /**
     * @brief deserialize float(64 bytes) type data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gfloat64_t &data, guint16_t const id) noexcept;

    /**
     * @brief serialize float(128 bytes) type data
     * @param [in] data the dealed data
     * @note no exception
     */
    gvoid_t serialize(gfloat128_t const data) noexcept;

    /**
     * @brief deserialize float(128 bytes) type data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(gfloat128_t &data) noexcept;

    /**
     * @brief serialize float(128 bytes) type data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gfloat128_t const data, guint16_t const id) noexcept;

    /**
     * @brief deserialize float(128 bytes) type data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gfloat128_t &data, guint16_t const id) noexcept;

    /**
     * @brief serialize string type data
     * @param [in] data the dealed data
     * @note no exception
     */
    gvoid_t serialize(gstring_t const &data) noexcept;

    /**
     * @brief deserialize string type data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(gstring_t &data) noexcept;

    /**
     * @brief serialize string type data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gstring_t const &data, guint16_t const id) noexcept;

    /**
     * @brief deserialize string type data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gstring_t &data, guint16_t const id) noexcept;

    /**
     * @brief serialize string(wide) type data
     * @param [in] data the dealed data
     * @note no exception
     */
    gvoid_t serialize(gu16string_t const &data) noexcept;

    /**
     * @brief deserialize string(wide) type data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(gu16string_t &data) noexcept;

    /**
     * @brief serialize string(wide) type data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gu16string_t const &data, guint16_t const id) noexcept;

    /**
     * @brief deserialize string(wide) type data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gu16string_t &data, guint16_t const id) noexcept;

    /**
     * @brief serialize unsigned char type pointer data
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t serialize(guchar_t const *const data, guint32_t const size) noexcept;

    /**
     * @brief deserialize unsigned char type pointer data
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t deserialize(guchar_t *const data, guint32_t const size) noexcept;

    /**
     * @brief serialize unsigned char type pointer data with parameter id
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(guchar_t const *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief deserialize unsigned char type pointer data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(guchar_t *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief serialize boolean type pointer data
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t serialize(gbool_t const *const data, guint32_t const size) noexcept;

    /**
     * @brief deserialize boolean type pointer data
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t deserialize(gbool_t *const data, guint32_t const size) noexcept;

    /**
     * @brief serialize boolean type pointer data with parameter id
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gbool_t const *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief deserialize boolean type pointer data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gbool_t *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief serialize char type pointer data
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t serialize(gchar_t const *const data, guint32_t const size) noexcept;

    /**
     * @brief deserialize char type pointer data
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t deserialize(gchar_t *const data, guint32_t const size) noexcept;

    /**
     * @brief serialize char type pointer data with parameter id
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gchar_t const *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief deserialize char type pointer data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gchar_t *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief serialize char(wide) type pointer data
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t serialize(gchar16_t const *const data, guint32_t const size) noexcept;

    /**
     * @brief deserialize char(wide) type pointer data
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t deserialize(gchar16_t *const data, guint32_t const size) noexcept;

    /**
     * @brief serialize char(wide) type pointer data with parameter id
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gchar16_t const *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief deserialize unsigned char type pointer data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gchar16_t *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief serialize int(16 bytes) type pointer data
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t serialize(gint16_t const *const data, guint32_t const size) noexcept;

    /**
     * @brief deserialize int(16 bytes) type pointer data
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t deserialize(gint16_t *const data, guint32_t const size) noexcept;

    /**
     * @brief serialize int(16 bytes) type pointer data with parameter id
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gint16_t const *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief deserialize int(16 bytes) type pointer data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gint16_t *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief serialize unsigned int(16 bytes) type pointer data
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t serialize(guint16_t const *const data, guint32_t const size) noexcept;

    /**
     * @brief deserialize unsigned int(16 bytes) type pointer data
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t deserialize(guint16_t *const data, guint32_t const size) noexcept;

    /**
     * @brief serialize unsigned int(16 bytes) type pointer data with parameter id
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(guint16_t const *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief deserialize unsigned int(16 bytes) type pointer data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(guint16_t *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief serialize int(32 bytes) type pointer data
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t serialize(gint32_t const *const data, guint32_t const size) noexcept;

    /**
     * @brief deserialize int(32 bytes) type pointer data
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t deserialize(gint32_t *const data, guint32_t const size) noexcept;

    /**
     * @brief serialize int(32 bytes) type pointer data with parameter id
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gint32_t const *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief deserialize int(32 bytes) type pointer data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gint32_t *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief serialize unsigned int(32 bytes) type pointer data
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t serialize(guint32_t const *const data, guint32_t const size) noexcept;

    /**
     * @brief deserialize unsigned int(32 bytes) type pointer data
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t deserialize(guint32_t *const data, guint32_t const size) noexcept;

    /**
     * @brief serialize unsigned int(32 bytes) type pointer data with parameter id
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(guint32_t const *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief deserialize unsigned int(32 bytes) type pointer data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(guint32_t *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief serialize int(64 bytes) type pointer data
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t serialize(gint64_t const *const data, guint32_t const size) noexcept;

    /**
     * @brief deserialize int(64 bytes) type pointer data
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t deserialize(gint64_t *const data, guint32_t const size) noexcept;

    /**
     * @brief serialize int(64 bytes) type pointer data with parameter id
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gint64_t const *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief deserialize int(64 bytes) type pointer data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gint64_t *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief serialize unsigned int(64 bytes) type pointer data
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t serialize(guint64_t const *const data, guint32_t const size) noexcept;

    /**
     * @brief deserialize unsigned int(64 bytes) type pointer data
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t deserialize(guint64_t *const data, guint32_t const size) noexcept;

    /**
     * @brief serialize unsigned int(64 bytes) type pointer data with parameter id
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(guint64_t const *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief deserialize unsigned int(64 bytes) type pointer data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(guint64_t *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief serialize float(32 bytes) type pointer data
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t serialize(gfloat32_t const *const data, guint32_t const size) noexcept;

    /**
     * @brief deserialize float(32 bytes) type pointer data
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t deserialize(gfloat32_t *const data, guint32_t const size) noexcept;

    /**
     * @brief serialize float(32 bytes) type pointer data with parameter id
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gfloat32_t const *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief deserialize float(32 bytes) type pointer data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gfloat32_t *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief serialize float(64 bytes) type pointer data
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t serialize(gfloat64_t const *const data, guint32_t const size) noexcept;

    /**
     * @brief deserialize float(64 bytes) type pointer data
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t deserialize(gfloat64_t *const data, guint32_t const size) noexcept;

    /**
     * @brief serialize float(64 bytes) type pointer data with parameter id
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gfloat64_t const *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief deserialize float(64 bytes) type pointer data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gfloat64_t *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief serialize float(128 bytes) type pointer data
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t serialize(gfloat128_t const *const data, guint32_t const size) noexcept;

    /**
     * @brief deserialize float(128 bytes) type pointer data
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t deserialize(gfloat128_t *const data, guint32_t const size) noexcept;

    /**
     * @brief serialize float(128 bytes) type pointer data with parameter id
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gfloat128_t const *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief deserialize float(128 bytes) type pointer data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gfloat128_t *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief serialize string type pointer data
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t serialize(gstring_t const *const data, guint32_t const size) noexcept;

    /**
     * @brief deserialize float(128 bytes) type pointer data
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t deserialize(gstring_t *const data, guint32_t const size) noexcept;

    /**
     * @brief serialize string type pointer data with parameter id
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gstring_t const *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief deserialize string type pointer data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gstring_t *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief serialize string(wide) type pointer data
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t serialize(gu16string_t const *const data, guint32_t const size) noexcept;

    /**
     * @brief deserialize string(wide) type pointer data
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @note no exception
     */
    gvoid_t deserialize(gu16string_t *const data, guint32_t const size) noexcept;

    /**
     * @brief serialize string(wide) type pointer data with parameter id
     * @param [in] data the dealed data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(gu16string_t const *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief deserialize string(wide) type pointer data with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] size the data size
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(gu16string_t *const data, guint32_t const size, guint16_t const id) noexcept;

    /**
     * @brief serialize unsined char type list data
     * @param [in] data the deal data
     * @note no exception
     */
    gvoid_t serialize(std::vector<guchar_t> const &data) noexcept;

    /**
     * @brief deserialize unsined char type list data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(std::vector<guchar_t> &data) noexcept;

    /**
     * @brief serialize unsigned char type list data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(std::vector<guchar_t> const &data, guint16_t const id) noexcept;

    /**
     * @brief deserialize unsigned char type list data with parameter id
     * @param [in,out] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(std::vector<guchar_t> &data, guint16_t const id) noexcept;

    /**
     * @brief serialize boolean type list data
     * @param [in] data the deal data
     * @note no exception
     */
    gvoid_t serialize(std::vector<gbool_t> const &data) noexcept;

    /**
     * @brief deserialize boolean type list data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gbool_t> &data) noexcept;

    /**
     * @brief serialize boolean type list data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(std::vector<gbool_t> const &data, guint16_t const id) noexcept;

    /**
     * @brief deserialize boolean type list data with parameter id
     * @param [in,out] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gbool_t> &data, guint16_t const id) noexcept;

    /**
     * @brief serialize char type list data
     * @param [in] data the deal data
     * @note no exception
     */
    gvoid_t serialize(std::vector<gchar_t> const &data) noexcept;

    /**
     * @brief deserialize char type list data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gchar_t> &data) noexcept;

    /**
     * @brief serialize char type list data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(std::vector<gchar_t> const &data, guint16_t const id) noexcept;

    /**
     * @brief deserialize char type list data with parameter id
     * @param [in,out] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gchar_t> &data, guint16_t const id) noexcept;

    /**
     * @brief serialize char(wide) type list data
     * @param [in] data the deal data
     * @note no exception
     */
    gvoid_t serialize(std::vector<char16_t> const &data) noexcept;

    /**
     * @brief deserialize char(wide) type list data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(std::vector<char16_t> &data) noexcept;

    /**
     * @brief serialize char(wide) type list data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(std::vector<char16_t> const &data, guint16_t const id) noexcept;

    /**
     * @brief deserialize char(wide) type list data with parameter id
     * @param [in,out] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(std::vector<char16_t> &data, guint16_t const id) noexcept;

    /**
     * @brief serialize int(16 bytes) type list data
     * @param [in] data the deal data
     * @note no exception
     */
    gvoid_t serialize(std::vector<gint16_t> const &data) noexcept;

    /**
     * @brief deserialize int(16 bytes) type list data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gint16_t> &data) noexcept;

    /**
     * @brief serialize int(16 bytes) type list data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(std::vector<gint16_t> const &data, guint16_t const id) noexcept;

    /**
     * @brief deserialize int(16 bytes) type list data with parameter id
     * @param [in,out] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gint16_t> &data, guint16_t const id) noexcept;

    /**
     * @brief serialize unsigned int(16 bytes) type list data
     * @param [in] data the deal data
     * @note no exception
     */
    gvoid_t serialize(std::vector<guint16_t> const &data) noexcept;

    /**
     * @brief deserialize unsined int(16 bytes) type list data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(std::vector<guint16_t> &data) noexcept;

    /**
     * @brief serialize unsigned int(16 bytes) type list data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(std::vector<guint16_t> const &data, guint16_t const id) noexcept;

    /**
     * @brief deserialize unsigned int(16 bytes) type list data with parameter id
     * @param [in,out] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(std::vector<guint16_t> &data, guint16_t const id) noexcept;

    /**
     * @brief serialize int(32 bytes) type list data
     * @param [in] data the deal data
     * @note no exception
     */
    gvoid_t serialize(std::vector<gint32_t> const &data) noexcept;

    /**
     * @brief deserialize int(32 bytes) type list data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gint32_t> &data) noexcept;

    /**
     * @brief serialize int(32 bytes) type list data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(std::vector<gint32_t> const &data, guint16_t const id) noexcept;

    /**
     * @brief deserialize int(32 bytes) type list data with parameter id
     * @param [in,out] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gint32_t> &data, guint16_t const id) noexcept;

    /**
     * @brief serialize unsigned int(32 bytes) type list data
     * @param [in] data the deal data
     * @note no exception
     */
    gvoid_t serialize(std::vector<guint32_t> const &data) noexcept;

    /**
     * @brief deserialize unsined int(32 bytes) type list data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(std::vector<guint32_t> &data) noexcept;

    /**
     * @brief serialize unsigned int(32 bytes) type list data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(std::vector<guint32_t> const &data, guint16_t const id) noexcept;

    /**
     * @brief deserialize unsigned int(32 bytes) type list data with parameter id
     * @param [in,out] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(std::vector<guint32_t> &data, guint16_t const id) noexcept;

    /**
     * @brief serialize int(64 bytes) type list data
     * @param [in] data the deal data
     * @note no exception
     */
    gvoid_t serialize(std::vector<gint64_t> const &data) noexcept;

    /**
     * @brief deserialize int(64 bytes) type list data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gint64_t> &data) noexcept;

    /**
     * @brief serialize int(64 bytes) type list data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(std::vector<gint64_t> const &data, guint16_t const id) noexcept;

    /**
     * @brief deserialize int(64 bytes) type list data with parameter id
     * @param [in,out] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gint64_t> &data, guint16_t const id) noexcept;

    /**
     * @brief serialize unsigned int(64 bytes) type list data
     * @param [in] data the deal data
     * @note no exception
     */
    gvoid_t serialize(std::vector<guint64_t> const &data) noexcept;

    /**
     * @brief deserialize unsined int(64 bytes) type list data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(std::vector<guint64_t> &data) noexcept;

    /**
     * @brief serialize unsigned int(64 bytes) type list data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(std::vector<guint64_t> const &data, guint16_t const id) noexcept;

    /**
     * @brief deserialize unsigned int(64 bytes) type list data with parameter id
     * @param [in,out] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(std::vector<guint64_t> &data, guint16_t const id) noexcept;

    /**
     * @brief serialize float(32 bytes) type list data
     * @param [in] data the deal data
     * @note no exception
     */
    gvoid_t serialize(std::vector<gfloat32_t> const &data) noexcept;

    /**
     * @brief deserialize float(32 bytes) type list data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gfloat32_t> &data) noexcept;

    /**
     * @brief serialize float(32 bytes) type list data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(std::vector<gfloat32_t> const &data, guint16_t const id) noexcept;

    /**
     * @brief deserialize float(32 bytes) type list data with parameter id
     * @param [in,out] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gfloat32_t> &data, guint16_t const id) noexcept;

    /**
     * @brief serialize float(64 bytes) type list data
     * @param [in] data the deal data
     * @note no exception
     */
    gvoid_t serialize(std::vector<gfloat64_t> const &data) noexcept;

    /**
     * @brief deserialize float(64 bytes) type list data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gfloat64_t> &data) noexcept;

    /**
     * @brief serialize float(64 bytes) type list data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(std::vector<gfloat64_t> const &data, guint16_t const id) noexcept;

    /**
     * @brief deserialize float(64 bytes) type list data with parameter id
     * @param [in,out] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gfloat64_t> &data, guint16_t const id) noexcept;

    /**
     * @brief serialize float(128 bytes) type list data
     * @param [in] data the deal data
     * @note no exception
     */
    gvoid_t serialize(std::vector<gfloat128_t> const &data) noexcept;

    /**
     * @brief deserialize float(128 bytes) type list data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gfloat128_t> &data) noexcept;

    /**
     * @brief serialize float(128 bytes) type list data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(std::vector<gfloat128_t> const &data, guint16_t const id) noexcept;

    /**
     * @brief deserialize float(128 bytes) type list data with parameter id
     * @param [in,out] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gfloat128_t> &data, guint16_t const id) noexcept;

    /**
     * @brief serialize stinrg type list data
     * @param [in] data the deal data
     * @note no exception
     */
    gvoid_t serialize(std::vector<gstring_t> const &data) noexcept;

    /**
     * @brief deserialize string type list data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gstring_t> &data) noexcept;

    /**
     * @brief serialize string type list data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(std::vector<gstring_t> const &data, guint16_t const id) noexcept;

    /**
     * @brief deserialize string type list data with parameter id
     * @param [in,out] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gstring_t> &data, guint16_t const id) noexcept;

    /**
     * @brief serialize string(wide) type list data
     * @param [in] data the deal data
     * @note no exception
     */
    gvoid_t serialize(std::vector<gu16string_t> const &data) noexcept;

    /**
     * @brief deserialize string(wide) type list data
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gu16string_t> &data) noexcept;

    /**
     * @brief serialize string(wide) type list data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t serialize(std::vector<gu16string_t> const &data, guint16_t const id) noexcept;

    /**
     * @brief deserialize string(wide) type list data with parameter id
     * @param [in,out] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    gvoid_t deserialize(std::vector<gu16string_t> &data, guint16_t const id) noexcept;


    static constexpr guint32_t gMaxSimplePidLen {0x0000FFFFU};

    /**
     * @brief the serialized template function for enum type with parameter id
     * @param [in] data the dealed data
     * @param id the parameter id
     * @note no exception
     */
    template <class _T_>
    inline gvoid_t serialize(_T_ const &data, guint16_t const id) noexcept
    {
        if (!get_cdr_state().check_encoding(CdrEncoding::PLCDR_ENCODING))
        {
            ErrorInfo::getInstance()->setLastErrorInfo(ERROR_ENCODING_ERROR, "serialize failed. encoding error");
            return;
        }
        CdrState const tmpCdrState {get_cdr_state()};

        guint32_t const startOffset {get_cdr_state().cur_offset()};
        serialize(data);
        guint32_t const endOffset {get_cdr_state().cur_offset()};
        guint32_t len;
        len = static_cast<guint32_t>(endOffset - startOffset);
        guint32_t const tmpLen {calc_param_len(len)};

        set_cdr_state(tmpCdrState);

        this->move_length(len);
        this->move_position(len);

        if (tmpLen > gMaxSimplePidLen)
        {
            guint32_t eMemHeader;
            if (id2e_mem_header(id, eMemHeader))
            {
                guint16_t const pid {PID_EXTENDED | PID_FLAG_M};
                serialize(pid);
                serialize(static_cast<guint16_t>(PID_EXTENDED_LEN));
                serialize(eMemHeader);
                serialize(tmpLen);
                serialize(data);

                this->padding(tmpLen - len);
                this->state_offset(tmpLen - len);
            }
            else
            {
                ErrorInfo::getInstance()->setLastErrorInfo(ERROR_SERIALIZE_ID2EMEMBERHEADER_FAILED,
                                                           "id2e_mem_header failed.");
            }
        }
        else
        {
            guint16_t pid;
            if (id_to_pid(false, false, id, pid))
            {
                serialize(pid);
                serialize(static_cast<guint16_t>(tmpLen));
                serialize(data);

                this->padding(tmpLen - len);
                this->state_offset((tmpLen - len));
            }
            else
            {
                ErrorInfo::getInstance()->setLastErrorInfo(ERROR_SERIALIZE_ID2PID_FAILED, "id2pid failed.");
            }
        }

        return;
    }

    /**
     * @brief the deserialized template function for general type with parameter id,which has length information
     * @param [in,out] data the deserialized data
     * @param data_len [in] the data length
     * @param [in] id the parameter id
     * @note no exception
     */
    template <typename _T_>
    inline gvoid_t deserialize(_T_ &data, guint32_t data_len, guint16_t const id) noexcept
    {
        if (!read_pid_and_size())
        {
            return;
        }

        if (get_pid() != static_cast<gint32_t>(id))
        {
            ErrorInfo::getInstance()->setLastErrorInfo(ERROR_DESERIALIZE_FAILED, "id not existed");
            return;
        }

        reset_pid_and_size();

        data.deserialize(*this, data_len);

        reset_pid_and_size();
        return;
    }

    /**
     * @brief the deserialized template function for general type with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    template <typename _T_>
    inline gvoid_t deserialize(_T_ &data, guint16_t const id) noexcept
    {
        if (!read_pid_and_size())
        {
            return;
        }

        if (get_pid() != static_cast<gint32_t>(id))
        {
            ErrorInfo::getInstance()->setLastErrorInfo(ERROR_DESERIALIZE_FAILED, "id not existed");
            return;
        }

        reset_pid_and_size();

        guint32_t const startOffset {get_cdr_state().cur_offset()};
        deserialize(data);
        guint32_t const endOffset {get_cdr_state().cur_offset()};
        guint32_t len;
        len = static_cast<guint32_t>(endOffset - startOffset);
        guint32_t const padsize {calc_param_len(len) - len};
        /* jump pad */
        this->jumping(padsize);
        this->state_offset(static_cast<guint32_t>(padsize));

        reset_pid_and_size();
        return;
    }

    /**
     * @brief the serialized template function for vector type with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    template <typename _T_>
    inline gvoid_t serialize(std::vector<_T_> const &data, guint16_t const id) noexcept
    {
        if (!get_cdr_state().check_encoding(CdrEncoding::PLCDR_ENCODING))
        {
            ErrorInfo::getInstance()->setLastErrorInfo(ERROR_ENCODING_ERROR, "serialize failed. encoding error");
            return;
        }

        CdrState const tmpCdrState {get_cdr_state()};

        guint32_t const startOffset {get_cdr_state().cur_offset()};
        serialize(data);
        guint32_t const endOffset {get_cdr_state().cur_offset()};
        guint32_t const len {static_cast<guint32_t>(endOffset - startOffset)};
        guint32_t const tmpLen {calc_param_len(len)};

        set_cdr_state(tmpCdrState);

        this->move_length(len);
        this->move_position(len);

        if (tmpLen > gMaxSimplePidLen)
        {
            guint32_t eMemHeader;
            if (id2e_mem_header(id, eMemHeader))
            {
                guint16_t const pid {PID_EXTENDED | PID_FLAG_M};
                serialize(pid);
                serialize(static_cast<guint16_t>(PID_EXTENDED_LEN));
                serialize(eMemHeader);
                serialize(tmpLen);
                serialize(data);

                this->padding(tmpLen - len);
                this->state_offset(tmpLen - len);
            }
            else
            {
                ErrorInfo::getInstance()->setLastErrorInfo(ERROR_SERIALIZE_ID2EMEMBERHEADER_FAILED,
                                                           "id2e_mem_header failed");
            }
        }
        else
        {
            guint16_t pid {0U};
            if (id_to_pid(false, false, id, pid))
            {
                serialize(pid);
                serialize(static_cast<guint16_t>(tmpLen));
                serialize(data);

                this->padding(tmpLen - len);
                this->state_offset(tmpLen - len);
            }
            else
            {
                ErrorInfo::getInstance()->setLastErrorInfo(ERROR_SERIALIZE_ID2PID_FAILED, "id2pid failed");
            }
        }
        return;
    }

    /**
     * @brief the deserialized template function for vector type with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    template <typename _T_>
    inline gvoid_t deserialize(std::vector<_T_> &data, guint16_t const id) noexcept
    {
        if (!read_pid_and_size())
        {
            return;
        }

        if (get_pid() != static_cast<gint32_t>(id))
        {
            ErrorInfo::getInstance()->setLastErrorInfo(ERROR_DESERIALIZE_FAILED, "id not existed");
            return;
        }

        guint32_t const bufSize {get_buffer_size()};

        reset_pid_and_size();

        guint32_t const start {get_cdr_state().cur_offset()};
        deserialize(data);

        guint32_t const end {get_cdr_state().cur_offset()};
        reset_pid_and_size();

        this->jumping(bufSize - (end - start));

        this->state_offset(bufSize - (end - start));
        return;
    }

    /**
     * @brief the serialized template function for array type with parameter id
     * @param [in] data the dealed data
     * @param [in] id the parameter id
     * @note no exception
     */
    template <typename _DATA_, size_t _SIZE_>
    inline gvoid_t serialize(std::array<_DATA_, _SIZE_> const &data, guint16_t const id) noexcept
    {
        guint32_t const size {static_cast<guint32_t>(_SIZE_)};
        if (!get_cdr_state().check_encoding(CdrEncoding::PLCDR_ENCODING))
        {
            ErrorInfo::getInstance()->setLastErrorInfo(ERROR_ENCODING_ERROR, "serialize failed. encoding error");
            return;
        }

        guint32_t len;
        if (IsPrimitive<_DATA_>::VALUE || IsTrivially<_DATA_>::VALUE)
        {
            len = size * sizeof(_DATA_);
        }
        else
        {
            CdrState const tmpCdrState {get_cdr_state()};
            guint32_t const startOffset {get_cdr_state().cur_offset()};
            guint32_t i;
            for (i = 0U; i < static_cast<guint32_t>(size); i++)
            {
                serialize((data[static_cast<size_t>(i)]));
            }
            guint32_t const endOffset {get_cdr_state().cur_offset()};
            len = endOffset - startOffset;
            set_cdr_state(tmpCdrState);
            this->move_length(len);
            this->move_position(len);
        }

        guint32_t const tmpLen {calc_param_len(len)};

        if (tmpLen > gMaxSimplePidLen)
        {
            guint32_t eMemHeader;
            if (id2e_mem_header(id, eMemHeader))
            {
                guint16_t const pid {PID_EXTENDED | PID_FLAG_M};
                serialize(pid);
                serialize(static_cast<guint16_t>(PID_EXTENDED_LEN));
                serialize(eMemHeader);
                serialize(tmpLen);
                 
                serialize(data);
                this->padding(tmpLen - len);
                this->state_offset(tmpLen - len);
            }
            else
            {
                ErrorInfo::getInstance()->setLastErrorInfo(ERROR_SERIALIZE_ID2EMEMBERHEADER_FAILED,
                                                           "id2e_mem_header failed.");
            }
        }
        else
        {
            guint16_t pid {0U};
            if (id_to_pid(false, false, id, pid))
            {
                serialize(pid);
                serialize(static_cast<guint16_t>(tmpLen));

                serialize(data);
                this->padding(tmpLen - len);
                this->state_offset(tmpLen - len);
            }
            else
            {
                ErrorInfo::getInstance()->setLastErrorInfo(ERROR_SERIALIZE_ID2PID_FAILED, "id2pid failed.");
            }
        }

        return;
    }

    /**
     * @brief the deserialized template function for array type with parameter id
     * @param [in,out] data the deserialized data
     * @param [in] id the parameter id
     * @note no exception
     */
    template <typename _DATA_, size_t _SIZE_>
    inline gvoid_t deserialize(std::array<_DATA_, _SIZE_> &data, guint16_t const id) noexcept
    {
        if (!read_pid_and_size())
        {
            return;
        }
        reset_pid_and_size();
        deserialize(data);
        reset_pid_and_size();
        return;
    }

    /**
     * @brief the serialized template function for map type data
     * @param [in] data the dealed data
     * @note no exception
     */
    template <typename _KEY_, typename _VALUE_>
    inline gvoid_t serialize(std::map<_KEY_, _VALUE_> const &data) noexcept
    {
        guint32_t const len {(static_cast<guint32_t>(data.size()))};
        serialize(len);

        for (auto it = data.begin(); it != data.end(); ++it)
        {
            serialize(it->first);
            serialize(it->second);
        }
        return;
    }

    /**
     * @brief the deserialized template function for map type data
     * @param [in,out] data the deserialied data
     * @note no exception
     */
    template <typename _KEY_, typename _VALUE_>
    inline gvoid_t deserialize(std::map<_KEY_, _VALUE_> &data) noexcept
    {
        guint32_t len {0U};
        deserialize(len);

        for (guint32_t i {0U}; i < len; i++)
        {
            _KEY_ key;
            _VALUE_ value;
            deserialize(key);
            deserialize(value);
            data[key] = value;
        }
        return;
    }

    /**
     * @brief the serialized template function for map type data with parameter id
     * @param [in] data the dealed data
     * @param [in] id the paramter id
     * @note no exception
     */
    template <typename _KEY_, typename _VALUE_>
    inline gvoid_t serialize(std::map<_KEY_, _VALUE_> const &data, guint16_t const id) noexcept
    {
        if (!get_cdr_state().check_encoding(CdrEncoding::PLCDR_ENCODING))
        {
            ErrorInfo::getInstance()->setLastErrorInfo(ERROR_ENCODING_ERROR, "serialize failed. encoding error");
            return;
        }

        CdrState const tmpCdrState {get_cdr_state()};

        guint32_t const startOffset {get_cdr_state().cur_offset()};
        serialize(data);
        guint32_t const endOffset {get_cdr_state().cur_offset()};
        guint32_t const len {endOffset - startOffset};
        guint32_t const tmpLen {calc_param_len(len)};

        set_cdr_state(tmpCdrState);

        this->move_length(len);
        this->move_position(len);

        if (tmpLen > gMaxSimplePidLen)
        {
            guint32_t eMemHeader;
            if (id2e_mem_header(id, eMemHeader))
            {
                guint16_t const pid {PID_EXTENDED | PID_FLAG_M};
                serialize(pid);
                serialize(static_cast<guint16_t>(PID_EXTENDED_LEN));
                serialize(eMemHeader);
                serialize(tmpLen);
                serialize(data);
                this->padding(tmpLen - len);
                this->state_offset(tmpLen - len);
            }
            else
            {
                ErrorInfo::getInstance()->setLastErrorInfo(ERROR_SERIALIZE_ID2EMEMBERHEADER_FAILED,
                                                           "id2e_mem_header failed.");
            }
        }
        else
        {
            guint16_t pid {0U};
            if (id_to_pid(false, false, id, pid))
            {
                serialize(pid);
                serialize(static_cast<guint16_t>(tmpLen));
                serialize(data);
                this->padding(tmpLen - len);
                this->state_offset(tmpLen - len);
            }
            else
            {
                ErrorInfo::getInstance()->setLastErrorInfo(ERROR_SERIALIZE_ID2PID_FAILED, "id2pid failed.");
            }
        }
        return;
    }

    /**
     * @brief the deserialized template function for map type data with parameter id
     * @param [in,out] data the deserialied data
     * @param [in] id the paramter id
     * @note no exception
     */
    template <typename _KEY_, typename _VALUE_>
    inline gvoid_t deserialize(std::map<_KEY_, _VALUE_> &data, guint16_t const id) noexcept
    {
        if (!read_pid_and_size())
        {
            ErrorInfo::getInstance()->setLastErrorInfo(ERROR_DESERIALIZE_FAILED, "readpid fail");
            return;
        }

        if (get_pid() != static_cast<gint32_t>(id))
        {
            ErrorInfo::getInstance()->setLastErrorInfo(ERROR_DESERIALIZE_FAILED, "id not existed");
            return;
        }

        guint32_t bufSize = get_buffer_size();
        reset_pid_and_size();

        guint32_t start = get_cdr_state().cur_offset();
        deserialize(data);
        guint32_t end = get_cdr_state().cur_offset();
        this->jumping(bufSize - (end - start));
        this->state_offset(bufSize - (end - start));

        reset_pid_and_size();
        return;
    }
private:

    /**
     * @brief default constructor for DdsCdr object
     * @note had declared deletion
     */
    DdsCdr(DdsCdr const &) = delete;

    /**
     * @brief default assign constructor for DdsCdr object
     * @note had declared deletion
     */
    DdsCdr &operator=(DdsCdr const &) = delete;

    /**
     * @brief default move copy construtor for DdsCdr object
     * @param [in] moved_cdr moved object
     * @note had declared deletion
     */
    DdsCdr(DdsCdr &&moved_cdr) = delete;

    /**
     * @brief default move assign constructor for DdsCdr object
     * @param [in] a_cdr moved object
     * @return DdsCdr&
     * @note had declared deletion
     */
    DdsCdr &operator=(DdsCdr &&a_cdr) = delete;

    using SerializeMethod = std::function<DdsCdr&(gvoid_t const*, DdsCdr&)>;
    using DeserializeMethod = std::function<DdsCdr&(gvoid_t*, DdsCdr&)>;

    gvoid_t serialize_trivially_data(gvoid_t const* data, gsize_t type_size, SerializeMethod serialize_method) noexcept;
    gvoid_t serialize_trivially_data_seq(gvoid_t const* data, gsize_t type_size, gsize_t length, SerializeMethod serialize_method) noexcept;
    gvoid_t deserialize_trivially_data(gvoid_t* data, gsize_t type_size, DeserializeMethod deserialize_method) noexcept;
    gvoid_t deserialize_trivially_data_seq(gvoid_t* data, gsize_t type_size, gsize_t length, DeserializeMethod serialize_method) noexcept;

public:
    template <class _Tp>
    class IsPrimitive
    {
    private:
        using UnderlyingT = typename std::decay<_Tp>::type;
    public:
        static constexpr bool VALUE {std::is_integral<UnderlyingT>::value || std::is_enum<UnderlyingT>::value ||
                                     std::is_floating_point<UnderlyingT>::value};
    };

    template <class _Tp>
    class Primitive
    {
    private:
        static constexpr gsize_t TYPE_SIZE {sizeof(_Tp)};
    public:
        using Type = typename std::conditional<
            TYPE_SIZE == 1, guint8_t,
            typename std::conditional<
                TYPE_SIZE == sizeof(guint16_t), guint16_t,
                typename std::conditional<
                    TYPE_SIZE == sizeof(guint32_t), guint32_t,
                    typename std::conditional<TYPE_SIZE == sizeof(guint64_t), guint64_t,
                                              typename std::conditional<TYPE_SIZE == sizeof(gfloat128_t), gfloat128_t,
                                                                        gvoid_t>::type>::type>::type>::type>::type;
    };

    template <class _Tp, class _Up = bool>
    class IsTrivially {
    public:
        static constexpr bool VALUE {false};
    };

    template <class _Tp>
    class IsTrivially<_Tp, decltype(_Tp::IS_ID_DEFINED, true)>
    {
    private:
        static constexpr bool IS_DATA_PADDING { !(sizeof(_Tp) == _Tp::DATA_SIZE) || _Tp::IS_DATA_PADDING };
    public:
        static constexpr bool VALUE {std::is_trivially_copy_constructible<_Tp>::value && (!_Tp::IS_ID_DEFINED) && (!IS_DATA_PADDING) && !IsPrimitive<_Tp>::VALUE};

    };

    template <class _Tp>
    static auto trivially_serializer(gvoid_t const* data, DdsCdr& cdr) -> typename std::enable_if<IsTrivially<_Tp>::VALUE, DdsCdr&>::type
    {
        return static_cast<_Tp const*>(data)->serialize(cdr);
    }

    template <class _Tp>
    static auto trivially_deserializer(gvoid_t *data, DdsCdr& cdr) -> typename std::enable_if<IsTrivially<_Tp>::VALUE, DdsCdr&>::type
    {
        return static_cast<_Tp*>(data)->deserialize(cdr);
    }

    /**
     * @brief the serialized template function for primitive type
     * @param [in] data the dealed data
     * @note no exception
     */
    template <class _Tp>
    inline auto serialize(_Tp const &data) noexcept -> typename std::enable_if<IsPrimitive<_Tp>::VALUE, gvoid_t>::type
    {
        using UnderlyingT = typename Primitive<_Tp>::Type;
        UnderlyingT const *const ptr {static_cast<UnderlyingT const *>(static_cast<gvoid_t const *>(&data))};
        serialize(*ptr);
    }

    /**
     * @brief the serialized template function for primitive type
     * @param [in] data the dealed data
     * @note no exception
     */
    template <class _Tp>
    inline auto serialize(_Tp const &data) noexcept -> typename std::enable_if<IsTrivially<_Tp>::VALUE, gvoid_t>::type
    {
        serialize_trivially_data(static_cast<gvoid_t const*>(&data), sizeof(_Tp), &trivially_serializer<_Tp>);
    }

    /**
     * @brief the serialized template function for primitive type
     * @param [in] data the dealed data
     * @note no exception
     */
    template <class _Tp>
    inline auto serialize(_Tp const &data) noexcept -> typename std::enable_if<(!IsPrimitive<_Tp>::VALUE) && (!IsTrivially<_Tp>::VALUE), gvoid_t>::type
    {
        data.serialize(*this);
    }

    /**
     * @brief the deserialized template function for common type
     * @param [in,out] data the deserialized data
     */
    template <class _Tp>
    inline auto deserialize(_Tp &data) noexcept -> typename std::enable_if<IsPrimitive<_Tp>::VALUE, gvoid_t>::type
    {
        using UnderlyingT = typename Primitive<_Tp>::Type;
        UnderlyingT *const ptr {static_cast<UnderlyingT*>(static_cast<gvoid_t *>(&data))};
        deserialize(*ptr);
    }

    /**
     * @brief the deserialized template function for common type
     * @param [in,out] data the deserialized data
     */
    template <class _Tp>
    inline auto deserialize(_Tp &data) noexcept -> typename std::enable_if<IsTrivially<_Tp>::VALUE, gvoid_t>::type
    {
        deserialize_trivially_data(static_cast<gvoid_t*>(&data), sizeof(_Tp), &trivially_deserializer<_Tp>);
    }

    /**
     * @brief the deserialized template function for common type
     * @param [in,out] data the deserialized data
     */
    template <class _Tp>
    inline auto deserialize(_Tp &data) noexcept -> typename std::enable_if<!IsPrimitive<_Tp>::VALUE && !IsTrivially<_Tp>::VALUE, gvoid_t>::type
    {
        data.deserialize(*this);
    }

    /**
     * @brief the serialized template function for vector type
     * @param [in] data the dealed data
     * @note no exception
     */
    template <class _Tp>
    inline auto serialize(std::vector<_Tp> const &data) noexcept -> typename std::enable_if<IsPrimitive<_Tp>::VALUE, gvoid_t>::type
    {
        guint32_t const size {static_cast<guint32_t>(data.size())};
        serialize(size);
        using UnderlyingT = typename Primitive<_Tp>::Type;
        UnderlyingT const *const ptr {static_cast<UnderlyingT const*>(static_cast<gvoid_t const*>(data.data()))};
        serialize(ptr, size);
    }

    /**
     * @brief the serialized template function for vector type
     * @param [in] data the dealed data
     * @note no exception
     */
    template <class _Tp>
    inline auto serialize(std::vector<_Tp> const &data) noexcept -> typename std::enable_if<IsTrivially<_Tp>::VALUE, gvoid_t>::type
    {
        guint32_t const size {static_cast<guint32_t>(data.size())};
        serialize(size);
        gvoid_t const* ptr {static_cast<gvoid_t const*>(data.data())};
        serialize_trivially_data_seq(ptr, sizeof(_Tp), data.size(), &trivially_serializer<_Tp>);
    }

    /**
     * @brief the serialized template function for vector type
     * @param [in] data the dealed data
     * @note no exception
     */
    template <class _Tp>
    inline auto serialize(std::vector<_Tp> const &data) noexcept -> typename std::enable_if<!IsPrimitive<_Tp>::VALUE && !IsTrivially<_Tp>::VALUE, gvoid_t>::type
    {
        guint32_t const size {static_cast<guint32_t>(data.size())};
        serialize(size);
        for (guint32_t idx {0U}; idx < size; idx++)
        {
            this->serialize(data.at(static_cast<size_t>(idx)));
        }
    }

    /**
     * @brief the deserialized template function for vector type
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    template <class _Tp>
    inline auto deserialize(std::vector<_Tp> &data) noexcept -> typename std::enable_if<IsPrimitive<_Tp>::VALUE, gvoid_t>::type
    {
        guint32_t size {0U};
        deserialize(size);
        data.resize(static_cast<gsize_t>(size));
        using UnderlyingT = typename Primitive<_Tp>::Type;
        UnderlyingT *const ptr {static_cast<UnderlyingT *>(static_cast<gvoid_t *>(data.data()))};
        deserialize(ptr, size);
    }

    /**
     * @brief the deserialized template function for vector type
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    template <class _Tp>
    inline auto deserialize(std::vector<_Tp> &data) noexcept -> typename std::enable_if<IsTrivially<_Tp>::VALUE, gvoid_t>::type
    {
        guint32_t size {0U};
        deserialize(size);
        data.resize(static_cast<gsize_t>(size));
        gvoid_t* ptr {static_cast<gvoid_t*>(data.data())};
        deserialize_trivially_data_seq(ptr, sizeof(_Tp), data.size(), &trivially_deserializer<_Tp>);
    }

    /**
     * @brief the deserialized template function for vector type
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    template <class _Tp>
    inline auto deserialize(std::vector<_Tp> &data) noexcept -> typename std::enable_if<!IsPrimitive<_Tp>::VALUE && !IsTrivially<_Tp>::VALUE, gvoid_t>::type
    {
        guint32_t size {0U};
        deserialize(size);
        data.resize(static_cast<gsize_t>(size));
        for (guint32_t idx {0U}; idx < size; idx++)
        {
            this->deserialize(data.at(static_cast<size_t>(idx)));
        }
    }

    /**
     * @brief the serialized template function for array type
     * @param [in] data the dealed data
     * @note no exception
     */
    template <class _Tp, gsize_t _Size>
    inline auto serialize(std::array<_Tp, _Size> const &data) noexcept -> typename std::enable_if<IsPrimitive<_Tp>::VALUE, gvoid_t>::type
    {
        using UnderlyingT = typename Primitive<_Tp>::Type;
        UnderlyingT const *const ptr {static_cast<UnderlyingT const*>(static_cast<gvoid_t const*>(data.data()))};
        serialize(ptr, _Size);
    }

    /**
     * @brief the serialized template function for array type
     * @param [in] data the dealed data
     * @note no exception
     */
    template <class _Tp, gsize_t _Size>
    inline auto serialize(std::array<_Tp, _Size> const &data) noexcept -> typename std::enable_if<IsTrivially<_Tp>::VALUE, gvoid_t>::type
    {
        gvoid_t const* const ptr {static_cast<gvoid_t const*>(data.data())};
        serialize_trivially_data_seq(ptr, sizeof(_Tp), _Size, &trivially_serializer<_Tp>);
    }

    /**
     * @brief the serialized template function for array type
     * @param [in] data the dealed data
     * @note no exception
     */
    template <class _Tp, gsize_t _Size>
    inline auto serialize(std::array<_Tp, _Size> const &data) noexcept -> typename std::enable_if<!IsPrimitive<_Tp>::VALUE && !IsTrivially<_Tp>::VALUE, gvoid_t>::type
    {
        for (guint32_t idx {0U}; idx < _Size; idx++)
        {
            this->serialize(data.at(idx));
        }
    }

    /**
     * @brief the deserialized template function for array type
     * @param [in] data the dealed data
     * @note no exception
     */
    template <class _Tp, gsize_t _Size>
    inline auto deserialize(std::array<_Tp, _Size> &data) noexcept -> typename std::enable_if<IsPrimitive<_Tp>::VALUE, gvoid_t>::type
    {
        using UnderlyingT = typename Primitive<_Tp>::Type;
        UnderlyingT* const ptr {static_cast<UnderlyingT *>(static_cast<gvoid_t *>(data.data()))};
        deserialize(ptr, _Size);
    }


    /**
     * @brief the deserialized template function for array type
     * @param [in] data the dealed data
     * @note no exception
     */
    template <class _Tp, gsize_t _Size>
    inline auto deserialize(std::array<_Tp, _Size> &data) noexcept -> typename std::enable_if<IsTrivially<_Tp>::VALUE, gvoid_t>::type
    {
        gvoid_t* ptr {static_cast<gvoid_t*>(data.data())};
        deserialize_trivially_data_seq(ptr, sizeof(_Tp), _Size, &trivially_deserializer<_Tp>);
    }


    /**
     * @brief the deserialized template function for array type
     * @param [in] data the dealed data
     * @note no exception
     */
    template <class _Tp, gsize_t _Size>
    inline auto deserialize(std::array<_Tp, _Size> &data) noexcept -> typename std::enable_if<!IsPrimitive<_Tp>::VALUE && !IsTrivially<_Tp>::VALUE, gvoid_t>::type
    {
        for (guint32_t idx {0U}; idx < _Size; idx++)
        {
            this->deserialize(data.at(idx));
        }
    }

    /**
     * @brief set the cdr object state
     * @param [in] valid_flag the working state
     * @note no exception
     */
    inline gvoid_t set_state(gbool_t const valid_flag = true) noexcept
    {
        m_state = valid_flag;
    }

    /**
     * @brief check and convert parameter id
     * @param [in] id the parameter id
     * @param [in,out] mem_header the valid header
     * @return gbool_t
     * @retval true if valid id convert succeed
     * @retval false if convert fail
     * @note no exception
     */
    gbool_t id2e_mem_header(guint16_t const id, guint32_t &mem_header) const noexcept;

    /**
     * @brief calculate the valid length
     * @param [in] len the processing length value
     * @return guint32_t
     * @retval valid length after proceed
     * @note no exception
     */
    guint32_t calc_param_len(guint32_t const len) const noexcept;

    /**
     * @brief get the cdr inner state
     * @return CdrState const&
     * @retval return current inner current state
     * @note no exception
     */
    CdrState const &get_cdr_state() const noexcept;

    /**
     * @brief set the cdr inner state
     * @param [in] new_state the kept cdr state
     * @note no exception
     */
    gvoid_t set_cdr_state(CdrState const &new_state) const noexcept;

    /**
     * @brief read the parameter id and length information
     * @return gbool_t
     * @retval true if read valid id and length from specific buffer succeed
     * @retval false if read valid id and length from specific buffer failed
     * @note no exception
     */
    gbool_t read_pid_and_size() const noexcept;

    /**
     * @brief reset the paramter id and length
     * @note no exception
     */
    gvoid_t reset_pid_and_size() const noexcept;

    /**
     * @brief combine parameter id
     * @param [in] flag_ignore ignore flag
     * @param [in] flag_must must flag
     * @param [in] id the proceed id
     * @param [in,out] pid the valid parameter id
     * @return gbool_t
     * @retval true parameter id combined succeed
     * @retval false parameter id combined failed
     * @note no exception
     */
    gbool_t id_to_pid(gbool_t const flag_ignore, gbool_t const flag_must, guint16_t const id,
                      guint16_t &pid) const noexcept;

    /**
     * @brief get the pid
     * @return gint32_t
     * @retval return valid parameter id
     * @note no exception
     */
    gint32_t get_pid() const noexcept;

    /**
     * @brief get the buffer's offset position
     * @param [in] buffer the buffer address
     * @param [in] size the element size
     * @param [in] count the offset count
     * @return gvoid_t const*
     * @retval return real postion
     * @note no exception
     */
    gvoid_t const *buffer_offset(gvoid_t const *const buffer, gsize_t const size, guint32_t const count) noexcept;

    // the cdr implementation
    std::shared_ptr<DdsCdrImpl> m_cdr {nullptr};

    // the cdr state flag
    gbool_t m_state {true};
};

} /*rtps*/
} /*gstone*/

/* notes: template */
using DdsCdr = gstone::rtps::DdsCdr;

__GS_DDS4CPP_END_DECLS


#endif /*GSTONE_RTPS_DDSCDR_API_H*/
