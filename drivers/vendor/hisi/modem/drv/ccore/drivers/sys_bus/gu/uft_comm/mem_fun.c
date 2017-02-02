/**********************************************************************
 Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
  FileName: test.cpp
  Author:������ 	 ID: 56989      Version : 1.0         Date: 2009-11-5
  Description:     function dealing with memory       
  Version:         1.0
  Function List:   // ��Ҫ�������书��
	1. mem_init () ; //��ʼ��ָ���ڴ��
	2. mem_clr ()  ; //��ָ���ڴ������
	3. mem_copy () ; //����ָ���ڴ�ε���һλ��
	4. mem_comp () ; //�Ա�ָ���������ڴ��
	5. mem_test () ; //ʹ��������ݼ���ڴ��д�Ƿ��д���
    
  History:         // ��ʷ�޸ļ�¼
	  <author>  <ID>     <time>   <version >   <desc>
	  dlm       56989    09/11/05     1.0     dealing with memory   
**********************************************************************/
#include "mem_fun.h"
#include  "BasicFunc.h"
#include  "baseaddr.h"
//#include "./dmav300/dmav300.h"
//#define _UNIT_DEBUG

/***********************************************************
  Function:       mem_init() // ��������
  Description:    memory ��ʱ������// �������ܡ����ܵȵ�����
  Calls:          set32 ; set8 ; read32 ; read8 ; printf // �����������õĺ����嵥������������
  Called By:      // ���ñ������ĺ����嵥������������
  Table Accessed: ��// �����ʵı����������ǣ�������ݿ�����ĳ���
  Table Updated:  ��// ���޸ĵı����������ǣ�������ݿ�����ĳ���
  Input:          src_addr����ʼ��memory �ĵ�ַ��32bit 
                  num_byte����ʼ��memory �Ĵ�С����λbyte
                  init_data������memory �ĳ�ʼֵ
  Output:         �� // �����������˵����
  Return:         ��// ��������ֵ��˵��
  Others:         // ����˵��
***********************************************************/

int mem_init( UINT32 src_addr,    /*Memory Address*/
			   int     num_byte,   /* Number of Data in Byte*/
			   UINT32 init_data)   /* Data to initiate */
{
    int cnt1  ;
    int cnt2  ;
    //int cnt3  ;
    UINT32 write_data ;
    //UINT32 read_data;
    UINT8  init_data_byte ;
    //UINT8  read_data_byte ;
    UINT32 addr ;
    
    cnt1  = 0 ;
    cnt2  = 0 ;
    //cnt3  = 0 ;
    addr = src_addr ;
    write_data = init_data;
    
    /*�� ��src_addr Ϊ��ʼ��ַ����num_byte Ϊ��С��һ��memory ��д���ʱֵinit_data */
    for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
    {
        /*���memory �Ĵ�С�Ƿ�32bits �ı������������32bits �ı����������ռ�ʹ��8bits д������ȫ*/
        if(cnt1 >= 0x4)
        {
        	set32(addr, write_data++);//write_data);
            addr = addr + 0x4 ;
        }
        else
        {
            cnt2 = cnt1;
            init_data_byte = write_data  ; 
            while ( cnt2 )
            {
                set8(addr, init_data_byte);
                write_data = write_data >> 8 ;
                init_data_byte = write_data ;
                addr = addr + 0x1 ;
                cnt2 = cnt2 - 0x1 ;
            }
        }	
    }
    //addr = src_addr ;
    //write_data = init_data;

/*�����Ҫ�ж�memory ��ʼ���Ƿ���ȷ����define debug*/
//#ifdef _UNIT_DEBUG
    /*����ʼ�����memory ���жϳ�ʱ���Ƿ�ɹ�*/
    /*for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
    {
        if(cnt1 >= 0x4)
        {
            read_data = read32( addr );
            addr = addr + 0x4 ;
            if ( init_data++ != read_data )//( init_data != read_data )
            {
            	cnt3 = cnt3 + 0x4 ;
            }
        }
        else
        {       
            cnt2 = cnt1;
            while ( cnt2 )
            {
                read_data_byte = read8 ( addr );
                addr = addr + 0x1 ;
                cnt2 = cnt2 - 0x1 ;				
                init_data_byte = write_data ;
                write_data = write_data >> 8 ;
                if ( init_data_byte != read_data_byte )
                {
                    cnt3 = cnt3 + 0x1 ;
                }
            }
        }
    }       
            
    if ( 0 == cnt3 )
    {
    	printf("EDMAC: Memory Initiation OK!\n"); 
    }
    else
    {
    	printf("EDMAC: Memory Initiation FAILED!\n");
    	return 1;
    }	*/
    
//#endif
	return 0;
}

