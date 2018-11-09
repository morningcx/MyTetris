#pragma once
#include "PixelCanvas.h"

class Shape;
class Tetris {
public:
	using size_type = int;

	Tetris();
	void startGame();
	void endGame();
	void setSpeed(unsigned long s) { speed = s; }
	~Tetris();
private:
	PixelCanvas canvas; // ����
	bool gameContinue;
	Shape *getRandomShape();
	Shape *curr;
	Shape *next; // ��һ��ͼ��
	unsigned long speed; // �Զ��½�ʱ����ms
	size_type startX;
	size_type startY;
};

