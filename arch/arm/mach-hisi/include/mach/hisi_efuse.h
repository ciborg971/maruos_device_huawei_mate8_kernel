#ifndef _HISILICON_EFUSE_H_
#define _HISILICON_EFUSE_H_

#define EFUSE_MAX_SIZE			2048
#define EFUSEC_GROUP_MAX_COUNT		(EFUSE_MAX_SIZE/32)

#define OK      			(0)
#define ERROR  				(-1)
#define ERROR_EXIT_PD			(-2)	/* �����˳�power downģʽ */
#define ERROR_ENTER_PD			(-3)	/* �����˳�power downģʽ */
#define ERROR_APB_PGM_DIS		(-4)	/* ��ǰeFusec��������д */
#define ERROR_EFUSEC_READ		(-5)	/* �������һ��eFuse������ */
#define ERROR_PRE_WRITE			(-6)	/* δ���Ԥ��д��λ */
#define ERROR_PG_OPERATION		(-7)	/* �������һ��eFuseд���� */
#define ERROR_SECURE_OS                 (-8)	/* ��ȫOSִ�д��� */

#define	HISI_EFUSE_READ_CHIPID		0x1000
#define	HISI_EFUSE_READ_DIEID		0x2000

/******************************************************************************
Function:	    bsp_efuse_write
Description:	    ��ָ��Wordsƫ�ƿ�ʼд��ָ��Words������eFuseֵ
Input:		    buf			- ������������Ҫд�뵽eFuse�е�ֵ
		    size		- ���������Ҫд���Words����
		    group		- �����������ָ����Wordsƫ�ƴ���ʼд�룬
					  ���б�ʾeFuse�������group
Output:		    none
Return:		    0: OK  ����: ERROR��
******************************************************************************/
extern int bsp_efuse_write(const unsigned int* buf,
			  const unsigned int group,
			  const unsigned int size);

/******************************************************************************
Function:	    bsp_efuse_read
Description:	    ��ָ��Wordsƫ�ƿ�ʼ��ȡָ��Words������eFuseֵ
Input:		    buf			- ����&�����������Ŷ�ȡ����eFuseֵ��
					  �ɵ��÷���������ڴ�
		    group		- �����������ָ����Wordsƫ�ƴ���ʼ��ȡ��
					  ���б�ʾeFuse�������group
		    size		- ���������Ҫ��ȡ��Words����
Output:		    buf			- �����������Ŷ�ȡ����eFuseֵ��
					  �ɵ��÷���������ڴ�
Return:		    0: OK  ����: ERROR��
******************************************************************************/
extern int bsp_efuse_read(unsigned int* buf,
			  const unsigned int group,
			  const unsigned int size);

#endif
