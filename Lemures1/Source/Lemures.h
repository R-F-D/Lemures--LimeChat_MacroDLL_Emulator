//--------------------------------------------------------------------------------
//LimeChat2.x DllHook�G�~�����[�^
//--------------------------------------------------------------------------------
#pragma once

#include <windows.h>
#include <string>
#include <iostream>

//�^
#define	DLLARG_HOOK	const char*,const char*,const char*,const char*,const char*,const char*,char*
#define	DLLARG_STR	const char*,char*
typedef void (*DLLFUNC_HOOK)(DLLARG_HOOK);
typedef void (*DLLFUNC_STR) (DLLARG_STR);

//��{���
const std::string	SOFTWARE_NAME		= "OD Lemures: LimeChat MacroDLL Emulator -";	//�\�t�g�E�F�A��
const int			SOFTWARE_VERSION[3]	= {1,2,2};													//�\�t�g�E�F�A�̃o�[�W����
const std::string	INIFILE_NAME		= "Lemures1.ini";											//�ݒ�t�@�C���̃p�X

//�o�b�t�@�T�C�Y
const int			INIFILE_BUF_SIZE	= 1024;
const int			OUTPUT_BUF_SIZE		= (4097*16);

//�e��ݒ�
const std::string	SECTION_COMMON				= "Common";		//DLL�{�̂�A�h���X�Ɋւ�鍀��
const std::string	SECTION_PARAMETER			= "Parameter";	//DllHook�֐��Ăяo���̃p�����[�^

const std::string	KEY_COMMON_DLL_PATH			= "DllPath";			//���ʐݒ�
const std::string	KEY_COMMON_FUNC_NAME		= "FunctionName";		//
const std::string	KEY_COMMON_FUNC_TYPE		= "FunctionType";		//
const std::string	KEY_PARAMETER_NICKNAME		= "SenderNick";			//DllHook�֐��ɓn���p�����[�^
const std::string	KEY_PARAMETER_USERNAME		= "SenderUsername";		//
const std::string	KEY_PARAMETER_ADRESS		= "SenderAddress";		//
const std::string	KEY_PARAMETER_COMMAND		= "Command";			//
const std::string	KEY_PARAMETER_TARGET		= "Target";				//
const std::string	KEY_PARAMETER_TRAIL			= "Trail";				//
const std::string	KEY_PARAMETER_TRAIL_PREFIX	= "PrefixTrail";		//
const std::string	KEY_PARAMETER_TRAIL_SUFFIX	= "SuffixTrail";		//

//�֐��^�C�v
const int			FUNCTYPE_NULL			= 0;		//���w��
const int			FUNCTYPE_DLLHOOK		= 1;		//DllHook
const int			FUNCTYPE_DLLSTR			= 2;		//DllString

//���̑�
const std::string	BAR					= "------------------------------------------------------------";

//�֐�
std::string	GetPrivateProfileStringEx	(const std::string &appName, const std::string &keyName, const std::string &defaultValue,const std::string &fileName);
UINT		GetPrivateProfileIntEx		(const std::string &appName, const std::string &keyName, const int defaultValue, const std::string &fileName);
void		SetKey						(std::string &str,const std::string &nameKey);
void		SetKey						(UINT &value, const std::string &nameKey);
