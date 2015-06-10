#include "GraphicsSpace.h"
#include "qbrush.h"
#include "qrgb.h"
#include "qcolor.h"
#include "qpen.h"

GraphicsSpace::GraphicsSpace(QWidget* parent) : QGraphicsView(parent)
{
	//_storage = 0;
	setScene(&mainscene);
	_zoom = 1.0;
	current_scene_width = V::scenewidth;
	_current_tool = V::toolDrawPoint;
	setSceneRect(-current_scene_width, -current_scene_width, current_scene_width * 2, current_scene_width * 2);
	isSelecting = false;
	Color c = V::Selected;
	selectionRectItem = new QGraphicsRectItem;
	selectionRectItem->setVisible(false);
	selectionRectItem->setPen(QPen(QBrush(QColor(c.red(), c.green(), c.blue(), 70)), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
	selectionRectItem->setBrush(QBrush(QColor(c.red(), c.green(), c.blue(), 20)));
	mainscene.addItem(selectionRectItem);
	_setupGrid();
	_test();
}
GraphicsSpace::~GraphicsSpace()
{
	delete selectionRectItem;
	for (std::vector<QGraphicsItem*>::iterator i = _gridlines.begin(); i != _gridlines.end(); i++)
	{
		delete *i;
	}
	delete _grid;
}

void GraphicsSpace::Connect(GlobalStorage* storage)
{
	_storage = storage;
}


void GraphicsSpace::mouseMoveEvent(QMouseEvent* event)
{
	QPointF pt = mapToScene(event->pos());
	clickx(pt.x() / _zoom);
	clicky(-pt.y() / _zoom);
	if (isSelecting)
	{
		selectionRect.setBottomRight(pt);
		selectionRectItem->setRect(selectionRect.normalized());
	}
}

void GraphicsSpace::mousePressEvent(QMouseEvent* event)
{
	QPointF pt = mapToScene(event->pos());
	switch (_current_tool)
	{
		case V::toolSelection:
		{
			if (event->button() == Qt::LeftButton)
			{
				isSelecting = true;
				startpos = pt;
				selectionRect.setTopLeft(pt);
				selectionRect.setBottomRight(pt);
				selectionRectItem->setRect(selectionRect);
				selectionRectItem->setVisible(true);
			}
			break;
		}
		case V::toolDrawPoint:
		{
			if (event->button() == Qt::LeftButton)
			{
				startpos = pt;
			}
			break;
		}
	}
}

void GraphicsSpace::_test()
{
	//Draw_Point(1, 10, 0, flag(false));
	//Draw_Point(1, 0, 10, flag(true));
	//Draw_Segment(1, 100, 100, -100, -100, flag(false));
	//Draw_Segment(1, 100, -100, -100, 100, flag(true));
	//Draw_Circle(1, -100, 0, 100, flag(false));
	//Draw_Circle(1, 0, 100, 100, flag(true));
	//Draw_Line(1, 1, 1, 100, flag(false));
	//Draw_Line(1, 1, 1, -100, flag(false));
	//Draw_Line(1, 1, -1, 0, flag(false));
	//Draw_Line(1, 1.0 / 2, 1, 30, flag(false));
	//Draw_Line(1, 1, 1.0 / 2, 40, flag(false));
	//Draw_Line(1, -2, 1, 50, flag(false));
	//Draw_Line(1, 1, -2, 60, flag(false));
	//Draw_Line(1, 0, 1, 70, flag(false));
	//Draw_Line(1, 2, 0, 80, flag(false));
}

void GraphicsSpace::mouseReleaseEvent(QMouseEvent* event)
{
	isSelecting = false;
	selectionRectItem->setVisible(false);
	QPointF pt = mapToScene(event->pos());
	if (pt == startpos)
	{
		switch (_current_tool)
		{
			case V::toolSelection:
			{
				_storage->SelectObject(pt.x() / _zoom, -pt.y() / _zoom);
				somethingChanged();
				break;
			}
			case V::toolDrawPoint:
			{
				_storage->NewPoint(pt.x() / _zoom, -pt.y() / _zoom, flag(false));
				somethingChanged();
				break;
			}
		}
	}
	else
	{
		switch (_current_tool)
		{
			case V::toolSelection:
			{
				_storage->SelectObjects(pt.x() / _zoom, -pt.y() / _zoom, startpos.x() / _zoom, -startpos.y() / _zoom);
				somethingChanged();
				break;
			}
		}
	}
}

void GraphicsSpace::wheelEvent(QWheelEvent* event)
{
	if (event->delta() > 0)
	{
		if (_zoom > 100) return;
		_zoom *= _zoomscale;
		current_scene_width *= _zoomscale;
	}
	else
	{
		if (_zoom < 0.2) return;
		_zoom /= _zoomscale;
		current_scene_width /= _zoomscale;
	}
	setSceneRect(-current_scene_width, -current_scene_width,
					 current_scene_width * 2, current_scene_width * 2);

	for (std::vector<QGraphicsItem*>::iterator i = _gridlines.begin(); i != _gridlines.end(); i++)
	{
		delete *i;
	}
	delete _grid;
	_gridlines.clear();

	_setupGrid();
	somethingChanged();
}

void GraphicsSpace::ClearScene()
{
	mainscene.removeItem(selectionRectItem);
	mainscene.removeItem(_grid);
	mainscene.clear();
	mainscene.addItem(selectionRectItem);
	mainscene.addItem(_grid);
}

void GraphicsSpace::_setupGrid()
{
	const double r = 0.7;
	QPen pen(Qt::DashLine);
	pen.setWidthF(r);
	QPen smallpen(Qt::DotLine);
	smallpen.setWidthF(r - 0.2);
	{
		_grid = new QGraphicsItemGroup;
		QGraphicsLineItem* line1;
		for (double i = -current_scene_width; i <= current_scene_width; i += 100 * _zoom)
		{
			line1 = new QGraphicsLineItem(i, -current_scene_width, i, current_scene_width);
			line1->setPen(pen);
			_gridlines.push_back(line1);
			_grid->addToGroup(line1);
			line1 = new QGraphicsLineItem(-current_scene_width, i, current_scene_width, i);
			line1->setPen(pen);
			_gridlines.push_back(line1);
			_grid->addToGroup(line1);
			if (i >= current_scene_width) break;
			for (double j = i + 10 * _zoom; j < i + 100 * _zoom; j += 10 * _zoom)
			{
				line1 = new QGraphicsLineItem(j, -current_scene_width, j, current_scene_width);
				line1->setPen(smallpen);
				_gridlines.push_back(line1);
				_grid->addToGroup(line1);
				line1 = new QGraphicsLineItem(-current_scene_width, j, current_scene_width, j);
				line1->setPen(smallpen);
				_gridlines.push_back(line1);
				_grid->addToGroup(line1);
			}
		}
	}
	mainscene.addItem(_grid);
}

void GraphicsSpace::Draw_Point(uint id, double x, double y, flag f, Color c)
{
	if (!(std::isinf(x) || std::isinf(y)))
	{
		QPen pen(QBrush(QColor(QRgb(f._0() ? V::Selected : c.color()))), _linewidth, Qt::SolidLine, Qt::RoundCap);
		// pen = f._0() ? QPen(QColor(QRgb(V::Selected))) : QPen(QColor(c.red(), c.green(), c.blue()));
		if (f._0()) pen.setStyle(Qt::DotLine);
		QBrush brush;
		brush = f._0() ? QBrush(QColor(QRgb(V::Selected))) : QBrush(QColor(c.red(), c.green(), c.blue()));
		mainscene.addEllipse(x * _zoom - _pointradius, -y * _zoom - _pointradius,
									_pointradius * 2, _pointradius * 2, pen, brush);
		if (f._0())
		{
			mainscene.addEllipse(x * _zoom - _pointradius - _selectPradius - _constIndent,
										-y * _zoom - _pointradius - _selectPradius - _constIndent,
										_selectPradius * 2, _selectPradius * 2, pen, brush);
			mainscene.addEllipse(x * _zoom + _pointradius - _selectPradius + _constIndent,
										-y * _zoom - _pointradius - _selectPradius - _constIndent,
										_selectPradius * 2, _selectPradius * 2, pen, brush);
			mainscene.addEllipse(x * _zoom + _pointradius - _selectPradius + _constIndent,
										-y * _zoom + _pointradius - _selectPradius + _constIndent,
										_selectPradius * 2, _selectPradius * 2, pen, brush);
			mainscene.addEllipse(x * _zoom - _pointradius - _selectPradius - _constIndent,
										-y * _zoom + _pointradius - _selectPradius + _constIndent,
										_selectPradius * 2, _selectPradius * 2, pen, brush);

		}
	}
}
void GraphicsSpace::Draw_Segment(uint id, double x1, double y1, double x2, double y2, flag f, Color c)
{
	if (!(std::isinf(x1) || std::isinf(y1) || std::isinf(x2) || std::isinf(y2)))
	{
		QPen pen(QBrush(QColor(QRgb(f._0() ? V::Selected : c.color()))), _linewidth, Qt::SolidLine, Qt::RoundCap);
		// pen = f._0() ? QPen(QColor(QRgb(V::Selected))) : QPen(QColor(c.red(), c.green(), c.blue()));
		if (f._0()) pen.setStyle(Qt::DashLine);
		mainscene.addLine(x1 * _zoom, -y1 * _zoom,
								x2 * _zoom, -y2 * _zoom,
								pen);
		/*if (f._0())
		{
			QBrush brush;
			brush = QBrush(QColor(QRgb(V::Selected)));

			mainscene.addEllipse(x * _zoom - _pointradius - _selectPradius - _constIndent,
										-y * _zoom - _pointradius - _selectPradius - _constIndent,
										_selectPradius * 2, _selectPradius * 2, pen, brush);
			mainscene.addEllipse(x * _zoom + _pointradius - _selectPradius + _constIndent,
										-y * _zoom - _pointradius - _selectPradius - _constIndent,
										_selectPradius * 2, _selectPradius * 2, pen, brush);
			mainscene.addEllipse(x * _zoom + _pointradius - _selectPradius + _constIndent,
										-y * _zoom + _pointradius - _selectPradius + _constIndent,
										_selectPradius * 2, _selectPradius * 2, pen, brush);
			mainscene.addEllipse(x * _zoom - _pointradius - _selectPradius - _constIndent,
										-y * _zoom + _pointradius - _selectPradius + _constIndent,
										_selectPradius * 2, _selectPradius * 2, pen, brush);
		}*/
	}
}
void GraphicsSpace::Draw_Circle(uint id, double x, double y, double r, flag f, Color c)
{
	if (!(std::isinf(x) || std::isinf(y) || std::isinf(r)))
	{
		QPen pen(QBrush(QColor(QRgb(f._0() ? V::Selected : c.color()))), _linewidth, Qt::SolidLine, Qt::RoundCap);
		// pen = f._0() ? QPen(QColor(QRgb(V::Selected))) : QPen(QColor(c.red(), c.green(), c.blue()));
		if (f._0()) pen.setStyle(Qt::DashLine);
		mainscene.addEllipse((x - r) * _zoom, (-y - r) * _zoom,
									r * _zoom * 2, r * _zoom * 2, pen);
		if (f._0())
		{
			QBrush brush;
			brush = QBrush(QColor(QRgb(V::Selected)));

			mainscene.addEllipse(x * _zoom - r * _zoom - _selectPradius - _constIndent,
										-y * _zoom - r * _zoom - _selectPradius - _constIndent,
										_selectPradius * 2, _selectPradius * 2, pen, brush);
			mainscene.addEllipse(x * _zoom + r * _zoom - _selectPradius + _constIndent,
										-y * _zoom - r * _zoom - _selectPradius - _constIndent,
										_selectPradius * 2, _selectPradius * 2, pen, brush);
			mainscene.addEllipse(x * _zoom + r * _zoom - _selectPradius + _constIndent,
										-y * _zoom + r * _zoom - _selectPradius + _constIndent,
										_selectPradius * 2, _selectPradius * 2, pen, brush);
			mainscene.addEllipse(x * _zoom - r * _zoom - _selectPradius - _constIndent,
										-y * _zoom + r * _zoom - _selectPradius + _constIndent,
										_selectPradius * 2, _selectPradius * 2, pen, brush);
		}
	}
}
void GraphicsSpace::Draw_Line(uint id, double A, double B, double C, flag f, Color c)
{
	if (!(std::isinf(A) || std::isinf(B) || std::isinf(C)))
	{
		QPen pen(QBrush(QColor(QRgb(f._0() ? V::Selected : c.color()))), _linewidth, Qt::SolidLine, Qt::RoundCap);
		// pen = f._0() ? QPen(QColor(QRgb(V::Selected))) : QPen(QColor(c.red(), c.green(), c.blue()));
		if (f._0()) pen.setStyle(Qt::DashLine);

		if (A == 0 && B == 0) throw V::Error("Line corrupted");
		else if (A == 0)
		{
			mainscene.addLine(current_scene_width, -C / B,
									-current_scene_width, -C / B,
									pen);
		}
		else if (B == 0)
		{
			mainscene.addLine(-C / A, current_scene_width,
									-C / A, -current_scene_width,
									pen);
		}
		else
		{
			if (A / B <= 1 && A / B >= -1)
			{
				double Y = -A / B *V::scenewidth - C / B;
				double X;
				if (Y >= -V::scenewidth && Y <= V::scenewidth)
				{
					mainscene.addLine(current_scene_width, Y * _zoom,
											-current_scene_width, -Y * _zoom,
											pen);
				}
				else if (Y > V::scenewidth)
				{
					X = -B / A*V::scenewidth - C / A;
					mainscene.addLine(X * _zoom, current_scene_width,
											-X * _zoom, -current_scene_width,
											pen);
				}
				else if (Y < -V::scenewidth)
				{
					X = B / A*V::scenewidth - C / A;
					mainscene.addLine(-X * _zoom, current_scene_width,
											X * _zoom, -current_scene_width,
											pen);
				}
			}
			else
			{
				double X = -B / A*V::scenewidth - C / A;
				double Y;
				if (X >= -V::scenewidth && X <= V::scenewidth)
				{
					mainscene.addLine(X * _zoom, current_scene_width,
											-X * _zoom, -current_scene_width,
											pen);
				}
				else if (X > V::scenewidth)
				{
					Y = -B / A*V::scenewidth - C / A;
					mainscene.addLine(current_scene_width, Y * _zoom,
											-current_scene_width, -Y * _zoom,
											pen);
				}
				else if (X < -V::scenewidth)
				{
					Y = B / A*V::scenewidth - C / A;
					mainscene.addLine(current_scene_width, Y * _zoom,
											-current_scene_width, -Y * _zoom,
											pen);
				}
			}
		}

		/*mainscene.addLine(x1 * _zoom, -y1 * _zoom,
								x2 * _zoom, -y2 * _zoom,
								pen);*/
		/*if (f._0())
		{
			QBrush brush;
			brush = QBrush(QColor(QRgb(V::Selected)));
		}*/
	}
}

void GraphicsSpace::Write_Constraint(uint, V::TConstraint)
{

}