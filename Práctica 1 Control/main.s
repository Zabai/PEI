.data 0xFFFF0000	# Registros de los dispositivos de entrada/salida
	# Teclado control
	kbdCtr: .word 0xFFFF0000
	# Teclado dato
	kbdDat: .word 0xFFFF0004

	# Pantalla control
	scnCtr: .word 0xFFFF0008
	# Pantalla dato
	scnDat: .word 0xFFFF000C
.data 0x10000000
	# Buffer
	buffer: .space 50
	null: .word 0
	count: .word 0

.text 0x400000
.globl main

main:
	la $s0,buffer

Teclado:
	jal LeerTeclado

	li $t0,0x13
	beq $a0, $t0, StringFinal

	sb $a0, 0($s0)
	addi $s0, $s0, 1
	j Teclado

bucle:
	nop
	j bucle


StringFinal:
	lb $t0, null($zero)
	sb $t0, 0($s0)

	li $t0,0x701 			# Interrupción pantalla en Status
	mtc0 $t0, $12

	li $t0,2				# Interrupción pantalla en el registro de control
	sw $t0, scnCtr($zero)

	j bucle

LeerTeclado:
	lw $t0, kbdCtr($zero)
	li $t1,1
	bne $t0, $t1, LeerTeclado

	lb $a0, kbdDat($zero)
	jr $ra

ScreenInterrupt:
	la $s1,buffer
	lw $t0, count($zero)
	add $s1, $s1, $t0
	lb $t1, 0($s1)

	beqz $t1,ScreenFin
	sb $t1, scnDat($zero)


	addi $t0, $t0, 1
	sw $t0, count($zero)

	jr $ra

ScreenFin:
	mtc0 $zero, $12
	j bucle