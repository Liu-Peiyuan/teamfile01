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
#include "life.h"
#include "score.h"
#include "timer.h"
#include "enemy.h"
#include "item.h"

// �}�N����`

// �V�[���̏���������
void InitGameScene(void)
{
	// �e�̏���������
	InitBullet(0);

	// �v���C���[�̏���������
	InitPlayer();

	// �G�l�~�[�̏���������
	InitEnemy(0);

	// �t�@�C���̓ǂݍ���
	OpenFile();

	// �}�b�v�̏���������
	InitMap();

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

	// �G�l�~�[�̏I������
	UninitEnemy();

	// �}�b�v�̏I������
	UninitMap();

	// ���C�t�̏I������
	UninitLife();

	//// �X�R�A�̏I������
	//UninitScore();

	// �^�C�}�[�̏I������
	UninitTimer();
}

// �V�[���̍X�V����
void UpdateGameScene(void)
{
	// �}�b�v�̍X�V����
	UpdateMap();

	// �v���C���[�̍X�V����
	UpdatePlayer();

	// �G�l�~�[�̍X�V����
	UpdateEnemy();

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

	// �X�R�A�̕`�揈��
	DrawScore();

	// �^�C�}�[�̕`�揈��
	DrawTimer();

	// ���C�t�̕`�揈��
	DrawLife();

	// �G�l�~�[�̕`�揈��
	DrawEnemy();
	
	// �v���C���[�̕`�揈��
	DrawPlayer();

	// �o���b�g�̕`�揈��
	DrawBullet();
}