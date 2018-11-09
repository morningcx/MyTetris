#pragma once
#include <vector>
#include <string>

using namespace std;
class PixelCanvas {
public:
	using size_type = int;
	using graph = vector<pair<size_type, size_type>>; // 图形形状

	PixelCanvas(size_type width, size_type height);
	void initCanvas();
	void refresh();
	bool addGraph(const graph &list);
	bool changeGraph(const graph &before, const graph &after); // 改变特定图形的位置
	void removeFullLine(const graph &list); // 清除占满行
	void setNext(vector<string> n) { next = n; }
	size_type getHeight() { return height; }
	size_type getWidth() { return width; }
private:
	size_type score = 0; // 得分
	vector<string> next; // 下一个图形
	size_type width;
	size_type height;
	const char empty = '0';
	const char stuff = '1';
	vector<vector<char>> canvas;

	bool check_range(size_type x, size_type y);
};

