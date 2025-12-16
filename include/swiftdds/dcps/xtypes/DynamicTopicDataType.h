/**************************************************************
* @file DynamicTopicDataType.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_DYNAMIC_TOPIC_DATA_TYPE_API_H_
#define GSTONE_DYNAMIC_TOPIC_DATA_TYPE_API_H_ 1

#include "swiftdds/rtps/TopicDataType.h"
#include "swiftdds/rtps/UtilHelper.h"
#include "swiftdds/dcps/xtypes/DynamicType.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace xtypes
{
    /**
     * @brief This class is an adapter that allows using DynamicData on DDS. It inherits from TopicDataType and
     * implements the functions needed to communicate the DynamicData between Publishers and Subscribers.
     */
    class GS_DDS4CPP_API DynamicTopicDataType : public dds::topic::TopicDataType
    {
    public:
        /**
         * @brief Constructor with no parameter.
         * build a new DynamicTopicDataType variable with m_dynamicType = nullptr
         */
        DynamicTopicDataType() noexcept;
        
        /**
         * @brief Constructor with a dynamic type parameter.
         * build a new DynamicTopicDataType variable with an existed dynamic type.
         * @param [in] type A valid dynamic type to create this dynamic topic data type.
         */
        DynamicTopicDataType(DynamicType_Ptr const type) noexcept;
        
        /**
         * @brief Set function of the DynamicTopicDataType class
         * Set type to an existed type.
         * @param [in] type Topic data type.
         * @return gvoid_t 
         */
        inline gvoid_t setDynamicType(DynamicType_Ptr const type) noexcept
        {
            m_dynamicType = type;
        }
        
        /**
         * @brief Get type of this dynamic topic data type.
         * @return DynamicType_Ptr const Dynamic type.
         */
        inline DynamicType_Ptr const get_dynamic_type() noexcept override
        {
            return m_dynamicType;
        }
        
        /**
         * @brief This function tells you if the Key has been defined for this type
         * @return gbool_t If type is with key, return true.
         */
        gbool_t is_with_key() noexcept override;
        
        /**
         * @brief Get the key associated with the data.
         * @param [in] data Pointer to the data.
         * @param [in,out] ihandle Pointer to the Handle.
         * @return gbool_t True if correct.
         */
        gbool_t get_key(
            gvoid_t* data, 
            gstone::rtps::InstanceHandle_t* ihandle) noexcept override;
        
        /**
         * @brief Get the key associated with the data.
         * @param [in] data data of the type in payload type.
         * @param [in,out] ihandle Pointer to the Handle.
         * @return gbool_t True if correct.
         */
        gbool_t get_key(
            std::shared_ptr<gstone::rtps::SerializedPayload_t> data_value, 
            gstone::rtps::InstanceHandle_t* ihandle) noexcept override;
        
        /**
         * @brief This function serializes a dynamic data using CDR serialization.
         * @param [in,out] cdr CDR serialization object.
         * @param [in] data data that to be serialized.
         * @param [in,out] data_value buffer information of this serialized data
         * @return gbool_t 
         */
        gbool_t serialize(
            DdsCdr &cdr, 
            gvoid_t *data, 
            std::shared_ptr<gstone::rtps::SerializedPayload_t> data_value) noexcept override;
        
        /**
         * @brief This function deserializes a dynamic data using CDR serialization.
         * @param [in,out] cdr CDR serialization object.
         * @param [in] data_value buffer information of this serialized data
         * @param [in] data variable that will receive the valid data.
         * @return gbool_t 
         */
        gbool_t deserialize(
            DdsCdr &cdr, 
            std::shared_ptr<gstone::rtps::SerializedPayload_t> data_value, 
            gvoid_t *data) noexcept override;
    private:
        DynamicType_Ptr m_dynamicType;
    };
} // namespace xtypes
} // namespace dds

__GS_DDS4CPP_END_DECLS

#endif // GSTONE_DYNAMIC_TOPIC_DATA_TYPE_API_H_