int mem_init_v9r1( UINT32 src_addr,    /*Memory Address*/
			   int     num_byte,   /* Number of Data in Byte*/
			   UINT32 init_data,
			   UINT32 inc_type)   /* Data to initiate */
{
    int cnt1  ;
    int cnt2  ;
    //int cnt3  ;
    UINT32 write_data ;
    //UINT32 read_data;
    UINT8  init_data_byte ;
    //UINT8  read_data_byte ;
    UINT32 addr ;
    
    cnt1  = 0 ;
    cnt2  = 0 ;
    //cnt3  = 0 ;
    addr = src_addr ;
    write_data = init_data;
    
    /*�� ��src_addr Ϊ��ʼ��ַ����num_byte Ϊ��С��һ��memory ��д���ʱֵinit_data */
    for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
    {
        /*���memory �Ĵ�С�Ƿ�32bits �ı������������32bits �ı����������ռ�ʹ��8bits д������ȫ*/
        if(cnt1 >= 0x4)
        {
        	if (inc_type == 1)
        	{
        		set32(addr, write_data++);//write_data);
        	}
        	else if (inc_type == 0)
        	{
        		set32(addr, init_data);
        	}
        	else
        	{
        		set32(addr, 0);
        	}
            addr = addr + 0x4 ;
        }
        else
        {
            cnt2 = cnt1;
            if (inc_type == 1)
            {
            	write_data = write_data;
            }
            else if (inc_type == 0)
            {
            	write_data = init_data;
            }
            else
            {
            	write_data = 0;
            }
            init_data_byte = write_data  ; 
            while ( cnt2 )
            {
                set8(addr, init_data_byte);
                write_data = write_data >> 8 ;
                init_data_byte = write_data ;
                addr = addr + 0x1 ;
                cnt2 = cnt2 - 0x1 ;
            }
        }	
    }
    //addr = src_addr ;
    //write_data = init_data;

/*�����Ҫ�ж�memory ��ʼ���Ƿ���ȷ����define debug*/
//#ifdef _UNIT_DEBUG
    /*����ʼ�����memory ���жϳ�ʱ���Ƿ�ɹ�*/
    /*for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
    {
        if(cnt1 >= 0x4)
        {
            read_data = read32( addr );
            addr = addr + 0x4 ;
            if ( init_data++ != read_data )//( init_data != read_data )
            {
            	cnt3 = cnt3 + 0x4 ;
            }
        }
        else
        {       
            cnt2 = cnt1;
            while ( cnt2 )
            {
                read_data_byte = read8 ( addr );
                addr = addr + 0x1 ;
                cnt2 = cnt2 - 0x1 ;				
                init_data_byte = write_data ;
                write_data = write_data >> 8 ;
                if ( init_data_byte != read_data_byte )
                {
                    cnt3 = cnt3 + 0x1 ;
                }
            }
        }
    }       
            
    if ( 0 == cnt3 )
    {
    	printf("EDMAC: Memory Initiation OK!\n"); 
    }
    else
    {
    	printf("EDMAC: Memory Initiation FAILED!\n");
    	return 1;
    }	*/
    
//#endif
	return 0;
}

