#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#define Y 25
#define X 80
void draw(int x_func, int y_func);

int main () {
	int x_func, y_func;
	draw(x_func,y_func);
}

voif draw(int x_func, int y_func) {
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			if (x_func == j && y_func == i)
				printf("*");
			else
				printf(".");
		}
		printf("\n");
	}
}
