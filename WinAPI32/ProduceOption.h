#pragma once
#include "Vecter.h"
#include "Option.h"
enum ENEMY_TYPE
{
	ZACO_TYPE,
	NONE_TYPE,
	BOSS_TYPE
};

enum FLIGHT_TYPE
{
	BOSS_MOVE,
	TRIANGLE_TYPE,
	GO_TYPE,
};

class ProduceOption
{
	ENEMY_TYPE m_Type;
	FIRE_TYPE m_FireType;
	Vecter m_Fraem;
	float m_HP;		// 생명력
	float m_AttackDamage;		// 공격력
	bool m_ALive;				// 살아있는 상태
public:
	ProduceOption(float Hp, float Damage, bool Alive, ENEMY_TYPE Type, FIRE_TYPE FType, Vecter Fram);
	ProduceOption();
	~ProduceOption();
	void SetFrame(Vecter Fraem);
	Vecter GetFrame();
	float GetHP();
	float GetDamage();
	bool GetLive();
	void SetHp(float Hp);
	void SetDamage(float Damage);
	void SetAlive(bool Live);
	void SetType(ENEMY_TYPE Type, FIRE_TYPE FType);
	ENEMY_TYPE GetEnemyType();
	FIRE_TYPE GetFireType();
	//BULLET_TYPE GetBulletType;
};

class Flight_Data
{
	FLIGHT_TYPE m_Type;
	Vecter m_initPos;
	ENEMY_DIRECT m_direct;
	float m_MaxAngle;
	float m_Speed;
	float m_MaxDistance;
	float m_Angle;
	float m_RatateAngle;
public:
	Flight_Data(FLIGHT_TYPE Type, float Speed, float m_MaxDistance);
	Flight_Data();
	~Flight_Data();
	float GetSpeed();
	float GetMaxDistance();
	float GetAngle();
	float GetRotateAngle();
	ENEMY_DIRECT GetDirect();
	void SetDirect(ENEMY_DIRECT direct);
	void SetRatateAngle(float RoateAngle);
	FLIGHT_TYPE GetType();
	void SetSpeed(float Speed);
	void SetMaxDistance(float MaxDistance);
	float GetMaxAngle();
	void SetMaxAngle(float Angle);
	void SetType(FLIGHT_TYPE Type);
	void SetAngle(float Angle);
	Vecter GetInitPos();
	void SetInitPos(Vecter pos);
	bool isMaxDistance(Vecter pos);
};
