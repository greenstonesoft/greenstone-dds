/**************************************************************
* @file LoanableTypeData.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_LOANABLETYPEDATA_API_H
#define GSTONE_LOANABLETYPEDATA_API_H 1

#include "dcps/sub/LoanableData.h"
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace sub
{
	/**
	 * @class LoanableTypeData
	 * @brief zero_copy data type
	 */
	template<typename T>
	class GS_DDS4CPP_API LoanableTypeData : public LoanableData
	{
	public:
		/**
		 * @brief Construct a new Loanable Type Data object
		 */
		LoanableTypeData() = default;
		
		/**
		 * @brief This function is deleted.
		 * @param [in] data Another LoanableTypeData
		 */
		LoanableTypeData(LoanableTypeData const &data) = delete;
		
		/**
		 * @brief This function is deleted.
		 * @param [in] data Another LoanableTypeData
		 */
		LoanableTypeData(LoanableTypeData &&data) = delete;
		
		/**
		 * @brief This function is deleted.
		 * @param [in] data Another LoanableTypeData
		 * @return Copy of LoanableTypeData
		 */
		LoanableTypeData& operator=(LoanableTypeData const &data) = delete;
		
		/**
		 * @brief This function is deleted.
		 * @param [in] data Another LoanableTypeData
		 * @return Copy of LoanableTypeData
		 */
		LoanableTypeData& operator=(LoanableTypeData &&data) = delete;
		
		/**
		 * @brief Destroy the Loanable Type Data object
		 */
		~LoanableTypeData() noexcept
		{
			if (m_userData != nullptr)
			{
				delete m_userData;
				m_userData = nullptr;
			}
		}
		
		/**
		 * @brief get user data in user type
		 * @return T& The reference of user data
		 */
		T& to_user_type()
		{
			return *static_cast<T*>(get_loanable_ptr());
		}
		
		/**
		 * @brief get user data in user type
		 * @return T& The const reference of user data
		 */
		T const& to_user_type() const
		{
			return *static_cast<const T*>(get_loanable_ptr());
		}

	protected:
		/**
		 * @brief Get the user data ptr object
		 * @return void* The void type pointer of user data
		 */
		void* get_user_data_ptr() noexcept override
		{
			if (m_userData == nullptr)
			{
				m_userData = new T;
			}
			set_loanable_ptr(reinterpret_cast<void*>(m_userData));
			return get_loanable_ptr();
		}

	private:
		T* m_userData{ nullptr };
	};

} /* sub */
} /* dds */

__GS_DDS4CPP_END_DECLS

#endif /* GSTONE_LOANABLETYPEDATA_API_H */
