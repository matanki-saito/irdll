#include "pch.h"
#include "plugin_64.h"

using namespace std;

namespace Version {
	typedef struct {
		char ascii1;
		char dot1;
		char ascii2;
		char dot2;
		char ascii3;

		int calVer() {
			int ver = (ascii1 - 0x30) * 1000 + (ascii2 - 0x30) * 10 + (ascii3 - 0x30);
			return ver;
		}
	} Pattern;

	string versionString(IrVersion version) {
		switch (version) {
		case v1_3_2_0:
			return "v1_3_2_0";
		default:
			return "UNKNOWN";
		}
	}

	void GetVersionFromExe(RunOptions *options) {
		IrVersion version;
		
		// imperator.pdx __ ?.?.?
		BytePattern::temp_instance().find_pattern("69 6D 70 65 72 61 74 6F 72 2E 70 64 78 00 00 00 ? 2E ? 2E ? 00 00 00");
		if (BytePattern::temp_instance().count() > 0) {
			// ?を取得する
			Pattern minor = Injector::ReadMemory<Pattern>(BytePattern::temp_instance().get_first().address(16), true);

			switch (minor.calVer()) {
			case 1032:
				version = v1_3_2_0;
				break;
			default:
				version = UNKNOWN;
				break;
				;;
			}

			BytePattern::LoggingInfo(versionString(version));
		}
		else {
			version = UNKNOWN;
		}

		options->version = version;
	}
}