/***********************************************************
  Function:       mem_clr() // ��������
  Description:    ��ָ��memory ���㺯��// �������ܡ����ܵȵ�����
  Calls:          set32 ; set8 ; read32 ; read8 ; printf // �����������õĺ����嵥������������
  Called By:      // ���ñ������ĺ����嵥������������
  Table Accessed: ��// �����ʵı����������ǣ�������ݿ�����ĳ���
  Table Updated:  ��// ���޸ĵı����������ǣ�������ݿ�����ĳ���
  Input:          src_addr����Ҫ������ڴ���׵�ַ��32bit 
				  num_byte����Ҫ������ڴ�γ��ȣ���λbyte
  Output:         �� // �����������˵����
  Return:         ��// ��������ֵ��˵��
  Others:         // ����˵��
***********************************************************/


int mem_clr( UINT32 src_addr,         /*Memory Address*/
			int     num_byte )    /*Number of Data to clear in Byte*/
{
    int cnt1  ;
    int cnt2  ;
#ifdef _UNIT_DEBUG	
    int cnt3 = 0  ;
#endif
    UINT32 addr ;
	
    cnt1 = 0 ;
    cnt2 = 0 ;
    addr = src_addr ; 
    

    
    /*��һ�� ��src_addr Ϊ��ʼ��ַ����num_byte Ϊ��С��memory ��ֵ���� */
    for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
    {
        if(cnt1 >= 0x4)
        {
            set32(addr, 0x0);
            addr = addr + 0x4 ;
        }
        else
        {
            cnt2 = cnt1;
            while ( cnt2 )
            {
                set8(addr, 0x0);
                addr = addr + 0x1 ;
                cnt2 = cnt2 - 0x1 ;
            }
        }
        	
    }
    
    addr = src_addr ; 
	
/*�����Ҫ�ж�memory ��ʼ���Ƿ���ȷ����define debug*/	
#ifdef _UNIT_DEBUG	

    /*��������memory ���ж�clear �����Ƿ�ɹ�*/
    for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
    {
        if(cnt1 >= 0x4)
        {
            read_data = read32( addr );
            addr = addr + 0x4 ;
            if ( 0x0 != read_data )
            {
            	cnt3 = cnt3 + 0x4 ;
            }
        }
        else
        {
            cnt2 = cnt1;
            while ( cnt2 )
            {
                read_data_byte = read8 ( addr );
                addr = addr + 0x1 ;
                cnt2 = cnt2 - 0x1 ;
                if ( 0x0 != read_data_byte )
                {
                    cnt3 = cnt3 + 0x1 ;
                }
            }
        }
    }
    
    if ( 0 == cnt3 )
    {
		//#ifdef _UNIT_DEBUG
		printf("Memory Clear OK!\n"); 
		return 0;
		//#endif
    }
    else
    {
        printf("Memory Clear FAILED!\n");
        return 1;
    }	
    
#endif	
    
   return 0;
}

/***********************************************************
  Function:       mem_copy() // ��������
  Description:    ����ָ���ڴ�ε���һλ�á�
  Calls:          set32 ; set8 ; printf // �����������õĺ����嵥������������
  Called By:      // ���ñ������ĺ����嵥������������
  Table Accessed: ��// �����ʵı����������ǣ�������ݿ�����ĳ���
  Table Updated:  ��// ���޸ĵı����������ǣ�������ݿ�����ĳ���
  Input:          src_addr��Դ�ڴ��ַ��32bit 
				  des_addr��Ŀ���ڴ��ַ��32bit 
				  num_byte����Ҫ���Ƶ��ڴ�ĳ��ȣ���λbyt
  Output:         �� // �����������˵����
  Return:         ��// ��������ֵ��˵��
  Others:         // ����˵��
***********************************************************/
void mem_copy( UINT32 src_addr,    /* Memory Source Address*/
			   UINT32 des_addr,    /* Memory Destination Address*/
			   int    num_byte)    /* Number of Data in Byte*/
{
int cnt1  ;
int cnt2  ;

UINT32  read_data ;
UINT8   read_data_byte ; 

cnt1 = 0 ;
cnt2 = 0 ;

/*��������������32bitsʹ��32bits ������д����������32bits��memoryʹ��8bits ������д����*/	
for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
{       
    if(cnt1 >= 0x4)
    {
        read_data = read32( src_addr );
        set32(des_addr , read_data );
        src_addr = src_addr + 0x4 ;
        des_addr = des_addr + 0x4 ;
    }
    else
    {
        cnt2 = cnt1;
        while ( cnt2 )
        {
            read_data_byte = read8 ( src_addr );
            set8(des_addr, read_data_byte );
            src_addr = src_addr + 0x1 ;
            des_addr = des_addr + 0x1 ;
            cnt2 = cnt2 - 0x1 ;
        }
    }
}
#ifdef _UNIT_DEBUG
    printf("Copy finish!\n"); 
#endif	

return;
}	
		 
