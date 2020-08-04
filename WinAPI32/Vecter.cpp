#include "stdafx.h"
#include "Vecter.h"


Vecter::Vecter(const float vecX, const float vecY)
{
	x = vecX;
	y = vecY;
}

Vecter::Vecter()
{
	x = 0.0f;
	y = 0.0f;
}

Vecter::~Vecter()
{
}

Vecter & Vecter::operator=(const Vecter & vecForCopy)
{
	x = vecForCopy.x;
	y = vecForCopy.y;
	return *this;
}

Vecter & Vecter::operator=(const float floatForCopy)
{
	x = floatForCopy;
	y = floatForCopy;
	return *this;
}

Vecter & Vecter::operator+(const Vecter & vecForPlus)
{
	x += vecForPlus.x;
	y += vecForPlus.y;
	return *this;
}

Vecter & Vecter::operator+(const float floatForPlus)
{
	x += floatForPlus;
	y += floatForPlus;
	return *this;
}

Vecter & Vecter::operator-(const Vecter & vecForMinus)
{
	x -= vecForMinus.x;
	y -= vecForMinus.y;
	return *this;
}

Vecter & Vecter::operator-(const float floatForMinu)
{
	x -= floatForMinu;
	y -= floatForMinu;
	return *this;
}

Vecter & Vecter::operator*(const Vecter & vecForMulti)
{
	x *= vecForMulti.x;
	y *= vecForMulti.y;
	return *this;
}

Vecter & Vecter::operator*(const float floatForMulti)
{
	x *= floatForMulti;
	y *= floatForMulti;
	return *this;
}

Vecter & Vecter::operator/(const Vecter & vecForDivide)
{
	if (!vecForDivide.x && !vecForDivide.y)
	{
		x /= vecForDivide.x;
		y /= vecForDivide.y;
	}
	return *this;
}

Vecter & Vecter::operator/(const float floatForDivide)
{
	if (!floatForDivide)
	{
		x /= floatForDivide;
		y /= floatForDivide;
	}
	return *this;
}

bool Vecter::operator==(const Vecter compareVec)
{
	if (x != compareVec.x)
	{
		return FALSE;
	}
	else if (y != compareVec.y)
	{
		return FALSE;
	}
	return TRUE;
}

Vecter Vecter::GetMinusVec() const
{
	return Vecter(-x, -y);
}

Vecter Vecter::GetYSymmetryVec() const
{
	return Vecter(-x, y);
}

Vecter Vecter::GetXSymmetryVec() const
{
	return Vecter(x, -y);
}
