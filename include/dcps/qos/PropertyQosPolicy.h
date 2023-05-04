/**************************************************************
* @file PorpertyQosPolicy.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_PROPERTYQOSPOLICY_H
#define GSTONE_PROPERTYQOSPOLICY_H 1

#include <algorithm>
#include <cstring>

#include "rtps/Property.h"
#include "rtps/BinaryProperty.h"
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
    namespace qos
    {
    /**
     * @class PropertyQosPolicy
     * @brief Security-7.2.5,The PropertyQosPolicy applies to the DDS entities(DomainParticipant,DataWriter,DataReader)
     * @details To allow configuration of this policy from DDS API,the DDS Security specification extends the definitions of DDS entities,
     *          a new additional memeber "property" of type ProperQosPolicy shall be indicated at DDS entities' QoS,such as DomainParticipantQos,DataWriterQos,DataReaderQos.
     *          The PropertyQosPolicy shall be propagated via DDS discovery,it is used by plugins to check configuration compatibility.
     *          Specifically only the ones with propagate=TRUE are propagated via DDS discovery.
     */
    class GS_DDS4CPP_API PropertyQosPolicy final
    {
    public:
        /**
         * @brief Constructer of the PropertyQosPolicy class
         */
        PropertyQosPolicy() = default;

        /**
         * @brief Move constructer of the PropertyQosPolicy class
         * @param [in] other Rvalue reference of the PropertyQosPolicy object
         */
        PropertyQosPolicy(PropertyQosPolicy&& other) = default;

        /**
         * @brief Move assignment of the class PropertyQosPolicy
         * @param [in] other Rvalue reference of this PropertyQosPolicy object.
         * @return Reference of this PropertyQosPolicy object.
         */
        PropertyQosPolicy& operator=(PropertyQosPolicy&& other) = default;

        /**
         * @brief Copy constructer of the PropertyQosPolicy class
         * @param [in] other Const reference of the PropertyQosPolicy object
         */
        PropertyQosPolicy(PropertyQosPolicy const& other) = default;

        /**
         * @brief Assign a PropertyQosPolicy object to the locally PropertyQosPolicy object.
         * @param [in] other Const reference of this PropertyQosPolicy object.
         * @return Reference of this PropertyQosPolicy object.
         */
        PropertyQosPolicy& operator=(PropertyQosPolicy const& other) = default;

        /**
         * @brief Destructer of the PropertyQosPolicy class
         */
        ~PropertyQosPolicy() = default;

        /**
         * @brief This function get the value
         * @return Reference of a sequence of Property object
         */
        inline gstone::PropertySeq & value() noexcept 
        {
            return m_value;
        }

        /**
         * @brief This function get the value
         * @return Const reference to a sequence of Property object
         */
        inline gstone::PropertySeq const& value() const noexcept
        {
            return m_value;
        }

        /**
         * @brief This function get the binary_value
         * @return Const reference to a sequence of BinaryProperty object
         */
        inline gstone::BinaryPropertySeq const& binary_value() const noexcept {
            return m_binaryValue;
        }

        /**
         * @brief This function set the value
         * @param [in] m_valuet Const reference to a sequence of Property object to be set to
         */
        inline void value(gstone::PropertySeq const& m_valuet) noexcept
        {
            m_value = m_valuet;
        }

        /**
         * @brief This function set the binary_value
         * @param [in] m_valuet Const reference to a sequence of BinaryProperty object to be set to
         */
        inline void binary_value(gstone::BinaryPropertySeq const& m_binaryValuet) noexcept
        {
            m_binaryValue = m_binaryValuet;
        }

    private:
        //attributes.
        gstone::PropertySeq m_value;
        gstone::BinaryPropertySeq m_binaryValue;
    };


    /**
     * @brief This class provide some operations to help to use PropertyPolicy.
     */
    class GS_DDS4CPP_API PropertyPolicyHelper final
    {
    public:
        /**
         * @brief This function finds property in PropertyQosPolicy by prefix
         * @param [in] a_property Reference of the PropertyQosPolicy
         * @param [in] a_prefix Const reference of the property's prefix to be found 
         * @return The value property associated with the name
         * @retval nullptr Fail to find the property
         * @retval other Success to find the property
         */
        inline static gstring_t const * find_property(PropertyQosPolicy &a_property, gstring_t const &a_prefix) noexcept
        {
            guint64_t const seq_size{ a_property.value().size() };
            std::vector<gstone::Property>::iterator ele{ a_property.value().begin() };
            for (guint64_t index_{ 0U }; index_ < seq_size; index_++)
            {
                if ((memcmp((*ele).name().c_str(), a_prefix.c_str(), (*ele).name().length()) == 0))
                {
                    return &((*ele).value());
                }
                ele++;
            }

            return nullptr;
        }

        /**
         * @brief This function finds property in PropertyQosPolicy by prefix
         * @param [in] a_property Const reference of the PropertyQosPolicy
         * @param [in] a_prefix Const reference of the property's prefix to be found 
         * @return The value property associated with the name
         * @retval nullptr Fail to find the property
         * @retval other Success to find the property
         */
        inline static gstring_t const *find_property(PropertyQosPolicy const &a_property, gstring_t const &a_prefix) noexcept
        {
            gstring_t const * ret{ nullptr };
            guint64_t const seq_size{ a_property.value().size() };
            std::vector<gstone::Property>::const_iterator ele{ a_property.value().begin() };
            for (guint64_t index_{ 0U }; index_ < seq_size; index_++)
            {
                if ((memcmp((*ele).name().c_str(), a_prefix.c_str(), (*ele).name().length()) == 0))
                {
                    ret = &((*ele).value());
                    break;
                }
                ele++;
            }

            return ret;
        }


    };
    }/*qos*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_PROPERTYQOSPOLICY_H*/
