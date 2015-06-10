#include "GlobalStorage.h"
#include "objects.h"
#include <cmath>

GlobalStorage::GlobalStorage()
{
	_storage_of_objects.insert(objectPair(0, 0));
	_last_id = 0;
}


GlobalStorage::~GlobalStorage()
{
	{
		SofObjects::iterator s_end = _storage_of_objects.end();
		for (SofObjects::iterator i = _storage_of_objects.begin(); i != s_end; i++)
		{
			delete i->second;
		}
	}
	{
		std::map<ldoub*, bool>::iterator s_end = _parameters.end();
		for (std::map<ldoub*, bool>::iterator i = _parameters.begin(); i != s_end; i++)
		{
			delete i->first;
		}
	}
}

void GlobalStorage::Clear()
{
	_last_id = 0;
	_selected_objects.clear();
	{
		SofObjects::iterator s_end = _storage_of_objects.end();
		for (SofObjects::iterator i = _storage_of_objects.begin(); i != s_end; i++)
		{
			delete i->second;
		}
	}
	_storage_of_objects.clear();
	{
		std::map<ldoub*, bool>::iterator s_end = _parameters.end();
		for (std::map<ldoub*, bool>::iterator i = _parameters.begin(); i != s_end; i++)
		{
			delete i->first;
		}
	}
	_parameters.clear();
	_storage_of_objects.insert(objectPair(0, 0));
}

bool GlobalStorage::Upload_All_To(IInterface& Interface)
{
	for (SofObjects::iterator i = _storage_of_objects.begin(); i != _storage_of_objects.end(); i++)
	{
		if (i->first == 0) continue;
		switch (i->second->type())
		{
			case V::POINT:
			{
				Point* point = dynamic_cast<Point*>(i->second);
				Interface.Draw_Point(point->id.value(), *point->x, *point->y,
											flag(_parameters.find(point->x)->second,
											_parameters.find(point->y)->second), point->color);
				break;
			}
			case V::SEGMENT:
			{
				Segment* segment = dynamic_cast<Segment*>(i->second);
				Interface.Draw_Segment(segment->id.value(), *segment->point1->x, *segment->point1->y,
											  *segment->point2->x, *segment->point2->y,
											  flag(_parameters.find(segment->point1->x)->second,
											  _parameters.find(segment->point1->y)->second,
											  _parameters.find(segment->point2->x)->second,
											  _parameters.find(segment->point2->y)->second), segment->color);
				break;
			}
			case V::CIRCLE:
			{
				Circle* circle = dynamic_cast<Circle*>(i->second);
				Interface.Draw_Circle(circle->id.value(), *circle->point->x, *circle->point->y, *circle->radius,
											 flag(_parameters.find(circle->point->x)->second,
											 _parameters.find(circle->point->y)->second,
											 _parameters.find(circle->radius)->second), circle->color);
				break;
			}
			case V::LINE:
			{
				Line* line = dynamic_cast<Line*>(i->second);
				Interface.Draw_Line(line->id.value(), *line->A, *line->B, *line->C,
											 flag(_parameters.find(line->A)->second,
											 _parameters.find(line->B)->second,
											 _parameters.find(line->C)->second), line->color);
				break;
			}
			default:
				throw V::Error("Storage corrupted");
		}
	}
	return true;
}
bool GlobalStorage::GetObject(IInterface& Interface, uint id)
{
	SofObjects::iterator i = _storage_of_objects.find(id);
	if (i != _storage_of_objects.end())
	{
		switch (i->second->type())
		{
			case V::POINT:
			{
				Point* point = dynamic_cast<Point*>(i->second);
				Interface.Draw_Point(point->id.value(), *point->x, *point->y,
											flag(_parameters.find(point->x)->second,
											_parameters.find(point->y)->second), point->color);
				break;
			}
			case V::SEGMENT:
			{
				Segment* segment = dynamic_cast<Segment*>(i->second);
				Interface.Draw_Segment(segment->id.value(), *segment->point1->x, *segment->point1->y,
											  *segment->point2->x, *segment->point2->y,
											  flag(_parameters.find(segment->point1->x)->second,
											  _parameters.find(segment->point1->y)->second,
											  _parameters.find(segment->point2->x)->second,
											  _parameters.find(segment->point2->y)->second), segment->color);
				break;
			}
			case V::CIRCLE:
			{
				Circle* circle = dynamic_cast<Circle*>(i->second);
				Interface.Draw_Circle(circle->id.value(), *circle->point->x, *circle->point->y, *circle->radius,
											 flag(_parameters.find(circle->point->x)->second,
											 _parameters.find(circle->point->y)->second,
											 _parameters.find(circle->radius)->second), circle->color);
				break;
			}
			case V::LINE:
			{
				Line* line = dynamic_cast<Line*>(i->second);
				Interface.Draw_Line(line->id.value(), *line->A, *line->B, *line->C,
										  flag(_parameters.find(line->A)->second,
										  _parameters.find(line->B)->second,
										  _parameters.find(line->C)->second), line->color);
				break;
			}
			default:
				throw V::Error("Storage corrupted");
		}
		return true;
	}
	return false;
}
bool GlobalStorage::GetConstraint(IInterface&, uint)
{
	return 0;
}

