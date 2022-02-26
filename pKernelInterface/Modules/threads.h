#pragma once
#include <thread>
#include "Items.h"
#include "Extracts.h"
#include "Grenades.h"
#include "Players.h"
#define _USE_MATH_DEFINES
#include <math.h>

//using namespace std::chrono_literals;
std::vector<Player> tmpPlayers;
std::vector<Player> PlayerList;
int Width = GetSystemMetrics(SM_CXSCREEN);
int Height = GetSystemMetrics(SM_CYSCREEN);
glm::vec2 player_closestScreenHead{};

uint64_t GetClosest() {
	float minDist = 999999999999999;
	uint64_t curBest = 12345678910;

	for (auto& player : PlayerList) {


		if (!Utils::Camera::world_to_screen(player.headPosition, &player_closestScreenHead)) continue;
		float dist = glm::distance(glm::vec3{ Width / 2, Height / 2, 0 }, glm::vec3{ player_closestScreenHead.x, player_closestScreenHead.y, 0 });
		if (dist < minDist) {
			curBest = player.instance;
			minDist = dist;

		}
	}
	return curBest;

}
glm::vec3 GetClosestHeadPos() {

	for (auto& player : PlayerList) {
		if (!player.instance)
			return glm::vec3();
		if (player.instance == SDK::Globals::closest)
			return player.headPosition;
		else
		{
			return glm::vec3();
			continue;
		}
	}
}
PVOID BaseValues() {
	while (true) {


		
		if (!SDK::Globals::g_gameObjectManager)
			continue;

		auto active_objects = mem->Read<std::array<uint64_t, 2>>(SDK::Globals::g_gameObjectManager + 0x20);

		SDK::Globals::g_gameWorld = Utils::GetObjectFromList(active_objects[1], active_objects[0], "GameWorld");

		if (!SDK::Globals::g_gameWorld) {
			Sleep(500);
			continue;
		}

		SDK::Globals::g_localGameWorld = mem->ReadChain<uint64_t>(SDK::Globals::g_gameWorld, { 0x30, 0x18, 0x28 });
		if (!SDK::Globals::g_localGameWorld)
			continue;

		//	printf("localgameWorld: 0x%X\n", SDK::Globals::g_localGameWorld);

		auto tagged_objects = mem->Read<std::array<uint64_t, 2>>(SDK::Globals::g_gameObjectManager + 0x10);
		SDK::Globals::g_fpsCamera = Utils::GetObjectFromList(tagged_objects[1], tagged_objects[0], "FPS Camera");
		if (!SDK::Globals::g_fpsCamera)
			continue;


		SDK::Globals::closest = GetClosest();
		if (!Utils::Camera::world_to_screen(SDK::Globals::firePortPos, &SDK::Globals::hands_Screen))
			continue;

		uint64_t fov = mem->ReadChain<uint64_t>(SDK::Globals::g_fpsCamera, { 0x30, 0x18 });
		if (!fov)
			continue;
		SDK::Globals::localFov = mem->Read<float>(fov + 0x15C);

		Sleep(10);
	}
}



PVOID ESPThread() {
	while (true)
	{

		tmpPlayers.clear();

		if (!Utils::valid_pointer(SDK::Globals::g_localGameWorld))
			continue;
		SDK::Globals::g_onlineUsers = mem->Read<uint64_t>(SDK::Globals::g_localGameWorld + 0x80);
		if (!Utils::valid_pointer(SDK::Globals::g_onlineUsers))
			continue;
		int g_playerCount = mem->Read<int>(SDK::Globals::g_onlineUsers + 0x18);
		uint64_t list_base = mem->Read<uint64_t>(SDK::Globals::g_onlineUsers + 0x10);
		if (g_playerCount <= 0 || g_playerCount > 127 || !Utils::valid_pointer(list_base))
			continue;
		constexpr auto BUFFER_SIZE = 128;

		uint64_t player_buffer[BUFFER_SIZE];


		mem->Read(list_base + 0x20, player_buffer, sizeof(uint64_t) * g_playerCount);

		for (int i = 0; i < g_playerCount; i++) {

			if (!Utils::valid_pointer(player_buffer[i]))
				continue;

			Player player;
			player.instance = player_buffer[i];
			if (i == 0)
			{
				SDK::Entity::g_localPlayer = player.instance;
				SDK::Globals::localHeadPos = Utils::Player::Bones::get_bone_position(player.instance, 133);
				continue;
			}

			player.GetRootPosition();
			player.GetDistance();
			if (player.distance > MenuItems[2].fValue)
				continue;
			player.GetHeadPosition();
			player.GetRole();
			player.GetName();
			player.GetWeaponName();

			tmpPlayers.push_back(player);
		}
		PlayerList = tmpPlayers;
		Sleep(1);
	}
}

