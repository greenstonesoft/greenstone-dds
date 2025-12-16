/**************************************************************
 * @file ParticipantSecurityInfo.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
 **************************************************************/
#ifndef GSTONE_PARTICIPANTSECURITYINFO_H
#define GSTONE_PARTICIPANTSECURITYINFO_H 1

#include "swiftdds/dcps/PITypes.h"
#include "swiftdds/rtps/DdsCdr.h"

namespace gstone
{
namespace rtps
{
class DdsCdr;
}
}


namespace gstone
{
	namespace security
	{

		using PluginParticipantSecurityAttributesMask = guint32_t;

		constexpr guint32_t PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_RTPS_ENCRYPTED                  {(0x00000001UL << 0)};
		constexpr guint32_t PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_BUILTIN_IS_DISCOVERY_ENCRYPTED     {(0x00000001UL << 1)};
		constexpr guint32_t PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_LIVELINESS_ENCRYPTED            {(0x00000001UL << 2)};
		constexpr guint32_t PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_RTPS_ORIGIN_AUTHENTICATED       {(0x00000001UL << 3)};
		constexpr guint32_t PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_DISCOVERY_ORIGIN_AUTHENTICATED  {(0x00000001UL << 4)};
		constexpr guint32_t PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_LIVELINESS_ORIGIN_AUTHENTICATED {(0x00000001UL << 5)};

		constexpr guint32_t PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_VALID                           {(0x00000001UL << 31)};
		constexpr guint32_t PARTICIPANT_SECURITY_OFFSET_31 {31U};
// #define PARTICIPANT_SECURITY_INFO_DEFAULT_ATTRIBUTES {0, 0}

		/**
		 * @class PluginParticipantSecurityAttributes
		 * @brief this class describe plugin-specific behavior of the builtin DDS-crypto
		*/
		class GS_DDS4CPP_API PluginParticipantSecurityAttributes final
		{
			public:
			/**
			 * @brief constructor
			*/
			PluginParticipantSecurityAttributes() noexcept:
				is_rtps_encrypted{false}, is_discovery_encrypted{false}, is_liveliness_encrypted{false},
				is_rtps_origin_authenticated{false}, is_discovery_origin_authenticated{false},
				is_liveliness_origin_authenticated{false}
			{}

			/**
			 * @brief definition constructor
			 * @param  [in] mask_flag the mask info
			*/
			explicit PluginParticipantSecurityAttributes(PluginParticipantSecurityAttributesMask const mask_flag) noexcept:
				is_rtps_encrypted{(mask_flag & PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_RTPS_ENCRYPTED) != 0U},
				is_discovery_encrypted{(mask_flag & PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_BUILTIN_IS_DISCOVERY_ENCRYPTED) != 0U},
				is_liveliness_encrypted{(mask_flag & PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_LIVELINESS_ENCRYPTED) != 0U},
				is_rtps_origin_authenticated{(mask_flag & PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_RTPS_ORIGIN_AUTHENTICATED) != 0U},
				is_discovery_origin_authenticated{(mask_flag & PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_DISCOVERY_ORIGIN_AUTHENTICATED) != 0U},
				is_liveliness_origin_authenticated{(mask_flag & PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_LIVELINESS_ORIGIN_AUTHENTICATED) != 0U}
			{}


			/**
			 * @brief retrieve the contained security attributes
			 * @return PluginParticipantSecurityAttributesMask 
			 * @note no exception
			*/
			inline PluginParticipantSecurityAttributesMask mask() const noexcept
			{
				PluginParticipantSecurityAttributesMask rv { PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_VALID };
				if (is_rtps_encrypted)
				{
					rv |= PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_RTPS_ENCRYPTED;
				}
				if (is_discovery_encrypted)
				{
					rv |= PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_BUILTIN_IS_DISCOVERY_ENCRYPTED;
				}
				if (is_liveliness_encrypted)
				{
					rv |= PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_LIVELINESS_ENCRYPTED;
				}
				if (is_rtps_origin_authenticated)
				{
					rv |= PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_RTPS_ORIGIN_AUTHENTICATED;
				}
				if (is_discovery_origin_authenticated)
				{
					rv |= PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_DISCOVERY_ORIGIN_AUTHENTICATED;
				}
				if (is_liveliness_origin_authenticated)
				{
					rv |= PLUGIN_PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_LIVELINESS_ORIGIN_AUTHENTICATED;
				}
				return rv;
			}

			gbool_t is_rtps_encrypted;

			gbool_t is_discovery_encrypted;

			gbool_t is_liveliness_encrypted;

			gbool_t is_rtps_origin_authenticated;

			gbool_t is_discovery_origin_authenticated;

			gbool_t is_liveliness_origin_authenticated;
		};

		using ParticipantSecurityAttributesMask = guint32_t;

		// security(8.2.4.5)
		constexpr guint32_t PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_RTPS_PROTECTED       {(0x00000001UL << 0)};
		constexpr guint32_t PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_DISCOVERY_PROTECTED  {(0x00000001UL << 1)};
		constexpr guint32_t PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_LIVELINESS_PROTECTED {(0x00000001UL << 2)};
		constexpr guint32_t PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_VALID                {(0x00000001UL << 31)};

		/**
		 * @class ParticipantSecurityAttributes
		 * @brief this class describe how the middleware should protect the DomainParticipant
		*/
		class GS_DDS4CPP_API ParticipantSecurityAttributes final
		{
			public:
			/**
			 * @brief constructor
			*/
			ParticipantSecurityAttributes() noexcept:
				allow_unauthenticated_participants{false}, is_access_protected{true},
				is_rtps_protected{false}, is_discovery_protected{false}, is_liveliness_protected{false},
				plugin_participant_attributes{0UL}
			{}

