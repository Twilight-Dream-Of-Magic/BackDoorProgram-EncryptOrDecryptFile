/****************************************************************************
Read Me - About This Source Code File

Chinese����:
�������������: C++
�����ļ���: File_Lock
����ƽ̨����: Windows �����п���̨
����ʵ������: �ļ��Գ�ʽ���ܽ���
�汾: Beta 3.1
Դ�����޸�ʱ��: 2018-6-20
����: Twilight-Dream-Of-Magic

EnglishӢ��:
Computer Language Type: C ++
Program File Name: File_Lock
Program Platform Type: Windows Command Line Console
The actual role of the program: file symmetric encryption and decryption
Version: Beta 3.1
Source code modified by: 2018-6-20
Author: Twilight-Dream-Of-Magic
*****************************************************************************/

#include <iostream>
#include <fstream>
#include <io.h>
#include <stdio.h>   //�����C���Ա�׼����������� Computer C language standard input and output functions
#include <stdlib.h>  //�����C���Ա�׼�⺯�� Computer C language standard library functions
#include <string.h>  //�����C�����ַ��������� Computer C language string handling functions
#include <windows.h>
#include "stdafx.h"

//#include <ImageHlp.h> //MakeSureDirectoryPathExists("");
//#pragma comment(lib, "ImageHlp.lib")

using namespace std;

//typedef unsigned char byte;

int RunEncryptFile(const char *E_SourceFileCharPath, char *E_KEY, char *E_KEY2, char *E_KEY3, char *E_KEY4, const char *E_TargetFileCharPath);
int RunDecryptFile(const char *D_SourceFileCharPath, char *D_KEY, char *D_KEY2, char *D_KEY3, char *D_KEY4, const char *D_TargetFileCharPath);

/***��������-��ʼ Declare the code - the beginning***/
//���±���,Ӧ�õ��ļ�������ʱ
//The following variables apply when the file is encrypted
string E_IF_PATH = ".\\WorkPath\\Encrypt\\InputFile\\", //����֮ǰ���ļ���·�� Before encrypting the path of the file
E_OF_PATH = ".\\WorkPath\\Encrypt\\OutputFile\\"; //����֮���ļ���·�� After encrypting the path of the file

string E_SourceFileName,       // Դ�ļ���
E_SourceFileMainName,     // Դ�ļ���Ҫ��
E_SourceFileExtendedName, // Դ�ļ���չ��
E_TargetFileExtendedName; // Ŀ���ļ���չ��

char E_KEY[256], //File (Encryption or Encrypted) key �ļ�������Կ
E_KEY2[256],
E_KEY3[256],
E_KEY4[256];
/***��������-���� Declare the code - end***/

/***��������-��ʼ Declare the code - the beginning***/
//���±���,Ӧ�õ��ļ�������ʱ
//The following variables apply when the file is decrypted
string D_IF_PATH = ".\\WorkPath\\Decrypt\\InputFile\\", //����֮ǰ���ļ���·�� Before decrypting the path of the file
D_OF_PATH = ".\\WorkPath\\Decrypt\\OutputFile\\"; //����֮���ļ���·�� After decrypting the path of the file

string D_SourceFileName,      //Դ�ļ���
D_TargetFileMainName,     //Ŀ���ļ���Ҫ��
D_TargetFileTempName,     //Ŀ���ļ���ʱ�����
D_TargetFileExtendedName; //Ŀ���ļ�Դ��չ��

char D_KEY[256], //File (Decryption or Decrypted) key �ļ�������Կ
D_KEY2[256],
D_KEY3[256],
D_KEY4[256];
/***��������-���� Declare the code - end***/

/****************************************************************************************************************************************************************/

