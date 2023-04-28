/**************************************************************
 * @file SecBuiltinEndpoint.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
 **************************************************************/
#ifndef GSTONE_ENDPOINTSECURITYINFO_H
#define GSTONE_ENDPOINTSECURITYINFO_H 1

#include "dcps/PITypes.h"


namespace gstone
{
	namespace security
	{

		using PluginEndpointSecurityAttributesMask = guint32_t;

		constexpr guint32_t PLUGIN_ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_SUBMESSAGE_ENCRYPTED            {(0x00000001UL << 0)};
		constexpr guint32_t PLUGIN_ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_PAYLOAD_ENCRYPTED               {(0x00000001UL << 1)};
		constexpr guint32_t PLUGIN_ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_SUBMESSAGE_ORIGIN_AUTHENTICATED {(0x00000001UL << 2)};
		constexpr guint32_t PLUGIN_ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_VALID                           {(0x00000001UL << 31)};

		constexpr guint32_t PLUGIN_ENDPOINT_SECURITY_ATTRIBUTES_MASK_DEFAULT {PLUGIN_ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_VALID};
// #define ENDPOINT_SECURITY_INFO_DEFAULT_ATTRIBUTES {0,0}

		/**
		 * @class PluginEndpointSecurityAttributes
		 * @brief define the plugin-endpointer security attributes
		 * @note this class referenced to security
		*/
		class PluginEndpointSecurityAttributes final
		{
			public:
			/**
			 * @brief constructor
			*/
			PluginEndpointSecurityAttributes() noexcept:
				m_is_submessage_encrypted{false}, m_is_submessage_origin_authenticated{false}, m_is_payload_encrypted{false}
			{ }

			/**
			 * @brief construct with attributes mask
			 * @param [in] plugin_mask the attributes mask
			*/
			explicit PluginEndpointSecurityAttributes( PluginEndpointSecurityAttributesMask const plugin_mask) noexcept:
				m_is_submessage_encrypted{(plugin_mask & PLUGIN_ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_SUBMESSAGE_ENCRYPTED) != 0U},
				m_is_submessage_origin_authenticated{(plugin_mask & PLUGIN_ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_SUBMESSAGE_ORIGIN_AUTHENTICATED) != 0U},
				m_is_payload_encrypted{(plugin_mask & PLUGIN_ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_PAYLOAD_ENCRYPTED) != 0U}
			{
			}

			/**
			 * @brief set the submessage encrypt flag
			 * @param [in] flag the encrypt flag
			 * @note no exception
			*/
			inline gvoid_t is_submessage_encrypted(gbool_t const flag) noexcept
			{
				m_is_submessage_encrypted = flag;
			}

			/**
			 * @brief retrieve the submessage encrypt flag
			 * @return gbool_t 
			 * @retval true if encrpted,otherwise false
			 * @note no exception
			*/
			inline gbool_t is_submessage_encrypted() const noexcept
			{
				return m_is_submessage_encrypted;
			}

			/**
			 * @brief set the submessage origin authentication flag
			 * @param [in] flag the authentication flag
			 * @note no exception
			*/
			inline gvoid_t is_submessage_origin_authenticated(gbool_t const flag) noexcept
			{
				m_is_submessage_origin_authenticated = flag;
			}

			/**
			 * @brief retrieve the submessage authentication flag
			 * @return gbool_t 
			 * @retval true if authentication,otherwise false
			 * @note no exception
			*/
			inline gbool_t is_submessage_origin_authenticated() const noexcept
			{
				return m_is_submessage_origin_authenticated;
			}

			/**
			 * @brief set the payload encrypt flag
			 * @param [in] flag the encrypt flag
			 * @note no exception
			*/
			inline gvoid_t is_payload_encrypted(gbool_t const flag) noexcept
			{
				m_is_payload_encrypted = flag;
			}

			/**
			 * @brief retrieve the payload encrypt flag
			 * @return gbool_t 
			 * @retval true if encrpted,otherwise false
			 * @note no exception
			*/
			inline gbool_t is_payload_encrypted() const noexcept
			{
				return m_is_payload_encrypted;
			}

			/**
			 * @brief retrieve the contained security mask
			 * @return PluginEndpointSecurityAttributesMask 
			*/
			inline PluginEndpointSecurityAttributesMask mask() const noexcept
			{
				PluginEndpointSecurityAttributesMask rv { PLUGIN_ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_VALID };
				if (m_is_submessage_encrypted)
				{
					rv |= PLUGIN_ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_SUBMESSAGE_ENCRYPTED;
				}
				if (m_is_submessage_origin_authenticated)
				{
					rv |= PLUGIN_ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_SUBMESSAGE_ORIGIN_AUTHENTICATED;
				}
				if (m_is_payload_encrypted)
				{
					rv |= PLUGIN_ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_PAYLOAD_ENCRYPTED;
				}
				return rv;
			}

			private:
			gbool_t m_is_submessage_encrypted;
			gbool_t m_is_submessage_origin_authenticated;
			gbool_t m_is_payload_encrypted;
		};

		typedef PluginEndpointSecurityAttributes* PluginEndpointSecurityAttributes_ptr;

		using EndpointSecurityAttributesMask = guint32_t;

		constexpr guint32_t ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_READ_PROTECTED       {(0x00000001UL << 0)};
		constexpr guint32_t ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_WRITE_PROTECTED      {(0x00000001UL << 1)};
		constexpr guint32_t ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_DISCOVERY_PROTECTED  {(0x00000001UL << 2)};
		constexpr guint32_t ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_SUBMESSAGE_PROTECTED {(0x00000001UL << 3)};
		constexpr guint32_t ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_PAYLOAD_PROTECTED    {(0x00000001UL << 4)};
		constexpr guint32_t ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_KEY_PROTECTED        {(0x00000001UL << 5)};
		constexpr guint32_t ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_LIVELINESS_PROTECTED {(0x00000001UL << 6)};
		constexpr guint32_t ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_VALID                {(0x00000001UL << 31)};