			/**
			 * @brief Destructor
			*/
			~ParticipantSecurityAttributes() noexcept =default;

			/**
			 * @brief Copy constructor
			*/
			ParticipantSecurityAttributes(ParticipantSecurityAttributes const& part_other) noexcept =default;

			/**
			 * @brief Move constructor
			*/
			ParticipantSecurityAttributes(ParticipantSecurityAttributes &&part_other) noexcept =default;

			/**
			 * @brief Move assign operation
			*/
			ParticipantSecurityAttributes& operator=(ParticipantSecurityAttributes &&) noexcept =default;

			/**
			 * @brief assign operation
			 * @param [in] part_other compelte assign object
			 * @return ParticipantSecurityAttributes& 
			 * @note no exception
			*/
			ParticipantSecurityAttributes& operator=( ParticipantSecurityAttributes const& part_other) noexcept =default;

			/**
			 * @brief constructor with a mask
			 * @param [in] part_mask the mask information
			*/
			explicit ParticipantSecurityAttributes( ParticipantSecurityAttributesMask const part_mask) noexcept:
				allow_unauthenticated_participants{false}, is_access_protected{true},
				is_rtps_protected{(part_mask & PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_RTPS_PROTECTED) != 0U},
				is_discovery_protected{(part_mask & PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_DISCOVERY_PROTECTED) != 0U},
				is_liveliness_protected{(part_mask & PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_LIVELINESS_PROTECTED) != 0U},
				plugin_participant_attributes{0UL}
			{}




			/**
			 * @brief retrieve the contained security attributes
			 * @return ParticipantSecurityAttributesMask 
			*/
			inline ParticipantSecurityAttributesMask mask() const noexcept
			{
				ParticipantSecurityAttributesMask rv {PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_VALID};
				if (is_rtps_protected)
				{
					rv |= PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_RTPS_PROTECTED;
				}
				if (is_discovery_protected)
				{
					rv |= PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_DISCOVERY_PROTECTED;
				}
				if (is_liveliness_protected)
				{
					rv |= PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_LIVELINESS_PROTECTED;
				}
				return rv;
			}

			/**
			 * @brief match the local attributes with the remote attributes
			 * @param [in] remote_mask local attributes
			 * @param [in] remote_plugin_mask remote attributes
			 * @return gbool_t 
			 * @retval true if compatibility,otherwise return false
			*/
			inline gbool_t match( ParticipantSecurityAttributesMask const remote_mask,
			                      PluginParticipantSecurityAttributesMask const remote_plugin_mask) const noexcept
			{
				return security_mask_matches(mask(), remote_mask) &&
				       security_mask_matches(plugin_participant_attributes, remote_plugin_mask);
			}

			/**
			 * @brief check the mask matching for the intergral values
			 * @param [in] local_mask local mask
			 * @param [in] remote_mask remote mask
			 * @return gbool_t 
			 * @retval true if compatibility,otherwise return false
			 * @note no exception
			*/
			static inline gbool_t security_mask_matches( guint32_t const& local_mask,  guint32_t const& remote_mask) noexcept
			{
				if (((local_mask & (1UL << PARTICIPANT_SECURITY_OFFSET_31)) == 0U) || ((remote_mask & (1UL << PARTICIPANT_SECURITY_OFFSET_31)) == 0U))
				{
					return true;
				}

				return local_mask == remote_mask;
			}


			/**
			 * @brief check plugin-attributes validity,whichi is a extends opeation
			 * @param [in] plugin_mask the checking mask
			 * @return gbool_t 
			 * @retval true if compatibility,otherwise return false
			 * @note no exception
			*/
			inline gbool_t check_plugin_attributes( PluginParticipantSecurityAttributesMask const& plugin_mask) const noexcept
			{
				return ((this->plugin_participant_attributes & plugin_mask) != 0U);
			}

			gbool_t allow_unauthenticated_participants;

			gbool_t is_access_protected;

			gbool_t is_rtps_protected;

			gbool_t is_discovery_protected;

			gbool_t is_liveliness_protected;

			PluginParticipantSecurityAttributesMask plugin_participant_attributes;

		};


		/**
		 * @class ParticipantSecurityInfo
		 * @brief this class defined a compatible configuration which having the same value for all of the attributes,referenced to security-7.2.7
		*/
		class GS_DDS4CPP_API  ParticipantSecurityInfo final
		{
		public:
			/**
			 * @brief serialize the holderData attributes
			 * @param [in] s_cdr,the cdr woker 
			*/
			gvoid_t serialize(DdsCdr& s_cdr) const noexcept
			{
				s_cdr.serialize(participant_security_attributes);
				s_cdr.serialize(plugin_participant_security_attributes);
			}
			
			/**
			 * @brief deserialize the holderData attributes
			 * @param [in] d_cdr,the cdr woker 
			*/
			gvoid_t deserialize(DdsCdr& d_cdr) noexcept
			{
				d_cdr.deserialize(participant_security_attributes);
				d_cdr.deserialize(plugin_participant_security_attributes);
			}

			ParticipantSecurityAttributesMask participant_security_attributes;
			PluginParticipantSecurityAttributesMask plugin_participant_security_attributes;

		};

	}/*security*/
}/*gstone*/
using ParticipantSecurityInfo = gstone::security::ParticipantSecurityInfo;

#endif /*GSTONE_PARTICIPANTSECURITYINFO_H*/
