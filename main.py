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
#for filename in os.listdir(real_test_dir):
    #if os.path.splitext(filename)[1].lower() in ['.png', '.jpg', '.jpeg']:
        #image_paths.append(os.path.join(real_test_dir, filename))

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
    # 2 Cigarette centered, start roller
    if not coordinates:
        continue

    time.sleep(3)

# Serial Communication
# arduino = serial.Serial(port='COM3', baudrate=115200, timeout=.1)
# def write_read(x):
#     arduino.write(bytes(x, 'utf-8'))
#     time.sleep(0.05)
#     data = arduino.readline()
#     return data
#
# while True:
#     num = input("Enter a number: ")
#     value = write_read(num)
#     print(value)