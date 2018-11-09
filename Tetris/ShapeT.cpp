#include "ShapeT.h"



ShapeT::ShapeT(size_type x, size_type y) : Shape(x, y) {
	// ���ĵ�Ϊ�ײ��м�
	points.push_back({ x, y });
	points.push_back({ x, y - 1 });
	points.push_back({ x, y + 1 });
	points.push_back({ x - 1, y });
}


vector<string> ShapeT::getString() {
	vector<string> s;
	s.push_back("  ��");
	s.push_back("������");
	return s;
}