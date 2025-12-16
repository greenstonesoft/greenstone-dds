/**************************************************************
* @file PorpertyQosPolicy.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_PROPERTYQOSPOLICY_H
#define GSTONE_PROPERTYQOSPOLICY_H 1

#include <algorithm>
#include <cstring>

#include "swiftdds/dcps/qos/QosPolicy.h"
#include "swiftdds/rtps/Property.h"
#include "swiftdds/rtps/BinaryProperty.h"
#include "swiftdds/dcps/DeclExport.h"

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
    class GS_DDS4CPP_API PropertyQosPolicy final : public QosPolicy
    {
    public:
        /**
         * @brief Constructer of the PropertyQosPolicy class
         */
        PropertyQosPolicy() : QosPolicy{ "Property" }
                            , m_publicProperty{}
                            , m_privateProperty{}
                            , m_binaryValue{}
        {}

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
        ~PropertyQosPolicy() final = default;

        /**
         * @brief This function get the value
         * @return Reference of a sequence of Property object
         */
        inline gstone::PropertySeq & public_property() noexcept 
        {
            return m_publicProperty;
        }

        /**
         * @brief This function get the value
         * @return Const reference to a sequence of Property object
         */
        inline gstone::PropertySeq const& public_property() const noexcept
        {
            return m_publicProperty;
        }

        /**
         * @brief This function get the value
         * @return Reference of a sequence of Property object
         */
        inline gstone::PropertySeq & private_property() noexcept 
        {
            return m_privateProperty;
        }

        /**
         * @brief This function get the value
         * @return Const reference to a sequence of Property object
         */
        inline gstone::PropertySeq const& private_property() const noexcept
        {
            return m_privateProperty;
        }

        /**
         * @brief This function get the value
         * @return Reference of a sequence of Property object
         */
        inline gstone::PropertySeq value() noexcept 
        {
            gstone::PropertySeq seq{};
            seq.insert(seq.cend(), m_privateProperty.cbegin(), m_privateProperty.cend());
            seq.insert(seq.cend(), m_publicProperty.cbegin(), m_publicProperty.cend());
            return seq;
        }

        /**
         * @brief This function get the value
         * @return Reference of a sequence of Property object
         */
        inline gstone::PropertySeq const value() const noexcept 
        {
            gstone::PropertySeq seq{};
            seq.insert(seq.cend(), m_privateProperty.cbegin(), m_privateProperty.cend());
            seq.insert(seq.cend(), m_publicProperty.cbegin(), m_publicProperty.cend());
            return seq;
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
         * @param [in] prop Const reference to a sequence of Property object to be set to
         */
        inline void add_property(gstone::Property const& prop) noexcept
        {
            if (prop.propagate())
            {
                m_publicProperty.push_back(prop);
            }
            else
            {
                m_privateProperty.push_back(prop);
            }
        }

        /**
         * @brief This function set the binary_value
         * @param [in] m_valuet Const reference to a sequence of BinaryProperty object to be set to
         */
        inline void binary_value(gstone::BinaryPropertySeq const& binaryValue) noexcept
        {
            m_binaryValue = binaryValue;
        }

        inline DdsCdr& serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_publicProperty);
            return cdr;
        }

        inline DdsCdr& deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_publicProperty);
            return cdr;
        }
    private:
        //attributes.
        gstone::PropertySeq m_publicProperty;
        gstone::PropertySeq m_privateProperty;
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
        inline static gstring_t const find_property(PropertyQosPolicy &a_property, gstring_t const &a_prefix) noexcept
        {
            gstone::PropertySeq const values {a_property.value()};
            std::vector<gstone::Property>::const_iterator ele{values.cbegin() };
            for (; ele != values.cend(); ele++)
            {
                if ((memcmp((*ele).name().c_str(), a_prefix.c_str(), (*ele).name().length()) == 0))
                {
                    return ele->value();
                }
            }

            return "";
        }

        /**
         * @brief This function finds property in PropertyQosPolicy by prefix
         * @param [in] a_property Const reference of the PropertyQosPolicy
         * @param [in] a_prefix Const reference of the property's prefix to be found 
         * @return The value property associated with the name
         * @retval nullptr Fail to find the property
         * @retval other Success to find the property
         */
        inline static gstring_t const find_property(PropertyQosPolicy const &a_property, gstring_t const &a_prefix) noexcept
        {
            gstone::PropertySeq const values {a_property.value()};
            std::vector<gstone::Property>::const_iterator ele{values.cbegin() };
            for (; ele != values.cend(); ele++)
            {
                if ((memcmp((*ele).name().c_str(), a_prefix.c_str(), (*ele).name().length()) == 0))
                {
                    return ele->value();
                }
            }

            return "";
        }


    };
    }/*qos*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_PROPERTYQOSPOLICY_H*/
