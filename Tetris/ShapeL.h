#pragma once
#include "Shape.h"
class ShapeL : public Shape {
public:
	ShapeL(size_type x, size_type y, size_type type = 0);
	vector<string> getString() override;
private:
	size_type type;
};

