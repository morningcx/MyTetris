#pragma once
#include "Shape.h"

class ShapeO : public Shape{
public:
	ShapeO(size_type x, size_type y);
	void rotate(PixelCanvas &canvas) override {} // 正方形不需要旋转处理
	vector<string> getString() override;
};

