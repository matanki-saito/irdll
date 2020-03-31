EXTERN	dateProc1ReturnAddress	:	QWORD
EXTERN	dateProc1CallAddress1	:	QWORD
EXTERN	dateProc1CallAddress2	:	QWORD
EXTERN	dateProc1CallAddress3	:	QWORD
EXTERN  dateProc1Separator1		:	QWORD
EXTERN  dateProc1Separator2		:	QWORD
EXTERN	dateProc2ReturnAddress	:	QWORD
EXTERN	dateProc2CallAddress1	:	QWORD
EXTERN	dateProc2CallAddress2	:	QWORD

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

;----------------------------------------------;

dateProc1V1400 PROC
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
dateProc1V1400 ENDP

;----------------------------------------------;

dateProc2 PROC
	; セパレータ１作成
	lea		ebx, [rax+1];
	mov		qword ptr [rbp - 60h], 0Fh;
	mov		[rbp-68h], r14;
	mov		byte ptr [rbp-78h], 0;
	mov		r8d, 3;
	mov		rdx, dateProc1Separator1; 年
	lea		rcx, [rbp-78h];
	call	dateProc1CallAddress1;
	nop;

	; セパレータ２作成
	mov		qword ptr [rsp + 128h - 0E8h], 0Fh;
	mov		qword ptr [rsp + 128h - 0F0h], r14;
	mov		byte ptr [rsp + 128h -100h], 0
	mov		r8d, 3;
	mov     rdx, dateProc1Separator2;
	lea		rcx, [rsp + 128h - 100h];
	call	dateProc1CallAddress1;
	nop;

	; アドレスではなくて日付の数値をそのまま渡している
	mov		edx, ebx;
	lea		rcx, [rsp + 128h - 0C0h];
	call	dateProc1CallAddress2;
	nop;

	; B.C.304年
	lea		rdx, [rsp + 128h - 0E0h];
	mov		rcx, rsi;
	call	dateProc2CallAddress2;
	nop;

	; append
	or		r9, 0FFFFFFFFFFFFFFFFh;
	xor     r8d, r8d
	mov     rdx, rax
	mov     rcx, rdi
	call    dateProc2CallAddress1;
	nop;

	; セパレータ２をくっつける
	lea		r8, [rsp + 128h - 100h];
	lea		rdx, [rsp + 128h - 0C0h];
	lea     rcx, [rsp + 128h - 0E0h]
	call	dateProc1CallAddress3;
	nop;

	; 月をくっつける
	lea		rdx, [rbp-18h];
	mov		r8, rax;
	lea		rcx, [rbp-38h];
	call	dateProc1CallAddress3;
	nop;

	; セパレータ１をくっつける
	lea		rdx, [rbp-78h];
	mov		r8, rax;
	lea		rcx, [rbp-58h];
	call	dateProc1CallAddress3;
	nop;

	; append
	or		r9, 0FFFFFFFFFFFFFFFFh;
	xor		r8d, r8d;
	mov		rdx, rax;
	mov		rcx, rdi;
	call	dateProc2CallAddress1;
	nop;

	push	dateProc2ReturnAddress;
	ret;
dateProc2 ENDP
END