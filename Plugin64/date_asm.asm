EXTERN	dateProc1ReturnAddress	:	QWORD
EXTERN	dateProc1CallAddress	:	QWORD

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

.DATA
	dateProc1Separator1		DD	" "
	dateProc1Separator2		DD	" "

.CODE
dateProc1 PROC
	mov     qword ptr [rsp + 168h -108h], 0Fh
	mov		qword ptr [rsp + 168h -110h], r15;
	mov		byte ptr [rsp + 168h - 120h], 0;
	mov		r8d, 1;
	lea     rdx, dateProc1Separator1;
	lea		rcx, [rsp + 168h - 120h];
	call	dateProc1CallAddress;
	nop;

	mov		qword ptr [rsp + 168h -128h], 0Fh;
	mov     qword ptr [rsp + 168h -130h], r15;
	mov		byte ptr [rsp + 168h -140h], 0;
	mov		r8d, 1;
	lea     rdx, dateProc1Separator2;
	lea		rcx, [rsp + 168h -140h];
	call	dateProc1CallAddress;
	nop;

	push	dateProc1ReturnAddress;
	ret;
dateProc1 ENDP
END