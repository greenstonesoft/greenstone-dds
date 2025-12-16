/**************************************************************
* @file DynamicTypeMember.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_DYNAMIC_TYPE_MEMBER_API_H_
#define GSTONE_DYNAMIC_TYPE_MEMBER_API_H_ 1

#include <vector>
#include <string>

#include "swiftdds/dcps/xtypes/TypeDefs.h"
#include "swiftdds/dcps/xtypes/MemberDescriptor.h"
#include "swiftdds/dcps/xtypes/AnnotationDescriptor.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace xtypes
{
    class DynamicType;
    class AnnotationDescriptor;
    class MemberDescriptor;
    using DynamicType_Ptr = std::shared_ptr<DynamicType>;
    /**
     * @brief A DynamicTypeMember represents a "member" of a type. A "member" in this sense may be a 
     * member of an aggregated type, a constant within an enumeration, or some other type substructure.
     * @details Represents a data member of a DynamicType that is also a DynamicType. Compound types 
     * (dynamic types that are composed of other dynamic types) have a DynamicTypeMember for every 
     * child DynamicType added to it.
     */
    class GS_DDS4CPP_API DynamicTypeMember final
    {
    public:
        /**
         * @brief Default constructor.
         */
        DynamicTypeMember();
        
        /**
         * @brief Construct a new DynamicTypeMember object with another.
         * @param [in] other The pointer to another DynamicTypeMember object.
         */
        DynamicTypeMember(DynamicTypeMember const *const other);
        
        /**
         * @brief Construct a new DynamicTypeMember object wiht the MemberDescriptor object.
         * @param [in] descriptor The properties of the new type member to create.
         * @param [in] id The member id of the new type member to create.
         */
        DynamicTypeMember(MemberDescriptor const *const descriptor, MemberId const id);
        
        /**
         * @brief Destroy the current DynamicTypeMember object
         */
        ~DynamicTypeMember() noexcept;
        
        /**
         * @brief Copy assignment.
         * @param [in] x Reference to the object DynamicTypeMember that will be copied.
         * @return DynamicTypeMember& Reference to the object DynamicTypeMember that will be assigned.
         */
        DynamicTypeMember& operator=(DynamicTypeMember const &x) &;
        
        /**
         * @brief Default Move assignment.
         * @param [in] x Reference to the object DynamicTypeMember that will be copied.
         * @return DynamicTypeMember& Reference to the object DynamicTypeMember that will be assigned.
         */
        DynamicTypeMember& operator=(DynamicTypeMember &&x) = default;
        
        /**
         * @brief Default copy constructor(deleted, do not use this).
         * @param [in] x Reference to the object DynamicTypeMember that will be copied.
         */
        DynamicTypeMember(DynamicTypeMember const &x) = delete;
        
        /**
         * @brief Default move constructor(deleted, do not use this).
         * @param [in] x Reference to the object DynamicTypeMember that will be copied.
         */
        DynamicTypeMember(DynamicTypeMember &&x) = delete;
    public:
        /**
         * @brief This operation provides a summary of the state of this type. 
         * It overwrites the state of an application-provided object.
         * @param [in,out] descriptor MemberDescriptor value object where the value is returned.
         * @return DDS::ReturnCode_t If the argument is nil, this operation shall fail with DDS::ReturnCode_t::RETCODE_BAD_PARAMETER.
         */
        DDS::ReturnCode_t get_descriptor(MemberDescriptor *const descriptor) const;
        
        /**
         * @brief This function tells you that if one type member equals to another or not.
         * @param [in] other Another type member to be compared.
         * @return true if and only if they belong to the same type and all of their respective properties are equal.
         * @return false if they belong to the different type or have different properties.
         */
        bool equals(DynamicTypeMember const *const other) const;
        
        /**
         * @brief This convenience operation provides the member ID of this member.
         * Result shall be identical to the ID value that is a member of the descriptor property.
         * @return MemberId Member ID of the current type member.
         */
        MemberId get_id() const noexcept;
        
        /**
         * @brief This convenience operation provides the name of this member.
         * Its result shall be identical to the name string that is a member of the descriptor property.
         * @return std::string Name of the current type member.
         */
        std::string get_name() const noexcept;

        /**
        * @brief This operation checks whether or not the given type is a key type.
        * @return true If this type is annotated by a \@key annotation.
        * @return false If this type is not annotated by a \@key annotation.
        */
        bool is_key_member() const noexcept;
        
        /**
         * @brief Apply the given annotation to this type. It shall subsequently appear in the annotation property.
         * @param [in] descriptor Consistent descriptor for the annotation to apply.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if this argument descriptor is not consistent.
         */
        DDS::ReturnCode_t apply_annotation(AnnotationDescriptor const &descriptor);
        
        /**
         * @brief This operation returns the annotation that corresponds to the specified index, if any.
         * @param [in, out] descriptor Descriptor value object where the value is returned.
         * @param [in] _index Index of the wanted descriptor. 
         * @return DDS::ReturnCode_t  DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if the specified index is greater than the current annotation count.
         */
        DDS::ReturnCode_t get_annotation(AnnotationDescriptor& descriptor, uint32_t const _index) const;
        
        /**
         * @brief This operation returns the current number of annotations applied to the type.
         * @return uint32_t If no annotation was applied, result is zero. 
         */
        uint32_t get_annotation_count() const noexcept;
        
        /**
         * @brief This convenience operation indicates the kind of this type (e.g., integer, structure, etc.).
         *  Its result shall be the same as the kind indicated by the descriptor property.
         * @return TypeKind Kind of this type
         */
        TypeKind get_kind() const noexcept;
        
        /**
         * @brief This function tells you if the type member is a union type's default option.
         * @return true If it is the default option of a union.
         * @return false If it is not the default option of a union.
         */
        bool is_default_union_value() const noexcept;
        
        /**
         * @brief This function returns the labels of a union type.
         * @return std::vector<uint64_t> Case Labels for unions.
         */
        std::vector<int64_t> get_union_labels() const;
        
        /**
         * @brief This function sets the index value.
         * @param [in] _index New value for the index.
         */
        inline void set_index(uint32_t const _index) noexcept
        {
            m_descriptor.set_index(_index);
        }
        
        /**
         * @brief This function returns the index of a type member.
         * @return uint32_t Definition order of the member inside it's parent
         */
        inline uint32_t get_index() const noexcept
        {
            return m_descriptor.get_index();
        }
        
        /**
         * @brief This function returns the descriptor of a type member.
         * @return MemberDescriptor const* const Pointer to the type member's descriptor.
         */
        inline MemberDescriptor const *const get_descriptor() const noexcept
        {
            return &m_descriptor;
        }
        
        /**
         * @brief This operation provides a summary of the state of this type. \n
         * It overwrites the state of an application-provided object.
         * @param [in,out] descriptor MemberDescriptor value object where the value is returned.
         * @return DDS::ReturnCode_t If the argument is nil, this operation shall fail with DDS::ReturnCode_t::RETCODE_BAD_PARAMETER.
         */
        DDS::ReturnCode_t get_descriptor(std::shared_ptr<MemberDescriptor> descriptor) const;
        
        /**
         * @brief This function sets the parent type of current type member.
         * @param [in] parent If current type member is not a child, parent type is nil.
         */
        inline void set_parent(DynamicType *const parent) noexcept
        {
            m_parent = parent;
        }
        
        /**
         * @brief This operation checks whether or not the given type is a key type.
         * @return true If this type is annotated by a \@key annotation.
         * @return false If this type is not annotated by a \@key annotation.
         */
        bool is_with_key() const noexcept;

        inline DynamicType_Ptr get_type() const noexcept
        {
            return m_descriptor.get_type();
        }
    private:
        DynamicType* m_parent;
        MemberDescriptor m_descriptor;
        MemberId m_id;
        std::vector<std::shared_ptr<AnnotationDescriptor> > m_annotation;
    };
} // namespace xtypes
} // namespace dds

__GS_DDS4CPP_END_DECLS

#endif // GSTONE_DYNAMIC_TYPE_MEMBER_API_H_