/***********************************************************
  Function:       mem_comp() // ��������
  Description:    �Ա�ָ���������ڴ�Ρ�
  Calls:          read32 ; read8 ; printf // �����������õĺ����嵥������������
  Called By:      // ���ñ������ĺ����嵥������������
  Table Accessed: ��// �����ʵı����������ǣ�������ݿ�����ĳ���
  Table Updated:  ��// ���޸ĵı����������ǣ�������ݿ�����ĳ���
  Input:          addr1����Ҫ�Աȵĵ�ַ��1�׵�ַ��32bit 
				  addr2����Ҫ�Աȵĵ�ַ��2�׵�ַ��32bit 
				  num_byte���Ա��ڴ�εĳ��ȣ���λbyt
  Output:         �� // �����������˵����
  Return:         cnt3������memory �ϲ�ͬ���ݵĸ���
  Others:         ����ͨ���궨��debug ��ȷ���Ƿ��ӡ����memory �ϲ�ͬ���ݵľ��������
***********************************************************/
int mem_comp( UINT32 addr1,     
			  UINT32 addr2,     
			  UINT32 num_byte )    
{
    int cnt1  ;
    int cnt2  ;
    int cnt3  ;
    UINT32 read_data1 ;
    UINT32 read_data2 ;
    UINT8 read_data_byte1 ; 
    UINT8 read_data_byte2 ; 
    
    cnt1 = 0 ;
    cnt2 = 0 ;
    cnt3 = 0 ;
    	
    for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
    {
        if(cnt1 >= 0x4)
        {
            read_data1 = read32( addr1 );
            read_data2 = read32( addr2 );
            if ( read_data1 != read_data2 )
            {
                cnt3 = cnt3 + 0x1 ;
/*�ж��Ƿ��ӡ����memory �ϲ�ͬ���ݵľ������*/					
//#ifdef debug
                printf("error %d!\n" , cnt3 ); 
                printf("addr1=%x,data1=%x\n",addr1,read_data1);
                printf("addr2=%x,data2=%x\n",addr2,read_data2);
//#endif                      
            }
			/*else 
			{
				printf("Compare right!!\n");
			}*/
			
            addr1 = addr1 + 0x4 ;
            addr2 = addr2 + 0x4 ;
        }
        else
        {
            cnt2 = cnt1;
            while ( cnt2 )
            {
                read_data_byte1 = read8 ( addr1 );
                read_data_byte2 = read8 ( addr2 );
                if ( read_data_byte1 != read_data_byte2 )
                {
                    cnt3 = cnt3 + 0x1 ;			  
/*�ж��Ƿ��ӡ����memory �ϲ�ͬ���ݵľ������*/      	
//#ifdef _UNIT_DEBUG
                    printf("error %d!\n" , cnt3 );
                    printf("addr1=%x,data1=%x\n",addr1, read_data_byte1);
                    printf("addr2=%x,data2=%x\n",addr2, read_data_byte2);
//#endif
                 }
				/*else 
				{
					printf("Compare right!!\n");
				}*/
                 addr1 = addr1 + 0x1 ;
                 addr2 = addr2 + 0x1 ;			
                 cnt2 = cnt2 - 0x1 ;
            }
        }
			
    }
#ifdef _UNIT_DEBUG
    if ( 0 == cnt3 )
    {
        printf("Memory Compare OK!\n"); 
    }
    else
    {
        printf("Memory Compare FAILED!\n");
    }
#endif	
    return cnt3 ;
}

