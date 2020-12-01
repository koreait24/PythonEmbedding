// APP1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <Windows.h>
#include "header1.h"

int main()
{
	double a, b;
	a = 8.0f, b = 5.0f;

	printf("Hello\n");
	printf("%.2f", mpow(a, b));

	system("pause");
	return 0;
}

