#!/usr/bin/python3

import PIL
from PIL import Image
import sys


def binarize(img, threshold = 200):
    img = img.convert('L');
    w, h = img.size
    if w < 200 or h < 200:
        print("Warning: Image is too small")
    ret = []
    for x in range(200):
        for i in range(25):
            a = 0
            for j in range(8):
                y = i * 8 + j
                if x >= w or y >= h or img.getpixel((x, y)) > threshold:
                    a |= (128 >> j)
            ret.append(a)
    return ret
                 

def toStr(mat):
    ret = "uint8_t mat[200 * 25] = {\n";
    for x in range(200):
        ret += '    '
        for y in range(25):
            ret += '0x{:02x}'.format(mat[25 * x + y]) + ', '
        ret += '\n'
    ret += '};\n'
    return ret


if __name__ == "__main__":
    fname = sys.argv[1]
    img = Image.open(fname)
    mat = binarize(img, 150)
    f = open('image.h', 'w')
    f.write(toStr(mat))
    f.close()

