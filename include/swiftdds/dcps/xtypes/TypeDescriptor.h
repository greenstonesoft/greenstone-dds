/**************************************************************
* @file TypeDescriptor.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_TYPE_DESCRIPTOR_API_H_
#define GSTONE_TYPE_DESCRIPTOR_API_H_ 1

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include "swiftdds/dcps/xtypes/TypeDefs.h"
#include "swiftdds/dcps/xtypes/TypeKind.h"
#include "swiftdds/dcps/xtypes/AnnotationDescriptor.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace xtypes
{
    class DynamicType;
    using DynamicType_Ptr = std::shared_ptr<DynamicType>;
    /**
     * @brief A TypeDescriptor packages together the state of a type. TypeDescriptor objects have value semantics,
     * allowing them to be deeply copied and compared.
     * @details Stores the information about one type with its relationships and restrictions. This is the class 
     * that describes the inner structure of a DynamicType. The DynamicTypeBuilder has an internal instance of 
     * TypeDescriptor that modifies during the type building process. When the DynamicType is created, the 
     * DynamicTypeBuilderFactory uses the information of the TypeDescriptor in the builder to create the DynamicType.
     * During the creation, the TypeDescriptor is copied to the DynamicType, so that it becomes independent from 
     * the DynamicTypeBuilder, and the builder can be reused for another type.
     */
    class GS_DDS4CPP_API TypeDescriptor final
    {
    public:
        /**
         * @brief Construct a new TypeDescriptor object with another object.
         * @param [in] other Pointer to the TypeDescriptor object to copy.
         */
        TypeDescriptor(TypeDescriptor const *const other);
 
        /**
         * @brief Construct a new TypeDescriptor object with another object.
         * @param [in] other Smart pointer to the TypeDescriptor object to copy.
         */
        TypeDescriptor(std::shared_ptr<TypeDescriptor> const other);
 
        /**
         * @brief Construct a new TypeDescriptor object with given name and kind.
         * @param [in] name The new TypeDescriptor object's name.
         * @param [in] kind The new TypeDescriptor object's type kind.
         */
        TypeDescriptor(std::string const &name, TypeKind const kind);
 
        /**
         * @brief Destructor for the TypeDescriptor objects.
         */
        ~TypeDescriptor() noexcept;
 
        /**
         * @brief Overwrite the contents of this descriptor with those of another descriptor such that subsequent
         * calls to equals, passing the same argument as to this method, return true. The other descriptor
         * shall not be changed by this operation.
         * @param [in] other The descriptor whose contents are to be copied.
         * @return DDS::ReturnCode_t::RETCODE_ERROR if an error occurs.
         * @return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if this other argument is nil.
         * @return DDS::ReturnCode_t::RETCODE_OK if the operation is done.
         */
        DDS::ReturnCode_t copy_from(TypeDescriptor const *const other);
 
        /**
         * @brief This function tells you if one type descriptor is identical to another.
         * @param [in] other Another descriptor to compare to this one.
         * @return true If and only if the values of all of the properties are equal in each of them.
         * @return false At least one of the properties is not equal in each of them or other is nil.
         */
        bool equals(TypeDescriptor const *const other) const;
 
        /**
         * @brief This function tells you if this type descriptor is consistent or not.
         * @return true If all of this descriptor's properties are consistent.
         * @return false At least one of the current descriptor's property is not consistent.
         */
        bool is_consistent() const noexcept;

        /**
         * @brief Default constructor.
         */
        TypeDescriptor() = default;
 
        /**
         * @brief Default copy constructor(deleted, do not use it).
         * @param [in] x Reference to the object TypeDescriptor that will be copied.
         */
        TypeDescriptor(TypeDescriptor const &x) = delete;
 
        /**
         * @brief Default move constructor(deleted, do not use it).
         * @param x Reference to the object TypeDescriptor that will be copied.
         */
        TypeDescriptor(TypeDescriptor&& x) = delete;
 
        /**
         * @brief Default copy assignment(deleted, do not use it).
         * @param [in] x Reference to the object TypeDescriptor that will be copied.
         * @return TypeDescriptor& Reference to the object TypeDescriptor that will be assigned.
         */
        TypeDescriptor& operator=(TypeDescriptor const &x) = delete;
 
        /**
         * @brief Default move assignment(deleted, do not use it).
         * @param [in] x Reference to the object TypeDescriptor that will be copied.
         * @return TypeDescriptor& Reference to the object TypeDescriptor that will be assigned.
         */
        TypeDescriptor& operator=(TypeDescriptor&& x) = delete;
 
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
         * @brief This function sets the current type descriptor's type kind.
         * @param [in] kind New type kind for this type descriptor.
         */
        inline void set_kind(TypeKind const kind) noexcept
        {
            m_kind = kind;
        } 
 
        /**
         * @brief This convenience operation provides the fully qualified name of this type.
         * It shall be identical to the name string that is a member of the descriptor property.
         * @return std::string Type descriptor's fully qualified name.
         */
        inline std::string get_name() const noexcept
        {
            return m_name;
        }
 
        /**
         * @brief This function sets the current type descriptor's name.
         * @param [in] name New name for this type descriptor.
         */
        inline void set_name(std::string const &name) noexcept
        {
            m_name = name;
        }
 
        /**
         * @brief Get this type's base type.
         * If this type is a structure type, base_type indicates the supertype of that type. 
         * A nil value of this property indicates that the structure type has no supertype.
         * If this type represents an alias type, base_type indicates the type being aliased. 
         * A nil value for this property is not considered consistent.
         * In all other cases, a consistent descriptor shall have a nil value for this property.
         * @return DynamicType_Ptr Smart pointer to the base type.
         */
        inline DynamicType_Ptr const &get_base_type() const noexcept
        {
            return m_baseType;
        }
 
        /**
         * @brief This function sets the current type descriptor's base type.
         * Only a structure type or an alias type has a no-nil base-type.
         * @param [in] in_type New base type for this type.
         */
        inline gvoid_t set_base_type(DynamicType_Ptr const &in_type) noexcept
        {
            m_baseType = in_type;
        }
 
        /**
         * @brief Get this type's element type.
         * If this type is an array, sequence, or string type, this property indicates the element type of the collection. 
         * It must not be nil for the descriptor to be consistent.
         * If this type is a map type, this property indicates the value element type of the map. 
         * It must not be nil for the descriptor to be consistent.
         * If this type is a bitmask type, this property must indicate a Boolean type for the descriptor to be consistent.
         * If this type is any other kind of type, this property must be nil for the descriptor to be consistent.
         * @return DynamicType_Ptr Smart pointer to the element type.
         */
        inline DynamicType_Ptr const &get_element_type() const noexcept
        {
            return m_elementType;
        }
 
        /**
         * @brief This function sets the current type descriptor's element type.
         * An element type only exists in an array, sequence, string map or bitmask type.
         * @param [in] in_type New element type for this type.
         */
        inline gvoid_t set_element_type(DynamicType_Ptr const &in_type) noexcept
        {
            m_elementType = in_type;
        }
 
        /**
         * @brief Get this type's key type.
         * If this type is a map type, this property indicates the value element type of the map. 
         * It must not be nil for the descriptor to be consistent.
         * If this type is any other kind of type, this property must be nil for the descriptor to be consistent.
         * @return DynamicType_Ptr Smart pointer to the map type.
         */
        inline DynamicType_Ptr const &get_key_element_type() const noexcept
        {
            return m_keyElementType;
        }
 
        /**
         * @brief This function sets the current type descriptor's key element type.
         * An element type only exists in a map type.
         * @param [in] in_type New key element type for this type.
         */
        inline gvoid_t set_key_element_type(DynamicType_Ptr const &in_type) noexcept
        {
            m_keyElementType = in_type;
        }
 
        /**
         * @brief Get this type's discriminator type.
         * If this type is a union type, discriminator_type indicates the type of the discriminator of the union. 
         * It must not be nil for the descriptor to be consistent.
         * If this type is any other kind of type, 
         * this property must be nil for this descriptor to be consistent.
         * @return DynamicType_Ptr Smart pointer to the discriminator type.
         */
        inline DynamicType_Ptr const &get_discriminator_type() const noexcept
        {
            return m_discriminatorType;
        }
 
        /**
         * @brief This function sets the current type descriptor's discriminator type.
         * An element type only exists in a union type.
         * @param [in] in_type New discriminator type for this type.
         */
        inline gvoid_t set_discriminator_type(DynamicType_Ptr const &in_type) noexcept
        {
            m_discriminatorType = in_type;
        }
 
        /**
         * @brief This operation returns all of the annotation descriptor/s.
         * @return std::vector<std::shared_ptr<AnnotationDescriptor> > const &Descriptor value objects where the value is returned.
         */
        inline std::vector<std::shared_ptr<AnnotationDescriptor> > const &get_annotation() const noexcept
        {
            return m_annotation;
        }
 
        /**
         * @brief Implement an FSM string parser to deal with both a plain type name and a fully qualified name.
         * According to the DDS xtypes standard, type's fully qualified name is a concatenation of module names with
         * the name of a type inside of those modules.
         * @param [in] a_name 
         * @return true If this name is consistent.
         * @return false If this name is not consistent.
         */
        static bool is_type_name_consistent(std::string const &a_name) noexcept;
 
        /**
         * @brief Get the bound of the corresponding dimension.
         * @param [in] a_index Dimension of the type bound.
         * @return guint32_t Bound size specified by dimension.
         */
        uint32_t get_bounds(uint32_t const a_index = 0U) const noexcept;
 
        /**
         * @brief Get the dimension of bound.
         * @return guint32_t Get dimensions of type bound.
         */
        uint32_t get_bounds_size() const noexcept;
 
        /**
         * @brief Get the total bounds indicating the bound of collection and similar types.
         * If this descriptor represents an array type, the length of the property value indicates the number of
         * dimensions in the array, and each value indicates the bound of the corresponding dimension.
         * If this descriptor represents a sequence, map, bitmask, or string type, the length of the property value
         * is one and the integral value in that property indicates the bound of the collection.
         * @return guint32_t A nil value for the bound property in all other cases.
         */
        uint32_t get_total_bounds() const noexcept;
 
        /**
         * @brief This operation returns the annotation that corresponds to the specified name, if any.
         * @param [in] name Name of the wanted descriptor.
         * @return AnnotationDescriptor* Descriptor value object where the value is returned.
         */
        AnnotationDescriptor *get_annotation(std::string const &name) const;
 
        /**
         * @brief Apply the given annotation to this type. It shall subsequently appear in the annotation property.
         * @param [in,out] descriptor Consistent descriptor for the annotation to apply.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if this argument descriptor is not consistent.
         */
        DDS::ReturnCode_t apply_annotation(AnnotationDescriptor const &descriptor);
 
        /**
         * @brief This operation add a new bound to this descriptor.
         * @param in_bound New bound for the descriptor.
         */
        inline gvoid_t set_bound(uint32_t const &in_bound)
        {
            m_bound.push_back(in_bound);
        }
 
        /**
         * @brief This operation reset new bound/s to this descriptor.
         * @param in_bound New bound/s for the descriptor.
         */
        inline gvoid_t set_all_bound(std::vector<uint32_t> const &in_bound)
        {
            m_bound = in_bound;
        }
    private:
        /**
         * @brief Clean all properties and release the resource. Cannot use outside
         */
        void clean() noexcept;
 
        /**
         * @brief Delegating constructor, used by other constructors.Cannot use outside
         * @param [in] kind The new TypeDescriptor object's type kind.
         * @param [in] name The new TypeDescriptor object's name.
         * @param [in] base_type The new TypeDescriptor object's base type.
         * @param [in] discriminator_type The new TypeDescriptor object's discriminator type.
         * @param [in] element_type The new TypeDescriptor object's element type.
         * @param [in] key_element_type The new TypeDescriptor object's key element type.
         * @param [in] bound The new TypeDescriptor object's bound/s.
         * @param [in] annotation The new TypeDescriptor object's annotation/s
         */
        TypeDescriptor(
            TypeKind const kind,
            std::string const &name,
            DynamicType_Ptr const base_type,
            DynamicType_Ptr const discriminator_type,
            DynamicType_Ptr const element_type,
            DynamicType_Ptr const key_element_type,
            std::vector<uint32_t> const &bound,
            std::vector<std::shared_ptr<AnnotationDescriptor> > const &annotation
        );

        TypeKind m_kind;
        std::string m_name;
        DynamicType_Ptr m_baseType;
        DynamicType_Ptr m_discriminatorType;
        DynamicType_Ptr m_elementType;
        DynamicType_Ptr m_keyElementType;
        std::vector<uint32_t> m_bound;
        std::vector<std::shared_ptr<AnnotationDescriptor> > m_annotation;
    };
} // namespace xtypes
} // namespace dds

__GS_DDS4CPP_END_DECLS

#endif // GSTONE_TYPE_DESCRIPTOR_API_H_

