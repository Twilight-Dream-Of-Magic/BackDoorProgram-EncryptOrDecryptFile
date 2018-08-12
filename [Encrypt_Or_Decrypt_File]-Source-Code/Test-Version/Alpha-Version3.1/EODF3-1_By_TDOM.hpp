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

			int FileByteData,                              //ÿ�δ��ļ��ж�ȡ���ֽ��� The number of bytes read from the file each time
				RTNOC,                                     //����ѭ������ (Run The Number Of Cycles)
				KeyLength = strlen(E_KEY),                 //��Կ�ĳ��� The length of the key
				KeyLength2 = strlen(E_KEY2),
				KeyLength3 = strlen(E_KEY3),
				KeyLength4 = strlen(E_KEY4);

			FilePointerSource = fopen(E_SourceFileCharPath, "rb"); //�Զ����Ʒ�ʽ��ȡ�ļ�
			if(FilePointerSource == NULL)
			{
				printf("File[%s]failed to open, please check whether the file path and name are entered correctly! \n", E_SourceFileCharPath);
				printf("�ļ�[%s]��ʧ�ܣ������ļ�·���������Ƿ�������ȷ��\n", E_SourceFileCharPath);
				getchar();
				return 0;
			}

			 FilePointerTarget = fopen(E_TargetFileCharPath, "wb+"); //�Զ����Ʒ�ʽд���ļ�
			if(FilePointerTarget == NULL)
			{
				printf("File[%s]creation/write failed! Please check whether the file path and name are entered correctly!\n", E_TargetFileCharPath);
				printf("�ļ�[%s]����/д��ʧ�ܣ������ļ�·���������Ƿ�������ȷ��\n", E_TargetFileCharPath);
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
		while((FileHeaderByteData = fread(buffer, 1, FileHeaderLength, FilePointerSource)) > 0) //Continuously read fileheaderlength length data from file, save to buffer until end of file
		{
			fwrite(buffer, 1, FileHeaderByteData, FilePointerTarget); //Write data from buffer to file
		}

		/*The pointer to the file stream is moved, and the read and write data continues to start at the 513rd byte*/
		fseek(FilePointerSource,513L,SEEK_SET);
		fseek(FilePointerTarget,513L,SEEK_SET);


		for(NOIEM = 0;NOIEM < MAX_NOT_E_MODULE;NOIEM++)
		{
			system("@color 6F");
			std::cout << "Please wait, read and write in the file......" << endl;
			std::cout << "��ȴ����ļ���д��......" << endl;
			system("@color 0D");
			std :: cout << "Encrypting...... Currently in use the first key" << endl;

			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				//Mini-Group Encryption Module Key1-Calculate1
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
						buffer[RTNOC] /= E_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				//Mini-Group Encryption Module Key1-Calculate2
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
			}

			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				//Mini-Group Encryption Module Key1-Calculate3
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
						buffer[RTNOC] *= E_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				//Mini-Group Encryption Module Key1-Calculate4
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
						buffer[RTNOC] -= E_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

//�ļ�����Կ2�ڻ������м���
//The file and key2 are counted in Buffer

			std :: cout << "Encrypting...... Currently in use the second key" << endl;

			//Mini-Group Encryption Module Key2-Calculate1
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= E_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���е�������
					{
						buffer[RTNOC] *= E_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Encryption Module Key2-Calculate2
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= E_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���е�������
					{
					   buffer[RTNOC] -= E_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Encryption Module Key2-Calculate3
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= E_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���е�������
					{
					   buffer[RTNOC] /= E_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Encryption Module Key2-Calculate4
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= E_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���е�������
					{
					   buffer[RTNOC] += E_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

//�ļ�����Կ3�ڻ������м���
//The file and key3 are counted in Buffer

			std :: cout << "Encrypting...... Currently in use the third key" << endl;

			//Mini-Group Encryption Module Key3-Calculate1
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{

				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= E_KEY3[RTNOC];
					}
				fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���е�������
					{
						buffer[RTNOC] -= E_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Encryption Module Key3-Calculate2
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{

				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= E_KEY3[RTNOC];
					}
				fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���е�������
					{
						buffer[RTNOC] /= E_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Encryption Module Key3-Calculate3
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{

				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= E_KEY3[RTNOC];
					}
				fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���е�������
					{
						buffer[RTNOC] += E_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Encryption Module Key3-Calculate4
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{

				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= E_KEY3[RTNOC];
					}
				fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���е�������
					{
						buffer[RTNOC] *= E_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

//�ļ�����Կ4�ڻ������м���
//The file and key4 are counted in Buffer

			std :: cout << "Encrypting...... Currently in use the fourth key" << endl;

			//Mini-Group Encryption Module Key4-Calculate1

			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for (RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
					buffer[RTNOC] ^= E_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���е�������
					{
						buffer[RTNOC] += E_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Encryption Module Key4-Calculate2
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for (RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
					buffer[RTNOC] ^= E_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���е�������
					{
						buffer[RTNOC] *= E_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Encryption Module Key4-Calculate3
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for (RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
					buffer[RTNOC] ^= E_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���е�������
					{
						buffer[RTNOC] -= E_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Encryption Module Key4-Calculate4
			for(NOIEM = 0;NOIEM < MINI_NOT_E_GROUP;NOIEM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for (RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
					buffer[RTNOC] ^= E_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���е�������
					{
						buffer[RTNOC] /= E_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			if(NOIEM < MAX_NOT_E_MODULE || 12800)
			{
			  break; //End encrypting process
			}

		}

/***********************************************************************************************************************************************************/

/*�����㷨����*/

		  fclose(FilePointerSource);
		  fclose(FilePointerTarget);

		  //DeleteFile(E_SourceFileCharPath);

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

			int FileByteData,                              //ÿ�δ��ļ��ж�ȡ���ֽ��� The number of bytes read from the file each time
				RTNOC,                                     //����ѭ������ (Run The Number Of Cycles)
				KeyLength = strlen(D_KEY),                 //��Կ�ĳ��� The length of the key
				KeyLength2 = strlen(D_KEY2),
				KeyLength3 = strlen(D_KEY3),
				KeyLength4 = strlen(D_KEY4);

			FilePointerSource = fopen(D_SourceFileCharPath, "rb"); //�Զ����Ʒ�ʽ��ȡ�ļ�
			if(FilePointerSource == NULL)
			{
				printf("File[%s]failed to open, please check whether the file path and name are entered correctly! \n", D_SourceFileCharPath);
				printf("�ļ�[%s]��ʧ�ܣ������ļ�·���������Ƿ�������ȷ��\n", D_SourceFileCharPath);
				getchar();
				return 0;
			}

			FilePointerTarget = fopen(D_TargetFileCharPath, "wb+"); //�Զ����Ʒ�ʽд���ļ�
			if(FilePointerTarget == NULL)
			{
				printf("File[%s]creation/write failed! Please check whether the file path and name are entered correctly!\n", D_TargetFileCharPath);
				printf("�ļ�[%s]����/д��ʧ�ܣ������ļ�·���������Ƿ�������ȷ��\n", D_TargetFileCharPath);
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
		while((FileHeaderByteData = fread(buffer, 1, FileHeaderLength, FilePointerSource)) > 0) //Continuously read fileheaderlength length data from file, save to buffer until end of file
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
			std :: cout << "Decrypting...... Currently in use the first key" << endl;

			//Mini-Group Decryption Module Key1-Calculate1
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= D_KEY[RTNOC];
					}
				fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݼ�����
					{
						buffer[RTNOC] /= D_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Decryption Module Key1-Calculate2
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= D_KEY[RTNOC];
					}
				fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݼ�����
					{
						buffer[RTNOC] -= D_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Decryption Module Key1-Calculate3
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= D_KEY[RTNOC];
					}
				fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݼ�����
					{
						buffer[RTNOC] *= D_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Decryption Module Key1-Calculate4
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= D_KEY[RTNOC];
					}
				fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݼ�����
					{
						buffer[RTNOC] += D_KEY[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

//�ļ�����Կ2�ڻ������м���
//The file and key2 are counted in Buffer

			std :: cout << "Decrypting...... Currently in use the second key" << endl;

			//Mini-Group Decryption Module Key2-Calculate1
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= D_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݼ�����
					{
						buffer[RTNOC] *= D_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Decryption Module Key2-Calculate2
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= D_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݼ�����
					{
						buffer[RTNOC] += D_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Decryption Module Key2-Calculate3
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= D_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݼ�����
					{
						buffer[RTNOC] /= D_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Decryption Module Key2-Calculate4
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= D_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݼ�����
					{
						buffer[RTNOC] -= D_KEY2[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

//�ļ�����Կ3�ڻ������м���
//The file and key3 are counted in Buffer

			std :: cout << "Decrypting...... Currently in use the third key" << endl;

			//Mini-Group Decryption Module Key3-Calculate1
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while ((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for (RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= D_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݼ�����
					{
						buffer[RTNOC] += D_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Decryption Module Key3-Calculate2
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while ((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for (RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= D_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݼ�����
					{
						buffer[RTNOC] /= D_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Decryption Module Key3-Calculate3
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while ((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for (RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= D_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݼ�����
					{
						buffer[RTNOC] -= D_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Decryption Module Key3-Calculate4
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while ((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for (RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= D_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݼ�����
					{
						buffer[RTNOC] *= D_KEY3[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

//�ļ�����Կ4�ڻ������м���
//The file and key4 are counted in Buffer

			std :: cout << "Decrypting...... Currently in use the fourth key" << endl;

			//Mini-Group Decryption Module Key4-Calculate1
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= D_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݼ�����
					{
						buffer[RTNOC] -= D_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Decryption Module Key4-Calculate2
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= D_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݼ�����
					{
						buffer[RTNOC] *= D_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Decryption Module Key4-Calculate3
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= D_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݼ�����
					{
						buffer[RTNOC] += D_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			//Mini-Group Decryption Module Key4-Calculate4
			for(NOIDM = 0;NOIDM < MINI_NOT_D_GROUP;NOIDM++)
			{
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY�����������
					{
						buffer[RTNOC] ^= D_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
				while((FileByteData = fread(buffer, 1, KeyLength4, FilePointerSource)) > 0) //���ϵش��ļ��ж�ȡ KeyLength4 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
				{
					for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڵĺ�E_KEY���еݼ�����
					{
						buffer[RTNOC] /= D_KEY4[RTNOC];
					}
				  fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
				}
			}

			if(NOIEM < MAX_NOT_D_MODULE || 12800)
			{
			  break; //End decrypting process
			}
		}

/***********************************************************************************************************************************************************/

/*�����㷨����*/

		  fclose(FilePointerSource);
		  fclose(FilePointerTarget);

		  //DeleteFile(D_SourceFileCharPath);

		return 1;
	}