void ConsoleTableColorSet(int R, int G, int B)
{
	if (R < 0) R = 0;
	if (R > 1) R = 1;

	if (G < 0) G = 0;
	if (G > 1) G = 1;

	if (B < 0) B = 0;
	if (B > 1) B = 1;

	if (R == 1 && G == 1 && B == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	else if (R == 1 && G == 1 && B == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	}
	else if (R == 1 && G == 0 && B == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	}
	else if (R == 0 && G == 1 && B == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	else if (R == 1 && G == 0 && B == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	}
	else if (R == 0 && G == 1 && B == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	}
	else if (R == 0 && G == 0 && B == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	}
}

void CleanFileFromThisWorkspace()
{
	DeleteFile(".\\SourceFileName.CONFIGFILE");
	DeleteFile(".\\SourceFileMainName.CONFIGFILE");
	DeleteFile(".\\SourceFileExtendedName.CONFIGFILE");

	system("@Del /s /f /q .\\File-Key-Record-Log\\*.*");
	system("@Del /s /f /q .\\WorkPath\\*.*");

	system("@Del /s /f /q .\\WorkPath\\Encrypt\\*.*");
	system("@Del /s /f /q .\\WorkPath\\Encrypt\\InputFile\\*.*");
	system("@Del /s /f /q .\\WorkPath\\Encrypt\\OutputFile\\*.*");

	system("@Del /s /f /q .\\WorkPath\\Decrypt\\*.*");
	system("@Del /s /f /q .\\WorkPath\\Decrypt\\InputFile\\*.*");
	system("@Del /s /f /q .\\WorkPath\\Decrypt\\OutputFile\\*.*");

	system("@Rmdir /s /q .\\File-Key-Record-Log\\");

	system("@Rmdir /s /q .\\WorkPath\\Encrypt\\OutputFile\\");
	system("@Rmdir /s /q .\\WorkPath\\Encrypt\\InputFile\\");
	system("@Rmdir /s /q .\\WorkPath\\Encrypt\\");

	system("@Rmdir /s /q .\\WorkPath\\Decrypt\\OutputFile\\");
	system("@Rmdir /s /q .\\WorkPath\\Decrypt\\InputFile\\");
	system("@Rmdir /s /q .\\WorkPath\\Decrypt\\");
	system("@Rmdir /s /q .\\WorkPath\\");

	system("cls");
}

int main()
{
 ProgramMainMenu:

	string Load_User_Keyboard_Input;

	system("color 0A");
	system("cls");

	std::cout << "----------------------------------------" << endl;
	std::cout << "Enter 1 Encrypt File" << endl;
	std::cout << "1.�����ļ�\n" << endl;
	std::cout << "Enter 2 Decrypt File" << endl;
	std::cout << "2.�����ļ�\n" << endl;
	std::cout << "Enter 3 Use The Information Manual" << endl;
	std::cout << "3.ʹ����Ϣ˵���ֲ�\n" << endl;
	std::cout << "Enter 4 Clean Up The Workspace[To Restore The Initial State]" << endl;
	std::cout << "4.�������ռ�[�ָ���ʼ״̬]\n" << endl;
	std::cout << "Enter 5 Exit Program" << endl;
	std::cout << "5.�˳�����\n" << endl;
	std::cout << "----------------------------------------" << endl;
	std::cout << "System:Input And Output/Enter>";

	std::cin >> Load_User_Keyboard_Input;
	getchar();

/****************************************************************************************************************************************************************/

	if (Load_User_Keyboard_Input == "1")
	{
		if (!access(".\\WorkPath\\Encrypt\\InputFile\\", 0))
		{
			std::cout << "Building and Loading Folder 20%" << endl;
		}
		else
		{
			system("@Mkdir .\\WorkPath\\Encrypt\\InputFile\\");
		}

		if (!access(".\\WorkPath\\Encrypt\\OutputFile\\", 0))
		{
			std::cout << "Building and Loading Folder 40%" << endl;
		}
		else
		{
			system("@Mkdir .\\WorkPath\\Encrypt\\OutputFile\\");
		}

		if (!access(".\\WorkPath\\Decrypt\\InputFile\\", 0))
		{
			std::cout << "Building and Loading Folder 60%" << endl;
		}
		else
		{
			system("@Mkdir .\\WorkPath\\Decrypt\\InputFile\\");
		}

		if (!access(".\\WorkPath\\Decrypt\\OutputFile\\", 0))
		{
			std::cout << "Building and Loading Folder 80%" << endl;
		}
		else
		{
			system("@Mkdir .\\WorkPath\\Decrypt\\OutputFile\\");
		}

		if (!access(".\\File-Key-Record-Log\\", 0))
		{
			std::cout << "Building and Loading Folder 100%" << endl;
		}
		else
		{
			system("@Mkdir .\\File-Key-Record-Log\\");
		}

		system("cls");
		system("color 1A");

		ConsoleTableColorSet(0, 0, 0);
		std::cout << "Please input >>> the source file name + file extension name.\nDo not enter spaces!\n:" << endl;
		std::cout << "����Ҫ���ܵ��ļ���+�ļ���չ������Ҫ����ո�!" << endl;
		std::cin >> E_SourceFileName;

		std::cout << "Please input >>> the source file name, not the file extension name!\nDo not enter spaces!\n:" << endl;
		std::cout << "����Ҫ���ܵ��ļ���Ҫ���������ļ���չ������Ҫ����ո�!" << endl;
		std::cin >> E_SourceFileMainName;

		std::cout << "Please input >>> the file extension name.\nDo not enter spaces!\n:" << endl;
		std::cout << "����Ҫ���ܵ��ļ���չ������Ҫ����ո�!" << endl;
		std::cin >> E_SourceFileExtendedName;
		system("cls");

		std::cout << "���ڼ�¼��������Դ�ļ�����......\n[����!]�ڽ��б��β��������´�ѡ��ͬ�����Ƶļ����ļ������н����ļ�����!\n��������֮ǰ����������ֹʹ�ü����ļ����ܣ�" << endl;
		std::cout << "Recording and exporting, source file name......\n[Warning!]After doing this operation, please select the same name next time the encrypted file, decrypt the file operation!\nOtherwise, before that, please immediately disable the use of encrypted file function" << endl;
		std::cout << "���Ƿ�������Э��?[����Enter����] ���� [�رճ���]......" << endl;
		std::cout << "Whether you accept this agreement?[Keyboard Enter Continue] Or [Close this program]......" << endl;

		system("pause");
		system("cls");

		ofstream SourceFileNameTemporarySave;

		SourceFileNameTemporarySave.open(".\\SourceFileName.CONFIGFILE");
		SourceFileNameTemporarySave << E_SourceFileName << endl;
		SourceFileNameTemporarySave.close();

		SourceFileNameTemporarySave.open(".\\SourceFileMainName.CONFIGFILE");
		SourceFileNameTemporarySave << E_SourceFileMainName << endl;
		SourceFileNameTemporarySave.close();

		SourceFileNameTemporarySave.open(".\\SourceFileExtendedName.CONFIGFILE");
		SourceFileNameTemporarySave << E_SourceFileExtendedName << endl;
		SourceFileNameTemporarySave.close();

		//������Կ�����û��Լ�����ģ�(����С��256)����������ĸ�һ����Ҫ���ܵ��ļ����һ������������Կ��
		//Encryption key code is user-defined, (length less than 256). You can optionally add one or more encryption keys to the one files you want to encrypt
	E_KEY_LENTH_IS_INCORRECT:
		int E_KEY_CODE_MAX_LENGTH = 256;

		ConsoleTableColorSet(0, 0, 1);
		std::cout << "\n";
		std::cout << "����(����С��256)��Կ,��Ҫ����ո�!" << endl;
		std::cout << "Please input >>> the key,Do not enter spaces!\n(length less than 256):" << endl;
		std::cin >> E_KEY;
		if(strlen(E_KEY) > E_KEY_CODE_MAX_LENGTH)
		{
		    memset(E_KEY,NULL,sizeof(E_KEY)); //Reset This Variable The Value (NULL = 0)
			std :: cout << "������Կ�ĳ��ȣ��Ѿ�����256λ�ַ��� �������������м�����Կ��" << endl;
			std :: cout << "Encryption key length, has more than 256 characters. Please re-enter the all encryption key!" << endl;
			system("pause");
			goto E_KEY_LENTH_IS_INCORRECT;
		}

		ConsoleTableColorSet(0, 1, 0);
		std::cout << "\n";
		std::cout << "����(����С��256)��Կ2,��Ҫ����ո�!" << endl;
		std::cout << "Please input >>> the key2,Do not enter spaces!\n(length less than 256):" << endl;
		std::cin >> E_KEY2;
		if(strlen(E_KEY2) > E_KEY_CODE_MAX_LENGTH)
		{
		    memset(E_KEY2,NULL,sizeof(E_KEY2)); //Reset This Variable The Value (NULL = 0)
			std :: cout << "������Կ2�ĳ��ȣ��Ѿ�����256λ�ַ��� �������������м�����Կ��" << endl;
			std :: cout << "Encryption key2 length, has more than 256 characters. Please re-enter the all encryption key!" << endl;
			system("pause");
			goto E_KEY_LENTH_IS_INCORRECT;
		}

		ConsoleTableColorSet(0, 1, 1);
		std::cout << "\n";
		std::cout << "����(����С��256)��Կ3,��Ҫ����ո�!" << endl;
		std::cout << "Please input >>> the key3,Do not enter spaces!\n(length less than 256):" << endl;
		std::cin >> E_KEY3;
		if(strlen(E_KEY3) > E_KEY_CODE_MAX_LENGTH)
		{
		    memset(E_KEY3,NULL,sizeof(E_KEY3)); //Reset This Variable The Value (NULL = 0)
			std :: cout << "������Կ3�ĳ��ȣ��Ѿ�����256λ�ַ��� �������������м�����Կ��" << endl;
			std :: cout << "Encryption key3 length, has more than 256 characters. Please re-enter the all encryption key!" << endl;
			system("pause");
			goto E_KEY_LENTH_IS_INCORRECT;
		}

		ConsoleTableColorSet(1, 0, 0);
		std::cout << "\n";
		std::cout << "����(����С��256)��Կ4,��Ҫ����ո�!" << endl;
		std::cout << "Please input >>> the key3,Do not enter spaces!\n(length less than 256):" << endl;
		std::cin >> E_KEY4;
		if(strlen(E_KEY4) > E_KEY_CODE_MAX_LENGTH)
		{
		    memset(E_KEY4,NULL,sizeof(E_KEY4)); //Reset This Variable The Value (NULL = 0)
			std :: cout << "������Կ4�ĳ��ȣ��Ѿ�����256λ�ַ��� �������������м�����Կ��" << endl;
			std :: cout << "Encryption key4 length, has more than 256 characters. Please re-enter the all encryption key!" << endl;
			system("pause");
			goto E_KEY_LENTH_IS_INCORRECT;
		}

		ConsoleTableColorSet(1, 0, 1);
		std::cout << "\n";
		std::cout << "Please output >>> file extension name.\nDo not enter spaces!\n[.TSMY-ENCRYPTED]:" << endl;
		std::cout << "����ļ���չ��,��Ҫ����ո�[.TSMY-ENCRYPTED]��" << endl; //�����ܺ���ļ�����ļ���չ���������� Export the file extension to the encrypted file and save it
		std::cin >> E_TargetFileExtendedName;
		if (E_TargetFileExtendedName == " ")
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

		ConsoleTableColorSet(1, 1, 0);
		std::cout << "���ڼ�¼�����������������ļ����ܣ�4����Կ�ַ���......" << endl;
		std::cout << "Is being recorded and exported, this time for file encryption, 4 key string......" << endl;

		ofstream KeyStringSaveToFile;

		KeyStringSaveToFile.open(".\\File-Key-Record-Log\\ENCRYPTION-DECRYPTIPN-PASSWORD.KEY.TXT");

		KeyStringSaveToFile << "Twlilght_Yujiang File Lock Password [Key String] Save\n" << endl;
		KeyStringSaveToFile << "\n" << endl;
		KeyStringSaveToFile << "Source Input File Name and Path: " << E_SourceFileStringPath << "\n" << endl;
		KeyStringSaveToFile << "EncryptFile: New Output Target File Name and Path: " << E_TargetFileStringPath << "\n" << endl;
		KeyStringSaveToFile << "Key string1 [Password1]: " << E_KEY << "\n" << endl;
		KeyStringSaveToFile << "Key string2 [Password2]: " << E_KEY2 << "\n" << endl;
		KeyStringSaveToFile << "Key string3 [Password3]: " << E_KEY3 << "\n" << endl;
		KeyStringSaveToFile << "Key string4 [Password4]: " << E_KEY4 << "\n" << endl;
		KeyStringSaveToFile << "<******************************************************************************************>" << "\n" << endl;

		KeyStringSaveToFile.close();

		ConsoleTableColorSet(1, 1, 1);
		std::cout << "Please wait, read and write in the file......" << endl;
		std::cout << "��ȴ����ļ���д��......" << endl;
		getchar();

		if (RunEncryptFile(E_SourceFileCharPath, E_KEY, E_KEY2, E_KEY3, E_KEY4, E_TargetFileCharPath))
		{
			printf("��ϲ�㣬�ļ�[%s]���ܳɹ���������[%s]��\n", E_SourceFileCharPath, E_TargetFileCharPath);
			printf("Congratulations, the file [%s] is encrypted successfully, saved in [%s]. \n", E_SourceFileCharPath, E_TargetFileCharPath);
			getchar();
			system("pause");
			system("cls");
			goto ProgramMainMenu;
		}
	}

/****************************************************************************************************************************************************************/

	if (Load_User_Keyboard_Input == "2")
	{
		if (!access(".\\WorkPath\\Encrypt\\InputFile\\", 0))
		{
			std::cout << "Building and Loading Folder 20%" << endl;
		}
		else
		{
			system("@Mkdir .\\WorkPath\\Encrypt\\InputFile\\");
		}

		if (!access(".\\WorkPath\\Encrypt\\OutputFile\\", 0))
		{
			std::cout << "Building and Loading Folder 40%" << endl;
		}
		else
		{
			system("@Mkdir .\\WorkPath\\Encrypt\\OutputFile\\");
		}

		if (!access(".\\WorkPath\\Decrypt\\InputFile\\", 0))
		{
			std::cout << "Building and Loading Folder 60%" << endl;
		}
		else
		{
			system("@Mkdir .\\WorkPath\\Decrypt\\InputFile\\");
		}

		if (!access(".\\WorkPath\\Decrypt\\OutputFile\\", 0))
		{
			std::cout << "Building and Loading Folder 80%" << endl;
		}
		else
		{
			system("@Mkdir .\\WorkPath\\Decrypt\\OutputFile\\");
		}

		if (!access(".\\File-Key-Record-Log\\", 0))
		{
			std::cout << "Building and Loading Folder 100%" << endl;
		}
		else
		{
			system("@Mkdir .\\File-Key-Record-Log\\");
		}

		system("cls");
		system("color 1A");

		ConsoleTableColorSet(1, 1, 1);
		std::cout << "Please input >>> the source file name + file extension name.\nDo not enter spaces!\n:" << endl;
		std::cout << "����Ҫ���ܵ��ļ���+�ļ���չ��,��Ҫ����ո�!" << endl;
		std::cin >> D_SourceFileName;

		//������Կ�������û��Լ��ڼ����ļ��������õġ�������壬���Ա�������Կ��Ĳ������Ķ������ļ���˵����������Կ����ڼ�����Կ�룩������Ը�����һ����Ҫ���ܵ��ļ���������ȷ�Ľ�����Կ��
		//The decryption key code is set by the user himself at the encrypted file step. This definition, from the encrypted key code of the operation of the binary file (Description: decryption key code is equal to the encryption key code). You can give a random file to be decrypted and enter the correct decryption key code
	D_KEY_LENTH_IS_INCORRECT:
		int D_KEY_CODE_MAX_LENGTH = 256;

		ConsoleTableColorSet(1, 1, 0);
		std::cout << "\n";
		std::cout << "����(����С��256)��Կ,��Ҫ����ո�!" << endl;
		std::cout << "Please input >>> the key3,Do not enter spaces!\n(length less than 256):" << endl;
		std::cin >> D_KEY;
		if(strlen(D_KEY) > D_KEY_CODE_MAX_LENGTH)
		{
		    memset(D_KEY,NULL,sizeof(D_KEY)); //Reset This Variable The Value (NULL = 0)
			std :: cout << "������Կ�ĳ��ȣ��Ѿ�����256λ�ַ��� �������������н�����Կ��" << endl;
			std :: cout << "Decryption key length, has more than 256 characters. Please re-enter the all decryption key!" << endl;
			system("pause");
			goto D_KEY_LENTH_IS_INCORRECT;
		}

		ConsoleTableColorSet(1, 0, 1);
		std::cout << "\n";
		std::cout << "����(����С��256)��Կ2,��Ҫ����ո�!" << endl;
		std::cout << "Please input >>> the key2,Do not enter spaces!\n(length less than 256):" << endl;
		std::cin >> D_KEY2;
		if(strlen(D_KEY2) > D_KEY_CODE_MAX_LENGTH)
		{
		    memset(D_KEY2,NULL,sizeof(D_KEY2)); //Reset This Variable The Value (NULL = 0)
			std :: cout << "������Կ2�ĳ��ȣ��Ѿ�����256λ�ַ��� �������������н�����Կ��" << endl;
			std :: cout << "Decryption key2 length, has more than 256 characters. Please re-enter the all decryption key!" << endl;
			system("pause");
			goto D_KEY_LENTH_IS_INCORRECT;
		}

		ConsoleTableColorSet(1, 0, 0);
		std::cout << "\n";
		std::cout << "����(����С��256)��Կ3,��Ҫ����ո�!" << endl;
		std::cout << "Please input >>> the key,Do not enter spaces!\n(length less than 256):" << endl;
		std::cin >> D_KEY3;
		if(strlen(D_KEY3) > D_KEY_CODE_MAX_LENGTH)
		{
		    memset(D_KEY3,NULL,sizeof(D_KEY3)); //Reset This Variable The Value (NULL = 0)
			std :: cout << "������Կ3�ĳ��ȣ��Ѿ�����256λ�ַ��� �������������н�����Կ��" << endl;
			std :: cout << "Decryption key3 length, has more than 256 characters. Please re-enter the all decryption key!" << endl;
			system("pause");
			goto D_KEY_LENTH_IS_INCORRECT;
		}

		ConsoleTableColorSet(0, 1, 1);
		std::cout << "\n";
		std::cout << "����(����С��256)��Կ4,��Ҫ����ո�!" << endl;
		std::cout << "Please input >>> the key,Do not enter spaces!\n(length less than 256):" << endl;
		std::cin >> D_KEY4;
		if(strlen(D_KEY4) > D_KEY_CODE_MAX_LENGTH)
		{
		    memset(D_KEY4,NULL,sizeof(D_KEY4)); //Reset This Variable The Value (NULL = 0)
			std :: cout << "������Կ4�ĳ��ȣ��Ѿ�����256λ�ַ��� �������������н�����Կ��" << endl;
			std :: cout << "Decryption key4 length, has more than 256 characters. Please re-enter the all decryption key!" << endl;
			system("pause");
			goto D_KEY_LENTH_IS_INCORRECT;
		}

		system("cls");

		ConsoleTableColorSet(0, 1, 0);

		std::cout << "\n";
		std::cout << "����ڵ�ǰ�ļ����������ļ�[.\\*.CONFIGFILE]�����ڣ�����Ͳ�������Զ��ָ�ԭ�����ļ����ơ�\n����Ҫ���������ļ���!" << endl;
		std::cout << "If the configuration file [.\\*.CONFIGFILE] does not exist in the current folder, the program will not automatically restore the original file name.\nYou need to re-enter the file name!" << endl;
		std::cout << "Please output >>> target file main name,not the file extension name!\nDo not enter spaces!\n[DATA-DECRYPTED]:" << endl;
		std::cout << "����ļ���Ҫ���������ļ���չ������Ҫ����ո�[DATA-TSMY-DECRYPTED]!" << endl; //�����ܺ���ļ������Ҫ�ļ����������� Output the main file name to the decrypted file and save it
		if (!access(".\\SourceFileMainName.CONFIGFILE", 0))
		{
			//char TFMN_Buffer[256];
			ifstream LoadSourceFileNameConfigure(".\\SourceFileMainName.CONFIGFILE", ios::in);
			if (LoadSourceFileNameConfigure.fail())
			{
				std::cout << "���������ļ�ʱ��������δ֪���󲢽���" << endl;
				std::cout << "When the configuration file is loaded, an unknown error has occurred and ends" << endl;
				system("pause");
				return 0;
			}
			while (!LoadSourceFileNameConfigure.eof())
			{
				LoadSourceFileNameConfigure >> D_TargetFileMainName;
				//LoadSourceFileNameConfigure.getline(TFMN_Buffer,256,'\n'); //getline(char *,int,char) ��ʾ�����ַ��ﵽ256�����������оͽ���
				//D_TargetFileMainName = TFMN_Buffer;

				std::cout << "���ѳɹ������˲���" << endl;
				std::cout << "You have successfully skipped this step" << endl;
			}
			LoadSourceFileNameConfigure.close();
		}
		else
		{
			std::cout << "�����ļ�" << ".\\SourceFileMainName.CONFIGFILE" << "δ�ҵ�!\n" << "��������������!" << endl;
			std::cout << "Configuration file" << ".\\SourceFileMainName.CONFIGFILE " << "Not found!\n" << "Please re-enter the name!" << endl;
			HANDLE hFILE = CreateFile(".\\SourceFileMainName.CONFIGFILE", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			std::cin >> D_TargetFileMainName;

		}

		system("cls");

		std::cout << "����ڵ�ǰ�ļ����������ļ�[.\\*.CONFIGFILE]�����ڣ�����Ͳ�������Զ��ָ�ԭ�����ļ����ơ�\n����Ҫ���������ļ���!" << endl;
		std::cout << "If the configuration file [.\\*.CONFIGFILE] does not exist in the current folder, the program will not automatically restore the original file name.\nYou need to re-enter the file name!" << endl;
		std::cout << "Please output >>> target file extension name!\nDo not enter spaces!\n[Example: .txt]:" << endl;
		std::cout << "����ļ���չ������Ҫ����ո�[ʵ���� .txt]!" << endl; //�����ܺ���ļ�����ļ���չ����������
		if (!access(".\\SourceFileExtendedName.CONFIGFILE", 0))
		{
			ifstream LoadSourceFileNameConfigure(".\\SourceFileExtendedName.CONFIGFILE", ios::in);
			//char TFEN_Buffer[256];
			if (LoadSourceFileNameConfigure.fail())
			{
				std::cout << "���������ļ�ʱ��������δ֪���󲢽���" << endl;
				std::cout << "When the configuration file is loaded, an unknown error has occurred and ends" << endl;
				system("pause");
				return 0;
			}
			while (!LoadSourceFileNameConfigure.eof())
			{
				LoadSourceFileNameConfigure >> D_TargetFileExtendedName;
				//LoadSourceFileNameConfigure.getline(TFEN_Buffer,256,'\n'); //getline(char *,int,char) ��ʾ�����ַ��ﵽ256�����������оͽ���
				//D_TargetFileExtendedName = TFEN_Buffer;

				std::cout << "���ѳɹ������˲���" << endl;
				std::cout << "You have successfully skipped this step" << endl;
			}
			LoadSourceFileNameConfigure.close();
		}
		else
		{
			std::cout << "�����ļ�" << ".\\SourceFileExtendedName.CONFIGFILE" << "δ�ҵ�!\n" << "��������������!" << endl;
			std::cout << "Configuration file" << ".\\SourceFileExtendedName.CONFIGFILE " << "Not found!\n" << "Please re-enter the name!" << endl;
			HANDLE hFILE = CreateFile(".\\SourceFileExtendedName.CONFIGFILE", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			std::cin >> D_TargetFileExtendedName;
		}

		system("cls");

		std::cout << "\n";
		std::cout << "����ڵ�ǰ�ļ����������ļ�[.\\*.CONFIGFILE]�����ڣ�����Ͳ�������Զ��ָ�ԭ�����ļ����ơ�\n����Ҫ���������ļ���!" << endl;
		std::cout << "If the configuration file [.\\*.CONFIGFILE] does not exist in the current folder, the program will not automatically restore the original file name.\nYou need to re-enter the file name!" << endl;
		std::cout << "Please output >>> target file temporary add name.\nDo not enter spaces!\n[-DECRYPTED]:" << endl;
		std::cout << "����ļ���ʱ���������Ҫ����ո�[-TSMY-DECRYPTED]!" << endl; //�����ܺ���ļ�����ļ���ʱ�������������
		std::cout << "Prevent source encrypted files from being overwritten" << endl;
		std::cout << "��ֹԴ�����ļ�������" << endl;
		std::cin >> D_TargetFileTempName;
		if (D_TargetFileTempName == " ")
		{
			string D_TargetFileAddName = "-TSMY-DECRYPTED";
			D_TargetFileTempName = D_TargetFileAddName;
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

		ConsoleTableColorSet(0, 0, 1);
		std::cout << "Please wait, read and write in the file......" << endl;
		std::cout << "��ȴ����ļ���д��......" << endl;
		getchar();

		if (RunDecryptFile(D_SourceFileCharPath, D_KEY, D_KEY2, D_KEY3, D_KEY4, D_TargetFileCharPath))
		{
			printf("��ϲ�㣬�ļ�[%s]���ܳɹ���������[%s]��\n", D_SourceFileCharPath, D_TargetFileCharPath);
			printf("Congratulations, the file [%s] is decrypted successfully, saved in [%s]. \n", D_SourceFileCharPath, D_TargetFileCharPath);
			getchar();
			system("pause");
			system("cls");
			goto ProgramMainMenu;
		}
	}

/****************************************************************************************************************************************************************/

	if (Load_User_Keyboard_Input == "3")
	{
	 Instruction_Manual_Language_Restart:
	  system("cls");
	    system("color 1A");
		std::cout << "��ӭ��ĵ��������Ǳ������˵���ֲ�[Beta Version 3.1]���������ʹ��ǰ����ϸ�Ķ�" << endl;
		std::cout << "Welcome to your arrival! This is the instruction manual [Beta Version 3.1] of this program, please be sure to read carefully before using it" << endl;
		std::cout << "" << endl;
		std::cout << "enUS----------English Ӣ��" << endl;
		std::cout << "zhCN----------Chinese ����" << endl;
		std::cout << "MENU----------Back Main Menu �������˵�" << endl;
		std::cout << "" << endl;
		std::cout << "Manual:\\Program\\Keyboard_Input> ";
		string Instruction_Manual_Language;
		std::cin >> Instruction_Manual_Language;
		if (Instruction_Manual_Language == "enUS")
		{
			system("cls");
			system("color 67");
			std::cout << "Manual:\\Program\\Keyboard_Output> " << endl;
			std::cout << "" << endl;
			std::cout << "When the program executes the function of encrypting the file or decrypting the file, it will create the workspace folder, input the folder, output the folder.\n" << endl;
			std::cout << "When the program encrypts the file or decrypts the file and waits, the program is reading and writing the file in the background.\nNever close the program at this time! Otherwise your data is damaged and bear the consequences.\nIt is recommended that you after the data backup, use this program to encrypt the file or decrypt the file!\n" << endl;
			system("pause");
			system("cls");
		}
		if (Instruction_Manual_Language == "zhCN")
		{
			system("cls");
			system("color 17");
			std::cout << "Manual:\\Program\\Keyboard_Output> " << endl;
			std::cout << "" << endl;
			std::cout << "������ִ�м����ļ�������ļ��Ĺ���ʱ�������������ռ��ļ��У������ļ��У�����ļ��С�\n" << endl;
			std::cout << "����������ļ�������ļ����ҵȴ�ʱ���������ں�̨��ȡ��д���ļ������ʱ����Զ��Ҫ�ر��������\n�����������ݱ��𻵲��е�������������ڽ������ݱ���֮���������������ļ�������ļ���\n" << endl;
			system("pause");
			system("cls");

		}
		if (Instruction_Manual_Language == "MENU","menu")
		{
			system("cls");
			goto ProgramMainMenu;
		}
		else
		{
			if (Instruction_Manual_Language != "enUS", "zhCN")
			{
				ConsoleTableColorSet(0, 0, 0);
				goto Instruction_Manual_Language_Restart;
			}
		}

	}

/****************************************************************************************************************************************************************/

	if (Load_User_Keyboard_Input == "4")
	{
	Waring_Information:
		string You_understand;
		system("color 0C");
		std::cout << "[����!]�������еĲ�������ѡ�� <File-Key-Record-Log> �� <WorkPath> �ļ��У�Ȼ�����õ�ɾ����������!\n" << endl;
		std::cout << "����Դ�ļ������ɵļ����ļ������ɵĽ����ļ���������־������\n" << endl;
		std::cout << "�����֪�����գ��밴���� [Y������ N������]\n[ Yes / No ]" << endl;

		std::cout << "[Warning!] The upcoming operation will select the <File-Key-Record-Log>and <WorkPath folders>, and then permanently delete all the data!\n" << endl;
		std::cout << "Including source files, generated encrypted files, generated decrypted files, password logs, configuration\n" << endl;
		std::cout << "If you know the risk, press the keypad [Y key to continue N key to return]\n[Yes / No]" << endl;
		std::cin >> You_understand; //���˽���գ� You understand the risks?


		if (You_understand == "N")
		{
			goto ProgramMainMenu;
		}
		if (You_understand == "n")
		{
			goto ProgramMainMenu;
		}
		if (You_understand== "Y")
		{
			CleanFileFromThisWorkspace();

			goto ProgramMainMenu;
		}
		if (You_understand == "y")
		{
			CleanFileFromThisWorkspace();

			goto ProgramMainMenu;
		}
		else
		{
			goto Waring_Information;
		}
	}

/****************************************************************************************************************************************************************/

	if (Load_User_Keyboard_Input == "5")
	{
		return 0;
	}
	else
	{
		if (Load_User_Keyboard_Input != "1", "2", "3", "4")
		{
			ConsoleTableColorSet(0, 0, 0);
			std::cout << "User Keyboard Input Error !" << endl;
			getchar();
			exit(1);
		}
	}
}

#include "EODF3-1_By_TDOM.hpp"
