/**************************************************************
* @file SamplesCollectionBase.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_SAMPLES_COLLECTION_BASE_API_H
#define GSTONE_SAMPLES_COLLECTION_BASE_API_H 1

#include <vector>

#include "swiftdds/dcps/DdsBaseTypes.h"
#include "swiftdds/dcps/DeclExport.h"
#include "swiftdds/dcps/sub/LoanableData.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace sub
{
    /**
     * @class SamplesCollectionBase
     * @brief Base class for SamplesCollectionDerived
     */
    class GS_DDS4CPP_API SamplesCollectionBase
    {
    public:
        /**
         * @brief Construct a new Samples Collection Base object
         */
        SamplesCollectionBase() noexcept    
        { 
            m_loanableDataVec.clear(); 
        }
        
        /**
         * @brief Destroy the Samples Collection Base object
         */
        virtual ~SamplesCollectionBase() = default;

        /**
         * @brief Conpy-Construct a new Samples Collection Base object
         * @param [in] other Another SamplesCollectionBase
         */
        SamplesCollectionBase(SamplesCollectionBase const& other) = default;
        
        /**
         * @brief Move-Construct a new Samples Collection Base object
         * @param [in] other Another SamplesCollectionBase
         */
        SamplesCollectionBase(SamplesCollectionBase&& other) = default;
        
        /**
         * @brief Assign a SamplesCollectionBase object to the locally SamplesCollectionBase object.
         * @param [in] other. reference of a SamplesCollectionBase object.
         * @return Reference of the locally SamplesCollectionBase object.
         */
        SamplesCollectionBase& operator=(SamplesCollectionBase const& other) = default;
        
        /**
         * @brief Assign a SamplesCollectionBase object to the locally SamplesCollectionBase object.
         * @param [in] other. reference of a SamplesCollectionBase object.
         * @return Reference of the locally SamplesCollectionBase object.
         */
        SamplesCollectionBase& operator=(SamplesCollectionBase&& other) = default;
        
        /**
         * @brief Get the data count
         * @return guint32_t The size of data 
         */
        virtual guint32_t const get_data_count() const noexcept
        {
            return static_cast<guint32_t>(this->m_dataAmount);
        }
        
        /**
         * @brief Set the data count
         * @param [in] data_amount_t The size of data
         */
        virtual void set_data_count(size_t data_amount_t) noexcept
        {
            this->m_dataAmount = data_amount_t;
        }
        
        /**
         * @brief Get the data vector
         * @return std::vector<LoanableData*>& the data vector
         */
        virtual std::vector<LoanableData*>& get_data_vec() noexcept
        {
            return m_loanableDataVec;
        }
        
        /**
         * @brief allocate memory
         * @param [in] sample_count The size of sample
         */
        inline virtual void allocate_memory(size_t sample_count) noexcept
        {
            if (sample_count > 0U)
            {
                return;
            }
        }
        
        /**
         * @brief clear resource
         */
        virtual void clear_resource() noexcept {}

    private:
        std::vector<dds::sub::LoanableData*> m_loanableDataVec{};
        size_t m_dataAmount{ 0U };
    };
} /* sub */
} /* dds */

__GS_DDS4CPP_END_DECLS

#endif
