#include "pch.h"
#include "plugin_64.h"

namespace Date {
	extern "C" {
		void dateProc1();
		void dateProc1V1400();
		uintptr_t dateProc1ReturnAddress;
		uintptr_t dateProc1CallAddress1;
		uintptr_t dateProc1CallAddress2;
		uintptr_t dateProc1CallAddress3;
		uintptr_t dateProc1Separator1;
		uintptr_t dateProc1Separator2;

		void dateProc2();
		uintptr_t dateProc2ReturnAddress;
		uintptr_t dateProc2CallAddress1;
		uintptr_t dateProc2CallAddress2;
	}

	const char* dateProc1Separator1Year = u8"年";
	const char* dateProc1Separator1Day = u8"日";

	DllError dateProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v2_0_4_0:
			break;

		case v1_4_0_0:
		case v1_4_1_0:
		case v1_4_2_0:
		case v1_5_0_0:
		case v1_5_2_0:
			// lea     ebx, [rax+1]
			BytePattern::temp_instance().find_pattern("8D 58 01 8B D6 48 8D 4D 08");
			if (BytePattern::temp_instance().has_size(1, u8"日付表記を変更")) {
				dateProc1Separator1 = (uintptr_t)dateProc1Separator1Year;
				dateProc1Separator2 = (uintptr_t)dateProc1Separator1Day;

				// mov     [rsp+168h+var_108], 0Fh
				uintptr_t address = BytePattern::temp_instance().get_first().address(0xF);

				// or      r9, 0FFFFFFFFFFFFFFFFh
				dateProc1ReturnAddress = address + 0xAB;

				Injector::MakeJMP(address, dateProc1V1400, true);

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
		case v1_3_2_0:
			// lea     ebx, [rax+1]
			BytePattern::temp_instance().find_pattern("8D 58 01 41 8B D6 48 8D 4D 08");
			if (BytePattern::temp_instance().has_size(1, u8"日付表記を変更")) {
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

	DllError dateProc2Injector(RunOptions options) {
		DllError e = {};
		int match_count = 2;

		switch (options.version) {
		case v2_0_4_0:
			break;
		case v1_5_2_0:
		case v1_5_0_0:
			match_count = 1;
		case v1_3_2_0:
		case v1_4_0_0:
		case v1_4_1_0:
		case v1_4_2_0:
			// lea     rdx, [rsp+128h+var_E0]
			BytePattern::temp_instance().find_pattern("48 8D 54 24 48 48 8B CE E8 ? ? ? ? 90 49 83 C9 FF");
			if (BytePattern::temp_instance().has_size(match_count, u8"西暦日付表記を変更")) {

				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {xxxxx}
				dateProc2CallAddress2 = Injector::GetBranchDestination(address + 8).as_int();

				// 短絡する jmp xx
				Injector::WriteMemory(address, 0xEB,true);
				Injector::WriteMemory(address+1, 0x1F,true);
			}
			else {
				e.unmatch.dateProc2Injector = true;
			}
			break;
		default:
			e.version.dateProc2Injector = true;
		}

		switch (options.version) {
		case v2_0_4_0:
			break;
		case v1_3_2_0:
		case v1_4_0_0:
		case v1_4_1_0:
		case v1_4_2_0:
		case v1_5_0_0:
		case v1_5_2_0:
			// lea     ebx, [rax+1]
			BytePattern::temp_instance().find_pattern("8D 58 01 48 C7 45 A0 0F 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"西暦日付表記を変更")) {

				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {xxxxx} / append
				dateProc2CallAddress1 = Injector::GetBranchDestination(address + 0xA6).as_int();

				// mov     r8, [rbp-40h]
				dateProc2ReturnAddress = address + 0xAC;

				Injector::MakeJMP(address, dateProc2, true);
			}
			else {
				e.unmatch.dateProc2Injector = true;
			}
			break;
		default:
			e.version.dateProc2Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= dateProc1Injector(options);
		result |= dateProc2Injector(options);

		return result;
	}
}