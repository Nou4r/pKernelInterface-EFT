#pragma once



RGBA orangecol = Col.orange;
RGBA greencol = Col.green;
RGBA redcol = Col.red;
RGBA bluecol = Col.blue;
RGBA purplecol = Col.purple;
class Player {
private:
	uint64_t list_base;
	uintptr_t transform;


	uintptr_t Index(int index) {
		return mem->Read<uint64_t>(list_base + 0x20 + (index * 0x08));
	}
public:
	uintptr_t instance;
	glm::vec3 headPosition;
	glm::vec3 location;
	std::wstring name;
	std::wstring role;
	RGBA color;
	float distance;
	bool isScav;
	bool isPlayer;
	bool isPlayerScav;
	
	int roleInt;
	std::wstring weapon;
	glm::vec3 vHeadBone, vHip, vNeck
		, vUpperArmLeft, vUpperArmRight, vLeftHand
		, vRightHand, vLeftHand1, vRightHand1
		, vRightThigh, vLeftThigh, vRightCalf
		, vLeftCalf, vLeftFoot, vRightFoot, Pelvis;
	//explicit Player(int index) {
		//instance = Index(index);
	//}

	bool Init() {


		//list_base = mem->Read<uint64_t>(SDK::Globals::g_onlineUsers + 0x10);
		//if (!Utils::valid_pointer(list_base))
		//	return false;


		return true;
	}

	void GetRootPosition() {
		uint64_t bone_matrix = Utils::Player::Bones::getbone_matrix(instance);
		if (!Utils::valid_pointer(bone_matrix))
			return;
		uint64_t bone = mem->ReadChain<uint64_t>(bone_matrix, { 0x20, 0x10, 0x38 });
		if (!Utils::valid_pointer(bone))
			return;
		location = mem->Read<glm::vec3>(bone + 0x90);
	}

	void GetHeadPosition() {
		headPosition = Utils::Player::Bones::get_bone_position(instance, 133);
	}



	void GetDistance() {
		distance = glm::distance(location, SDK::Globals::localHeadPos);
	}

	uint64_t GetPlayerInfo() {
		return mem->Read<uint64_t>(mem->Read<uint64_t>(instance + 0x4B8) + 0x28);
	}

	int GetRole() {
		uint64_t settings = mem->Read<uint64_t>(GetPlayerInfo() + 0x38);
		if (!Utils::valid_pointer(settings))
			return 0;
		return mem->Read<int>(settings + 0x10);
	}

