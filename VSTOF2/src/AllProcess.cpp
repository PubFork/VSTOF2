#include "AllProcess.h"
#include "UI.h"

bool AllProcess::init(LPSTR cmd, WINDOW_INFO win_info2) { //�����������s�֐�
	//�ϐ����
	win_info = win_info2;
	//���L�������֘A
	wchar_t *wlocal = new wchar_t[strlen(cmd)];
	Utility::LPtoLPCW(cmd, wlocal);
	if (sm.Open(wlocal)) {
		return 1;
	}
	delete wlocal;
	if (sm.smd->Ready != nullptr) { //���d�N���h�~
		return 1;
	}
	else {
		sm.smd->Ready = win_info.hwnd;
	}
	return 0;
}

bool AllProcess::loop() { //���[�v���ɌĂяo���֐�
	//��ʏ�����
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