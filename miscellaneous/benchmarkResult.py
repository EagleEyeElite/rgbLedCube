import subprocess
import sys
from datetime import datetime

if __name__ == '__main__':
    testInfo = ""
    if len(sys.argv) > 1:
        testInfo = sys.argv[1]
    else:
        testInfo = "no info, pass argument as string"

    # Linux terminal: command <<< "data input"
    command = "avrdude -c stk500 -b 115200 -P /dev/ttyACM0 -p atmega1284p -B 0.5 -t"
    dataInput = "dump eeprom 0 4"

    result = subprocess.run(command, shell=True, input=dataInput, encoding='ascii', stdout=subprocess.PIPE)

    output = result.stdout

    output = output[52: 63]
    ticks = int("".join(output.split()[::-1]), 16)

    timeS = ticks * 0.051
    timeMs = timeS / 1000

    info = datetime.now().strftime("%d/%m/%Y %H:%M:%S") + "\n"
    info += "test: " + testInfo + "\n"
    info += "ticks = " + f"{int(ticks):#0{10}x}" + "\n"
    info += "time  = " + '%.2f' % timeS + "ms" + "\n"
    info += "time  = " + '%.2f' % timeMs + "s" + "\n"

    print(info)

    file_object = open('benchmarkResult.txt', 'a')
    file_object.write(info + "\n")
    file_object.close()

