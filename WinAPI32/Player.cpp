#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	ZeroMemory(&m_Pos, sizeof(m_Pos));
	ZeroMemory(&m_rc, sizeof(m_rc));
}


Player::~Player()
{
}

HRESULT Player::init()
{
	DelayTime = 0.0f;
	m_Speed = 300.0f;
	m_isDead = false;
	Cheat = false;
	FrameX = 0;
	m_RotateAngle = 0.0f;
	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	DelayTime += g_ETime;

	if (!m_isDead)
	{
		if (KEYMANAGER->StayKeyDown(VK_LEFT) && m_rc.left - (m_Speed * g_ETime) > m_Stage.left)
		{
			m_Pos.x -= m_Speed * g_ETime;
		}
		if (KEYMANAGER->StayKeyDown(VK_RIGHT) && m_rc.right + (m_Speed * g_ETime) < m_Stage.right)
		{
			m_Pos.x += m_Speed * g_ETime;
		}
		if (KEYMANAGER->StayKeyDown(VK_UP) && m_rc.top > m_Stage.top)
		{
			m_Pos.y -= m_Speed * g_ETime;
		}
		if (KEYMANAGER->StayKeyDown(VK_DOWN) && m_rc.bottom < m_Stage.bottom)
		{
			m_Pos.y += m_Speed * g_ETime;
		}
		if (KEYMANAGER->StayKeyDown(VK_F9))
		{
			Cheat = true;
		}
		if (KEYMANAGER->StayKeyDown(VK_SPACE))
		{
			if (DelayTime > 0.2f)
			{
				DelayTime = 0.0f;
				SOUNDMANAGER->play("GUN", 0.8f);
				PlayerBullet* bulet = ObjectPool<PlayerBullet>::GetInstance()->GetObObject();
				bulet->init();
				bulet->SetPos(m_Pos);
				bulet->SetStage(m_Stage);
				bulet->SetAngle(90.0f);
				bulet->SetFireSpeed(0.23f);
				bulet->SetSpeed(500.0f);
				bulet->SetSize(10.0f);
				m_PlBullet.emplace_back(bulet);
			}
		}
		m_PlBulletit = m_PlBullet.begin();
		while (m_PlBulletit != m_PlBullet.end())
		{
			(*m_PlBulletit)->update();
			if ((*m_PlBulletit)->OnDisplay())
			{
				ObjectPool<PlayerBullet>::GetInstance()->PushObject((*m_PlBulletit));
				m_PlBulletit = m_PlBullet.erase(m_PlBulletit++);
			}
			else
			{
				m_PlBulletit++;
			}
		}
	}
	else
	{
		if (DelayTime > 0.2f && FrameX == 0)
		{
			DelayTime = 0.0f;
			FrameX = 1;
		}
		else if (DelayTime > 0.5f &&FrameX == 1)
		{
			m_RotateAngle++;
			if (DelayTime >= 2.0f)
			{
				m_RotateAngle = 0;
				DelayTime = 0.0f;
				FrameX = 2;
			}
		}
	}
	m_rc = RectMakeCenter(m_Pos.x, m_Pos.y, m_Width, m_Height);
}

void Player::render()
{
	//DrawfRect(g_MemDC, m_rc);
	if (!m_isDead)
	{
		IMGMANAGER->render("Charter", g_MemDC, m_rc.left - 10, m_rc.top - 5, 55, 55);
		m_PlBulletit = m_PlBullet.begin();
		while (m_PlBulletit != m_PlBullet.end())
		{
			(*m_PlBulletit)->render();
			m_PlBulletit++;
		}
	}
	else
	{
		IMGMANAGER->frameRotateRender("Effect", g_MemDC, m_RotateAngle * TORADIAN, false, 1.0f, FrameX, 0, m_rc.left - 10, m_rc.top - 5);
	}
}

void Player::SetStage(FRECT stage)
{
	m_Stage = stage;
}

void Player::SetPlayer(float XPos, float Ypos, float Width, float Height)
{
	m_Pos = { XPos, Ypos };
	m_Width = Width;
	m_Height = Height;
	m_rc = RectMakeCenter(m_Pos.x - 5, m_Pos.y, Width, Height);
}

bool Player::OnColid(FCIRCLE rc)
{
	if (IntersectRectCircle(m_rc, rc))
	{
		return true;
	}
	return false;
}

void Player::SetPlayerDie(bool Die)
{
	if (!Cheat)
	{
		m_isDead = Die;
	}
	else
	{
		m_isDead = false;
	}
}

bool Player::GetPlayerDie()
{
	return m_isDead;
}

bool Player::EnemyColidBullet(FRECT rc)
{
	m_PlBulletit = m_PlBullet.begin();
	while (m_PlBulletit != m_PlBullet.end())
	{
		if ((*m_PlBulletit)->CharColide(rc))
		{
			ObjectPool<PlayerBullet>::GetInstance()->PushObject((*m_PlBulletit));
			m_PlBullet.erase(m_PlBulletit++);
			return true;
		}
		else
		{
			m_PlBulletit++;
		}
	}
	return false;
}

Vecter * Player::GetPlayerpos()
{
	return &m_Pos;
}

FRECT Player::GetPlayer()
{
	return m_rc;
}
