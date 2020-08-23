//! @file	spear.cpp
//! @author	kitade mayumi
//! @date	2020-08-20
//! @brief	�j�̎���

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "spear.h"
#include "map.h"
#include "checkhit.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_GAME_SPEAR		_T("data/TEXTURE/spears/spear01.png")			// �j�̉摜
#define POP_COUNT_SPEAR	(60 * 3)

// �j�̌����Ă������
enum SPEAR_TYPE
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexSpear( int no );						// �j�̒��_���쐬
void SetTextureSpear(int no, int cntPattern, int direction);// �j�̒��_���W�̐ݒ�
void SetVertexSpear(int no);							// �j�̃e�N�X�`��z�̐ݒ�
void MovingDirectionSpear(int no, D3DXVECTOR3 *vec);	// �j�̈ړ�����
void SetSpear(void);
void MoveSpear(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureSpear = NULL;		// �e�N�X�`���ւ̃|���S��

static SPEAR					g_spear[SPEAR_MAX];			// �j�̍\����
//=============================================================================
// ����������
//=============================================================================
HRESULT InitSpear(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SPEAR *spear = &g_spear[0];		// �j�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_SPEAR,			// �t�@�C���̖��O
			&g_pD3DTextureSpear);			// �ǂݍ��ރ������̃|�C���^
		
	}

	// �o���b�g�̏���������
	for (int i = 0; i < SPEAR_MAX; i++, spear++)
	{
		spear->use = false;									// ���g�p�i���˂���Ă��Ȃ��e�j
		spear->downUse = false;
		spear->popUse = false;
		spear->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���W�f�[�^��������
		spear->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�f�[�^��������
		spear->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ��ʂ̃f�[�^��������
		spear->vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �x�N�g���̏�����

		spear->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		spear->CountAnim = 0;									// �A�j���J�E���g��������
		spear->speed = 0.2f;									// �ړ��X�s�[�h
		spear->direction = LEFT;
		spear->MoveCnt = 0;
		spear->PopCnt = 0;

		spear->Texture = g_pD3DTextureSpear;				// �e�N�X�`�����
		MakeVertexSpear(i);									// ���_���̍쐬
	}

	SetSpear();

	for (int i = 0; i < SPEAR_MAX; i++, spear++)
	{
		MovingDirectionSpear(i, &spear[i].vec);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSpear(void)
{
	SPEAR *spear = g_spear;				// �j�̃|�C���^�[��������

	if (g_pD3DTextureSpear != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureSpear->Release();
		g_pD3DTextureSpear = NULL;
	}
	for (int i = 0; i < SPEAR_MAX; i++, spear++)
	{
		spear->use = false;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSpear(void)
{
	SPEAR *spear = g_spear;				// �j�̃|�C���^�[��������
	int scene = GetScene();

	for (int i = 0; i < SPEAR_MAX; i++, spear++)
	{
		if (spear->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����  
			spear->CountAnim++;
			if ((spear->CountAnim % TIME_ANIMATION_SPEAR) == 0)
			{
				// �p�^�[���̐؂�ւ�
				spear->PatternAnim = (spear->PatternAnim + 1) % ANIM_PATTERN_NUM_SPEAR;
			}

			MoveSpear(i);
			// ��ʊO�܂Ői�񂾁H
			if (spear->pos.x < 0.0f
				|| spear->pos.x >=SCREEN_WIDTH)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				spear->use = false;
			}

			SetTextureSpear(i, spear->PatternAnim, spear->direction);	// �A�j���[�V������̃e�N�X�`���̐ݒ�

			SetVertexSpear(i);							// �ړ���̍��W�Œ��_��ݒ�
		}

	}
}

//=============================================================================
// �j�̈ړ�����
//=============================================================================
void MoveSpear(int no)
{
	SPEAR *spear = &g_spear[no];		// �j�̃|�C���^�[��������

	if (!spear->downUse && !spear->popUse)
	{
		spear->move += spear->vec * spear->speed;
		spear->MoveCnt++;

		if (spear->MoveCnt == MAP_TEXTURE_SIZE_X)
		{
			spear->MoveCnt = 0;
			spear->downUse = true;
			spear->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ��ʂ̃f�[�^��������
		}
	}

	else if(spear->downUse && !spear->popUse)
	{
		spear->move += spear->vec * spear->speed * -1;
		spear->MoveCnt++;

		if (spear->MoveCnt == MAP_TEXTURE_SIZE_X)
		{
			spear->MoveCnt = 0;
			spear->popUse = true;
			spear->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ��ʂ̃f�[�^��������
		}

	}

	if (spear->popUse)
	{
		spear->PopCnt++;

		if (spear->PopCnt == POP_COUNT_SPEAR)
		{
			spear->downUse = false;
			spear->popUse = false;
			spear->PopCnt = 0;
		}
	}


	D3DXVec3Add(&spear->pos, &spear->pos, &spear->move);

}

//=============================================================================
// �ړ��x�N�g����������
//=============================================================================
void MovingDirectionSpear(int no, D3DXVECTOR3 *vec)
{
	SPEAR *spear = &g_spear[no];		// �j�̃|�C���^�[��������
	D3DXVECTOR3 vec2;
	switch (spear->direction)
	{
	case UP:
		vec2 = D3DXVECTOR3(spear->pos.x, 0.0f, 0.0f);
		D3DXVec3Subtract(&spear->vec, &vec2, &spear->pos);
		break;

	case DOWN:
		vec2 = D3DXVECTOR3(spear->pos.x, SCREEN_HEIGHT, 0.0f);
		D3DXVec3Subtract(&spear->vec, &vec2, &spear->pos);
		break;

	case RIGHT:
		vec2 = D3DXVECTOR3(SCREEN_WIDTH, spear->pos.y, 0.0f);
		D3DXVec3Subtract(&spear->vec, &vec2, &spear->pos);
		break;

	case LEFT:
		vec2 = D3DXVECTOR3(0.0f, spear->pos.y, 0.0f);
		D3DXVec3Subtract(&spear->vec, &vec2, &spear->pos);
		break;
	default:
		break;
	}
	D3DXVec3Normalize(&spear->vec, &spear->vec);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSpear(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SPEAR *spear = &g_spear[0];			// �j�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < SPEAR_MAX; i++, spear++)
	{
		if (spear->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, spear->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_SPEAR, spear->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

/**************************************************************************//**
	@brief		MakeVertexSpear
	@brief		�j�̒��_���W�쐬
	@param[in]	no		�j�̔ԍ�
	@return			S_OK	�����̐���
					E-FAIL	�����̎��s
*//***************************************************************************/
HRESULT MakeVertexSpear( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SPEAR *spear = &g_spear[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexSpear( no );

	// rhw�̐ݒ�
	spear->vertexWk[0].rhw =
	spear->vertexWk[1].rhw =
	spear->vertexWk[2].rhw =
	spear->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	spear->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	spear->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	spear->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	spear->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	spear->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	spear->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_SPEAR, 0.0f);
	spear->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_SPEAR);
	spear->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_SPEAR, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_SPEAR);

	return S_OK;
}

/**************************************************************************//**
	@brief		SetTextureSpear
	@brief		�j�̃e�N�X�`���̍��W�ݒ�
	@param[in]	no				�j�̔ԍ�
	@param[in]	cntPattern		�j�̃A�j���[�V�����J�E���g�p�^�[��
	@param[in]	direction		�j�̌���
	@return		�Ȃ�
*//***************************************************************************/
void SetTextureSpear( int no, int cntPattern, int direction)
{
	SPEAR *spear = &g_spear[no];			// �o���b�g�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_SPEAR;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_SPEAR;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_SPEAR;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_SPEAR;
	
	switch (direction)
	{
	case UP:
		spear->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		spear->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		spear->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		spear->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
		break;

	case DOWN:
		spear->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		spear->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		spear->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		spear->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
		break;

	case RIGHT:
		spear->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		spear->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		spear->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		spear->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
		break;

	case LEFT:
		spear->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		spear->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		spear->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		spear->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
		break;
	}
}

/**************************************************************************//**
	@brief		SetVertexSpear
	@brief		�j�̒��_���W�ݒ�
	@param[in]	no		�j�̔ԍ�
	@return		�Ȃ�
*//***************************************************************************/
void SetVertexSpear( int no )
{
	SPEAR *spear = &g_spear[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	spear->vertexWk[0].vtx.x = spear->pos.x - TEXTURE_SPEAR_SIZE_X;
	spear->vertexWk[0].vtx.y = spear->pos.y - TEXTURE_SPEAR_SIZE_Y;
	spear->vertexWk[0].vtx.z = 0.0f;

	spear->vertexWk[1].vtx.x = spear->pos.x + TEXTURE_SPEAR_SIZE_X;
	spear->vertexWk[1].vtx.y = spear->pos.y - TEXTURE_SPEAR_SIZE_Y;
	spear->vertexWk[1].vtx.z = 0.0f;

	spear->vertexWk[2].vtx.x = spear->pos.x - TEXTURE_SPEAR_SIZE_X;
	spear->vertexWk[2].vtx.y = spear->pos.y + TEXTURE_SPEAR_SIZE_Y;
	spear->vertexWk[2].vtx.z = 0.0f;

	spear->vertexWk[3].vtx.x = spear->pos.x + TEXTURE_SPEAR_SIZE_X;
	spear->vertexWk[3].vtx.y = spear->pos.y + TEXTURE_SPEAR_SIZE_Y;
	spear->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �j�̔��ːݒ�
//=============================================================================
void SetSpear(void)
{
	SPEAR *spear = &g_spear[0];			// �j�̃|�C���^�[��������
	MAP *map = GetMapData();			// �}�b�v�̃|�C���^�[���擾

	for (int p = 0; p < MAP_MAXDATA * SIZE_X * SIZE_Y; p++, map++)
	{
		// �j�̎�ނɉ����Ĕ�΂�������ς��Ă݂鏈��
		switch (map->type)
		{
		case BLOCK7:
			spear->direction = UP;
			spear->pos = map->pos;
			spear->pos.y += MAP_TEXTURE_SIZE_Y * 2.0f;
			break;

		case BLOCK8:
			spear->direction = DOWN;
			spear->pos = map->pos;
			spear->pos.y -= MAP_TEXTURE_SIZE_Y * 2.0f;
			break;

		case BLOCK9:
			spear->direction = RIGHT;
			spear->pos = map->pos;
			spear->pos.x -= MAP_TEXTURE_SIZE_X * 2.0f;
			break;

		case BLOCK11:
			spear->direction = LEFT;
			spear->pos = map->pos;
			spear->pos.x += MAP_TEXTURE_SIZE_X * 2.0f;
			break;

		}

		if (map->type == BLOCK7
			|| map->type == BLOCK8
			|| map->type == BLOCK9
			|| map->type == BLOCK11)
		{
			spear->use = true;
			spear++;
		}
	}
}

//=============================================================================
// �j�̎擾�֐�
//=============================================================================
SPEAR *GetSpear(int no)
{
	return(&g_spear[no]);
}

