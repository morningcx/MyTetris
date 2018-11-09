#include "ShapeZ.h"
#include "PixelCanvas.h"


ShapeZ::ShapeZ(size_type x, size_type y, size_type type) : Shape(x, y), status(true), type(type) {
	// ���ĵ�Ϊ�ڶ��п�ͷ
	points.push_back({ x, y });
	points.push_back({ x - 1, y });
	points.push_back({ x - 1, type == 0 ? y - 1 : y + 1 });
	points.push_back({ x, type == 0 ? y + 1 : y - 1 });
}

/*��תͼ��*/
void ShapeZ::rotate(PixelCanvas &canvas) {
	graph before = points; // ����һ��ԭ�е�ͼ��
	if (status) {
		Shape::anticlockwise_rotate();
	} else {
		Shape::clockwise_rotate();
	}
	if (!canvas.changeGraph(before, points)) { // ������ײ
		points = before; // ��ԭ
		return;
	}
	status = !status;
}


vector<string> ShapeZ::getString() {
	vector<string> s;
	s.push_back(type == 0 ? "����" : "  ����");
	s.push_back(type == 0 ? "  ����" : "����");
	return s;
}