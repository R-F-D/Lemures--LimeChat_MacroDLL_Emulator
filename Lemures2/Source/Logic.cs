using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows;

namespace Lemures
{
	public class Logic
	{
		protected string	dllPath;			//DLLパス
		protected string	dllFunctionName;	//DLLから呼び出す関数名
		protected bool		isDllHookFormat	= true;

		protected string	senderNick		="";
		protected string	senderUsername	="";
		protected string	senderAddress	="";
		protected string	ircCommand		="";
		protected string	cmdTarget		="";
		protected string	cmdTrail		="";

		protected string	retValue		= "";

		//テスト実行
		public string TestDll(out int nBytes)
		{
			nBytes	= 0;
			this.retValue	= "";

			if(this.dllPath=="" || this.dllFunctionName=="")	throw new System.ArgumentException();

			//関数呼び出し
			Utility.DllFunction	df	= new Utility.DllFunction(this.dllPath, this.dllFunctionName);
			try
			{
				if(this.isDllHookFormat)	this.retValue	= df.CallDllHook(this.senderNick,this.senderUsername,this.senderAddress,this.ircCommand,this.cmdTarget,this.cmdTrail);
				else						this.retValue	= df.CallDllString(this.cmdTrail);
			}
			catch(System.DllNotFoundException)
			{
				MessageBox.Show("DLLファイルの読み込みに失敗しました。","Error",MessageBoxButton.OK,MessageBoxImage.Error);
			}
			catch(System.EntryPointNotFoundException)
			{
				MessageBox.Show("指定された関数を見つけられませんでした。","Error",MessageBoxButton.OK,MessageBoxImage.Error);
			}
			catch
			{
				throw;
			}

			//出力された文字列
			Encoding	sjis	= Encoding.GetEncoding("Shift_JIS");
			nBytes	= sjis.GetByteCount(this.retValue) +1;
			return this.retValue;
		}
		public string TestDll()
		{
			int tmp;
			return this.TestDll(out tmp);
		}

		//サーバに送信されるIRCメッセージを取得
		public string GetSendingIrcMessage(out int nBytes)
		{
			string mes;
			if(this.isDllHookFormat)	mes	= this.ircCommand+" "+this.cmdTarget+" :"+ this.cmdTrail;
			else						mes	= "$DllFunc(" + this.dllPath + "," + this.dllFunctionName + "," + this.cmdTrail + ")";

			Encoding	sjis	= Encoding.GetEncoding("Shift_JIS");
			nBytes	= sjis.GetByteCount(mes) +1;
			return mes;
		}
		//サーバに送信されるIRCメッセージを取得
		public string GetSendingIrcMessage()
		{
			int tmp;
			return this.GetSendingIrcMessage(out tmp);
		}



		//アクセサ
		public void SetDllPath(String path)			{ this.dllPath			= path;		}
		public void SetDllFunctionName(String name)	{ this.dllFunctionName	= name;		}
		public void	SetDllHookFormat(bool isDllHook){ this.isDllHookFormat	= isDllHook;}
		public void SetSenderNick(String nick)		{ this.senderNick		= nick;		}
		public void SetSenderUsername(String name)	{ this.senderUsername	= name;		}
		public void SetSenderAddress(String addr)	{ this.senderAddress	= addr;		}
		public void SetIrcCommand(String cmd)		{ this.ircCommand		= cmd;		}
		public void SetCmdTarget(String target)		{ this.cmdTarget		= target;	}
		public void SetCmdTrail(String trail)		{ this.cmdTrail			= trail;	}
	}
}
