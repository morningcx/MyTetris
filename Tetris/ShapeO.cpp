#include "ShapeO.h"



ShapeO::ShapeO(size_type x, size_type y) : Shape(x, y){
	// 中心点为左下角
	points.push_back({ x, y });
	points.push_back({ x, y + 1 });
	points.push_back({ x - 1, y });
	points.push_back({ x - 1, y + 1 });
}

vector<string> ShapeO::getString() {
	vector<string> s;
	s.push_back("■■");
	s.push_back("■■");
	return s;
}