/**************************************************************
* @file SampleInfo.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_SAMPLEINFO_H
#define GSTONE_SAMPLEINFO_H 1

#include "dcps/DdsBaseTypes.h"
#include "dcps/DeclExport.h"

namespace dds
{
namespace core
{
/**
* @class SampleInfo
* @brief SampleInfo is the information that accompanies each sample that is ‘read’ or ‘taken.’
* @note This class will record sample information.
*/
class GS_DDS4CPP_API SampleInfo final
{
public:
    /* The sample_state,(READ or NOT_READ) - indicates whether or not the corresponding data sample has already been read.*/
    DDS::SampleStateMask sample_state { DDS::READ_SAMPLE_STATE};

    /* The view_state,(NEW, or NOT_NEW) - indicates whether the DataReader has already seen samples for the most current generation of the related instance.*/
    DDS::ViewStateMask view_state { DDS::NEW_VIEW_STATE};

    /* 
     * The instance_state,(ALIVE, NOT_ALIVE_DISPOSED, or NOT_ALIVE_NO_WRITERS) 
     * - indicates whether the instance is currently in existence or, if it has been disposed, the reason why it was disposed.
     */
    DDS::InstanceStateMask instance_state { DDS::ALIVE_INSTANCE_STATE};

    /* 
     * The disposed_generation_count that indicates the number of times the instance had become alive after it was disposed 
     * explicitly by a DataWriter, at the time the sample was received.
     */
    guint32_t disposed_generation_count {0U};

    /*
     * The no_writers_generation_count that indicates the number of times the instance had become alive after it was 
     * disposed because there were no writers, at the time the sample was received.
     */
    guint32_t no_writers_generation_count {0U};

    /*
     * The sample_rank that indicates the number of samples related to the same instance that follow in the collection 
     * returned by read or take.
     */
    guint32_t sample_rank {0U};

    /*
     * The generation_rank that indicates the generation difference (number of times the instance was disposed and become 
     * alive again) between the time the sample was received, and the time the most recent sample in the collection related to 
     * the same instance was received.
     */
    guint32_t generation_rank {0U};

    /*
     * The absolute_generation_rank that indicates the generation difference (number of times the instance was disposed and 
     * become alive again) between the time the sample was received, and the time the most recent sample (which may not be 
     * in the returned collection) related to the same instance was received.
     */
    guint32_t absolute_generation_rank {0U};

    /* The source_timestamp that indicates the time provided by the DataWriter when the sample was written.*/
    gstone::rtps::Duration_t source_timestamp {};

    /* The instance_handle that identifies locally the corresponding instance.*/
    gstone::rtps::InstanceHandle_t instance_handle {};

    /* 
     * The publication_handle that identifies locally the DataWriter that modified the instance. The publication_handle is the 
     * same InstanceHandle_t that is returned by the operation get_matched_publications on the DataReader and can also 
     * be used as a parameter to the DataReader operation get_matched_publication_data.
     */
    gstone::rtps::InstanceHandle_t publication_handle {};

    /*
     * The valid_data flag that indicates whether the DataSample contains data or else it is only used to communicate of a 
     * change in the instance_state of the instance.
     */
    gbool_t valid_data {false};

    /* The reception_timestamp that indicates the time provided by the DataReader when the sample was read.*/
    gstone::rtps::Duration_t reception_timestamp {};
    
    /* The ready_timestamp that indicates the time when previous samples were received (include itself).*/
    gstone::rtps::Duration_t ready_timestamp {};

    /**
     * @brief Construct a new SampleInfo object with default parameter.
     */
    SampleInfo() = default;

    /**
     * @brief Destroy the SampleInfo object.
     */
    ~SampleInfo() = default;

    /**
     * @brief Construct a new SampleInfo object with copying SampleInfo object.
     * @param [in] a_sample_info A new SampleInfo object is created by copying this SampleInfo object.
     */
    SampleInfo( SampleInfo const& a_sample_info) = default;

    /**
     * @brief Copy a SampleInfo object with a SampleInfo object.
     * @param [in] a_sample_info The SampleInfo object that need to copy.
     * @return SampleInfo object that after copying.
     */
    SampleInfo& operator=( SampleInfo const& a_sample_info) = default;

     /**
     * @brief Construct a new Base Status object with moving SampleInfo object.
     * @param [in] a_sample_info A new SampleInfo object is created by moving this SampleInfo object.
     */
    SampleInfo( SampleInfo && a_sample_info) = default;

    /**
     * @brief Move a SampleInfo object with a SampleInfo object.
     * @param [in] a_sample_info The SampleInfo object that need to move.
     * @return SampleInfo object that after moving.
     */
    SampleInfo &operator=(SampleInfo && a_sample_info) = default;
};

} /*core*/
} /*dds*/

#endif /* GSTONE_SAMPLEINFO_H */
