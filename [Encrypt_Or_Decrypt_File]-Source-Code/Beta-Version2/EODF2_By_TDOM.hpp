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

        int RunEncryptFile(char *E_SourceFileName, char *E_KEY, char *E_KEY2, char *E_KEY3, char *E_TargetFileNewName)
        {
            FILE *FilePointerSource, *FilePointerTarget; //Ҫ�򿪵��ļ���ָ��
            char buffer[1024];               //�����������ڴ�Ŵ��ļ���ȡ������

            int FileByteData,                //ÿ�δ��ļ��ж�ȡ���ֽ���
                RTNOC,                       //����ѭ������ (Run The Number Of Cycles)
                KeyLength = strlen(E_KEY),   //��Կ�ĳ���
                KeyLength2 = strlen(E_KEY2),
                KeyLength3 = strlen(E_KEY3);

             FilePointerSource = fopen(E_SourceFileName, "rb"); //�Զ����Ʒ�ʽ��ȡ�ļ�
             if(FilePointerSource == NULL)
             {
               printf("File[%s]failed to open, please check whether the file path and name are entered correctly! \n", E_SourceFileName);
               printf("�ļ�[%s]��ʧ�ܣ������ļ�·���������Ƿ�������ȷ��\n", E_SourceFileName);
               getchar();
               return 0;
             }

             FilePointerTarget = fopen(E_TargetFileNewName, "wb"); //�Զ����Ʒ�ʽд���ļ�
             if(FilePointerTarget == NULL)
             {
               printf("File[%s]creation/write failed! Please check whether the file path and name are entered correctly!\n", E_TargetFileNewName);
               printf("�ļ�[%s]����/д��ʧ�ܣ������ļ�·���������Ƿ�������ȷ��\n", E_TargetFileNewName);
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

          DeleteFile(E_SourceFileName);

        return 1;
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

        int RunDecryptFile(char *D_SourceFileName, char *D_KEY, char *D_KEY2, char *D_KEY3, char *D_TargetFileNewName)
        {
            FILE *FilePointerSource, *FilePointerTarget; //Ҫ�򿪵��ļ���ָ��
            char buffer[1024];               //�����������ڴ�Ŵ��ļ���ȡ������

            int FileByteData,                //ÿ�δ��ļ��ж�ȡ���ֽ���
                RTNOC,                       //����ѭ������ (Run The Number Of Cycles)
                KeyLength = strlen(D_KEY),   //��Կ�ĳ���
                KeyLength2 = strlen(D_KEY2),
                KeyLength3 = strlen(D_KEY3);

             FilePointerSource = fopen(D_SourceFileName, "rb"); //�Զ����Ʒ�ʽ��ȡ�ļ�
             if(FilePointerSource == NULL)
             {
               printf("File[%s]failed to open, please check whether the file path and name are entered correctly! \n", D_SourceFileName);
               printf("�ļ�[%s]��ʧ�ܣ������ļ�·���������Ƿ�������ȷ��\n", D_SourceFileName);
               getchar();
               return 0;
             }

             FilePointerTarget = fopen(D_TargetFileNewName, "wb"); //�Զ����Ʒ�ʽд���ļ�
             if(FilePointerTarget == NULL)
             {
               printf("File[%s]creation/write failed! Please check whether the file path and name are entered correctly!\n", D_TargetFileNewName);
               printf("�ļ�[%s]����/д��ʧ�ܣ������ļ�·���������Ƿ�������ȷ��\n", D_TargetFileNewName);
               getchar();
               return 0;
             }

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
