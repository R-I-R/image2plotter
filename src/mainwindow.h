#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cstdio>
#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QGraphicsSvgItem>
#include <QtOpenGL>

#include "svgViewer.hpp"

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

private slots:
	void openSvg();
};

#endif // MAINWINDOW_H
