/**************************************************************
 * @file ParticipantAttributes.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_PARTICIPANTATTRIBUTES_H
#define GSTONE_PARTICIPANTATTRIBUTES_H 1

#include "swiftdds/dcps/DdsBaseTypes.h"
#include "swiftdds/rtps/PortParameters.h"
#include "swiftdds/rtps/Duration.h"
#include "swiftdds/rtps/Locator.h"
#include "swiftdds/rtps/TransportConfig/TransportConfigFactory.h"
#include "swiftdds/dcps/DeclExport.h"

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
 * @class LocalMode
 * @brief Local writer/reader mode.
 */
enum class LocalMode : gint32_t
{
    TURN_OFF = 0,
    TURN_ON = 1,
    // ALL_MSG = 2
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
    inline gbool_t metatraffic_unicast_empty() const noexcept
    {
        return (m_metatrafficUnicastLocatorList.empty());
    }

    /**
     * @brief Get a metatraffic unicast locator.
     * @param [in] an_index The index of a locator.
     * @return gstone::rtps::Locator_t A metatraffic unicast locator.
     */
    inline gstone::rtps::Locator_t metatraffic_unicast_at(guint32_t const an_index) const noexcept
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
     * @return All of the metatraffic unicast locators.
     */
    inline gstone::rtps::LocatorList_t const &metatraffic_unicast_locators() const noexcept
    {
        return this->m_metatrafficUnicastLocatorList;
    }

    /**
     * @brief Get all of the metatraffic unicast locators.
     * @return All of the metatraffic unicast locators.
     */
    inline gstone::rtps::LocatorList_t &metatraffic_unicast_locators() noexcept
    {
        return this->m_metatrafficUnicastLocatorList;
    }

    /**
     * @brief Get all of the metatraffic multicast locators that can be used to send messages to the built-in Endpoints
     * contained in the Participant.
     * @return All of the metatraffic multicast locators.
     */
    inline gstone::rtps::LocatorList_t const &metatraffic_multicast_locators() const noexcept
    {
        return this->m_metatrafficMulticastLocatorList;
    }

    /**
     * @brief Get all of the metatraffic multicast locators that can be used to send messages to the built-in Endpoints
     * contained in the Participant.
     * @return All of the metatraffic multicast locators.
     */
    inline gstone::rtps::LocatorList_t &metatraffic_multicast_locators() noexcept
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
     * @return The domain id in this object.
     */
    inline guint32_t domain_id() const noexcept
    {
        return m_domainId;
    }

    /**
     * @brief Get the domain tag.
     * @return The domain tag in this object.
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
     * @return The const reference of port parameters in this object.
     */
    inline gstone::rtps::PortParameters const &port_param() const noexcept
    {
        return m_portParam;
    }

    /**
     * @brief Get port parameters.
     * @return The reference of port parameters in this object.
     */
    inline gstone::rtps::PortParameters &port_param() noexcept
    {
        return m_portParam;
    }

    /**
     * @brief Get the period of send SPDP message.
     * @return The period of send SPDP message.
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
    inline gvoid_t add_meta_unicast_locator(gstone::rtps::Locator_t const &a_locator) noexcept
    {
        m_metatrafficUnicastLocatorList.push_back(a_locator);
    }

    /**
     * @brief Add a metatraffic unicast address.
     * @param [in] the_address The address used to discover.
     */
    inline gvoid_t add_meta_unicast_address(gchar_t const *const the_address) noexcept
    {
        m_metatrafficUnicastLocatorList.push_back(gstone::rtps::Locator_t(gstone::rtps::LOCATOR_KIND_UDPv4, 0U, the_address));
    }

    /**
     * @brief Add a metatraffic multicast locator.
     * @param [in] a_locator A locator used to add.
     */
    inline gvoid_t add_meta_multicast_locator(gstone::rtps::Locator_t const &a_locator) noexcept
    {
        m_metatrafficMulticastLocatorList.push_back(a_locator);
    }

