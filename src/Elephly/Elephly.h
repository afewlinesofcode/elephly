/**
 * @file Elephly.h
 * @brief Elephly main class.
 * @author Stanislav Yaranov
 * @version 0.1
 * @date 2017-06-14
 */

#ifndef ELEPHLY_ELEPHLY_H
#define ELEPHLY_ELEPHLY_H

#include "Words.h"

namespace Elephly
{

/**
 * @brief Elephly the facade.
 */
class Elephly
{
public:
    /**
     * @brief Constructor.
     * Initialize elephly path finder.
     */
    Elephly();

    /**
     * @brief Get source and target words container.
     * @return Words container with source and target words.
     */
    Words& words()
    {
        return words_;
    }

    /**
     * @brief Get dictionary container.
     * @return Words container with dictionary.
     */
    Words& dict()
    {
        return dict_;
    }

    /**
     * @brief Find the path from source to target words.
     * @return Words container with path words.
     */
    Words run();
private:
    /**
     * @brief Source and target words container.
     */
    Words words_ {};

    /**
     * @brief Dictionary container.
     */
    Words dict_ {};
}; // class Elephly

} // namespace Elephly

#endif // ELEPHLY_ELEPHLY_H

