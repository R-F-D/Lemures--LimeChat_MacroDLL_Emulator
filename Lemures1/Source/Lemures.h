//--------------------------------------------------------------------------------
//LimeChat2.x DllHookエミュレータ
//--------------------------------------------------------------------------------
#pragma once

#include <windows.h>
#include <string>
#include <iostream>

//型
#define	DLLARG_HOOK	const char*,const char*,const char*,const char*,const char*,const char*,char*
#define	DLLARG_STR	const char*,char*
typedef void (*DLLFUNC_HOOK)(DLLARG_HOOK);
typedef void (*DLLFUNC_STR) (DLLARG_STR);

//基本情報
const std::string	SOFTWARE_NAME		= "OD Lemures: LimeChat MacroDLL Emulator -";	//ソフトウェア名
const int			SOFTWARE_VERSION[3]	= {1,2,2};													//ソフトウェアのバージョン
const std::string	INIFILE_NAME		= "Lemures1.ini";											//設定ファイルのパス

//バッファサイズ
const int			INIFILE_BUF_SIZE	= 1024;
const int			OUTPUT_BUF_SIZE		= (4097*16);

//各種設定
const std::string	SECTION_COMMON				= "Common";		//DLL本体やアドレスに関わる項目
const std::string	SECTION_PARAMETER			= "Parameter";	//DllHook関数呼び出しのパラメータ

const std::string	KEY_COMMON_DLL_PATH			= "DllPath";			//共通設定
const std::string	KEY_COMMON_FUNC_NAME		= "FunctionName";		//
const std::string	KEY_COMMON_FUNC_TYPE		= "FunctionType";		//
const std::string	KEY_PARAMETER_NICKNAME		= "SenderNick";			//DllHook関数に渡すパラメータ
const std::string	KEY_PARAMETER_USERNAME		= "SenderUsername";		//
const std::string	KEY_PARAMETER_ADRESS		= "SenderAddress";		//
const std::string	KEY_PARAMETER_COMMAND		= "Command";			//
const std::string	KEY_PARAMETER_TARGET		= "Target";				//
const std::string	KEY_PARAMETER_TRAIL			= "Trail";				//
const std::string	KEY_PARAMETER_TRAIL_PREFIX	= "PrefixTrail";		//
const std::string	KEY_PARAMETER_TRAIL_SUFFIX	= "SuffixTrail";		//

//関数タイプ
const int			FUNCTYPE_NULL			= 0;		//未指定
const int			FUNCTYPE_DLLHOOK		= 1;		//DllHook
const int			FUNCTYPE_DLLSTR			= 2;		//DllString

//その他
const std::string	BAR					= "------------------------------------------------------------";

//関数
std::string	GetPrivateProfileStringEx	(const std::string &appName, const std::string &keyName, const std::string &defaultValue,const std::string &fileName);
UINT		GetPrivateProfileIntEx		(const std::string &appName, const std::string &keyName, const int defaultValue, const std::string &fileName);
void		SetKey						(std::string &str,const std::string &nameKey);
void		SetKey						(UINT &value, const std::string &nameKey);
