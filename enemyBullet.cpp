//! @file	enemyBullet.cpp
//! @author	�܂�
//! @date	2020-08-04
//! @brief	�G�l�~�[�p�̒e�̎���

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "bullet.h"
#include "sound.h"
#include "playerTest.h"
#include "enemy.h"
#include "enemyBullet.h"
#include "map.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemyBullet( int no );				// �e�̒��_���쐬
void SetTextureEnemyBullet(int no, int cntPattern);		// �e�̒��_���W�̐ݒ�
void SetVertexEnemyBullet(int no);						// �e�̃e�N�X�`���̐ݒ�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9			g_pD3DTextureEnemyBullet = NULL;		// �e�N�X�`���ւ̃|���S��

ENEMYBULLET					g_enemyBullet[BULLET_MAX];			// �e�̍\����

//LPDIRECTSOUNDBUFFER8		g_pSE;							// SE�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemyBullet(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *bullet = &g_enemyBullet[0];		// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMY_BULLET,		// �t�@�C���̖��O
			&g_pD3DTextureEnemyBullet);		// �ǂݍ��ރ������̃|�C���^
		
		//g_pSE = LoadSound(SE_00);

	}

	// �o���b�g�̏���������
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		bullet->use = false;									// ���g�p�i���˂���Ă��Ȃ��e�j
		bullet->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// ���W�f�[�^��������
		bullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�f�[�^��������
		bullet->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		bullet->CountAnim = 0;									// �A�j���J�E���g��������
		bullet->speed = 2.0f;

		bullet->Texture = g_pD3DTextureEnemyBullet;					// �e�N�X�`�����
		MakeVertexEnemyBullet(i);									// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyBullet(void)
{
	ENEMYBULLET *bullet = g_enemyBullet;				// �o���b�g�̃|�C���^�[��������

	if (g_pD3DTextureEnemyBullet != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEnemyBullet->Release();
		g_pD3DTextureEnemyBullet = NULL;
	}

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		bullet->use = false;
	}
	//if (g_pSE != NULL)
	//{	// �e�N�X�`���̊J��
	//	g_pSE->Release();
	//	g_pSE = NULL;
	//}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyBullet(void)
{
	ENEMYBULLET *bullet = g_enemyBullet;				// �o���b�g�̃|�C���^�[��������
	PLAYER *player = GetPlayer();

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����  
			bullet->CountAnim++;
			if ((bullet->CountAnim % TIME_ANIMATION_BULLET) == 0)
			{
				// �p�^�[���̐؂�ւ�
				bullet->PatternAnim = (bullet->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY_BULLET;
			}
			SetTextureEnemyBullet(i, bullet->PatternAnim);	// �A�j���[�V������̃e�N�X�`���̐ݒ�

			// �o���b�g�̈ړ�����
			bullet->move = bullet->vec * bullet->speed;

			D3DXVec3Add(&bullet->pos, &bullet->pos, &bullet->move);

			// ��ʊO�܂Ői�񂾁H
			if (bullet->pos.x < 0.0f
				|| bullet->pos.x >SCREEN_WIDTH
				||bullet->pos.y < 0.0f
				||bullet->pos.y > SCREEN_HEIGHT)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				bullet->use = false;
			}

			SetVertexEnemyBullet(i);				// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *bullet = g_enemyBullet;				// �o���b�g�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, bullet->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BULLET, bullet->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

/**************************************************************************//**
	@brief		MakeVertexEnemyBullet
	@brief		�e�̒��_���W�쐬
	@param[in]	no		�e�̔ԍ�
	@return			S_OK	�����̐���
					E-FAIL	�����̎��s
*//***************************************************************************/
HRESULT MakeVertexEnemyBullet( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *bullet = &g_enemyBullet[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexEnemyBullet( no );

	// rhw�̐ݒ�
	bullet->vertexWk[0].rhw =
	bullet->vertexWk[1].rhw =
	bullet->vertexWk[2].rhw =
	bullet->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	bullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bullet->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY_BULLET, 0.0f);
	bullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY_BULLET);
	bullet->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY_BULLET, 1.0f/ TEXTURE_PATTERN_DIVIDE_Y_ENEMY_BULLET);

	return S_OK;
}

