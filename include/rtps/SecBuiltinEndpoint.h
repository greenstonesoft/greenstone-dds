/**************************************************************
 * @file SecBuiltinEndpoint.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
 **************************************************************/
#ifndef GSTONE_SECBUILTINENDPOINT_H
#define GSTONE_SECBUILTINENDPOINT_H 1

namespace gstone
{
namespace rtps
{

constexpr guint32_t RTPS_PARTICIPANT_ENTITY_ID {0x000001C1UL};



constexpr guint32_t ENTITYID_SEDP_BUILTIN_PUBLICATIONS_SECURE_WRITER  {0xFF0003C2UL};
constexpr guint32_t ENTITYID_SEDP_BUILTIN_PUBLICATIONS_SECURE_READER  {0xFF0003C7UL};
constexpr guint32_t ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_SECURE_WRITER {0xFF0004C2UL};
constexpr guint32_t ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_SECURE_READER  {0xFF0004C7UL};
constexpr guint32_t ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_SECURE_WRITER {0xFF0200C2UL};
constexpr guint32_t ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_SECURE_READER {0xFF0200C7UL};
constexpr guint32_t ENTITYID_P2P_BUILTIN_PARTICIPANT_STATELESS_WRITER {0x000201C3UL};
constexpr guint32_t ENTITYID_P2P_BUILTIN_PARTICIPANT_STATELESS_READER {0x000201C4UL};
constexpr guint32_t ENTITYID_P2P_BUILTIN_PARTICIPANT_VOLATILE_MESSAGE_SECURE_WRITER  {0xFF0202C3UL};
constexpr guint32_t ENTITYID_P2P_BUILTIN_PARTICIPANT_VOLATILE_MESSAGE_SECURE_READER  {0xFF0202C4UL};
constexpr guint32_t ENTITYID_SPDP_RELIABLE_BUILTIN_PARTICIPANT_SECURE_WRITER {0xFF0101C2UL};
constexpr guint32_t ENTITYID_SPDP_RELIABLE_BUILTIN_PARTICIPANT_SECURE_READER {0xFF0101C7UL};







constexpr guint32_t DISC_BUILTIN_ENDPOINT_PUBLICATION_SECURE_ANNOUNCER       {(0x00000001UL << 16)};
constexpr guint32_t DISC_BUILTIN_ENDPOINT_PUBLICATION_SECURE_DETECTOR        {(0x00000001UL << 17)};
constexpr guint32_t DISC_BUILTIN_ENDPOINT_SUBSCRIPTION_SECURE_ANNOUNCER      {(0x00000001UL << 18)};
constexpr guint32_t DISC_BUILTIN_ENDPOINT_SUBSCRIPTION_SECURE_DETECTOR       {(0x00000001UL << 19)};
constexpr guint32_t BUILTIN_ENDPOINT_PARTICIPANT_MESSAGE_SECURE_DATA_WRITER  {(0x00000001UL << 20)};
constexpr guint32_t BUILTIN_ENDPOINT_PARTICIPANT_MESSAGE_SECURE_DATA_READER  {(0x00000001UL << 21)};
constexpr guint32_t BUILTIN_ENDPOINT_PARTICIPANT_STATELESS_MESSAGE_WRITER    {(0x00000001UL << 22)};
constexpr guint32_t BUILTIN_ENDPOINT_PARTICIPANT_STATELESS_MESSAGE_READER    {(0x00000001UL << 23)};
constexpr guint32_t BUILTIN_ENDPOINT_PARTICIPANT_VOLATILE_MESSAGE_SECURE_WRITER {(0x00000001UL << 24)};
constexpr guint32_t BUILTIN_ENDPOINT_PARTICIPANT_VOLATILE_MESSAGE_SECURE_READER {(0x00000001UL << 25)};
constexpr guint32_t DISC_BUILTIN_ENDPOINT_PARTICIPANT_SECURE_ANNOUNCER       {(0x00000001UL << 26)};
constexpr guint32_t DISC_BUILTIN_ENDPOINT_PARTICIPANT_SECURE_DETECTOR        {(0x00000001UL << 27)};



}/*rtps*/
}/*gstone*/

#endif /*GSTONE_RTPS_SECBUILTINENDPOINT_H*/
