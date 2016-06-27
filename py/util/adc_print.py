import socket
import sys

def print_voltage_adc1():
	adc_value = 134
	adc_step = 5.6
	converted =70

	print "-----------------------------"
	for step in range ( 70,128,+2):
		converted=step		
		print "{%s, %s}" %(int(round(adc_value)), converted)
		adc_value=adc_value+adc_step


def print_voltage_adc2():
	adc_value = 325
	adc_step = 5.6
	converted = 154

	print "-----------------------------"
	for step in range ( 154,400,+2):
		converted=step		
		print "{%s, %s}" %(int(round(adc_value)), converted)
		adc_value=adc_value+adc_step
	
if __name__ == '__main__':
#	print_voltage_adc1()
	print_voltage_adc2()
	


