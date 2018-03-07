//----------------------------------------------------------
//�t�@�C����  	2048.cpp
//�T�v			�����Q�[��
//�쐬��		2014/09/01
//�X�V��		2014/09/08
//�쐬��		���V��
//----------------------------------------------------------
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
#define MAX_Y 17
#define MAX_X 29

int dim[4][4] = {0};			//�z��
int score = 0;					//�X�R�A
int hiscore = 0;				//�O10�ʂ̃X�R�A

void setCursor(int y, int x);	//�J�[�\���ʒu��ݒ肷��֐�
void title();					//�J�n���
void map_print();				//�w�i�̕\��
void rule_print();				//���[���̕\��
void output();					//�������o��
void dim_print();				//�z��̕\��
void action();					//����
void achive(int x);				//�ڕW�B���̕\��
void fuction();			//�Q�[���̗���
void gameover();				//�Q�[���I�[�o�[�̕\��


int main(void)
{			
	int playerInput;	//�v���C���[�̓��͂��󂯎��
	int end = 0;		//�I���t���O
	int i;				//�J�E���^

	srand((unsigned int)time(NULL));	//���݂̎��Ԃ��g���ė����\��ύX����

	//�X�^�[�g��ʂ̕\��
	title();
	for(i = 0;i > 5; i++){
		//0.2�b���Ƃ�2����s
		Sleep( 200 );
		printf("\n\n");
	}

	do{
		playerInput = _getch();		//�v���C���[�̓��͂��󂯎��
		switch (playerInput){
			//�Q�[���̃X�^�[�g
			case '1':		fuction();		break;
			//���[���̕\��
			case '9':		rule_print();	break;
			//�I���
			case '0':		end = 1;		break;
			//�t���O��ύX����	
		}
	}while(end == 0);
		
	_getch();
	return 0;
}


/*setCursor------------------------------------------------------------------------------------st
�T�v�F		�ʒu��ݒ肷��
�g�p�ϐ��F	y	�c��
			x	����
�����F		y�A��
�߂�l�F	�Ȃ�
-----------------------------------------------------------------------------------------------*/
void setCursor(int y, int x)
{
	HANDLE hStdOut;	//	�o�̓R���\�[���̃n���h��

	//�n���h���̎擾
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(hStdOut == INVALID_HANDLE_VALUE){
		return;
	}
	//�J�[�\���ʒu�̐ݒ�
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(hStdOut, coord);
}
/*setCursor---------------------------------------------------------------------------------end*/

/*title----------------------------------------------------------------------------------------st
�T�v�F		�J�n���
�g�p�ϐ��F	 i
�����F		�Ȃ�
�߂�l�F	�Ȃ�
-----------------------------------------------------------------------------------------------*/
void title()
{	
	int i;	//�J�E���^	
	
	for(i = 0; i < 20; i++)	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);	
		if(i % 2 == 0){
			system("cls");
			printf("\n\n");
			printf("                ����������������������������������������������\n");
			printf("                ��                                          ��\n");
			printf("                ��    ����      ����        ��      ����    ��\n");
			printf("                ��  ��    ��  ��    ��  ��  ��    ��    ��  ��\n");
			printf("                ��        ��  ��    ��  ��  ��    ��    ��  ��\n");
			printf("                ��      ��    ��    ��  ��  ��      ����    ��\n");
			printf("                ��    ��      ��    ��  ��������  ��    ��  ��\n");
			printf("                ��  ��        ��    ��      ��    ��    ��  ��\n");
			printf("                ��  ��������    ����        ��      ����    ��\n");
			printf("                ��                                          ��\n");
			printf("                ����������������������������������������������\n"); 
		}else{
			system("cls");
			printf("\n\n");
			printf("                ����������������������������������������������\n");
			printf("                ��                                          ��\n");
			printf("                ��    ����      ����        ��      ����    ��\n");
			printf("                ��  ��    ��  ��    ��  ��  ��    ��    ��  ��\n");
			printf("                ��        ��  ��    ��  ��  ��    ��    ��  ��\n");
			printf("                ��      ��    ��    ��  ��  ��      ����    ��\n");
			printf("                ��    ��      ��    ��  ��������  ��    ��  ��\n");
			printf("                ��  ��        ��    ��      ��    ��    ��  ��\n");
			printf("                ��  ��������    ����        ��      ����    ��\n");
			printf("                ��                                          ��\n");
			printf("                ����������������������������������������������\n"); 
		}
		Sleep(200);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	
	printf("\n\n");
	printf("                        ������������������������������\n");
	printf("                        ��                          ��\n");
	printf("                        ����     1       �X�^�[�g   ��\n");
	printf("                        ��                          ��\n");
	printf("                        ����     9       ����       ��\n");
	printf("                        ��                          ��\n");
	printf("                        ����     0       �G���h     ��\n");
	printf("                        ��                          ��\n");
	printf("                        ������������������������������\n");

}
/*title-------------------------------------------------------------------------------------end*/

