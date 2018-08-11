#include "Support-Libary.hpp"

using namespace std;

int RunEncryptFile(const char *E_SourceFileCharPath, char *E_KEY, char *E_KEY2, char *E_KEY3, char *E_KEY4, const char *E_TargetFileCharPath);
int RunDecryptFile(const char *D_SourceFileCharPath, char *D_KEY, char *D_KEY2, char *D_KEY3, char *D_KEY4, const char *D_TargetFileCharPath);

/***��������-��ʼ Declare the code - the beginning***/
//���±���,Ӧ�õ��ļ�������ʱ
//The following variables apply when the file is encrypted

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

string D_SourceFileName,      //Դ�ļ���
D_TargetFileMainName,     //Ŀ���ļ���Ҫ��
D_TargetFileTempName,     //Ŀ���ļ���ʱ�����
D_TargetFileExtendedName; //Ŀ���ļ�Դ��չ��

char D_KEY[256], //File (Decryption or Decrypted) key �ļ�������Կ
D_KEY2[256],
D_KEY3[256],
D_KEY4[256];
/***��������-���� Declare the code - end***/

int NOIEM; //��ʼ����ģ����� (Number of initial encryption modules)
int NOIDM; //��ʼ����ģ����� (Number of initial decryption modules)

int MAX_NOT_E_MODULE = 12801; //����ģ�����ѭ������ (The maximum number of times the encryption module is running)
int MINI_NOT_E_GROUP = 6401; //���ܼ�����Сѭ������ (The minimum number of times the encryption group is running)

int MAX_NOT_D_MODULE = 12801; //����ģ�����ѭ������ (The maximum number of times the decryption module is running)
int MINI_NOT_D_GROUP = 6401; //���ܼ�����Сѭ������ (The minimum number of times the decryption group is running)

long FileHeaderLength = 0;
long FileHeaderByteData = 0;

