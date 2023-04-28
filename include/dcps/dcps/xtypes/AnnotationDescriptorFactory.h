/**************************************************************
* @file AnnotationDescriptorFactory.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_ANNOTATION_DESCRIPTOR_FACTORY_API_H_
#define GSTONE_ANNOTATION_DESCRIPTOR_FACTORY_API_H_ 1

#include <vector>
#include <mutex>

#include "AnnotationDescriptor.h"
#include "TypeKind.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace xtypes
{
    /**
     * @brief The sole purpose of this class is to apply the creation and destruction of AnnotationDescriptor objects.
     * AnnotationDescriptorFactory itself has no factory. It is a pre-existing singleton object that can be accessed by means of the
     * get_instance() class operation on the AnnotationDescriptorFactory.
     */
    class GS_DDS4CPP_API AnnotationDescriptorFactory final
    {
    public:
        /**
         * @brief Function to returns the AnnotationDescriptorFactory singleton.
         * @return AnnotationDescriptorFactory* The AnnotationDescriptorFactory singleton.
         */
        static AnnotationDescriptorFactory* get_instance();
        
        /**
         * @brief Function to delete the AnnotationDescriptorFactory singleton.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_OK when it is successfull, otherwise return DDS::ReturnCode_t::RETCODE_ERROR.
         */
        static DDS::ReturnCode_t delete_instance() noexcept;
        
        /**
         * @brief Function to create an annotation descriptor with kind and value.
         * @param [in] annotation_kind Annotation kind to be created.
         * @param [in] value Annotation value in string format.
         * @return std::shared_ptr<AnnotationDescriptor> The annotation descriptor that supported, otherwise result is null pointer.
         */
        std::shared_ptr<AnnotationDescriptor> create_annotation_descriptor(
            gstring_t const &annotation_kind, 
            gstring_t const &value);
        
        /**
         * @brief Function to create a "key" annotation descriptor. 
         * @return std::shared_ptr<AnnotationDescriptor> A "key" annotation descriptor.
         */
        std::shared_ptr<AnnotationDescriptor> create_annotation_descriptor_with_key();
        
        /**
         * @brief function to create a "id" annotation descriptor.
         * @param [in] PL_CDR_ID ID value in unsigned int16 range.
         * @return std::shared_ptr<AnnotationDescriptor> An "id" annotation descriptor.
         */
        std::shared_ptr<AnnotationDescriptor> create_annotation_descriptor_with_id(guint16_t const PL_CDR_ID);
        
        /**
         * @brief Function to create a "auto-id" annotation descriptor.
         * @param [in] type Auto id type, value is SEQUENTIAL or HASH(not supported now).
         * @return * std::shared_ptr<AnnotationDescriptor> An "auto-id" annotation descriptor.
         */
        std::shared_ptr<AnnotationDescriptor> create_annotation_descriptor_with_auto_id(
            dds::xtypes::AutoidKind const type = dds::xtypes::AutoidKind::SEQUENTIAL);
        
        /**
         * @brief Function to create an annotation descriptor with bitset position information.
         * @param [in] bitset_position Start position of this bitset member.
         * @return std::shared_ptr<AnnotationDescriptor> A bitset position annotation descriptor.
         */
        std::shared_ptr<AnnotationDescriptor> create_annotation_descriptor_with_bitset_position(
            uint32_t const bitset_position);
        
        /**
         * @brief Function to create an annotation descriptor with bitset bound information.
         * @param [in] bitset_bound Number of bits of this bitset member.
         * @return std::shared_ptr<AnnotationDescriptor> A bitset bound annotation descriptor.
         */
        std::shared_ptr<AnnotationDescriptor> create_annotation_descriptor_with_bitset_bound(
            uint32_t const bitset_bound);
        
        /**
         * @brief Function to create an annotation descriptor with only kind parameter.
         * @param [in] annotation_kind Annotation kind to be created.
         * @return std::shared_ptr<AnnotationDescriptor> A default annotation descriptor.
         */
        std::shared_ptr<AnnotationDescriptor> create_annotation_descriptor(gstring_t const &annotation_kind);
    
    private:
        /**
         * @brief Default constructor, Can not call this constructor outside.
         */
        AnnotationDescriptorFactory() = default;

        /**
         * @brief Default destructor, Can not call this constructor outside.
         *
         */
        ~AnnotationDescriptorFactory() = default;
        /**
         * @brief Copy constructor.
         * Deleted constructor, not used.
         * @param [in] x Reference to the object AnnotationDescriptorFactory that will be copied.
         */
        AnnotationDescriptorFactory(AnnotationDescriptorFactory const &x) = delete;
        
        /**
         * @brief Move constructor.
         * Deleted constructor, not used.
         * @param [in] x Reference to the object AnnotationDescriptorFactory that will be copied.
         */
        AnnotationDescriptorFactory(AnnotationDescriptorFactory &&x) = delete;
        
        /**
         * @brief Copy assignment.
         * Deleted assignment operator, not used.
         * @param [in] x Reference to the object AnnotationDescriptorFactory that will be copied.
         * @return AnnotationDescriptorFactory& Reference to the object AnnotationDescriptorFactory that to be assigned.
         */
        AnnotationDescriptorFactory& operator=(AnnotationDescriptorFactory const &x) = delete;
        
        /**
         * @brief Move assignment.
         * Deleted assignment operator, not used.
         * @param [in] x Reference to the object AnnotationDescriptorFactory that will be copied.
         * @return AnnotationDescriptorFactory& Reference to the object AnnotationDescriptorFactory that to be assigned.
         */
        AnnotationDescriptorFactory& operator=(AnnotationDescriptorFactory &&x) = delete;

        mutable std::recursive_mutex m_mutex_annotation_descriptors;
        std::vector<std::shared_ptr<AnnotationDescriptor> > m_annotation_descriptors;
    };
} // namespace xtypes
} // namespace dds

__GS_DDS4CPP_END_DECLS

#endif // GSTONE_ANNOTATION_DESCRIPTOR_FACTORY_API_H_

