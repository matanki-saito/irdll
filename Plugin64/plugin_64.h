#pragma once
#include "pch.h"

enum IrVersion {
	UNKNOWN = 0,
	v1_3_2_0 = 1032,
	v1_4_0_0 = 1040,
	v1_4_1_0 = 1041,
	v1_4_2_0 = 1042,
	v1_5_0_0 = 1050
};

typedef UINT64 DllErrorCode;

struct DllError{
	union {
		DllErrorCode code0;
		struct {
			bool timeout : 1;
			bool waitFailed : 1;
			bool proccessFaild : 1;
		};
	} mod;

	union {
		DllErrorCode code1;
		struct {
			bool dateProc1Injector : 1;
			bool dateProc2Injector : 1;
		};
	} version;

	union {
		DllErrorCode code2;
		struct {
			bool dateProc1Injector : 1;
			bool dateProc2Injector : 1;
		};
	} unmatch;

	void operator |= (DllError e)
	{
		this->mod.code0 |= e.mod.code0;
		this->version.code1 |= e.version.code1;
		this->unmatch.code2 |= e.unmatch.code2;
	}
};

typedef struct _ParadoxTextObject {
	union {
		char text[0x10];
		char* p;
	} t;
	UINT64 len;
	UINT64 len2;

	std::string getString() {
		if (len2 >= 0x10) {
			return std::string(t.p);
		}
		else {
			return std::string(t.text);
		}
	}

	void setString(std::string *src) {

		len = src->length();

		if (len >= 0x10) {
			len2 = 0x1F;
			auto p = (char*)calloc(len+3, sizeof(char));
			if (p != NULL) {
				memcpy(p, src->c_str(), len);
				t.p = p;
			}
		}
		else {
			memcpy(t.text, src->c_str(), len);
		}
	}

} ParadoxTextObject;

typedef struct _RunOptions {
	IrVersion version;
	bool test;
	int separateCharacterCodePoint;
} RunOptions;

namespace Version {
	void GetVersionFromExe(RunOptions *option);
}

namespace Ini {
	void GetOptionsFromIni(RunOptions *option);
}

namespace Date {
	DllError Init(RunOptions option);
}

namespace Validator {
	void Validate(DllError dllError, RunOptions options);
	bool ValidateVersion(DllError dllError, RunOptions options);
}