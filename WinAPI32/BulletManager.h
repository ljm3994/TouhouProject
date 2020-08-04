#pragma once
#include "Option.h"
#include "GameNode.h"
class Player;
class BulletManager : public GameNode
{
private:
	FCIRCLE m_crBullet;
	Vecter    m_Pos;
	float m_BulletSpeed;			// �Ѿ��� �ʴ��̵��ϴ� �ȼ���
	float m_FireSpeed;			// �ʴ� �߻�ӵ�
	float  m_FireAngle;			// �߻簢, ����
	float m_FireAngle_rotate;		// �߻簢 ȸ���ӵ�, ����
	bool m_IsFire;         
	FRECT m_Stage; 
public:
	BulletManager(Vecter Pos, float BulletSize, float BulletSpeed, float FireSpeed, float Angle, float RotateAngle);
	BulletManager();
	~BulletManager();
	void render() override;
	//get,set �Լ�
	void SetSpeed(float Speed);
	void SetFireSpeed(float Speed);
	void SetAngle(float Angle);
	void SetRotateAngle(float Angle);
	void SetStage(FRECT Stage);
	float GetRotateAngle();
	float GetAngle();;
	float GetSpeed();
	float GetBulletSpeed();
	void SetPos(Vecter pos);
	bool GetFire();
	void SetFire(bool Fire);
	void SetSize(float Size);
	bool OnDisplay();
	bool CharColide(FRECT Object);
	FCIRCLE GetBullet();
	Vecter GetPos();
};

