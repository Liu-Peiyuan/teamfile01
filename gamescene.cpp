//! @file	gamescene.cpp
//! @author	�܂�
//! @date	2020-07-13
//! @brief	�Q�[���V�[���̎���

// �C���N���[�h�t�@�C��
#include "main.h"
#include "bullet.h"
#include "playerTest.h"
#include "file.h"
#include "map01.h"
#include "map02.h"
#include "life.h"
#include "score.h"
#include "timer.h"

// �}�N����`

// �V�[���̏���������
void InitGameScene(void)
{
	// �e�̏���������
	InitBullet(0);

	// �v���C���[�̏���������
	InitPlayer();

	// �t�@�C���̓ǂݍ���
	InitFile();

	// �t�@�C��2�̓ǂݍ���
	InitFile2();

	// �}�b�v�̏���������
	InitMap();

	// �}�b�v2�̏���������
	InitMap2();

	// ���C�t�̏���������
	InitLife();

	// �X�R�A�̏���������
	InitScore();

	// �^�C�}�[�̏���������
	InitTimer();
}

// �V�[���̏I������
void UninitGameScene(void)
{
	// �e�̏I������
	UninitBullet();

	// �v���C���[�̏I������
	UninitPlayer();

	// �}�b�v2�̏I������
	UninitMap2();

	// �}�b�v�̏I������
	UninitMap();

	// ���C�t�̏I������
	UninitLife();

	// �X�R�A�̏I������
	UninitScore();

	// �^�C�}�[�̏I������
	UninitTimer();
}

// �V�[���̍X�V����
void UpdateGameScene(void)
{
	// �}�b�v�̍X�V����
	UpdateMap();

	// �}�b�v2�̍X�V����
	UpdateMap2();

	// �v���C���[�̍X�V����
	UpdatePlayer();

	// �e�̍X�V����
	UpdateBullet();

	// ���C�t�̍X�V����
	UpdateLife();

	// �^�C�}�[�̍X�V����
	UpdateTimer();

	// �X�R�A�̍X�V����
	UpdateScore();
}

// �V�[���̕`�揈��
void DrawGameScene(void)
{
	// �}�b�v�̕`�揈��
	DrawMap();

	// �}�b�v2�̕`�揈��
	DrawMap2();

	// �X�R�A�̕`�揈��
	DrawScore();

	// �^�C�}�[�̕`�揈��
	DrawTimer();

	// ���C�t�̕`�揈��
	DrawLife();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// �o���b�g�̕`�揈��
	DrawBullet();
}