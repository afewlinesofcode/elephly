/**
 * @file Words.h
 * @brief Words class.
 * @author Stanislav Yaranov
 * @version 0.1
 * @date 2017-06-14
 */

#ifndef ELEPHLY_H
#define ELEPHLY_H

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>
#include <limits>

namespace Elephly
{

/**
 * @brief Extended vector container for manipulating words.
 */
class Words: public std::vector<std::wstring>
{
public:
    /**
     * @brief Base class type.
     */
    using base_type = std::vector<std::wstring>;

    /**
     * @brief Container value type (a word type).
     */
    using value_type = base_type::value_type;

    /**
     * @brief Container size type.
     */
    using size_type = base_type::size_type;

    /**
     * @brief Filtering callback type.
     */
    using filter_type = std::function<bool(size_type, value_type const&)>;


    /*
     * Import base class constructors.
     */
    using base_type::base_type;

    /**
     * @brief Append element to the end.
     * @param s Appended element.
     */
    void push_back(value_type const& s);

    /**
     * @brief Add a filtering callback.
     * @param f Filtering callback.
     */
    void filter(filter_type const& f);

    /**
     * @brief Get position of a word.
     * @return Index of a word in a collection or MAX_INT of not found.
     */
    size_type find(value_type const& s);

    /**
     * @brief Read word lines from input stream.
     * @param is Stream to read from.
     * @param words Container to read into.
     * @return Same stream.
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
     * @param os Stream to write to.
     * @param words Words to output.
     * @return Same stream.
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
     * @brief Collection of filtering callbacks.
     */
    std::vector<filter_type> filters_ {};

    /**
     * @brief Test whether a string passes all filters.
     * @param s Tested string.
     * @return True if filters are passed.
     */
    bool passFilter(value_type const& s);
}; // class Words

} // namespace Elephly

#endif // ELEPHLY_H

