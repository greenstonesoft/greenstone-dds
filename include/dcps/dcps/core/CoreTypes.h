/**************************************************************
* @file CoreTypes.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_CORETYPES_API_H
#define GSTONE_CORETYPES_API_H 1

#include <vector>
#include <set>
#include <string>

#include "dcps/DdsBaseTypes.h"
#include "dcps/core/SampleInfo.h"
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace core
{
    using StringSeq = std::vector<std::string>;
    using HandleSeq = std::set<gstone::rtps::InstanceHandle_t>;
    using SampleInfoSeq = std::vector<dds::core::SampleInfo>;

} /*core*/
} /*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_CORETYPES_API_H*/
