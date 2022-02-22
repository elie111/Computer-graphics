# Assignment 2 part 2

# 1) we added to the ImGui the ability to add multiple lights and control their position,
# and we also added a feature that allows the user to change the color of the model,
# and computed the lightning for the ambient light :
# here is the new ImGui:
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/lightgui.png)
# and here is the bunny after we calculated the ambient light:
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/ambient.png)
# we used red as the color for the ambient ,specular and diffusive lightings and we allowed the user to change the color
# of the lighting in the imgui
# 2) Flat shading:
# here is the bunny after we calculated the defuse component:
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/defusive.png)


# 3) Goaraud shading 
# here is the bunny after we calculated the gaoraud shading:
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/goaraud.png)

# 4) the reflection vector 
# we calculated the direction of specular light reflection as  rendered as a black lines when the light point is at (0,1,0) e.g up the mesh

![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/reflection.png)

# 5) Phong shading
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/phong.gif)
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/phongbanana.png)

# 6) we implemented the directional light by setting the position of the light to infinity
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/directional.png)

# 7) here are the results with diffrent models, lights ,shadings,and camera positions
# beethoven and bunny with goaraud shading:
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/7_part1.png)

# beethoven and bunny in flat shading :
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/7_part2_flat.png)

# beethoven and bunny in phong shading with a different light position:
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/7_part3_phong.png)

# beethoven and bunny in phong shading and in perspective camera:
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/7_part4_pers.png)

# beethoven and bunny in orthographic camera and phong lightning with the second light with different position:
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/7_part5_2nd_light.png)

# here is a video showing how we switch between different lights and change the position of the light:
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/7_video.gif)


# 8) we implemented post-processing effects 
# -simple marble effect : 
# the equation we used : pointamb = { sin((0.3 * it * it + jt * jt)),sin((0.7 * it * it + jt * jt)),sin((0.4 * it * it + jt * jt)) };
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/marble.png)


# -we also added another effect that made the model transparent /blur
# here is the result with the ambient lights
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment2Report/images/blur.png)




