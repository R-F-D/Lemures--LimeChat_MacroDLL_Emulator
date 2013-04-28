/********************************************************************************

	LimeChat DllHook�G�~�����[�^

********************************************************************************/
#include "Lemures.h"


int main(int argc, char *argv[])
{
	//�\�t�g�E�F�A���̂ƃo�[�W�����̕\��
	std::cout	<< BAR << std::endl
				<< SOFTWARE_NAME << std::endl
				<< "Version " << SOFTWARE_VERSION[0] << "." << SOFTWARE_VERSION[1] << "." << SOFTWARE_VERSION[2] << std::endl
				<< BAR << std::endl;


	//�ݒ�t�@�C���̃p�X�𐶐�
	char	dirCurrent[MAX_PATH];			//�J�����g�f�B���N�g��
	::GetCurrentDirectory(MAX_PATH,dirCurrent);	//�J�����g�f�B���N�g�����擾
	std::string	pathIni	= dirCurrent;
	pathIni	+= "/" + INIFILE_NAME;

	//�e��ݒ�
	UINT		typeFunc;		//�֐��̃^�C�v
	std::string	pathDLL;		//DLL�̃p�X
	std::string	nameFunc;		//�֐���
	std::string	keyNickname;	//�j�b�N�l�[��
	std::string	keyUsername;	//���[�U�l�[��
	std::string	keyAddress;		//�A�h���X
	std::string	keyCommand;		//IRC�R�}���h
	std::string	keyTarget;		//�Ώ�
	std::string	keyTrail;		//���M������
	std::string	keyTrailPrefix;	//Trail�̑O�ɕt������镶����
	std::string	keyTrailSuffix;	//Trail�̌�ɕt������镶����

	//���ʐݒ�����[�h
	pathDLL			= GetPrivateProfileStringEx(SECTION_COMMON,	KEY_COMMON_DLL_PATH,	"",				pathIni);
	nameFunc		= GetPrivateProfileStringEx(SECTION_COMMON,	KEY_COMMON_FUNC_NAME,	"",				pathIni);
	typeFunc		= GetPrivateProfileIntEx(	SECTION_COMMON,	KEY_COMMON_FUNC_TYPE,	FUNCTYPE_NULL,	pathIni);

	//�f�t�H���g���w�肳��Ă��Ȃ���Γ��͂����߂�
	SetKey(pathDLL,		"DLL�t�@�C���̃p�X");
	SetKey(nameFunc,	"�Ăяo���֐��̖��O");
	SetKey(typeFunc,	"�Ăяo���֐��̎�ށi [1] DllHook / [2] DllFunc �j");


	//�֐��ɓn���p�����[�^�����[�h
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

		//�f�t�H���g���w�肳��Ă��Ȃ���Γ��͂����߂�
		SetKey(keyNickname,	"���M�҂̃j�b�N�l�[��(SenderNick)");
		SetKey(keyUsername,	"���M�҂̃��[�U��(SenderUsername)");
		SetKey(keyAddress,	"���M�҂̃A�h���X(SenderAddress)");
		SetKey(keyCommand,	"���M�����IRC�R�}���h(Command)");
		SetKey(keyTarget,	"�Ώۃ`�����l����(Target)");
		SetKey(keyTrail,	"�R�}���h�ɕt������镶����(Trail)");
	}
	else if	(typeFunc == FUNCTYPE_DLLSTR)	//DllString
	{
		keyTrail		= GetPrivateProfileStringEx( SECTION_PARAMETER,	KEY_PARAMETER_TRAIL,		"",	pathIni);
		keyTrailPrefix	= GetPrivateProfileStringEx( SECTION_PARAMETER,	KEY_PARAMETER_TRAIL_PREFIX,	"",	pathIni);
		keyTrailSuffix	= GetPrivateProfileStringEx( SECTION_PARAMETER,	KEY_PARAMETER_TRAIL_SUFFIX,	"",	pathIni);

		//�f�t�H���g���w�肳��Ă��Ȃ���Γ��͂����߂�
		SetKey(keyTrail,	"�֐��ɓn����镶����(Input)");
	}
	else
	{
		std::cout << "�w�肳�ꂽ�֐��̎�ނ�����������܂���B" << std::endl;
		return 0;
	}
	std::cout	<< BAR << std::endl;




	//�c�k�k�ǂݍ���
	HINSTANCE		hDLL;		//�c�k�k�̃n���h��
	DLLFUNC_HOOK	pFuncHook;	//�G�N�X�|�[�g����DllHook�֐��̃A�h���X
	DLLFUNC_STR		pFuncStr;	//�G�N�X�|�[�g����DllString�֐��̃A�h���X

	std::cout << "DLL�����[�h���܂�...";
	hDLL	= ::LoadLibrary(pathDLL.c_str());
	if(!hDLL)
	{
		std::cout << "���s" << std::endl << std::endl;
		return 1;
	}
	std::cout << "����" << std::endl;


	//�֐��|�C���^�̎擾
	std::cout << "�֐��|�C���^���擾���܂�...";
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
		std::cout << "���s" << std::endl << std::endl;
		::FreeLibrary(hDLL);
		return 1;
	}
	std::cout << "����" << std::endl;


	//�֐��̌Ăяo��
	std::string	input					= keyTrailPrefix + keyTrail + keyTrailSuffix;
	char		output[OUTPUT_BUF_SIZE]	= {0};
	std::cout	<< std::endl << "���́F" << std::endl;
	if		(typeFunc == FUNCTYPE_DLLHOOK)
	{
		std::cout	<< keyCommand << " " << keyTarget << " "<< input << std::endl;
		pFuncHook(keyNickname.c_str(),keyUsername.c_str(),keyAddress.c_str(),keyCommand.c_str(),keyTarget.c_str(),input.c_str(),output);
		std::cout	<< "�iTrail:" << input.size()+1 << "�o�C�g�j" << std::endl;
	}
	else if	(typeFunc == FUNCTYPE_DLLSTR)
	{
		std::cout	<< input << std::endl;
		pFuncStr(input.c_str(),output);
		std::cout	<< "�iInput:" << input.size()+1 << "�o�C�g�j" << std::endl;
	}
	::FreeLibrary(hDLL);

	//���ʂ̏o��
	std::cout	<< std::endl << "�o�́F" << std::endl
				<< output << std::endl
				<< "�iOutput:" << strlen(output) +1 << "�o�C�g�j" << std::endl
				<< BAR << std::endl;

	return 0;
}



//�ݒ�t�@�C�����當������擾�istd::string�Łj
std::string GetPrivateProfileStringEx(const std::string &appName, const std::string &keyName, const std::string &defaultValue,const std::string &fileName)
{
	char result[INIFILE_BUF_SIZE]	= {0};
	int szBuf	= ::GetPrivateProfileString(appName.c_str(),keyName.c_str(),defaultValue.c_str(),result,INIFILE_BUF_SIZE,fileName.c_str());

	std::string tmp	= result;
	return tmp;
}
//�ݒ�t�@�C�����琮�����擾�istd::string�Łj0
UINT GetPrivateProfileIntEx(const std::string &appName, const std::string &keyName, const int defaultValue, const std::string &fileName)
{
	return ::GetPrivateProfileInt(appName.c_str(),keyName.c_str(),defaultValue,fileName.c_str());
}


//�ݒ�t�@�C���ɏ�񂪖�����Γ��͂����߂�
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
//�ݒ�t�@�C���ɏ�񂪖�����Γ��͂����߂�
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

