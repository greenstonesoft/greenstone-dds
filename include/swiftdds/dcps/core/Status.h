/**************************************************************
* @file Status.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_STATUS_API_H
#define GSTONE_STATUS_API_H 1

#include "swiftdds/dcps/DdsBaseTypes.h"
#include "swiftdds/dcps/qos/QosPolicyCount.h"
#include "swiftdds/dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds {
namespace core {
/**
* @class BaseStatus
* @brief BaseStatus is the abstract root class for all communication status objects. All concrete kinds of BaseStatus classes specialize this class.
* @note Each concrete Entity is associated with a set of BaseStatus objects whose value represents the "communication status" of that entity.
*/
class GS_DDS4CPP_API BaseStatus
{
public:
    /**
     * @brief Construct a new BaseStatus object with default parameter.
     */
    BaseStatus() noexcept = default;

    /**
     * @brief Destroy the BaseStatus object.
     */
    virtual ~BaseStatus() = default;

    /**
     * @brief This operation gets total cumulative count of samples caused by BaseStatus.
     * @return Total cumulative count of samples caused by BaseStatus. 
     * @note Return value is const.
     */
    inline gint32_t total_count() const noexcept
    {
        return m_totalCount;
    }

    /**
     * @brief This operation gets the incremental number of samples caused by BaseStatus.
     * @return The incremental number of samples caused by BaseStatus. 
     * @note Return value is const.
     */
    inline gint32_t total_count_change() const noexcept
    {
        return m_totalCountChange;
    }

    /**
     * @brief This operation sets total cumulative count of samples caused by BaseStatus.
     * @param [in] in_total_count Total cumulative count of samples caused by BaseStatus.
     * @note Input value is const.
     */
    inline void total_count(gint32_t const in_total_count) noexcept
    {
        m_totalCount = in_total_count;
    }

    /**
     * @brief This operation sets the incremental number of samples caused by BaseStatus.
     * @param [in] in_total_count_change The incremental number of samples caused by BaseStatus.
     * @note Input value is const.
     */
    inline void total_count_change(gint32_t const in_total_count_change) noexcept
    {
        m_totalCountChange = in_total_count_change;
    }

protected:
    /**
     * @brief Construct a new BaseStatus object with copying BaseStatus object.
     * @param [in] a_base_status A new BaseStatus object is created by copying this BaseStatus object.
     */
    BaseStatus(BaseStatus const& a_base_status) = default;

    /**
     * @brief Construct a new Base Status object with moving BaseStatus object.
     * @param [in] a_base_status A new BaseStatus object is created by moving this BaseStatus object.
     */
    BaseStatus(BaseStatus && a_base_status) = default;

    /**
     * @brief Copy a BaseStatus object with a BaseStatus object.
     * @param [in] a_base_status The BaseStatus object that need to copy.
     * @return BaseStatus object that after copying.
     */
    BaseStatus& operator=(BaseStatus const& a_base_status) = default;

    /**
     * @brief Move a BaseStatus object with a BaseStatus object.
     * @param [in] a_base_status The BaseStatus object that need to move.
     * @return BaseStatus object that after moving.
     */
    BaseStatus& operator=(BaseStatus && a_base_status) = default;

private:
    gint32_t m_totalCount {0};
    gint32_t m_totalCountChange {0};
};

/**
* @class SampleLostStatus
* @brief A sample has been lost (never received).
* @note SampleLostStatus only have total_count and total_count_change attribute.
*/
class GS_DDS4CPP_API SampleLostStatus : public BaseStatus
{
public:
    /**
     * @brief Construct a new SampleLostStatus object with default parameter.
     */
    SampleLostStatus() noexcept = default;

    /**
     * @brief Destroy the SampleLostStatus object.
     */
    ~SampleLostStatus() noexcept override = default;

    /**
     * @brief Construct a new SampleLostStatus object with copying SampleLostStatus object.
     * @param [in] a_sample_lost_status A new SampleLostStatus object is created by copying this SampleLostStatus object.
     */
    SampleLostStatus(SampleLostStatus const & a_sample_lost_status) = default;

    /**
     * @brief Construct a new Base Status object with moving SampleLostStatus object.
     * @param [in] a_sample_lost_status A new SampleLostStatus object is created by moving this SampleLostStatus object.
     */
    SampleLostStatus(SampleLostStatus && a_sample_lost_status) = default;

    /**
     * @brief Copy a SampleLostStatus object with a SampleLostStatus object.
     * @param [in] a_sample_lost_status The SampleLostStatus object that need to copy.
     * @return SampleLostStatus object that after copying.
     */
    SampleLostStatus &operator=(SampleLostStatus const & a_sample_lost_status) = default;

    /**
     * @brief Move a SampleLostStatus object with a SampleLostStatus object.
     * @param [in] a_sample_lost_status The SampleLostStatus object that need to move.
     * @return SampleLostStatus object that after moving.
     */
    SampleLostStatus &operator=(SampleLostStatus && a_sample_lost_status) = default;

    /**
     * @brief This operation compares two SampleLostStatus are equal or not.
     * @param [in] lhs One of two SampleLostStatus.
     * @param [in] rhs Another of two SampleLostStatus.
     * @return Comparing SampleLostStatus result.
     * @retval true Two SampleLostStatus are equal.
     * @retval false Two SampleLostStatus are not equal. 
     */
    inline friend bool operator==(SampleLostStatus const &lhs, SampleLostStatus const &rhs) noexcept
    {
        gint32_t const lhs_total_count {lhs.total_count()};
        gint32_t const rhs_total_count  {rhs.total_count()};
        return (lhs_total_count == rhs_total_count);
    }
};

/**
* @class InconsistentTopicStatus
* @brief Another topic exists with the same name but different characteristics.
* @note InconsistentTopicStatus only have total_count and total_count_change attribute.
*/
class GS_DDS4CPP_API InconsistentTopicStatus : public BaseStatus
{
public:
    /**
     * @brief Construct a new InconsistentTopicStatus object with default parameter.
     */
    InconsistentTopicStatus() noexcept = default;

    /**
     * @brief Destroy the InconsistentTopicStatus object.
     */
    ~InconsistentTopicStatus() noexcept override = default;

    /**
     * @brief Construct a new InconsistentTopicStatus object with copying InconsistentTopicStatus object.
     * @param [in] an_inconsistent_topic_status A new InconsistentTopicStatus object is created by copying this InconsistentTopicStatus object.
     */
    InconsistentTopicStatus(InconsistentTopicStatus const & an_inconsistent_topic_status) = default;

    /**
     * @brief Construct a new Base Status object with moving InconsistentTopicStatus object.
     * @param [in] an_inconsistent_topic_status A new InconsistentTopicStatus object is created by moving this InconsistentTopicStatus object.
     */
    InconsistentTopicStatus(InconsistentTopicStatus && an_inconsistent_topic_status) = default;

    /**
     * @brief Copy a InconsistentTopicStatus object with a InconsistentTopicStatus object.
     * @param [in] an_inconsistent_topic_status The InconsistentTopicStatus object that need to copy.
     * @return InconsistentTopicStatus object that after copying.
     */
    InconsistentTopicStatus &operator=(InconsistentTopicStatus const & an_inconsistent_topic_status) = default;

    /**
     * @brief Move a InconsistentTopicStatus object with a InconsistentTopicStatus object. 
     * @param [in] an_inconsistent_topic_status The InconsistentTopicStatus object that need to move.
     * @return InconsistentTopicStatus object that after moving.
     */
    InconsistentTopicStatus &operator=(InconsistentTopicStatus && an_inconsistent_topic_status) = default;

    /**
     * @brief This operation compares two SampleLostStatus are equal or not.
     * @param [in] lhs One of two InconsistentTopicStatus.
     * @param [in] rhs Another of two InconsistentTopicStatus.
     * @return Comparing InconsistentTopicStatus result.
     * @retval true Two InconsistentTopicStatus are equal.
     * @retval false Two InconsistentTopicStatus are not equal. 
     */
    inline friend bool operator==(InconsistentTopicStatus const &lhs, InconsistentTopicStatus const &rhs) noexcept
    {
        gint32_t const lhs_total_count {lhs.total_count()};
        gint32_t const rhs_total_count  {rhs.total_count()};
        return (lhs_total_count == rhs_total_count);
    }
};

