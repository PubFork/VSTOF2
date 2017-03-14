#include "Frame.h"

void Frame::reset() {
	//�ϐ��̏�����
	root = nullptr; //root�t���[���̃|�C���^
	parent = nullptr; //�e�t���[���̃|�C���^
	index = 0;//���t���[�����̎��t���[���̊����ԍ�(=0,1,2,3,...)
	pos = { 0,0,0,0 }; //�t���[�����W
	size = { 0, 0 }; //�t���[���T�C�Y(���[�t���[���̂ݑ��)
	name = ""; //�t���[���̖���
	description = ""; //�t���[������UI�̉��
	mode = 0; //�q�t���[�����c����=0,������=1
	gap = 0; //�q�t���[���ԓ��m�̌���(px�P��)
	length = 0; //�S�t���[���������l�T�C�Y���̎��t���[���̃T�C�Y
	lock = 0; //�e�q�t���[���̒���(mode=0�Ȃ�c��,mode=1�Ȃ牡��)�̌Œ�on/off
	lock_length = 0; //�Œ�T�C�Y�̑S�q�t���[���ƑSgap�̘a(���[�t���[����0����)
	return;
}

void Frame::main_draw() {
	return;
}

void Frame::childs_draw() {
	for (int i = 0; i < childs.size(); i++) {
		childs[i]->draw();
	}
	return;
}

void Frame::when_create() {
	//���t���[���̃C���f�b�N�X�ԍ��擾
	get_index();
	//���t���[���̃c���[��root�t���[���擾
	get_root();
	//root�t���[���ȉ���length���ĎZ�o
	root->get_length();
	//root�t���[���ȉ��̃t���[���Ĕz�u
	root->resize();
	//WINDOW_INFO��e�t���[���Ɠ���̂��̂ɂ���
	if (parent != nullptr) {
		win = parent->win;
	}
}

void Frame::set_win_info(WINDOW_INFO *set_win) {
	if ((root->win != set_win) && (this != root)) {
		root->set_win_info(set_win);
	}
	else {
		win = set_win;
		for (int i = 0; i < childs.size(); i++) {
			childs[i]->set_win_info(set_win);
		}
	}
}

void Frame::resize(){
	size.x = pos.right - pos.left;
	size.y = pos.bottom - pos.top;
	if (childs.size() != 0) {
		if (mode) {
			//�����т̏ꍇ
			//�q�t���[�������[�v
			for (int i = 0; i < childs.size(); i++) {
				//i�ڂ̎q�t���[���ʒu�Z�o
				//�㉺�ʒu
				childs[i]->pos.top = pos.top + gap;
				childs[i]->pos.bottom = pos.bottom - gap;
				//���ʒu
				if (i == 0) {
					childs[i]->pos.left = pos.left + gap;
				}
				else {
					childs[i]->pos.left = childs[i - 1]->pos.right + gap;
				}
				//�E�ʒu
				if (childs[i]->lock) {
					//�Œ�T�C�Y�t���[���̏ꍇ�͊����ϊ��s�v
					childs[i]->pos.right =
						childs[i]->pos.left +
						childs[i]->length;
				}
				else {
					//��Œ�T�C�Y�t���[���̏ꍇ�͊����v�Z
					childs[i]->pos.right =
						childs[i]->pos.left +
						Utility::Proportion(
							childs[i]->length,
							0,
							length - lock_length,
							0,
							size.x - lock_length
						);
				}
				//�q�t���[���ʒu�ݒ�
				childs[i]->resize();
			}
		}
		else {
			//�c���т̏ꍇ
			//�q�t���[�������[�v
			for (int i = 0; i < childs.size(); i++) {
				//i�ڂ̎q�t���[���ʒu�Z�o
				//���E�ʒu
				childs[i]->pos.left = pos.left + gap;
				childs[i]->pos.right = pos.right - gap;
				//��ʒu
				if (i == 0) {
					childs[i]->pos.top = pos.top + gap;
				}
				else {
					childs[i]->pos.top = childs[i - 1]->pos.bottom + gap;
				}
				//���ʒu
				if (childs[i]->lock) {
					//�Œ�T�C�Y�t���[��or�X�N���[���t���[���̏ꍇ�͊����ϊ��s�v
					childs[i]->pos.bottom =
						childs[i]->pos.top +
						childs[i]->length;
				}
				else {
					//��Œ�T�C�Y�t���[���̏ꍇ�͊����v�Z
					childs[i]->pos.bottom =
						childs[i]->pos.top +
						Utility::Proportion(
							childs[i]->length,
							0,
							length - lock_length,
							0,
							size.y - lock_length
						);
				}
				//�q�t���[���ʒu�ݒ�
				childs[i]->resize();
			}
		}
	}
	return;
}

void Frame::draw() {
	main_draw();
	childs_draw();
	return;
}

void Frame::get_length() {
	if (childs.size() != 0) {
		length = 0; //�S�q�t���[���ƑSgap�̘a
		lock_length = 0; //�Œ�T�C�Y�̑S�q�t���[���ƑSgap�̘a(���[�t���[����0����)
		//�q�t���[���̌������[�v
		for (int i = 0; i < childs.size(); i++) {
			//�q�t���[�����q�t���[���������Ă����ꍇ�A�ċA
			if (childs.size() != 0) {
				childs[i]->get_length();
			}
			//�e�t���[���̒����Ɏq�t���[���̒����𑫂��Ă���
			length += childs[i]->length;
			//�����q�t���[�������[�t���[���ŁA�Œ�T�C�Y�t���[���̏ꍇ
			if (childs[i]->lock) {
				lock_length += childs[i]->length;
			}
		}
		//�Sgap�𑫂�
		length += gap * (childs.size() + 1);
		lock_length += gap * (childs.size() + 1);
	}
	return;
}

void Frame::get_root() {
	if (parent != nullptr) {
		parent->get_root();
		root = parent->root;
	}
	else {
		root = this;
	}
return;
}

void Frame::get_index() {
	if (parent != nullptr) {
		index = parent->childs.size() - 1;
	}
	else {
		index = 0;
	}
}

Frame::Frame(Frame *set_parent = nullptr, int set_length = 0, bool set_lock = 0, std::string set_name = "", std::string set_description = "") {
	reset();
	parent = set_parent;
	length = set_length;
	lock = set_lock;
	name = set_name;
	description = set_description;
	when_create();
}
Frame::Frame(bool set_mode, Frame *set_parent, std::string set_name = "", std::string set_description = "") {
	reset();
	mode = set_mode;
	parent = set_parent;
	name = set_name;
	description = set_description;
	when_create();
}