/**************************************************************************//**
	@brief		SetTextureEnemyBullet
	@brief		�e�̃e�N�X�`���̍��W�ݒ�
	@param[in]	no				�e�̔ԍ�
	@param[in]	cntPattern		�e�̃A�j���[�V�����J�E���g�p�^�[��
	@return		�Ȃ�
*//***************************************************************************/
void SetTextureEnemyBullet( int no, int cntPattern )
{
	ENEMYBULLET *bullet = &g_enemyBullet[no];			// �o���b�g�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY_BULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY_BULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY_BULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY_BULLET;
	
	bullet->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	bullet->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	bullet->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	bullet->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

/**************************************************************************//**
	@brief		SetVertexEnemyBullet
	@brief		�e�̒��_���W�ݒ�
	@param[in]	no		�e�̔ԍ�
	@return		�Ȃ�
*//***************************************************************************/
void SetVertexEnemyBullet( int no )
{
	ENEMYBULLET *bullet = &g_enemyBullet[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	bullet->vertexWk[0].vtx.x = bullet->pos.x - TEXTURE_BULLET_SIZE_X;
	bullet->vertexWk[0].vtx.y = bullet->pos.y - TEXTURE_BULLET_SIZE_Y;
	bullet->vertexWk[0].vtx.z = 0.0f;

	bullet->vertexWk[1].vtx.x = bullet->pos.x + TEXTURE_BULLET_SIZE_X;
	bullet->vertexWk[1].vtx.y = bullet->pos.y - TEXTURE_BULLET_SIZE_Y;
	bullet->vertexWk[1].vtx.z = 0.0f;

	bullet->vertexWk[2].vtx.x = bullet->pos.x - TEXTURE_BULLET_SIZE_X;
	bullet->vertexWk[2].vtx.y = bullet->pos.y + TEXTURE_BULLET_SIZE_Y;
	bullet->vertexWk[2].vtx.z = 0.0f;

	bullet->vertexWk[3].vtx.x = bullet->pos.x + TEXTURE_BULLET_SIZE_X;
	bullet->vertexWk[3].vtx.y = bullet->pos.y + TEXTURE_BULLET_SIZE_Y;
	bullet->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�̒e�̔��ːݒ�
//=============================================================================
void SetEnemyBullet(D3DXVECTOR3 enemyPos, D3DXVECTOR3 playerPos, int enemyType, int *countShot)
{
	ENEMYBULLET *bullet = &g_enemyBullet[0];			// �o���b�g�̃|�C���^�[��������
	D3DXVECTOR3 vec;									// ���x�N�g��

	for (int j = 0; j < ENEMY_MAX; j++)
	{
		// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
		for (int i = 0; i < BULLET_MAX; i++, bullet++)
		{
			D3DXVec3Subtract(&vec, &playerPos, &enemyPos);		// �G�l�~�[����v���C���[�Ɍ����Ẵx�N�g����vec�Ɋi�[
			D3DXVec3Normalize(&vec, &vec);						// vec�𐳋K��

 			if (bullet->use == false)
			{
				bullet->use = true;
				bullet->pos = enemyPos;
				D3DXVec3Scale(&vec, &vec, bullet->speed);	// ���x�����炩���ߑ�������ꍇ�̓X�s�[�h�𑫂��Ă����B�R�����g��
				*countShot = 0;								// �G�l�~�[�̃J�E���g�^�C�}�[��������
				bullet->vec = vec;							// vec�̒l���o���b�g�̃x�N�g���Ɋi�[
				return;
			}
		}
	}
}

//=============================================================================
// �{�X�G�l�~�[�̒e�̒��e�ݒ�
//=============================================================================
bool FallEnemyBullet(void)
{
	ENEMYBULLET *bullet = &g_enemyBullet[0];			// �o���b�g�̃|�C���^�[��������
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->use && bullet->pos.y >= (SCREEN_HEIGHT - (MAP_TEXTURE_SIZE_Y * 2)))
		{
			return true;
		}

	}
	return false;
}

//=============================================================================
// �e�̎擾�֐�
//=============================================================================
ENEMYBULLET *GetEnemyBullet(int no)
{
	return(&g_enemyBullet[no]);
}

