#include "stdafx.h"
#include "MainScreen.h"


MainScreen::MainScreen()
{
	ZeroMemory(&Game, sizeof(Game));
}


MainScreen::~MainScreen()
{
}

HRESULT MainScreen::init()
{
	m_FrameX = 1;
	m_FrameY = 0;
	m_DelayTime = 0.0f;
	Game = new TanMakGame();
	Game->init();
	m_Alpha = 255;
	m_bStart = false;
	m_isEnter = false;
	m_Loading = false;
	Xpos = 0;
	return S_OK;
}

void MainScreen::release()
{
}

void MainScreen::update()
{
	if (!m_Loading && !m_bStart)
	{
		if (KEYMANAGER->isKeyDown(VK_RETURN))
		{
			m_isEnter = true;
		}
		if (Xpos < (WINSIZEX / 2))
		{
			Xpos+= 500 * g_ETime;
		}
		if (m_isEnter)
		{
			m_DelayTime += g_ETime;
			if (m_DelayTime >= 0.2f)
			{
				m_DelayTime = 0.0f;
				m_Alpha -= 50;
				switch (m_FrameX)
				{
				case 0:
					m_FrameX = 2;
					break;
				case 1:
					m_FrameX = 0;
					break;
				case 2:
					m_Alpha = 255;
					m_DelayTime = 0.0f;
					m_Loading = true;
					break;
				}
			}
		}
	}
	else
	{
		if (m_Loading && !m_bStart)
		{
			m_DelayTime += g_ETime;
			m_Alpha--;
			if (m_DelayTime >= 4.0f)
			{
				m_DelayTime = 0.0f;
				m_Loading = false;
				m_bStart = true;
			}
		}
		else if (!m_Loading && m_bStart)
		{
			Game->update();
		}
	}
}

void MainScreen::render()
{
	if (!m_Loading && !m_bStart)
	{
		IMGMANAGER->alphaRender("Main", g_MemDC, m_Alpha, 0, 0, WINSIZEX, WINSIZEY);
		IMGMANAGER->frameAlphaRender("Logo1", g_MemDC, m_Alpha, 0, 0, WINSIZEX - Xpos, 100, 100, 100);
		IMGMANAGER->frameAlphaRender("Logo1", g_MemDC, m_Alpha, 0, 1, Xpos, 170, 100, 100);
		IMGMANAGER->rotateRender("Logo2", g_MemDC, 6, false, 1.0f, WINSIZEX - Xpos, 270);
		IMGMANAGER->frameAlphaRender("Logo1", g_MemDC, m_Alpha, 1, 0, Xpos, 350, 100, 100);
		IMGMANAGER->frameAlphaRender("Logo1", g_MemDC, m_Alpha, 1, 1, WINSIZEX - Xpos, 450, 100, 100);
		if (Xpos >= WINSIZEX / 2)
		{
			IMGMANAGER->rotateRender("Logo3", g_MemDC, 100, false, 1.0f, (WINSIZEX - Xpos) - 100, 300);
		}
		switch (m_FrameY)
		{
		case 0:
			IMGMANAGER->frameAlphaRender("Start", g_MemDC, m_Alpha, m_FrameX, 0, WINSIZEX - 300, (WINSIZEY / 2) - 70, 100, 32);
			IMGMANAGER->frameAlphaRender("Start", g_MemDC, m_Alpha, 0, 1, WINSIZEX - 300, (WINSIZEY / 2) - 50, 100, 32);
			break;
		case 1:
			IMGMANAGER->frameAlphaRender("Start", g_MemDC, m_Alpha, 0, 0, WINSIZEX - 300, (WINSIZEY / 2) - 70, 100, 32);
			IMGMANAGER->frameAlphaRender("Start", g_MemDC, m_Alpha, m_FrameX, 1, WINSIZEX - 300, (WINSIZEY / 2) - 50, 100, 32);
			break;
		default:
			break;
		}
	}
	else
	{
		if (m_Loading && !m_bStart)
		{
			IMGMANAGER->alphaRender("Loading", g_MemDC, m_Alpha, 0, 0, WINSIZEX, WINSIZEY);
		}
		else if (!m_Loading && m_bStart)
		{
			Game->render();
		}
	}
}
