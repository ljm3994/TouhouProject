#include "stdafx.h"
#include "EnemyGroup.h"


EnemyGroup::EnemyGroup(FRECT Stage)
{
	EnemyCount = 0;
	m_Stage = Stage;
}

EnemyGroup::EnemyGroup()
{
}


EnemyGroup::~EnemyGroup()
{
}

HRESULT EnemyGroup::init()
{
	BossDelay = 0.0f;
	EnemyCount = 0;
	m_BossCreate = false;
	return S_OK;
}

void EnemyGroup::release()
{
}

void EnemyGroup::update()
{
	BossDelay += g_ETime;

	if (!m_BossCreate && BossDelay >= 60.0f && EnemyCount == 0)
	{
		m_BossCreate = true;
		BossDelay = 0.0f;
	}
	CreateEnemy();
	if (!m_BossCreate)
	{
		m_EnemyGroupit = m_EnemyGroup.begin();
		while (m_EnemyGroupit != m_EnemyGroup.end())
		{
			(*m_EnemyGroupit)->update();
			if ((*m_EnemyGroupit)->GetFire())
			{
				if ((*m_EnemyGroupit)->OnDisplay() && (*m_EnemyGroupit)->GetProperty().GetEnemyType() == ZACO_TYPE)
				{
					(*m_EnemyGroupit)->SetDie(true);
					if ((*m_EnemyGroupit)->isBulletAllRemove())
					{
						ObjectPool<Enemy>::GetInstance()->PushObject((*m_EnemyGroupit));
						m_EnemyGroup.erase(m_EnemyGroupit++);
						EnemyCount--;
					}
					else
					{
						m_EnemyGroupit++;
					}
				}
				else
				{
					if ((*m_EnemyGroupit)->GetDie())
					{
						if ((*m_EnemyGroupit)->isBulletAllRemove())
						{
							ObjectPool<Enemy>::GetInstance()->PushObject((*m_EnemyGroupit));
							m_EnemyGroup.erase(m_EnemyGroupit++);
							EnemyCount--;
						}
						else
						{
							m_EnemyGroupit++;
						}
					}
					else
					{
						m_EnemyGroupit++;
					}
				}
			}
			else
			{
				m_EnemyGroupit++;
			}
		}
	}
	else
	{
		m_boss->update();
		if (m_boss->GetFire() && !m_boss->GetDie())
		{
			m_boss->OnDisplay();
		}
		else if (m_boss->GetDie())
		{
			ObjectPool<BossEnemy>::GetInstance()->PushObject(m_boss);
			EnemyCount--;
		}
	}
}

void EnemyGroup::render()
{
	if (!m_BossCreate)
	{
		for (m_EnemyGroupit = m_EnemyGroup.begin(); m_EnemyGroupit != m_EnemyGroup.end(); m_EnemyGroupit++)
		{
			(*m_EnemyGroupit)->render();
		}
	}
	else
	{
		m_boss->render();
	}
}

bool EnemyGroup::BossCreateis()
{
	return m_BossCreate;
}

void EnemyGroup::SetPlayerPos(Vecter *pos)
{
	m_playerpos = pos;
}

void EnemyGroup::CreateEnemy()
{
	if (EnemyCount == 0)
	{
		if (!m_BossCreate)
		{
			EnemyCount = GetFromIntTo(2, 4);

			for (int i = 0; i < EnemyCount; i++)
			{
				Enemy * Temp = ObjectPool<Enemy>::GetInstance()->GetObObject();
				Temp->init();
				Temp->SetStage(m_Stage);
				ProduceOption ProOption = { 100, 100, true, ENEMY_TYPE::ZACO_TYPE, FIRE_TYPE::FIRE_TYPE_NUM, {0, 0} };
				Temp->SetProperty(ProOption);
				Temp->SetInit(GetFromIntTo(m_Stage.left + 70, m_Stage.right - 70), -100 - (i * 5), 40, 40, 0);
				m_EnemyGroup.emplace_back(Temp);
			}
		}
		else
		{
			m_boss = ObjectPool<BossEnemy>::GetInstance()->GetObObject();
			m_boss->init();
			ProduceOption ProOption = { 1000, 100, true, ENEMY_TYPE::ZACO_TYPE, FIRE_TYPE::CIRCLE_FIRE, {0, 0} };
			m_boss->SetProperty(ProOption);
			m_boss->SetPlayerPos(m_playerpos);
			m_boss->SetStage(m_Stage);
			m_boss->SetInit(GetFromIntTo(m_Stage.left + 70, m_Stage.right - 70), -100, 70, 70, 0);
			EnemyCount = 1;
		}
	}
}

bool EnemyGroup::PlayerEnemyBulletColid(FRECT rc)
{
	for (m_EnemyGroupit = m_EnemyGroup.begin(); m_EnemyGroupit != m_EnemyGroup.end(); m_EnemyGroupit++)
	{
		if ((*m_EnemyGroupit)->isPlayerKill(rc))
		{
			SOUNDMANAGER->play("PDead");
			return true;
		}
	}
	return false;
}

bool EnemyGroup::PlayerBossEnemyBulletColid(FRECT rc)
{
	if (m_boss->isPlayerKill(rc))
	{
		SOUNDMANAGER->play("PDead");
		return true;
	}
	return false;
}

list<Enemy * > EnemyGroup::GetEnemy()
{
	return m_EnemyGroup;
}

BossEnemy * EnemyGroup::GetBoss()
{
	return m_boss;
}
