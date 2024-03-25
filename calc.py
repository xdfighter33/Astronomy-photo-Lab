import numpy as np
from PIL import Image
table = np.loadtxt('finalimageAverage_bias_frame.txt.txt')
table2 = np.loadtxt('finalimageAverage_Dark_frame.txt')
table3 = np.loadtxt('finalimageAverage_Flat_frame.txt')
image = Image.fromarray(table.astype('uint8'))
image = Image.fromarray(table.astype('uint8'))
image2 = Image.fromarray(table2.astype('uint8'))
image3 = Image.fromarray(table3.astype('uint8'))


image.save('Bias_frame_image.jpeg')
image2.save('Dark_frame_image.jpeg')
image3.save('Flat_frame_image.jpeg')