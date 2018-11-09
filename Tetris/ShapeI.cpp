#include "ShapeI.h"
#include "PixelCanvas.h"


/*��ʼ��ͼ�Σ�Ĭ��Ϊ���*/
ShapeI::ShapeI(size_type x, size_type y) : Shape(x, y), status(true) {
	// ���ĵ�Ϊ�����ڶ���
	points.push_back({ x, y - 1 });
	points.push_back({ x, y });
	points.push_back({ x, y + 1 });
	points.push_back({ x, y + 2 });
}

/*��תͼ��*/
void ShapeI::rotate(PixelCanvas &canvas) {
	graph before = points; // ����һ��ԭ�е�ͼ��
	if (status) {
		Shape::clockwise_rotate();
	} else {
		Shape::anticlockwise_rotate();
	}
	if (!canvas.changeGraph(before, points)) { // ������ײ
		points = before; // ��ԭ
		return;
	}
	status = !status;
}

vector<string> ShapeI::getString() {
	vector<string> s;
	s.push_back("��������");
	return s;
}