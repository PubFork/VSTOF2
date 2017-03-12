#include "AllProcess.h"
#include "UI.h"

bool AllProcess::init(LPSTR cmd, WINDOW_INFO win_info2) { //初期化時実行関数
	//変数代入
	win_info = win_info2;
	//共有メモリ関連
	wchar_t *wlocal = new wchar_t[strlen(cmd)];
	Utility::LPtoLPCW(cmd, wlocal);
	if (sm.Open(wlocal)) {
		return 1;
	}
	delete wlocal;
	if (sm.smd->Ready != nullptr) { //多重起動防止
		return 1;
	}
	else {
		sm.smd->Ready = win_info.hwnd;
	}
	return 0;
}

bool AllProcess::loop() { //ループ中に呼び出す関数
	//画面初期化
	ofSetColor(30, 30, 30, 255);
	ofRect(0, 0, 854, 480);
	//

	Debug::SetFpsTitle(win_info);
	return 0;
}

AllProcess::~AllProcess() {
	if (sm.smd != nullptr) {
		sm.smd->Ready = nullptr;
	}
}