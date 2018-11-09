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
	PixelCanvas canvas; // 画布
	bool gameContinue;
	Shape *getRandomShape();
	Shape *curr;
	Shape *next; // 下一个图形
	unsigned long speed; // 自动下降时间间隔ms
	size_type startX;
	size_type startY;
};

