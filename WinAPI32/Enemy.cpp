#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(float Xpos, float Ypos, float Width, float Height, int MaxBulletCount)
	:EnemyManager(Xpos, Ypos, Width, Height, MaxBulletCount)
{
	m_MaxBulletCount = 0;
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

HRESULT Enemy::init()
{
	m_IsFire = false;
	DelayMove = 0.0;
	m_DelayTime = 0.0f;
	return S_OK;
}

void Enemy::release()
{
}

void Enemy::update()
{
	if (!GetDie())                    //적 사망시 모든 행동을 정지한다.
	{
		m_UpdateDelayTime += g_ETime;
		if (m_UpdateDelayTime >= 0.02f)
		{
			if (!GetMoveEsc())
			{
				DirectMove(m_FData.GetDirect(), g_ETime);
			}
			else
			{
				SetFire(true);
				SetDirect();
				if (GetCurrentBullet() == 0)
				{
					m_DelayTime += g_ETime;
					if (m_DelayTime >= 2.0f)                //2초후 화면 밖으로 빠진다.
					{
						m_DelayTime = 0.0f;
						SetMoveEsc(false);
					}
				}
			}
			m_UpdateDelayTime = 0.0f;
		}
	}
	ShootUpdate(g_ETime);            //적이 사망했더라도 총알은 계속해서 날라가야 한다.
}

void Enemy::render()
{
	if (!GetDie() && m_pos.y > m_Stage.top)
	{
		IMGMANAGER->frameRender("Enemy", g_MemDC, m_Option.GetFrame().x, m_Option.GetFrame().y, m_rc.left, m_rc.top, 40, 40);
		//DrawfRect(g_MemDC, m_rc);
	}
	for (m_BulletIt = m_Bullet.begin(); m_BulletIt != m_Bullet.end(); m_BulletIt++)
	{
		(*m_BulletIt)->render();
	}
}

void Enemy::SetInit(float Xpos, float Ypos, float Width, float Height, int MaxBulletCount)
{
	m_FData.SetDirect(ENEMY_DIRECT::GO_AWAY);
	m_FData.SetMaxDistance((GetFromIntTo(170, 230)));
	m_MaxBulletCount = MaxBulletCount;
	m_pos = { Xpos, Ypos };
	m_rc = RectMakeCenter(Xpos, Ypos, Width, Height);
}

