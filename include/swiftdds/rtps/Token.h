/**************************************************************
 * @file Token.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_SECURITY_TOKEN_H
#define GSTONE_SECURITY_TOKEN_H 1

#include "swiftdds/rtps/Property.h"
#include "swiftdds/rtps/BinaryProperty.h"
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

		/**
		 * @class DataHolder
		 * @brief DataHolder uesed to hold generic data,reference to @security-7.2.3
		*/
		class GS_DDS4CPP_API DataHolder
		{
		public:
			/**
			 * @brief constructor
			*/
			DataHolder() = default;

			/**
			 * @brief constructor
			 * @param [in] the_class_id,the speficied class id
			*/
			DataHolder( gstring_t const& the_class_id);

			/**
			 * @brief default copy constructor
			 * @param [in] other,other complete object
			*/
			DataHolder(DataHolder const &other) = default;

			/**
			 * @brief move copy constructor
			 * @param [in] other,other complete object
			*/
			DataHolder(DataHolder &&other) = default;

			/**
			 * @brief destructor
			*/
			virtual ~DataHolder() noexcept = default;

			/**
			 * @brief default assign function
			 * @param [in] other,the assigned object 
			 * @return DataHolder& 
			*/
			DataHolder& operator=(DataHolder const &other) = default;

			/**
			 * @brief move assign function
			 * @param [in] other,the assigned object 
			 * @return DataHolder& 
			*/
			DataHolder& operator=(DataHolder &&other) = default;

			/**
			 * @brief check is empty object
			 * @return gbool_t 
			 * @retval true is empty object
			 * @retval false if not empty obejct
			*/
			gbool_t is_nil() const noexcept
			{
				return ((this->m_class_id.empty()) && (this->m_properties.empty()) && (this->m_binary_properties.empty()));
			}

			/**
			 * @brief  get the class id information
			 * @return gstring_t const& 
			*/
			gstring_t const & class_id() const noexcept
			{
				return this->m_class_id;
			}

			/**
			 * @brief Set the class id object
			 * @param the_class_id 
			*/
			gvoid_t set_class_id(gstring_t const & the_class_id) noexcept
			{
				this->m_class_id = the_class_id;
			}

			/**
			 * @brief add property to the object
			 * @param [in] pro,the adding property informaton
			*/
			gvoid_t add_property(Property const & pro) noexcept
			{
				m_properties.emplace_back(pro);
			}
			
			/**
			 * @brief add property with auxiliary information
			 * @param [in] p_name,the property name
			 * @param [in] p_value,the property value
			 * @param [in] p_propagate,appoint transport flag,true for transport with the network
			*/
			gvoid_t add_property(gstring_t const &p_name,  gstring_t const &p_value , gbool_t const p_propagate) noexcept
			{
				m_properties.emplace_back(p_name,p_value,p_propagate);
			}

			/**
			 * @brief add property with auxiliary information
			 * @param [in] p_name,the property name
			 * @param [in] p_data,the property data
			 * @param [in] p_len,the data length
			 * @param [in] p_propagate,appoint transport flag,true for transport with the network
			*/
			gvoid_t add_property(gstring_t const &p_name,  guint8_t const*p_data, gint32_t const &p_len,gbool_t const p_propagate = true) noexcept
			{
				m_properties.emplace_back(p_name,p_data,p_len,p_propagate);
			}

			/**
			 * @brief get the cached property information
			 * @return PropertySeq 
			*/
			PropertySeq const & properties() const noexcept
			{
				return m_properties;
			}

			/**
			 * @brief add binary property with auxiliary information
			 * @param [in] p_name,the property name
			 * @param [in] p_data,the property data
			 * @param [in] p_propagate,appoint transport flag,true for transport with the network
			*/
			gvoid_t add_binary_property(gstring_t const &p_name, gstring_t const &p_data, gbool_t const p_propagate = true)
			{
				m_binary_properties.emplace_back(p_name,p_data,p_propagate);
			}

			/**
			 * @brief add binary property with auxiliary information
			 * @param [in] p_name,the property name
			 * @param [in] p_data,the property data
			 * @param [in] p_len,the data length
			 * @param [in] p_propagate,appoint transport flag,true for transport with the network
			*/
			gvoid_t add_binary_property(gstring_t const &p_name,  guint8_t const*p_data, gint32_t const &p_len,
                   gbool_t const p_propagate = true)
			{
				m_binary_properties.emplace_back(p_name,p_data,p_len,p_propagate);
			}

			/**
			 * @brief add binary property with auxiliary information
			 * @param [in] p_name,the property name
			 * @param [in] p_data,the property data
			 * @param [in] p_propagate,appoint transport flag,true for transport with the network
			*/
			gvoid_t add_binary_property(gstring_t const &p_name, std::vector<guint8_t> const &p_data, gbool_t const p_propagate = true)
			{
				m_binary_properties.emplace_back(p_name,p_data,p_propagate);
			}

			/**
			 * @brief add binary property with auxiliary information
			 * @param [in] p_name,the property name
			 * @param [in] p_data,the property data
			 * @param [in] p_len,the data length
			 * @param [in] p_propagate,appoint transport flag,true for transport with the network
			*/
			gvoid_t add_binary_property(gstring_t const &p_name,  gchar_t const * p_data, gint32_t const &p_len,
                   gbool_t const p_propagate = true)
			{
				m_binary_properties.emplace_back(p_name,p_data,p_len,p_propagate);
			}

			/**
			 * @brief add binary property with auxiliary information
			 * @param [in] pro,the adding property information
			*/
			gvoid_t add_binary_property(BinaryProperty const & pro)
			{
				m_binary_properties.emplace_back(pro);
			}

			/**
			 * @brief get the binary property information
			 * @return BinaryPropertySeq const& 
			*/
			BinaryPropertySeq const & binary_properties() const noexcept
			{
				return m_binary_properties;
			}

			//@extends
			/**
			 * @brief serialize the holderData attributes
			 * @param [in] s_cdr,the cdr woker 
			*/
			virtual gvoid_t serialize(DdsCdr& s_cdr) const noexcept;
			
			/**
			 * @brief deserialize the holderData attributes
			 * @param [in] d_cdr,the cdr woker 
			*/
			virtual gvoid_t deserialize(DdsCdr& d_cdr) noexcept;

		private:
			//attributes
			gstring_t m_class_id{""};
			PropertySeq m_properties{};
			BinaryPropertySeq m_binary_properties{};			
		};


		//security-7.2.4
		///The Token class is structurally identical to the DataHolder class and therefore has the SAME structure for tall plugin implementations.
		///However,the contents and interpretation of the Token objects shall be specified by each plugin implementation.

		using DataHolderSeq = std::vector<DataHolder> ;
		using Token = DataHolder ;
		using MessageToken = Token ;
		//@security-9.3.2.4,which contains future_challenge
		using AuthRequestMessageToken = MessageToken ;
		using HandshakeMessageToken = MessageToken ;
		//@security-9.3.2.1,IdentityToken for builtin Authentication plugin,
		//which contains dds.cert.sn,dds.cert.algo,dds.ca.sn.dds.ca.algo
		using IdentityToken = Token ;
		//@security-9.3.2.2,which contains ocsp_status
		using IdentityStatusToken =Token ;
		//@security-9.3.2.3,which contains dds.perm_ca.sn,dds.perm_ca.algo
		using PermissionsToken = Token ;
		//@security-9.3.2.3,which contains c.id,c.perm
		using AuthenticatedPeerCredentialToken = Token ;
		using PermissionsCredentialToken = Token ;

		//using IdentityToken_ptr =  IdentityToken* ;
		//using IdentityStatusToken_ptr =  IdentityStatusToken* ;
		using PermissionsToken_ptr = PermissionsToken* ;
		using PermissionsCredentialToken_ptr = PermissionsCredentialToken* ;
		//using HandshakeMessageToken_ptr = HandshakeMessageToken* ;
		//using AuthenticatedPeerCredentialToken_ptr = AuthenticatedPeerCredentialToken* ;

		using CryptoToken = Token ;
		using ParticipantCryptoToken = Token ;
		using DatawriterCryptoToken = Token ;
		using DatareaderCryptoToken = Token ;
		using HandshakeMessageTokenSeq = std::vector<HandshakeMessageToken> ;
		using CryptoTokenSeq = std::vector<CryptoToken> ;
		using ParticipantCryptoTokenSeq = CryptoTokenSeq ;
		using DatawriterCryptoTokenSeq = CryptoTokenSeq ;
		using DatareaderCryptoTokenSeq = CryptoTokenSeq ;

	}/*security*/
}/*gstone*/

//define the token
//using IdentityToken = gstone::security::IdentityToken ;
//using PermissionsToken = gstone::security::PermissionsToken ;

#endif /*GSTONE_RTPS_TOKEN_H*/