uint GlobalStorage::_generate_id()
{
	_last_id++;
	while (_storage_of_objects.count(_last_id))
	{
		_last_id++;
	}
	return _last_id;
}

ID GlobalStorage::NewPoint(ldoub x, ldoub y, flag fixed, Color color, ID id)
{
	if (_storage_of_objects.find(id.value()) != _storage_of_objects.end())
	{
		id = _generate_id();
	}

	ldoub* _x = new ldoub; *_x = x;
	ldoub* _y = new ldoub; *_y = y;
	_parameters.insert(paraPair(_x, fixed._0()));
	_parameters.insert(paraPair(_y, fixed._1()));

	Point* point = new Point(_x, _y);
	point->color = color;
	point->id = id;
	_storage_of_objects.insert(objectPair(id.value(), point));

	return id;
}
ID GlobalStorage::NewSegment(uint point1_id, uint point2_id, Color color, ID id)
{
	Point* p1 = dynamic_cast<Point*>(_storage_of_objects.at(point1_id));
	if (p1)
	{
		Point* p2 = dynamic_cast<Point*>(_storage_of_objects.at(point2_id));
		if (p2)
		{
		}
	}
	return 0;
}
ID GlobalStorage::NewLine(ldoub a, ldoub b, ldoub c, flag fixed, Color color, ID id)
{
	if (_storage_of_objects.find(id.value()) != _storage_of_objects.end())
	{
		id = _generate_id();
	}

	ldoub* _a = new ldoub; *_a = a;
	ldoub* _b = new ldoub; *_b = b;
	ldoub* _c = new ldoub; *_c = c;
	_parameters.insert(paraPair(_a, fixed._0()));
	_parameters.insert(paraPair(_b, fixed._1()));
	_parameters.insert(paraPair(_c, fixed._2()));

	Line* line = new Line(_a, _b, _c);
	line->color = color;
	line->id = id;
	_storage_of_objects.insert(objectPair(id.value(), line));

	return id;
}
ID GlobalStorage::NewCircle(uint point_id, ldoub r, flag fixed, Color color, ID id)
{
	ObjectBase* obj = _storage_of_objects.at(point_id);
	if (obj->type() == V::POINT)
	{
		if (_storage_of_objects.find(id.value()) != _storage_of_objects.end())
		{
			id = _generate_id();
		}

		ldoub* _r = new ldoub; *_r = r;
		_parameters.insert(paraPair(_r, fixed._0()));

		Circle* circle = new Circle(dynamic_cast<Point*>(obj), _r);
		circle->color = color;
		circle->id = id;
		_storage_of_objects.insert(objectPair(id.value(), circle));
	}
	return id;
}

