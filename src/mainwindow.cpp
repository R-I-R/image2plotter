#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow),svgRender(NULL){
	ui->setupUi(this);
	
	connect(ui->openFileBtn, &QPushButton::clicked, this, &MainWindow::openSvg);
	
}

MainWindow::~MainWindow(){
	delete ui;
}

void MainWindow::openSvg(){
	QString filename = QFileDialog::getOpenFileName(this, tr("Open svg"), "./", tr("Svg files (*.svg)"));

	if(filename.isEmpty()) return;
	
	QFile file(filename);

	if(!file.open(QIODevice::ReadOnly)){
		QMessageBox::information(this,tr("Unable to open file"),file.errorString());
		return;
	}

	if(svgRender){
		delete svgRender;
		delete svgScene;
		svgRender = NULL;
		svgScene = NULL;
		drawings.clear();
	}

	QByteArray svgStr(file.readAll());
	svgRender = new QSvgRenderer(svgStr);
	svgScene = new QGraphicsScene();

	QGraphicsRectItem *background = new QGraphicsRectItem(svgRender->viewBoxF());
	background->setBrush(QBrush(Qt::white));
	svgScene->addItem(background);
	ui->svgView->setSceneRect(background->boundingRect());

	int index = 0, pathI = 0, pathsFound = 0;
	char pathStr[] = "<path";

	while(index < svgStr.size()){
		if(svgStr[index] == pathStr[pathI]) pathI++;
		else pathI = 0;

		if(pathI == 5){
			drawings.emplace_back(svgStr,index,pathsFound++);

			QGraphicsSvgItem *svgItem = new QGraphicsSvgItem();
			svgItem->setSharedRenderer(svgRender);

			QString svgId(drawings.back().getId());
			QRectF rect = svgRender->transformForElement(svgId).mapRect(svgRender->boundsOnElement(svgId));

			svgItem->setElementId(svgId);
			svgItem->setCacheMode(QGraphicsItem::NoCache);
			svgItem->setZValue(drawings.back().getZpos());
			svgItem->setPos(rect.x(),rect.y());

			svgScene->addItem(svgItem);

			pathI = 0;
		}

		index++;
	}

	ui->svgView->setScene(svgScene);
	ui->svgView->fitInView(svgScene->sceneRect(), Qt::KeepAspectRatio);
	ui->svgView->show();
	
	file.close();

}