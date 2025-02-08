from PIL import Image
import os

##
## EPITECH PROJECT, 2025
## Jam-Illusion
## File description:
## script
##

# Open the image
img = Image.open("player(15x23).png")

# Define the directions and their corresponding y-coordinates
directions = {
    "idle": 0,
    "down": 23,
    "right": 46,
    "left": 69,
    "up": 92
}

# Create the output directories if they don't exist
for direction in directions.keys():
    os.makedirs(f"assets/player/{direction}", exist_ok=True)

# Extract frames
frame_width = 15
frame_height = 23

for direction, y in directions.items():
    for frame in range(img.width // frame_width):
        box = (frame * frame_width, y, (frame + 1) * frame_width, y + frame_height)
        frame_img = img.crop(box)
        frame_img.save(f"assets/player/{direction}/{frame + 1}.png")