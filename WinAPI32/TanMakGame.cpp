#include "stdafx.h"
#include "TanMakGame.h"


TanMakGame::TanMakGame()
{
}


TanMakGame::~TanMakGame()
{
}

HRESULT TanMakGame::init()
{
	m_Score = 0;
	m_side = { &m_Score };
	m_side.init();
	m_Stage = RectMake(50, 20, WINSIZEX - ((WINSIZEX / 2) - 130), WINSIZEY - 40);
	m_EnemyGroup = { m_Stage };
	m_EnemyGroup.init();
	m_GameClear = false;
	m_Player.init();
	m_Player.SetStage(m_Stage);
	m_bFirst = true;
	m_Player.SetPlayer(100, WINSIZEY - 100, 30, 40);
	Frame = { 0, 0 };
	m_DelayTime = 0.0f;
	m_Alpha = 0;
	m_EndingFirst = false;
	m_EnemyGroup.SetPlayerPos(m_Player.GetPlayerpos());
	return S_OK;
}

void TanMakGame::release()
{
}

void TanMakGame::update()
{
	if (!m_GameClear)
	{
		if (m_bFirst)
		{
			m_bFirst = false;
			SOUNDMANAGER->play("BGM");
		}
		m_EnemyGroup.update();
		m_Player.update();
		EnemyKill();
		if (!m_Player.GetPlayerDie())
		{
			if (!m_EnemyGroup.BossCreateis())
			{
				m_Player.SetPlayerDie(m_EnemyGroup.PlayerEnemyBulletColid(m_Player.GetPlayer()));
			}
			else
			{
				m_Player.SetPlayerDie(m_EnemyGroup.PlayerBossEnemyBulletColid(m_Player.GetPlayer()));
			}
		}

		m_Itemit = m_Item.begin();
		while (m_Itemit != m_Item.end())
		{
			(*m_Itemit)->update();
			if ((*m_Itemit)->PlayerItemEat(m_Player.GetPlayer()))
			{
				ItemEat(*(*m_Itemit));
				SOUNDMANAGER->play("ITEM");
				ObjectPool<ItemManager>::GetInstance()->PushObject((*m_Itemit));
				m_Itemit = m_Item.erase(m_Itemit++);
			}
			else if ((*m_Itemit)->OnDisplay())
			{
				ObjectPool<ItemManager>::GetInstance()->PushObject((*m_Itemit));
				m_Itemit = m_Item.erase(m_Itemit++);
			}
			else
			{
				m_Itemit++;
			}
		}
		a -= 2;
	}
	else
	{
		if (!m_EndingFirst)
		{
			m_EndingFirst = true;
			SOUNDMANAGER->stop("BGM");
			SOUNDMANAGER->play("Ending");
		}
		m_DelayTime += g_ETime;
		if (m_DelayTime >= 10.0f)
		{
			m_DelayTime = 0.0f;
			m_Alpha = 0;
			Frame.x++;
			if (Frame.x == 4)
			{
				Frame.x = 0;
				Frame.y++;
			}
			if (Frame.x == 4 && Frame.y == 2)
			{
				Frame.x = 0;
				Frame.y = 0;
			}
		}
	}
}

void TanMakGame::render()
{
	if (!m_GameClear)
	{
		int x = static_cast<int>(round(WINSIZEX / 257));
		int y = static_cast<int>(round(WINSIZEY / 255));

		//IMGMANAGER->render("Background1", g_MemDC, 0, 0, WINSIZEX, WINSIZEY);

		//DrawfRect(g_MemDC, m_Stage);
		m_side.render();
		IMGMANAGER->loopRender("Background", g_MemDC, m_Stage.left, m_Stage.top, 0, a);
		m_EnemyGroup.render();
		for (m_Itemit = m_Item.begin(); m_Itemit != m_Item.end(); m_Itemit++)
		{
			(*m_Itemit)->render();
		}
		m_Player.render();
	}
	else
	{
		IMGMANAGER->frameAlphaRender("Ending", g_MemDC, 255, Frame.x, Frame.y, 0, 0, WINSIZEX, WINSIZEY);
	}
	//DrawfRect(g_MemDC, m_Stage);
}

void TanMakGame::EnemyKill()
{
	if (!m_EnemyGroup.BossCreateis())
	{
		list<Enemy *> Temp = m_EnemyGroup.GetEnemy();
		list<Enemy *>::iterator Tempit;
		for (Tempit = Temp.begin(); Tempit != Temp.end(); Tempit++)
		{
			if (!(*Tempit)->GetDie())
			{
				if (m_Player.EnemyColidBullet((*Tempit)->GetEnemy()))
				{
					(*Tempit)->SetDie(true);
					SOUNDMANAGER->play("DAMAGE");
					ItemManager * Temp = ObjectPool<ItemManager>::GetInstance()->GetObObject();
					Temp->SetStage(m_Stage);
					Temp->init();
					Temp->SettingItem((*Tempit)->GetPos(), ItemType::ScoreItem);
					m_Item.emplace_back(Temp);
				}
			}
		}
		Temp.clear();
	}
	else
	{
		BossEnemy * boss = m_EnemyGroup.GetBoss();
		if (!boss->GetDie())
		{
			if (m_Player.EnemyColidBullet(boss->GetEnemy()))
			{
				SOUNDMANAGER->play("BossTan");
				boss->SetHPPercent(10.0f);
				if (boss->BossDie())
				{
					boss->SetDie(true);
					m_GameClear = true;
				}
			}
		}
	}
}

void TanMakGame::ItemEat(ItemManager Item)
{
	switch (Item.GetType())
	{
	case PowerItem:
		break;
	case ScoreItem:
		m_Score += GetFromIntTo(40, 60);
		break;
	}
}