uint GlobalStorage::SelectObject(ldoub x, ldoub y)
{
	ldoub min = 4;
	uint min_id = 0;
	for (SofObjects::iterator i = _storage_of_objects.begin(); i != _storage_of_objects.end(); i++)
	{
		if (i->first)
		{
			switch (i->second->type())
			{
				case V::POINT:
				{
					Point* p = dynamic_cast<Point*>(i->second);
					if (length(*p->x, *p->y, x, y) < min)
					{
						min = length(*p->x, *p->y, x, y);
						min_id = p->id.value();
					}
					break;
				}
				case V::SEGMENT:
				{
					Segment* s = dynamic_cast<Segment*>(i->second);
					ldoub A = *s->point2->y - *s->point2->y;
					ldoub B = *s->point1->x - *s->point2->x;
					ldoub C = *s->point1->y * *s->point2->x - *s->point1->x * *s->point2->y;
					if ((abs(A*x + B*y + C) / sqrt(A*A + B*B) < min) &&
						 (pow(length(*s->point1->x, *s->point1->y, x, y), 2) <=
						 ((A*x + B*y + C)*(A*x + B*y + C) / (A*A + B*B) +
						 pow(length(*s->point1->x, *s->point1->y, *s->point2->x, *s->point2->y), 2)))
						 && (pow(length(*s->point2->x, *s->point2->y, x, y), 2) <=
						 ((A*x + B*y + C)*(A*x + B*y + C) / (A*A + B*B) +
						 pow(length(*s->point1->x, *s->point1->y, *s->point2->x, *s->point2->y), 2)))
						 && length(*s->point1->x, *s->point1->y, x, y)>1.67 &&
						 length(*s->point2->x, *s->point2->y, x, y)>1.67)
					{
						min = abs(A*x + B*y + C) / sqrt(A*A + B*B);
						min_id = s->id.value();
					}
					break;
				}
				case V::CIRCLE:
				{
					Circle* c = dynamic_cast<Circle*>(i->second);
					if ((length(*c->point->x, *c->point->y, x, y) < (*c->radius + min)) &&
						 (length(*c->point->x, *c->point->y, x, y) > (*c->radius - min)))
					{
						min = abs(length(*c->point->x, *c->point->y, x, y) - *c->radius);
						min_id = c->id.value();
					}
					break;
				}
			}
		}
	}
	if (SelectObject(min_id))
	{
		return min_id;
	}
	return 0;
}

bool GlobalStorage::SelectObject(uint id)
{
	if (id)
	{
		ObjectBase* object = _storage_of_objects.at(id);
		if (object)
		{
			object->changeSelect();
			if (object->select())
			{
				_selected_objects.insert(objectPair(object->id.value(), object));
			}
			else
			{
				_selected_objects.erase(object->id.value());
			}
			return true;
		}
	}
	return false;
}

void GlobalStorage::SelectObjects(ldoub x1, ldoub y1, ldoub x2, ldoub y2)
{
	ClearSelection();
	uint size = _storage_of_objects.size();
	SofObjects::iterator end = _storage_of_objects.end();
	for (SofObjects::iterator i = _storage_of_objects.begin(); i != end; i++)
	{
		if (i->first == 0) continue;
		switch (i->second->type())
		{
			case V::POINT:
			{
				Point* point = dynamic_cast<Point*>(i->second);
				if (_isInArea(*point->x, *point->y, x1, y1, x2, y2))
				{
					point->changeSelect(true);
					_selected_objects.insert(objectPair(point->id.value(), point));
				}
				break;
			}
			case V::SEGMENT:
			{
				Segment* segment = dynamic_cast<Segment*>(i->second);
				if (_isInArea(*segment->point1->x, *segment->point1->y, x1, y1, x2, y2) &&
					 _isInArea(*segment->point2->x, *segment->point2->y, x1, y1, x2, y2))
				{
					segment->changeSelect(true);
					_selected_objects.insert(objectPair(segment->id.value(), segment));
				}
				break;
			}
			case V::CIRCLE:
			{
				Circle* circle = dynamic_cast<Circle*>(i->second);
				if ((_isInArea(*circle->point->x, *circle->point->y, x1, y1, x2, y2)) &&
					 (*circle->point->x + *circle->radius) >= x1 && (*circle->point->x + *circle->radius) <= x2 &&
					 (*circle->point->y + *circle->radius) >= y1 && (*circle->point->y + *circle->radius) <= y2)
				{
					circle->changeSelect(true);
					_selected_objects.insert(objectPair(circle->id.value(), circle));
				}
				break;
			}
			case V::LINE:
			{
				break;
			}
			default:
				break;
		}
	}
}

bool GlobalStorage::_isInArea(ldoub x, ldoub y, ldoub x1, ldoub y1, ldoub x2, ldoub y2)
{
	if (x2 < x1)
	{
		ldoub temp = x2;
		x2 = x1;
		x1 = temp;
	}
	if (y2 < y1)
	{
		ldoub temp = y2;
		y2 = y1;
		y1 = temp;
	}
	if (x1 < x && x < x2 && y1 < y && y < y2)
	{
		return true;
	}
	return false;
}

void GlobalStorage::ClearSelection()
{
	SofObjects::iterator end = _selected_objects.end();
	for (SofObjects::iterator i = _selected_objects.begin(); i != end; i++)
	{
		i->second->changeSelect(false);
	}
	_selected_objects.clear();
}