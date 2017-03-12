#pragma once

#include "Debug.h"
#include "define.h"
#include "Frame.h"
#include "ShareMem.h"
#include "UI.h"

//�p�����[�^�[�l�\����
struct VSTParameteresFrames {
	Frame window;

	Frame root;
	Frame tone, fade;
	//���F�n
	Button make_auto; //�����ŉ��F�𐶐����邩
	Frame raw_wave_para; //���L�C���f���g�𑩂˂�
						 //���g�`�f�[�^�h��
	Button use_rawwave; //���g�`�f�[�^�̎g�p�����邩�ǂ���
	Graph rawwave; //���g�`�̎g�p�����g�`(�t�@�C���}�b�s���O�ɂ��邩��(�L�E�ցE�M))
	Graph base_pitch; //��ʒu(�蓮�ύX��)
	Frame tone_para; //���L�C���f���g�̃t���[���𑩂˂�
	Button change_natural; //�����ω������R�ɂ��邩
	Graph overtones; //�{���O���tor���X�y�N�g���O���t
	Figure iovertones; //�{���̐�
	WaveForm wave_type; //��{�g�`�̌`
					 //�Đ����ύX�ł���ƕ֗��ȃp�����[�^�[
	Frame hostpar;
	Volume vol;
	Volume pitch; //MIDI�l�ɉ��Z
				 //�g�`�̐�Βl�̏��
	Graph wave_limit;
	//�����g�`
	Graph outwave; //�o�͂����g�`
				   //�t�F�[�h�n
	Button use_string_mode; //�����[�h�̎g�p�����邩�ǂ���
	Button use_fade_change; //�Ȃ߂炩�ȉ���,���ʂ̕ω����g�p���邩�ǂ���(2�����ɉ����o���Ȃ�)
	Frame fadein;
	Graph fadein_vol;
	Graph fadein_pitch;
	Frame fadeout;
	Graph fadeout_vol;
	Graph fadeout_pitch;
	Frame fadechange;
	Graph fadechange_vol;
	Graph fadechange_pitch;
};

//�p�����[�^�[�̒l��t���[���ϐ��Ǘ��N���X
class Parameteres {
public:
	//�R���X�g���N�g
	FrameManagement frame_m; //�t���[������N���X

	//�ϐ�������
	VSTParameteres *p_value; //�p�����[�^�[�l�ϐ��Q�|�C���^
	VSTParameteresFrames p_frame; //�p�����[�^�[�t���[���ϐ��Q

	//�֐��錾
	//�R���X�g���N�^
	Parameteres();
};

//�`��N���X
class Draw {
public:
	//�ϐ��錾
	float fps;
	RECT win_size;

	//�R���X�g���N�g
	Parameteres para;

	//�֐��錾
	void set_p_value(VSTParameteres *p_value);
	bool resize(WINDOW_INFO win_info);
	void loop();
};