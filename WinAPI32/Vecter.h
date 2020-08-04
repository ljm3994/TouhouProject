#pragma once
class Vecter : public FPOINT
{
public:
	float		m_Time;
	Vecter(const float, const float);
	Vecter();
	~Vecter();
	Vecter& operator = (const Vecter &vecForCopy);
	Vecter& operator = (const float floatForCopy);
	Vecter& operator + (const Vecter &vecForPlus);
	Vecter& operator + (const float floatForPlus);
	Vecter& operator - (const Vecter &vecForMinus);
	Vecter& operator - (const float floatForMinu);
	Vecter& operator * (const Vecter &vecForMulti);
	Vecter& operator * (const float floatForMulti);
	Vecter& operator / (const Vecter &vecForDivide);
	Vecter& operator / (const float floatForDivide);
	bool operator==(const Vecter);

	Vecter GetMinusVec() const;
	Vecter GetYSymmetryVec() const;
	Vecter GetXSymmetryVec() const;
};

