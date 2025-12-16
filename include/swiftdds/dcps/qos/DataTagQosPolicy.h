/**************************************************************
* @file DataTagQosPolicy.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_DATATAGQOSPOLICY_H
#define GSTONE_DATATAGQOSPOLICY_H 1

#include <vector>
#include "swiftdds/dcps/PITypes.h"
#include "swiftdds/dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace qos
{
    /**
     * @brief This class defines Tag used for security information
     */
    class GS_DDS4CPP_API Tag final
    {
        gstring_t m_name;
        gstring_t m_value;
    };

    using TagSeq = std::vector<Tag>;
    using TagSeq_t = TagSeq;

    /**
     * @brief This class is used to add a data tag for each data sample.
     */
    class GS_DDS4CPP_API DataTags final
    {
        TagSeq_t m_tags;
    };

    //using DataTagQosPolicy = DataTags_t;

}/*qos*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_DATATAGQOSPOLICY_H*/
