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

#include <iostream>
#include <Imlib2.h>

#if __GNUC__ == 6
#include <experimental/filesystem>
#else
#include <filesystem>
#endif

#include "utils.h"

namespace fs = std::experimental::filesystem;

class art : public utils
{
	public:
		art();
		~art();
		
		void convert(const std::string &file, const std::string &name);
		void copyart(const std::string &file, const std::string &name);
		
	private:
		bool checkFormat(const std::string &file);
		
		std::string nb = getHomeDir() + "/.config/retroarch/thumbnails/Bash - Sh Launcher - PC/Named_Boxarts/";
		std::string ns = getHomeDir() + "/.config/retroarch/thumbnails/Bash - Sh Launcher - PC/Named_Snaps/";
		std::string nt = getHomeDir() + "/.config/retroarch/thumbnails/Bash - Sh Launcher - PC/Named_Titles/";
		
		Imlib_Image image;
};
