/**************************************************************
* @file PublisherListener.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/


#ifndef GSTONE_PUBLISHERLISTENER_API_H
#define GSTONE_PUBLISHERLISTENER_API_H 1

#include "dcps/pub/DataWriterListener.h"
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace pub
{
    /**
    * @class PublisherListener
    * @brief This class is DDSListener for DDSPublisher status.
    */
    class GS_DDS4CPP_API PublisherListener : public virtual dds::pub::DataWriterListener
    {
    public:
        /**
        * @brief Destructor of the class PublisherListener.
        */
        ~PublisherListener() override = default;
        
        /**
        * @brief Constructor of the class PublisherListener.
        */
        PublisherListener() = default;
        
        /**
        * @brief Constructor of the class PublisherListener by another PublisherListener object.
        * @param [in] a_info Const reference of a PublisherListener object.
        */
        PublisherListener(PublisherListener const& a_info) = default;
        
        /**
        * @brief Assign a PublisherListener object to the locally PublisherListener object.
        * @param [in] a_info Const reference of a PublisherListener object.
        * @return Reference of the locally PublisherListener object.
        */
        PublisherListener& operator=(PublisherListener const& a_info) = default;
        
        /**
        * @brief Don't use move constructor of the class PublisherListener.
        * @param [in] a_info Rvalue reference of a PublisherListener object.
        */
        PublisherListener(PublisherListener&& a_info) = delete;
        
        /**
        * @brief Don't use move assignment of the class PublisherListener.
        * @param [in] a_info Rvalue reference of this PublisherListener object.
        * @return Reference of this PublisherListener object.
        */
        PublisherListener& operator=(PublisherListener&& a_info) = delete;
    };
}/*pub*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_PUBLISHERLISTENER_API_H*/
