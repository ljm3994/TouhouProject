#include "stdafx.h"
#include "BulletManager.h"

BulletManager::BulletManager(Vecter Pos, float BulletSize, float BulletSpeed, float FireSpeed, float Angle, float RotateAngle)
	:m_Pos(Pos),m_BulletSpeed(BulletSpeed), m_FireSpeed(FireSpeed), m_FireAngle(Angle), m_FireAngle_rotate(RotateAngle)
{
	m_crBullet.x = Pos.x;
	m_crBullet.y = Pos.y;
	m_crBullet.r = round(BulletSize / 2);
}

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
}

void BulletManager::render()
{
	IMGMANAGER->frameRender("Bullet", g_MemDC, 2, 0, (m_crBullet.x - m_crBullet.r) - 3, (m_crBullet.y - m_crBullet.r) - 3, 20, 20);
}

void BulletManager::SetSpeed(float Speed)
{
	m_BulletSpeed = Speed;
}

void BulletManager::SetFireSpeed(float Speed)
{
	m_FireSpeed = Speed;
}

void BulletManager::SetAngle(float Angle)
{
	m_FireAngle = Angle;
}

void BulletManager::SetRotateAngle(float Angle)
{
	m_FireAngle_rotate = Angle;
}

void BulletManager::SetStage(FRECT Stage)
{
	m_Stage = Stage;
}

float BulletManager::GetRotateAngle()
{
	return m_FireAngle_rotate;
}

float BulletManager::GetAngle()
{
	return m_FireAngle;
}

float BulletManager::GetSpeed()
{
	return m_FireSpeed;
}

float BulletManager::GetBulletSpeed()
{
	return m_BulletSpeed;
}

void BulletManager::SetPos(Vecter pos)
{
	m_Pos = pos;
	m_crBullet.x = pos.x;
	m_crBullet.y = pos.y;
}


bool BulletManager::GetFire()
{
	return m_IsFire;
}

void BulletManager::SetFire(bool Fire)
{
	m_IsFire = Fire;
}

void BulletManager::SetSize(float Size)
{
	m_crBullet.r = round(Size / 2);
}

bool BulletManager::OnDisplay()
{
	if ((m_crBullet.x + m_crBullet.r) + (GetBulletSpeed() * g_ETime) > m_Stage.right)
	{
		return true;
	}
	if ((m_crBullet.x - m_crBullet.r) - (GetBulletSpeed() * g_ETime) < m_Stage.left)
	{
		return true;
	}
	if ((m_crBullet.y - m_crBullet.r) - (GetBulletSpeed() * g_ETime) < m_Stage.top)
	{
		return true;
	}
	if ((m_crBullet.y + m_crBullet.r) + (GetBulletSpeed() * g_ETime) > m_Stage.bottom)
	{
		return true;
	}
	return false;
}

bool BulletManager::CharColide(FRECT Object)
{
	if (IntersectRectCircle(Object, m_crBullet))
	{
		return true;
	}
	return false;
}

FCIRCLE BulletManager::GetBullet()
{
	return m_crBullet;
}

Vecter BulletManager::GetPos()
{
	return m_Pos;
}
