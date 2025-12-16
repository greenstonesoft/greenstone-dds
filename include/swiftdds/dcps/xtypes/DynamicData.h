/**************************************************************
* @file DynamicData.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_DYNAMIC_DATA_API_H_
#define GSTONE_DYNAMIC_DATA_API_H_ 1

#include <map>
#include <vector>
#include <memory>
#include <iostream>

#include "swiftdds/dcps/xtypes/TypeDefs.h"
#include "swiftdds/dcps/xtypes/TypeKind.h"
#include "swiftdds/rtps/DdsCdr.h"
#include "swiftdds/rtps/SerializedPayload.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace xtypes
{
class DynamicType;
class MemberDescriptor;
class DynamicTypeMember;
class DynamicType;
class DynamicData;
using DynamicType_Ptr = std::shared_ptr<DynamicType>;
using DynamicData_Ptr = std::shared_ptr<DynamicData>;
/**
 * @brief Each object of the DynamicData class represents a corresponding 
 * object of the type represented by the DynamicData object's DynamicType.
 * @details While a DynamicType describes a type, 
 * DynamicData represents a data instance of a DynamicType. 
 * It provides functions to access and modify the data values in the instance.
 * DynamicData objects have reference semantics; however, 
 * there is an equals operation to allow them to be deeply compared.
 */
class GS_DDS4CPP_API DynamicData
{
public:
    /**
     * @brief Default constructor.
     */
    DynamicData() noexcept = default;

    /**
     * @brief Default destructor.
     */
    virtual ~DynamicData() = default;
public:
    /**
     * @brief This convenience operation indicates the kind of 
     * this data (e.g., integer, structure, etc.).
     * Its result shall be the same as the kind indicated by 
     * the type's descriptor property.
     * @return TypeKind Kind of this Data.
     */
    virtual TypeKind const get_kind() const noexcept = 0;

    /**
     * @brief This convenience operation indicates the type of 
     * this data (e.g., integer, structure, etc.).
     * Its result shall be the same as the type creating this data.
     * @return Dynamictype of this data.
     */
    virtual DynamicType_Ptr const get_type() const noexcept = 0;

    /**
     * @brief The "item count" of the data depends on the type of the object.
     * Different type has different calculation methods.
     * @return Total item count in a dynamic data instance.
     */
    virtual uint32_t const get_item_count() const noexcept = 0;

    /**
     * @brief Two data samples are considered to be equal if and 
     * only if all of the following conditions hold:
     * Their respective type definitions are equal.
     * All contained values are equal and occur in the same order.
     * @param [in] other Data will be compared with this one.
     * @return ture if two data is same, otherwise return false.
     */
    virtual bool equals(DynamicData_Ptr const other) const noexcept = 0;

    /**
     * @brief The "loan" operations loan to the application a DynamicData object 
     * representing a value within this sample. These operations allow applications 
     * to visit values without allocating additional DynamicData objects or copying values.
     * This loan shall be returned by the return_loaned_value operation.
     * @param [in] id Value id to be loaned.
     * @return The smart pointer of DynamicData with parameter id or nil value 
     * if the indicated value does not exist/an application violates this constraint
     */
    virtual DynamicData_Ptr loan_value(MemberId const id) noexcept = 0;

    /**
     * @brief A given DynamicData object may support only a single outstanding 
     * loan at a time. That is, after calling a "loan" operation, an application 
     * must subsequently call return_loaned_value before calling a loan operation again.
     * @param [in] value The loaned value to be returned.
     * @return False if the provided sample object does not represent an outstanding 
     * loan from the sample on which the operation is invoked.
     */
    virtual bool const return_loaned_value(DynamicData_Ptr const data) noexcept = 0;

