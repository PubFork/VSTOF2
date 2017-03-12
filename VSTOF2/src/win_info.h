#pragma once

#include "define.h"

//マウスイベント処理クラス
class MOUSE {
public:
	struct Click {
		bool l; //lクリック
		bool r; //rクリック
		bool wheel; //ホイール
	};
	//変数宣言
	WindowPos mouse; //マウス座標
	WindowPos b_mouse; //前フレームのマウス座標
	Click push; //押されてたらずっと1
	Click b_push; //前フレームのpush
	Click click; //押されたフレームのみ1

	MOUSE();
	//指定RECT内に存在するかどうか
	bool in(RECT area);
	bool in(POINT pos, int size);
	//クリック判定
	void hudg_click();
	//ループ関数
	void loop();
};

//ウィンドウ情報保持変数
class WINDOW_INFO {
public:
	//変数宣言
	POINT size; //ウィンドウサイズ
	POINT b_size; //前フレームのウィンドウサイズ
	RECT window; //ウィンドウ左上右下座標(デスクトップ基準)
	HDC glDc; //OpenFrameworksのOpenGLのデバイスコンテキスト
	HWND hwnd; //OpenFrameworksの生成ウィンドウのハンドル
	double fps; //ウィンドウの描画フレームレート
	double speed; //60fpsを基準としたフレーム単位のアニメーション速度
	MOUSE mouse;

	//ループ関数
	void loop();
};