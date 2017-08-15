/****************************************************************************
Read Me - About This Source Code File

Chinese����:
�������������: C++
�����ļ���: Twlilght_Yujiang_File_Lock
����ƽ̨����: Windows �����п���̨
����ʵ������: �ļ��Գ�ʽ���ܽ���
�汾: Beta 2.0
Դ�����޸�ʱ��: 2017-8-11
����:Twlilght_Yujiang

EnglishӢ��:
Chinese
Computer Language Type: C ++
Program File Name: Twlilght_Yujiang_File_Lock
Program Platform Type: Windows Command Line Console
The actual role of the program: file symmetric encryption and decryption
Version: Beta 2.0
Source code modified by: 2017-8-11
Author: Twlilght_Yujiang
*****************************************************************************/

#include <iostream>
#include <fstream>
#include <stdio.h>   //C��׼�����������
#include <stdlib.h>  //C��׼�⺯��
#include <string.h>  //�ַ���������
#include <windows.h>

using namespace std;

//typedef unsigned char byte;

int RunEncryptFile(char *E_SourceFileName, char *E_KEY, char *E_KEY2, char *E_KEY3, char *E_TargetFileNewName);
int RunDecryptFile(char *D_SourceFileName, char *D_KEY, char *D_KEY2, char *D_KEY3, char *D_TargetFileNewName);

void ConsoleTableColorSet(int R,int G,int B)
{
	if(R<0) R=0;
	if(R>1) R=1;

	if(G<0) G=0;
	if(G>1) G=1;

	if(B<0) B=0;
	if(B>1) B=1;

    if(R == 1 && G == 1 && B == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	}
	else if(R == 1 && G == 1 && B == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
	}
	else if(R == 1 && G == 0 && B == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);
	}
	else if(R == 0 && G == 1 && B == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
	}
	else if(R == 1 && G == 0 && B == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
	}
	else if(R == 0 && G == 1 && B == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	}
	else if(R == 0 && G == 0 && B == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
	}
}

