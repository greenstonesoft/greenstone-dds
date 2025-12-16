/**************************************************************
* @file SubscriberListener.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_SUBSCRIBERLISTENER_API_H
#define GSTONE_SUBSCRIBERLISTENER_API_H 1

#include "swiftdds/dcps/sub/DataReaderListener.h"
#include "swiftdds/dcps/core/ForwardDeclaration.h"
#include "swiftdds/dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace sub
{
    /**
     * @class SubscriberListener
     * @brief Since a Subscriber is a kind of Entity, it has the ability to have an associated listener.
     * In this case, the associated listener should be of concrete type SubscriberListener
     */
    class GS_DDS4CPP_API SubscriberListener : virtual public dds::sub::DataReaderListener
    {
        public:
            /**
             * @brief Construct a new Subscriber Listener object
             */
            SubscriberListener() = default;
            
            /**
             * @brief Destroy the Subscriber Listener object
             */
            ~SubscriberListener() override = default;
            
            /**
             * @brief Copy-Construct a new Subscriber Listener object
             * @param [in] other Another SubscriberListener
             */
            SubscriberListener(SubscriberListener const& other) = default;
            
            /**
             * @brief Move-Construct a new Subscriber Listener object
             * @param [in] other Another SubscriberListener
             */
            SubscriberListener(SubscriberListener&& other) = default;
            
            /**
             * @brief This function is deleted.
             */
            SubscriberListener& operator=(SubscriberListener const& other) = delete;
            
            /**
             * @brief This function is deleted.
             */
            SubscriberListener& operator=(SubscriberListener&& other) = delete;

            /**
             * @brief The callback for coming message
             * @param [in] subscriber The subscriber is active.
             */
            virtual void on_data_on_readers(dds::sub::Subscriber* subscriber) noexcept;
    };
} /* sub */
} /* dds */

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_SUBSCRIBERLISTENER_API_H*/