std::vector<Item> tmpItems;
std::vector<Item> ItemsList;
std::ifstream ifstreammm(std::string(std::string(getenv(("systemroot"))) + std::string(("\\System32\\all.json"))));
nlohmann::json jf = nlohmann::json::parse(ifstreammm);
PVOID ItemsThread() {
	while (true)
	{

		tmpItems.clear();


		if (!Utils::valid_pointer(SDK::Globals::g_localGameWorld))
			continue;

		if (!MenuItems[11].bValue) {
			Sleep(1000);
			continue;
		}



		uint64_t LootList = mem->Read<uint64_t>(SDK::Globals::g_localGameWorld + 0x60);
		if (!Utils::valid_pointer(LootList))
			continue;

		SDK::Globals::LootCount = mem->Read<int>(LootList + 0x18);
		if (SDK::Globals::LootCount <= 0)
			continue;

		std::string name = "";
		int price = 100;
		for (int i = 0; i < SDK::Globals::LootCount; i++)
		{

			Item item(i);

			if (!item.Init())
				continue;

			item.GetLocation();
			if (glm::distance(SDK::Globals::localHeadPos, item.location) > 1000)
				continue;

			uint64_t namePtr = mem->Read<uint64_t>(item.instance + 0x78);
			if (!Utils::valid_pointer(namePtr))
				continue;
			std::wstring id1 = mem->GetWString(namePtr);

			std::string idd = Utils::Text::wstring_to_utf8(id1);
			if (idd == "")
				continue;
			if (idd == "55d7217a4bdc2d86028b456d") {
				continue;
			}


			for (auto e : jf) {
				if (e["bsgId"] != idd)
					continue;

				e["name"].get_to(name);

				e["avg24hPrice"].get_to(price);
			}


			item.name = Utils::Text::utf8_to_wstring(name);
			item.price = price;





			tmpItems.push_back(item);
		}
		ItemsList = tmpItems;
		Sleep(10);
		//Sleep(6000);
	}
}


std::vector<Extract> tmpExtracts;
std::vector<Extract> ExtractsList;

PVOID ExtractsThread() {
	while (true) {

		tmpExtracts.clear();



		if (!MenuItems[15].bValue) {
			Sleep(1000);
			continue;
		}

		if (!Utils::valid_pointer(SDK::Globals::g_localGameWorld))
			continue;

		uintptr_t exitController = mem->Read<uintptr_t>(SDK::Globals::g_localGameWorld + 0x18);
		if (!exitController)
			continue;
		uintptr_t exitPoint = mem->Read<uintptr_t>(exitController + 0x20);
		if (!exitPoint)
			continue;
		uintptr_t exitCount = mem->Read<int>(exitPoint + 0x18);
		if (!exitCount)
			continue;
		for (int i = 0; i < exitCount; i++) {
			Extract extract(i);
			if (!extract.Init())
				continue;
			extract.GetPos();
			extract.GetExtractName();
			extract.GetExtractStatus();
			tmpExtracts.push_back(extract);
		}
		ExtractsList = tmpExtracts;
		Sleep(10000);
	}
}
std::vector<Grenade> tmpGrenades;
std::vector<Grenade> GrenadesList;
PVOID GrenadesThread() {
	while (true) {


		tmpGrenades.clear();

		if (!MenuItems[9].bValue) {
			Sleep(1000);
			continue;
		}

		if (!Utils::valid_pointer(SDK::Globals::g_localGameWorld))
			continue;

		uint64_t Grenades = mem->Read<uint64_t>(SDK::Globals::g_localGameWorld + 0xF0);

		if (!Grenades)
			continue;

		uint64_t GrenadeList = mem->Read<uint64_t>(Grenades + 0x18);

		if (!GrenadeList)
			continue;

		int grenadeCount = mem->Read<int>(GrenadeList + 0x18);

		if (!grenadeCount)
			continue;

		for (int i = 0; i < grenadeCount; i++) {
			Grenade grenade(i);
			if (!grenade.Init())
				continue;
			grenade.GetLocation();
			grenade.GetName();

			tmpGrenades.push_back(grenade);
		}
		GrenadesList = tmpGrenades;
		Sleep(1);
	}
}



