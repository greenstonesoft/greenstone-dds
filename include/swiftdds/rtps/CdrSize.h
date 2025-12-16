/**************************************************************
 * @file CdrSize.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
 **************************************************************/
#ifndef GS_CDRsize_H
#define GS_CDRsize_H 1

#include <type_traits>
#include <array>
#include <vector>
#include <map>
#include <string>

namespace gstone
{
namespace rtps
{
/**
 * @class CdrUtil
 * @brief used to calculate the serialiezed size
 * @note apply to primitive and complex data type
*/
class CdrUtil
{
public:
/**
 * @brief alignment with current position for common data
 * @param [in] cur_al current position
 * @param [in] size the data size
 * @return std::size_t 
 * @retval the alignmented size
*/
inline static std::size_t alignment_bytes(std::size_t const cur_al, std::size_t const size) noexcept
{
    return ((((cur_al+size-1))&(~(size-1U)))+size);
}

/**
 * @brief alignment with current position for integeral data
 * @param [in] cur_al current position
 * @param [in] val the data 
 * @return std::size_t 
 * @retval the alignmented size
*/
template<typename T,
typename std::enable_if<std::is_integral<T>{},bool>::type = true>
inline static std::size_t alignment(std::size_t const cur_al, T const &val) noexcept
{
    return alignment_bytes(cur_al, sizeof(T));
}

/**
 * @brief alignment with current position for float data
 * @param [in] cur_al current position
 * @param [in] val the data 
 * @return std::size_t 
 * @retval the alignmented size
*/
template<typename T,
typename std::enable_if<std::is_floating_point<T>{},bool>::type = true>
inline static std::size_t alignment(std::size_t const cur_al, T const &val) noexcept
{
    return alignment_bytes(cur_al, sizeof(T));
}

/**
 * @brief alignment with current position for enum data
 * @param [in] cur_al current position
 * @param [in] val the data 
 * @return std::size_t 
 * @retval the alignmented size
*/
template<typename T,
typename std::enable_if<std::is_enum<T>{},bool>::type = true>
inline static std::size_t alignment(std::size_t const cur_al, T const &val) noexcept
{
    return alignment_bytes(cur_al, 4U);
}

/**
 * @brief alignment with current position for class data
 * @param [in] cur_al current position
 * @param [in] val the data 
 * @return std::size_t 
 * @retval the alignmented size
*/
template<typename T,
typename std::enable_if<std::is_class<T>{},bool>::type = true>
inline static std::size_t alignment(std::size_t const cur_al, T const &val) noexcept
{
    return val.max_align_size(cur_al);
}

/**
 * @brief alignment with current position for string data
 * @param [in] cur_al current position
 * @param [in] val the data
 * @return std::size_t 
 * @retval the alignmented size
*/
inline static std::size_t alignment(std::size_t const cur_al, std::string const &val) noexcept
{
    std::size_t cur{CdrUtil::alignment(cur_al, 4U)};
    cur += val.length() + 1U;
    return cur;
}

/**
 * @brief alignment with current position for u16string data
 * @param [in] cur_al current position
 * @param [in] val the data
 * @return std::size_t 
 * @retval the alignmented size
*/
inline static std::size_t alignment(std::size_t const cur_al, std::u16string const &val) noexcept
{
    std::size_t cur{CdrUtil::alignment(cur_al, 4U)};
    cur += (val.length() + 1U) * 2U;
    return cur;
}

/**
 * @brief alignment with current position for array data
 * @param [in] cur_al current position
 * @param [in] val the data
 * @return std::size_t 
 * @retval the alignmented size
*/
template<typename T, std::size_t N>
inline static std::size_t alignment(std::size_t const cur_al, std::array<T,N> const &val) noexcept
{
    if(N < 1U)
    {
        return cur_al;
    }

    std::size_t const one_ele { CdrUtil::alignment(1U, val[0U]) };
    return (cur_al + one_ele*N);

}

template<std::size_t N>
inline static std::size_t alignment(std::size_t const cur_al, std::array<std::u16string,N> const &val) noexcept
{
    std::size_t cur {cur_al};
    if(N < 1U)
    {
        return cur;
    }
    for(std::size_t i {0U};i < N;++i)
    {
        cur = CdrUtil::alignment(cur, val[i]);
    }

    return cur;

}

template<std::size_t N>
inline static std::size_t alignment(std::size_t const cur_al, std::array<std::string,N> const &val) noexcept
{
    std::size_t cur {cur_al};
    if(N < 1U)
    {
        return cur;
    }
    for(std::size_t i {0U};i < N;++i)
    {
        cur = CdrUtil::alignment(cur, val[i]);
    }

    return cur;

}

/**
 * @brief alignment with current position for vector data
 * @param [in] cur_al current position
 * @param [in] val the data
 * @return std::size_t 
 * @retval the alignmented size
*/
template<typename T>
inline static typename std::enable_if<!std::is_integral<T>::value && !std::is_floating_point<T>::value, std::size_t>::type 
alignment(std::size_t const cur_al, std::vector<T> const &val) noexcept
{

    std::size_t cur { CdrUtil::alignment(cur_al, sizeof(int)) };
    if(val.size() < 1U)
    {
        return cur;
    }
    std::size_t const one_ele { CdrUtil::alignment(1U, val[0U]) };
    return (cur + one_ele*val.size());
}

template<typename T>
inline static typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, std::size_t>::type 
alignment(std::size_t const cur_al, std::vector<T> const &val) noexcept
{

    std::size_t cur { CdrUtil::alignment(cur_al, sizeof(int)) };
    if(val.size() < 1U)
    {
        if(sizeof(T) == 8U)
        {
            return alignment_bytes(cur, 8U);
        }
        else
        {
            return cur;
        }
    }
    std::size_t const one_ele { CdrUtil::alignment(1U, val[0U]) };
    return (cur + one_ele*val.size());
}

inline static std::size_t alignment(std::size_t const cur_al, std::vector<std::u16string> const &val) noexcept
{

    std::size_t cur { CdrUtil::alignment(cur_al, sizeof(int)) };
    if(val.size() < 1U)
    {
        return cur;
    }
    for(std::size_t i {0U};i < val.size(); ++i)
    {
        cur = CdrUtil::alignment(cur, val[i]);
    }
    return cur;
}

inline static std::size_t alignment(std::size_t const cur_al, std::vector<std::string> const &val) noexcept
{

    std::size_t cur { CdrUtil::alignment(cur_al, sizeof(int)) };
    if(val.size() < 1U)
    {
        return cur;
    }
    for(std::size_t i {0U};i < val.size(); ++i)
    {
        cur = CdrUtil::alignment(cur, val[i]);
    }
    return cur;
}

/**
 * @brief alignment with current position for map data
 * @param [in] cur_al current position
 * @param [in] val the data
 * @return std::size_t 
 * @retval the alignmented size
*/
template<typename K,typename V>
inline static std::size_t alignment(std::size_t const cur_al, std::map<K,V> const &val) noexcept
{

    std::size_t cur { CdrUtil::alignment(cur_al, sizeof(int)) };
    if(val.size() < 1U)
    {
        return cur;
    }

    std::size_t const k_ele = CdrUtil::alignment(1U, K());
    std::size_t const v_ele = CdrUtil::alignment(1U, V());

    return (cur + (k_ele+v_ele)*val.size());
}

};
}/*rtps*/
}/*gstone*/

#endif /* __GS_CDR_UTIL_H */
