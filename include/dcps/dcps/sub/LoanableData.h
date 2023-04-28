/**************************************************************
* @file LoanableData.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_LOANABLEDATA_API_H
#define GSTONE_LOANABLEDATA_API_H 1

// #include "sub/DataReader.h"
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace sub
{
	class DataReader;
	/**
	 * @class LoanableData
	 * @brief For packaging zero-copy messages
	 */
	class GS_DDS4CPP_API LoanableData
	{
	public:
		/**
		 * @brief This function is deleted.
		 * @param [in] data Another LoanableData
		 */
		LoanableData(LoanableData const &data) = delete;
		
		/**
		 * @brief This function is deleted.
		 * @param [in] data Another LoanableData
		 */
		LoanableData(LoanableData &&data) = delete;
		
		/**
		 * @brief This function is deleted.
		 * @param [in] data Another LoanableData
		 * @return Copy of LoanableData
		 */
		LoanableData& operator=(LoanableData const &data) = delete;
		
		/**
		 * @brief This function is deleted.
		 * @param [in] data Another LoanableData
		 * @return Copy of LoanableData
		 */
		LoanableData& operator=(LoanableData &&data) = delete;
		
		/**
		 * @brief Get the loanable ptr object
		 * @return void* The pointer of loanable object
		 */
		void* get_loanable_ptr() const noexcept
		{
			return m_ptr;
		}
		
		/**
		 * @brief Set the loanable ptr object
		 * @param [in] ptr_t The pointer of loanable object
		 */
		void set_loanable_ptr(void* const ptr_t) noexcept
		{
			this->m_ptr = ptr_t;
		}
		
		/**
		 * @brief Get the user data ptr object
		 * @return void* the user data ptr
		 */
		virtual void* get_user_data_ptr() noexcept
		{
			return nullptr;
		}
	protected:
		/**
		 * @brief Construct a new Loanable Data object
		 */
		LoanableData() = default;
		
		/**
		 * @brief Destroy the Loanable Data object
		 */
		~LoanableData() noexcept
		{
			m_ptr = nullptr;
		}

	private:
		void* m_ptr{ nullptr };
	};
} /* sub */
} /* dds */

__GS_DDS4CPP_END_DECLS


#endif