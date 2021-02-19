import os
import numpy as np
import time
import serial
import skimage
from model_setup import model_setup
from coordinates import process_image
import time
import picamera

model = model_setup()

real_test_dir = './img'
image_paths = []
arduino = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1)
arduino.flush()

detected = False

with picamera.PiCamera() as camera:
    camera.resolution = (1024, 768)
    camera.start_preview()
    # Camera warm-up time
    time.sleep(2)

def process_photo():
    with picamera.PiCamera() as camera:
        camera.capture('cigarette.jpg')
    return process_image('cigarette.jpg', model)

while True:
    coordinates = process_photo()
    print("Coordinates:" + str(coordinates) + "\n")
    if coordinates:
        if detected:
            arduino.write((str(coordinates[0]) + '\n').encode('utf-8'))
            line = arduino.readline().decode('utf-8').rstrip()
            print(line)
        else:
            arduino.write(('Detected Cigarette\n').encode('utf-8'))
            while(arduino.readline().decode('utf-8').rstrip() != 'Stopped'):
                time.sleep(1)
            detected = True
    else:
        detected = False

    time.sleep(1)

