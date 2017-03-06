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
	# Frase a imprimir por el programa principal
	string: .asciiz "En un lugar de la Mancha de cuyo nombre ....\n"
	# Salto de línea
	n: .asciiz "\n"
	# Definición del mensaje: [Pulsación (n) = tecla"
	message1: .asciiz " [Pulsacion ("
	message2: .asciiz ") = "
	message3: .asciiz "] "
	# Nº de pulsaciones
	pulseCount: .word 0
	# Delay y Compare
	delay: .word 200000
	setDelay: .asciiz "\n Introduce el delay de impresion: "
	compare: .word 100
	setCompare: .asciiz "\n Introduce el valor del registro Compare: "
	# Pausa
	pause: .asciiz "\n------------- PAUSA -------------\n
Comandos: \n
	Ctrl + E: Configurar delay de impresion.\n
	Ctrl + R: Configurar hora local.\n
	Ctlr + T: Configurar valor del registro Compare.\n
	Ctrl + Q: Salir.\n
Pulsa Enter para continuar..."
	# Implementación del reloj, …
	message4: .asciiz "\n Hora Local: "
	hour1: .word 0
	hour0: .word 0
	minute1: .word 0
	minute0: .word 0
	second1: .word 0
	second0: .word 0
	sep: .asciiz ":"
	setHour: .asciiz "\n Introduce la hora: "
	setMinute: .asciiz "\n Introduce los minutos: "
	setSecond: .asciiz "\n Introduce los segundos: "
	badFormat: .asciiz "\n El formato introducido es incorrecto. Entrada ignorada.\n"

.text 0x400000
.globl main

# Programa principal
main:
	jal KbdIntrEnable		# Habilita interrupciones teclado

	jal TimerIntrEnable		# Habilita interrupciones Timer

Reset:
	la $s0, string			# $S0 = Frase

Sentence:
	jal PrintCharacter			# Salto a subrutina PrintCharacter
	jal Delay					# Salto a subrutina Delay
	j Sentence

# Fin de Programa principal

################################################################

# Utilidades
	# -> PrintCharacter(): Imprime un carácter en pantalla por consulta de estado
	# -> Delay(): Temporizador

# PrintCharacter(): Imprime un carácter en pantalla por consulta de estado
	# $t0: Carácter a imprimir
PrintCharacter:
	lb $t0, 0($s0)
	beqz $t0,Reset
	CheckScreen:
		lw $t1, scnCtr($zero)
		andi $t1, $t1, 1
		beqz $t1,CheckScreen
		sw $t0, scnDat($zero)
		addi $s0, $s0, 1
		jr $ra

# Delay(): Temporizador 0.5s aprox
	# $t0: Tiempo
Delay:
	lw $t0, delay($zero)
	Delayc:
		addi $t0, $t0, -1
		bne $t0, $zero, Delayc
		j $ra
# Fin Utilidades

################################################################

# Subrutinas relacionadas con la gestión de interrupciones
	# -> KbdIntrEnable(): Habilita la interrupción por teclado
	# -> TimerIntrEnable(): Habilita la interrupción por Timer
	# -> KbdIntr(): Rutina de servicio para atender al teclado
	# -> TimerIntr(): Rutina de servicio para atender al Timer
	# -> SetTime(): Rutina para fijar un tiempo a la hora local
	# -> TimeError(): Rutina para cuando se introduce un tiempo incorrecto
	# -> SetDelay(): Configura el Delay
	# -> SetCompare(): Configura el registro Compare
	# -> Pause(): Pausa el programa
	# -> Exit(): Sale del programa

# KbdIntrEnable(): Habilita la interrupción por teclado
KbdIntrEnable:
	# Configuración del registro Status
	mfc0 $t0, $12		# $t0 = Status
	li $t1, 0xff00		# $t1 = Bits deshabilitadores
	not $t1, $t1
	and $t0, $t0, $t1
	ori $t0, $t0, 0x801
	mtc0 $t0, $12		# Status = $t0

	# Configuración del registro de control teclado
	li $t0,2
	sw $t0, kbdCtr($zero)

	j $ra

# TimerIntrEnable(): Habilita la interrupción por Timer
TimerIntrEnable:
	# Configuración del registro Status
	mfc0 $t0, $12
	ori $t0, $t0, 0x8000
	mtc0 $t0, $12

	# Configuración del registro Count y Compare
	mtc0 $zero, $9
	lw $t0, compare($zero)
	mtc0 $t0, $11
	j $ra

# KbdIntr(): Rutina de servicio para atender al teclado
KbdIntr:
	# Actualiza Contador
	lw $t0, pulseCount($zero)
	addi $t0, $t0, 1
	sw $t0, pulseCount($zero)

	# Funciones de teclas
	lw $t0, kbdDat($zero)
	li $t1,0x05				# Ctrl + E en ASCII
	beq $t0, $t1, SetDelay
	li $t1,0x11				# Ctrl + Q en ASCII
	beq $t0, $t1, Exit
	li $t1,0x12				# Ctrl + R en ASCII
	beq $t0, $t1, SetTime
	li $t1,0x14				# Ctrl + T en ASCII
	beq $t0, $t1, SetCompare
	li $t1,0x17				# Ctrl + W en ASCII
	beq $t0, $t1, Pause

	# Impresión del mensaje
	la $a0,message1 		# Imprime primera parte del mensaje
	li $v0, 4
	syscall
	lw $a0,pulseCount		# Imprime nº de la pulsación
	li $v0,1
	syscall
	la $a0,message2			# Imprime segunda parte del mensaje
	li $v0,4
	syscall

	lw $v0, kbdDat($zero)	# Coge carácter del teclado (ver si se puede con el reg $t0)
	sw $v0, scnDat($zero)	# Envia carácter a pantalla

	la $a0,message3 		# Imprime tercera parte del mensaje
	li $v0,4
	syscall

	jr $ra

