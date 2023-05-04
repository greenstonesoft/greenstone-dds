/**************************************************************
* @file DynamicData.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_DYNAMIC_DATA_API_H_
#define GSTONE_DYNAMIC_DATA_API_H_ 1

#include <map>
#include <vector>
#include <memory>
#include <iostream>

#include "TypeDefs.h"
#include "TypeKind.h"
#include "rtps/DdsCdr.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace xtypes
{
    class DynamicType;
    class MemberDescriptor;
    class DynamicTypeMember;
    class DynamicType;
    using DynamicType_ptr = std::shared_ptr<DynamicType>;
    /**
     * @brief Each object of the DynamicData class represents a corresponding object of the type represented by the DynamicData object's DynamicType.
     * @details While a DynamicType describes a type, DynamicData represents a data instance of a DynamicType. 
     * It provides functions to access and modify the data values in the instance.
     * DynamicData objects have reference semantics; however, there is an equals operation to allow them to be deeply compared.
     */
    class GS_DDS4CPP_API DynamicData final
    {
    public:
        /**
         * @brief Default constructor.
         */
        DynamicData() noexcept;
        
        /**
         * @brief Construct a new DynamicData object with a DynamicData pointer.
         * @param [in] pData Pointer to an existed DanamicData.
         */
        DynamicData(DynamicData const *const pData);
        
        /**
         * @brief Construct a new DynamicData object with a DynamicData smart pointer.
         * @param [in] a_type Smart pointer to an existed DanamicData.
         */
        DynamicData(DynamicType_ptr a_type);
        
        /**
         * @brief Default destructor.
         */
        ~DynamicData() noexcept;
        
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
        
        /**
         * @brief Get member id of the specified member name.
         * @param [in] name Specified member name.
         * @return MemberId If member name is correct, return the member's id; otherwise return MEMBER_ID_INVALID.
         */
        MemberId get_member_id_by_name(gstring_t const &name) const noexcept;
        
        /**
         * @brief Get member id of the specified member index.
         * @param [in] _index Specified member index.
         * @return MemberId If member id is valid, return the member's id; otherwise return MEMBER_ID_INVALID.
         */
        MemberId get_member_id_at_index(guint32_t const _index) const noexcept;
        
        /**
         * @brief The "item count" of the data depends on the type of the object.
         * Different type has different calculation methods.
         * @return guint32_t Total item count in a type object.
         */
        guint32_t get_item_count() const noexcept;
        
        /**
         * @brief If two dynamic data samples are equal or not.
         * Criteria for judgment is refered to the official doc. 
         * @param [in] other The Dynamic Data to be compared.
         * @return gbool_t Result of the data sampels comparison
         */
        gbool_t equals(DynamicData const *const other) const;
        
        /**
         * @brief The clear_all_members takes the clear_values action for each value in turn.
         * The meaning of "clearing" a member depends on the type of data represented by this sample.
         * @return DDS::ReturnCode_t  Result of all clear_values action.
         */
        DDS::ReturnCode_t clear_all_values();
        
        /**
         * @brief The clear_nonkey_value operation has exactly the same effect as clear_all_values with one exception:
         * the values of key fields of aggregated types retain their values.
         * @return DDS::ReturnCode_t Result of all clear_values action.
         */
        DDS::ReturnCode_t clear_nonkey_values() const noexcept;
        
        /**
         * @brief Clear specified member based on member id and member type.
         * Criteria for clearing is refer to the official doc.
         * @param [in] id ID of the member to be cleared.
         * @return DDS::ReturnCode_t If the id is valid, do the clear job return DDS::ReturnCode_t::RETCODE_OK.
         */
        DDS::ReturnCode_t clear_value(MemberId const id);
        
        /**
         * @brief The "loan" operations loan to the application a DynamicData object representing a value within this sample.
         * These operations allow applications to visit values without allocating additional DynamicData objects or copying values.
         * This loan shall be returned by the return_loaned_value operation.
         * @param [in] id  Value id to be loaned.
         * @return std::shared_ptr<DynamicData> The smart pointer of DynamicData with parameter id or nil value if the indicated value does not
         * exist/an application violates this constraint
         */
        std::shared_ptr<DynamicData> loan_value(MemberId const id);
        
        /**
         * @brief A given DynamicData object may support only a single outstanding loan at a time.
         * That is, after calling a "loan" operation,  an application must subsequently call 
         * return_loaned_value before calling a loan operation again.
         * @param [in] value The loaned value to be returned.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET if the provided sample object does not 
         * represent an outstanding loan from the sample on which the operation is invoked.
         */
        DDS::ReturnCode_t return_loaned_value(DynamicData const *const value);
        
        /**
         * @brief A given DynamicData object may support only a single outstanding loan at a time.
         * That is, after calling a "loan" operation,  an application must subsequently call 
         * return_loaned_value before calling a loan operation again.
         * @param [in] value The loaned value to be returned.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET if the provided sample object does not 
         * represent an outstanding loan from the sample on which the operation is invoked.
         */
        DDS::ReturnCode_t return_loaned_value(std::shared_ptr<DynamicData> const value);
        
        /**
         * @brief Create and return a new data sample with the same contents as this one.
         * A comparison of this object and the clone using equals immediately following this call will return true.
         * @param [in] other Traget dynamic data to be copied.
         */
        void clone(DynamicData const *const other);

        /**
         * @brief Create and add a new dynamic data by given type kind and member id.
         * @param [in] kind Type kind for the new data.
         * @param [in] id Member id for the new data.
         */
        void add_value(
            TypeKind const kind,
            MemberId const id);
        
        /**
         * @brief Set a default data value with the specified member id.
         * @param [in] id Member id for the data to set.
         */
        void set_default_value(MemberId const id);
        
        /**
         * @brief Create a mapping from member ids to member descriptors by the given dynamic type.
         * @param [in] a_type On which to create the above mapping.
         */
        void create_members(DynamicType_ptr a_type);
        
        /**
         * @brief Create a mapping from member ids to member descriptors by the given dynamic data.
         * @param [in] a_data On which to create the above mapping.
         */
        void create_members(std::shared_ptr<DynamicData> const a_data);
        
        /**
         * @brief Create a mapping from member ids to member descriptors by the given dynamic data.
         * @param [in] a_data On which to create the above mapping.
         */
        void create_members(DynamicData const *const a_data);
        
        /**
         * @brief Clean all properties and release the resource.
         */
        void clean();
        
        /**
         * @brief Clone a new data with given member id and type kind.
         * @param [in] id New data's member id.
         * @param [in] kind New data's type kind.
         * @return std::shared_ptr<void> Pointer to the created data.
         */
        std::shared_ptr<void> clone_value(
            MemberId const id,
            TypeKind const kind) const;
        
        /**
         * @brief This operation compare two data and return if them equal or not.
         * @param [in] kind Type kind of the data.
         * @param [in] left One of the data to be comapred.
         * @param [in] right Another of the data to be comapred.
         * @return gbool_t Result of this comparison, true if the value is same.
         */
        static gbool_t compare_values(
            TypeKind const kind,
            std::shared_ptr<void> const left,
            std::shared_ptr<void> const right) noexcept;
        
        /**
         * @brief This function tells you if the key will be serazlized by cdr or not.
         * @return gbool_t True if this data has two keys or lenght os larger than limit.
         */
        gbool_t is_key_serialized_by_cdr() const;
        
        /**
         * @brief This function serializes a data's key using CDR serialization.
         * @param [in,out] cdr CDR serialization object.
         */
        void serialize_key(DdsCdr &cdr) const;
        
        /**
         * @brief This function serializes a data's key.
         * @param [in,out] buf Key's content.
         * @param [in,out] len Key's length 
         */
        void serialize_key(gchar_t **const buf, guint32_t *const len);
        
        /**
         * @brief Get the key annotations' id and type.
         * @param [in,out] id_and_type Value object where the value is returned.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_NO_DATA if no key annotation found.
         */
        DDS::ReturnCode_t get_key_id_and_type(std::vector<std::pair<MemberId, TypeKind> > &id_and_type) const;
        
        /**
         * @brief Get the key annotations' id and type.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_NO_DATA if no key annotation found.
         */
        DDS::ReturnCode_t get_key_id_and_type();
        
        /**
         * @brief Set the payload header of this data.
         * @return DDS::ReturnCode_t If no error occurs, return DDS::ReturnCode_t::RETCODE_OK.
         */
        DDS::ReturnCode_t set_payload_header_id() noexcept;
        
        /**
         * @brief This function get the payoload header of this data.
         * @return gstone::rtps::SerializedPayloadHeader SerializedPayloadHeader value object where the value is returned.
         */
        inline gstone::rtps::SerializedPayloadHeader get_payload_header() const noexcept
        {
            return m_payloadHeader;
        }
        
        /**
         * @brief This function returns the type member with a specified member id.
         * @param [in] id Member id to the target type member.
         * @param [in,out] type_member Type member with the specified member id.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if Member id is not invalid.
         */
        DDS::ReturnCode_t get_type_member_by_id(MemberId const id, DynamicTypeMember &type_member) const;
        
        /**
         * @brief This function returns the dynamic data with a specified member id.
         * @param [in] id Member id to the target type member.
         * @return DynamicData* DynamicData value object where the value is returned.
         */
        DynamicData* get_data_by_id(guint16_t const id) const;
        
        /**
         * @brief This function returns the dynamic data with a specified member id.
         * @param [in] id Member id to the target type member.
         * @return DynamicData* DynamicData value object where the value is returned.
         */
        DynamicData* get_data_by_member_id(guint16_t const id) const;

        /**
         * @brief This function returns the member descriptor with a specified member id.
         * @param [in,out] value MemberDescriptor value object where the value is returned.
         * @param [in] id Member id to the MemberDescriptor object. 
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if id is invalid.
         */
        DDS::ReturnCode_t get_descriptor(
            MemberDescriptor &value,
            MemberId const id);
        
        /**
         * @brief This function changes the member descriptor with a specified member id.
         * @param [in] id Member id to the MemberDescriptor object to change.
         * @param [in] value New value for the MemberDescriptor object.
         * @return DDS::ReturnCode_t 
         */
        DDS::ReturnCode_t set_descriptor(
            MemberId const id,
            MemberDescriptor const *const value);
        
        /**
         * @brief This convenience operation indicates the kind of this type (e.g., integer, structure, etc.).
         * Its result shall be the same as the kind indicated by the type's descriptor property.
         * @return TypeKind Kind of this type.
         */
        TypeKind get_kind() const noexcept;
        
        /**
         * @brief This convenience operation provides the fully qualified name of this type.
         * It shall be identical to the name string that is a member of the descriptor property.
         * @return gstring_t Type's fully qualified name.
         */
        gstring_t get_name() noexcept;
        
        /**
         * @brief This convenience operation sets the type name.
         * @param [in] name New name for the type.
         */
        void set_type_name(gstring_t const &name);
        
        /**
         * @brief This function clear all contained data and related resource.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_OK if all data is delete successfully.
         */
        DDS::ReturnCode_t clear_data();

        /**
         * @brief This function retrieves the 32-bit integer value with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_int32_value(
            gint32_t &value,
            MemberId const id) const;
        
        /**
         * @brief This function sets a new value for the 32-bit integer data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_int32_value(
            gint32_t const value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function retrieves the 32-bit unsigend integer value with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_uint32_value(
            guint32_t &value,
            MemberId const id) const;
        
        /**
         * @brief This function sets a new value for the 32-bit unsigend integer data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_uint32_value(
            guint32_t const value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function retrieves the 16-bit integer value with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_int16_value(
            gint16_t &value,
            MemberId const id) const;
        
        /**
         * @brief This function sets a new value for the 16-bit integer data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_int16_value(
            gint16_t const value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function retrieves the 16-bit unsigned integer value with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_uint16_value(
            guint16_t &value,
            MemberId const id) const;
        
        /**
         * @brief This function sets a new value for the 16-bit unsigned integer data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_uint16_value(
            guint16_t const value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function retrieves the 64-bit integer value with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_int64_value(
            gint64_t &value,
            MemberId const id) const;
        
        /**
         * @brief This function sets a new value for the 64-bit integer data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_int64_value(
            gint64_t const value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function retrieves the 64-bit unsigned integer value with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_uint64_value(
            guint64_t &value,
            MemberId const id) const;
        
        /**
         * @brief This function sets a new value for the 64-bit unsigned integer data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_uint64_value(
            guint64_t const value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function retrieves the 32-bit floating point value with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_float32_value(
            gfloat32_t &value,
            MemberId const id) const;
        
        /**
         * @brief This function sets a new value for the 32-bit floating point data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_float32_value(
            gfloat32_t const value,
            MemberId const id = MEMBER_ID_INVALID);
        
        
        /**
         * @brief This function retrieves the 64-bit floating point value with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_float64_value(
            gfloat64_t &value,
            MemberId const id) const;
        
        /**
         * @brief This function sets a new value for the 64-bit floating point data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_float64_value(
            gfloat64_t const value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function retrieves the 128-bit floating point value with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_float128_value(
            gfloat128_t &value,
            MemberId const id) const;
        
        /**
         * @brief This function sets a new value for the 128-bit floating point data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_float128_value(
            gfloat128_t const value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function retrieves the 8-bit character value with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_char8_value(
            gchar_t &value,
            MemberId const id) const;
        
        /**
         * @brief This function sets a new value for the 8-bit character data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_char8_value(
            gchar_t const value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function retrieves the 16-bit character value with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_char16_value(
            gchar16_t &value,
            MemberId const id) const;
        
        /**
         * @brief This function sets a new value for the 16-bit character data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_char16_value(
            gchar16_t const value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function retrieves the 8-bit byte value with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_byte_value(
            octet &value,
            MemberId const id) const;
        
        /**
         * @brief This function sets a new value for the 8-bit byte data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_byte_value(
            octet const value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function retrieves the 8-bit integer value with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_int8_value(
            int8_t &value,
            MemberId const id) const;
        
        /**
         * @brief This function sets a new value for the 8-bit integer data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_int8_value(
            int8_t const value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function retrieves the 8-bit unsigned integer value with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_uint8_value(
            guint8_t &value,
            MemberId const id) const;
        
        /**
         * @brief This function sets a new value for the 8-bit unsigned integer data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_uint8_value(
            guint8_t const value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function retrieves the boolean value with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_bool_value(
            gbool_t &value,
            MemberId const id) const;
        
        /**
         * @brief This function retrieves the boolean value with a given member id.
         * @param [in] id Member id of the target value.
         * @return false If an error occurs like invalid member id or data type.
         * @return true If no error occurs.
         */
        gbool_t get_bool_value(
            MemberId const id) const;
        
        /**
         * @brief This function retrieves the boolean value with a given member name.
         * @param [in] name Member name of the target value.
         * @return false If an error occurs like invalid member id or data type.
         * @return true If no error occurs.
         */
        gbool_t get_bool_value(
            gstring_t const &name) const;
        
        /**
         * @brief This function sets a new value for the boolean data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_bool_value(
            gbool_t const value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function sets a new value for the boolean data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] name Member name of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_bool_value(
            gbool_t const value,
            gstring_t const &name);
        
        /**
         * @brief This function retrieves the string value with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_string_value(
            gstring_t &value,
            MemberId const id) const;
        
        /**
         * @brief This function sets a new value for the string data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_string_value(
            gstring_t const &value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function retrieves the wide string value with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_wstring_value(
            gu16string_t &value,
            MemberId const id) const;
        
        /**
         * @brief This function sets a new value for the wide string data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_wstring_value(
            gu16string_t const &value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function retrieves the string value of a enumaration data with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_enum_value(
            gstring_t &value,
            MemberId const id = MEMBER_ID_INVALID) const;
        
        /**
         * @brief This function sets a new string value for the enumaration data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_enum_value(
            gstring_t const &value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function retrieves the digital value of a enumaration data with a given member id.
         * @param [in,out] value Reference to value where the data is returned.
         * @param [in] id Member id of the target value.
         * @return DDS::ReturnCode_t::RETCODE_NO_DATA If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_enum_value(
            guint32_t &value,
            MemberId const id = MEMBER_ID_INVALID) const;
        
        /**
         * @brief This function sets a new digital value for the enumaration data with a given member id.
         * @param [in] value New value for the data.
         * @param [in] id Member id of the the data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_enum_value(
            guint32_t const &value,
            MemberId const id = MEMBER_ID_INVALID);
        
        /**
         * @brief This function retrieves the 64-bit unsigned integer value of a bitmask data.
         * @param [in,out] value Reference to value where the data is returned.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_bitmask_value(
            guint64_t &value) const;
        
        /**
         * @brief This function retrieves the 64-bit unsigned integer value of a bitmask data.
         * @return guint64_t Reference to value where the data is returned.
         */
        guint64_t get_bitmask_value() const;
        
        /**
         * @brief This function sets a new 64-bit unsigned integer value for the bitmask data.
         * @param [in] value New value for the data.
         * @return DDS::ReturnCode_t 
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETE If member id is not found in the value map.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If member id or data type is not invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_bitmask_value(guint64_t const value);

        /**
         * @brief This operatiron gets the default array value of this data.
         * @return std::shared_ptr<DynamicData> const & Reference to value where the data is returned.
         */
        inline std::shared_ptr<DynamicData> const &get_default_array_value() const noexcept
        {
            return m_defaultArrayValue;
        }
        
        /**
         * @brief This operatiron sets the default array value to this data.
         * @param [in] in_data New value for the default array value.
         */
        inline gvoid_t set_default_array_value(std::shared_ptr<DynamicData> const &in_data) noexcept
        {
            m_defaultArrayValue = in_data;   
        }

        /**
         * @brief This function sets a new union id for this data and update related infomation.
         * @param [in] id The new union id for this data.
         * @return DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET If this data not a union type data.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If the member id is not found.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t set_union_id(MemberId const id);
        
        /**
         * @brief This function returns the union id of this data.
         * @return MemberId Value of data's union id.
         */
        inline MemberId get_union_id() const noexcept
        {
            return m_unionId;
        }
        
        /**
         * @brief Update union type data's discriminator infomation.
         */
        void update_union_discriminator();
        
        /**
         * @brief This function sets a new union discriminator data.
         * @param [in] data The new discriminator value for this data.
         */
        void set_union_discriminator(std::shared_ptr<DynamicData> const data) noexcept;

        /**
         * @brief This function gets the effective member id by a giver union label.
         * @param [in] label_value The union label to find related member.
         * @return MemberId ID of the eligible member.
         */
        MemberId get_member_id_by_discriminator(guint64_t const label_value);
        
        /**
         * @brief This function sets the discriminator value of this data.
         * @param [in] value New value for this data's discriminator.
         */
        inline void set_discriminator_value(guint64_t const value) noexcept
        {
            m_discriminatorValue = value;
        }
        
        /**
         * @brief This function returns this union data's discriminator value.
         * @param [in,out] out_value Reference to value where the data is returned.
         */
        void get_discriminator_value(guint64_t &out_value) const noexcept;
        
        /**
         * @brief This function returns this union data's discriminator value.
         * @return guint64_t Discriminator value of this data.
         */
        inline guint64_t get_discriminator_value() const noexcept
        {
            return m_discriminatorValue;
        }
        
        /**
         * @brief This function returns this union data's label.
         * @param [in,out] value Reference to label where the data is returned.
         * @return DDS::ReturnCode_t::RETCODE_ERROR If the label is invalid.
         * @return DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET If the type is invalid.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t get_union_label(guint64_t &value) const;
        
        /**
         * @brief This function returns this union data's label.
         * @return guint64_t Label of the current union data.
         */
        guint64_t get_union_label() const;

        /**
         * @brief This function returns the position of an array type by a given bounds.
         * @param [in] position In bounds to find the target position.
         * @return MemberId Target position of the array type.
         */
        MemberId get_array_index(
            std::vector<guint32_t> const &position);
        
        /**
         * @brief This operation creates and inserts a new element data by a given index.
         * @param [in] index_id Position of the new array element data to create.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If the index is not legal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating element data fail.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_array_data(
            MemberId index_id);
        
        /**
         * @brief This operation remove an existed element data by a given index.
         * @param [in] index_id Position of the array element data to remove.
         * @return DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET If data type is not array. 
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If index is not legal.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t remove_array_data(
            MemberId const index_id);

        /**
         * @brief This operation creates and inserts a new element data by a given index.
         * @param [in,out] index_id Position of the new sequence element data to create.
         * @return DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET If this data's type is not sequence type.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If the given index is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating new element data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_sequence_data(
            MemberId& index_id);

        /**
         * @brief This operation creates and inserts a new element data by a given index.
         * @param in_data Complex data to create and copy insert.
         * @param [in,out] index_id Position of the new sequence element data to create.
         * @return DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET If this data's type is not sequence type.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If the given index is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating new element data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_sequence_data(
            DynamicData const* const in_data,
            MemberId& index_id);

        /**
         * @brief This operation remove an existed element data by a given index.
         * @param [in] index_id Position of the sequence element data to remove.
         * @return DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET If data type is not sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If index is not legal.
         * @return If no error occurs.
         */
        DDS::ReturnCode_t remove_sequence_data(
            MemberId const index_id);
        
        /**
         * @brief This operation inserts a new 8-bit byte type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_byte_value(
            octet const value,
            MemberId &out_id);
        
        /**
         * @brief This operation inserts a new boolena type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_bool_value(
            gbool_t const value,
            MemberId &out_id);
        
        /**
         * @brief This operation inserts a new 8-bit integer type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_int8_value(
            int8_t const value,
            MemberId &out_id);
        
        /**
         * @brief This operation inserts a new 16-bit integer type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_int16_value(
            gint16_t const value,
            MemberId &out_id);
        
        /**
         * @brief This operation inserts a new 32-bit integer type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_int32_value(
            gint32_t const value,
            MemberId &out_id);
        
        /**
         * @brief This operation inserts a new 64-bit integer type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_int64_value(
            gint64_t const value,
            MemberId &out_id);
        
        /**
         * @brief This operation inserts a new 8-bit unsigned integer type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_uint8_value(
            guint8_t const value,
            MemberId &out_id);
        
        /**
         * @brief This operation inserts a new 16-bit unsigned integer type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_uint16_value(
            guint16_t const value,
            MemberId &out_id);
        
        /**
         * @brief This operation inserts a new 32-bit unsigned integer type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_uint32_value(
            guint32_t const value,
            MemberId &out_id);
        
        /**
         * @brief This operation inserts a new 64-bit unsigned integer type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_uint64_value(
            guint64_t const value,
            MemberId &out_id);
        
        /**
         * @brief This operation inserts a new 32-bit floating point type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_float32_value(
            gfloat32_t const value,
            MemberId &out_id);
        
        /**
         * @brief This operation inserts a new 64-bit floating point type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_float64_value(
            gfloat64_t const value,
            MemberId &out_id);
        
        /**
         * @brief This operation inserts a new 128-bit floating point type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_float128_value(
            gfloat128_t const value,
            MemberId &out_id);
        
        /**
         * @brief This operation inserts a new 8-bit character type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_char8_value(
            gchar_t const value,
            MemberId &out_id);
        
        /**
         * @brief This operation inserts a new 16-bit character type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_char16_value(
            gchar16_t const value,
            MemberId &out_id);
        
        /**
         * @brief This operation inserts a new string type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_string_value(
            gstring_t const &value,
            MemberId &out_id);
        
        /**
         * @brief This operation inserts a new wide string type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_wstring_value(
            gu16string_t const &value,
            MemberId &out_id);
        
        /**
         * @brief This operation inserts a new wide string type element data to the sequence.
         * @param [in] value New value to add for this sequence data.
         * @param [in,out] out_id Position to place this new data in the sequence.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If type kind is invalid or member id is illegal.
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_complex_value(
            std::shared_ptr<DynamicData> value,
            MemberId &out_id);
        
        /**
         * @brief Set a new value to an existed complex data in sequence.
         * @param [in] value The complex data with new value.
         * @param [in] id Data position to set.
         * @return DDS::ReturnCode_t 
         */
        DDS::ReturnCode_t set_complex_value(
            std::shared_ptr<DynamicData> value,
            MemberId id = MEMBER_ID_INVALID);

        /**
         * @brief This function creates and inserts a pair of key-value data to the map.
         * @param [in] key The key element data to add for this map.
         * @param [in,out] out_key_id Next key position for this map.
         * @param [in,out] out_value_id Next value position for this map.
         * @return DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET If type is not valid. 
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating data or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If the position is not correct.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_map_data(
            DynamicData const *const key,
            MemberId &out_key_id,
            MemberId &out_value_id);
        
        /**
         * @brief This function creates and inserts a pair of key-value data to the map.
         * @param [in] key The key element data to add for this map.
         * @param [in] value The value element data to add for this map.
         * @param [in,out] out_key Next key position for this map.
         * @param [in,out] out_value Next value position for this map.
         * @return DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET If type is not valid. 
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating data or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If the position is not correct.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_map_data(
            DynamicData const *const key,
            DynamicData* value,
            MemberId &out_key,
            MemberId &out_value);
        
        /**
         * @brief This function creates and inserts a pair of key-value data to the map.
         * @param [in] key The key element data to add for this map.
         * @param [in] value The value element data to add for this map.
         * @param [in,out] out_key Next key position for this map.
         * @param [in,out] out_value Next value position for this map.
         * @return DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET If type is not valid. 
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating data or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If the position is not correct.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_map_data(
            DynamicData const *const key,
            DynamicData const *const value,
            MemberId &out_key,
            MemberId &out_value);
        
        /**
         * @brief This function creates and inserts a pair of key-value data to the map.
         * @param [in] key The key element data to add for this map.
         * @param [in] value The value element data to add for this map.
         * @param [in,out] out_key Next key position for this map.
         * @param [in,out] out_value Next value position for this map.
         * @return DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET If type is not valid. 
         * @return DDS::ReturnCode_t::RETCODE_UNSUPPORTED If creating data or inserting data fails.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If the position is not correct.
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t insert_map_data(
            DynamicData const *const key,
            std::shared_ptr<DynamicData> value,
            MemberId &out_key,
            MemberId &out_value);
        
        /**
         * @brief This function removes a pair of key-value data to the map.
         * @param [in] key_id The key element data id to remove.
         * @return DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET If type is not valid.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If the key id is incorrect. 
         * @return DDS::ReturnCode_t::RETCODE_OK If no error occurs.
         */
        DDS::ReturnCode_t remove_map_data(MemberId const key_id);
        
        /**
         * @brief This operation re-sort the order of the rest members from the start position.
         * @param [in] start_id Start point from where to begin the sorting.
         */
        void sort_member_ids(MemberId const start_id);

        /**
         * @brief This method returns the type of this dynamic data.
         * @return std::shared_ptr<dds::xtypes::DynamicType> This data's dynamic type.
         */
        std::shared_ptr<dds::xtypes::DynamicType> get_type() const;
        
        /**
         * @brief This method returns the element type of this array dynamic data.
         * @return std::shared_ptr<dds::xtypes::DynamicType> This array data's element type
         */
        std::shared_ptr<dds::xtypes::DynamicType> get_array_base_type();
        
        /**
         * @brief This method returns the element type of this sequence dynamic data.
         * @return std::shared_ptr<dds::xtypes::DynamicType> This sequence data's element type
         */
        std::shared_ptr<dds::xtypes::DynamicType> get_sequence_base_type();
        
        /**
         * @brief This method returns the key element type of this map dynamic data.
         * @return std::shared_ptr<dds::xtypes::DynamicType> This map data's key element type
         */
        std::shared_ptr<dds::xtypes::DynamicType> get_map_key_type();
        
        /**
         * @brief This method returns the element type of this map dynamic data.
         * @return std::shared_ptr<dds::xtypes::DynamicType> This map data's element type
         */
        std::shared_ptr<dds::xtypes::DynamicType> get_map_value_type();

        /**
         * @brief This operatrion serializes a type with empty value using CDR serialization.
         * @param [in] a_type The empty data's type to serialize.
         * @param [in] cdr CDR serialization object.
         */
        void serialize_empty_data(DynamicType_ptr const a_type, DdsCdr &cdr) const;
        
        /**
         * @brief This operatrion serializes a discriminator value without considering it's type.
         * @param [in] cdr CDR serialization object.
         */
        gvoid_t serialize_discriminator_typeless(DdsCdr &cdr) const noexcept;
        
        /**
         * @brief This operatrion serializes a discriminator value without considering it's type.
         * @param [in,out] cdr CDR serialization object.
         */
        gvoid_t deserialize_discriminator_typeless(DdsCdr &cdr) noexcept;
        
        /**
         * @brief This function serializes an object with \@id using CDR serialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id Parameter List CDR ID to serialize.
         */
        gvoid_t serialize_id(DdsCdr &cdr, guint16_t const id) const;
        
        /**
         * @brief This function deserializes an object using CDR serialization.
         * @param [in,out] cdr CDR serialization object.
         */
        gvoid_t deserialize_id(DdsCdr &cdr) const;
        
        /**
         * @brief This function deserializes an object using CDR serialization.
         * @param [in,out] cdr CDR serialization object.
         * @param [in] data Data to deserialize.
         * @param [in] id Parameter List CDR ID to serialize.
         */
        static gvoid_t deserialize_id(DdsCdr &cdr, DynamicData *const data, guint16_t const id) noexcept;
        
        /**
         * @brief This function serializes an object with \@auto_id using CDR serialization.
         * @param [in] cdr CDR serialization object.
         * @param [in] id Parameter List CDR ID to serialize.
         */
        gvoid_t serialize_auto_id(DdsCdr &cdr, guint16_t const id) const;
        
        /**
         * @brief This function deserializes an object annotated with \@auto_id using CDR serialization.
         * @param [in,out] cdr CDR serialization object.
         */
        gvoid_t deserialize_auto_id(DdsCdr &cdr) const;
        
        /**
         * @brief This function serializes an object using CDR serialization.
         * @param [in] cdr CDR serialization object.
         */
        gvoid_t serialize(DdsCdr &cdr) const noexcept;
        
        /**
         * @brief This function deserializes an object using CDR serialization.
         * @param [in,out] cdr CDR serialization object.
         */
        gvoid_t deserialize(DdsCdr &cdr) noexcept;

    private:
        DynamicType_ptr m_type;
        std::map<MemberId, std::shared_ptr<MemberDescriptor> > m_descriptor;
        std::map<MemberId, std::shared_ptr<void> > m_value;
        std::vector<MemberId> m_loanedValue;
        gbool_t m_keyElement;
        std::shared_ptr<DynamicData> m_defaultArrayValue; // m_defaultArrayValue
        guint64_t m_unionLabel;
        MemberId m_unionId;
        std::shared_ptr<DynamicData> m_unionDiscriminator;
        guint64_t m_discriminatorValue;
        std::vector<std::pair<MemberId, TypeKind> > m_keyIdAndType;
        gstone::rtps::SerializedPayloadHeader m_payloadHeader;
    };
} // namespace xtypes
} // namespace dds

__GS_DDS4CPP_END_DECLS

#endif // GSTONE_DYNAMIC_DATA_API_H_