#if 0
/***********************************************************
  Function:       mem_comp() // ��������
  Description:    �Ա�ָ���������ڴ�Ρ�
  Calls:          read32 ; read8 ; printf // �����������õĺ����嵥������������
  Called By:      // ���ñ������ĺ����嵥������������
  Table Accessed: ��// �����ʵı����������ǣ�������ݿ�����ĳ���
  Table Updated:  ��// ���޸ĵı����������ǣ�������ݿ�����ĳ���
  Input:          addr1����Ҫ�Աȵĵ�ַ��1�׵�ַ��32bit 
				  addr2����Ҫ�Աȵĵ�ַ��2�׵�ַ��32bit 
				  num_byte���Ա��ڴ�εĳ��ȣ���λbyt
  Output:         �� // �����������˵����
  Return:         cnt3������memory �ϲ�ͬ���ݵĸ���
  Others:         ����ͨ���궨��debug ��ȷ���Ƿ��ӡ����memory �ϲ�ͬ���ݵľ��������
***********************************************************/
int edmac_mem_comp( UINT32 src_addr,     
			  UINT32 des_addr,     
			  UINT32 num_byte,
			  UINT32 trans_type)    
{
	int cnt1  ;
	int cnt2  ;
	int cnt3  ;
	UINT32 read_data1 ;
	UINT32 read_data2 ;
	UINT8 read_data_byte1 ; 
	UINT8 read_data_byte2 ; 
	UINT32 ch_state;
	UINT32 addr1;
	UINT32 addr2;
	
	addr1 = src_addr;
	addr2 = des_addr;
	
	cnt1 = 0 ;
	cnt2 = 0 ;
	cnt3 = 0 ;
	
	do
	{
		ch_state = read32(EDMAC_BASEADDR+CH_STAT);
	} 
	while (ch_state != 0);
	
	//printf("EDMAC: Memory Transmit complete\n");
    	
	for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
	{
		if(cnt1 >= 0x4)
		{
			read_data1 = read32( addr1 );
			read_data2 = read32( addr2 );
			if ( read_data1 != read_data2 )
			{
				cnt3 = cnt3 + 0x1 ;
/*�ж��Ƿ��ӡ����memory �ϲ�ͬ���ݵľ������*/					
//#ifdef debug
				printf("EDMAC error %d!\n" , cnt3 ); 
				printf("addr1=%x,data1=%x\n",addr1,read_data1);
				printf("addr2=%x,data2=%x\n",addr2,read_data2);
//#endif                      
			}
			addr1 = addr1 + 0x4 ;
			addr2 = addr2 + 0x4 ;
		}
		else
		{
			cnt2 = cnt1;
			while ( cnt2 )
			{
				read_data_byte1 = read8 ( addr1 );
				read_data_byte2 = read8 ( addr2 );
				if ( read_data_byte1 != read_data_byte2 )
				{
					cnt3 = cnt3 + 0x1 ;			  
/*�ж��Ƿ��ӡ����memory �ϲ�ͬ���ݵľ������*/      	
//#ifdef _UNIT_DEBUG
					printf("error %d!\n" , cnt3 );
					printf("addr1=%x,data1=%x\n",addr1, read_data_byte1);
					printf("addr2=%x,data2=%x\n",addr2, read_data_byte2);
//#endif
				 }
				 addr1 = addr1 + 0x1 ;
				 addr2 = addr2 + 0x1 ;			
				 cnt2 = cnt2 - 0x1 ;
			}
		}
			
	}
#ifdef _UNIT_DEBUG
	if ( 0 == cnt3 )
	{
		printf("Memory Compare OK!\n"); 
	}
	else
	{
		printf("Memory Compare FAILED!\n");
	}
#endif	
	if (cnt3 == 0)
	{
#ifdef V9R1_DEBUG
		if (trans_type == 0)
		{
			printf ("---- EDMAC OK ----\n");
		}
		else if(trans_type == 1)
		{
			printf ("---- BBP OK ----\n");
		}
#endif
		return 0;
	}
	else
	{
		if (trans_type == 0)
		{
			printf ("EDMAC ERROR\n");
		}
		else if(trans_type == 1)
		{
			printf ("BBP TRANSFER ERROR\n");
		}
		return 1;
	}
}
#endif

