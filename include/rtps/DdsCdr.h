/**************************************************************
 * @file DdsCdr.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
 * All rights reserved
 **************************************************************/

#ifndef GSTONE_DDSCDR_API_H
#define GSTONE_DDSCDR_API_H 1

#include <vector>
#include <map>
#include <memory>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

#include "rtps/CdrState.h"
#include "rtps/CdrBuffer.h"
#include "rtps/SerializedPayloadHeader.h"
#include "dcps/DeclExport.h"
#include "dcps/PITypes.h"

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

    /**
     * @brief the serialized template function for enum type
     * @param [in] data the dealed data
     * @note no exception
     */
    template <class _T_>
    inline gvoid_t serialize(_T_ const &data) noexcept(noexcept(std::is_enum<_T_>()))
    {
        serialize_aux(data, std::is_enum<_T_>());
        return;
    }

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
     * @brief the deserialized template function for common type
     * @param [in,out] data the deserialized data
     */
    template <typename _T_>
    inline gvoid_t deserialize(_T_ &data) noexcept
    {
        deserialize_aux(data, std::is_enum<_T_>());
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
     * @brief the serialized template function for vector type
     * @param [in] data the dealed data
     * @note no exception
     */
    template <typename _T_>
    inline gvoid_t serialize(std::vector<_T_> const &data) noexcept
    {
        guint32_t const tmp_count {static_cast<guint32_t>(data.size())};
        serialize(tmp_count);

        if (IsPrimitive<_T_>::VALUE)
        {
            using UnderlyingT = typename Primitive<_T_>::Type;
            UnderlyingT const *const ptr {static_cast<UnderlyingT const *>(static_cast<gvoid_t const *>(data.data()))};
            serialize(ptr, tmp_count);
        }
        else
        {
            for (gsize_t idx {0U}; idx < static_cast<gsize_t>(tmp_count); idx++)
            {
                this->serialize(data.at(idx));
            }
        }
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
     * @brief the deserialized template function for vector type
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    template <typename _T_>
    inline gvoid_t deserialize(std::vector<_T_> &data) noexcept(
        noexcept(data.resize(data.size())) &&noexcept(data.size()))
    {
        guint32_t size {0U};
        deserialize(size);

        data.resize(static_cast<gsize_t>(size));

        gsize_t const used_size {data.size()};

        if (IsPrimitive<_T_>::VALUE)
        {
            using UnderlyingT = typename Primitive<_T_>::Type;
            UnderlyingT *const ptr {static_cast<UnderlyingT *>(static_cast<gvoid_t *>(data.data()))};
            deserialize(ptr, used_size);
        }
        else
        {
            for (gsize_t idx {0U}; idx < used_size; idx++)
            {
                this->deserialize(data.at(idx));
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
     * @brief the serialized template function for array type
     * @param [in] data the dealed data
     * @note no exception
     */
    template <typename _DATA_, size_t _SIZE_>
    inline gvoid_t serialize(std::array<_DATA_, _SIZE_> const &data) noexcept
    {
        static_assert(_SIZE_ <= static_cast<size_t>(std::numeric_limits<guint32_t>::max()), "");
        if (IsPrimitive<_DATA_>::VALUE)
        {
            using UnderlyingT = typename Primitive<_DATA_>::Type;
            UnderlyingT const *const ptr {static_cast<UnderlyingT const *>(static_cast<gvoid_t const *>(data.data()))};
            serialize(ptr, static_cast<guint32_t>(_SIZE_));
        }
        else
        {
            for (guint32_t i {0U}; i < _SIZE_; i++)
            {
                this->serialize(data.at(static_cast<gsize_t>(i)));
            }
        }
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
        serialize(data.data(), static_cast<guint32_t>(data.size()), id);
        return;
    }

    /**
     * @brief the deserialized template function for array type
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    template <typename _DATA_, size_t _SIZE_>
    inline gvoid_t deserialize(std::array<_DATA_, _SIZE_> &data) noexcept
    {
        static_assert(_SIZE_ <= static_cast<size_t>(std::numeric_limits<guint32_t>::max()), "");
        if (IsPrimitive<_DATA_>::VALUE)
        {
            using UnderlyingT = typename Primitive<_DATA_>::Type;
            UnderlyingT *const ptr {static_cast<UnderlyingT *>(static_cast<gvoid_t *>(data.data()))};
            deserialize(ptr, static_cast<guint32_t>(_SIZE_));
        }
        else
        {
            for (guint32_t i {0U}; i < _SIZE_; i++)
            {
                this->deserialize(data.at(static_cast<gsize_t>(i)));
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
        guint32_t const len {static_cast<guint32_t>(data.size())};
        deserialize(data.data(), len, id);
        return;
    }

    /**
     * @brief the serialized template function for pointer type data
     * @param [in] data the dealed data
     * @param [in] size the data length
     * @note no exception
     */
    template <typename _DATA_, typename _SIZE_>
    inline gvoid_t serialize(_DATA_ const *const data, _SIZE_ const size) noexcept
    {
        serialize(data, static_cast<guint32_t>(size));
        return;
    }

    /**
     * @brief the serialized template function for pointer type data with parameter id
     * @param [in] data the dealed data
     * @param size the data length
     * @param [in] id the paramter id
     * @note no exception
     */
    template <typename _DATA_, typename _SIZE_>
    inline gvoid_t serialize(_DATA_ const *const data, _SIZE_ const size, guint16_t const id) noexcept
    {
        if (!get_cdr_state().check_encoding(CdrEncoding::PLCDR_ENCODING))
        {
            ErrorInfo::getInstance()->setLastErrorInfo(ERROR_ENCODING_ERROR, "serialize failed. encoding error");
            return;
        }

        guint32_t len;
        if (IsPrimitive<_DATA_>::VALUE)
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
                serialize((data[i]));
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

                if (IsPrimitive<_DATA_>::VALUE)
                {
                    using UnderlyingT = typename Primitive<_DATA_>::Type;
                    UnderlyingT const *const ptr {static_cast<UnderlyingT const *>(static_cast<gvoid_t const *>(data))};
                    serialize(ptr, static_cast<guint32_t>(size));
                }
                else
                {
                    for (guint32_t j {0U}; j < static_cast<guint32_t>(size); j++)
                    {
                        serialize(*(static_cast<_DATA_ const *>(buffer_offset((data), sizeof(_DATA_), j))));
                    }
                }
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

                if (IsPrimitive<_DATA_>::VALUE)
                {
                    using UnderlyingT = typename Primitive<_DATA_>::Type;
                    UnderlyingT const *const ptr {static_cast<UnderlyingT const *>(static_cast<gvoid_t const *>(data))};
                    serialize(ptr, static_cast<guint32_t>(size));
                }
                else
                {
                    guint32_t k;
                    for (k = 0U; k < static_cast<guint32_t>(size); k++)
                    {
                        serialize(*(static_cast<_DATA_ const *>(buffer_offset(data, sizeof(_DATA_), k))));
                    }
                }
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
     * @brief the deserialized template function for pointer type data
     * @param [in,out] data the deserialied data
     * @param size the data length
     * @note no exception
     */
    template <typename _DATA_, typename _SIZE_>
    inline gvoid_t deserialize(_DATA_ *const data, _SIZE_ const size) noexcept
    {
        guint32_t len;
        len = static_cast<guint32_t>(size);
        deserialize(data, len);
        return;
    }

    /**
     * @brief the deserialized template function for pointer type data with parameter id
     * @param [in,out] data the deserialied data
     * @param [in] size the data length
     * @param [in] id the paramter id
     * @note no exception
     */
    template <typename _DATA_, typename _SIZE_>
    inline gvoid_t deserialize(_DATA_ *data, _SIZE_ size, guint16_t const id) noexcept
    {
        if (!read_pid_and_size())
        {
            return;
        }

        reset_pid_and_size();
        gint32_t i;
        for (i = 0; i < static_cast<gint32_t>(size); i++)
        {
            (data + i)->deserialize(*this);
        }
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
     * @brief the serialized template function for enum type,which is auxiliary function
     * @param [in] data the dealed data
     * @note no exception
     */
    template <typename _T>
    inline gvoid_t serialize_aux(_T const &data, std::true_type) noexcept
    {
        guint32_t const temp {static_cast<guint32_t>(data)};
        serialize(temp);
        return;
    }

    /**
     * @brief the serialized template function for common type,which is auxiliary function
     * @param [in] data the dealed data
     * @note no exception
     */
    template <typename _T>
    inline gvoid_t serialize_aux(_T const &data, std::false_type) noexcept
    {
        this->set_state();
        data.serialize(*this);
        return;
    }

    /**
     * @brief the deserialized template function for enum type,which is auxiliary function
     * @param [in,out] data the dealed data
     * @note no exception
     */
    template <typename _T>
    inline gvoid_t deserialize_aux(_T &data, std::true_type) noexcept
    {
        guint32_t temp {0U};
        deserialize(temp);
        data = static_cast<_T>(temp);
        return;
    }

    /**
     * @brief the deserialized template function for common type,which is auxiliary function
     * @param [in,out] data the deserialized data
     * @note no exception
     */
    template <typename _T>
    inline gvoid_t deserialize_aux(_T &data, std::false_type) noexcept
    {
        this->set_state();
        data.deserialize(*this);
        return;
    }

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
