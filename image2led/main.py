from PIL import Image
import sys
import os

# get the input argument from the args
input_image = sys.argv[1]
image_name = input_image.split(".")[0]

# create a folder to store the output
os.makedirs(image_name, exist_ok=True)

# Open the image
img = Image.open(input_image)

# Resize the image to 228 pixels in height while maintaining aspect ratio
base_height = 228
width, height = img.size
aspect_ratio = width / height
new_width = int(base_height * aspect_ratio)
img_rescaled = img.resize((new_width, base_height))
# Rotate the image 90 degrees clockwise
img_rescaled = img_rescaled.rotate(-90, expand=True)  # -90 rotates clockwise
# Save the rescaled and rotated image
img_rescaled.save( image_name + "/source_image.jpg")
# Ensure the image is in RGB mode
img_rescaled = img_rescaled.convert("RGB")


image_width = img_rescaled.size[0]
image_height = img_rescaled.size[1]

# iterate over all the pixels in the image
# open an image.txt file to store the pixel values
# on every line in the txt file, write the pixel values in RGB format, comma separated

with open(image_name + "/image.txt", "w") as f:
    for y in range(image_height):
        for x in range(image_width):
            r, g, b = img_rescaled.getpixel((x, y))
            r = f"{r:03}"
            g = f"{g:03}"
            b = f"{b:03}"
            # if(x > 0):
            #     f.write(",")
            f.write(f",{r},{g},{b}")
        f.write("\n")

# get the first line of the txt file
# split the line by comma

# with open(image_name + "/image.txt", "r") as f:
#     first_line = f.readline()
#     # get the 2nd line
#     first_line = first_line.split(",")
#     # print the length of the first_line
#     print(len(first_line) / 3)
            
