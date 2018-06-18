/****************************************************************************
Read Me - About This Source Code File

Chinese����:
�������������: C++
�����ļ���: Twlilght_Yujiang_File_Lock
����ƽ̨����: Windows �����п���̨
����ʵ������: �ļ��Գ�ʽ���ܽ���
�汾: Beta 3.0
Դ�����޸�ʱ��: 2017-8-14
����: Twilight-Dream-Of-Magic

EnglishӢ��:
Chinese
Computer Language Type: C ++
Program File Name: Twlilght_Yujiang_File_Lock
Program Platform Type: Windows Command Line Console
The actual role of the program: file symmetric encryption and decryption
Version: Beta 3.0
Source code modified by: 2017-8-14
Author: Twilight-Dream-Of-Magic
*****************************************************************************/

#include <iostream>
#include <fstream>
#include <io.h>
#include <stdio.h>   //�����C���Ա�׼����������� Computer C language standard input and output functions
#include <stdlib.h>  //�����C���Ա�׼�⺯�� Computer C language standard library functions
#include <string.h>  //�����C�����ַ����������� Computer C language string handling functions
#include <windows.h>
#include "stdafx.h"

//#include <ImageHlp.h> //MakeSureDirectoryPathExists("");
//#pragma comment(lib, "ImageHlp.lib")

using namespace std;

//typedef unsigned char byte;

int RunEncryptFile(const char *E_SourceFileCharPath, char *E_KEY, char *E_KEY2, char *E_KEY3, char *E_KEY4, const char *E_TargetFileCharPath);
int RunDecryptFile(const char *D_SourceFileCharPath, char *D_KEY, char *D_KEY2, char *D_KEY3, char *D_KEY4, const char *D_TargetFileCharPath);

string E_IF_PATH = ".\\WorkPath\\Encrypt\\InputFile\\",  //����֮ǰ���ļ���·�� Before encrypting the path of the file
	   E_OF_PATH = ".\\WorkPath\\Encrypt\\OutputFile\\"; //����֮���ļ���·�� After encrypting the path of the file

string E_SourceFileName,         // Դ�ļ���
       E_SourceFileMainName,     // Դ�ļ���Ҫ��
       E_SourceFileExtendedName, // Դ�ļ���չ��
       E_TargetFileExtendedName; // Ŀ���ļ���չ��

char E_KEY[128], //File (Encryption or Encrypted) key �ļ�������Կ
     E_KEY2[128],
     E_KEY3[128],
	 E_KEY4[128];

string D_IF_PATH = ".\\WorkPath\\Decrypt\\InputFile\\",  //����֮ǰ���ļ���·�� Before decrypting the path of the file
	   D_OF_PATH = ".\\WorkPath\\Decrypt\\OutputFile\\"; //����֮���ļ���·�� After decrypting the path of the file

string D_SourceFileName,         //Դ�ļ���
	   D_TargetFileMainName,     //Ŀ���ļ���Ҫ��
       D_TargetFileTempName,     //Ŀ���ļ���ʱ������
       D_TargetFileExtendedName; //Ŀ���ļ�Դ��չ��

