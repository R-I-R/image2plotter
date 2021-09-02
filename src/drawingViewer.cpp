#include <drawingViewer.hpp>

SvgViewer::SvgViewer(QWidget *parent):QGraphicsView(parent){
	//setViewport(new QGLWidget());
	setViewport(new QOpenGLWidget());

}

void SvgViewer::wheelEvent(QWheelEvent* event){

	const ViewportAnchor anchor = transformationAnchor();
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	qreal factor;
	if(event->angleDelta().y() > 0) factor = 1.1;
	else factor = 0.9;

	scale(factor,factor);
	setTransformationAnchor(anchor);

}

