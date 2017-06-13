/* 
 * Elephly. A tool for making an elephant from a fly.
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

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <boost/locale.hpp>
#include "Elephly/Elephly.h"

int main(int argc, char* argv[])
{
    /* 
     * Going C++ mode.
     */
    std::ios_base::sync_with_stdio(false);

    /*
     * Init locale from system.
     */
    boost::locale::generator gen;
    std::locale::global(std::locale { gen("") });

    /* 
     * Require 1 + 2 parameters.
     * The first cmdline parameter is a path to words file
     * (contains source and target).
     * The second cmdline parameter is a path to a dictionary file.
     */
    if (argc < 3)
        throw std::runtime_error("Insufficient parameters");

    /* 
     * Setting up the streams with words and dictionary.
     */
    std::wifstream words { argv[1] };
    std::wifstream dict { argv[2] };

    if (!words.good())
        throw std::runtime_error("Unable to read words");

    if (!dict.good())
        throw std::runtime_error("Unable to read dictionary");

    /* 
     * Init path finder.
     */
    Elephly::Elephly elephly;

    /*
     * Read the files.
     */
    words >> elephly.words();
    dict >> elephly.dict();

    /*
     * Perform a search action.
     * Will search for path from first to second word in words container
     * which are also known as source and target words.
     */
    auto path = elephly.run();

    if (path.size() == 1)
        std::wcout << "Destination unreachable" << std::endl;
    else
        std::wcout << "PATH:" << std::endl << path << std::endl;

    return 0;
}

