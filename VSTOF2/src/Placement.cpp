#include "Placement.h"

Parameteres::Parameteres() { //�S�p�����[�^�[���̃t���[���쐬
	//�t���[������
	//frame_m.add(frame *parent, frame *self, std::string name, int length, bool lock)
	frame_m.add(nullptr, &p_frame.window, "window", 0, 0);
	frame_m.add(nullptr, &p_frame.root, "root", 0, 0);
	frame_m.add(&p_frame.root, &p_frame.tone, "tone", 0, 0); //���F�ݒ�t���[������
	frame_m.add(&p_frame.tone, &p_frame.make_auto, "make_auto", 200, 0); //�����ŉ��F�𐶐����邩
	frame_m.add(&p_frame.tone, &p_frame.raw_wave_para, "raw_wave_para", 0, 0); //���L�C���f���g�𑩂˂�
	frame_m.add(&p_frame.raw_wave_para, &p_frame.use_rawwave, "use_rawwave", 100, 0); //���g�`�f�[�^�̎g�p�����邩�ǂ���
	frame_m.add(&p_frame.raw_wave_para, &p_frame.rawwave, "rawwave", 100, 0); //���g�`�̎g�p�����g�`(�t�@�C���}�b�s���O�ɂ��邩��(�L�E�ցE�M))
	frame_m.add(&p_frame.raw_wave_para, &p_frame.base_pitch, "base_pitch", 100, 0); //��ʒu(�蓮�ύX��)
	frame_m.add(&p_frame.tone, &p_frame.tone_para, "tone_para", 0, 0); //���L�C���f���g�̃t���[���𑩂˂�
	frame_m.add(&p_frame.tone_para, &p_frame.change_natural, "change_natural", 100, 0); //�����ω������R�ɂ��邩
	frame_m.add(&p_frame.tone_para, &p_frame.overtones, "overtones", 100, 0); //�{���O���tor���X�y�N�g���O���t
	frame_m.add(&p_frame.tone_para, &p_frame.iovertones, "iovertones", 100, 0); //�{���̐�
	frame_m.add(&p_frame.tone_para, &p_frame.wave_type, "wave_type", 100, 0); //��{�g�`�̌`
	frame_m.add(&p_frame.tone_para, &p_frame.hostpar, "hostpar", 0, 0); //���L�C���f���g�̃t���[���𑩂˂�
	frame_m.add(&p_frame.hostpar, &p_frame.vol, "vol", 100, 0); //����
	frame_m.add(&p_frame.hostpar, &p_frame.pitch, "pitch", 100, 0); //����(IDI�l�ɉ��Z)
	frame_m.add(&p_frame.tone, &p_frame.wave_limit, "wave_limit", 100, 0); //�g�`�̐�Βl�̏��
	frame_m.add(&p_frame.tone, &p_frame.outwave, "outwave", 100, 0); //�o�͔g�`
	frame_m.add(&p_frame.root, &p_frame.fade, "fade", 0, 0); //�t�F�[�h�ݒ�t���[������
	frame_m.add(&p_frame.fade, &p_frame.use_string_mode, "use_string_mode", 100, 0); //�����[�h�̎g�p�����邩�ǂ���
	frame_m.add(&p_frame.fade, &p_frame.use_fade_change, "use_fade_change", 100, 0); //�Ȃ߂炩�ȉ���,���ʂ̕ω����g�p���邩�ǂ���(2�����ɉ����o���Ȃ�)
	frame_m.add(&p_frame.fade, &p_frame.fadein, "fadein", 0, 0);
	frame_m.add(&p_frame.fadein, &p_frame.fadein_vol, "fadein_vol", 100, 0);
	frame_m.add(&p_frame.fadein, &p_frame.fadein_pitch, "fadein_pitch", 100, 0);
	frame_m.add(&p_frame.fade, &p_frame.fadeout, "fadeout", 0, 0);
	frame_m.add(&p_frame.fadeout, &p_frame.fadeout_vol, "fadeout_vol", 100, 0);
	frame_m.add(&p_frame.fadeout, &p_frame.fadeout_pitch, "fadeout_pitch", 100, 0);
	frame_m.add(&p_frame.fade, &p_frame.fadechange, "fadechange", 0, 0);
	frame_m.add(&p_frame.fadechange, &p_frame.fadechange_vol, "fadechange_vol", 100, 0);
	frame_m.add(&p_frame.fadechange, &p_frame.fadechange_pitch, "fadechange_pitch", 100, 0);

	//set_parent(frame *self, bool mode, int gap)
	frame_m.set_parent(&p_frame.root, 0, 2);
	frame_m.set_parent(&p_frame.hostpar, 1, 2);
	frame_m.set_parent(&p_frame.fadein, 1, 2);
	frame_m.set_parent(&p_frame.fadeout, 1, 2);
	frame_m.set_parent(&p_frame.fadechange, 1, 2);
	frame_m.set_parent(&p_frame.fadechange, 1, 2);

	//set_description(frame *f, std::string description)
	frame_m.set_description(&p_frame.tone, "Timbre setting");
	frame_m.set_description(&p_frame.make_auto, "Automatically generate tone");
	frame_m.set_description(&p_frame.use_rawwave, "Use raw sound source");
	frame_m.set_description(&p_frame.rawwave, "Trimming");

	frame_m.get_length(&p_frame.root); //root���S�t���[����length���擾
	frame_m.resize(&p_frame.root, { 0,0,1,p_frame.root.length }); //root�t���[���ꎞ���T�C�Y

	//�c���[�\����CUI�`��(DEBUG�p)
	Debug::draw_node_name(&p_frame.root);
}

