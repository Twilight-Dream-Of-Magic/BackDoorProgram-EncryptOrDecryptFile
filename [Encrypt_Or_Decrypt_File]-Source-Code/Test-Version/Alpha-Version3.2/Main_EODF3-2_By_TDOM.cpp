/****************************************************************************
Read Me - About This Source Code File

Chinese����:
�������������: C++
�����ļ���: File_Lock
����ƽ̨����: Windows �����п���̨
����ʵ������: �Գ�ʽ���ܺͶԳ�ʽ�������ļ�
�汾: Alpha 3.2
Դ�����޸�ʱ��: 2018-8-08
����: Twilight-Dream-Of-Magic

EnglishӢ��:
Computer Language Type: C ++
Program File Name: File_Lock
Program Platform Type: Windows Command Line Console
The actual role of the program: symmetric encryption and decryption to file
Version: Alpha 3.2
Source code modified by: 2018-8-08
Author: Twilight-Dream-Of-Magic
*****************************************************************************/

#include "EODF3-2_By_TDOM.hpp"

//Variable argc is Argument counter
//Variable argv is Argument vector

int main (int argc, char *argv[])
{   
  string ShowLanguage;

  if (argc == 3 && strcmp(argv[1],"-help") == 0 || argc == 2 && strcmp(argv[1],"--display-help") == 0)
  {
    if(strcmp(argv[2],"") == 0 || strcmp(argv[2]," ") == 0)
    {
      cout << "" << endl;
      cout << "Error: Language for command help manual not set !" << endl;
      cout << "����δ������������ֲ������ !" << endl;
      cout << "" << endl;
      return 0;
    }
    if(strcmp(argv[2],"?") == 0)
    {
      cout << "" << endl;
      cout << "==============================" << endl;
      cout << "+ Help manual language list  +" << endl;
      cout << "==============================" << endl;
      cout << "+  en-US = American English  +" << endl;
      cout << "+ zh-CN = Simplified Chinese +" << endl;
      cout << "==============================" << endl;
      cout << "" << endl;
      return 0;
    }
    if(strcmp(argv[2],"en-US") == 0)
    {
      ShowLanguage = argv[2];
      DisplayHelpManual(ShowLanguage);
    }
    if(strcmp(argv[2],"zh-CN") == 0)
    {
      ShowLanguage = argv[2];
      DisplayHelpManual(ShowLanguage);
    }
  }
  if (argc == 2 && strcmp(argv[1],"-cui") == 0 || argc == 3 && strcmp(argv[1],"--user-interface") == 0 && strcmp(argv[2],"command") == 0)
  {
    CTUI();
  }
  if (argc == 2 && strcmp(argv[1],"-gui") == 0 || argc == 3 && strcmp(argv[1],"--user-interface") == 0 && strcmp(argv[2],"graphical") == 0)
  {
    GWUI();
  }
  if (argc == 14 && strcmp(argv[1],"-e") == 0 && strcmp(argv[2],"-sf") == 0 && strcmp(argv[4],"-k") == 0 && strcmp(argv[6],"-k2") == 0 && strcmp(argv[8],"-k3") == 0 && strcmp(argv[10],"-k4") == 0 && strcmp(argv[12],"-tf") == 0)
  {
    CallCustomEncryptToFile(argv[3],argv[5],argv[7],argv[9],argv[11],argv[13]);
  }
  if (argc == 14 && strcmp(argv[1],"--encrypt") == 0 && strcmp(argv[2],"--source-file") == 0 && strcmp(argv[4],"--key") == 0 && strcmp(argv[6],"--key2") == 0 && strcmp(argv[8],"--key3") == 0 && strcmp(argv[10],"--key4") == 0 && strcmp(argv[12],"--target-file") == 0)
  {
    CallCustomEncryptToFile(argv[3],argv[5],argv[7],argv[9],argv[11],argv[13]);
  }
  if (argc == 14 && strcmp(argv[1],"-d") == 0 && strcmp(argv[2],"-sf") == 0 && strcmp(argv[4],"-k") == 0 && strcmp(argv[6],"-k2") == 0 && strcmp(argv[8],"-k3") == 0 && strcmp(argv[10],"-k4") == 0 && strcmp(argv[12],"-tf") == 0)
  {
     CallCustomDecryptToFile(argv[3],argv[5],argv[7],argv[9],argv[11],argv[13]);
  }
  if (argc == 14 && strcmp(argv[1],"--decrypt") == 0 && strcmp(argv[2],"--source-file") == 0 && strcmp(argv[4],"--key") == 0 && strcmp(argv[6],"--key2") == 0 && strcmp(argv[8],"--key3") == 0 && strcmp(argv[10],"--key4") == 0 && strcmp(argv[12],"--target-file") == 0)
  {
     CallCustomDecryptToFile(argv[3],argv[5],argv[7],argv[9],argv[11],argv[13]);
  }
  else if (argc == 1)
  {
    cout << "" << endl;
    cout << "Your method of using this program is incorrect, please use the" << " -help " << "command to view the manual." << endl;
    cout << "Since the use of this [-help] command parameter requires the next command parameter to set the display language, use [-help ?] to check the supported language." << endl;
    cout << "" << endl;
    cout << "���ʹ�ñ�����ķ�������ȷ����ʹ��" << " -help " << "����������鿴�ֲᡣ" << endl;
    cout << "���[-help] ���������ʹ�÷�������Ϊ��Ҫ��һ�����������������ʾ���ԣ�����ʹ��[-help ?]�������֧�ֵ����ԡ�" << endl;
    cout << "" << endl;
    system("Pause");
    return 0;
  }
  return 0;
}