#define BOOST_TEST_MODULE Elephly tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <Elephly/Elephly.h>
#include "words.fixture.h"

BOOST_AUTO_TEST_SUITE(Elephly)

BOOST_AUTO_TEST_CASE(construct_isEmpty)
{
    Elephly elephly;

    BOOST_TEST(elephly.words().empty());
    BOOST_TEST(elephly.dict().empty());
}

BOOST_AUTO_TEST_CASE(readWords_variousWordsLength_onlySameLengthWordsCollected)
{
    Elephly elephly;
    WordsFixture fix { L"qwe", L"asdf", L"zxc" };
    Words expected { L"qwe", L"zxc" };

    fix.istream >> elephly.words();

    BOOST_TEST(elephly.words() == expected);
}

BOOST_AUTO_TEST_CASE(readDict_variousWordsLength_onlyWordsWithSourceWordLengthCollected)
{
    Elephly elephly;
    WordsFixture words { L"source", L"target" };
    WordsFixture dict { L"sourc1", L"word1", L"word2", L"sourc2" };
    Words expected { L"sourc1", L"sourc2" };

    words.istream >> elephly.words();
    dict.istream >> elephly.dict();

    BOOST_TEST(elephly.dict() == expected);
}

BOOST_AUTO_TEST_CASE(readDict_repeatingWords_onlyUniqueWordsCollected)
{
    Elephly elephly;
    WordsFixture words { L"abc", L"xyz" };
    WordsFixture dict { L"qwe", L"abc", L"asd", L"qwe" };
    Words expected { L"qwe", L"asd" };

    words.istream >> elephly.words();
    dict.istream >> elephly.dict();

    BOOST_TEST(elephly.dict() == expected);
}

BOOST_AUTO_TEST_CASE(run_withPossiblePath_pathIsFound)
{
    Elephly elephly;
    WordsFixture words { L"abc", L"xyz" };
    WordsFixture dict { L"abz", L"bbz", L"abx", L"xbz" };
    Words expected { L"abc", L"abz", L"xbz", L"xyz" };

    //auto path = elephly.run();

    //BOOST_TEST(path == expected);
}

BOOST_AUTO_TEST_SUITE_END()

