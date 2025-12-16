#ifndef GSTONE_ERRNO_H
#define GSTONE_ERRNO_H
#include "swiftdds/dcps/DeclExport.h"
#include "swiftdds/dcps/PITypes.h"

__GS_DDS4CPP_BEGIN_DECLS

#define GSDDS_ERRNO_NO_ERROR (0U)       /* no error. */
#define GSDDS_ERRNO_INVALID (1U)        /* gsdds_errno is invalid. */
#define GSDDS_ERRNO_PARTICIPANT0 (100U) /* config error, The period of spdp should be smaller than lease duration. */
#define GSDDS_ERRNO_PARTICIPANT1 (101U) /* config error, The domainId should be range (0~230). */
#define GSDDS_ERRNO_PARTICIPANT2 (102U) /* config error, The participantId should be range (0~120). */
#define GSDDS_ERRNO_PARTICIPANT3 (103U) /* system error, can't reader net card info. */
#define GSDDS_ERRNO_PARTICIPANT4 (104U) /* system error, no ip address. */
#define GSDDS_ERRNO_PARTICIPANT5 (105U) /* ddslib error, participant locator regist error. */
#define GSDDS_ERRNO_PARTICIPANT6 (106U) /* ddslib error, spdp locator regist error. */
#define GSDDS_ERRNO_TOPIC0 (200U)       /* user error, create topic failed because this topic is registered. */
#define GSDDS_ERRNO_READER0 (300U)      /* ddslib error, In this version, the service can create 20 datawrites or datareaders at most. */
#define GSDDS_ERRNO_READER1 (301U)      /* user error, invalid paramter,topic is nullptr. */
#define GSDDS_ERRNO_READER2 (302U)      /* qos error, liveliness.lease_duration < 50ms. */
#define GSDDS_ERRNO_READER3 (303U)      /* qos error, time_based_filter >= deadline. */
#define GSDDS_ERRNO_READER4 (304U)      /* qos error, must verify that depth <= max_samples_per_instance <= max_samples. */
#define GSDDS_ERRNO_READER5 (305U)      /* qos error, domainparticipant of subscriber is nullptr. */
#define GSDDS_ERRNO_READER6 (306U)      /* user error, reader's topic is useless. */
#define GSDDS_ERRNO_READER7 (307U)      /* user error, get register type is fail. */
#define GSDDS_ERRNO_READER8 (308U)      /* user error, reader topic is created by other participant. */
#define GSDDS_ERRNO_READER9 (309U)      /* user error, reader's topic or subscriber is unenable. */
#define GSDDS_ERRNO_READER10 (310U)     /* ddslib error, topic type is null. */
#define GSDDS_ERRNO_WRITER0 (400U)      /* ddslib error, In this version, the service can create 20 datawrites or datareaders at most. */
#define GSDDS_ERRNO_WRITER1 (401U)      /* user error, topic is nullptr. */
#define GSDDS_ERRNO_WRITER2 (402U)      /* qos error, liveliness.lease_duration < 50ms. */
#define GSDDS_ERRNO_WRITER3 (403U)      /* qos error, must verify that depth <= max_samples_per_instance <= max_samples. */
#define GSDDS_ERRNO_WRITER4 (404U)      /* ddslib error, domainParticipant of publisher is nullptr. */
#define GSDDS_ERRNO_WRITER5 (405U)      /* ddslib error, writer's topic is useless. */
#define GSDDS_ERRNO_WRITER6 (406U)      /* ddslib error, getRegisteredType failed. type is nullptr. */
#define GSDDS_ERRNO_WRITER7 (407U)      /* ddslib error, writer topic is created by other participant. */
#define GSDDS_ERRNO_WRITER8 (408U)      /* qos error, participant's shared memory size is less than wrtier's shared memroy max frag size. */
#define GSDDS_ERRNO_WRITER9 (409U)      /* ddslib error, writer's topic or publisher is unenable. */
#define GSDDS_ERRNO_WRITER10 (410U)      /* ddslib error, publisher coherent set is enalbe, not allowed create or remove DataWriter. */
#define GSDDS_ERRNO_SEND0 (500U)        /* participant is unenable. */
#define GSDDS_ERRNO_SEND1 (501U)        /* writerHistoryCache remove_a_instance fail. */
#define GSDDS_ERRNO_SEND2 (502U)        /* writerHistoryCache add_change fail. */
#define GSDDS_ERRNO_RECV0 (600U)        /* participant, store too much msgData. */
#define GSDDS_ERRNO_MEMORY0 (700U)      /* out of memory. */

namespace greenstone
{
    namespace dds
    {
        GS_DDS4CPP_API extern guint32_t *dds_errno();
        GS_DDS4CPP_API extern const gchar_t *dds_strerror(guint32_t errnum);
    }
}

#define gsdds_errno (*greenstone::dds::dds_errno())
#define gsdds_strerror(err) (greenstone::dds::dds_strerror(err))

__GS_DDS4CPP_END_DECLS

#endif
