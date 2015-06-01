#include "GlobalStorage.h"
#define uint unsigned
#define ldoub long double

GlobalStorage::GlobalStorage()
{

}


GlobalStorage::~GlobalStorage()
{

}

void GlobalStorage::Clear()
{

}

bool GlobalStorage::Upload_All_To(const IInterface&)
{
	return 0;
}
bool GlobalStorage::GetObject(const IInterface&, uint)
{
	return 0;
}
bool GlobalStorage::GetConstraint(const IInterface&, uint)
{
	return 0;
}

ID GlobalStorage::_generate_id()
{
	_last_id++;
	while (_storage_of_objects.count(_last_id))
	{
		_last_id++;
	}
	return ID(_last_id);
}

ID GlobalStorage::NewPoint(ldoub x, ldoub y, flag fixed, Color color, ID id)
{
	return 0;
}
ID GlobalStorage::NewSegment(uint point1_id, uint point2_id, Color color, ID id)
{
	return 0;
}
ID GlobalStorage::NewLine(ldoub a, ldoub b, ldoub c, flag fixed, Color color, ID id)
{
	return 0;
}
ID GlobalStorage::NewCircle(uint point_id, ldoub r, flag fixed, Color color, ID id)
{
	return 0;
}

#undef uint
#undef ldoub