#pragma once
#include "TanMakGame.h"
class MainScreen : public GameNode
{
	TanMakGame * Game;
	bool m_bStart;
	bool m_isEnter;
	bool m_Loading;
	float m_DelayTime;
	int Xpos;
	FPOINT Logo3Angle;
	int m_FrameX;
	int m_FrameY;
	BYTE m_Alpha;
public:
	MainScreen();
	~MainScreen();	
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

