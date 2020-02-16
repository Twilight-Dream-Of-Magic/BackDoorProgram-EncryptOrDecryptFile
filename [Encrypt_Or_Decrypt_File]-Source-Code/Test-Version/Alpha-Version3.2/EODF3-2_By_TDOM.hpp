/* File Cipher The Return Enum Status For Worked */
enum
{
   SUCCESSFUL, //Function return value is 0
   FAILED, //Function return value is 1
   RUNTIME_ERROR, //Function return value is 2
   THROW_EXCEPTED //Function return value is 3
};

#include "Multiple-Cryptography-Algorithm-To-File.hpp"
#include "Command-Text_User-Interface.hpp"
#include "Graphical-Window_User-Interface.hpp"

void KeyString_SaveToFile(auto VariableSF, auto VariableK, auto VariableK2, auto VariableK3, auto VariableK4, auto VariableTF)
{
   if (!access(".\\File-Key-Record-Log\\", 0))
    {
      cout << "Building and Loading Folder." << endl;
    }
    else
    {
      system("@Mkdir .\\File-Key-Record-Log\\");
    }

    cout << "���ڼ�¼�����������������ļ����ܣ�4����Կ�ַ���......" << endl;
    cout << "Is being recorded and exported, this time for file encryption, 4 key string......" << endl;

    time_t time_value = time(0);
    char now_time_char[64];
    strftime(now_time_char, sizeof(now_time_char), "%Y-%m-%d %X %A",localtime(&time_value));

    ofstream KeyStringSaveToFile;

    KeyStringSaveToFile.open(".\\File-Key-Record-Log\\ENCRYPTION-DECRYPTION-PASSWORD.KEY.TXT");

    KeyStringSaveToFile << "Log Time:" << " " << now_time_char << "\n" << endl;
    KeyStringSaveToFile << "Twilight-Dream-Of-Magic File Lock Password [Key String] Save\n" << endl;
    KeyStringSaveToFile << "\n" << endl;
    KeyStringSaveToFile << "Source Input File Name and Path: " << VariableSF << "\n" << endl;
    KeyStringSaveToFile << "EncryptFile: New Output Target File Name and Path: " << VariableTF << "\n" << endl;
    KeyStringSaveToFile << "Key string1 [Password1]: " << VariableK << "\n" << endl;
    KeyStringSaveToFile << "Key string2 [Password2]: " << VariableK2 << "\n" << endl;
    KeyStringSaveToFile << "Key string3 [Password3]: " << VariableK3<< "\n" << endl;
    KeyStringSaveToFile << "Key string4 [Password4]: " << VariableK4 << "\n" << endl;
    KeyStringSaveToFile << "<******************************************************************************************>" << "\n" << endl;

    KeyStringSaveToFile.close();
}

void CallCustomEncryptToFile(auto VariableSF, auto VariableK, auto VariableK2, auto VariableK3, auto VariableK4, auto VariableTF) //const char* ESF, char* EK[], char* EK2[], char* EK3[], char* EK4[], const char* ETF
{
   KeyString_SaveToFile(VariableSF, VariableK, VariableK2, VariableK3, VariableK4, VariableTF);
   
   int CIPHER_RETURN_STATUS = RunEncryptFile(VariableSF, VariableK, VariableK2, VariableK3, VariableK4, VariableTF);
   
   if (CIPHER_RETURN_STATUS == SUCCESSFUL)
    {
      printf("��ϲ�㣬�ļ�[%s]���ܳɹ���������[%s]��\n", VariableSF, VariableTF);
      printf("Congratulations, the file [%s] is encrypted successfully, saved in [%s]. \n", VariableSF, VariableTF);
      getchar();
      system("Pause");
      system("Cls")
    }
    if(CIPHER_RETURN_STATUS == FAILED)
    {
       cout << "An unknown error occurred while the program was running the core child process function (note: using cryptographic methods to apply data to the file)." << endl;
       cout << "�����������к��ĵ��ӽ��̺�����ע�ͣ� ʹ������ѧ�ķ�����������Ӧ�õ��ļ���ʱ��������δ֪����" << endl;
       exit(1);
    }
    if(CIPHER_RETURN_STATUS == RUNTIME_ERROR)
    {
       cout << "Function Runtime Has Been Error" << endl; 
    }
    else if(CIPHER_RETURN_STATUS == THROW_EXCEPTED)
    {
       cout << "Checked And Throw Exception For Function Working " << endl;
    }

}

