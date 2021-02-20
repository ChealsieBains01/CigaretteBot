# CigaretteBot
## What it does
Our robot is a modern-day Wall-E. The main objectives of the robot are to:
1. Safely drive around the sidewalks in the city
2. Detect and locate cigarette butts on the ground
3. Collect and dispose of the cigarette butts

## How we built it
Our basic idea was to build a robot with a camera that could find cigarette butts on the ground and collect those cigarette butts with a roller-mechanism. Below are more in-depth explanations of each part of our robot.
### Software
We needed a method to be able to easily detect cigarette butts on the ground, thus we used computer vision. We made use of this open-source project: [Mask R-CNN for Object Detection and Segmentation](https://github.com/matterport/Mask_RCNN) and [pre-trained weights](https://www.immersivelimit.com/datasets/cigarette-butts). We used a Raspberry Pi and a Pi Camera to take pictures of cigarettes, process the image Tensorflow, and then output coordinates of the location of the cigarette for the robot. The Raspberry Pi would then send these coordinates to an Arduino with UART.

### Hardware
The Arduino controls all the hardware on the robot, including the motors and roller-mechanism. The basic idea of the Arduino code is:
1. Drive a pre-determined path on the sidewalk
2. Wait for the Pi Camera to detect a cigarette
3. Stop the robot and wait for a set of coordinates from the Raspberry Pi to be delivered with UART
4. Travel to the coordinates and retrieve the cigarette butt
5. Repeat

We use sensors such as a gyro and accelerometer to detect the speed and orientation of our robot to know exactly where to travel.

### Mechanical
We used Solidworks to design the chassis, roller/sweeper-mechanism, and mounts for the camera of the robot. For the robot, we used VEX parts to assemble it. The mount was 3D-printed based on the Solidworks model.

## Setup Instructions:
1. Clone Repo using `git clone https://github.com/ChealsieBains01/CigaretteBot.git`
2. Run `pip install -r requirements.txt`
3. Download trained weights froom https://www.immersivelimit.com/datasets/cigarette-butts
4. Place the `mask_rcnn_cig_butts_0008.h5` file into the `Mask_RCNN` folder
5. Run `./install_venv.sh`
