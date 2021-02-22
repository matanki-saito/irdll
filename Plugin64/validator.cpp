#include "pch.h"
#include "plugin_64.h"

namespace Validator {
	void Validate(DllError e, RunOptions options) {
		if (e.unmatch.code2 > 0 || e.version.code1 > 0 || e.mod.code0 > 0) {
			const DWORD sysDefLcid = ::GetSystemDefaultLCID();

			const WCHAR* message;
			const WCHAR* caption;

			switch (sysDefLcid) {
			case MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN):
				caption = L"エラー";
				message = L""
					L"日付変更dllはこのバージョンに未対応です。修正をお待ちください";
				break;

			case MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US):
			default:
				caption = L"ERROR";
				message = L""
					L"Date format fix DLL hasn't supported this game version yet.\n"
					L"It will be updated automatically, when new one is published.\n"
					L"\n"
					L"DLL announce page:\n"
					L"https://github.com/matanki-saito/irdll";
			}

			MessageBoxW(NULL, message, caption, MB_OK);

			BytePattern::LoggingInfo("DLL [NG]");

			exit(-1);
		}
		else {
			BytePattern::LoggingInfo("DLL [OK]");
		}
	}

	bool ValidateVersion(DllError e, RunOptions options) {
		if (options.version == UNKNOWN) {
			const DWORD sysDefLcid = ::GetSystemDefaultLCID();

			const WCHAR* message;
			const WCHAR* caption;

			switch (sysDefLcid) {
			case MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN):
				caption = L"未対応バージョン";
				message = L""
					L"日付変更dllはこのバージョンに未対応です。起動を優先しますか？";
				break;

			case MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US):
			default:
				caption = L"NO SUPPORT VERSION";
				message = L""
					L"Date format fix DLL hasn't supported this game version yet.\n"
					L"Do you want to start a game?";
					break;
			}

			int result = MessageBoxW(NULL, message, caption, MB_YESNO);

			if (result == IDYES) {
				BytePattern::LoggingInfo("DLL [SKIP]");
				return false;
			}
			else {
				BytePattern::LoggingInfo("DLL [VERSION MISMATCH]");
				exit(-1);
			}
		}
		else {
			BytePattern::LoggingInfo("DLL [MATCH VERSION]");
			return true;
		}
	}
}
