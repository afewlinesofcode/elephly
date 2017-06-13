#ifndef ELEPHLY_WORDSGRAPH_H
#define ELEPHLY_WORDSGRAPH_H

#include <iterator>
#include <algorithm>
#include <utility>
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
     * @brief Graph type.
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
     * @brief Default constructor is deleted since graph shoud not be empty.
     */
    WordsGraph() = delete;

    /**
     * @brief Get words collection.
     * @return
     */
    Words const& words() const
    {
        return words_;
    }

    /**
     * @brief Get processing graph.
     * @return 
     */
    Graph const& graph() const
    {
        return graph_;
    }

    /**
     * @brief Create object from words.
     * @param words
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
     * @brief Get a path to specified word from calculated data.
     * @param to
     * @return
     */
    Words path(Words::value_type const& to);

    /**
     * @brief Whether two words are neighbours.
     * @param lhs
     * @param rhs
     * @return 
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
     * Graph vertices index.
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
     * @brief Initialize graph from words.
     */
    void initGraph();

    /**
     * @brief Append specified words to words collection.
     */
    template<typename W, typename ...T>
    void append(W const& w, T const&... words)
    {
        append(w);
        append(words...);
    }

    /**
     * @brief Append specified words to words collection.
     */
    void append(Words const& w);
}; // class WordsGraph

}; // namespace Elephly

#endif // ELEPHLY_WORDSGRAPH_H

