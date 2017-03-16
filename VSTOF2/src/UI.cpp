#include "UI.h"

Graph::Graph(graph set_g, int set_length, Frame *set_parent = nullptr, bool set_lock = 0, bool set_fill_wave = 0, std::string set_name = "", std::string set_description = "")
	: Frame(set_parent, set_length, set_lock, set_name, set_description)
{
	g = set_g;
	fill_wave = set_fill_wave;
}

void Graph::main_draw() {
	//�`��������̂��߁A�s�N�Z���̐��ɍ��킹�ĕ`��
	int index = 0; //�z�񂩂�l���Q�Ƃ���Ƃ��̃C���f�b�N�X
	float percentage = 0.0f;
	float height; //���`�悷��g�̍���
	float b_height; //�O�t���[����height
	float zero = Utility::Proportion(0.0f, g.val_min, g.val_max, (float)(pos.bottom), (float)(pos.top)); //�O���ty���W��0�̂Ƃ��̃t���[��y���W
	for (int i = 0; i < size.x; i++) {
		percentage = Utility::Proportion((float)i, 0.0f, (float)size.x, (float)g.start_index, (float)g.end_index); //�ꎞ���
		index = (int)percentage; //�g�`�z��̃C���f�b�N�X�Z�o
		percentage = percentage - (float)index; //int,float�̐�����K�����̐��ɂȂ�
												//(�O�̈�)index+1>=num_sample�ɂȂ����烋�[�v�E�o
		if (index + 1 >= g.num_sample) {
			break;
		}
		//���`�悷��g�̍���
		height =
			Utility::Proportion(g.samples[index], g.val_min, g.val_max, (float)(pos.bottom), (float)(pos.top)) * (1.0f - percentage) +
			Utility::Proportion(g.samples[index + 1], g.val_min, g.val_max, (float)(pos.bottom), (float)(pos.top)) * (percentage);
		//�O���t�`��
		if (i > 0) {
			ofSetColor(255, 255, 255, 255);
			ofLine(
				pos.left + i - 1,
				b_height,
				pos.left + i,
				height
			);
		}
		//�h��Ԃ�
		if (fill_wave) {
			if ((i / 10) % 2 == 0) {
				ofSetColor(255, 255, 255, 255);
				ofLine(
					pos.left + i,
					zero,
					pos.left + i,
					height
				);
			}
		}
		b_height = height; //�O�t���[���̂Ƃ���height�擾�p
	}
	//���t���[���ȉ��̂��ׂĂ̎q�t���[���`��
	childs_draw();
}