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

#include "utils.h"

utils::utils(){}
utils::~utils(){}

// https://stackoverflow.com/questions/8520560/get-a-file-name-from-a-path#8520871
struct MatchPathSeparator
{
	bool operator()( char ch ) const
	{
		return ch == '/';
	}
};

std::string utils::basename(const std::string &filename)
{
	return std::string( 
		std::find_if( filename.rbegin(), filename.rend(),
				MatchPathSeparator() ).base(),
			filename.end() );
}

// https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c#4654718
bool utils::is_number(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

std::string utils::getHomeDir()
{
	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	
	return std::string(homedir);
}

std::vector<std::string> utils::split(const std::string &s, char delim) 
{
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
  
	while (std::getline(ss, item, delim))
		elems.push_back(item);
	
	return elems;
}

std::string utils::replaceAll(std::string str, const std::string &from, const std::string &to)
{
	size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) 
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
