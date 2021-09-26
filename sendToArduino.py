import RPi.GPIO as GPIO
from lib_nrf24 import NRF24
import time
import spidev
import P3picam
motionState = False

GPIO.setmode(GPIO.BCM)

pipes = [[0xE8, 0xE8, 0xF0, 0xF0, 0xE1], [0xF0, 0xF0, 0xF0, 0xF0, 0xE1]]

radio = NRF24(GPIO, spidev.SpiDev())
radio.begin(0,17)

radio.setPayloadSize(32)
radio.setChannel(0x76)
radio.serDataRate(NRF24.BR_1MBPS)
radio.setPAlevel(NRF24.PA_MIN)

radio.setAutoAck(True)
radio.enableDynamicPayloads()
radio.enableAckPayload()

radio.openWritingPipe(pipes[0])
radio.openReadingPipe(1,pipes[1])
radio.printDetails()

while True:
	# start = time.time()
	motionState = P3picam.motion()
	print(motionState)
	radio.write(motionState)


	# while not radio.available(0):
	# 	time.sleep(1/100)

