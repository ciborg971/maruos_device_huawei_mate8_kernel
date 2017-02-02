/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                               mp_sh_def.h
 *
 *  Project Code: VISP1.5
 *   Module Name: MP
 *  Date Created: 2005-09-30
 *        Author: songrujie
 *   Description: VISP3 MP component��macro define
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2005-09-28      songrujie       Create
 *  2006-03-31      ZhuKun          Adjust for D00663
 *  2006-04-21      ZhuKun          Adjust for D00876
 *
 *************************************************************************/
 
#ifndef _MP_SH_DEF_H_
#define _MP_SH_DEF_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* ÿ�δ�MP���ն�����ȡ�����ĵ���Ŀ; from 40 to 200 */
#define MP_GET_FROM_QUE                 200 

#define MSG_BASE_MP_SHOW                20
#define MSG_MP_DISP_GROUP               (MSG_BASE_MP_SHOW +1)   /*��ȡMP-group��MP��Ϣ*/
#define MSG_MP_DISP_FIRST_VA            (MSG_BASE_MP_SHOW +2)   /*��ȡ��һ��VA��MP��Ϣ*/
#define MSG_MP_DISP_NEXT_VA             (MSG_BASE_MP_SHOW +3)   /*��ȡ��һ��VA��MP��Ϣ*/

#define MP_DISP_IO_TIMEOUT_LIMIT        4000                    /* �ֲ�ʽshow�Ľӿڰ�ͬ��ȡ�ĳ�ʱʱ�� */

#define MSG_MP_GET_MULTILINK_DESCR      (MSG_BASE_MP_SHOW+5)    /*ȡ����ͨ�����󶨵ĸ��ӿڵ�������Ϣ*/
#define MSG_MP_MIB_MULTILINKTABLE_INFO  (MSG_BASE_MP_SHOW+6)    /*��ȡ��ͨ����Ϣ��*/
#define MSG_MP_MIB_MEMBERLINKTABLE_INFO (MSG_BASE_MP_SHOW+7)    /*��ȡ��ͨ����Ϣ��*/

/*IPCͨ����Ϣ����*/
#define MP_ADD_FATHER_INDEX             1
#define MP_DEL_FATHER_INDEX             2
#define MP_ADD_SON_INDEX                3
#define MP_DEL_SON_INDEX                4
#define MP_RESP_FATHER_INDEX_TO_VT      5
#define MP_RESP_FATHER_INDEX_TO_SON     6
/*-------------------------------------------------------------*/
/*              ������Ϣ��ʩ�¸��ݰ��������                 */
/*-------------------------------------------------------------*/
/* ����Up,Down�ĺ���ͬppp״̬���еĺ��� */
#define MSG_MP_FIND_FATHER_CHANEL       7
#define MSG_MP_NOTIFY_IO_FATHER_CHANEL  8
#define MSG_MP_SON_UP                   9
#define MSG_MP_SON_DOWN                 10
#define MSG_MP_CLOSE_SON                11
#define MSG_MP_OPEN_SON                 12
#define MSG_MP_FATHER_DOWN              13
#define MSG_MP_GET_DISCR_ADDR           14
#define MSG_MP_SEND_DISCR_ADDR          15

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _MP_SH_DEF_H_ */
