/********************************************************************************

	LimeChat DllHookエミュレータ

********************************************************************************/
#include "Lemures.h"


int main(int argc, char *argv[])
{
	//ソフトウェア名称とバージョンの表示
	std::cout	<< BAR << std::endl
				<< SOFTWARE_NAME << std::endl
				<< "Version " << SOFTWARE_VERSION[0] << "." << SOFTWARE_VERSION[1] << "." << SOFTWARE_VERSION[2] << std::endl
				<< BAR << std::endl;


	//設定ファイルのパスを生成
	char	dirCurrent[MAX_PATH];			//カレントディレクトリ
	::GetCurrentDirectory(MAX_PATH,dirCurrent);	//カレントディレクトリを取得
	std::string	pathIni	= dirCurrent;
	pathIni	+= "/" + INIFILE_NAME;

	//各種設定
	UINT		typeFunc;		//関数のタイプ
	std::string	pathDLL;		//DLLのパス
	std::string	nameFunc;		//関数名
	std::string	keyNickname;	//ニックネーム
	std::string	keyUsername;	//ユーザネーム
	std::string	keyAddress;		//アドレス
	std::string	keyCommand;		//IRCコマンド
	std::string	keyTarget;		//対象
	std::string	keyTrail;		//送信文字列
	std::string	keyTrailPrefix;	//Trailの前に付加される文字列
	std::string	keyTrailSuffix;	//Trailの後に付加される文字列

	//共通設定をロード
	pathDLL			= GetPrivateProfileStringEx(SECTION_COMMON,	KEY_COMMON_DLL_PATH,	"",				pathIni);
	nameFunc		= GetPrivateProfileStringEx(SECTION_COMMON,	KEY_COMMON_FUNC_NAME,	"",				pathIni);
	typeFunc		= GetPrivateProfileIntEx(	SECTION_COMMON,	KEY_COMMON_FUNC_TYPE,	FUNCTYPE_NULL,	pathIni);

	//デフォルトが指定されていなければ入力を求める
	SetKey(pathDLL,		"DLLファイルのパス");
	SetKey(nameFunc,	"呼び出す関数の名前");
	SetKey(typeFunc,	"呼び出す関数の種類（ [1] DllHook / [2] DllFunc ）");


	//関数に渡すパラメータをロード
	if		(typeFunc == FUNCTYPE_DLLHOOK)			//DllHook
	{
		keyNickname		= GetPrivateProfileStringEx( SECTION_PARAMETER,	KEY_PARAMETER_NICKNAME,		"",	pathIni);
		keyUsername		= GetPrivateProfileStringEx( SECTION_PARAMETER,	KEY_PARAMETER_USERNAME,		"",	pathIni);
		keyAddress		= GetPrivateProfileStringEx( SECTION_PARAMETER,	KEY_PARAMETER_ADRESS,		"",	pathIni);
		keyCommand		= GetPrivateProfileStringEx( SECTION_PARAMETER,	KEY_PARAMETER_COMMAND,		"",	pathIni);
		keyTarget		= GetPrivateProfileStringEx( SECTION_PARAMETER,	KEY_PARAMETER_TARGET,		"",	pathIni);
		keyTrail		= GetPrivateProfileStringEx( SECTION_PARAMETER,	KEY_PARAMETER_TRAIL,		"",	pathIni);
		keyTrailPrefix	= GetPrivateProfileStringEx( SECTION_PARAMETER,	KEY_PARAMETER_TRAIL_PREFIX,	"",	pathIni);
		keyTrailSuffix	= GetPrivateProfileStringEx( SECTION_PARAMETER,	KEY_PARAMETER_TRAIL_SUFFIX,	"",	pathIni);

		//デフォルトが指定されていなければ入力を求める
		SetKey(keyNickname,	"送信者のニックネーム(SenderNick)");
		SetKey(keyUsername,	"送信者のユーザ名(SenderUsername)");
		SetKey(keyAddress,	"送信者のアドレス(SenderAddress)");
		SetKey(keyCommand,	"送信されるIRCコマンド(Command)");
		SetKey(keyTarget,	"対象チャンネル等(Target)");
		SetKey(keyTrail,	"コマンドに付加される文字列(Trail)");
	}
	else if	(typeFunc == FUNCTYPE_DLLSTR)	//DllString
	{
		keyTrail		= GetPrivateProfileStringEx( SECTION_PARAMETER,	KEY_PARAMETER_TRAIL,		"",	pathIni);
		keyTrailPrefix	= GetPrivateProfileStringEx( SECTION_PARAMETER,	KEY_PARAMETER_TRAIL_PREFIX,	"",	pathIni);
		keyTrailSuffix	= GetPrivateProfileStringEx( SECTION_PARAMETER,	KEY_PARAMETER_TRAIL_SUFFIX,	"",	pathIni);

		//デフォルトが指定されていなければ入力を求める
		SetKey(keyTrail,	"関数に渡される文字列(Input)");
	}
	else
	{
		std::cout << "指定された関数の種類が正しくありません。" << std::endl;
		return 0;
	}
	std::cout	<< BAR << std::endl;




	//ＤＬＬ読み込み
	HINSTANCE		hDLL;		//ＤＬＬのハンドル
	DLLFUNC_HOOK	pFuncHook;	//エクスポートしたDllHook関数のアドレス
	DLLFUNC_STR		pFuncStr;	//エクスポートしたDllString関数のアドレス

	std::cout << "DLLをロードします...";
	hDLL	= ::LoadLibrary(pathDLL.c_str());
	if(!hDLL)
	{
		std::cout << "失敗" << std::endl << std::endl;
		return 1;
	}
	std::cout << "成功" << std::endl;


	//関数ポインタの取得
	std::cout << "関数ポインタを取得します...";
	bool isSuccess	= false;
	if(typeFunc == FUNCTYPE_DLLHOOK)
	{
		pFuncHook	= (DLLFUNC_HOOK)::GetProcAddress(hDLL,nameFunc.c_str());
		if(pFuncHook) isSuccess	= true;
	}
	else if(typeFunc == FUNCTYPE_DLLSTR)
	{
		pFuncStr	= (DLLFUNC_STR)::GetProcAddress(hDLL,nameFunc.c_str());
		if(pFuncStr) isSuccess	= true;
	}

	if(!isSuccess)
	{
		std::cout << "失敗" << std::endl << std::endl;
		::FreeLibrary(hDLL);
		return 1;
	}
	std::cout << "成功" << std::endl;


	//関数の呼び出し
	std::string	input					= keyTrailPrefix + keyTrail + keyTrailSuffix;
	char		output[OUTPUT_BUF_SIZE]	= {0};
	std::cout	<< std::endl << "入力：" << std::endl;
	if		(typeFunc == FUNCTYPE_DLLHOOK)
	{
		std::cout	<< keyCommand << " " << keyTarget << " "<< input << std::endl;
		pFuncHook(keyNickname.c_str(),keyUsername.c_str(),keyAddress.c_str(),keyCommand.c_str(),keyTarget.c_str(),input.c_str(),output);
		std::cout	<< "（Trail:" << input.size()+1 << "バイト）" << std::endl;
	}
	else if	(typeFunc == FUNCTYPE_DLLSTR)
	{
		std::cout	<< input << std::endl;
		pFuncStr(input.c_str(),output);
		std::cout	<< "（Input:" << input.size()+1 << "バイト）" << std::endl;
	}
	::FreeLibrary(hDLL);

	//結果の出力
	std::cout	<< std::endl << "出力：" << std::endl
				<< output << std::endl
				<< "（Output:" << strlen(output) +1 << "バイト）" << std::endl
				<< BAR << std::endl;

	return 0;
}



