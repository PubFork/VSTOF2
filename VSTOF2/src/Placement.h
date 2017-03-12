#pragma once

#include "Debug.h"
#include "define.h"
#include "Frame.h"
#include "ShareMem.h"
#include "UI.h"

//パラメーター値構造体
struct VSTParameteresFrames {
	Frame window;

	Frame root;
	Frame tone, fade;
	//音色系
	Button make_auto; //自動で音色を生成するか
	Frame raw_wave_para; //下記インデントを束ねる
						 //生波形データ派生
	Button use_rawwave; //生波形データの使用をするかどうか
	Graph rawwave; //生波形の使用部分波形(ファイルマッピングにするかも(´・ω・｀))
	Graph base_pitch; //基音位置(手動変更可)
	Frame tone_para; //下記インデントのフレームを束ねる
	Button change_natural; //音程変化を自然にするか
	Graph overtones; //倍音グラフor共鳴スペクトルグラフ
	Figure iovertones; //倍音の数
	WaveForm wave_type; //基本波形の形
					 //再生中変更できると便利なパラメーター
	Frame hostpar;
	Volume vol;
	Volume pitch; //MIDI値に加算
				 //波形の絶対値の上限
	Graph wave_limit;
	//生成波形
	Graph outwave; //出力される波形
				   //フェード系
	Button use_string_mode; //弦モードの使用をするかどうか
	Button use_fade_change; //なめらかな音程,音量の変化を使用するかどうか(2つ同時に音を出せない)
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

//パラメーターの値やフレーム変数管理クラス
class Parameteres {
public:
	//コンストラクト
	FrameManagement frame_m; //フレーム操作クラス

	//変数初期化
	VSTParameteres *p_value; //パラメーター値変数群ポインタ
	VSTParameteresFrames p_frame; //パラメーターフレーム変数群

	//関数宣言
	//コンストラクタ
	Parameteres();
};

//描画クラス
class Draw {
public:
	//変数宣言
	float fps;
	RECT win_size;

	//コンストラクト
	Parameteres para;

	//関数宣言
	void set_p_value(VSTParameteres *p_value);
	bool resize(WINDOW_INFO win_info);
	void loop();
};