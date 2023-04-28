/**************************************************************
* @file DataReaderListener.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_DATAREADERLISTENER_API_H
#define GSTONE_DATAREADERLISTENER_API_H 1

#include "dcps/core/Status.h"
#include "dcps/core/Listener.h"
#include "rtps/basetypes/Guid.h"
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace sub
{
    class DataReader;
    /**
     * @class DataReaderListener
     * @brief Since a DataReader is a kind of Entity, it has the ability to have an associated listener.
     * In this case, the associated listener should be of concrete type DataReaderListener.
     */
    class GS_DDS4CPP_API DataReaderListener : virtual public dds::core::Listener
    {
    public:
        /**
         * @brief Construct a new Data Reader Listener object
         */
        DataReaderListener() noexcept = default;
        
        /**
         * @brief Destroy the Data Reader Listener object
         */
        ~DataReaderListener() noexcept override = default;

        /**
         * @brief callback for deadline missed
         * @param [in] reader The pointer of active reader
         * @param [in] status The info about deadline missed
         */
        virtual void on_requested_deadline_missed(dds::sub::DataReader* reader, dds::core::RequestedDeadlineMissedStatus const& status) noexcept;
        
        /**
         * @brief callback for incompatible qos
         * @param [in] reader The pointer of active reader
         * @param [in] status The info about incompatible qos
         */
        virtual void on_requested_incompatible_qos(
            dds::sub::DataReader* reader, dds::core::RequestedIncompatibleQosStatus const& status) noexcept;
        
        /**
         * @brief callback for sample rejected
         * @param [in] reader The pointer of active reader
         * @param [in] status The info about sample rejected
         */
        virtual void on_sample_rejected(dds::sub::DataReader* reader,
            dds::core::SampleRejectedStatus const& status) noexcept;
        
        /**
         * @brief callback for liveliness changed
         * @param [in] reader The pointer of active reader
         * @param [in] status The info about liveliness changed
         */
        virtual void on_liveliness_changed(dds::sub::DataReader* reader,
            dds::core::LivelinessChangedStatus const& status) noexcept;
        
        /**
         * @brief callback for data available
         * @param [in] reader The pointer of active reader
         */
        virtual void on_data_available(dds::sub::DataReader* reader) noexcept;
        
        /**
         * @brief callback for subscription matched
         * @param [in] reader The pointer of active reader
         * @param [in] status The info about subscription matched
         */
        virtual void on_subscription_matched(dds::sub::DataReader* reader,
            dds::core::SubscriptionMatchedStatus const& status) noexcept;
        
        /**
         * @brief callback for sample lost
         * @param [in] reader The pointer of active reader
         * @param [in] status The info about sample lost
         */
        virtual void on_sample_lost(dds::sub::DataReader* reader,
            dds::core::SampleLostStatus const& status) noexcept;
        
    protected:
        /**
         * @brief Construct a new Data Reader Listener object
         * @param [in] other Another Data Reader Listener
         */
        DataReaderListener(DataReaderListener const& other) = default;
        
        /**
         * @brief Construct a new Data Reader Listener object
         * @param [in] other Another Data Reader Listener
         */
        DataReaderListener(DataReaderListener&& other) = default;
        
        /**
         * @brief This operator is Deprecated.
         * @param [in] Another DataReaderListener
         * @return Copy of DataReaderListener
         */
        DataReaderListener& operator=(DataReaderListener const& other) = delete;
        
        /**
         * @brief This operator is Deprecated.
         * @param [in] Another DataReaderListener
         * @return Copy of DataReaderListener
         */
        DataReaderListener& operator=(DataReaderListener&& other) = delete;
    };
} /* sub */
} /* dds */

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_DATAREADERLISTENER_API_H*/
