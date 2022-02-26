#pragma once


class Extract {
private:
	uintptr_t exitPoint;
	

	uintptr_t Index(int index) {
		return mem->Read<uint64_t>(exitPoint + 0x20 + (index * 0x08));
	}
public:
	uintptr_t instance;
	glm::vec3 extractLocation;
	std::wstring extractName;
	int status;
	float distance;

	explicit Extract(int index) {
		instance = Index(index);
	}

	bool Init() {

		uintptr_t exitController = mem->Read<uintptr_t>(SDK::Globals::g_localGameWorld + 0x18);
		if (!Utils::valid_pointer(exitController))
			return false;
		exitPoint = mem->Read<uintptr_t>(exitController + 0x20);
		if (!Utils::valid_pointer(exitPoint))
			return false;
		//exitCount = mem->Read<int>(exitPoint + 0x18);
		//if (!exitCount)
		//	return false;
		
		

		return true;
	}

	void GetPos() {
		//transform = mem->ReadChain<uint64_t>(instance, { 0x10, 0x30, 0x30, 0x8, 0x28 });
		//if (!transform)
		//	return;
		extractLocation = Utils::Player::Bones::get_transform_position(mem->ReadChain<uint64_t>(instance, { 0x10, 0x30, 0x30, 0x8, 0x28 }));
	}

	void GetExtractName() {
		extractName = mem->GetWString(mem->ReadChain<uint64_t>(instance, { 0x58, 0x10 }));
	}

	void GetDistance() {
		distance = glm::distance(SDK::Globals::localHeadPos, extractLocation);
	}

	void GetExtractStatus() {
		//int stat = mem->Read<int>(instance + 0xA8); /* NotOpen = 1// Imcpmpleterequirement = 2 // Countdown = 3 // Open = 4 // Pending = 5 // Awaot ,amial Activation = 6*/
		status = mem->Read<int>(instance + 0xA8);
		
	}


};

