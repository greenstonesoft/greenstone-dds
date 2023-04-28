/**************************************************************
 * @file TopicDataType.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
 * All rights reserved
 *************************************************************/
#ifndef GSTONE_RTPS_TOPICDATATYPE_H
#define GSTONE_RTPS_TOPICDATATYPE_H

#include <string>

#include "rtps/DdsCdr.h"
#include "rtps/InstanceHandle.h"
#include "rtps/SerializedPayload.h"
#include "dcps/DeclExport.h"
#include "dcps/core/TypeSupport.h"

#include "dcps/xtypes/DynamicTypeBuilderFactory.h"
#include "dcps/xtypes/DynamicTypeBuilder.h"
#include "dcps/xtypes/DynamicData.h"
#include "dcps/xtypes/DynamicDataFactory.h"
#include "dcps/xtypes/DynamicTypeMember.h"

__GS_DDS4CPP_BEGIN_DECLS
namespace dds {
namespace topic {

/**
 * @class TopicDataType
 * @brief The TopicDataType interface is an abstract interface that has to be specialized for each concrete type that
 * will be used by the application.
 */
class GS_DDS4CPP_API TopicDataType : public dds::core::TypeSupport
{
public:
    /**
     * @brief The default constructor for TopicDataType.
     */
    TopicDataType() : m_isStaticType(true) {}

    /**
     * @brief Destroy the TopicDataType object
     */
    virtual ~TopicDataType() {}

    /**
     * @brief Serialize the given data to a SerializedPayload_t object.
     * @param [in] cdr A DdsCdr object used to do serializing.
     * @param [in] data The given data used to serialize.
     * @param [in] data_value A SerializedPayload_t object used to hold serialized data.
     * @return true Serialization completed successfully.
     * @return false Serialization completed failed.
     */
    virtual bool serialize(DdsCdr &cdr, void *data, std::shared_ptr<gstone::rtps::SerializedPayload_t> data_value) = 0;

    /**
     * @brief Deserialize from the SerializedPayload_t object.
     * @param [in] cdr A DdsCdr object used to do deserializing.
     * @param [in] data_value 
     * @param [in] data
     * @return true
     * @return false
     */
    virtual bool deserialize(DdsCdr &cdr, std::shared_ptr<gstone::rtps::SerializedPayload_t> data_value,
                             void *data) = 0;

    /**
     * @brief
     * @param [in] cdr
     * @param [in] data
     * @param [in] data_value
     * @return true
     * @return false
     */
    virtual bool serialize_key(DdsCdr &cdr, void *data, std::shared_ptr<gstone::rtps::SerializedPayload_t> data_value)
    {
        return true;
    }

    /**
     * @brief Get the Key object
     * @param [in] data
     * @param [in] ihandle
     * @return true
     * @return false
     */
    virtual bool get_key(void *data, gstone::rtps::InstanceHandle_t *ihandle)
    {
        return true;
    }

    /**
     * @brief Get the Key object
     * @param [in] data_value
     * @param [in] ihandle
     * @return true
     * @return false
     */
    virtual bool get_key(std::shared_ptr<gstone::rtps::SerializedPayload_t> data_value, gstone::rtps::InstanceHandle_t *ihandle)
    {
        return true;
    }

    /**
     * @brief
     * @param [in] data
     * @return true
     * @return false
     */
    virtual bool init_data_ptr(void *data)
    {
        return true;
    }

    /**
     * @brief Get the Cdr Serialized Size object
     * @param [in] data
     * @return uint32_t
     */
    virtual uint32_t get_cdr_serialized_size(void *data)
    {
        return 0;
    }

    /**
     * @brief
     * @return true
     * @return false
     */
    virtual bool is_with_key()
    {
        return true;
    }

    /**
     * @brief
     * @return true
     * @return false
     */
    virtual bool is_plain_types()
    {
        return true;
    }

    /**
     * @brief Create a Data Resource object
     * @return void*
     */
    virtual void *create_data_resource()
    {
        return nullptr;
    }

    /**
     * @brief
     */
    virtual void release_data_resource(void *) {}

    /**
     * @brief Set the Name object
     * @param [in] name
     */
    inline void set_name(const char *name) noexcept
    {
        m_sTopicDataTypeName = std::string(name);
    }

    /**
     * @brief Get the Name object
     * @return gstring_t const&
     */
    inline gstring_t const &get_name() const noexcept
    {
        return m_sTopicDataTypeName;
    }

    /**
     * @brief
     * @param [in] participant
     * @param [in] type_name
     * @return DDS::ReturnCode_t
     */
    inline DDS::ReturnCode_t register_type(dds::domain::DomainParticipant* participant, std::string &type_name) override
    {
        if (type_name.empty())
            return participant->register_type(this);
        else if (type_name == get_type_name())
            return participant->register_type(this);
        else if (type_name != get_type_name())
        {
            if (participant->is_type_registered(this))
            {
                return ::DDS::ReturnCode_t::RETCODE_PRECONDITION_NOT_MET;
            }
            this->set_name(type_name.c_str());
            return participant->register_type(this);
        }
        else
            return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER;
    }

    /**
     * @brief Get the type name object
     * @return std::string const&
     */
    inline std::string const &get_type_name() const noexcept override
    {
        return this->m_sTopicDataTypeName;
    }

    /**
     * @brief
     * @return true
     * @return false
     */
    inline bool is_static_type() const noexcept
    {
        return m_isStaticType;
    }

    /**
     * @brief Set the static type object
     * @param [in] value
     */
    inline void set_static_type(bool value) noexcept
    {
        m_isStaticType = value;
    }

    /**
     * @brief Get the Dynamic Type object
     * @return dds::xtypes::DynamicType_ptr const
     */
    virtual dds::xtypes::DynamicType_ptr const get_dynamic_type() noexcept
    {
        return nullptr;
    }

protected:
    /**
     * @brief The copy constructor for Duration.
     */
    TopicDataType(TopicDataType const &) = default;
    /**
     * @brief The move constructor for Duration.
     */
    TopicDataType(TopicDataType &&) = default;

    /**
     * @brief The copy assignment operator.
     * @return TopicDataType& Duration& Reference of the locally Duration object.
     */
    TopicDataType &operator=(TopicDataType const &) = default;
    /**
     * @brief  The move assignment operator.
     * @return TopicDataType& Duration& Reference of the locally Duration object.
     */
    TopicDataType &operator=(TopicDataType &&) = default;

private:
    bool m_isStaticType;
    std::string m_sTopicDataTypeName;
};

} /*rtps*/
} /*gstone*/

__GS_DDS4CPP_END_DECLS

#endif /*GSTONE_RTPS_TOPICDATATYPE_H*/
