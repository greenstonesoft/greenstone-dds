/**************************************************************
 * @file DdsOptionalMember.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
 * All rights reserved
 **************************************************************/

#ifndef GSTONE_RTPS_DDSOPTIONALMEMBER_H
#define GSTONE_RTPS_DDSOPTIONALMEMBER_H

#include "swiftdds/dcps/DeclExport.h"
#include "swiftdds/rtps/DdsCdr.h"
#include "swiftdds/rtps/CdrSize.h"
#include "swiftdds/dcps/PITypes.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone
{
namespace rtps
{

template<class _Tp>
class GS_DDS4CPP_API DdsOptionalMember
{
public:
    static constexpr gbool_t HAS_OPTIONAL_OPT{true};
    /**
     * @brief The default constructor for DdsOptionalMember.
     */
    DdsOptionalMember() = default;

     /**
     * @brief The copy constructor for DdsOptionalMember.
     */   
    DdsOptionalMember(DdsOptionalMember const&) = default;

    /**
     * @brief The move constructor for DdsOptionalMember.
     */
    DdsOptionalMember(DdsOptionalMember &&) = default;

    /**
     * @brief The copy assignment operator.
     * @return DdsOptionalMember& Reference of the locally DdsOptionalMember object.
     */
    DdsOptionalMember& operator=(DdsOptionalMember const&) = default;

    /**
     * @brief The move assignment operator.
     * @return DdsOptionalMember& Reference of the locally DdsOptionalMember object.
     */
    DdsOptionalMember& operator=(DdsOptionalMember &&) = default;

    /**
     * @brief The type data value assignment operator.
     * @return DdsOptionalMember& Reference of the locally DdsOptionalMember object.
     */
    DdsOptionalMember& operator=(_Tp const &_val) noexcept
    {
        m_data = _val;
        m_optionalFlag = true;
        return *this;
    }

    /**
     * @brief Destroy the DdsOptionalMember object.
     */
    ~DdsOptionalMember() = default;
    
    /**
    * @brief This function set the value of DdsOptionalMember optionalFlag
    * @param [in] _flag Const reference of the DdsOptionalMember optionalFlag to be set to.
    */
    inline gvoid_t optional_flag(gbool_t const &_flag) noexcept
    {
        m_optionalFlag = _flag;
    }

    /**
    * @brief This function get the value of DdsOptionalMember optionalFlag
    * @return Value of the DdsOptionalMember optionalFlag.
    */
    inline gbool_t optional_flag() const noexcept
    {
        return m_optionalFlag;
    }

    /**
     * @brief the serialized function for DdsOptionalMember type
     * @param [in] cdr the serialized object
     * @return DdsCdr
     * @retval return the object DdsCdr
     * @note no exception
     */
    DdsCdr& serialize(DdsCdr &cdr) const
    {
        gstone::rtps::CdrEncoding const encode{cdr.get_encoding()};
        gstone::rtps::CdrEversion const eversion{cdr.get_eversion()};

        if((encode == gstone::rtps::CdrEncoding::CDR_ENCODING) && (eversion == gstone::rtps::CdrEversion::VERSION1))
        {
            return serialize_plain_cdr(cdr);
        }
        else if((encode == gstone::rtps::CdrEncoding::CDR_ENCODING) && (eversion == gstone::rtps::CdrEversion::VERSION2))
        {
            return serialize_plain_cdr2_delimited_cdr(cdr);
        }
        else if(encode == gstone::rtps::CdrEncoding::PLCDR_ENCODING)
        {
            return serialize_pl_cdr_pl_cdr2(cdr);
        }
        else
        {
            return cdr;
        }
    }

    /**
     * @brief the deserialized function for DdsOptionalMember type
     * @param [in] cdr the deserialized object
     * @return DdsCdr
     * @retval return the object DdsCdr
     * @note no exception
     */
	DdsCdr& deserialize(DdsCdr &cdr)
    {
        gstone::rtps::CdrEncoding const encode{cdr.get_encoding()};
        gstone::rtps::CdrEversion const eversion{cdr.get_eversion()};

        if((encode == gstone::rtps::CdrEncoding::CDR_ENCODING) && (eversion == gstone::rtps::CdrEversion::VERSION1))
        {
            return deserialize_plain_cdr(cdr);
        }
        else if((encode == gstone::rtps::CdrEncoding::CDR_ENCODING) && (eversion == gstone::rtps::CdrEversion::VERSION2))
        {
            return deserialize_plain_cdr2_delimited_cdr(cdr);
        }
        else if(encode == gstone::rtps::CdrEncoding::PLCDR_ENCODING)
        {
            return deserialize_pl_cdr_pl_cdr2(cdr);
        }
        else
        {
            return cdr;
        }
    }

    /**
     * @brief alignment with current position for DdsOptionalMember
     * @param [in] _cur_al current position
     * @return guint32_t
     * @retval the alignmented size
    */
    inline guint32_t max_align_size(uint32_t const _cur_al) const
    {
        guint32_t max_size {_cur_al};
        guint32_t const len {0U};
        max_size = gstone::rtps::CdrUtil::alignment(max_size, len);
        if(m_optionalFlag)
        {
            max_size = gstone::rtps::CdrUtil::alignment(max_size, m_data);
        }

        return max_size;
    }

    /**
    * @brief This function set the value of DdsOptionalMember data
    * @param [in] _val Const reference of the DdsOptionalMember data to be set to.
    */
    inline gvoid_t set_value(_Tp const & _val) noexcept
    {
        m_data = _val;
        m_optionalFlag = true;
    }

    /**
    * @brief The move function set the value of DdsOptionalMember data
    * @param [in] _val Reference of the DdsOptionalMember data to be set to.
    */
    inline gvoid_t set_value(_Tp && _val) noexcept
    {
        m_data = _val;
        m_optionalFlag = true;
    }

    /**
    * @brief This function get the value of DdsOptionalMember data
    * @return Const reference of the type representing Qos DdsOptionalMember data.
    */
    inline _Tp const& get_value() const noexcept
    {
        return m_data;
    }

    /**
    * @brief This function get the value of DdsOptionalMember data
    * @return Reference of the type representing Qos DdsOptionalMember data.
    */
    inline _Tp& get_value() noexcept
    {
        return m_data;
    }

private:
    DdsCdr& serialize_plain_cdr(DdsCdr &cdr) const
    {
        guint32_t const tmp_len {0U};
        CdrState const tmpCdrState {cdr.get_cdr_state()};
        cdr.serialize(tmp_len);
        if(m_optionalFlag)
        {
            guint32_t const startOffset {cdr.get_cdr_state().cur_offset()};
            cdr.serialize(m_data);
            CdrState const endCdrState {cdr.get_cdr_state()};
            guint32_t const endOffset {endCdrState.cur_offset()};
            guint32_t const len {static_cast<guint32_t>(endOffset - startOffset)};
            guint32_t const diff_len {static_cast<guint32_t>(endOffset - tmpCdrState.cur_offset())};

            cdr.set_cdr_state(tmpCdrState);
            cdr.move_length(diff_len);
            cdr.move_position(diff_len);
            cdr.serialize(len);

            cdr.jumping(len);
            cdr.length_offset(len);

            cdr.set_cdr_state(endCdrState);
        }

        return cdr;
    }
    DdsCdr& serialize_plain_cdr2_delimited_cdr(DdsCdr &cdr) const
    {
        gbool_t const is_present{m_optionalFlag};
        cdr.serialize(is_present);
        if(is_present)
        {
            cdr.serialize(m_data);
        }

        return cdr;
    }
    DdsCdr& serialize_pl_cdr_pl_cdr2(DdsCdr &cdr) const
    {
        if(m_optionalFlag)
        {
            cdr.serialize(m_data);
        }
        return cdr;
    }

    DdsCdr& deserialize_plain_cdr(DdsCdr &cdr)
    {
        guint32_t len;
        cdr.deserialize(len);
        if(len > 0U)
        {
            m_optionalFlag = true;
            cdr.deserialize(m_data);
        }

        return cdr;
    }
    DdsCdr& deserialize_plain_cdr2_delimited_cdr(DdsCdr &cdr)
    {
        gbool_t is_present;
        cdr.deserialize(is_present);
        if(is_present)
        {
            m_optionalFlag = true;
            cdr.deserialize(m_data);
        }
        return cdr;
    }
    DdsCdr& deserialize_pl_cdr_pl_cdr2(DdsCdr &cdr)
    {
        m_optionalFlag = true;
        cdr.deserialize(m_data);      
        return cdr;
    }
 
private:
    _Tp m_data{};
    gbool_t m_optionalFlag{false};
};


} /*rtps*/
} /*gstone*/


__GS_DDS4CPP_END_DECLS


#endif /* GSTONE_RTPS_DDSOPTIONALMEMBER_H */
