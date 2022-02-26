#pragma once
#include <vector>
#include<algorithm>
char distBuf[256];
char nameBuf[256];
char weaponBuf[256];
char itemBuf[256];
char itemPriceBuf[256];
char extractBuf[256];
std::wstring name;
glm::vec2 player_screen{};
glm::vec2 player_screenHead{};
glm::vec2 item_screen{};
glm::vec2 body_screen{};
glm::vec2 extract_screen{};
glm::vec2 vHeadBoneOut, vHipOut, vNeckOut
, vUpperArmLeftOut, vUpperArmRightOut, vLeftHandOut
, vRightHandOut, vLeftHandOut1, vRightHandOut1
, vRightThighOut, vLeftThighOut, vRightCalfOut
, vLeftCalfOut, vLeftFootOut, vRightFootOut, PelvisOut;



void DrawPlayers() {

	
	for (auto& player : PlayerList) {

		if (!Utils::Camera::world_to_screen(player.headPosition, &player_screenHead)) continue;
		if (!Utils::Camera::world_to_screen(player.location, &player_screen)) continue;

		

		//if (MenuItems[3].bValue) {
			if (player.distance <= 300) {
				float BoxHeight = (float)(player_screen.y - player_screenHead.y);
				float BoxWidth = BoxHeight / 2.0f;
				//if(std::find(Friends.begin(), Friends.end(), player.instance) != Friends.end())
					//DrawNormalBox(player_screen.x - (BoxWidth / 2), player_screenHead.y, BoxWidth, BoxHeight, 1, &Col.green);
			//	else
					DrawNormalBox(player_screen.x - (BoxWidth / 2), player_screenHead.y, BoxWidth, BoxHeight, 1, &Col.white);
				DrawCircle(player_screenHead.x, player_screenHead.y, BoxHeight / 25, &Col.white, 100);
			}
		//}



		//if (MenuItems[5].bValue) {
			sprintf(nameBuf, "%ls", player.name.c_str());
			DrawStrokeText3(player_screen.x, player_screenHead.y, &player.color, nameBuf);

		//}
		//if (MenuItems[6].bValue)
		//{
			sprintf(weaponBuf, "%ls", player.weapon.c_str());

			DrawStrokeText2(player_screen.x, player_screen.y + 10, &player.color, weaponBuf);
		//}
		//if (MenuItems[7].bValue) {
			sprintf_s(distBuf, "[%0.0fm]", player.distance);
			DrawStrokeText2(player_screen.x, player_screen.y, &player.color, distBuf);
		//}

		if (player.instance == SDK::Globals::closest && Vars::Aimbot::snapLines) {
		
			DrawLine(Width / 2, Height / 2, player_screen.x, player_screen.y, &Col.white, 1);
		}


		/*if (!Utils::Camera::world_to_screen(player.vHeadBone, &vHeadBoneOut))
			continue;

		if (!Utils::Camera::world_to_screen(player.vHip, &vHipOut))
			continue;

		if (!Utils::Camera::world_to_screen(player.vNeck, &vNeckOut))
			continue;

		if (!Utils::Camera::world_to_screen(player.vUpperArmLeft, &vUpperArmLeftOut))
			continue;

		if (!Utils::Camera::world_to_screen(player.vUpperArmRight, &vUpperArmRightOut))
			continue;

		if (!Utils::Camera::world_to_screen(player.vLeftHand, &vLeftHandOut))
			continue;

		if (!Utils::Camera::world_to_screen(player.vRightHand, &vRightHandOut))
			continue;

		if (!Utils::Camera::world_to_screen(player.vLeftHand1, &vLeftHandOut1))
			continue;

		if (!Utils::Camera::world_to_screen(player.vRightHand1, &vRightHandOut1))
			continue;

		if (!Utils::Camera::world_to_screen(player.vRightThigh, &vRightThighOut))
			continue;

		if (!Utils::Camera::world_to_screen(player.vLeftThigh, &vLeftThighOut))
			continue;

		if (!Utils::Camera::world_to_screen(player.vRightCalf, &vRightCalfOut))
			continue;


		if (!Utils::Camera::world_to_screen(player.vLeftCalf, &vLeftCalfOut))
			continue;


		if (!Utils::Camera::world_to_screen(player.vLeftFoot, &vLeftFootOut))
			continue;

		if (!Utils::Camera::world_to_screen(player.vRightFoot, &vRightFootOut))
			continue;

		if (!Utils::Camera::world_to_screen(player.Pelvis, &PelvisOut))
			continue;
		DrawLine(vNeckOut.x, vNeckOut.y, vHeadBoneOut.x, vHeadBoneOut.y, &Col.green, 1);
		DrawLine(PelvisOut.x, PelvisOut.y, vNeckOut.x, vNeckOut.y, &Col.green, 1);

		DrawLine(vUpperArmLeftOut.x, vUpperArmLeftOut.y, vNeckOut.x, vNeckOut.y, &Col.green, 1);
		DrawLine(vUpperArmRightOut.x, vUpperArmRightOut.y, vNeckOut.x, vNeckOut.y, &Col.green, 1);

		DrawLine(vLeftHandOut.x, vLeftHandOut.y, vUpperArmLeftOut.x, vUpperArmLeftOut.y, &Col.green, 1);
		DrawLine(vRightHandOut.x, vRightHandOut.y, vUpperArmRightOut.x, vUpperArmRightOut.y, &Col.green, 1);

		DrawLine(vLeftHandOut.x, vLeftHandOut.y, vLeftHandOut1.x, vLeftHandOut1.y, &Col.green, 1);
		DrawLine(vRightHandOut.x, vRightHandOut.y, vRightHandOut1.x, vRightHandOut1.y, &Col.green, 1);

		DrawLine(vLeftThighOut.x, vLeftThighOut.y, vHipOut.x, vHipOut.y, &Col.green, 1);
		DrawLine(vRightThighOut.x, vRightThighOut.y, vHipOut.x, vHipOut.y, &Col.green, 1);

		DrawLine(vLeftCalfOut.x, vLeftCalfOut.y, vLeftThighOut.x, vLeftThighOut.y, &Col.green, 1);
		DrawLine(vRightCalfOut.x, vRightCalfOut.y, vRightThighOut.x, vRightThighOut.y, &Col.green, 1);

		DrawLine(vLeftFootOut.x, vLeftFootOut.y, vLeftCalfOut.x, vLeftCalfOut.y, &Col.green, 1);
		DrawLine(vRightFootOut.x, vRightFootOut.y, vRightCalfOut.x, vRightCalfOut.y, &Col.green, 1);
		//Line(Width / 2, Height / 2, player_screen.x, player_screen.y, 255, 0, 0, 255);*/
	}

}
void DrawItems() {


	for (auto& item : ItemsList) {

		//if (item.price < MenuItems[13].iValue)
		//	continue;
		if (!Utils::Camera::world_to_screen(item.location, &item_screen)) continue;

		//if (!MenuItems[12].bValue) {
			sprintf_s(itemBuf, "[%ls]", item.name.c_str());
			DrawStrokeText2(item_screen.x, item_screen.y, &Col.white, itemBuf);
		//}

		//if (MenuItems[12].bValue) {
			sprintf_s(itemPriceBuf, "%ls | %dk", item.name.c_str(), item.price);
			DrawStrokeText2(item_screen.x, item_screen.y + 10, &Col.white, itemPriceBuf);
		//}
	}

}


