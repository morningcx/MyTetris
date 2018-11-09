#pragma once
#include "Shape.h"
class ShapeZ : public Shape {
public:
	ShapeZ(size_type x, size_type y, size_type type = 0);
	void rotate(PixelCanvas &canvas) override;
	vector<string> getString() override;
private:
	size_type type;
	bool status; // 横放为true， 竖放为false
};

