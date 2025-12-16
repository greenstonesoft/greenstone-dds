/**************************************************************
* @file SampleIdentity.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_SAMPLEIDENTITY_API_H
#define GSTONE_SAMPLEIDENTITY_API_H

#include "swiftdds/dcps/DdsBaseTypes.h"
#include "swiftdds/dcps/DeclExport.h"
#include "swiftdds/rtps/basetypes/Guid.h"

namespace dds
{
namespace core
{

/**
* @class SampleIdentity
* @brief SampleIdentity is the information that accompanies each sample.
* @note This class will record sample information of guid and sequence number.
*/
class GS_DDS4CPP_API SampleIdentity
{
public:

    /**
     * @brief Construct a new SampleIdentity object with default parameter.
     */
    SampleIdentity() = default;

    /**
     * @brief Destroy the SampleIdentity object.
     */
    ~SampleIdentity() = default;

    /**
     * @brief Construct a new SampleIdentity object with copying SampleIdentity object.
     * @param [in] a_sample_id A new SampleIdentity object is created by copying this SampleIdentity object.
     */
    SampleIdentity( SampleIdentity const& a_sample_id) = default;

    /**
     * @brief Copy a SampleIdentity object with a SampleIdentity object.
     * @param [in] a_sample_id The SampleIdentity object that need to copy.
     * @return SampleIdentity object that after copying.
     */
    SampleIdentity& operator=( SampleIdentity const& a_sample_id) = default;

     /**
     * @brief Construct a new Base Status object with moving SampleIdentity object.
     * @param [in] a_sample_id A new SampleIdentity object is created by moving this SampleIdentity object.
     */
    SampleIdentity( SampleIdentity && a_sample_id) = default;

    /**
     * @brief Move a SampleIdentity object with a SampleIdentity object.
     * @param [in] a_sample_id The SampleIdentity object that need to move.
     * @return SampleIdentity object that after moving.
     */
    SampleIdentity &operator=(SampleIdentity && a_sample_id) = default;

    /*!
     * @brief
     */
    gbool_t operator ==(SampleIdentity const & a_sample_id) const noexcept
    {
        return (m_writerGuid == a_sample_id.m_writerGuid) && (m_sequenceNumberVal == a_sample_id.m_sequenceNumberVal);
    }

    /*!
     * @brief
     */
    gbool_t operator !=(SampleIdentity const& a_sample_id) const noexcept
    {
        return !(*this == a_sample_id);
    }

    /**
     * @brief To allow using SampleIdentity as map key.
     * @param a_sample_id
     * @return
     */
    gbool_t operator <(SampleIdentity const& a_sample_id) const
    {
        return (m_writerGuid < a_sample_id.m_writerGuid) ||
               ((m_writerGuid == a_sample_id.m_writerGuid) && (m_sequenceNumberVal < a_sample_id.m_sequenceNumberVal));
    }

    /**
    * @brief This function sets the value of 'm_writerGuid' parameter.
    * @param [in] _guid Const reference of a GUID object.
    */
    inline gvoid_t writer_guid(gstone::rtps::GUID const &_guid) noexcept
    {
        m_writerGuid = _guid;
    }

    /**
    * @brief This function gets the value of 'm_writerGuid' parameter.
    * @return Return GUID object.
    */
    inline gstone::rtps::GUID const& writer_guid() const noexcept
    {
        return m_writerGuid;
    }

    /**
    * @brief This function sets the value of 'm_sequenceNumberVal' parameter.
    * @param [in] _val Const  of a seq value.
    */
    inline gvoid_t sequence_number_val(gint64_t const _val) noexcept
    {
        m_sequenceNumberVal = _val;
    }

    /**
    * @brief This function gets the value of 'm_sequenceNumberVal' parameter.
    * @return Return gint64_t.
    */
    inline gint64_t sequence_number_val() const noexcept
    {
        return m_sequenceNumberVal;
    }


private:

    gstone::rtps::GUID m_writerGuid {};

    gint64_t m_sequenceNumberVal {-1};

};
    
} // namespace core   
} // namespace dds



#endif /* GSTONE_SAMPLEIDENTITY_API_H */
