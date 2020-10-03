EESchema Schematic File Version 4
EELAYER 30 0
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
L Device:Battery BT1
U 1 1 5F780761
P 1300 1200
F 0 "BT1" H 950 1350 50  0000 L CNN
F 1 "AA batts" H 850 1200 50  0000 L CNN
F 2 "" V 1300 1260 50  0001 C CNN
F 3 "~" V 1300 1260 50  0001 C CNN
	1    1300 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5F7824C1
P 1300 1500
F 0 "#PWR0101" H 1300 1250 50  0001 C CNN
F 1 "GND" H 1305 1327 50  0000 C CNN
F 2 "" H 1300 1500 50  0001 C CNN
F 3 "" H 1300 1500 50  0001 C CNN
	1    1300 1500
	1    0    0    -1  
$EndComp
$Comp
L _mysyms:DD0405MA U1
U 1 1 5F780BB7
P 2550 1000
F 0 "U1" H 2550 1242 50  0000 C CNN
F 1 "DD0405MA" H 2550 1151 50  0000 C CNN
F 2 "DD0405MA" H 2550 1225 50  0001 C CIN
F 3 "https://datasheet.lcsc.com/szlcsc/Nanjing-Micro-One-Elec-ME2108A33M3G_C236804.pdf" H 2550 950 50  0001 C CNN
	1    2550 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1000 2250 1000
$Comp
L power:GND #PWR0102
U 1 1 5F781507
P 2550 1400
F 0 "#PWR0102" H 2550 1150 50  0001 C CNN
F 1 "GND" H 2555 1227 50  0000 C CNN
F 2 "" H 2550 1400 50  0001 C CNN
F 3 "" H 2550 1400 50  0001 C CNN
	1    2550 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 1400 2550 1300
$Comp
L Device:CP1_Small C1
U 1 1 5F782867
P 3050 1100
F 0 "C1" H 3050 1400 50  0000 C CNN
F 1 "2200uF" H 3050 1300 50  0000 C CNN
F 2 "" H 3050 1100 50  0001 C CNN
F 3 "~" H 3050 1100 50  0001 C CNN
	1    3050 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5F784ED8
P 3400 1100
F 0 "C2" H 3400 1400 50  0000 C CNN
F 1 "10uF" H 3400 1300 50  0000 C CNN
F 2 "" H 3400 1100 50  0001 C CNN
F 3 "~" H 3400 1100 50  0001 C CNN
	1    3400 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 1000 3050 1000
$Comp
L power:GND #PWR0103
U 1 1 5F78959B
P 3200 1400
F 0 "#PWR0103" H 3200 1150 50  0001 C CNN
F 1 "GND" H 3205 1227 50  0000 C CNN
F 2 "" H 3200 1400 50  0001 C CNN
F 3 "" H 3200 1400 50  0001 C CNN
	1    3200 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 1200 3200 1200
Wire Wire Line
	3050 1000 3400 1000
Connection ~ 3050 1000
Wire Wire Line
	3200 1200 3200 1400
Connection ~ 3200 1200
Wire Wire Line
	3200 1200 3400 1200
Wire Wire Line
	3400 1000 3650 1000
Connection ~ 3400 1000
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5F78A931
P 1300 1450
F 0 "#FLG02" H 1300 1525 50  0001 C CNN
F 1 "PWR_FLAG" V 1300 1577 50  0000 L CNN
F 2 "" H 1300 1450 50  0001 C CNN
F 3 "~" H 1300 1450 50  0001 C CNN
	1    1300 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1300 1500 1300 1450
Connection ~ 1300 1450
Wire Wire Line
	1300 1450 1300 1400
$Comp
L power:+3V3 #PWR0104
U 1 1 5F78E3C2
P 3650 1000
F 0 "#PWR0104" H 3650 850 50  0001 C CNN
F 1 "+3V3" H 3665 1173 50  0000 C CNN
F 2 "" H 3650 1000 50  0001 C CNN
F 3 "" H 3650 1000 50  0001 C CNN
	1    3650 1000
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5F78F6B0
P 1300 1000
F 0 "#FLG0101" H 1300 1075 50  0001 C CNN
F 1 "PWR_FLAG" H 1300 1173 50  0000 C CNN
F 2 "" H 1300 1000 50  0001 C CNN
F 3 "~" H 1300 1000 50  0001 C CNN
	1    1300 1000
	1    0    0    -1  
