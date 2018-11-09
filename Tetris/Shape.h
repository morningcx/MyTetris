#pragma once
#include <vector>
#include <string>
#include "PixelCanvas.h"

class PixelCanvas;
using namespace std;
class Shape {
public:
	using size_type = int;
	using graph = vector<pair<size_type, size_type>>; // 图形形状

	Shape(size_type x, size_type y) : center({ x, y }) {}
	virtual void rotate(PixelCanvas &canvas);
	virtual vector<string> getString() = 0; // 图形输出字符串
	void moveLeft(PixelCanvas &canvas);
	void moveRight(PixelCanvas &canvas);
	bool moveDown(PixelCanvas &canvas);
	bool addToCanvas(PixelCanvas &canvas) { return canvas.addGraph(points); }
	virtual ~Shape() = default;
protected:
	graph points; // 图形组成的点
	pair<size_type, size_type> center; // 旋转中心点
	void clockwise_rotate(); // 顺时针
	void anticlockwise_rotate(); // 逆时针
};