/**
* @class SampleRejectedStatus
* @brief A (received) sample has been rejected.
* @note SampleRejectedStatus have total_count, total_count_change, last_reason and last_instance_handle attribute.
*/
class GS_DDS4CPP_API SampleRejectedStatus : public BaseStatus
{
public:
    /**
     * @brief Construct a new SampleRejectedStatus object with default parameter.
     */
    SampleRejectedStatus()  = default;

    /**
     * @brief Destroy the SampleRejectedStatus object.
     */
    ~SampleRejectedStatus() noexcept override = default;

    /**
     * @brief Construct a new SampleRejectedStatus object with copying SampleRejectedStatus object.
     * @param [in] a_sample_rejected_status A new SampleRejectedStatus object is created by copying this SampleRejectedStatus object.
     */
    SampleRejectedStatus(SampleRejectedStatus const & a_sample_rejected_status) = default;

    /**
     * @brief Construct a new Base Status object with moving SampleRejectedStatus object.
     * @param [in] a_sample_rejected_status A new SampleRejectedStatus object is created by moving this SampleRejectedStatus object.
     */
    SampleRejectedStatus(SampleRejectedStatus && a_sample_rejected_status) = default;

    /**
     * @brief Copy a SampleRejectedStatus object with a SampleRejectedStatus object.
     * @param [in] a_sample_rejected_status The SampleRejectedStatus object that need to copy.
     * @return SampleRejectedStatus object that after copying.
     */
    SampleRejectedStatus &operator=(SampleRejectedStatus const & a_sample_rejected_status) = default;

    /**
     * @brief Move a SampleRejectedStatus object with a SampleRejectedStatus object.
     * @param [in] a_sample_rejected_status The SampleRejectedStatus object that need to move.
     * @return SampleRejectedStatus object that after moving.
     */
    SampleRejectedStatus &operator=(SampleRejectedStatus && a_sample_rejected_status) = default;

    /**
     * @brief This operation gets reason for rejecting the last sample rejected. 
     * @return Reason for rejecting the last sample rejected.
     * @note If no samples have been rejected, the reason is the special value NOT_REJECTED. Return value is const.
     */
    inline DDS::SampleRejectedStatusKind last_reason() const noexcept
    {
        return m_lastReason;
    }

    /**
     * @brief This operation gets handle to the instance being updated by the last sample that was rejected.
     * @return Handle to the instance.
     * @note Return value is const.
     */
    inline gstone::rtps::InstanceHandle_t const last_instance_handle() const noexcept
    {
        return m_lastInstanceHandle;
    }

    /**
     * @brief This operation sets reason for rejecting the last sample rejected. 
     * @param [in] in_last_reason Reason for rejecting.
     */
    inline void last_reason(DDS::SampleRejectedStatusKind const in_last_reason) noexcept
    {
        m_lastReason = in_last_reason;
    }

    /**
     * @brief This operation sets handle to the instance being updated by the last sample that was rejected.
     * @param [in] in_last_instance_handle Handle to the instance being updated by the last sample that was rejected.
     * @return Setting handle result.
     * @retval true Setting successfully.
     * @retval false Setting failed.
     */
    inline bool last_instance_handle(gstone::rtps::InstanceHandle_t const in_last_instance_handle) noexcept
    {
        if (&in_last_instance_handle == &m_lastInstanceHandle) 
        {
            return false;
        }
        m_lastInstanceHandle = in_last_instance_handle;
        return true;
    }

    /**
     * @brief This operation compares two SampleRejectedStatus are equal or not.
     * @param [in] lhs One of two SampleRejectedStatus.
     * @param [in] rhs Another of two SampleRejectedStatus.
     * @return Comparing SampleRejectedStatus result.
     * @retval true Two SampleRejectedStatus are equal.
     * @retval false Two SampleRejectedStatus are not equal.
     */
    inline friend bool operator==(SampleRejectedStatus const &lhs, SampleRejectedStatus const &rhs) noexcept
    {
        gint32_t const lhs_total_count {lhs.total_count()};
        gint32_t const rhs_total_count {rhs.total_count()};
        DDS::SampleRejectedStatusKind const lhs_last_reason {lhs.last_reason()};
        DDS::SampleRejectedStatusKind const rhs_last_reason {rhs.last_reason()};
        gstone::rtps::InstanceHandle_t const lhs_last_instance_handle {lhs.last_instance_handle()};
        gstone::rtps::InstanceHandle_t const rhs_last_instance_handle {rhs.last_instance_handle()};
        return (lhs_total_count == rhs_total_count) && (lhs_last_reason == rhs_last_reason) &&
               (lhs_last_instance_handle == rhs_last_instance_handle);
    }
private:
    DDS::SampleRejectedStatusKind m_lastReason {DDS::SampleRejectedStatusKind::NOT_REJECTED};
    gstone::rtps::InstanceHandle_t m_lastInstanceHandle {0};
};

/**
* @class PublicationMatchedStatus
* @brief The DataWriter has found DataReader that matches the Topic and has 
* compatible QoS, or has ceased to be matched with a DataReader that was previously considered to be matched.
* @note PublicationMatchedStatus have total_count, total_count_change, current_count, current_count_change and last_subscription_handle attribute.
*/
class GS_DDS4CPP_API PublicationMatchedStatus : public BaseStatus
{
public:
    /**
     * @brief Construct a new PublicationMatchedStatus object with default parameter.
     */
    PublicationMatchedStatus() = default;

    /**
     * @brief Destroy the PublicationMatchedStatus object.
     */
    ~PublicationMatchedStatus() noexcept override = default;

    /**
     * @brief Construct a new PublicationMatchedStatus object with copying PublicationMatchedStatus object.
     * @param [in] a_publication_matched_status A new PublicationMatchedStatus object is created by copying this PublicationMatchedStatus object.
     */
    PublicationMatchedStatus(PublicationMatchedStatus const & a_publication_matched_status) = default;

    /**
     * @brief Construct a new Base Status object with moving PublicationMatchedStatus object.
     * @param [in] a_publication_matched_status A new PublicationMatchedStatus object is created by moving this PublicationMatchedStatus object.
     */
    PublicationMatchedStatus(PublicationMatchedStatus && a_publication_matched_status) = default;

    /**
     * @brief Copy a PublicationMatchedStatus object with a PublicationMatchedStatus object.
     * @param [in] a_publication_matched_status The PublicationMatchedStatus object that need to copy.
     * @return PublicationMatchedStatus object that after copying.
     */
    PublicationMatchedStatus &operator=(PublicationMatchedStatus const & a_publication_matched_status) = default;

    /**
     * @brief Move a PublicationMatchedStatus object with a PublicationMatchedStatus object.
     * @param [in] a_publication_matched_status The PublicationMatchedStatus object that need to move.
     * @return PublicationMatchedStatus object that after moving.
     */
    PublicationMatchedStatus &operator=(PublicationMatchedStatus && a_publication_matched_status) = default;

    /**
     * @brief This operation gets the number of DataReaders currently matched to the concerned DataWriter.
     * @return The number of DataReaders currently matched.
     * @note Return value is const.
     */
    inline gint32_t current_count() const noexcept
    {
        return m_currentCount;
    }

    /**
     * @brief This operation gets the change in current_count since the last time the listener was called or the status was read.
     * @return The change in current_count since the last time the listener was called or the status was read. 
     * @note Return value is const.
     */
    inline gint32_t current_count_change() const noexcept
    {
        return m_currentCountChange;
    }

    /**
     * @brief This operation gets handle to the last DataReader that matched the DataWriter causing the status to change.
     * @return Handle to the last DataReader that matched the DataWriter. 
     * @note Return value is const.
     */
    inline gstone::rtps::InstanceHandle_t const last_subscription_handle() const noexcept
    {
        return m_lastSubscriptionHandle;
    }

