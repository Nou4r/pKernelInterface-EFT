#pragma once
#include <experimental/filesystem>
#include "Json/json.hpp"



bool itemEsp = false;
class Item {
private:
	uintptr_t LootArray;
	
	
	//std::vector<Item> ItemList;

	uintptr_t Index(int index) {
		return mem->Read<uint64_t>(LootArray + 0x20 + (index * 0x08));
	}
public:
	uintptr_t instance;
	glm::vec3 location;
	std::wstring name;
	uint64_t m_lItemProfile;
	uint64_t m_lItemBasicInfo;
	uint64_t m_lItemLocalization;
	uint64_t m_lItemCoordinates;
	uint64_t m_lItemLocationContainer;
	int price;
	uint64_t Template;

	explicit Item(int index) {
		uint64_t LootList = mem->Read<uint64_t>(SDK::Globals::g_localGameWorld + 0x60);
		if (!Utils::valid_pointer(LootList))
			return;


		LootArray = mem->Read<uint64_t>(LootList + 0x10);
		if (!Utils::valid_pointer(LootArray))
			return;

		instance = Index(index);
	}

	bool Init(){

			m_lItemProfile = mem->Read<uint64_t>(instance + 0x10);
			if (!Utils::valid_pointer(m_lItemProfile))
				return false;
			m_lItemBasicInfo = mem->Read<uint64_t>(m_lItemProfile + 0x30);
			if (!Utils::valid_pointer(m_lItemBasicInfo))
				return false;
			m_lItemLocalization = mem->Read<uint64_t>(m_lItemBasicInfo + 0x30);
			if (!Utils::valid_pointer(m_lItemLocalization))
				return false;
			m_lItemCoordinates = mem->Read<uint64_t>(m_lItemLocalization + 0x8);
			if (!Utils::valid_pointer(m_lItemCoordinates))
				return false;
			m_lItemLocationContainer = mem->Read<uint64_t>(m_lItemCoordinates + 0x38);
			if (!Utils::valid_pointer(m_lItemLocationContainer))
				return false;
			//Template = mem->ReadChain(instance, { 0x10, 0x28, 0x50, 0x40 });
			//if (Template <= 0)
				//return false;
			return true;
	}

	void GetLocation() {
		location =  mem->Read<glm::vec3>(m_lItemLocationContainer + 0x90);
	}
	//void IsQuestItem() {
	//	questItem = mem->Read<bool>(Template + 0x94);
	//}
};

