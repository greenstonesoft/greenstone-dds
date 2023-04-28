/**************************************************************
 * @file Duration.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_RTPS_DURATION_H
#define GSTONE_RTPS_DURATION_H

#include "dcps/DeclExport.h"
#include "rtps/DdsCdr.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace gstone {
namespace rtps {

/**
 * @class Duration
 * @brief Type used to hold time differences.
 */
class GS_DDS4CPP_API Duration final
{
public:
    /**
     * @brief The default constructor for Duration.
     */
    constexpr Duration() noexcept : m_seconds {0}, m_fraction {0U} {}

    /**
     * @brief Construct a new Duration object.
     */
    constexpr Duration(gint32_t const _seconds, guint32_t const _fraction) noexcept
        : m_seconds {_seconds}, m_fraction {_fraction}
    {
    }

    /**
     * @brief Use milliseconds construct a new Duration object.
     * @param [in] ms Milliseconds used to construct the new object.
     */
    explicit Duration(uint64_t const ms) noexcept : m_seconds {0}, m_fraction {0U}
    {
        set_millisecond(ms);
    }

    /**
     * @brief Destroy the Duration object.
     */
    ~Duration() = default;

    /**
     * @brief The copy constructor for Duration.
     */
    Duration(Duration const &) = default;

    /**
     * @brief The move constructor for Duration.
     */
    Duration(Duration &&) = default;

    /**
     * @brief The copy assignment operator.
     * @return Duration& Reference of the locally Duration object.
     */
    Duration &operator=(Duration const &) = default;

    /**
     * @brief The move assignment operator.
     * @return Duration& Reference of the locally Duration object.
     */
    Duration &operator=(Duration &&) = default;

    /**
     * @brief An assignment operator.
     * @param [in] milliseconds Milliseconds used to set this object.
     * @return Duration& Reference of the locally Duration object.
     */
    inline Duration &operator=(guint64_t const milliseconds) &noexcept
    {
        set_millisecond(milliseconds);
        return *this;
    }

    /**
     * @brief Compare two Duration objects for equality.
     * @param [in] lhs Lhs parameter.
     * @param [in] rhs Rhs parameter.
     * @return gbool_t Whether lhs is equal to rhs.
     * @retval true Lhs is equal to rhs.
     * @retval false Lhs is inequal to rhs.
     */
    friend gbool_t operator==(Duration const &lhs, Duration const &rhs) noexcept
    {
        return (lhs.seconds() == rhs.seconds()) && (lhs.fraction() == rhs.fraction());
    }

    /**
     * @brief Compares two Duration objects for inequality.
     * @param [in] lhs Lhs parameter.
     * @param [in] rhs Rhs parameter.
     * @return gbool_t Whether lhs is inequal to rhs.
     * @retval true Lhs is inequal to rhs.
     * @retval false Lhs is equal to rhs.
     */
    friend gbool_t operator!=(Duration const &lhs, Duration const &rhs) noexcept
    {
        return !(lhs == rhs);
    }

    /**
     * @brief Get seconds of this duration.
     * @return gint32_t Seconds of this duration.
     */
    inline gint32_t seconds() const noexcept
    {
        return m_seconds;
    }

    /**
     * @brief Set seconds of this duration.
     * @param [in] the_seconds Seconds used to set.
     */
    inline gvoid_t seconds(gint32_t const the_seconds) noexcept
    {
        m_seconds = the_seconds;
    }

    /**
     * @brief Get fraction of this duration.
     * @return guint32_t Fraction of this Duration object.
     */
    inline guint32_t fraction() const noexcept
    {
        return m_fraction;
    }

    /**
     * @brief Set fraction of this duration.
     * @param [in] fraction Fraction Used to set.
     */
    inline gvoid_t fraction(guint32_t const fraction) noexcept
    {
        m_fraction = fraction;
    }

    /**
     * @brief Convert to milliseconds.
     * @return guint64_t Milliseconds of this duration.
     */
    guint64_t to_millisecond() const noexcept;

    /**
     * @brief Convert from milliseconds.
     * @param [in] ms Milliseconds used to set.
     */
    gvoid_t set_millisecond(uint64_t const ms) noexcept;

    /**
     * @brief Whether this durtion is zero.
     * @return gbool_t Whether this duration is zero.
     * @retval true This duration is zero.
     * @retval false This duration isn't zero.
     */
    inline gbool_t is_zero() const noexcept
    {
        return (m_seconds == 0) && (m_fraction == 0U);
    }

    /**
     * @brief Whether this durtion is infinite.
     * @return gbool_t Whether this duration is indinite.
     * @retval true This duration is infinite.
     * @retval false This duration isn't infinite.
     */
    inline gbool_t is_infinite() const noexcept
    {
        return (m_seconds == INIFITE_SECONDS) && (m_fraction == INIDITE_FRACTION);
    }

    /**
     * @brief Convert to microseconds.
     * @return guint64_t Microseconds of this duration.
     */
    guint64_t to_microsecond() const noexcept;

    /**
     * @brief Convert to nanoseconds.
     * @return guint64_t Nanoseconds of this duration.
     */
    guint64_t to_nanosecond() const noexcept;

    /**
     * @brief Get a zero duration.
     * @return Duration A zero Duration object.
     */
    static constexpr inline Duration duration_zero() noexcept
    {
        return {0, 0U};
    }

    /**
     * @brief Get a infinite duration.
     * @return Duration An infinite Duration object.
     */
    static constexpr inline Duration duration_infinite() noexcept
    {
        return {INIFITE_SECONDS, INIDITE_FRACTION};
    }

    /**
     * @brief Get nanosecond of this duration.
     * @return guint64_t Nanoseconds of this Duration object.
     */
    guint64_t get_nanosecond() const noexcept;

    /**
     * @brief Serialize this object.
     * @param [in] cdr A DdsCdr object reference.
     */
    inline gvoid_t serialize(DdsCdr &cdr) const noexcept
    {
        cdr.serialize(m_seconds);
        cdr.serialize(m_fraction);
        return;
    }

    /**
     * @brief Deserialize this object.
     * @param [in] cdr A DdsCdr object reference.
     */
    inline gvoid_t deserialize(DdsCdr &cdr) noexcept
    {
        cdr.deserialize(m_seconds);
        cdr.deserialize(m_fraction);
        return;
    }
private:
    static constexpr gint32_t INIFITE_SECONDS {0x7FFFFFFF};
    static constexpr guint32_t INIDITE_FRACTION {0xFFFFFFFFU};

    gint32_t m_seconds;     
    guint32_t m_fraction;
};

using Duration_t = Duration;

} /*rtps*/
} /*gstone*/

__GS_DDS4CPP_END_DECLS

#endif /*GSTONE_RTPS_DURATION_API_H*/