void MaxSkills(uint64_t player) {
	if (!Utils::valid_pointer(SDK::Globals::g_localGameWorld))
		return;
	uint64_t PlayerProfile = mem->Read<uint64_t>(player + 0x4B8);
	if (!Utils::valid_pointer(PlayerProfile))
		return;

	uint64_t Skills = mem->Read<uint64_t>(PlayerProfile + 0x60);
	if (!Utils::valid_pointer(Skills))
		return;

	float maxlevel = (100.f * 60.f);

	uintptr_t StrengthBuffJumpHeightInc = mem->Read<uintptr_t>(Skills + 0x58);

	if (Utils::valid_pointer(StrengthBuffJumpHeightInc))
		if (MenuItems[21].bValue)
			mem->Write<float>(StrengthBuffJumpHeightInc + 0x28, 0.6f);

	uintptr_t MagDrillsLoadSpeed = mem->Read<uintptr_t>(Skills + 0x170);

	if (Utils::valid_pointer(MagDrillsLoadSpeed))
		if (MenuItems[29].bValue)
			mem->Write<float>(MagDrillsLoadSpeed + 0x28, 50.f);

	uintptr_t MagDrillsUnLoadSpeed = mem->Read<uintptr_t>(Skills + 0x178);

	if (Utils::valid_pointer(MagDrillsUnLoadSpeed))
		if (MenuItems[30].bValue)
			mem->Write<float>(MagDrillsUnLoadSpeed + 0x28, 50.f);
}




std::vector<Item> tmpBodies;
std::vector<Item> BodiesList;

PVOID BodiesThread() {
	while (true)
	{

		tmpBodies.clear();

		if (!MenuItems[18].bValue) {
			Sleep(1000);
			continue;
		}

		if (!Utils::valid_pointer(SDK::Globals::g_localGameWorld))
			continue;


		uint64_t LootList = mem->Read<uint64_t>(SDK::Globals::g_localGameWorld + 0x60);
		if (!Utils::valid_pointer(LootList))
			continue;

		int lootCount = mem->Read<int>(LootList + 0x18);
		if (SDK::Globals::LootCount <= 0)
			continue;

		for (int i = 0; i < lootCount; i++)
		{

			Item item(i);

			if (!item.Init())
				continue;

			item.GetLocation();


		
			uint64_t namePtr = mem->Read<uint64_t>(item.instance + 0x78);
			if (!Utils::valid_pointer(namePtr))
				continue;
			std::wstring id1 = mem->GetWString(namePtr);
			if (id1 != L"55d7217a4bdc2d86028b456d") {
				continue;
			}


			item.name = L"Dead Body";
			tmpBodies.push_back(item);
		}
		BodiesList = tmpBodies;
		Sleep(10);
	}
}
glm::vec3 CalcViewAngles(glm::vec3 LocalPlayerPos, glm::vec3 TargetPos)
{
	glm::vec3 diff = LocalPlayerPos - TargetPos;
	glm::vec3 ret;

	float length = glm::length(diff);
	ret.y = asinf(diff.y / length);
	ret.x = -atan2f(diff.x, -diff.z);

	return ret * 57.29578f;
}
PVOID SilentAimThread() {
	while (true) {




		if (Vars::Aimbot::enabled) {
			if (!Utils::valid_pointer(SDK::Globals::closest)) {
				Sleep(500);
				continue;
			}
			const auto procedural_weapon_animation = mem->Read<uintptr_t>(SDK::Entity::g_localPlayer + 0x190);
			if (!Utils::valid_pointer(procedural_weapon_animation))
				continue;
			const auto firearm_controller = mem->Read<uintptr_t>(procedural_weapon_animation + 0x80);
			if (!Utils::valid_pointer(firearm_controller))
				continue;
			const auto fireport = mem->Read<uintptr_t>(firearm_controller + 0xe8);
			if (!Utils::valid_pointer(fireport))
				continue;
			const auto fireport_orginal_transform = mem->Read<uintptr_t>(fireport + 0x10);
			if (!Utils::valid_pointer(fireport_orginal_transform))
				continue;
			SDK::Globals::firePortPos = Utils::Player::Bones::get_transform_position(fireport_orginal_transform);
			glm::vec3 aim_angle = CalcViewAngles(SDK::Globals::firePortPos, Utils::Player::Bones::get_bone_position(SDK::Globals::closest, 133));
			uintptr_t movement_context = mem->Read<uintptr_t>(SDK::Entity::g_localPlayer + 0x40);
			if (!Utils::valid_pointer(movement_context))
				continue;
			if(GetAsyncKeyState(VK_RBUTTON))
				mem->Write<glm::vec2>(movement_context + 0x22C, { aim_angle.x, aim_angle.y });
		}
		Sleep(1);

	}
}






