#include "pch.h"
#include "plugin_64.h"

namespace Date {
	extern "C" {
		void dateProc1();
		uintptr_t dateProc1ReturnAddress;
		uintptr_t dateProc1CallAddress;
	}

	DllError dateProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_3_2_0:
			// lea     ebx, [rax+1]
			BytePattern::temp_instance().find_pattern("8D 58 01 41 8B D6 48 8D 4D 08");
			if (BytePattern::temp_instance().has_size(1, "日付表記を変更")) {
				// mov     [rsp+168h+var_108], 0Fh
				uintptr_t address = BytePattern::temp_instance().get_first().address(0x10);

				// mov     edx, ebx
				dateProc1ReturnAddress = address + 0x56;

				Injector::MakeJMP(address, dateProc1, true);

				// call {xxxxx}
				dateProc1CallAddress = Injector::GetBranchDestination(address + 0x25).as_int();
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