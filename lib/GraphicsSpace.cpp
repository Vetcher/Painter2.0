#include "GraphicsSpace.h"

GraphicsSpace::GraphicsSpace(QWidget* parent) : QGraphicsView(parent)
{
	setScene(&mainscene);
	_current_tool = V::toolSelection;
	setSceneRect(-V::scenewidth, -V::scenewidth, V::scenewidth * 2, V::scenewidth * 2);
}
GraphicsSpace::~GraphicsSpace()
{
	
}

void GraphicsSpace::mouseMoveEvent(QMouseEvent* event)
{
	QPointF pt = mapToScene(event->pos());
	clickx(pt.x());
	clicky(-pt.y());
}

void GraphicsSpace::mousePressEvent()
{
	switch (_current_tool)
	{
		case V::toolSelection:
		{
			break;
		}
		case V::toolDrawPoint:
		{
			break;
		}
	}
}

void GraphicsSpace::Draw_Point(uint, ldoub, ldoub, flag, Color)
{

}
void GraphicsSpace::Draw_Segment(uint, ldoub, ldoub, ldoub, ldoub, flag, Color)
{

}
void GraphicsSpace::Draw_Circle(uint, ldoub, ldoub, ldoub, flag, Color)
{

}
void GraphicsSpace::Draw_Line(uint, ldoub, ldoub, ldoub, flag, Color)
{

}

void GraphicsSpace::Write_Constraint(uint, V::TConstraint)
{

}