#include "stdafx.h"
#include "SideScreen.h"


SideScreen::SideScreen(UINT * Score)
{
	m_Score = Score;
}

SideScreen::SideScreen()
{
}


SideScreen::~SideScreen()
{
}

HRESULT SideScreen::init()
{
	m_rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	return S_OK;
}

void SideScreen::release()
{
}

void SideScreen::update()
{
}

void SideScreen::render()
{
	IMGMANAGER->render("UI", g_MemDC, 0, 0, WINSIZEX, WINSIZEY);
	for (int i = 0; i < 10; i++)
	{
		int num = pow(10, i);
		int Fram = *m_Score / num;
		Fram = Fram % 10;
		IMGMANAGER->frameRender("Font", g_MemDC, Fram, 0,(WINSIZEX - 260) + (20 * (10 - i)), WINSIZEY - 620, 20, 20);
	}
	for (int i = 0; i < 10; i++)
	{
		int num = pow(10, i);
		int Fram = *m_Score / num;
		Fram = Fram % 10;
		IMGMANAGER->frameRender("Font", g_MemDC, Fram, 0, (WINSIZEX - 260) + (20 * (10 - i)), WINSIZEY - 580, 20, 20);
	}
	//DrawfRect(g_MemDC, m_rc);
}
