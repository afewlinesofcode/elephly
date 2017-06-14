/**
 * @file WordsGraph.cc
 * @brief WordsGraph class.
 * @author Stanislav Yaranov
 * @version 0.1
 * @date 2017-06-14
 */

#include "WordsGraph.h"

#include <iterator>
#include <algorithm>
#include <boost/graph/dijkstra_shortest_paths.hpp>

namespace Elephly
{

/**
 * @brief Perform djikstra search from starting word to all other words.
 * @param from Starting word to search from.
 */
void WordsGraph::search(Words::value_type const& from)
{
    /*
     * Check for the word is in the collection.
     */

    auto it = std::find(words_.begin(), words_.end(), from);

    if (it == words_.end())
        throw std::runtime_error("Specified word is not in the collection");

    /*
     * Init collections for calculation results.
     */

    auto p_map = boost::make_iterator_property_map(
                     predecessors_.begin(),
                     boost::get(boost::vertex_index, graph_)
                 );

    auto d_map = boost::make_iterator_property_map(
                     distances_.begin(),
                     boost::get(boost::vertex_index, graph_)
                 );

    /*
     * Perform a search.
     */
    boost::dijkstra_shortest_paths(
        graph_,
        boost::vertex(std::distance(words_.begin(), it), graph_),
        boost::predecessor_map(p_map).distance_map(d_map));

    from_ = from;
}

/**
 * @brief Get a path to specified word from previously calculated data.
 * @param to A target word.
 * @return Words collection with a path.
 */
Words WordsGraph::path(Words::value_type const& to)
{
    /**
     * @brief The path will be collected here.
     */
    Words path { to };

    /*
     * Handle special case for path to itself.
     */
    if (to == from_)
    {
        path.push_back(from_);
        return path;
    }

    /**
     * @brief Index for a word in the collection.
     */
    auto pos = words_.find(to);

    /*
     * Test if the word is known.
     */
    if (pos == std::numeric_limits<decltype(pos)>::max())
        return path;

    /*
     * Collect path from previously calculated predecessors collection.
     */
    for (decltype(pos) p = vertexIndex_[predecessors_[pos]]; p != pos;
            pos = p, p = vertexIndex_[predecessors_[pos]])
        path.push_back(words_[p]);

    /*
     * Since words were collected from target to source need to reverse.
     */
    std::reverse(path.begin(), path.end());

    return path;
}

/**
 * @brief Whether the two words are neighbours.
 * @param lhs
 * @param rhs
 * @return True if lhs and lhs are same length and
 *         differ with only one letter.
 */
bool WordsGraph::neighbours(Words::value_type const& lhs,
                            Words::value_type const& rhs)
{
    /**
     * @brief Diffs counter.
     */
    size_t counter = 0;

    /*
     * Must be equal length.
     */
    if (lhs.size() != rhs.size())
        return false;

    /*
     * Walk through chars.
     */
    for (auto lit = lhs.begin(), rit = rhs.begin();
            lit != lhs.end(); ++lit, ++rit)
    {
        if (*lit != *rit)
        {
            ++counter;

            /*
             * Too many diffs.
             */
            if (counter > 1)
                return false;
        }
    }

    /*
     * Only one diff is what we need.
     */
    return counter == 1;
}

/**
 * @brief Initialize graph from words.
 */
void WordsGraph::initGraph()
{
    /*
     * Init graph object with required amount of vertices.
     */
    graph_ = Graph { words_.size() };

    /*
     * Init vertices index.
     */
    vertexIndex_ = boost::get(boost::vertex_index, graph_);

    /*
     * Add edges for all neighbours.
     * Every next word ...
     */
    for (size_t pos = 0, count = words_.size(); pos < count; ++pos)
    {
        /**
         * @brief The word.
         */
        auto& word = words_[pos];

        /**
         * @brief The word's descriptor.
         */
        auto v = boost::vertex(pos, graph_);

        /*
         * ... is compared with all previous words.
         */
        for (size_t i = 0; i < pos; ++i)
        {
            if (neighbours(words_[i], word))
                add_edge(boost::vertex(i, graph_), v, { 1 }, graph_);
        }
    }

    /*
     * Init containers for future calculated results.
     */

    distances_.resize(words_.size());
    predecessors_.resize(words_.size());

}

/**
 * @brief Append words from single words collection.
 * @param w Words collection to append words from.
 */
void WordsGraph::append(Words const& w)
{
    std::copy(w.begin(), w.end(), std::back_inserter(words_));
}

}; // namespace Elephly

