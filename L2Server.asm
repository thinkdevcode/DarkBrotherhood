.const

fnAssemble	dq	61EF80h
fnVAssemble	dq	61D8A0h
fnDisassemble	dq	61F510h
fnVDisassemble	dq	61F1E0h

fnBroadcastToNeighbor	dq	4E8CB0h

fnBroadcastToAllUser	dq	822F40h
fnBroadcastToAllUser_Announce	dq	823660h

fnRequestSavePledgePower	dq	52E0C0h

fnNpcServerSend	dq	6CCD40h

.code

Assemble proc
	jmp		qword ptr [fnAssemble]
Assemble endp

VAssemble	proc
	jmp		qword ptr [fnVAssemble]
VAssemble	endp

Disassemble	proc
	jmp		qword ptr [fnDisassemble]
Disassemble	endp

VDisassemble	proc
	jmp		qword ptr [fnVDisassemble]
VDisassemble	endp

BroadcastToNeighbor	proc
	jmp		qword ptr [fnBroadcastToNeighbor]
BroadcastToNeighbor	endp

BroadcastToAllUser	proc
	jmp		qword ptr [fnBroadcastToAllUser]
BroadcastToAllUser	endp

BroadcastToAllUser_Announce proc
	jmp		qword ptr [fnBroadcastToAllUser_Announce]
BroadcastToAllUser_Announce endp

RequestSavePledgePower	proc
	jmp		qword ptr [fnRequestSavePledgePower]
RequestSavePledgePower	endp

NpcServer_Send	proc
	jmp		qword ptr [fnNpcServerSend]
NpcServer_Send	endp

END