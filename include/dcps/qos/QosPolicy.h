/**************************************************************
* @file QosPolicy.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#ifndef GSTONE_QOSPOLICY_API_H
#define GSTONE_QOSPOLICY_API_H 1

#include <string>
#include <vector>

#include "rtps/Duration.h"
#include "dcps/DeclExport.h"
#include "rtps/DdsCdr.h"
#include "rtps/Locator.h"
#include "dcps/DdsBaseTypes.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace qos {
    
    using QosPolicyLong_t = gint32_t;

    constexpr DDS::QosPolicyId_t INVALID_QOS_POLICY_ID{ 0U };               ///< Don't refer to any valid QosPolicy
    constexpr DDS::QosPolicyId_t USERDATA_QOS_POLICY_ID{ 1U };              ///< UserDataQosPolicy
    constexpr DDS::QosPolicyId_t DURABILITY_QOS_POLICY_ID{ 2U };            ///< DurabilityQosPolicy
    constexpr DDS::QosPolicyId_t PRESENTATION_QOS_POLICY_ID{ 3U };          ///< PresentationQosPolicy
    constexpr DDS::QosPolicyId_t DEADLINE_QOS_POLICY_ID{ 4U };              ///< DeadlineQosPolicy
    constexpr DDS::QosPolicyId_t LATENCYBUDGET_QOS_POLICY_ID{ 5U };         ///< LatencyBudgetQosPolicy
    constexpr DDS::QosPolicyId_t OWNERSHIP_QOS_POLICY_ID{ 6U };             ///< OwnershipQosPolicy
    constexpr DDS::QosPolicyId_t OWNERSHIPSTRENGTH_QOS_POLICY_ID{ 7U };     ///< OwnershipStrengthQosPolicy
    constexpr DDS::QosPolicyId_t LIVELINESS_QOS_POLICY_ID{ 8U };            ///< LivelinessQosPolicy
    constexpr DDS::QosPolicyId_t TIMEBASEDFILTER_QOS_POLICY_ID{ 9U };       ///< TimeBasedFilterQosPolicy
    constexpr DDS::QosPolicyId_t PARTITION_QOS_POLICY_ID{ 10U };            ///< PartitionQosPolicy
    constexpr DDS::QosPolicyId_t RELIABILITY_QOS_POLICY_ID{ 11U };          ///< ReliabilityQosPolicy
    constexpr DDS::QosPolicyId_t DESTINATIONORDER_QOS_POLICY_ID{ 12U };     ///< DestinationOrderQosPolicy
    constexpr DDS::QosPolicyId_t HISTORY_QOS_POLICY_ID{ 13U };              ///< HistoryQosPolicy
    constexpr DDS::QosPolicyId_t RESOURCELIMITS_QOS_POLICY_ID{ 14U };       ///< ResourceLimitsQosPolicy
    constexpr DDS::QosPolicyId_t ENTITYFACTORY_QOS_POLICY_ID{ 15U };        ///< EntityFactoryQosPolicy
    constexpr DDS::QosPolicyId_t WRITERDATALIFECYCLE_QOS_POLICY_ID{ 16U };  ///< WriterDataLifecycleQosPolicy
    constexpr DDS::QosPolicyId_t READERDATALIFECYCLE_QOS_POLICY_ID{ 17U };  ///< ReaderDataLifecycleQosPolicy
    constexpr DDS::QosPolicyId_t TOPICDATA_QOS_POLICY_ID{ 18U };            ///< TopicDataQosPolicy
    constexpr DDS::QosPolicyId_t GROUPDATA_QOS_POLICY_ID{ 19U };            ///< GroupDataQosPolicy
    constexpr DDS::QosPolicyId_t TRANSPORTPRIORITY_QOS_POLICY_ID{ 20U };    ///< TransportPriorityQosPolicy
    constexpr DDS::QosPolicyId_t LIFESPAN_QOS_POLICY_ID{ 21U };             ///< LifespanQosPolicy
    constexpr DDS::QosPolicyId_t DURABILITYSERVICE_QOS_POLICY_ID{ 22U };    ///< DurabilityServiceQosPolicy

    constexpr QosPolicyLong_t LENGTH_UNLIMITED{ 0 };            ///< Used to indicate the absence of a particular limit
    constexpr guint64_t DEFAULT_MAX_BLOCKING_TIME{ 100U };      ///< Default value of max blocking time

    /**
    * @brief This class is the abstract root for all the QoS policies.
    */
    class GS_DDS4CPP_API QosPolicy
    {
    public:
        QosPolicy() = delete;
        QosPolicy(std::string const& QosName) : m_name{ QosName } {}
        virtual ~QosPolicy() = default;

        /**
        * @brief This function get the name of Qos policy.
        * @return Const reference of the string representing Qos policy name.
        */
        inline std::string const& name() const noexcept
        {
            return m_name;
        }

        /**
        * @brief This function set the name of Qos policy.
        * @param [in] name_t Const reference of the Qos policy name to be set to.
        */
        inline void name(std::string const& name_t) noexcept
        {
            m_name = name_t;
        }
    protected:
        QosPolicy& operator=(QosPolicy const& other) = default;
        QosPolicy& operator=(QosPolicy&& other) = default;
        QosPolicy(QosPolicy const& other) = default;
        QosPolicy(QosPolicy&& other) = default;

    private:
        std::string m_name;
    };

    /**
    * @brief This QoS allow the application to attach additional information to the created Entity objects such that when 
    *        a remote application discovers their existence it can access that information and use it for its own purposes.
    */
    class GS_DDS4CPP_API UserDataQosPolicy : public QosPolicy
    {
    public:
        UserDataQosPolicy() : QosPolicy{ "UserData" }, m_value{} {}

        /**
        * @brief This function serializies UserDataQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_value);
            return;
        }

        /**
        * @brief This function deserializies UserDataQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_value);
            return;
        }

        /**
        * @brief This function get user data value.
        * @return Const reference of a sequence of octets representing user data value.
        */
        inline std::vector<octet> const& value() const noexcept
        {
            return m_value;
        }

        /**
        * @brief This function set user data value.
        * @param [in] value_t A sequence of octets representing the user data value to be set to.
        */
        inline void value(std::vector<octet> const& value_t) noexcept
        {
            m_value = value_t;
        }

        /**
         * @brief Compare two UserDataQosPolicy objects for equailty.
         * @param [in] l_userData_qos Const Reference of the left UserDataQosPolicy object.
         * @param [in] r_userData_qos Const Reference of the right UserDataQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(UserDataQosPolicy const& l_userData_qos, UserDataQosPolicy const& r_userData_qos) noexcept
        {
            if (l_userData_qos.value() == r_userData_qos.value())
            {
                return true;
            }
            return false;
        }

    private:
        std::vector<octet> m_value;
    };

    /**
    * @brief This QoS allow the application to attach additional information to the created Topic such that when a remote 
    *        application discovers their existence it can examine the information and use it in an application-defined way.
    */
    class GS_DDS4CPP_API TopicDataQosPolicy : public QosPolicy
    {
    public:
        TopicDataQosPolicy() : QosPolicy{ "TopicData" }, m_value{} {}

        /**
        * @brief This function serializies TopicDataQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_value);
            return;
        }

        /**
        * @brief This function deserializies TopicDataQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_value);
            return;
        }

        /**
        * @brief This function get topic data value.
        * @return A sequence of octets means topic data value.
        */
        inline std::vector<octet> const& value() const noexcept
        {
            return m_value;
        }

        /**
        * @brief This function set topic data value.
        * @param [in] value_t A sequence of octets means the topic data value to be set to.
        */
        inline void value(std::vector<octet> const& value_t) noexcept
        {
            m_value = value_t;
        }

        /**
         * @brief Compare two TopicDataQosPolicy objects for equailty.
         * @param [in] l_topicData_qos Const Reference of the left TopicDataQosPolicy object.
         * @param [in] r_topicData_qos Const Reference of the right TopicDataQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(TopicDataQosPolicy const& l_topicData_qos, TopicDataQosPolicy const& r_topicData_qos) noexcept
        {
            if (l_topicData_qos.value() == r_topicData_qos.value())
            {
                return true;
            }
            return false;
        }

    private:
        std::vector<octet> m_value;
    };
    

    /**
    * @brief This QoS allow the application to attach additional information to the created Publisher or Subscriber.
    */
    class GS_DDS4CPP_API GroupDataQosPolicy : public QosPolicy
    {
    public:
        GroupDataQosPolicy() : QosPolicy{ "GroupData" }, m_value{} {}

        /**
        * @brief This function serializies GroupDataQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_value);
            return;
        }

        /**
        * @brief This function deserializies GroupDataQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_value);
            return;
        }

        /**
        * @brief This function get group data value.
        * @return A sequence of octets representing group data value.
        */
        inline std::vector<octet> const& value() const noexcept 
        {
            return m_value;
        }

        /**
        * @brief This function set group data value.
        * @param [in] value_t A sequence of octets means the group data value to be set to.
        */
        inline void value(std::vector<octet> const& value_t) noexcept
        {
            m_value = value_t;
        }

        /**
         * @brief Compare two GroupDataQosPolicy objects for equailty.
         * @param [in] l_groupData_qos Const Reference of the left GroupDataQosPolicy object.
         * @param [in] r_groupData_qos Const Reference of the right GroupDataQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(GroupDataQosPolicy const& l_groupData_qos, GroupDataQosPolicy const& r_groupData_qos)noexcept
        {
            if (l_groupData_qos.value() == r_groupData_qos.value())
            {
                return true;
            }
            return false;
        }

    private:
        std::vector<octet> m_value;
    };

    /**
    * @brief This policy allows the introduction of a logical partition concept inside the "physical" partition induced by a domain.
    */
    class GS_DDS4CPP_API PartitionQosPolicy : public QosPolicy
    {
    public:
        PartitionQosPolicy() : QosPolicy{ "Partition" }, m_value{} {}

        /**
        * @brief This function serializies PartitionQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_value);
            return;
        }

        /**
        * @brief This function deserializies PartitionQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_value);
            return;
        }

        /**
        * @brief This function get partion value.
        * @return a sequence of string means partion value.
        */
        inline std::vector<std::string> const& value() const noexcept
        {
            return m_value;
        }

        /**
        * @brief This function set pation value.
        * @param [in] value_t A sequence of string representing the partion value to be set to.
        */
        inline void value(std::vector<std::string> const& value_t) noexcept {
            m_value = value_t;
        }

        /**
        * @brief This function add a partion value to partion value sequence.
        * @param [in] val String of the partion value to be added to.
        */
        inline void addValue(std::string const& val) noexcept
        {
            m_value.emplace_back(val);
        }

        /**
         * @brief Compare two PartitionQosPolicy objects for equailty.
         * @param [in] l_partition_qos Const Reference of the left PartitionQosPolicy object.
         * @param [in] r_partition_qos Const Reference of the right PartitionQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(PartitionQosPolicy const& l_partition_qos, PartitionQosPolicy const& r_partition_qos) noexcept
        {
            if (l_partition_qos.value() == r_partition_qos.value())
            {
                return true;
            }
            return false;
        }

    private:
        std::vector<std::string> m_value;
    };

    /**
    * @brief This policy is a hint to the infrastructure as to how to set the priority of the underlying transport used to send the data.
    */
    class GS_DDS4CPP_API TransportPriorityQosPolicy : public QosPolicy
    {
    public:
        TransportPriorityQosPolicy() : QosPolicy{ "TransportPriority" }  {}

        /**
        * @brief This function get transport priority value
        * @return A int number representing the partion value
        */
        inline QosPolicyLong_t const value() const noexcept 
        {
            return m_value;
        }

        /**
        * @brief This function set transport priority value.
        * @param [in] value_t A int number representing the partion value to be added to.
        */
        inline void value(QosPolicyLong_t const value_t) noexcept
        {
            m_value = value_t;
        }
    private:
        QosPolicyLong_t m_value{ 0 };
    };

    /**
    * @brief This policy specifies the maximum duration of validity of the data written by the DataWriter.
    */
    class GS_DDS4CPP_API LifespanQosPolicy : public QosPolicy
    {
    public:
        LifespanQosPolicy() : QosPolicy{ "Lifespan" }, m_duration{ gstone::rtps::Duration_t::duration_infinite() } {}

        /**
        * @brief This function serializies LifespanQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_duration);
            return;
        }

        /**
        * @brief This function deserializies LifespanQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_duration);
            return;
        }

        /**
        * @brief This function get lifespan duration value, this value means the expire time for each sample.
        * @return A Duration class representing lifespan duration value.
        */
        inline gstone::rtps::Duration_t const& duration() const noexcept 
        {
            return m_duration;
        }

        /**
        * @brief This function set lifespan duration value.
        * @param [in] duration_t A Duration class representing lifespan duration value to be set.
        */
        inline void duration(gstone::rtps::Duration_t const& duration_t) noexcept {
            m_duration = duration_t;
        }

        /**
         * @brief Compare two LifespanQosPolicy objects for equailty.
         * @param [in] l_lifespan_qos Const Reference of the left LifespanQosPolicy object.
         * @param [in] r_lifespan_qos Const Reference of the right LifespanQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(LifespanQosPolicy const& l_lifespan_qos, LifespanQosPolicy const& r_lifespan_qos) noexcept
        {
            if (l_lifespan_qos.duration() == r_lifespan_qos.duration())
            {
                return true;
            }
            return false;
        }

    private:
        gstone::rtps::Duration_t m_duration;
    };

    /**
    * @brief This enum class defines different kinds of durability for DurabilityQosPolicy.
    */
    enum class DurabilityQosPolicyKind : guint32_t
    {
        /**
        * The Service does not need to keep any samples of data-instances on behalf of any DataReader that is not known by the 
        * DataWriter at the time the instance is  written. In other words the Service will only attempt to provide the data 
        * to existing subscribers.This is the default kind.
        */
        VOLATILE_DURABILITY_QOS = 0x00,
        /**
        * The service is only required to keep the data in the memory of the DataWriter that wrote the data and the data is not 
        * required to survive the DataWriter.
        */
        TRANSIENT_LOCAL_DURABILITY_QOS,
        /**
        * The service is only required to keep the data in memory and not in permanent storage.
        */
        TRANSIENT_DURABILITY_QOS,
        /**
        * Data is kept on permanent storage, so that they can outlive a system session
        */
        PERSISTENT_DURABILITY_QOS
    };

    /**
    * @brief This policy expresses if the data should outlive their writing time.
    */
    class GS_DDS4CPP_API DurabilityQosPolicy : public QosPolicy
    {
    public:
        DurabilityQosPolicy() : QosPolicy{ "Durability" } {}

        /**
        * @brief This function serializies DurabilityQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_kind);
            return;
        }

        /**
        * @brief This function deserializies DurabilityQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_kind);
            return;
        }

        /**
        * @brief This function get durability kind.
        * @return A enum class representing durability kind.
        */
        inline DurabilityQosPolicyKind kind() const noexcept 
        {
            return m_kind;
        }

        /**
        * @brief This function set durability kind.
        * @param [in] kind_t A enum class representing durability kind to be set to.
        */
        inline void kind(DurabilityQosPolicyKind const kind_t) noexcept 
        {
            m_kind = kind_t;
        }

        /**
         * @brief Compare two DurabilityQosPolicy objects for equailty.
         * @param [in] l_durability_qos Const Reference of the left DurabilityQosPolicy object.
         * @param [in] r_durability_qos Const Reference of the right DurabilityQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(DurabilityQosPolicy const& l_durability_qos, DurabilityQosPolicy const& r_durability_qos) noexcept
        {
            if (l_durability_qos.kind() == r_durability_qos.kind())
            {
                return true;
            }
            return false;
        }

    private:
        DurabilityQosPolicyKind m_kind{ DurabilityQosPolicyKind::VOLATILE_DURABILITY_QOS };
    };

    /**
    * @brief This enum class defines different kinds of presentation order for PresentationQosPolicy.
    */
    enum class PresentationQosPolicyAccessScopeKind : guint32_t
    {
        /**
        * Scope spans only a single instance. Indicates that changes to one instance need not be coherent nor ordered with respect to 
        * changes to any other instance. In other words, order and coherent changes apply to each instance separately.
        */
        INSTANCE_PRESENTATION_QOS = 0x00,
        /**
        * Scope spans to all instances within the same DataWriter (or DataReader), but not across instances in different 
        * DataWriter (or DataReader).
        */
        TOPIC_PRESENTATION_QOS,
        /**
        * Scope spans to all instances belonging to DataWriter (or DataReader) entities within the same Publisher (or Subscriber).
        */
        GROUP_PRESENTATION_QOS
    };

    /**
    * @brief This policy specifies how the samples representing changes to data instances are presented to the subscribing application.
    */
    class GS_DDS4CPP_API PresentationQosPolicy : public QosPolicy
    {
    public:
        PresentationQosPolicy()
            : QosPolicy{ "Presentation" }
        {
        }

        /**
        * @brief This function get access scope kind.
        * @return A enum class representing access scope kind.
        */
        inline PresentationQosPolicyAccessScopeKind const access_scope() const noexcept 
        {
            return m_accessScope;
        }

        /**
        * @brief This function get coherent access kind.
        * @return Whether it supports coherent access.
        */
        inline gbool_t const coherent_access() const noexcept
        {
            return m_coherentAccess;
        }

        /**
        * @brief This function get ordered access kind.
        * @return Whether it supports ordered access.
        */
        inline gbool_t const ordered_access() const noexcept
        {
            return m_orderedAccess;
        }

        /**
        * @brief This function set access scope kind.
        * @param [in] access_scope_t The access scope kind to be set to.
        */
        inline void access_scope(PresentationQosPolicyAccessScopeKind const access_scope_t) noexcept {
            m_accessScope = access_scope_t;
        }

        /**
        * @brief This function set coherent access kind.
        * @param [in] coherent_access_t The coherent access kind to be set to.
        */
        inline void coherent_access(gbool_t const coherent_access_t) noexcept {
            m_coherentAccess = coherent_access_t;
        }

        /**
        * @brief This function set ordered access kind.
        * @param [in] ordered_access_t The ordered access kind to be set to.
        */
        inline void ordered_access(gbool_t const ordered_access_t) noexcept {
            m_orderedAccess = ordered_access_t;
        }

        /**
         * @brief Compare two PresentationQosPolicy objects for equailty.
         * @param [in] f1 Const Reference of the left PresentationQosPolicy object.
         * @param [in] f2 Const Reference of the right PresentationQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(PresentationQosPolicy const &f1, PresentationQosPolicy const &f2) noexcept
        {
            gbool_t const coh_ret{f1.coherent_access() == f2.coherent_access()};
            gbool_t const ord_ret{f1.ordered_access() == f2.ordered_access()};
            return ((coh_ret) && (ord_ret));
        }

        /**
         * @brief Compare two PresentationQosPolicy objects for inequailty.
         * @param [in] f1 Const Reference of the left PresentationQosPolicy object.
         * @param [in] f2 Const Reference of the right PresentationQosPolicy object.
         * @return Return true if inequality, else return false. 
         */
        inline friend gbool_t operator!=(PresentationQosPolicy const &f1, PresentationQosPolicy const &f2) noexcept
        {
            return !(f1 == f2);
        }

    private:
        PresentationQosPolicyAccessScopeKind m_accessScope{ PresentationQosPolicyAccessScopeKind::INSTANCE_PRESENTATION_QOS };
        bool m_coherentAccess{ false };
        bool m_orderedAccess{ false };
    };

    /**
    * @brief This policy specifies the maximum duration(deadline) within which an instance is expected to be updated.
    */
    class GS_DDS4CPP_API DeadlineQosPolicy : public QosPolicy
    {
    public:
        DeadlineQosPolicy() : QosPolicy{ "Deadline" }, m_period{ gstone::rtps::Duration_t::duration_infinite() } {}

        /**
        * @brief This function serializies DeadlineQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_period);
            return;
        }

        /**
        * @brief This function deserializies DeadlineQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_period);
            return;
        }

        /**
        * @brief This function get deadline period value.
        * @return A Duration class representing the deadline qos period.
        */
        inline gstone::rtps::Duration_t const& period() const noexcept 
        {
            return m_period;
        }

        /**
        * @brief This function set deadline period value.
        * @param [in] period_t A Duration class representing the deadline qos period to be set to.
        */
        inline void period(gstone::rtps::Duration_t const& period_t) noexcept {
            m_period = period_t;
        }

        /**
         * @brief Compare two DeadlineQosPolicy objects for equailty.
         * @param [in] l_deadline_qos Const Reference of the left DeadlineQosPolicy object.
         * @param [in] r_deadline_qos Const Reference of the right DeadlineQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(DeadlineQosPolicy const& l_deadline_qos, DeadlineQosPolicy const& r_deadline_qos) noexcept
        {
            if (l_deadline_qos.period() == r_deadline_qos.period())
            {
                return true;
            }
            return false;
        }

    private:
        gstone::rtps::Duration_t m_period;
    };


    /**
    * @brief This policy specifies the maximum acceptable delay from the time the data is written until the data is inserted 
    *        in the receiver's application-cache and the receiving application is notified of the fact.
    */
    class GS_DDS4CPP_API LatencyBudgetQosPolicy : public QosPolicy
    {
    public:
        LatencyBudgetQosPolicy() : QosPolicy{ "LatencyBudget" }, m_duration{ gstone::rtps::Duration_t::duration_zero() } {}

        /**
        * @brief This function serializies LatencyBudgetQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_duration);
            return;
        }

        /**
        * @brief This function deserializies LatencyBudgetQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_duration);
            return;
        }

        /**
        * @brief This function get latency budget duration value.
        * @return A Duration class representing latency budget duration.
        */
        inline gstone::rtps::Duration_t const& duration() const noexcept 
        {
            return m_duration;
        }

        /**
        * @brief This function set latency budget duration value.
        * @param [in] duration_t A Duration class representing latency budget duration to be set to.
        */
        inline void duration(gstone::rtps::Duration_t const& duration_t) noexcept 
        {
            m_duration = duration_t;
        }

        /**
         * @brief Compare two LatencyBudgetQosPolicy objects for equailty.
         * @param [in] l_latencyBudget_qos Const Reference of the left LatencyBudgetQosPolicy object.
         * @param [in] r_latencyBudget_qos Const Reference of the right LatencyBudgetQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(LatencyBudgetQosPolicy const& l_latencyBudget_qos, LatencyBudgetQosPolicy const& r_latencyBudget_qos)noexcept
        {
            if (l_latencyBudget_qos.duration() == r_latencyBudget_qos.duration())
            {
                return true;
            }
            return false;
        }

    private:
        gstone::rtps::Duration_t m_duration;
    };

    /**
    * @brief This enum class defines different kinds of ownership for OwnershipQosPolicy.
    */
    enum class OwnershipQosPolicyKind : guint32_t
    {
        /**
        * Indicates shared ownership for each instance. Multiple writers are allowed to update the same instance and all the updates are made 
        * available to the readers. 
        */
        SHARED_OWNERSHIP_QOS = 0x00,
        /**
        * Indicates each instance can only be owned by one DataWriter, but the owner of an instance can change dynamically.
        */
        EXCLUSIVE_OWNERSHIP_QOS
    };

    /**
    * @brief This policy specifies whether it is allowed for multiple DataWriters to write the same instance of the data.
    */
    class GS_DDS4CPP_API OwnershipQosPolicy : public QosPolicy
    {
    public:
        OwnershipQosPolicy() : QosPolicy{ "Ownership" } {}

        /**
        * @brief This function serializies OwnershipQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_kind);
            return;
        }

        /**
        * @brief This function deserializies OwnershipQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_kind);
            return;
        }

        /**
        * @brief This function get ownership kind.
        * @return A enum class representing ownership kind.
        */
        inline OwnershipQosPolicyKind const kind() const noexcept
        {
            return m_kind;
        }

        /**
        * @brief This function get ownership kind.
        * @param [in] kind_t A enum class representing ownership kind to be set to.
        */
        inline void kind(OwnershipQosPolicyKind const kind_t) noexcept {
            m_kind = kind_t;
        }

        /**
         * @brief Compare two OwnershipQosPolicy objects for equailty.
         * @param [in] l_ownership_qos Const Reference of the left OwnershipQosPolicy object.
         * @param [in] r_ownership_qos Const Reference of the right OwnershipQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(OwnershipQosPolicy const& l_ownership_qos, OwnershipQosPolicy const& r_ownership_qos)noexcept
        {
            if (l_ownership_qos.kind() == r_ownership_qos.kind())
            {
                return true;
            }
            return false;
        }

    private:
        OwnershipQosPolicyKind m_kind{ OwnershipQosPolicyKind::SHARED_OWNERSHIP_QOS };
    };


    /**
    * @brief This policy specifies the value of the "strength" used to arbitrate among multiple DataWriter objects that 
    *        attempt to modify the same instance of a data-object.
    */
    class GS_DDS4CPP_API OwnershipStrengthQosPolicy : public QosPolicy
    {
    public:
        OwnershipStrengthQosPolicy() : QosPolicy{ "OwnershipStrengh" } {}

        /**
        * @brief This function serializies OwnershipStrengthQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_value);
            return;
        }

        /**
        * @brief This function deserializies OwnershipStrengthQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_value);
            return;
        }

        /**
        * @brief This function get ownership strength value.
        * @return A int number representing ownership strength value.
        */
        inline QosPolicyLong_t const value() const noexcept
        {
            return m_value;
        }

        /**
        * @brief This function set ownership strength value.
        * @param [in] value_t A int number representing ownership strength value to be set to.
        */
        inline void value(QosPolicyLong_t const value_t) noexcept 
        {
            m_value = value_t;
        }

        /**
         * @brief Compare two OwnershipStrengthQosPolicy objects for equailty.
         * @param [in] l_owernshipStrength_qos Const Reference of the left OwnershipStrengthQosPolicy object.
         * @param [in] r_owernshipStrength_qos Const Reference of the right OwnershipStrengthQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(OwnershipStrengthQosPolicy const& l_owernshipStrength_qos, OwnershipStrengthQosPolicy const& r_owernshipStrength_qos)noexcept
        {
            if (l_owernshipStrength_qos.value() == r_owernshipStrength_qos.value())
            {
                return true;
            }
            return false;
        }

    private:
        QosPolicyLong_t m_value{ 0 };
    };


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


    /**
    * @brief This policy allows DataReader to specify that it is interested only in (potentially) a subset of the values of the data.
    */
    class GS_DDS4CPP_API TimeBasedFilterQosPolicy : public QosPolicy
    {
    public:
        TimeBasedFilterQosPolicy()
            : QosPolicy{ "TimeBasedFilter" }, m_minimumSeparation{ gstone::rtps::Duration_t::duration_zero() }
        {
        }

        /**
        * @brief This function serializies TimeBasedFilterQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_minimumSeparation);
            return;
        }

        /**
        * @brief This function deserializies TimeBasedFilterQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_minimumSeparation);
            return;
        }

        /**
        * @brief This function get minimum separation.
        * @return A Duration class representing minimum separation.
        */
        inline gstone::rtps::Duration_t const& minimum_separation() const noexcept 
        {
            return m_minimumSeparation;
        }

        /**
        * @brief This function set minimum separation.
        * @param [in] minimum_separation_t A Duration class representing minimum separation to be set to.
        */
        inline void minimum_separation(gstone::rtps::Duration_t const& minimum_separation_t) noexcept {
            m_minimumSeparation = minimum_separation_t;
        }

        /**
         * @brief Compare two TimeBasedFilterQosPolicy objects for equailty.
         * @param [in] l_timeBasedFilter_qos Const Reference of the left TimeBasedFilterQosPolicy object.
         * @param [in] r_timeBasedFilter_qos Const Reference of the right TimeBasedFilterQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(TimeBasedFilterQosPolicy const& l_timeBasedFilter_qos, TimeBasedFilterQosPolicy const& r_timeBasedFilter_qos) noexcept
        {
            if (l_timeBasedFilter_qos.minimum_separation() == r_timeBasedFilter_qos.minimum_separation())
            {
                return true;
            }
            return false;
        }

    private:
        gstone::rtps::Duration_t m_minimumSeparation;    
    };


    /**
    * @brief This enum class defines different kinds of reliability for ReliabilityQosPolicy.
    */
    enum class ReliabilityQosPolicyKind :guint32_t
    {
        /**
        * Indicates that it is acceptable to not retry propagation of any samples. Presumably new values for the samples are generated 
        * often enough that it is not necessary to resend or acknowledge any samples.
        */
        BEST_EFFORT_RELIABILITY_QOS = 0x01,
        /**
        * Specifies the Service will attempt to deliver all samples in its history. Missed samples may be retried. In steady-state (no 
        * modifications communicated via the DataWriter) the middleware guarantees that all samples in the DataWriter history will 
        * eventually be delivered to all the DataReader1 objects.
        */
        RELIABLE_RELIABILITY_QOS
    };


    /**
    * @brief This policy indicates the level of reliability offered/requested by the Service.
    */
    class GS_DDS4CPP_API ReliabilityQosPolicy : public QosPolicy
    {
    public:
        ReliabilityQosPolicy()
            : QosPolicy{ "Reliability" }
        {
        }

        /**
        * @brief This function serializies ReliabilityQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_kind);
            cdr.serialize(m_maxBlockingTime);
            return;
        }

        /**
        * @brief This function deserializies ReliabilityQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_kind);
            cdr.deserialize(m_maxBlockingTime);
            return;
        }

        /**
        * @brief This function get reliability kind.
        * @return A enum class representing reliability kind.
        */
        inline ReliabilityQosPolicyKind const kind() const noexcept
        {
            return m_kind;
        }

        /**
        * @brief This function set reliability kind.
        * @param [in] kind_t A enum class representing reliability kind to be set to.
        */
        inline void kind(ReliabilityQosPolicyKind const kind_t) noexcept 
        {
            m_kind = kind_t;
        }

        /**
        * @brief This function get max blocking time.
        * @return A Duration class representing the maximum time the write operation may block waiting for space to become available.
        */
        inline gstone::rtps::Duration_t const& max_blocking_time() const noexcept 
        {
            return m_maxBlockingTime;
        }

        /**
        * @brief This function set max blocking time.
        * @param [in] max_blocking_time_t A Duration class representing max blocking time to be set to.
        */
        inline void max_blocking_time(gstone::rtps::Duration_t const& max_blocking_time_t) noexcept 
        {
            m_maxBlockingTime = max_blocking_time_t;
        }

        /**
         * @brief Compare two ReliabilityQosPolicy objects for equailty.
         * @param [in] l_reliability_qos Const Reference of the left ReliabilityQosPolicy object.
         * @param [in] r_reliability_qos Const Reference of the right ReliabilityQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(ReliabilityQosPolicy const& l_reliability_qos, ReliabilityQosPolicy const& r_reliability_qos) noexcept
        {
            if (l_reliability_qos.kind() == r_reliability_qos.kind())
            {
                return true;
            }
            return false;
        }

    private:
        ReliabilityQosPolicyKind m_kind{ ReliabilityQosPolicyKind::BEST_EFFORT_RELIABILITY_QOS };
        gstone::rtps::Duration_t m_maxBlockingTime{ DEFAULT_MAX_BLOCKING_TIME };
    };


    /**
    * @brief This enum class defines different kinds of destination order for DestinationOrderQosPolicy.
    */
    enum class DestinationOrderQosPolicyKind :guint32_t
    {
        /**
        * Indicates that data is ordered based on the reception time at each Subscriber.
        */
        BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS = 0x00,
        /**
        * Indicates that data is ordered based on a timestamp placed at the source (by the Service or by the application).
        */
        BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS
    };


    /**
    * @brief This policy controls the criteria used to determine the logical order among changes made by Publisher entities to 
    *        the same instance of data.
    */
    class GS_DDS4CPP_API DestinationOrderQosPolicy : public QosPolicy
    {
    public:
        DestinationOrderQosPolicy()
            : QosPolicy{ "DestinationOrder" }
        {
        }

        /**
        * @brief This function serializies DestinationOrderQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_kind);
            return;
        }

        /**
        * @brief This function deserializies DestinationOrderQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_kind);
            return;
        }

        /**
        * @brief This function get destination order kind.
        * @return A enum class representing destination order kind.
        */
        inline DestinationOrderQosPolicyKind const kind() const noexcept
        {
            return m_kind;
        }

        /**
        * @brief This function set destination order kind.
        * @param [in] kind_t A enum class representing destination order kind to be set to.
        */
        inline void kind(DestinationOrderQosPolicyKind const kind_t) noexcept {
            m_kind = kind_t;
        }

        /**
         * @brief Compare two DestinationOrderQosPolicy objects for equailty.
         * @param [in] l_destinationOrder_qos Const Reference of the left DestinationOrderQosPolicy object.
         * @param [in] r_destinationOrder_qos Const Reference of the right DestinationOrderQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(DestinationOrderQosPolicy const& l_destinationOrder_qos, DestinationOrderQosPolicy const& r_destinationOrder_qos) noexcept
        {
            if (l_destinationOrder_qos.kind() == r_destinationOrder_qos.kind())
            {
                return true;
            }
            return false;
        }

    private:
        DestinationOrderQosPolicyKind m_kind{ DestinationOrderQosPolicyKind::BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS };
    };


    /**
    * @brief This enum class defines different kinds of history policy for HistoryQosPolicy.
    */
    enum class HistoryQosPolicyKind :guint32_t
    {
        /**
        * On the publishing side, the Service will only attempt to keep the most recent "depth" samples of each instance of data 
        * (identified by its key) managed by the DataWriter. On the subscribing side, the DataReader will only attempt to keep the most 
        * recent "depth" samples received for each instance (identified by its key) until the application "takes" them via the 
        * DataReader’s take operation.
        */
        KEEP_LAST_HISTORY_QOS = 0x00,
        /**
        * On the publishing side, the Service will attempt to keep all samples (representing each value written) of each instance of data 
        * (identified by its key) managed by the DataWriter until they can be delivered to all subscribers. On the subscribing side, the 
        * Service will attempt to keep all samples of each instance of data (identified by its key) managed by the DataReader.
        */
        KEEP_ALL_HISTORY_QOS
    };

    /**
    * @brief This policy specifies the behavior of the Service in the case where the value of a sample changes (one or more times) before 
    *        it can be successfully communicated to one or more existing subscribers.
    */
    class GS_DDS4CPP_API HistoryQosPolicy : public QosPolicy
    {
    public:
        HistoryQosPolicy() : QosPolicy{ "History" } {}

        /**
        * @brief This function get history kind.
        * @return A enum class representing history kind.
        */
        HistoryQosPolicyKind const kind() const noexcept 
        {
            return m_kind;
        }

        /**
        * @brief This function set history kind.
        * @param [in] kind_t A enum class representing history kind to be set to.
        */
        inline void kind(HistoryQosPolicyKind const kind_t) noexcept 
        {
            m_kind = kind_t;
        }

        /**
        * @brief This function get depth the Service will maintain and deliver.
        * @return A int number representing the maximum number of values the Service will maintain and deliver.
        */
        inline QosPolicyLong_t const depth() const noexcept
        {
            return m_depth;
        }

        /**
        * @brief This function get depth the Service will maintain and deliver.
        * @param [in] depth_t A int number representing depth to be set to.
        */
        inline void depth(QosPolicyLong_t const depth_t) noexcept 
        {
            m_depth = depth_t;
        }

        /**
         * @brief Compare two HistoryQosPolicy objects for equailty.
         * @param [in] l_history_qos Const Reference of the left HistoryQosPolicy object.
         * @param [in] r_history_qos Const Reference of the right HistoryQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(HistoryQosPolicy const& l_history_qos, HistoryQosPolicy const& r_history_qos) noexcept
        {
            if ((l_history_qos.kind() == r_history_qos.kind()) && (l_history_qos.depth() == r_history_qos.depth()))
            {
                return true;
            }
            return false;
        }

    private:
        HistoryQosPolicyKind m_kind{ HistoryQosPolicyKind::KEEP_LAST_HISTORY_QOS };
        QosPolicyLong_t m_depth{ 1 };
    };


    /**
    * @brief This policy controls the resources that the Service can use in order to meet the requirements imposed by the application
    *           and other QoS settings.
    */
    class GS_DDS4CPP_API ResourceLimitsQosPolicy : public QosPolicy
    {
    public:
        ResourceLimitsQosPolicy()
            : QosPolicy{ "ResourceLimits" }
        {

        }

        /**
         * @brief This function get max samples.
         * @return A int number representing the maximum number of instances DataWriter (or DataReader) can manage.
         */
        inline QosPolicyLong_t const max_samples() const noexcept
        {
            return m_maxSamples;
        }

        /**
         * @brief This function set max samples.
         * @param [in] max_samples_t A int number representing max smaples to be set to.
         */
        inline void max_samples(QosPolicyLong_t const max_samples_t) noexcept 
        {
            m_maxSamples = max_samples_t;
        }

        /**
         * @brief This function get max instances.
         * @return A int number representing the maximum number of data samples the DataWriter (or DataReader) can manage across
         *         all the instances associated with it.
         */
        inline QosPolicyLong_t const max_instances() const noexcept
        {
            return m_maxInstances;
        }

        /**
         * @brief This function set max instances.
         * @param [in] max_instances_t A int number representing max instances to be set to.
         */
        inline void max_instances(QosPolicyLong_t const max_instances_t) noexcept 
        {
            m_maxInstances = max_instances_t;
        }

        /**
         * @brief This function get max instances.
         * @return A int number representing the maximum number of samples of any one instance a DataWriter(or DataReader) can manage.
         */
        inline QosPolicyLong_t const max_samples_per_instance() const noexcept
        {
            return m_maxSamplesPerInstance;
        }

        /**
         * @brief This function set max samples per instance.
         * @param [in] max_samples_per_instance_t A int number representing max samples per instance to be set to.
         */
        inline void max_samples_per_instance(QosPolicyLong_t const max_samples_per_instance_t) noexcept 
        {
            m_maxSamplesPerInstance = max_samples_per_instance_t;
        }

        /**
         * @brief Compare two ResourceLimitsQosPolicy objects for equailty.
         * @param [in] l_resourceLimits_qos Const Reference of the left ResourceLimitsQosPolicy object.
         * @param [in] r_resourceLimits_qos Const Reference of the right ResourceLimitsQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(ResourceLimitsQosPolicy const& l_resourceLimits_qos, ResourceLimitsQosPolicy const& r_resourceLimits_qos) noexcept
        {
            if ((l_resourceLimits_qos.max_instances() == r_resourceLimits_qos.max_instances())
                && (l_resourceLimits_qos.max_samples() == r_resourceLimits_qos.max_samples())
                && (l_resourceLimits_qos.max_samples_per_instance() == r_resourceLimits_qos.max_samples_per_instance()))
            {
                return true;
            }
            return false;
        }

    private:
        QosPolicyLong_t m_maxSamples{ LENGTH_UNLIMITED };
        QosPolicyLong_t m_maxInstances{ LENGTH_UNLIMITED };
        QosPolicyLong_t m_maxSamplesPerInstance{ LENGTH_UNLIMITED };
    };


    /**
    * @brief This policy controls the behavior of the entity when acting as a factory for other entities.
    */
    class GS_DDS4CPP_API EntityFactoryQosPolicy : public QosPolicy
    {
    public:
        EntityFactoryQosPolicy() : QosPolicy{ "EntityFactory" } {}

        /**
        * @brief This function get autoenable_created_entities kind.
        * @return Whether the entity acting as a factory automatically enables the instances it creates.
        */
        inline gbool_t const autoenable_created_entities() const noexcept 
        {
            return m_autoenableCreatedEntities;
        }

        /**
        * @brief This function set autoenable_created_entities kind.
        * @param [in] autoenable_created_entities_t The kind of autoenable_created_entities to be set to.
        */
        inline void autoenable_created_entities(gbool_t const autoenable_created_entities_t) noexcept 
        {
            m_autoenableCreatedEntities = autoenable_created_entities_t;
        }

        /**
         * @brief Compare two EntityFactoryQosPolicy objects for equailty.
         * @param [in] f1_qos Const Reference of the left EntityFactoryQosPolicy object.
         * @param [in] f2_qos Const Reference of the right EntityFactoryQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(EntityFactoryQosPolicy const& f1_qos, EntityFactoryQosPolicy const& f2_qos) noexcept
        {
            if (f1_qos.autoenable_created_entities() == f2_qos.autoenable_created_entities())
            {
                return true;
            }
            return false;
        }

        /**
         * @brief Compare two EntityFactoryQosPolicy objects for inequailty.
         * @param [in] f1_qos Const Reference of the left EntityFactoryQosPolicy object.
         * @param [in] f2_qos Const Reference of the right EntityFactoryQosPolicy object.
         * @return Return true if inequality, else return false. 
         */
        inline friend gbool_t operator!=(EntityFactoryQosPolicy const& f1_qos, EntityFactoryQosPolicy const& f2_qos) noexcept
        {
            return !(f1_qos == f2_qos);
        }

    private:
        bool m_autoenableCreatedEntities{ true };
    };


    /**
    *@brief This policy specifies the behavior of the DataWriter with regards to the lifecycle of the data instances it manages.
    */
    class GS_DDS4CPP_API WriterDataLifecycleQosPolicy : public QosPolicy
    {
    public:
        WriterDataLifecycleQosPolicy()
            : QosPolicy{ "WriterDataLifecycle" }
        {
        }

        /**
        * @brief This function get autodispose_unregistered_instances kind.
        * @return whether a DataWriter will automatically dispose instances each time they are unregistered.
        */
        inline gbool_t const autodispose_unregistered_instances() const noexcept 
        {
            return m_autodisposeUnregisteredInstances;
        }

        /**
        * @brief This function get autodispose_unregistered_instances kind.
        * @param [in] autodispose_unregistered_instances_t Whether a DataWriter will automatically dispose instances each time they are unregistered.
        */
        inline void autodispose_unregistered_instances(gbool_t const autodispose_unregistered_instances_t) noexcept 
        {
            m_autodisposeUnregisteredInstances = autodispose_unregistered_instances_t;
        }

    private:
        bool m_autodisposeUnregisteredInstances{ false };
    };


    /**
    *@brief This policy specifies the behavior of the DataReader with regards to the lifecycle of the data instances it manages.
    */
    class GS_DDS4CPP_API ReaderDataLifecycleQosPolicy : public QosPolicy
    {
    public:
        ReaderDataLifecycleQosPolicy()
            : QosPolicy{ "ReaderDataLifecycle" },
            m_autopurgeNowriterSamplesDelay{ gstone::rtps::Duration::duration_infinite() },
            m_autopurgeDisposedSamplesDelay{ gstone::rtps::Duration::duration_infinite() }
        {
        }

        /**
        * @brief This function get autopurge_nowriter_samples_delay.
        * @return A Duration class representing the duration the DataReader must retain information regarding instances that 
        *         have the instance_stateNOT_ALIVE_NO_WRITERS.
        */
        inline gstone::rtps::Duration_t const& autopurge_nowriter_samples_delay() const noexcept 
        {
            return m_autopurgeNowriterSamplesDelay;
        }

        /**
        * @brief This function set autopurge_nowriter_samples_delay.
        * @param [in] autopurge_nowriter_samples_delay_t A Duration class representing autopurge_nowriter_samples_delay to be set to.
        */
        inline void autopurge_nowriter_samples_delay(gstone::rtps::Duration_t const& autopurge_nowriter_samples_delay_t) noexcept 
        {
            m_autopurgeNowriterSamplesDelay = autopurge_nowriter_samples_delay_t;
        }

        /**
        * @brief This function get autopurge_disposed_samples_delay.
        * @return A Duration class representing  the duration the DataReader must retain information regarding instances that 
        *         have the instance_stateNOT_ALIVE_DISPOSED.
        */
        inline gstone::rtps::Duration_t const& autopurge_disposed_samples_delay() const noexcept 
        {
            return m_autopurgeDisposedSamplesDelay;
        }

        /**
        * @brief This function set autopurge_disposed_samples_delay.
        * @param [in] autopurge_disposed_samples_delay_t A Duration class representing autopurge_disposed_samples_delay to be set to.
        */
        inline void autopurge_disposed_samples_delay(gstone::rtps::Duration_t const& autopurge_disposed_samples_delay_t) noexcept 
        {
            m_autopurgeDisposedSamplesDelay = autopurge_disposed_samples_delay_t;
        }

    private:
        gstone::rtps::Duration_t m_autopurgeNowriterSamplesDelay;
        gstone::rtps::Duration_t m_autopurgeDisposedSamplesDelay;
    };


    /**
    *@brief This policy specifies the configuration of the durability service.
    */
    class GS_DDS4CPP_API DurabilityServiceQosPolicy : public QosPolicy
    {
    public:
        DurabilityServiceQosPolicy()
            : QosPolicy{ "DurabilityService" }
        {
        }

        /**
        * @brief This function get service_cleanup_delay.
        * @return A Duration class representing service_cleanup_delay that control when the service is able to remove
        *         all information regarding a data-instance.
        */
        inline gstone::rtps::Duration_t const& service_cleanup_delay() const noexcept 
        {
            return m_serviceCleanupDelay;
        }

        /**
        * @brief This function get history_kind.
        * @return A enum class representing history_kind that controls the HISTORY QoS of the fictitious DataReader that stores the data
        *         within the durability service.
        */
        inline HistoryQosPolicyKind const history_kind() const noexcept
        {
            return m_historyKind;
        }

        /**
        * @brief This function get history_depth.
        * @return A int number representing history_depth that controls the HISTORY QoS of the fictitious DataReader that stores the data
        *         within the durability service.
        */
        inline QosPolicyLong_t const history_depth() const noexcept 
        {
            return m_historyDepth;
        }

        /**
        * @brief This function get max_samples.
        * @return A int number  representing max_samples that controls the HISTORY QoS of the fictitious DataReader that stores the data
        *         within the durability service.
        */
        inline QosPolicyLong_t const max_samples() const noexcept 
        {
            return m_maxSamples;
        }

        /**
        * @brief This function get max_instances.
        * @return A int number representing max_instances that controls the HISTORY QoS of the fictitious DataReader that stores the data
        *         within the durability service.
        */
        inline QosPolicyLong_t const max_instances() const noexcept 
        {
            return m_maxInstances;
        }

        /**
        * @brief This function get max_samples_per_instance.
        * @return A int number representing max_samples_per_instance that controls the HISTORY QoS of the fictitious DataReader that stores the data
        *         within the durability service.
        */
        inline QosPolicyLong_t const max_samples_per_instance() const noexcept 
        {
            return m_maxSamplesPerInstance;
        }

        /**
        * @brief This function set history_kind.
        * @param [in] history_kind_t A Duration class representing history_kind to be set to.
        */
        inline void history_kind(HistoryQosPolicyKind const history_kind_t) noexcept 
        {
            m_historyKind = history_kind_t;
        }

        /**
        * @brief This function set service_cleanup_delay.
        * @param [in] service_cleanup_delay_t A Duration class representing service_cleanup_delay to be set to.
        */
        inline void service_cleanup_delay(gstone::rtps::Duration_t const& service_cleanup_delay_t) noexcept 
        {
            m_serviceCleanupDelay = service_cleanup_delay_t;
        }

        /**
        * @brief This function set service_cleanup_delay.
        * @param [in] history_depth_t A int number representing history_depth to be set to.
        */
        inline void history_depth(QosPolicyLong_t const history_depth_t) noexcept 
        {
            m_historyDepth = history_depth_t;
        }

        /**
        * @brief This function set max_samples.
        * @param [in] max_samples_t A int number representing max_samples to be set to.
        */
        inline void max_samples(QosPolicyLong_t const max_samples_t) noexcept 
        {
            m_maxSamples = max_samples_t;
        }

        /**
        * @brief This function set max_instances.
        * @param [in] max_instances_t A int number representing max_instances to be set to.
        */
        inline void max_instances(QosPolicyLong_t const max_instances_t) noexcept 
        {
            m_maxInstances = max_instances_t;
        }

        /**
        * @brief This function set max_samples_per_instance.
        * @param [in] max_samples_per_instance_t A int number representing max_samples_per_instance to be set to.
        */
        inline void max_samples_per_instance(QosPolicyLong_t const max_samples_per_instance_t) noexcept {
            m_maxSamplesPerInstance = max_samples_per_instance_t;
        }

    private:
        gstone::rtps::Duration_t m_serviceCleanupDelay{ gstone::rtps::Duration::duration_zero() };
        HistoryQosPolicyKind m_historyKind{ HistoryQosPolicyKind::KEEP_LAST_HISTORY_QOS };
        QosPolicyLong_t m_historyDepth{ 1 };
        QosPolicyLong_t m_maxSamples{ LENGTH_UNLIMITED };
        QosPolicyLong_t m_maxInstances{ LENGTH_UNLIMITED };
        QosPolicyLong_t m_maxSamplesPerInstance{ LENGTH_UNLIMITED };
    };

    /*
    class GS_DDS4CPP_API DomainParticipantFactoryQos
    {
    public:
        EntityFactoryQosPolicy entity_factory;
    };
    */

    /**
    * @brief This enum class defines different kinds of switch for ThreadScheduleQosPolicy
    */
    enum class ThreadScheduleSwitch :guint32_t
    {
        /**
        * Use thread schedule.
        */
        ON,
        /**
        * Not use thread schedule.
        */
        OFF
    };

    /**
    * @brief This policy controls thread schedule.
    */
    class GS_DDS4CPP_API ThreadScheduleQosPolicy : public QosPolicy
    {
    public:
        ThreadScheduleQosPolicy()
            : QosPolicy{ "ThreadSchedule" }
            {}

        /**
        * @brief This function get thread schedule kind.
        * @return A enum class representing thread schedule kind.
        */
        ThreadScheduleSwitch const kind() const noexcept 
        {
            return m_kind;
        }

        /**
        * @brief This function set thread schedule kind.
        * @return kind_t A enum class representing thread schedule kind to be set to.
        */
        inline void kind(ThreadScheduleSwitch const kind_t) noexcept 
        {
            m_kind = kind_t;
        }

        /**
        * @brief This function get locator list.
        * @return Const reference of a sequence of locator.
        */
        inline gstone::rtps::LocatorList_t const& locator_list() const noexcept
        {
            return m_locatorList;
        }

        /**
        * @brief This function get locator list.
        * @return Reference of a sequence of locator.
        */
        inline gstone::rtps::LocatorList_t& locator_list() noexcept {
            return m_locatorList;
        }

        /**
        * @brief This function set locator list.
        * @param [in] locator_list_t Const reference of a sequence of locator to be set to.
        */
        inline void locator_list(gstone::rtps::LocatorList_t const& locator_list_t) noexcept 
        {
            m_locatorList = locator_list_t;
        }


    private:
        ThreadScheduleSwitch m_kind{ ThreadScheduleSwitch::OFF };
        gstone::rtps::LocatorList_t m_locatorList{};
    };
}/*qos*/
}/*dds*/


__GS_DDS4CPP_END_DECLS

#endif