#include "ShapeI.h"
#include "PixelCanvas.h"


/*初始化图形，默认为横放*/
ShapeI::ShapeI(size_type x, size_type y) : Shape(x, y), status(true) {
	// 中心点为左数第二个
	points.push_back({ x, y - 1 });
	points.push_back({ x, y });
	points.push_back({ x, y + 1 });
	points.push_back({ x, y + 2 });
}

/*旋转图形*/
void ShapeI::rotate(PixelCanvas &canvas) {
	graph before = points; // 拷贝一份原有的图形
	if (status) {
		Shape::clockwise_rotate();
	} else {
		Shape::anticlockwise_rotate();
	}
	if (!canvas.changeGraph(before, points)) { // 发生碰撞
		points = before; // 还原
		return;
	}
	status = !status;
}

vector<string> ShapeI::getString() {
	vector<string> s;
	s.push_back("■■■■");
	return s;
}