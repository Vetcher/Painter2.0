#pragma once
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
		value = V::Default;
	}
	Color(uint c)
	{
		value = c % 16777216;
	}
	Color(uint r, uint g, uint b)
	{
		value = r << 16 | g << 8 | b;
	}
	~Color()
	{
		
	}
	void operator=(uint a)
	{
		value = a;
	}
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

class flag
{
private:
	unsigned char _body;
public:
	flag()
	{
		_body = 0;
	}
	~flag()
	{

	}
	flag(unsigned char a)
	{
		_body = a;
	}
	flag(bool t0, bool t1 = false, bool t2 = false, bool t3 = false,
		  bool t4 = false, bool t5 = false, bool t6 = false, bool t7 = false)
	{
		_body = t0 | t1 << 1 | t2 << 2 | t3 << 3 | t4 << 4 | t5 << 5 | t6 << 6 | t7 << 7;
	}
	bool _0() const
	{
		return _body & 1 ? true : false;
	}
	bool _1() const
	{
		return _body & 2 ? true : false;
	}
	bool _2() const
	{
		return _body & 4 ? true : false;
	}
	bool _3() const
	{
		return _body & 8 ? true : false;
	}
	bool _4() const
	{
		return _body & 16 ? true : false;
	}
	bool _5() const
	{
		return _body & 32 ? true : false;
	}
	bool _6() const
	{
		return _body & 64 ? true : false;
	}
	bool _7() const
	{
		return _body & 128 ? true : false;
	}
	bool operator==(const flag& f) const
	{
		return _body == f._body;
	}
	bool operator!=(const flag& f) const
	{
		return _body == f._body;
	}
};

class IConstraint
{
public:
	virtual ldoub error() = 0;
	virtual ldoub differential(ldoub* arg) = 0;
	virtual V::TConstraint type() const = 0;
	virtual ldoub value() const = 0;
};

class IInterface
{
	virtual void Draw_Point(uint, ldoub, ldoub, flag, V::Color) = 0;
	virtual void Draw_Segment(uint, ldoub, ldoub, ldoub, ldoub, flag, V::Color) = 0;
	virtual void Draw_Circle(uint, ldoub, ldoub, ldoub, flag, V::Color) = 0;
	virtual void Draw_Line(uint, ldoub, ldoub, ldoub, ldoub, flag, V::Color) = 0;
	virtual void Write_Constraint(uint, V::TConstraint) = 0;
};

/*class Igui : IInterface
{
	virtual void Draw_Point(uint, ldoub, ldoub, Color) = 0;
	virtual void Draw_Segment(uint, ldoub, ldoub, ldoub, ldoub, Color) = 0;
	virtual void Draw_Circle(uint, ldoub, ldoub, ldoub, Color) = 0;
	virtual void Draw_Line(uint, ldoub, ldoub, ldoub, ldoub, Color) = 0;

	virtual void Write_Point(uint, ldoub, ldoub, flag, Color) = 0;
	virtual void Write_Segment(uint, ldoub, ldoub, ldoub, ldoub, flag, Color) = 0;
	virtual void Write_Circle(uint, ldoub, ldoub, ldoub, flag, Color) = 0;
	virtual void Write_Line(uint, ldoub, ldoub, ldoub, flag, Color) = 0;
	virtual void Write_Constraint(uint, V::TConstraint) = 0;
};*/

class ObjectBase
{
private:
	bool _select;
	bool _visible;
public:
	Color color;
	ID id;
	ObjectBase()
	{
		_select = false;
		_visible = false;
	}
	virtual ~ObjectBase()
	{

	}
	bool select() const
	{
		return _select;
	}
	bool changeSelect()
	{
		_select = !_select;
		return _select;
	}
	bool changeSelect(bool stat)
	{
		_select = stat;
		return _select;
	}
	virtual V::TObject type() const = 0;
};

#undef ldoub
#undef uint
#endif