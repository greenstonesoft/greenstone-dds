/**************************************************************
 * @file OriginalData.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_ORIGINAL_DATA_H
#define GSTONE_ORIGINAL_DATA_H 1

#include "swiftdds/dcps/DeclExport.h"
#include "swiftdds/rtps/SerializedPayload.h"

#include <memory>

__GS_DDS4CPP_BEGIN_DECLS

namespace DDS
{
    class GS_DDS4CPP_API OriginalData final
    {
    private:
        /* data */
        std::shared_ptr<gstone::rtps::SerializedPayload_t> m_payload;

    public:
        OriginalData();
        ~OriginalData() = default;
        OriginalData(OriginalData &&)=default;
        OriginalData &operator=(OriginalData &&)=default;
        OriginalData(OriginalData const&)=default;
        OriginalData & operator=(OriginalData const&)=default;

        gvoid_t fill_copy(gvoid_t *data, guint32_t size);
        gvoid_t fill_move(gvoid_t **data, guint32_t *size);

        octet *getDataPtr();
        guint32_t getDataLength();

        std::shared_ptr<gstone::rtps::SerializedPayload_t> getPayload();
        gvoid_t setPayload(std::shared_ptr<gstone::rtps::SerializedPayload_t> payload);
    };
} // namespace DDS

__GS_DDS4CPP_END_DECLS

#endif
