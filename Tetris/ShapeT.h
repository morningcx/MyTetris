#pragma once
#include "Shape.h"

class ShapeT : public Shape{
public:
	ShapeT(size_type x, size_type y);
	vector<string> getString() override;
};

