/**************************************************************
 * @file PortParameters.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
 * All rights reserved
 *************************************************************/
#ifndef GSTONE_RTPS_PORTPARAMETERS_H
#define GSTONE_RTPS_PORTPARAMETERS_H

#include "swiftdds/dcps/PITypes.h"
#include "swiftdds/dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace rtps {

/**
 * @class PortParameters
 * @brief Parameters used to generate default port number.
 */
class GS_DDS4CPP_API PortParameters final
{
public:
    /**
     * @brief The default constructor for PortParameters.
     */
    PortParameters() noexcept = default;

    /**
     * @brief Destroy the PortParameters object.
     */
    ~PortParameters() = default;

    /**
     * @brief Construct a new Port Parameters object.
     */
    PortParameters(PortParameters const &) = default;

    /**
     * @brief Construct a new Port Parameters object.
     */
    PortParameters(PortParameters &&) = default;

    /**
     * @brief The copy assignment operator.
     * @return PortParameters& Reference of the locally PortParameters object.
     */
    PortParameters &operator=(PortParameters const &) = default;

    /**
     * @brief The move assignment operator.
     * @return PortParameters& Reference of the locally PortParameters object.
     */
    PortParameters &operator=(PortParameters &&) = default;

    /**
     * @brief Compare two PortParameters objects for equality.
     * @param [in] lhs Lhs parameter.
     * @param [in] rhs Rhs parameter.
     * @return gbool_t Whether lhs equal to rhs.
     * @retval true Lhs equal to rhs.
     * @retval false Lhs inequal to rhs.
     */
    inline friend bool operator==(PortParameters const &lhs, PortParameters const &rhs) noexcept
    {
        return (lhs.m_portBase == rhs.port_base()) && (lhs.m_domainIDGain == rhs.domain_id_gain()) &&
               (lhs.m_participantIDGain == rhs.participant_id_gain()) && (lhs.m_offsetd0 == rhs.offsetd0()) &&
               (lhs.m_offsetd1 == rhs.offsetd1()) && (lhs.m_offsetd2 == rhs.offsetd2()) &&
               (lhs.m_offsetd3 == rhs.offsetd3());
    }
    
    /**
     * @brief Get the multicast port.
     * @param [in] a_domain_id A special domain id.
     * @return guint32_t The multicast port.
     */
    inline guint32_t get_multicast_port(guint32_t const a_domain_id) const noexcept
    {
        guint32_t const port {m_portBase + m_domainIDGain * a_domain_id + m_offsetd0};

        if (port > MAX_PORT_NUM)
        {
            return 0U;
        }

        return port;
    }

    /**
     * @brief Get the unicast port.
     * @param [in] a_domain_id A special domain id.
     * @param [in] a_participant_id A special participant id.
     * @return guint32_t The unicast port.
     */
    inline guint32_t get_unicast_port(guint32_t const a_domain_id, guint32_t const a_participant_id) const noexcept
    {
        guint32_t const port {m_portBase + m_domainIDGain * a_domain_id + m_offsetd1 +
                              m_participantIDGain * a_participant_id};

        if (port > MAX_PORT_NUM)
        {
            return 0U;
        }

        return port;
    }
    
    /**
     * @brief Get the user traffic unicast port.
     * @param [in] a_domain_id A special domain id.
     * @param [in] a_participant_id A special participant id.
     * @return guint32_t The user traffic unicast port.
     */
    inline guint32_t get_user_traffic_unicast_port(guint32_t const a_domain_id,
                                               guint32_t const a_participant_id) const noexcept
    {
        guint32_t const port {m_portBase + m_domainIDGain * a_domain_id + m_offsetd3 +
                              m_participantIDGain * a_participant_id};

        if (port > MAX_PORT_NUM)
        {
            return 0U;
        }

        return port;
    }
    
    /**
     * @brief Get the user traffic multicast port.
     * @param [in] a_domain_id A special domain id.
     * @return guint32_t The user traffic multicast port.
     */
    inline guint32_t get_user_traffic_multicast_port(guint32_t const a_domain_id) const noexcept
    {
        guint32_t const port {m_portBase + m_domainIDGain * a_domain_id + m_offsetd2};

        if (port > MAX_PORT_NUM)
        {
            return 0U;
        }

        return port;
    }

    /**
     * @brief Get port base number.
     * @return guint16_t The port base number.
     */
    inline guint16_t port_base() const noexcept
    {
        return m_portBase;
    }

