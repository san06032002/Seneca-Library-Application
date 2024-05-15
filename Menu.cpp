
#define _CRT_SECURE_NO_WARNINGS
#ifndef SDDS_MENU_CPP
#define SDDS_MENU_CPP
#include<iostream>
#include "Menu.h"
#include <cstring>

namespace sdds {

	MenuItem::MenuItem() 
	{
		content = nullptr;
	}
	MenuItem::MenuItem(const char* newcontent) 
	{
		if (newcontent && newcontent[0])
		{
			content = new char[strlen(newcontent) + 1];
			strcpy(content, newcontent);
		}
		else 
		{
			content = nullptr;
		}
	}
	MenuItem::~MenuItem() 
	{
		delete[]content;
	}

	MenuItem::operator bool() const
	{
		
		if (content && content[0])
		{
			return true;
			
		}
		
			return false;
		
	}
	MenuItem::operator const char* () const
	{
		return content;
	}
	std::ostream& MenuItem::displayMenuItem(std::ostream& os)
	{
		if (content) {
			os << content;
		}
		return os;
	}
	Menu::Menu()
	{
		trackMenuItem = 0;
	}
	Menu::Menu(const char* menuItemTitle) :menuTitle(menuItemTitle) {}
	Menu::~Menu()
	{
		unsigned int i = 0;
		while (i < MAX_MENU_ITEMS)
		{
			delete menuItem[i];

			i++;
		}
		
	}
	std::ostream& Menu::displayTitle(std::ostream& os) 
	{
		if (menuTitle) 
		{
			menuTitle.displayMenuItem();
		}
		return os;
	}
	std::ostream& Menu::display(std::ostream& os)
	{

		unsigned int i = 0;
		if (menuTitle)
		{
			menuTitle.displayMenuItem();
			os << std::endl;
		}

		while (i < trackMenuItem)
		{

			os.width(2);
			os.fill(' ');
			os.setf(std::ios::right);
			os << i + 1 << "- ";
			os.unsetf(std::ios::right);
			menuItem[i]->displayMenuItem(os);
			os << std::endl;

			i++;

		}
		
		os << " 0- Exit" << std::endl;
		os << "> ";
		return os;
	}
	unsigned int Menu::run()
	{
		unsigned int userIn;
		bool val = true;
		display();

		while (val)
		{
			std::cin >> userIn;
			if (userIn >= 0 && userIn <= trackMenuItem && std::cin) 
			{
				val = false;
			}
			else 
			{
				std::cout << "Invalid Selection, try again: ";
				std::cin.clear();
				std::cin.ignore(3276, '\n');
				val = true;
			}
		}
		return userIn;
	}
	unsigned int Menu:: operator~()
	{
		return run();
	}
	Menu& Menu::operator<<(const char* menuitemConent) 
	{
		if (trackMenuItem < MAX_MENU_ITEMS)
		{
			MenuItem* newMenuItem = new MenuItem(menuitemConent);
			menuItem[trackMenuItem] = newMenuItem;
			trackMenuItem++;
		}

		return *this;
	}
	Menu::operator int()
	{
		return trackMenuItem;
	}

	Menu::operator unsigned int() 
	{
		return trackMenuItem;
	}
	Menu::operator bool()
	{
		bool valid;
		if (trackMenuItem > 0)
		{
			valid = true;
		}
		else 
		{
			valid = false;
		}
		return valid;
	}
	std::ostream& operator<<(std::ostream& os, Menu& menu) 
	{
		return(menu.displayTitle(os));
	}
	const char* Menu::operator[](unsigned int ind) const
	{

		if (ind > trackMenuItem) 
		{
			return (menuItem[ind %= trackMenuItem]->content);
		}
		return(menuItem[ind]->content);
	}
}




#endif // !SDDS_MENU_CPP
