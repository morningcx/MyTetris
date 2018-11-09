#include "ShapeZ.h"
#include "PixelCanvas.h"


ShapeZ::ShapeZ(size_type x, size_type y, size_type type) : Shape(x, y), status(true), type(type) {
	// 中心点为第二行靠头
	points.push_back({ x, y });
	points.push_back({ x - 1, y });
	points.push_back({ x - 1, type == 0 ? y - 1 : y + 1 });
	points.push_back({ x, type == 0 ? y + 1 : y - 1 });
}

/*旋转图形*/
void ShapeZ::rotate(PixelCanvas &canvas) {
	graph before = points; // 拷贝一份原有的图形
	if (status) {
		Shape::anticlockwise_rotate();
	} else {
		Shape::clockwise_rotate();
	}
	if (!canvas.changeGraph(before, points)) { // 发生碰撞
		points = before; // 还原
		return;
	}
	status = !status;
}


vector<string> ShapeZ::getString() {
	vector<string> s;
	s.push_back(type == 0 ? "■■" : "  ■■");
	s.push_back(type == 0 ? "  ■■" : "■■");
	return s;
}