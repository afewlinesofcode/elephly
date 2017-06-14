/**
 * @file Words.cc
 * @brief Words class.
 * @author Stanislav Yaranov
 * @version 0.1
 * @date 2017-06-14
 */

#include "Words.h"

namespace Elephly
{

/**
 * @brief Append element to the end.
 * @param s Appended element.
 */
void Words::push_back(value_type const& s)
{
    if (passFilter(s))
    {
        base_type::push_back(s);
    }
}

/**
 * @brief Add a filtering callback.
 * @param f Filtering callback.
 */
void Words::filter(filter_type const& f)
{
    filters_.push_back(f);
}

/**
 * @brief Get position of a word.
 * @return Index of a word in a collection or MAX_INT if not found.
 */
Words::size_type Words::find(value_type const& s)
{
    auto it = std::find(begin(), end(), s);

    if (it == end())
    {
        return std::numeric_limits<size_type>::max();
    }

    return std::distance(begin(), it);
}

/**
 * @brief Test whether a string passes all filters.
 * @param s Tested string.
 * @return True if filters are passed.
 */
bool Words::passFilter(value_type const& s)
{
    if (filters_.empty())
        return true;

    const auto pos = size();

    auto ret = std::find_if_not(
                   filters_.begin(),
                   filters_.end(),
                   [pos, s](filter_type const& f)
    {
        return f(pos, s);
    });

    return ret == filters_.end();
}

} // namespace Elephly

