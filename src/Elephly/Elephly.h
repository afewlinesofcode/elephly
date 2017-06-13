#ifndef ELEPHLY_ELEPHLY_H
#define ELEPHLY_ELEPHLY_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include "Words.h"

namespace Elephly
{

class Elephly
{
public:
    using Graph = boost::adjacency_list<
                  boost::listS,
                  boost::vecS,
                  boost::undirectedS,
                  boost::no_property,
                  boost::property<boost::edge_weight_t, int>>;
    using Vertex = boost::graph_traits<Graph>::vertex_descriptor;
    using Edge = boost::graph_traits<Graph>::edge_descriptor;

    /**
     * @brief Constructor.
     */
    Elephly();

    /**
     * @brief Get source and target words container.
     * @return
     */
    Words& words()
    {
        return words_;
    }

    /**
     * @brief Get dictionary container.
     * @return
     */
    Words& dict()
    {
        return dict_;
    }

    /**
     * Find the path from source to target words.
     * @return
     */
    Words run();
private:
    /**
     * @brief Source and target words.
     */
    Words words_ {};

    /**
     * @brief Dictionary.
     */
    Words dict_ {};
}; // class Elephly

} // namespace Elephly

#endif // ELEPHLY_ELEPHLY_H

