/**************************************************************
* @file DynamicTypeBuilder.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_DYNAMIC_TYPE_BUILDER_API_H_
#define GSTONE_DYNAMIC_TYPE_BUILDER_API_H_ 1

#include <map>
#include <vector>
#include <string>
#include <memory>

#include "swiftdds/dcps/xtypes/TypeDefs.h"
#include "swiftdds/dcps/xtypes/TypeKind.h"
#include "swiftdds/dcps/xtypes/AnnotationDescriptor.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace xtypes
{
    class AnnotationDescriptor;
    class TypeDescriptor;
    class MemberDescriptor;
    class DynamicType;
    class DynamicTypeMember;
    using DynamicType_Ptr = std::shared_ptr<DynamicType>;
    /**
     * @brief A DynamicTypeBuilder object represents a transitional state of a particular type defined
     * according to the Type System. It is used to instantiate concrete DynamicType objects.
     * @details Intermediate class used to configure a DynamicType before it is created. By design,
     * the structure of a DynamicType (its member fields) cannot be modified once the object is created.
     * Therefore, all its structure must be defined prior to its creation. The builder is the object
     * used to set up this structure. Once defined, the DynamicTypeBuilderFactory is used to create
     * the DynamicType from the information contained in the builder. As a shortcut, the builder exposes
     * a function build() that internally uses the DynamicTypeBuilderFactory to return a fully constructed
     * DynamicType. The types created with build() are still subject  to the Memory management restrictions,
     * and must be deleted by the DynamicTypeBuilderFactory. Builders can be reused after the creation 
     * of a DynamicType, as the changes applied to the builder do not affect to types created previously.
     */
    class GS_DDS4CPP_API DynamicTypeBuilder final
    {
    public:
        /**
         * @brief Default constructor.
         */
        DynamicTypeBuilder() = default;
        
        /**
         * @brief Construct a new DynamicTypeBuilder object with a type descriptor.
         * @param [in] descriptor Pointer to the object TypeDescriptor that will be used.
         */
        DynamicTypeBuilder(TypeDescriptor const *const descriptor);
        
        /**
         * @brief Construct a new DynamicTypeBuilder object with another builder.
         * @param [in] other Pointer to the object DynamicTypeBuilder that will be used.
         */
        DynamicTypeBuilder(DynamicTypeBuilder const *const other);
        
        /**
         * @brief Default destructor.
         */
        ~DynamicTypeBuilder() noexcept;
        
        /**
         * @brief Add a "member" to ENUMERATION_TYPE or BITMASK_TYPE type builder.
         * @param [in] _index Value of the enumerated member.
         * @param [in] name name of the enumerated member
         * @return DDS::ReturnCode_t::RETCODE_OK if add member successfully
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER.
         */
        DDS::ReturnCode_t add_empty_member(
            uint32_t const _index, 
            std::string const &name);

        /**
         * @brief Add a "member" to an existed BITSET type builder.
         * @param [in] id Member id of the bitset member.
         * @param [in] position Start potion of this bitset member.
         * @param [in] bound Number of bits that can be stored (its size). The maximum value is 64.
         * @param [in] name Name of the bit field, if it is empty this bits is unused.
         * @param [in] type Type that will be used to manipulate the bit field as a whole
         * When no destination type is given, it takes as default value the smallest type 
         * able to store the bit field with no loss (i.e., boolean if size is 1, octet if it is between 2 and 8, 
         * unsigned short if it is between 9 and 16, unsigned long if it is between 17 and 32 and 
         * unsigned long long if it is between 33 and 64).
         * @return DDS::ReturnCode_t::RETCODE_OK if add member successfully.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if add member failed.
         * @return DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET if builder is not correct type.
         */
        DDS::ReturnCode_t add_member(
            MemberId const id,
            uint32_t const position,
            uint32_t const count,
            std::string const &name,
            DynamicType_Ptr const type = nullptr);
        
        /**
         * @brief Add a "member" to Struct type builder.
         * @param [in] id Member id of the struct member.
         * @param [in] name Member name of the struct member.
         * @param [in] type Member type of the struct member.
         * @return DDS::ReturnCode_t Return DDS::ReturnCode_t::RETCODE_OK if add member successfully, otherwise return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER.
         */
        DDS::ReturnCode_t add_member(
            MemberId const id, 
            std::string const &name, 
            DynamicType_Ptr const type = nullptr);

        /**
         * @brief Add a "member" to Union type builder.
         * @param [in] id Member id of the union member.
         * @param [in] name Member name of the union member.
         * @param [in] type  Member type of the union member.
         * @param [in] union_labels Member union labels of the union member.
         * @param [in] is_default is default member in this union type.
         * @return DDS::ReturnCode_t Return DDS::ReturnCode_t::RETCODE_OK if add member successfully, otherwise return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER.
         */
        DDS::ReturnCode_t add_member(
            MemberId const id,
            std::string const &name,
            DynamicType_Ptr const type,
            std::vector<int64_t> const &union_labels,
            gbool_t const is_default);
        
        /**
         * @brief Add a "member" to Union type builder.
         * @param [in] id Member id of the union member.
         * @param [in] name Member name of the union member.
         * @param [in] type  Member type of the union member.
         * @param [in] default_value Member default value of the union member.
         * @param [in] union_labels Member union labels of the union member.
         * @param [in] is_default is default member in this union type.
         * @return DDS::ReturnCode_t Return DDS::ReturnCode_t::RETCODE_OK if add member successfully, otherwise return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER.
         */
        DDS::ReturnCode_t add_member(
            MemberId const id,
            std::string const &name,
            DynamicType_Ptr const type,
            std::string const &default_value,
            std::vector<int64_t> const &union_labels,
            gbool_t const is_default);
        
        /**
         * @brief Apply the given annotation to this type. It shall subsequently appear in the annotation property.
         * @param [in] descriptor consistent descriptor for the annotation to apply.
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
         * @brief Create an immutable DynamicType object containing a snapshot of this builder's current state.
         * Subsequent changes to this builder, if any, shall have no observable effect on the states of any previously created DynamicTypes.
         * @return DynamicType_Ptr Smart pointer of the dynamic type which built by the builder.
         */
        DynamicType_Ptr build() const;
        
        /**
         * @brief Get the result if two dynamic type is the same type. \n
         * @param [in] other Dynamic type that to be compared.
         * @return gbool_t True if and only if all of their respective properties.
         */
        gbool_t equals(DynamicType const &other) const noexcept;
        
        /**
         * @brief This operation returns the annotation that corresponds to the specified index, if any.
         * @param [in,out] descriptor Descriptor value object where the value is returned.
         * @param [in] _index Index of the wanted descriptor. 
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if the specified index is greater than the current annotation count.
         */
        DDS::ReturnCode_t get_annotation(AnnotationDescriptor& descriptor, uint32_t const _index) const;
        
        /**
         * @brief This operation returns the current number of annotations applied to the type.
         * @return guint32_t If no annotation was applied, result is zero. 
         */
        uint32_t get_annotation_count() const noexcept;
        
        /**
         * @brief This operation provides a summary of the state of this type. It overwrites the state of an application-provided object.
         * @param [in,out] descriptor Descriptor value object where the value is returned.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if the argument is nil.
         */
        DDS::ReturnCode_t get_descriptor(TypeDescriptor &descriptor);
        
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
         * @param [in,out] member DynamicTypeMember value object where the value is returned.
         * @param [in] member_id Specified member ID to the target Member.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if there is no member with the specified member ID.
         */
        DDS::ReturnCode_t get_member(DynamicTypeMember& member, MemberId const member_id) const;
        
        /**
         * @brief This operation returns the member that corresponds to the specified index, if any.
         * @param [in,out] member DynamicTypeMember value object where the value is returned.
         * @param [in] _index Specified member index to the target Member.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if the specified index is greater than the current member count.
         */
        DDS::ReturnCode_t get_member_by_index(DynamicTypeMember& member, uint32_t const _index) const;
        
        /**
         * @brief This operation returns the member that corresponds to the specified name, if any.
         * @param [in,out] member DynamicTypeMember value object where the value is returned.
         * @param [in] name Specified member name to the target Member.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if there is no member with the specified name.
         */
        DDS::ReturnCode_t get_member_by_name(DynamicTypeMember& member, std::string const &name) const;
        
        /**
         * @brief This operation returns the current number of members.
         * @return guint32_t Members' count in total.
         */
        uint32_t get_member_count() const;
        
        /**
         * @brief This convenience operation provides the fully qualified name of this type.
         * It shall be identical to the name string that is a member of the descriptor property.
         * @return gstring_t Type's fully qualified name.
         */
        inline std::string get_name() const
        {
            return m_name;
        }
        
        /**
         * @brief This convenience operation changes the fully qualified name of this type.
         * @param [in] name New name for the type.
         * @return DDS::ReturnCode_t Always DDS::ReturnCode_t::RETCODE_OK.
         */
        DDS::ReturnCode_t set_name(std::string const &name);

        /**
         * @brief Default copy constructor which is deleted.
         * @param [in] x Reference to the object DynamicTypeBuilder that will be copied.
         */
        DynamicTypeBuilder(DynamicTypeBuilder const &x) = delete;
        
        /**
         * @brief Default move constructor which is deleted.
         * @param [in] x Reference to the object DynamicTypeBuilder that will be copied.
         */
        DynamicTypeBuilder(DynamicTypeBuilder &&x) = delete;
        
        /**
         * @brief Default copy assignment which is deleted.
         * @param [in] x Reference to the object DynamicTypeBuilder that will be copied.
         * @return DynamicTypeBuilder& Reference to the object DynamicTypeBuilder that to be assigned.
         */
        DynamicTypeBuilder& operator=(DynamicTypeBuilder const &x) = delete;
        
        /**
         * @brief Default move assignment which is deleted.
         * @param [in] x Reference to the object DynamicTypeBuilder that will be copied.
         * @return DynamicTypeBuilder& Reference to the object DynamicTypeBuilder that to be assigned.
         */
        DynamicTypeBuilder& operator=(DynamicTypeBuilder &&x) = delete;

        /**
         * @brief This function returns the pointer to the TypeDescriptor of this builder.
         * @return std::shared_ptr<TypeDescriptor> const &Shared pointer to the TypeDescriptor object.
         */
        inline std::shared_ptr<TypeDescriptor> const &get_descriptor() const noexcept
        {
            return m_descriptor;
        }
        
        /**
         * @brief This operation returns all DynamicTypeMember with it's member id at once.
         * @param [in,out] members A mapping from the member ID of a member of this (aggregated) type to the member itself
         * @return DDS::ReturnCode_t Always true right now.
         */
        DDS::ReturnCode_t get_all_members(std::map<MemberId, DynamicTypeMember*>& members) const;
        
        /**
         * @brief Add a "member" to this type, where the new "member" has the meaning defined in the
         * specification of the DynamicTypeMember class. Following a successful return, the new member 
         * shall appear in the member property and possibly in the member_by_id property,
         * based on the definition of that property.
         * @param [in] descriptor A descriptor of the new member to be added.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if descriptor is nil, DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET
         * if type kind is not supported, DDS::ReturnCode_t::RETCODE_OK otherwise.
         */
        DDS::ReturnCode_t add_member(MemberDescriptor const *const descriptor);
        
        /**
         * @brief Set base type to an existed type builder.
         * @param [in] base_type New base type for this builder.
         */
        void set_base_type(DynamicType_Ptr const &base_type) noexcept;
    private:
        /**
         * @brief This operation returns the member id that corresponds to the specified name, if any.
         * @param [in] name Name to find the specified member.
         * @return MemberId MEMBER_ID_INVALID if the specified name is not found.
         */
        MemberId get_member_id_by_name(std::string const &name) const;
        
        /**
         * @brief This function tells you if the type has a member with the specified name.
         * @param name Member name to find existed member.
         * @return true If a member with the specified name is found.
         * @return false If a member with the specified name is not found.
         */
        gbool_t exists_member_by_name(std::string const &name) const;
        
        /**
         * @brief This function tells you if a type is a legal union type or not.
         * @param [in] descriptor MemberDescriptor of a type to be check.
         * @return gbool_t True if a type is not union or a legal union tyoe.
         */
        gbool_t check_union_configuration(MemberDescriptor const *const descriptor);
        
        /**
         * @brief This function tells you if the type is a discriminator.
         * The discriminator of a union must be of one of the following types:
         * Boolean/Byte/Char8, Char16/Int8, UInt8, Int16, UInt16, Int32, UInt32, Int64, UInt64.
         * Any enumerated type/Any alias type that resolves, directly or indirectly, to one of the aforementioned types.
         * @return true If this type is a discriminator.
         * @return false If this type is not a discriminator.
         */
        gbool_t is_discriminator_type() const;
        
        /**
         * @brief Indicates whether the states of all of this descriptor's properties are consistent. 
         * The definitions of consistency for each property are given in the clause corresponding to that property.
         * @return true If this type is consistent.
         * @return false If this type is not consistent.
         */
        gbool_t is_consistent() const noexcept;
        
        /**
         * @brief Get the TypeDescriptor object's pointer.
         * @return TypeDescriptor const* Pinter to this builder's descriptor.
         */
        inline TypeDescriptor const* get_type_descriptor() const noexcept
        {
            return m_descriptor.get();
        }
    private:
        std::shared_ptr<TypeDescriptor> m_descriptor { nullptr };
        std::string m_name { "" };
        TypeKind m_kind { TK_NONE };
        uint32_t m_maxIndex { 0U };
        uint32_t m_currentBitPosition { 0U };
        MemberId m_currentMemberId { 0U };
        // This property contains a mapping from the member ID of a member of this (aggregated) type to the member itself.
        std::map<MemberId, DynamicTypeMember*> m_member { };
        // This property contains a mapping from the name of a member of this type to the member itself.
        std::map<std::string, DynamicTypeMember*> m_memberByName { };
        // This property provides all annotations that have previously been applied to this type with apply_annotation.
        std::vector<std::shared_ptr<AnnotationDescriptor> > m_annotation { };
        // This property contains all created DynamicTypeMember
        std::vector<std::shared_ptr<DynamicTypeMember> > m_memberCreated { }; 
    };
} // namespace xtypes
} // namespace dds

__GS_DDS4CPP_END_DECLS

#endif // GSTONE_DYNAMIC_TYPE_BUILDER_API_H_

