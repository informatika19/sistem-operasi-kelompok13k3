#include "math.h"

int div(int x, int y){
	int z = 0;
	while(z * y <= x){
		z += 1;
	}
	z -= 1;
	return z;
}

int mod(int x, int y){
	while(x >= y){
		x -= y;
	}
	return x;
}