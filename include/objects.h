#pragma once

#include "base.h"

class Point : public ObjectBase
{
public:
	ldoub* x;
	ldoub* y;
	Point(ldoub*_xx = 0, ldoub* _yy = 0)
	{
		x = _xx;
		y = _yy;
	}
	virtual ~Point()
	{

	}
	virtual V::TObject type() const
	{
		return V::POINT;
	}
};

class Segment : public ObjectBase
{
public:
	Point* point1;
	Point* point2;
	Segment()
	{
		point1 = 0;
		point2 = 0;
	}

	Segment(Point *_point1, Point *_point2)
	{
		point1 = _point1;
		point2 = _point2;
	}
	virtual ~Segment()
	{

	}
	virtual V::TObject type() const
	{
		return V::SEGMENT;
	}
};

class Circle :public ObjectBase
{
public:
	Point* point;
	ldoub* radius;

	Circle()
	{
		point = 0;
		radius = 0;
	}
	virtual ~Circle()
	{

	}
	Circle(Point *_point, ldoub *_radius = 0)
	{
		point = _point;
		radius = _radius;
	}
	virtual V::TObject type() const
	{
		return V::CIRCLE;
	}
};

class Line : public ObjectBase
{
public:
	ldoub* A;
	ldoub* B;
	ldoub* C;

	Line(ldoub* a = 0, ldoub* b = 0, ldoub* c = 0)
	{
		A = a; B = b; C = c;
	}
	virtual ~Line()
	{

	}
	virtual V::TObject type() const
	{
		return V::LINE;
	}
};