/**************************************************************
 * @file ParticipantAttributes.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_PARTICIPANTATTRIBUTES_H
#define GSTONE_PARTICIPANTATTRIBUTES_H 1

#include "rtps/PortParameters.h"
#include "rtps/Duration.h"
#include "rtps/Locator.h"
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace rtps {

/**
 * @class RecvMode_t
 * @brief Receive mode.
 */
enum class RecvMode_t : gint32_t
{
    AsyncRecvMode = 0,
    SynchRecvMode
};

/**
 * @class SPDPAttributes
 * @brief Attributes used by SPDP.
 */
class GS_DDS4CPP_API SPDPAttributes final
{
public:
    /**
     * @brief Check whether metatraffic unicast list is empty.
     * @return gbool_t Whether metatraffic unicast list is empty.
     * @retval true The metatraffic unicast list is empty.
     * @retval false The metatraffic unicast list isn't empty.
     */
    gbool_t metatraffic_unicast_empty() const noexcept
    {
        return (m_metatrafficUnicastLocatorList.empty());
    }

    /**
     * @brief Get a metatraffic unicast locator.
     * @param [in] an_index The index of a locator.
     * @return gstone::rtps::Locator_t A metatraffic unicast locator.
     */
    gstone::rtps::Locator_t metatraffic_unicast_at(guint32_t const an_index) const noexcept
    {
        gsize_t const use_size {static_cast<gsize_t>(an_index)};
        if (use_size < this->m_metatrafficUnicastLocatorList.size())
        {
            return this->m_metatrafficUnicastLocatorList.at(use_size);
        }
        else
        {
            return gstone::rtps::Locator_t();
        }
    }

    /**
     * @brief Get all of the metatraffic unicast locators that can be used to send messages to the built-in Endpoints
     * contained in the Participant.
     * @return gstone::rtps::LocatorList_t const& All of the metatraffic unicast locators.
     */
    gstone::rtps::LocatorList_t const &metatraffic_unicast_locators() const noexcept
    {
        return this->m_metatrafficUnicastLocatorList;
    }

    /**
     * @brief Get all of the metatraffic unicast locators.
     * @return gstone::rtps::LocatorList_t& All of the metatraffic unicast locators.
     */
    gstone::rtps::LocatorList_t &metatraffic_unicast_locators() noexcept
    {
        return this->m_metatrafficUnicastLocatorList;
    }

    /**
     * @brief Get all of the metatraffic multicast locators that can be used to send messages to the built-in Endpoints
     * contained in the Participant.
     * @return gstone::rtps::LocatorList_t const& All of the metatraffic multicast locators.
     */
    gstone::rtps::LocatorList_t const &metatraffic_multicast_locators() const noexcept
    {
        return this->m_metatrafficMulticastLocatorList;
    }

    /**
     * @brief Get all of the metatraffic multicast locators that can be used to send messages to the built-in Endpoints
     * contained in the Participant.
     * @return gstone::rtps::LocatorList_t& All of the metatraffic multicast locators.
     */
    gstone::rtps::LocatorList_t &metatraffic_multicast_locators() noexcept
    {
        return this->m_metatrafficMulticastLocatorList;
    }

    /**
     * @brief Set the domainId.
     * @param [in] the_domain_id The domainId used to set.
     */
    inline gvoid_t domain_id(guint32_t const the_domain_id) noexcept
    {
        m_domainId = the_domain_id;
    }

    /**
     * @brief Get the domainId.
     * @return guint32_t The domain id in this object.
     */
    inline guint32_t domain_id() const noexcept
    {
        return m_domainId;
    }

    /**
     * @brief Get the domain tag.
     * @return gstring_t const& The domain tag in this object.
     */
    inline gstring_t const &domain_tag() const noexcept
    {
        return m_domainTag;
    }

    /**
     * @brief Set the domain tag.
     * @param [in] the_tag The tag used to set.
     */
    inline gvoid_t domain_tag(gstring_t const &the_tag) noexcept
    {
        m_domainTag = the_tag;
    }

    /**
     * @brief Get port parameters.
     * @return gstone::rtps::PortParameters const& The port parameters in this object.
     */
    inline gstone::rtps::PortParameters const &port_param() const noexcept
    {
        return m_portParam;
    }

    /**
     * @brief Get port parameters.
     * @return gstone::rtps::PortParameters& The port parameters in this object.
     */
    inline gstone::rtps::PortParameters &port_param() noexcept
    {
        return m_portParam;
    }

