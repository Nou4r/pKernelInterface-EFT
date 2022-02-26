#pragma once
#include <variant>
#include "../Modules/Heartbeat.h"
#include <conio.h>

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


namespace Vars {
	namespace Menu {
		static bool enabled = false;
		static bool aimbot = false;
		static bool visuals = false;
		static bool memory = false;
	}
	namespace Aimbot {
		static bool enabled = true;
		static bool snapLines = false;
		static int fov = 100;
		static bool fovCircle;
		static int aimbotBone = 0;
	}
	namespace Players {
		static bool enabled = false;
		static float distance = 300.f;
		static bool boxes = false;
		static bool health = false;
		static bool skeletons = false;
		static bool names = false;
		static bool weapons = false;
		static bool distances = false;

	}
	namespace Grenades {
		static bool enabled = false;
		static bool circles = false;
		static bool distance = false;
		static bool lines = false;
	}
	namespace Items {
		static bool items = false;
		static bool prices = false;
		static int minPrice = 50000;
		static bool highTier = false;
		static bool questItems = false;
		static bool containers = false;
	}

	namespace Corpses {
		static bool enabled = false;
		static bool names = false;

	}
	namespace Memory {
		static bool noRecoil = false;
		static bool superJump = false;
		static bool infStam = false;
		static bool thermalVision = false;
		static bool nightVision = false;
		static bool fovChanger = false;
		static bool noVisor = false;
		static bool speedHack = false;
		static bool flyHack = false;
		static bool fastLoadMags = false;
		static bool fastUnLoadMags = false;
	}
};
bool LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
{
	// Load texture from disk
	PDIRECT3DTEXTURE9 texture;
	HRESULT hr = D3DXCreateTextureFromFileA(p_Device, filename, &texture);
	if (hr != S_OK)
		return false;

	// Retrieve description of the texture surface so we can access its size
	D3DSURFACE_DESC my_image_desc;
	texture->GetLevelDesc(0, &my_image_desc);
	*out_texture = texture;
	*out_width = (int)my_image_desc.Width;
	*out_height = (int)my_image_desc.Height;
	return true;
}




void DrawBackground()
{
	

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.09f, 0.09f, 0.09f, 0.40f / 1.f * 2.f));
	static auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Button] = ImVec4(0.24f, 0.40f, 0.95f, 0.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.39f, 0.39f, 0.00f);
	ImGui::Begin(("EFT"), NULL, flags);
	{
		ImGui::SetWindowSize(ImVec2(450, GetSystemMetrics(SM_CYSCREEN)), ImGuiCond_Once);
		{
			ImGui::Image((void*)my_texture, ImVec2(420, 100));
			if (GetAsyncKeyState(VK_INSERT) & 1) {

			}
			ImGui::SetCursorPos(ImVec2(GetSystemMetrics(SM_CYSCREEN) / 2 - 400, GetSystemMetrics(SM_CYSCREEN) / 2 - 150));
			ImGui::Separator();
			ImGui::PushFont(ButtonFont);
			if (ImGui::Button("A I M B O T", ImVec2(-1.f, 100.f))) {
				Vars::Menu::aimbot = !Vars::Menu::aimbot;
				Vars::Menu::visuals = false;
				Vars::Menu::memory = false;

			}
			ImGui::Separator();
			if (ImGui::Button("V I S U A L S", ImVec2(-1.f, 100.f))) {
				Vars::Menu::visuals = !Vars::Menu::visuals;
				Vars::Menu::memory = false;
				Vars::Menu::aimbot = false;
			}
			ImGui::Separator();
			if (ImGui::Button("M E M O R Y", ImVec2(-1.f, 100.f))) {
				Vars::Menu::memory = !Vars::Menu::memory;
				Vars::Menu::visuals = false;
				Vars::Menu::aimbot = false;
			}
			ImGui::Separator();
			ImGui::PopFont();
				
		}
	}
	ImGui::End();
}

