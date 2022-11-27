#pragma once
#include "Evaluator.h"
#include "ColorStorage.h"
class MidEvaluator : public Evaluator
{
	struct EdgeParameter
	{
		EdgeParameter& operator +=(const EdgeParameter& rhs)
		{
			stable += rhs.stable;
			wing += rhs.wing;
			mountain += rhs.mountain;
			Cput += rhs.Cput;

			return *this;
		}		

		//�m���
		short stable;

		//�E�C���O
		short wing;

		//�R
		short mountain;

		//C�ł�
		short Cput;
	};

	struct CornerParameter
	{
		//���ɂ����
		short corner;

		//X�ł�
		short Xput;
	};

	struct Weight
	{
		int mobility_w;
		int liberty_w;
		int stable_w;
		int wing_w;
		int Xput_w;
		int Cput_w;
	} EvalWeight;

	typedef ColorStorage<EdgeParameter> EdgeStorage;

	typedef ColorStorage<CornerParameter> CornerStorage;

	//�ÓI�����o�ϐ��͎��̂�ʂɐ錾����K�v������B
	static const int TABLE_SIZE = 6561;
	static EdgeStorage EdgeTable[TABLE_SIZE];
	static bool TableInit;

	void generateEdge(BoardStatus line[], unsigned index);
	EdgeParameter evalEdge(BoardStatus line[], BoardStatus color) const;
	CornerStorage evalCorner(Board& board);

	inline unsigned idxTop(Board&);
	inline unsigned idxButtom(Board&);
	inline unsigned idxRight(Board&);
	inline unsigned idxLeft(Board&);

	unsigned countLiberty(Board& board, BoardStatus color);

	unsigned idxLine(BoardStatus l[])
	{
		return 3 * (3 * (3 * (3 * (3 * (3 * (3 * (l[0] + 1) + l[1] + 1) + l[2] + 1) + l[3] + 1) + l[4] + 1) + l[5] + 1) + l[6] + 1) + l[7] + 1;
	}


public:
	MidEvaluator();

	// Evaluator ����Čp������܂���
	virtual int evaluate(Board& board) override;
};