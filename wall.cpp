//! @file	wall.cpp
//! @author	kitade mayumi
//! @date	2020-08-07
//! @brief	�ǂ̎���

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "wall.h"
#include "checkhit.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_WALL	"data/TEXTURE/wall04.png"
#define WALL_SPEED	(0.1f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakevertexWall(void);
void SettextureWall(VERTEX_2D *Vtx);
void SetVertexWall(VERTEX_2D *Vtx);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;	// �e�N�X�`���ւ̃|���S��
static WALL g_wall;										// �ǂ̊i�[���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_WALL,						// �t�@�C���̖��O
		&g_pD3DTexture);					// �ǂݍ��ރ������[

	g_wall.use = true;
	g_wall.pos = D3DXVECTOR3(-(WALL_TEXTURE_SIZEX / 4.0f), WALL_TEXTURE_SIZEY / 2.0f, 0.0f);
	g_wall.speed = WALL_SPEED;
	g_wall.Texture = g_pD3DTexture;

	MakevertexWall();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitWall(void)
{
	if (g_pD3DTexture != NULL)
	{
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWall(void)
{
	g_wall.pos.x += g_wall.speed;

	SetVertexWall(g_wall.vertexWk);

	CheckHitWall();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̍쐬
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_wall.use == true)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_wall.Texture);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_wall.vertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakevertexWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	g_wall.vertexWk[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_wall.vertexWk[1].vtx = D3DXVECTOR3(WALL_TEXTURE_SIZEX, 0.0f, 0.0f);
	g_wall.vertexWk[2].vtx = D3DXVECTOR3(0.0f, WALL_TEXTURE_SIZEY, 0.0f);
	g_wall.vertexWk[3].vtx = D3DXVECTOR3(WALL_TEXTURE_SIZEX, WALL_TEXTURE_SIZEY, 0.0f);

	// rhw�̐ݒ�
	g_wall.vertexWk[0].rhw = 1.0f;
	g_wall.vertexWk[1].rhw = 1.0f;
	g_wall.vertexWk[2].rhw = 1.0f;
	g_wall.vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_wall.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_wall.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_wall.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_wall.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	SettextureWall(g_wall.vertexWk);
	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�ݒ�
//=============================================================================
void SettextureWall(VERTEX_2D *Vtx)
{
	Vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// ���_�̐ݒ�
//=============================================================================
void SetVertexWall(VERTEX_2D *Vtx)
{
	Vtx[0].vtx.x = -WALL_TEXTURE_SIZEX + g_wall.pos.x;
	Vtx[1].vtx.x = 0.0f + g_wall.pos.x;
	Vtx[2].vtx.x = -WALL_TEXTURE_SIZEX + g_wall.pos.x;
	Vtx[3].vtx.x = 0.0f + g_wall.pos.x;
}

//=============================================================================
// �ǂ̃A�h���X�擾
//=============================================================================
WALL *GetWall(void)
{
	return &g_wall;
}