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
					L"未対応です";
				break;

			case MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US):
			default:
				caption = L"ERROR";
				message = L""
					L"Multibyte DLL hasn't supported this game version yet.\n"
					L"It will be updated automatically, when I publish new one.\n"
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
}