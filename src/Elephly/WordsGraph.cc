#include "WordsGraph.h"

#include <boost/graph/dijkstra_shortest_paths.hpp>

namespace Elephly
{

/**
 * @brief Perform djikstra search from starting word to all other words.
 * @param from Starting word to search from.
 */
void WordsGraph::search(Words::value_type const& from)
{
    auto it = std::find(words_.begin(), words_.end(), from);

    if (it == words_.end())
        throw std::runtime_error("Specified word is not in the collection");

    // Init collections for calculated data

    auto p_map = make_iterator_property_map(
                     predecessors_.begin(),
                     boost::get(boost::vertex_index, graph_)
                 );

    auto d_map = make_iterator_property_map(
                     distances_.begin(),
                     boost::get(boost::vertex_index, graph_)
                 );

    // Perform search
    boost::dijkstra_shortest_paths(
        graph_,
        boost::vertex(std::distance(words_.begin(), it), graph_),
        boost::predecessor_map(p_map).distance_map(d_map));
}

/**
 * @brief Get a path to specified word from calculated data.
 * @param to
 * @return
 */
Words WordsGraph::path(Words::value_type const& to)
{
    Words path { to };
    auto pos = words_.find(to);
    using Pos = decltype(pos);

    // Test if the word is know.
    if (pos == std::numeric_limits<Pos>::max())
        return path;

    // Collect path from predecessors collection.
    for (Pos p = vertexIndex_[predecessors_[pos]]; p != pos;
            pos = p, p = vertexIndex_[predecessors_[pos]])
        path.push_back(words_[p]);

    // Since collecting from the end doing a reverse.
    std::reverse(path.begin(), path.end());

    return path;
}

/**
 * @brief Whether two words are neighbours.
 * @param lhs
 * @param rhs
 * @return
 */
bool WordsGraph::neighbours(Words::value_type const& lhs,
                            Words::value_type const& rhs)
{
    size_t counter = 0;

    // Must be equal size.
    if (lhs.size() != rhs.size())
        return false;

    for (auto lit = lhs.begin(), rit = rhs.begin();
            lit != lhs.end(); ++lit, ++rit)
    {
        if (*lit != *rit)
        {
            ++counter;

            // Too many diffs.
            if (counter > 1)
                return false;
        }
    }

    // Only one diff is allowed.
    return counter == 1;
}

/**
 * @brief Initialize graph from words.
 */
void WordsGraph::initGraph()
{
    // Init graph object with required amount of vertices.
    graph_ = Graph { words_.size() };

    // Init vertices index.
    vertexIndex_ = boost::get(boost::vertex_index, graph_);

    // Add edges for all neighbours.
    for (size_t pos = 0, count = words_.size(); pos < count; ++pos)
    {
        auto& word = words_[pos];
        auto v = boost::vertex(pos, graph_);

        for (size_t i = 0; i < pos; ++i)
        {
            if (neighbours(words_[i], word))
                add_edge(boost::vertex(i, graph_), v, { 1 }, graph_);
        }
    }

    // Init vectors for future results.
    distances_.resize(words_.size());
    predecessors_.resize(words_.size());

}

/**
 * @brief Append specified words to words collection.
 */
void WordsGraph::append(Words const& w)
{
    std::copy(w.begin(), w.end(), std::back_inserter(words_));
}

}; // namespace Elephly

