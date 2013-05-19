using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Web;
using System.Configuration;
using Microsoft.Win32;


namespace Lemures
{
	/// <summary>
	/// MainWindow.xaml の相互作用ロジック
	/// </summary>
	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			try
			{
				InitializeComponent();
			}
			catch(Exception e)
			{
				MessageBox.Show(e.ToString(),"Error");
				System.Environment.Exit(1);
				return;
			}

			this.LoadSettings();
			this.SaveSettings();
		}

		//DLLファイル指定の参照ボタン
		private void dllFileDialog_Click(object sender, RoutedEventArgs e)
		{
			//実行ファイルのあるディレクトリ
			Uri currentDir = new Uri(System.AppDomain.CurrentDomain.BaseDirectory);

			//ダイアログ設定
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Filter = "ダイナミックリンクライブラリ(*.dll)|*.dll|全てのファイル(*.*)|*.*";
			ofd.InitialDirectory = (this.dllFilePath.Text!="") ? this.dllFilePath.Text : System.IO.Directory.GetCurrentDirectory();	//最初に表示するディレクトリ

			if(ofd.ShowDialog()==true)
			{
				Uri target = new Uri(ofd.FileName);
				String str = currentDir.MakeRelativeUri(target).ToString();		//相対パスに
				this.dllFilePath.Text = System.Web.HttpUtility.UrlDecode(str);	//日本語パスなどのデコード
			}
		}

		//試行ボタン
		private void testing_Click(object sender, RoutedEventArgs e)
		{
			//IOテキストボックスの初期化
			this.inputMessage.Text	= "";
			this.outputMessage.Text	= "";
			this.inputMessage.IsEnabled		= false;
			this.outputMessage.IsEnabled	= false;

			if(	this.dllFilePath.Text=="" || this.dllFunctionName.Text==""	||
				(this.isDllHookFormat.IsChecked==false && this.isDllStringFormat.IsChecked==false)	)
			{
				MessageBox.Show("DLLファイル名、DLL関数名、DLL関数形式の\r\nいずれかが未指定です","Error",MessageBoxButton.OK,MessageBoxImage.Error);
				return;
			}


			Lemures.Logic logic	= new Logic();
			logic.SetDllPath(this.dllFilePath.Text);
			logic.SetDllFunctionName(this.dllFunctionName.Text);
			logic.SetDllHookFormat(this.isDllHookFormat.IsChecked==true);

			logic.SetSenderNick(this.SenderNick.Text);
			logic.SetSenderUsername(this.SenderUsername.Text);
			logic.SetSenderAddress(this.SenderAddress.Text);
			logic.SetIrcCommand(this.IrcCommand.Text);
			logic.SetCmdTarget(this.cmdTarget.Text);
			logic.SetCmdTrail(this.cmdTrail.Text);

			//文字列のバイト数
			int nInputMesBytes	= 0;
			int nOutputMesBytes	= 0;

			//入力
			this.inputMessage.Text	= logic.GetSendingIrcMessage(out nInputMesBytes);
			this.inputSize.Content	= nInputMesBytes.ToString() + " byte(s)";
			this.inputMessage.IsEnabled		= true;

			//実行
			this.outputMessage.Text	= logic.TestDll(out nOutputMesBytes);
			if(this.outputMessage.Text=="") return;
			this.outputSize.Content	= nOutputMesBytes + " byte(s)";
			this.outputMessage.IsEnabled	= true;

			if(this.playsSound.IsChecked==true)	System.Media.SystemSounds.Asterisk.Play();
			return;
		}

		//DLL関数のフォーマット
		private void dllFuncFormat_CheckedChanged(object sender, RoutedEventArgs e)
		{
			bool isEnabled	= (this.isDllHookFormat.IsChecked==true);

			this.SenderNick.IsEnabled		= isEnabled;
			this.SenderUsername.IsEnabled	= isEnabled;
			this.SenderAddress.IsEnabled	= isEnabled;
			this.IrcCommand.IsEnabled		= isEnabled;
			this.cmdTarget.IsEnabled		= isEnabled;
		}

		//設定ファイル読み込み
		private void LoadSettings()
		{
			this.dllFilePath.Text			= Properties.Settings.Default.DllPath;
			this.dllFunctionName.Text		= Properties.Settings.Default.FunctionName;
			this.isDllHookFormat.IsChecked	= Properties.Settings.Default.FunctionFormat==1;
			this.isDllStringFormat.IsChecked= Properties.Settings.Default.FunctionFormat==2;

			this.SenderNick.Text		= Properties.Settings.Default.SenderNick;
			this.SenderUsername.Text	= Properties.Settings.Default.SenderUsername;
			this.SenderAddress.Text		= Properties.Settings.Default.SenderAddress;
			this.IrcCommand.Text		= Properties.Settings.Default.IrcCommand;
			this.cmdTarget.Text			= Properties.Settings.Default.CmdTarget;
			this.cmdTrail.Text			= Properties.Settings.Default.CmdTrail;

			this.playsSound.IsChecked	= Properties.Settings.Default.PlaysSound;
		}

		//設定ファイルへの保存
		private void SaveSettings()
		{
			Properties.Settings.Default.DllPath			= this.dllFilePath.Text;
			Properties.Settings.Default.FunctionName	= this.dllFunctionName.Text;
			Properties.Settings.Default.FunctionFormat	= this.isDllHookFormat.IsChecked==true ? 1 : 2;

			Properties.Settings.Default.SenderNick		= this.SenderNick.Text;
			Properties.Settings.Default.SenderUsername	= this.SenderUsername.Text;
			Properties.Settings.Default.SenderAddress	= this.SenderAddress.Text;
			Properties.Settings.Default.IrcCommand		= this.IrcCommand.Text;
			Properties.Settings.Default.CmdTarget		= this.cmdTarget.Text;
			Properties.Settings.Default.CmdTrail		= this.cmdTrail.Text;

			Properties.Settings.Default.PlaysSound		= this.playsSound.IsChecked==true;
			Properties.Settings.Default.Save();
		}

		private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
		{
			//フォーム内容の保存
			if(this.savesForm.IsChecked==true)
			{
				this.SaveSettings();
			}
			return;
		}

		//user.config
		private void openConfig_Click(object sender, RoutedEventArgs e)
		{
			string cfgPath	= ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.PerUserRoamingAndLocal).FilePath;
			string cfgDir	= System.IO.Path.GetDirectoryName(cfgPath);

			if(System.IO.Directory.Exists(cfgDir))	System.Diagnostics.Process.Start(cfgDir);
			else									MessageBox.Show("user.configファイルが見つかりませんでした。");
		}

		//ホットキー
		private void Textbox_OnHotKey(object sender, KeyEventArgs e)
		{
			//Enterで次のフォームにフォーカス移動（最後のフォームならテスト実行）
			if(e.Key==Key.Return)
			{
				System.Windows.Controls.Control nextTextBox	= null;
				if		(sender==this.dllFilePath)		nextTextBox	= this.dllFunctionName;
				else if	(sender==this.dllFunctionName)	nextTextBox	= this.SenderNick;
				else if	(sender==this.SenderNick)		nextTextBox	= this.SenderUsername;
				else if	(sender==this.SenderUsername)	nextTextBox	= this.SenderAddress;
				else if	(sender==this.SenderAddress)	nextTextBox	= this.IrcCommand;
				else if	(sender==this.IrcCommand)		nextTextBox	= this.cmdTarget;
				else if	(sender==this.cmdTarget)		nextTextBox	= this.cmdTrail;

				//フォーカス移動またはテスト実行
				if(nextTextBox != null)	nextTextBox.Focus();
				else					this.testing_Click(sender,e);;
			}
		}

		//ホットキー
		private void OnKeyDown(object sender, KeyEventArgs e)
		{
			//F1 ヘルプ
			if(e.Key==Key.F1)
			{
				//とりあえずカレントディレクトリを開くだけ
				string currentDir = System.AppDomain.CurrentDomain.BaseDirectory;
				if(System.IO.Directory.Exists(currentDir))	System.Diagnostics.Process.Start(currentDir);
			}
			//F5：試行ボタンと等価
			else if(e.Key==Key.F5)
			{
				this.testing_Click(sender,e);
			}
		}
	}
}
