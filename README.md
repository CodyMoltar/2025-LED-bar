## image2led

A little python script that converts images (jpg for now) to txt files, writing the rgb pixel values on 1 line.
Oh, and it also reizes the image (so that the original height is 228 pixels) and then rotates the image 90 degrees counter clockwise so it can be properly used by the LED bar.

## sketches/full-color

Arduino sketch that loads the txt file as found on the SD card (which is connected to the Arduino), it then displays the pixel values line by line.

**Note**: Heavily not optimized, runs quite slow (maybe 5 lines per second or something)
