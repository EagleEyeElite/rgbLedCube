# https://jared.geek.nz/2013/feb/linear-led-pwm

# https://medium.com/hipster-color-science/a-beginners-guide-to-colorimetry-401f1830b65a
# https://www.sciencedirect.com/topics/engineering/relative-luminance
# https://en.wikipedia.org/wiki/CIELUV

import matplotlib.pyplot as plt

INPUT_SIZE = 0xFF  # Input integer size
OUTPUT_SIZE = 0xFFF  # Output integer size
INT_TYPE = 'static volatile const uint16_t'
TABLE_NAME = 'lightness'


# reverse transformation
def cie1931(luminance):
    luminance *= 100.0
    if luminance <= 8:
        return luminance * ((3 / 29) ** 3)
    else:
        return ((luminance + 16.0) / 116.0) ** 3


def linear(luminance):
    return luminance


def middle(luminance):
    luminance *= 100.0
    return (((luminance + 130) / 160) ** 3)-0.5364


if __name__ == '__main__':
    x = range(0, int(INPUT_SIZE + 1))
    y = [round(cie1931(float(L) / INPUT_SIZE) * OUTPUT_SIZE) for L in x]
    plt.plot(x, y)
    y = [round((middle(float(L) / INPUT_SIZE) * OUTPUT_SIZE) / middle(1)) for L in x]
    plt.plot(x, y)

    y = [round(linear(float(L) / INPUT_SIZE) * OUTPUT_SIZE) for L in x]
    plt.plot(x, y)

    toPrint = 'Linear correction table:\n'
    toPrint += '%s %s[' % (INT_TYPE, TABLE_NAME) + hex(INPUT_SIZE + 1) + '] = {'

    for i, L in enumerate(y):
        toPrint += f"{int(L):#0{5}x}"
        if i != INPUT_SIZE:
            toPrint += ", "
    toPrint += '};'

    print(toPrint)

    plt.show()
