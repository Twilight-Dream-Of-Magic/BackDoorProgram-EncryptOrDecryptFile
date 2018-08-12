/****************************************************************************
Read Me - About This Source Code File

Chinese����:
�������������: C++
�����ļ���: Twilight-Dream-Of-Magic_File_Lock
����ƽ̨����: Windows �����п���̨
����ʵ������: �ļ��Գ�ʽ���ܽ���
�汾: Beta 1.0
Դ�����޸�ʱ��: 2017-8-1
����: Twilight-Dream-Of-Magic

EnglishӢ��:
Chinese
Computer Language Type: C++
Program File Name: Twilight-Dream-Of-Magic_File_Lock
Program Platform Type: Windows Command Line Console
The actual role of the program: file symmetric encryption and decryption
Version: Beta 1.0
Source code modified by: 2017-8-1
Author: Twilight-Dream-Of-Magic
*****************************************************************************/

#include <iostream>
#include <stdio.h>   //��׼�����������
#include <stdlib.h>  //��׼�⺯��
#include <string.h>  //�ַ���������
#include <windows.h>

using namespace std;

//typedef unsigned char byte;

int RunEncryptFile(char *E_SourceFileName, char *E_KEY, char *E_KEY2, char *E_KEY3, char *E_TargetFileNewName);
int RunDecryptFile(char *D_SourceFileName, char *D_KEY, char *D_KEY2, char *D_KEY3, char *D_TargetFileNewName);

int main()
{
	string Load_User_Keyboard_Input;

	std :: cout << "----------" << endl;
	std :: cout << "Enter 1 EncryptFile" << endl;
	std :: cout << "Enter 2 DecryptFile" << endl;
	std :: cout << "Enter 3 Exit Program" << endl;
	std :: cout << "----------" << endl;
	std :: cout << "" << endl;
	std :: cout << "System:Input And Output/Enter>";

	std :: cin >> Load_User_Keyboard_Input;
	getchar();

	if(Load_User_Keyboard_Input == "1")
	{
	  char E_SourceFileName[4096],     // ���ܵ��ļ���
		   E_TargetFileNewName[4096];  // ���ܺ�Ҫ������ļ���

	   char E_KEY[128], //File (Encryption or Encrypted) key �ļ�������Կ
			E_KEY2[128],
			E_KEY3[128];

	   printf("Please input >>> the source file name\n(Contains the directory name):\n");
	   printf("����Ҫ���ܵ��ļ���,[C:\]��Ҫ����ո�(��·��)��\n");
	   scanf("%s", E_SourceFileName);

		printf("\n");
		printf("����(����С��128)��Կ,��Ҫ����ո�\n");  //��Կ���û��Լ�����ģ�(����С��128)�������������Ҫ���ܵ��ļ������Կ
		printf("Please input >>> the key,Do not enter spaces!\n(length less than 128):\n");
		scanf("%s", E_KEY);

		printf("\n");
		printf("����(����С��128)��Կ2,��Ҫ����ո�\n"); //��Կ���û��Լ�����ģ�(����С��128)�������������Ҫ���ܵ��ļ������Կ
		printf("Please input >>> the key2,Do not enter spaces!\n(length less than 128):\n");
		scanf("%s", E_KEY2);

		printf("\n");
		printf("����(����С��128)��Կ3,��Ҫ����ո�\n"); //��Կ���û��Լ�����ģ�(����С��128)�������������Ҫ���ܵ��ļ������Կ
		printf("Please input >>> the key3,Do not enter spaces!\n(length less than 128):\n");
		scanf("%s", E_KEY3);

	   printf("\n");
	   printf("Please input >>> the target file new name(Contains the directory name):\n");
	   printf("���ܺ���ļ���,��Ҫ����ո�(��·��)��\n");  //�����ܺ���ļ�������������
	   scanf("%s",E_TargetFileNewName);

	   printf("Please wait, read and write in the file......\n");
	   printf("��ȴ����ļ���д��......\n");
	   getchar();

		if(RunEncryptFile(E_SourceFileName, E_KEY, E_KEY2, E_KEY3, E_TargetFileNewName))
		{
			printf("��ϲ�㣬�ļ�[%s]���ܳɹ���������[%s]��\n", E_SourceFileName, E_TargetFileNewName);
			printf("Congratulations, the file [%s] is encrypted successfully, saved in [%s]. \n", E_SourceFileName, E_TargetFileNewName);
			getchar();
			system("pause");
			return 0;
		}
	}
	if(Load_User_Keyboard_Input == "2")
	{
	   char D_SourceFileName[4096];     //Դ�ļ���
	   char D_TargetFileNewName[4096];  //Ŀ���ļ�������

		char D_KEY[128], //File (Decryption or Decrypted) key �ļ�������Կ
			 D_KEY2[128],
			 D_KEY3[128];

		 printf("\n");
		 printf("Please input >>> the source file name\n(Contains the directory name):\n");
		 printf("����Ҫ���ܵ��ļ���,[C:\]��Ҫ����ո�(��·��)��\n");
		 scanf("%s", D_SourceFileName);

		  printf("\n");
		  printf("����(����С��128)��Կ,��Ҫ����ո�\n");  //��Կ���û��Լ�����ģ������������Ҫ���ܵ��ļ�������Կ
		  printf("Please input >>> the key3,Do not enter spaces!\n(length less than 128):\n");
		  scanf("%s", D_KEY);

		  printf("\n");
		  printf("����(����С��128)��Կ2,��Ҫ����ո�\n");
		  printf("Please input >>> the key2,Do not enter spaces!\n(length less than 128):\n");
		  scanf("%s", D_KEY2);

		  printf("\n");
		  printf("����(����С��128)��Կ3,��Ҫ����ո�\n");
		  printf("Please input >>> the key,Do not enter spaces!\n(length less than 128):\n");
		  scanf("%s", D_KEY3);

		printf("\n");
		printf("Please input >>> the target file new name(Contains the directory name):\n");
		printf("���ܺ���ļ���,��Ҫ����ո�(��·��)��\n");  //�����ܺ���ļ�������������
		scanf("%s",D_TargetFileNewName);

		printf("Please wait, read and write in the file......\n");
		printf("��ȴ����ļ���д��......\n");
		getchar();

		if(RunDecryptFile(D_SourceFileName, D_KEY, D_KEY2, D_KEY3, D_TargetFileNewName))
		{
			printf("��ϲ�㣬�ļ�[%s]���ܳɹ���������[%s]��\n", D_SourceFileName, D_TargetFileNewName);
			printf("Congratulations, the file [%s] is decrypted successfully, saved in [%s]. \n", D_SourceFileName, D_TargetFileNewName);
			getchar();
			system("pause");
			return 0;
		}
	}

  if(Load_User_Keyboard_Input == "3")
  {
	return 0;
  }
  else
  {
	std :: cout << "User Input Error !" << endl;
	getchar();
	exit(1);
  }
}

#include "Main-By_Twilight-Dream.hpp