// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"
#include "plugin_64.h"
#include "mod_download.h"

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ulReasonForCall,
                      LPVOID lpReserved){

	if (ulReasonForCall == DLL_PROCESS_ATTACH){
		BytePattern::StartLog(L"ir_jps_2");

		DllError e = {};

		// mod download
		#ifndef _DEBUG
		e |= ModDownload::Init();
		#endif

		// 設定
		RunOptions options;

		// Version取得
		Version::GetVersionFromExe(&options);
		// INIから取得
		Ini::GetOptionsFromIni(&options);

		// 日付
		e |= Date::Init(options);

		Validator::Validate(e,options);
	}else if (ulReasonForCall == DLL_PROCESS_DETACH){
		BytePattern::ShutdownLog();
	}

    return TRUE;
}

