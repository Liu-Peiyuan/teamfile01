//! @file	effect.cpp
//! @author	kitade mayumi
//! @date	2020-08-24
//! @brief	�G�t�F�N�g�����̎���

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "effect.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define EMISSION_FULL 0		// �S�̒ǉ��t���Oon
#define EMISSION_RATE 1		// �S�̒ǉ��t���Ooff

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEffect( int nCount, LPDIRECT3DDEVICE9 pDevice);	 // �G�t�F�N�g�̒��_���쐬
void SetTextureEffect( int nCount, int nNum, int nCntPattern );		 // �e�N�X�`�����W�̐ݒ�
void SetVertexEffect( int nCount, int nNum);						 // ���_���W�̐ݒ�
void ResetParticle(int nCount, int nNum);							 // �p�[�e�B�N���̃��Z�b�g

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureEffect[MAX_KIND_EFFECT] = { NULL };		// �e�N�X�`���ւ̃|���S��

static EFFECT					effectWk[EFFECT_NUM_EFFECTS];	// �G�l�~�[�\����
static int				g_effectTexDevideX;				// �e�N�X�`����X������
static int				g_effectTexDevideY;				// �e�N�X�`����Y������
//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect(int type)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// �e�N�X�`���[�̏��������s��
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			EFFECT_TEXTURE_PLAYER_BLOOD,						// �t�@�C���̖��O
			&g_pD3DTextureEffect[PLAYER_BLOOD]);				// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			EFFECT_TEXTURE_ENEMY_BLOOD,							// �t�@�C���̖��O
			&g_pD3DTextureEffect[ENEMY_BLOOD]);					// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			EFFECT_TEXTURE_ITEM_HEAL,							// �t�@�C���̖��O
			&g_pD3DTextureEffect[ITEM_HEAL]);					// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			EFFECT_TEXTURE_ITEM_GET,							// �t�@�C���̖��O
			&g_pD3DTextureEffect[ITEM_GET]);					// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			EFFECT_TEXTURE_KILLER_APPEAR,							// �t�@�C���̖��O
			&g_pD3DTextureEffect[KILLER_APPEAR]);				// �ǂݍ��ރ������̃|�C���^
	}


	g_effectTexDevideX = EFFECT_TEXTURE_PLAYER_BLOOD_PATTERN_DIVIDE_X;
	g_effectTexDevideY = EFFECT_TEXTURE_PLAYER_BLOOD_PATTERN_DIVIDE_Y;

	// ����������
	for (int nCount = 0; nCount < EFFECT_NUM_EFFECTS; nCount++)
	{
		effectWk[nCount].nUse = false;
		effectWk[nCount].nElapsed = 0;

		MakeVertexEffect(nCount, pDevice);										// ���_���̍쐬

		for (int nNum = 0; nNum < EFFECT_NUM_PARTS; nNum++)
		{
			effectWk[nCount].pParticle[nNum].Texture = g_pD3DTextureEffect[PLAYER_BLOOD];
			ResetParticle(nCount, nNum);
		}
	}

	return S_OK;
}

