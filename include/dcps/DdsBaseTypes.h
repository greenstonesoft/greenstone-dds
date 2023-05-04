/**************************************************************
 * @file DdsBaseTypes.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_DDS_BASE_TYPE_H
#define GSTONE_DDS_BASE_TYPE_H 1

#include <memory>
//#include <string.h>
#include "dcps/PITypes.h"
#include "dcps/DeclExport.h"
#include "rtps/InstanceHandle.h"
#include "rtps/Duration.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace DDS 
{
    using DomainId_t = guint32_t;
    using Time_t = gint64_t;

    constexpr DDS::DomainId_t DEFAULT_DOMAIN_ID{1U};
    constexpr gint64_t DEFAULT_PARTICIPANT_ID{0};

    gstone::rtps::InstanceHandle_t const HANDLE_NIL {};

    //return codes
    enum class ReturnCode_t : int32_t
    {
        RETCODE_OK = 0,
        RETCODE_ERROR = 1,
        RETCODE_UNSUPPORTED = 2,
        RETCODE_BAD_PARAMETER = 3,
        RETCODE_PRECONDITION_NOT_MET = 4,
        RETCODE_OUT_OF_RESOURCES = 5,
        RETCODE_NOT_ENABLED = 6,
        RETCODE_IMMUTABLE_POLICY = 7,
        RETCODE_INCONSISTENT_POLICY = 8,
        RETCODE_ALREADY_DELETED = 9,
        RETCODE_TIMEOUT = 10,
        RETCODE_NO_DATA = 11,
        RETCODE_ILLEGAL_OPERATION = 12
    };

    using QosPolicyId_t = guint32_t;
    using SampleStateMask = guint32_t;
    constexpr SampleStateMask ANY_SAMPLE_STATE{0xFFFFU};
    enum SampleStateKind : guint32_t
    {
        READ_SAMPLE_STATE = 0x0001 << 0,
        NOT_READ_SAMPLE_STATE = 0x0001 << 1,
    };

    using ViewStateMask = guint32_t;
    constexpr ViewStateMask ANY_VIEW_STATE{0xFFFFU};
    enum ViewStateKind : guint32_t
    {
        NEW_VIEW_STATE = 0x0001 << 0,
        NOT_NEW_VIEW_STATE = 0x0001 << 1,
    };

    using InstanceStateMask = guint32_t;
    constexpr InstanceStateMask ANY_INSTANCE_STATE{0xFFFFU};
    enum InstanceStateKind : guint32_t
    {
        ALIVE_INSTANCE_STATE = 0x0001 << 0,
        NOT_ALIVE_DISPOSED_INSTANCE_STATE = 0x0001 << 1,
        NOT_ALIVE_NO_WRITERS_INSTANCE_STATE = 0x0001 << 2,
    };

    enum StatusKind:guint32_t
    {
        INCONSISTENT_TOPIC_STATUS         = 0x0001 << 0,  // topic
        OFFERED_DEADLINE_MISSED_STATUS    = 0x0001 << 1,  // reader
        REQUESTED_DEADLINE_MISSED_STATUS  = 0x0001 << 2,  // writer
        OFFERED_INCOMPATIBLE_QOS_STATUS   = 0x0001 << 5,  // reader
        REQUESTED_INCOMPATIBLE_QOS_STATUS = 0x0001 << 6,  // writer
        SAMPLE_LOST_STATUS                = 0x0001 << 7,  // reader
        SAMPLE_REJECTED_STATUS            = 0x0001 << 8,  // reader
        DATA_ON_READERS_STATUS            = 0x0001 << 9,  // reader
        DATA_AVAILABLE_STATUS             = 0x0001 << 10, // reader
        LIVELINESS_LOST_STATUS            = 0x0001 << 11, // writer
        LIVELINESS_CHANGED_STATUS         = 0x0001 << 12, // writer
        PUBLICATION_MATCHED_STATUS        = 0x0001 << 13, // writer
        SUBSCRIPTION_MATCHED_STATUS       = 0x0001 << 14  // reader
    };

    //Status to support liseners and conditions
    using StatusMask = guint32_t;
    constexpr StatusMask EmptyStatusMask { 0U };
    constexpr StatusMask AllStatusMask {0x7FE7U};

    //sampleRejctStatusKInd
    enum SampleRejectedStatusKind
    {
        NOT_REJECTED = 0,
        REJECTED_BY_INSTANCES_LIMIT,
        REJECTED_BY_SAMPLES_LIMIT,
        REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT
    };

    enum class ObjectType :guint32_t
    {
        UNDEFINED=0,
        WAITSET,
        LISTENER,
        DOMAINPARTICIPANTLISTENER,
        PUBLISHERLISTENER,
        SUBSCRIBERLISTENER,
        DATAREADERLISTENER,
        DATAWRITERLISTENER,
        TOPICLISTENER,
        CONDITION,
        STATUSCONDITION,
        GUARDCONDITION,
        READCONDITION,
        QUERYCONDITION,
        DOMAINPARTICIPANT,
        PUBLISHER,
        SUBSCRIBER,
        DATAWRITER,
        DATAREADER,
        DATAREADERVIEW,
        TOPICDESCRIPTION,
        TOPIC,
        CONTENTFILTEREDTOPIC,
    };

    enum class EntityType :guint32_t
    {
        UNDEFINED=0,
        DOMAINPARTICIPANT,
        PUBLISHER,
        SUBSCRIBER,
        DATAWRITER,
        DATAREADER,
        TOPIC,
    };
}

__GS_DDS4CPP_END_DECLS

#endif
