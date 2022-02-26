#pragma once
#include <iostream>
#include "globals.h"

#include <vector>
#include "glm/glm.hpp"

namespace Type
{
	enum Player
	{
		Human = 1,
		Zombie,
		Unknown
	};
}

struct EFTPlayer
{
	uint64_t instance;
	glm::vec3 location;
	bool isScav;
	bool isPlayer;
	glm::vec3 headPos;
	float health;
	std::wstring name;
	std::wstring groupId;
	float distance;
	uint64_t Mesh;
	DWORD color;
	glm::vec3 barrelPos;
	glm::vec2 bar_screen{};
	std::wstring weapon;
	glm::vec2 rotation;
	glm::vec2 vHeadBoneOut, vHipOut, vNeckOut
		, vUpperArmLeftOut, vUpperArmRightOut, vLeftHandOut
		, vRightHandOut, vLeftHandOut1, vRightHandOut1
		, vRightThighOut, vLeftThighOut, vRightCalfOut
		, vLeftCalfOut, vLeftFootOut, vRightFootOut, PelvisOut;
	std::wstring role;

};

struct BonesArray
{
	glm::vec2 vHeadBoneOut, vHipOut, vNeckOut
		, vUpperArmLeftOut, vUpperArmRightOut, vLeftHandOut
		, vRightHandOut, vLeftHandOut1, vRightHandOut1
		, vRightThighOut, vLeftThighOut, vRightCalfOut
		, vLeftCalfOut, vLeftFootOut, vRightFootOut, PelvisOut;
};

//typedef struct Item Player;

