#include "stdafx.h"
#include "Manager.h"


EnemyManager::EnemyManager(float Xpos, float Ypos, float Width, float Height, int MaxBulletCount)
	:m_MaxBulletCount(MaxBulletCount)
{
	m_pos = { Xpos, Ypos };
	m_rc = RectMakeCenter(Xpos, Ypos, Width, Height);
	m_IsFire = false;
	m_MoveEsc = false;
	m_MaxBulletCount = 0;
	m_DelayReload = 0.0f;
	m_UpdateDelayTime = 0.0f;
}

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::SetProperty(ProduceOption Option)
{
	m_Option = Option;
}

ProduceOption EnemyManager::GetProperty()
{
	return m_Option;
}

void EnemyManager::LoadBullet(FIRE_TYPE type)
{
	if (m_IsFire)
	{
		switch (type)
		{
			// 탄막 종류 없음
		case NORMAL_FIRE:
			break;
			// 지향성 탄막
		case AIMED_FIRE:
			for (int i = 0; i < 20; i++)
			{
				EnemyBullet * TempBullet = ObjectPool<EnemyBullet>::GetInstance()->GetObObject();
				TempBullet->init();
				TempBullet->SetStage(m_Stage);
				TempBullet->SetPlayerPos(m_PlayerPos);
				TempBullet->BulletSetting(m_pos, 12, 120.0f, 0.5f, ((360.0f / 30) * i), 90.0f, type);
				m_MaxBulletCount = 3;
				if (m_CurrentBulletCount == 0)
				{
					m_CurrentBulletCount = 3;
				}
				m_DelayReload = 3.0f;
				m_Bullet.emplace_back(TempBullet);
			}
			break;
			// 골뱅이형 탄막
		case N_WAY_FIRE:
			for (int i = 0; i < 5; i++)
			{
				EnemyBullet * TempBullet = ObjectPool<EnemyBullet>::GetInstance()->GetObObject();
				TempBullet->init();
				TempBullet->SetStage(m_Stage);
				TempBullet->BulletSetting(m_pos, 10, 120.0f, 0.05f, ((360.0f / 5) * i), 0.0f, type);
				m_MaxBulletCount = 5;
				if (m_CurrentBulletCount == 0)
				{
					m_CurrentBulletCount = 5;
				}
				m_DelayReload = 3.0f;
				m_Bullet.emplace_back(TempBullet);
			}
			break;
			// 회전없이 원형으로 퍼지는 탄막
		case MULTI_FIRE:
			for (int i = 0; i < 20; i++)
			{
				EnemyBullet * TempBullet = ObjectPool<EnemyBullet>::GetInstance()->GetObObject();
				TempBullet->init();
				TempBullet->SetStage(m_Stage);
				TempBullet->BulletSetting(m_pos, 12, 120.0f, 0.5f, ((180.0f / 20)* i), 4.0f, type);
				m_MaxBulletCount = 3;
				if (m_CurrentBulletCount == 0)
				{
					m_CurrentBulletCount = 3;
				}
				m_DelayReload = 3.0f;
				m_Bullet.emplace_back(TempBullet);
			}
			break;
			// 원형으로 회전하며 퍼져가는 탄막
		case CIRCLE_FIRE:
			for (int i = 0; i < 20; i++)
			{
				EnemyBullet * TempBullet = ObjectPool<EnemyBullet>::GetInstance()->GetObObject();
				TempBullet->init();
				TempBullet->SetStage(m_Stage);
				TempBullet->BulletSetting(m_pos, 10, 100.0f, 0.23f, ((360.0f / 20) * i), 15.0f, type);
				m_MaxBulletCount = 4;
				if (m_CurrentBulletCount == 0)
				{
					m_CurrentBulletCount = 4;
				}
				m_DelayReload = 3.0f;
				m_Bullet.emplace_back(TempBullet);
			}
			break;
		case FIRE_TYPE_NUM:
			for (int i = 0; i < 10; i++)
			{
				EnemyBullet * TempBullet = ObjectPool<EnemyBullet>::GetInstance()->GetObObject();
				TempBullet->init();
				TempBullet->SetStage(m_Stage);
				TempBullet->BulletSetting(m_pos, 10, 100.0f, 0.23f, ((180.0f / 10) * i), 4.0f, type);
				m_MaxBulletCount = 3;
				if (m_CurrentBulletCount == 0)
				{
					m_CurrentBulletCount = 3;
				}
				m_DelayReload = 3.0f;
				m_Bullet.emplace_back(TempBullet);
			}
			break;
		}
	}
}

