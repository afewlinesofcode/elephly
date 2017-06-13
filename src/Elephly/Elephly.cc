#include "Elephly.h"

#include <iostream>

#include "WordsGraph.h"

namespace Elephly
{

using namespace std;
using namespace boost;

Elephly::Elephly()
{
    words_.filter([this](size_t pos, wstring const& s)
    {
        // no empty words
        if (s.empty())
            return false;

        // target words must be same length as source word
        if (pos)
            return s.size() == words_[0].size();

        return true;
    });

    dict_.filter([this](size_t pos, wstring const& s)
    {
        // no empty strings
        if (s.empty())
            return false;

        // fill the dictionary when only source word is defined
        if (words_.empty())
            return false;

        // fill the dictionary with words which length is equal to source word length
        if (s.size() != words_[0].size())
            return false;

        return
            find(words_.begin(), words_.end(), s) == words_.end() &&
            find(dict_.begin(), dict_.end(), s) == dict_.end();
    });
}

/**
 * Find the path from source to target words.
 * @return
 */
Words Elephly::run()
{
    if (words_.size() < 2)
        throw std::runtime_error("Missing source or target word");

    if (dict_.empty())
        throw std::runtime_error("Dictionary is empty");

    WordsGraph g { words_, dict_ };

    g.search(words_[0]);

    return g.path(words_[1]);
}

} // namespace Elephly

