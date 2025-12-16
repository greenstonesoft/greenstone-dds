/**************************************************************
* @file Listener.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_LISTENER_API_H
#define GSTONE_LISTENER_API_H 1

#include "swiftdds/dcps/DdsBaseTypes.h"
#include "swiftdds/dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace core
{
/**
* @class Listener
* @brief Listener is the abstract root for all Listener interfaces.
* @note All the supported kinds of concrete Listener interfaces (one per concrete Entity: DomainParticipant, Topic, Publisher, DataWriter, Subscriber, and DataReader) 
* derive from this root and add methods whose prototype depends on the concrete Listener.
*/
class GS_DDS4CPP_API Listener
{
public:
    /**
     * @brief Construct a new Listener object with default parameter.
     */
    Listener() = default;

    /**
     * @brief Destroy the Listener object.
     */
    virtual ~Listener() = default;
protected:
    /**
     * @brief Do not use this operation to construct a new Listener object with copying Listener object.
     * @param [in] a_listener A new Listener object is created by copying this Listener object.
     */
    Listener(Listener const& a_listener) = delete;

    /**
     * @brief Do not use this operation to construct a new Base Status object with moving Listener object.
     * @param [in] a_listener A new Listener object is created by moving this Listener object.
     */
    Listener(Listener&& a_listener) = default;

    /**
     * @brief Do not use this operation to copy a Listener object with a Listener object.
     * @param [in] a_listener The Listener object that need to copy.
     * @return Listener object that after copying.
     */
    Listener& operator=(Listener const& a_listener) = delete;

    /**
     * @brief Do not use this operation to move a Listener object with a Listener object.
     * @param [in] a_listener The Listener object that need to copy.
     * @return Listener object that after moving.
     */
    Listener& operator=(Listener&& a_listener) = delete;

};
} /*core*/
} /*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_LISTENER_API_H*/
