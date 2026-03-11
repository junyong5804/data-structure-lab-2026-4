#include<stdio.h>
//a =[0,1,2,...,9]

int main(void) {
	printf("hello ds!\n");
	printf("Add two numbers: %d\n", add_tmp(4, 6));
	
	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	printf("add array: % d\n", add_array(a));
	return 0;
}

int add_tmp(int a, int b) {
	return a + b;
}

int add_array(int a[10]) {
	int s = 0;
	for (int i = 0; i < 10; i++) {
		if (a[i] % 2 == 0)
			s += a[i];
		
	}

	return s;
		
}

중간3번
프로젝트의 실행파일이 있는 폴더를 고르시오
솔루션의 디버그안에 실행파일이 들어있음