# TimerIntr(): Rutina de servicio para atender al Timer
TimerIntr:
	# Imprime la hora local
	la $a0,message4
	li $v0,4
	syscall

	# Horas
	lw $a0, hour1($zero)
	li $v0,1
	syscall
	lw $a0, hour0($zero)
	li $v0,1
	syscall

	# Separador
	la $a0,sep
	li $v0,4
	syscall

	# Minutos
	lw $a0, minute1($zero)
	li $v0,1
	syscall
	lw $a0, minute0($zero)
	li $v0,1
	syscall

	# Separador
	la $a0,sep
	li $v0,4
	syscall

	# Segundos
	lw $a0, second1($zero)
	li $v0,1
	syscall
	lw $a0, second0($zero)
	li $v0,1
	syscall

	# Nueva línea
	la $a0,n
	li $v0,4
	syscall

	# Implementación del reloj
	IncSec0:
		lw $a0, second0($zero)
		addi $a0, $a0, 1
		li $t0,9
		bgt $a0,$t0,IncSec1
		sw $a0, second0($zero)
		jr $ra
	IncSec1:
		sw $zero, second0($zero)
		lw $a0, second1($zero)
		addi $a0, $a0, 1
		li $t0,5
		bgt $a0,$t0,IncMin0
		sw $a0, second1($zero)
		jr $ra
	IncMin0:
		sw $zero, second1($zero)
		lw $a0, minute0($zero)
		addi $a0, $a0, 1
		li $t0,9
		bgt $a0,$t0,IncMin1
		sw $a0, minute0($zero)
		jr $ra
	IncMin1:
		sw $zero, minute0($zero)
		lw $a0, minute1($zero)
		addi $a0, $a0, 1
		li $t0,5
		bgt $a0,$t0,IncHour0a
		sw $a0, minute1($zero)
		jr $ra
	IncHour0a:
		sw $zero, minute1($zero)
		lw $a0, hour0($zero)
		lw $a1, hour1($zero)
		li $t0,2
		beq $a1, $t0, IncHour0b
		addi $a0, $a0, 1
		li $t0,9
		bgt $a0,$t0,IncHour1
		sw $a0, hour0($zero)
		jr $ra
	IncHour0b:
		addi $a0, $a0, 1
		li $t0,3
		bgt $a0,$t0,IncHour1
		sw $a0, hour0($zero)
		jr $ra
	IncHour1:
		sw $zero, hour0($zero)
		addi $a1, $a1, 1
		li $t0,2
		bgt $a1,$t0,IncFin
		sw $a0, hour1($zero)
		jr $ra
	IncFin:
		sw $zero, hour1($zero)
		jr $ra

# SetTime(): Rutina para fijar un tiempo a la hora local
SetTime:
	SetHourA:
		# Pide hora
		la $a0,setHour
		li $v0,4
		syscall

		li $v0,5
		syscall
		li $t0,24
		bge $v0,$t0,TimeError
		li $t0,10
		blt $v0,$t0,SetHourB

		divu $v0, $t0
		mfhi $t0
		sw $t0, hour0($zero)
		mflo $t1
		sw $t1, hour1($zero)
		j SetMinuteA

	SetHourB:
		sw $v0, hour0($zero)
		sw $zero, hour1($zero)

	SetMinuteA:
		# Pide minutos
		la $a0,setMinute
		li $v0,4
		syscall

		li $v0,5
		syscall
		li $t0,60
		bge $v0,$t0,TimeError
		li $t0,10
		blt $v0,$t0,SetMinuteB

		divu $v0, $t0
		mfhi $t0
		sw $t0, minute0($zero)
		mflo $t1
		sw $t1, minute1($zero)
		j SetSecondA

	SetMinuteB:
		sw $v0, minute0($zero)
		sw $zero, minute1($zero)

	SetSecondA:
		# Pide segundos
		la $a0,setSecond
		li $v0,4
		syscall

		li $v0,5
		syscall
		li $t0,60
		bge $v0,$t0,TimeError
		li $t0,10
		blt $v0,$t0,SetSecondB

		divu $v0, $t0
		mfhi $t0
		sw $t0, second0($zero)
		mflo $t1
		sw $t1, second1($zero)
		j SetFin

	SetSecondB:
		sw $v0, second0($zero)
		sw $zero, second1($zero)

	SetFin:
		mtc0 $zero, $9
		jr $ra

# TimeError(): Rutina para cuando se introduce un tiempo incorrecto
TimeError:
	la $a0,badFormat
	li $v0,4
	syscall
	mtc0 $zero, $9
	jr $ra

# SetDelay(): Configura el Delay
SetDelay:
	la $a0,setDelay
	li $v0,4
	syscall

	li $v0,5
	syscall
	sw $v0, delay($zero)
	jr $ra

# SetCompare(): Configura el registro Compare
SetCompare:
	la $a0,setCompare
	li $v0,4
	syscall

	li $v0,5
	syscall
	sw $v0, compare($zero)
	mtc0 $zero, $9
	mtc0 $v0, $11
	jr $ra

# Pause(): Pausa el programa
Pause:
	la $a0,pause
	li $v0,4
	syscall

	li $v0,5
	syscall

	mtc0 $zero, $9

	jr $ra

# Exit(): Sale del programa
Exit:
	li $v0,10
	syscall
