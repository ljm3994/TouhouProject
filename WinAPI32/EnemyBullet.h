#pragma once
#include "BulletManager.h"
#include "Option.h"
class EnemyBullet : public BulletManager
{
	FIRE_TYPE m_Type;
	bool		 m_bFirst;
	float		 m_fSec_count;
	float		m_Time;
	bool m_AimeFirst;
	Vecter * m_PlayerPos;
public:
	EnemyBullet(Vecter Pos, float BulletSize, float BulletSpeed, float FireSpeed, float Angle, float RotateAngle, FIRE_TYPE Type);
	EnemyBullet();
	~EnemyBullet();
	void update() override;
	HRESULT init() override;
	void release() override;
	void SetBullet(const float time);
	void FireFly();
	void FireBullet();
	void SetPlayerPos(Vecter * pos);
	void CircleFireBullet();
	void AimedFireBullet(const float Time);
	void N_AwayFire(const float Time);
	void BulletSetting(Vecter Pos, float BulletSize, float BulletSpeed, float FireSpeed, float Angle, float RotateAngle, FIRE_TYPE Type);
};

