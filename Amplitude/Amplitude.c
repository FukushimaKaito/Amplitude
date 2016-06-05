/*-------------------------------------------
振幅及び位相特性を調べるプログラム

5I30	福嶋開人
------------------------------------------*/
//�Z�L�����e�B�nError�𖳌�������
//#define _CRT_SECURE_NO_WARNINGS：_s対応でいらなくなってるはず
//M_PI(�~����)���g�����悤�ɂ��� 
#define _USE_MATH_DEFINES
#define BUFF 256

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
	printf("振幅位相特性を調べるプログラム\n");

	FILE *fpr;
	double *h, re = 0.0, im = 0.0, AM, PH;
	int NumH;
	char name[BUFF];
	printf("ファイル名入力：");
	scanf_s("%s", name, _countof(name));
	/*�t�B���^�t�@�C���̎擾*///文字化けして解析不可
	if (fopen_s(&fpr,name, "r") != 0){
		fprintf(stderr, "ファイルのオープンに失敗しました．\n");
		exit(1);
	}
	fscanf_s(fpr, "%d", &NumH);
	/* 動的確保 */
	if ((h = (double *)malloc(NumH*sizeof(double))) == NULL)
	{
		fprintf(stderr, "ファイルのオープンに失敗しました．\n");
		exit(1);
	}
	for (int i = 0; i < NumH; i++)/* 代入 */
	{//!!//#$//////*******----------!le注意
		fscanf_s(fpr, "%le", &h[i]);
	}
	fclose(fpr);
	printf("f			AM			PH\n");
	//fは正規化周波数．
	for (double f = 0.0; f <= 0.5; f += 0.1)
	{
		re = 0.0, im = 0.0;
		for (int n = 0; n < NumH; n++)
		{
			re += h[n] * cos(2.0 * M_PI*f*n);
			im += -h[n] * sin(2.0 * M_PI*f*n);
		}
		AM = 20.0 * log10(sqrt(pow(re,2.0) + pow(im,2.0)));
		PH = atan(im / re);//発散考慮してない．
		printf("%f	%f	%f\n", f, AM, PH);
	}
	return 0;
}