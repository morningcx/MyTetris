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


/*��ʼ��Ϸ*/
void Tetris::startGame() {
	long remind = speed; // ������unsigned
	DWORD t_start, t_end;
	while (gameContinue) {
		int key = 0; // ��¼���¼�ֵ
		t_start = GetTickCount(); // ��¼����ʼʱ��
		if (_kbhit()) {
			switch (key = _getch()) {
			case 72: // ��
				curr->rotate(canvas);
				break;
			case 75: // ��
				curr->moveLeft(canvas);
				break;
			case 77: // ��
				curr->moveRight(canvas);
				break;
			case 27: // esc
				gameContinue = false;
				break;
			default:
				break;
			}
		}
		t_end = GetTickCount(); // ��¼�������ʱ��
		remind -= t_end - t_start; // �����½�ʣ��ʱ��
		if (key == 80 || remind < 0) { // �������¼������Զ��½�ʱ���ѵ�
			if (!curr->moveDown(canvas)) { // ����Ƿ�����ײ
				delete curr;
				curr = next;
				next = getRandomShape();
				canvas.setNext(next->getString());
				gameContinue = curr->addToCanvas(canvas);
				// ÿ����һ������ͼ�Σ��½��ӳ�-10ms
				// �����ٶȿ죨ˢ�´�ӡ�ַ�̫�������ܻ���ְ����ӳٵ�����
				speed -= 10; 
			}
			remind = speed;
		}
	}
	if (!gameContinue) {
		endGame();
	}
}

/*������Ϸ*/
void Tetris::endGame() {
	printf("��Ϸ��������ESC���˳�����...\n");
	while (_getch() != 27);
}

/*�����ȡһ��ͼ��*/
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