/***********************************************************
  Function:       mem_test() // ��������
  Description:    ʹ��������ݼ���ڴ��д�Ƿ��д���
  Calls:          set32; read32 ; srand; rand; printf // �����������õĺ����嵥������������
  Called By:      // ���ñ������ĺ����嵥������������
  Table Accessed: ��// �����ʵı����������ǣ�������ݿ�����ĳ���
  Table Updated:  ��// ���޸ĵı����������ǣ�������ݿ�����ĳ���
  Input:          src_addr������memory �ĵ�ַ��32bit 
				  num_byte������memory �ĳ��ȣ� ��λbyte
				  test_num�����Ĵ���
  Output:         �� // �����������˵����
  Return:         cnt2�����memory �ϴ���ĸ���
  Others:         ����ͨ���궨��debug ��ȷ���Ƿ��ӡ����memory �ϲ�ͬ���ݵľ��������
***********************************************************/

int mem_test(  UINT32 src_addr,    /* Memory Address*/
			   long int    num_byte,    /* Number of Data in Byte*/
			   int    test_num )   /*���Ĵ���*/
{
    long int cnt1 ;
    int cnt2 ;
    int cnt3 ;
    UINT32 data1 ;
    UINT32 data2 ;
    UINT32 read_data1 ; 
    UINT32 read_data2 ; 
    UINT32 addr1 ; 
    UINT32 addr2 ; 
    
    cnt1 = 0 ;
    cnt2 = 0 ;
    cnt3 = 0 ;

  //  srand((unsigned)time());
    
    for(cnt3 = test_num ; cnt3 >0 ; cnt3 = cnt3 - 0x1 )
    {
        addr1 = src_addr ;
        addr2 = src_addr + 0x4 ;
        for (cnt1 = num_byte ; cnt1 >0 ; cnt1 = cnt1 - 0x8)
        {
        /*    data1 = rand() ;	      
            data1 = data1 <<16;
            data1_low = rand() ;
            data1 = data1 | data1_low ;*/
			data1 = 0x5a5a5a5a;
            set32(addr1, data1); 
	
            if (cnt1 >4) 
                        {
     /*           data2 = rand() ;
                data2 = data2 <<16;
                data2_low = rand() ;
                data2 = data2 | data2_low ;*/
	          data2 = 0xa5a5a5a5;
                set32( addr2, data2);
            }
            
            read_data1 = read32( addr1);
            if ( read_data1 != data1)
            {
                cnt2 = cnt2 + 0x1 ;
            }
            addr1 = addr1 + 0x8 ;
            							
            if (cnt1 >4) 
            {
                read_data2 = read32( addr2);
                if ( read_data2 != data2)
                    {
                        cnt2 = cnt2 + 0x1 ;			
                    }
                    addr2 = addr2 + 0x8 ;
            }	
            	
        }
#ifdef _UNIT_DEBUG
            printf("test %x!\n",cnt3 ); 
#endif
        }
    return cnt2 ; 
}

/**********************************************************
	This function is used to Clear Memory 
**********************************************************/

void MemClrNoLog ( UINT32 addr,       //Memory Address
				   int total_byte,    //Number of Data to clear in Byte
				   UINT32 logaddr, 
				   int logbit                                        
				 )
{
	UINT32 result;
	int i,j=0;	

	for(i=0;i<total_byte;i=i+4)
	{
		set32(addr+(UINT32)i,0x0);
		result = read32(addr+(UINT32)i);
		if(result == 0x0)
		{ 
			j++; 
		}
		else
		{ 
			j=j; 
		}
	}
	if(j == total_byte/4)
	{
		setbits(logaddr, logbit, logbit, 1);
	}
	else
	{
		setbits(logaddr, logbit, logbit, 0);
	}

	return;
}