void CallCustomDecryptToFile(auto VariableSF, auto VariableK, auto VariableK2, auto VariableK3, auto VariableK4, auto VariableTF) //const char* DSF, char* DK[], char* DK2[], char* DK3[], char* DK4[], const char* DTF
{
    int CIPHER_RETURN_STATUS = RunDecryptFile(VariableSF, VariableK, VariableK2, VariableK3, VariableK4, VariableTF);

    if (CIPHER_RETURN_STATUS == SUCCESSFUL)
    {
      printf("��ϲ�㣬�ļ�[%s]���ܳɹ���������[%s]��\n", VariableSF, VariableTF);
      printf("Congratulations, the file [%s] is decrypted successfully, saved in [%s]. \n", VariableSF, VariableTF);
      getchar();
      system("Pause");
      system("Cls");
    }
    if(CIPHER_RETURN_STATUS == FAILED)
    {
       cout << "An unknown error occurred while the program was running the core child process function (note: using cryptographic methods to apply data to the file)." << endl;
       cout << "�����������к��ĵ��ӽ��̺�����ע�ͣ� ʹ������ѧ�ķ�����������Ӧ�õ��ļ���ʱ��������δ֪����" << endl;
       exit(1);
    }
    if(CIPHER_RETURN_STATUS == RUNTIME_ERROR)
    {
       cout << "Function Runtime Has Been Error" << endl; 
    }
    else if(CIPHER_RETURN_STATUS == THROW_EXCEPTED)
    {
       cout << "Checked And Throw Exception For Function Working " << endl;
    }

}

