#pragma once
#include "BulletManager.h"
class PlayerBullet : public BulletManager
{
	float		m_Time;
public:
	PlayerBullet();
	~PlayerBullet();
	void update() override;
	HRESULT init() override;
	void release() override;
};

