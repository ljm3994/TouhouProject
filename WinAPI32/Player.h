#pragma once
#include "PlayerBullet.h"
#include "GameNode.h"
class Player : public GameNode
{
	Vecter m_Pos;
	FRECT m_rc;
	float DelayTime;
	float m_Speed;
	float m_Angle;
	float m_Width;
	float m_Height;
	bool m_isDead;
	int FrameX;
	bool Cheat;
	float m_RotateAngle;
	FRECT m_Stage;
	list<PlayerBullet *> m_PlBullet;
	list<PlayerBullet *>::iterator m_PlBulletit;
public:
	Player();
	~Player();
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	void SetStage(FRECT stage);
	void SetPlayer(float XPos, float Ypos, float Width, float Height);
	bool OnColid(FCIRCLE rc);
	void SetPlayerDie(bool Die);
	bool GetPlayerDie();
	bool EnemyColidBullet(FRECT rc);
	Vecter * GetPlayerpos();
	FRECT GetPlayer();
};

