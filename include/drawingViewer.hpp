#ifndef SVGVIEWER_HPP
#define SVGVIEWER_HPP

#include <QGraphicsView>
#include <QMouseEvent>
#include <QFile>
#include <QGraphicsSvgItem>
#include <QOpenGLWidget>
#include <QSvgRenderer>
#include <stack>

QT_BEGIN_NAMESPACE
namespace Ui { class SvgViewer; }
QT_END_NAMESPACE


class SvgViewer: public QGraphicsView{
	Q_OBJECT
public:
	explicit SvgViewer(QWidget *parent=nullptr);
	void wheelEvent(QWheelEvent *event);
};



#endif
