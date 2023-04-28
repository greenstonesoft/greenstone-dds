/**************************************************************
* @file DynamicDataFactory.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_DYNAMIC_DATA_FACTORY_API_H_
#define GSTONE_DYNAMIC_DATA_FACTORY_API_H_ 1

#include <memory>

#include "TypeDefs.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace xtypes
{
    class DynamicTypeBuilder;
    class DynamicData; 
    class DynamicType;
    using DynamicType_ptr = std::shared_ptr<DynamicType>;
    /**
     * @brief This class is logically a singleton which is the starting point for creating and deleting DynamicData and objects.
     * @details Singleton class that is in charge of the creation and the management of every DynamicData.
     * It can take a DynamicType and create an instance of a corresponding DynamicData.
     * Every data object created by the factory must be deleted to avoid memory leaking.
     */
    class GS_DDS4CPP_API DynamicDataFactory final
    {
    public:
        /**
         * @brief Function to return a DynamicDataFactory instance that behaves like a singleton,
         * although callers cannot assume pointer equality across invocations of this operation. 
         * It is legal to call this operation even after delete_instance has been called.
         * In such a case, the implementation shall recreate or restore the "singleton" as 
         * necessary to ensure that it can return a valid object to the caller.
         * @return DynamicDataFactory* A raw pointer to the DynamicDataFactory singleton instance.,
         * or a nil value if an error occurs.
         */
        static DynamicDataFactory* get_instance();
        
        /**
         * @brief Reclaim any resources associated with the object(s) previously returned from get_instance.
         * @return DDS::ReturnCode_t::RETCODE_OK when it is successfull. 
         * @return DDS::ReturnCode_t::RETCODE_ERROR if it fails for any implementation-specific reason.
         */
        static DDS::ReturnCode_t delete_instance() noexcept;
        
        /**
         * @brief Create and return a new data sample. All objects returned by this operation should eventually be deleted by calling delete_data.
         * @param [in] pType The type of the sample to create.
         * @return std::shared_ptr<DynamicData> Smart pointer to the created dynamic data based on specified dynamic type
         */
        std::shared_ptr<DynamicData> create_data(DynamicType_ptr pType);
        
        /**
         * @brief Dispose of a data sample, reclaiming any associated resources.
         * @param [in] pData The data sample to delete.
         * @return DDS::ReturnCode_t return DDS::ReturnCode_t::RETCODE_ERROR if a successful deletion, otherwise get DDS::ReturnCode_t::RETCODE_ERROR.
         */
        static DDS::ReturnCode_t delete_data(std::shared_ptr<DynamicData> pData) noexcept;
        
        /**
         * @brief Function to create a copy of the given dynamic data.
         * Use this method to get a duplication of an existed dynamic data.
         * @param [in] pData Smart pointer to the dynamic data to be copied.
         * @return std::shared_ptr<DynamicData> Smart pointer to the new dynamic data.
         */
        static std::shared_ptr<DynamicData> create_copy(std::shared_ptr<DynamicData> const pData);
         
        /**
         * @brief Function to create a copy of the given dynamic data.
         * Use this method to get a duplication of an existed dynamic data.
         * @param [in] pData Pointer to the dynamic data to be copied.
         * @return std::shared_ptr<DynamicData> Pointer to the new dynamic data.
         */
        static std::shared_ptr<DynamicData> create_copy(DynamicData const *const pData);
        
        /**
         * @brief Create a MemberId-MemberDescriptor map of a dynamic data with given type.
         * @param [in] pData Pointer to the data not having descriptor. 
         * @param [in] pType Related type to the dynamic data.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if failded, otherwise return DDS::ReturnCode_t::RETCODE_OK.
         */
        DDS::ReturnCode_t create_members(DynamicData *const pData, DynamicType_ptr pType);
        
        /**
         * @brief Create a MemberId-MemberDescriptor map of a dynamic data with given type.
         * @param [in] pData Pointer to the data not having descriptor. 
         * @param [in] pType Related type to the dynamic data.
         * @return DDS::ReturnCode_t DDS::ReturnCode_t::RETCODE_BAD_PARAMETER if failded, otherwise return DDS::ReturnCode_t::RETCODE_OK.
         */
        DDS::ReturnCode_t create_members(std::shared_ptr<DynamicData> const pData, DynamicType_ptr pType);
        
        /**
         * @brief Copy constructor.
         * Deleted constructor, not used.
         * @param [in] x Reference to the object DynamicDataFactory that will be copied.
         */
        DynamicDataFactory(DynamicDataFactory const &x) = delete;
        
        /**
         * @brief Move constructor.
         * Deleted constructor, not used.
         * @param [in] x Reference to the object DynamicDataFactory that will be copied.
         */
        DynamicDataFactory(DynamicDataFactory &&x) = delete;
        
        /**
         * @brief Copy assignment.
         * Deleted assignment operator, not used.
         * @param [in] x Reference to the object DynamicDataFactory that will be copied.
         * @return DynamicDataFactory &Reference to the object DynamicDataFactory that to be assigned.
         */
        DynamicDataFactory &operator=(DynamicDataFactory const &x) = delete;
        
        /**
         * @brief Move assignment.
         * Deleted assignment operator, not used.
         * @param [in] x Reference to the object DynamicDataFactory that will be copied.
         * @return DynamicDataFactory &Reference to the object DynamicDataFactory that to be assigned.
         */
        DynamicDataFactory &operator=(DynamicDataFactory &&x) = delete;

    private:
        /**
         * @brief Default constructor, Can not call this constructor outside.
         */
        DynamicDataFactory() = default;
        /**
         * @brief Default destructor, Can not call this constructor outside.
         *
         */
        ~DynamicDataFactory() = default;
    };
} // namespace xtypes
} // namespace dds

__GS_DDS4CPP_END_DECLS

#endif // GSTONE_DYNAMIC_DATA_FACTORY_API_H_

