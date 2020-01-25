EXTERN	dateProc1ReturnAddress	:	QWORD
EXTERN	dateProc1CallAddress1	:	QWORD
EXTERN	dateProc1CallAddress2	:	QWORD
EXTERN	dateProc1CallAddress3	:	QWORD
EXTERN  dateProc1Separator1		:	QWORD
EXTERN  dateProc1Separator2		:	QWORD

ESCAPE_SEQ_1	=	10h
ESCAPE_SEQ_2	=	11h
ESCAPE_SEQ_3	=	12h
ESCAPE_SEQ_4	=	13h
LOW_SHIFT		=	0Eh
HIGH_SHIFT		=	9h
SHIFT_2			=	LOW_SHIFT
SHIFT_3			=	900h
SHIFT_4			=	8F2h
NO_FONT			=	98Fh
NOT_DEF			=	2026h


.CODE
dateProc1 PROC
	; セパレータ１作成
	mov     qword ptr [rsp + 168h -108h], 0Fh
	mov		qword ptr [rsp + 168h -110h], r15;
	mov		byte ptr [rsp + 168h - 120h], 0;
	mov		r8d, 3;
	mov     rdx, dateProc1Separator1; 年
	lea		rcx, [rsp + 168h - 120h];
	call	dateProc1CallAddress1;
	nop;

	; セパレータ２作成
	mov		qword ptr [rsp + 168h -128h], 0Fh;
	mov     qword ptr [rsp + 168h -130h], r15;
	mov		byte ptr [rsp + 168h -140h], 0;
	mov		r8d, 3;
	mov     rdx, dateProc1Separator2;
	lea		rcx, [rsp + 168h -140h];
	call	dateProc1CallAddress1;
	nop;

	; アドレスではなくて日付の数値をそのまま渡している
	mov     edx, ebx;
	lea		rcx, [rsp + 168h - 100h];
	call	dateProc1CallAddress2;
	nop;

	; セパレータ２をくっつける
	lea		r8, [rsp + 168h - 140h];
	lea		rdx, [rsp + 168h - 100h];
	lea		rcx, [rbp-18h];
	call	dateProc1CallAddress3;
	nop;

	; 月をくっつける
	lea     rdx, [rbp+28h];
	mov		r8, rax;
	lea		rcx, [rbp-38h];
	call	dateProc1CallAddress3;
	nop;

	; セパレータ１をくっつける
	lea     rdx, [rsp + 168h -120h];
	mov     r8, rax;
	lea		rcx, [rbp-58h];
	call	dateProc1CallAddress3;
	nop;

	; 年をくっつける
	lea		rdx, [rbp+8];
	mov     r8, rax;
	lea		rcx, [rbp-78h];
	call	dateProc1CallAddress3;
	nop;

	push	dateProc1ReturnAddress;
	ret;
dateProc1 ENDP
END