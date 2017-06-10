#define BOOST_TEST_MODULE Elephly tests
#include <boost/test/included/unit_test.hpp>

#include <sstream>

#include <Elephly/Words.h>

using namespace std;
using namespace Elephly;

/**
 * @brief Fixture for testing working with streams.
 */
struct WordsFixture
{
    /**
     * @brief Strings list to build a stream from and to compare against.
     */
    vector<wstring> strings
    {
        L"first word",
        L"second word",
        L"third word"
    };

    /**
     * @brief Tested stream.
     */
    wistringstream istream;

    /**
     * @brief Built stream string.
     */
    wstring streamString;

    /**
     * @brief Initialize fixture.
     */
    WordsFixture()
    {
        streamString = strings[0];

        for_each(strings.begin() + 1, strings.end(),
                 [this](wstring const& s)
        {
            streamString.append(L"\n" + s);
        });

        istream.str(streamString);
    }
};

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
 * @brief Words are read and in valid order.
 */
BOOST_AUTO_TEST_CASE(readStream_wordsAreRead)
{
    Words words;
    WordsFixture fix;

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
 * @brief Filter callback received valid values.
 */
BOOST_AUTO_TEST_CASE(readStream_assignedFilter_filterReceivesValues)
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
    WordsFixture fix;

    words.filter([&fix](size_t pos, wstring const& s)
    {
        return s != fix.strings[1];
    });

    fix.istream >> words;

    BOOST_TEST(words.size() == 2);
    BOOST_TEST(words[0] == fix.strings[0]);
    BOOST_TEST(words[1] == fix.strings[2]);
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

