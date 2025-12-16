/**************************************************************
* @file TimeBasedFilterQosPolicy.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/

#ifndef GSTONE_QOSPOLICY_TIMEBASEDFILTER_H
#define GSTONE_QOSPOLICY_TIMEBASEDFILTER_H 1

#include "swiftdds/dcps/qos/QosPolicy.h"

namespace dds
{
namespace qos
{
    
    /**
    * @brief This policy allows DataReader to specify that it is interested only in (potentially) a subset of the values of the data.
    */
    class GS_DDS4CPP_API TimeBasedFilterQosPolicy : public QosPolicy
    {
    public:
        TimeBasedFilterQosPolicy()
            : QosPolicy{ "TimeBasedFilter" }, m_minimumSeparation{ gstone::rtps::Duration_t::duration_zero() }
        {
        }

        /**
        * @brief This function serializies TimeBasedFilterQosPolicy object with CDR serialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t serialize(DdsCdr& cdr) const noexcept
        {
            cdr.serialize(m_minimumSeparation);
            return;
        }

        /**
        * @brief This function deserializies TimeBasedFilterQosPolicy object with CDR deserialization.
        * @param [in] cdr CDR serialization object.
        */
        inline gvoid_t deserialize(DdsCdr& cdr) noexcept
        {
            cdr.deserialize(m_minimumSeparation);
            return;
        }

        /**
        * @brief This function get minimum separation.
        * @return A Duration class representing minimum separation.
        */
        inline gstone::rtps::Duration_t const& minimum_separation() const noexcept 
        {
            return m_minimumSeparation;
        }

        /**
        * @brief This function set minimum separation.
        * @param [in] minimum_separation_t A Duration class representing minimum separation to be set to.
        */
        inline void minimum_separation(gstone::rtps::Duration_t const& minimum_separation_t) noexcept {
            m_minimumSeparation = minimum_separation_t;
        }

        /**
         * @brief Compare two TimeBasedFilterQosPolicy objects for equailty.
         * @param [in] l_timeBasedFilter_qos Const Reference of the left TimeBasedFilterQosPolicy object.
         * @param [in] r_timeBasedFilter_qos Const Reference of the right TimeBasedFilterQosPolicy object.
         * @return Return true if equality, else return false. 
         */
        inline friend gbool_t operator==(TimeBasedFilterQosPolicy const& l_timeBasedFilter_qos, TimeBasedFilterQosPolicy const& r_timeBasedFilter_qos) noexcept
        {
            if (l_timeBasedFilter_qos.minimum_separation() == r_timeBasedFilter_qos.minimum_separation())
            {
                return true;
            }
            return false;
        }

    private:
        gstone::rtps::Duration_t m_minimumSeparation;    
    };
}
}

#endif