    /**
     * @brief Get the period of send SPDP message.
     * @return gstone::rtps::Duration_t const& The period of send SPDP message.
     */
    inline gstone::rtps::Duration_t const &period() const noexcept
    {
        return m_period;
    }

    /**
     * @brief Set the period of send SPDP message.
     * @param [in] the_period Period used to set.
     */
    inline gvoid_t period(gstone::rtps::Duration_t const &the_period) noexcept
    {
        m_period = the_period;
    }

    /**
     * @brief Add a metatraffic unicast locator.
     * @param [in] a_locator A locator used to add.
     */
    gvoid_t add_meta_unicast_locator(gstone::rtps::Locator_t const &a_locator) noexcept
    {
        m_metatrafficUnicastLocatorList.push_back(a_locator);
    }

    /**
     * @brief Add a metatraffic multicast locator.
     * @param [in] a_locator A locator used to add.
     */
    gvoid_t add_meta_multicast_locator(gstone::rtps::Locator_t const &a_locator) noexcept
    {
        m_metatrafficMulticastLocatorList.push_back(a_locator);
    }

    /**
     * @brief Set lease duration. This value decided how long a Participant should be considered alive every time an
     * announcement is received from the Participant.
     * @param [in] a_duration Duration used to set.
     */
    gvoid_t lease_duration(gstone::rtps::Duration_t const &a_duration) noexcept
    {
        m_leaseDuration = a_duration;
    }

    /**
     * @brief Get lease duration. This value decided how long a Participant should be considered alive every time an
     * announcement is received from the Participant.
     * @return gstone::rtps::Duration_t const& The lease duration.
     */
    gstone::rtps::Duration_t const &lease_duration() const noexcept
    {
        return m_leaseDuration;
    }

    /**
     * @brief Get default remote unicast locators.
     * @return gstone::rtps::LocatorList_t const&
     */
    inline gstone::rtps::LocatorList_t const &default_remote_unicast_locators() const noexcept
    {
        return m_defaultRemoteUnicastLocatorList;
    }

    /**
     * @brief Set default remote unicast locators.
     * @param [in] a_locator_list Locators used to set.
     */
    gvoid_t default_remote_unicast_locators(gstone::rtps::LocatorList_t const &a_locator_list) noexcept;

    /**
     * @brief Get default remote multicast locators.
     * @return gstone::rtps::LocatorList_t const&
     */
    inline gstone::rtps::LocatorList_t const &default_remote_multicast_locators() const noexcept
    {
        return m_defaultRemoteMulticastLocatorList;
    }

    /**
     * @brief Set default remote multicast locators.
     * @param [in] a_locator_list
     */
    gvoid_t default_remote_multicast_locators(gstone::rtps::LocatorList_t const &a_locator_list) noexcept;

    /**
     * @brief The default constructor for SPDPAttributes.
     */
    SPDPAttributes() = default;

    /**
     * @brief Destroy the SPDPAttributes object
     */
    ~SPDPAttributes() = default;

    /**
     * @brief The copy constructor for SPDPAttributes.
     */
    SPDPAttributes(SPDPAttributes const &) = default;

    /**
     * @brief The copy assignment operator.
     * @return SPDPAttributes& Reference of the locally SPDPAttributes object.
     */
    SPDPAttributes &operator=(SPDPAttributes const &) = default;

    /**
     * @brief The move assignment operator.
     */
    SPDPAttributes(SPDPAttributes &&) = default;

    /**
     * @brief The copy assignment operator.
     * @return SPDPAttributes& Reference of the locally SPDPAttributes object.
     */
    SPDPAttributes &operator=(SPDPAttributes &&) = default;

private:
    static constexpr guint32_t PERIOD_SECONDS {3U};
    static constexpr guint32_t LEASE_DURATION {30U};
    guint32_t m_domainId {0U};

    // std::string domainTag = "DefaultTag";
    gstring_t m_domainTag {};

    gstone::rtps::PortParameters m_portParam;

    gstone::rtps::Duration_t m_period {PERIOD_SECONDS, 0};

    gstone::rtps::Duration_t m_leaseDuration {LEASE_DURATION, 0};

    gstone::rtps::LocatorList_t m_metatrafficUnicastLocatorList;

    gstone::rtps::LocatorList_t m_metatrafficMulticastLocatorList;

    gstone::rtps::LocatorList_t m_defaultRemoteUnicastLocatorList;

    gstone::rtps::LocatorList_t m_defaultRemoteMulticastLocatorList;
};

/**
 * @class SEDPAttributes
 * @brief Attributes used by SEDP.
 */
