/*
 * Elephly tests for words graph util.
 * Copyright (C)
 * 2017 - Stanislav Yaranov
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#define BOOST_TEST_MODULE Elephly tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <Elephly/WordsGraph.h>

BOOST_AUTO_TEST_SUITE(WordsGraphTests)

/**
 * @brief Is constructable with initializing words and initializing words
 *        are correctly concatenated.
 */
BOOST_AUTO_TEST_CASE(construct_withWords_allWordsAreConcatenated)
{
    Elephly::WordsGraph words
    {
        Elephly::Words { L"qwe", L"asd" },
        Elephly::Words { L"abc", L"def", L"ghi" }
    };

    Elephly::Words expected = Elephly::Words { L"qwe", L"asd", L"abc", L"def",
                   L"ghi" };

    BOOST_TEST(words.words() == expected);
}

/**
 * @brief When constructed with initializing words required number of vertices
 *        are created.
 */
BOOST_AUTO_TEST_CASE(construct_withWords_requiredVerticesAreCreated)
{
    Elephly::WordsGraph words
    {
        Elephly::Words { L"qwe", L"asd" },
        Elephly::Words { L"abc", L"def", L"ghi" }
    };

    BOOST_TEST(num_vertices(words.graph()) == 5);
}

/**
 * @brief Words differing with only one letter are neighbours.
 */
BOOST_AUTO_TEST_CASE(neighbours_wordsDifferWithOneLetter_returnsTrue)
{
    BOOST_TEST(Elephly::WordsGraph::neighbours(L"asd", L"axd"));
}

/**
 * @brief Words differing with more than one letter are not neighbours.
 */
BOOST_AUTO_TEST_CASE(neighbours_wordsDifferWithMoreThanOneLetter_returnsFalse)
{
    BOOST_TEST(!Elephly::WordsGraph::neighbours(L"asd", L"sxd"));
}

/**
 * @brief Words that are equal are not neighbours.
 */
BOOST_AUTO_TEST_CASE(neighbours_wordsEqual_returnsFalse)
{
    BOOST_TEST(!Elephly::WordsGraph::neighbours(L"asd", L"asd"));
}

/**
 * @brief Words of different length are not neighbours.
 */
BOOST_AUTO_TEST_CASE(neighbours_wordsWithDifferentLength_returnsFalse)
{
    BOOST_TEST(!Elephly::WordsGraph::neighbours(L"asx", L"asdx"));
}

/**
 * @brief When constructed with words required edges are created.
 */
BOOST_AUTO_TEST_CASE(construct_withWords_requiredEdgesAreCreated)
{
    Elephly::WordsGraph words
    {
        Elephly::Words { L"qwe", L"ewq" },
        Elephly::Words { L"qwq", L"wwe" }
    };

    auto& g = words.graph();

    BOOST_TEST(num_edges(g) == 3);
    BOOST_TEST(boost::edge(vertex(0, g), vertex(2, g), g).second);
    BOOST_TEST(boost::edge(vertex(0, g), vertex(3, g), g).second);
    BOOST_TEST(boost::edge(vertex(1, g), vertex(2, g), g).second);
}

/**
 * @brief When try to search from unknown word exception is thrown.
 */
BOOST_AUTO_TEST_CASE(search_fromUnknownWord_throws)
{
    Elephly::WordsGraph w
    {
        Elephly::Words { L"abc", L"xyz" },
        Elephly::Words { L"abz", L"bbz", L"abx", L"xbz" }
    };

    BOOST_CHECK_THROW(w.search(L"aaa"), std::runtime_error);
}

/**
 * @brief When search is possible correct path is returned.
 */
BOOST_AUTO_TEST_CASE(search_withPossiblePath_pathIsReturned)
{
    Elephly::WordsGraph w
    {
        Elephly::Words { L"abc", L"xyz" },
        Elephly::Words { L"abz", L"bbz", L"fgh", L"abx", L"xbz" }
    };

    Elephly::Words expected { L"abc", L"abz", L"xbz", L"xyz" };

    w.search(L"abc");

    BOOST_TEST(w.path(L"xyz") == expected);
}

/**
 * @brief When search is possible correct path is returned.
 */
BOOST_AUTO_TEST_CASE(search_whenSourceIsEqualToTarget_trivialPathIsReturned)
{
    Elephly::WordsGraph w
    {
        Elephly::Words { L"abc", L"abc" },
        Elephly::Words { L"abz", L"bbz", L"fgh", L"abx", L"xbz" }
    };

    Elephly::Words expected { L"abc", L"abc" };

    w.search(L"abc");

    BOOST_TEST(w.path(L"abc") == expected);
}

BOOST_AUTO_TEST_SUITE_END()

