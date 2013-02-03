/********************************************************************************

	Sample DLL for DllHook/DllString
	DllHook/DllStringサンプルDLL

********************************************************************************/

//include
#include <stdio.h>

//define
#define	DLLFUNC		extern "C" __declspec(dllexport)
#define	DLLARG_HOOK	const char* SenderNick,	const char* SenderUsername,	const char* SenderAddress,	\
					const char* Command,	const char* Target,			const char* Trail,			char* Output
#define	DLLARG_STR	const char* Input,		char* Output

//const
const int	BUFFER_MAX	= 4097;

//DllHook関数
DLLFUNC void FuncHook(DLLARG_HOOK)
{
	sprintf_s(Output,BUFFER_MAX,"NOTICE %s :%s() was run.",Target,__FUNCTION__);

	return;
}

//DllString関数
DLLFUNC void FuncString(DLLARG_STR)
{
	//Sendコマンドでの利用例
	sprintf_s(Output,BUFFER_MAX,"%s() was run.",__FUNCTION__);

	return;
}