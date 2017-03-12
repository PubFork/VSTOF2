#pragma once

#include "define.h"
#include "win_info.h"

//�t���[�����N���X
class Frame {
private:
	//���t���[���ȉ��̑S�q�t���[����draw�֐����s
	void childs_draw();
public:
	//�ϐ�
	Frame *parent; //�e�t���[���̃|�C���^
	int num_child; //�q�t���[���̐�
	std::vector<Frame*> childs; //�S�q�t���[���̃|�C���^�z��
	int index;//���t���[�����̎��t���[���̊����ԍ�(=0,1,2,3,...)
	RECT pos; //�t���[�����W
	POINT size; //�t���[���T�C�Y(���[�t���[���̂ݑ��)
	std::string name; //�t���[���̖���
	std::string description; //�t���[������UI�̉��
	bool mode; //�q�t���[�����c����=0,������=1
	int gap; //�q�t���[���ԓ��m�̌���(px�P��)
	int length; //�S�t���[���������l�T�C�Y���̎��t���[���̃T�C�Y
	bool lock; //�e�q�t���[���̒���(mode=0�Ȃ�c��,mode=1�Ȃ牡��)�̌Œ�on/off
	int lock_length; //�Œ�T�C�Y�̑S�q�t���[���ƑSgap�̘a(���[�t���[����0����)
	double fps;
	WINDOW_INFO *win;

	//�֐�
	virtual void draw();
	Frame();
};

//�t���[������N���X
class FrameManagement {
public:
	//�֐��錾
	//�t���[���ǉ��֐�(����:�e�t���[��(�Ȃ����nullptr),���t���[��,�t���[����,�q�t���[���̔z����@(0�Ȃ�c,1�Ȃ牡),�q�t���[���Ԃ̊Ԋu,���t���[���̒���(mode=0�Ȃ獂��,1�Ȃ畝),���t���[�����Œ�T�C�Y�ɂ���on/off)
	void add(Frame *parent, Frame *self, std::string name, int length, bool lock);
	//�q�t���[���̕��ו��ݒ�֐�
	void set_parent(Frame *self, bool mode, int gap);
	//�t���[���̉���L��
	void set_description(Frame *self, std::string description);
	//�S�t���[���̓o�^�������ɁA���[�t���[������S�e�t���[����length���擾�֐�
	void get_length(Frame *f);
	//�S�t���[���̈ʒu�Z�o(����1,2,3:���t���[���̃|�C���^,���t���[����`�悷��ʒu,0�Ȃ璷���͏����l�̂܂�)
	void sub_resize(Frame *f, RECT pos);
	//�w��t���[���ȉ��̃t���[�����ׂĂ̍Ĕz�u
	void resize(Frame *f, RECT pos);
	//�q�t���[���̃|�C���^����root�t���[���̃|�C���^�擾
	Frame* get_root(Frame *f);
};