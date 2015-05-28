#pragma once

#include "base.h"
#define uint unsigned
#define ldoub long double

class GlobalStorage
{
private:

public:
	GlobalStorage();
	~GlobalStorage();
	void Clear();
	bool Upload_All_To(const IInterface&);
	uint NewPoint(ldoub x, ldoub y, flag fixed, Color color = C::Default, uint id = 0);
	uint NewSegment(uint point1_id, uint point2_id, Color color = C::Default, uint id = 0);
	uint NewLine(ldoub a, ldoub b, ldoub c, flag fixed, Color color = C::Default, uint id = 0);
	uint NewCircle(uint point_id, ldoub r, flag fixed, Color color = C::Default, uint id = 0);
};

#undef uint
#undef ldoub

