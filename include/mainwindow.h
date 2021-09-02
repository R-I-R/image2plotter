#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cstdio>
#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QGraphicsSvgItem>
#include <QtOpenGL>

#include "drawingViewer.hpp"
#include "drawingLayer.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	std::vector<DrawingLayer> drawings;
	QSvgRenderer *svgRender;
	QGraphicsScene *svgScene;

private slots:
	void openSvg();
};

#endif // MAINWINDOW_H