		/**
		 * @class EndpointSecurityAttributes
		 * @brief this class describe how the middleware shall protect the Entity
		*/
		class EndpointSecurityAttributes final
		{
			public:
			/**
			 * @brief constructor
			*/
			EndpointSecurityAttributes() noexcept:
				is_read_protected{false}, is_write_protected{false},
				is_discovery_protected{false}, is_liveliness_protected{false},
				is_submessage_protected{false}, is_payload_protected{false}, is_key_protected{false},
				plugin_endpoint_attributes{0UL}
			{}

			/**
			 * @brief constructor with a new mask
			 * @param [in] enpoint_mask the seucrity attributes mask
			*/
			explicit EndpointSecurityAttributes( EndpointSecurityAttributesMask const enpoint_mask) noexcept:
				is_read_protected{(enpoint_mask & ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_READ_PROTECTED) != 0},
				is_write_protected{(enpoint_mask & ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_WRITE_PROTECTED) != 0},
				is_discovery_protected{(enpoint_mask & ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_DISCOVERY_PROTECTED) != 0},
				is_liveliness_protected{(enpoint_mask & ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_LIVELINESS_PROTECTED) != 0},
				is_submessage_protected{(enpoint_mask & ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_SUBMESSAGE_PROTECTED) != 0},
				is_payload_protected{(enpoint_mask & ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_PAYLOAD_PROTECTED) != 0},
				is_key_protected{(enpoint_mask & ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_KEY_PROTECTED) != 0},
				plugin_endpoint_attributes{0UL}
			{}



			//PropertySeq ac_endpoint_properties
			/**
			 * @brief retrieve the contained mask information
			 * @return EndpointSecurityAttributesMask 
			 * @note no exception
			*/
			inline EndpointSecurityAttributesMask mask() const noexcept
			{
				EndpointSecurityAttributesMask rv { ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_VALID };
				if (is_read_protected)
				{
					rv |= ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_READ_PROTECTED;
				}
				if (is_write_protected)
				{
					rv |= ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_WRITE_PROTECTED;
				}
				if (is_discovery_protected)
				{
					rv |= ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_DISCOVERY_PROTECTED;
				}
				if (is_liveliness_protected)
				{
					rv |= ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_LIVELINESS_PROTECTED;
				}
				if (is_submessage_protected)
				{
					rv |= ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_SUBMESSAGE_PROTECTED;
				}
				if (is_payload_protected)
				{
					rv |= ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_PAYLOAD_PROTECTED;
				}
				if (is_key_protected)
				{
					rv |= ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_KEY_PROTECTED;
				}
				return rv;
			}

			/**
			 * @brief check the remote endpoint attributes has a compatibility with the plugin or not
			 * @param [in] remote_mask the remote endpointer attributes
			 * @param [in] remote_plugin_mask the remote plugin attributes
			 * @return gbool_t 
			 * @retval true if has compatibility,otherwise false 
			 * @note no exception
			*/
			inline gbool_t match( EndpointSecurityAttributesMask const remote_mask,
			                      PluginEndpointSecurityAttributesMask const remote_plugin_mask) const
			{
				return security_mask_matches(mask(), remote_mask) &&
				       security_mask_matches(plugin_endpoint_attributes, remote_plugin_mask);
			}

			/**
			 * @brief check the mask matching for the intergral values
			 * @param [in] local_mask the local mask
			 * @param [in] remote_mask the remote mask
			 * @return gbool_t 
			 * @retval true if mathed,otherwise false 
			 * @note no exception
			*/
			inline gbool_t security_mask_matches( guint32_t const& local_mask,  guint32_t const& remote_mask)const
			{
				if (((local_mask & (1UL << 31)) == 0) || ((remote_mask & (1UL << 31)) == 0))
				{
					return true;
				}

				return local_mask == remote_mask;
			}

			/**
			 * @brief check the plugin attributes have a compatibility or not
			 * @param [in] attri the plugin attributes
			 * @return gbool_t 
			 * @retval true if compatible,otherwise false 
			*/
			inline gbool_t check_plugin_attributes( PluginEndpointSecurityAttributesMask const& attri) const
			{
				return ((attri & this->plugin_endpoint_attributes) != 0);
			}

			public:

			gbool_t is_read_protected;

			gbool_t is_write_protected;

			gbool_t is_discovery_protected;

			gbool_t is_liveliness_protected;

			gbool_t is_submessage_protected;

			gbool_t is_payload_protected;

			gbool_t is_key_protected;

			PluginEndpointSecurityAttributesMask plugin_endpoint_attributes;
		};

		typedef EndpointSecurityAttributes* EndpointSecurityAttributes_ptr;


		/**
		 * @class EndpointSecurityInfo
		 * @brief define the combined endpoint security info
		*/
		struct EndpointSecurityInfo
		{
			public:
			EndpointSecurityAttributesMask endpoint_security_attributes;
			PluginEndpointSecurityAttributesMask plugin_endpoint_security_attributes;
		};

		using EndpointSecurityInfo_t = EndpointSecurityInfo;

	}/*security*/
}/*gstone*/

#endif /*GSTONE_RTPS_ENDPOINTSECURITYINFO_H*/
