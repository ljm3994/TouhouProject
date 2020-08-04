#include "stdafx.h"
#include "MainGame.h"


MainGame::MainGame()
{
}


MainGame::~MainGame()
{
	//�̱��� ����
	KEYMANAGER->ReleaseSingleton();
	TIMEMANAGER->ReleaseSingleton();
	//�̹��� �Ŵ��� ���� �����ǿ� ��� �̹��� ��ü ����
	IMGMANAGER->deleteAll();
	IMGMANAGER->ReleaseSingleton();
}

HRESULT MainGame::init()
{	
	//������(�ü��)�� ���۵Ǿ �帥 �ð��� 1/1000�� ������
	//DWORD���� �����ϴ� �Լ��� dword->unsigned long
	srand(GetTickCount());
	//////////////////////////////////////////

	IMGMANAGER->addImage("Background", _T("images/Sunset.bmp"), WINSIZEX - ((WINSIZEX / 2) - 130), WINSIZEY - 40);
	IMGMANAGER->addImage("Enemy", _T("images/Enemy.bmp"), 143, 36, 3, 1,  true, RGB(255, 255, 255));
	IMGMANAGER->addImage("Bullet", _T("images/źȯ.bmp"), 159, 22, 10, 1, true, RGB(255, 255, 255));
	IMGMANAGER->addImage("Charter", _T("images/���̹�.bmp"), 37, 54, true, RGB(255, 0, 255));
	IMGMANAGER->addImage("UI", _T("images/UI.bmp"), 639, 480);
	IMGMANAGER->addImage("Font", _T("images/FontNumber.bmp"), 160, 22, 10, 1, true, RGB(255, 255, 255));
	IMGMANAGER->addImage("Item", _T("images/Item.bmp"), 111, 18, 7, 1, true, RGB(255, 255, 255));
	IMGMANAGER->addImage("Boss", _T("images/boss.bmp"), 400, 522, 4, 4, true, RGB(255, 255, 255));
	IMGMANAGER->addImage("Main", _T("images/Main.bmp"), 639, 479, false);
	IMGMANAGER->addImage("Loading", _T("images/Loading.bmp"), 638, 477, false);
	IMGMANAGER->addImage("Start", _T("images/Start.bmp"), 223, 64, 3, 2 ,true, RGB(0, 0, 0));
	IMGMANAGER->addImage("Effect", _T("images/Effect.bmp"), 100, 33, 3, 1, true, RGB(255, 255, 255));
	IMGMANAGER->addImage("Ending", _T("images/Ending.bmp"), 3229, 1465, 5, 3, true, RGB(197, 0, 255));
	IMGMANAGER->addImage("Logo1", _T("images/Logo1.bmp"), 187, 185, 2, 2, true, RGB(0, 0, 0));
	IMGMANAGER->addImage("Logo2", _T("images/Logo2.bmp"), 87, 84, true, RGB(0, 0, 0));
	IMGMANAGER->addImage("Logo3", _T("images/Logo3.bmp"), 404, 27, true, RGB(0, 0, 0));
	//IMGMANAGER->addImage("Logo2", _T("images/Logo2.bmp"), 187, 185, 2, 2, true, RGB(0, 0, 0));
	SOUNDMANAGER->addSound("PDead", "sound/pldead00.wav", false);
	SOUNDMANAGER->addSound("BGM", "sound/BGM.wav", true);
	SOUNDMANAGER->addSound("GUN", "sound/gun00.wav", false);
	SOUNDMANAGER->addSound("ITEM", "sound/item00.wav", false);
	SOUNDMANAGER->addSound("DAMAGE", "sound/damage00.wav", false);
	SOUNDMANAGER->addSound("BossTan", "sound/tan01.wav", false);
	SOUNDMANAGER->addSound("Ending", "sound/EndingBGM.wav", true);
	temp.init();
	//////////////////////////////////////////
	return S_OK;
}

void MainGame::release()
{
	//////////////////////////////////////////

	//////////////////////////////////////////
}

void MainGame::update()
{
	//////////////////////////////////////////
	temp.update();

	//////////////////////////////////////////
}

void MainGame::render()
{
	//������ ����ϴ� �Լ�(dc�� ���õǾ��ִ� �귯�ø� �������� ��� WHITENESS �� ���� �׳� �Ͼ�� ���)
	PatBlt(g_MemDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//////////////////////////////////////////

	temp.render();

	//////////////////////////////////////////
	TIMEMANAGER->render();
	//������۸�
	BitBlt(IMGMANAGER->getHDC(), 0, 0, WINSIZEX, WINSIZEY,
		g_MemDC, 0, 0, SRCCOPY);

}
