/**
 * @file Elephly.cc
 * @brief Elephly main class.
 * @author Stanislav Yaranov
 * @version 0.1
 * @date 2017-06-14
 */

#include "Elephly.h"

#include "WordsGraph.h"

namespace Elephly
{

/**
 * @brief Constructor.
 * Initialize elephly path finder.
 */
Elephly::Elephly()
{
    /*
     * Initialize filter for source and target words container
     * to accept first word of arbitrary length and
     * other words with length equal to the length of the first one.
     */
    words_.filter([this](size_t pos, std::wstring const& s)
    {
        /*
         * No empty words.
         */
        if (s.empty())
            return false;

        /*
         * Target words must be same length as source word.
         */
        if (pos)
            return s.size() == words_[0].size();

        return true;
    });

    /*
     * Initialize filter for dictionary container to accept
     * only words with length equal to the length of the source word.
     */
    dict_.filter([this](size_t pos, std::wstring const& s)
    {
        /*
         * No empty strings.
         */
        if (s.empty())
            return false;

        /*
         * Fill the dictionary when only source word is defined.
         */
        if (words_.empty())
            return false;

        /*
         * Fill the dictionary with words which length is equal
         * to source word length.
         */
        if (s.size() != words_[0].size())
            return false;

        /*
         * Words must be unique across both containers.
         */
        return
            find(words_.begin(), words_.end(), s) == words_.end() &&
            find(dict_.begin(), dict_.end(), s) == dict_.end();
    });
}

/**
 * @brief Find the path from source to target words.
 * @return Words container with path words.
 */
Words Elephly::run()
{
    /*
     * Pre-condition.
     */

    if (words_.size() < 2)
        throw std::runtime_error("Missing source or target word");

    if (dict_.empty())
        throw std::runtime_error("Dictionary is empty");

    /*
     * Work.
     */

    WordsGraph g { words_, dict_ };

    g.search(words_[0]);

    return g.path(words_[1]);
}

} // namespace Elephly

