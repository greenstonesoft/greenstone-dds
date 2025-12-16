/**************************************************************
* @file LoanableTypeData.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_LOANABLETYPEDATA_API_H
#define GSTONE_LOANABLETYPEDATA_API_H 1

#include "swiftdds/dcps/sub/LoanableData.h"
#include "swiftdds/dcps/DeclExport.h"

#include <functional>

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
	class LoanableTypeData : public LoanableData
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
		virtual ~LoanableTypeData() noexcept = default;
		
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


		/**
		 * @brief set memory proc func
		 * @param [in] alloc_func alloc func
		 * @param [in] dealloc_func dealloc func
		 */
		inline gvoid_t set_memory_func(std::function<gvoid_t*()> const& alloc_func, std::function<gvoid_t(gvoid_t*)> const& dealloc_func) noexcept
		{
			if((alloc_func != nullptr) && (dealloc_func != nullptr))
			{
				m_allocFunc = alloc_func;
				m_deallocFunc = dealloc_func;
			}
		}

		/**
		 * @brief release memory func
		 */
		gvoid_t return_loan() noexcept override
		{
			gvoid_t *ptr = m_userData;
			if(ptr == nullptr)
			{
				ptr = get_loanable_ptr();
			}
			if(ptr != nullptr)
			{
				if((m_allocFunc != nullptr) && (m_deallocFunc != nullptr))
				{
					m_deallocFunc(ptr);
				}
				else
				{
					delete ptr;
				}
				m_userData = nullptr;
				set_loanable_ptr(nullptr);
			}
		}

	protected:
		/**
		 * @brief Get the user data ptr object
		 * @return gvoid_t* The void type pointer of user data
		 */
		gvoid_t* get_user_data_ptr() noexcept override
		{
			if (m_userData == nullptr)
			{
				if(m_allocFunc != nullptr)
				{
					m_userData = static_cast<T*>(m_allocFunc());
				}
				else
				{
					m_userData = new T;
				}
			}
			set_loanable_ptr(reinterpret_cast<void*>(m_userData));
			return get_loanable_ptr();
		}

	private:
		T* m_userData{ nullptr };
		std::function<gvoid_t*()> m_allocFunc{nullptr};
		std::function<gvoid_t(gvoid_t*)> m_deallocFunc{nullptr};
	};

} /* sub */
} /* dds */

__GS_DDS4CPP_END_DECLS

#endif /* GSTONE_LOANABLETYPEDATA_API_H */