void DrawMenu()
{
	static auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar| ImGuiWindowFlags_NoMove;
//	ImGui::SetNextWindowPos(ImVec2(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2));
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_TitleBg] = ImVec4(1, 0.640, 0.120, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(1, 0.640, 0.120, 1.00f);
	if (Vars::Menu::aimbot) {
		ImGui::SetNextWindowPos(ImVec2(450, 0));
		ImGui::Begin(("Aimbot"), NULL, flags);
		{
			ImGui::SetWindowSize(ImVec2(GetSystemMetrics(SM_CXSCREEN) - 450, GetSystemMetrics(SM_CYSCREEN)), ImGuiCond_Once);
			{
				ImGui::SetCursorPos(ImVec2((GetSystemMetrics(SM_CXSCREEN) - 450) - 200, 50));
				ImGui::PushFont(ButtonFont);
				ImGui::Button("A I M B O T");
				ImGui::Checkbox("Aimbot Enabled", &Vars::Aimbot::enabled);
				ImGui::Checkbox("Draw Snap Line", &Vars::Aimbot::snapLines);
				ImGui::Checkbox("Draw FOV", &Vars::Aimbot::fovCircle);
				ImGui::SliderInt("FOV", &Vars::Aimbot::fov, 1, 500, "%d");
				
				ImGui::PopFont();
				//if (ImGui::Button("Bitch"))
					//ImGui::SetWindowSize(ImVec2(0, 0));
			}
		}
		ImGui::End();
	}


	if (Vars::Menu::visuals) {
		ImGui::SetNextWindowPos(ImVec2(450, 0));
		ImGui::Begin(("Visuals"), NULL, flags);
		{
			ImGui::SetWindowSize(ImVec2(GetSystemMetrics(SM_CXSCREEN) - 450, GetSystemMetrics(SM_CYSCREEN)), ImGuiCond_Once);
			{
				ImGui::SetCursorPos(ImVec2((GetSystemMetrics(SM_CXSCREEN) - 450) - 200, 50));
				ImGui::PushFont(ButtonFont);
				ImGui::Button("V I S U A L S");
				ImGui::Checkbox("Player ESP Enabled", &Vars::Players::enabled);
				ImGui::Checkbox("Name", &Vars::Players::names);
				ImGui::Checkbox("Boxes", &Vars::Players::boxes);
				ImGui::Checkbox("Skeletons", &Vars::Players::skeletons);
				ImGui::Checkbox("Health", &Vars::Players::health);
				ImGui::Checkbox("Weapon Name", &Vars::Players::weapons);
				ImGui::Checkbox("Show Distance", &Vars::Players::distances);
				ImGui::SliderFloat("Max Distance", &Vars::Players::distance, 0, 1000, "%0.0f", 1.f);
				ImGui::PopFont();
				
			}
		}
		ImGui::End();
	}


	if (Vars::Menu::memory) {
		ImGui::SetNextWindowPos(ImVec2(450, 0));
		ImGui::Begin(("Memory"), NULL, flags);
		{
			ImGui::SetWindowSize(ImVec2(GetSystemMetrics(SM_CXSCREEN) - 450, GetSystemMetrics(SM_CYSCREEN)), ImGuiCond_Once);
			{
				ImGui::SetCursorPos(ImVec2((GetSystemMetrics(SM_CXSCREEN) - 450) - 200, 50));
				ImGui::PushFont(ButtonFont);
				ImGui::Button("M E M O R Y");
				ImGui::Checkbox("No Recoil", &Vars::Memory::noRecoil);
				ImGui::Checkbox("Moon Jump", &Vars::Memory::superJump);
				ImGui::Checkbox("Infinite Stamina", &Vars::Memory::infStam);
				ImGui::Checkbox("Thermal Vision", &Vars::Memory::thermalVision);
				ImGui::Checkbox("Night Vision", &Vars::Memory::nightVision);
				ImGui::Checkbox("FOV Changer", &Vars::Memory::fovChanger);
				ImGui::Checkbox("No Visor", &Vars::Memory::noVisor);
				ImGui::Checkbox("Speed Hack", &Vars::Memory::speedHack);
				ImGui::Checkbox("Fly Hack", &Vars::Memory::flyHack);
				ImGui::Checkbox("Fast Load Mag", &Vars::Memory::fastLoadMags);
				ImGui::Checkbox("Fast Un-Load Mag", &Vars::Memory::fastUnLoadMags);

				ImGui::PopFont();
				
			}
		}
		ImGui::End();
	}
}