    /**
     * @brief Add a metatraffic multicast address.
     * @param [in] the_address The address used to discover.
     */
    inline gvoid_t add_meta_multicast_address(gchar_t const *const the_address) noexcept
    {
        m_metatrafficMulticastLocatorList.push_back(gstone::rtps::Locator_t(gstone::rtps::LOCATOR_KIND_UDPv4, 0U, the_address));
    }

    /**
     * @brief Set lease duration. This value decided how long a Participant should be considered alive every time an
     * announcement is received from the Participant.
     * @param [in] a_duration Duration used to set.
     */
    inline gvoid_t lease_duration(gstone::rtps::Duration_t const &a_duration) noexcept
    {
        m_leaseDuration = a_duration;
    }

    /**
     * @brief Get lease duration. This value decided how long a Participant should be considered alive every time an
     * announcement is received from the Participant.
     * @return The lease duration value.
     */
    inline gstone::rtps::Duration_t const &lease_duration() const noexcept
    {
        return m_leaseDuration;
    }

    /**
     * @brief Get default remote unicast locators.
     * @return The default remote unicast locators.
     */
    inline gstone::rtps::LocatorList_t const &default_remote_unicast_locators() const noexcept
    {
        return m_defaultRemoteUnicastLocatorList;
    }

    /**
     * @brief Set default remote unicast locators.
     * @param [in] a_locator_list Locators used to set.
     */
    inline gvoid_t default_remote_unicast_locators(gstone::rtps::LocatorList_t const &a_locator_list) noexcept
    {
        m_defaultRemoteUnicastLocatorList = a_locator_list;
    }

    /**
     * @brief Get default remote multicast locators.
     * @return The default remote multicast locators.
     */
    inline gstone::rtps::LocatorList_t const &default_remote_multicast_locators() const noexcept
    {
        return m_defaultRemoteMulticastLocatorList;
    }

    /**
     * @brief Set default remote multicast locators.
     * @param [in] a_locator_list The default remote multicast locators used to set
     */
    inline gvoid_t default_remote_multicast_locators(gstone::rtps::LocatorList_t const &a_locator_list) noexcept
    {
        m_defaultRemoteMulticastLocatorList = a_locator_list;
    }

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
     * @brief The move assignment operator.
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
     * @brief Get heartbeat response delay.
     * @return The heartbeat response delay value.
     */
    inline gstone::rtps::Duration_t const &heartbeat_response_delay() const noexcept
    {
        return m_heartbeatResponseDelay;
    }

    /**
     * @brief Set heartbeat response delay.
     * @param [in] a_duration The heartbeat response delay value used to set.
     */
    inline gvoid_t heartbeat_response_delay(gstone::rtps::Duration_t const &a_duration) noexcept
    {
        m_heartbeatResponseDelay = a_duration;
    }

    /**
     * @brief Get heartbeat suppression duration.
     * @return The heartbeat suppression duration value.
     */
    inline gstone::rtps::Duration_t const &heartbeat_suppression_duration() const noexcept
    {
        return m_heartbeatSuppressionDuration;
    }
    /**
     * @brief Set heartbeat suppression duration.
     * @param [in] a_duration The heartbeat suppression duration value used to set.
     */
    inline gvoid_t heartbeat_suppression_duration(gstone::rtps::Duration_t const &a_duration) noexcept
    {
        m_heartbeatSuppressionDuration = a_duration;
    }

    /**
     * @brief Get heartbeat period.
     * @return The heartbeat period value.
     */
    inline gstone::rtps::Duration_t const &heartbeat_period() const noexcept
    {
        return m_heartbeatPeriod;
    }

    /**
     * @brief Set heartbeat period.
     * @param [in] a_duration The heartbeat period value.
     */
    inline gvoid_t heartbeat_period(gstone::rtps::Duration_t const &a_duration) noexcept
    {
        m_heartbeatPeriod = a_duration;
    }

    /**
     * @brief Get nack response delay.
     * @return The nack response delay value.
     */
    inline gstone::rtps::Duration_t const &nack_response_delay() const noexcept
    {
        return m_nackResponseDelay;
    }