    /**
     * @brief This operation sets the number of DataReaders currently matched to the concerned DataWriter.
     * @param [in] in_current_count The number of DataReaders currently matched.
     * @note Input value is const.
     */
    inline void current_count(gint32_t const in_current_count) noexcept
    {
        m_currentCount = in_current_count;
    }

    /**
     * @brief This operation sets the change in current_count since the last time the listener was called or the status was read.
     * @param [in] in_current_count_change The change in current_count since the last time the listener was called or the status was read.
     * @note Input value is const.
     */
    inline void current_count_change(gint32_t const in_current_count_change) noexcept
    {
        m_currentCountChange = in_current_count_change;
    }

    /**
     * @brief This operation sets handle to the last DataReader that matched the DataWriter causing the status to change.
     * @param [in] in_last_subscription_handle Handle to the last DataReader that matched the DataWriter.
     * @return Setting last_subscription_handle result.
     * @retval true Setting last_subscription_handle result successfully.
     * @retval false Setting last_subscription_handle result failed.  
     */
    inline bool last_subscription_handle(gstone::rtps::InstanceHandle_t const &in_last_subscription_handle) noexcept
    {
        if (&in_last_subscription_handle == &m_lastSubscriptionHandle) 
        {
            return false;
        }
        m_lastSubscriptionHandle = in_last_subscription_handle;
        return true;
    }

    /**
     * @brief This operation compares two PublicationMatchedStatus are equal or not.
     * @param [in] lhs One of two PublicationMatchedStatus.
     * @param [in] rhs Another of two PublicationMatchedStatus.
     * @return Comparing PublicationMatchedStatus result.
     * @retval true Two PublicationMatchedStatus are equal.
     * @retval false Two PublicationMatchedStatus are not equal.
     */
    inline friend bool operator==(PublicationMatchedStatus const &lhs, PublicationMatchedStatus const &rhs) noexcept
    {
        gint32_t const lhs_total_count {lhs.total_count()};
        gint32_t const rhs_total_count {rhs.total_count()};
        gint32_t const lhs_current_count {lhs.current_count()};
        gint32_t const rhs_current_count {rhs.current_count()};
        gstone::rtps::InstanceHandle_t const lhs_last_subscription_handle {lhs.last_subscription_handle()};
        gstone::rtps::InstanceHandle_t const rhs_last_subscription_handle {rhs.last_subscription_handle()};
        return (lhs_total_count == rhs_total_count) && (lhs_current_count == rhs_current_count) &&
               (lhs_last_subscription_handle == rhs_last_subscription_handle);
    }
private:
    gint32_t m_currentCount {0};
    gint32_t m_currentCountChange {0};
    gstone::rtps::InstanceHandle_t m_lastSubscriptionHandle {0};
};

/**
* @class LivelinessChangedStatus
* @brief The liveliness of one or more DataWriter that were writing instances read 
* through the DataReader has changed. Some DataWriter have become "active" or "inactive."
* @note LivelinessChangedStatus have alive_count, not_alive_count, alive_count_change
* , not_alive_count_change, last_publication_handle, total_count and total_count_change attribute.
*/
class GS_DDS4CPP_API LivelinessChangedStatus final
{
public:
    /**
     * @brief Construct a new LivelinessChangedStatus object with default parameter.
     */
    LivelinessChangedStatus() = default;

    /**
     * @brief Destroy the LivelinessChangedStatus object.
     */
    ~LivelinessChangedStatus() noexcept = default;

    /**
     * @brief Construct a new LivelinessChangedStatus object with copying LivelinessChangedStatus object.
     * @param [in] a_liveliness_changed_status A new LivelinessChangedStatus object is created by copying this LivelinessChangedStatus object.
     */
    LivelinessChangedStatus(LivelinessChangedStatus const & a_liveliness_changed_status) = default;

    /**
     * @brief Construct a new Base Status object with moving LivelinessChangedStatus object.
     * @param [in] a_liveliness_changed_status A new LivelinessChangedStatus object is created by moving this LivelinessChangedStatus object.
     */
    LivelinessChangedStatus(LivelinessChangedStatus && a_liveliness_changed_status) = default;

    /**
     * @brief Copy a LivelinessChangedStatus object with a LivelinessChangedStatus object.
     * @param [in] a_liveliness_changed_status The LivelinessChangedStatus object that need to copy.
     * @return LivelinessChangedStatus object that after copying.
     */
    LivelinessChangedStatus &operator=(LivelinessChangedStatus const & a_liveliness_changed_status) = default;

    /**
     * @brief Move a LivelinessChangedStatus object with a LivelinessChangedStatus object.
     * @param [in] a_liveliness_changed_status The LivelinessChangedStatus object that need to move.
     * @return LivelinessChangedStatus object that after moving.
     */
    LivelinessChangedStatus &operator=(LivelinessChangedStatus && a_liveliness_changed_status) = default;

    /**
     * @brief This operation compares two LivelinessChangedStatus are equal or not.
     * @param [in] lhs One of two LivelinessChangedStatus.
     * @param [in] rhs Another of two LivelinessChangedStatus.
     * @return Comparing LivelinessChangedStatus result.
     * @retval true Two LivelinessChangedStatus are equal.
     * @retval false Two LivelinessChangedStatus are not equal. 
     */
    inline friend bool operator==(LivelinessChangedStatus const &lhs, LivelinessChangedStatus const &rhs) noexcept
    {
        gint32_t const lhs_alive_count {lhs.alive_count()};
        gint32_t const rhs_alive_count {rhs.alive_count()};
        gint32_t const lhs_not_alive_count {lhs.not_alive_count()};
        gint32_t const rhs_not_alive_count {rhs.not_alive_count()};
        return (lhs_alive_count == rhs_alive_count) && (lhs_not_alive_count == rhs_not_alive_count);
    }

    /**
     * @brief This operation gets the total number of currently active DataWriters that write the Topic read by the DataReader.
     * @return The total number of currently active DataWriters that write the Topic read by the DataReader.
     */
    inline gint32_t alive_count() const noexcept
    {
        return m_aliveCount;
    }

    /**
     * @brief This operation gets the total count of currently DataWriters that write the Topic read by the DataReader that are no longer asserting their liveliness.
     * @return The total count of currently DataWriters that write the Topic read by the DataReader that are no longer asserting their liveliness. 
     */
    inline gint32_t not_alive_count() const noexcept
    {
        return m_notAliveCount;
    }

    /**
     * @brief This operation gets the change in the alive_count since the last time the listener was called or the status was read.
     * @return The change in the alive_count since the last time the listener was called or the status was read.
     */
    inline gint32_t alive_count_change() const noexcept
    {
        return m_aliveCountChange;
    }

    /**
     * @brief This operation gets the change in the not_alive_count since the last time the listener was called or the status was read. 
     * @return The change in the not_alive_count since the last time the listener was called or the status was read. 
     */
    inline gint32_t not_alive_count_change() const noexcept
    {
        return m_notAliveCountChange;
    }

    /**
     * @brief This operation gets handle to the last DataWriter whose change in liveliness caused this status to change. 
     * @return Handle to the last DataWriter whose change in liveliness caused this status to change. 
     */
    inline gstone::rtps::InstanceHandle_t last_publication_handle() const noexcept
    {
        return m_lastPublicationHandle;
    }

    /**
     * @brief This operation sets the total number of currently active DataWriters that write the Topic read by the DataReader.
     * @param [in] in_alive_count The total number of currently active DataWriters that write the Topic read by the DataReader.
     */
    inline void alive_count(gint32_t const in_alive_count) noexcept
    {
        m_aliveCount = in_alive_count;
    }

    /**
     * @brief This operation sets the total count of currently DataWriters that write the Topic read by the DataReader that are no longer asserting their liveliness.
     * @param [in] in_not_alive_count The total count of currently DataWriters that write the Topic read by the DataReader that are no longer asserting their liveliness. 
     */
    inline void not_alive_count(gint32_t const in_not_alive_count) noexcept
    {
        m_notAliveCount = in_not_alive_count;
    }

