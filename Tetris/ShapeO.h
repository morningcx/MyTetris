#pragma once
#include "Shape.h"

class ShapeO : public Shape{
public:
	ShapeO(size_type x, size_type y);
	void rotate(PixelCanvas &canvas) override {} // �����β���Ҫ��ת����
	vector<string> getString() override;
};