    /**
     * @brief Set nack response delay.
     * @param [in] a_duration The nack response delay value used to set.
     */
    inline gvoid_t nack_response_delay(gstone::rtps::Duration_t const &a_duration) noexcept
    {
        m_nackResponseDelay = a_duration;
    }

    /**
     * @brief Get nack suppression duration.
     * @return The nack suppression duration value.
     */
    inline gstone::rtps::Duration_t const &nack_suppression_duration() const noexcept
    {
        return m_nackSuppressionDuration;
    }

    /**
     * @brief Set nack suppression duration.
     * @param [in] a_duration The nack suppression duration value used to set.
     */
    inline gvoid_t nack_suppression_duration(gstone::rtps::Duration_t const &a_duration) noexcept
    {
        m_nackSuppressionDuration = a_duration;
    }

    /**
     * @brief Getter of pre_emptive_acknack_duration
     * @return gstone::rtps::Duration_t The value of pre_emptive_acknack_duration
     */
    inline gstone::rtps::Duration_t const& pre_emptive_acknack_duration() const noexcept 
    {
        return m_preEmptiveAckNackDuration;
    }

    /**
     * @brief Setter of pre_emptive_acknack_duration
     * @param [in] _duration The value of pre_emptive_acknack_duration
     */
    inline void pre_emptive_acknack_duration(gstone::rtps::Duration_t const& _duration) noexcept
    {
        m_preEmptiveAckNackDuration = _duration;
    }

    /**
    * @brief This function gets the value of 'm_readerActiveDuration' parameter.
    * @return Return guint32_t.
    * @retval If the writer receives a DataReader's acknack from last received is smaller than 'm_readerActiveDuration',
    * DataReader is active. Otherwhise DataReader is inactive.
    */
    inline guint32_t const& reader_active_duration() const noexcept 
    {
        return m_readerActiveDuration;
    }

    /**
    * @brief This function sets the value of 'm_readerActiveDuration' parameter.
    * @param [in] a_reader_active_duration Const reference of a guint32_t, the unit is ms.
    */
    inline void reader_active_duration(guint32_t const& a_reader_active_duration) noexcept 
    {
        m_readerActiveDuration = a_reader_active_duration;
    }

    /**
     * @brief Construct a new Simple E D P Attributes object.
     */
    SEDPAttributes() = default;

private:
    static constexpr guint64_t hb_rsp_miseconds {100U};
    static constexpr guint64_t hb_sup_miseconds {1U};
    static constexpr guint64_t hb_period_miseconds {200U};
    static constexpr guint64_t ncak_rsp_miseconds {5U};
    static constexpr guint64_t nack_sup_miseconds {1U};
    static constexpr guint32_t default_reader_active_duration{10000U};
    gbool_t m_useDataWriters {true};

    gbool_t m_useDataReaders {true};

    gstone::rtps::Duration_t m_heartbeatResponseDelay {Duration_t(hb_rsp_miseconds)};
    gstone::rtps::Duration_t m_heartbeatSuppressionDuration {Duration_t(hb_sup_miseconds)};

    gstone::rtps::Duration_t m_heartbeatPeriod {Duration_t(hb_period_miseconds)};
    gstone::rtps::Duration_t m_nackResponseDelay {Duration_t(ncak_rsp_miseconds)};
    gstone::rtps::Duration_t m_nackSuppressionDuration {Duration_t(nack_sup_miseconds)};

    gstone::rtps::Duration_t m_preEmptiveAckNackDuration {gstone::rtps::Duration::duration_infinite()};
    
    guint32_t m_readerActiveDuration{ default_reader_active_duration };
};

/**
 * @brief
 */
class GS_DDS4CPP_API ParticipantAttributes final
{
public:
    /**
     * @brief Construct a new Participant Attributes object.
     */
    ParticipantAttributes() = default;

    /**
     * @brief Destroy the Participant Attributes object.
     */
    ~ParticipantAttributes() noexcept = default;

    /**
     * @brief Construct a new Participant Attributes.
     */
    ParticipantAttributes(ParticipantAttributes const &) = default;

