#pragma once

#include "define.h"
#include "Frame.h"
#include "Animation.h"
#include "FBO.h"
#include "GraphPara.h"

//�O���t�`��N���X
class Graph : public Frame {
private:
	//�g�`��h��Ԃ����ǂ���
	bool fill_wave;
	void main_draw();
public:
	graph g;
	Graph(graph set_g, int set_length, Frame *set_parent = nullptr, bool set_lock = 0, bool set_fill_wave = 0, std::string set_name = "", std::string set_description = "");
};

//�t�F�[�h�O���t�`��N���X
class Fade : public Frame {

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