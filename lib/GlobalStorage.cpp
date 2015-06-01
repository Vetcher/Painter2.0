#include "GlobalStorage.h"
#include "objects.h"

GlobalStorage::GlobalStorage()
{
	_storage_of_objects.insert(objectPair(0, 0));
}


GlobalStorage::~GlobalStorage()
{

}

void GlobalStorage::Clear()
{

}

bool GlobalStorage::Upload_All_To(IInterface& Interface)
{
	for (SofObjects::iterator i = _storage_of_objects.begin(); i != _storage_of_objects.end(); i++)
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
	ObjectBase* obj = _storage_of_objects.find(point_id)->second;
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
