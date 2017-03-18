#include "Placement.h"

Parameteres::Parameteres() { //�S�p�����[�^�[���̃t���[���쐬
	//�ꎞ�ϐ�������
	graph g_buf;
	//�t���[������
	/*
	Frame(Frame *set_parent = nullptr, int set_length = 0, bool set_lock = 0, std::string set_name = "", std::string set_description = "");
	Frame(bool set_mode, Frame *set_parent, std::string set_name = "", std::string set_description = "");
	Graph(graph set_g, int set_length, Frame *set_parent = nullptr, bool set_lock = 0, bool set_fill_wave = 0, std::string set_name = "", std::string set_description = "");
	*/
	p_frame.window = new Frame(1, nullptr, "window"); //�E�B���h�E�Ɠ����p�t���[��
	p_frame.root = new Frame(0, nullptr, "root"); //�p�����[�^�֌W�̃t���[���c���[��root�t���[��
	p_frame.tone = new Frame(0, p_frame.root, "tone"); //���F�ݒ�t���[��
	p_frame.fade = new Frame(0, p_frame.root, "fade"); //�t�F�[�h�ݒ�t���[��
	//���F�n
	p_frame.make_auto = new Button; //�����ŉ��F�𐶐����邩
	p_frame.raw_wave_para = new Frame(0, p_frame.tone, "raw_wave_para"); //���L�C���f���g�𑩂˂�
	//���g�`�f�[�^�h��
	p_frame.use_rawwave = new Button; //���g�`�f�[�^�̎g�p�����邩�ǂ���
	g_buf.samples = p_value->rawwave;
	g_buf.num_sample = p_value->nrawwave;
	g_buf.end_index = g_buf.num_sample;
	p_frame.rawwave = new Graph(g_buf, 100, p_frame.raw_wave_para, "rawwave"); //���g�`�̎g�p�����g�`(�t�@�C���}�b�s���O�ɂ��邩��(�L�E�ցE�M))
	g_buf.samples = p_value->overtones;
	g_buf.num_sample = p_value->iovertones;
	g_buf.end_index = g_buf.num_sample;
	p_frame.base_pitch = new Graph(g_buf, 100, p_frame.raw_wave_para, "base_pitch"); //��ʒu(�蓮�ύX��)
	p_frame.tone_para = new Frame(0, p_frame.tone, "tone_para"); //���L�C���f���g�̃t���[���𑩂˂�
	p_frame.change_natural = new Button; //�����ω������R�ɂ��邩
	g_buf.samples = p_value->overtones;
	g_buf.num_sample = p_value->iovertones;
	g_buf.end_index = g_buf.num_sample;
	p_frame.overtones = new Graph(g_buf, 100, p_frame.tone_para, "overtones"); //�{���O���tor���X�y�N�g���O���t
	p_frame.iovertones = new Figure; //�{���̐�
	p_frame.wave_type = new WaveForm; //��{�g�`�̌`
	//�Đ����ύX�ł���ƕ֗��ȃp�����[�^�[
	p_frame.hostpar = new Frame(1, p_frame.tone_para, "hostpar");
	p_frame.vol = new Volume;
	p_frame.pitch = new Volume; //MIDI�l�ɉ��Z
	//�g�`�̐�Βl�̏��
	g_buf.samples = p_value->outwave;
	g_buf.num_sample = p_value->noutwave;
	g_buf.end_index = g_buf.num_sample;
	p_frame.wave_limit = new Graph(g_buf, 100, p_frame.tone, "wave_limit");
	//�����g�`
	g_buf.samples = p_value->outwave;
	g_buf.num_sample = p_value->noutwave;
	g_buf.end_index = g_buf.num_sample;
	p_frame.outwave = new Graph(g_buf, 100, p_frame.tone, "outwave"); //�o�͂����g�`
	//�t�F�[�h�n
	p_frame.use_string_mode = new Button; //�����[�h�̎g�p�����邩�ǂ���
	p_frame.use_fade_change = new Button; //�Ȃ߂炩�ȉ���,���ʂ̕ω����g�p���邩�ǂ���(2�����ɉ����o���Ȃ�)
	p_frame.fadein = new Frame(1, p_frame.fade, "fadein");
	p_frame.fadein_vol = new Fade;
	p_frame.fadein_pitch = new Fade;
	p_frame.fadeout = new Frame(1, p_frame.fade, "fadeout");
	p_frame.fadeout_vol = new Fade;
	p_frame.fadeout_pitch = new Fade;
	p_frame.fadechange = new Frame(1, p_frame.fade, "fadechange");
	p_frame.fadechange_vol = new Fade;
	p_frame.fadechange_pitch = new Fade;

	//�c���[�\����CUI�`��(DEBUG�p)
	Debug::draw_node_name(p_frame.root);
}

void Draw::set_p_value(VSTParameteres *p_value) {
	para.p_value = p_value;
}

bool Draw::resize(WINDOW_INFO win_info) { //�`��̈�ύX
	//win_info�̃E�B���h�E�T�C�Y�X�V
	GetClientRect(win_info.hwnd, &win_info.window);
	win_info.size.x = win_info.window.right - win_info.window.left;
	win_info.size.y = win_info.window.bottom - win_info.window.top;
	para.p_frame.window->pos.left = 0;
	para.p_frame.window->pos.top = 0;
	para.p_frame.window->pos.right = win_info.size.x;
	para.p_frame.window->pos.bottom = win_info.size.y;
	para.p_frame.window->size = win_info.size;
	fps = win_info.fps;
	return 0;
}

void Draw::loop() { //���[�v���ɌĂяo���֐�
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