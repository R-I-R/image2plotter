#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow){
	ui->setupUi(this);
	
	connect(ui->openFileBtn, &QPushButton::clicked, this, &MainWindow::openSvg);
	
}

MainWindow::~MainWindow(){
	delete ui;
}

void MainWindow::openSvg(){
	printf("abierto\n");
	QString filename = QFileDialog::getOpenFileName(this, tr("Open svg"), "./", tr("Svg files (*.svg)"));
	printf("fin dialogo:%s\n",filename.toLocal8Bit().data());

	if(filename.isEmpty()) return;
	
	QFile file(filename);

	if(!file.open(QIODevice::ReadOnly)){
		QMessageBox::information(this,tr("Unable to open file"),file.errorString());
		return;
	}

	ui->graphicsView->loadSvg(file);
	
	file.close();

}