void EnemyManager::SetMoveEsc(bool Move)
{
	m_MoveEsc = Move;
}

void EnemyManager::EnemyMove(float Time)
{
	if (m_FData.GetInitPos() == Vecter{ 0, 0 })
	{
		m_FData.SetInitPos(m_pos);
	}
	if (!m_FData.isMaxDistance(m_pos))
	{
		float Angle = m_FData.GetAngle();
		float Speed = m_FData.GetSpeed();
		m_pos.x += sinf(Angle * TORADIAN) * Speed * Time;
		m_pos.y -= cosf(Angle * TORADIAN) * Speed * Time;

		m_FData.SetAngle(Angle);
	}
	else
	{
		m_FData.SetInitPos(Vecter{ 0, 0 });
		m_MoveEsc = true;
	}

	m_rc = RectMakeCenter(m_pos.x, m_pos.y, m_rc.right - m_rc.left, m_rc.bottom - m_rc.top);
}

bool EnemyManager::GetFire()
{
	return m_IsFire;
}

void EnemyManager::SetFire(bool Fire)
{
	m_IsFire = Fire;
}

void EnemyManager::SetFlightData(Flight_Data data)
{
	m_FData = data;
}

Vecter EnemyManager::GetPos()
{
	return m_pos;
}

Flight_Data EnemyManager::GetFlightData()
{
	return m_FData;
}

int EnemyManager::GetCurrentBullet()
{
	return m_CurrentBulletCount;
}

void EnemyManager::SetCurrentBullet(int Count)
{
	m_CurrentBulletCount = Count;
}

void EnemyManager::ShootUpdate(float Time)
{
	if (!GetDie() && GetFire())
	{
		if (m_MaxBulletCount == 0)
		{
			LoadBullet(m_Option.GetFireType());
		}
		if (m_MaxBulletCount > 0)
		{
			m_DelayReload += g_ETime;
			if (m_DelayReload > 0.5f && m_CurrentBulletCount > 0)
			{
				LoadBullet(m_Option.GetFireType());
				m_DelayReload = 0.0f;
				m_CurrentBulletCount--;
			}
		}
	}
	BulletUpdate();
}

bool EnemyManager::GetMoveEsc()
{
	return m_MoveEsc;
}

void EnemyManager::SetDie(bool Die)
{
	m_Option.SetAlive(Die);
}

bool EnemyManager::GetDie()
{
	return m_Option.GetLive();
}

void EnemyManager::BulletUpdate()
{
	m_BulletIt = m_Bullet.begin();

	while (m_BulletIt != m_Bullet.end())
	{
		(*m_BulletIt)->update();
		if ((*m_BulletIt)->OnDisplay())
		{
			ObjectPool<EnemyBullet>::GetInstance()->PushObject((*m_BulletIt));
			m_BulletIt = m_Bullet.erase(m_BulletIt++);
		}
		else
		{
			m_BulletIt++;
		}
	}
}

FRECT EnemyManager::GetEnemy()
{
	return m_rc;
}