int main()
{
ProgramMainMenu:

    string Load_User_Keyboard_Input;

    system("color 0A");

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
       system("cls");
       system("color 1A");

       char E_SourceFileName[4096],    // ���ܵ��ļ���
            E_TargetFileNewName[4096]; // ���ܺ�Ҫ������ļ���

      //char E_TargetFileLastNameOutput = (E_TargetFileNewName + ".TY_ENCRYPTED"); //��󱣴�ļ��ܺ��ļ���

        char E_KEY[128], //File (Encryption or Encrypted) key �ļ�������Կ
             E_KEY2[128],
             E_KEY3[128];

         std :: cout << "Please input >>> the source file name.\nDo not enter spaces!\n(Contains the directory name):" << endl;
         std :: cout << "����Ҫ���ܵ��ļ���,[C:\]��Ҫ����ո�(��·��)��" << endl;
         std :: cin >> E_SourceFileName;

          std :: cout << "\n";
          std :: cout << "����(����С��128)��Կ,��Ҫ����ո�" << endl;  //��Կ���û��Լ�����ģ�(����С��128)�������������Ҫ���ܵ��ļ������Կ
          std :: cout << "Please input >>> the key,Do not enter spaces!\n(length less than 128):" << endl;
          std :: cin >> E_KEY;

          std :: cout << "\n";
		  std :: cout << "����(����С��128)��Կ2,��Ҫ����ո�" << endl;
          std :: cout << "Please input >>> the key2,Do not enter spaces!\n(length less than 128):" << endl;
          std :: cin >> E_KEY2;

          std :: cout << "\n";
          std :: cout << "����(����С��128)��Կ3,��Ҫ����ո�" << endl;
          std :: cout << "Please input >>> the key3,Do not enter spaces!\n(length less than 128):" << endl;
          std :: cin >> E_KEY3;

           std :: cout << "\n";
           std :: cout << "Please output >>> the target file new name.\nDo not enter spaces!\n(Contains the directory name):" << endl;
           std :: cout << "���ܺ���ļ���,��Ҫ����ո�(��·��)��" << endl;  //�����ܺ���ļ�������������
           std :: cin >> E_TargetFileNewName;
           system("cls");

		   std :: cout << "���ڼ�¼�����������������ļ����ܣ�3����Կ�ַ���......" << endl;
		   std :: cout << "Is being recorded and exported, this time for file encryption, 3 key string......" << endl;
		   ofstream PasswordOutputKeyFile;
		   PasswordOutputKeyFile.open("FILE-ENCRYPTION-DECRYPTIPN-PASSWORD.KEY.TXT");
		   PasswordOutputKeyFile << "Twlilght_Yujiang File Lock Password [Key String] Save\n" << endl;
		   PasswordOutputKeyFile << "\n" << endl;
		   PasswordOutputKeyFile << "Source Input File Name and Path: " << E_SourceFileName << "\n" << endl;
		   PasswordOutputKeyFile << "EncryptFile: New Output Target File Name and Path: " << E_TargetFileNewName << "\n" << endl;
		   PasswordOutputKeyFile << "Key string1 [Password1]: " << E_KEY << "\n" << endl;
		   PasswordOutputKeyFile << "Key string2 [Password2]: " << E_KEY2 << "\n" << endl;
		   PasswordOutputKeyFile << "Key string3 [Password3]: " << E_KEY3 << "\n" << endl;
		   PasswordOutputKeyFile << "<******************************************************************************************>" << "\n" << endl;
		   PasswordOutputKeyFile.close();

	        std :: cout << "Please wait, read and write in the file......" << endl;
	        std :: cout << "��ȴ����ļ���д��......" << endl;
	        getchar();

      if(RunEncryptFile(E_SourceFileName, E_KEY, E_KEY2, E_KEY3, E_TargetFileNewName))
      {
         printf("��ϲ�㣬�ļ�[%s]���ܳɹ���������[%s]��\n", E_SourceFileName, E_TargetFileNewName);
         printf("Congratulations, the file [%s] is encrypted successfully, saved in [%s]. \n", E_SourceFileName, E_TargetFileNewName);
		 getchar();
         system("pause");
         system("cls");
         goto ProgramMainMenu;
      }
    }
    if(Load_User_Keyboard_Input == "2")
    {
       system("cls");
       system("color 1A");

   	   char D_SourceFileName[4096],    //Դ�ļ���
            D_TargetFileNewName[4096]; //Ŀ���ļ�������

       //char D_TargetFileLastNameOutput = (D_TargetFileNewName - ".TY_ENCRYPTED"); //��󱣴�Ľ��ܺ��ļ���

        char D_KEY[128], //File (Decryption or Decrypted) key �ļ�������Կ
             D_KEY2[128],
             D_KEY3[128];

         std :: cout << "Please input >>> the source file name.\nDo not enter spaces!\n(Contains the directory name):" << endl;
		 std :: cout << "����Ҫ���ܵ��ļ���,[C:\]��Ҫ����ո�(��·��)��" << endl;
         std :: cin >> D_SourceFileName;

          std :: cout << "\n";
          std :: cout << "����(����С��128)��Կ,��Ҫ����ո�" << endl;  //��Կ���û��Լ�����ģ������������Ҫ���ܵ��ļ�������Կ
          std :: cout << "Please input >>> the key3,Do not enter spaces!\n(length less than 128):" << endl;
          std :: cin >> D_KEY;

          std :: cout << "\n";
		  std :: cout << "����(����С��128)��Կ2,��Ҫ����ո�" << endl;
		  std :: cout << "Please input >>> the key2,Do not enter spaces!\n(length less than 128):" << endl;
          std :: cin >> D_KEY2;

          std :: cout << "\n";
		  std :: cout << "����(����С��128)��Կ3,��Ҫ����ո�" << endl;
		  std :: cout << "Please input >>> the key,Do not enter spaces!\n(length less than 128):" << endl;
          std :: cin >> D_KEY3;

           std :: cout << "\n";
		   std :: cout << "Please output >>> the target file new name.\nDo not enter spaces!\n(Contains the directory name):" << endl;
           std :: cout << "���ܺ���ļ���,��Ҫ����ո�(��·��)��" << endl;  //�����ܺ���ļ�������������
           std :: cin >> D_TargetFileNewName;
           system("cls");

		    std :: cout << "Please wait, read and write in the file......" << endl;
	        std :: cout << "��ȴ����ļ���д��......" << endl;
		    getchar();

       if(RunDecryptFile(D_SourceFileName, D_KEY, D_KEY2, D_KEY3, D_TargetFileNewName))
       {
          printf("��ϲ�㣬�ļ�[%s]���ܳɹ���������[%s]��\n", D_SourceFileName, D_TargetFileNewName);
          printf("Congratulations, the file [%s] is decrypted successfully, saved in [%s]. \n", D_SourceFileName, D_TargetFileNewName);
		  getchar();
          system("pause");
          system("cls");
          goto ProgramMainMenu;
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

#include "Main_2_By_Twlilght_Yujiang.hpp"