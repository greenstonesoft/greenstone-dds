/**************************************************************
* @file MemberDescriptor.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_MEMBER_DESCRIPTOR_API_H_
#define GSTONE_MEMBER_DESCRIPTOR_API_H_ 1

#include <cstdint>
#include <vector>
#include <string>
#include <memory>

#include "swiftdds/dcps/xtypes/TypeDefs.h"
#include "swiftdds/dcps/xtypes/TypeKind.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace xtypes
{
    class DynamicType;
    class AnnotationDescriptor;
    /**
     * @brief A MemberDescriptor packages together the state of a DynamicTypeMember. MemberDescriptor 
     * objects have value semantics, allowing them to be deeply copied and compared.
     * @details Just as a TypeDescriptor describes the inner structure of a DynamicType, a MemberDescriptor 
     * stores all the information needed to manage a DynamicTypeMember, like their name, their unique ID, 
     * or the default value after the creation. This information is copied to the DynamicData on its creation.
     */
    class GS_DDS4CPP_API MemberDescriptor final
    {
    public:
        /**
        * @brief Default constructor.
        */
        MemberDescriptor();
        
        /**
         * @brief Construct a new MemberDescriptor object with another.
         * @param [in] other The pointer to another MemberDescriptor object.
         */
        MemberDescriptor(MemberDescriptor const *const other);
        
        /**
         * @brief Construct a new MemberDescriptor object with another.
         * @param [in] descriptor The smart pointer to another MemberDescriptor object.
         */
        MemberDescriptor(std::shared_ptr<MemberDescriptor> const descriptor);
        
        /**
         * @brief Construct a new MemberDescriptor object with index and name.
         * @param [in] _index The new MemberDescriptor object's index.
         * @param [in] name The new MemberDescriptor object's name.
         */
        MemberDescriptor(
            uint32_t const _index,
            std::string const &name);
        
        /**
         * @brief Construct a new MemberDescriptor object with member id, name and type.
         * @param [in] id The new MemberDescriptor object's member id.
         * @param [in] name The new MemberDescriptor object's name.
         * @param [in] _type The new MemberDescriptor object's type.
         */
        MemberDescriptor(
            MemberId const id,
            std::string const &name,
            std::shared_ptr<DynamicType> const _type);
        
        /**
         * @brief Construct a new MemberDescriptor object with member id, name type and default value.
         * @param [in] id The new MemberDescriptor object's member id.
         * @param [in] name The new MemberDescriptor object's name.
         * @param [in] _type The new MemberDescriptor object's type.
         * @param [in] union_labels The new MemberDescriptor object's union labels.
         * @param [in] is_default_label The new MemberDescriptor object's default lable flag.
         */
        MemberDescriptor(
            MemberId const id,
            std::string const &name,
            std::shared_ptr<DynamicType> const _type,
            std::vector<int64_t> const &union_labels,
            bool const is_default_label) noexcept;
        
        /**
         * @brief Construct a new MemberDescriptor object with member id, name type, default value,
         * union labels and "is default label" flag.
         * @param [in] id The new MemberDescriptor object's member id.
         * @param [in] name The new MemberDescriptor object's name.
         * @param [in] _type The new MemberDescriptor object's type.
         * @param [in] default_value The new MemberDescriptor object's default vaue.
         * @param [in] union_labels The new MemberDescriptor object's union labels.
         * @param [in] is_default_label The new MemberDescriptor object's default lable flag.
         */
        MemberDescriptor(
            MemberId const id,
            std::string const &name,
            std::shared_ptr<DynamicType> const _type,
            std::string const &default_value,
            std::vector<int64_t> const &union_labels,
            bool const is_default_label) noexcept;
        
        /**
         * @brief Destroy the current MemberDescriptor object.
         */
        ~MemberDescriptor() noexcept;
        
        /**
         * @brief Default copy constructor(deleted, do not use this).
         * @param [in] x Reference to the object MemberDescriptor that will be copied.
         */
        MemberDescriptor(MemberDescriptor const &x) = delete;
        
        /**
         * @brief Default move constructor(deleted, do not use this).
         * @param [in] x Reference to the object MemberDescriptor that will be copied.
         */
        MemberDescriptor(MemberDescriptor &&x) = delete;
        
        /**
         * @brief Default copy assignment(deleted, do not use this).
         * @param [in] x Reference to the object MemberDescriptor that will be copied.
         * @return MemberDescriptor& Reference to the object MemberDescriptor that will be assigned.
         */
        MemberDescriptor& operator=(MemberDescriptor const &x) = delete;
        
        /**
         * @brief Default move assignment(deleted, do not use this).
         * @param [in] x Reference to the object MemberDescriptor that will be copied.
         * @return MemberDescriptor& Reference to the object MemberDescriptor that will be assigned.
         */
        MemberDescriptor& operator=(MemberDescriptor &&x) = delete;
    public:
        
        /**
         * @brief Overwrite the contents of this descriptor with those of another descriptor such that 
         * subsequent calls to equals, passing the same argument as to this method, return true. 
         * The other descriptor shall not be changed by this operation.
         * @param [in] other The descriptor whose contents are to be copied.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER If this argument is nil.
         * @return DDS::ReturnCode_t::RETCODE_ERROR If this operation fails in an implementation-specific way
         */
        DDS::ReturnCode_t copy_from(MemberDescriptor const *const other);
        
        /**
         * @brief This function tells you whether one member descriptor is equals to another.
         * @param [in] other Another descriptor to compare to this one.
         * @return true If and only if the values of all of the properties are equal in each of them.
         * @return false If this argument is nil or not equal to each other.
         */
        bool equals(MemberDescriptor const *const other) const;
        
        /**
         * @brief This function tells you if a descriptor with specified kind is consistent or not.
         * @param [in] parent_kind The kind of type to check.
         * @return true A descriptor shall be considered consistent if and only if all of the values 
         * of its properties are considered consistent.
         * @return false Kind is not valid or type is not consitent.
         */
        bool is_consistent(TypeKind const parent_kind) const noexcept;
    public:
        
        /**
         * @brief This function sets the current member descriptor's member id.
         * @param [in] id New member id for the member descriptor.
         */
        inline void set_id(MemberId const id) noexcept
        {
            m_id = id;
        }
        
        /**
         * @brief This function returns the current member descriptor's member id.
         * @return MemberId Member id of this member descriptor.
         */
        inline MemberId get_id() const noexcept
        {
            return m_id;
        }
        
        /**
         * @brief This function sets the current member descriptor's index.
         * @param [in] _index New index for the member descriptor.
         */
        inline void set_index(uint32_t const _index) noexcept
        {
            m_index = _index;
        }
        
        /**
         * @brief This function returns the current member descriptor's index.
         * @return uint32_t Index id of this member descriptor.
         */
        inline uint32_t get_index() const noexcept
        {
            return m_index;
        }
        
        /**
         * @brief This function sets the current member descriptor's name.
         * @param [in] name New name for the member descriptor.
         */
        inline void set_name(std::string const &name) noexcept
        {
            m_name = name;
        }
        
        /**
         * @brief This function returns the current member descriptor's name.
         * @return std::string Name id of this member descriptor.
         */
        inline std::string get_name() const noexcept
        {
            return m_name;
        }
        
        /**
         * @brief This function sets the current member descriptor's type.
         * @param [in] type New type for the member descriptor.
         */
        inline void set_type(std::shared_ptr<DynamicType> const type) noexcept
        {
            m_type = type;
        }
        
        /**
         * @brief This function returns the current member descriptor's type.
         * @return std::shared_ptr<DynamicType> const &Type of this member descriptor.
         */
        inline std::shared_ptr<DynamicType> const &get_type() const noexcept
        {
            return m_type;
        }
        
        /**
         * @brief This function tells you if the type member is a union type's default option.
         * @return true If it is the default option of a union.
         * @return false If it is not the default option of a union.
         */
        inline bool is_default_union_value() const noexcept
        {
            return m_isDefaultLabel;
        }
        
        /**
         * @brief This function returns the labels of a union type.
         * @return std::vector<uint64_t> Case Labels for unions.
         */
        inline std::vector<int64_t> get_union_labels() const
        {
            return m_label;
        }
        
        /**
         * @brief This function returns the default value of current member.
         * @return std::string Default value of the member in string.
         */
        inline std::string get_default_value() const 
        {
            return m_defaultValue; 
        }
        
        /**
         * @brief This function sets the current member descriptor's default value.
         * @param [in] value New default value for the member descriptor.
         */
        inline void set_default_value(std::string const &value)
        {
            m_defaultValue = value;
        }
        
        /**
         * @brief This function sets the current member descriptor's default label.
         * @param [in] default_label Flag that current member descriptor is union default lable or not.
         */
        inline void set_default_union_value(bool const default_label) noexcept
        {
            m_isDefaultLabel = default_label;
        }
        
        /**
         * @brief This operation returns all of the existed annotation/s to apply.
         * @return std::vector<std::shared_ptr<AnnotationDescriptor> > const &Reference to the annotation descriptor.
         */
        inline std::vector<std::shared_ptr<AnnotationDescriptor> > const &get_annotation() const noexcept
        {
            return m_annotation;
        }
        
        /**
         * @brief This function returns the type kind of current member.
         * @return TypeKind Kind of this member descriptor.
         */
        TypeKind get_kind() const noexcept;
        
        /**
         * @brief Check labels is valid in curent member descriptor.
         * @param [in] labels Labels to check.
         * @return true If anyone in labels can be found in this descriptor's labels.
         * @return false None of labels can be found in this descriptor's labels.
         */
        bool check_union_labels(std::vector<int64_t> const &labels) const noexcept;
        
        /**
         * @brief Add a valid union label to this descriptor's labels.
         * @param [in] value New union label for this descriptor.
         */
        void add_union_case_index(int64_t const value);
        
        /**
         * @brief This operation checks whether or not this member is with \@id.
         * @return true If this type is annotated by an \@id annotation.
         * @return false If this type is not annotated by an \@id annotation.
         */
        bool is_at_id_member() const;
        
        /**
         * @brief This function get the id value of an type if it has an \@id annotation.
         * @return uint16_t ID value of the existed \@id annotation
         */
        uint16_t annotation_get_id() const;
        
        /**
         * @brief This operation returns the annotation that corresponds to the specified name, if any.
         * @param [in] name Name of the wanted descriptor. 
         * @return AnnotationDescriptor* Descriptor value object where the value is returned.
         */
        AnnotationDescriptor* get_annotation(std::string const &name) const;
        
        /**
         * @brief Apply the given annotation to this type. It shall subsequently appear in the annotation property.
         * @param [in] descriptor Consistent descriptor for the annotation to apply.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if this argument descriptor is not consistent.
         */
        DDS::ReturnCode_t apply_annotation(AnnotationDescriptor const &descriptor);

        /**
         * @brief This operation checks whether or not this member is with \@key.
         * @return true If this member is annotated by a \@key annotation.
         * @return false If this member is not annotated by a \@key annotation.
         */
        bool const is_key_member() const noexcept
        {
            return m_isKey;
        }

        /**
         * @brief This operation checks whether or not this member is with \@optional.
         * @return true If this member is annotated by an \@optional annotation.
         * @return false If this member is not annotated by an \@optional annotation.
         */
        bool const is_optional_member() const noexcept
        {
            return m_isOptional;
        }

        /**
         * @brief This operation checks whether or not this member is set with a value.
         * @return true If this member is set.
         * @return false If this member is not set.
         */
        bool const is_set() const noexcept
        {
            return m_isSet;
        }

        /**
         * @brief Change the set flag of this member.
         * @param [in] flag New value for the flag.
         */
        void change_set_state(bool const flag) noexcept
        {
            m_isSet = flag;
        }
    
    private:
        /**
        * @brief Delegating constructor, used by other constructors.
        * @param [in] name The new MemberDescriptor object's name.
        * @param [in] id The new MemberDescriptor object's member id.
        * @param [in] type The new MemberDescriptor object's type.
        * @param [in] default_value The new MemberDescriptor object's default_value.
        * @param [in] _index The new MemberDescriptor object's index.
        * @param [in] labels The new MemberDescriptor object's labels.
        * @param [in] key The new MemberDescriptor object's key flag.
        * @param [in] optional The new MemberDescriptor object's optional flag.
        * @param [in] default_label The new MemberDescriptor object's default_label flag.
        * @param [in] set The new MemberDescriptor object's set value flag.
        * @param [in] annotation The new MemberDescriptor object's annotation.
        */
        MemberDescriptor(
            std::string const &name,
            MemberId const id,
            std::shared_ptr<DynamicType> const type,
            std::string const &default_value,
            uint32_t const _index,
            std::vector<int64_t> const &labels,
            bool const key,
            bool const optional,
            bool const default_label,
            bool const set,
            std::vector<std::shared_ptr<AnnotationDescriptor> > const &annotation
        ) noexcept;

        std::string m_name;                                                         // Name of the member
        MemberId m_id;                                                              // MemberId, it should be filled automatically when the member is added.
        std::shared_ptr<DynamicType> m_type;                                        // Member's Type.
        std::string m_defaultValue;                                                 // Default value of the member in string.
        uint32_t m_index;                                                           // Definition order of the member inside it's parent.
        std::vector<int64_t> m_label;                                               // Case Labels for unions.
        bool m_isKey;                                                               // TRUE if this member is part of the key for the objects.
        bool m_isOptional;                                                          // TRUE if this the element is set as optional 
        bool m_isDefaultLabel;                                                      // TRUE if it's the default option of a union.
        bool m_isSet;                                                               // TRUE if this has been set value.
        std::vector<std::shared_ptr<AnnotationDescriptor> > m_annotation;           // Annotations to apply
    };
} // namespace xtypes
} // namespace dds

__GS_DDS4CPP_END_DECLS

#endif // GSTONE_MEMBER_DESCRIPTOR_API_H_

