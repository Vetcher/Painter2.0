#pragma once

#include "QtWidgets/qgraphicsview.h"
#include "GlobalStorage.h"
#include "qevent.h"
#include "qgraphicsscene.h"
#include "base.h"
#include "qpoint.h"
#include "qgraphicsitem.h"
#include <vector>

class GraphicsSpace : public QGraphicsView, public IInterface
{
	Q_OBJECT

public:
	explicit GraphicsSpace(QWidget *parent = 0);
	~GraphicsSpace();

// IInterface functions
	virtual void Draw_Point(uint, double, double, flag, Color = V::Default);
	virtual void Draw_Segment(uint, double, double, double, double, flag, Color = V::Default);
	virtual void Draw_Circle(uint, double, double, double, flag, Color = V::Default);
	virtual void Draw_Line(uint, double, double, double, flag, Color = V::Default);
	virtual void Write_Constraint(uint, V::TConstraint);
// ------------------------
	void ClearScene();

	void Connect(GlobalStorage*);

public slots:
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent *event);
signals:
	void clickx(double);
	void clicky(double);
	void somethingChanged();
private:
	QGraphicsScene mainscene;
	V::Tool _current_tool;
	float _zoom;
	double current_scene_width;
	GlobalStorage* _storage;

	// for rect selection
	bool isSelecting;
	QPointF startpos;
	QGraphicsRectItem* selectionRectItem;
	QRectF selectionRect;

	//for grid
	QGraphicsItemGroup* _grid;
	std::vector<QGraphicsItem*> _gridlines;
	void _setupGrid();
	void _test();

	// constants
	const float _zoomscale = 1.3;
	const float _pointradius = 5;
	const float _selectPradius = 2;
	const float _constIndent = 2;
	const float _linewidth = 1.5;
};
