#include "Words.h"

namespace Elephly
{

void Words::filter(filter_type const& f)
{
    filters_.emplace_back(f);
}

bool Words::passFilter(std::wstring const& s)
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

