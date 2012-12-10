.const

fnCSocketSend	dq	7D5F10h
fnCSocketSendV	dq	7D5D40h

fnCIOSocketClose	dq	61E540h

.code

Send	proc
	jmp		qword ptr [fnCSocketSend]
Send	endp

SendV	proc
	jmp		qword ptr [fnCSocketSendV]
SendV	endp

Close	proc
	jmp		qword ptr [fnCIOSocketClose]
Close	endp

GetAddress	proc
	mov		eax, [ecx + 0B0h]
	
	ret
GetAddress	endp

GetUser	proc
	mov		eax, [ecx + 158h]
	
	ret
GetUser	endp

END