    /**
     * @brief This operation sets the change in the alive_count since the last time the listener was called or the status was read.
     * @param [in] in_alive_count_change The change in the alive_count since the last time the listener was called or the status was read.
     */
    inline void alive_count_change(gint32_t const in_alive_count_change) noexcept
    {
        m_aliveCountChange = in_alive_count_change;
    }

    /**
     * @brief This operation sets the change in the not_alive_count since the last time the listener was called or the status was read. 
     * @param [in] in_not_alive_count_change The change in the not_alive_count since the last time the listener was called or the status was read. 
     */
    inline void not_alive_count_change(gint32_t const in_not_alive_count_change) noexcept
    {
        m_notAliveCountChange = in_not_alive_count_change;
    }

    /**
     * @brief This operation gets handle to the last DataWriter whose change in liveliness caused this status to change. 
     * @param [in] handle Handle to the last DataWriter whose change in liveliness caused this status to change. 
     */
    inline void last_publication_handle(gstone::rtps::InstanceHandle_t const &handle) noexcept
    {
        if (&handle != &m_lastPublicationHandle)
        {
            m_lastPublicationHandle = handle;
        }
    }

    gint32_t m_aliveCount;
    gint32_t m_notAliveCount;
    gint32_t m_aliveCountChange;
    gint32_t m_notAliveCountChange;
    gstone::rtps::InstanceHandle_t m_lastPublicationHandle;
};

/**
* @class OfferedDeadlineMissedStatus
* @brief The deadline that the DataWriter has committed through its QosPolicy DEADLINE was not respected for a specific instance.
* @note OfferedDeadlineMissedStatus have total_count, total_count_change and last_instance_handle attribute.
*/
class GS_DDS4CPP_API OfferedDeadlineMissedStatus : public BaseStatus
{
public:
    /**
     * @brief Construct a new OfferedDeadlineMissedStatus object with default parameter.
     */
    OfferedDeadlineMissedStatus() noexcept : BaseStatus {}, m_lastInstanceHandle {0} {}

    /**
     * @brief Destroy the OfferedDeadlineMissedStatus object.
     */
    ~OfferedDeadlineMissedStatus() noexcept override = default;

    /**
     * @brief Construct a new OfferedDeadlineMissedStatus object with copying OfferedDeadlineMissedStatus object.
     * @param [in] an_offered_deadline_missed_status A new OfferedDeadlineMissedStatus object is created by copying this OfferedDeadlineMissedStatus object.
     */
    OfferedDeadlineMissedStatus(OfferedDeadlineMissedStatus const & an_offered_deadline_missed_status) = default;

    /**
     * @brief Construct a new Base Status object with moving OfferedDeadlineMissedStatus object.
     * @param [in] an_offered_deadline_missed_status A new OfferedDeadlineMissedStatus object is created by moving this OfferedDeadlineMissedStatus object.
     */
    OfferedDeadlineMissedStatus(OfferedDeadlineMissedStatus && an_offered_deadline_missed_status) = default;

    /**
     * @brief Copy a OfferedDeadlineMissedStatus object with a OfferedDeadlineMissedStatus object.
     * @param [in] an_offered_deadline_missed_status The OfferedDeadlineMissedStatus object that need to copy.
     * @return OfferedDeadlineMissedStatus object that after copying.
     */
    OfferedDeadlineMissedStatus &operator=(OfferedDeadlineMissedStatus const & an_offered_deadline_missed_status) = default;

    /**
     * @brief Move a OfferedDeadlineMissedStatus object with a OfferedDeadlineMissedStatus object.
     * @param [in] an_offered_deadline_missed_status The OfferedDeadlineMissedStatus object that need to move.
     * @return OfferedDeadlineMissedStatus object that after moving.
     */
    OfferedDeadlineMissedStatus &operator=(OfferedDeadlineMissedStatus && an_offered_deadline_missed_status) = default;

    /**
     * @brief This operation gets handle to the last instance in the DataWriter for which an offered deadline was missed.
     * @return Handle to the last instance in the DataWriter for which an offered deadline was missed.
     */
    inline gstone::rtps::InstanceHandle_t const last_instance_handle() const noexcept
    {
        return m_lastInstanceHandle;
    }

    /**
     * @brief This operation sets handle to the last instance in the DataWriter for which an offered deadline was missed.
     * @param [in] in_last_instance_handle Handle to the last instance in the DataWriter for which an offered deadline was missed.
     * @return Setting handle result.
     * @retval true Setting successfully.
     * @retval false Setting failed.
     */
    inline bool last_instance_handle(gstone::rtps::InstanceHandle_t const &in_last_instance_handle) noexcept
    {
        if (&in_last_instance_handle == &m_lastInstanceHandle) 
        {
            return false;
        }
        m_lastInstanceHandle = in_last_instance_handle;
        return true;
    }

    /**
     * @brief This operation compares two OfferedDeadlineMissedStatus are equal or not.
     * @param [in] lhs One of two OfferedDeadlineMissedStatus.
     * @param [in] rhs Another of two OfferedDeadlineMissedStatus.
     * @return Comparing OfferedDeadlineMissedStatus result.
     * @retval true Two OfferedDeadlineMissedStatus are equal.
     * @retval false Two OfferedDeadlineMissedStatus are not equal. 
     */
    inline friend bool operator==(OfferedDeadlineMissedStatus const &lhs, OfferedDeadlineMissedStatus const &rhs) noexcept
    {
        gint32_t const lhs_total_count  {lhs.total_count()};
        gint32_t const rhs_total_count {rhs.total_count()};
        gstone::rtps::InstanceHandle_t const lhs_last_instance_handle {lhs.last_instance_handle()};
        gstone::rtps::InstanceHandle_t const rhs_last_instance_handle {rhs.last_instance_handle()};
        return (lhs_total_count == rhs_total_count) && (lhs_last_instance_handle == rhs_last_instance_handle);
    }
private:
    gstone::rtps::InstanceHandle_t m_lastInstanceHandle;
};

/**
* @class RequestedDeadlineMissedStatus
* @brief The deadline that the DataReader was expecting through its QosPolicy DEADLINE was not respected for a specific instance.
* @note RequestedDeadlineMissedStatus have total_count, total_count_change and last_instance_handle attribute.
*/
class GS_DDS4CPP_API RequestedDeadlineMissedStatus : public BaseStatus
{
public:
    /**
     * @brief Construct a new RequestedDeadlineMissedStatus object with default parameter.
     */
    RequestedDeadlineMissedStatus() noexcept : BaseStatus {}, m_lastInstanceHandle {0} {}

    /**
     * @brief Destroy the RequestedDeadlineMissedStatus object.
     */
    ~RequestedDeadlineMissedStatus() noexcept override = default;

    /**
     * @brief Construct a new RequestedDeadlineMissedStatus object with copying RequestedDeadlineMissedStatus object.
     * @param [in] a_requested_deadline_missed_status A new RequestedDeadlineMissedStatus object is created by copying this RequestedDeadlineMissedStatus object.
     */
    RequestedDeadlineMissedStatus(RequestedDeadlineMissedStatus const & a_requested_deadline_missed_status) = default;

    /**
     * @brief Construct a new Base Status object with moving RequestedDeadlineMissedStatus object.
     * @param [in] a_requested_deadline_missed_status A new RequestedDeadlineMissedStatus object is created by moving this RequestedDeadlineMissedStatus object.
     */
    RequestedDeadlineMissedStatus(RequestedDeadlineMissedStatus && a_requested_deadline_missed_status) = default;

    /**
     * @brief Copy a RequestedDeadlineMissedStatus object with a RequestedDeadlineMissedStatus object.
     * @param [in] a_requested_deadline_missed_status The RequestedDeadlineMissedStatus object that need to copy.
     * @return RequestedDeadlineMissedStatus object that after copying.
     */
    RequestedDeadlineMissedStatus &operator=(RequestedDeadlineMissedStatus const & a_requested_deadline_missed_status) = default;