/**********************************************************
	This function is used to perform Result Checking 
	between two Memories without log message
**********************************************************/

void MemCompNoLog ( UINT32 addr1, //Address 1
					UINT32 addr2, //Address 2
					UINT32 length, //Number of data to Check in Byte 
					UINT32 logaddr, 
					int logbit
				  )
{
	unsigned int i,j;
	UINT32 rdata1,rdata2;
	j=0;

	  //  RegBitWrite(logaddr, logbit, logbit, 0);
	
	for(i=0;i<length;i=i+4)
	{
		rdata1=read32(addr1+i);
		rdata2=read32(addr2+i);
		if(rdata1==rdata2)
		{
			j++;
		}
		else
		{
			j=j;
			break;
		}
	}
	if(j==length/4)
		setbits(logaddr, logbit, logbit, 1);
	else 
		setbits(logaddr, logbit, logbit, 0);
	
	j=0;
	
	return;
}



int mem_byte_cmp(UINT32 src_addr,  UINT32 dest_addr,  UINT32 length)
{
	
	unsigned int check_flag=0;
	UINT32 cnt1;	
	UINT8 rdata1,rdata2;
		
	for( cnt1 = 0; cnt1 < length; cnt1++ )
	{
			rdata1 = read8(src_addr);
			rdata2 = read8(dest_addr);
			if( rdata1 != rdata2 )
			{
				printf("Error: src_addr = %x, des_addr = %x, src_data = %x, dest_data = %x\n", src_addr, dest_addr, rdata1, rdata2 );
				
				check_flag++;
			}
			
			src_addr++ ;
			dest_addr++ ;
	}
	
	if(check_flag == 0)
	{
		#ifdef _UNIT_DEBUG
	    printf("Compare OK!\n");
	    #endif
	    
	    return 0;
	}
	
	else
	{
		#ifdef _UNIT_DEBUG
		printf("Compare Fail!\n");
		#endif
		
		return 1;
	}
	
}

int mem_cmp(UINT32 src_addr,  UINT32 dest_addr,  UINT32 length)
{
	UINT32 i;
		
	UINT32 rdata1,rdata2;
	
	UINT32 data_len;
	
	if ((length%32)==0)
	{
		data_len  =  length/32;
	}
	else 
	{
		data_len  =  (length/32) + 1;
	}	
	for( i = 0; i < data_len; i = i+1 )
	{
			rdata1 = read32(src_addr);
			rdata2 = read32(dest_addr);
			if( rdata1 != rdata2 )
			{
				//set32(SMIM_BASEADDR,0x51525354);
				
				printf("Compare Error!!!!\n");
				printf("Compare Error: addr = %x, src_data = %x, corr_data = %x\n", src_addr, rdata1, rdata2 );
	 		    
				return 1;
			}			
			src_addr = src_addr + 4 ;
			
			dest_addr = dest_addr + 4 ;
	}

	return 0;	
}
#if 0
void ddr_write (UINT32 data_len)
{
	UINT32 i,j;
		
	UINT32 rdata1,rdata2;
	
	//UINT32 data_len;
	
	j = 0;
	
	//data_len = 1000000;
	
	for( j = 0; j < data_len; j = j+1 )
	{
		for( i = 0; i < 1000000; i = i+1 )
	    {
		    set32(MDDR_BASEADDR + 0x1300000 + i*4 ,i);
	    }
		printf("Write Complete!!\n");
    }
}
	
void ddr_read (UINT32 data_len)
{
	UINT32 i,j;
	
	UINT32 rdata1,rdata2;
	
	//UINT32 data_len;
	
	j = 0;
	
	//data_len = 1000000;
	
	for( j = 0; j < data_len; j = j+1 )
	{
		for( i = 0; i < 1000000; i = i+1 )
		{
			read32(MDDR_BASEADDR + 0x1300000 + i*4);
		}
		printf("Read Complete!!\n");
	}
}
#endif

