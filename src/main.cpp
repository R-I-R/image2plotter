#include "mainwindow.h"
#include "svgViewer.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
	QApplication a(argc, argv);
	MainWindow w;
	w.showMaximized();
	return a.exec();


	return 0;
}