void DisplayHelpManual(string ShowLanguage)
{
  if (ShowLanguage == "en-US")
  {
    cout << "" << endl;
    cout << "########################################################################################################################" << endl;
    cout << "*                                                     Help Manual                                                      *" << endl;
    cout << "*                                                                                                                      *" << endl;
    cout << "*                        Functional description: Display command help manual from this program                         *" << endl;
    cout << "*                                   Command parameter: [-help] or [--display-help].                                    *" << endl;
    cout << "*                                                                                                                      *" << endl;
    cout << "*                                            Functional group description:                                             *" << endl;
    cout << "*                                   �� About the user interface using this program. ��                                   *" << endl;
    cout << "*                                                                                                                      *" << endl;
    cout << "*                                   Using the user interface: (Command Console Text)                                   *" << endl;
    cout << "*                               Command parameter: [-cui] or [--user-interface command]                                *" << endl;
    cout << "*                                                                                                                      *" << endl;
    cout << "*                                     Using the user interface: (Graphical Window)                                     *" << endl;
    cout << "*                              Command parameter: [-gui] or [--user-interface graphical]                               *" << endl;
    cout << "*                                                                                                                      *" << endl;
    cout << "*                                            Function group 2 description:                                             *" << endl;
    cout << "*                                  �� About the cryptography method in this program, ��                                  *" << endl;
    cout << "*                                 �� If the target file is processed by this program. ��                                 *" << endl;
    cout << "*                           �� Then, the contents of the file are protected and converted. ��                            *" << endl;
    cout << "*         �� After that, the user needs to modify the operation of the file, such as relocking and unlocking. ��         *" << endl;
    cout << "*                                 �� SPAF = ( a secure password to access the file ) ��                                  *" << endl;
    cout << "*    �� These requests to the target file require the correct input (SPAF) before the conversion can be restored. ��     *" << endl;
    cout << "*              �� So that the original contents of the file cannot be obtained by the third party...... ��               *" << endl;
    cout << "*                                                                                                                      *" << endl;
    cout << "*                                                                                                                      *" << endl;
    cout << "*                                                                                                                      *" << endl;
    cout << "*                           Use the command line to interact: (Method: Encrypt to your file)                           *" << endl;
    cout << "*                                        Command parameter: [-e] or [--encrypt]                                        *" << endl;
    cout << "*                                            �� And next command parameter ��                                            *" << endl;
    cout << "*                 Command parameter: [-sf file_path+file_name] or [--source-file file_path+file_name]                  *" << endl;
    cout << "*                                            �� And next command parameter ��                                            *" << endl;
    cout << "*                                 Command parameter: [-k password] or [--key password]                                 *" << endl;
    cout << "*                                            �� And next command parameter ��                                            *" << endl;
    cout << "*                               Command parameter: [-k2 password2] or [--key2 password2]                               *" << endl;
    cout << "*                                            �� And next command parameter ��                                            *" << endl;
    cout << "*                               Command parameter: [-k3 password3] or [--key3 password3]                               *" << endl;
    cout << "*                                            �� And next command parameter ��                                            *" << endl;
    cout << "*                               Command parameter: [-k4 password4] or [--key4 password4]                               *" << endl;
    cout << "*                                            �� And next command parameter ��                                            *" << endl;
    cout << "*                 Command parameter: [-tf file_path+file_name] or [--target-file file_path+file_name]                  *" << endl;
    cout << "*                                                                                                                      *" << endl;
    cout << "*                                                                                                                      *" << endl;
    cout << "*                                                                                                                      *" << endl;
    cout << "*                           Use the command line to interact: (Method: Decrypt to your file)                           *" << endl;
    cout << "*                                        Command parameter: [-d] or [--decrypt]                                        *" << endl;
    cout << "*                                            �� And next command parameter ��                                            *" << endl;
    cout << "*                 Command parameter: [-sf file_path+file_name] or [--source-file file_path+file_name]                  *" << endl;
    cout << "*                                            �� And next command parameter ��                                            *" << endl;
    cout << "*                                 Command parameter: [-k password] or [--key password]                                 *" << endl;
    cout << "*                                            �� And next command parameter ��                                            *" << endl;
    cout << "*                               Command parameter: [-k2 password2] or [--key2 password2]                               *" << endl;
    cout << "*                                            �� And next command parameter ��                                            *" << endl;
    cout << "*                               Command parameter: [-k3 password3] or [--key3 password3]                               *" << endl;
    cout << "*                                            �� And next command parameter ��                                            *" << endl;
    cout << "*                               Command parameter: [-k4 password4] or [--key4 password4]                               *" << endl;
    cout << "*                                            �� And next command parameter ��                                            *" << endl;
    cout << "*                 Command parameter: [-tf file_path+file_name] or [--target-file file_path+file_name]                  *" << endl;
    cout << "*                                                                                                                      *" << endl;
    cout << "########################################################################################################################" << endl;
    cout << "" << endl;
    return;
  }
  if(ShowLanguage == "zh-CN")
  {
    cout << "" << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "+                                  �����ֲ�                                   +" << endl;
    cout << "+                                                                         +" << endl;
    cout << "+                           �����������Ӹó�����ʾ��������ֲᡣ                            +" << endl;
    cout << "+                                                                         +" << endl;
    cout << "+                                                                         +" << endl;
    cout << "+                                 ������������                                  +" << endl;
    cout << "+                            �� ����ʹ�ô˳�����û����档 ��                            +" << endl;
    cout << "+                                                                         +" << endl;
    cout << "+                            ʹ���û�����:  �������̨�ı�                             +" << endl;
    cout << "+                �������: [-cui] �� [--user-interface command]                +" << endl;
    cout << "+                                                                         +" << endl;
    cout << "+                              ʹ���û�����:  ͼ�δ���                              +" << endl;
    cout << "+               �������: [-gui] �� [--user-interface graphical]               +" << endl;
    cout << "+                                                                         +" << endl;
    cout << "+                                 ������2������                                 +" << endl;
    cout << "+                                   �� ���ڴ˳����еļ��ܷ��� ��                       +" << endl;
    cout << "+                          �� ����Ŀ���ļ����������������ɡ� ��                          +" << endl;
    cout << "+                           �� Ȼ���ļ����ݣ���������ת���� ��                           +" << endl;
    cout << "+                      �� ֮���û���Ҫ�޸��ļ��Ĳ������������������ͽ����� ��                       +" << endl;
    cout << "+              �� ��ЩӦ����Ŀ���ļ���������Ҫ������ȷ��(�����ļ��İ�ȫ����)���ſ��Ի�ԭת���� ��               +" << endl;
    cout << "+                         �� ����ʹ�������޷���ȡ�ļ���ԭʼ����...... ��                     +" << endl;
    cout << "+                                                                         +" << endl;
    cout << "+                                                                         +" << endl;
    cout << "+                                                                         +" << endl;
    cout << "+                                  ʹ�������н��н���                              +" << endl;
    cout << "+                                   ִ�й��� -> ���ܵ�����ļ�                       +" << endl;
    cout << "+                         �������: [-e] �� [--encrypt]                        +" << endl;
    cout << "+                              �� Ȼ����һ��������� ��                              +" << endl;
    cout << "+              �������: [-sf �ļ�·��+�ļ�����] �� [--source-file �ļ�·��+�ļ�����]          +" << endl;
    cout << "+                              �� Ȼ����һ��������� ��                              +" << endl;
    cout << "+                          �������: [-k ����] �� [--key ����]                     +" << endl;
    cout << "+                              �� Ȼ����һ��������� ��                              +" << endl;
    cout << "+                          �������: [-k2 ����2] �� [--key2 ����2]                 +" << endl;
    cout << "+                              �� Ȼ����һ��������� ��                              +" << endl;
    cout << "+                          �������: [-k3 ����3] �� [--key3 ����3]                 +" << endl;
    cout << "+                              �� Ȼ����һ��������� ��                              +" << endl;
    cout << "+                          �������: [-k4 ����4] �� [--key4 ����4]                 +" << endl;
    cout << "+                              �� Ȼ����һ��������� ��                              +" << endl;
    cout << "+             �������: [-tf �ļ�·��+�ļ�����] �� [--target-file �ļ�·��+�ļ�����]           +" << endl;
    cout << "+                                                                         +" << endl;
    cout << "+                                                                         +" << endl;
    cout << "+                                                                         +" << endl;
    cout << "+                                  ʹ�������н��н���                              +" << endl;
    cout << "+                                   ִ�й���: ���ܵ�����ļ�                         +" << endl;
    cout << "+                         �������: [-d] �� [--decrypt]                        +" << endl;
    cout << "+                              �� Ȼ����һ��������� ��                              +" << endl;
    cout << "+              �������: [-sf �ļ�·��+�ļ�����] �� [--source-file �ļ�·��+�ļ�����]          +" << endl;
    cout << "+                              �� Ȼ����һ��������� ��                              +" << endl;
    cout << "+                          �������: [-k ����] �� [--key ����]                     +" << endl;
    cout << "+                              �� Ȼ����һ��������� ��                              +" << endl;
    cout << "+                          �������: [-k2 ����2] �� [--key2 ����2]                 +" << endl;
    cout << "+                              �� Ȼ����һ��������� ��                              +" << endl;
    cout << "+                          �������: [-k3 ����3] �� [--key3 ����3]                 +" << endl;
    cout << "+                              �� Ȼ����һ��������� ��                              +" << endl;
    cout << "+                          �������: [-k4 ����4] �� [--key4 ����4]                 +" << endl;
    cout << "+                              �� Ȼ����һ��������� ��                              +" << endl;
    cout << "+            �������: [-tf �ļ�·��+�ļ�����] �� [--target-file �ļ�·��+�ļ�����]            +" << endl;
    cout << "+                                                                         +" << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "" << endl;
    return;
  }
}