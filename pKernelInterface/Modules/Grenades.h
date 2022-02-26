#pragma once


class Grenade {
private:
	uint64_t Grenades;
	uint64_t GrenadeList;
	uint64_t ListStart;
	int exitCount;


	uintptr_t Index(int index) {
		return mem->Read<uint64_t>(ListStart + 0x20 + (index * 0x08));
	}
public:
	uintptr_t instance;
	glm::vec3 location;
	std::wstring name;
	float distance;


	explicit Grenade(int index) {
		instance = Index(index);
	}

	bool Init() {
		Grenades = mem->Read<uint64_t>(SDK::Globals::g_localGameWorld + 0xE8);
		//std::cout << Grenades << std::endl;
		if (!Grenades)
			return false;
		GrenadeList = mem->Read<uint64_t>(Grenades + 0x18);
		//std::cout << GrenadeList << std::endl;
		if (!GrenadeList)
			return false;

		ListStart = mem->Read<uint64_t>(GrenadeList + 0x10);
		if (!ListStart)
			return false;

		return true;
	}

	void GetLocation() {
		location = mem->Read<glm::vec3>(mem->ReadChain<uint64_t>(instance, { 0x10, 0x30, 0x30, 0x8, 0x38 }) + 0x90);
	}

	void GetName() {
		//name = mem->GetWString(mem->ReadChain<uint64_t>(instance, { 0x58, 0x10 }));
	}

	void GetDistance() {
		distance = glm::distance(SDK::Globals::localHeadPos, location);
	}


};

