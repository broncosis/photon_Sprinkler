EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:particle-boards
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L PHOTON U1
U 1 1 5795A50A
P 4750 3350
F 0 "U1" H 4750 2750 60  0000 C CNN
F 1 "PHOTON" H 4750 4050 60  0000 C CNN
F 2 "particle-boards:PHOTON" H 4750 3450 60  0001 C CNN
F 3 "" H 4750 3450 60  0000 C CNN
	1    4750 3350
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 Relays1
U 1 1 5795A8D6
P 1450 2950
F 0 "Relays1" H 1450 3300 50  0000 C CNN
F 1 "CONN_01X06" V 1550 2950 50  0000 C CNN
F 2 "Connectors_JST:JST_XH_B06B-XH-A_06x2.50mm_Straight" H 1450 2950 50  0001 C CNN
F 3 "" H 1450 2950 50  0000 C CNN
	1    1450 2950
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X06 soil1
U 1 1 5795AA23
P 1450 3700
F 0 "soil1" H 1450 4050 50  0000 C CNN
F 1 "CONN_01X06" V 1550 3700 50  0000 C CNN
F 2 "Connectors_JST:JST_XH_B06B-XH-A_06x2.50mm_Straight" H 1450 3700 50  0001 C CNN
F 3 "" H 1450 3700 50  0000 C CNN
	1    1450 3700
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X04 hc-sr4
U 1 1 5795AA6A
P 7200 3250
F 0 "hc-sr4" H 7200 3500 50  0000 C CNN
F 1 "CONN_01X04" V 7300 3250 50  0000 C CNN
F 2 "Connectors_JST:JST_XH_B04B-XH-A_04x2.50mm_Straight" H 7200 3250 50  0001 C CNN
F 3 "" H 7200 3250 50  0000 C CNN
	1    7200 3250
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 I2c1
U 1 1 5795AAED
P 7250 3800
F 0 "I2c1" H 7250 4050 50  0000 C CNN
F 1 "CONN_01X04" V 7350 3800 50  0000 C CNN
F 2 "Connectors_JST:JST_XH_B04B-XH-A_04x2.50mm_Straight" H 7250 3800 50  0001 C CNN
F 3 "" H 7250 3800 50  0000 C CNN
	1    7250 3800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5795B027
P 3900 2750
F 0 "#PWR01" H 3900 2500 50  0001 C CNN
F 1 "GND" H 3900 2600 50  0000 C CNN
F 2 "" H 3900 2750 50  0000 C CNN
F 3 "" H 3900 2750 50  0000 C CNN
	1    3900 2750
	0    1    1    0   
$EndComp
$Comp
L GND #PWR02
U 1 1 5795B055
P 1750 2700
F 0 "#PWR02" H 1750 2450 50  0001 C CNN
F 1 "GND" H 1750 2550 50  0000 C CNN
F 2 "" H 1750 2700 50  0000 C CNN
F 3 "" H 1750 2700 50  0000 C CNN
	1    1750 2700
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR03
U 1 1 5795B073
P 1700 3450
F 0 "#PWR03" H 1700 3200 50  0001 C CNN
F 1 "GND" H 1700 3300 50  0000 C CNN
F 2 "" H 1700 3450 50  0000 C CNN
F 3 "" H 1700 3450 50  0000 C CNN
	1    1700 3450
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR04
U 1 1 5795B0CD
P 7000 3950
F 0 "#PWR04" H 7000 3700 50  0001 C CNN
F 1 "GND" H 7000 3800 50  0000 C CNN
F 2 "" H 7000 3950 50  0000 C CNN
F 3 "" H 7000 3950 50  0000 C CNN
	1    7000 3950
	0    1    1    0   
$EndComp
$Comp
L GND #PWR05
U 1 1 5795B0EB
P 6950 3400
F 0 "#PWR05" H 6950 3150 50  0001 C CNN
F 1 "GND" H 6950 3250 50  0000 C CNN
F 2 "" H 6950 3400 50  0000 C CNN
F 3 "" H 6950 3400 50  0000 C CNN
	1    6950 3400
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR06
U 1 1 5795B10E
P 7000 3650
F 0 "#PWR06" H 7000 3500 50  0001 C CNN
F 1 "+3.3V" H 7000 3790 50  0000 C CNN
F 2 "" H 7000 3650 50  0000 C CNN
F 3 "" H 7000 3650 50  0000 C CNN
	1    7000 3650
	0    -1   -1   0   
