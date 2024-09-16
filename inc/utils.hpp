/**
 * @file utils.hpp
 *
 * @brief Utility functions
 *
 * @date 09/2024
 */

#ifndef UTILS_HPP
#define UTILS_HPP

namespace utils {

/**
* @brief Map a value from one range to another
    *
    * @param value Value to map
* @param from_low Lower bound of the input range
* @param from_high Upper bound of the input range
* @param to_low Lower bound of the output range
* @param to_high Upper bound of the output range
*
* @return Mapped value
*/
constexpr float map(float value, float from_low, float from_high, float to_low, float to_high) {
    return (value - from_low) * (to_high - to_low) / (from_high - from_low) + to_low;
}
}  // namespace utils

#endif  // UTILS_HPP
