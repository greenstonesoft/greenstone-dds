/**************************************************************
* @file LiveLinessQosPolicy.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/

#ifndef GSTONE_QOSPOLICY_LIVELINESS_H
#define GSTONE_QOSPOLICY_LIVELINESS_H 1

#include "swiftdds/dcps/qos/QosPolicy.h"

namespace dds
{
namespace qos
{
    /**
    * @brief This enum class defines different kinds of liveliness for LivelinessQosPolicy.
    */
    enum class LivelinessQosPolicyKind : guint32_t
    {
        /**
        * The infrastructure will automatically signal liveliness for the DataWriters at least as often as required by the lease_duration.
        */
        AUTOMATIC_LIVELINESS_QOS = 0x00,
        /**
        * The Service will assume that as long as at least one Entity within the DomainParticipant has asserted its liveliness the other 
        * Entities in that same DomainParticipant are also alive.
        */
        MANUAL_BY_PARTICIPANT_LIVELINESS_QOS,
        /**
        * The Service will only assume liveliness of the DataWriter if the application has asserted liveliness of that DataWriter itself.
        */
        MANUAL_BY_TOPIC_LIVELINESS_QOS
    };

    /**
    * @brief This policy controls the mechanismand parameters used by the Service to ensure that particular entities on the network
    *        are still "alive".
    */
    class GS_DDS4CPP_API LivelinessQosPolicy : public QosPolicy
    {
    public:
        LivelinessQosPolicy()
            : QosPolicy{ "Liveliness" }
        {
        }

    public:
        /**
        * @brief This function serializies LivelinessQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_kind);
            cdr.serialize(m_leaseDuration);
            return;
        }

        /**
        * @brief This function deserializies LivelinessQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_kind);
            cdr.deserialize(m_leaseDuration);
            return;
        }

        /**
        * @brief This function get durability kind.
        * @return A enum class representing liveliness kind.
        */
        LivelinessQosPolicyKind const kind() const noexcept 
        {
            return m_kind;
        }

        /**
        * @brief This function set durability kind.
        * @param [in] kind_t A enum class representing liveliness kind to be set to.
        */
        inline void kind(LivelinessQosPolicyKind const kind_t) noexcept 
        {
            m_kind = kind_t;
        }

        /**
        * @brief This function get lease duration.
        * @return A Duration class representing liveliness duration.
        */
        inline gstone::rtps::Duration_t const& lease_duration() const noexcept 
        {
            return m_leaseDuration;
        }

        /**
        * @brief This function set lease duration.
        * @param [in] lease_duration_t A Duration class representing liveliness duration to be set to.
        */
        inline void lease_duration(gstone::rtps::Duration_t const& lease_duration_t) noexcept {
            m_leaseDuration = lease_duration_t;
        }

        /**
         * @brief Compare two LivelinessQosPolicy objects for equailty.
         * @param [in] l_liveliness_qos Const Reference of the left LivelinessQosPolicy object.
         * @param [in] r_liveliness_qos Const Reference of the right LivelinessQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(LivelinessQosPolicy const& l_liveliness_qos, LivelinessQosPolicy const& r_liveliness_qos) noexcept
        {
            if ((l_liveliness_qos.kind() == r_liveliness_qos.kind()) && (l_liveliness_qos.lease_duration() == r_liveliness_qos.lease_duration()))
            {
                return true;
            }
            return false;
        }

    private:
        LivelinessQosPolicyKind m_kind{ LivelinessQosPolicyKind::AUTOMATIC_LIVELINESS_QOS };
        gstone::rtps::Duration_t m_leaseDuration{ gstone::rtps::Duration_t::duration_infinite() };
    };
}
}

#endif
