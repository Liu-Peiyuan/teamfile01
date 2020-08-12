//! @file	killer.cpp
//! @author	kitade mayumi
//! @date	2020-08-07
//! @brief	�L���[�̎���

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "killer.h"
#include "playerTest.h"
#include "map.h"
#include "checkhit.h"
#include "scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_GAME_KILLER		_T("data/TEXTURE/EnemyChara/killer01.png")			// �摜
#define POP_COUNT_KILLER	(60 * 4)

// �L���[�̃^�C�v�̗񋓌^
enum KILLER_TYPE
{
	TRACKER,
	VECTOR,
	KILLER_TYPE_MAX
};

// �L���[�̌����Ă������
enum KILLER_DIRECTION
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexKiller( int no );					// �L���[�̒��_���쐬
void SetTextureKiller(int no, int cntPattern, int direction);// �L���[�̒��_���W�̐ݒ�
void SetVertexKiller(int no);						// �L���[�̃e�N�X�`��z�̐ݒ�
void MovingKiller(void);							// �L���[�̈ړ�����
void SetKiller(void);
void DirectionKiller(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureKiller = NULL;		// �e�N�X�`���ւ̃|���S��

KILLER					g_killer[KILLER_MAX];			// �L���[�̍\����
static int g_count;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitKiller(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	KILLER *killer = &g_killer[0];		// �L���[�̃|�C���^�[��������
	g_count = 0;

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_KILLER,			// �t�@�C���̖��O
			&g_pD3DTextureKiller);			// �ǂݍ��ރ������̃|�C���^
		
	}

	// �o���b�g�̏���������
	for (int i = 0; i < KILLER_MAX; i++, killer++)
	{
		killer->use = false;									// ���g�p�i���˂���Ă��Ȃ��e�j
		killer->dead = false;
		killer->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���W�f�[�^��������
		killer->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�f�[�^��������
		killer->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ��ʂ̃f�[�^��������
		killer->vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �x�N�g���̏�����

		killer->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		killer->CountAnim = 0;									// �A�j���J�E���g��������
		killer->speed = 2.0f;									// �ړ��X�s�[�h
		killer->type = TRACKER;
		killer->vecUse = false;
		killer->popCnt = 0;
		killer->direction = LEFT;

		killer->Texture = g_pD3DTextureKiller;					// �e�N�X�`�����
		MakeVertexKiller(i);									// ���_���̍쐬
	}

	SetKiller();

	g_count++;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitKiller(void)
{
	KILLER *killer = g_killer;				// �L���[�̃|�C���^�[��������

	if (g_pD3DTextureKiller != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureKiller->Release();
		g_pD3DTextureKiller = NULL;
	}
	for (int i = 0; i < KILLER_MAX; i++, killer++)
	{
		killer->use = false;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateKiller(void)
{
	KILLER *killer = g_killer;				// �L���[�̃|�C���^�[��������
	int scene = GetScene();

	for (int i = 0; i < KILLER_MAX; i++, killer++)
	{
		if (killer->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����  
			killer->CountAnim++;
			if ((killer->CountAnim % TIME_ANIMATION_KILLER) == 0)
			{
				// �p�^�[���̐؂�ւ�
				killer->PatternAnim = (killer->PatternAnim + 1) % ANIM_PATTERN_NUM_KILLER;
			}
			// �L���[�̈ړ�����
			MovingKiller();

			killer->move = killer->vec * killer->speed;

			D3DXVec3Add(&killer->pos, &killer->pos, &killer->move);

			DirectionKiller(i);

			// ��ʊO�܂Ői�񂾁H
			if (killer->pos.x < 0.0f
				|| killer->pos.x >=SCREEN_WIDTH
				|| killer->pos.y <0.0f
				|| killer->pos.y >=SCREEN_HEIGHT)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				killer->use = false;
			}
			else
			{
				if (scene == SCENE_GAME)
				{
					if (!killer->use && killer->dead)
					{
						// �ă|�b�v�܂ł̃J�E���g
						killer->popCnt++;
					}

					// �ă|�b�v�܂ł̃J�E���g�����𖞂������������x�Z�b�g
					if (killer->popCnt == POP_COUNT_KILLER)
					{
						SetKiller();
					}
				}
			}
			SetTextureKiller(i, killer->PatternAnim, killer->direction);	// �A�j���[�V������̃e�N�X�`���̐ݒ�

			SetVertexKiller(i);							// �ړ���̍��W�Œ��_��ݒ�
		}

	}
	CheckHitKiller();
}

//=============================================================================
// �ړ�����
//=============================================================================
void MovingKiller(void)
{
	KILLER *killer = &g_killer[0];			// �L���[�̃|�C���^�[��������
	PLAYER *player = GetPlayer();			// �v���C���[�̃|�C���^���擾
	D3DXVECTOR3 vec, vec2;					// ���̃x�N�g���̍쐬

	for (int i = 0; i < KILLER_MAX; i++, killer++)
	{
		if (killer->type == TRACKER)
		{
			D3DXVec3Subtract(&vec, &player->pos, &killer->pos);
			D3DXVec3Normalize(&vec, &vec);
			D3DXVec3Scale(&vec, &vec, killer->speed);
			//// ��]����
			//D3DXVECTOR3 pos = GetPlayer()->pos - killer->pos;
			//killer->rot.z = atan2f(pos.y, pos.x) - D3DX_PI / 2;
			killer->vec = vec;
		}

		else if(killer->type == VECTOR)
		{
			if (!killer->vecUse)
			{
				D3DXVec3Subtract(&vec2, &player->pos, &killer->pos);
				D3DXVec3Normalize(&vec2, &vec2);
				D3DXVec3Scale(&vec2, &vec2, killer->speed * 3.0f);
				killer->vec = vec2;
				killer->vecUse = true;
			}
		}
	}
}

//=============================================================================
// �����Ă�������̐ݒ�
//=============================================================================
void DirectionKiller(int no)
{
	KILLER *killer = &g_killer[no];			// �L���[�̃|�C���^�[��������
	PLAYER *player = GetPlayer();

	// �L���[�̌����Ă������ = �L���[��X����Y���̃x�N�g���̑傫�����ׂĂ��傫���ق���D��ɂ���
	if (killer->vec.y <= killer->vec.x)
	{
		if (killer->vec.x <= 0)
		{
			killer->direction = LEFT;
		}
		else
		{
			killer->direction = RIGHT;
		}
	}
	else
	{
		if (killer->vec.y <= 0)
		{
			killer->direction = UP;
		}
		else
		{
			killer->direction = DOWN;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawKiller(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	KILLER *killer = &g_killer[0];			// �L���[�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < KILLER_MAX; i++, killer++)
	{
		if (killer->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, killer->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_KILLER, killer->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

/**************************************************************************//**
	@brief		MakeVertexKiller
	@brief		�L���[�̒��_���W�쐬
	@param[in]	no		�L���[�̔ԍ�
	@return			S_OK	�����̐���
					E-FAIL	�����̎��s
*//***************************************************************************/
HRESULT MakeVertexKiller( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	KILLER *killer = &g_killer[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexKiller( no );

	// rhw�̐ݒ�
	killer->vertexWk[0].rhw =
	killer->vertexWk[1].rhw =
	killer->vertexWk[2].rhw =
	killer->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	killer->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	killer->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	killer->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	killer->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	killer->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	killer->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_KILLER, 0.0f);
	killer->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_KILLER);
	killer->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_KILLER, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_KILLER);

	return S_OK;
}

/**************************************************************************//**
	@brief		SetTextureKiller
	@brief		�L���[�̃e�N�X�`���̍��W�ݒ�
	@param[in]	no				�L���[�̔ԍ�
	@param[in]	cntPattern		�L���[�̃A�j���[�V�����J�E���g�p�^�[��
	@param[in]	direction		�L���[�̌���
	@return		�Ȃ�
*//***************************************************************************/
void SetTextureKiller( int no, int cntPattern, int direction)
{
	KILLER *killer = &g_killer[no];			// �o���b�g�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_KILLER;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_KILLER;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_KILLER;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_KILLER;
	
	switch (direction)
	{
	case UP:
		killer->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		killer->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		killer->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		killer->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
		break;

	case DOWN:
		killer->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		killer->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		killer->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		killer->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
		break;

	case RIGHT:
		killer->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		killer->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		killer->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		killer->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
		break;

	case LEFT:
		killer->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		killer->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		killer->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		killer->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
		break;
	}
}

/**************************************************************************//**
	@brief		SetVertexKiller
	@brief		�L���[�̒��_���W�ݒ�
	@param[in]	no		�L���[�̔ԍ�
	@return		�Ȃ�
*//***************************************************************************/
void SetVertexKiller( int no )
{
	KILLER *killer = &g_killer[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	killer->vertexWk[0].vtx.x = killer->pos.x - TEXTURE_KILLER_SIZE_X;
	killer->vertexWk[0].vtx.y = killer->pos.y - TEXTURE_KILLER_SIZE_Y;
	killer->vertexWk[0].vtx.z = 0.0f;

	killer->vertexWk[1].vtx.x = killer->pos.x + TEXTURE_KILLER_SIZE_X;
	killer->vertexWk[1].vtx.y = killer->pos.y - TEXTURE_KILLER_SIZE_Y;
	killer->vertexWk[1].vtx.z = 0.0f;

	killer->vertexWk[2].vtx.x = killer->pos.x - TEXTURE_KILLER_SIZE_X;
	killer->vertexWk[2].vtx.y = killer->pos.y + TEXTURE_KILLER_SIZE_Y;
	killer->vertexWk[2].vtx.z = 0.0f;

	killer->vertexWk[3].vtx.x = killer->pos.x + TEXTURE_KILLER_SIZE_X;
	killer->vertexWk[3].vtx.y = killer->pos.y + TEXTURE_KILLER_SIZE_Y;
	killer->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �L���[�̔��ːݒ�
//=============================================================================
void SetKiller(void)
{
	KILLER *killer = &g_killer[0];			// �L���[�̃|�C���^�[��������
	MAP *map = GetMapData();				// �}�b�v�̃|�C���^�[���擾

	for (int p = 0; p < MAP_MAXDATA * SIZE_X * SIZE_Y; p++, map++)
	{
		if (killer->dead || g_count == 0)
		{
			// �L���[�̎�ނɉ����Ĕ�΂�������ς��Ă݂鏈��
			switch (map->type)
			{
			case BLOCK4:
			case BLOCK5:
				if (map->type == BLOCK4)
				{
					killer->type = TRACKER;
				}
				else
				{
					killer->type = VECTOR;
				}
				killer->use = true;
				killer->pos = map->pos;
				killer->popCnt = 0;
				killer->dead = false;
				killer->vecUse = false;
				killer++;
				break;
			}
		}
	}
}

//=============================================================================
// �L���[�̎擾�֐�
//=============================================================================
KILLER *GetKiller(int no)
{
	return(&g_killer[no]);
}

