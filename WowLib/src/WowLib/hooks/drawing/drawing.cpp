#include "../hooks.h"

namespace WowLib
{
	namespace Drawing
	{
		void CDrawing::Initialize(IDirect3DDevice9* pDevice, char* fontName)
		{
			if (initialized)
				return;

			if (!pLine)
				D3DXCreateLine(pDevice, &pLine);

			if (!pFont)
				D3DXCreateFont(pDevice, 15, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, fontName, &pFont);

			initialized = true;
		}

		bool CDrawing::Initialized()
		{
			return initialized;
		}

		void CDrawing::Reset(long value)
		{
			if (pFont)
				pFont->OnLostDevice();

			if (pLine)
				pLine->OnLostDevice();

			if (value == D3D_OK) {

				if (pFont)
					pFont->OnResetDevice();

				if (pLine)
					pLine->OnResetDevice();
			}
		}

		D3DXVECTOR2 CDrawing::GetTextSize(const char *szText, ID3DXFont* iFont)
		{
			RECT rcRect = { 0, 0, 0, 0 };
			if (iFont)
			{
				// calculate required rect
				iFont->DrawText(NULL, szText, strlen(szText), &rcRect, DT_CALCRECT,
					D3DCOLOR_XRGB(0, 0, 0));
			}

			// return width
			return D3DXVECTOR2(rcRect.right - rcRect.left, rcRect.bottom - rcRect.top);
		}
		void CDrawing::DrawString(bool center, int x, int y, D3DCOLOR color, char* String)
		{
			if (!initialized)
				return;

			RECT ShadowPos;
			ShadowPos.left = x + 1;
			ShadowPos.top = y + 1;
			RECT FontPos;
			FontPos.left = x;
			FontPos.top = y;

			if (center)
			{
				D3DXVECTOR2 size = GetTextSize(String, pFont);

				ShadowPos.left -= size.x / 2;
				ShadowPos.top -= size.y / 2;

				FontPos.left -= size.x / 2;
				FontPos.top -= size.y / 2;
			}

			pFont->DrawTextA(0, String, strlen(String), &ShadowPos, DT_NOCLIP, color / 3);
			pFont->DrawTextA(0, String, strlen(String), &FontPos, DT_NOCLIP, color);
			return;
		}
		void CDrawing::DrawShadowString(bool center, int x, int y, D3DCOLOR color, char* String)
		{
			if (!initialized)
				return;

			RECT Font;
			Font.left = x;
			Font.top = y;
			RECT Fonts;
			Fonts.left = x + 1;
			Fonts.top = y + 1;
			RECT Fonts1;
			Fonts1.left = x - 1;
			Fonts1.top = y - 1;

			if (center)
			{
				D3DXVECTOR2 size = GetTextSize(String, pFont);

				Font.left -= size.x / 2;
				Font.top -= size.y / 2;

				Fonts.left -= size.x / 2;
				Fonts.top -= size.y / 2;

				Fonts1.left -= size.x / 2;
				Fonts1.top -= size.y / 2;
			}

			pFont->DrawTextA(0, String, strlen(String), &Fonts1, DT_NOCLIP, D3DCOLOR_ARGB(255, 1, 1, 1));
			pFont->DrawTextA(0, String, strlen(String), &Fonts, DT_NOCLIP, D3DCOLOR_ARGB(255, 1, 1, 1));
			pFont->DrawTextA(0, String, strlen(String), &Font, DT_NOCLIP, color);
			return;
		}
		void CDrawing::DrawLine(float x, float y, float xx, float yy, D3DCOLOR color)
		{
			if (!initialized)
				return;

			D3DXVECTOR2 dLine[2];

			pLine->SetWidth(1);

			dLine[0].x = x;
			dLine[0].y = y;

			dLine[1].x = xx;
			dLine[1].y = yy;

			pLine->Draw(dLine, 2, color);

		}
		void CDrawing::DrawFilledRect(float x, float y, float w, float h, D3DCOLOR color)
		{
			if (!initialized)
				return;

			D3DXVECTOR2 vLine[2];

			w += 1;
			h += 1;

			pLine->SetWidth(w);

			vLine[0].x = x + w / 2;
			vLine[0].y = y;
			vLine[1].x = x + w / 2;
			vLine[1].y = y + h;

			pLine->Begin();
			pLine->Draw(vLine, 2, color);
			pLine->End();
		}
		void CDrawing::DrawBox(float x, float y, float width, float height, float px, D3DCOLOR color)
		{
			if (!initialized)
				return;

			D3DXVECTOR2 points[5];
			points[0] = D3DXVECTOR2(x, y);
			points[1] = D3DXVECTOR2(x + width, y);
			points[2] = D3DXVECTOR2(x + width, y + height);
			points[3] = D3DXVECTOR2(x, y + height);
			points[4] = D3DXVECTOR2(x, y);
			pLine->SetWidth(px);
			pLine->Draw(points, 5, color);
		}
		void CDrawing::DrawOutlinedRect(float x, float y, float width, float height, D3DCOLOR color)
		{
			if (!initialized)
				return;

			//DrawBox(x - 1, y - 1, width + 1, height + 1, 1, D3DCOLOR_RGBA(0, 0, 0, 255));
			DrawBox(x, y, width, height, 1, color);
			//DrawBox(x + 1, y + 1, width - 1, height - 1, 1, D3DCOLOR_RGBA(0, 0, 0, 255));
		}
	}
}