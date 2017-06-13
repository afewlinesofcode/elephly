/*
 * Elephly tests for testing main facade class.
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

#include <Elephly/Elephly.h>
#include "words.fixture.h"

BOOST_AUTO_TEST_SUITE(Elephly)

/**
 * @brief Is default constructable with empty words and dict collections.
 */
BOOST_AUTO_TEST_CASE(construct_byDefault_collectionsAreEmpty)
{
    Elephly elephly;

    BOOST_TEST(elephly.words().empty());
    BOOST_TEST(elephly.dict().empty());
}

/**
 * @brief Words stream data is correctly filtered while reading.
 */
BOOST_AUTO_TEST_CASE(readWords_variousLengthWords_onlySameLengthWordsAreCollected)
{
    Elephly elephly;
    WordsFixture fix { L"qwe", L"asdf", L"zxc" };
    Words expected { L"qwe", L"zxc" };

    fix.istream >> elephly.words();

    BOOST_TEST(elephly.words() == expected);
}

/**
 * @brief Dictionary data is not read unless source word is read.
 */
BOOST_AUTO_TEST_CASE(readDict_withoutReadingSourceWord_noWordIsCollectedForDict)
{
    Elephly elephly;
    WordsFixture dict { L"sourc1", L"word1", L"word2", L"sourc2" };

    dict.istream >> elephly.dict();

    BOOST_TEST(elephly.dict().empty());
}

/**
 * @brief Dictionary stream data is correctly filtered while reading.
 */
BOOST_AUTO_TEST_CASE(readDict_variousLengthWords_onlyWordsWithSourceWordLengthAreCollected)
{
    Elephly elephly;
    WordsFixture words { L"source", L"target" };
    WordsFixture dict { L"sourc1", L"word1", L"word2", L"sourc2" };
    Words expected { L"sourc1", L"sourc2" };

    words.istream >> elephly.words();
    dict.istream >> elephly.dict();

    BOOST_TEST(elephly.dict() == expected);
}

/**
 * @brief Not repeats in dictionary.
 */
BOOST_AUTO_TEST_CASE(readDict_repeatingWords_onlyUniqueWordsAreCollected)
{
    Elephly elephly;
    WordsFixture words { L"abc", L"xyz" };
    WordsFixture dict { L"qwe", L"abc", L"asd", L"qwe" };
    Words expected { L"qwe", L"asd" };

    words.istream >> elephly.words();
    dict.istream >> elephly.dict();

    BOOST_TEST(elephly.dict() == expected);
}

/**
 * @brief Search just works.
 */
BOOST_AUTO_TEST_CASE(run_withPossiblePath_pathIsFound)
{
    Elephly elephly;
    WordsFixture words { L"abc", L"xyz" };
    WordsFixture dict { L"abz", L"bbz", L"abx", L"xbz" };
    Words expected { L"abc", L"abz", L"xbz", L"xyz" };

    words.istream >> elephly.words();
    dict.istream >> elephly.dict();

    auto path = elephly.run();

    BOOST_TEST(path == expected);
}

BOOST_AUTO_TEST_SUITE_END()

