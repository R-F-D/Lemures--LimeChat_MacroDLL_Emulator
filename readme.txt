--------------------------------------------------------------------------------

	OD Lemures: LimeChat MacroDLL Emulator

--------------------------------------------------------------------------------


--------------------
▼はじめに

	このプログラムは単体では機能しません。
	Win32版LimeChat( http://limechat.net/ )のマクロツールの作成を補佐するために作られた、
	DLL開発者またはLimeChatヘビーユーザ向けのソフトウェアです。


--------------------
▼ソフトウェア概要

	名称		：OD Lemures: LimeChat MacroDLL Emulator 
	著作権者	：R.F.D. / ODプロジェクト
	種別		：フリーソフトウェア
	ライセンス	：修正BSD

	2.x系：
		バージョン	：2.1.1
		開発環境	：WindowsXP / Visual C# 2010 Express
		開発言語	：C# / .NET Framework 4.0

	1.x系：
		バージョン	：1.2.1
		開発環境	：WindowsXP / Visual C++ 2010 Express
		開発言語	：C++


--------------------
▼対応しているLimeChatマクロ機能

	マクロアクション
		(1)DllHook		：Lime2.xでのみ使用可能

	マクロ関数
		(2)$DllString	：Lime1.x、Lime2.xの両方で使用可能
		(3)$DllFunc		：Lime2.xでのみ使用可能
	
	ただし、$DllFuncと$DllStringは完全に互換性がありますので、
	当ソフトウェアではこの2つを同一視しています。


--------------------
▼Lemures1.xのリファレンス

	コマンドプロンプト(いわゆるDOS窓)よりLemures1.exeを起動してください。
	DLLファイル開発の際は、デバッガに登録しておくと便利です。

	プログラムが起動したら、DLLの関数を呼び出すための設定を入力します。
	これらの設定については、初期化ファイルを用意することでコンソールからの入力を省略することも可能です。

		(1) DLLファイルのパス
				対象となるDLLファイルの名前を入力してください。フルパスと相対パスのいずれでも可能です。
				相対パス指定の場合は、実行ファイルのカレントディレクトリが正しく設定されている必要があります。

		(2) 呼び出す関数の名前
				DLL側に書かれた関数名を入力してください。戻り値や仮引数（括弧内）などは必要ありません。
				大文字/小文字は区別されますので、正しく入力してください。

		(3) 呼び出す関数の種類（ [1] DllHook / [2] $DllFunc ）
				どちらの機能をエミュレートするか選択してください。
				誤った入力を行うと、プログラムが強制終了したりフリーズする可能性があります。

		(4) 送信者のニックネーム（SenderNick）
				DllHookのパラメータ SenderNick を指定します。詳細はLimeChatのヘルプを参照してください。

		(5) 送信者のユーザ名（SenderUsername）
				DllHookのパラメータ SenderUsername を指定します。詳細はLimeChatのヘルプを参照してください。

		(6) 送信者のアドレス（SenderAddress）
				DllHookのパラメータ SenderAddress を指定します。詳細はLimeChatのヘルプを参照してください。

		(7) 送信されるコマンド（Command）
				DllHookのパラメータ Command を指定します。詳細はLimeChatのヘルプを参照してください。
				PRIVMSG等のIRCコマンドが入ります。

		(8) 対象チャンネル等（Target）
				DllHookのパラメータ Target を指定します。詳細はLimeChatのヘルプを参照してください。

		(9) コマンドに付加される文字列（Trail）
				DllHookのパラメータ Trail を指定します。詳細はLimeChatのヘルプを参照してください。
				例えばPRIVMSGコマンドなら、発言内容を格納します。

		(10)関数に渡される文字列（Input）
				$DllFunc関数に渡される文字列です。DllHookエミュレート時とは異なり、この内容しか渡されません。
				必要であれば、この中に対象チャンネルや発言者の名前といった情報も含めておき（空白区切り等）、
				DLL側でこれらを解析してください。

	※(4)～(9)はDllHookエミュレート時、(10)は$DllFuncエミュレート時にのみ設定する項目です。


--------------------
▼Lemures1.xの初期化ファイル

	カレントディレクトリに初期化ファイルLemures.iniを用意することで
	Lemures.exe起動時に設定を入力しなくても良いようになります。
	Function、Trail、Function２つ以外は設定しておいたほうが無難でしょう。


		[Common]
			DllPath			：DLLのパス
			FunctionName	：関数名
			FunctionType	：関数のタイプ（[1] DllHook / [2] DllFunc）

		[Parameter]
			SenderNick		：ニックネーム
			SenderUsername	：ユーザ名
			SenderAddress	：アドレス
			Command			：コマンド
			Target			：対象
			Trail			：（DllHook時） コマンドの最後に付加される文字列
							　（$DllFunc時）関数に渡される文字列	
			PrefixTrail		：Trailの前に自動的に付加される文字列
			SuffixTrail		：Trailの後に自動的に付加される文字列


	初期化ファイルの仕様上、一部の半角スペースは無視されます。
	空白を含めたいときは、
		PrefixTrail="#channel nikname "
	のように、ダブルクォーテーション(")で括ってください。

	PrefixTrail、およびSuffixTrailについて、
	これらを設定しておくと、Trailの前後に自動的に付加されます。
	例えば、
		Privmsg #Channel :ほげほげ
	というコマンドの場合、「:」をプリフィクスとして設定しておくと、
	毎回 Trail の項目に入力しなくて良いので便利かもしれません。
	特に、$DllFuncでチャンネル名などを含めるときには必須でしょう。


--------------------
▼Lemures2.xのリファレンス

	Lemures2.exeをダブルクリックして実行してください。
	DLLファイル開発の際は、デバッガに登録しておくと便利です。

	プログラムが起動したら、DLLの関数を呼び出すための設定を入力します。
	必要項目を入力し終えたら、「試行」ボタンを押してください。

		(1) DLLファイルのパス
				対象となるDLLファイルの名前を入力してください。

		(2) 関数の名前と種別
				DLL側に書かれた関数名を入力してください。戻り値や仮引数（括弧内）などは必要ありません。
				大文字/小文字は区別されますので、正しく入力してください。
				ラジオボタンで、どちらの機能をエミュレートするか選択してください。
				誤った入力を行うと、プログラムが強制終了したりフリーズする可能性があります。

		(4) 送信者のニックネーム（SenderNick）
				DllHookのパラメータ SenderNick を指定します。

		(5) 送信者のユーザ名（SenderUsername）
				DllHookのパラメータ SenderUsername を指定します。

		(6) 送信者のアドレス（SenderAddress）
				DllHookのパラメータ SenderAddress を指定します。

		(7) 送信されるコマンド（Command）
				DllHookのパラメータ Command を指定します。
				PRIVMSG等のIRCコマンドが入ります。

		(8) 対象チャンネル等（Target）
				DllHookのパラメータ Target を指定します。

		(9) 付加文字列（Trail）または入力文字列（Input）
				DllHookのパラメータ Trail、または$DllFunc関数に渡される文字列を指定します。


	また、以下のショートカットキーが利用できます

		(1)Enter	TrailまたはInput入力時、DLLの関数を実行する（試行ボタンと等価）。
		(2)F1		カレントディレクトリを開く。
		(3)F5		DLLの関数を実行する（試行ボタンと等価）。


--------------------
▼同梱DLLファイルについて

	SampleDll.dllというサンプルファイルを用意しました。
	以下のような文字列がOutputに返ってくるだけの簡単なプログラムです。
	
	DllHook形式
		　関数名	：FuncHook
		　出力		：NOTICE （チャンネル名） :FuncHook() was run.

	$DllFunc/$DllString形式
		　関数名	：FuncString
		　出力		：FuncString() was run.


--------------------
▼免責とライセンス

	license.txt をご覧ください。


--------------------
▼連絡先

	プロフィール
		http://goo.gl/DjCBS
	ウェブサイト
		http://goo.gl/3UBmF
	Twitter
		http://goo.gl/e1NxV


--------------------
▼開発履歴

	2013/05/20	Version 2.1.1	初期化処理で投げられる例外をトラップ
	2013/05/17	Version 2.1.0	表示するテキストの一部をWPFのリソースファイルに分離
	2013/05/04	Version 2.0.1	微調整
	2013/04/28	Version 2.0.0	2.x系を初リリース。

	2013/05/04	Version 1.2.2	微調整
	2013/04/28	Version 1.2.1	$FuncString形式を$FuncHook形式に統一。ファイル構成変更。ライセンスファイル誤字修正。
	2013/02/03	Version 1.2.0	ライセンスを修正BSDに変更。ファイル構成を変更。
	2007/06/18	Version 1.1.0	$DllStringに対応、それに伴いパラメータなどを修正
	2007/01/18	Version 1.0.1	スペルミスを修正
	2007/01/16	Version 1.0.0	初リリース
	2007/01/04	Version 0.9.0	一応の完成
	2007/01/03	開発開始

