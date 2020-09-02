//=============================================================================
//
// �g����A�C�e������ [substitute.cpp]
// Author : kitade mayumi
//
//=============================================================================
#include "main.h"
#include "scene.h"
#include "playerTest.h"
#include "controller.h"
#include "input.h"
#include "map.h"
#include "bullet.h"
#include "checkhit.h"
#include "sound.h"
#include "substitute.h"
#include "fade.h"
#include <math.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DIFFUSE	(255)
#define SUBSTITUTE_MAP_MOVE_SPEED	(10.0f)

#define SUBSTITUTE_MOVE_SPEED	(2.0f)
#define SUBSTITUTE_INIT_POSX	(30.0f)

#define SUBSTITUTE_RELEASE_TIME	(60 * 10)
#define SUBSTITUTE_MOVE_TIME	(60)
#define SUBSTITUTE_MOVE_ATTACK_SPEED	(3.5f)
enum SUBSTITUTE_STATE_ANIME
{
	IDLE,
	RUN,
	JUMP,
	RELEASE,
	STATE_MAX,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void ReadTextureSubstitute(void);
void SetSubstitute(void);

HRESULT MakeVertexSubstitute(void);
void SetTextureSubstitute(VERTEX_2D *Vtx, int cntPattern);
void SetVertexSubstitute(VERTEX_2D *Vtx);
void animSubstituteState(int * animState);

void UpdateStickingSubstitute(void);
void UpdateAttackSubstitute(void);

void SlideSubstitute(void);
void ReleaseSubstitute(void);
void LenghtSubstitute(void);

void FallSubstitute(void);
void JumpSubstitute(void);
void AttackSubstitute(void);
void SubstituteMoving(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture[STATE_MAX] = { NULL };	// �e�N�X�`���ւ̃|���S��

static SUBSTITUTE				g_substitute;		// �g����A�C�e���\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSubstitute(void)
{
	ReadTextureSubstitute();
	int scene = GetScene();
	PLAYER *player = GetPlayer();
	g_substitute.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���̍��W�f�[�^��Ԃ�

	g_substitute.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ��]�f�[�^��������

	g_substitute.moveSpeed = SUBSTITUTE_MOVE_SPEED;
	g_substitute.use = true;
	g_substitute.releaseUse = false;
	g_substitute.sticking = false;
	g_substitute.attackUse = false;

	// �A�j���p�^�[���ԍ��������_���ŏ�����
	g_substitute.animeCnt.PatternAnim = rand() % SUBSTITUTE_IDLE_TEXTURE_PATTERN_DIVIDE_X;

	g_substitute.textureSize = D3DXVECTOR2(SUBSTITUTE_TEXTURE_SIZE_X, SUBSTITUTE_TEXTURE_SIZE_Y);

	g_substitute.state = IDLE;
	g_substitute.Texture = g_pD3DTexture[g_substitute.state];
	g_substitute.lenght = 0.0f;		// �v���C���[�Ƃ̈ʒu�֌W

	g_substitute.animeCnt.PatDivX = SUBSTITUTE_IDLE_TEXTURE_PATTERN_DIVIDE_X;	// �e�N�X�`���̓�������X��������
	g_substitute.animeCnt.PatDivY = SUBSTITUTE_IDLE_TEXTURE_PATTERN_DIVIDE_Y;	// �e�N�X�`���̓�������Y��������
	g_substitute.animeCnt.AnimPatNum = SUBSTITUTE_IDLE_ANIM_PATTERN_NUM;		// �A�j���[�V�����p�^�[������������
	g_substitute.animeCnt.TimeAnim = SUBSTITUTE_IDLE_TIME_ANIMATION;			// �A�j���[�V�����̐؂�ւ��J�E���g��������
	g_substitute.animeCnt.PatternAnim = 0;									// �A�j���p�^�[���ԍ�������

	g_substitute.animeCnt.CountAnim = 0;								// �A�j���J�E���g��������
	g_substitute.countReleaseTime = 0;
	g_substitute.moveCount = 0;											// �ړ��ʂ̃J�E���g������

	D3DXVECTOR2 temp = D3DXVECTOR2(SUBSTITUTE_TEXTURE_SIZE_X, SUBSTITUTE_TEXTURE_SIZE_Y);
	g_substitute.radius = D3DXVec2Length(&temp);									// ���a��������
	g_substitute.baseAngle = atan2f(SUBSTITUTE_TEXTURE_SIZE_Y, SUBSTITUTE_TEXTURE_SIZE_X);	// �p�x��������

	g_substitute.jumpForce = 0;	// �W�����v���Ă��Ȃ�
	g_substitute.dropSpeed = 0;	// �d�͉����x������

	g_substitute.ofsPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �I�t�Z�b�g���W��������
	g_substitute.direction = player->direction;				// �g����A�C�e���̓v���C���[�Ɠ�������

	MakeVertexSubstitute();

	SetSubstitute();

	if (FAILED(MakeVertexSubstitute()))
	{
		return E_FAIL;
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSubstitute(void)
{
	for (int i = 0; i < (STATE_MAX - 1); i++)
	{
		if (g_pD3DTexture[i] != NULL)
		{	// �e�N�X�`���̊J��
			g_pD3DTexture[i]->Release();
			g_pD3DTexture[i] = NULL;
		}
	}
}

//=============================================================================
// �g����A�C�e���̂������Ă���Ƃ��̍X�V����
//=============================================================================
void UpdateStickingSubstitute(void)
{
	if (g_substitute.sticking)
	{
		// �L�[���͂ňړ� 
		if (GetInput(JUMPMOVE))	// �W�����v�֌W
		{
			if (g_substitute.dropSpeed > 1 && g_substitute.jumpForce <= 1)	//�u�n�ォ��W�����v���Ă���̈�񂾂��󒆃W�����v�v�Ɓu���ꂩ�玩�R��������̈�񂾂��󒆃W�����v�v�����邽�߂̔���
			{
				g_substitute.dropSpeed = 0;	//�d�͉����x��0�ɂ��邱�ƂŁA�Ăѐg����A�C�e�����㏸���͂��߂�
				g_substitute.jumpForce++;	// ��������jump++�ƍ��킹��jump��2�ȏ�ɂȂ�̂ŁA�ǂ̂悤�ȃ^�C�~���O�ł��u�󒆃W�����v��̓W�����v�ł��Ȃ��v
										// SE�Đ�
				//PlaySound(SOUND_LABEL_SE_jump2);
			}
			else
			{
				//PlaySound(SOUND_LABEL_SE_jump);
			}

			g_substitute.jumpForce++;		// �W�����v�̐؂�ւ��A1�ȏ�ŃW�����v��ԂɂȂ�
			g_substitute.state = JUMP;		// �e�N�X�`���́u�W�����v�v
		}
		SubstituteMoving();
		//SlideSubstitute();

		JumpSubstitute();

		AttackSubstitute();

	}
}

//=============================================================================
// �g����A�C�e���̍U�����Ă��鎞�̍X�V����
//=============================================================================
void UpdateAttackSubstitute(void)
{
	// sticking = false; Attack�ɂ���ė��ꂽ��ԂɂȂ���
	if (g_substitute.attackUse && !g_substitute.sticking)
	{
		if (g_substitute.direction == Right)
		{
			g_substitute.pos.x += g_substitute.moveSpeed * SUBSTITUTE_MOVE_ATTACK_SPEED;
		}
		else
		{
			g_substitute.pos.x -= g_substitute.moveSpeed * SUBSTITUTE_MOVE_ATTACK_SPEED;
		}
		g_substitute.moveCount++;
	}

	// �ő�ړ��ʂɒB�������U����ԂłȂ��Ȃ�i����ȏ�̔򋗗����Ȃ���ԁj
	if (g_substitute.moveCount >= SUBSTITUTE_MOVE_TIME)
	{
		g_substitute.moveCount = 0;
		g_substitute.attackUse = false;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSubstitute(void)
{
	int scene = GetScene();
	PLAYER *player = GetPlayer();

	if (g_substitute.use)
	{
		// �A�j���[�V�����̃p�^�[�����X�V------------------
		g_substitute.animeCnt.CountAnim++;

		// ���̃t���[�������Ԑ؂ꂽ��
		if ((g_substitute.animeCnt.CountAnim % g_substitute.animeCnt.TimeAnim) == 0)
		{
			//cnt���Z�b�g
			g_substitute.animeCnt.CountAnim = 0;
			// ���̃t���[���ɐi��
			g_substitute.animeCnt.PatternAnim = (g_substitute.animeCnt.PatternAnim + 1) % g_substitute.animeCnt.AnimPatNum;
		}

		if (g_substitute.jumpForce == 0)	// �g����A�C�e�����W�����v���Ă��Ȃ��Ɨ�����ԂɂȂ�
		{
			g_substitute.state = IDLE;
		}

		ReleaseSubstitute();
		UpdateStickingSubstitute();
		RestrictionSubstitute();
		FallSubstitute();
		LenghtSubstitute();

		UpdateAttackSubstitute();
		CheckHitEnemySubstitute();

		animSubstituteState(&g_substitute.state);

		SetVertexSubstitute(g_substitute.vertexWk);
		SetTextureSubstitute(g_substitute.vertexWk, g_substitute.animeCnt.PatternAnim);
	}
}

//=============================================================================
// �g����A�C�e���̃e�N�X�`���ǂݍ���
//=============================================================================
void ReadTextureSubstitute(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// �A�C�h�����
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SUBSTITUTE_IDLE,		// �t�@�C���̖��O
		&g_pD3DTexture[IDLE]);			// �ǂݍ��ރ������[
	// ���s���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SUBSTITUTE_RUN,			// �t�@�C���̖��O
		&g_pD3DTexture[RUN]);			// �ǂݍ��ރ������[
	// �W�����v���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SUBSTITUTE_JUMP,		// �t�@�C���̖��O
		&g_pD3DTexture[JUMP]);			// �ǂݍ��ރ������[

}

//=============================================================================
// �g����A�C�e���ړ�
//=============================================================================
void SubstituteMoving(void)
{
	// �E�ړ�----------------------------------------
	if (GetInput(RIGHTMOVE))
	{
		if (DownSpeed())
		{
			g_substitute.pos.x += g_substitute.moveSpeed / 2.0f;
		}
		else
		{
			g_substitute.pos.x += g_substitute.moveSpeed;
		}

		g_substitute.direction = Right;					// ���ړ�
		g_substitute.state = RUN;						// �����j���Otrue

	}
	// ���ړ�-----------------------------------------
	else if (GetInput(LEFTMOVE))
	{
		if (DownSpeed())
		{
			g_substitute.pos.x -= g_substitute.moveSpeed / 2.0f;
		}
		else
		{
			g_substitute.pos.x -= g_substitute.moveSpeed;
		}
		g_substitute.direction = Left;					// ���ړ�
		g_substitute.state = RUN;						// �����j���Otrue

	}
}

//=============================================================================
// �g����A�C�e���̊��鏈��
//=============================================================================
void SlideSubstitute(void)
{
	PLAYER *player = GetPlayer();
	if (SlidePlayer())
	{
		if (g_substitute.direction == Right)
		{
			g_substitute.pos.x += (PLAYER_SLIDE_MAX - (player->slideCnt * 1.0f));
		}
		else
		{
			g_substitute.pos.x -= (PLAYER_SLIDE_MAX - (player->slideCnt * 1.0f));
		}
	}
}

//=============================================================================
// �g����A�C�e���̗�������
//=============================================================================
void FallSubstitute(void)
{
	g_substitute.pos.y += g_substitute.dropSpeed * 0.7f;	// �����x�I�ɉ��ֈړ��A�d�͉����x
	g_substitute.dropSpeed++;

	FallCheckHitSubstitute();
}

//=============================================================================
// �g����A�C�e���̃W�����v����
//=============================================================================
void JumpSubstitute(void)
{
	if (g_substitute.jumpForce >= 1)	//�W�����v�����瓙���ŏ㏸�B�������x�������x�I�ɑ�������̂Ŏ��Ԍo�߂ŗ�������
	{
		if (DownSpeed())
		{
			g_substitute.pos.y -= SUBSTITUTE_ACCELE / 2;
		}
		else
		{
			g_substitute.pos.y -= SUBSTITUTE_ACCELE;
		}
		g_substitute.state = JUMP;		// �e�N�X�`���́u�W�����v�v

		g_substitute.textureSize = D3DXVECTOR2(SUBSTITUTE_TEXTURE_SIZE_X, SUBSTITUTE_TEXTURE_SIZE_Y);

	}
	/* ���n������W�����v���O�ɂ��ăW�����v��Ԃ���������B���̏�����FallSubstitute���ɂ��� */
}

//=============================================================================
// �g����A�C�e���̍U��
//=============================================================================
void AttackSubstitute(void)
{
	if (GetInput(ATTACK))
	{
		D3DXVECTOR3 pos = g_substitute.pos;
		//PlaySound(SOUND_LABEL_SE_shot2);
		g_substitute.releaseUse = true;
		g_substitute.sticking = false;
		g_substitute.attackUse = true;
	}
}

//=============================================================================
// �g����A�C�e���̃����[�X��Ԃ̎��ԕω�
//=============================================================================
void ReleaseSubstitute(void)
{
	if (g_substitute.releaseUse == true
		&& !g_substitute.attackUse)
	{
		g_substitute.countReleaseTime++;

		if (g_substitute.countReleaseTime >= SUBSTITUTE_RELEASE_TIME)
		{
			if (!g_substitute.sticking)
			{
				g_substitute.use = false;
			}
		}
	}
	else
	{
		g_substitute.countReleaseTime = 0;
	}
}

//=============================================================================
// �g����A�C�e���̃X�e�[�^�X�ɂ��e�N�X�`����ԕω�
//=============================================================================
void animSubstituteState(int * animState)
{
	switch (*animState)
	{
	case IDLE:
	case RELEASE:
		// Idle�A�j���[�V����
		g_substitute.Texture = g_pD3DTexture[*animState];
		g_substitute.animeCnt.PatDivX = SUBSTITUTE_IDLE_TEXTURE_PATTERN_DIVIDE_X;
		g_substitute.animeCnt.PatDivY = SUBSTITUTE_IDLE_TEXTURE_PATTERN_DIVIDE_Y;
		g_substitute.animeCnt.AnimPatNum = SUBSTITUTE_IDLE_ANIM_PATTERN_NUM;
		g_substitute.animeCnt.TimeAnim = SUBSTITUTE_IDLE_TIME_ANIMATION;

		g_substitute.textureSize = D3DXVECTOR2(SUBSTITUTE_TEXTURE_SIZE_X, SUBSTITUTE_TEXTURE_SIZE_Y);
		break;

	case RUN:
		// Run�A�j���[�V����
		g_substitute.Texture = g_pD3DTexture[*animState];
		g_substitute.animeCnt.PatDivX = SUBSTITUTE_RUN_TEXTURE_PATTERN_DIVIDE_X;
		g_substitute.animeCnt.PatDivY = SUBSTITUTE_RUN_TEXTURE_PATTERN_DIVIDE_Y;
		g_substitute.animeCnt.AnimPatNum = SUBSTITUTE_RUN_ANIM_PATTERN_NUM;
		g_substitute.animeCnt.TimeAnim = SUBSTITUTE_RUN_TIME_ANIMATION;

		g_substitute.textureSize = D3DXVECTOR2(SUBSTITUTE_TEXTURE_SIZE_X, SUBSTITUTE_TEXTURE_SIZE_Y);
		break;

	case JUMP:
		// Jump�A�j���[�V����
		g_substitute.Texture = g_pD3DTexture[*animState];
		g_substitute.animeCnt.PatDivX = SUBSTITUTE_JUMP_TEXTURE_PATTERN_DIVIDE_X;
		g_substitute.animeCnt.PatDivY = SUBSTITUTE_JUMP_TEXTURE_PATTERN_DIVIDE_Y;
		g_substitute.animeCnt.AnimPatNum = SUBSTITUTE_JUMP_ANIM_PATTERN_NUM;
		g_substitute.animeCnt.TimeAnim = SUBSTITUTE_JUMP_TIME_ANIMATION;

		break;

	default:
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSubstitute(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_substitute.use == true)			// �g�p���Ă����ԂȂ�`�悷��
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_substitute.Texture);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_substitute.vertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexSubstitute(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	g_substitute.vertexWk[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_substitute.vertexWk[1].vtx = D3DXVECTOR3(0.0f + SUBSTITUTE_TEXTURE_SIZE_X, 0.0f, 0.0f);
	g_substitute.vertexWk[2].vtx = D3DXVECTOR3(0.0f, 0.0f + SUBSTITUTE_TEXTURE_SIZE_Y, 0.0f);
	g_substitute.vertexWk[3].vtx = D3DXVECTOR3(0.0f + SUBSTITUTE_TEXTURE_SIZE_X, 0.0f + SUBSTITUTE_TEXTURE_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	g_substitute.vertexWk[0].rhw =
		g_substitute.vertexWk[1].rhw =
		g_substitute.vertexWk[2].rhw =
		g_substitute.vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_substitute.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_substitute.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_substitute.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_substitute.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	SetTextureSubstitute(g_substitute.vertexWk, g_substitute.animeCnt.PatternAnim);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�ݒ�
//=============================================================================
void SetTextureSubstitute(VERTEX_2D *Vtx, int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % g_substitute.animeCnt.PatDivX;
	int y = cntPattern / g_substitute.animeCnt.PatDivX;
	float sizeX = 1.0f / g_substitute.animeCnt.PatDivX;
	float sizeY = 1.0f / g_substitute.animeCnt.PatDivY;

	if (g_substitute.direction == Right)
	{
		Vtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		Vtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		Vtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		Vtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}
	else if (g_substitute.direction == Left)
	{
		Vtx[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		Vtx[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		Vtx[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		Vtx[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}

	int flashing = (g_substitute.countReleaseTime + 1) % 2;

	if (g_substitute.countReleaseTime > 0)
	{
		Vtx[0].diffuse = D3DCOLOR_RGBA(0, 255, 255, flashing * 255);
		Vtx[1].diffuse = D3DCOLOR_RGBA(0, 255, 255, flashing * 255);
		Vtx[2].diffuse = D3DCOLOR_RGBA(0, 255, 255, flashing * 255);
		Vtx[3].diffuse = D3DCOLOR_RGBA(0, 255, 255, flashing * 255);
	}

	else
	{
		Vtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		Vtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		Vtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		Vtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexSubstitute(VERTEX_2D *Vtx)
{
	//D3DXVECTOR3 pos = g_substitute.pos + g_substitute.ofsPos;

	// ���_���W�̐ݒ�

	Vtx[0].vtx.x = g_substitute.pos.x - cosf(g_substitute.baseAngle + g_substitute.rot.z) * g_substitute.radius;
	Vtx[0].vtx.y = g_substitute.pos.y - sinf(g_substitute.baseAngle + g_substitute.rot.z) * g_substitute.radius;
	Vtx[0].vtx.z = 0.0f;

	Vtx[1].vtx.x = g_substitute.pos.x + cosf(g_substitute.baseAngle - g_substitute.rot.z) * g_substitute.radius;
	Vtx[1].vtx.y = g_substitute.pos.y - sinf(g_substitute.baseAngle - g_substitute.rot.z) * g_substitute.radius;
	Vtx[1].vtx.z = 0.0f;

	Vtx[2].vtx.x = g_substitute.pos.x - cosf(g_substitute.baseAngle - g_substitute.rot.z) * g_substitute.radius;
	Vtx[2].vtx.y = g_substitute.pos.y + sinf(g_substitute.baseAngle - g_substitute.rot.z) * g_substitute.radius;
	Vtx[2].vtx.z = 0.0f;

	Vtx[3].vtx.x = g_substitute.pos.x + cosf(g_substitute.baseAngle + g_substitute.rot.z) * g_substitute.radius;
	Vtx[3].vtx.y = g_substitute.pos.y + sinf(g_substitute.baseAngle + g_substitute.rot.z) * g_substitute.radius;
	Vtx[3].vtx.z = 0.0f;
}

//=============================================================================
// �g����A�C�e���擾�֐�
//=============================================================================
SUBSTITUTE *GetSubstitute(void)
{
	return(&g_substitute);
}

//=============================================================================
// �g����A�C�e���̃Z�b�g�����i�ʒu�j
//=============================================================================
void SetSubstitute(void)
{
	MAP *map = GetMapData();

	for (int p = 0; p < MAP_MAXDATA * SIZE_X * SIZE_Y; p++, map++)
	{
		if (map->type == ITEM18)
		{
			g_substitute.Texture = g_pD3DTexture[IDLE];
			g_substitute.pos = map->pos;
			g_substitute.use = true;
			break;
		}
	}
}

//=============================================================================
// �g����A�C�e���̃v���C���[�Ƃ̋����̏����i�v���C���[�̈ʒu�ɍ��킹��j
//=============================================================================
void LenghtSubstitute(void)
{
	PLAYER *player = GetPlayer();
	float vecLenghtX = 0.0f;
	float vecLenghtY = 0.0f;

	vecLenghtX = g_substitute.pos.x - player->pos.x;
	vecLenghtY = fabsf(g_substitute.pos.y - player->pos.y);
	g_substitute.lenght = fabsf(g_substitute.pos.x - player->pos.x);
	if (g_substitute.sticking && g_substitute.attackUse == false)
	{
		if (g_substitute.lenght > SUBSTITUTE_INIT_POSX
			&& vecLenghtY <= 0.0f)
		{
			g_substitute.state = RUN;

			if (vecLenghtX < 0)
			{
				g_substitute.pos.x += g_substitute.moveSpeed;
			}
			else
			{
				g_substitute.pos.x -= g_substitute.moveSpeed;
			}
		}
		else if(vecLenghtY > 0.0f)
		{
			g_substitute.sticking = false;
			g_substitute.releaseUse = true;
		}
	}
}

//=============================================================================
// �g����A�C�e���̃Z�b�g�����i�v���C���[�̈ʒu�ɍ��킹��j
//=============================================================================
void SetPosSubstitute(void)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(SUBSTITUTE_INIT_POSX, 0.0f, 0.0f);
	PLAYER *player = GetPlayer();
	if (player->direction == Right)
	{
		D3DXVec3Subtract(&g_substitute.pos, &player->pos, &pos);

	}
	else if (player->direction == Left)
	{
		D3DXVec3Add(&g_substitute.pos, &player->pos, &pos);

	}
}
