

#ifndef  __BST_DBG_LOG_H__
#define  __BST_DBG_LOG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Typedefine.h"
#include "BST_PAL_Log.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define BST_RLS_LOG(MsgString) \
    BST_PAL_ERROR_LOG(  "<Bastet Info>   " MsgString "\r\n")
                    
#define BST_RLS_LOG1(MsgString,Para1) \
    BST_PAL_ERROR_LOG1( "<Bastet Info>   " MsgString "\r\n",\
                        (Para1) )
                    
#define BST_RLS_LOG2(MsgString,Para1,Para2) \
    BST_PAL_ERROR_LOG2( "<Bastet Info>   " MsgString "\r\n",\
                        (Para1), (Para2) )
                    
#define BST_RLS_LOG3(MsgString,Para1,Para2,Para3) \
    BST_PAL_ERROR_LOG3( "<Bastet Info>   " MsgString "\r\n",\
                        (Para1), (Para2), (Para3) )
                    
#define BST_RLS_LOG4(MsgString,Para1,Para2,Para3,Para4) \
    BST_PAL_ERROR_LOG4( "<Bastet Info>   " MsgString "\r\n",\
                        (Para1), (Para2), (Para3), (Para4) )
                    
#define BST_DBG_LOG(MsgString) \
    BST_PAL_INFO_LOG(  "<Bastet Info>   " MsgString "\r\n")
                    
#define BST_DBG_LOG1(MsgString,Para1) \
    BST_PAL_INFO_LOG1( "<Bastet Info>   " MsgString "\r\n",\
                       (Para1) )
                    
#define BST_DBG_LOG2(MsgString,Para1,Para2) \
    BST_PAL_INFO_LOG2( "<Bastet Info>   " MsgString "\r\n",\
                       (Para1), (Para2) )
                    
#define BST_DBG_LOG3(MsgString,Para1,Para2,Para3) \
    BST_PAL_INFO_LOG3( "<Bastet Info>   " MsgString "\r\n",\
                       (Para1), (Para2), (Para3) )
                    
#define BST_DBG_LOG4(MsgString,Para1,Para2,Para3,Para4) \
    BST_PAL_INFO_LOG4( "<Bastet Info>   " MsgString "\r\n",\
                       (Para1), (Para2), (Para3), (Para4) )

#define BST_ASSERT_NULL( ptr ) \
                    if ( BST_NULL_PTR == ptr )\
                    {\
                        BST_PAL_ERROR_LOG2("<Bastet Error>  " "%s,%d " #ptr "\r\n",\
                                    __FILE__,__LINE__);\
                        return;\
                    }
                    

#define BST_ASSERT_NULL_RTN( ptr, ret ) \
                    if ( BST_NULL_PTR == ptr )\
                    {\
                        BST_PAL_ERROR_LOG2("<Bastet Error>  " "%s,%d " #ptr "\r\n",\
                                    __FILE__,__LINE__);\
                        return ret;\
                    }
                    

#define BST_ASSERT_0( data_0 ) \
                    if ( 0U == data_0 )\
                    {\
                        BST_PAL_ERROR_LOG2("<Bastet Error>  " "%s,%d " #data_0 "\r\n",\
                                    __FILE__,__LINE__);\
                        return;\
                    }
                    
#define BST_ASSERT_0_RTN( data_0, ret ) \
                    if ( 0U == data_0 )\
                    {\
                        BST_PAL_ERROR_LOG2("<Bastet Error>  " "%s,%d " #data_0 "\r\n",\
                                    __FILE__,__LINE__);\
                        return ret;\
                    }
                    

#define BST_ASSERT_NORM( exp ) \
                    if ( (exp) )\
                    {\
                        BST_PAL_ERROR_LOG2("<Bastet Error>  " "%s,%d " #exp "\r\n",\
                                    __FILE__,__LINE__);\
                        return;\
                    }
                    

#define BST_ASSERT_NORM_RTN( exp, ret ) \
                    if ( (exp) )\
                    {\
                        BST_PAL_ERROR_LOG2("<Bastet Error>  " "%s,%d " #exp "\r\n",\
                                    __FILE__,__LINE__);\
                        return ret;\
                    }
                    

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  8 ��������
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif
