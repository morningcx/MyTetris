#pragma once
#include <vector>
#include <string>
#include "PixelCanvas.h"

class PixelCanvas;
using namespace std;
class Shape {
public:
	using size_type = int;
	using graph = vector<pair<size_type, size_type>>; // ͼ����״

	Shape(size_type x, size_type y) : center({ x, y }) {}
	virtual void rotate(PixelCanvas &canvas);
	virtual vector<string> getString() = 0; // ͼ������ַ���
	void moveLeft(PixelCanvas &canvas);
	void moveRight(PixelCanvas &canvas);
	bool moveDown(PixelCanvas &canvas);
	bool addToCanvas(PixelCanvas &canvas) { return canvas.addGraph(points); }
	virtual ~Shape() = default;
protected:
	graph points; // ͼ����ɵĵ�
	pair<size_type, size_type> center; // ��ת���ĵ�
	void clockwise_rotate(); // ˳ʱ��
	void anticlockwise_rotate(); // ��ʱ��
};