void EnemyManager::SetDirect()
{
	int Direct = GetFromIntTo(0, 4);
	m_FData.SetMaxDistance(700);
	switch (Direct)
	{
	case 0:
		m_FData.SetDirect(ENEMY_DIRECT::RIGHT_WAY);
		break;
	case 1:
		m_FData.SetDirect(ENEMY_DIRECT::LEFT_WAY);
		break;
	case 2:
		m_FData.SetDirect(ENEMY_DIRECT::RIGHT_CONNER_WAY);
		m_FData.SetMaxAngle(m_FData.GetAngle() - 120.0f);
		break;
	case 3:
		m_FData.SetDirect(ENEMY_DIRECT::LEFT_CONNER_WAY);
		m_FData.SetMaxAngle(m_FData.GetAngle() + 120.0f);
		break;
	case 4:
		m_FData.SetDirect(ENEMY_DIRECT::BACK_WAY);
		break;
	}
}

bool EnemyManager::isBulletAllRemove()
{
	return m_Bullet.empty();
}

bool EnemyManager::isPlayerKill(FRECT m_Player)
{
	for (m_BulletIt = m_Bullet.begin(); m_BulletIt != m_Bullet.end(); m_BulletIt++)
	{
		if ((*m_BulletIt)->CharColide(m_Player))
		{
			return true;
		}
	}
	return false;
}

void EnemyManager::SetPlayerPos(Vecter * pos)
{
	m_PlayerPos = pos;
}

void EnemyManager::DirectMove(ENEMY_DIRECT direct, float Time)
{
	float Angle = 0.0f;
	switch (direct)
	{
		// 일직선으로 아래로 내려간다.
	case GO_AWAY:
		m_FData.SetAngle(180.0f);
		m_FData.SetMaxAngle(180.0f);
		m_FData.SetSpeed(400.0f);
		m_FData.SetType(FLIGHT_TYPE::GO_TYPE);
		EnemyMove(Time);
		break;
		// 오른쪽으로 간다
	case RIGHT_WAY:
		m_FData.SetAngle(90.0f);
		m_FData.SetMaxAngle(90.0f);
		m_FData.SetSpeed(400.0f);
		m_FData.SetType(FLIGHT_TYPE::GO_TYPE);
		EnemyMove(Time);
		break;
		// 왼쪽으로 간다
	case LEFT_WAY:
		m_FData.SetAngle(260.0f);
		m_FData.SetMaxAngle(260.0f);
		m_FData.SetSpeed(400.0f);
		m_FData.SetType(FLIGHT_TYPE::GO_TYPE);
		EnemyMove(Time);
		break;
		// 오른쪽으로 코너를 돈다
	case RIGHT_CONNER_WAY:
		Angle = m_FData.GetAngle();
		if (Angle > m_FData.GetMaxAngle())
		{
			float Angle = m_FData.GetAngle() - 4.0f;
			m_FData.SetAngle(Angle);
		}
		EnemyMove(Time);
		break;
		// 왼쪽으로 코너를 돈다
	case LEFT_CONNER_WAY:
		Angle = m_FData.GetAngle();
		if (Angle < m_FData.GetMaxAngle())
		{
			float Angle = m_FData.GetAngle() + 4.0f;
			m_FData.SetAngle(Angle);
		}
		EnemyMove(Time);
		break;
		// 뒤로 돌아간다.
	case BACK_WAY:
		Angle = m_FData.GetAngle();
		Angle += 360.0f - Angle;
		m_FData.SetAngle(Angle);
		EnemyMove(Time);
		break;
	}
}

void EnemyManager::SetStage(FRECT Stage)
{
	m_Stage = Stage;
}

bool EnemyManager::OnDisplay()
{
	if (m_pos.x - (m_FData.GetSpeed() * g_ETime) < m_Stage.left)
	{
		return true;
	}
	if (m_pos.x + (m_FData.GetSpeed() * g_ETime) > m_Stage.right)
	{
		return true;
	}
	if (m_pos.y - (m_FData.GetSpeed() * g_ETime) < m_Stage.top)
	{
		return true;
	}
	if (m_pos.y + (m_FData.GetSpeed() * g_ETime) > m_Stage.bottom)
	{
		return true;
	}
	return false;
}