    /**
     * @brief Move a RequestedDeadlineMissedStatus object with a RequestedDeadlineMissedStatus object.
     * @param [in] a_requested_deadline_missed_status The RequestedDeadlineMissedStatus object that need to move.
     * @return RequestedDeadlineMissedStatus object that after moving.
     */
    RequestedDeadlineMissedStatus &operator=(RequestedDeadlineMissedStatus && a_requested_deadline_missed_status) = default;

    /**
     * @brief This operation gets handle to the last instance in the DataReader for which a deadline was detected. 
     * @return Handle to the last instance in the DataReader for which a deadline was detected. 
     */
    inline gstone::rtps::InstanceHandle_t const last_instance_handle() const noexcept
    {
        return m_lastInstanceHandle;
    }

    /**
     * @brief This operation sets handle to the last instance in the DataReader for which a deadline was detected. 
     * @param [in] in_last_instance_handle Handle to the last instance in the DataReader for which a deadline was detected. 
     * @return Setting handle result.
     * @retval true Setting successfully.
     * @retval false Setting failed.
     */
    inline bool last_instance_handle(gstone::rtps::InstanceHandle_t const &in_last_instance_handle) noexcept
    {
        if (&in_last_instance_handle == &m_lastInstanceHandle) 
        {
            return false;
        }
        m_lastInstanceHandle = in_last_instance_handle;
        return true;
    }

    /**
     * @brief This operation compares two RequestedDeadlineMissedStatus are equal or not.
     * @param [in] lhs One of two RequestedDeadlineMissedStatus.
     * @param [in] rhs Another of two RequestedDeadlineMissedStatus.
     * @return Comparing RequestedDeadlineMissedStatus result.
     * @retval true Two RequestedDeadlineMissedStatus are equal.
     * @retval false Two RequestedDeadlineMissedStatus are not equal.
     */
    inline friend bool operator==(RequestedDeadlineMissedStatus const &lhs, RequestedDeadlineMissedStatus const &rhs) noexcept
    {
        gint32_t const lhs_total_count {lhs.total_count()};
        gint32_t const rhs_total_count  {rhs.total_count()};
        gstone::rtps::InstanceHandle_t const lhs_last_instance_handle {lhs.last_instance_handle()};
        gstone::rtps::InstanceHandle_t const rhs_last_instance_handle {rhs.last_instance_handle()};
        return (lhs_total_count == rhs_total_count) && (lhs_last_instance_handle == rhs_last_instance_handle);
    }
private:
    gstone::rtps::InstanceHandle_t m_lastInstanceHandle;
};

/**
* @class SubscriptionMatchedStatus
* @brief The DataReader has found a DataWriter that matches the Topic and has compatible QoS, or has ceased to be matched with a DataWriter that was 
* previously considered to be matched.
* @note SubscriptionMatchedStatus have total_count, total_count_change, current_count, current_count_change and last_publication_handle attribute.
*/
class GS_DDS4CPP_API SubscriptionMatchedStatus : public BaseStatus
{
public:
    /**
     * @brief Construct a new SubscriptionMatchedStatus object with default parameter.
     */
    SubscriptionMatchedStatus()  = default;

    /**
     * @brief Destroy the SubscriptionMatchedStatus object.
     */
    ~SubscriptionMatchedStatus() noexcept override = default;

    /**
     * @brief Construct a new SubscriptionMatchedStatus object with copying SubscriptionMatchedStatus object.
     * @param [in] a_subscription_matched_status A new SubscriptionMatchedStatus object is created by copying this SubscriptionMatchedStatus object.
     */
    SubscriptionMatchedStatus(SubscriptionMatchedStatus const & a_subscription_matched_status) = default;

    /**
     * @brief Construct a new Base Status object with moving SubscriptionMatchedStatus object.
     * @param [in] a_subscription_matched_status A new SubscriptionMatchedStatus object is created by moving this SubscriptionMatchedStatus object.
     */
    SubscriptionMatchedStatus(SubscriptionMatchedStatus && a_subscription_matched_status) = default;

    /**
     * @brief Copy a SubscriptionMatchedStatus object with a SubscriptionMatchedStatus object.
     * @param [in] a_subscription_matched_status The SubscriptionMatchedStatus object that need to copy.
     * @return SubscriptionMatchedStatus object that after copying.
     */
    SubscriptionMatchedStatus &operator=(SubscriptionMatchedStatus const & a_subscription_matched_status) = default;

    /**
     * @brief Move a SubscriptionMatchedStatus object with a SubscriptionMatchedStatus object.
     * @param [in] a_subscription_matched_status The SubscriptionMatchedStatus object that need to move.
     * @return SubscriptionMatchedStatus object that after moving.
     */
    SubscriptionMatchedStatus &operator=(SubscriptionMatchedStatus && a_subscription_matched_status) = default;

    /**
     * @brief This operation gets the number of DataWriters currently matched to the concerned DataReader. 
     * @return The number of DataWriters currently matched to the concerned DataReader. 
     */
    inline gint32_t current_count() const noexcept
    {
        return m_currentCount;
    }

    /**
     * @brief This operation gets the change in current_count since the last time the listener was called or the status was read. 
     * @return The change in current_count since the last time the listener was called or the status was read. 
     */
    inline gint32_t current_count_change() const noexcept
    {
        return m_currentCountChange;
    }

    /**
     * @brief This operation gets handle to the last DataWriter that matched the DataReader causing the status to change. 
     * @return Handle to the last DataWriter that matched the DataReader causing the status to change. 
     */
    inline gstone::rtps::InstanceHandle_t const last_publication_handle() const noexcept
    {
        return m_lastPublicationHandle;
    }

    /**
     * @brief This operation sets the number of DataWriters currently matched to the concerned DataReader.
     * @param [in] in_current_count The number of DataWriters currently matched to the concerned DataReader.
     */
    inline void current_count(gint32_t const in_current_count) noexcept
    {
        m_currentCount = in_current_count;
    }

    /**
     * @brief This operation sets the change in current_count since the last time the listener was called or the status was read. 
     * @param [in] in_current_count_change The change in current_count since the last time the listener was called or the status was read. 
     */
    inline void current_count_change(gint32_t const in_current_count_change) noexcept
    {
        m_currentCountChange = in_current_count_change;
    }

    /**
     * @brief This operation sets handle to the last DataWriter that matched the DataReader causing the status to change.
     * @param [in] in_last_publication_handle Handle to the last DataWriter that matched the DataReader causing the status to change.
     */
    inline void last_publication_handle(gstone::rtps::InstanceHandle_t const &in_last_publication_handle) noexcept
    {
        if (&in_last_publication_handle != &m_lastPublicationHandle) 
        {
            m_lastPublicationHandle = in_last_publication_handle;
        }        
    }

    /**
     * @brief This operation compares two SubscriptionMatchedStatus are equal or not.
     * @param [in] lhs One of two SubscriptionMatchedStatus.
     * @param [in] rhs Another of two SubscriptionMatchedStatus.
     * @return Comparing SubscriptionMatchedStatus result.
     * @retval true Two SubscriptionMatchedStatus are equal.
     * @retval false Two SubscriptionMatchedStatus are not equal. 
     */
    inline friend bool operator==(SubscriptionMatchedStatus const &lhs, SubscriptionMatchedStatus const &rhs) noexcept
    {
        gint32_t const lhs_total_count {lhs.total_count()};
        gint32_t const rhs_total_count { rhs.total_count()};
        gint32_t const lhs_current_count {lhs.current_count()};
        gint32_t const rhs_current_count {rhs.current_count()};
        gstone::rtps::InstanceHandle_t const lhs_last_publication_handle {lhs.last_publication_handle()};
        gstone::rtps::InstanceHandle_t const rhs_last_publication_handle {rhs.last_publication_handle()};
        return (lhs_total_count == rhs_total_count) && (lhs_current_count == rhs_current_count) &&
               (lhs_last_publication_handle == rhs_last_publication_handle);
    }
private:
    gint32_t m_currentCount {0};
    gint32_t m_currentCountChange {0};
    gstone::rtps::InstanceHandle_t m_lastPublicationHandle {0};
};

