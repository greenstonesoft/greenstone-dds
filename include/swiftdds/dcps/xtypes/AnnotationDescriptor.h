/**************************************************************
* @file AnnotationDescriptor.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_ANNOTATION_DESCRIPTOR_API_H_
#define GSTONE_ANNOTATION_DESCRIPTOR_API_H_ 1

#include <map>
#include <string>
#include <mutex>

#include "swiftdds/dcps/xtypes/TypeDefs.h"
#include "swiftdds/dcps/xtypes/DynamicType.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace xtypes
{
    class DynamicType;
    /**
     * @brief An AnnotationDescriptor packages together the state of an annotation as it is applied to some element (not an annotation type)
     * AnnotationDescriptor objects have value semantics, allowing them to be deeply copied and compared.
     */
    class GS_DDS4CPP_API AnnotationDescriptor final
    {
    public:
        /**
         * @brief Default constructor.
         */
        AnnotationDescriptor() = default;
        
        /**
         * @brief Default destructor.
         */
        ~AnnotationDescriptor() noexcept;
        
        /**
         * @brief Construct a new AnnotationDescriptor object with an AnnotationDescriptor pointer.
         * @param [in] descriptor Const pointer to the object AnnotationDescriptor that will be copied.
         */
        AnnotationDescriptor(AnnotationDescriptor const *const descriptor);
        
        /**
         * @brief Construct a new AnnotationDescriptor object with an AnnotationDescriptor smart pointer.
         * @param [in] descriptor Const smart pointer to the object AnnotationDescriptor that will be copied.
         */
        AnnotationDescriptor(std::shared_ptr<AnnotationDescriptor> const descriptor);
        
        /**
         * @brief Construct a new Annotation Descriptor object with an DynamicType smart pointer.
         * @param [in] pType  Const smart pointer to the object DynamicType that will be copied.
         */
        AnnotationDescriptor(std::shared_ptr<DynamicType> const pType) noexcept;
        
        /**
         * @brief Copy constructor.
         * This constructor has been deleted.
         * @param [in] x Reference to the object AnnotationDescriptor that will be copied.
         */
        AnnotationDescriptor(AnnotationDescriptor const &x) = delete;
        
        /**
         * @brief Move constructor.
         * This constructor has been deleted.
         * @param [in] x Reference to the object AnnotationDescriptor that will be copied.
         */
        AnnotationDescriptor(AnnotationDescriptor&& x) = delete;
        
        /**
         * @brief Copy assignment.
         * This assignment has been deleted.
         * @param [in] x Reference to the object AnnotationDescriptor that will be copied.
         * @return AnnotationDescriptor& Reference to the object AnnotationDescriptor that will be assigned.
         */
        AnnotationDescriptor& operator=(AnnotationDescriptor const &x) = delete;
        
        /**
         * @brief Move assignment.
         * This assignment has been deleted.
         * @param [in] x Reference to the object AnnotationDescriptor that will be copied.
         * @return AnnotationDescriptor& Reference to the object AnnotationDescriptor that will be assigned.
         */
        AnnotationDescriptor& operator=(AnnotationDescriptor &&x) = delete;
        
        /**
         * @brief Overwrite the contents of this descriptor with those of another descriptor such that subsequent calls to equals, 
         * passing the same argument as to this method, return true. The other descriptor shall not be changed by this operation.
         * @param [in] descriptor The descriptor whose contents are to be copied. If this argument is nil, the operation shall fail with DDS::ReturnCode_t::RETCODE_BAD_PARAMETER.
         * @return DDS::ReturnCode_t If this operation fails in an implementation-specific way, this operation shall return DDS::ReturnCode_t::RETCODE_ERROR.
         */
        DDS::ReturnCode_t copy_from(AnnotationDescriptor const *const descriptor);
        
        /**
         * @brief Two annotation descriptors ad1 and ad2 are considered equal if and only if all of the following apply:
         * 1 Their type properties refer to equal types.
         * 2 For every string s1 for which ad1.value[s1] does not exist, ad2.value[s1] also does not exist.
         * 3 For every string s1 for which ad2.value[s1] does not exist, ad1.value[s1] also does not exist.
         * 4 For every string s1 for which ad1.value[s1] is a non-nil string ad1-s2, ad2.value[s1] is a non-nil string ad2-s2 such that ad1-s2 equals ad2-s2.
         * 5 For every string s1 for which ad2.value[s1] is a non-nil string ad2-s2, ad1.value[s1] is a non-nil string ad1-s2 such that ad1-s2 equals ad2-s2.
         * @param [in] other Another descriptor to compare to this descriptor. If this argument is nil, this operation shall return false.
         * @return gbool_t True if two descriptors are identical, otherwise result is false.
         */
        gbool_t equals(AnnotationDescriptor const *const other) const;
        
        /**
         * @brief Indicate whether this descriptor describes a valid annotation type instantiation. 
         * An annotation descriptor is considered consistent if and only if all of the following qualities apply:
         * 1 The type property refers to a non-nil type of kind ANNOTATION_TYPE.
         * 2 For every pair of strings s1 and s2 such that value[s1] equals value[s2]:
         * 2.1 String s1 is the name of an attribute defined by the annotation type referred to by the type property.
         * 2.2 String s2 is a well-formed string representation of an object of the type of the attribute named by s1.
         * @return gbool_t True if this descriptors is consistent, otherwise result is false.
         */
        gbool_t is_consistent() const noexcept;

        /**
         * @brief Indicate whether this descriptor is a \@key descriptor.
         * @return True if this this descriptor is a \@key descriptor, otherwise result is false.
         */
        gbool_t const key_annotation() const;

        /**
         * @brief Indicate whether this descriptor is an \@optional descriptor.
         * @return True if this this descriptor is an \@optional descriptor, otherwise result is false.
         */
        gbool_t const optional_annotation() const;

        /**
         * @brief Indicate whether this descriptor is an \@id descriptor.
         * @return True if this this descriptor is an \@id descriptor, otherwise result is false.
         */
        gbool_t const at_id_annotation() const;
        
        /**
         * @brief Indicate whether this descriptor is an \@auto_id descriptor.
         * @return True if this this descriptor is an \@auto_id descriptor, otherwise result is false.
         */
        gbool_t const auto_id_annotation() const;
        
        /**
         * @brief Retrieves the value object which match the key parameter.
         * @param [in] value Descriptor value object where the value is returned.
         * @param [in] key Descriptor key to the target value.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_OK if satisfactory value is found, otherwise return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER.
         */
        DDS::ReturnCode_t get_value(gstring_t &value, gstring_t const &key);
        
        /**
         * @brief Retrieves the value object whose key is "key".
         * @param [in] value Descriptor value object where the value is returned.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_OK if satisfactory value is found, otherwise return DDS::ReturnCode_t::RETCODE_BAD_param [in]ETER.
         */
        DDS::ReturnCode_t get_value(gstring_t &value);
        
        /**
         * @brief Fills the value object with the value of this descriptor.
         * @param [in] value Value object where the descriptor value is returned.
         * @return DDS::ReturnCode_t::RETCODE_OK 
         */
        DDS::ReturnCode_t get_all_value(std::map<gstring_t, gstring_t> &value) const;
        
        /**
         * @brief Modifies the descriptor value whose key equals to key.
         * @param [in] key Key to find target value/s.
         * @param [in] value New value for the descriptor.
         * @return DDS::ReturnCode_t::RETCODE_OK 
         */
        DDS::ReturnCode_t set_value(gstring_t const &key, gstring_t const &value);
        
        /**
         * @brief Modifies the descriptor, set its type as _type.
         * @param [in] type New value for the descriptor type.
         */
        inline void set_type(std::shared_ptr<DynamicType> const type) noexcept
        {
            m_type = type;
        }
        
        /**
         * @brief Retrieves the type for this descriptor.
         * @return std::shared_ptr<DynamicType> const &Shared pointer to the type of this descriptor.
         */
        inline std::shared_ptr<DynamicType> const &get_type() const noexcept
        {
            return m_type;
        }
    private:
        /**
         * @brief Delegate constructor. Cannot call this constructor outside.
         * @param [in] type Type of the AnnotationDescriptor object to be constructed.
         * @param [in] value Value of the AnnotationDescriptor object to be constructed.
         */
        AnnotationDescriptor(std::shared_ptr<DynamicType> const type, std::map<gstring_t, gstring_t> const &value);

        mutable std::mutex m_mutex_value;
        std::shared_ptr<DynamicType> m_type;
        std::map<gstring_t, gstring_t> m_value;
    };
} // namespace xtypes
} // namespace dds

__GS_DDS4CPP_END_DECLS

#endif // GSTONE_ANNOTATION_DESCRIPTOR_API_H_

