#ifndef ELEPHLY_H
#define ELEPHLY_H

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>


namespace Elephly
{

/**
 * @brief Words container.
 */
class Words: public std::vector<std::wstring>
{
public:
    /**
     * @brief Base class type.
     */
    using base_type = std::vector<std::wstring>;

    /**
     * @brief Container value type.
     */
    using value_type = base_type::value_type;

    /**
     * @brief Filtering callback type.
     */
    using filter_type = std::function<bool(size_t, value_type const&)>;

    /*
     * Import base class constructors.
     */
    using base_type::base_type;

    /**
     * @brief Append element to the end.
     * @param s
     */
    void push_back(value_type const& s);

    /**
     * @brief Add a filtering callback.
     * @param f
     */
    void filter(filter_type const& f);

    /**
     * @brief Read word lines from input stream.
     * @param is
     * @param words
     * @return 
     */
    friend std::wistream& operator>>(std::wistream& is, Words& words)
    {
        while (is.good())
        {
            std::wstring s;

            getline(is, s);
            words.push_back(s);
        }

        return is;
    }

    /**
     * @brief Write words to output stream.
     * @param os
     * @param words
     * @return 
     */
    friend std::wostream& operator<<(std::wostream& os, Words const& words)
    {
        if (words.empty())
            return os;

        os << words[0];

        std::for_each(
                words.begin() + 1,
                words.end(),
                [&os](value_type const& w)
                {
                    os << std::endl << w;
                });

        return os;
    }

private:
    /**
     * @brief Vector of filtering callbacks.
     */
    std::vector<filter_type> filters_ {};

    /**
     * @brief Test whether a string passes all filters.
     * @param s
     * @return 
     */
    bool passFilter(value_type const& s);
}; // class Words

} // namespace Elephly

#endif // ELEPHLY_H

