

/*
 * �뽫�����ģ��껻�ɸ�ͷ�ļ�����ģ���ģ��ꡣ
 * ���磬������·��Э��ģ��PPP��ͷ�ļ�ppp_var.h��Ӧ�ø�Ϊ��
 *
 *    #if( VRP_MODULE_LINK_PPP == VRP_YES )
 *
 * ���øú��Ŀ����Ϊ��ͨ���ֹ������ڱ���ʱ�ü�VRP�������ÿ���ļ�������
 * ���е���Щģ��궼��VRP3.0�����ù���Ա������ͷ�ļ�vrpcfg.h�ж��塣
 */

#ifndef    _TCPIP_IF_INDEX_H_
#define    _TCPIP_IF_INDEX_H_
/*
 * �ú�Ķ��巽ʽΪ��"_" + "ȫ����д���ļ���" + "_" + "H" + "_"
 * ���磬������·��Э��ģ��PPP��ͷ�ļ�ppp_var.h��Ӧ�ö���Ϊ��
 *
 *    #ifndef    _PPP_VAR_H_
 *    #define    _PPP_VAR_H_
 *
 * ����ú��Ŀ����ȥ���ظ�����һ��ͷ�ļ��Ŀ�����
 */

#ifdef __cplusplus
extern "C"{
#endif
/*
 * Ϊ��ʹVRP3.0��ӦC++�����������Ĵ�����ÿ���ļ�������
 */


/************************************************************************
 * ����������д��ͷ�ļ��ľ�������                                       *
 * ......                                                               *
 * ......                                                               *
 * ......                                                               *
 ************************************************************************/
/*����η�Χ������ֵ������ಥģ��ר�ã�
������Щ�����е�ǰ6λ��ʾ�ۺŵ�λ����1��
���ۺ��ǲ�������ô�����ֵģ����һ��ӿ�
������ʹ���������ֵ��  pengjimei  2002/06/05*/
#define IFINDEX_MCAST_RESERVED_BEGIN     0xFC000000
#define IFINDEX_MCAST_RESERVED_END       0xFC00000F

IFNET_S *IF_GetIfByIndex(ULONG ulIfIndex);

ULONG IF_GetFirstIfIndex(ULONG * pIndex);
ULONG IF_GetNextIfIndex( ULONG ulIndex, ULONG * pNextIndex ) ;

#ifdef __cplusplus
}
#endif    /* end of __cplusplus */

#endif    /* end of _TEMPLETE_H_ */



