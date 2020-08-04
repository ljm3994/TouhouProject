#include "stdafx.h"
#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(Vecter Pos, float BulletSize, float BulletSpeed, float FireSpeed, float Angle, float RotateAngle, FIRE_TYPE Type)
	:BulletManager(Pos, BulletSize, BulletSpeed, FireSpeed, Angle, RotateAngle), m_Type(Type)
{
}

EnemyBullet::EnemyBullet()
{
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::update()
{
	SetBullet(g_ETime);
	switch (m_Type)
	{
	case NORMAL_FIRE:
		FireFly();
		break;
	case AIMED_FIRE:
		AimedFireBullet(g_ETime);
		break;
	case N_WAY_FIRE:
		N_AwayFire(g_ETime);
		break;
	case MULTI_FIRE:
		CircleFireBullet();
		break;
	case FIRE_TYPE_NUM:
		CircleFireBullet();
		break;
	case CIRCLE_FIRE:
		CircleFireBullet();
		break;
	}
}

HRESULT EnemyBullet::init()
{
	m_bFirst = false;
	m_AimeFirst = true;
	m_fSec_count = 0.0f;
	m_Time = 0.0f;
	return S_OK;
}

void EnemyBullet::release()
{
}

void EnemyBullet::SetBullet(const float time)
{
	if (m_bFirst)
	{
		m_bFirst = false;
	}
	if(!m_bFirst && !GetFire())
	{
		m_fSec_count += time;
		float Angle = GetAngle();
		float RotateAngle = GetRotateAngle();
		Angle += RotateAngle * time;
		//m_Time = 0;
		if (Angle >= 6.283185308f)
		{
			Angle -= 6.283185308f;
		}
		SetFire(true);
		SetAngle(Angle);
	}
}

void EnemyBullet::FireFly()
{
	if (!m_bFirst)
	{
		bool fire = GetFire();
		if (fire)
		{
			float Speed = GetSpeed();
			float Count = m_fSec_count;
			Vecter pos = GetPos();
			float Angle = GetAngle();
			Count -= (Speed);

			pos.x += cosf((Angle * TORADIAN) * Count) * (WINSIZEX / GetBulletSpeed()* g_ETime);
			pos.y += sinf((Angle * TORADIAN) * Count) * (WINSIZEY / GetBulletSpeed()* g_ETime);

			SetPos(pos);
		}
	}
}

void EnemyBullet::FireBullet()
{
	if (!m_bFirst)
	{
		bool fire = GetFire();
		if (fire)
		{
			float Speed = GetSpeed();
			float Count = m_fSec_count;
			Vecter pos = GetPos();
			float Angle = GetAngle();
			float RotateAngle = GetRotateAngle();
			Count -= (Speed);
			
			pos.x += cosf(Angle - (RotateAngle * TORADIAN) * Count) * (GetBulletSpeed() * g_ETime);
			pos.y += sinf(Angle - (RotateAngle * TORADIAN) * Count) * (GetBulletSpeed()* g_ETime);
			//cout << m_fSec_count << endl;

			SetPos(pos);
		}
	}
}

void EnemyBullet::SetPlayerPos(Vecter * pos)
{
	m_PlayerPos = pos;
}

void EnemyBullet::CircleFireBullet()
{
	if (!m_bFirst)
	{
		m_Time += g_ETime;
		bool fire = GetFire();
		if (fire)
		{
		
			float Angle = GetAngle();
			float rotateAngle = GetRotateAngle();
			float Speed = GetSpeed();
			float bulletSpeed = GetBulletSpeed();
			Vecter pos = GetPos();
			float rad = (Angle + 1.0f) * TORADIAN;
			pos.x += (bulletSpeed * g_ETime) * cosf(rad);
			pos.y += (bulletSpeed * g_ETime) * sinf(rad);
			Angle += rotateAngle *g_ETime;
			//bulletSpeed += Speed;
			SetAngle(Angle);
			//SetSpeed(bulletSpeed);
			//cout << m_fSec_count << endl;

			SetPos(pos);
		}
	}
}

void EnemyBullet::AimedFireBullet(const float Time)
{
	if (!m_bFirst)
	{
		bool fire = GetFire();
		if (fire)
		{
			m_Time += g_ETime;
			//cout << "Time : " << m_Time << endl;
			if (m_Time >= 2.0f)
			{
				if (m_AimeFirst)
				{
					m_AimeFirst = false;
					Vecter pos = GetPos();
					float Angle = GetDegree(m_PlayerPos->x, m_PlayerPos->y, pos.x, pos.y);
					SetAngle(Angle);
				}
				float Speed = GetSpeed();
				float Angle = GetAngle();
				float rotateAngle = GetRotateAngle();
				float bulletSpeed = GetBulletSpeed();
				Vecter pos = GetPos();
				pos.x -= (bulletSpeed * g_ETime) * cosf(Angle * TORADIAN);
				pos.y += (bulletSpeed * g_ETime) * sinf(Angle* TORADIAN);
				
				SetAngle(Angle);
				SetPos(pos);
			}
			else
			{
				CircleFireBullet();
			}
		}
	}
}

void EnemyBullet::N_AwayFire(const float Time)
{
	if (!m_bFirst)
	{
		bool fire = GetFire();
		if (fire)
		{
			m_Time += g_ETime;
			//cout << "Time : " << m_Time << endl;
			if (m_Time <= 1.5f)
			{
				CircleFireBullet();
			}
			else if(m_Time >= 4.0f)
			{
				if (m_AimeFirst)
				{
					m_AimeFirst = false;
					Vecter pos = GetPos();
					float Angle = GetFromFloatTo(10.0f, 350.0f);
					SetAngle(Angle);
				}
				float Speed = GetSpeed();
				float Angle = GetAngle();
				float rotateAngle = GetRotateAngle();
				float bulletSpeed = GetBulletSpeed();
				Vecter pos = GetPos();
				pos.x -= (bulletSpeed * g_ETime) * cosf(Angle * TORADIAN);
				pos.y += (bulletSpeed * g_ETime) * sinf(Angle* TORADIAN);

				SetAngle(Angle);
				SetPos(pos);
			}
		}
	}
}


void EnemyBullet::BulletSetting(Vecter Pos, float BulletSize, float BulletSpeed, float FireSpeed, float Angle, float RotateAngle, FIRE_TYPE Type)
{
	SetSize(BulletSize);
	SetPos(Pos);
	SetSpeed(BulletSpeed);
	SetFireSpeed(FireSpeed);
	SetAngle(Angle);
	SetRotateAngle(RotateAngle);
	m_Type = Type;
}