/**
* @class LivelinessLostStatus
* @brief The liveliness that the DataWriter has committed through its QosPolicy LIVELINESS was not respected; thus DataReader entities will consider 
* the DataWriter as no longer "active."
* @note LivelinessLostStatus have total_count and total_count_change attribute.
*/
class GS_DDS4CPP_API LivelinessLostStatus : public BaseStatus
{
public:
    /**
     * @brief Construct a new LivelinessLostStatus object with default parameter.
     */
    LivelinessLostStatus() = default;

    /**
     * @brief Destroy the LivelinessLostStatus object.
     */
    ~LivelinessLostStatus() noexcept override = default;

    /**
     * @brief Construct a new LivelinessLostStatus object with copying LivelinessLostStatus object.
     * @param [in] a_liveliness_lost_status A new LivelinessLostStatus object is created by copying this LivelinessLostStatus object.
     */
    LivelinessLostStatus(LivelinessLostStatus const & a_liveliness_lost_status) = default;

    /**
     * @brief Construct a new Base Status object with moving LivelinessLostStatus object.
     * @param [in] a_liveliness_lost_status A new LivelinessLostStatus object is created by moving this LivelinessLostStatus object.
     */
    LivelinessLostStatus(LivelinessLostStatus && a_liveliness_lost_status) = default;

    /**
     * @brief Copy a LivelinessLostStatus object with a LivelinessLostStatus object.
     * @param [in] a_liveliness_lost_status The LivelinessLostStatus object that need to copy.
     * @return LivelinessLostStatus object that after copying.
     */
    LivelinessLostStatus &operator=(LivelinessLostStatus const & a_liveliness_lost_status) = default;

    /**
     * @brief Move a LivelinessLostStatus object with a LivelinessLostStatus object.
     * @param [in] a_liveliness_lost_status The LivelinessLostStatus object that need to move.
     * @return LivelinessLostStatus object that after moving.
     */
    LivelinessLostStatus &operator=(LivelinessLostStatus && a_liveliness_lost_status) = default;

    /**
     * @brief This operation compares two LivelinessLostStatus are equal or not.
     * @param [in] lhs One of two LivelinessLostStatus.
     * @param [in] rhs Another of two LivelinessLostStatus.
     * @return Comparing LivelinessLostStatus result.
     * @retval true Two LivelinessLostStatus are equal.
     * @retval false Two LivelinessLostStatus are not equal.
     */
    inline friend bool operator==(LivelinessLostStatus const &lhs, LivelinessLostStatus const &rhs) noexcept
    {
        gint32_t const lhs_total_count {lhs.total_count()};
        gint32_t const rhs_total_count {rhs.total_count()};
        return lhs_total_count == rhs_total_count;
    }
};

/**
* @class RequestedIncompatibleQosStatus
* @brief A QosPolicy value was incompatible with what is offered.
* @note RequestedIncompatibleQosStatus have last_policy_id, policies, total_count and total_count_change attribute.
*/
class GS_DDS4CPP_API RequestedIncompatibleQosStatus : public BaseStatus
{
public:
    /**
     * @brief Construct a new RequestedIncompatibleQosStatus object with default parameter.
     */
    RequestedIncompatibleQosStatus() noexcept =  default;

    /**
     * @brief Destroy the RequestedIncompatibleQosStatus object.
     */
    ~RequestedIncompatibleQosStatus() noexcept override = default;

    /**
     * @brief Construct a new RequestedIncompatibleQosStatus object with copying RequestedIncompatibleQosStatus object.
     * @param [in] a_requested_incompatible_qos_status A new RequestedIncompatibleQosStatus object is created by copying this RequestedIncompatibleQosStatus object.
     */
    RequestedIncompatibleQosStatus(RequestedIncompatibleQosStatus const & a_requested_incompatible_qos_status) = default;

    /**
     * @brief Construct a new Base Status object with moving RequestedIncompatibleQosStatus object.
     * @param [in] a_requested_incompatible_qos_status A new RequestedIncompatibleQosStatus object is created by moving this RequestedIncompatibleQosStatus object.
     */
    RequestedIncompatibleQosStatus(RequestedIncompatibleQosStatus && a_requested_incompatible_qos_status) = default;

    /**
     * @brief Copy a RequestedIncompatibleQosStatus object with a RequestedIncompatibleQosStatus object.
     * @param [in] a_requested_incompatible_qos_status The RequestedIncompatibleQosStatus object that need to copy.
     * @return RequestedIncompatibleQosStatus object that after copying.
     */
    RequestedIncompatibleQosStatus &operator=(RequestedIncompatibleQosStatus const & a_requested_incompatible_qos_status) = default;

    /**
     * @brief Move a RequestedIncompatibleQosStatus object with a RequestedIncompatibleQosStatus object.
     * @param [in] a_requested_incompatible_qos_status The RequestedIncompatibleQosStatus object that need to move.
     * @return RequestedIncompatibleQosStatus object that after moving.
     */
    RequestedIncompatibleQosStatus &operator=(RequestedIncompatibleQosStatus && a_requested_incompatible_qos_status) = default;

    /**
     * @brief This operation gets the QosPolicyId_t of one of the policies that was found to be incompatible the last time an incompatibility was detected. 
     * @return The QosPolicyId_t of one of the policies that was found to be incompatible the last time an incompatibility was detected. 
     */
    inline DDS::QosPolicyId_t last_policy_id() const noexcept
    {
        return m_lastPolicyId;
    }

    /**
     * @brief This operation sets the QosPolicyId_t of one of the policies that was found to be incompatible the last time an incompatibility was detected. 
     * @param [in] in_last_policy_id The QosPolicyId_t of one of the policies that was found to be incompatible the last time an incompatibility was detected. 
     */
    inline void last_policy_id(DDS::QosPolicyId_t const in_last_policy_id) noexcept
    {
        m_lastPolicyId = in_last_policy_id;
    }

    /**
     * @brief This operation gets a list containing for each policy the total number of times that the 
     * concerned DataReader discovered a DataWriter for the same Topic with an offered QoS that is incompatible with that requested by the DataReader. 
     * @return A list containing for each policy the total number of times that the 
     * concerned DataReader discovered a DataWriter for the same Topic with an offered QoS that is incompatible with that requested by the DataReader. 
     */
    inline dds::qos::QosPolicyCountSeq const policies() const noexcept
    {
        return m_policies;
    }

    /**
     * @brief This operation sets a list containing for each policy the total number of times that the 
     * concerned DataReader discovered a DataWriter for the same Topic with an offered QoS that is incompatible with that requested by the DataReader. 
     * @param [in] dst A list containing for each policy the total number of times that the 
     * concerned DataReader discovered a DataWriter for the same Topic with an offered QoS that is incompatible with that requested by the DataReader.  
     */
    inline void policies(dds::qos::QosPolicyCountSeq const &dst) noexcept
    {
        m_policies = dst;
    }

    /**
     * @brief This operation compares two RequestedIncompatibleQosStatus are equal or not.
     * @param [in] lhs One of two RequestedIncompatibleQosStatus.
     * @param [in] rhs Another of two RequestedIncompatibleQosStatus.
     * @return Comparing RequestedIncompatibleQosStatus result.
     * @retval true Two RequestedIncompatibleQosStatus are equal.
     * @retval false Two RequestedIncompatibleQosStatus are not equal.  
     */
    inline friend bool operator==(RequestedIncompatibleQosStatus const &lhs,
                           RequestedIncompatibleQosStatus const &rhs) noexcept
    {
        gint32_t const lhs_total_count {lhs.total_count()};
        gint32_t const rhs_total_count {rhs.total_count()};
        DDS::QosPolicyId_t const lhs_last_policy_id {lhs.last_policy_id()};
        DDS::QosPolicyId_t const rhs_last_policy_id {rhs.last_policy_id()};
        dds::qos::QosPolicyCountSeq const lhs_policies {lhs.policies()};
        dds::qos::QosPolicyCountSeq const rhs_policies {rhs.policies()};
        bool const is_equal {lhs_policies == rhs_policies};
        return (lhs_total_count == rhs_total_count) && (lhs_last_policy_id == rhs_last_policy_id) && is_equal;
    }
private:
    DDS::QosPolicyId_t m_lastPolicyId {0U};
    dds::qos::QosPolicyCountSeq m_policies {};
};

