# Assignment 2 part 1

# 1) ImGui 
```
First of all we modified our imgui design to look better and suit the new requirements
```
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/part1_imgui.png)
```
here is an example of loading a mesh and choosing which buffer to use and changing the grey scale degree and
 switching between orthographic camera and perspective camera
```

![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/part1_gui.gif)

# 2) Bounding rectangles
```
  we added a new feature allowing the user to add the bounding rectangles for each triangle by checking a check box
```
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/part1_rec.png)

# 3) edge walking algorithm
```
and then we used the edge walking algorithm to fill all the triangles and we used a random color for each triangle
```
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/part1_edge_walking.png)

![the result ](https://media.giphy.com/media/3o7aD56B2QS5MyTGfe/giphy.gif)

# 4) z-buffer
```
and finally we implemented the z-buffer algorithm to fix the overlapping triangles issue,
we calculated the Z value for each pixel using the Linear interpolation triangles Barycentric
coordinates.
we added a feature allowing the user to switch between z-buffer with random colors or 
z-buffers on a grey scale and also we allowed the user to change the degree of the scale 
which is how drastically the color changes to a darker shade
```

# this is an example of beethoven before we implemented the z -buffer

![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/part1_edge_walking.png)


# and this is beethoven with the z-buffer 

# beethoven with random colors
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/part1_beethoven_z_colored.png)
# beethoven on the grey scale
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/part1_beethoven_z_grey.png)

# here is a second example with the bunny 

# bunny without z-buffer
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/part1_bunny_no_z.png)


# bunny with z-buffer colored
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/part1_bunny_z_colored.png)

# bunny with z-buffer on a grey scale
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/part1_bunny_z_grey.png)


# bunny with the z-buffer in perspective camera on a grey scale
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/part1_bunny_pers_grey.png)


![the result ](https://media.giphy.com/media/11ISwbgCxEzMyY/giphy.gif)




