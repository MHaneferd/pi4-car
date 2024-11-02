# pi4-car

Test files in python and c++ for stearing a four (4) motor car with L298N motor controller and Raspberry PI 4, using GPIO

Build motor-test.cpp:
'''bash
g++ -std=c++23 motor-test.cpp -o motor-test

sudo ./motor-test
'''

For python;
'''bash
sudo python3 motor_test.py

The programs are easy to read, and I use all the pins for varying speed,etc on the L298N controller. two motors  (left front and left back) are connected to one of the controller (Ena, i1,i2) , and the other side to Enb, i3,i4
