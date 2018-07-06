/*
    Libretro Sh Launcher - allow you to launch (ba)sh scripts throught Retroarch.
    Copyright (C) 2018 Volk_Milit (aka Ja'Virr-Dar)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef __PLAYLIST_GENERATOR_H__
#define __PLAYLIST_GENERATOR_H__

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

#if __GNUC__ == 6
#include <experimental/filesystem>
#else
#include <filesystem>
#endif

#include "utils.h"
#include "third-party/crc/crc.h"

namespace fs = std::experimental::filesystem;

class playlist_generator : public utils, public crc
{
	public:
		playlist_generator();
		~playlist_generator();
	
		void generate();
};

#endif //__PLAYLIST_GENERATOR_H__
