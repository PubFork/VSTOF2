#pragma once

#include "define.h"
#include "Frame.h"
#include "Animation.h"
#include "FBO.h"
#include "GraphPara.h"

//グラフ描画クラス
class Graph : public Frame {
private:
	bool FillWave;
public:
	Graph();
	graph g;
	void set_data(graph set_g);
	void fill_wave(bool Enable);
	void draw();
};

//ボタン描画クラス
class Button : public Frame {

};

//ボリューム描画クラス
class Volume : public Frame {

};

//個数選択描画クラス
class Figure : public Frame {

};

//波形の形選択描画クラス
class WaveForm : public Frame {

};