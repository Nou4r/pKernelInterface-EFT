#pragma once
#include <Windows.h>
#include "CheatData.h"
#include <vector>

namespace SDK {
	namespace Globals
	{
		uintptr_t g_gameObjectManager;
		uintptr_t g_fpsCamera;
		glm::highp_mat4 g_viewMatrix;
		uintptr_t g_gameWorld;
		uintptr_t g_applicationMain;
		uintptr_t g_localGameWorld;
		uintptr_t g_onlineUsers;
		uintptr_t closest;
		uintptr_t hands;
		glm::vec3 firePortPos;
		glm::vec2 hands_Screen{};
		float localFov;
		int g_playerCount;
		//std::vector<EFTPlayer> tmpPlayers;
		int LootCount;
		glm::vec3 localHeadPos;
		uint64_t matrix_list_base = 0;
		uint64_t dependency_index_table_base = 0;

		int Width = GetSystemMetrics(SM_CXSCREEN);
		int Height = GetSystemMetrics(SM_CYSCREEN);
	};

	namespace Entity {
		
		
		uintptr_t g_localPlayer;

		namespace Enums {
			
				enum EPlayerSide : int
				{
					Usec = 1,
					Bear,
					Savage = 4
				};



		}
	}
};