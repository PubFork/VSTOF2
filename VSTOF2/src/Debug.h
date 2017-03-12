#pragma once

#include "define.h"
#include "Frame.h"

class Debug {
public:
	//ツリー構造のCUI描画(DEGUG用)
	static void draw_node_name(Frame *f) {
		std::string tree = "[Frame nodes tree viewer]\n";
		std::vector<int> gap;
		tree = draw_node_name(f, gap, tree);
		std::cout << tree << std::endl;
	}
	static string draw_node_name(Frame *f, std::vector<int> gap, std::string tree) {
		bool pop_back = true;
		if (f->parent != nullptr) {
			if (f->parent->parent != nullptr) {
				if (f->parent->parent->childs[f->parent->parent->childs.size() - 1] == f->parent) {
					if (gap.size() >= 2) {
						gap[gap.size() - 2] += gap[gap.size() - 1] + 2;
						gap.pop_back();
						pop_back = false;
					}
				}
			}
		}
		if (f->parent != nullptr) {
			tree += "\n";
			for (int i = 0; i < gap.size(); i++) {
				for (int j = 0; j < gap[i]; j++) {
					tree += " ";
				}
				if (i == (gap.size() - 1)) {
					break;
				}
				tree += "┃";
			}
			if (f->parent->childs[f->parent->childs.size() - 1] == f) {
				tree += "┗";
			}
			else {
				tree += "┣";
			}
		}
		tree += "[";
		tree += f->name;
		tree += "]";
		gap.push_back(0);
		for (int i = 0; i < f->childs.size(); i++) {
			tree = draw_node_name(f->childs[i], gap, tree);
		}
		if (pop_back) {
			gap.pop_back();
		}
		return tree;
	}
	//現在のFPSをタイトルバーに表示
	static void SetFpsTitle(WINDOW_INFO win_info) {
		std::string title = "";
		title += "fps:";
		title += std::to_string(ofGetFrameRate());
		wchar_t *wlocal = new wchar_t[strlen(title.c_str())+1];
		Utility::LPtoLPCW((LPSTR)title.c_str(), wlocal);
		SetWindowText(win_info.hwnd, wlocal);
		delete wlocal;
	}
};