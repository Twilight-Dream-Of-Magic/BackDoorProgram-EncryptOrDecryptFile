/****************************************************************************
Read Me - About This Source Code File

Chinese����:
�������������: C++
�����ļ���: Twlilght_Yujiang_File_Lock
����ƽ̨����: Windows �����п���̨
����ʵ������: �ļ��Գ�ʽ���ܽ���
�汾: Debugging 1.0
Դ�����޸�ʱ��: 2017-8-11
����:Twlilght_Yujiang

EnglishӢ��:
Chinese
Computer Language Type: C++
Program File Name: Twlilght_Yujiang_File_Lock
Program Platform Type: Windows Command Line Console
The actual role of the program: file symmetric encryption and decryption
Version: Debugging 1.0
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

int RunEncryptFile(char *E_SFN, char *E_KEY, char *E_KEY2, char *E_KEY3, char *E_TFN);
int RunDecryptFile(char *D_STN, char *D_KEY, char *D_KEY2, char *D_KEY3, char *D_TFN);

void DOSColorSet(int R,int G,int B)
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

       string E_SourceFileName,    // ���ܵ��ļ���
              E_TargetFileNewName; // ���ܺ�Ҫ������ļ���

       char* E_SFN;
       char* E_TFN;

      //char E_TargetFileLastNameOutput = (E_TargetFileNewName + ".TY_ENCRYPTED"); //��󱣴�ļ��ܺ��ļ���

        char E_KEY[128], //File (Encryption or Encrypted) key �ļ�������Կ
             E_KEY2[128],
             E_KEY3[128];

         std :: cout << "Please input >>> the source file name.\n(Contains the directory name):" << endl;
         std :: cout << "����Ҫ���ܵ��ļ���,[C:\](��·��)��" << endl;
         std :: cin >> E_SourceFileName;
         int String_Length = E_SourceFileName.length();
         E_SFN = (char *)malloc((String_Length+1)*sizeof(char));
         E_SourceFileName.copy(E_SFN,String_Length,0);

          std :: cout << "\n";
          std :: cout << "����(����С��128)��Կ,��Ҫ����ո�" << endl;  //��Կ���û��Լ�����ģ�(����С��128)�������������Ҫ���ܵ��ļ������Կ
          std :: cout << "Please input >>> the key,Do not enter spaces!\n(length less than 128):" << endl;
          std :: cin >> E_KEY;

          std :: cout << "\n";
		  std :: cout << "����(����С��128)��Կ2,��Ҫ����ո�" << endl; //��Կ���û��Լ�����ģ�(����С��128)�������������Ҫ���ܵ��ļ������Կ
          std :: cout << "Please input >>> the key2,Do not enter spaces!\n(length less than 128):" << endl;
          std :: cin >> E_KEY2;

          std :: cout << "\n";
          std :: cout << "����(����С��128)��Կ3,��Ҫ����ո�" << endl; //��Կ���û��Լ�����ģ�(����С��128)�������������Ҫ���ܵ��ļ������Կ
          std :: cout << "Please input >>> the key3,Do not enter spaces!\n(length less than 128):" << endl;
          std :: cin >> E_KEY3;

           std :: cout << "\n";
           std :: cout << "Please input >>> the target file new name(Contains the directory name):" << endl;
           std :: cout << "���ܺ���ļ���(��·��)��" << endl;  //�����ܺ���ļ�������������
           std :: cin >> E_TargetFileNewName;
           int String_Length2 = E_TargetFileNewName.length();
           E_TFN = (char *)malloc((String_Length2+1)*sizeof(char));
           E_TargetFileNewName.copy(E_TFN,String_Length2,0);

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

      if(RunEncryptFile(E_SFN, E_KEY, E_KEY2, E_KEY3, E_TFN))
      {
         printf("��ϲ�㣬�ļ�[%s]���ܳɹ���������[%s]��\n", E_SFN, E_TFN);
         printf("Congratulations, the file [%s] is encrypted successfully, saved in [%s]. \n", E_SFN, E_TFN);
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

   	   string D_SourceFileName,    //Դ�ļ���
              D_TargetFileNewName; //Ŀ���ļ�������

       char* D_SFN;
       char* D_TFN;

       //char D_TargetFileLastNameOutput = (D_TargetFileNewName - ".TY_ENCRYPTED"); //��󱣴�Ľ��ܺ��ļ���

        char D_KEY[128], //File (Decryption or Decrypted) key �ļ�������Կ
             D_KEY2[128],
             D_KEY3[128];

         std :: cout << "\n";
         std :: cout << "Please input >>> the source file name.\nDo not enter spaces!\n(Contains the directory name):" << endl;
		 std :: cout << "����Ҫ���ܵ��ļ���,[C:\]��Ҫ����ո�(��·��)��" << endl;
         std :: cin >> D_SourceFileName;
         int String_Length3 = D_SourceFileName.length();
         D_SFN = (char *)malloc((String_Length3+1)*sizeof(char));
         D_SourceFileName.copy(D_SFN,String_Length3,0);

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
		   std :: cout << "Please input >>> the target file new name(Contains the directory name):" << endl;
           std :: cout << "���ܺ���ļ���,��Ҫ����ո�(��·��)��" << endl;  //�����ܺ���ļ�������������
           std :: cin >> D_TargetFileNewName;
           int String_Length4 = D_TargetFileNewName.length();
           D_TFN = (char *)malloc((String_Length4+1)*sizeof(char));
           D_TargetFileNewName.copy(D_TFN,String_Length4,0);

           system("cls");

		    std :: cout << "Please wait, read and write in the file......" << endl;
	        std :: cout << "��ȴ����ļ���д��......" << endl;
		    getchar();

       if(RunDecryptFile(D_SFN, D_KEY, D_KEY2, D_KEY3, D_TFN))
       {
          printf("��ϲ�㣬�ļ�[%s]���ܳɹ���������[%s]��\n", D_SFN, D_TFN);
          printf("Congratulations, the file [%s] is decrypted successfully, saved in [%s]. \n", D_SFN, D_TFN);
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

	/*******************************************
    *                 �����ļ�
    *
    * E_SourceFileName    Ҫ���ܵ��ļ���
    * E_KEY               ��Կ
    * E_TargetFileNewName ���ܺ�Ҫ������ļ���
    *
    * @return  ���ܳɹ���ʧ�ܵ����ֱ�ʾ
    *
	* 0 = ����ʧ��
    * 1 = ���ܳɹ�
    ********************************************/

		int RunEncryptFile(char* E_SFN, char *E_KEY, char *E_KEY2, char *E_KEY3, char* E_TFN)
		{
            FILE *FilePointerSource, *FilePointerTarget; //Ҫ�򿪵��ļ���ָ��
            char buffer[1024];               //�����������ڴ�Ŵ��ļ���ȡ������

		    int FileByteData,                //ÿ�δ��ļ��ж�ȡ���ֽ���
                RTNOC,                       //ѭ������
                KeyLength = strlen(E_KEY),   //��Կ�ĳ���
                KeyLength2 = strlen(E_KEY2),
                KeyLength3 = strlen(E_KEY3);

             FilePointerSource = fopen(E_SFN, "rb"); //�Զ����Ʒ�ʽ��ȡ�ļ�
             if(FilePointerSource == NULL)
		     {
	     	   printf("File[%s]failed to open, please check whether the file path and name are entered correctly! \n", E_SFN);
               printf("�ļ�[%s]��ʧ�ܣ������ļ�·���������Ƿ�������ȷ��\n", E_SFN);
			   getchar();
               return 0;
             }

		     FilePointerTarget = fopen(E_TFN, "wb"); //�Զ����Ʒ�ʽд���ļ�
             if(FilePointerTarget == NULL)
             {
           	   printf("File[%s]creation/write failed! Please check whether the file path and name are entered correctly!\n", FilePointerTarget);
               printf("�ļ�[%s]����/д��ʧ�ܣ������ļ�·���������Ƿ�������ȷ��\n", FilePointerTarget);
			   getchar();
               return 0;
             }

/*�����㷨��ʼ*/
//���������������ͼ���ģ��
//Run three large encryption modules in turn

//�ļ�����Կ�ڻ������м���
//The file and key are counted in Buffer

            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
                 {
                 buffer[RTNOC] ^= E_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���е�������
                 {
                 buffer[RTNOC] += E_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݳ�����
                 {
                 buffer[RTNOC] *= E_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

//�ļ�����Կ2�ڻ������м���
//The file and key2 are counted in Buffer

            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY2�����������
                 {
                 buffer[RTNOC] ^= E_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY2���е�������
                 {
                 buffer[RTNOC] += E_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY2���еݳ�����
                 {
                 buffer[RTNOC] *= E_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

//�ļ�����Կ3�ڻ������м���
//The file and key3 are counted in Buffer

            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY3�����������
                 {
                 buffer[RTNOC] ^= E_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY3���е�������
                 {
                 buffer[RTNOC] += E_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY3���еݳ�����
                 {
                 buffer[RTNOC] *= E_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

/***********************************************************************************************************************************************************/

//�ļ�����Կ�ڻ������м���
//The file and key are counted in Buffer

            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
                 {
                 buffer[RTNOC] ^= E_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���е�������
                 {
                 buffer[RTNOC] += E_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݳ�����
                 {
                 buffer[RTNOC] *= E_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

//�ļ�����Կ2�ڻ������м���
//The file and key2 are counted in Buffer

            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY2�����������
                 {
                 buffer[RTNOC] ^= E_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY2���е�������
                 {
                 buffer[RTNOC] += E_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY2���еݳ�����
                 {
                 buffer[RTNOC] *= E_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

//�ļ�����Կ3�ڻ������м���
//The file and key3 are counted in Buffer

            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY3�����������
                 {
                 buffer[RTNOC] ^= E_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY3���е�������
                 {
                 buffer[RTNOC] += E_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY3���еݳ�����
                 {
                 buffer[RTNOC] *= E_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

/***********************************************************************************************************************************************************/

//�ļ�����Կ�ڻ������м���
//The file and key are counted in Buffer

            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
                 {
                 buffer[RTNOC] ^= E_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���е�������
                 {
                 buffer[RTNOC] += E_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݳ�����
                 {
                 buffer[RTNOC] *= E_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

//�ļ�����Կ2�ڻ������м���
//The file and key2 are counted in Buffer

            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY2�����������
                 {
                 buffer[RTNOC] ^= E_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY2���е�������
                 {
                 buffer[RTNOC] += E_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY2���еݳ�����
                 {
                 buffer[RTNOC] *= E_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

//�ļ�����Կ3�ڻ������м���
//The file and key3 are counted in Buffer

            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY3�����������
                 {
                 buffer[RTNOC] ^= E_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY3���е�������
                 {
                 buffer[RTNOC] += E_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY3���еݳ�����
                 {
                 buffer[RTNOC] *= E_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

/*�����㷨����*/

		  fclose(FilePointerSource);
          fclose(FilePointerTarget);

          DeleteFile(E_SFN);

		return 1;
        }

        int RunDecryptFile(char* D_SFN, char *D_KEY, char *D_KEY2, char *D_KEY3, char* D_TFN)
		{
            FILE *FilePointerSource, *FilePointerTarget; //Ҫ�򿪵��ļ���ָ��
            char buffer[1024];               //�����������ڴ�Ŵ��ļ���ȡ������

		    int FileByteData,                //ÿ�δ��ļ��ж�ȡ���ֽ���
                RTNOC,                       //ѭ������
                KeyLength = strlen(D_KEY),   //��Կ�ĳ���
                KeyLength2 = strlen(D_KEY2),
                KeyLength3 = strlen(D_KEY3);

             FilePointerSource = fopen(D_SFN, "rb"); //�Զ����Ʒ�ʽ��ȡ�ļ�
             if(FilePointerSource == NULL)
		     {
	     	   printf("File[%s]failed to open, please check whether the file path and name are entered correctly! \n", D_SFN);
               printf("�ļ�[%s]��ʧ�ܣ������ļ�·���������Ƿ�������ȷ��\n", D_SFN);
			   getchar();
               return 0;
             }

		     FilePointerTarget = fopen(D_TFN, "wb"); //�Զ����Ʒ�ʽд���ļ�
             if(FilePointerTarget == NULL)
             {
               printf("File[%s]creation/write failed! Please check whether the file path and name are entered correctly!\n", FilePointerTarget);
               printf("�ļ�[%s]����/д��ʧ�ܣ������ļ�·���������Ƿ�������ȷ��\n", FilePointerTarget);
			   getchar();
               return 0;
             }

	/*******************************************
    *                 �����ļ�
    *
    * D_SourceFileName    Ҫ���ܵ��ļ���
    * D_KEY               ��Կ
    * D_TargetFileNewName ���ܺ�Ҫ������ļ���
    *
    * @return  ���ܳɹ���ʧ�ܵ����ֱ�ʾ
    *
	* 0 = ����ʧ��
    * 1 = ���ܳɹ�
    ********************************************/

/*�����㷨��ʼ*/
//�������д�����������ģ��
//Run three large decryption modules in turn

//�ļ�����Կ�ڻ������м���
//The file and key are counted in Buffer

            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY�����������
                 {
                 buffer[RTNOC] ^= D_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY���еݼ�����
                 {
                 buffer[RTNOC] -= D_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY���еݳ�����
                 {
                 buffer[RTNOC] /= D_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

//�ļ�����Կ2�ڻ������м���
//The file and key2 are counted in Buffer

            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY2�����������
                 {
                 buffer[RTNOC] ^= D_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY2���еݼ�����
                 {
                 buffer[RTNOC] -= D_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY2���еݳ�����
                 {
                 buffer[RTNOC] /= D_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

//�ļ�����Կ3�ڻ������м���
//The file and key3 are counted in Buffer

            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY3�����������
                 {
                 buffer[RTNOC] ^= D_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY3���еݼ�����
                 {
                 buffer[RTNOC] -= D_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY3���еݳ�����
                 {
                 buffer[RTNOC] /= D_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

/***********************************************************************************************************************************************************/

//�ļ�����Կ�ڻ������м���
//The file and key are counted in Buffer

            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY�����������
                 {
                 buffer[RTNOC] ^= D_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY���еݼ�����
                 {
                 buffer[RTNOC] -= D_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY���еݳ�����
                 {
                 buffer[RTNOC] /= D_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

//�ļ�����Կ2�ڻ������м���
//The file and key2 are counted in Buffer

            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY2�����������
                 {
                 buffer[RTNOC] ^= D_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY2���еݼ�����
                 {
                 buffer[RTNOC] -= D_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY2���еݳ�����
                 {
                 buffer[RTNOC] /= D_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

//�ļ�����Կ3�ڻ������м���
//The file and key3 are counted in Buffer

            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY3�����������
                 {
                 buffer[RTNOC] ^= D_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY3���еݼ�����
                 {
                 buffer[RTNOC] -= D_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY3���еݳ�����
                 {
                 buffer[RTNOC] /= D_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

/***********************************************************************************************************************************************************/

//�ļ�����Կ�ڻ������м���
//The file and key are counted in Buffer

             while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY�����������
                 {
                 buffer[RTNOC] ^= D_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY���еݼ�����
                 {
                 buffer[RTNOC] -= D_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY���еݳ�����
                 {
                 buffer[RTNOC] /= D_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

//�ļ�����Կ2�ڻ������м���
//The file and key2 are counted in Buffer

            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY2�����������
                 {
                 buffer[RTNOC] ^= D_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY2���еݼ�����
                 {
                 buffer[RTNOC] -= D_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY2���еݳ�����
                 {
                 buffer[RTNOC] /= D_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

//�ļ�����Կ3�ڻ������м���
//The file and key3 are counted in Buffer

            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY3�����������
                 {
                 buffer[RTNOC] ^= D_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY3���еݼ�����
                 {
                 buffer[RTNOC] -= D_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�D_KEY3���еݳ�����
                 {
                 buffer[RTNOC] /= D_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

/*�����㷨����*/

          fclose(FilePointerSource);
          fclose(FilePointerTarget);

		return 1;
        }

//string New_PlainText; //������
//string New_CipherText; //������


