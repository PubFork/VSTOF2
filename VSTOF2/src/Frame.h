#pragma once

#include "define.h"
#include "win_info.h"

//�t���[�����N���X
class Frame {
protected:
	//�S�ϐ�������
	void reset();
	//�q�t���[�����玩�t���[����length��lock_length���Z�o(�q�t���[�����ǉ�����邽�т�root�t���[���̂��̊֐����Ă�)
	void get_length();
	//root�t���[���̃|�C���^�擾
	void get_root();
	//���t���[���̃C���f�b�N�X�ԍ��擾
	void get_index();
	//���t���[���̒��ɕ`�悷��֐�
	virtual void main_draw();
	//���t���[���ȉ��̑S�q�t���[����draw�֐����s
	void childs_draw();
public:
	//�ϐ�
	Frame *root; //root�t���[���̃|�C���^
	Frame *parent; //�e�t���[���̃|�C���^
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
	WINDOW_INFO *win;

	//�֐��錾
	//�ϐ��̑��
	virtual void set_data();
	//�t���[���ǉ������s�֐�
	virtual void when_create();
	//���t���[���ȉ��̑S�t���[���`��
	void draw();
	//���t���[���̃T�C�Y�ɍ��킹�Ďq�t���[���T�C�Y�X�V
	void resize();
	//�R���X�g���N�^
	Frame(Frame *set_parent, int set_length, bool set_lock);
};

//�t���[������N���X
class FrameManagement {
private:
	Frame *parent;
public:
	//�֐��錾
	FrameManagement();
	//���̊֐��̎��s�ȍ~�͒ǉ�����t���[���̐e�t���[������Ɉ����̃t���[���ɂȂ�
	void set_parent(Frame *f);
	//�t���[���̐V�K�쐬
	Frame* create(int length, bool lock);
	Frame* create();
	Frame* create(std::string name, int length, bool lock);
};