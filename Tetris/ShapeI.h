#pragma once
#include "Shape.h"

class ShapeI : public Shape {
public:
	ShapeI(size_type x, size_type y);
	void rotate(PixelCanvas &canvas) override;
	vector<string> getString() override;
private:
	bool status; // 横放为true， 竖放为false
};