	void is_scav()
	{
		INT32 entity_id = Utils::Player::Info::GetRegistrationDate(this->instance);
		if (!Utils::valid_pointer(entity_id))
			return;
		INT32 entity_side = Utils::Player::Info::GetSide(this->instance);
		if (!Utils::valid_pointer(entity_side))
			return;


		if (entity_id == 0)
			this->isScav = true;
		else if (entity_id != 0 && entity_side == 4)
			this->isPlayerScav = true;
	}
	bool HasSpecialCharacters(const wchar_t* str)
	{
		return str[wcsspn(str, L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_")] != 0;
	}
	void GetName() {


		
		name = L"Player Scav";
		color = orangecol;
		if (Utils::Player::Info::is_player(instance)) {
			uint64_t GetProfile = mem->Read<uint64_t>(instance + 0x4B8);
			if (!Utils::valid_pointer(GetProfile))
				return;
			uint64_t playerinfo = mem->Read<uint64_t>(GetProfile + 0x28);
			if (!Utils::valid_pointer(playerinfo))
				return;
			const auto player_name_ptr = mem->Read<uintptr_t>(playerinfo + 0x10);
			if (!Utils::valid_pointer(player_name_ptr))
				return;
			if(HasSpecialCharacters(mem->GetWString(player_name_ptr).c_str()))
				name = L"Player Scav";
			else
				name = mem->GetWString(player_name_ptr);
			color = bluecol;
		}
		//else if (this->isPlayerScav){
			//name = L"Player Scav";
			//color = orangecol;
		//}
		else if (Utils::Player::Info::is_scav(instance)) {

			switch (GetRole()) {
			case 1:
				name = L"Scav";
				color = orangecol;
				break;
			case 2:
				name = L"Scav";
				color = orangecol;
				break;
			case 4:
				name = L"Boss Test";
				color = redcol;
				break;
			case 8:
				name = L"Reshala"; // Rashalla
				color = redcol;
				break;
			case 16:
				name = L"Follower Test";
				color = orangecol;
				break;
			case 32:
				name = L"Reshala Guard";
				color = orangecol;
				break;
			case 64:
				name = L"Killa";
				color = redcol;
				break;
			case 128:
				name = L"Shturman";
				color = redcol;
				break;
			case 256:
				name = L"Shturman Guard";
				color = orangecol;
				break;
			case 512:
				name = L"PMC Raider";
				color = bluecol;
				break;
			case 1024:
				name = L"Cursed Scav";
				color = orangecol;
				break;
			case 2048:
				name = L"Gluhar";
				color = redcol;
				break;
			case 4096:
				name = L"Gluhar Assault";
				color = orangecol;
				break;
			case 8192:
				name = L"Gluhar Security";
				color = orangecol;
				break;
			case 16384:
				name = L"Gluhar Scout";
				color = orangecol;
				break;
			case 32768:
				name = L"Gluhar Sniper";
				color = orangecol;
				break;
			case 65536:
				name = L"Sanitar Guard";
				color = orangecol;
				break;
			case 131072:
				name = L"Sanitar";
				color = redcol;
				break;
			case 262144:
				name = L"Test";
				color = orangecol;
				break;
			case 524288:
				name = L"Assault Raider";
				color = orangecol;
				break;
			case 1048576:
				name = L"Sectant Warrior";
				color = orangecol;
				break;
			case 2097152:
				name = L"Sectant Priest";
				color = orangecol;
				break;
			case 4194304:
				name = L"Tagilla";
				color = redcol;
				break;
			case 8388608:
				name = L"Tagilla Guard";
				color = orangecol;
				break;
			case 16777216:
				name = L"Ex-PMC";
				color = orangecol;
				break;
			case 33554432:
				name = L"SANTA!!!!";
				color = purplecol;
				break;
			}

		}

		if (std::find(Friends.begin(), Friends.end(), instance) != Friends.end())
			color = greencol;

			//if (get_player_group(local::local_player) == player.groupId) {
				//color = &Col.greens;
			//}
			//name = mem->GetWString(mem->ReadChain<uint64_t>(instance, { 0x58, 0x10 }));
			//color = &Col.greens;
		//else
		//	name = mem->GetWString(mem->ReadChain<uint64_t>(instance, { 0x58, 0x10 }));
		//name = mem->GetWString(mem->ReadChain<uint64_t>(instance, { 0x58, 0x10 }));
		//if (name == L"") {
		//	name = L"Scav";
		//}
	}

	void GetWeaponName() {
		uint64_t ProceduralWeaponAnimation = mem->Read<uint64_t>(instance + 0x190);
		if (!Utils::valid_pointer(ProceduralWeaponAnimation))
			return;
		uint64_t weaponId = mem->ReadChain<uint64_t>(ProceduralWeaponAnimation, { 0x48, 0x28, 0x40 });
		if (!Utils::valid_pointer(weaponId))
			return;
		uint64_t EngineString = mem->Read<uint64_t>(weaponId + 0x18);
		if (!Utils::valid_pointer(EngineString))
			return;
		int32_t nameLength = mem->Read<int32_t>(EngineString + 0x10);
		weapon = mem->GetWString(EngineString);
	}

	void GetBones() {
		 vHeadBone = Utils::Player::Bones::get_bone_position(instance, 133);


		 vHip =Utils::Player::Bones::get_bone_position(instance, 14);


		 vNeck =Utils::Player::Bones::get_bone_position(instance, 132);


		 vUpperArmLeft =Utils::Player::Bones::get_bone_position(instance, 90);
		

		 vUpperArmRight =Utils::Player::Bones::get_bone_position(instance, 111);


		 vLeftHand =Utils::Player::Bones::get_bone_position(instance, 91);


		 vRightHand =Utils::Player::Bones::get_bone_position(instance, 112);


		 vLeftHand1 =Utils::Player::Bones::get_bone_position(instance, 92);


		 vRightHand1 =Utils::Player::Bones::get_bone_position(instance, 113);


		 vRightThigh =Utils::Player::Bones::get_bone_position(instance, 20);


		 vLeftThigh =Utils::Player::Bones::get_bone_position(instance, 15);


		 vRightCalf =Utils::Player::Bones::get_bone_position(instance, 22);


		 vLeftCalf =Utils::Player::Bones::get_bone_position(instance, 17);


		 vLeftFoot =Utils::Player::Bones::get_bone_position(instance, 18);


		 vRightFoot =Utils::Player::Bones::get_bone_position(instance, 23);


		 Pelvis =Utils::Player::Bones::get_bone_position(instance, 14);

	}


};