/**************************************************************************//**
	@brief			�p�[�e�B�N���̃��Z�b�g
	@param[in,out]	nCount		�G�t�F�N�g�̐��̃J�E���g
	@param[in]		nNum		�p�[�e�B�N���̐�
	@return			�Ȃ�
*//***************************************************************************/
void ResetParticle(int nCount, int nNum) 
{
	// ���W�f�[�^��������
	effectWk[nCount].pParticle[nNum].pos = 
								D3DXVECTOR3(effectWk[nCount].pos.x + rand() % 30 - 15,
									effectWk[nCount].pos.y + rand() % 30 - 15, 0.0f);
	effectWk[nCount].pParticle[nNum].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���

	effectWk[nCount].pParticle[nNum].nPatternAnim = 0;							// �A�j���p�^�[���ԍ��������_���ŏ�����
	effectWk[nCount].pParticle[nNum].nCountAnim = 0;								// �A�j���J�E���g��������
	effectWk[nCount].pParticle[nNum].nLiveTime = 30;								// �p�[�e�B�N���̐�������
	effectWk[nCount].pParticle[nNum].bIsFinish = 0;								// �p�[�e�B�N���̏I��
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	for (int i = 0; i < MAX_KIND_EFFECT; i++)
	{
		if (g_pD3DTextureEffect[i] != NULL)
		{	// �e�N�X�`���̊J��
			g_pD3DTextureEffect[i]->Release();
			g_pD3DTextureEffect[i] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	for (int nCount = 0; nCount < EFFECT_NUM_EFFECTS; nCount++)
	{
		if (effectWk[nCount].nUse)
		{
			if (effectWk[nCount].nIsEnding){
				effectWk[nCount].nUse = FALSE;
				continue;
			}

			//�G�~�b�g���L���ł���΃G�t�F�N�g�쐬�������s��
			if (effectWk[nCount].bIsRemoveOnFinish == FALSE)
			{

				//�G�t�F�N�g�쐬���[�g�̑�������
				if (effectWk[nCount].nEffectCount < EFFECT_NUM_PARTS)
					effectWk[nCount].nEmitCounter++;

				//�o�b�t�@�ɋ󂫂�����A�ǉ��^�C�~���O�����Ă���ΐV���ȃG�t�F�N�g��ǉ�����
				while ((effectWk[nCount].nEffectCount < EFFECT_NUM_PARTS) && (effectWk[nCount].nEmitCounter > EMISSION_RATE))
				{
					//�S�̒ǉ��t���O��ON�ł���΋󂫗̈�S�ĂɐV���ȃG�t�F�N�g��ǉ�����
					if (EMISSION_FULL)
						effectWk[nCount].nEffectCount = EFFECT_NUM_PARTS;
					else
						effectWk[nCount].nEffectCount++;

					//�G�t�F�N�g�쐬���[�g�̏�����
					effectWk[nCount].nEmitCounter = 0;
				}

				effectWk[nCount].nElapsed++;

				//���Ԓ���
				if ((effectWk[nCount].nDuration != -1) && (effectWk[nCount].nDuration < effectWk[nCount].nElapsed)){
					effectWk[nCount].bIsRemoveOnFinish = TRUE;
				}
			}

			int effectIndex = 0;

			//�G�t�F�N�g�̍X�V����
			while (effectIndex < effectWk[nCount].nEffectCount)
			{
				if (effectWk[nCount].pParticle[effectIndex].nLiveTime > 0)
				{
					//�����t���[������
					effectWk[nCount].pParticle[effectIndex].nLiveTime--;

					//�A�j���p�^�[���i�s
					if (++effectWk[nCount].pParticle[effectIndex].nCountAnim > EFFECT_TIME_ANIMATION) {
						//�A�j���p�^�[�����ő�l�ɒB�����ꍇ�ł��I��
						if (++effectWk[nCount].pParticle[effectIndex].nPatternAnim >= ((g_effectTexDevideX * g_effectTexDevideY) -1))
						{
							effectWk[nCount].pParticle[effectIndex].nPatternAnim = (g_effectTexDevideX * g_effectTexDevideY) - 1;
							effectWk[nCount].pParticle[effectIndex].nLiveTime = 0;
						}

						effectWk[nCount].pParticle[effectIndex].nCountAnim = 0;
					}

					SetTextureEffect(nCount, effectIndex, effectWk[nCount].pParticle[effectIndex].nPatternAnim);

					SetVertexEffect(nCount, effectIndex);						// �ړ���̍��W�Œ��_��ݒ�

					effectIndex++;
				}
				else{
					if (effectWk[nCount].bIsRemoveOnFinish){
						if (effectWk[nCount].pParticle[effectIndex].bIsFinish == 0)
						{
							effectWk[nCount].pParticle[effectIndex].bIsFinish = 1;
							effectWk[nCount].nNumFinish++;
						}
						//�I������
						if (effectWk[nCount].nNumFinish == effectWk[nCount].nEffectCount)
						{
							effectWk[nCount].nIsEnding = TRUE;
							break;
						}
						effectIndex++;
					}
					else{
						//�o�b�t�@������������
						ResetParticle(nCount, effectIndex);

						//�����łȂ���΃C���f�b�N�X���l�߂�
						if (effectIndex != (effectWk[nCount].nEffectCount - 1))
						{
							effectWk[nCount].pParticle[effectIndex] = effectWk[nCount].pParticle[effectWk[nCount].nEffectCount - 1];
							ResetParticle(nCount, (effectWk[nCount].nEffectCount - 1));
						}
						effectWk[nCount].nEffectCount--;
					}
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < EFFECT_NUM_EFFECTS; nCount++)
	{
		if (effectWk[nCount].nUse)
		{
			for (int nNum = 0; nNum < effectWk[nCount].nEffectCount; nNum++)
			{
				if (effectWk[nCount].pParticle[nNum].bIsFinish == 0) {
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, effectWk[nCount].pParticle[nNum].Texture);
					// �|���S���̕`��
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, effectWk[nCount].pParticle[nNum].vertexWk, sizeof(VERTEX_2D));
				}
			}
		}
	}
}

/**************************************************************************//**
	@brief			�G�t�F�N�g�̒��_���쐬
	@param[in,out]	pDevice	�f�o�C�X�̃|�C���^
	@param[in]		nCnt	�G�t�F�N�g�̐��̃J�E���g
	@return			S_OK	�����̐���
					E-FAIL	�����̎��s
*//***************************************************************************/
HRESULT MakeVertexEffect( int nCount,LPDIRECT3DDEVICE9 pDevice)
{
	for (int nNum = 0; nNum < EFFECT_NUM_PARTS; nNum++){

		// ���_���W�̐ݒ�
		SetVertexEffect(nCount,nNum);
		// ���_���W�̐ݒ�
		SetTextureEffect(nCount, nNum, 0);

		// rhw�̐ݒ�
		effectWk[nCount].pParticle[nNum].vertexWk[0].rhw =
		effectWk[nCount].pParticle[nNum].vertexWk[1].rhw =
		effectWk[nCount].pParticle[nNum].vertexWk[2].rhw =
		effectWk[nCount].pParticle[nNum].vertexWk[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		effectWk[nCount].pParticle[nNum].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		effectWk[nCount].pParticle[nNum].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		effectWk[nCount].pParticle[nNum].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		effectWk[nCount].pParticle[nNum].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	return S_OK;
}

/**************************************************************************//**
	@brief			�e�N�X�`�����W�̐ݒ�
	@param[in,out]	nCount		�G�t�F�N�g�̐��̃J�E���g
	@param[in]		nNum		�p�[�e�B�N���̐�
	@param[in]		nCntPattern	�G�t�F�N�g�p�^�[���̃J�E���g
	@return			�Ȃ�
*//***************************************************************************/
void SetTextureEffect( int nCount, int nNum, int nCntPattern )
{
	// �e�N�X�`�����W�̐ݒ�
	int x = nCntPattern % g_effectTexDevideX;
	int y = nCntPattern / g_effectTexDevideX;
	float sizeX = 1.0f / g_effectTexDevideX;
	float sizeY = 1.0f / g_effectTexDevideY;

	effectWk[nCount].pParticle[nNum].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y) * sizeY );
	effectWk[nCount].pParticle[nNum].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	effectWk[nCount].pParticle[nNum].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	effectWk[nCount].pParticle[nNum].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

/**************************************************************************//**
	@brief			���_���W�̐ݒ�
	@param[in,out]	nCount		�G�t�F�N�g�̐��̃J�E���g
	@param[in]		nNum		�p�[�e�B�N���̐�
	@return			�Ȃ�
*//***************************************************************************/
void SetVertexEffect( int nCount, int nNum )
{
	int scene = GetScene();
	if (scene == SCENE_RESULT)
	{
		// ���_���W�̐ݒ�
		effectWk[nCount].pParticle[nNum].vertexWk[0].vtx.x = effectWk[nCount].pParticle[nNum].pos.x - EFFECT_TEXTURE_SIZE_FALRE_X;
		effectWk[nCount].pParticle[nNum].vertexWk[0].vtx.y = effectWk[nCount].pParticle[nNum].pos.y - EFFECT_TEXTURE_SIZE_FALRE_Y;
		effectWk[nCount].pParticle[nNum].vertexWk[0].vtx.z = 0.0f;

		effectWk[nCount].pParticle[nNum].vertexWk[1].vtx.x = effectWk[nCount].pParticle[nNum].pos.x + EFFECT_TEXTURE_SIZE_FALRE_X;
		effectWk[nCount].pParticle[nNum].vertexWk[1].vtx.y = effectWk[nCount].pParticle[nNum].pos.y - EFFECT_TEXTURE_SIZE_FALRE_Y;
		effectWk[nCount].pParticle[nNum].vertexWk[1].vtx.z = 0.0f;

		effectWk[nCount].pParticle[nNum].vertexWk[2].vtx.x = effectWk[nCount].pParticle[nNum].pos.x - EFFECT_TEXTURE_SIZE_FALRE_X;
		effectWk[nCount].pParticle[nNum].vertexWk[2].vtx.y = effectWk[nCount].pParticle[nNum].pos.y + EFFECT_TEXTURE_SIZE_FALRE_Y;
		effectWk[nCount].pParticle[nNum].vertexWk[2].vtx.z = 0.0f;

		effectWk[nCount].pParticle[nNum].vertexWk[3].vtx.x = effectWk[nCount].pParticle[nNum].pos.x + EFFECT_TEXTURE_SIZE_FALRE_X;
		effectWk[nCount].pParticle[nNum].vertexWk[3].vtx.y = effectWk[nCount].pParticle[nNum].pos.y + EFFECT_TEXTURE_SIZE_FALRE_Y;
		effectWk[nCount].pParticle[nNum].vertexWk[3].vtx.z = 0.0f;
	}
	else
	{
		// ���_���W�̐ݒ�
		effectWk[nCount].pParticle[nNum].vertexWk[0].vtx.x = effectWk[nCount].pParticle[nNum].pos.x - EFFECT_TEXTURE_SIZE_X;
		effectWk[nCount].pParticle[nNum].vertexWk[0].vtx.y = effectWk[nCount].pParticle[nNum].pos.y - EFFECT_TEXTURE_SIZE_Y;
		effectWk[nCount].pParticle[nNum].vertexWk[0].vtx.z = 0.0f;

		effectWk[nCount].pParticle[nNum].vertexWk[1].vtx.x = effectWk[nCount].pParticle[nNum].pos.x + EFFECT_TEXTURE_SIZE_X;
		effectWk[nCount].pParticle[nNum].vertexWk[1].vtx.y = effectWk[nCount].pParticle[nNum].pos.y - EFFECT_TEXTURE_SIZE_Y;
		effectWk[nCount].pParticle[nNum].vertexWk[1].vtx.z = 0.0f;

		effectWk[nCount].pParticle[nNum].vertexWk[2].vtx.x = effectWk[nCount].pParticle[nNum].pos.x - EFFECT_TEXTURE_SIZE_X;
		effectWk[nCount].pParticle[nNum].vertexWk[2].vtx.y = effectWk[nCount].pParticle[nNum].pos.y + EFFECT_TEXTURE_SIZE_Y;
		effectWk[nCount].pParticle[nNum].vertexWk[2].vtx.z = 0.0f;

		effectWk[nCount].pParticle[nNum].vertexWk[3].vtx.x = effectWk[nCount].pParticle[nNum].pos.x + EFFECT_TEXTURE_SIZE_X;
		effectWk[nCount].pParticle[nNum].vertexWk[3].vtx.y = effectWk[nCount].pParticle[nNum].pos.y + EFFECT_TEXTURE_SIZE_Y;
		effectWk[nCount].pParticle[nNum].vertexWk[3].vtx.z = 0.0f;
	}
}

//=============================================================================
// �G�t�F�N�g�̃Z�b�g
//=============================================================================
void SetEffect(float fX, float fY, int nDuration, int type)
{
	switch (type)
	{
	case PLAYER_BLOOD:
		g_effectTexDevideX = EFFECT_TEXTURE_PLAYER_BLOOD_PATTERN_DIVIDE_X;
		g_effectTexDevideY = EFFECT_TEXTURE_PLAYER_BLOOD_PATTERN_DIVIDE_Y;
		break;

	case ENEMY_BLOOD:
		g_effectTexDevideX = EFFECT_TEXTURE_ENEMY_BLOOD_PATTERN_DIVIDE_X;
		g_effectTexDevideY = EFFECT_TEXTURE_ENEMY_BLOOD_PATTERN_DIVIDE_Y;
		break;

	case ITEM_HEAL:
		g_effectTexDevideX = EFFECT_TEXTURE_ITEM_HEAL_PATTERN_DIVIDE_X;
		g_effectTexDevideY = EFFECT_TEXTURE_ITEM_HEAL_PATTERN_DIVIDE_Y;
		break;

	case ITEM_GET:
		g_effectTexDevideX = EFFECT_TEXTURE_PLAYER_BLOOD_PATTERN_DIVIDE_X;
		g_effectTexDevideY = EFFECT_TEXTURE_PLAYER_BLOOD_PATTERN_DIVIDE_Y;
		break;

	case KILLER_APPEAR:
		g_effectTexDevideX = EFFECT_TEXTURE_KILLER_APPEAR_PATTERN_DIVIDE_X;
		g_effectTexDevideY = EFFECT_TEXTURE_KILLER_APPEAR_PATTERN_DIVIDE_Y;
		break;

	default:
		break;
	}

	// �������g�p�̃G�t�F�N�g��������������s���Ȃ�( =����ȏ�\���ł��Ȃ����Ď� )
	for (int nCount = 0; nCount < EFFECT_NUM_EFFECTS; nCount++)
	{
		if (effectWk[nCount].nUse == false)		// ���g�p��Ԃ̃G�t�F�N�g��������
		{
			effectWk[nCount].nUse = true;
			effectWk[nCount].nIsEnding = false;
			effectWk[nCount].bIsRemoveOnFinish = FALSE;

			effectWk[nCount].nDuration = nDuration;
			effectWk[nCount].pos.x = fX;			// ���W���Z�b�g
			effectWk[nCount].pos.y = fY;			// ���W���Z�b�g

			effectWk[nCount].nEffectCount = 0;
			effectWk[nCount].nElapsed = 0;
			effectWk[nCount].nEmitCounter = 0;
			effectWk[nCount].nNumFinish = 0;

			//�p�[�e�B�N���̏�����
			for (int nNum = 0; nNum < EFFECT_NUM_PARTS; nNum++)
			{
				effectWk[nCount].pParticle[nNum].Texture = g_pD3DTextureEffect[type];
				ResetParticle(nCount, nNum);
			}

			return;							// 1�Z�b�g�����̂ŏI������
		}
	}
}
