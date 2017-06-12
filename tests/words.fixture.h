#ifndef WORDS_FIXTURE_H
#define WORDS_FIXTURE_H

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

/**
 * @brief Fixture for testing streams.
 */
struct WordsFixture
{
    /**
     * @brief A list of strings to build a stream from and to compare against.
     */
    vector<wstring> strings;

    /**
     * @brief Tested stream.
     */
    wistringstream istream;

    /**
     * @brief Built stream string.
     */
    wstring streamString;

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
    WordsFixture(initializer_list<wstring> words)
        : WordsFixture { vector<wstring> { words } }
    {
    }

    /**
     * @brief Initialize with specified words.
     * @param words
     */
    WordsFixture(vector<wstring> const& words)
    {
        strings = words;
        streamString = strings[0];

        for_each(strings.begin() + 1, strings.end(),
                 [this](wstring const& s)
        {
            streamString.append(L"\n" + s);
        });

        istream.str(streamString);
    }
};

#endif // WORDS_FIXTURE_H

