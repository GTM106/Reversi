#pragma once
#include "Board.h"

//�v���C���[�A�R���s���[�^�̃^�[�������̎�������������C���^�[�t�F�[�X�̂悤�Ȃ���
class ITurn
{
public:
	virtual ~ITurn() {};
	virtual	bool turn(Board& board) = 0;
};