#ifndef SVGVIEWER_HPP
#define SVGVIEWER_HPP

#include <QGraphicsView>
#include <QMouseEvent>
#include <QFile>
#include <QGraphicsSvgItem>
#include <QtOpenGL>
#include <QSvgRenderer>
#include <stack>

QT_BEGIN_NAMESPACE
namespace Ui { class SvgViewer; }
QT_END_NAMESPACE

void appendSubArray(QByteArray& destination, QByteArray& source, size_t begin, size_t end);
QByteArray getSubArray(QByteArray& source, size_t begin, size_t end);

class SvgTreeNode{
public:
	SvgTreeNode(QByteArray elm, int index, int type);
	~SvgTreeNode();
	int type;
	QByteArray elm;
	SvgTreeNode *next, *child;

	enum types{
		svg,
		g,
		path
	};
private:
	bool enabled;
	int index;
};

class SvgTree{
public:
	SvgTree(QByteArray data);
	~SvgTree();
	const QByteArray& getSvg();
private:
	unsigned int Head;
	SvgTreeNode *child;
	QByteArray svgStr;
};

class SvgViewer: public QGraphicsView{
	Q_OBJECT
public:
	explicit SvgViewer(QWidget *parent=nullptr);
	~SvgViewer();
	void wheelEvent(QWheelEvent *event);
	void loadSvg(QFile &file);
private:
	QGraphicsSvgItem svgItem;
	QSvgRenderer svgRender;
	SvgTree *svgTree;
	
};


#endif