# RGB LED Cube

# board git conf:
git setup: https://jnavila.github.io/plotkicadsch/
example: https://github.com/John-Nagle/ttyloopdriver


# programmer examples
Arduino: get terminal: avrdude -c stk500v1 -b 19200 -P /dev/ttyACM0 -p atmega1284p -t
Programmer: avrdude -c stk500 -b 115200 -P /dev/ttyACM0 -p atmega1284p -t
get all available ports: ls -l /dev/ttyACM*

