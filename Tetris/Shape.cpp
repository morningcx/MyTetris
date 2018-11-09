#include "Shape.h"
#include "PixelCanvas.h"

/*图形逆时针旋转*/
void Shape::rotate(PixelCanvas &canvas) {
	graph before = points; // 拷贝一份原有的图形
	anticlockwise_rotate(); // 默认是逆时针旋转
	if (!canvas.changeGraph(before, points)) { // 发生碰撞
		points = before; // 还原
	}
}


/*顺时针旋转*/
void Shape::clockwise_rotate() {
	for (auto &point : points) {
		size_type x = point.first - center.first;
		size_type y = center.second - point.second;
		point.first = center.first - y;
		point.second = center.second - x;
	}
}

/*逆时针旋转*/
void Shape::anticlockwise_rotate() {
	for (auto &point : points) {
		size_type x = point.first - center.first;
		size_type y = center.second - point.second;
		point.first = center.first + y;
		point.second = center.second + x;
	}
}

/*图形左移*/
void Shape::moveLeft(PixelCanvas &canvas) {
	graph before = points;
	for (auto &point : points) {
		point.second -= 1;
	}
	if (!canvas.changeGraph(before, points)) {
		points = before;
		return;
	}
	--center.second;
}

/*图形右移*/
void Shape::moveRight(PixelCanvas &canvas) {
	graph before = points;
	for (auto &point : points) {
		point.second += 1;
	}
	if (!canvas.changeGraph(before, points)) {
		points = before;
		return;
	}
	++center.second;
}

/*图形下移*/
bool Shape::moveDown(PixelCanvas &canvas) {
	++center.first; // 下移失败也不需要重置中心点
	graph before = points;
	for (auto &point : points) {
		point.first += 1;
	}
	if (!canvas.changeGraph(before, points)) {
		points = before;
		canvas.removeFullLine(points);
		return false;
	}
	return true;
}

