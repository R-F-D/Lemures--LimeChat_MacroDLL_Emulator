--------------------------------------------------------------------------------

	Lemures - LimeChat2.x MacroDLL Emulator -

--------------------------------------------------------------------------------

▼はじめに

	このプログラムは単体では機能しません。
	Win32版LimeChat(http://limechat.net/)のマクロツールの作成を補佐するために作られた、
	DLL開発者またはLimeChatヘビーユーザ向けのソフトウェアです。

▼ソフトウェア概要

	名称		：Lemures
	バージョン	：1.2.0
	開発環境	：WindowsXP + VisualStudio 2005
	開発言語	：C++

	種別		：フリーソフトウェア
	著作権者	：R.F.D. / ODプロジェクト
	ライセンス	：修正BSD


▼対応しているLimeChatマクロ機能

	マクロアクション
		(1)DllHook		：Lime2.xでのみ使用可能

	マクロ関数
		(2)$DllString	：Lime1.x、Lime2.xの両方で使用可能
		(3)$DllFunc		：Lime2.xでのみ使用可能
	
	ただし、$DllFuncについては、$DllStringと完全に互換性がありますので、
	Lemuresではこの2つを同一視し、$DllStringとして扱います。


▼リファレンス

	コマンドプロンプト（DOS窓）よりLemures.exeを起動すると
	DLLの関数を呼び出すための設定を入力します。

		共通設定
			(1) DLLファイルのパス
			(2) 呼び出す関数の名前
			(3) 呼び出す関数の種類（ [1] DllHook / [2] DllString ）

		DllHookエミュレート時の設定
			(4) 送信者のニックネーム（SenderNick）
			(5) 送信者のユーザ名（SenderUsername）
			(6) 送信者のアドレス（SenderAddress）
			(7) 送信されるコマンド（Command）
			(8) 対象チャンネル等（Target）
			(9) コマンドに付加される文字列（Trail）
		
		DllStringエミュレート時の設定
			(10)関数に渡される文字列（Input）

	
	(3)では、1（DllHook）または 2（DllString）を入力してください。
	間違った入力を行うとフリーズしたり強制終了する可能性があります。

	(4)～(10)は、それぞれ呼び出す関数の仮引数に対応しています。
	括弧内の文字列がその名前です。
	詳細はLimeChatのヘルプを参照してください。

	(4)～(8)は、DllHook機能のエミュレート時にのみ設定します。
	(9)は、Privmsgコマンドで言うところの発言内容にあたります。
	
	(10)は関数に渡される文字列です。
	DllHookエミュレート時のTrailとは異なり、ここの内容だけしか渡されません。
	そのため、$DllStringの使い方によっては、
	この中に対象チャンネルや発言者の名前といった情報も含めておき、
	DLLの関数の中でこれらを自前で解析しなければならないでしょう。

	なお、これらの設定については、初期化ファイルを用意することで
	コンソールからの入力を省略することも可能です。


▼初期化ファイル

	カレントディレクトリに初期化ファイルLemures.iniを用意することで
	Lemures.exe起動時に設定を入力しなくても良いようになります。
	Function、Trail、Function２つ以外は設定しておいたほうが無難でしょう。


	[Common]
		DllPath			：DLLのパス
		FunctionName	：関数名
		FunctionType	：関数のタイプ（[1] DllHook / [2] DllString）

	[Parameter]
		SenderNick		：ニックネーム
		SenderUsername	：ユーザ名
		SenderAddress	：アドレス
		Command			：コマンド
		Target			：対象
		Trail			：（DllHook時）  コマンドの最後に付加される文字列
						　（DllString時）関数に渡される文字列	
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
	特に、$DllStringでチャンネル名などを含めるときには必須でしょう。


▼同梱DLLファイルについて

	SampleDll.dllというサンプルファイルを用意しました。
	以下のような文字列がOutputに返ってくるだけの簡単なプログラムです。
	
	DllHook形式
		　関数名	：FuncHook
		　出力		：NOTICE （チャンネル名） :FuncHook() was run.

	DllString形式
		　関数名	：FuncString
		　出力		：FuncString() was run.


▼免責とライセンス

	license.txt をご覧ください。


▼開発履歴

	2013/02/03	Version 1.2.0	ライセンスを修正BSDに変更。ファイル構成を変更。
	2007/06/18	Version 1.1.0	$DllStringに対応、それに伴いパラメータなどを修正
	2007/01/18	Version 1.0.1	スペルミスを修正
	2007/01/16	Version 1.0.0	初リリース
	2007/01/04	Version 0.9.0	一応の完成
	2007/01/03	開発開始

