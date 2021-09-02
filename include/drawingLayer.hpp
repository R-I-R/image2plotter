#ifndef DRAWINGLAYER_HPP
#define DRAWINGLAYER_HPP

#include <QByteArray>
#include <QString>



class DrawingLayer{
	public:
		DrawingLayer(const QByteArray &path, int &index, int zPos=0);
		const QString& getId();
		int getZpos();

	private:
		bool enabled;
		QString Id, strokes, color;
		int zPos;
		float width;
		
};


#endif