    /**
     * @brief Get the domian id gain.
     * @return guint16_t The domain id gain.
     */
    inline guint16_t domain_id_gain() const noexcept
    {
        return m_domainIDGain;
    }

    /**
     * @brief Get the participant id gain.
     * @return guint16_t The participant id gain.
     */
    inline guint16_t participant_id_gain() const noexcept
    {
        return m_participantIDGain;
    }

    /**
     * @brief Get the additional offset d0.
     * @return guint16_t The additional offset d0.
     */
    inline guint16_t offsetd0() const noexcept
    {
        return m_offsetd0;
    }

    /**
     * @brief Get the additional offset d1.
     * @return guint16_t The additional offset d1.
     */
    inline guint16_t offsetd1() const noexcept
    {
        return m_offsetd1;
    }

    /**
     * @brief Get the additional offset d2.
     * @return guint16_t The additional offset d2.
     */
    inline guint16_t offsetd2() const noexcept
    {
        return m_offsetd2;
    }

    /**
     * @brief Get the additional offset d3.
     * @return guint16_t The additional offset d3.
     */
    inline guint16_t offsetd3() const noexcept
    {
        return m_offsetd3;
    }

    /**
     * @brief Set port base number.
     * @param [in] a_port_base A port base number used to set.
     */
    inline gvoid_t port_base(guint16_t const a_port_base) noexcept
    {
        m_portBase = a_port_base;
    }

    /**
     * @brief Set domain id gain.
     * @param [in] a_domain_id_gain A domain id gain used to set.
     */
    inline gvoid_t domain_id_gain(guint16_t const a_domain_id_gain) noexcept
    {
        m_domainIDGain = a_domain_id_gain;
    }

    /**
     * @brief Set participant id gain.
     * @param [in] a_participantid_gain A participant id gain used to set.
     */
    inline gvoid_t participant_id_gain(guint16_t const a_participantid_gain) noexcept
    {
        m_participantIDGain = a_participantid_gain;
    }

    /**
     * @brief Set additional offset d0.
     * @param [in] offset_d0 A d0 used to set.
     */
    inline gvoid_t offsetd0(guint16_t const offset_d0) noexcept
    {
        m_offsetd0 = offset_d0;
    }

    /**
     * @brief Set additional offset d1.
     * @param [in] offset_d1 A d0 used to set.
     */
    inline gvoid_t offsetd1(guint16_t const offset_d1) noexcept
    {
        m_offsetd1 = offset_d1;
    }

    /**
     * @brief Set additional offset d2.
     * @param [in] offset_d2 A d0 used to set.
     */
    inline gvoid_t offsetd2(guint16_t const offset_d2) noexcept
    {
        m_offsetd2 = offset_d2;
    }

    /**
     * @brief Set additional offset d3.
     * @param [in] offset_d3 A d0 used to set.
     */
    inline gvoid_t offsetd3(guint16_t const offset_d3) noexcept
    {
        m_offsetd3 = offset_d3;
    }
    
private:
    guint16_t m_portBase {DEFAULT_PORT_BASE};
    guint16_t m_domainIDGain {DEFAULT_DOMAIN_ID_GAIN};
    guint16_t m_participantIDGain {DEFAULT_PARTICIPANT_ID_GAIN};
    guint16_t m_offsetd0 {DEFAULT_OFFSET_D0};
    guint16_t m_offsetd1 {DEFAULT_OFFSET_D1};
    guint16_t m_offsetd2 {DEFAULT_OFFSET_D2};
    guint16_t m_offsetd3 {DEFAULT_OFFSET_D3};

    static constexpr guint16_t DEFAULT_PORT_BASE {7400U};
    static constexpr guint16_t DEFAULT_DOMAIN_ID_GAIN {250U};
    static constexpr guint16_t DEFAULT_PARTICIPANT_ID_GAIN {2U};
    static constexpr guint16_t DEFAULT_OFFSET_D0 {0U};
    static constexpr guint16_t DEFAULT_OFFSET_D1 {10U};
    static constexpr guint16_t DEFAULT_OFFSET_D2 {1U};
    static constexpr guint16_t DEFAULT_OFFSET_D3 {11U};
    static constexpr guint32_t MAX_PORT_NUM {65535U};
};

} /*rtps*/
} /*gstone*/

__GS_DDS4CPP_END_DECLS

#endif /*GSTONE_RTPS_PORTPARAMETERS_H*/
