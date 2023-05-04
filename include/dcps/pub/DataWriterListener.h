/**************************************************************
* @file DataWriterListener.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_DATAWRITERLISTENER_API_H
#define GSTONE_DATAWRITERLISTENER_API_H 1

#include "dcps/core/Listener.h"
#include "dcps/core/Status.h"
#include "dcps/pub/DataWriter.h"
#include "rtps/basetypes/Guid.h"
#include "dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds
{
namespace pub
{
    class DataWriter;

/**
* @class DataWriterListener
* @brief This class is DDSListener for DDSDataWriter status.
*/
class GS_DDS4CPP_API DataWriterListener : public virtual dds::core::Listener
{
public:
    /**
    * @brief Constructor of the class DataWriterListener.
    */
    DataWriterListener();
    
    /**
    * @brief Destructor of the class DataWriterListener.
    */
    ~DataWriterListener() noexcept override;

    /**
    * @brief The deadline that the DataWriter has committed through its QosPolicy DEADLINE was not respected for a specific instance.
    * @param [in,out] a_dataWriter A pointer of the locally DataWriter that triggers the listener callback.
    * @param [in,out] a_status Const reference of the locally DataWriter's OfferedDeadlineMissedStatus.
    */
    virtual void on_offered_deadline_missed(dds::pub::DataWriter* a_dataWriter,
                                            dds::core::OfferedDeadlineMissedStatus const &a_status) noexcept;
    
    /**
    * @brief The liveliness that the DataWriter has committed through its QosPolicy LIVELINESS was not respected; 
    * thus DataReader entities will consider the DataWriter as no longer “active.”
    * @param [in,out] a_dataWriter A pointer of the locally DataWriter that triggers the listener callback.
    * @param [in,out] a_status Const reference of the locally DataWriter's LivelinessLostStatus.
    */
    virtual void on_liveliness_lost(dds::pub::DataWriter* a_dataWriter, dds::core::LivelinessLostStatus const &a_status) noexcept;
    
    /**
    * @brief A QosPolicy value was incompatible with what was requested.
    * @param [in,out] a_writer A pointer of the locally DataWriter that triggers the listener callback.
    * @param [in,out] a_status Const reference of the locally DataWriter's OfferedIncompatibleQosStatus.
    */
    virtual void on_offered_incompatible_qos(dds::pub::DataWriter* a_writer,
                                             dds::core::OfferedIncompatibleQosStatus const &a_status) noexcept;
    
    /**
    * @brief The DataWriter has found DataReader that matches the Topic and has compatible QoS, or has ceased to 
    * be matched with a DataReader that was previously considered to be matched.
    * @param [in,out] a_writer A pointer of the locally DataWriter that triggers the listener callback.
    * @param [in,out] a_status Const reference of the locally DataWriter's PublicationMatchedStatus.
    */
    virtual void on_publication_matched(dds::pub::DataWriter* a_writer,
                                        dds::core::PublicationMatchedStatus const &a_status) noexcept;

protected:
    /**
    * @brief Constructor of the class DataWriterListener by another DataWriterListener object.
    * @param [in] a_info Const reference of a DataWriterListener object.
    */
    DataWriterListener(DataWriterListener const&a_info) = default;
    
    /**
    * @brief Assign a DataWriterListener object to the current DataWriterListener object.
    * @param [in] a_info Const reference of a DataWriterListener object.
    * @return Reference of this DataWriterListener object.
    */
    DataWriterListener& operator=(DataWriterListener const& a_info) = default;
    
    /**
    * @brief Don't use move constructor of the class DataWriterListener.
    * @param [in] a_info Rvalue reference of this DataWriterListener object.
    */
    DataWriterListener(DataWriterListener&&a_info) = delete;
    
    /**
    * @brief Don't use move assignment of the class DataWriterListener.
    * @param [in] a_info Rvalue reference of this DataWriterListener object.
    * @return Reference of this DataWriterListener object.
    */
    DataWriterListener& operator=(DataWriterListener&&a_info) = delete;
};
}/*pub*/
}/*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_DATAWRITERLISTENER_API_H*/