void Draw::set_p_value(VSTParameteres *p_value) {
	para.p_value = p_value;
}

bool Draw::resize(WINDOW_INFO win_info) { //�`��̈�ύX
	//win_info�̃E�B���h�E�T�C�Y�X�V
	GetClientRect(win_info.hwnd, &win_info.window);
	win_info.size.x = win_info.window.right - win_info.window.left;
	win_info.size.y = win_info.window.bottom - win_info.window.top;
	para.p_frame.window.pos.left = 0;
	para.p_frame.window.pos.top = 0;
	para.p_frame.window.pos.right = win_info.size.x;
	para.p_frame.window.pos.bottom = win_info.size.y;
	para.p_frame.window.size = win_info.size;
	fps = win_info.fps;
	gui.set_fps(fps);
	return 0;
}

void Draw::loop() { //���[�v���ɌĂяo���֐�
	//��ʏ�����
	gui.reset();
	//�e�p�����[�^�[�`��
	VSTParameteresFrames *f = &para.p_frame;
	VSTParameteres *p = para.p_value;

	/*memo*/
	//�t���[������n�̏������Ɏ��s���āA
	//���̎��ɕ`��n�̏��������s����

	//�t���[������n
	gui.scroll(&f->root, &f->window);
	//�`��n
	gui.sw(&f->make_auto, &p->make_auto);
	gui.sw(&f->use_rawwave, &p->use_rawwave);
	ofSetColor(255, 255, 255, 255);
	gui.wave_gui(&f->rawwave, p->rawwave, p->nrawwave, 0); //<-nrawwave��DXVST2�̕��ő������ĂȂ����ۂ�
	
	/*
	{
		gui.wave_gui(&f->make_auto, p->outwave, p->noutwave, 0);
		gui.sw(&f->use_rawwave, &p->use_rawwave);
		//gui.volume_gui(&f->rawwave, &b);
	}
	*/

	//�t���[���̋��E���`��
	gui.FrameLine(&para.p_frame.root);
	//�t���[���̖��̕`��
	gui.FrameName(&para.p_frame.root);

	//���t���[���Ăяo���֐�
	gui.loop();
}