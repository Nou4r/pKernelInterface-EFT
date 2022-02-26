#pragma once
#include "Memory/KernelInterface.h"
#include <xmmintrin.h>
#include <emmintrin.h>
#include "glm/glm.hpp"
#include <iostream>
#include <codecvt>
#include <string>
namespace Utils {
    inline auto valid_pointer(uintptr_t pointer) -> bool {
        return (pointer && pointer > 0xFFFFFF && pointer < 0x7FFFFFFFFFFF);
    }
    struct BaseObject
        {
            uint64_t previousObjectLink; //0x0000
            uint64_t nextObjectLink; //0x0008
            uint64_t object; //0x0010
        };
    uintptr_t get_object_by_name(std::string object_name)
        {

            char name[256];
            uintptr_t lastActiveObject = mem->Read<uintptr_t>(SDK::Globals::g_gameObjectManager + 0x20);
            uintptr_t activeObjects = mem->Read<uintptr_t>(SDK::Globals::g_gameObjectManager + 0x28);

            uint64_t classNamePtr = 0x0;    

            int i = 0;

            BaseObject activeObject = mem->Read<BaseObject>(activeObjects);
            BaseObject lastObject = mem->Read<BaseObject>(lastActiveObject);
           // std::cout << "-------------------" << std::endl;
            if (activeObject.object != 0x0)
            {
                while (activeObject.object != 0 && activeObject.object != lastObject.object)
                {
                    classNamePtr = mem->Read<uint64_t>(activeObject.object + 0x60);

                    mem->Read(classNamePtr, &name, sizeof(name));
                    std::string name1 = name;
                   // std::cout << name << std::endl;
                    if (name1.find(object_name) != std::string::npos)
                    {

                        return activeObject.object;
                    }

                    activeObject = mem->Read<BaseObject>(activeObject.nextObjectLink);

                }
            }

            if (lastObject.object != 0x0)
            {
                classNamePtr = mem->Read<uint64_t>(lastObject.object + 0x60);
                mem->Read(classNamePtr, &name, sizeof(name));
                std::string name1 = name;
               // std::cout << name << std::endl;
                if (name1.find(object_name) != std::string::npos)
                {
                    return lastObject.object;
                }
            }
            //std::cout << "-------------------" << std::endl;
        }
    uintptr_t get_tagged_object_by_name(std::string object_name)
        {

            char name[256];
            uintptr_t lastActiveObject = mem->Read<uintptr_t>(SDK::Globals::g_gameObjectManager + 0x10);
            uintptr_t activeObjects = mem->Read<uintptr_t>(SDK::Globals::g_gameObjectManager + 0x18);

            uint64_t classNamePtr = 0x0;

            int i = 0;
           // std::cout << "-------------------" << std::endl;
            BaseObject activeObject = mem->Read<BaseObject>(activeObjects);
            BaseObject lastObject = mem->Read<BaseObject>(lastActiveObject);

            if (activeObject.object != 0x0)
            {
                while (activeObject.object != 0 && activeObject.object != lastObject.object)
                {
                    classNamePtr = mem->Read<uint64_t>(activeObject.object + 0x60);

                    mem->Read(classNamePtr + 0x0, &name, sizeof(name));

                    
                    std::string name1 = name;
                    std::cout << name << std::endl;
                    if (name1.find(object_name) != std::string::npos)
                    {
                        //std::cout << name << std::endl;
                        return activeObject.object;
                    }

                    activeObject = mem->Read<BaseObject>(activeObject.nextObjectLink);
                   // std::cout << name << std::endl;
                }
            }

            if (lastObject.object != 0x0)
            {
                classNamePtr = mem->Read<uint64_t>(lastObject.object + 0x60);
                mem->Read(classNamePtr + 0x0, &name, sizeof(name));
                std::string name1 = name;
                std::cout << name << std::endl;
                if (name1.find(object_name) != std::string::npos)
                {
                    //std::cout << name << std::endl;
                    return lastObject.object;
                }
                //std::cout << name << std::endl;
            }
            //std::cout << "-------------------" << std::endl;
        }

