#include "Multiple-Cryptography-Algorithm-To-File.hpp"
#include "Command-Text_User-Interface.hpp"
#include "Graphical-Window_User-Interface.hpp"

using namespace std;

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