char D_KEY[128], //File (Decryption or Decrypted) key �ļ�������Կ
     D_KEY2[128],
     D_KEY3[128],
	 D_KEY4[128];

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
    system("cls");

    std :: cout << "----------------------------------------" << endl;
    std :: cout << "Enter 1 Encrypt File" << endl;
    std :: cout << "1.�����ļ�\n" << endl;
    std :: cout << "Enter 2 Decrypt File" << endl;
    std :: cout << "2.�����ļ�\n" << endl;
	std :: cout << "Enter 3 Use The Information Manual" << endl;
	std :: cout << "3.ʹ����Ϣ˵���ֲ�\n" << endl;
	std :: cout << "Enter 4 Clean Up The Workspace[To Restore The Initial State]" << endl;
	std :: cout << "4.���������ռ�[�ָ���ʼ״̬]\n" << endl;
    std :: cout << "Enter 5 Exit Program" << endl;
    std :: cout << "5.�˳�����\n" << endl;
    std :: cout << "----------------------------------------" << endl;
    std :: cout << "System:Input And Output/Enter>";

    std :: cin >> Load_User_Keyboard_Input;
	getchar();

    if(Load_User_Keyboard_Input == "1")
    {
        if(!access(".\\WorkPath\\Encrypt\\InputFile\\",0))
        {
            std :: cout << "Building and Loading Folder 20%" << endl;
        }
        else
        {
            system("@Mkdir .\\WorkPath\\Encrypt\\InputFile\\");
        }

        if(!access(".\\WorkPath\\Encrypt\\OutputFile\\",0))
        {
            std :: cout << "Building and Loading Folder 40%" << endl;
        }
        else
        {
            system("@Mkdir .\\WorkPath\\Encrypt\\OutputFile\\");
        }

        if(!access(".\\WorkPath\\Decrypt\\InputFile\\",0))
        {
            std :: cout << "Building and Loading Folder 60%" << endl;
        }
        else
        {
            system("@Mkdir .\\WorkPath\\Decrypt\\InputFile\\");
        }

        if(!access(".\\WorkPath\\Decrypt\\OutputFile\\",0))
        {
            std :: cout << "Building and Loading Folder 80%" << endl;
        }
        else
        {
            system("@Mkdir .\\WorkPath\\Decrypt\\OutputFile\\");
        }

        if(!access(".\\File-Key-Record-Log\\",0))
        {
            std :: cout << "Building and Loading Folder 100%" << endl;
        }
        else
        {
            system("@Mkdir .\\File-Key-Record-Log\\");
        }

    system("cls");
    system("color 1A");

		 ConsoleTableColorSet(0,0,0);
		 std :: cout << "Please input >>> the source file name + file extension name.\nDo not enter spaces!\n:" << endl;
         std :: cout << "����Ҫ���ܵ��ļ���+�ļ���չ������Ҫ����ո�!" << endl;
         std :: cin >> E_SourceFileName;

         std :: cout << "Please input >>> the source file name, not the file extension name!\nDo not enter spaces!\n:" << endl;
         std :: cout << "����Ҫ���ܵ��ļ���Ҫ���������ļ���չ������Ҫ����ո�!" << endl;
         std :: cin >> E_SourceFileMainName;

         std :: cout << "Please input >>> the file extension name.\nDo not enter spaces!\n:" << endl;
         std :: cout << "����Ҫ���ܵ��ļ���չ������Ҫ����ո�!" << endl;
         std :: cin >> E_SourceFileExtendedName;
         system("cls");

		   std :: cout << "���ڼ�¼��������Դ�ļ�����......\n[����!]�ڽ��б��β��������´�ѡ��ͬ�����Ƶļ����ļ������н����ļ�����!\n��������֮ǰ����������ֹʹ�ü����ļ����ܣ�" << endl;
           std :: cout << "Recording and exporting, source file name......\n[Warning!]After doing this operation, please select the same name next time the encrypted file, decrypt the file operation!\nOtherwise, before that, please immediately disable the use of encrypted file function" << endl;
		   std :: cout << "���Ƿ�������Э��?[����Enter����] ���� [�رճ���]......" << endl;
		   std :: cout << "Whether you accept this agreement?[Keyboard Enter Continue] Or [Close this program]......" << endl;
		   system("pause");
		   system("cls");

            ofstream SourceFileNameTempOutput;
		    SourceFileNameTempOutput.open(".\\SourceFileName_Temp.INI");
            SourceFileNameTempOutput << E_SourceFileName << endl;
		    SourceFileNameTempOutput.close();
		    SourceFileNameTempOutput.open(".\\SourceFileMainName_Temp.INI");
		    SourceFileNameTempOutput << E_SourceFileMainName << endl;
		    SourceFileNameTempOutput.close();
		    SourceFileNameTempOutput.open(".\\SourceFileExtendedName_Temp.INI");
		    SourceFileNameTempOutput << E_SourceFileExtendedName << endl;
		    SourceFileNameTempOutput.close();

             ConsoleTableColorSet(0,0,1);
             std :: cout << "\n";
             std :: cout << "����(����С��128)��Կ,��Ҫ����ո�!" << endl;  //��Կ���û��Լ�����ģ�(����С��128)�������������Ҫ���ܵ��ļ�������Կ
             std :: cout << "Please input >>> the key,Do not enter spaces!\n(length less than 128):" << endl;
             std :: cin >> E_KEY;

             ConsoleTableColorSet(0,1,0);
             std :: cout << "\n";
             std :: cout << "����(����С��128)��Կ2,��Ҫ����ո�!" << endl;
             std :: cout << "Please input >>> the key2,Do not enter spaces!\n(length less than 128):" << endl;
             std :: cin >> E_KEY2;

             ConsoleTableColorSet(0,1,1);
             std :: cout << "\n";
             std :: cout << "����(����С��128)��Կ3,��Ҫ����ո�!" << endl;
             std :: cout << "Please input >>> the key3,Do not enter spaces!\n(length less than 128):" << endl;
             std :: cin >> E_KEY3;

             ConsoleTableColorSet(1,0,0);
		     std :: cout << "\n";
             std :: cout << "����(����С��128)��Կ4,��Ҫ����ո�!" << endl;
             std :: cout << "Please input >>> the key3,Do not enter spaces!\n(length less than 128):" << endl;
             std :: cin >> E_KEY4;

		      ConsoleTableColorSet(1,0,1);
              std :: cout << "\n";
              std :: cout << "Please output >>> file extension name.\nDo not enter spaces!\n[.TSMY-ENCRYPTED]:" << endl;
              std :: cout << "����ļ���չ��,��Ҫ����ո�[.TSMY-ENCRYPTED]��" << endl;  //�����ܺ���ļ�����ļ���չ����������
              std :: cin >> E_TargetFileExtendedName;
		      if(E_TargetFileExtendedName == " ")
		      {
                 string E_TargetFileAddExtendedName = ".TSMY-ENCRYPTED";
                 E_TargetFileExtendedName = E_TargetFileAddExtendedName;
		      }

		      system("cls");

		       string E_SourceFileStringPath = E_IF_PATH + E_SourceFileName;
               string E_TargetFileStringPath = E_OF_PATH + E_SourceFileName + E_TargetFileExtendedName;

               const char *E_SourceFileCharPath = E_SourceFileStringPath.c_str();
               const char *E_TargetFileCharPath = E_TargetFileStringPath.c_str();

              /*char *E_SourceFileLastNameOutput; //����д���ļ���
               strcpy(E_SourceFileLastNameOutput,E_SourceFileCharPath);
	           char *E_TargetFileLastNameOutput; //��󱣴�ļ��ܺ��ļ���
	           strcpy(E_TargetFileLastNameOutput,E_TargetFileCharPath);*/

		        ConsoleTableColorSet(1,1,0);
		        std :: cout << "���ڼ�¼�����������������ļ����ܣ�4����Կ�ַ���......" << endl;
		        std :: cout << "Is being recorded and exported, this time for file encryption, 4 key string......" << endl;
		        ofstream PasswordOutputKeyFile;
		        PasswordOutputKeyFile.open(".\\File-Key-Record-Log\\ENCRYPTION-DECRYPTIPN-PASSWORD.KEY.TXT");
		        PasswordOutputKeyFile << "Twlilght_Yujiang File Lock Password [Key String] Save\n" << endl;
		        PasswordOutputKeyFile << "\n" << endl;
		        PasswordOutputKeyFile << "Source Input File Name and Path: " << E_SourceFileStringPath << "\n" << endl;
		        PasswordOutputKeyFile << "EncryptFile: New Output Target File Name and Path: " << E_TargetFileStringPath << "\n" << endl;
		        PasswordOutputKeyFile << "Key string1 [Password1]: " << E_KEY << "\n" << endl;
		        PasswordOutputKeyFile << "Key string2 [Password2]: " << E_KEY2 << "\n" << endl;
		        PasswordOutputKeyFile << "Key string3 [Password3]: " << E_KEY3 << "\n" << endl;
		        PasswordOutputKeyFile << "Key string4 [Password3]: " << E_KEY4 << "\n" << endl;
		        PasswordOutputKeyFile << "<******************************************************************************************>" << "\n" << endl;
		        PasswordOutputKeyFile.close();

                 ConsoleTableColorSet(1,1,1);
	             std :: cout << "Please wait, read and write in the file......" << endl;
	             std :: cout << "��ȴ����ļ���д��......" << endl;
	             getchar();

                 if(RunEncryptFile(E_SourceFileCharPath, E_KEY, E_KEY2, E_KEY3, E_KEY4, E_TargetFileCharPath))
                 {
                   printf("��ϲ�㣬�ļ�[%s]���ܳɹ���������[%s]��\n", E_SourceFileCharPath, E_TargetFileCharPath);
                   printf("Congratulations, the file [%s] is encrypted successfully, saved in [%s]. \n", E_SourceFileCharPath, E_TargetFileCharPath);
		           getchar();
                   system("pause");
                   system("cls");
                   goto ProgramMainMenu;
                 }
            }

    if(Load_User_Keyboard_Input == "2")
    {
        if(!access(".\\WorkPath\\Encrypt\\InputFile\\",0))
        {
            std :: cout << "Building and Loading Folder 20%" << endl;
        }
        else
        {
            system("@Mkdir .\\WorkPath\\Encrypt\\InputFile\\");
        }

        if(!access(".\\WorkPath\\Encrypt\\OutputFile\\",0))
        {
            std :: cout << "Building and Loading Folder 40%" << endl;
        }
        else
        {
            system("@Mkdir .\\WorkPath\\Encrypt\\OutputFile\\");
        }

        if(!access(".\\WorkPath\\Decrypt\\InputFile\\",0))
        {
            std :: cout << "Building and Loading Folder 60%" << endl;
        }
        else
        {
            system("@Mkdir .\\WorkPath\\Decrypt\\InputFile\\");
        }

        if(!access(".\\WorkPath\\Decrypt\\OutputFile\\",0))
        {
            std :: cout << "Building and Loading Folder 80%" << endl;
        }
        else
        {
            system("@Mkdir .\\WorkPath\\Decrypt\\OutputFile\\");
        }

        if(!access(".\\File-Key-Record-Log\\",0))
        {
            std :: cout << "Building and Loading Folder 100%" << endl;
        }
        else
        {
            system("@Mkdir .\\File-Key-Record-Log\\");
        }

    system("cls");
    system("color 1A");

		 ConsoleTableColorSet(1,1,1);
         std :: cout << "Please input >>> the source file name + file extension name.\nDo not enter spaces!\n:" << endl;
		 std :: cout << "����Ҫ���ܵ��ļ���+�ļ���չ��,��Ҫ����ո�!" << endl;
         std :: cin >> D_SourceFileName;

		  ConsoleTableColorSet(1,1,0);
          std :: cout << "\n";
          std :: cout << "����(����С��128)��Կ,��Ҫ����ո�!" << endl;  //��Կ���û��Լ�����ģ������������Ҫ���ܵ��ļ�������Կ
          std :: cout << "Please input >>> the key3,Do not enter spaces!\n(length less than 128):" << endl;
          std :: cin >> D_KEY;

		  ConsoleTableColorSet(1,0,1);
          std :: cout << "\n";
		  std :: cout << "����(����С��128)��Կ2,��Ҫ����ո�!" << endl;
		  std :: cout << "Please input >>> the key2,Do not enter spaces!\n(length less than 128):" << endl;
          std :: cin >> D_KEY2;

		  ConsoleTableColorSet(1,0,0);
          std :: cout << "\n";
		  std :: cout << "����(����С��128)��Կ3,��Ҫ����ո�!" << endl;
		  std :: cout << "Please input >>> the key,Do not enter spaces!\n(length less than 128):" << endl;
          std :: cin >> D_KEY3;

		  ConsoleTableColorSet(0,1,1);
		  std :: cout << "\n";
		  std :: cout << "����(����С��128)��Կ4,��Ҫ����ո�!" << endl;
		  std :: cout << "Please input >>> the key,Do not enter spaces!\n(length less than 128):" << endl;
          std :: cin >> D_KEY4;

          system("cls");

           ConsoleTableColorSet(0,1,0);

           std :: cout << "\n";
           std :: cout << "����ڵ�ǰ�ļ����������ļ�[.\\*.INI]�����ڣ�����Ͳ�������Զ��ָ�ԭ�����ļ����ơ�\n����Ҫ���������ļ���!" << endl;
           std :: cout << "If the configuration file [.\\*.INI] does not exist in the current folder, the program will not automatically restore the original file name.\nYou need to re-enter the file name!" << endl;
		   std :: cout << "Please output >>> target file main name,not the file extension name!\nDo not enter spaces!\n[DATA-DECRYPTED]:" << endl;
           std :: cout << "����ļ���Ҫ���������ļ���չ������Ҫ����ո�[DATA-TSMY-DECRYPTED]!" << endl;  //�����ܺ���ļ������Ҫ�ļ�����������
           if(!access(".\\SourceFileMainName_Temp.INI",0))
           {
               //char TFMN_Buffer[256];
               ifstream LoadSourceFileNameConfigure(".\\SourceFileMainName_Temp.INI",ios::in);
               if(LoadSourceFileNameConfigure.fail())
               {
                 std :: cout << "Error End" << endl;
               }
               while(!LoadSourceFileNameConfigure.eof())
               {
                 LoadSourceFileNameConfigure >> D_TargetFileMainName;
                 //LoadSourceFileNameConfigure.getline(TFMN_Buffer,256,'\n'); //getline(char *,int,char) ��ʾ�����ַ��ﵽ256�����������оͽ���
                 //D_TargetFileMainName = TFMN_Buffer;
               }
               LoadSourceFileNameConfigure.close();
           }
           else
           {
               std :: cout << "�����ļ�" << ".\\SourceFileMainName_Temp.INI" << "δ�ҵ�!\n" << "��������������!" << endl;
               std :: cout << "Configuration file" << ".\\SourceFileMainName_Temp.INI" << "Not found!\n" << "Please re-enter the name!" << endl;
               HANDLE hFILE = CreateFile(".\\SourceFileMainName_Temp.INI",GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
               std :: cin >> D_TargetFileMainName;

           }

           system("cls");

           std :: cout << "\n";
           std :: cout << "����ڵ�ǰ�ļ����������ļ�[.\\*.INI]�����ڣ�����Ͳ�������Զ��ָ�ԭ�����ļ����ơ�\n����Ҫ���������ļ���!" << endl;
           std :: cout << "If the configuration file [.\\*.INI] does not exist in the current folder, the program will not automatically restore the original file name.\nYou need to re-enter the file name!" << endl;
		   std :: cout << "Please output >>> target file temp add name.\nDo not enter spaces!\n[-DECRYPTED]:" << endl;
           std :: cout << "����ļ���ʱ����������Ҫ����ո�[-TSMY-DECRYPTED]!" << endl; //�����ܺ���ļ�����ļ���ʱ��������������
           std :: cout << "Prevent source encrypted files from being overwritten" << endl;
           std :: cout << "��ֹԴ�����ļ�������" << endl;
           std :: cin >> D_TargetFileTempName;
           if(D_TargetFileTempName == " ")
		   {
              string D_TargetFileAddName = "-TSMY-DECRYPTED";
              D_TargetFileTempName = D_TargetFileAddName;
		   }

		   system("cls");

           std :: cout << "����ڵ�ǰ�ļ����������ļ�[.\\*.INI]�����ڣ�����Ͳ�������Զ��ָ�ԭ�����ļ����ơ�\n����Ҫ���������ļ���!" << endl;
           std :: cout << "If the configuration file [.\\*.INI] does not exist in the current folder, the program will not automatically restore the original file name.\nYou need to re-enter the file name!" << endl;
		   std :: cout << "Please output >>> target file extension name!\nDo not enter spaces!\n[-DECRYPTED]:" << endl;
           std :: cout << "����ļ���չ������Ҫ����ո�[-TSMY-DECRYPTED]!" << endl;  //�����ܺ���ļ�����ļ���չ����������
           if(!access(".\\SourceFileExtendedName_Temp.INI",0))
           {
             ifstream LoadSourceFileNameConfigure(".\\SourceFileExtendedName_Temp.INI",ios::in);
             //char TFEN_Buffer[256];
             if(LoadSourceFileNameConfigure.fail())
             {
               std :: cout << "Error End" << endl;
             }
             while(!LoadSourceFileNameConfigure.eof())
             {
               LoadSourceFileNameConfigure >> D_TargetFileExtendedName;
               //LoadSourceFileNameConfigure.getline(TFEN_Buffer,256,'\n'); //getline(char *,int,char) ��ʾ�����ַ��ﵽ256�����������оͽ���
               //D_TargetFileExtendedName = TFEN_Buffer;
             }
             LoadSourceFileNameConfigure.close();
           }
           else
           {
               std :: cout << "�����ļ�" << ".\\SourceFileExtendedName_Temp.INI" << "δ�ҵ�!\n" << "��������������!" << endl;
               std :: cout << "Configuration file" << ".\\SourceFileExtendedName_Temp.INI" << "Not found!\n" << "Please re-enter the name!" << endl;
               HANDLE hFILE = CreateFile(".\\SourceFileExtendedName_Temp.INI",GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
               std :: cin >> D_TargetFileExtendedName;
           }

           system("cls");

           string D_SourceFileStringPath = D_IF_PATH + D_SourceFileName;
           string D_TargetFileStringPath = D_OF_PATH + D_TargetFileMainName + D_TargetFileTempName + D_TargetFileExtendedName;

           const char *D_SourceFileCharPath = D_SourceFileStringPath.c_str();
           const char *D_TargetFileCharPath = D_TargetFileStringPath.c_str();

           /*char *D_SourceFileLastNameOutput; //����д���ļ���
           strcpy(D_SourceFileLastNameOutput,D_SourceFileCharPath);
           char *D_TargetFileLastNameOutput; //�����ʱ����Ľ��ܺ���ļ���
           strcpy(D_TargetFileLastNameOutput,D_TargetFileCharPath);*/

			ConsoleTableColorSet(0,0,1);
		    std :: cout << "Please wait, read and write in the file......" << endl;
	        std :: cout << "��ȴ����ļ���д��......" << endl;
		    getchar();

       if(RunDecryptFile(D_SourceFileCharPath, D_KEY, D_KEY2, D_KEY3, D_KEY4, D_TargetFileCharPath))
       {
          printf("��ϲ�㣬�ļ�[%s]���ܳɹ���������[%s]��\n", D_SourceFileCharPath, D_TargetFileCharPath);
          printf("Congratulations, the file [%s] is decrypted successfully, saved in [%s]. \n", D_SourceFileCharPath, D_TargetFileCharPath);
		  getchar();
          system("pause");
          system("cls");
          goto ProgramMainMenu;
       }
    }
  if(Load_User_Keyboard_Input == "3")
  {
    Instruction_Manual_Language_Restart:
    system("cls");
  	std :: cout << "��ӭ��ĵ����� ���Ǳ������˵���ֲ�[Beta Version 3.0]���������ʹ��ǰ����ϸ�Ķ�" << endl;
  	std :: cout << "Welcome to your arrival! This is the instruction manual [Beta Version 3.0] of this program, please be sure to read carefully before using it" << endl;
  	std :: cout << "" << endl;
  	std :: cout << "enUS----------English Ӣ��" << endl;
  	std :: cout << "zhCN----------Chinese ����" << endl;
  	std :: cout << "MENU----------Back Main Menu �������˵�" << endl;
  	string Instruction_Manual_Language;
  	std :: cin >> Instruction_Manual_Language;
  	if(Instruction_Manual_Language == "enUS")
    {
      system("cls");
      system("color 67");
      std :: cout << "When the program executes the function of encrypting the file or decrypting the file, it will create the workspace folder, input the folder, output the folder.\n" << endl;
      std :: cout << "When the program encrypts the file or decrypts the file and waits, the program is reading and writing the file in the background.\nNever close the program at this time! Otherwise your data is damaged and bear the consequences.\nIt is recommended that you after the data backup, use this program to encrypt the file or decrypt the file!\n" << endl;
      system("pause");
      system("cls");

    }
    if(Instruction_Manual_Language == "zhCN")
    {
      system("cls");
      system("color 17");
      std :: cout << "������ִ�м����ļ�������ļ��Ĺ���ʱ�������������ռ��ļ��У������ļ��У�����ļ��С�\n" << endl;
      std :: cout << "����������ļ�������ļ����ҵȴ�ʱ���������ں�̨��ȡ��д���ļ������ʱ����Զ��Ҫ�ر��������\n�����������ݱ��𻵲��е�������������ڽ������ݱ���֮���������������ļ�������ļ���\n" << endl;
      system("pause");
      system("cls");

    }
    if(Instruction_Manual_Language == "MENU")
    {
       system("cls");
       goto ProgramMainMenu;
    }
    else
    {
        if(Instruction_Manual_Language != "enUS","zhCN")
        {
          ConsoleTableColorSet(0,0,0);
          goto Instruction_Manual_Language_Restart;
        }
    }

  }
  if(Load_User_Keyboard_Input == "4")
  {
    Clear_Workspace_Restart:
    string Clear_Workspace;
    system("color 0C");
  	std :: cout << "[����!]�������еĲ�������ѡ�� <File-Key-Record-Log> �� <WorkPath> �ļ��У�Ȼ�����õ�ɾ����������!\n" << endl;
  	std :: cout << "����Դ�ļ������ɵļ����ļ������ɵĽ����ļ���������־������\n" << endl;
  	std :: cout << "�����֪�����գ��밴���� [Y������ N������]\n[ Yes / No ]" << endl;

  	std :: cout << "[Warning!] The upcoming operation will select the <File-Key-Record-Log>and <WorkPath folders>, and then permanently delete all the data!\n" << endl;
  	std :: cout << "Including source files, generated encrypted files, generated decrypted files, password logs, configuration\n" << endl;
  	std :: cout << "If you know the risk, press the keypad [Y key to continue N key to return]\n[Yes / No]" << endl;
  	std :: cin >> Clear_Workspace;
  	if(Clear_Workspace == "Y","y")
    {
       DeleteFile(".\\SourceFileName_Temp.INI");
       DeleteFile(".\\SourceFileMainName_Temp.INI");
       DeleteFile(".\\SourceFileExtendedName_Temp.INI");
       
	   system("@Del /s /f /q .\\File-Key-Record-Log\\*.*");
	   system("@Del /s /f /q .\\WorkPath\\*.*");
       
	   system("@Del /s /f /q .\\WorkPath\\Encrypt\\*.*");
	   system("@Del /s /f /q .\\WorkPath\\Encrypt\\InputFile\\*.*");
	   system("@Del /s /f /q .\\WorkPath\\Encrypt\\OutputFile\\*.*");
	   
	   system("@Del /s /f /q .\\WorkPath\\Decrypt\\*.*");
	   system("@Del /s /f /q .\\WorkPath\\Decrypt\\InputFile\\*.*");
	   system("@Del /s /f /q .\\WorkPath\\Decrypt\\OutputFile\\*.*");
       
	   system("@Rmdir /s /q .\\File-Key-Record-Log\\");
	   
	   system("@Rd /s /q .\\WorkPath\\Encrypt\\OutputFile\\");
	   system("@Rd /s /q .\\WorkPath\\Encrypt\\InputFile\\");
	   system("@Rd /s /q .\\WorkPath\\Encrypt\\");
	   
	   system("@Rd /s /q .\\WorkPath\\Decrypt\\OutputFile\\");
	   system("@Rd /s /q .\\WorkPath\\Decrypt\\InputFile\\");
	   system("@Rd /s /q .\\WorkPath\\Decrypt\\");
	   system("@Rd /s /q .\\WorkPath\\");
	   
       system("cls");
       
	   goto ProgramMainMenu;

    }
    if(Clear_Workspace == "N","n")
    {
       goto ProgramMainMenu;
    }
    else
    {
        if(Clear_Workspace != "Y","N","y","n")
        {
          goto Clear_Workspace_Restart;
        }
    }


  }
  if(Load_User_Keyboard_Input == "5")
  {
  	return 0;
  }
  else
  {
      if(Load_User_Keyboard_Input != "1","2","3","4")
      {
        ConsoleTableColorSet(0,0,0);
        std :: cout << "User Keyboard Input Error !" << endl;
        getchar();
        exit(1);
      }
  }
}

#include "Main_3_By_Twlilght_Yujiang.hpp"