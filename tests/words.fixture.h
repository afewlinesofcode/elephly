/* 
 * A words collection fixture with some mock data to be used in tests.
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

#ifndef WORDS_FIXTURE_H
#define WORDS_FIXTURE_H

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

/**
 * @brief Fixture for testing streams.
 */
struct WordsFixture
{
    /**
     * @brief A list of strings to build a stream from and to compare against.
     */
    std::vector<std::wstring> strings;

    /**
     * @brief Tested stream.
     */
    std::wistringstream istream;

    /**
     * @brief Built stream string.
     */
    std::wstring streamString;

    /**
     * @brief Default constructor.
     */
    WordsFixture()
        : WordsFixture { L"first word", L"second word", L"third word" }
    {
    }

    /**
     * @brief Initialize from initializer list.
     * @param words
     */
    WordsFixture(std::initializer_list<std::wstring> words)
        : WordsFixture { std::vector<std::wstring> { words } }
    {
    }

    /**
     * @brief Initialize with specified words.
     * @param words
     */
    WordsFixture(std::vector<std::wstring> const& words)
    {
        strings = words;
        streamString = strings[0];

        std::for_each(strings.begin() + 1, strings.end(),
                 [this](std::wstring const& s)
        {
            streamString.append(L"\n" + s);
        });

        istream.str(streamString);
    }
};

#endif // WORDS_FIXTURE_H

