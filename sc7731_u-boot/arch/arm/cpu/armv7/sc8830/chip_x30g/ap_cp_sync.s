	AREA	Init, CODE, READONLY
	ENTRY
	CODE32

DMC_RET
	CMP	r0,#0x0
	ADREQ	r3,AP_STACK
	CMP	r0,#0x1
	ADREQ	r3,CP0_STACK
	CMP	r0,#0x2
	ADREQ	r3,CP2_STACK

	STMFD	r3!,{r4-r9,lr}

	ADR	r5,REG_CTRL_INFO_STRUCT
	MOV	r4,#0x28
	MUL	r4,r0,r4
	ADD	r4,r4,r5
	MOV	r5,#0x14
	MUL	r6,r1,r5
	ADD	r4,r4,r6
	MUL	r6,r2,r5
	ADD	r4,r4,r6

	CMP	r1,#0x1
	;*(volatile unsigned int*)0x402b012c |= (0x1 << 24);
	LDREQ	r8,[r4,#0x04]
	LDREQ	r9,[r8,#0x12c]
	ORREQ	r9,r9,#0x01000000
	STREQ	r9,[r8,#0x12c]
	BEQ	finish

	;r2=is_exit_nopd == 1
	CMP	r2,#0x1
	BNE	no_delay
	;get delay time
	ADR	r5,DELAY_TIME
	MOV	r6,r0,lsl #0x2
	ADD	r5,r5,r6
	LDR	r6,[r5]
wait_loop
	SUB	r6,r6,#0x1
	CMP	r6,#0x0
	BNE	wait_loop

no_delay
	LDR	r8,[r4,#0x04]
check_pub_fsm_0
	LDR	r9,[r8,#0xc8]
	AND	r9,r9,#0x00F0
	CMP	r9,#0x0
	BNE	check_pub_fsm_0
check_phy_fsm_0
	LDR	r9,[r8,#0xc8]
	AND	r9,r9,#0xF000
	CMP	r9,#0x0
	BNE	check_phy_fsm_0

	LDR	r5,[r4]
get_hw_spinlock
	LDR	r6,[r5]
	CMP	r6,#0x0
	BNE	get_hw_spinlock

	;set information for who taken hw spinlock
	ADR	r8,DEBUG_INFO
	MOV	r9,#0x1
	MOV	r9,r9,lsl r0
	STR	r9,[r8,#0x0]
	STR	r1,[r8,#0x4]
	STR	r2,[r8,#0x8]
	MOV	r7,#0x0
	STR	r7,[r8,#0xc]

	;check ddr phy is power down
	LDR	r8,[r4,#0x10]
	LDR	r9,[r8]
	TST	r9,#0x1
	BNE	rel_hw_spinlock
	ORR	r9,r9,#0x1
	STR	r9,[r8]

	ADR	r8,DEBUG_INFO
	ORR	r7,r7,#0x1
	STR	r7,[r8,#0xc]

	LDR	r8,[r4,#0x8]
	ADR	r5,DMC_PHY_RET_CHECK
	LDR	r5,[r5]
check_retention
	LDR	r9,[r8]
	CMP	r5,r9
	BNE	check_retention

	ADR	r8,DEBUG_INFO
	ORR	r7,r7,#0x2
	STR	r7,[r8,#0xc]

	LDR	r8,[r4,#0x0c]	;r8=dfimisc address
	MOV	r9,#0x00
	STR	r9,[r8]

	ADR	r8,DEBUG_INFO
	ORR	r7,r7,#0x4
	STR	r7,[r8,#0xc]

	LDR	r8,[r4,#0x08]	;r8=phy base address
	MOV	r9,#0x21
	STR	r9,[r8,#0x04]

check_point_0
	LDR	r9,[r8,#0x18]
	TST	r9,#0x1
	BEQ	check_point_0

check_point_1
	LDR	r9,[r8,#0x18]
	TST	r9,#0x1
	BEQ	check_point_1

	ADR	r8,DEBUG_INFO
	ORR	r7,r7,#0x8
	STR	r7,[r8,#0xc]

	LDR	r8,[r4,#0x0C]	;r8=dfimisc address
	MOV	r9,#0x1
	STR	r9,[r8]

	ADR	r8,DEBUG_INFO
	ORR	r7,r7,#0x10
	STR	r7,[r8,#0xc]

rel_hw_spinlock
	;clear who taken hw spinlock
	ADR	r8,DEBUG_INFO
	MOV	r9,#0x0
	STR	r9,[r8]

	LDR	r8,[r4]
	ADR	r9,SPINLOCK_31_MAGIC
	LDR	r9,[r9]
	STR	r9,[r8]

	;*(volatile unsigned int*)0x402b012c &= ~(0x1 << 24)
	LDR	r8,[r4,#0x04]
	LDR	r9,[r8,#0x12c]
	BIC	r9,r9,#0x01000000
	STR	r9,[r8,#0x12c]

finish
	LDMFD	r3!,{r4-r9,pc}

DMC_PHY_RET_CHECK
	DCD	0x00131154
SPINLOCK_31_MAGIC
	DCD	0x55aa10c5
REG_CTRL_INFO_STRUCT
	DCD	0x4006087c	;ap aon spinlock phys address
	DCD	0x402b0000	;ap aon phy auto en phys address
	DCD	0x30010000	;ap ddr phy base phys address
	DCD	0x300001b0	;ap umctl dfimisc phys address
	DCD	0x30040000	;ap pub busmon reg phys address

	DCD	0xF51F687c	;ap aon spinlock virt address
	DCD	0xF5230000	;ap aon phy auto ret en virt address
	DCD	0xF5170000	;ap ddr phy base virt address
	DCD	0xF51601b0	;ap umctl dfimisc virt address
	DCD	0xF519E000	;ap pub busmon reg virt address

	DCD	0x0206087c	;cp0 aon spinlock phys address
	DCD	0x022b0000	;cp0 aon phy auto en phys address
	DCD	0x01010000	;cp0 ddr phy base phys address
	DCD	0x010001b0	;cp0 umctl dfimisc phys address
	DCD	0x01040000	;cp0 pub busmon reg phys address

	DCD	0x0206087c	;cp0 aon spinlock virt address
	DCD	0x022b0000	;cp0 aon phy auto en virt address
	DCD	0x01010000	;cp0 ddr phy base virt address
	DCD	0x010001b0	;cp0 umctl dfimisc virt address
	DCD	0x01040000	;cp0 pub busmon reg virt address

	DCD	0x0206087c	;cp2 aon spinlock phys address
	DCD	0x022b0000	;cp2 aon phy auto en phys address
	DCD	0x01010000	;cp2 ddr phy base phys address
	DCD	0x010001b0	;cp2 umctl dfimisc phys address
	DCD	0x01040000	;cp2 pub busmon reg phys address

	DCD	0x0206087c	;cp2 aon spinlock virt address
	DCD	0x022b0000	;cp2 aon phy auto en virt address
	DCD	0x01010000	;cp2 ddr phy base virt address
	DCD	0x010001b0	;cp2 umctl dfimisc virt address
	DCD	0x01040000	;cp2 pub busmon reg virt address

	DCD	0x00000000	;r4
	DCD	0x00000000	;r5
	DCD	0x00000000	;r6
	DCD	0x00000000	;r7
	DCD	0x00000000	;r8
	DCD	0x00000000	;r9
	DCD	0x00000000	;lr
AP_STACK
	DCD	0x00000000	;r4
	DCD	0x00000000	;r5
	DCD	0x00000000	;r6
	DCD	0x00000000	;r7
	DCD	0x00000000	;r8
	DCD	0x00000000	;r9
	DCD	0x00000000	;lr
CP0_STACK
	DCD	0x00000000	;r4
	DCD	0x00000000	;r5
	DCD	0x00000000	;r6
	DCD	0x00000000	;r7
	DCD	0x00000000	;r8
	DCD	0x00000000	;r9
	DCD	0x00000000	;lr
CP2_STACK
DEBUG_INFO
	DCD	0x5a5aa5a5
	DCD	0x5a5aa5a5
	DCD	0x5a5aa5a5
	DCD	0x5a5aa5a5
	DCD	0x5a5aa5a5
DELAY_TIME
	DCD	0x00001000
	DCD	0x00000600
	DCD	0x00000500
	DCD	0x5a5aa5a5
	END
