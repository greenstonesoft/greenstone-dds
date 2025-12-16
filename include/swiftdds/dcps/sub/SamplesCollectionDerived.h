/**************************************************************
* @file SamplesCollectionDerived.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_SAMPLES_COLLECTION_DERIVED_API_H
#define GSTONE_SAMPLES_COLLECTION_DERIVED_API_H 1

#include <memory>

#include "swiftdds/dcps/DeclExport.h"

#include "swiftdds/dcps/sub/SamplesCollectionBase.h"
#include "swiftdds/dcps/sub/LoanableTypeData.h"

namespace dds
{
namespace sub
{
    /**
     * @class SamplesCollectionDerived
     * @brief The Packaging of message
     */
    template<typename T>
    class SamplesCollectionDerived : public SamplesCollectionBase
    {
    public:
        typedef std::shared_ptr<LoanableTypeData<T>> data_ptr;

        /**
         * @brief Construct a new Samples Collection Derived object
         */
        SamplesCollectionDerived();
        
        /**
         * @brief Destroy the Samples Collection Derived object
         */
        ~SamplesCollectionDerived();

        /**
         * @brief allocate memory
         * @param [in] mem_size The size of sample
         */
        inline void allocate_memory(size_t mem_size) noexcept override;
        
        /**
         * @brief Get the data by index
         * @param [in] mem_index The index of data
         * @return T& The data found by index
         */
       
        T& get_data_by_index(size_t mem_index);
        /**
         * @brief Get the data by index
         * @param [in] mem_index The index of data
         * @return T& The data found by index
         */
        
        T& operator[] (size_t mem_index);
        /**
         * @brief clear resource
         */
        
        inline void clear_resource() noexcept override
        {
            get_data_vec().clear();
            m_loanableTypeDataVec.clear();
        }
    private:
        std::vector<data_ptr> m_loanableTypeDataVec;
    };


template<typename T> 
SamplesCollectionDerived<T>::SamplesCollectionDerived()
{
    m_loanableTypeDataVec.clear();
}

template<typename T> 
SamplesCollectionDerived<T>::~SamplesCollectionDerived()
{
}

template<typename T> 
void SamplesCollectionDerived<T>::allocate_memory(size_t sample_count) noexcept
{
    this->set_data_count(sample_count);
    size_t index = 0;
    while (index != sample_count)
    {
        std::shared_ptr<LoanableTypeData<T>> loanabledata_ptr = std::make_shared<LoanableTypeData<T>>();
        m_loanableTypeDataVec.push_back(loanabledata_ptr);
        LoanableData* data_ptr = (LoanableData*)(m_loanableTypeDataVec[index].get());
        get_data_vec().push_back(data_ptr);
        ++index;
    }
}

template<typename T> 
T &SamplesCollectionDerived<T>::get_data_by_index(size_t index)
{
    if (this->get_data_count() > 0 && index >= 0 && index < this->get_data_count())
    {
        return ((m_loanableTypeDataVec[index])->to_user_type());
    }
    else
    {
        std::shared_ptr<LoanableTypeData<T>> loanabledata_ptr = std::make_shared<LoanableTypeData<T>>();
        return loanabledata_ptr->to_user_type();
    }
}

template<typename T> 
T &SamplesCollectionDerived<T>::operator[](size_t index)
{
    return this->get_data_by_index(index);
}

} /* sub */
} /* dds */

#endif /* GSTONE_SAMPLES_COLLECTION_DERIVED_API_H */
