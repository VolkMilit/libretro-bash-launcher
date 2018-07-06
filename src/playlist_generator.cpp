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

#include "playlist_generator.h"
#include "art.h"

#include "third-party/ftlip/ftlip.h"
#include "third-party/https-downloader/HTTPDownloader.hpp"

playlist_generator::playlist_generator(){}
playlist_generator::~playlist_generator(){}

void playlist_generator::generate()
{
    const std::string HOME = getHomeDir();

	const std::string &ra_config = HOME + "/.config/retroarch/retroarch.cfg";
	ftlip playlist(ra_config);
	std::string playlist_path_tmp = playlist.get("playlist_directory");
	std::string playlist_path = playlist_path_tmp.substr(2, playlist_path_tmp.size()-3);
	
	// where config must be
    const std::string &config = HOME + "/.config/retroarch/sh-launcher.cfg";
	
	ftlip ini(config);
	const std::string &path = ini.get("path");
	
    // where playlist must be
    std::string playlists = playlist_path + "/Bash - Sh Launcher - PC.lpl";
    playlists = utils::replaceAll(playlists, "~", HOME); // C++14\17 filesystem doesn't know about ~
    
    std::ofstream oplst(playlists, std::ios_base::app);
    if (!fs::exists(playlists)) // create new playlist, otherwise it will fail
		oplst << "";
	
	unsigned int crcnum = 0;
	
	const std::string &cached_s = ini.get("cached");
	std::vector<std::string> cached = split(cached_s, ' ');
	
	art a;
	HTTPDownloader dwnl;
	
	for (auto & p : fs::directory_iterator(path))
    {
        if(is_directory(p.path()))
            continue;

		ftlip sh(p.path());
		
		std::string NAME = sh.get("NAME");
		std::string ART = sh.get("ART");
		
		std::string fpath = p.path();
		fpath.substr(1, fpath.size()-2);
		
		std::string NAMEs = basename(fpath);
		if (NAME != "")
			NAMEs = NAME.substr(1, NAME.size()-2); // remove " symbols

        std::string current = fs::current_path();
        current.substr(1, current.size()-2);
		
		if (ART != "")
		{
			ART = ART.substr(1, ART.size()-2);
			
			if (!is_number(ART)) // doesn't steam id
			{
				a.convert(ART, NAMEs);
			}
			else // steam id
			{
                dwnl.download("http://cdn.edgecast.steamstatic.com/steam/apps/" + ART + "/header.jpg",\
                              "/tmp/" + NAMEs + ".jpg");
				a.convert("/tmp/" + NAMEs + ".jpg", NAMEs);
				
				if (fs::exists("/tmp/" + NAMEs + ".jpg"))
					fs::remove("/tmp/" + NAMEs + ".jpg");
					
				if (fs::exists("/tmp/" + NAMEs + ".png"))
					fs::remove("/tmp/" + NAMEs + ".png");
			}
		}
		else
		{
            if (ini.get("display_generic_art") == "true")
            {
                std::string generic_art = "/xmb/monochrome/png/generic_art.png";

                if (fs::exists(HOME + "/.config/retroarch" + generic_art))
                    a.copyart(HOME + "/.config/retroarch" + generic_art, NAMEs);
                else if (fs::exists("/usr/share/libretro/assets" + generic_art))
                    a.copyart("/usr/share/libretro/assets" + generic_art, NAMEs);
            }
		}
		
		const char *name_cstr = NAME.c_str();
		crcnum = crc32b(name_cstr);
		
		if ( std::find(cached.begin(), cached.end(), std::to_string(crcnum)) != cached.end() )
			continue;

		oplst << fpath << std::endl;
		oplst << NAMEs << std::endl;
        oplst << current << "/sh_launcher_libretro.so" << std::endl;
		oplst << "Linux (Sh Launcher)" << std::endl;
		oplst << std::to_string(crcnum) + "|crc" << std::endl;
		oplst << "Bash - Sh Launcher - PC.lpl" << std::endl;

		ini.append("cached", " " + std::to_string(crcnum));
	}
	
	oplst.close();
}