PVOID TestThread() {
	while (true) {
		
		if (GetAsyncKeyState(VK_F8) & 1) {
			MenuItems[15].bValue = false;
			MenuItems[11].bValue = false;
		}

		if (!Utils::valid_pointer(SDK::Globals::g_localGameWorld) || !Utils::valid_pointer(SDK::Entity::g_localPlayer))
		{
			Sleep(1000);
			continue;
		}

		//std::cout << "d2" << std::endl;

		/*if (GetAsyncKeyState(VK_DELETE)) {
			uintptr_t WeaponAnim = mem->Read<uintptr_t>(SDK::Entity::g_localPlayer + 0x190);
			if (WeaponAnim <= 0)
				continue;

			mem->Write<float>(WeaponAnim + 0x1DC, -15.f);
		}


		
		//if (GetAsyncKeyState(VK_HOME)) {
		//if (MenuItems[22].bValue) {
			uintptr_t WeaponAnim = mem->Read<uintptr_t>(SDK::Entity::g_localPlayer + 0x190);
			//if (WeaponAnim <= 0)
			//	continue;
			glm::vec3 localPlayerViewAngles = mem->Read<glm::vec3>(WeaponAnim + 0x22C);
			uintptr_t FireamController = mem->Read<uintptr_t>(WeaponAnim + 0x80);
			//if (FireamController <= 0)
			//	continue;
			uint64_t Fireport = mem->Read<uintptr_t>(FireamController + 0xE8);
			uint64_t MovementContext = mem->Read<uint64_t>(SDK::Entity::g_localPlayer + 0x40);

			glm::vec3 firePortPos = Utils::Player::Bones::get_transform_position(mem->Read<uint64_t>(Fireport + 0x10));

			glm::vec3 newViewAngles = CalcViewAngles(firePortPos, Utils::Player::Bones::get_bone_position(SDK::Globals::closest, 133));

			glm::vec3 delta = newViewAngles - localPlayerViewAngles;
			delta = (delta);

			glm::vec3 gunAngle = glm::vec3{ ToRad(delta.x), ToRad(delta.y), ToRad(delta.z) } / (SDK::Globals::localFov / 50.f);
			gunAngle.y *= -1.f;
			glm::vec3 tmp = { gunAngle.x, -1.f , gunAngle.y };
			mem->Write<glm::vec3>(WeaponAnim + 0x1E0, tmp);
			std::cout << mem->Read<glm::vec3>(WeaponAnim + 0x1E0).x << " " << mem->Read<glm::vec3>(WeaponAnim + 0x1E0).y << " " << mem->Read<glm::vec3>(WeaponAnim + 0x1E0).z << std::endl;
			//if (GetAsyncKeyState(VK_RIGHT))
				//mem->Write<glm::vec2>(MovementContext + 0x22C, { glm::normalize(CalcViewAngles(pos, SDK::Globals::closestHeadPos)).x, glm::normalize(CalcViewAngles(pos, SDK::Globals::closestHeadPos)).y });
			//glm::vec3 test = mem->Read<glm::vec3>(WeaponAnim + 0x22C);
			//std::cout << mem->Read<glm::vec3>(WeaponAnim + 0x1E0).x << " " << mem->Read<glm::vec3>(WeaponAnim + 0x1E0).y << " " << mem->Read<glm::vec3>(WeaponAnim + 0x1E0).z << std::endl;
			//uintptr_t TurnAwayEffector = mem->Read<uintptr_t>(WeaponAnim + 0x50);
			//mem->Write<glm::vec3>(TurnAwayEffector + 0x98, { -15, 0, -15 });
			//mem->Write<float>(TurnAwayEffector + 0xBC, -20.f);
			//mem->Write<float>(TurnAwayEffector + 0xC0, -20.f);
			// }*/
		//}

		//if (MenuItems[21].bValue)
		//MaxSkills(SDK::Entity::g_localPlayer);

		//if (MenuItems[20].bValue) {

			uintptr_t WeaponAnim = mem->Read<uintptr_t>(SDK::Entity::g_localPlayer + 0x190);
			if (!Utils::valid_pointer(WeaponAnim))
				continue;

			/*uintptr_t BreathEffector = mem->Read<uintptr_t>(WeaponAnim + 0x28);
			if (!Utils::valid_pointer(BreathEffector))
				continue;

			uintptr_t ShotEffector = mem->Read<uintptr_t>(WeaponAnim + 0x48);
			if (!Utils::valid_pointer(ShotEffector))
				continue;

			mem->Write<glm::vec2>(ShotEffector + 0x40, { 0.f, 0.f });
			mem->Write<glm::vec2>(ShotEffector + 0x48, { 0.f, 0.f });
			mem->Write<glm::vec2>(ShotEffector + 0x50, { 0.f, 0.f });
			mem->Write<glm::vec3>(ShotEffector + 0x58, { 0.f, 0.f, 0.f });
			mem->Write<glm::vec2>(ShotEffector + 0x64, { 0.f, 0.f });
			mem->Write<float>(BreathEffector + 0xA4, 0.f);
			mem->Write<float>(BreathEffector + 0xA8, 0.f);
			mem->Write<float>(BreathEffector + 0xAC, 0.f);
			mem->Write<float>(BreathEffector + 0xB0, 0.f);
			mem->Write<float>(BreathEffector + 0xB4, 0.f);
			mem->Write<float>(BreathEffector + 0xE4, 0.f);
			mem->Write<float>(ShotEffector + 0x6C, 0.f);
			mem->Write<float>(ShotEffector + 0x70, 0.f);*/

			mem->Write<int>(WeaponAnim + 0x100, 0);

			/*mem->Write<glm::vec3>(WeaponAnim + 0x20C, {0.f, 0.f, 0.f});
			mem->Write<glm::vec2>(ShotEffector + 0x64, { 0.f, 0.f });
			mem->Write<glm::vec2>(ShotEffector + 0x48, { 0.f, 0.f });
			mem->Write<glm::vec2>(ShotEffector + 0x40, { 0.f, 0.f });
			mem->Write<float>(ShotEffector + 0x70, 0.f);
			mem->Write<float>(ShotEffector + 0x6C, 0.f);
			mem->Write<float>(BreathEffector + 0xA4, 0.f);
			mem->Write<float>(BreathEffector + 0xA8, 0.f);
			mem->Write<float>(BreathEffector + 0xAC, 0.f);
			mem->Write<float>(BreathEffector + 0xB0, 0.f);
			mem->Write<float>(BreathEffector + 0xB4, 0.f);
			mem->Write<float>(BreathEffector + 0xE4, 0.f);*/
		//}
		//if (MenuItems[22].bValue) {
			if (!Utils::valid_pointer(SDK::Entity::g_localPlayer))
				continue;
			uintptr_t Physical = mem->Read<uintptr_t>(SDK::Entity::g_localPlayer + 0x4C8);
			if (!Utils::valid_pointer(Physical))
				continue;

			uintptr_t Stamina = mem->Read<uintptr_t>(Physical + 0x38);
			if (!Utils::valid_pointer(Stamina))
				continue;

			//	uintptr_t Oxygen = mem->Read<uintptr_t>(Physical + 0x48);
				//if (Oxygen <= 0)
					//continue;

			mem->Write<float>(Stamina + 0x48, 50.f);
			//mem->Write<FLOAT>(Oxygen + 0x48, 50.f);

		//}
		/*if (MenuItems[28].bValue) {
			uintptr_t MovementContext = mem->Read<uintptr_t>(SDK::Entity::g_localPlayer + 0x40);
			if (!Utils::valid_pointer(MovementContext))
				continue;
			mem->Write<float>(MovementContext + 0x1F8, 0.f);
			//	mem->Write<float>(MovementContext + 0x404, 0.f);
			//	mem->Write<float>(MovementContext + 0x408, 0.f);
		}
		
		if (MenuItems[25].bValue) {
			uint64_t fov = mem->ReadChain<uint64_t>(SDK::Globals::g_fpsCamera, { 0x30, 0x18 });
			if (!Utils::valid_pointer(fov))
				continue;
			mem->Write<float>(fov + 0x15C, 120.f);
		}
		//	else if (!MenuItems[25].bValue) {
			//	uint64_t fov = mem->ReadChain<uint64_t>(SDK::Globals::g_fpsCamera, { 0x30, 0x18 });
			//	if (!fov)
			//		continue;
			//	mem->Write<float>(fov + 0x15C, 75.f);
			//}
		if (MenuItems[23].bValue) {
			uint64_t thermalVision = Utils::GetComponentFromGameObject(SDK::Globals::g_fpsCamera, "ThermalVision");
			if (!Utils::valid_pointer(thermalVision))
				continue;
			//uint64_t material = mem->ReadChain<uint64_t>(thermalVision, { 0x90, 0x10 });
			//mem->Write<int>(material + 0x38, 224); //Cancer mode
			//mem->Write<int>(material + 0x38, 224);
			mem->Write<bool>(thermalVision + 0xD0, true); // Enable
			mem->Write<bool>(thermalVision + 0xD1, false); // IsNoisy
			mem->Write<bool>(thermalVision + 0xD2, false); // IsFpSstuck
			mem->Write<bool>(thermalVision + 0xD3, false); // MotionBlur
			mem->Write<bool>(thermalVision + 0xD4, false); // IsGlitched
			mem->Write<bool>(thermalVision + 0xD5, false); // Pixellated
		}
		else if (!MenuItems[23].bValue) {
			uint64_t thermalVision = Utils::GetComponentFromGameObject(SDK::Globals::g_fpsCamera, "ThermalVision");
			if (!Utils::valid_pointer(thermalVision))
				continue;
			mem->Write<bool>(thermalVision + 0xD0, false);
			mem->Write<bool>(thermalVision + 0xD1, true); // IsNoisy
			mem->Write<bool>(thermalVision + 0xD2, true); // IsFpSstuck
			mem->Write<bool>(thermalVision + 0xD3, true); // MotionBlur
			mem->Write<bool>(thermalVision + 0xD4, true); // IsGlitched
			mem->Write<bool>(thermalVision + 0xD5, true); // Pixellated
		}

		if (MenuItems[24].bValue) {
			uint64_t nightVision = Utils::GetComponentFromGameObject(SDK::Globals::g_fpsCamera, "NightVision");
			if (!Utils::valid_pointer(nightVision))
				continue;
			mem->Write<bool>(nightVision + 0xCC, true); //_on
		}
		else if (!MenuItems[24].bValue) {
			uint64_t nightVision = Utils::GetComponentFromGameObject(SDK::Globals::g_fpsCamera, "NightVision");
			if (!Utils::valid_pointer(nightVision))
				continue;
			mem->Write<bool>(nightVision + 0xCC, false); //_on
		}
		if (MenuItems[26].bValue) {
			uint64_t VisorComp = Utils::GetComponentFromGameObject(SDK::Globals::g_fpsCamera, "VisorEffect");
			if (!Utils::valid_pointer(VisorComp))
				continue;
			mem->Write<float>(VisorComp + 0xB8, 0.f);
		}
		if (MenuItems[27].bValue) {
			uintptr_t time = (0x17F8AE0 + (7 * 8));
			uint64_t time_scale = mem->Read<uint64_t>(mem->m_unityplayer + time);
			if (!Utils::valid_pointer(time_scale))
				continue;
			mem->Write<float>(time_scale + 0xFC, 2.0f);
		}
		else if (!MenuItems[27].bValue) {
			uintptr_t time = (0x17F8AE0 + (7 * 8));
			uint64_t time_scale = mem->Read<uint64_t>(mem->m_unityplayer + time);
			if (!Utils::valid_pointer(time_scale))
				continue;
			mem->Write<float>(time_scale + 0xFC, 1.0f);
		}*/

		Sleep(1);
	}
}

PVOID ViewMatrix() {
	while (true) {
		if (GetAsyncKeyState(VK_INSERT) & 1)
			Vars::Menu::enabled = !Vars::Menu::enabled;
		SDK::Globals::g_viewMatrix = glm::transpose(Utils::Camera::get_view_matrix());
		Sleep(1);
	}
}