$EndComp
$Comp
L +3.3V #PWR07
U 1 1 5795B14F
P 3550 2850
F 0 "#PWR07" H 3550 2700 50  0001 C CNN
F 1 "+3.3V" H 3550 2990 50  0000 C CNN
F 2 "" H 3550 2850 50  0000 C CNN
F 3 "" H 3550 2850 50  0000 C CNN
	1    3550 2850
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR08
U 1 1 5795B16D
P 1700 3950
F 0 "#PWR08" H 1700 3800 50  0001 C CNN
F 1 "+5V" H 1700 4090 50  0000 C CNN
F 2 "" H 1700 3950 50  0000 C CNN
F 3 "" H 1700 3950 50  0000 C CNN
	1    1700 3950
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR09
U 1 1 5795B19B
P 3950 2600
F 0 "#PWR09" H 3950 2450 50  0001 C CNN
F 1 "+5V" H 3950 2740 50  0000 C CNN
F 2 "" H 3950 2600 50  0000 C CNN
F 3 "" H 3950 2600 50  0000 C CNN
	1    3950 2600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR010
U 1 1 5795B1B9
P 1700 3200
F 0 "#PWR010" H 1700 3050 50  0001 C CNN
F 1 "+5V" H 1700 3340 50  0000 C CNN
F 2 "" H 1700 3200 50  0000 C CNN
F 3 "" H 1700 3200 50  0000 C CNN
	1    1700 3200
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR011
U 1 1 5795B1E6
P 6900 3100
F 0 "#PWR011" H 6900 2950 50  0001 C CNN
F 1 "+5V" H 6900 3240 50  0000 C CNN
F 2 "" H 6900 3100 50  0000 C CNN
F 3 "" H 6900 3100 50  0000 C CNN
	1    6900 3100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1650 3450 1700 3450
Wire Wire Line
	1650 2700 1750 2700
Wire Wire Line
	3950 2750 3900 2750
Wire Wire Line
	6900 3100 7000 3100
Wire Wire Line
	6950 3400 7000 3400
Wire Wire Line
	7000 3650 7050 3650
Wire Wire Line
	7000 3950 7050 3950
Wire Wire Line
	1650 3950 1700 3950
Wire Wire Line
	1650 3200 1700 3200
Wire Wire Line
	3950 2600 3950 2650
Wire Wire Line
	3800 2850 3950 2850
$Comp
L CONN_01X02 JP1
U 1 1 5795B340
P 3700 2900
F 0 "JP1" H 3700 3050 50  0000 C CNN
F 1 "CONN_01X02" V 3800 2900 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x02" H 3700 2900 50  0001 C CNN
F 3 "" H 3700 2900 50  0000 C CNN
	1    3700 2900
	-1   0    0    1   
$EndComp
Wire Wire Line
	3900 2950 3950 2950
Wire Wire Line
	3900 2850 3550 2850
Connection ~ 3900 2850
Wire Wire Line
	1650 3100 2400 3100
Wire Wire Line
	2400 3100 2400 3550
Wire Wire Line
	2400 3550 3950 3550
Wire Wire Line
	3950 3450 2500 3450
Wire Wire Line
	2500 3450 2500 3000
Wire Wire Line
	2500 3000 1650 3000
Wire Wire Line
	1650 2900 2600 2900
Wire Wire Line
	2600 2900 2600 3350
Wire Wire Line
	2600 3350 3950 3350
Wire Wire Line
	3950 3150 2750 3150
Wire Wire Line
	2750 3150 2750 2800
Wire Wire Line
	2750 2800 1650 2800
