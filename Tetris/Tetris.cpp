#include <conio.h>
#include <memory>
#include <Windows.h>
#include <time.h>
#include "Tetris.h"
#include "ShapeGroup.h"

Tetris::Tetris() : gameContinue(true), canvas(PixelCanvas(13, 20)), speed(1000) {
	startX = 2;
	if (canvas.getWidth() % 2) {
		startY = (canvas.getWidth() + 1) / 2;
	} else {
		startY = canvas.getWidth() / 2;
	}
	curr = getRandomShape();
	next = getRandomShape();
	canvas.setNext(next->getString());
	curr->addToCanvas(canvas);
}


/*开始游戏*/
void Tetris::startGame() {
	long remind = speed; // 不能用unsigned
	DWORD t_start, t_end;
	while (gameContinue) {
		int key = 0; // 记录按下键值
		t_start = GetTickCount(); // 记录处理开始时间
		if (_kbhit()) {
			switch (key = _getch()) {
			case 72: // 上
				curr->rotate(canvas);
				break;
			case 75: // 左
				curr->moveLeft(canvas);
				break;
			case 77: // 右
				curr->moveRight(canvas);
				break;
			case 27: // esc
				gameContinue = false;
				break;
			default:
				break;
			}
		}
		t_end = GetTickCount(); // 记录处理结束时间
		remind -= t_end - t_start; // 计算下降剩余时间
		if (key == 80 || remind < 0) { // 按下向下键或者自动下降时间已到
			if (!curr->moveDown(canvas)) { // 检测是否发生碰撞
				delete curr;
				curr = next;
				next = getRandomShape();
				canvas.setNext(next->getString());
				gameContinue = curr->addToCanvas(canvas);
				// 每出现一个方块图形，下降延迟-10ms
				// 后期速度快（刷新打印字符太慢）可能会出现按键延迟的现象
				speed -= 10; 
			}
			remind = speed;
		}
	}
	if (!gameContinue) {
		endGame();
	}
}

/*结束游戏*/
void Tetris::endGame() {
	printf("游戏结束！按ESC键退出程序...\n");
	while (_getch() != 27);
}

/*随机获取一个图形*/
Shape *Tetris::getRandomShape() {
	srand((unsigned)time(NULL));
	Shape *s;
	switch (rand() % 7) {
	case 0:
		s = new ShapeI(startX - 1, startY);
		break;
	case 1:
		s = new ShapeL(startX, startY, 0);
		break;
	case 2:
		s = new ShapeL(startX, startY, 1);
		break;
	case 3:
		s = new ShapeZ(startX, startY, 0);
		break;
	case 4:
		s = new ShapeZ(startX, startY, 1);
		break;
	case 5:
		s = new ShapeT(startX, startY);
		break;
	case 6:
		s = new ShapeO(startX, startY);
		break;
	default:
		s = new ShapeO(startX, startY);
		break;
	}
	return s;
}

Tetris::~Tetris() {
	if (curr) {
		delete curr;
	}
	if (next) {
		delete next;
	}
}