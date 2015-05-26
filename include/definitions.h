#ifndef PI
#define PI 3.1415926535897932384

#include <cmath>

long double length(long double x1, long double y1, long double x2, long double y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

namespace V // identificator for all basic and global classes/enums/constants e.t.c.
{
	enum TConstraint : unsigned
	{
		Collector = 0,
		Distance_from_Point_to_Point
	};

	enum Color : unsigned
	{
		Selected = 0x3560d6,
		Default = 0x000000,
		Red = 0xff0000,
		Green = 0x00ff00,
		Blue = 0x0000ff
	};


}

#endif