$Comp
L R R3
U 1 1 5795B6F3
P 2350 3950
F 0 "R3" V 2430 3950 50  0000 C CNN
F 1 "R" V 2350 3950 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 2280 3950 50  0001 C CNN
F 3 "" H 2350 3950 50  0000 C CNN
	1    2350 3950
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 5795B8FD
P 2350 3800
F 0 "R2" V 2430 3800 50  0000 C CNN
F 1 "R" V 2350 3800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 2280 3800 50  0001 C CNN
F 3 "" H 2350 3800 50  0000 C CNN
	1    2350 3800
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 5795B928
P 2350 3650
F 0 "R1" V 2430 3650 50  0000 C CNN
F 1 "R" V 2350 3650 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 2280 3650 50  0001 C CNN
F 3 "" H 2350 3650 50  0000 C CNN
	1    2350 3650
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 5795B975
P 2350 4100
F 0 "R4" V 2430 4100 50  0000 C CNN
F 1 "R" V 2350 4100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 2280 4100 50  0001 C CNN
F 3 "" H 2350 4100 50  0000 C CNN
	1    2350 4100
	0    1    1    0   
$EndComp
$Comp
L R R8
U 1 1 5795B9C2
P 2650 4100
F 0 "R8" V 2730 4100 50  0000 C CNN
F 1 "R" V 2650 4100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 2580 4100 50  0001 C CNN
F 3 "" H 2650 4100 50  0000 C CNN
	1    2650 4100
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 5795BA13
P 2650 3950
F 0 "R7" V 2730 3950 50  0000 C CNN
F 1 "R" V 2650 3950 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 2580 3950 50  0001 C CNN
F 3 "" H 2650 3950 50  0000 C CNN
	1    2650 3950
	0    1    1    0   
$EndComp
$Comp
L R R5
U 1 1 5795BA4C
P 2650 3650
F 0 "R5" V 2730 3650 50  0000 C CNN
F 1 "R" V 2650 3650 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 2580 3650 50  0001 C CNN
F 3 "" H 2650 3650 50  0000 C CNN
	1    2650 3650
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 5795BAB5
P 2650 3800
F 0 "R6" V 2730 3800 50  0000 C CNN
F 1 "R" V 2650 3800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 2580 3800 50  0001 C CNN
F 3 "" H 2650 3800 50  0000 C CNN
	1    2650 3800
	0    1    1    0   
$EndComp
Wire Wire Line
	2500 3650 2500 3700
Wire Wire Line
	2500 3700 3150 3700
Wire Wire Line
	3150 3700 3150 3650
Wire Wire Line
	3150 3650 3950 3650
Wire Wire Line
	2500 3800 2500 3850
Wire Wire Line
	2500 3850 3250 3850
Wire Wire Line
	3250 3850 3250 3750
Wire Wire Line
	3250 3750 3950 3750
Wire Wire Line
	3950 3850 3350 3850
Wire Wire Line
	3350 3850 3350 3900
Wire Wire Line
	3350 3900 2500 3900
Wire Wire Line
	2500 3900 2500 3950
Wire Wire Line
	2500 4100 2500 4000
Wire Wire Line
	2500 4000 3950 4000
Wire Wire Line
	3950 4000 3950 3950
Wire Wire Line
	1650 3850 1900 3850
Wire Wire Line
	1900 3850 1900 4100
Wire Wire Line
	1900 4100 2200 4100
Wire Wire Line
	1650 3750 1950 3750
Wire Wire Line
	1950 3750 1950 4000
Wire Wire Line
	1950 4000 2200 4000
Wire Wire Line
	2200 4000 2200 3950
Wire Wire Line
	2200 3800 2000 3800
Wire Wire Line
	2000 3800 2000 3650
Wire Wire Line
	2000 3650 1650 3650
Wire Wire Line
	1650 3550 2200 3550
Wire Wire Line
	2200 3550 2200 3650
$Comp
L GND #PWR012
U 1 1 5795BE03
P 2800 4100
F 0 "#PWR012" H 2800 3850 50  0001 C CNN
F 1 "GND" H 2800 3950 50  0000 C CNN
F 2 "" H 2800 4100 50  0000 C CNN
F 3 "" H 2800 4100 50  0000 C CNN
	1    2800 4100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 5795BE33
