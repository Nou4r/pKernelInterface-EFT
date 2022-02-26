#include <variant>
#include "../Modules/Heartbeat.h"
#include <conio.h>
//#include "Overlay.h"
//template<typename T>
enum Category {
	Players = 0,
	Grenades,
	Items,
	Extracts,
	Memory
};
enum ItemType {
	Bool = 1,
	Integer,
	Float,
	Header
};
int selectedItem = 1;
bool ShowMenu = true;
class MenuItem {
public:
	Category category;
	std::string name;
	bool bValue = false;
	int iValue = 50000;
	float fValue = 300;

	//int& iValuePtr;
	//float& fValuePtr;
	//bool& bValuePtr;

	ItemType type;

	std::string get_value_bool()
	{
		return bValue ? "<On>" : "<Off>";
	}
	std::string get_value_int()
	{
		char buf[256];
		sprintf(buf, "<%i>", iValue);
		return buf;
	}
	void handle_left() {
		switch (type) {
		case ItemType::Bool:
			bValue = !bValue;
			break;
		case ItemType::Integer:
			iValue = iValue - 100;
			break;
		case ItemType::Float:
			fValue--;
			break;
		}

	}

	void handle_right() {
		switch (type) {
		case ItemType::Bool:
			bValue = !bValue;
			break;
		case ItemType::Integer:
			iValue = iValue + 100;
			break;
		case ItemType::Float:
			fValue++;
			break;
		}
	}

	std::string get_value_float()
	{
		char buf[256];
		sprintf(buf, "<%0.fM>", fValue);
		return buf;
	}




};


class MenuCategory {
	bool open;
	std::string name;
	std::vector<MenuItem> Items;
};



std::vector<MenuItem> MenuItems;



void AddMenuItem(ItemType type, Category category, std::string name) {
	MenuItem MenuItem;

	MenuItem.category = category;
	MenuItem.name = name;
	MenuItem.type = type;
	MenuItems.push_back(MenuItem);
}
void HandleUp(ItemType type)
{

	if (GetAsyncKeyState(VK_UP) & 1) {
		selectedItem--;
		if (type == ItemType::Header)
			selectedItem--;


	}
}

void HandleDown(ItemType type)
{
	if (GetAsyncKeyState(VK_DOWN) & 1) {
		selectedItem++;
		if (type == ItemType::Header)
			//if (selectedItem == i)
			selectedItem++;

	}

}
void HandleItems() {

	//Players
	AddMenuItem(ItemType::Header, Category::Players, "Players");
	AddMenuItem(ItemType::Bool, Category::Players, "Enabled");
	AddMenuItem(ItemType::Float, Category::Players, "Max Distance");
	AddMenuItem(ItemType::Bool, Category::Players, "Boxes");
	AddMenuItem(ItemType::Bool, Category::Players, "Health");
	AddMenuItem(ItemType::Bool, Category::Players, "Names");
	AddMenuItem(ItemType::Bool, Category::Players, "Weapons");
	AddMenuItem(ItemType::Bool, Category::Players, "Distances");

	//Grenades
	AddMenuItem(ItemType::Header, Category::Grenades, "Grenades");
	AddMenuItem(ItemType::Bool, Category::Grenades, "Enabled");

	//Items
	AddMenuItem(ItemType::Header, Category::Items, "Items");
	AddMenuItem(ItemType::Bool, Category::Items, "Enabled");
	AddMenuItem(ItemType::Bool, Category::Items, "Prices");
	AddMenuItem(ItemType::Integer, Category::Items, "Min Price");

	//Extracts
	AddMenuItem(ItemType::Header, Category::Extracts, "Extracts");
	AddMenuItem(ItemType::Bool, Category::Extracts, "Enabled");
	AddMenuItem(ItemType::Bool, Category::Extracts, "Status");

	//Extracts
	AddMenuItem(ItemType::Header, Category::Extracts, "Corpses");
	AddMenuItem(ItemType::Bool, Category::Extracts, "Enabled");
	//AddMenuItem(ItemType::Bool, Category::Extracts, "Status");

	//Memory
	AddMenuItem(ItemType::Header, Category::Memory, "Memory");
	AddMenuItem(ItemType::Bool, Category::Memory, "No Recoil");
	AddMenuItem(ItemType::Bool, Category::Memory, "Super Jump");
	AddMenuItem(ItemType::Bool, Category::Memory, "Infinite Stamina");
	AddMenuItem(ItemType::Bool, Category::Memory, "Thermal Vision");
	AddMenuItem(ItemType::Bool, Category::Memory, "Night Vision");
	AddMenuItem(ItemType::Bool, Category::Memory, "FOV Changer");
	AddMenuItem(ItemType::Bool, Category::Memory, "No Visor");
	AddMenuItem(ItemType::Bool, Category::Memory, "SpeedHack");

	AddMenuItem(ItemType::Bool, Category::Memory, "No Fall/FlyHack");
	AddMenuItem(ItemType::Bool, Category::Memory, "Fast LoadMags");
	AddMenuItem(ItemType::Bool, Category::Memory, "Fast UnLoadMags");

	AddMenuItem(ItemType::Header, Category::Memory, "Aimbot");
	AddMenuItem(ItemType::Bool, Category::Memory, "Enabled");
	AddMenuItem(ItemType::Bool, Category::Memory, "Snaplines");
}