    /**
     * @brief The copy assignment operator.
     * @return The reference of a new ParticipantAttributes object.
     */
    ParticipantAttributes &operator=(ParticipantAttributes const &) = default;

    /**
     * @brief Construct a new Participant Attributes object
     */
    ParticipantAttributes(ParticipantAttributes &&) = default;

    /**
     * @brief The move assignment operator.
     * @return The reference of a new ParticipantAttributes object.
     */
    ParticipantAttributes &operator=(ParticipantAttributes &&) = default;
public:
    /**
     * @brief Get const reference of spdp attributes.
     * @return The const reference of spdp attributes object.
     */
    inline SPDPAttributes const &spdp_attributes() const noexcept
    {
        return this->m_spdpAttributes;
    }

    /**
     * @brief Get reference of spdp attributes.
     * @return The reference of spdp attributes object.
     */
    inline SPDPAttributes &spdp_attributes() noexcept
    {
        return this->m_spdpAttributes;
    }

    /**
     * @brief Set spdp attributes.
     * @param [in] a_attributes The spdp attributes object used to set.
     */
    inline gvoid_t spdp_attributes(SPDPAttributes const &a_attributes) noexcept
    {
        this->m_spdpAttributes = a_attributes;
    }

    /**
     * @brief Get whether used wlp.
     * @return The flag whether used wlp.
     */
    inline gbool_t used_wlp() const noexcept
    {
        return this->m_useWLP;
    }

    /**
     * @brief Set used wlp flag.
     * @param [in] used_flag The flag used to set.
     */
    inline gvoid_t used_wlp(gbool_t const used_flag) noexcept
    {
        this->m_useWLP = used_flag;
    }

    /**
     * @brief Add a locator to spdp attributes.
     * @param [in] a_locator The locator used to set.
     */
    inline gvoid_t add_meta_unicast_locator(gstone::rtps::Locator_t const &a_locator) noexcept
    {
        m_spdpAttributes.add_meta_unicast_locator(a_locator);
    }

    /**
     * @brief Get default unicast locatorlist.
     * @return The const reference of default unicast locatorlist.
     */
    inline gstone::rtps::LocatorList_t const &default_unicast_locatorlist() const noexcept
    {
        return m_defaultUnicastLocatorList;
    }

    /**
     * @brief Get default unicast locatorlist.
     * @return The reference of default unicast locatorlist.
     */
    inline gstone::rtps::LocatorList_t &default_unicast_locatorlist() noexcept
    {
        return m_defaultUnicastLocatorList;
    }

    /**
     * @brief Set default unicast locatorlist.
     * @param [in] a_locator_list The locatorlist used to set.
     */
    inline gvoid_t default_unicast_locatorlist(gstone::rtps::LocatorList_t const &a_locator_list) noexcept
    {
        m_defaultUnicastLocatorList = a_locator_list;
    }

    /**
     * @brief  Get default multicast locatorlist.
     * @return The const reference of default multicast locatorlist.
     */
    inline gstone::rtps::LocatorList_t const &default_multicast_locatorlist() const noexcept
    {
        return m_defaultMulticastLocatorList;
    }

    /**
     * @brief  Get default multicast locatorlist.
     * @return The reference of default multicast locatorlist.
     */
    inline gstone::rtps::LocatorList_t &default_multicast_locatorlist() noexcept
    {
        return m_defaultMulticastLocatorList;
    }

    /**
     * @brief Set default multicast locatorlist.
     * @param [in] a_locator_list The locator list used to set.
     */
    inline gvoid_t default_multicast_locatorlist(gstone::rtps::LocatorList_t const &a_locator_list) noexcept
    {
        m_defaultMulticastLocatorList = a_locator_list;
    }

    /**
     * @brief Get participant id.
     * @return The participant id value.
     */
    inline guint32_t participant_id() const noexcept
    {
        return m_participantID;
    }

    /**
     * @brief Set participant id.
     * @param [in] a_participant_id The participant id value uesd to set
     */
    inline gvoid_t participant_id(guint32_t const a_participant_id) noexcept
    {
        m_participantID = a_participant_id;
    }

