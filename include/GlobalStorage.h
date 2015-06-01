#pragma once

#include "base.h"
#include "mainwindow.h"
#include <map>

#define uint unsigned
#define ldoub long double

class GlobalStorage
{
private:
	uint _last_id;
	std::map<uint, ObjectBase*> _storage_of_objects;

	ID _generate_id();
public:
	GlobalStorage();
	~GlobalStorage();

	void Clear();
	//void ReturnBack();

	bool Upload_All_To(const IInterface&);
	bool GetObject(const IInterface&, uint);
	bool GetConstraint(const IInterface&, uint);

	bool SelectObject(uint id);
	bool SelectObject(ldoub x, ldoub y);
	void ClearSelection();

	ID NewPoint(ldoub x, ldoub y, flag fixed, Color color = V::Default, ID id = 0);
	ID NewSegment(uint point1_id, uint point2_id, Color color = V::Default, ID id = 0);
	ID NewLine(ldoub a, ldoub b, ldoub c, flag fixed, Color color = V::Default, ID id = 0);
	ID NewCircle(uint point_id, ldoub r, flag fixed, Color color = V::Default, ID id = 0);
};

#undef uint
#undef ldoub