/**
* @class OfferedIncompatibleQosStatus
* @brief A QosPolicy value was incompatible with what was requested.
* @note OfferedIncompatibleQosStatus have last_policy_id, policies, total_count and total_count_change attribute.
*/
class GS_DDS4CPP_API OfferedIncompatibleQosStatus : public BaseStatus
{
public:
    /**
     * @brief Construct a new OfferedIncompatibleQosStatus object with default parameter.
     */
    OfferedIncompatibleQosStatus() noexcept = default;

    /**
     * @brief Destroy the OfferedIncompatibleQosStatus object.
     */
    ~OfferedIncompatibleQosStatus() noexcept override = default;

    /**
     * @brief Construct a new OfferedIncompatibleQosStatus object with copying OfferedIncompatibleQosStatus object.
     * @param [in] an_offered_incompatible_qos_status A new OfferedIncompatibleQosStatus object is created by copying this OfferedIncompatibleQosStatus object.
     */
    OfferedIncompatibleQosStatus(OfferedIncompatibleQosStatus const & an_offered_incompatible_qos_status) = default;

    /**
     * @brief Construct a new Base Status object with moving OfferedIncompatibleQosStatus object.
     * @param [in] an_offered_incompatible_qos_status A new OfferedIncompatibleQosStatus object is created by moving this OfferedIncompatibleQosStatus object.
     */
    OfferedIncompatibleQosStatus(OfferedIncompatibleQosStatus && an_offered_incompatible_qos_status) = default;

    /**
     * @brief Copy a OfferedIncompatibleQosStatus object with a OfferedIncompatibleQosStatus object.
     * @param [in] an_offered_incompatible_qos_status The OfferedIncompatibleQosStatus object that need to copy.
     * @return OfferedIncompatibleQosStatus object that after copying.
     */
    OfferedIncompatibleQosStatus &operator=(OfferedIncompatibleQosStatus const & an_offered_incompatible_qos_status) = default;

    /**
     * @brief Move a OfferedIncompatibleQosStatus object with a OfferedIncompatibleQosStatus object.
     * @param [in] an_offered_incompatible_qos_status The OfferedIncompatibleQosStatus object that need to move.
     * @return OfferedIncompatibleQosStatus object that after moving.
     */
    OfferedIncompatibleQosStatus &operator=(OfferedIncompatibleQosStatus && an_offered_incompatible_qos_status) = default;

    /**
     * @brief The operation gets the PolicyId_t of one of the policies that was found to be incompatible the last time an incompatibility was detected. 
     * @return The PolicyId_t of one of the policies that was found to be incompatible the last time an incompatibility was detected. 
     */
    inline DDS::QosPolicyId_t last_policy_id() const noexcept
    {
        return m_lastPolicyId;
    }

    /**
     * @brief  The operation gets a list containing for each policy the total number of times that the 
     * concerned DataWriter discovered a DataReader for the same Topic with a requested QoS that is incompatible with that offered by the DataWriter.
     * @return A list containing for each policy the total number of times that the 
     * concerned DataWriter discovered a DataReader for the same Topic with a requested QoS that is incompatible with that offered by the DataWriter. 
     */
    inline dds::qos::QosPolicyCountSeq const policies() const
    {
        return m_policies;
    }

    /**
     * @brief The operation gets a list containing for each policy the total number of times that the 
     * concerned DataWriter discovered a DataReader for the same Topic with a requested QoS that is incompatible with that offered by the DataWriter.
     * @param [in] dst A list containing for each policy the total number of times that the 
     * concerned DataWriter discovered a DataReader for the same Topic with a requested QoS that is incompatible with that offered by the DataWriter.
     */
    inline void policies(dds::qos::QosPolicyCountSeq const &dst) noexcept
    {
        m_policies = dst;
    }

    /**
     * @brief The operation sets the PolicyId_t of one of the policies that was found to be incompatible the last time an incompatibility was detected. 
     * @param [in] in_last_policy_id The PolicyId_t of one of the policies that was found to be incompatible the last time an incompatibility was detected. 
     */
    inline void last_policy_id(DDS::QosPolicyId_t const in_last_policy_id) noexcept
    {
        m_lastPolicyId = in_last_policy_id;
    }

    /**
     * @brief This operation compares two OfferedIncompatibleQosStatus are equal or not.
     * @param [in] lhs One of two OfferedIncompatibleQosStatus.
     * @param [in] rhs Another of two OfferedIncompatibleQosStatus.
     * @return Comparing OfferedIncompatibleQosStatus result.
     * @retval true Two OfferedIncompatibleQosStatus are equal.
     * @retval false Two OfferedIncompatibleQosStatus are not equal.  
     */
    inline friend bool operator==(OfferedIncompatibleQosStatus const &lhs, OfferedIncompatibleQosStatus const &rhs) noexcept
    {
        gint32_t const lhs_total_count {lhs.total_count()};
        gint32_t const rhs_total_count {rhs.total_count()};
        DDS::QosPolicyId_t const lhs_last_policy_id {lhs.last_policy_id()};
        DDS::QosPolicyId_t const rhs_last_policy_id {rhs.last_policy_id()};
        dds::qos::QosPolicyCountSeq const lhs_policies {lhs.policies()};
        dds::qos::QosPolicyCountSeq const rhs_policies {rhs.policies()};
        bool const is_equal {lhs_policies == rhs_policies};
        return (lhs_total_count == rhs_total_count) && (lhs_last_policy_id == rhs_last_policy_id) && is_equal;
    }
private:
    DDS::QosPolicyId_t m_lastPolicyId {0U};
    dds::qos::QosPolicyCountSeq m_policies {};
};

/**
* @class WriterLostPacketStatisticInfo
* @brief The DataWriter statisticals loss of data when exchanging information with DataReader.
*/
class GS_DDS4CPP_API WriterLostPacketStatisticInfo final
{
public:
    /**
     * @brief Construct a new WriterLostPacketStatisticInfo object with default parameter.
     */
    WriterLostPacketStatisticInfo() = default;

    /**
     * @brief Destroy the WriterLostPacketStatisticInfo object.
     */
    ~WriterLostPacketStatisticInfo() = default;

    /**
     * @brief Construct a new WriterLostPacketStatisticInfo object with copying WriterLostPacketStatisticInfo object.
     * @param [in] a_writer_lost_packet_statistic_info A new WriterLostPacketStatisticInfo object is created by copying this WriterLostPacketStatisticInfo object.
     */
    WriterLostPacketStatisticInfo(WriterLostPacketStatisticInfo const & a_writer_lost_packet_statistic_info) = default;

    /**
     * @brief Construct a new Base Status object with moving WriterLostPacketStatisticInfo object.
     * @param [in] a_writer_lost_packet_statistic_info A new WriterLostPacketStatisticInfo object is created by moving this WriterLostPacketStatisticInfo object.
     */
    WriterLostPacketStatisticInfo(WriterLostPacketStatisticInfo && a_writer_lost_packet_statistic_info) = default;

    /**
     * @brief Copy a WriterLostPacketStatisticInfo object with a WriterLostPacketStatisticInfo object.
     * @param [in] a_writer_lost_packet_statistic_info The WriterLostPacketStatisticInfo object that need to copy.
     * @return WriterLostPacketStatisticInfo object that after copying.
     */
    WriterLostPacketStatisticInfo &operator=(WriterLostPacketStatisticInfo const & a_writer_lost_packet_statistic_info) = default;

