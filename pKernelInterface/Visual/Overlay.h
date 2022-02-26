#pragma once
#include <Windows.h>

/*void DrawString(int x, int y, const char* fmt)
{
	RECT window_metrics;

	if (!GetWindowRect(GameWnd, &window_metrics))
		return;
	RECT FontPos{ x, y, window_metrics.right - window_metrics.left, window_metrics.bottom - window_metrics.top };
	p_Font->DrawTextA(NULL, fmt, -1, &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));
}
void DrawString(int x, int y, const char* fmt, DWORD argb)
{
	RECT window_metrics;

	if (!GetWindowRect(GameWnd, &window_metrics))
		return;
	//RECT FontPos{ x, y, window_metrics.right - window_metrics.left, window_metrics.bottom - window_metrics.top };

	
	//RECT FontPos = { x, y - 1, window_metrics.right - window_metrics.left, window_metrics.bottom - window_metrics.top };
	//p_Font->DrawTextA(NULL, fmt, -1, &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
	//FontPos = { x, y + 1, window_metrics.right - window_metrics.left, window_metrics.bottom - window_metrics.top };
	//p_Font->DrawTextA(NULL, fmt, -1, &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
	//FontPos = { x - 1, y, window_metrics.right - window_metrics.left, window_metrics.bottom - window_metrics.top };
	//p_Font->DrawTextA(NULL, fmt, -1, &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
	///FontPos = { x + 1, y, window_metrics.right - window_metrics.left, window_metrics.bottom - window_metrics.top };
	//p_Font->DrawTextA(NULL, fmt, -1, &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
	RECT FontPos = { x, y, window_metrics.right - window_metrics.left, window_metrics.bottom - window_metrics.top };
	
	p_Font->DrawTextA(NULL, fmt, -1, &FontPos, DT_NOCLIP, argb);
	
}

void String(int x, int y, const char* Format, DWORD Color, ...)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	char Buffer[1024] = { '\0' };
	va_list va_alist;
	va_start(va_alist, Format);
	vsprintf_s(Buffer, Format, va_alist);
	va_end(va_alist);
	p_Font->DrawTextA(NULL, Buffer, -1, &rect, DT_CENTER | DT_NOCLIP, Color);
	return;
}

/*void String(int x, int y, const char* Format, DWORD Color, ...) {

	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT rect;
	SetRect(&rect, x, y, x, y);
	char Buffer[1024] = { '\0' };
	va_list va_alist;
	va_start(va_alist, Format);
	vsprintf_s(Buffer, Format, va_alist);
	va_end(va_alist);

	rect.left = x + 1;
	rect.top = y - 1;
	p_Font->DrawTextA(pSprite, Buffer, -1, &rect, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));

	rect.left = x + 1;
	rect.top = y + 1;
	p_Font->DrawTextA(pSprite, Buffer, -1, &rect, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));

	rect.left = x - 1;
	rect.top = y - 1;
	p_Font->DrawTextA(pSprite, Buffer, -1, &rect, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));

	rect.left = x - 1;
	rect.top = y + 1;
	p_Font->DrawTextA(pSprite, Buffer, -1, &rect, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));

	rect.left = x;
	rect.top = y;
	p_Font->DrawTextA(pSprite, Buffer, -1, &rect, DT_NOCLIP, Color);


	pSprite->End();

}

void DrawString2(int x, int y, const char* fmt, DWORD argb)
{
	RECT window_metrics;

	if (!GetWindowRect(GameWnd, &window_metrics))
		return;
	//RECT FontPos{ x, y, window_metrics.right - window_metrics.left, window_metrics.bottom - window_metrics.top };


	//RECT FontPos = { x, y - 1, window_metrics.right - window_metrics.left, window_metrics.bottom - window_metrics.top };
	//p_Font->DrawTextA(NULL, fmt, -1, &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
	//FontPos = { x, y + 1, window_metrics.right - window_metrics.left, window_metrics.bottom - window_metrics.top };
	//p_Font->DrawTextA(NULL, fmt, -1, &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
	//FontPos = { x - 1, y, window_metrics.right - window_metrics.left, window_metrics.bottom - window_metrics.top };
	//p_Font->DrawTextA(NULL, fmt, -1, &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
	//FontPos = { x + 1, y, window_metrics.right - window_metrics.left, window_metrics.bottom - window_metrics.top };
	//p_Font->DrawTextA(NULL, fmt, -1, &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
	RECT FontPos = { x, y, window_metrics.right - window_metrics.left, window_metrics.bottom - window_metrics.top };
	//p_Font2->DrawTextA(NULL, fmt, -1, &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
	p_Font->DrawTextA(NULL, fmt, -1, &FontPos, DT_NOCLIP, argb);

}
struct vertex
{
	FLOAT x, y, z, rhw;
	DWORD color;
};
void Line(float X, float Y, float X2, float Y2, int R, int G, int B, int A)
{
	if (!p_Line)
		D3DXCreateLine(p_Device, &p_Line);

	D3DXVECTOR2 Vertex[2];
	Vertex[0].x = X;
	Vertex[0].y = Y;
	Vertex[1].x = X2;
	Vertex[1].y = Y2;

	p_Line->Draw(Vertex, 2, D3DCOLOR_ARGB(A, R, G, B));
}
void BoxFilled(float x, float y, float w, float h, DWORD color)
{
	vertex V[4];

	V[0].color = V[1].color = V[2].color = V[3].color = color;

	V[0].z = V[1].z = V[2].z = V[3].z = 0;
	V[0].rhw = V[1].rhw = V[2].rhw = V[3].rhw = 0;

	V[0].x = x;
	V[0].y = y;
	V[1].x = x + w;
	V[1].y = y;
	V[2].x = x + w;
	V[2].y = y + h;
	V[3].x = x;
	V[3].y = y + h;

	unsigned short indexes[] = { 0, 1, 3, 1, 2, 3 };

	p_Device->CreateVertexBuffer(4 * sizeof(vertex), D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &g_pVB, NULL);
	p_Device->CreateIndexBuffer(2 * sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIB, NULL);

	VOID* pVertices;
	g_pVB->Lock(0, sizeof(V), (void**)&pVertices, 0);
	memcpy(pVertices, V, sizeof(V));
	g_pVB->Unlock();

	VOID* pIndex;
	g_pIB->Lock(0, sizeof(indexes), (void**)&pIndex, 0);
	memcpy(pIndex, indexes, sizeof(indexes));
	g_pIB->Unlock();

	p_Device->SetTexture(0, NULL);
	p_Device->SetPixelShader(NULL);
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	p_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	p_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	p_Device->SetStreamSource(0, g_pVB, 0, sizeof(vertex));
	p_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	p_Device->SetIndices(g_pIB);

	p_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	g_pVB->Release();
	g_pIB->Release();
}
void Box(float x, float y, float w, float h, float linewidth, DWORD color)
{
	if (linewidth == 0 || linewidth == 1)
	{
		BoxFilled(x, y, w, 1, color);             // Top
		BoxFilled(x, y + h - 1, w, 1, color);         // Bottom
		BoxFilled(x, y + 1, 1, h - 2 * 1, color);       // Left
		BoxFilled(x + w - 1, y + 1, 1, h - 2 * 1, color);   // Right
	}
	else
	{
		BoxFilled(x, y, w, linewidth, color);                                     // Top
		BoxFilled(x, y + h - linewidth, w, linewidth, color);                         // Bottom
		BoxFilled(x, y + linewidth, linewidth, h - 2 * linewidth, color);               // Left
		BoxFilled(x + w - linewidth, y + linewidth, linewidth, h - 2 * linewidth, color);   // Right
	}
}

void BoxBordered(float x, float y, float w, float h, float border_width, DWORD color, DWORD color_border)
{
	BoxFilled(x, y, w, h, color);
	Box(x - border_width, y - border_width, w + 2 * border_width, h + border_width, border_width, color_border);
}

void Circle(float x, float y, float radius, int rotate, int type, bool smoothing, int resolution, DWORD color)
{
	std::vector<vertex> circle(resolution + 2);
	float angle = rotate * D3DX_PI / 180;
	float pi;

	if (type == 1) pi = D3DX_PI;        // Full circle
	if (type == 2) pi = D3DX_PI / 2;      // 1/2 circle
	if (type == 3) pi = D3DX_PI / 4;   // 1/4 circle

	for (int i = 0; i < resolution + 2; i++)
	{
		circle[i].x = (float)(x - radius * cos(i * (2 * pi / resolution)));
		circle[i].y = (float)(y - radius * sin(i * (2 * pi / resolution)));
		circle[i].z = 0;
		circle[i].rhw = 1;
		circle[i].color = color;
	}

	// Rotate matrix
	int _res = resolution + 2;
	for (int i = 0; i < _res; i++)
	{
		circle[i].x = x + cos(angle) * (circle[i].x - x) - sin(angle) * (circle[i].y - y);
		circle[i].y = y + sin(angle) * (circle[i].x - x) + cos(angle) * (circle[i].y - y);
	}

	p_Device->CreateVertexBuffer((resolution + 2) * sizeof(vertex), D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &g_pVB, NULL);

	VOID* pVertices;
	g_pVB->Lock(0, (resolution + 2) * sizeof(vertex), (void**)&pVertices, 0);
	memcpy(pVertices, &circle[0], (resolution + 2) * sizeof(vertex));
	g_pVB->Unlock();


	p_Device->SetTexture(0, NULL);
	p_Device->SetPixelShader(NULL);
	if (smoothing)
	{
		p_Device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
		p_Device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);
	}
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	p_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	p_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	p_Device->SetStreamSource(0, g_pVB, 0, sizeof(vertex));
	p_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	p_Device->DrawPrimitive(D3DPT_LINESTRIP, 0, resolution);
	if (g_pVB != NULL) g_pVB->Release();
}*/