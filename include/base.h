#ifndef BASE_H
#define BASE_H

#include "definitions.h"
#include <limits>
#define uint unsigned
#define ldoub long double

class Color
{
private:
	uint value;
public:
	Color()
	{
		value = C::Default;
	}
	Color(uint c)
	{
		value = c % 16777216;
	}
	Color(uint r, uint g, uint b)
	{
		value = r << 16 | g << 8 | b;
	}
	~Color();
	uint color() const
	{
		return value;
	}
	uint red() const
	{
		return (value >> 16) & 0xFF;
	}
	uint green() const
	{
		return (value >> 8) & 0xFF;
	}
	uint blue() const
	{
		return value & 0xFF;
	}
};

class IConstraint
{
public:
	virtual ldoub error() = 0;
	virtual ldoub differential() = 0;
	virtual V::TConstraint type() const = 0;
	virtual ldoub value() const = 0;
};

class IInterface
{
	virtual void Draw_Point(uint, ldoub, ldoub, Color) = 0;
	virtual void Draw_Segment(uint, ldoub, ldoub, ldoub, ldoub, Color) = 0;
	virtual void Draw_Circle(uint, ldoub, ldoub, ldoub, Color) = 0;
	virtual void Draw_Line(uint, ldoub, ldoub, ldoub, ldoub, Color) = 0;
	virtual void Write_Constraint(uint, V::TConstraint) = 0;
};

class ID
{
private:
	unsigned _id;
public:
	ID()
	{
		_id = 0;
	}
	ID(uint id)
	{
		_id = id;
	}
	uint value() const
	{
		return _id;
	}
	uint operator=(ID i)
	{
		_id = i._id;
		return _id;
	}
	bool operator==(ID i)
	{
		return _id == i._id;
	}
	bool operator==(uint i)
	{
		return _id == i;
	}
	bool operator==(int i)
	{
		return _id == static_cast<uint>(i);
	}
	bool operator!=(ID i)
	{
		return _id != i._id;
	}
	bool operator!=(uint i)
	{
		return _id != i;
	}
	bool operator!=(int i)
	{
		return _id != static_cast<uint>(i);
	}
};
#undef ldoub
#undef uint
#endif