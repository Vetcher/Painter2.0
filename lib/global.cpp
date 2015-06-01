#pragma once
#include "definitions.h"
#include <cmath>

long double length(long double x1, long double y1, long double x2, long double y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}