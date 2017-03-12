#include "Frame.h"

void Frame::childs_draw() {
	for (int i = 0; i < childs.size(); i++) {
		childs[i]->draw();
	}
	return;
}

void Frame::draw() {
	childs_draw();
	return;
}

Frame::Frame() {
	//�ϐ��̏�����
	parent = nullptr; //�e�t���[���̃|�C���^
	num_child = 0; //�q�t���[���̐�
	index = 0;//���t���[�����̎��t���[���̊����ԍ�(=0,1,2,3,...)
	pos = { 0,0,0,0 }; //�t���[�����W
	size = {0, 0}; //�t���[���T�C�Y(���[�t���[���̂ݑ��)
	name = ""; //�t���[���̖���
	description = ""; //�t���[������UI�̉��
	mode = 0; //�q�t���[�����c����=0,������=1
	gap = 0; //�q�t���[���ԓ��m�̌���(px�P��)
	length = 0; //�S�t���[���������l�T�C�Y���̎��t���[���̃T�C�Y
	lock = 0; //�e�q�t���[���̒���(mode=0�Ȃ�c��,mode=1�Ȃ牡��)�̌Œ�on/off
	lock_length = 0; //�Œ�T�C�Y�̑S�q�t���[���ƑSgap�̘a(���[�t���[����0����)
}

void FrameManagement::add(Frame *parent, Frame *self, std::string name, int length, bool lock) {
	self->parent = parent; //�e�t���[���̃|�C���^
	self->num_child = 0; //�q�t���[���̐�������
	self->pos.left = 0; //�t���[�������W
	self->pos.top = 0; //�t���[������W
	self->pos.right = 0; //�t���[���E���W
	self->pos.bottom = 0; //�t���[�������W
	self->size = { 0,0 }; //�t���[���T�C�Y
	self->name = name; //�t���[���̖���
	self->description = ""; //����̓I�v�V�����Ȃ̂łƂ肠�������L��
	self->mode = 0; //�q�t���[�����c����=0,������=1
	self->gap = 0; //�q�t���[���ԓ��m�̌���(px�P��)
	self->length = length; //�S�t���[���������l�T�C�Y���̎��t���[���̃T�C�Y
	self->lock = lock; //���݂̎��t���[���̒���(mode = 0�Ȃ�c��, mode = 1�Ȃ牡��)�̌Œ��on/off
	self->index = 0;
	self->lock_length = 0; //�Œ�T�C�Y�̑S�q�t���[���ƑSgap�̘a(���[�t���[����0����)
						   //�e�t���[�������w��̏ꍇ�A�ȉ��̏������Ȃ�
	if (parent == nullptr) {
		return;
	}
	self->parent->childs.push_back(self); //�e�t���[���Ɏ��t���[���ǉ��o�^
	self->index = self->parent->num_child;//���t���[�����̎��t���[���̊����ԍ�(=0,1,2,3,...)
	self->parent->num_child += 1; //�e�t���[�����X�V
	return;
}

void FrameManagement::set_parent(Frame *self, bool mode, int gap) {
	self->mode = mode; //�q�t���[���������тȂ�0,�c���тȂ�1
	self->gap = gap; //���t���[���Ԃ̌��ԃT�C�Y(px�P��)
	return;
}

void FrameManagement::set_description(Frame *self, std::string description) {
	self->description = description;
}

void FrameManagement::get_length(Frame *f) {
	if (f->num_child != 0) {
		f->length = 0; //�S�q�t���[���ƑSgap�̘a
		f->lock_length = 0; //�Œ�T�C�Y�̑S�q�t���[���ƑSgap�̘a(���[�t���[����0����)
		//�q�t���[���̌������[�v
		for (int i = 0; i < f->num_child; i++) {
			//�q�t���[�����q�t���[���������Ă����ꍇ�A�ċA
			if (f->childs[i]->num_child != 0) {
				get_length(f->childs[i]);
			}
			//�e�t���[���̒����Ɏq�t���[���̒����𑫂��Ă���
			f->length += f->childs[i]->length;
			//�����q�t���[�������[�t���[���ŁA�Œ�T�C�Y�t���[���̏ꍇ
			if (f->childs[i]->lock) {
				f->lock_length += f->childs[i]->length;
			}
		}
		//�Sgap�𑫂�
		f->length += f->gap * (f->num_child + 1);
		f->lock_length += f->gap * (f->num_child + 1);
	}
	return;
}