    /**
     * @brief Move a WriterLostPacketStatisticInfo object with a WriterLostPacketStatisticInfo object.
     * @param [in] a_writer_lost_packet_statistic_info The WriterLostPacketStatisticInfo object that need to move.
     * @return WriterLostPacketStatisticInfo object that after moving.
     */
    WriterLostPacketStatisticInfo &operator=(WriterLostPacketStatisticInfo && a_writer_lost_packet_statistic_info) = default;

    /**
     * @brief This operation gets the total count of currently DataWriter that lose changes because of timeout.
     * @return The total count of currently DataWriter that lose changes because of timeout.
     */
    inline gint32_t w_timeout_count() const noexcept
    {
        return m_timeoutCount;
    }

    /**
     * @brief This operation sets the total count of currently DataWriter that lose changes because of timeout.
     * @param [in] value The total count of currently DataWriter that lose changes because of timeout.
     */
    inline void w_timeout_count(gint32_t const &value) noexcept
    {
        m_timeoutCount = value;
    }

    /**
     * @brief This operation gets the total count of currently DataWriter that lose changes because of resource limits. 
     * @return The total count of currently DataWriter that lose changes because of resource limits. 
     */
    inline gint32_t w_resource_count() const noexcept
    {
        return m_resourceCount;
    }

    /**
     * @brief This operation sets the total count of currently DataWriter that lose changes because of resource limits.
     * @param [in] value The total count of currently DataWriter that lose changes because of resource limits. 
     */
    inline void w_resource_count(gint32_t const &value) noexcept
    {
        m_resourceCount = value;
    }

    /**
     * @brief This operation gets the total count of currently DataWriter that lose changes because of history limits.
     * @return The total count of currently DataWriter that lose changes because of history limits. 
     */
    inline gint32_t w_history_count() const noexcept
    {
        return m_historyCount;
    }

    /**
     * @brief This operation sets the total count of currently DataWriter that lose changes because of history limits.
     * @param [in] value The total count of currently DataWriter that lose changes because of history limits. 
     */
    inline void w_history_count(gint32_t const &value) noexcept
    {
        m_historyCount = value;
    }

    /**
     * @brief This operation gets the total count of currently DataWriter that lose changes because of shared memory limits.
     * @return The total count of currently DataWriter that lose changes because of shared memory limits. 
     */
    inline gint32_t w_shm_count() const noexcept
    {
        return m_shmCount;
    }

    /**
     * @brief This operation sets the total count of currently DataWriter that lose changes because of shared memory limits.
     * @param [in] value The total count of currently DataWriter that lose changes because of shared memory limits. 
     */
    inline void w_shm_count(gint32_t const &value) noexcept
    {
        m_shmCount = value;
    }

    /**
     * @brief This operation gets the total count of currently DataWriter that lose changes.
     * @return The total count of currently DataWriter that lose changes. 
     */
    inline gint32_t w_total_count() const noexcept
    {
        return m_totalCount;
    }

    /**
     * @brief This operation sets the total count of currently DataWriter that lose changes.
     * @param [in] value The total count of currently DataWriter that lose changes. 
     */
    inline void w_total_count(gint32_t const &value) noexcept
    {
        m_totalCount = value;
    }
private:
    gint32_t m_timeoutCount {0};
    gint32_t m_resourceCount {0};
    gint32_t m_historyCount {0};
    gint32_t m_shmCount {0};
    gint32_t m_totalCount {0};
};

/**
* @class ReaderLostPacketStatisticInfo
* @brief The DataReader statisticals loss of data when exchanging information with DataWriter.
*/
class GS_DDS4CPP_API ReaderLostPacketStatisticInfo final
{
public:
    /**
     * @brief Construct a new ReaderLostPacketStatisticInfo object with default parameter.
     */
    ReaderLostPacketStatisticInfo() = default;

    /**
     * @brief Destroy the ReaderLostPacketStatisticInfo object.
     */
    ~ReaderLostPacketStatisticInfo() = default;

    /**
     * @brief Construct a new ReaderLostPacketStatisticInfo object with copying ReaderLostPacketStatisticInfo object.
     * @param [in] a_reader_lost_packet_statistic_info A new ReaderLostPacketStatisticInfo object is created by copying this ReaderLostPacketStatisticInfo object.
     */
    ReaderLostPacketStatisticInfo(ReaderLostPacketStatisticInfo const & a_reader_lost_packet_statistic_info) = default;

    /**
     * @brief Construct a new Base Status object with moving ReaderLostPacketStatisticInfo object.
     * @param [in] a_reader_lost_packet_statistic_info A new ReaderLostPacketStatisticInfo object is created by moving this ReaderLostPacketStatisticInfo object.
     */
    ReaderLostPacketStatisticInfo(ReaderLostPacketStatisticInfo && a_reader_lost_packet_statistic_info) = default;

    /**
     * @brief Copy a ReaderLostPacketStatisticInfo object with a ReaderLostPacketStatisticInfo object.
     * @param [in] a_reader_lost_packet_statistic_info The WriterLostPacketStatisticInfo object that need to copy.
     * @return ReaderLostPacketStatisticInfo object that after copying.
     */
    ReaderLostPacketStatisticInfo &operator=(ReaderLostPacketStatisticInfo const & a_reader_lost_packet_statistic_info) = default;

    /**
     * @brief Move a ReaderLostPacketStatisticInfo object with a ReaderLostPacketStatisticInfo object.
     * @param [in] a_reader_lost_packet_statistic_info The WriterLostPacketStatisticInfo object that need to copy.
     * @return ReaderLostPacketStatisticInfo object that after moving.
     */
    ReaderLostPacketStatisticInfo &operator=(ReaderLostPacketStatisticInfo && a_reader_lost_packet_statistic_info) = default;

    /**
     * @brief This operation gets the total count of currently DataReader that lose changes because of resource limits.
     * @return The total count of currently DataReader that lose changes because of resource limits. 
     */
    inline gint32_t r_resource_count() const noexcept
    {
        return m_resourceCount;
    }

    /**
     * @brief This operation sets the total count of currently DataReader that lose changes because of resource limits.
     * @param [in] value The total count of currently DataReader that lose changes because of resource limits.  
     */
    inline void r_resource_count(gint32_t const &value) noexcept
    {
        m_resourceCount = value;
    }

    /**
     * @brief This operation gets the total count of currently DataReader that lose changes because of history limits.
     * @return The total count of currently DataReader that lose changes because of history limits. 
     */
    inline gint32_t r_history_count() const noexcept
    {
        return m_historyCount;
    }

    /**
     * @brief This operation sets the total count of currently DataReader that lose changes because of history limits.
     * @param [in] value The total count of currently DataReader that lose changes because of history limits. 
     */
    inline void r_history_count(gint32_t const &value) noexcept
    {
        m_historyCount = value;
    }

    /**
     * @brief This operation gets the total count of currently DataReader that lose changes because of shared memory limits.
     * @return The total count of currently DataReader that lose changes because of shared memory limits. 
     */
    inline gint32_t r_shm_count() const noexcept
    {
        return m_shmCount;
    }

    /**
     * @brief This operation sets the total count of currently DataReader that lose changes because of shared memory limits.
     * @param [in] value The total count of currently DataReader that lose changes because of shared memory limits. 
     */
    inline void r_shm_count(gint32_t const &value) noexcept
    {
        m_shmCount = value;
    }

    /**
     * @brief This operation gets the total count of currently DataReader that lose changes.
     * @return The total count of currently DataReader that lose changes. 
     */
    inline gint32_t r_total_count() const noexcept
    {
        return m_totalCount;
    }

    /**
     * @brief This operation sets the total count of currently DataReader that lose changes.
     * @param [in] value The total count of currently DataReader that lose changes.
     */
    inline void r_total_count(gint32_t const &value) noexcept
    {
        m_totalCount = value;
    }
private:
    gint32_t m_resourceCount {0};
    gint32_t m_historyCount {0};
    gint32_t m_shmCount {0};
    gint32_t m_totalCount {0};
};

} /*core*/
} /*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_STATUS_API_H*/
