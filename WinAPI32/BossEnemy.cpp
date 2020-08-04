#include "stdafx.h"
#include "BossEnemy.h"


BossEnemy::BossEnemy(float Xpos, float Ypos, float Width, float Height, int m_MaxBulletCount)
	:EnemyManager(Xpos, Ypos, Width, Height, m_MaxBulletCount)
{
	m_MaxBulletCount = 0;
}

BossEnemy::BossEnemy()
{
}


BossEnemy::~BossEnemy()
{
}

void BossEnemy::SetHPPercent(float Damage)
{
	float Hp = m_Option.GetHP();
	Hp -= Damage;
	m_Percent = (Hp / m_MaxHp) * 100;
	cout << "Hp : " << Hp << m_Percent << endl;
	m_Option.SetHp(Hp);
}

HRESULT BossEnemy::init()
{
	m_bMove = true;
	m_Percent = 100;
	m_MaxHp = 0;
	m_MaxBulletCount = 0;
	m_Alpha = 255;
	return S_OK;
}

void BossEnemy::release()
{
}

void BossEnemy::update()
{
	m_UpdateDelayTime += g_ETime;
	if (m_UpdateDelayTime >= 0.02f)
	{
		if (!GetFire())
		{
			if (!GetMoveEsc())
			{
				//m_FData.SetMaxDistance(100);
				DirectMove(ENEMY_DIRECT::GO_AWAY, g_ETime);
			}
			else
			{
				SetFire(true);
				m_bMove = false;
				SetDirect();
				RandomPartern();
				SetMoveEsc(false);
			}
		}
		else
		{
			ShootUpdate(g_ETime);
			if (m_CurrentBulletCount == 0)
			{
				if (!GetMoveEsc())
				{
					DirectMove(m_FData.GetDirect(), g_ETime);
					RandomPartern();
				}
				else
				{
					m_MaxBulletCount = 0;
					RandomPartern();
					SetDirect();
					m_bMove = false;
					SetMoveEsc(false);
				}
			}
		}
		m_UpdateDelayTime = 0.0f;
	}
}

void BossEnemy::SetDirect()
{
	int Direct = GetFromIntTo(0, 4);
	m_FData.SetMaxDistance(100);
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

void BossEnemy::render()
{
	IMGMANAGER->frameAlphaRender("Boss", g_MemDC, m_Alpha, 1, 0, m_rc.left, m_rc.top, m_rc.right - m_rc.left, m_rc.bottom - m_rc.top);
	DrawfRect(g_MemDC, m_HPBar);
	GradientRender();
	for (m_BulletIt = m_Bullet.begin(); m_BulletIt != m_Bullet.end(); m_BulletIt++)
	{
		(*m_BulletIt)->render();
	}
}

bool BossEnemy::OnDisplay()
{
	if (m_pos.x + (m_FData.GetSpeed() * g_ETime) > m_Stage.right)
	{
		m_FData.SetMaxDistance(100);
		DirectMove(ENEMY_DIRECT::LEFT_WAY, g_ETime);
	}
	if (m_pos.x - (m_FData.GetSpeed() * g_ETime) < m_Stage.left)
	{
		m_FData.SetMaxDistance(100);
		DirectMove(ENEMY_DIRECT::RIGHT_WAY, g_ETime);
	}
	if (m_pos.y - (m_FData.GetSpeed() * g_ETime) < m_Stage.top + 100)
	{
		m_FData.SetMaxDistance(10);
		DirectMove(ENEMY_DIRECT::GO_AWAY, g_ETime);
	}
	if (m_pos.y + (m_FData.GetSpeed() * g_ETime) > (m_Stage.bottom / 2))
	{
		m_FData.SetMaxDistance(110);
		DirectMove(ENEMY_DIRECT::BACK_WAY, g_ETime);
	}
	return false;
}

void BossEnemy::RandomPartern()
{
	int Partern = GetInt(4);
	switch (Partern)
	{
	case 0:
		m_Option.SetType(ENEMY_TYPE::BOSS_TYPE, FIRE_TYPE::N_WAY_FIRE);
		break;
	case 1:
		m_Option.SetType(ENEMY_TYPE::BOSS_TYPE, FIRE_TYPE::CIRCLE_FIRE);
		break;
	case 2:
		m_Option.SetType(ENEMY_TYPE::BOSS_TYPE, FIRE_TYPE::MULTI_FIRE);
		break;
	case 3:
		m_Option.SetType(ENEMY_TYPE::BOSS_TYPE, FIRE_TYPE::AIMED_FIRE);
		break;
	}
}

bool BossEnemy::BossDie()
{
	if (m_Option.GetHP() <= 0)
	{
		return true;
	}
	return false;
}

void BossEnemy::SetInit(float Xpos, float Ypos, float Width, float Height, int MaxBulletCount)
{
	m_FData.SetDirect(ENEMY_DIRECT::GO_AWAY);
	m_FData.SetMaxDistance((GetFromIntTo(170, 230)));
	m_MaxHp = m_Option.GetHP();
	m_MaxBulletCount = MaxBulletCount;
	m_pos = { Xpos, Ypos };
	m_HPBar = RectMakeCenter(((m_Stage.left + (m_Stage.right - m_Stage.left)) / 2) + 25, m_Stage.top + 10, (m_Stage.right - m_Stage.left), 20);
	m_rc = RectMakeCenter(Xpos, Ypos, Width, Height);
}

void BossEnemy::GradientRender()
{
	GRADIENT_RECT gtr;
	TRIVERTEX vert[2];
	vert[0].x = m_HPBar.left;
	vert[0].y = m_HPBar.top + 1;
	vert[0].Red = 0xff00;
	vert[0].Green = 0;
	vert[0].Blue = 0;
	vert[0].Alpha = 0;
	vert[1].x = m_HPBar.left + ((m_HPBar.right - m_HPBar.left)  * (m_Percent / 100));
	vert[1].y = (m_HPBar.bottom - 1);
	vert[1].Red = 0xff00;
	vert[1].Green = 0;
	//0xff00;
	vert[1].Alpha = 0xff00;
	vert[1].Blue = 0;
	gtr.LowerRight = 0;
	gtr.UpperLeft = 1;

	GdiGradientFill(g_MemDC, vert, 2, &gtr, 1, GRADIENT_FILL_RECT_H);
}
