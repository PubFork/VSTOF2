#pragma once

#include "define.h"
#include "Frame.h"
#include "Animation.h"
#include "FBO.h"
#include "GraphPara.h"

//�O���t�`��N���X
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

//�{�^���`��N���X
class Button : public Frame {

};

//�{�����[���`��N���X
class Volume : public Frame {

};

//���I��`��N���X
class Figure : public Frame {

};

//�g�`�̌`�I��`��N���X
class WaveForm : public Frame {

};