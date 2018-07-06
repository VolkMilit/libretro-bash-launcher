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

#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

class utils
{
	public:
		utils();
		~utils();
		
	protected:
		static std::string basename(const std::string &str);
		static std::string getHomeDir();
		static std::vector<std::string> split(const std::string &str, char delim);
		static bool is_number(const std::string &s);
		static std::string replaceAll(std::string str, const std::string &from, const std::string &to);
};

#endif /* __UTILS_H__ */
