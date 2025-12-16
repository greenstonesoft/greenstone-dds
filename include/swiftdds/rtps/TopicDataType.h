/**************************************************************
 * @file TopicDataType.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
 * All rights reserved
 *************************************************************/
#ifndef GSTONE_RTPS_TOPICDATATYPE_H
#define GSTONE_RTPS_TOPICDATATYPE_H

#include <string>

#include "swiftdds/rtps/DdsCdr.h"
#include "swiftdds/rtps/InstanceHandle.h"
#include "swiftdds/rtps/SerializedPayload.h"
#include "swiftdds/dcps/DeclExport.h"
#include "swiftdds/dcps/core/TypeSupport.h"
#include "swiftdds/rtps/SerializedPayloadHeader.h"

#include "swiftdds/dcps/xtypes/DynamicTypeBuilderFactory.h"
#include "swiftdds/dcps/xtypes/DynamicTypeBuilder.h"
#include "swiftdds/dcps/xtypes/DynamicData.h"
#include "swiftdds/dcps/xtypes/DynamicDataFactory.h"
#include "swiftdds/dcps/xtypes/DynamicTypeMember.h"

__GS_DDS4CPP_BEGIN_DECLS
namespace dds {
namespace topic {

static constexpr octet OCTET_00 {0x00U};
static constexpr octet OCTET_01 {0x01U};

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
    TopicDataType() noexcept : TypeSupport{}, m_isStaticType {true}, m_sTopicDataTypeName{}, m_isWithKey {false} {}

    /**
     * @brief Destroy the TopicDataType object
     */
    ~TopicDataType() override =default;

    /**
     * @brief Serialize the given data to a SerializedPayload_t object.
     * @param [in] cdr A DdsCdr object used to do serializing.
     * @param [in] data The given data used to serialize.
     * @param [in] data_value A SerializedPayload_t object used to hold serialized data.
     * @return true Serialization completed successfully.
     * @return false Serialization completed failed.
     */
    virtual gbool_t serialize(DdsCdr &, gvoid_t *, std::shared_ptr<gstone::rtps::SerializedPayload_t>)
    {
        return true;
    }

    /**
     * @brief Deserialize from the SerializedPayload_t object.
     * @param [in] cdr A DdsCdr object used to do deserializing.
     * @param [in] data_value 
     * @param [in] data
     * @return true
     * @return false
     */
    virtual gbool_t deserialize(DdsCdr &, std::shared_ptr<gstone::rtps::SerializedPayload_t> ,
                             gvoid_t *)
    {
        return true;
    }

    /**
     * @brief
     * @param [in] cdr
     * @param [in] data
     * @param [in] data_value
     * @return true
     * @return false
     */
    virtual gbool_t serialize_key(DdsCdr &, gvoid_t *, std::shared_ptr<gstone::rtps::SerializedPayload_t> ) noexcept
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
    virtual gbool_t get_key(gvoid_t *, gstone::rtps::InstanceHandle_t *) noexcept
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
    virtual gbool_t get_key(std::shared_ptr<gstone::rtps::SerializedPayload_t> , gstone::rtps::InstanceHandle_t *) noexcept
    {
        return true;
    }

    /**
     * @brief
     * @param [in] data
     * @return true
     * @return false
     */
    virtual gbool_t init_data_ptr(gvoid_t *) noexcept
    {
        return true;
    }

    /**
     * @brief Get the Cdr Serialized Size object
     * @param [in] data
     * @return uint32_t
     */
    virtual guint32_t get_cdr_serialized_size(gvoid_t *) noexcept
    {
        return 0U;
    }

    /**
     * @brief
     * @return true
     * @return false
     */
    virtual gbool_t is_with_key() noexcept
    {
        return m_isWithKey;
    }

    /**
     * @brief
     * @return true
     * @return false
     */
    virtual gbool_t is_plain_types() noexcept
    {
        return true;
    }

    /**
     * @brief Create a Data Resource object
     * @return void*
     */
    virtual gvoid_t *create_data_resource() noexcept
    {
        return nullptr;
    }

    /**
     * @brief
     */
    virtual gvoid_t release_data_resource(gvoid_t *)  noexcept {}

    /**
     * @brief Set the Name object
     * @param [in] name
     */
    inline gvoid_t set_name(gchar_t const *const name) noexcept
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
    inline DDS::ReturnCode_t register_type(dds::domain::DomainParticipant* participant, std::string &type_name) noexcept override
    {
        if (type_name.empty())
        {
            return participant->register_type(this);
        }
        else if (type_name == get_type_name())
        {
            return participant->register_type(this);
        }
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
        {
            return DDS::ReturnCode_t::RETCODE_BAD_PARAMETER;
        }
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
    inline gbool_t is_static_type() const noexcept
    {
        return m_isStaticType;
    }

    /**
     * @brief Set the static type object
     * @param [in] value
     */
    inline gvoid_t set_static_type(gbool_t const value) noexcept
    {
        m_isStaticType = value;
    }

    /**
     * @brief Get the Dynamic Type object
     * @return dds::xtypes::DynamicType_Ptr const
     */
    virtual dds::xtypes::DynamicType_Ptr const get_dynamic_type() noexcept
    {
        return nullptr;
    }

    /**
     * @brief Get the SerializedPayloadHeader
     * @return gstone::rtps::SerializedPayloadHeader const
     */
    virtual gstone::rtps::SerializedPayloadHeader const get_serialized_payload_header() noexcept
    {
        static gstone::rtps::SerializedPayloadHeader const header {{OCTET_00,OCTET_01},{OCTET_00,OCTET_00}};    // PLAIN_CDR, LITTLE_ENDIAN
        return header;
    }

    /**
     * @brief Get the Key value data object
     * @param [in] data
     * @return data ptr
     */
    virtual gvoid_t* const get_key_value_data(gvoid_t *) noexcept
    {
        return nullptr;
    }

    /**
     * @brief Get the Key value data object
     * @param [in] data serialized payload
     * @return data ptr
     */
    virtual gvoid_t* const get_key_value_data(std::shared_ptr<gstone::rtps::SerializedPayload_t>) noexcept
    {
        return nullptr;
    }

    /**
     * @brief Copy key value data to user data
     * @param [in] Key value data
     * @param [in] User data
     */
    virtual gvoid_t copy_key_value_to_data(gvoid_t const *const, gvoid_t *const) noexcept
    {
    }

    /**
     * @brief Set the isWithKey value
     * @param [in] val
     */
    inline gvoid_t is_with_key(gbool_t const val) noexcept
    {
        m_isWithKey = val;
    }

    virtual guint32_t data_size_of() noexcept
    {
        return 0U;
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
    gbool_t m_isStaticType;
    std::string m_sTopicDataTypeName;
    gbool_t m_isWithKey;

};

} /*rtps*/
} /*gstone*/

__GS_DDS4CPP_END_DECLS

#endif /*GSTONE_RTPS_TOPICDATATYPE_H*/
