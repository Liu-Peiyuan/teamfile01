//! @file	resultscene.cpp
//! @author	�܂�
//! @date	2020-07-13
//! @brief	���U���g�V�[���̎���

// �C���N���[�h�t�@�C��
#include "main.h"
#include "result.h"
#include "savefile.h"
#include "resultscene.h"
#include "result_score.h"
#include "score.h"
#include "sound.h"

// �}�N����`

// ����������
void InitResultScene(void)
{
	// ���S�Ɣw�i�̏���������
	InitResult(0);

	//�Z�[�u�f�[�^���烉���L���O����������o��
	LoadData();

	// �X�R�A
	InitResult_Score(0);

	// �T�E���h�̊J�n
	PlaySound(SOUND_LABEL_BGM_sample002);
}

// �I������
void UninitResultScene(void)
{
	// ���S�Ɣw�i�̏I������
	UninitResult();

	UninitResult_Score();

	UninitScore();

	// �T�E���h�̏I������
	StopSound(SOUND_LABEL_BGM_sample002);

}

// �X�V����
void UpdateResultScene(void)
{
	// ���S�Ɣw�i�̍X�V����
	UpdateResult();

	// ���U���g�X�R�A�̍X�V����
	UpdateResult_Score();
}

// �`�揈��
void DrawResultScene(void)
{
	// ���S�Ɣw�i�̕`�揈��
	DrawResult();

	// ���U���g�X�R�A�̕`�揈��
	DrawResult_Score();
}