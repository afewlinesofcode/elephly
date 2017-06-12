#define BOOST_TEST_MODULE Elephly tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <sstream>

#include <Elephly/Words.h>
#include "words.fixture.h"

using namespace std;
using namespace Elephly;

BOOST_AUTO_TEST_SUITE(ElephlyWords)

/**
 * @brief Is constructable and initialized empty.
 */
BOOST_AUTO_TEST_CASE(construct_isEmpty)
{
    Words words;

    BOOST_TEST(words.empty());
}

/**
 * @brief Words have been read in valid order.
 */
BOOST_AUTO_TEST_CASE(readStream_allWordsHaveBeenRead)
{
    Words words;
    WordsFixture fix {};

    fix.istream >> words;

    // Same words count test
    BOOST_TEST(fix.strings.size() == words.size());

    for (size_t i = 0; i < words.size(); ++i)
    {
        // Same words order test
        BOOST_TEST(fix.strings[i] == words[i]);
    }
}

/**
 * @brief Filtering callback received valid values.
 */
BOOST_AUTO_TEST_CASE(readStream_assignedFilter_filterReceivesValidValues)
{
    Words words;
    WordsFixture fix;
    size_t index = 0;

    words.filter([&fix, &index](size_t pos, wstring const& s)
    {
        BOOST_TEST(pos == index++);
        BOOST_TEST(s == fix.strings[pos]);

        return true;
    });

    fix.istream >> words;
}

/**
 * @brief Assigned filter is applied.
 */
BOOST_AUTO_TEST_CASE(readStream_assignedFilter_wordsAreFiltered)
{
    Words words;
    WordsFixture fix { L"qwe", L"asd", L"zxc" };
    Words expected { L"qwe", L"zxc" };

    words.filter([&fix](size_t pos, wstring const& s)
    {
        return s != fix.strings[1];
    });

    fix.istream >> words;

    BOOST_TEST(words == expected);
}

/**
 * @brief Writes to stream valid data.
 */
BOOST_AUTO_TEST_CASE(writeStream_fromFixture_outputIsValid)
{
    Words words;
    WordsFixture fix;
    wostringstream os;

    fix.istream >> words;
    os << words;

    BOOST_TEST(os.str() == fix.streamString);
}

BOOST_AUTO_TEST_SUITE_END()

