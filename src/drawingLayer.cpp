#include "drawingLayer.hpp"
#include <QDebug>

DrawingLayer::DrawingLayer(const QByteArray &path, int &index, int zPos): enabled(true),zPos(zPos),width(0){
	//int index = 0;
	char tags[4][15] = {"stroke-width:","fill:","id=\"","d=\""};
	int indexs[] = {0,0,0,0};

	while(index < path.size()){
		if(path[index] == '>') break;

		for(int a = 0; a < 4; a++){
			if(path[index] == tags[a][indexs[a]]) indexs[a]++;
			else indexs[a] = 0;
		}

		index++;

		if(indexs[0] == 13){ //found "stroke-width:"
			bool dot = false;
			float ex = 10.0;
			while(path[index] != ';' && path[index] != '"'){
				if(path[index] == '.') dot = true;
				else{
					if(dot){
						width += float(path[index]-48)/ex;
						ex *= 10.0;
					}else{
						width *= 10.0;
						width += float(path[index]-48);
					}
				}
				index++;
			}

			for(int a = 0; a < 4; a++) indexs[a] = 0;

		}else if(indexs[1] == 5){ //found "fill:"
			while(path[index] != ';' && path[index] != '"'){
				color.append(path[index]);
				index++;
			}
			for(int a = 0; a < 4; a++) indexs[a] = 0;

		}else if(indexs[2] == 4){ //found "id=\""
			while(path[index] != '"'){
				Id.append(path[index]);
				index++;
			}

			for(int a = 0; a < 4; a++) indexs[a] = 0;

		}else if(indexs[3] == 3){ //found "d=\""
			while(path[index] != '"'){
				strokes.append(path[index]);
				index++;
			}

			for(int a = 0; a < 4; a++) indexs[a] = 0;
		}


	}

	
}

const QString& DrawingLayer::getId(){ return Id; }
int DrawingLayer::getZpos(){ return zPos; }