    /**
     * @brief Get sedp attributes.
     * @return The sedp attributes object.
     */
    inline SEDPAttributes const &sedp_attributes() const noexcept
    {
        return m_sedpAttributes;
    }

    /**
     * @brief Set sedp attributes.
     * @param [in] the_attributes The sedp attributes object used to set.
     */
    inline gvoid_t sedp_attributes(SEDPAttributes const &the_attributes) noexcept
    {
        m_sedpAttributes = the_attributes;
    }

    /**
     * @brief Get receive mode kind.
     * @return The receive mode kind.
     */
    inline RecvMode_t recv_mode() const noexcept
    {
        return m_recvMode;
    }

    /**
     * @brief Set receive mode kind.
     * @param [in] the_recv_mode The receive mode kind used to set.
     */
    inline gvoid_t recv_mode(RecvMode_t const the_recv_mode) noexcept
    {
        m_recvMode = the_recv_mode;
    }

    /**
     * @brief Get async thread size.
     * @return The async thread size value.
     */
    inline guint32_t async_thread_size() const noexcept
    {
        return m_asyncThreadSize;
    }

    /**
     * @brief Set async thread size.
     * @param [in] the_async_thread_size The async thread size value used to set.
     */
    inline gvoid_t async_thread_size(guint32_t const the_async_thread_size) noexcept
    {
        if (the_async_thread_size != 0U)
        {
            m_asyncThreadSize = the_async_thread_size;
        }
    }

    /**
     * @brief Get async max buffer size.
     * @return The async max buffer size value.
     */
    inline guint32_t async_max_buffer_size() const noexcept
    {
        return m_asyncMaxBufferSize;
    }

    /**
     * @brief Set async max buffer size.
     * @param [in] the_async_max_buffer_size The async max buffer size value used to set.
     *             0 means Infinite.
     */
    inline gvoid_t async_max_buffer_size(guint32_t const the_async_max_buffer_size) noexcept
    {
        m_asyncMaxBufferSize = the_async_max_buffer_size;
    }

    /**
     * @brief Get whether use ipv6.
     * @return The flag whether use ipv6.
     */
    inline gbool_t use_ipv6() const noexcept
    {
        return m_useIpv6;
    }

    /**
     * @brief Set use ipv6 flag.
     * @param [in] used_flag The flag used to set.
     */
    inline gvoid_t use_ipv6(gbool_t const used_flag) noexcept
    {
        m_useIpv6 = used_flag;
    }

    /**
     * @brief Get shared memory size.
     * @return The shared memory size value.
     */
    inline guint32_t shared_memory_size() const noexcept
    {
        return m_sharedMemorySize;
    }

    /**
     * @brief Set shared memory size.
     * @param [in] the_memory_size The shared memory size value used to set.
     */
    inline gvoid_t shared_memory_size(guint32_t const the_memory_size) noexcept
    {
        m_sharedMemorySize = the_memory_size;
    }

    /**
     * @brief Get whether use xtypes.
     * @return The flag whether use xtypes.
     */
    inline gbool_t use_xtypes() const noexcept
    {
        return m_useXtypes;
    }

    /**
     * @brief Set use xtypes flag.
     * @param [in] used_flag The flag used to set.
     */
    inline gvoid_t use_xtypes(gbool_t const used_flag) noexcept
    {
        m_useXtypes = used_flag;
    }

    /**
     * @brief Get handle
     */
    inline gvoid_t *const sec_handle() const noexcept
    {
        return m_secHandle;
    }

    /**
     * @brief Set handle 
     * @param [in] a_handle The handle used to set.
     */
    inline gvoid_t sec_handle(gvoid_t *const a_handle) noexcept
    {
        m_secHandle = a_handle;
    }

    /**
     * @brief Get whether enable monitoring.
     * @return The flag whether enable monitoring.
     */
    inline gbool_t enable_monitoring() const noexcept
    {
        return m_enableMonitoring;
    }

    /**
     * @brief Set enable monitoring flag.
     * @param [in] used_flag The flag used to set.
     */
    inline gvoid_t enable_monitoring(gbool_t const used_flag) noexcept
    {
        m_enableMonitoring = used_flag;
    }

