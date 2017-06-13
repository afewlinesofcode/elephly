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

