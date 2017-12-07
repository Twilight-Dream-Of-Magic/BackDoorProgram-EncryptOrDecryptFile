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
            FILE *FilePointerSource, *FilePointerTarget;    //Ҫ�򿪵��ļ���ָ��
            char buffer[1024];               //�����������ڴ�Ŵ��ļ���ȡ������

            int FileByteData,                //ÿ�δ��ļ��ж�ȡ���ֽ���
                RTNOC,                       //ѭ������
                KeyLength = strlen(E_KEY),   //��Կ�ĳ���
                KeyLength2 = strlen(E_KEY2),
                KeyLength3 = strlen(E_KEY3);

             FilePointerSource = fopen(E_SourceFileName, "rb"); //�Զ����Ʒ�ʽ��ȡ�ļ�
             if(FilePointerSource== NULL)
             {
               printf("file[%s]failed to open, please check whether the file path and name are entered correctly! \n", E_SourceFileName);
               printf("�ļ�[%s]��ʧ�ܣ������ļ�·���������Ƿ�������ȷ��\n", E_SourceFileName);
               getchar();
               return 0;
             }

             FilePointerTarget = fopen(E_TargetFileNewName, "wb"); //�Զ����Ʒ�ʽд���ļ�
             if(FilePointerTarget== NULL)
             {
               printf("File[%s]creation/write failed! Please check whether the file path and name are entered correctly!\n", FilePointerTarget);
               printf("�ļ�[%s]����/д��ʧ�ܣ������ļ�·���������Ƿ�������ȷ��\n", FilePointerTarget);
               getchar();
               return 0;
             }
/*�����㷨��ʼ*/
            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0 ) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڽ����������
                 {
                 buffer[RTNOC] ^= E_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0 ) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڽ����������
                 {
                 buffer[RTNOC] ^= E_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0 ) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڽ����������
                 {
                 buffer[RTNOC] ^= E_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

/*�����㷨����*/

      fclose(FilePointerSource);
          fclose(FilePointerTarget);

    return 1;
        }

        int RunDecryptFile(char *D_SourceFileName, char *D_KEY, char *D_KEY2, char *D_KEY3, char *D_TargetFileNewName)
        {
            FILE *FilePointerSource, *FilePointerTarget;    //Ҫ�򿪵��ļ���ָ��
            char buffer[1024];               //�����������ڴ�Ŵ��ļ���ȡ������

            int FileByteData,                //ÿ�δ��ļ��ж�ȡ���ֽ���
                RTNOC,                       //ѭ������
                KeyLength = strlen(D_KEY),   //��Կ�ĳ���
                KeyLength2 = strlen(D_KEY2),
                KeyLength3 = strlen(D_KEY3);

             FilePointerSource = fopen(D_SourceFileName, "rb"); //�Զ����Ʒ�ʽ��ȡ�ļ�
             if(FilePointerSource== NULL)
             {
               printf("file[%s]failed to open, please check whether the file path and name are entered correctly! \n", D_SourceFileName);
               printf("�ļ�[%s]��ʧ�ܣ������ļ�·���������Ƿ�������ȷ��\n", D_SourceFileName);
               getchar();
               return 0;
             }

             FilePointerTarget = fopen(D_TargetFileNewName, "wb"); //�Զ����Ʒ�ʽд���ļ�
             if(FilePointerTarget== NULL)
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
            while((FileByteData = fread(buffer, 1, KeyLength, FilePointerSource)) > 0 ) //���ϵش��ļ��ж�ȡ KeyLength ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڽ����������
                 {
                 buffer[RTNOC] ^= D_KEY[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength2, FilePointerSource)) > 0 ) //���ϵش��ļ��ж�ȡ KeyLength2 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڽ����������
                 {
                 buffer[RTNOC] ^= D_KEY2[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }
            while((FileByteData = fread(buffer, 1, KeyLength3, FilePointerSource)) > 0 ) //���ϵش��ļ��ж�ȡ KeyLength3 ���ȵ����ݣ����浽buffer��ֱ���ļ�����
            {
                 for(RTNOC = 0; RTNOC < FileByteData; RTNOC++) //��buffer�е��������ֽڽ����������
                 {
                 buffer[RTNOC] ^= D_KEY3[RTNOC];
                 }
              fwrite(buffer, 1, FileByteData, FilePointerTarget); //��buffer�е�����д���ļ�
            }

/*�����㷨����*/

          fclose(FilePointerSource);
          fclose(FilePointerTarget);

        return 1;
        }