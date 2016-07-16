#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace WowLib
{
	namespace Drawing
	{
		class CDrawing
		{
		private:
			ID3DXLine* pLine;
			ID3DXFont* pFont;
			ID3DXFont* pActiveFont;
			bool initialized = false;
			D3DXVECTOR2 GetTextSize(const char *szText, ID3DXFont* iFont);
		public:
			void Initialize(IDirect3DDevice9* pDevice, char* fontName);
			bool Initialized();
			void Reset(long value);
			void DrawString(bool center, int x, int y, D3DCOLOR color, char* String);
			void DrawShadowString(bool center, int x, int y, D3DCOLOR color, char* String);
			void DrawLine(float x, float y, float xx, float yy, D3DCOLOR color);
			void DrawFilledRect(float x, float y, float w, float h, D3DCOLOR color);
			void DrawBox(float x, float y, float width, float height, float px, D3DCOLOR color);
			void DrawOutlinedRect(float x, float y, float width, float height, D3DCOLOR color);
		};
	}
}