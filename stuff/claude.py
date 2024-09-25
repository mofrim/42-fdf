import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def sphere(radius, resolution=100):
    phi = np.linspace(0, np.pi, resolution)
    theta = np.linspace(0, 2*np.pi, resolution)
    phi, theta = np.meshgrid(phi, theta)
    
    x = radius * np.sin(phi) * np.cos(theta)
    y = radius * np.sin(phi) * np.sin(theta)
    z = radius * np.cos(phi)
    
    return x, y, z

def great_circle(p1, p2, radius, resolution=100):
    # Convert to Cartesian coordinates
    x1, y1, z1 = (radius * np.cos(p1[1]) * np.cos(p1[0]),
                  radius * np.cos(p1[1]) * np.sin(p1[0]),
                  radius * np.sin(p1[1]))
    x2, y2, z2 = (radius * np.cos(p2[1]) * np.cos(p2[0]),
                  radius * np.cos(p2[1]) * np.sin(p2[0]),
                  radius * np.sin(p2[1]))
    
    # Calculate the great circle
    t = np.linspace(0, 1, resolution)
    x = x1 + t * (x2 - x1)
    y = y1 + t * (y2 - y1)
    z = z1 + t * (z2 - z1)
    
    # Normalize to sphere surface
    norm = np.sqrt(x**2 + y**2 + z**2)
    x, y, z = radius * x/norm, radius * y/norm, radius * z/norm
    
    return x, y, z

# Set up the figure and axis
fig = plt.figure(figsize=(10, 10))
ax = fig.add_subplot(111, projection='3d')

# Draw the sphere
radius = 1
x, y, z = sphere(radius)
ax.plot_surface(x, y, z, color='b', alpha=0.3)

# Define two points on the sphere (in spherical coordinates: longitude, latitude)
p1 = (np.pi/4, np.pi/4)  # (45°, 45°)
p2 = (3*np.pi/4, -np.pi/4)  # (135°, -45°)

# Draw the great circle
x, y, z = great_circle(p1, p2, radius)
ax.plot(x, y, z, color='r', linewidth=2)

# Plot the points
ax.scatter(*great_circle(p1, p1, radius), color='g', s=50, label='Point 1')
ax.scatter(*great_circle(p2, p2, radius), color='y', s=50, label='Point 2')

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.legend()

plt.title('Shortest Path (Great Circle) on a Sphere')
plt.tight_layout()
plt.show()