    uint64_t GetObjectFromList(uint64_t listPtr, uint64_t lastObjectPtr, const char* objectName)
    {
        char name[256];
        uint64_t classNamePtr = 0x0;

        BaseObject activeObject = mem->Read<BaseObject>(listPtr);
        BaseObject lastObject = mem->Read<BaseObject>(lastObjectPtr);
      //  std::cout << "-------------------" << std::endl;
        if (activeObject.object != 0x0)
        {
            while (activeObject.object != 0 && activeObject.object != lastObject.object)
            {
                classNamePtr = mem->Read<uint64_t>(activeObject.object + 0x60);
                mem->Read(classNamePtr + 0x0, &name, sizeof(name));
             //   std::cout << name << std::endl;
                if (strcmp(name, objectName) == 0)
                {
                    return activeObject.object;
                }

                activeObject = mem->Read<BaseObject>(activeObject.nextObjectLink);
            }
        }
        if (lastObject.object != 0x0)
        {
            classNamePtr = mem->Read<uint64_t>(lastObject.object + 0x60);
            mem->Read(classNamePtr + 0x0, &name, 256);
           // std::cout << name << std::endl;
            if (strcmp(name, objectName) == 0)
            {
                return lastObject.object;
            }
        }
      //  std::cout << "-------------------" << std::endl;
        return uint64_t();
    }

    uint64_t GetComponentFromGameObject(uint64_t game_object, const char* component_name)
    {
        char Name[256];

        uint64_t Test = mem->Read<uint64_t>(game_object + 0x30);

        for (int i = 0x8; i < 0x1000; i += 0x10)
        {
            uint64_t Fields = mem->Read<uint64_t>(mem->Read<uint64_t>(Test + i) + 0x28);

            uint64_t NameChain = mem->ReadChain<uint64_t>(Fields, { 0x0, 0x0, 0x48 });

            mem->Read(NameChain, &Name, 256);

            if (strcmp(Name, component_name) == 0)
            {
                return Fields;
            }
        }

        return 0;
    }
   


