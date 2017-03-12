#include "UI.h"

UI::Graph::Graph() {
	FillWave = 0;
}

void UI::Graph::set_data(graph set_g) {
	g = set_g;
}

void UI::Graph::fill_wave(bool Enable) {
	FillWave = Enable;
}

void UI::Graph::draw() {
	//描画効率化のため、ピクセルの数に合わせて描画
	int index = 0; //配列から値を参照するときのインデックス
	float percentage = 0.0f;
	float height; //今描画する波の高さ
	float b_height; //前フレームのheight
	float zero = Utility::Proportion(0.0f, g.val_min, g.val_max, (float)(pos.bottom), (float)(pos.top)); //グラフy座標が0のときのフレームy座標
	for (int i = 0; i < size.x; i++) {
		percentage = Utility::Proportion((float)i, 0.0f, (float)size.x, (float)g.start_index, (float)g.end_index); //一時代入
		index = (int)percentage; //波形配列のインデックス算出
		percentage = percentage - (float)index; //int,floatの性質上必ず正の数になる
												//(念の為)index+1>=num_sampleになったらループ脱出
		if (index + 1 >= g.num_sample) {
			break;
		}
		//今描画する波の高さ
		height =
			Utility::Proportion(g.samples[index], g.val_min, g.val_max, (float)(pos.bottom), (float)(pos.top)) * (1.0f - percentage) +
			Utility::Proportion(g.samples[index + 1], g.val_min, g.val_max, (float)(pos.bottom), (float)(pos.top)) * (percentage);
		//グラフ描画
		if (i > 0) {
			ofSetColor(255, 255, 255, 255);
			ofLine(
				pos.left + i - 1,
				b_height,
				pos.left + i,
				height
			);
		}
		//塗りつぶし
		if (FillWave) {
			if ((i / 10) % 2 == 0) {
				ofSetColor(255, 255, 255, 255);
				ofLine(
					pos.left + i,
					zero,
					pos.left + i,
					height
				);
			}
		}
		b_height = height; //前フレームのときのheight取得用
	}
}