class GS_DDS4CPP_API SEDPAttributes final
{
public:
    /**
     * @brief Whether use DataWriters.
     * @return gbool_t
     */
    inline gbool_t use_data_writers() const noexcept
    {
        return m_useDataWriters;
    }

    /**
     * @brief Set whether use DataWriters.
     * @param [in] used_flag Value used to set.
     */
    inline gvoid_t use_data_writers(gbool_t const used_flag) noexcept
    {
        m_useDataWriters = used_flag;
    }

    /**
     * @brief
     * @return gbool_t
     */
    inline gbool_t use_data_readers() const noexcept
    {
        return m_useDataReaders;
    }

    /**
     * @brief
     * @param [in] used_flag
     */
    inline gvoid_t use_data_readers(gbool_t const used_flag) noexcept
    {
        m_useDataReaders = used_flag;
    }

    /**
     * @brief
     * @return gstone::rtps::Duration_t const&
     */
    inline gstone::rtps::Duration_t const &heartbeat_response_delay() const noexcept
    {
        return m_heartbeatResponseDelay;
    }

    /**
     * @brief
     * @param [in] a_duration
     */
    inline gvoid_t heartbeat_response_delay(gstone::rtps::Duration_t const &a_duration) noexcept
    {
        m_heartbeatResponseDelay = a_duration;
    }

    /**
     * @brief
     * @return gstone::rtps::Duration_t const&
     */
    inline gstone::rtps::Duration_t const &heartbeat_suppression_duration() const noexcept
    {
        return m_heartbeatSuppressionDuration;
    }
    /**
     * @brief
     * @param [in] a_duration
     */
    inline gvoid_t heartbeat_suppression_duration(gstone::rtps::Duration_t const &a_duration) noexcept
    {
        m_heartbeatSuppressionDuration = a_duration;
    }

    /**
     * @brief
     * @return gstone::rtps::Duration_t const&
     */
    inline gstone::rtps::Duration_t const &heartbeat_period() const noexcept
    {
        return m_heartbeatPeriod;
    }

    /**
     * @brief
     * @param [in] a_duration
     */
    inline gvoid_t heartbeat_period(gstone::rtps::Duration_t const &a_duration) noexcept
    {
        m_heartbeatPeriod = a_duration;
    }

    /**
     * @brief
     * @return gstone::rtps::Duration_t const&
     */
    inline gstone::rtps::Duration_t const &nack_response_delay() const noexcept
    {
        return m_nackResponseDelay;
    }

    /**
     * @brief
     * @param [in] a_duration
     */
    inline gvoid_t nack_response_delay(gstone::rtps::Duration_t const &a_duration) noexcept
    {
        m_nackResponseDelay = a_duration;
    }

    /**
     * @brief
     * @return gstone::rtps::Duration_t const&
     */
    inline gstone::rtps::Duration_t const &nack_suppression_duration() const noexcept
    {
        return m_nackSuppressionDuration;
    }

    /**
     * @brief
     * @param [in] a_duration
     */
    inline gvoid_t nack_suppression_duration(gstone::rtps::Duration_t const &a_duration) noexcept
    {
        m_nackSuppressionDuration = a_duration;
    }

    /**
     * @brief Construct a new Simple E D P Attributes object
     */
    SEDPAttributes() = default;

    /**
     * @brief
     * @param [] lhs
     * @param [] rhs
     * @return gbool_t
     */
    friend gbool_t operator==(SEDPAttributes const &lhs, SEDPAttributes const &rhs) noexcept
    {
        return (lhs.use_data_writers() == rhs.use_data_writers()) && (lhs.use_data_readers() == rhs.use_data_readers());
    }
private:
    static constexpr guint64_t hb_rsp_miseconds {100U};
    static constexpr guint64_t hb_sup_miseconds {1U};
    static constexpr guint64_t hb_period_miseconds {200U};
    static constexpr guint64_t ncak_rsp_miseconds {5U};
    static constexpr guint64_t nack_sup_miseconds {1U};
    gbool_t m_useDataWriters {true};

    gbool_t m_useDataReaders {true};

    gstone::rtps::Duration_t m_heartbeatResponseDelay {Duration_t(hb_rsp_miseconds)};
    gstone::rtps::Duration_t m_heartbeatSuppressionDuration {Duration_t(hb_sup_miseconds)};

    gstone::rtps::Duration_t m_heartbeatPeriod {Duration_t(hb_period_miseconds)};
    gstone::rtps::Duration_t m_nackResponseDelay {Duration_t(ncak_rsp_miseconds)};
    gstone::rtps::Duration_t m_nackSuppressionDuration {Duration_t(nack_sup_miseconds)};
};

/**
 * @brief
 */