/*******************************************
*                 �����ļ�
*
* E_SourceFileName    ��Ҫ���ܵ��ļ���
* E_KEY               ��Կ
* E_TargetFileNewName ������ɺ�Ҫ������ļ���
*
* @return  ���ܳɹ���ʧ�ܵ����ֱ�ʾ
*
* 0 = ����ʧ��
* 1 = ���ܳɹ�
********************************************/

	int RunEncryptFile(const char *E_SourceFileCharPath, char *E_KEY, char *E_KEY2, char *E_KEY3, char *E_KEY4, const char *E_TargetFileCharPath)
	{
			FILE *FilePointerSource, *FilePointerTarget; //��Ҫ�򿪵��ļ���ָ�� Need to open the file pointer
			char buffer[1024];                           //�ļ��������������ڴ�Ŵ��ļ���ȡ������ File stream buffer, used to store the data read from the file

			int FileByteData,                            //ÿ�δ��ļ��ж�ȡ���ֽ��� The number of bytes read from the file each time
				RTNOC,                                     //����ѭ������ (Run The Number Of Cycles)
				KeyLength = strlen(E_KEY),                 //��Կ�ĳ��� The length of the key
				KeyLength2 = strlen(E_KEY2),
				KeyLength3 = strlen(E_KEY3),
				KeyLength4 = strlen(E_KEY4);

			FilePointerSource = fopen(E_SourceFileCharPath, "rb"); //�Զ����Ʒ�ʽ��ȡ�ļ�
			if(FilePointerSource == NULL)
			{
				//printf("File[%s]failed to open, please check whether the file path and name are entered correctly !\n", E_SourceFileCharPath);
				//printf("�ļ�[%s]��ʧ�ܣ������ļ�·���������Ƿ�������ȷ ��\n", E_SourceFileCharPath);
        cout << "File " << "[ " << E_SourceFileCharPath << " ]" << " failed to open, please check whether the file path and name are entered correctly!" << endl;
        cout << "�ļ� " << "[ " << E_SourceFileCharPath << " ]" << " ��ʧ�ܣ������ļ�·���������Ƿ�������ȷ ��" << endl;
				getchar();
				return 0;
			}

			FilePointerTarget = fopen(E_TargetFileCharPath, "wb+"); //�Զ����Ʒ�ʽд���ļ�
			if(FilePointerTarget == NULL)
			{
				//printf("File[%s]creation/write failed! Please check whether the file path and name are entered correctly !\n", E_TargetFileCharPath);
				//printf("�ļ�[%s]����/д��ʧ�ܣ������ļ�·���������Ƿ�������ȷ ��\n", E_TargetFileCharPath);
        cout << "File " << "[ " << E_TargetFileCharPath << " ]" << " creation/write failed! Please check whether the file path and name are entered correctly !" << endl;
        cout << "�ļ� " << "[ " << E_TargetFileCharPath << " ]" << " ����/д��ʧ�ܣ������ļ�·���������Ƿ�������ȷ ��" << endl;
				getchar();
				return 0;
			}

/*�����㷨��ʼ*/

/*****************************************************************************buffer[RTNOC]******************************************************************************/

//���д��ͼ���ģ��
//Run large encryption module

//�ļ�����Կ�ڻ������м���
//The file and key are counted in Buffer

    /*Skip file header (512 byte)*/
		fseek(FilePointerSource,512L,SEEK_SET); //Move the file pointer to the 512th byte of the file start
		FileHeaderLength = ftell(FilePointerSource);//Get this file header length
		fseek(FilePointerSource,0L,SEEK_SET);//Move the file pointer to this file start point

    /*Continuously read fileheaderlength length data from file, save to buffer until end of file*/
		while((FileHeaderByteData = fread(buffer, 1, FileHeaderLength, FilePointerSource)) > 0)
		{
			fwrite(buffer, 1, FileHeaderByteData, FilePointerTarget); //Write data from buffer to file
		}

		/*The pointer to the file stream is moved, and the read and write data continues to start at the 513rd byte*/
		fseek(FilePointerSource,513L,SEEK_SET);
		fseek(FilePointerTarget,513L,SEEK_SET);


		for(NOIEM = 0;NOIEM < MAX_NOT_E_MODULE;NOIEM++)
		{
			system("@color 6F");
			cout << "Please wait, read and write in the file......" << endl;
			cout << "��ȴ����ļ���д��......" << endl;
			system("@color 0D");
			cout << "The display of the interaction progress has been opened using the request for the encryption function." << endl;
			cout << "ʹ�ü��ܹ��ܵ����󣬽������ȵ���ʾ�Ѿ����򿪡�" << endl;
			cout << "Encrypting...... Currently in use the first key" << endl;

			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				//Mini-Group Encryption Module Key1-Calculate1
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and E_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= E_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop division) operation of byte-by-byte and E_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݳ�����.
					{
						buffer[RTNOC] /= E_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				//Mini-Group Encryption Module Key1-Calculate2
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and E_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= E_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop addition) operation of byte-by-byte and E_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���е�������.
					{
						buffer[RTNOC] += E_KEY[RTNOC];
					}
				   fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				//Mini-Group Encryption Module Key1-Calculate3
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //��Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and E_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= E_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop multiplication) operation of byte-by-byte and E_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݳ�����.
					{
						buffer[RTNOC] *= E_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				//Mini-Group Encryption Module Key1-Calculate4
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and E_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= E_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop subtraction) operation of byte-by-byte and E_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݼ�����.
					{
						buffer[RTNOC] -= E_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

//�ļ�����Կ2�ڻ������м���
//The file and key2 are counted in Buffer

			cout << "Encrypting...... Currently in use the second key" << endl;

			//Mini-Group Encryption Module Key2-Calculate1
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and E_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= E_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop multiplication) operation of byte-by-byte and E_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݳ�����.
					{
						buffer[RTNOC] *= E_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Encryption Module Key2-Calculate2
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and E_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= E_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop subtraction) operation of byte-by-byte and E_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݼ�����.
					{
					   buffer[RTNOC] -= E_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Encryption Module Key2-Calculate3
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and E_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= E_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop division) operation of byte-by-byte and E_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݳ����㡣
					{
					   buffer[RTNOC] /= E_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Encryption Module Key2-Calculate4
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and E_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= E_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop addition) operation of byte-by-byte and E_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���е�������.
					{
					   buffer[RTNOC] += E_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

//�ļ�����Կ3�ڻ������м���
//The file and key3 are counted in Buffer

			cout << "Encrypting...... Currently in use the third key" << endl;

			//Mini-Group Encryption Module Key3-Calculate1
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{

				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and E_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= E_KEY3[RTNOC];
					}
				fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop subtraction) operation of byte-by-byte and E_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݼ�����.
					{
						buffer[RTNOC] -= E_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Encryption Module Key3-Calculate2
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{

				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and E_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= E_KEY3[RTNOC];
					}
				fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop division) operation of byte-by-byte and E_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݳ�����.
					{
						buffer[RTNOC] /= E_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Encryption Module Key3-Calculate3
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{

				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and E_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= E_KEY3[RTNOC];
					}
				fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop addition) operation of byte-by-byte and E_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���е�������.
					{
						buffer[RTNOC] += E_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}

			}

			//Mini-Group Encryption Module Key3-Calculate4
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{

				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and E_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= E_KEY3[RTNOC];
					}
				fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop multiplication) operation of byte-by-byte and E_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݳ�����.
					{
						buffer[RTNOC] *= E_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

//�ļ�����Կ4�ڻ������м���
//The file and key4 are counted in Buffer

			cout << "Encrypting...... Currently in use the fourth key" << endl;

			//Mini-Group Encryption Module Key4-Calculate1

			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for (RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and E_KEY on the data in the buffer
					{
					buffer[RTNOC] ^= E_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //��Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop addition) operation of byte-by-byte and E_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���е�������.
					{
						buffer[RTNOC] += E_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Encryption Module Key4-Calculate2
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for (RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and E_KEY on the data in the buffer
					{
					buffer[RTNOC] ^= E_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop multiplication) operation of byte-by-byte and E_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݳ�����.
					{
						buffer[RTNOC] *= E_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Encryption Module Key4-Calculate3
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for (RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and E_KEY on the data in the buffer
					{
					buffer[RTNOC] ^= E_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop subtraction) operation of byte-by-byte and E_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݼ�����.
					{
						buffer[RTNOC] -= E_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Encryption Module Key4-Calculate4
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for (RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and E_KEY on the data in the buffer
					{
					buffer[RTNOC] ^= E_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop division) operation of byte-by-byte and E_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݳ�����.
					{
						buffer[RTNOC] /= E_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			system("@color 07");
			cout << "The display of the interaction progress has been closed for the encryption function." << endl;
			cout << "�Ѿ��رռ��ܹ��ܵĽ������ȵ���ʾ��" << endl;

			if(NOIEM < MAX_NOT_E_MODULE || 12800)
			{
			  break; //End encrypting process
			}

		}

/***********************************************************************************************************************************************************/

/*�����㷨����*/

		  fclose(FilePointerSource);
		  fclose(FilePointerTarget);

		  //DeleteFile(E_SourceFileCharPath); /*This is windows API function*/
			//remove(E_SourceFileCharPath); /*This is C & C++ language the delete file common IO function, use in the linux and unix or windows platform.*/

		return 1;
	}

/*******************************************
*                 �����ļ�
*
* D_SourceFileName    ��Ҫ���ܵ��ļ���
* D_KEY               ��Կ
* D_TargetFileNewName ������ɺ�Ҫ������ļ���
*
* @return  ���ܳɹ���ʧ�ܵ����ֱ�ʾ
*
* 0 = ����ʧ��
* 1 = ���ܳɹ�
********************************************/

	int RunDecryptFile(const char *D_SourceFileCharPath, char *D_KEY, char *D_KEY2, char *D_KEY3, char *D_KEY4, const char *D_TargetFileCharPath)
	{
			FILE *FilePointerSource, *FilePointerTarget; //��Ҫ�򿪵��ļ���ָ�� Need to open the file pointer
			char buffer[1024];                           //�ļ��������������ڴ�Ŵ��ļ���ȡ������ File stream buffer, used to store the data read from the file

			int FileByteData,                            //ÿ�δ��ļ��ж�ȡ���ֽ��� The number of bytes read from the file each time
				RTNOC,                                     //����ѭ������ (Run The Number Of Cycles)
				KeyLength = strlen(D_KEY),                 //��Կ�ĳ��� The length of the key
				KeyLength2 = strlen(D_KEY2),
				KeyLength3 = strlen(D_KEY3),
				KeyLength4 = strlen(D_KEY4);

			FilePointerSource = fopen(D_SourceFileCharPath, "rb"); //�Զ����Ʒ�ʽ��ȡ�ļ�
			if(FilePointerSource == NULL)
			{
				//printf("File[%s]failed to open, please check whether the file path and name are entered correctly !\n", D_SourceFileCharPath);
				//printf("�ļ�[%s]��ʧ�ܣ������ļ�·���������Ƿ�������ȷ ��\n", D_SourceFileCharPath);
        cout << "File " << "[ " << D_SourceFileCharPath << " ]" << " failed to open, please check whether the file path and name are entered correctly !" << endl;
        cout << "�ļ� " << "[ " << D_SourceFileCharPath << " ]" << " ��ʧ�ܣ������ļ�·���������Ƿ�������ȷ ��" << endl;
				getchar();
				return 0;
			}

			FilePointerTarget = fopen(D_TargetFileCharPath, "wb+"); //�Զ����Ʒ�ʽд���ļ�
			if(FilePointerTarget == NULL)
			{
				//printf("File[%s]creation/write failed! Please check whether the file path and name are entered correctly !\n", D_TargetFileCharPath);
				//printf("�ļ�[%s]����/д��ʧ�ܣ������ļ�·���������Ƿ�������ȷ ��\n", D_TargetFileCharPath);
        cout << "File " << "[ " << D_TargetFileCharPath << " ]" << " creation/write failed! Please check whether the file path and name are entered correctly !" << endl;
        cout << "�ļ� " << "[ " << D_TargetFileCharPath << " ]" << " ����/д��ʧ�ܣ������ļ�·���������Ƿ�������ȷ ��" << endl;
				getchar();
				return 0;
			}

/*�����㷨��ʼ*/

/***********************************************************************************************************************************************************/

//���д��ͽ���ģ��
//Run large decryption module

//�ļ�����Կ�ڻ������м���
//The file and key are counted in Buffer

    /*Skip file header (512 byte)*/
		fseek(FilePointerSource,512L,SEEK_SET); //Move the file pointer to the 512th byte of the file start
		FileHeaderLength = ftell(FilePointerSource);//Get this file header length
		fseek(FilePointerSource,0L,SEEK_SET);//Move the file pointer to this file start point

    /*Continuously read fileheaderlength length data from file, save to buffer until end of file*/
		while((FileHeaderByteData = fread(buffer, 1, FileHeaderLength, FilePointerSource)) > 0)
		{
			fwrite(buffer, 1, FileHeaderByteData, FilePointerTarget); //Write data from buffer to file
		}

		/*The pointer to the file stream is moved, and the read and write data continues to start at the 513rd byte*/
		fseek(FilePointerSource,513L,SEEK_SET);
		fseek(FilePointerTarget,513L,SEEK_SET);

		for(NOIDM = 0;NOIDM < MAX_NOT_D_MODULE;NOIDM++)
		{
			system("@color 6F");
			std::cout << "Please wait, read and write in the file......" << endl;
			std::cout << "��ȴ����ļ���д��......" << endl;
			system("@color 0D");
			cout << "The display of the interaction progress has been opened using the request for the decryption function." << endl;
			cout << "ʹ�ý��ܹ��ܵ����󣬽������ȵ���ʾ�Ѿ����򿪡�" << endl;
			cout << "Decrypting...... Currently in use the first key" << endl;

			//Mini-Group Decryption Module Key1-Calculate1
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and D_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= D_KEY[RTNOC];
					}
				fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop division) operation of byte-by-byte and D_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݳ�����.
					{
						buffer[RTNOC] /= D_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Decryption Module Key1-Calculate2
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and D_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= D_KEY[RTNOC];
					}
				fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop subtraction) operation of byte-by-byte and D_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݼ�����.
					{
						buffer[RTNOC] -= D_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Decryption Module Key1-Calculate3
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and D_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= D_KEY[RTNOC];
					}
				fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop multiplication) operation of byte-by-byte and D_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݳ�����.
					{
						buffer[RTNOC] *= D_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Decryption Module Key1-Calculate4
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and D_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= D_KEY[RTNOC];
					}
				fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //Constantly reads KeyLength-length data from a file, saves it to the buffer until the end of the file. ���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�������
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop addition) operation of byte-by-byte and D_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���е�������.
					{
						buffer[RTNOC] += D_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

//�ļ�����Կ2�ڻ������м���
//The file and key2 are counted in Buffer

			cout << "Decrypting...... Currently in use the second key" << endl;

			//Mini-Group Decryption Module Key2-Calculate1
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and D_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= D_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop multiplication) operation of byte-by-byte and D_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݳ�����.
					{
						buffer[RTNOC] *= D_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Decryption Module Key2-Calculate2
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and D_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= D_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop addition) operation of byte-by-byte and D_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���е�������.
					{
						buffer[RTNOC] += D_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Decryption Module Key2-Calculate3
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and D_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= D_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop division) operation of byte-by-byte and D_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݳ�����.
					{
						buffer[RTNOC] /= D_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Decryption Module Key2-Calculate4
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and D_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= D_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop subtraction) operation of byte-by-byte and D_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݼ�����.
					{
						buffer[RTNOC] -= D_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

//�ļ�����Կ3�ڻ������м���
//The file and key3 are counted in Buffer

			cout << "Decrypting...... Currently in use the third key" << endl;

			//Mini-Group Decryption Module Key3-Calculate1
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while ((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for (RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and D_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= D_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop addition) operation of byte-by-byte and D_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���е�������.
					{
						buffer[RTNOC] += D_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Decryption Module Key3-Calculate2
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while ((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for (RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and D_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= D_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop division) operation of byte-by-byte and D_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݳ�����.
					{
						buffer[RTNOC] /= D_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Decryption Module Key3-Calculate3
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while ((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for (RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and D_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= D_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop subtraction) operation of byte-by-byte and D_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݼ�����.
					{
						buffer[RTNOC] -= D_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Decryption Module Key3-Calculate4
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while ((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for (RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and D_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= D_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop multiplication) operation of byte-by-byte and D_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݳ�����.
					{
						buffer[RTNOC] *= D_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

//�ļ�����Կ4�ڻ������м���
//The file and key4 are counted in Buffer

			cout << "Decrypting...... Currently in use the fourth key" << endl;

			//Mini-Group Decryption Module Key4-Calculate1
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and D_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= D_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop subtraction) operation of byte-by-byte and D_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݼ�����.
					{
						buffer[RTNOC] -= D_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Decryption Module Key4-Calculate2
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and D_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= D_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop multiplication) operation of byte-by-byte and D_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݳ�����.
					{
						buffer[RTNOC] *= D_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Decryption Module Key4-Calculate3
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and D_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= D_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop addition) operation of byte-by-byte and D_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���е�������.
					{
						buffer[RTNOC] += D_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			//Mini-Group Decryption Module Key4-Calculate4
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (XOR = Exclusive or) operation of byte-by-byte and D_KEY on the data in the buffer
					{
						buffer[RTNOC] ^= D_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //Execute the (loop division) operation of byte-by-byte and D_KEY on the data in the buffer. ��buffer�е��������ֽڵĺ�E_KEY���еݳ�����.
					{
						buffer[RTNOC] /= D_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //Write buffer data to file. ��buffer�е�����д���ļ���
				}
			}

			system("@color 07");
			cout << "The display of the interaction progress has been closed for the decryption function." << endl;
			cout << "�Ѿ��رս��ܹ��ܵĽ������ȵ���ʾ��" << endl;

			if(NOIEM < MAX_NOT_D_MODULE || 12800)
			{
			  break; //End decrypting process
			}

		}

/***********************************************************************************************************************************************************/

/*�����㷨����*/

		  fclose(FilePointerSource);
		  fclose(FilePointerTarget);

			//DeleteFile(D_SourceFileCharPath); /*This is windows API function*/
		  //remove(D_SourceFileCharPath); /*This is C & C++ language the delete file common IO function, use in the linux and unix or windows platform.*/

		return 1;
	}