void DrawBodies() {

	for (auto& body : BodiesList) {

		//if (item.price < MenuItems[13].iValue)
			//continue;
		if (!Utils::Camera::world_to_screen(body.location, &body_screen)) continue;


		DrawStrokeText(body_screen.x, body_screen.y, &Col.purple, "[Deady Body]");
	}

}


void DrawExtracts() {

	for (auto& extract : ExtractsList) {


		if (!Utils::Camera::world_to_screen(extract.extractLocation, &extract_screen)) continue;

		sprintf_s(extractBuf, "[%ls]", extract.extractName.c_str());


		DrawStrokeText(extract_screen.x, extract_screen.y, &Col.green, extractBuf);

	}

}

void DrawGrenades() {

}
/*void DrawPlayers() {


	for (auto& player : PlayerList) {

		if (player.distance > visuals::MaxDistance)
			continue;
		std::cout << "drawplayer" << std::endl;
		if (!Utils::Camera::world_to_screen(player.headPosition, &player_screenHead)) continue;
		if (!Utils::Camera::world_to_screen(player.location, &player_screen)) continue;


		//colorr = &Col.white;
		//name = L"Player Scav";
		if (player.isScav) {
			switch (player.role) {
			case 1:
				name = L"Scav";
				//colorr = &Col.yellow;
				break;
			case 2:
				name = L"Scav";
				//colorr = &Col.yellow;
				break;
			case 4:
				name = L"Boss Test";
				//colorr = &Col.red;
				break;
			case 8:
				name = L"Reshala"; // Rashalla
				//colorr = &Col.red;
				break;
			case 16:
				name = L"Follower Test";
				//colorr = &Col.orange;
				break;
			case 32:
				name = L"Reshala Guard";
				//colorr = &Col.orange;
				break;
			case 64:
				name = L"Killa";
				//colorr = &Col.red;
				break;
			case 128:
				name = L"Shturman";
				//colorr = &Col.red;
				break;
			case 256:
				name = L"Shturman Guard";
				//colorr = &Col.orange;
				break;
			case 512:
				name = L"PMC Raider";
				//colorr = &Col.blues;
				break;
			case 1024:
				name = L"Cursed Scav";
				//colorr = &Col.orange;
				break;
			case 2048:
				name = L"Gluhar";
				//colorr = &Col.red;
				break;
			case 4096:
				name = L"Gluhar Assault";
				//colorr = &Col.orange;
				break;
			case 8192:
				name = L"Gluhar Security";
				//colorr = &Col.orange;
				break;
			case 16384:
				name = L"Gluhar Scout";
				//colorr = &Col.orange;
				break;
			case 32768:
				name = L"Gluhar Sniper";
				//colorr = &Col.orange;
				break;
			case 65536:
				name = L"Sanitar Guard";
				//colorr = &Col.orange;
				break;
			case 131072:
				name = L"Sanitar";
				//colorr = &Col.red;
				break;
			case 262144:
				name = L"Test";
				//colorr = &Col.orange;
				break;
			case 524288:
				name = L"Assault Raider";
				//colorr = &Col.orange;
				break;
			case 1048576:
				name = L"Sectant Warrior";
				//colorr = &Col.orange;
				break;
			case 2097152:
				name = L"Sectant Priest";
				//colorr = &Col.orange;
				break;
			case 4194304:
				name = L"Tagilla";
				//colorr = &Col.red;
				break;
			case 8388608:
				name = L"Tagilla Guard";
				//colorr = &Col.orange;
				break;
			case 16777216:
				name = L"Ex-PMC";
				//colorr = &Col.orange;
				break;
			case 33554432:
				name = L"SANTA!!!!";
				//colorr = &Col.purple;
				break;
			default:
				name = L"Player Scav";
				break;
			}

		}
		else if (player.isPlayer) {
			//if (player.isPlayer)
			name = player.name;
			//else
				//name = L"Player Scav";

		}




		if (player.instance == SDK::Globals::closest) {
			if (visuals::showDistance) {
				sprintf_s(distBuf, "[%0.0fm]", player.distance);
				DrawStrokeText(player_screen.x, player_screen.y + 30, &Col.red, distBuf);
			}

			//float BoxHeight = (float)(player_screen.y - player_screen2.y);
			//std::cout << "d" << std::endl;
			//DrawString(12, player_screen.x, player_screen.y, &Col.white, true, true, distBuf);
			float BoxHeight = (float)(player_screen.y - player_screenHead.y) + 10.f;
			float BoxWidth = BoxHeight / 3.0f;
			if (visuals::show_head)
				DrawCircle(player_screenHead.x, player_screenHead.y, 5, &Col.red, 100);
			if (visuals::weapon) {
				sprintf_s(weaponBuf, "%ls", player.weapon.c_str());

				DrawStrokeText(player_screen.x, player_screen.y + 45, &Col.red, weaponBuf);
			}
			if (visuals::name) {
				sprintf_s(nameBuf, "%S", name.c_str());
				DrawStrokeText(player_screen.x, player_screen.y + 15, &Col.red, nameBuf);
			}


			if (visuals::box)
				DrawNormalBox(player_screen.x - (BoxWidth / 2), player_screenHead.y, BoxWidth, BoxHeight, menu::box_thick, &Col.red);
			if (visuals::lines)
				DrawLine(Width / 2, Height / 2, player_screenHead.x, player_screenHead.y, &Col.white_, 1);

		}
		else {
			if (visuals::showDistance) {
				sprintf_s(distBuf, "[%0.0fm]", player.distance);
				DrawStrokeText(player_screen.x, player_screen.y + 30, colorr, distBuf);
			}

			//float BoxHeight = (float)(player_screen.y - player_screen2.y);
			//std::cout << "d" << std::endl;
			//DrawString(12, player_screen.x, player_screen.y, &Col.white, true, true, distBuf);
			float BoxHeight = (float)(player_screen.y - player_screenHead.y) + 10.f;
			float BoxWidth = BoxHeight / 3.0f;
			if (visuals::show_head)
				DrawCircle(player_screenHead.x, player_screenHead.y, 5, &Col.white, 100);
			if (visuals::weapon) {
				sprintf_s(weaponBuf, "%ls", player.weapon.c_str());

				DrawStrokeText(player_screen.x, player_screen.y + 45, colorr, weaponBuf);
			}
			if (visuals::name) {


				sprintf_s(nameBuf, "%S", name.c_str());
				DrawStrokeText(player_screen.x, player_screen.y + 15, colorr, nameBuf);


			}


			if (visuals::box)
				DrawNormalBox(player_screen.x - (BoxWidth / 2), player_screenHead.y, BoxWidth, BoxHeight, menu::box_thick, colorr);
		}

	}
}


char itemNameBuf[256];
void DrawBones() {

	glm::vec2 item_screen{};
	for (auto& item : ItemsList) {
		if (item.price < visuals::minItemPrice)
			continue;
		//if (glm::distance(item.location, SDK::Globals::localHeadPos) > visuals::itemDistance)
		//	continue;
		//std::cout << item.location.x << " " << item.location.y << " " << item.location.z << std::endl;
		if (!Utils::Camera::world_to_screen(item.location, &item_screen)) continue;
		if (visuals::itemName) {
			sprintf_s(itemNameBuf, "[%S]", item.name.c_str());
			DrawStrokeText(item_screen.x, item_screen.y, &Col.white, itemNameBuf);
		}
		if (visuals::itemPrice) {
			sprintf_s(itemNameBuf, "[%d]", item.price);
			DrawStrokeText(item_screen.x, item_screen.y + 15, &Col.white, itemNameBuf);
		}
	}
}

char extractNameBuf[256];
char extractDistanceBuf[256];
char extractStatusBuf[256];
void DrawExtracts() {

	glm::vec2 extract_screen{};
	for (auto& extract : ExtractsList) {
		if (!Utils::Camera::world_to_screen(extract.extractLocation, &extract_screen)) continue;
		//std::wcout << extract.extractName << std::endl;
		RGBA* color;
		std::wstring status;
		switch (extract.status) {
		case 1:
			status = L"Not Open";
			color = &Col.red;
			break;
		case 2:
			status = L"Incomplete";
			color = &Col.red;
			break;
		case 3:
			status = L"Countdown";
			color = &Col.yellow;
			break;
		case 4:
			status = L"Open";
			color = &Col.greens;
			break;
		case 5:
			status = L"Pending";
			color = &Col.yellow;
			break;
		case 6:
			status = L"Awaiting Manual Activation";
			color = &Col.yellow;
			break;
		default:
			status = L"Error";
			color = &Col.red;
			break;
		}
		//std::cout << extract.location.x << " " << extract.location.y << " " << extract.location.z << std::endl;
		//std::cout << item.location.x << " " << item.location.y << " " << item.location.z << std::endl;

		sprintf_s(extractNameBuf, "[%S]", extract.extractName.c_str());
		DrawString(12.f, extract_screen.x, extract_screen.y, color, true, true, extractNameBuf);
		if (visuals::extractStatus) {

			sprintf_s(extractStatusBuf, "[%S]", status.c_str());
			DrawString(12.f, extract_screen.x, extract_screen.y + 15, color, true, true, extractStatusBuf);
		}
		//extract.GetDistance();
		//std::wcout << extract.name << ": " << extract.distance << std::endl;
		//sprintf_s(extractDistanceBuf, "[%0.0fm]", extract.distance);
	   // DrawString(12.f, extract_screen.x, extract_screen.y + 15, &Col.red, true, true, extractDistanceBuf);
	}
}

char grenadesNameBuf[256];
char grenadesDistanceBuf[256];
void DrawGrenades() {

	glm::vec2 grenade_screen{};
	for (auto& grenade : GrenadesList) {

		//std::cout << extract.location.x << " " << extract.location.y << " " << extract.location.z << std::endl;
		//std::cout << item.location.x << " " << item.location.y << " " << item.location.z << std::endl;
		if (!Utils::Camera::world_to_screen(grenade.location, &grenade_screen)) continue;

		DrawString(12.f, grenade_screen.x, grenade_screen.y, &Col.red, true, true, "Grenade");
		grenade.GetDistance();
		sprintf_s(grenadesDistanceBuf, "[%0.0fm]", grenade.distance);
		DrawString(12.f, grenade_screen.x, grenade_screen.y + 15, &Col.red, true, true, grenadesDistanceBuf);
	}
}*/