class GS_DDS4CPP_API ParticipantAttributes final
{
public:
    /**
     * @brief Construct a new Participant Attributes object
     */
    ParticipantAttributes() = default;

    /**
     * @brief Destroy the Participant Attributes object
     */
    ~ParticipantAttributes() noexcept = default;

    /**
     * @brief Construct a new Participant Attributes 
     */
    ParticipantAttributes(ParticipantAttributes const &) = default;

    /**
     * @brief
     * @return ParticipantAttributes&
     */
    ParticipantAttributes &operator=(ParticipantAttributes const &) = default;

    /**
     * @brief Construct a new Participant Attributes object
     */
    ParticipantAttributes(ParticipantAttributes &&) = default;

    /**
     * @brief
     * @return ParticipantAttributes&
     */
    ParticipantAttributes &operator=(ParticipantAttributes &&) = default;
public:
    /**
     * @brief
     * @return SPDPAttributes const&
     */
    inline SPDPAttributes const &spdp_attributes() const noexcept
    {
        return this->m_spdpAttributes;
    }

    /**
     * @brief
     * @return SPDPAttributes&
     */
    inline SPDPAttributes &spdp_attributes() noexcept
    {
        return this->m_spdpAttributes;
    }

    /**
     * @brief
     * @param [in] a_attributes
     */
    inline gvoid_t spdp_attributes(SPDPAttributes const &a_attributes) noexcept
    {
        this->m_spdpAttributes = a_attributes;
    }

    /**
     * @brief
     * @return gbool_t
     */
    inline gbool_t used_wlp() const noexcept
    {
        return this->m_useWLP;
    }

    /**
     * @brief
     * @param [in] used_flag
     */
    inline gvoid_t used_wlp(gbool_t const used_flag) noexcept
    {
        this->m_useWLP = used_flag;
    }

    /**
     * @brief
     * @return guint32_t
     */
    guint32_t domain_id() noexcept
    {
        return m_spdpAttributes.domain_id();
    }

    /**
     * @brief
     * @param [in] a_domain_id
     */
    gvoid_t domain_id(guint32_t const a_domain_id) noexcept
    {
        m_spdpAttributes.domain_id(a_domain_id);
    }

    /**
     * @brief
     * @param [in] a_locator
     */
    gvoid_t add_meta_unicast_locator(gstone::rtps::Locator_t const &a_locator) noexcept
    {
        m_spdpAttributes.add_meta_unicast_locator(a_locator);
    }

    /**
     * @brief
     * @param [in] a_duration
     */
    gvoid_t lease_duration(gstone::rtps::Duration_t const &a_duration) noexcept
    {
        m_spdpAttributes.lease_duration(a_duration);
    }

    /**
     * @brief
     * @return gstone::rtps::LocatorList_t const&
     */
    gstone::rtps::LocatorList_t const &default_unicast_locatorlist() const noexcept
    {
        return m_defaultUnicastLocatorList;
    }

    /**
     * @brief
     * @return gstone::rtps::LocatorList_t&
     */
    gstone::rtps::LocatorList_t &default_unicast_locatorlist() noexcept
    {
        return m_defaultUnicastLocatorList;
    }

    /**
     * @brief
     * @param [in] a_locator_list
     */
    gvoid_t default_unicast_locatorlist(gstone::rtps::LocatorList_t const &a_locator_list) noexcept;

    /**
     * @brief
     * @return gstone::rtps::LocatorList_t const&
     */
    gstone::rtps::LocatorList_t const &default_multicast_locatorlist() const noexcept
    {
        return m_defaultMulticastLocatorList;
    }

    /**
     * @brief
     * @return gstone::rtps::LocatorList_t&
     */
    gstone::rtps::LocatorList_t &default_multicast_locatorlist() noexcept
    {
        return m_defaultMulticastLocatorList;
    }

    /**
     * @brief
     * @param [in] a_locator_list
     */
    gvoid_t default_multicast_locatorlist(gstone::rtps::LocatorList_t const &a_locator_list) noexcept;

    /**
     * @brief
     * @return guint32_t
     */
    inline guint32_t participant_id() const noexcept
    {
        return m_participantID;
    }

    /**
     * @brief
     * @param [in] a_participant_id
     */
    inline gvoid_t participant_id(guint32_t const a_participant_id) noexcept
    {
        m_participantID = a_participant_id;
    }

    /**
     * @brief
     * @return SEDPAttributes const&
     */
    inline SEDPAttributes const &sedp_attributes() const noexcept
    {
        return m_sedpAttributes;
    }