    /**
     * @brief Get whether enable distlog.
     * @return The flag whether enable monitoring.
     */
    inline gbool_t enable_distlog() const noexcept
    {
        return m_enableDistlog;
    }

    /**
     * @brief Set enable distlog flag.
     * @param [in] used_flag The flag whether enable distlog.
     */
    inline gvoid_t enable_distlog(gbool_t const used_flag) noexcept
    {
        m_enableDistlog = used_flag;
    }

    /**
     * @brief Get local writer/reader kind.
     * @return The local mode kind.
     */
    inline LocalMode local_mode() const noexcept
    {
        return m_localMode;
    }

    /**
     * @brief Set local writer/reader mode.
     * @param [in] mode The local mode kind used to set.
     */
    inline void local_mode(LocalMode const mode) noexcept
    {
        m_localMode = mode;
    }

    /**
     * @brief check local mode is TURN_ON or not
     * @return true if the local mode is TURN_ON
     * @return false if the local mode is set to TURN_OFF
     */
    inline bool local_mode_is_on() const noexcept
    {
        return m_localMode == LocalMode::TURN_ON;
    }

    /**
     * @brief check local mode is TURN_OFF or not
     * @return true if the local mode is TURN_OFF
     * @return false if the local mode is TURN_ON
     */
    inline bool local_mode_is_off() const noexcept
    {
        return m_localMode == LocalMode::TURN_OFF;
    }

    /**
     * @brief Add a transport instance to unicast transport list.
     * @param [in] kind Transport kind.
     * @param [in] port Transport port.
     * @param [in] addr Ip of host.
     */
    inline void add_unicast_transport(gint32_t const kind, guint32_t const port, gchar_t const *const addr) noexcept
    {
        if (kind != LOCATOR_KIND_UDPv4)
        {
            if (std::any_of(m_unicastTransportList.cbegin(), m_unicastTransportList.cend(),
                [kind, port, addr](std::shared_ptr<TransportConfig> const &tc) noexcept ->gbool_t
                {
                    bool const c1{tc->kind() == kind};
                    bool const c2{tc->port() == port};
                    bool const c3{memcmp(tc->addr().data(), addr, strlen(addr)) == 0};
                    return c1 && c2 && c3;
                }))
            {
                return;
            }

            std::shared_ptr<TransportConfig> const transport{TransportConfigFactory::create_transport_config(kind, port, addr)};
            if (transport != nullptr)
            {
                m_unicastTransportList.push_back(transport);
            }
        }
    }

    inline void check_unicast_transport(LocatorList_t const &locList, Locator_t const &locator) noexcept
    {
        for (auto &unicast_transport : m_unicastTransportList)
        {
            decltype(locList.begin()) const it {std::find_if(locList.begin(),locList.end(),[&unicast_transport](Locator_t const &loc) noexcept -> gbool_t {
                return (unicast_transport->addr() == loc.address());
            })};
            if (it == locList.end())
            {
                unicast_transport->update_addr(locator.address());
            }
        }
    }

    /**
     * @brief Add a transport instance to multicast transport list.
     * @param [in] kind Transport kind.
     * @param [in] port Transport port.
     * @param [in] addr Ip of host.
     */
    inline void add_multicast_transport(gint32_t const kind, guint32_t const port, gchar_t const *const addr) noexcept
    {
        if (kind != LOCATOR_KIND_UDPv4)
        {
            if (std::any_of(m_multicastTransportList.cbegin(), m_multicastTransportList.cend(),
                [kind, port, addr](std::shared_ptr<TransportConfig> const &tc) noexcept ->gbool_t
                {
                    bool const c1{tc->kind() == kind};
                    bool const c2{tc->port() == port};
                    bool const c3{memcmp(tc->addr().data(), addr, strlen(addr)) == 0};
                    return c1 && c2 && c3;}
                ))
            {
                return;
            }

            std::shared_ptr<TransportConfig> const transport{TransportConfigFactory::create_transport_config(kind, port, addr)};
            if (transport != nullptr)
            {
                m_multicastTransportList.push_back(transport);
            }
        }
    }

