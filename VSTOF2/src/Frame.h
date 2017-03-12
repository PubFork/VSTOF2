#pragma once

#include "define.h"
#include "win_info.h"

//フレーム基底クラス
class Frame {
private:
	//自フレーム以下の全子フレームのdraw関数実行
	void childs_draw();
public:
	//変数
	Frame *parent; //親フレームのポインタ
	int num_child; //子フレームの数
	std::vector<Frame*> childs; //全子フレームのポインタ配列
	int index;//同フレーム内の自フレームの割当番号(=0,1,2,3,...)
	RECT pos; //フレーム座標
	POINT size; //フレームサイズ(末端フレームのみ代入)
	std::string name; //フレームの名称
	std::string description; //フレーム内のUIの解説
	bool mode; //子フレームが縦並び=0,横並び=1
	int gap; //子フレーム間同士の隙間(px単位)
	int length; //全フレームが初期値サイズ時の自フレームのサイズ
	bool lock; //各子フレームの長さ(mode=0なら縦幅,mode=1なら横幅)の固定on/off
	int lock_length; //固定サイズの全子フレームと全gapの和(末端フレームは0を代入)
	double fps;
	WINDOW_INFO *win;

	//関数
	virtual void draw();
	Frame();
};

//フレーム操作クラス
class FrameManagement {
public:
	//関数宣言
	//フレーム追加関数(引数:親フレーム(なければnullptr),自フレーム,フレーム名,子フレームの配列方法(0なら縦,1なら横),子フレーム間の間隔,自フレームの長さ(mode=0なら高さ,1なら幅),自フレームを固定サイズにするon/off)
	void add(Frame *parent, Frame *self, std::string name, int length, bool lock);
	//子フレームの並べ方設定関数
	void set_parent(Frame *self, bool mode, int gap);
	//フレームの解説記入
	void set_description(Frame *self, std::string description);
	//全フレームの登録完了時に、末端フレームから全親フレームのlength等取得関数
	void get_length(Frame *f);
	//全フレームの位置算出(引数1,2,3:自フレームのポインタ,自フレームを描画する位置,0なら長さは初期値のまま)
	void sub_resize(Frame *f, RECT pos);
	//指定フレーム以下のフレームすべての再配置
	void resize(Frame *f, RECT pos);
	//子フレームのポインタからrootフレームのポインタ取得
	Frame* get_root(Frame *f);
};