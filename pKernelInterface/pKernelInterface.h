#pragma once

#include <windows.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <memory>
#include <array>
#include <dwmapi.h>
#include <comdef.h> 
#include <TlHelp32.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <Wininet.h>
#include <sstream>
#include <random>
#include <iostream>
#include <string_view>
#include <array>
#include <string>
#include <cstring>
#include <algorithm>
#include <random>
#include <chrono>
#include <d3dx9math.h>
#include <math.h>


#pragma comment(lib, "wininet.lib")

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_dx9.h"
#include "Imgui/imgui_impl_win32.h"
#include "Visual/Text.h"
IDirect3D9Ex* p_Object = NULL;
IDirect3DDevice9Ex* p_Device = NULL;
ID3DXLine* p_Line = NULL;
ID3DXFont* p_Font = NULL;
ID3DXSprite* pSprite = NULL;
ImFont* ButtonFont;
LPDIRECT3DVERTEXBUFFER9 g_pVB;    // Buffer to hold vertices
LPDIRECT3DINDEXBUFFER9  g_pIB;    // Buffer to hold indices
D3DPRESENT_PARAMETERS p_Params = { NULL };


int my_image_width = 0;
int my_image_height = 0;
PDIRECT3DTEXTURE9 my_texture = NULL;
bool ret;


const MARGINS Margin = { -1 };
HWND MyWnd = NULL;
HWND GameWnd = NULL;
RECT GameRect = { NULL };
MSG Message = { NULL };

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT DirectXInit(HWND hWnd);
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
void SetupWindow();
WPARAM MainLoop();
void CleanuoD3D();