void DrawMenuItems(int i) {
	if (MenuItems[i].type == ItemType::Header) {

		DrawStrokeText(40, 115 + i * 15.f, &Col.purple, MenuItems[i].name.c_str());
		DrawStrokeText(160, 115 + i * 15.f, &Col.purple, "[-]");
	}
	else {
		RGBA* color = &Col.white;
		if (selectedItem == i) {
			color = &Col.purple;
		}
		DrawStrokeText(50, 115 + i * 15.f, color, MenuItems[i].name.c_str());
		if (MenuItems[i].type == ItemType::Bool)
			DrawStrokeText(160, 115 + i * 15.f, color, MenuItems[i].get_value_bool().c_str());
		else if (MenuItems[i].type == ItemType::Integer)
			DrawStrokeText(160, 115 + i * 15.f, color, MenuItems[i].get_value_int().c_str());
		else if (MenuItems[i].type == ItemType::Float)
			DrawStrokeText(160, 115 + i * 15.f, color, MenuItems[i].get_value_float().c_str());



	}
	if (GetAsyncKeyState(VK_DOWN) & 1) {
		if (MenuItems[i].type == ItemType::Header && selectedItem == i)
			selectedItem = selectedItem + 2;
		else
			selectedItem = selectedItem + 1;

	}
	if (GetAsyncKeyState(VK_UP) & 1) {
		if (MenuItems[i].type == ItemType::Header && selectedItem == i)
			selectedItem = selectedItem - 2;
		else
			selectedItem = selectedItem - 1;


	}
	if (selectedItem == i) {
		if (MenuItems[i].type == ItemType::Integer) {
			if (GetAsyncKeyState(VK_LEFT)) {
				MenuItems[i].handle_left();
			}
			if (GetAsyncKeyState(VK_RIGHT)) {
				MenuItems[i].handle_right();
			}
		}
		else {
			if (GetAsyncKeyState(VK_LEFT) & 1) {
				MenuItems[i].handle_left();
			}
			if (GetAsyncKeyState(VK_RIGHT) & 1) {
				MenuItems[i].handle_right();
			}
		}

	}
}
INT Fps = 0;
FLOAT LastTickCount = 0.0f;
FLOAT CurrentTickCount;
CHAR FrameRate[50] = "";
void Menu() {
	//std::cout << MenuItems.size() << std::endl;
	
	if (ShowMenu) {
		//BoxBordered(30, 80, 190, 50 + MenuItems.size() * 15, 1, D3DCOLOR_ARGB(255, 0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawRect(29, 79, 190, 50 + MenuItems.size() * 15, &Col.white, 1);
		DrawRect(31, 81, 190, 50 + MenuItems.size() * 15, &Col.white, 1);
		DrawFilledRect(30, 80, 190, 50 + MenuItems.size() * 15, &Col.black);

		//Line(40, 110, 180, 110, 255, 255, 255, 255);
		DrawLine(40, 110, 180, 110, &Col.white, 1);
		DrawStrokeText(40, 90, &Col.red, "klapt.io");
		for (int i = 0; MenuItems.size() > i; i++) {
			DrawMenuItems(i);

			//HandleUp(MenuItems[i].type);
			//HandleDown(MenuItems[i].type);

			//DrawString(170, 115 + i * 15.f, "[-]", D3DCOLOR_ARGB(250, 255, 0, 255));



		}
	}

}