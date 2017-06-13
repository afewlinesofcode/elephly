/**
 * @file WordsGraph.h
 * @brief WordsGraph class.
 * @author Stanislav Yaranov
 * @version 0.1
 * @date 2017-06-14
 */

#ifndef ELEPHLY_WORDSGRAPH_H
#define ELEPHLY_WORDSGRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>

#include "Words.h"

namespace Elephly
{

/**
 * @brief Path finder for words using graph utils.
 */
class WordsGraph
{
public:
    /**
     * @brief Graph type to be used.
     */
    using Graph = boost::adjacency_list<
                  boost::listS,
                  boost::vecS,
                  boost::undirectedS,
                  boost::no_property,
                  boost::property<boost::edge_weight_t, int>>;

    /**
     * @brief Vertex type.
     */
    using Vertex = boost::graph_traits<Graph>::vertex_descriptor;

    /**
     * @brief Vertex index type.
     */
    using VertexIndex = boost::property_map<Graph, boost::vertex_index_t>::type;

    /**
     * @brief Default constructor is deleted
     * as normally graph should not be empty.
     */
    WordsGraph() = delete;

    /**
     * @brief Get words collection.
     * @return Words collection.
     */
    Words const& words() const
    {
        return words_;
    }

    /**
     * @brief Get processing graph.
     * @return Processing graph.
     */
    Graph const& graph() const
    {
        return graph_;
    }

    /**
     * @brief Constructor.
     * Create object from words.
     * @param words Words collections to build graph from.
     */
    template<typename ...T>
    WordsGraph(T const&... words)
    {
        append(words...);
        initGraph();
    }

    /**
     * @brief Perform djikstra search from starting word to all other words.
     * @param from Starting word to search from.
     */
    void search(Words::value_type const& from);

    /**
     * @brief Get a path to specified word from previously calculated data.
     * @param to A target word.
     * @return Words collection with a path.
     */
    Words path(Words::value_type const& to);

    /**
     * @brief Whether two words are neighbours.
     * @param lhs
     * @param rhs
     * @return True if lhs and lhs are same length and
     *         differ with only one letter.
     */
    static bool neighbours(Words::value_type const& lhs,
                           Words::value_type const& rhs);

private:
    /**
     * @brief Words collection.
     */
    Words words_ {};

    /**
     * @brief Processing graph.
     */
    Graph graph_ {};

    /**
     * @brief Graph vertices index.
     * Will make it possible to get index of a vertex from its descriptor.
     */
    VertexIndex vertexIndex_;

    /**
     * @brief Calculated distances.
     */
    std::vector<int> distances_ {};

    /**
     * @brief Calculated predecessors.
     */
    std::vector<Vertex> predecessors_ {};

    /**
     * @brief A word the last search was performed from.
     */
    Words::value_type from_;

    /**
     * @brief Initialize graph from words.
     */
    void initGraph();

    /**
     * @brief Append words from a list of words collections.
     * @param w Words collection to append words from.
     * @param words Other words collections to append words from.
     */
    template<typename W, typename ...T>
    void append(W const& w, T const&... words)
    {
        append(w);
        append(words...);
    }

    /**
     * @brief Append words from single words collection.
     * @param w Words collection to append words from.
     */
    void append(Words const& w);
}; // class WordsGraph

}; // namespace Elephly

#endif // ELEPHLY_WORDSGRAPH_H