    /**
     * @brief Query unicast transport list.
     */
    inline TransportList_t unicast_transport_list() const noexcept
    {
        return m_unicastTransportList;
    }

    /**
     * @brief Query multicast transport list.
     */
    inline TransportList_t multicast_transport_list() const noexcept
    {
        return m_multicastTransportList;
    }

    /**
     * @brief Clear unicast transport list.
     */
    inline gvoid_t clear_unicast_transport_list() noexcept
    {
        m_unicastTransportList.clear();
    }

    /**
     * @brief Clear multicast transport list.
     */
    inline gvoid_t clear_multicast_transport_list() noexcept
    {
        m_multicastTransportList.clear();
    }

    /**
     * @brief Get ConcurrencyControlQosPolicy.
     * @return The ConcurrencyControlQosPolicy object.
     */
    inline dds::qos::ConcurrencyControlQosPolicy const &concurrency_control() const noexcept
    {
        return m_concurrencyControl;
    }

    /**
     * @brief Set ConcurrencyControlQosPolicy.
     * @param [in] _policy The ConcurrencyControlQosPolicy object used to set.
     */
    inline gvoid_t concurrency_control(dds::qos::ConcurrencyControlQosPolicy const &_policy) noexcept
    {
        m_concurrencyControl = _policy;
    }

    inline gbool_t use_buildin_transports_port() const noexcept
    {
        return m_use_buildin_transport_port;
    }

    inline gvoid_t use_buildin_transports_port(gbool_t const &use_buildin_transport_port) noexcept
    {
        m_use_buildin_transport_port = use_buildin_transport_port;
    }

    inline guint32_t use_send_transports_port() const noexcept
    {
        return m_use_send_transport_port;
    }

    inline gvoid_t use_send_transports_port(guint32_t const &use_send_transport_port) noexcept
    {
        m_use_send_transport_port = use_send_transport_port;
    }

    inline gvoid_t send_optional_qos(gbool_t const val) noexcept
    {
        m_sendOptionalQos = val;
    }

    inline gbool_t send_optional_qos() const noexcept
    {
        return m_sendOptionalQos;
    }

    inline gvoid_t data_use_shared_memory(gbool_t const val) noexcept
    {
        m_dataUseSharedMemory = val;
    }

    inline gbool_t data_use_shared_memory() const noexcept
    {
        return m_dataUseSharedMemory;
    }

private:
    LocatorList_t m_defaultUnicastLocatorList {};
    LocatorList_t m_defaultMulticastLocatorList {};

    TransportList_t m_unicastTransportList{};
    TransportList_t m_multicastTransportList{};

    SPDPAttributes m_spdpAttributes;

    SEDPAttributes m_sedpAttributes;

    guint32_t m_participantID {DDS::PARTICIPANT_ID_AUTO};

    RecvMode_t m_recvMode {RecvMode_t::AsyncRecvMode};
    guint32_t m_asyncThreadSize{1U};
    guint32_t m_asyncMaxBufferSize{0U};

    gbool_t m_useBuiltinTransports {true};
    gbool_t m_useWLP {false};
    gbool_t m_useIpv6 {false};

    guint32_t m_sharedMemorySize {100U * 1024U * 1024U};

    gbool_t m_useXtypes {false};

    gvoid_t *m_secHandle {nullptr};

    gbool_t m_enableMonitoring {false};
    gbool_t m_enableDistlog {false};

    LocalMode m_localMode {LocalMode::TURN_ON};

    dds::qos::ConcurrencyControlQosPolicy m_concurrencyControl{};

    gbool_t m_use_buildin_transport_port {true};

    guint32_t m_use_send_transport_port {DDS::DEFAULT_SEND_PORT};

    gbool_t m_sendOptionalQos {false};

    gbool_t m_dataUseSharedMemory {false};
};

} /*rtps*/
} /*gstone*/

__GS_DDS4CPP_END_DECLS

#endif /*GSTONE_RTPS_PARTICIPANTATTRIBUTES_H*/