    /**
     * @brief Get DynamicData of base type if any.
     * @return Const reference of base type Data. 
     */
    virtual DynamicData_Ptr const get_base_data() const noexcept;
public:
    /**
     * @brief Retrieves the boolean value with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_bool_value(
        gbool_t &value,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new value for the boolean data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_bool_value(
        gbool_t const value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new boolena value to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_bool_value(
        gbool_t const value) noexcept;
    
    /**
     * @brief Retrieves the byte value with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_byte_value(
        octet &value,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new value for the boolean data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_byte_value(
        octet const value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new byte value to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_byte_value(
        octet const value) noexcept;

    /**
     * @brief Retrieves the 16-bit integer value with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_int16_value(
        int16_t &value,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new value for the 16-bit integer data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_int16_value(
        int16_t const value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new 16-bit integer value to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_int16_value(
        int16_t const value) noexcept;

    /**
     * @brief Retrieves the 32-bit integer value with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_int32_value(
        int32_t &value,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new value for the 32-bit integer data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_int32_value(
        int32_t const value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new 32-bit integer value to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_int32_value(
        int32_t const value) noexcept;

    /**
     * @brief Retrieves the 64-bit integer value with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_int64_value(
        int64_t &value,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new value for the 64-bit integer data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_int64_value(
        int64_t const value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new 64-bit integer value to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_int64_value(
        int64_t const value) noexcept;

    /**
     * @brief Retrieves the 64-bit unsigned integer value with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_uint16_value(
        uint16_t &value,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new value for the 16-bit unsigned integer data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_uint16_value(
        uint16_t const value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new 16-bit unsigned integer value to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_uint16_value(
        uint16_t const value) noexcept;

    /**
     * @brief Retrieves the 32-bit unsigned integer value with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_uint32_value(
        uint32_t &value,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new value for the 32-bit unsigned integer data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_uint32_value(
        uint32_t const value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new 32-bit unsigned integer value to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_uint32_value(
        uint32_t const value) noexcept;

    /**
     * @brief Retrieves the 64-bit unsigned integer value with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_uint64_value(
        uint64_t &value,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new value for the 64-bit unsigned integer data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_uint64_value(
        uint64_t const value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new 64-bit unsigned integer value to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_uint64_value(
        uint64_t const value) noexcept;

    /**
     * @brief Retrieves the 32-bit floating value with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_float32_value(
        float &value,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new value for the 32-bit floating  data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_float32_value(
        float const value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new 32-bit floating value to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_float32_value(
        float const value) noexcept;

    /**
     * @brief Retrieves the 64-bit floating value with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_float64_value(
        double &value,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new value for the 64-bit floating  data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_float64_value(
        double const value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new 64-bit floating value to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_float64_value(
        double const value) noexcept;

    /**
     * @brief Retrieves the 128-bit floating value with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_float128_value(
        gfloat128_t &value,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new value for the 128-bit floating  data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_float128_value(
        gfloat128_t const value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new 128-bit floating value to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_float128_value(
        gfloat128_t const value) noexcept;

    /**
     * @brief Retrieves the 8-bit integer value with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_int8_value(
        gint8_t &value,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new value for the 8-bit integer data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_int8_value(
        gint8_t const value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new 8-bit integer value to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_int8_value(
        gint8_t const value) noexcept;

    /**
     * @brief Retrieves the 8-bit unsigned integer value with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_uint8_value(
        guint8_t &value,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new value for the 8-bit unsigned integer data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_uint8_value(
        guint8_t const value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new 8-bit unsigned integer value to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_uint8_value(
        guint8_t const value) noexcept;

    /**
     * @brief Retrieves the 8-bit character value with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_char8_value(
        gchar_t &value,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new value for the 8-bit character data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_char8_value(
        gchar_t const value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new 8-bit character value to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_char8_value(
        gchar_t const value) noexcept;

    /**
     * @brief Retrieves the 16-bit character value with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_char16_value(
        gchar16_t &value,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new value for the 16-bit character data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_char16_value(
        gchar16_t const value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new 16-bit character value to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_char16_value(
        gchar16_t const value) noexcept;

    /**
     * @brief Retrieves the string value with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_string_value(
        std::string &value,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new value for the string data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_string_value(
        std::string const &value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new string value to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_string_value(
        std::string const &value) noexcept;

    /**
     * @brief Retrieves the wide-string value with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_wstring_value(
        std::u16string &value,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new value for the wide-string data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_wstring_value(
        std::u16string const &value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new wide-string value to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_wstring_value(
        std::u16string const &value) noexcept;

    /**
     * @brief Retrieves the numeric value of a enumeration data with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_enumeration_value(
        uint32_t &value,
        MemberId const id) const noexcept = 0;
    
    /**
     * @brief Sets a new numeric value for the enumeration data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_enumeration_value(
        uint32_t const value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new numeric value of the enumeration data 
     * to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_enumeration_value(
        uint32_t const value) noexcept;

    /**
     * @brief Retrieves the literal value of a enumeration data with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_enumeration_value(
        std::string &value,
        MemberId const id) const noexcept = 0;
    
    /**
     * @brief Sets a new literal value for the enumeration data with an id.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_enumeration_value(
        std::string const &value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new literal value of the enumeration data 
     * to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_enumeration_value(
        std::string const &value) noexcept;

    /**
     * @brief Retrieves the boolean value of a bitmask data 
     * with an id at the given position.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] position Bit position of the target value.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_bitmask_value(
        bool &value,
        uint32_t const position,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new boolean value for the bitmask data 
     * with an id at given positon.
     * @param [in] value New value for the data.
     * @param [in] position Bit position of the target value.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_bitmask_value(
        bool const value,
        uint32_t const position,
        MemberId const id) noexcept = 0;
    
    /**
     * @brief Inserts a new bitmask value with true at 
     * given postion to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_bitmask_value(
        bool const value,
        uint32_t const position) noexcept;

    /**
     * @brief Retrieves the literal value of a bitmask data 
     * with an id at the given position.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] position Bit position of the target value.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_bitmask_value(
        std::string &value,
        uint32_t const position,
        MemberId const id) const noexcept = 0;

    /**
     * @brief Sets a new literal value for the bitmask data 
     * with an id at given positon.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_bitmask_value(
        std::string const &value,
        MemberId const id) noexcept = 0;

    /**
     * @brief Inserts a new bitmask value with true at 
     * given postion to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_bitmask_value(
        std::string const &value) noexcept;
    
    /**
     * @brief Retrieves the numeric value of a bitmask data
     * for all bits with an id.
     * @param [in,out] value Reference to value where the data is returned.
     * @param [in] id Member id of the target value.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t get_bitmask_value(
        uint64_t &value,
        MemberId const id) const noexcept = 0;
    
    /**
     * @brief Sets a new numeric value for the bitmask data 
     * with an id at all bits positon.
     * @param [in] value New value for the data.
     * @param [in] id Member id of the the data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t set_bitmask_value(
        uint64_t const value,
        MemberId const id) noexcept = 0;
    
    /**
     * @brief Inserts a new bitmask value in numeric format 
     * to a sequence or map data.
     * @param [in] value New value to add for this data.
     * @return Error code of this operation.
     */
    virtual DDS::ReturnCode_t insert_bitmask_value(
        uint64_t const value) noexcept;
public:
    /**
     * @brief This convenience operation will add a complex
     * data to an existing sequence or map data and then 
     * return the new data.
     * @return Reference to the new complex data.
     */
    virtual DynamicData_Ptr insert_complex_value() noexcept;

