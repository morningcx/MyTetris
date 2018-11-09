#include "Shape.h"
#include "PixelCanvas.h"

/*ͼ����ʱ����ת*/
void Shape::rotate(PixelCanvas &canvas) {
	graph before = points; // ����һ��ԭ�е�ͼ��
	anticlockwise_rotate(); // Ĭ������ʱ����ת
	if (!canvas.changeGraph(before, points)) { // ������ײ
		points = before; // ��ԭ
	}
}


/*˳ʱ����ת*/
void Shape::clockwise_rotate() {
	for (auto &point : points) {
		size_type x = point.first - center.first;
		size_type y = center.second - point.second;
		point.first = center.first - y;
		point.second = center.second - x;
	}
}

/*��ʱ����ת*/
void Shape::anticlockwise_rotate() {
	for (auto &point : points) {
		size_type x = point.first - center.first;
		size_type y = center.second - point.second;
		point.first = center.first + y;
		point.second = center.second + x;
	}
}

/*ͼ������*/
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

/*ͼ������*/
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

/*ͼ������*/
bool Shape::moveDown(PixelCanvas &canvas) {
	++center.first; // ����ʧ��Ҳ����Ҫ�������ĵ�
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

