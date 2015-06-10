#pragma once

#include "base.h"
#include <map>
#include "definitions.h"
#include <utility>



class GlobalStorage
{
private:
	typedef std::pair<uint, ObjectBase*> objectPair;
	typedef std::pair<ldoub*, bool> paraPair;
	typedef std::map<uint, ObjectBase*> SofObjects;

	uint _last_id;
	SofObjects _storage_of_objects;
	std::map<ldoub*, bool> _parameters;
	SofObjects _selected_objects;

	uint _generate_id();
	bool _isInArea(ldoub x, ldoub y, ldoub x1, ldoub y1, ldoub x2, ldoub y2);
public:
	GlobalStorage();
	~GlobalStorage();

	void Clear();
	//void ReturnBack();

	bool Upload_All_To(IInterface&);
	bool GetObject(IInterface&, uint);
	bool GetConstraint(IInterface&, uint);

	bool SelectObject(uint id);
	uint SelectObject(ldoub x, ldoub y);
	void SelectObjects(ldoub x1, ldoub y1, ldoub x2, ldoub y2);
	void ClearSelection();

	ID NewPoint(ldoub x, ldoub y, flag fixed, Color color = V::Default, ID id = 0);
	ID NewSegment(uint point1_id, uint point2_id, Color color = V::Default, ID id = 0);
	ID NewLine(ldoub a, ldoub b, ldoub c, flag fixed, Color color = V::Default, ID id = 0);
	ID NewCircle(uint point_id, ldoub r, flag fixed, Color color = V::Default, ID id = 0);
};
