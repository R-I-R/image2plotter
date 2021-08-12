#include "svgViewer.hpp"


void appendSubArray(QByteArray& destination, QByteArray& source, size_t begin, size_t end){
	for(int i = begin; i <= end; i++){
		destination.append(source[i]);
	}
}
QByteArray getSubArray(QByteArray& source, size_t begin, size_t end){
	QByteArray tmp;
	appendSubArray(tmp,source,begin,end);
	return tmp;
}

SvgViewer::SvgViewer(QWidget *parent):QGraphicsView(parent),svgTree(NULL){
	//setViewport(new QGLWidget());
	setViewport(new QOpenGLWidget());
	
	QGraphicsScene *s = new QGraphicsScene();
	s->addItem(&svgItem);
	setScene(s);
}

SvgViewer::~SvgViewer(){
	if(svgTree) delete svgTree;
	svgTree = NULL;
}

void SvgViewer::loadSvg(QFile &file){
	if(svgTree) delete svgTree;
	svgTree = new SvgTree(file.readAll());
	svgRender.load(svgTree->getSvg());
	//svgRender.load(file.readAll());
	//svgRender.repaintNeeded();
	/*QFile test("out.svg");
	if(!test.open(QIODevice::WriteOnly)){
		return;
	}
	test.write(svgTree->getSvg());
	test.close();*/
	svgItem.setSharedRenderer(&svgRender);
	/*QGraphicsScene *s = new QGraphicsScene();
	s->addItem(&svgItem);
	setScene(s);*/

	fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
	//show();
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

SvgTree::SvgTree(QByteArray data):child(NULL){
	std::stack<SvgTreeNode*> fathers;
	SvgTreeNode **nextNode = NULL;
	
	bool open = false, quotes = false;
	int tagSpaceIndex = -1, openIndex = 0;
	
	for(int i = 0; i < data.size(); i++){
		if(data[i] == '"'){ //check quotes to prevent fake matchs
			quotes = !quotes;
			continue;
		}
		if(!quotes){
			if(!open && data[i] == '<'){
				open = true;
				openIndex = i;
				tagSpaceIndex = -1;
				
			}else if(open && isspace(data[i]) && tagSpaceIndex == -1){
				tagSpaceIndex = i;

			}else if(open && data[i] == '>'){
				open = false;
				QByteArray tagName(getSubArray(data,openIndex+1,(tagSpaceIndex < openIndex ? i:tagSpaceIndex)-1));

				if("?xml" == tagName){
					appendSubArray(svgStr,data,openIndex,i);
				}else if("svg" == tagName){
					if(child == NULL) child = new SvgTreeNode(getSubArray(data,openIndex,i),svgStr.size(),SvgTreeNode::svg);
					//else throw error
					fathers.push(child);
					nextNode = &fathers.top()->child;
					appendSubArray(svgStr,data,openIndex,i);
				}else if("g" == tagName){
					(*nextNode) = new SvgTreeNode(getSubArray(data,openIndex,i),svgStr.size(),SvgTreeNode::g);
					fathers.push((*nextNode));
					nextNode = &fathers.top()->child;
					appendSubArray(svgStr,data,openIndex,i);
				}else if("path" == tagName){
					(*nextNode) = new SvgTreeNode(getSubArray(data,openIndex,i),svgStr.size(),SvgTreeNode::path);
					nextNode = &(*nextNode)->next;
					appendSubArray(svgStr,data,openIndex,i);
				}else if("/g" == tagName){
					nextNode = &fathers.top()->next;
					fathers.pop();
					appendSubArray(svgStr,data,openIndex,i);
				}else if("/svg" == tagName){
					nextNode = &fathers.top()->next;
					fathers.pop();
					appendSubArray(svgStr,data,openIndex,i);
				}

			}
		}
	}
}

const QByteArray& SvgTree::getSvg(){
	return svgStr;
}

SvgTree::~SvgTree(){
	if(child) delete child;
	child = NULL;
}

SvgTreeNode::SvgTreeNode(QByteArray elm, int index,int type):type(type),elm(elm),next(NULL),child(NULL),enabled(true),index(index){}
SvgTreeNode::~SvgTreeNode(){
	if(child) delete child;
	if(next) delete next;
}