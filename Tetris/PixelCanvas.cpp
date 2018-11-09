#include "PixelCanvas.h"
#include <iostream>
#include <string>
#include <stdio.h>

PixelCanvas::PixelCanvas(size_type width, size_type height) : width(width), height(height) {
	vector<char> td(width + 2, stuff); // ���¿�
	vector<char> line(width + 2, empty); // �м���
	line[0] = line[width + 1] = stuff;
	canvas.insert(canvas.begin(), 2, td);
	canvas.insert(canvas.begin() + 1, height, line);
}

/*��ʼ������*/
void PixelCanvas::initCanvas() {
	refresh();
}

/*ˢ�»���*/
void PixelCanvas::refresh() {
	// �����ո����һ������
	string out = "", out_stuff = "��", out_empty = "  ", out_enter = "\n";
	int line_index = 0;
	int show = height - 5;
	for (auto &line : canvas) {
		for (auto &c : line) {
			out += (c == empty) ? out_empty : out_stuff; // string+=�����൱��append
		}
		// �ұ�����÷ֺ���һ������ͼ��
		if (line_index >= show) {
			if (line_index == show) {
				out += out_empty + "�÷֣�" + to_string(score);
			} else if (line_index == show + 2) {
				out += out_empty + "��һ��:";
			} else if (line_index == show + 4) {
				out += out_empty + next[0];
			} else if (line_index == show + 5 && next.size() != 1) {
				out += out_empty + next[1];
			}
		}
		out += out_enter;
		++line_index;
	}
	system("cls"); // �����Ļ
	printf(out.c_str()); // �����cout��һ���
}

/*����ͼ�Σ�û�и����򷵻�true*/
bool PixelCanvas::addGraph(const graph &list) {
	bool no_repeat = true;
	for (auto &pos : list) {
		if (!check_range(pos.first, pos.second)) continue; // Խ��
		if (canvas[pos.first][pos.second] == stuff) {
			no_repeat = false;
		} else {
			canvas[pos.first][pos.second] = stuff;
		}
	}
	refresh();
	return no_repeat;
}

/*������귶Χ*/
bool PixelCanvas::check_range(size_type x, size_type y) {
	return x > 0 && x <= height && y > 0 && y <= width;
}

/*�ı�ͼ����״��beforeΪҪ��յ�ͼ�Σ�afterΪ��Ҫ���Ϊstuff��ͼ��*/
bool PixelCanvas::changeGraph(const graph &before, const graph &after) {
	for (auto &pos : after) {
		if (canvas[pos.first][pos.second] == stuff && // ��Ҫ�任�ĵط����ڷ���
			find(before.begin(), before.end(), pos) == before.end()) { // ���Ҵ��ڵķ��鲻�Ǳ����
			return false; // ������ײ
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

/*���ռ���������*/
void PixelCanvas::removeFullLine(const graph &list) {
	size_type low = height, top = 1; // low����������У�top�������
	vector<size_type> full;
	// ��¼ͼ����ռ������������������ֻ��������֮���ж��Ƿ�����
	for (auto &pos : list) {
		if (pos.first < low) low = pos.first;
		if (pos.first > top) top = pos.first;
	}
	// �����������
	for (size_type i = low; i <= top; ++i) {
		auto line = canvas[i];
		if (find(line.begin(), line.end(), empty) == line.end()) {
			full.push_back(i);
		}
	}
	// δ����������в���
	if (!full.empty()) {
		size_type rl = full[full.size() - 1], ml = rl - 1; // ����к��ƶ��е�˫ָ��
		bool replaceEmptyLine = false; // �Ƿ��Ѿ��������
		// �����м��������Ҫ��������
		while (!replaceEmptyLine && ml != 0) {
			// �ҵ�ռ���������һ������ռ������
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
		// ���ƺ��������������
		for (size_type i = ml + (ml == 0 ? 1 : 2); i <= rl; ++i) {
			for (size_type j = 1; j <= width; ++j) {
				canvas[i][j] = empty;
			}
		}
		score += full.size();
		refresh();
	}
}