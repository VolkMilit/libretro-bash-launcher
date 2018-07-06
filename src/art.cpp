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

#include "art.h"

#include "third-party/ftlip/ftlip.h"

art::art(){}
art::~art()
{
	image = nullptr;
}

bool art::checkFormat(const std::string &file)
{
	std::string tmp = basename(file);
	if (tmp.substr(tmp.find_last_of(".") + 1) != "png")
		return true;
	
	return false;
}

void art::copyart(const std::string &file, const std::string &name)
{
	if (fs::exists(nb + name + ".png"))
		return;
	
	try
	{
		fs::copy(file, nb + name + ".png");
		fs::copy(file, ns + name + ".png");
		fs::copy(file, nt + name + ".png");
	}
	catch(...)
	{
		std::cout << "error fs::copy: Something horrible is happend!" << std::endl;
	}
}

void art::convert(const std::string &file, const std::string &name)
{
	if (!checkFormat(file))
	{
		/*
		 * TODO:
		 *	check for md5
		 * */
		
		// we don't need to convert anything
		copyart(file, name);
		return;
	}
	
	this->image = imlib_load_image(file.c_str());
	
	if (this->image)
	{
		imlib_context_set_image(image);
		imlib_image_set_format("png");
		imlib_save_image("/tmp/test.png");
	}

	copyart("/tmp/test.png", name);
	
	if (fs::exists("/tmp/test.png"))
		fs::remove("/tmp/test.png");
}