    /**
     * @brief
     * @param [in] the_attributes
     */
    inline gvoid_t sedp_attributes(SEDPAttributes const &the_attributes) noexcept
    {
        m_sedpAttributes = the_attributes;
    }

    /**
     * @brief
     * @return RecvMode_t
     */
    inline RecvMode_t recv_mode() const noexcept
    {
        return m_recvMode;
    }

    /**
     * @brief
     * @param [in] the_recv_mode
     */
    inline gvoid_t recv_mode(RecvMode_t const the_recv_mode) noexcept
    {
        m_recvMode = the_recv_mode;
    }

    /**
     * @brief
     * @return gbool_t
     */
    inline gbool_t use_builtin_transports() const noexcept
    {
        return m_useBuiltinTransports;
    }

    /**
     * @brief
     * @param [in] used_flag
     */
    inline gvoid_t use_builtin_transports(gbool_t const used_flag) noexcept
    {
        m_useBuiltinTransports = used_flag;
    }

    /**
     * @brief
     * @return gbool_t
     */
    inline gbool_t use_ipv6() const noexcept
    {
        return m_useIpv6;
    }

    /**
     * @brief
     * @param [in] used_flag
     */
    inline gvoid_t use_ipv6(gbool_t const used_flag) noexcept
    {
        m_useIpv6 = used_flag;
    }

    /**
     * @brief
     * @return guint32_t
     */
    inline guint32_t heartbeat_period() const noexcept
    {
        return m_heartbeatPeriod;
    }

    /**
     * @brief
     * @param [in] the_hb_period
     */
    inline gvoid_t heartbeat_period(guint32_t const the_hb_period) noexcept
    {
        m_heartbeatPeriod = the_hb_period;
    }

    /**
     * @brief
     * @return guint32_t
     */
    inline guint32_t shared_memory_size() const noexcept
    {
        return m_sharedMemorySize;
    }

    /**
     * @brief
     * @param [in] the_memory_size
     */
    inline gvoid_t shared_memory_size(guint32_t const the_memory_size) noexcept
    {
        m_sharedMemorySize = the_memory_size;
    }

    /**
     * @brief
     * @return gbool_t
     */
    inline gbool_t use_xtypes() const noexcept
    {
        return m_useXtypes;
    }

    /**
     * @brief
     * @param [in] used_flag
     */
    inline gvoid_t use_xtypes(gbool_t const used_flag) noexcept
    {
        m_useXtypes = used_flag;
    }

    /**
     * @brief* const
     */
    inline gvoid_t *const sec_handle() const noexcept
    {
        return m_secHandle;
    }

    /**
     * @brief
     * @param [in] a_handle
     */
    inline gvoid_t sec_handle(gvoid_t *const a_handle) noexcept
    {
        m_secHandle = a_handle;
    }

    /**
     * @brief
     * @return gbool_t
     */
    inline gbool_t enable_monitoring() const noexcept
    {
        return m_enableMonitoring;
    }

    /**
     * @brief
     * @param [in] used_flag
     */
    inline gvoid_t enable_monitoring(gbool_t const used_flag) noexcept
    {
        m_enableMonitoring = used_flag;
    }

    /**
     * @brief
     * @return gbool_t
     */
    inline gbool_t enable_distlog() const noexcept
    {
        return m_enableDistlog;
    }

    /**
     * @brief
     * @param [in] used_flag
     */
    inline gvoid_t enable_distlog(gbool_t const used_flag) noexcept
    {
        m_enableDistlog = used_flag;
    }
private:
    static constexpr guint32_t default_participant_id {0U};
    gstone::rtps::LocatorList_t m_defaultUnicastLocatorList {}; 

    gstone::rtps::LocatorList_t m_defaultMulticastLocatorList {}; 

    SPDPAttributes m_spdpAttributes;

    SEDPAttributes m_sedpAttributes;

    guint32_t m_participantID {default_participant_id};

    RecvMode_t m_recvMode {RecvMode_t::AsyncRecvMode};

    gbool_t m_useBuiltinTransports {true};
    gbool_t m_useWLP {false};
    gbool_t m_useIpv6 {false};

    guint32_t m_heartbeatPeriod {200U}; 

    guint32_t m_sharedMemorySize {100U * 1024U * 1024U};

    gbool_t m_useXtypes {false};

    gvoid_t *m_secHandle {nullptr};

    gbool_t m_enableMonitoring {false};
    gbool_t m_enableDistlog {false};
};

} /*rtps*/
} /*gstone*/

__GS_DDS4CPP_END_DECLS

#endif /*GSTONE_RTPS_PARTICIPANTATTRIBUTES_H*/