    namespace Player {

        
        namespace Bones {
            uintptr_t get_bone_transform(uintptr_t instance, int bone) {
                uintptr_t bone_info = mem->ReadChain<uint64_t>(instance, { 0xA8 , 0x28, 0x28, 0x10 });
                if (!bone_info)
                    return 0;
                uintptr_t transform = mem->Read<uintptr_t>(mem->Read<uintptr_t>(bone_info + 0x20 + (bone * 0x8)) + 0x10);
                if (!transform)
                    return 0;
                return transform;
            }
            glm::vec3 get_transform_position1(int64_t pMatrix, uint32_t index)
            {
                uint64_t matrix_list_base = 0;
                uint64_t dependency_index_table_base = 0;
                mem->Read(pMatrix + 0x18, &matrix_list_base, sizeof(matrix_list_base));
                mem->Read(pMatrix + 0x20, &dependency_index_table_base, sizeof(dependency_index_table_base));

                static auto get_dependency_index = [](uint64_t base, int32_t index) {
                    //read_memory(base + index * 4, uint64_t(&index), sizeof(index));
                    index = mem->Read<uint32_t>(base + index * 4);
                    return index;
                };

                static auto get_matrix_blob = [](uint64_t base, uint64_t offs, float* blob, uint32_t size) {
                    mem->Read(base + offs, blob, size);
                };

                int32_t index_relation = get_dependency_index(dependency_index_table_base, index);

                glm::vec3 ret_value;
                {
                    float* base_matrix3x4 = (float*)malloc(64),
                        * matrix3x4_buffer0 = (float*)((uint64_t)base_matrix3x4 + 16),
                        * matrix3x4_buffer1 = (float*)((uint64_t)base_matrix3x4 + 32),
                        * matrix3x4_buffer2 = (float*)((uint64_t)base_matrix3x4 + 48);

                    get_matrix_blob(matrix_list_base, index * 48, base_matrix3x4, 16);

                    __m128 xmmword_1410D1340 = { -2.f, 2.f, -2.f, 0.f };
                    __m128 xmmword_1410D1350 = { 2.f, -2.f, -2.f, 0.f };
                    __m128 xmmword_1410D1360 = { -2.f, -2.f, 2.f, 0.f };

                    while (index_relation >= 0) {
                        uint32_t matrix_relation_index = 6 * index_relation;

                        // paziuret kur tik 3 nureadina, ten translationas, kur 4 = quatas ir yra rotationas.
                        get_matrix_blob(matrix_list_base, 8 * matrix_relation_index, matrix3x4_buffer2, 16);
                        __m128 v_0 = *(__m128*)matrix3x4_buffer2;

                        get_matrix_blob(matrix_list_base, 8 * matrix_relation_index + 32, matrix3x4_buffer0, 16);
                        __m128 v_1 = *(__m128*)matrix3x4_buffer0;

                        get_matrix_blob(matrix_list_base, 8 * matrix_relation_index + 16, matrix3x4_buffer1, 16);
                        __m128i v9 = *(__m128i*)matrix3x4_buffer1;

                        __m128* v3 = (__m128*)base_matrix3x4; // r10@1
                        __m128 v10; // xmm9@2
                        __m128 v11; // xmm3@2
                        __m128 v12; // xmm8@2
                        __m128 v13; // xmm4@2
                        __m128 v14; // xmm2@2
                        __m128 v15; // xmm5@2
                        __m128 v16; // xmm6@2
                        __m128 v17; // xmm7@2

                        v10 = _mm_mul_ps(v_1, *v3);
                        v11 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, 0));
                        v12 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, 85));
                        v13 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, -114));
                        v14 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, -37));
                        v15 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, -86));
                        v16 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, 113));

                        v17 = _mm_add_ps(
                            _mm_add_ps(
                                _mm_add_ps(
                                    _mm_mul_ps(
                                        _mm_sub_ps(
                                            _mm_mul_ps(_mm_mul_ps(v11, (__m128)xmmword_1410D1350), v13),
                                            _mm_mul_ps(_mm_mul_ps(v12, (__m128)xmmword_1410D1360), v14)),
                                        _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), -86))),
                                    _mm_mul_ps(
                                        _mm_sub_ps(
                                            _mm_mul_ps(_mm_mul_ps(v15, (__m128)xmmword_1410D1360), v14),
                                            _mm_mul_ps(_mm_mul_ps(v11, (__m128)xmmword_1410D1340), v16)),
                                        _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 85)))),
                                _mm_add_ps(
                                    _mm_mul_ps(
                                        _mm_sub_ps(
                                            _mm_mul_ps(_mm_mul_ps(v12, (__m128)xmmword_1410D1340), v16),
                                            _mm_mul_ps(_mm_mul_ps(v15, (__m128)xmmword_1410D1350), v13)),
                                        _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 0))),
                                    v10)),
                            v_0);

                        *v3 = v17;

                        index_relation = get_dependency_index(dependency_index_table_base, index_relation);
                    }
                    ret_value = *(glm::vec3*)base_matrix3x4;
                    delete[] base_matrix3x4;
                }
                return ret_value;
            }
            glm::vec3 get_transform_position(uint64_t transform) {
                auto transform_internal = mem->Read<uint64_t>(transform + 0x10);
                if (!transform_internal)
                    return  glm::vec3();

                auto matrices = mem->Read<uint64_t>(transform_internal + 0x38);
                if (!matrices)
                    return glm::vec3();
                auto index = mem->Read<uint32_t>(transform_internal + 0x40);
                if (!matrices || index < 0)
                    return  glm::vec3();

                return get_transform_position1(matrices, index);
            }
            uint64_t getbone_matrix(uint64_t instance)
            {
                return mem->ReadChain<uint64_t>(instance, { 0xA8 , 0x28, 0x28, 0x10 });
            }
            glm::vec3 get_bone_position(uint64_t entity, uint32_t index) {
                auto bone_transform = mem->Read<uint64_t>(getbone_matrix(entity) + 0x20 + index * 8);
                if (!bone_transform)
                    return  glm::vec3();
                return get_transform_position(bone_transform);
            }
        }
        
        namespace Info{
           int GetSide(uint64_t entity) {

                uint64_t GetProfile = mem->Read<uint64_t>(entity + 0x4B8);
                if (!GetProfile)
                    return 0;
                uint64_t playerinfo = mem->Read<uint64_t>(GetProfile + 0x28);
                if (!playerinfo)
                    return 0;
                return mem->Read<int>(playerinfo + 0x58);
            }
            uint64_t GetRegistrationDate(uint64_t entity) {

                uint64_t GetProfile = mem->Read<uint64_t>(entity + 0x4B8);
                if (!GetProfile)
                    return 0;
                uint64_t playerinfo = mem->Read<uint64_t>(GetProfile + 0x28);
                if (!playerinfo)
                    return 0;

                return mem->Read<uint64_t>(playerinfo + 0x5C);
            }
            bool is_player(uint64_t entity) {
                return GetSide(entity) == SDK::Entity::Enums::EPlayerSide::Usec || SDK::Entity::Enums::EPlayerSide::Bear && GetRegistrationDate(entity) != 0;
            }
            bool is_scav(uint64_t entity) {
                return GetRegistrationDate(entity) == 0;
            }
            std::wstring GetName(std::uint64_t entity)
            {
                uint64_t GetProfile = mem->Read<uint64_t>(entity + 0x4B8);
                uint64_t playerinfo = mem->Read<uint64_t>(GetProfile + 0x28);
                const auto player_name_ptr = mem->Read<uintptr_t>(playerinfo + 0x18);

                if (is_player(entity)) {
                   // std::cout << GetWString(player_name_ptr) << std::endl;
                    return mem->GetWString(player_name_ptr);

                    //return L"Player";
                }
                else {
                    return std::wstring((L"Player Scav"));
                }
            }
        }
        float get_player_health(uint64_t entity)
        {
            uint64_t m_pHealthController = mem->Read<uint64_t>(entity + 0x498);
            uint64_t m_pHealthBody = mem->Read<uint64_t>(m_pHealthController + 0x50);
            uint64_t m_pBodyController = mem->Read<uint64_t>(m_pHealthBody + 0x18);

            for (int i = 0; i <= 7; i++) {

                auto body_part = mem->Read<uintptr_t>(m_pBodyController + 0x30 + (i * 0x18));
                auto health_container = mem->Read<uintptr_t>(body_part + 0x10);
                auto health = mem->Read<float>(health_container + 0x10);
                auto health_max = mem->Read<float>(health_container + 0x14);

                health = mem->Read<float>(health_container + 0x10);
                float hp = 0.f;
                hp += health;
                health = hp / health_max * 100;

                return health;
            }
        }


        namespace Local {
            inline glm::vec3 GetHeadPosition() {
                return Utils::Player::Bones::get_bone_position(SDK::Entity::g_localPlayer, 133);
            }
        }
    }

    namespace Camera {
        uint64_t get_camera_entity() {
            return mem->ReadChain<uint64_t>(SDK::Globals::g_fpsCamera, {0x30, 0x18});
        }

       glm::mat4x4 get_view_matrix() {

            //return mem->Read<glm::mat4x4>(get_optic_matrix() + 0xD8);
            return mem->Read<glm::mat4x4>(get_camera_entity() + 0xDC);
        }

       bool world_to_screen(glm::vec3 world, glm::vec2* screen)
       {
          // auto matrix = glm::transpose(get_view_matrix());

          

           //if (is_scoped())
           //{
           //	matrix = glm::transpose(get_optic_matrix());
           //}

           const auto pos_vec = glm::vec3{ SDK::Globals::g_viewMatrix[3][0], SDK::Globals::g_viewMatrix[3][1], SDK::Globals::g_viewMatrix[3][2] };

           const auto z = glm::dot(pos_vec, world) + SDK::Globals::g_viewMatrix[3][3];

           if (z < 0.098f)
               return false;

           const auto x = glm::dot(glm::vec3{ SDK::Globals::g_viewMatrix[0][0], SDK::Globals::g_viewMatrix[0][1], SDK::Globals::g_viewMatrix[0][2] }, world) + SDK::Globals::g_viewMatrix[0][3];
           const auto y = glm::dot(glm::vec3{ SDK::Globals::g_viewMatrix[1][0], SDK::Globals::g_viewMatrix[1][1], SDK::Globals::g_viewMatrix[1][2] }, world) + SDK::Globals::g_viewMatrix[1][3];

           static const auto screen_center_x = SDK::Globals::Width * 0.5f;
           static const auto screen_center_y = SDK::Globals::Height * 0.5f;

           if (screen)
           {
               *screen =
               {
                   screen_center_x * (1.f + x / z),
                   screen_center_y * (1.f - y / z)
               };
           }

           return true;
       }
    }

    namespace Text {
        std::string wstring_to_utf8(const std::wstring& str) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
            return myconv.to_bytes(str);
        }

        std::wstring utf8_to_wstring(const std::string& str) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
            return myconv.from_bytes(str);
        }
    }
}