$EndComp
Connection ~ 1300 1000
$Comp
L Transistor_BJT:BC327 Q1
U 1 1 5F78C4AB
P 1900 2400
F 0 "Q1" H 2091 2354 50  0000 L CNN
F 1 "BC327" H 2091 2445 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 2100 2325 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/BC327-D.PDF" H 1900 2400 50  0001 L CNN
	1    1900 2400
	1    0    0    1   
$EndComp
$Comp
L power:+3V3 #PWR0105
U 1 1 5F78E830
P 2000 2200
F 0 "#PWR0105" H 2000 2050 50  0001 C CNN
F 1 "+3V3" H 2015 2373 50  0000 C CNN
F 2 "" H 2000 2200 50  0001 C CNN
F 3 "" H 2000 2200 50  0001 C CNN
	1    2000 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R1
U 1 1 5F78FD80
P 1600 2400
F 0 "R1" V 1500 2400 50  0000 C CNN
F 1 "1k" V 1700 2400 50  0000 C CNN
F 2 "" H 1600 2400 50  0001 C CNN
F 3 "~" H 1600 2400 50  0001 C CNN
	1    1600 2400
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_SPST SW1
U 1 1 5F792B65
P 1150 2400
F 0 "SW1" H 1000 2500 50  0000 C CNN
F 1 "sensing loop" H 1200 2300 50  0000 C CNN
F 2 "" H 1150 2400 50  0001 C CNN
F 3 "~" H 1150 2400 50  0001 C CNN
	1    1150 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 2400 1500 2400
$Comp
L power:GND #PWR01
U 1 1 5F793765
P 850 2450
F 0 "#PWR01" H 850 2200 50  0001 C CNN
F 1 "GND" H 855 2277 50  0000 C CNN
F 2 "" H 850 2450 50  0001 C CNN
F 3 "" H 850 2450 50  0001 C CNN
	1    850  2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  2400 850  2400
Wire Wire Line
	850  2400 850  2450
$Comp
L Device:R_Small R2
U 1 1 5F7959A8
P 2000 2850
F 0 "R2" H 1800 2900 50  0000 L CNN
F 1 "1k" H 1800 2800 50  0000 L CNN
F 2 "" H 2000 2850 50  0001 C CNN
F 3 "~" H 2000 2850 50  0001 C CNN
	1    2000 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 2600 2000 2700
$Comp
L power:GND #PWR02
U 1 1 5F7965D3
P 2000 3050
F 0 "#PWR02" H 2000 2800 50  0001 C CNN
F 1 "GND" H 2005 2877 50  0000 C CNN
F 2 "" H 2000 3050 50  0001 C CNN
F 3 "" H 2000 3050 50  0001 C CNN
	1    2000 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 3050 2000 3000
$Comp
L Device:R_Small R3
U 1 1 5F796B46
P 2300 2700
F 0 "R3" V 2200 2650 50  0000 L CNN
F 1 "10k" V 2400 2650 50  0000 L CNN
F 2 "" H 2300 2700 50  0001 C CNN
F 3 "~" H 2300 2700 50  0001 C CNN
	1    2300 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	2200 2700 2000 2700
Connection ~ 2000 2700
Wire Wire Line
	2000 2700 2000 2750
$Comp
L Device:C_Small C3
U 1 1 5F797694
P 2550 2800
F 0 "C3" H 2700 2800 50  0000 C CNN
F 1 "10uF" H 2700 2700 50  0000 C CNN
F 2 "" H 2550 2800 50  0001 C CNN
F 3 "~" H 2550 2800 50  0001 C CNN
	1    2550 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 2700 2550 2700
Connection ~ 2000 3000
Wire Wire Line
	2000 3000 2000 2950
Text GLabel 2900 2700 2    50   Input ~ 0
EN
Connection ~ 2550 2700
Wire Wire Line
	2550 2900 2550 3000
Wire Wire Line
	2550 2700 2900 2700
Wire Wire Line
	2550 3000 2000 3000
$EndSCHEMATC