void FrameManagement::sub_resize(Frame *f, RECT pos) {
	f->size.x = pos.right - pos.left;
	f->size.y = pos.bottom - pos.top;
	f->pos = pos;
	//�q�t���[��������΁A�q�t���[���̔z�u�����Ă���
	//length��size�̃T�C�Y�ύX
	if (f->num_child != 0) {
		if (f->mode) {
			//�����т̏ꍇ
			//�q�t���[�������[�v
			for (int i = 0; i < f->num_child; i++) {
				//i�ڂ̎q�t���[���ʒu�ϐ�������
				RECT child_pos;
				//i�ڂ̎q�t���[���ʒu�Z�o
				//�㉺�ʒu
				child_pos.top = f->pos.top + f->gap;
				child_pos.bottom = f->pos.bottom - f->gap;
				//���ʒu
				if (i == 0) {
					child_pos.left = f->pos.left + f->gap;
				}
				else {
					child_pos.left = f->childs[i - 1]->pos.right + f->gap;
				}
				//�E�ʒu
				if (f->childs[i]->lock) {
					//�Œ�T�C�Y�t���[���̏ꍇ�͊����ϊ��s�v
					child_pos.right =
						child_pos.left +
						f->childs[i]->length;
				}
				else {
					//��Œ�T�C�Y�t���[���̏ꍇ�͊����v�Z
					child_pos.right =
						child_pos.left +
						Utility::Proportion(
							f->childs[i]->length,
							0,
							f->length - f->lock_length,
							0,
							f->size.x - f->lock_length
						);
				}
				//�q�t���[���ʒu�ݒ�
				resize(f->childs[i], child_pos);
			}
		}
		else {
			//�c���т̏ꍇ
			//�q�t���[�������[�v
			for (int i = 0; i < f->num_child; i++) {
				//i�ڂ̎q�t���[���ʒu�ϐ�������
				RECT child_pos;
				//i�ڂ̎q�t���[���ʒu�Z�o
				//���E�ʒu
				child_pos.left = f->pos.left + f->gap;
				child_pos.right = f->pos.right - f->gap;
				//��ʒu
				if (i == 0) {
					child_pos.top = f->pos.top + f->gap;
				}
				else {
					child_pos.top = f->childs[i - 1]->pos.bottom + f->gap;
				}
				//���ʒu
				if (f->childs[i]->lock) {
					//�Œ�T�C�Y�t���[��or�X�N���[���t���[���̏ꍇ�͊����ϊ��s�v
					child_pos.bottom =
						child_pos.top +
						f->childs[i]->length;
				}
				else {
					//��Œ�T�C�Y�t���[���̏ꍇ�͊����v�Z
					child_pos.bottom =
						child_pos.top +
						Utility::Proportion(
							f->childs[i]->length,
							0,
							f->length - f->lock_length,
							0,
							f->size.y - f->lock_length
						);
				}
				//�q�t���[���ʒu�ݒ�
				resize(f->childs[i], child_pos);
			}
		}
	}
	return;
}

void FrameManagement::resize(Frame *f, RECT pos) {
	get_length(f);
	sub_resize(f, pos);
}

Frame* FrameManagement::get_root(Frame *f) {
	Frame *b_f; //�t���[���|�C���^�ꎞ����p�ϐ�
	b_f = f;
	while (true) {
		if (b_f->parent != nullptr) {
			b_f = b_f->parent;
		}
		else {
			return b_f;
		}
	}
}