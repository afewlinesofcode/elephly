#include "Words.h"

namespace Elephly
{

/**
 * @brief Append element to the end.
 * @param s
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
 * @param f
 */
void Words::filter(filter_type const& f)
{
    filters_.push_back(f);
}

/**
 * @brief Test whether a string passes all filters.
 * @param s
 * @return
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

