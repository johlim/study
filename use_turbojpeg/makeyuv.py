import numpy as np

# Define the dimensions of the YUV image
width = 640
height = 480

# Create arrays to store Y, U, and V components
y_component = np.zeros((height, width), dtype=np.uint8)
u_component = np.zeros((height, width), dtype=np.uint8)
v_component = np.zeros((height, width), dtype=np.uint8)

# Define sample values for Y, U, and V (you can modify these as needed)
y_value = 128
u_value = 128
v_value = 128

# Fill the Y, U, and V components with the sample values
y_component[:, :] = y_value
u_component[:, :] = u_value
v_component[:, :] = v_value

# Combine the Y, U, and V components into a single YUV frame
yuv_frame = np.dstack((y_component, u_component, v_component))

# Save the YUV frame to a binary file
with open("output640480.yuv", "wb") as f:
    yuv_frame.tofile(f)