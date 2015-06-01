#pragma once

#include "base.h"
#include <vector>


class Recalculator : IInterface
{
private:
	std::vector<ldoub*> pointers;
	//std::vector<IConstraint*> constraints;
	IConstraint* constraint;

	bool BuildFigureGoldMethod();

public:

	virtual void Draw_Point(uint, ldoub, ldoub, flag, Color);
	virtual void Draw_Segment(uint, ldoub, ldoub, ldoub, ldoub, flag, Color);
	virtual void Draw_Circle(uint, ldoub, ldoub, ldoub, flag, Color);
	virtual void Draw_Line(uint, ldoub, ldoub, ldoub, ldoub, flag, Color);
	virtual void Write_Constraint(uint, V::TConstraint);

	void Calculate();
};
