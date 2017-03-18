#include "Placement.h"

Parameteres::Parameteres() { //全パラメーター分のフレーム作成
	//一時変数初期化
	graph g_buf;
	//フレーム生成
	/*
	Frame(Frame *set_parent = nullptr, int set_length = 0, bool set_lock = 0, std::string set_name = "", std::string set_description = "");
	Frame(bool set_mode, Frame *set_parent, std::string set_name = "", std::string set_description = "");
	Graph(graph set_g, int set_length, Frame *set_parent = nullptr, bool set_lock = 0, bool set_fill_wave = 0, std::string set_name = "", std::string set_description = "");
	*/
	p_frame.window = new Frame(1, nullptr, "window"); //ウィンドウと同期用フレーム
	p_frame.root = new Frame(0, nullptr, "root"); //パラメータ関係のフレームツリーのrootフレーム
	p_frame.tone = new Frame(0, p_frame.root, "tone"); //音色設定フレーム
	p_frame.fade = new Frame(0, p_frame.root, "fade"); //フェード設定フレーム
	//音色系
	p_frame.make_auto = new Button; //自動で音色を生成するか
	p_frame.raw_wave_para = new Frame(0, p_frame.tone, "raw_wave_para"); //下記インデントを束ねる
	//生波形データ派生
	p_frame.use_rawwave = new Button; //生波形データの使用をするかどうか
	g_buf.samples = p_value->rawwave;
	g_buf.num_sample = p_value->nrawwave;
	g_buf.end_index = g_buf.num_sample;
	p_frame.rawwave = new Graph(g_buf, 100, p_frame.raw_wave_para, "rawwave"); //生波形の使用部分波形(ファイルマッピングにするかも(´・ω・｀))
	g_buf.samples = p_value->overtones;
	g_buf.num_sample = p_value->iovertones;
	g_buf.end_index = g_buf.num_sample;
	p_frame.base_pitch = new Graph(g_buf, 100, p_frame.raw_wave_para, "base_pitch"); //基音位置(手動変更可)
	p_frame.tone_para = new Frame(0, p_frame.tone, "tone_para"); //下記インデントのフレームを束ねる
	p_frame.change_natural = new Button; //音程変化を自然にするか
	g_buf.samples = p_value->overtones;
	g_buf.num_sample = p_value->iovertones;
	g_buf.end_index = g_buf.num_sample;
	p_frame.overtones = new Graph(g_buf, 100, p_frame.tone_para, "overtones"); //倍音グラフor共鳴スペクトルグラフ
	p_frame.iovertones = new Figure; //倍音の数
	p_frame.wave_type = new WaveForm; //基本波形の形
	//再生中変更できると便利なパラメーター
	p_frame.hostpar = new Frame(1, p_frame.tone_para, "hostpar");
	p_frame.vol = new Volume;
	p_frame.pitch = new Volume; //MIDI値に加算
	//波形の絶対値の上限
	g_buf.samples = p_value->outwave;
	g_buf.num_sample = p_value->noutwave;
	g_buf.end_index = g_buf.num_sample;
	p_frame.wave_limit = new Graph(g_buf, 100, p_frame.tone, "wave_limit");
	//生成波形
	g_buf.samples = p_value->outwave;
	g_buf.num_sample = p_value->noutwave;
	g_buf.end_index = g_buf.num_sample;
	p_frame.outwave = new Graph(g_buf, 100, p_frame.tone, "outwave"); //出力される波形
	//フェード系
	p_frame.use_string_mode = new Button; //弦モードの使用をするかどうか
	p_frame.use_fade_change = new Button; //なめらかな音程,音量の変化を使用するかどうか(2つ同時に音を出せない)
	p_frame.fadein = new Frame(1, p_frame.fade, "fadein");
	p_frame.fadein_vol = new Fade;
	p_frame.fadein_pitch = new Fade;
	p_frame.fadeout = new Frame(1, p_frame.fade, "fadeout");
	p_frame.fadeout_vol = new Fade;
	p_frame.fadeout_pitch = new Fade;
	p_frame.fadechange = new Frame(1, p_frame.fade, "fadechange");
	p_frame.fadechange_vol = new Fade;
	p_frame.fadechange_pitch = new Fade;

	//ツリー構造のCUI描画(DEBUG用)
	Debug::draw_node_name(p_frame.root);
}

void Draw::set_p_value(VSTParameteres *p_value) {
	para.p_value = p_value;
}

bool Draw::resize(WINDOW_INFO win_info) { //描画領域変更
	//win_infoのウィンドウサイズ更新
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

void Draw::loop() { //ループ中に呼び出す関数
	//各パラメーター描画
	VSTParameteresFrames *f = &para.p_frame;
	VSTParameteres *p = para.p_value;

	/*memo*/
	//フレーム操作系の処理を先に実行して、
	//その次に描画系の処理を実行する

	//フレーム操作系
	gui.scroll(&f->root, &f->window);
	//描画系
	gui.sw(&f->make_auto, &p->make_auto);
	gui.sw(&f->use_rawwave, &p->use_rawwave);
	ofSetColor(255, 255, 255, 255);
	gui.wave_gui(&f->rawwave, p->rawwave, p->nrawwave, 0); //<-nrawwaveがDXVST2の方で代入されてないっぽい
	
	/*
	{
		gui.wave_gui(&f->make_auto, p->outwave, p->noutwave, 0);
		gui.sw(&f->use_rawwave, &p->use_rawwave);
		//gui.volume_gui(&f->rawwave, &b);
	}
	*/

	//フレームの境界線描画
	gui.FrameLine(&para.p_frame.root);
	//フレームの名称描画
	gui.FrameName(&para.p_frame.root);

	//毎フレーム呼び出し関数
	gui.loop();
}