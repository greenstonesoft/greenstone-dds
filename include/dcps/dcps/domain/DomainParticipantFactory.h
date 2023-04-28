/**************************************************************
* @file DomainParticipantFactory.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#ifndef GSTONE_DOMAINPARTICIPANTFACTORY_API_H
#define GSTONE_DOMAINPARTICIPANTFACTORY_API_H 1

#include "dcps/core/CoreTypes.h"
#include "dcps/domain/DomainParticipant.h"
#include "dcps/domain/DomainParticipantListener.h"
#include "dcps/domain/DomainParticipantQos.h"
#include "dcps/domain/DomainParticipantFactoryQos.h"
#include <thread>
#include <vector>
#include <mutex>
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds {
	namespace domain {
		class DomainParticipantFactoryDelegate;
	}/*pub*/
}/*gstone*/

namespace dds
{
namespace domain
{
	/**
	* @class DomainParticipantFactory
	* @brief Factory for allowing creation and destruction of DDSDomainParticipant objects.
	*/
	class GS_DDS4CPP_API DomainParticipantFactory final
	{
	public:
		/**
		* @brief This function returns the DomainParticipantFactory singleton.
		* @return Return the singleton DomainParticipantFactory instance.
		*/
		static DomainParticipantFactory* get_instance() noexcept;
		
		/**
		* @brief This function creates a new DomainParticipant object.
		* @param [in] a_domain_id DomainId.
		* @return A Pointer of the created DomainParticipant object or nullptr.
		* @retval nullptr if get_unicastlocatorlist(a_qos) returns false, it returns nullptr.
		* If the DomainParticipant fails to enable when autoenable_created_entities is set, it returns nullptr. 
		*/
		DomainParticipant *create_participant(DDS::DomainId_t const a_domain_id) noexcept;
		
		/**
		* @brief This function creates a new DomainParticipant object.
		* @param [in] a_domain_id DomainId.
		* @param [in] a_qos Reference of DomainParticipantQos.
		* @param [in] a_listener A Pointer of DomainParticipantListener,
		* @param [in] a_mask Communication status mask.
		* @return A Pointer of the created DomainParticipant object or nullptr.
		* @retval nullptr if get_unicastlocatorlist(a_qos) returns false, it returns nullptr.
		* If the DomainParticipant fails to enable when autoenable_created_entities is set, it returns nullptr.
		*/
		DomainParticipant *create_participant(DDS::DomainId_t const a_domain_id,
			DomainParticipantQos &a_qos,
			DomainParticipantListener* const a_listener,
			DDS::StatusMask const a_mask) noexcept;
		
		/**
		* @brief This function deletes an existing DomainParticipant.
		* @param [in] a_domain_participant Const pointer of DomainParticipant.
		* @return return DDS::ReturnCode_t.
		* @retval RETCODE_PRECONDITION_NOT_MET If a_domain_participant is nullptr or a entity created by this DomainParticipant 
		* exists, it returns RETCODE_PRECONDITION_NOT_MET.
		* @retval RETCODE_OK It is successful to delete participant.
		*/
		DDS::ReturnCode_t delete_participant(DomainParticipant const *const a_domain_participant) noexcept;
		
		/**
		* @brief This function retrieves a previously created DomainParticipant belonging to specified domain_id.
		* @param [in] a_domain_id DomainId.
		* @return A Pointer of a previously created DomainParticipant object or nullptr.
		* @retval nullptr If it does not find participant has 'a_domain_id', it returns nullptr.
		*/
		DomainParticipant *lookup_participant(DDS::DomainId_t const a_domain_id) noexcept;
		
		/**
		* @brief This function sets the default DomainParticipantQos.
		* @details The DomainParticipantQos which will be used for newly created DomainParticipant entities 
		* in the case where the QoS policies are defaulted in the create_participant operation.
		* @param [in] a_qos Const reference of a DomainParticipantQos object.
		* @return Return DDS::ReturnCode_t.
		* @retval RETCODE_ERROR  If a_qos is nullptr, it will return RETCODE_ERROR.
		* @retval RETCODE_OK It is successful to set default participant qos.
		* @retval RETCODE_INCONSISTENT_POLICY If entity was enabled, it will can't update qos and return RETCODE_INCONSISTENT_POLICY.
		*/
		DDS::ReturnCode_t set_default_participant_qos(DomainParticipantQos const& a_qos) noexcept;
		
		/**
		* @brief This function retrieves the default value of the DomainParticipant QoS.
		* @param [in,out] a_qos Reference of a DomainParticipantQos object.
		* @return Return DDS::ReturnCode_t.
		* @retval RETCODE_ERROR If a_qos is nullptr, it will return RETCODE_ERROR.
		* @retval RETCODE_OK It is successful to get default participant qos.
		*/
		DDS::ReturnCode_t get_default_participant_qos(DomainParticipantQos &a_qos) noexcept;
		
		/**
		* @brief This function sets DomainParticipantFactoryQos of the DomainParticipantFactory.
		* @param [in] a_qos Const reference of a DomainParticipantFactoryQos object.
		* @return Return DDS::ReturnCode_t.
		* @retval RETCODE_ERROR If a_qos is nullptr, it will return RETCODE_ERROR.
		* @retval RETCODE_OK It is successful to set qos.
		*/
		DDS::ReturnCode_t set_qos(DomainParticipantFactoryQos const &a_qos) noexcept;
		
		/**
		* @brief This function retrieves DomainParticipantFactoryQos of the DomainParticipantFactory.
		* @param [in,out] a_qos Reference of a DomainParticipantFactoryQos object.
		* @return Return DDS::ReturnCode_t
		* @retval RETCODE_ERROR If a_qos is nullptr, it will return RETCODE_ERROR.
		* @retval RETCODE_OK It is successful to get qos.
		*/
		DDS::ReturnCode_t get_qos(DomainParticipantFactoryQos &a_qos) noexcept;
	protected:
		/**
		* @brief Destructor of the class DomainParticipantFactory.
		*/
		~DomainParticipantFactory() = default;
	private:
		/**
		* @brief Don't use constructor of the class DomainParticipantFactory by another DomainParticipantFactory object.
		* @param [in] a_info Const reference of a DomainParticipantFactory object.
		*/
		DomainParticipantFactory( DomainParticipantFactory const & a_info) = delete;
		
		/**
		* @brief Don't use assign a DomainParticipantFactory object to the locally DomainParticipantFactory object.
		* @param [in] a_info Const reference of a DomainParticipantFactory object.
		* @return Reference of the locally DomainParticipantFactory object.
		*/
		DomainParticipantFactory& operator=( DomainParticipantFactory const& a_info) = delete;
		
		/**
		* @brief Don't use move constructor of the class DomainParticipantFactory.
		* @param [in] a_info Rvalue reference of a DomainParticipantFactory object.
		*/
		DomainParticipantFactory( DomainParticipantFactory && a_info) = delete;
		
		/**
		* @brief Don't use move assignment of the class DomainParticipantFactory.
		* @param [in] a_info Rvalue reference of this DomainParticipantFactory object.
		* @return Reference of this DomainParticipantFactory object.
		*/
		DomainParticipantFactory &operator=(DomainParticipantFactory &&a_info) = delete;
		
		/**
		* @brief Don't use Constructor of the class DomainParticipantFactory.
		*/
		DomainParticipantFactory();
		
		DomainParticipantFactoryDelegate* m_delegate;
	};
}/*domain*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif//__GSTONE_DOMAINPARTICIPANTFACTORY_API_H