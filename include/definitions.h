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

}
namespace C
{
	enum VColor : unsigned
	{
		Selected = 0x3560d6,
		Default = 0x000000,
		Black = 0x000000,
		White = 0xffffff,
		LightRed = 0xffaaaa,
		Red = 0xff0000,
		DarkRed = 0xaa0000,
		LightGreen = 0xaaffaa,
		Green = 0x00ff00,
		DarkGreen = 0x00aa00,
		LightBlue = 0xaaaaff,
		Blue = 0x0000ff,
		DarkBlue = 0x0000aa,
		LightGray = 0xdddddd,
		Gray = 0x888888,
		DarkGray = 444444
	};
}

#endif