/* 
 * Elephly tests for words collection.
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

#include <sstream>

#include <Elephly/Words.h>
#include "words.fixture.h"

BOOST_AUTO_TEST_SUITE(ElephlyWords)

/**
 * @brief Is constructable and initialized empty.
 */
BOOST_AUTO_TEST_CASE(construct_byDefault_collectionIsEmpty)
{
    Elephly::Words words;

    BOOST_TEST(words.empty());
}

/**
 * @brief Words have been read from stream in valid order.
 */
BOOST_AUTO_TEST_CASE(readStream_someWords_allWordsAreReadInSameOrder)
{
    Elephly::Words words;
    WordsFixture fix {};

    fix.istream >> words;

    /*
     * Same words count test.
     */
    BOOST_TEST(fix.strings.size() == words.size());

    for (size_t i = 0; i < words.size(); ++i)
    {
        /*
         * Same words order test.
         */
        BOOST_TEST(fix.strings[i] == words[i]);
    }
}

/**
 * @brief Filtering callback received valid values.
 */
BOOST_AUTO_TEST_CASE(readStream_withAssignedFilter_filterReceivesValidValues)
{
    Elephly::Words words;
    WordsFixture fix;
    size_t index = 0;

    words.filter([&fix, &index](size_t pos, std::wstring const& s)
    {
        /*
         * `pos` is incremented each time.
         */
        BOOST_TEST(pos == index++);

        /*
         * `s` refers to a valid corresponding string.
         */
        BOOST_TEST(s == fix.strings[pos]);

        return true;
    });

    /*
     * Initiate filter callback.
     */
    fix.istream >> words;
}

/**
 * @brief Assigned filter is applied.
 */
BOOST_AUTO_TEST_CASE(readStream_withAssignedFilter_wordsAreFilteredAsExpected)
{
    Elephly::Words words;
    WordsFixture fix { L"qwe", L"asd", L"zxc" };
    Elephly::Words expected { L"qwe", L"zxc" };

    words.filter([&fix](size_t pos, std::wstring const& s)
    {
        return s != L"asd";
    });

    fix.istream >> words;

    BOOST_TEST(words == expected);
}

/**
 * @brief Writes to stream all words in valid order.
 */
BOOST_AUTO_TEST_CASE(writeStream_fromFixture_outputIsAsExpected)
{
    Elephly::Words words;
    WordsFixture fix;
    std::wostringstream os;

    fix.istream >> words;
    os << words;

    BOOST_TEST(os.str() == fix.streamString);
}

/**
 * Returns index of an existing word in the collection.
 */
BOOST_AUTO_TEST_CASE(find_existingWord_returnsWordIndex)
{
    Elephly::Words words { L"qwe", L"asd", L"zxc" };

    BOOST_TEST(words.find(L"asd") == 1);
}

/**
 * Returns MAX_INT if word is not in the collection.
 */
BOOST_AUTO_TEST_CASE(find_notExistingWord_returnsLimit)
{
    Elephly::Words words { L"qwe", L"asd", L"zxc" };

    BOOST_TEST(words.find(L"asdq") == std::numeric_limits<size_t>::max());
}

BOOST_AUTO_TEST_SUITE_END()

