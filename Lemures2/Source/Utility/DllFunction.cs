using System;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Collections;

namespace Utility
{
	//DLLを動的に読み込む
	class DllFunction
	{
		const string	WINAPI_DLL	= "kernel32.dll";
		protected string	dllPath;
		protected string	funcName;


		//構築s
		public DllFunction(string dllPath, string funcName)
		{
			this.dllPath	= dllPath;
			this.funcName	= funcName;
		}


		//DllHook関数の呼び出し
		public string CallDllHook(string senderNick, string senderUsername, string senderAddress, string ircCommand, string cmdTarget, string cmdTrail)
		{
			//DLL読み込み
			int hModule	= DllFunction.LoadLibrary(this.dllPath);
			if(hModule==0) throw new System.DllNotFoundException();

			//関数ポインタを取得し、デリゲートに変換
			IntPtr	pFunc	= DllFunction.GetProcAddress(hModule,this.funcName);
			if(pFunc==IntPtr.Zero) throw new System.EntryPointNotFoundException();
			DllHook Function	= (DllHook)Marshal.GetDelegateForFunctionPointer(pFunc,typeof(DllHook));

			//呼び出し
			StringBuilder	buf	= new StringBuilder(4096+1);	//*Outputを受け取るバッファ
			Function(senderNick,senderUsername,senderAddress,ircCommand,cmdTarget,cmdTrail,buf);

			//解放
			DllFunction.FreeLibrary(hModule);
			return buf.ToString();
		}

		//DllString関数の呼び出し
		public string CallDllString(string input)
		{
			//DLL読み込み
			int hModule	= DllFunction.LoadLibrary(this.dllPath);
			if(hModule==0) throw new System.DllNotFoundException();

			//関数ポインタを取得し、デリゲートに変換
			IntPtr	pFunc	= DllFunction.GetProcAddress(hModule,this.funcName);
			if(pFunc==IntPtr.Zero) throw new System.EntryPointNotFoundException();
			DllString Function	= (DllString)Marshal.GetDelegateForFunctionPointer(pFunc,typeof(DllString));

			//呼び出し
			StringBuilder	buf	= new StringBuilder(4096+1);	//*Outputを受け取るバッファ
			Function(input,buf);

			//解放
			DllFunction.FreeLibrary(hModule);
			return buf.ToString();
		}
	
		//DllHook型
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		protected delegate void DllHook(String senderNick, String senderUsername, String senderAddress, String command, String target, String trail, StringBuilder output);

		//DllString型
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		protected delegate void DllString(String input, StringBuilder output);

		//Win32 API
		[DllImport(WINAPI_DLL)]	protected static extern int LoadLibrary([MarshalAs(UnmanagedType.LPStr)] string lpFileName);
		[DllImport(WINAPI_DLL)]	protected static extern IntPtr GetProcAddress(int hModule, [MarshalAs(UnmanagedType.LPStr)] string lpProcName);
		[DllImport(WINAPI_DLL)]	protected static extern bool FreeLibrary(int hModule);
	}
}
