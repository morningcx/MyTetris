#include "ShapeL.h"



ShapeL::ShapeL(size_type x, size_type y, size_type type) : Shape(x, y), type(type) {
	// 中心点为中间那块
	points.push_back({ x - 1, type == 0 ? y - 1 : y + 1 });
	points.push_back({ x, y - 1 });
	points.push_back({ x, y });
	points.push_back({ x, y + 1 });
}

vector<string> ShapeL::getString() {
	vector<string> s;
	s.push_back(type == 0 ? "■" : "    ■");
	s.push_back("■■■");
	return s;
}