    /**
     * @brief This operations is available just with union data and 
     * can change the applicable member.
     * @param [in] value New discriminator value to set.
     * @return ture if new discriminator value is valid and 
     * update specified member id, otherwise return false.
     */
    virtual bool const set_discriminator_value(int64_t const value) noexcept;

    /**
     * @brief This convenience operation will return the newest
     * member id of sequence/map/union data.
     * @return Applicable member id of current data.
     */
    virtual MemberId const get_current_id() const noexcept;

    /**
     * @brief You can get the member id with give key value and visit
     * value data further, usable when map data.
     * @param [in] value Key to an existing map.
     * @return If value is in map, it's member id will be returned.
     */
    virtual MemberId const find(void *value) const noexcept;

    /**
     * @brief This function serializes a data's key.
     * @param [in,out] buf Address of key's content.
     * @param [in,out] len Address of key's length. 
     */
    virtual gvoid_t serialize_key(
        gchar_t **const buf,
        uint32_t *const length) noexcept;

    /**
     * @brief This function serializes an object using CDR serialization.
     * @param [in] cdr CDR serialization object.
     */
    virtual gvoid_t serialize(DdsCdr &cdr) const noexcept = 0;

    /**
     * @brief This function deserializes an object using CDR serialization.
     * @param [in,out] cdr CDR serialization object.
     */
    virtual gvoid_t deserialize(DdsCdr &cdr) noexcept = 0;

    /**
     * @brief This function gets the data's deserialization flag.
     * @return True if this data need deserializeed, otherwise return False.
     */
    virtual gbool_t const get_deserialize_flag() const noexcept;

    /**
     * @brief This function sets the data's deserialization flag.
     * @param [in] flag New deserialization flag for this data.
     */
    virtual gvoid_t set_deserialize_flag(bool const flag) noexcept;

    /**
     * @brief This function gets the data's raw buffer in a payload format.
     * @return Payload Pointer if this data has raw data, otherwise return nil.
     */
    virtual std::shared_ptr<gstone::rtps::SerializedPayload_t> const get_raw_data() const noexcept;

    /**
     * @brief This function sets the data's raw buffer in a payload format.
     * @param [in] pay_load New raw data for this data.
     */
    virtual gvoid_t set_raw_date(std::shared_ptr<gstone::rtps::SerializedPayload_t> const &pay_load) noexcept;

public:
    /**
     * @brief Copy constructor.
     * Deleted constructor, not used.
     * @param [in] x Reference to the object DynamicData that will be copied.
     */
    DynamicData(DynamicData const &x) = delete;

    /**
     * @brief Move constructor.
     * Deleted constructor, not used.
     * @param [in] x Reference to the object DynamicData that will be copied.
     */
    DynamicData(DynamicData &&x) = delete;

    /**
     * @brief Copy assignment.
     * Deleted assignment operator, not used.
     * @param [in] x Reference to the object DynamicData that will be copied.
     * @return DynamicData &Reference to the object DynamicData that to be assigned
     */
    DynamicData &operator=(DynamicData const &x) = delete;

    /**
     * @brief Move assignment.
     * Deleted assignment operator, not used.
     * @param [in] x Reference to the object DynamicData that will be copied.
     * @return DynamicData &Reference to the object DynamicData that to be assigned
     */
    DynamicData &operator=(DynamicData &&x) = delete;
};
    
} // namespace xtypes
} // namespace dds

__GS_DDS4CPP_END_DECLS

#endif // GSTONE_DYNAMIC_DATA_API_H_

