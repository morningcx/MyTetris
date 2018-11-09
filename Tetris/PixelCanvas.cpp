#include "PixelCanvas.h"
#include <iostream>
#include <string>
#include <stdio.h>

PixelCanvas::PixelCanvas(size_type width, size_type height) : width(width), height(height) {
	vector<char> td(width + 2, stuff); // 上下框
	vector<char> line(width + 2, empty); // 中间行
	line[0] = line[width + 1] = stuff;
	canvas.insert(canvas.begin(), 2, td);
	canvas.insert(canvas.begin() + 1, height, line);
}

/*初始化画布*/
void PixelCanvas::initCanvas() {
	refresh();
}

/*刷新画布*/
void PixelCanvas::refresh() {
	// 两个空格对齐一个方块
	string out = "", out_stuff = "■", out_empty = "  ", out_enter = "\n";
	int line_index = 0;
	int show = height - 5;
	for (auto &line : canvas) {
		for (auto &c : line) {
			out += (c == empty) ? out_empty : out_stuff; // string+=重载相当于append
		}
		// 右边输出得分和下一个方框图形
		if (line_index >= show) {
			if (line_index == show) {
				out += out_empty + "得分：" + to_string(score);
			} else if (line_index == show + 2) {
				out += out_empty + "下一个:";
			} else if (line_index == show + 4) {
				out += out_empty + next[0];
			} else if (line_index == show + 5 && next.size() != 1) {
				out += out_empty + next[1];
			}
		}
		out += out_enter;
		++line_index;
	}
	system("cls"); // 清除屏幕
	printf(out.c_str()); // 输出比cout快一点点
}

/*新增图形，没有覆盖则返回true*/
bool PixelCanvas::addGraph(const graph &list) {
	bool no_repeat = true;
	for (auto &pos : list) {
		if (!check_range(pos.first, pos.second)) continue; // 越界
		if (canvas[pos.first][pos.second] == stuff) {
			no_repeat = false;
		} else {
			canvas[pos.first][pos.second] = stuff;
		}
	}
	refresh();
	return no_repeat;
}

/*检查坐标范围*/
bool PixelCanvas::check_range(size_type x, size_type y) {
	return x > 0 && x <= height && y > 0 && y <= width;
}

/*改变图形形状，before为要清空的图形，after为需要填充为stuff的图形*/
bool PixelCanvas::changeGraph(const graph &before, const graph &after) {
	for (auto &pos : after) {
		if (canvas[pos.first][pos.second] == stuff && // 所要变换的地方存在方块
			find(before.begin(), before.end(), pos) == before.end()) { // 并且存在的方块不是本身的
			return false; // 发生碰撞
		}
	}
	for (auto &pos : before) {
		canvas[pos.first][pos.second] = empty;
	}
	for (auto &pos : after) {
		canvas[pos.first][pos.second] = stuff;
	}
	refresh();
	return true;
}

/*清除占满方块的行*/
void PixelCanvas::removeFullLine(const graph &list) {
	size_type low = height, top = 1; // low反而是最高行，top是最低行
	vector<size_type> full;
	// 记录图形所占最低行数和最高行数，只需在两者之间判断是否满行
	for (auto &pos : list) {
		if (pos.first < low) low = pos.first;
		if (pos.first > top) top = pos.first;
	}
	// 添加满行索引
	for (size_type i = low; i <= top; ++i) {
		auto line = canvas[i];
		if (find(line.begin(), line.end(), empty) == line.end()) {
			full.push_back(i);
		}
	}
	// 未满行无需进行操作
	if (!full.empty()) {
		size_type rl = full[full.size() - 1], ml = rl - 1; // 填充行和移动行的双指针
		bool replaceEmptyLine = false; // 是否已经下移完成
		// 下移中间行填充需要消除的行
		while (!replaceEmptyLine && ml != 0) {
			// 找到占满行上面第一个不被占满的行
			while (find(full.begin(), full.end(), ml) != full.end()) --ml;
			auto &replace = canvas[rl--], &move = canvas[ml--];
			replaceEmptyLine = true;
			for (size_type i = 1; i <= width; ++i) {
				replace[i] = move[i];
				if (replaceEmptyLine && replace[i] == stuff) {
					replaceEmptyLine = false;
				}
			}
		}
		// 下移后清空上面额外的行
		for (size_type i = ml + (ml == 0 ? 1 : 2); i <= rl; ++i) {
			for (size_type j = 1; j <= width; ++j) {
				canvas[i][j] = empty;
			}
		}
		score += full.size();
		refresh();
	}
}