/*rule_print-----------------------------------------------------------------------------------st
�T�v�F		���[������
�g�p�ϐ��F	�Ȃ�
�����F		�Ȃ�
�߂�l�F	�Ȃ�
-----------------------------------------------------------------------------------------------*/
void rule_print()
{
	system("cls");
	printf("          ����������������������������������������������������������\n");
	printf("          ��                                                      ��\n");
	printf("          ��  ��  ������@                                        ��\n");
	printf("          ��                                                      ��\n");
	printf("          ��      8�F��    4�F��    6�F��    5�F��                ��\n");
	printf("          ��    �����L�[8�A5�C4�C6�������ƁA                      ��\n");
	printf("          �� �E�㉺���E�ɋ󔒂�����Έړ������邱�Ƃ��ł��܂��B   ��\n");
	printf("          �� �E�����������m�́A�d�˂�Ƒ����Z����ĂP���̃^�C��   ��\n");
	printf("          ��   �ɂȂ�܂� �B                                      ��\n");
	printf("          ��                                                      ��\n");
	printf("          ��  ��  ��(�}�P�̎��A8�������ƁA�}�Q�ɂȂ�)             ��\n");
	printf("          ��      -----------------         -----------------     ��\n");
	printf("          ��      |   | 2 |   | 4 |         |   | 4 | 2 | 8 |     ��\n");
	printf("          ��      |---+---+---+---|         |---+---+---+---|     ��\n");
	printf("          ��      |   |   |   |   |   8     |   |   | 8 |   |     ��\n");
	printf("          ��      |---+---+---+---|  ����   |---+---+---+---|     ��\n");
	printf("          ��      |   | 2 | 2 |   |         |   |   |   |   |     ��\n");
	printf("          ��      |---+---+---+---|         |---+---+---+---|     ��\n");
	printf("          ��      |   |   | 8 | 4 |         |   |   |   |   |     ��\n");
	printf("          ��      -----------------         ----------------      ��\n");
	printf("          ��         �@  �}�P                      �}�Q           ��\n");
	printf("          �� ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	
	printf("����ł́A2048�̃^�C����ڎw���āA�X�^�[�g���܂��傤");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf(" ��\n");
	printf("          ��          ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("1: �Q�[���X�^�[�g");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("�@�@0�F�Q�[���I���@�@�@�@�@");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("��\n");
	printf("          ����������������������������������������������������������\n");

}
/*rule_print--------------------------------------------------------------------------------end*/

/*map_print------------------------------------------------------------------------------------st
�T�v�F		�w�i�̕\��
�g�p�ϐ��F	map[MAX_Y][MAX_X]  iCnt_Y  iCnt_X  
�����F		�Ȃ�
�߂�l�F	�Ȃ�
-----------------------------------------------------------------------------------------------*/
void map_print()
{
	system("cls");
	int iCnt_Y;							//�c���̃J�E���^
	int iCnt_X;							//�����̃J�E���^
	int map[MAX_Y][MAX_X] = {
		//0 1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  
		{1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1},//0
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//1
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//2
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//3
		{1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1},//4
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//5
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//6
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//7
		{1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1},//8
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//9
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//0
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//1
		{1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1},//2		
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//3
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//4
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//5
		{1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1} //6
	};

	printf(" \n");
	//���F�ɕύX����
	setCursor(1, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	
	for(iCnt_Y = 0; iCnt_Y < MAX_Y; iCnt_Y++){
		for(iCnt_X = 0; iCnt_X < MAX_X; iCnt_X++){				
			switch(map[iCnt_Y][iCnt_X])	{					
				case 0:		printf("  ");		break;	//	��							
				case 1:		printf("��");		break;	//	��
				case 2:		printf("��");		break;	//	��
				case 3:		printf("�U");		break;	//	��
			}
		}
		printf(" \n");
	}
	//���ɕύX����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	
	//�{�^���̕\��	
	setCursor(18, 10);
	printf(" __ ");		
	setCursor(19, 5 * 2);
	printf("|�W|			8�F��  4�F��  6�F��  5�F��");
	setCursor(20, 3 * 2);
	printf(" __  --  __");
	setCursor(21, 3 * 2);
	printf("|�S||�T||�U|		���������Ɍ����āA�ړ�����");	
	setCursor(22, 3 * 2);
	printf(" --  --  -- ");
	
	//�����L���O�̕\��
	setCursor(5, 30 * 2);
	printf("��-��  SCORE ��-��");
	setCursor(6, 30 * 2);
	printf("�b              �b");
	setCursor(7, 30 * 2);
	printf("�� ���j�ō��_:  ��");
	setCursor(8, 30 * 2);
	printf("�b              �b");
	setCursor(9, 30 * 2);
	printf("��              ��");
	setCursor(10, 30 * 2);
	printf("�b ���̃X�R�A�F �b");
	setCursor(11, 30 * 2);
	printf("��              ��");
	setCursor(12, 30 * 2);
	printf("�b              �b");
	setCursor(13, 30 * 2);
	printf("��==============��");	

}
/*map_print---------------------------------------------------------------------------------end*/

/*output----------------------------------------------------------------------------------------st
�T�v�F		�����������_���ɏo��
�g�p�ϐ��F	iCnt_Y  iCnt_X   num  score 
�����F		�Ȃ�
�߂�l�F	�Ȃ�
-----------------------------------------------------------------------------------------------*/
void output()
{
	int iCnt_X;	//�z��̉���
	int iCnt_Y;	//�z��̏c��
	int num;

	//�����������_���ɏo��
	num = (rand() % 2 + 1) * 2;	

	//���l�̈ʒu�������_���Ɍ���
	do{
		iCnt_X = rand() % 4;			//����
		iCnt_Y = rand() % 4;			//�c��
	}while(dim[iCnt_Y][iCnt_X] != 0);	//���肵���ʒu�ɐ���������΁A������x�I������

	//�o���̐�����z��v�f�ɑ��
	dim[iCnt_Y][iCnt_X] = num;
	
	//�ō��_�̌v�Z
	if(score > hiscore)	{
		hiscore = score;		
	}

	//�z��̕\��
	dim_print();
}
/*output------------------------------------------------------------------------------------end*/

/*dim_print------------------------------------------------------------------------------------st
�T�v�F		�z��̕\��
�g�p�ϐ��F	dim[4][4]  iCnt_Y  iCnt_X  
�����F		�Ȃ�
�߂�l�F	�Ȃ�
-----------------------------------------------------------------------------------------------*/
void dim_print()
{	
	int iCnt_Y;							//�c���̃J�E���^
	int iCnt_X;							//�����̃J�E���^

	//�����̕\��
	printf(" \n\n");
	for(iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++){
		setCursor((iCnt_Y+1) * 4 - 1, 0);
		for(iCnt_X = 0; iCnt_X < 4; iCnt_X++){	
			//���F�ɖ߂�			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);	
			printf("�U");			
			if(dim[iCnt_Y][iCnt_X] != 0){
				//2,4���D�F�ŕ\��
				if(dim[iCnt_Y][iCnt_X] <= 4){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
					printf("  %4d      ", dim[iCnt_Y][iCnt_X]);
				}
				//8,16�𔒐F�ŕ\��
				else if(dim[iCnt_Y][iCnt_X] <= 16){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
					printf("  %4d      ", dim[iCnt_Y][iCnt_X]);
				}
				//32,64��F�ŕ\��
				else if(dim[iCnt_Y][iCnt_X] <= 64){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
					printf("  %4d      ", dim[iCnt_Y][iCnt_X]);
				}
				//128,256��΂ŕ\��
				else if(dim[iCnt_Y][iCnt_X] <= 256){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
					printf("   %4d     ", dim[iCnt_Y][iCnt_X]);
				}
				//512�����F�ŕ\��
				else if(dim[iCnt_Y][iCnt_X] = 512){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
					printf("   %4d     ", dim[iCnt_Y][iCnt_X]);
				}
				//1024�����F�ŕ\��
				else if(dim[iCnt_Y][iCnt_X] = 1024){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
					printf("   %4d     ", dim[iCnt_Y][iCnt_X]);
				}
				//2048�ȏ�̐�����ԐF�ŕ\��
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
					printf("    %4d    ", dim[iCnt_Y][iCnt_X]);
				}
			}else{
				printf("            ");
			}
		}
		//���F�ɖ߂�
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
		printf("�U\n");
	}

	//�X�R�A�̕\��
	setCursor(11, 62);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("%12d", score);
	
	//�ō��X�R�A�̕\��
	setCursor(8, 62);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	printf("%12d", hiscore);

	
	return ;
}
/*dim_print---------------------------------------------------------------------------------end*/

/*action---------------------------------------------------------------------------------------st
�T�v�F		����
�g�p�ϐ��F	dim[4][4] temp[4] iCnt_Y  iCnt_X  i playerInput  sw
�����F		�Ȃ�
�߂�l�F	�Ȃ�
-----------------------------------------------------------------------------------------------*/
void action()
{
	int iCnt_Y;			//�c���̃J�E���^
	int iCnt_X;			//�����̃J�E���^
	int playerInput;	//�v���C���[�̓��͂��󂯎��
	int temp[4];		//�ꎞ�I�Ȕz��
	int i;				//�J�E���^
	int sw = 0;			//�z��̈ړ��t���O(0: �ł��Ȃ�  1�F�ł��� )
	
	playerInput = _getch();		// �v���C���[�̓��͂��󂯎��

	// �v���C���[�̌��ݒn�̈ړ��Ɠ��͓����s��
	switch(playerInput)
	{
		// ��������Ɉړ�
		case '8':	
			//1�񂸂A�ړ�����
			for(iCnt_X = 0; iCnt_X < 4; iCnt_X++){								
				//�ꎞ�I�Ȕz��̗v�f�ԍ��̏�����					
				i = 0;
				//1�s���A���f����
				for(iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++){						
					//0�ȊO�̐������ꎞ�I�Ȕz��ɓ����
					if(dim[iCnt_Y][iCnt_X] != 0 ){	
						temp[i] = dim[iCnt_Y][iCnt_X];
						i++;
					}						
				}
				//�g���Ă��Ȃ��v�f��0�Ƃ���
				for (; i < 4; temp[i++] = 0);
				i = 0;

				//�ړ���������`�F�b�N����
				//�ꎞ�I�Ȕz��̐������S���A����ɓ��ꂽ���A���[�v���甲����
				for(iCnt_Y = 0; iCnt_Y < 4 && i < 4; iCnt_Y++){							
					//�V�����z��̒l�ƈႤ�ꍇ�i�܂�A�������ړ������j
					if(dim[iCnt_Y][iCnt_X] != temp[i]){
						//����ւ�
						dim[iCnt_Y][iCnt_X] = temp[i];
						//�ړ��ł���t���O
						sw = 1;		
					}
					//�ׂɓ����������m������ꍇ
					if(i < 3 && dim[iCnt_Y][iCnt_X] == temp[i + 1] && temp[i + 1] != 0 ){
						//�ړ����Ȃ���A����
						dim[iCnt_Y][iCnt_X] += temp[i + 1];
						temp[i + 1] = 0;
						//������������������A�X�R�A����������
						score = dim[iCnt_Y][iCnt_X] + score;
						//���̒l���`�F�b�N����
						i++;
						//�ړ��ł���t���O
						sw = 1;		
					}
					//�O�̒l���������ǂ�����킸�A���̒l���`�F�b�N����
					i++;							
				}
				if(iCnt_Y < i){
					for(; iCnt_Y < 4; iCnt_Y++){
						dim[iCnt_Y][iCnt_X] = 0;
					}
				}				
			}					
			break;

		// �E�Ɉړ�
		case '6':
			//1�s���A�ړ�����
			for(iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++){	
				//�ꎞ�I�Ȕz��̏�����										
				i = 3;
				//1�񂸂A���f����
				for(iCnt_X = 3; iCnt_X >= 0; iCnt_X--){						
					//0�ȊO�̐������ꎞ�I�Ȕz��ɓ����
					if(dim[iCnt_Y][iCnt_X] != 0){	
						temp[i] = dim[iCnt_Y][iCnt_X];
						i--;
					}						
				}
					
				//�g���Ă��Ȃ��v�f��0�Ƃ���
				for(; i >= 0; i--){	
					temp[i] = 0;										
				}
				i = 3;
				//�ړ���������`�F�b�N����
				//�ꎞ�I�Ȕz��̐������S���A����ɓ��ꂽ���A���[�v���甲����
				for(iCnt_X = 3; iCnt_X >= 0 && i >= 0; iCnt_X--){							
					//�V�����z��̒l�ƈႤ�ꍇ�i�܂�A�������ړ������j
					if(dim[iCnt_Y][iCnt_X] != temp[i]){
						//����ւ�
						dim[iCnt_Y][iCnt_X] = temp[i];
						//�ړ��ł���t���O
						sw = 1;		
					}
					//�ׂɓ����������m������ꍇ
					if(i >=0 && dim[iCnt_Y][iCnt_X] == temp[i - 1] && temp[i - 1] != 0 ){
						//�ړ����Ȃ���A����
						dim[iCnt_Y][iCnt_X] += temp[i - 1];
						//������������������A�X�R�A����������
						score = dim[iCnt_Y][iCnt_X] + score;
						//���̒l���`�F�b�N����
						i--;
						//�ړ��ł���t���O
						sw = 1;		
					}
					//�O�̒l���������ǂ�����킸�A���̒l���`�F�b�N����
					i--;							
				}
				if(iCnt_X > i){
					for(; iCnt_X >= 0; iCnt_X--){
						dim[iCnt_Y][iCnt_X] = 0;
					}
				}				
			}
			break;

		// ���Ɉړ�
		case '4':
			//1�s���A�ړ�����
			for(iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++){	
				//�ꎞ�I�Ȕz��̏�����	
				i = 0;
				//1�s���A���f����
				for(iCnt_X = 0; iCnt_X < 4; iCnt_X++){						
					//0�ȊO�̐������ꎞ�I�Ȕz��ɓ����
					if(dim[iCnt_Y][iCnt_X] != 0 ){	
						temp[i] = dim[iCnt_Y][iCnt_X];
						i++;
					}						
				}
				//�g���Ă��Ȃ��v�f��0�Ƃ���
				for (; i < 4; temp[i++] = 0);
					
				i = 0;

				//�ړ���������`�F�b�N����
				//�ꎞ�I�Ȕz��̐������S���A����ɓ��ꂽ���A���[�v���甲����
				for(iCnt_X = 0; iCnt_X < 4 && i < 4; iCnt_X++){							
					//�V�����z��̒l�ƈႤ�ꍇ�i�܂�A�������ړ������j
					if(dim[iCnt_Y][iCnt_X] != temp[i]){
						//����ւ�
						dim[iCnt_Y][iCnt_X] = temp[i];
						//�ړ��ł���t���O
						sw = 1;		
					}
					//�ׂɓ����������m������ꍇ
					if(i < 3 && dim[iCnt_Y][iCnt_X] == temp[i + 1] && temp[i + 1] != 0 ){
						//�ړ����Ȃ���A����
						dim[iCnt_Y][iCnt_X] += temp[i + 1];
						temp[i + 1] = 0;
						//������������������A�X�R�A����������
						score = dim[iCnt_Y][iCnt_X] + score;
						//���̒l���`�F�b�N����
						i++;
						//�ړ��ł���t���O
						sw = 1;		
					}
					//�O�̒l���������ǂ�����킸�A���̒l���`�F�b�N����
					i++;							
				}
				if(iCnt_X < i){
					for(; iCnt_X < 4; iCnt_X++){
						dim[iCnt_Y][iCnt_X] = 0;
					}
				}
			}
			break;

		// ���Ɉړ�
		case '5':
			//1�񂸂A�ړ�����
			for(iCnt_X = 0; iCnt_X < 4; iCnt_X++){								
				//�ꎞ�I�Ȕz��̗v�f�ԍ��̏�����					
				i = 3;
				//1�s���A���f����
				for(iCnt_Y = 3; iCnt_Y >= 0; iCnt_Y--){						
					//0�ȊO�̐������ꎞ�I�Ȕz��ɓ����
					if(dim[iCnt_Y][iCnt_X] != 0 ){	
						temp[i] = dim[iCnt_Y][iCnt_X];
						i--;
					}						
				}

				//�g���Ă��Ȃ��v�f��0�Ƃ���
				for (; i >= 0; temp[i--] = 0);
					
				i = 3;
				//�ړ���������`�F�b�N����
				//�ꎞ�I�Ȕz��̐������S���A����ɓ��ꂽ���A���[�v���甲����
				for(iCnt_Y = 3; iCnt_Y >= 0 && i >= 0; iCnt_Y--){							
					//�V�����z��̒l�ƈႤ�ꍇ�i�܂�A�������ړ������j
					if(dim[iCnt_Y][iCnt_X] != temp[i]){
						//����ւ�
						dim[iCnt_Y][iCnt_X] = temp[i];
						//�ړ��ł���t���O
						sw = 1;		
					}
					//�ׂɓ����������m������ꍇ
					if(i >=0 && dim[iCnt_Y][iCnt_X] == temp[i - 1] && temp[i - 1] != 0 ){
						//�ړ����Ȃ���A����
						dim[iCnt_Y][iCnt_X] += temp[i - 1];
						//������������������A�X�R�A����������
						score = dim[iCnt_Y][iCnt_X] + score;
						//���̒l���`�F�b�N����
						i--;
						//�ړ��ł���t���O
						sw = 1;		
					}
					//�O�̒l���������ǂ�����킸�A���̒l���`�F�b�N����
					i--;							
				}
				if(iCnt_Y > i){
					for(; iCnt_Y >= 0; iCnt_Y--){
						dim[iCnt_Y][iCnt_X] = 0;
					}
				}				
			}					
			break;
	}
	//�ړ������ꍇ�A�����P�������o��				
	if(sw == 1){
		output();
	}
}
/*action------------------------------------------------------------------------------------end*/

/*achive---------------------------------------------------------------------------------------st
�T�v�F		����
�g�p�ϐ��F	map[11][23]  map2048[11][23] map4096[11][23]  map8192[11][23]  iCnt_Y iCnt_X  
�����F		�Ȃ�
�߂�l�F	�Ȃ�
-----------------------------------------------------------------------------------------------*/
void achive(int x)
{
	int iCnt_Y;			//�c���̃J�E���^
	int iCnt_X;			//�����̃J�E���^
	int i;				//�J�E���^

	for(iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++){
		for(iCnt_X = 0; iCnt_X <4; iCnt_X++){	
			if(x == 2048 || x == 4096 || x == 8192){
				for(i = 0; i < 20; i++){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	
					if(i % 2 == 0){
						setCursor(7, 12 * 2);
						printf("����������������������������������");
						setCursor(8, 12 * 2);
						printf("��                              ��");
						setCursor(9, 12 * 2);
						printf("��                              ��");
						setCursor(10, 12 * 2);
						printf("��                              ��");
						setCursor(11, 12 * 2);
						printf("����������������������������������");
					}else{
						setCursor(7, 12 * 2);
						printf("����������������������������������");
						setCursor(8, 12 * 2);
						printf("��                              ��");
						setCursor(9, 12 * 2);
						printf("��                              ��");
						setCursor(10, 12 * 2);
						printf("��                              ��");
						setCursor(11, 12 * 2);
						printf("����������������������������������");
					}
					setCursor(9, 14 * 2);
					//�_����ŕ\��
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);	
					printf(" %d",x);
					//�����𔒂ŕ\��
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	
					printf(" �_�B���I�������ł��ˁ`");
					//�X�g�b�v
					Sleep(200);
				}
				system("cls");
				//�w�i�̕\��
				map_print();
				dim_print();
			}		
		}
	}		
}
/*achive------------------------------------------------------------------------------------end*/

/*fuction--------------------------------------------------------------------------------------st
�T�v�F		����
�g�p�ϐ��F	dim[4][4] iCnt_Y iCnt_X i sw  
�����F		�Ȃ�
�߂�l�F	�Ȃ�
-----------------------------------------------------------------------------------------------*/
void fuction()
{
	int iCnt_Y;			//�c���̃J�E���^
	int iCnt_X;			//�����̃J�E���^
	int i;				//�J�E���^
	int sw;				//�X�C�b�`

	system("cls");
	//�w�i�̕\��
	map_print();

	//�z�������������
	for(iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++){
		for(iCnt_X = 0; iCnt_X <4; iCnt_X++){	
			dim[iCnt_Y][iCnt_X] = 0;					
		}
	}
	//�X�R�A������������
	score = 0;

	//�ŏ���2�̐������o��
	for (i = 0; i < 2; output(), i++);
				
	do{
		sw = 0;		//�ړ��ł��Ȃ��Ə���������
		action();	//`�ړ����Ȃ���A�v�Z����

		//�ڕW�B���̕\��
		for(iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++){
			for(iCnt_X = 0; iCnt_X <4; iCnt_X++){	
				achive(dim[iCnt_Y][iCnt_X]);	//2048�A4096�C8192���`�F�b�N����				
			}
		}
		
		if (sw == 0){
			//���E�̓����������`�F�b�N����
			for(iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++){
				for(iCnt_X = 0; iCnt_X < 3; iCnt_X++){	
					//�E�ɓ����������m������ꍇ
					if(dim[iCnt_Y][iCnt_X] == dim[iCnt_Y][iCnt_X + 1]){
						sw = 1;				//�ړ��ł���̂�,���[�v�𑱂���
						break;				//���ʂȏ������Ȃ��ɂ���
					}					
				}
			}
			//�㉺�̓����������`�F�b�N����
			for (iCnt_X = 0; iCnt_X < 4; iCnt_X++) {
				for (iCnt_Y = 0; iCnt_Y < 3; iCnt_Y++) {
					//���ɓ����������m������ꍇ
					if (dim[iCnt_Y][iCnt_X] == dim[iCnt_Y + 1][iCnt_X]) {
						sw = 1;				//�ړ��ł���̂�,���[�v�𑱂���
						break;				//���ʂȏ������Ȃ��ɂ���
					}
				}
			}
		}		

		//�󔒂��`�F�b�N����
		for (iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++) {
			for (iCnt_X = 0; iCnt_X <4; iCnt_X++) {
				//�󔒂�����ꍇ
				if (dim[iCnt_Y][iCnt_X] == 0) {
					sw = 1;				//�ړ��ł���̂�,���[�v�𑱂���
					break;				//���ʂȏ������Ȃ��ɂ���
				}
			}
		}
	}while(sw == 1);

	//
	gameover();
	
}
/*fuction------------------------------------------------------------------------------------end*/

/*gameover--------------------------------------------------------------------------------------st
�T�v�F		����
�g�p�ϐ��F	dim[4][4] iCnt_Y iCnt_X i sw  
�����F		�Ȃ�
�߂�l�F	�Ȃ�
-----------------------------------------------------------------------------------------------*/
void gameover()
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("          \n\n");
	printf("          ����������������������������������������������������������\n");
	printf("          ��       ������         ��       ��      ��  ��������   ��\n");
	printf("          ��    ��       ��     ����      ����  ����  ��          ��\n");
	printf("          ��   ��             ��  ��     �� ���� ��  ��           ��\n");
	printf("          ��  ��  ������    ��������    ��  ��  ��  ��������      ��\n");
	printf("          ��  ��   ����   ��      ��   ��      ��  ��             ��\n");
	printf("          ��   ���� ��  ��        ��  ��      ��  ����������      ��\n");
	printf("          ��                                                      ��\n");
	printf("          ��         ������   ��        ��  ��������     ������   ��\n");
	printf("          ��       ��     ��  ��      ��   ��          ��      �� ��\n");
	printf("          ��     ��       ��  ��    ��    ��          ��      ��  ��\n");
	printf("          ��    ��       ��   ��  ��     ��������    ��������     ��\n");
	printf("          ��    ��      ��    ����      ��          ��   ��       ��\n");
	printf("          ��     ������       ��       ����������  ��      ��     ��\n");
	printf("          ����������������������������������������������������������\n");
	printf("          \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("          ����̃X�R�A��");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf(" %d ", score);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("�_�ŁA");

	if(score >= hiscore){
		printf("���j�ō��_��������B���߂łƂ��I\n\n");
	}else{
		printf("���j�ō��_�𒴂��Ă��Ȃ��B�c�O�ł��I�I\n\n");
	}
	printf("            ������x���킵�܂����H�i");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("�P: YES");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("     0 : NO");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("�j\n");
}
/*gameover------------------------------------------------------------------------------------end*/
