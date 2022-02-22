#                                                                  assignment 1 part 2

# 1) first we loaded a mesh to display it's vertices and faces to the console here is what we got:

# the vertics of the mesh:
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment1Report/images/vertices.png)

# and the faces of the mesh:
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment1Report/images/faces.png)




# 2) we loaded a mesh model and then with the translation and scaling functions centered it in the window




# 3) and then with the help of the drawline function we drew the mesh:
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment1Report/images/beethoven.png)





# 4) we designed 2 gui windows one for local transformations and the other for world transformations

![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment1Report/images/imgui.png)




# 5)  computed every matrix we need for the transformation for each local and world then multiply
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment1Report/images/matrices.png)
# extract the current face vertices and muliply each exctracted vertex by the transform matrix
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment1Report/images/matrices2.png)


# and then we tested the importance of the order of the transformation functions 

#here is the original shape
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment1Report/images/pic3.png)
# here we first translated locally and then rotated 72 degrees in world
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment1Report/images/pic1.png)
# and here we rotated locally and the translated in world
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment1Report/images/pic2.png)





# 6) and then we also enabled loading more than one model at a time by declaring a new array containing the values of the transforamtion
 # parameters of each mesh shape
 # and we were able to control each shape at the same time ,here is an example ,we loaded 3 shapes:
![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment1Report/images/multipleobjects.png)






# 7)  and finally we also added a new feature which allows us to move the shape using the keyboard
# D->right world
# A->left world
# L->left local
# R->right local

![the result gif](https://media.giphy.com/media/l2R0eYcNq9rJUsVAA/giphy.gif)