P 2800 3950
F 0 "#PWR013" H 2800 3700 50  0001 C CNN
F 1 "GND" H 2800 3800 50  0000 C CNN
F 2 "" H 2800 3950 50  0000 C CNN
F 3 "" H 2800 3950 50  0000 C CNN
	1    2800 3950
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR014
U 1 1 5795BE63
P 2800 3800
F 0 "#PWR014" H 2800 3550 50  0001 C CNN
F 1 "GND" H 2800 3650 50  0000 C CNN
F 2 "" H 2800 3800 50  0000 C CNN
F 3 "" H 2800 3800 50  0000 C CNN
	1    2800 3800
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR015
U 1 1 5795BE93
P 2800 3650
F 0 "#PWR015" H 2800 3400 50  0001 C CNN
F 1 "GND" H 2800 3500 50  0000 C CNN
F 2 "" H 2800 3650 50  0000 C CNN
F 3 "" H 2800 3650 50  0000 C CNN
	1    2800 3650
	0    -1   -1   0   
$EndComp
$Comp
L R R9
U 1 1 5795C81D
P 6150 3150
F 0 "R9" V 6230 3150 50  0000 C CNN
F 1 "R" V 6150 3150 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 6080 3150 50  0001 C CNN
F 3 "" H 6150 3150 50  0000 C CNN
	1    6150 3150
	0    1    1    0   
$EndComp
$Comp
L R R10
U 1 1 5795C8B4
P 6150 3250
F 0 "R10" V 6230 3250 50  0000 C CNN
F 1 "R" V 6150 3250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 6080 3250 50  0001 C CNN
F 3 "" H 6150 3250 50  0000 C CNN
	1    6150 3250
	0    1    1    0   
$EndComp
Wire Wire Line
	6000 3150 6000 3450
Wire Wire Line
	6300 3250 7000 3250
Wire Wire Line
	7000 3250 7000 3200
Wire Wire Line
	7000 3300 6550 3300
Wire Wire Line
	6550 3300 6550 3550
Wire Wire Line
	6550 3550 5550 3550
Wire Wire Line
	6000 3450 5550 3450
Connection ~ 6000 3250
$Comp
L GND #PWR016
U 1 1 5795CA24
P 6300 3150
F 0 "#PWR016" H 6300 2900 50  0001 C CNN
F 1 "GND" H 6300 3000 50  0000 C CNN
F 2 "" H 6300 3150 50  0000 C CNN
F 3 "" H 6300 3150 50  0000 C CNN
	1    6300 3150
	-1   0    0    1   
$EndComp
Wire Wire Line
	7050 3750 6050 3750
Wire Wire Line
	6050 3750 6050 3850
Wire Wire Line
	6050 3850 5550 3850
Wire Wire Line
	7050 3850 6150 3850
Wire Wire Line
	6150 3850 6150 3950
Wire Wire Line
	6150 3950 5550 3950
$Comp
L CONN_01X02 P1
U 1 1 5795CD95
P 3650 4650
F 0 "P1" H 3650 4800 50  0000 C CNN
F 1 "CONN_01X02" V 3750 4650 50  0000 C CNN
F 2 "Connectors_Phoenix:PhoenixContact_MC-G_02x3.81mm_Angled" H 3650 4650 50  0001 C CNN
F 3 "" H 3650 4650 50  0000 C CNN
	1    3650 4650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 5795CE80
P 3450 4600
F 0 "#PWR017" H 3450 4350 50  0001 C CNN
F 1 "GND" H 3450 4450 50  0000 C CNN
F 2 "" H 3450 4600 50  0000 C CNN
F 3 "" H 3450 4600 50  0000 C CNN
	1    3450 4600
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR018
U 1 1 5795CEB6
P 3450 4700
F 0 "#PWR018" H 3450 4550 50  0001 C CNN
F 1 "+5V" H 3450 4840 50  0000 C CNN
F 2 "" H 3450 4700 50  0000 C CNN
F 3 "" H 3450 4700 50  0000 C CNN
	1    3450 4700
	-1   0    0    1   
$EndComp
$EndSCHEMATC