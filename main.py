import os
import numpy as np
import time
import serial
import skimage
from model_setup import model_setup
from coordinates import process_image

model = model_setup()

real_test_dir = './img'
image_paths = []
for filename in os.listdir(real_test_dir):
    if os.path.splitext(filename)[1].lower() in ['.png', '.jpg', '.jpeg']:
        image_paths.append(os.path.join(real_test_dir, filename))

for image_path in image_paths:
    coordinates = process_image(image_path, model)
    for coordinate in coordinates:
        print(coordinate)

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