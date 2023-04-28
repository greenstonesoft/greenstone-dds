/**************************************************************
* @file DynamicTypeBuilderFactory.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_DYNAMIC_TYPE_BUILDER_FACTORY_API_H_
#define GSTONE_DYNAMIC_TYPE_BUILDER_FACTORY_API_H_ 1

#include <memory>
#include <string>
#include <vector>
#include <mutex>

#include "TypeDefs.h"
#include "TypeKind.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace xtypes 
{
    class TypeDescriptor;
    class TypeIdentifier;
    class DynamicTypeBuilder;
    class DynamicType;
    class DynamicData;
    class MemberDescriptor;
    class TypeObject;
    class CompleteStructMember;
    using DynamicType_ptr = std::shared_ptr<DynamicType>;
    using CompleteStructMemberSeq = std::vector<CompleteStructMember>;
    /**
     * @brief This class is logically a singleton (although it need not technically be a singleton in practice).
     * Its "only" instance is the starting point for creating and deleting DynamicTypeBuilder objects.
     * @details Singleton class that is in charge of the creation and the management of every DynamicType and 
     * DynamicTypeBuilder. It declares functions to create builders for each kind of supported types. 
     * Given a builder for a specific type, it can also create the corresponding DynamicType. 
     * Some simpler types can be created directly, avoiding the step of creating a DynamicTypeBuilder.
     * Please, refer to the Supported Types documentation for details about which ones support this option.
     */
    class GS_DDS4CPP_API DynamicTypeBuilderFactory final
    {
    private:
        /**
         * @brief Default constructor which is declared as a private method.
         * It can not be called outside.
         */
        DynamicTypeBuilderFactory() = default;
    public:
        /**
         * @brief Get the pointer to the DynamicTypeBuilderFactory singleton class.
         * @return DynamicTypeBuilderFactory* A DynamicTypeBuilderFactory singleton instance's raw pointer.
         * @return Nil value if an error occurs.
         */
        static DynamicTypeBuilderFactory* get_instance();
        /**
         * @brief Reclaim any resources associated with any object(s) previously returned from get_instance.
         * @return DDS::ReturnCode_t::RETCODE_ERROR if any error occurs.
         * @return DDS::ReturnCode_t::RETCODE_OK if the deletion operation is successful.
         */
        static DDS::ReturnCode_t delete_instance() noexcept;
        /**
         * @brief Create and return a new string dynamic type.
         * @param [in] bound The maximum number of elements that may be stored in a string of the new type. \n
         * If this argument is equal to dds::qos::LENGTH_UNLIMITED, the string type shall be considered to be unbounded. \n
         * The element type of the result returned by create_string_type shall be Char8.
         * @return DynamicType_ptr A nil value if an error occurs.
         */
        static DynamicType_ptr create_string_type(uint32_t bound = MAX_STRING_LENGTH);
        /**
         * @brief Create and return a new wide string dynamic type.
         * @param [in] bound The maximum number of elements that may be stored in a wide string of the new type. \n
         * If this argument is equal to dds::qos::LENGTH_UNLIMITED, the string type shall be considered to be unbounded. \n
         * The element type of the result returned by create_wstring_type shall be Char16.
         * @return DynamicType_ptr A nil value if an error occurs.
         */
        static DynamicType_ptr create_wstring_type(uint32_t bound = MAX_STRING_LENGTH);        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing a sequence type.
         * @param [in] type The type of all objects that can be stored in a sequence of the new type.
         * @param [in] bound The maximum number of elements that may be stored in a map of the new type.
         * If this argument is equal to LENGTH_UNLIMITED, the string type shall be considered to be unbounded.
         * @return DynamicTypeBuilder* A nil value if an error occurs, like type is nil.
         */
        DynamicTypeBuilder* create_sequence_builder(
            DynamicType_ptr const type,
            uint32_t bound = MAX_ELEMENTS_COUNT);
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing a array type.
         * @param [in] type The type of all objects that can be stored in an array of the new type.
         * @param [in] bounds A collection of unsigned integers, the length of which is equal to the number 
         * of dimensions in the new array type, and the values of which are the bounds of each dimension.
         * @return DynamicTypeBuilder* A nil value if the type or bounds is illegal.
         */
        DynamicTypeBuilder* create_array_builder(
            DynamicType_ptr const type,
            std::vector<uint32_t> const &bounds);        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing a map type.
         * @param [in] key_type The type of all objects that can be stored as keys in a map of the new type.
         * @param [in] value_type The type of all objects that can be stored as values in a map of the new type.
         * @param [in] bound The maximum number of key-value pairs that may be stored in a map of the new type.
         * If this argument is equal to LENGTH_UNLIMITED, the map type shall be considered to be unbounded.
         * @return DynamicTypeBuilder* This method shall return a nil value if an error occurs.
         */
        DynamicTypeBuilder* create_map_builder(
            DynamicType_ptr key_type,
            DynamicType_ptr value_type,
            uint32_t bound = MAX_ELEMENTS_COUNT);
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing a bitmask type.
         * @param [in] bound The number of reserved bits in the bitmask.
         * @return DynamicTypeBuilder* A nil value if bound is out of range.
         */
        DynamicTypeBuilder* create_bitmask_builder(uint32_t const bound);
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing a enumerated type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_enum_builder();
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing a union type.
         * @param [in] discriminator_type Discriminator type of a union type, it is essential and ues as a union type's default type.
         * @return DynamicTypeBuilder* If discriminator is invalid, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_union_builder(DynamicType_ptr discriminator_type);
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing a struct type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_struct_builder();
        
        /**
         * @brief Create a derived struct builder object with given base type builder.
         * @param [in] base_builder Base type builder to create the derived builder.
         * @return DynamicTypeBuilder* Get a derived builder or a nil value if any error occurs.
         */
        DynamicTypeBuilder* create_derived_struct_builder(
            DynamicTypeBuilder const *const base_builder);
        
        /**
         * @brief Retrieve a DynamicType object corresponding to the indicated primitive type kind.
         * @param [in] kind The kind of the primitive type whose representation is to be returned.
         * @return DynamicType_ptr A nil value if the given kind does not correspond to a primitive type.
         */
        static DynamicType_ptr get_primitive_type(TypeKind const kind);
        
        /**
         * @brief Retrieve a DynamicType object corresponding to the 8-bit integer type. \n
         * Signed integer minimally capable of representing values in the range -127 to +128.
         * @return DynamicType_ptr If an error occurs, this method shall return a nil value.
         */
        static DynamicType_ptr create_int8_type();
        
        /**
         * @brief Retrieve a DynamicType object corresponding to the 8-bit unsigned integer type. \n
         * Unsigned integer minimally capable of representing values in the range 0 to +255.
         * @return DynamicType_ptr If an error occurs, this method shall return a nil value.
         */
        static DynamicType_ptr create_uint8_type();
        
        /**
         * @brief Retrieve a DynamicType object corresponding to the 16-bit integer type. \n
         * Signed integer minimally capable of representing values in the range -32768 to +32767.
         * @return DynamicType_ptr If an error occurs, this method shall return a nil value.
         */
        static DynamicType_ptr create_int16_type();
        
        /**
         * @brief Retrieve a DynamicType object corresponding to the 16-bit unsigned integer type. \n
         * Unsigned integer minimally capable of representing values in the range 0 to +65535.
         * @return DynamicType_ptr If an error occurs, this method shall return a nil value.
         */
        static DynamicType_ptr create_uint16_type();
        
        /**
         * @brief Retrieve a DynamicType object corresponding to the 32-bit integer type. \n
         * Signed integer minimally capable of representing values in the range -2147483648 to +2147483647.
         * @return DynamicType_ptr If an error occurs, this method shall return a nil value.
         */
        static DynamicType_ptr create_int32_type();
        
        /**
         * @brief Retrieve a DynamicType object corresponding to the 32-bit unsigned integer type. \n
         * Unsigned integer minimally capable of representing values in the range 0 to +4294967295.
         * @return DynamicType_ptr If an error occurs, this method shall return a nil value.
         */
        static DynamicType_ptr create_uint32_type();
        
        /**
         * @brief Retrieve a DynamicType object corresponding to the 64-bit integer type. \n
         * Signed integer minimally capable of supporting values in the range -9223372036854775808 to +9223372036854775807.
         * @return DynamicType_ptr If an error occurs, this method shall return a nil value.
         */
        static DynamicType_ptr create_int64_type();
        
        /**
         * @brief Retrieve a DynamicType object corresponding to the 64-bit unsigned integer type. \n
         * Unsigned integer minimally capable of supporting values in the range 0 to +18446744073709551617.
         * @return DynamicType_ptr If an error occurs, this method shall return a nil value.
         */
        static DynamicType_ptr create_uint64_type();
        
        /**
         * @brief Retrieve a DynamicType object corresponding to the 32-bit floating point type. \n
         * Floating point number minimally capable of supporting the range and precision of an IEEE 754 single-precision floating point value.
         * @return DynamicType_ptr If an error occurs, this method shall return a nil value.
         */
        static DynamicType_ptr create_float32_type();
        
        /**
         * @brief Retrieve a DynamicType object corresponding to the 64-bit floating point type. \n
         * Floating point number minimally capable of supporting the range and precision of an IEEE 754 double-precision floating point value.
         * @return DynamicType_ptr If an error occurs, this method shall return a nil value.
         */
        static DynamicType_ptr create_float64_type();
        
        /**
         * @brief Retrieve a DynamicType object corresponding to the 128-bit floating point type. \n
         * Floating point number minimally capable of supporting the range and precision of an IEEE 754 quadruple-precision floating point value.
         * @return DynamicType_ptr If an error occurs, this method shall return a nil value.
         */
        static DynamicType_ptr create_float128_type();
        
        /**
         * @brief Retrieve a DynamicType object corresponding to the 8-bit character type. \n
         * 8-bit character type. There is no encoding specified, it may be ASCII, ISO-8859-1, or used to hold a byte of a multi-byte-encoded character set.
         * @return DynamicType_ptr If an error occurs, this method shall return a nil value.
         */
        static DynamicType_ptr create_char8_type();
        
        /**
         * @brief Retrieve a DynamicType object corresponding to the 16-bit character type. \n
         * 16-bit character type capable of supporting the Basic Multilingual Plane (BMP) encoded in UTF-16.
         * @return DynamicType_ptr If an error occurs, this method shall return a nil value.
         */
        static DynamicType_ptr create_char16_type();
        
        /**
         * @brief Retrieve a DynamicType object corresponding to the boolean type. \n
         * Boolean type. Data of this type can only take two values: true and false.
         * @return DynamicType_ptr If an error occurs, this method shall return a nil value.
         */
        static DynamicType_ptr create_bool_type();
        
        /**
         * @brief Retrieve a DynamicType object corresponding to the 8-bit byte type. \n
         * Single opaque byte. A Byte value has no numeric value.
         * @return DynamicType_ptr If an error occurs, this method shall return a nil value.
         */
        static DynamicType_ptr create_byte_type();
        
        /**
         * @brief Delete the given DynamicType object, which was previously created by this factory.
         * @param [in] type The type to delete.
         * @return DDS::ReturnCode_t::RETCODE_ERROR if an implementation-specific error occurs,
         * @return DDS::ReturnCode_t::RETCODE_ALREADY_DELETED if this argument is an object that was already deleted,
         * @return DDS::ReturnCode_t::RETCODE_OK if operation is finished or deletions on nil/objects returned by get_primitive_type.
         */
        static DDS::ReturnCode_t delete_type(DynamicType *const type) noexcept;

        /**
         * @brief Default destructor.
         */
        ~DynamicTypeBuilderFactory() noexcept;
        
        /**
         * @brief Default copy constructor(deleted).
         * @param [in] x Reference to the object DynamicTypeBuilderFactory that will be copied.
         */
        DynamicTypeBuilderFactory(DynamicTypeBuilderFactory const &x) = delete;
        
        /**
         * @brief Default move constructor(deleted).
         * @param [in] x Reference to the object DynamicTypeBuilderFactory that will be copied.
         */
        DynamicTypeBuilderFactory(DynamicTypeBuilderFactory &&x) = delete;
        
        /**
         * @brief Default copy assignment(deleted).
         * @param [in] x Reference to the object DynamicTypeBuilderFactory that will be copied.
         * @return DynamicTypeBuilderFactory &Reference to the object DynamicTypeBuilderFactory that will be assigned.
         */
        DynamicTypeBuilderFactory &operator=(DynamicTypeBuilderFactory const &x) = delete;
        
        /**
         * @brief Default move assignment(deleted).
         * @param [in] x Reference to the object DynamicTypeBuilderFactory that will be copied.
         * @return DynamicTypeBuilderFactory &Reference to the object DynamicTypeBuilderFactory that will be assigned.
         */
        DynamicTypeBuilderFactory &operator=(DynamicTypeBuilderFactory &&x) = delete;

        /**
         * @brief Create and return a new DynamicType object as described by the given type builder.
         * @param [in] other The builder of the new type to create.
         * @return DynamicType_ptr If this argument is nil or invalid, this operation shall fail and return a nil value.
         */
        static DynamicType_ptr create_type(DynamicTypeBuilder const *const other);
        
        /**
         * @brief Create and return a new DynamicType object as described by the given type descriptor.
         * This method is the conventional mechanism for creating structrued, enumerated, and alias types, \n
         * although it can also be used to create types of other kinds.
         * @param [in] descriptor The properties of the new type to create.
         * @return DynamicType_ptr If descriptor is nil or inconsistent (as indicated by its is_consistent operation), \n 
         * this operation shall fail and return a nil value.
         */
        static DynamicType_ptr create_type(TypeDescriptor const *const descriptor);
        
        /**
         * @brief Create and return a new DynamicType object as described by the given type descriptor and name.
         * @param [in] descriptor The properties of the new type to create.
         * @param [in] name The name of the new type to create.
         * @return DynamicType_ptr If descriptor is nil or inconsistent (as indicated by its is_consistent operation), \n
         * this operation shall fail and return a nil value.
         */
        static DynamicType_ptr create_type(
            TypeDescriptor const *const descriptor,
            gstring_t const &name);
        
        /**
         * @brief Create and return a new primitive or string/wstring DynamicType object with the kind.
         * @param [in] kind The kind of the primitive or string type whose representation is to be returned.
         * @return DynamicType_ptr The operation shall fail and return a nil value if the given kind is not 
         * correspond to a primitive or a string type.
         */
        static DynamicType_ptr get_type(TypeKind const kind);
        
        /**
         * @brief Create a new TypeObject object as described by the given dynamic type and constraint.
         * @param [in] type Dynamic type to create the object.
         * @param [in,out] object New object that will be created and returned.
         * @param [in] complete If "complete" is true the created object wll be complete, otherwise the object will be minimal.
         * @param [in] force If "force" is true, the object is still to be created no matter already existed or not.
         */
        void create_type_object(
            DynamicType_ptr const type,
            TypeObject &object,
            bool const complete = true,
            bool const force = false);
        
        /**
         * @brief Create a new TypeObject object as described by the given dynamic type and constraint.
         * @param [in] descriptor The properties of the new object to create.
         * @param [in,out] object New object that will be created and returned.
         * @param [in] members Descriptors of members in the dynamic type.
         * @param [in] complete If true the created object wll be complete, otherwise the object will be minimal.
         * @param [in] force If true, the object is still to be created no matter already existed or not.
         */
        void create_type_object(
            TypeDescriptor const *const descriptor, 
            TypeObject &object,
            std::vector<MemberDescriptor const *> const *const members = nullptr, 
            bool const complete = true,
            bool const force = false);
        
        /**
         * @brief Create a new string identifier as described by the given descriptor.
         * @param [in] descriptor The properties of the string type to create.
         */
        static void build_string8_type_code(
            TypeDescriptor const *const descriptor);
        
        /**
         * @brief Create a new wide string identifier as described by the given descriptor.
         * @param [in] descriptor The properties of the wide string type to create.
         */
        static void build_string16_type_code(
            TypeDescriptor const *const descriptor);
        
        /**
         * @brief Create a new structrue type object as described by the given information.
         * @param [in] descriptor The properties of the new object to create.
         * @param [in,out] object New object that will be created and returned.
         * @param [in] members Descriptor of member in the dynamic type.
         * @param [in] complete If true the created object wll be complete, otherwise the object will be minimal.
         */
        void build_struct_type_code(
            TypeDescriptor const *const descriptor,
            TypeObject &object,
            std::vector<MemberDescriptor const *> const &members,
            bool const complete = true);
        
        /**
         * @brief Create a new union type object as described by the given information.
         * @param [in] descriptor The properties of the new object to create.
         * @param [in,out] object New object that will be created and returned.
         * @param [in] members Descriptors of members in the dynamic type.
         * @param [in] complete If true the created object wll be complete, otherwise the object will be minimal.
         */
        void build_union_type_code(
            TypeDescriptor const *const descriptor,
            TypeObject &object,
            std::vector<MemberDescriptor const *> const &members,
            bool const complete = true);
        
        /**
         * @brief Create a new enumaration type object as described by the given information.
         * @param [in] descriptor The properties of the new object to create.
         * @param [in,out] object New object that will be created and returned.
         * @param [in] members Descriptors of members in the dynamic type.
         * @param [in] complete If true the created object wll be complete, otherwise the object will be minimal.
         */
        static void build_enum_type_code(
            TypeDescriptor const *const descriptor,
            TypeObject &object,
            std::vector<MemberDescriptor const *> const &members,
            bool const complete = true);
        
        /**
         * @brief Create a new bitmask type object as described by the given information.
         * @param [in] descriptor The properties of the new object to create.
         * @param [in,out] object New object that will be created and returned.
         * @param [in] members Descriptors of members in the dynamic type.
         * @param [in] complete If true the created object wll be complete, otherwise the object will be minimal.
         */
        static void build_bitmask_type_code(
            TypeDescriptor const *const descriptor,
            TypeObject &object,
            std::vector<MemberDescriptor const *> const &members,
            bool const complete = true);
        
        /**
         * @brief Create a new sequence type object as described by the given information.
         * @param [in] descriptor The properties of the new object to create.
         * @param [in,out] object New object that will be created and returned.
         * @param [in] complete If true the created object wll be complete, otherwise the object will be minimal.
         */
        void build_sequence_type_code(
            TypeDescriptor const *const descriptor,
            TypeObject &object,
            bool const complete = true);
        
        /**
         * @brief Create a new array type object as described by the given information.
         * @param [in] descriptor The properties of the new object to create.
         * @param [in,out] object New object that will be created and returned.
         * @param [in] complete If true the created object wll be complete, otherwise the object will be minimal.
         */
        void build_array_type_code(
            TypeDescriptor const *const descriptor,
            TypeObject &object,
            bool const complete = true);
        
        /**
         * @brief Create a new map type object as described by the given information.
         * @param [in] descriptor The properties of the new object to create.
         * @param [in,out] object New object that will be created and returned.
         * @param [in] complete If true the created object wll be complete, otherwise the object will be minimal.
         */
        void build_map_type_code(
            TypeDescriptor const *const descriptor,
            TypeObject &object,
            bool const complete = true);
        
        /**
         * @brief Create a new alias type object as described by the given information.
         * @param descriptor The properties of the new object to create.
         * @param object New object that will be created and returned.
         * @param complete If true the created object wll be complete, otherwise the object will be minimal.
         */
        void build_alias_type_code(
            TypeDescriptor const *const descriptor,
            TypeObject &object,
            bool const complete = true);
        
        /**
         * @brief Create a new inheritance type object as described by the given information.
         * @param [in] descriptor The properties of the new object to create.
         * @param [in,out] object New object that will be created and returned.
         * @param [in] members Descriptor of member in the dynamic type.
         * @param complete If true the created object wll be complete, otherwise the object will be minimal.
         */
        void build_inheritance_type_code(
            TypeDescriptor const *const descriptor,
            TypeObject &object,
            std::vector<MemberDescriptor const *> const &members,
            bool const complete = true);
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object as described by the given type descriptor.
         * @param [in] descriptor The properties of the new builder to create.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_one_builder(
            TypeDescriptor const *const descriptor);
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object as described by the given type descriptor and name.
         * @param [in] descriptor The properties of the new builder to create.
         * @param [in] name The name of the new builder to create.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_one_builder(
            TypeDescriptor const* descriptor,
            gstring_t const &name);
        
        /**
         * @brief Create and add a new TypeIdentifier object as described by the given dynamic type and constraint.
         * @param [in] type Dynamic type to create the identifier.
         * @param [in,out] identifier New identifier that will be created and returned.
         * @param [in] complete If true the created object wll be complete, otherwise the object will be minimal.
         */
        void build_type_identifier(
            DynamicType_ptr const type,
            TypeIdentifier &identifier,
            bool const complete = true) const;
        
        /**
         * @brief Create and add a new TypeIdentifier object as described by the given descriptor and constraint.
         * @param [in] descriptor The properties of the new builder to create.
         * @param [in,out] identifier New identifier that will be created and returned.
         * @param [in] complete If true the created object wll be complete, otherwise the object will be minimal.
         */
        void build_type_identifier(
            TypeDescriptor const *const descriptor,
            TypeIdentifier &identifier,
            bool const complete = true) const;
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing an array type.
         * @param [in] element_type An existed builder with an array type.
         * @param [in] bounds A collection of unsigned integers, the length of which is equal to the number
         * of dimensions in the new array type, and the values of which are the bounds of each dimension.
         * @return DynamicTypeBuilder* A nil value if the builder or bounds is illegal.
         */
        DynamicTypeBuilder* create_array_builder(
            DynamicTypeBuilder const *const element_type,
            std::vector<uint32_t> const &bounds);
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing a bitmask type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_bitset_builder();
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing a map type.
         * @param [in] key_element_builder An existed builder with a map key builder.
         * @param [in] value_element_builder An existed builder with a map value builder.
         * @param [in] bound The maximum number of key-value pairs that may be stored in a map of the new type.
         * If this argument is equal to LENGTH_UNLIMITED, the map type shall be considered to be unbounded.
         * @return DynamicTypeBuilder* This method shall return a nil value if an error occurs.
         */
        DynamicTypeBuilder* create_map_builder(
            DynamicTypeBuilder const *const key_element_builder,
            DynamicTypeBuilder const *const value_element_builder,
            uint32_t const bound = MAX_ELEMENTS_COUNT);
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing the 16-bit integer type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_int16_builder();
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing the 16-bit unsigned integer type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_uint16_builder();
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing the 32-bit integer type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_int32_builder();
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing the 32-bit unsigned integer type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_uint32_builder();
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing the 64-bit integer type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_int64_builder();
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing the 64-bit unsigned integer type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_uint64_builder();
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing the 32-bit floating point type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_float32_builder();
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing the 64-bit floating point type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_float64_builder();
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing the 128-bit floating point type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_float128_builder();
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing the 8-bit character type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_char8_builder();
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing the 16-bit character type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_char16_builder();
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing the boolean type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_bool_builder();
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing the 8-bit byte type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_byte_builder();
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing the string type.
         * @param [in] bound The maximum number of elements that may be stored in a string of the new type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_string_builder(uint32_t bound = MAX_STRING_LENGTH);
        
        /**
         * @brief Create and return a new DynamicTypeBuilder object representing the wide string type.
         * @param [in] bound The maximum number of elements that may be stored in a string of the new type.
         * @return DynamicTypeBuilder* If an error occurs, this method shall return a nil value.
         */
        DynamicTypeBuilder* create_wstring_builder(uint32_t bound = MAX_STRING_LENGTH);
        
        /**
         * @brief Create and return a alias dynamic type.
         * @param [in] base_type The base tpye of the alias type to create.
         * @param [in] name The name of the alias type to create.
         * @return DynamicType_ptr A nil value if the builder or bounds is illegal.
         */
        static DynamicType_ptr create_alias_type(
            DynamicType_ptr const base_type,
            gstring_t const &alias_name);
        
        /**
         * @brief Create and return a alias dynamic type.
         * @param [in] base_type An existed builder with an alias' base type.
         * @param [in] name The name of the alias type to create.
         * @return DynamicType_ptr A nil value if the builder or bounds is illegal.
         */
        static DynamicType_ptr create_alias_type(
            DynamicTypeBuilder const *const base_type_builder,
            gstring_t const &alias_name);
        
        /**
         * @brief Create and return a dynamic type of an primitive annotation with given name.
         * @param [in] name The name of the type to create.
         * @return DynamicType_ptr A nil value if the builder or bounds is illegal.
         */
        static DynamicType_ptr create_annotation_primitive(gstring_t const &name);
    private:
        /**
         * @brief Create a CompleteStructMemberSeq object from the given MemberDescriptor object.
         * @param [in,out] aux_member_seq Reference to the CompleteStructMemberSeq object where result returned.
         * @param [in] member_descriptor Raw pointer to the MemberDescriptor object to create object.
         * @return true If this creation is correct;
         * @return false If any error occurs when creating target object.
         */
        bool const create_complete_struct_member_seq(
            CompleteStructMemberSeq &aux_member_seq,
            MemberDescriptor const *const member_descriptor);

        /**
         * @brief Add created DynamicTypeBuilder to the factory's list.
         * @param [in] builder The builder to be added.
         */
        void add_to_builder_list(std::shared_ptr<DynamicTypeBuilder> const builder);

    private:
        mutable std::mutex m_mutex_builder;
        std::vector<std::shared_ptr<DynamicTypeBuilder> > m_buildersList;
    };
} // namespace xtypes
} // namespace dds

__GS_DDS4CPP_END_DECLS

#endif // GSTONE_DYNAMIC_TYPE_BUILDER_FACTORY_API_H_

