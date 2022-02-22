

# Assignment 1 part 1

                  we implemented the Bresenham’s algorithm to test it's correctness,
                  we chose the coordinates of a circle and drew lines from the center to many point around the circumference

# our implementation of the code:


```
void Renderer::DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
{	int x,y, deltax, deltay;
	double a;

	x = p1.x;
	y = p1.y;
	deltax = p2.x - p1.x;
	deltay = p2.y - p1.y;
	if (deltax != 0) {
		a = (double)deltay / (double)deltax;
	}
	else {
		a = 1;
	}
	deltax = abs(deltax);
	deltay = abs(deltay);
	if (a >= 0 && a < 1) {
		if (x <= p2.x) {
			int e = -deltax;

			while (x <= p2.x) {
				if (e > 0) {
					y = y + 1;
					e = e - 2 * deltax;
				}
				PutPixel(x, y, color);
				x = x + 1;
				e = e + 2 * deltay;
			}
		}
		else {
			int e = -deltax;

			while (x >= p2.x) {
				if (e > 0) {
					y = y - 1;
					e = e - 2 * deltax;
				}
				PutPixel(x, y, color);
				x = x - 1;
				e = e + 2 * deltay;
			}
		}
	}
	
	if (a >= 1) {
		if (y <= p2.y) {
			int e = -deltay;

			while (y <= p2.y) {
				if (e > 0) {
					x = x + 1;
					e = e - 2 * deltay;
				}
				PutPixel(x, y, color);
				y = y + 1;
				e = e + 2 * deltax;
			}
		}
		else {
			int e = -deltay;

			while (y >= p2.y) {
				if (e > 0) {
					x = x - 1;
					e = e - 2 * deltay;
				}
				PutPixel(x, y, color);
				y = y - 1;
				e = e + 2 * deltax;
			}
		}
	}
	if (a < 0 && a >= -1) {
		if (x <= p2.x) {
			int e = -deltax;

			while (x <= p2.x) {
				if (e > 0) {
					y = y - 1;
					e = e - 2 * deltax;
				}
				PutPixel(x, y, color);
				x = x + 1;
				e = e + 2 * deltay;
			}
		}
		else {
			int e = -deltax;

			while (x >= p2.x) {
				if (e > 0) {
					y = y + 1;
					e = e - 2 * deltax;
				}
				PutPixel(x, y, color);
				x = x - 1;
				e = e + 2 * deltay;
			}
		}
	}
	if (a < -1) {
		if (y >= p2.y) {
			int e = -deltay;

			while (y >= p2.y) {
				if (e > 0) {
					x = x + 1;
					e = e - 2 * deltay;
				}
				PutPixel(x, y, color);
				y = y - 1;
				e = e + 2 * deltax;
			}
		}

		else {
			int e = -deltay;

			while (y <= p2.y) {
				if (e > 0) {
					x = x - 1;
					e = e - 2 * deltay;
				}
				PutPixel(x, y, color);
				y = y + 1;
				e = e + 2 * deltax;
			}
		}
	}
}
```




 # and then we chose the circle with the center (500,400) and radius 100


```

	int cx, cy,r,a;
	cx = 500;
	cy = 400;
	r = 100;
	a = 100;
	//DrawLine(glm::ivec2(100,100),glm::ivec2(100,200), glm::vec3 (1.0f, 0.5f, 0.31f) );
	
	for (int i = 0; i < a; i++)
	{
		DrawLine(glm::ivec2(cx, cy), glm::ivec2(cx+r*cos((2*PI*i)/a), cy + r * sin((2 * PI*i) / a)), glm::vec3(1.0f, 0.5f, 0.31f));
}


```


# and the result was:

![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment1Report/images/report1.png)



![the result gif](https://media3.giphy.com/media/SACoDGYTvVNhZYNb5a/giphy.gif?cid=ecf05e4720n7tajynufvcvn2dkqop8y7qqx032jjhebr7yo6&rid=giphy.gif)



#                            and then we drew the logo of the university of haifa : 
```
for (int i = 0; i < 50; i++) {
		DrawLine(glm::ivec2(355 + i, 350 + i), glm::ivec2(355 + i, 300 + i), glm::vec3(0.988, 0.808, 0.));
	}
	for (int i = 0; i< 100; i++) {
		DrawLine(glm::ivec2(130+i, 250+i), glm::ivec2(130+i, 300+i), glm::vec3(0.078, 0.761, 0.863));
	}
	for (int i = 0; i < 100; i++) {
		DrawLine(glm::ivec2(230 + i, 350- i), glm::ivec2(230 + i, 400 - i), glm::vec3(0.353, 0.741, 0.565));
	}

	for (int i = 0; i < 100; i++) {
		DrawLine(glm::ivec2(230 + i, 250 + i), glm::ivec2(230 + i, 300 + i), glm::vec3(0.914, 0.129, 0.149));
	}
	for (int i = 0; i < 100; i++) {
		DrawLine(glm::ivec2(330 + i, 350 - i), glm::ivec2(330 + i, 400 - i), glm::vec3(0.882, 0.4, 0.137));
	}
	
	for (int i = 0; i < 25; i++) {
		DrawLine(glm::ivec2(405 + i, 350 + i), glm::ivec2(405 + i, 400 - i), glm::vec3(0.125, 0.729, 0.875));
	}

	for (int i = 0; i < 10; i++) {
		DrawLine(glm::ivec2(500 + i, 250 ), glm::ivec2(500 + i, 400), glm::vec3(0., 0., 0.));
		DrawLine(glm::ivec2(600 + i, 250 ), glm::ivec2(600 + i, 400), glm::vec3(0., 0., 0.));

		DrawLine(glm::ivec2(650 + i, 250), glm::ivec2(650 + i, 400), glm::vec3(0., 0., 0.));
		DrawLine(glm::ivec2(750 + i, 250), glm::ivec2(750 + i, 400), glm::vec3(0., 0., 0.));

	}
	for (int i = 0; i < 110; i++) {
		DrawLine(glm::ivec2(500 + i, 315 ), glm::ivec2(500 + i, 325 ), glm::vec3(0., 0., 0.));
	}
	for (int i = 0; i < 100; i++) {
		DrawLine(glm::ivec2(650 + i, 250), glm::ivec2(650 + i, 260), glm::vec3(0., 0., 0.));
	}
```


![the result ](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-elie-faisal/blob/master/Assignment1Report/images/hu.png)

![the result gif](https://media.giphy.com/media/3o7qDEq2bMbcbPRQ2c/giphy.gif)