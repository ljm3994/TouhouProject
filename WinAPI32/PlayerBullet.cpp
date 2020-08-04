#include "stdafx.h"
#include "PlayerBullet.h"


PlayerBullet::PlayerBullet()
{
}


PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::update()
{
	float Speed = GetSpeed();
	Vecter pos = GetPos();
	float Angle = GetAngle();

	pos.x += cosf((Angle * TORADIAN)) * (GetBulletSpeed()) * g_ETime;
	pos.y -= sinf((Angle * TORADIAN)) * (GetBulletSpeed())* g_ETime;

	SetPos(pos);
}

HRESULT PlayerBullet::init()
{
	m_Time = 0.0f;
	return S_OK;
}

void PlayerBullet::release()
{
}
