#include "stdafx.h"
#include "ProduceOption.h"

ProduceOption::ProduceOption(float Hp, float Damage, bool Alive, ENEMY_TYPE Type, FIRE_TYPE FType, Vecter Fram)
	:m_HP(Hp), m_AttackDamage(Damage), m_ALive(Alive), m_Type(Type), m_FireType(FType), m_Fraem(Fram)
{
	m_ALive = false;
}

ProduceOption::ProduceOption()
{
	
}

ProduceOption::~ProduceOption()
{
}

void ProduceOption::SetFrame(Vecter Fraem)
{
	m_Fraem = Fraem;
}

Vecter ProduceOption::GetFrame()
{
	return m_Fraem;
}

float ProduceOption::GetHP()
{
	return m_HP;
}

float ProduceOption::GetDamage()
{
	return m_AttackDamage;
}

bool ProduceOption::GetLive()
{
	return m_ALive;
}

void ProduceOption::SetHp(float Hp)
{
	m_HP = Hp;
}

void ProduceOption::SetDamage(float Damage)
{
	m_AttackDamage = Damage;
}

void ProduceOption::SetAlive(bool Live)
{
	m_ALive = Live;
}

void ProduceOption::SetType(ENEMY_TYPE Type, FIRE_TYPE FType)
{
	m_Type = Type;
	m_FireType = FType;
}

ENEMY_TYPE ProduceOption::GetEnemyType()
{
	return m_Type;
}

FIRE_TYPE ProduceOption::GetFireType()
{
	return m_FireType;
}

Flight_Data::Flight_Data(FLIGHT_TYPE Type, float Speed, float m_MaxDistance)
{
	SetType(Type);
	SetSpeed(Speed);
	SetMaxDistance(m_MaxDistance);
	m_RatateAngle = 0;
	m_initPos = 0;
}

Flight_Data::Flight_Data()
{
}

Flight_Data::~Flight_Data()
{
}

float Flight_Data::GetSpeed()
{
	return m_Speed;
}

float Flight_Data::GetMaxDistance()
{
	return m_MaxDistance;
}

float Flight_Data::GetAngle()
{
	return m_Angle;
}

float Flight_Data::GetRotateAngle()
{
	return m_RatateAngle;
}

ENEMY_DIRECT Flight_Data::GetDirect()
{
	return m_direct;
}

void Flight_Data::SetDirect(ENEMY_DIRECT direct)
{
	m_direct = direct;
}

void Flight_Data::SetRatateAngle(float RoateAngle)
{
	m_RatateAngle = RoateAngle;
}

FLIGHT_TYPE Flight_Data::GetType()
{
	return m_Type;
}

void Flight_Data::SetSpeed(float Speed)
{
	m_Speed = Speed;
}

void Flight_Data::SetMaxDistance(float MaxDistance)
{
	m_MaxDistance = MaxDistance;
}

float Flight_Data::GetMaxAngle()
{
	return m_MaxAngle;
}

void Flight_Data::SetMaxAngle(float Angle)
{
	m_MaxAngle = Angle;
}

void Flight_Data::SetType(FLIGHT_TYPE Type)
{
	m_Type = Type;
}

void Flight_Data::SetAngle(float Angle)
{
	m_Angle = Angle;
}

Vecter Flight_Data::GetInitPos()
{
	return m_initPos;
}

void Flight_Data::SetInitPos(Vecter pos)
{
	m_initPos = pos;
}

bool Flight_Data::isMaxDistance(Vecter pos)
{
	float Distance = GetDistance(m_initPos.x, m_initPos.y, pos.x, pos.y);//pos.y - m_initPos.y;
	if (Distance > m_MaxDistance)
	{
		return true;
	}
	return false;
}

