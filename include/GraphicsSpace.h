#pragma once

#include "QtWidgets/qgraphicsview.h"
#include "qevent.h"
#include "qgraphicsscene.h"
#include "qpainter.h"
#include "base.h"

class GraphicsSpace : public QGraphicsView, public IInterface
{
	Q_OBJECT
public:
	explicit GraphicsSpace(QWidget *parent = 0);
	~GraphicsSpace();

// IInterface functions
	virtual void Draw_Point(uint, ldoub, ldoub, flag, Color);
	virtual void Draw_Segment(uint, ldoub, ldoub, ldoub, ldoub, flag, Color);
	virtual void Draw_Circle(uint, ldoub, ldoub, ldoub, flag, Color);
	virtual void Draw_Line(uint, ldoub, ldoub, ldoub, flag, Color);
	virtual void Write_Constraint(uint, V::TConstraint);
// ------------------------

public slots:
	void mousePressEvent();
	void mouseMoveEvent(QMouseEvent* event);
signals:
	void clickx(double);
	void clicky(double);
private:
	QGraphicsScene mainscene;
	V::Tool _current_tool;
};
