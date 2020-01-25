#include "pch.h"
#include "plugin_64.h"

namespace Date {
	extern "C" {
		void dateProc1();
		uintptr_t dateProc1ReturnAddress;
		uintptr_t dateProc1CallAddress1;
		uintptr_t dateProc1CallAddress2;
		uintptr_t dateProc1CallAddress3;
		uintptr_t dateProc1Separator1;
		uintptr_t dateProc1Separator2;
	}

	char* dateProc1Separator1Year = u8"年";
	char* dateProc1Separator1Day = u8"日";

	DllError dateProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_3_2_0:
			// lea     ebx, [rax+1]
			BytePattern::temp_instance().find_pattern("8D 58 01 41 8B D6 48 8D 4D 08");
			if (BytePattern::temp_instance().has_size(1, "日付表記を変更")) {
				dateProc1Separator1 = (uintptr_t) dateProc1Separator1Year;
				dateProc1Separator2 = (uintptr_t)dateProc1Separator1Day;
	
				// mov     [rsp+168h+var_108], 0Fh
				uintptr_t address = BytePattern::temp_instance().get_first().address(0x10);

				// or      r9, 0FFFFFFFFFFFFFFFFh
				dateProc1ReturnAddress = address + 0xAB;

				Injector::MakeJMP(address, dateProc1, true);

				// call {xxxxx} / assign
				dateProc1CallAddress1 = Injector::GetBranchDestination(address + 0x25).as_int();

				// call {xxxxx} / to_string
				dateProc1CallAddress2 = Injector::GetBranchDestination(address + 0x5D).as_int();

				// call {xxxxx} / operator+
				dateProc1CallAddress3 = Injector::GetBranchDestination(address + 0x71).as_int();
			}
			else {
				e.unmatch.dateProc1Injector = true;
			}
			break;
		default:
			e.version.dateProc1Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= dateProc1Injector(options);

		return result;
	}
}