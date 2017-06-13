#define BOOST_TEST_MODULE Elephly tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <Elephly/WordsGraph.h>

using namespace std;
using namespace Elephly;

BOOST_AUTO_TEST_SUITE(WordsGraphTests)

/**
 * @brief Is constructable with initializing words.
 */
BOOST_AUTO_TEST_CASE(construct_withWords_allWordsAreConcatenated)
{
    WordsGraph words{ Words { L"qwe", L"asd" }, Words { L"abc", L"def", L"ghi" } };
    Words expected = Words { L"qwe", L"asd", L"abc", L"def", L"ghi" };

    BOOST_TEST(words.words() == expected);
}

/**
 * @brief When constructed with initializing words required number of vertices
 * are created.
 */
BOOST_AUTO_TEST_CASE(construct_withWords_requiredVerticesAreCreated)
{
    WordsGraph words{ Words { L"qwe", L"asd" }, Words { L"abc", L"def", L"ghi" } };

    BOOST_TEST(num_vertices(words.graph()) == 5);
}

/**
 * @brief Words differing with only one letter are neighbours.
 */
BOOST_AUTO_TEST_CASE(neighbours_wordsDifferWithOneLetter_returnsTrue)
{
    BOOST_TEST(WordsGraph::neighbours(L"asd", L"axd"));
}

/**
 * @brief Words differing with more than one letter are not neighbours.
 */
BOOST_AUTO_TEST_CASE(neighbours_wordsDifferWithMoreThanOneLetter_returnsFalse)
{
    BOOST_TEST(!WordsGraph::neighbours(L"asd", L"sxd"));
}

/**
 * @brief Words that are equal are not neighbours.
 */
BOOST_AUTO_TEST_CASE(neighbours_wordsEqual_returnsFalse)
{
    BOOST_TEST(!WordsGraph::neighbours(L"asd", L"asd"));
}

/**
 * @brief Words of different length are not neighbours.
 */
BOOST_AUTO_TEST_CASE(neighbours_wordsWithDifferentLength_returnsFalse)
{
    BOOST_TEST(!WordsGraph::neighbours(L"asx", L"asdx"));
}

/**
 * @brief When constructed with words required edges are created.
 */
BOOST_AUTO_TEST_CASE(construct_withWords_requiredEdgesAreCreated)
{
    WordsGraph words{ Words { L"qwe", L"ewq" }, Words { L"qwq", L"wwe" } };
    auto& g = words.graph();

    BOOST_TEST(num_edges(g) == 3);
    BOOST_TEST(boost::edge(vertex(0, g), vertex(2, g), g).second);
    BOOST_TEST(boost::edge(vertex(0, g), vertex(3, g), g).second);
    BOOST_TEST(boost::edge(vertex(1, g), vertex(2, g), g).second);
}

BOOST_AUTO_TEST_CASE(search_unknownWord_throws)
{
    WordsGraph w { Words { L"abc", L"xyz" }, Words { L"abz", L"bbz", L"abx", L"xbz" } };

    BOOST_CHECK_THROW(w.search(L"aaa"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(search_withPossiblePath_pathIsFound)
{
    WordsGraph w { Words { L"abc", L"xyz" }, Words { L"abz", L"bbz", L"fgh", L"abx", L"xbz" } };
    Words expected { L"abc", L"abz", L"xbz", L"xyz" };

    w.search(L"abc");

    BOOST_TEST(w.path(L"xyz") == expected);
}

BOOST_AUTO_TEST_SUITE_END()

