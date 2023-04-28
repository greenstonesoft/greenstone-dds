/**************************************************************
* @file DynamicType.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_DYNAMIC_TYPE_API_H_
#define GSTONE_DYNAMIC_TYPE_API_H_ 1

#include <map>
#include <vector>
#include <string>
#include <memory>

#include "TypeDefs.h"
#include "TypeKind.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace xtypes
{
    class DynamicTypeBuilder;
    class DynamicTypeMember;
    class TypeDescriptor;
    class AnnotationDescriptor;
    /**
     * @brief Base class of all types declared dynamically. It represents a dynamic data type 
     * that can be used to create DynamicData values. By design, the structure of a dynamic type 
     * (its member fields) cannot be modified once the type is created.
     * @details A DynamicType object represents a particular type defined according to the Type System.
     * DynamicType objects have reference semantics because of the large number of references to them 
     * that are expected to exist (e.g., in each DynamicData object created from a given DynamicType).
     * However, the type nevertheless provides operations to allow copying and comparison by value.
     */
    class GS_DDS4CPP_API DynamicType final
    {
    public:
        /**
         * @brief Default constructor.
         */
        DynamicType() = default;
        
        /**
         * @brief Construct a new Dynamic Type object with a pointer parameter.
         * @param [in] descriptor Pointer to a TypeDescriptor object.
         */
        DynamicType(TypeDescriptor const *const descriptor);
        
        /**
         * @brief Construct a new DynamicType object with a pointer parameter.
         * @param [in] descriptor Pointer to a DynamicTypeBuilder object.
         */
        DynamicType(DynamicTypeBuilder const *const _builder);
        
        /**
         * @brief Default destructor.
         */
        ~DynamicType() noexcept;
        
        /**
         * @brief Two types shall be considered equal if and only if all of their respective properties are equal.
         * @param [in] other Another type to be compared.
         * @return true All of their respective properties are equal.
         * @return false Any of their respective properties are not equal.
         */
        bool equals(DynamicType const *const other) const;
        
        /**
         * @brief This operation returns the annotation that corresponds to the specified index, if any.
         * @param [in,out] descriptor Descriptor value object where the value is returned.
         * @param [in] _index Index of the wanted descriptor. 
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if the specified index is greater than the current annotation count.
         */
        DDS::ReturnCode_t get_annotation(AnnotationDescriptor &descriptor, guint32_t const _index) const;
        
        /**
         * @brief This operation returns the current number of annotations applied to the type.
         * @return guint32_t If no annotation was applied, result is zero. 
         */
        guint32_t get_annotation_count() const noexcept;
        
        /**
         * @brief This operation provides a summary of the state of this type. It overwrites the state of an application-provided object.
         * @param [in] descriptor Descriptor value object where the value is returned.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if the argument is nil.
         */
        DDS::ReturnCode_t get_descriptor(TypeDescriptor *const descriptor) const;
        
        /**
         * @brief This convenience operation indicates the kind of this type (e.g., integer, structure, etc.).
         * Its result shall be the same as the kind indicated by the type's descriptor property.
         * @return TypeKind Kind of this type.
         */
        inline TypeKind get_kind() const noexcept
        {
            return m_kind;
        }
        
        /**
         * @brief This operation returns the member that corresponds to the specified member ID, if any.
         * @param [in] member DynamicTypeMember value object where the value is returned.
         * @param [in] member_id Specified member ID to the target Member.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if there is no member with the specified member ID.
         */
        DDS::ReturnCode_t get_member(DynamicTypeMember &member, MemberId const member_id) const;
        
        /**
         * @brief This operation returns the member that corresponds to the specified index, if any.
         * @param [in,out] member DynamicTypeMember value object where the value is returned.
         * @param [in] _index Specified member index to the target Member.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if the specified index is greater than the current member count.
         */
        DDS::ReturnCode_t get_member_by_index(DynamicTypeMember &member, guint32_t const _index) const;
        
        /**
         * @brief This operation returns the member that corresponds to the specified name, if any.
         * @param [in,out] member DynamicTypeMember value object where the value is returned.
         * @param [in] name Specified member name to the target Member.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if there is no member with the specified name.
         */
        DDS::ReturnCode_t get_member_by_name(DynamicTypeMember &member, gstring_t const &name) const;
        
        /**
         * @brief This operation returns the current number of members.
         * @return guint32_t Members' count in total.
         */
        guint32_t get_member_count() const noexcept;
        
        /**
         * @brief This convenience operation provides the fully qualified name of this type.
         * It shall be identical to the name string that is a member of the descriptor property.
         * @return gstring_t Type's fully qualified name.
         */
        inline gstring_t get_name() const noexcept
        {
            return m_name;
        }
        
        /**
         * @brief Default copy constructor.
         * Automatically generated by the compiler.
         * @param [in] x Reference to the object DynamicType that will be copied.
         */
        DynamicType(DynamicType const &x) = default;
        
        /**
         * @brief Default move constructor.
         * Automatically generated by the compiler.
         * @param [in] x Reference to the object DynamicType that will be copied.
         */
        DynamicType(DynamicType &&x) = default;
        
        /**
         * @brief Default copy assignment.
         * Automatically generated by the compiler.
         * @param [in] x Reference to the object DynamicType that will be copied.
         * @return DynamicType& Reference to the object DynamicType that will be assigned.
         */
        DynamicType &operator=(DynamicType const &x) = default;
        
        /**
         * @brief Default move assignment.
         * Automatically generated by the compiler.
         * @param [in] x Reference to the object DynamicType that will be copied.
         * @return DynamicType& Reference to the object DynamicType that will be assigned.
         */
        DynamicType &operator=(DynamicType &&x) = default;

        /**
         * @brief This function tells you if the type has child type.
         * @return true If type kind is annotation/array/map/sequence/structure/union/bitset.
         * @return false If type kind is not annotation/array/map/sequence/structure/union/bitset.
         */
        bool has_children() const noexcept;
        
        /**
         * @brief Set the type name.
         * @param [in] name New name for the type.
         */
        void set_name(gstring_t const &name);
        
        /**
         * @brief Get the TypeDescriptor of this type.
         * @return TypeDescriptor* pointer to the TypeDescriptor.
         */
        inline TypeDescriptor* get_type_descriptor() const noexcept
        {
            return m_descriptor.get();
        }
        
        /**
         * @brief Get this type's element type.
         * If this type is an array, sequence, or string type, this property indicates the element type of the collection. 
         * It must not be nil for the descriptor to be consistent.
         * If this type is a map type, this property indicates the value element type of the map. 
         * It must not be nil for the descriptor to be consistent.
         * If this type is a bitmask type, this property must indicate a Boolean type for the descriptor to be consistent.
         * If this type is any other kind of type, this property must be nil for the descriptor to be consistent.
         * @return std::shared_ptr<dds::xtypes::DynamicType> Smart pointer to the element type.
         */
        std::shared_ptr<dds::xtypes::DynamicType> get_element_type() const noexcept;
        
        /**
         * @brief Get this type's key type.
         * If this type is a map type, this property indicates the value element type of the map. 
         * It must not be nil for the descriptor to be consistent.
         * If this type is any other kind of type, this property must be nil for the descriptor to be consistent.
         * @return std::shared_ptr<dds::xtypes::DynamicType> Smart pointer to the map type.
         */
        std::shared_ptr<dds::xtypes::DynamicType> get_key_element_type() const noexcept;
        
        /**
         * @brief Get this type's base type.
         * If this type is a structure type, base_type indicates the supertype of that type. 
         * A nil value of this property indicates that the structure type has no supertype.
         * If this type represents an alias type, base_type indicates the type being aliased. 
         * A nil value for this property is not considered consistent.
         * In all other cases, a consistent descriptor shall have a nil value for this property.
         * @return std::shared_ptr<dds::xtypes::DynamicType> Smart pointer to the base type.
         */
        std::shared_ptr<DynamicType> get_base_type() const noexcept;
        
        /**
         * @brief Get this type's discriminator type.
         * If this type is a union type, discriminator_type indicates the type of the discriminator of the union. 
         * It must not be nil for the descriptor to be consistent.
         * If this type is any other kind of type, 
         * this property must be nil for this descriptor to be consistent.
         * @return std::shared_ptr<dds::xtypes::DynamicType> Smart pointer to the discriminator type.
         */
        std::shared_ptr<DynamicType> get_discriminator_type() const noexcept;
        
        /**
         * @brief This function tells you if the type has a member with the specified name.
         * @param [in] name Member name to find existed member..
         * @return true If a member with the specified name is found.
         * @return false If a member with the specified name is not found.
         */
        bool exists_member_by_name(gstring_t const &name) const;
        
        /**
         * @brief This function tells you if the type is a discriminator.
         * The discriminator of a union must be of one of the following types:
         * Boolean/Byte/Char8, Char16/Int8, UInt8, Int16, UInt16, Int32, UInt32, Int64, UInt64.
         * Any enumerated type/Any alias type that resolves, directly or indirectly, to one of the aforementioned types.
         * @return true If this type is a discriminator.
         * @return false If this type is not a discriminator.
         */
        bool is_discriminator_type() const;
        
        /**
         * @brief Indicates whether the states of all of this descriptor's properties are consistent. 
         * The definitions of consistency for each property are given in the clause corresponding to that property.
         * @return true If this type is consistent.
         * @return false If this type is not consistent.
         */
        bool is_consistent() const noexcept;
        
        /**
         * @brief This operation returns the member that corresponds to the specified member ID, if any.
         * @param [in,out] type_member DynamicTypeMember value object where the value is returned.
         * @param [in] id Specified member ID to the target Member.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if there is no member with the specified member ID.
         */
        DDS::ReturnCode_t get_type_member_by_id(MemberId const id, dds::xtypes::DynamicTypeMember &type_member);
        
        /**
         * @brief This operation returns all DynamicTypeMember with its id at once.
         * @param [in,out] members A map where all memberids and members are returned.
         * @return DDS::ReturnCode_t Always true right now.
         */
        DDS::ReturnCode_t get_all_members(std::map<MemberId, DynamicTypeMember*> &members) const;
        
        /**
         * @brief This function tells you if the type is complex or not.
         * @return true If type is primitive types or string types.
         * @return false If type is constructed Types, nested Types or snnotations type.
         */
        bool is_complex_kind() const noexcept;
        
        /**
         * @brief Get size of primitive type and enumerated types.
         * @return size_t Size of type in bytes.
         */
        size_t get_size() const;
        
        /**
         * @brief Get the bound of the corresponding dimension.
         * @param [in] _index Dimension of the type bound.
         * @return guint32_t Bound size specified by dimension.
         */
        guint32_t get_bounds(guint32_t const _index = 0U) const noexcept;
        
        /**
         * @brief Get the dimension of bound.
         * @return guint32_t Get dimensions of type bound.
         */
        guint32_t get_bounds_size() const noexcept;
        
        /**
         * @brief Get the total bounds indicating the bound of collection and similar types.
         * If this descriptor represents an array type, the length of the property value indicates the number of
         * dimensions in the array, and each value indicates the bound of the corresponding dimension.
         * If this descriptor represents a sequence, map, bitmask, or string type, the length of the property value
         * is one and the integral value in that property indicates the bound of the collection.
         * @return guint32_t A nil value for the bound property in all other cases.
         */
        guint32_t get_total_bounds() const noexcept;
        
        /**
         * @brief  This operation checks whether or not the given type is a key type.
         * @return true If this type is annotated by a \@key annotation.
         * @return false If this type is not annotated by a \@key annotation.
         */
        bool key_annotation() const;
        
        /**
         * @brief Apply the given annotation to this type. It shall subsequently appear in the annotation property.
         * @param [in,out] descriptor Consistent descriptor for the annotation to apply.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if this argument descriptor is not consistent.
         */
        DDS::ReturnCode_t apply_annotation(AnnotationDescriptor const &descriptor);
        
        /**
         * @brief Apply the given annotation to this member. It shall subsequently appear in the annotation property of the identified member.
         * @param [in] id Identifies the member to which the annotation shall be applied.
         * @param [in] descriptor A consistent descriptor for the annotation to apply.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if this argument descriptor is not consistent or id is not found.
         */
        DDS::ReturnCode_t apply_annotation_to_member(MemberId const id, AnnotationDescriptor const &descriptor);
        
        /**
         * @brief  This operation checks whether or not the given type is a key type.
         * @return true If this type is annotated by a \@key annotation.
         * @return false If this type is not annotated by a \@key annotation.
         */
        bool is_with_key();
        
        /**
         * @brief  This operation checks whether or not the given type is a type with id.
         * @return true If this type is annotated by an \@id annotation.
         * @return false If this type is not annotated by an \@id annotation.
         */
        bool annotation_is_id() const;
        
        /**
         * @brief  This operation checks whether or not the given type is a type with auto id.
         * @return true If this type is annotated by an \@auto_id annotation.
         * @return false If this type is not annotated by an \@auto_id annotation.
         */
        bool annotation_is_auto_id() const;
        
        /**
         * @brief public method to clear a dynamic type.
         */
        void destory();

    private:
        /**
         * @brief clear all contents in a dynamic type and turn it into default status.
         */
        void clear();

        std::shared_ptr<TypeDescriptor> m_descriptor { nullptr };
        std::vector<std::shared_ptr<AnnotationDescriptor> > m_annotation {};
        std::vector<std::shared_ptr<DynamicTypeMember> > m_memberCreated {};
        std::map<MemberId, DynamicTypeMember*> m_member {};
        std::map<gstring_t, DynamicTypeMember*> m_memberByName {};
        
        gstring_t m_name { "" };
        TypeKind m_kind { TK_NONE };
        bool m_isKeyDefined { false };
    };
    using DynamicType_ptr = std::shared_ptr<DynamicType>;
} // namespace xtypes
} // namespace dds

__GS_DDS4CPP_END_DECLS

#endif // GSTONE_DYNAMIC_TYPE_API_H_

