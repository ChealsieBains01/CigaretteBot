#!/bin/bash
#python3 -m venv --system-site-packages ./venv
#source ./venv/bin/activate 
pip3 install --upgrade pip
pip3 install -r requirements.txt
sudo apt-get install -y libhdf5-dev libc-ares-dev libeigen3-dev
#python3 -m pip install keras_applications==1.0.8 --no-deps
#python3 -m pip install keras_preprocessing==1.1.0 --no-deps
#python3 -m pip install h5py==2.9.0
sudo apt-get install -y openmpi-bin libopenmpi-dev
sudo apt-get install -y libatlas-base-dev
python3 -m pip install -U six wheel mock

pip3 install https://github.com/bitsy-ai/tensorflow-arm-bin/releases/download/v2.4.0-rc2/tensorflow-2.4.0rc2-cp37-none-linux_armv7l.whl
pip3 install --upgrade --force jupyter-console