//設定ファイルから文字列を取得（std::string版）
std::string GetPrivateProfileStringEx(const std::string &appName, const std::string &keyName, const std::string &defaultValue,const std::string &fileName)
{
	char result[INIFILE_BUF_SIZE]	= {0};
	int szBuf	= ::GetPrivateProfileString(appName.c_str(),keyName.c_str(),defaultValue.c_str(),result,INIFILE_BUF_SIZE,fileName.c_str());

	std::string tmp	= result;
	return tmp;
}
//設定ファイルから整数を取得（std::string版）0
UINT GetPrivateProfileIntEx(const std::string &appName, const std::string &keyName, const int defaultValue, const std::string &fileName)
{
	return ::GetPrivateProfileInt(appName.c_str(),keyName.c_str(),defaultValue,fileName.c_str());
}


//設定ファイルに情報が無ければ入力を求める
void SetKey(std::string &str,const std::string &nameKey)
{
	std::cout << nameKey << "... ";

	if(str.empty() || str=="")
	{
		std::cin.sync();

		char buf[INIFILE_BUF_SIZE]={0};
		std::cin.getline(buf,INIFILE_BUF_SIZE);
		str	= buf;
	}
	else
	{
		std::cout << str << std::endl;
	}

}
//設定ファイルに情報が無ければ入力を求める
void SetKey(UINT &value, const std::string &nameKey)
{
	std::cout << nameKey << "... ";

	if(value==FUNCTYPE_NULL)
	{
		std::cin.sync();

		std::string	str;
		std::cin >> str;
		value	= ::atoi(str.c_str());
	}
	else
	{
		std::cout << value << std::endl;
	}
}

