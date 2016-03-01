/**
 * @file	soundmng.h
 * @brief	サウンド マネージャ クラスの宣言およびインターフェイスの定義をします
 */

#pragma once

/**
 * PCM 番号
 */
enum SoundPCMNumber
{
	SOUND_PCMSEEK		= 0,		/*!< ヘッド移動 */
	SOUND_PCMSEEK1					/*!< 1クラスタ移動 */
};

#ifdef __cplusplus
extern "C"
{
#endif

UINT soundmng_create(UINT rate, UINT ms);
void soundmng_destroy(void);
void soundmng_reset(void);
void soundmng_play(void);
void soundmng_stop(void);
#define soundmng_sync()
void soundmng_setreverse(BOOL bReverse);

BRESULT soundmng_pcmplay(enum SoundPCMNumber nNum, BOOL bLoop);
void soundmng_pcmstop(enum SoundPCMNumber nNum);

#ifdef __cplusplus
}

#include "soundmng\sdbase.h"

class CSoundDeviceBase;

/**
 * サウンド プロシージャ
 */
enum SoundProc
{
	SNDPROC_MASTER		= 0,
	SNDPROC_MAIN,
	SNDPROC_TOOL,
	SNDPROC_SUBWIND
};

/**
 * @brief サウンド マネージャ クラス
 */
class CSoundMng : public ISoundData
{
public:
	static CSoundMng* GetInstance();
	static void Initialize();
	static void Deinitialize();

	CSoundMng();
	bool Open(LPCTSTR lpDevice, HWND hWnd);
	void Close();
	void Enable(SoundProc nProc);
	void Disable(SoundProc nProc);
	UINT CreateStream(UINT nSamplingRate, UINT ms);
	void DestroyStream();
	void ResetStream();
	void PlayStream();
	void StopStream();
	void SetReverse(bool bReverse);
	void LoadPCM(SoundPCMNumber nNum, LPCTSTR lpFilename);
	void SetPCMVolume(SoundPCMNumber nNum, int nVolume);
	bool PlayPCM(SoundPCMNumber nNum, BOOL bLoop);
	void StopPCM(SoundPCMNumber nNum);
	virtual UINT Get16(SINT16* lpBuffer, UINT nBufferCount);

private:
	static CSoundMng sm_instance;		//!< 唯一のインスタンスです

	/**
	 * satuation関数型宣言
	 */
	typedef void (PARTSCALL * FNMIX)(SINT16*, const SINT32*, UINT);

	CSoundDeviceBase* m_pSoundDevice;	//!< サウンド デバイス
	UINT m_nMute;						//!< ミュート フラグ
	FNMIX m_fnMix;						//!< satuation関数ポインタ
};

/**
 * インスタンスを得る
 * @return インスタンス
 */
inline CSoundMng* CSoundMng::GetInstance()
{
	return &sm_instance;
}

#endif
