//! @file	item.cpp
//! @author	�܂�
//! @date	2020-06-19
//! @brief	�A�C�e���̎���

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "item.h"
#include "bullet.h"
#include "map.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_GAME_ITEM_WATERMELON	_T("data/TEXTURE/Item/watermelon.png")	// �X�C�J�̉摜
#define TEXTURE_GAME_ITEM_APPLE			_T("data/TEXTURE/Item/apple.png")		// �����S�̉摜
#define	TEXTURE_GAME_ITEM_GRAPE			_T("data/TEXTURE/Item/grape.png")		// �u�h�E�̉摜
#define	TEXTURE_GAME_ITEM_STAR			_T("data/TEXTURE/Item/star02.png")		// �X�^�[�̉摜

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexItem( int no );				// �A�C�e���̒��_���쐬
void SetTextureItem(int no, int cntPattern);	// �A�C�e���̒��_���W�̐ݒ�
void SetVertexItem(int no);						// �A�C�e���̃e�N�X�`���̐ݒ�
void SetItem(float speed);
void DeathItem(void);							// �A�C�e���̔j������

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureItem[ITEM_KIND_MAX];		// �e�N�X�`���ւ̃|���S��

ITEM					itemWk[ITEM_MAX];			// �A�C�e���\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitItem(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ITEM *item = &itemWk[0];

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ITEM_WATERMELON,		// �t�@�C���̖��O
			&g_pD3DTextureItem[WATERMELON]);	// �ǂݍ��ރ������̃|�C���^
		
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ITEM_APPLE,			// �t�@�C���̖��O
			&g_pD3DTextureItem[APPLE]);			// �ǂݍ��ރ������̃|�C���^

		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ITEM_GRAPE,			// �t�@�C���̖��O
			&g_pD3DTextureItem[GRAPE]);			// �ǂݍ��ރ������̃|�C���^

		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ITEM_STAR,				// �t�@�C���̖��O
			&g_pD3DTextureItem[STAR]);			// �ǂݍ��ރ������̃|�C���^

	}

	// �A�C�e���̏���������
	for (int i = 0; i < ITEM_MAX; i++, item++)
	{
		item->use = false;									// �g�p
		item->delete_use = false;							// ���g�p			
		item->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�f�[�^��������
		item->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		item->CountAnim = 0;								// �A�j���J�E���g��������
		item->Texturenum = rand() % 3;						// �e�N�X�`���[��ނ������_���ŏ�����
		item->speed = 0;									// �A�C�e���X�s�[�h�̏�����
		item->type = 0;										// �A�C�e���̎��
		item->point = ITEM_POINT_HERB;
		
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ITEM_SIZE_X, TEXTURE_ITEM_SIZE_Y);
		item->Radius = D3DXVec2Length(&temp);				// �A�C�e���̔��a��������
		item->BaseAngle = atan2f(TEXTURE_ITEM_SIZE_Y, TEXTURE_ITEM_SIZE_X);	// �A�C�e���̊p�x��������

		if (item->Texturenum != STAR)
		{
			item->Texture = g_pD3DTextureItem[item->Texturenum];		// �e�N�X�`�����
		}
		MakeVertexItem(i);												// ���_���̍쐬
	}

	 SetItem(0.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitItem(void)
{
	ITEM *item = &itemWk[0];

	for (int i = 0; i < ITEM_KIND_MAX; i++)
	{
		if (g_pD3DTextureItem[i] != NULL)
		{	// �e�N�X�`���̊J��
			g_pD3DTextureItem[i]->Release(); // ��肪���鍀��
			g_pD3DTextureItem[i] = NULL;
		}
	}
	for (int i = 0; i < ITEM_MAX; i++, item++)
	{
		item->use = false;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItem(void)
{
	ITEM *item = &itemWk[0];

	for (int i = 0; i < ITEM_MAX; i++, item++)
	{
		if (item->delete_use == true)
		{
			if (item->Radius < 0.0f)
			{
				item->delete_use = false;
			}

			item->rot.z += 1.0f;
			item->Radius -= 1.0f;

			// �e�N�X�`�����W��ݒ�
			SetTextureItem(i, item->PatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexItem(i);
		}
	

		if (item->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			item->pos.x += item->speed;
			// �e�N�X�`�����W��ݒ�
			SetTextureItem(i, item->PatternAnim);

			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexItem(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ITEM *item = &itemWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ITEM_MAX; i++, item++)
	{
		if (item->use == true || item->delete_use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, item->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ITEM, item->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// �A�C�e���̔z�u�֐�
//=============================================================================
void SetItem(D3DXVECTOR3 pos)
{
	MAP * map = GetMapData();
	ITEM *item = &itemWk[0];

	for (int i = 0; i < MAP_MAXDATA * SIZE_X * SIZE_Y; i++, map++)
	{
		for (int j = 0; j < ITEM_MAX; j++, item++)
		{
			if (map->type == BLOCK2)
			{
				item->pos = pos;
			}
		}
	}
}

//=============================================================================
// �A�C�e���̔j���ݒ�
//=============================================================================
void DeathItem(void)
{
	ITEM *item = &itemWk[0];
	for (int i = 0; i < ITEM_MAX; i++, item++)
	{
		if (item->pos.x <= 0.0f)
		{
			item->use = false;
		}
	}
}

/**************************************************************************//**
	@brief		MakeVertexItem
	@brief		�A�C�e���̒��_���W�쐬
	@param[in]	no		�A�C�e���̔ԍ�
	@return			S_OK	�����̐���
					E-FAIL	�����̎��s
*//***************************************************************************/
HRESULT MakeVertexItem(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ITEM *item = &itemWk[no];

	// ���_���W�̐ݒ�
	SetVertexItem(no);

	// rhw�̐ݒ�
	item->vertexWk[0].rhw =
	item->vertexWk[1].rhw =
	item->vertexWk[2].rhw =
	item->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	item->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	item->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	item->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	item->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	if (item->type != STAR)
	{
		// �e�N�X�`�����W�̐ݒ�
		item->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		item->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X, 0.0f);
		item->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y);
		item->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X, 1.0f / TEXTURE_PATTERN_DIVIDE_Y);
	}
	else
	{
		item->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		item->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		item->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		item->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}

/**************************************************************************//**
	@brief		SetTextureItem
	@brief		�A�C�e���̃e�N�X�`���ݒ�
	@param[in]	no		�A�C�e���̔ԍ�
	@return		�Ȃ�
*//***************************************************************************/
void SetTextureItem( int no, int cntPattern )
{
	ITEM *item = &itemWk[no];
	
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern ;
	int y = cntPattern ;
	float sizeX = 1.0f ;
	float sizeY = 1.0f ;
	
	item->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	item->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	item->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	item->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}
/**************************************************************************//**
	@brief		SetVertexItem
	@brief		�A�C�e���̍��W�ݒ�
	@param[in]	no		�A�C�e���̔ԍ�
	@return		�Ȃ�
*//***************************************************************************/
void SetVertexItem(int no)
{
	ITEM *item = &itemWk[no];
	
	// ���_���W�̐ݒ�
	item->vertexWk[0].vtx.x = item->pos.x - cosf(item->BaseAngle + item->rot.z) * item->Radius;
	item->vertexWk[0].vtx.y = item->pos.y - sinf(item->BaseAngle + item->rot.z) * item->Radius;
	item->vertexWk[0].vtx.z = 0.0f;

	item->vertexWk[1].vtx.x = item->pos.x + cosf(item->BaseAngle - item->rot.z) * item->Radius;
	item->vertexWk[1].vtx.y = item->pos.y - sinf(item->BaseAngle - item->rot.z) * item->Radius;
	item->vertexWk[1].vtx.z = 0.0f;

	item->vertexWk[2].vtx.x = item->pos.x - cosf(item->BaseAngle - item->rot.z) * item->Radius;
	item->vertexWk[2].vtx.y = item->pos.y + sinf(item->BaseAngle - item->rot.z) * item->Radius;
	item->vertexWk[2].vtx.z = 0.0f;

	item->vertexWk[3].vtx.x = item->pos.x + cosf(item->BaseAngle + item->rot.z) * item->Radius;
	item->vertexWk[3].vtx.y = item->pos.y + sinf(item->BaseAngle + item->rot.z) * item->Radius;
	item->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �A�C�e���擾�֐�
//=============================================================================
ITEM *GetItem(int no)
{
	return(&itemWk[no]);
}

//============================================================================
// �A�C�e���̐ݒ�
//============================================================================
void SetItem(float speed)
{
	ITEM *item = GetItem(0);
	MAP *map = GetMapData();

	for (int i = 0; i < ITEM_MAX; i++, item++)
	{
		if (!item->use)
		{
			item->Texturenum = rand() % 3;						//�e�N�X�`���[��ނ������_���ŏ�����

			if (item->Texturenum == 2)							//�e�N�X�`���[�i���o�[���Q�Ȃ�
			{
				item->grape_use = true;							//�u�h�E���g�p��
			}
			D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ITEM_SIZE_X, TEXTURE_ITEM_SIZE_Y);
			item->Radius = D3DXVec2Length(&temp);				// �A�C�e���̔��a��������
			item->rot.z = 0.0f;
			
			item->speed = speed;
			item->delete_use = false;
		}
	}

	ITEM *items = GetItem(0);

	for (int j = 0; j < MAP_MAXDATA * SIZE_X * SIZE_Y; j++, map++)
	{
		if (map->type == BLOCK2)
		{
			items->use = true;
			items->pos = map->pos;
			items++;
		}
		if (map->type == ITEM17)
		{
			items->use = true;
			items->pos = map->pos;
			items->type = STAR;
			items->Texture = g_pD3DTextureItem[STAR];
			items++;
		}
	}

}
