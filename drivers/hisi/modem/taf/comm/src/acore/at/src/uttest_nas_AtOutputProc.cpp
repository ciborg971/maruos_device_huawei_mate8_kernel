#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtOutputProc.h"

//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;


//˵��������������gtest+�������׺Ͳ����������ֲ�����Ϊ��
//      ������ú�gtest��ͬ�Ĺؼ��֣����ⲻ��Ҫ���鷳
//      gtest�ṩ EXPECT �� ASSERT ����,���庬����Կ���Ƭ�����׺궼��һһ��Ӧ�ģ�������EXPECTΪ��

//1���ȶԲ������� EXPECT_TRUE��EXPECT_FALSE/ASSERT_TRUE
//2���Ƚ����� EXPECT_EQ EXPECT_NE
//3���Ƚ��ַ��� EXPECT_STREQ
//4������ʧ�������Ϣ ADD_FAILUREd
//5�����óɹ���ʧ�� SUCCEED FAIL
//6���Զ����ʽ EXPECT_PRED_FORMAT3
//7�����������������TRUE EXPECT_PRED1
//8�������ͱȽ� EXPECT_FLOAT_EQ EXPECT_PRED_FORMAT2 ASSERT_PRED_FORMAT2
//9�����ͼ�� StaticAssertTypeEq
//10������3�ֲ��Լ����¼�
//11����ȡ������������ test_case_name()
//12���Ƚ��쳣 EXPECT_THROW
//13���ṹ�����ͱȽ�ASSERT_SAME_DATA ASSERT_SAME_MEMORY


class Test_At_SendData: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_SendData,Test_At_SendData_001)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = AT_MAX_CLIENT_NUM;

    ulRlst = At_SendData(ucIndex, 0, VOS_NULL_PTR, 0);
    EXPECT_EQ(ulRlst, AT_FAILURE);
}


TEST_F(Test_At_SendData,Test_At_SendData_002)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = 0;

    gastAtClientTab[ucIndex].DataMode = AT_DATA_BUTT_MODE;

    ulRlst = At_SendData(ucIndex, 0, VOS_NULL_PTR, 0);

    EXPECT_EQ(ulRlst, AT_FAILURE);
}



TEST_F(Test_At_SendData,Test_At_SendData_003)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = 0;

    /* ��ǰ����δʹ�� */
    gastAtClientTab[ucIndex].ucUsed = AT_CLIENT_NULL;

    gastAtClientTab[ucIndex].DataMode = AT_IP_DATA_MODE;

    ulRlst = At_SendData(ucIndex, AT_PPP_DATA_MODE, VOS_NULL_PTR, 0);

    EXPECT_EQ(ulRlst, AT_FAILURE);
}
TEST_F(Test_At_SendData,Test_At_SendData_004)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = 0;

    /* ��ǰ����ʹ�� */
    gastAtClientTab[ucIndex].ucUsed = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode = AT_IP_DATA_MODE;

    /* AT_COM_USER */
    gastAtClientTab[ucIndex].UserType  = AT_USBCOM_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    /* ��������1�� */
    //MOCKER(AT_MsgBufferPut)
    //    .expects(exactly(1));

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, VOS_NULL_PTR, 0);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SendData,Test_At_SendData_005)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = 0;

    gastAtClientTab[ucIndex].ucUsed    = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode  = AT_IP_DATA_MODE;

    /* AT_CTR_USER */
    gastAtClientTab[ucIndex].UserType  = AT_CTR_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode      = AT_DATA_MODE;

    /* ��������1�� */
    //MOCKER(AT_CtrMsgBufferPut)
    //    .expects(exactly(1));

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, VOS_NULL_PTR, 0);

    GlobalMockObject::verify();
}
TEST_F(Test_At_SendData,Test_At_SendData_006)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = 0;

    gastAtClientTab[ucIndex].ucUsed    = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode  = AT_IP_DATA_MODE;

    gastAtClientTab[ucIndex].UserType  = AT_MODEM_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode      = AT_DATA_MODE;

    /* ��������1�� */
    MOCKER(AT_SendDataToModem)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, VOS_NULL_PTR, 0);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SendData,Test_At_SendData_007)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = 0;

    gastAtClientTab[ucIndex].ucUsed    = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode  = AT_IP_DATA_MODE;

    gastAtClientTab[ucIndex].UserType  = AT_NDIS_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode      = AT_DATA_MODE;

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, VOS_NULL_PTR, 0);

    EXPECT_EQ(ulRlst, AT_FAILURE);

}
TEST_F(Test_At_SendData,Test_At_SendData_008)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = 0;

    gastAtClientTab[ucIndex].ucUsed    = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode  = AT_IP_DATA_MODE;

    gastAtClientTab[ucIndex].UserType  = AT_BUTT_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode      = AT_DATA_MODE;

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, VOS_NULL_PTR, 0);

    EXPECT_EQ(ulRlst, AT_FAILURE);

}
TEST_F(Test_At_SendData,Test_At_SendData_009)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = 0;

    gastAtClientTab[ucIndex].ucUsed    = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode  = AT_IP_DATA_MODE;

    gastAtClientTab[ucIndex].UserType  = AT_HSIC1_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode      = AT_DATA_MODE;

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, VOS_NULL_PTR, 0);

    EXPECT_EQ(ulRlst, AT_FAILURE);

}
TEST_F(Test_At_SendData,Test_At_SendData_010)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = AT_CLIENT_TAB_APP1_INDEX;

    gastAtClientTab[ucIndex].ucUsed    = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode  = AT_IP_DATA_MODE;

    gastAtClientTab[ucIndex].UserType  = AT_APP_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode      = AT_DATA_MODE;

    MOCKER(APP_VCOM_Send)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, VOS_NULL_PTR, 0);

    EXPECT_EQ(ulRlst, AT_SUCCESS);

}

#if (FEATURE_ON == FEATURE_AT_HSIC)
TEST_F(Test_At_SendData,Test_At_SendData_011)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           aucData[3] = {'O', 'K', 0};

    ucIndex = 0;
    usDataLen = 2;

    gastAtClientTab[ucIndex].ucUsed    = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode  = AT_IP_DATA_MODE;

    gastAtClientTab[ucIndex].UserType  = AT_HSIC4_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode      = AT_DATA_MODE;

    MOCKER(AT_SendDataToHsic)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror(aucData), eq(usDataLen));

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, aucData, usDataLen);

    EXPECT_EQ(ulRlst, AT_SUCCESS);
}
TEST_F(Test_At_SendData,Test_At_SendData_012)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;
    VOS_UINT8                           ucNvId;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           ucMuxSupportFlg;
    VOS_UINT8                           aucData[3] = {'O', 'K', 0};

    ucMuxSupportFlg = VOS_TRUE;

    ucIndex = AT_CLIENT_TAB_MUX1_INDEX;
    ucNvId  = en_NV_Item_Mux_Support_Flg;
    usDataLen = 2;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(ucNvId), outBoundP(&ucMuxSupportFlg))
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(MUX_DlciDlDataSend)
        .stubs()
        .with(any(), mirror(aucData), eq(usDataLen));

    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue(VOS_FALSE));

    MOCKER(VOS_SmBCreate)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(NV_GetLength)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    /* AT PID INIT*/
    At_PidInit(VOS_IP_INITIAL);

    gastAtClientTab[ucIndex].ucUsed    = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode  = AT_IP_DATA_MODE;

    gastAtClientTab[ucIndex].UserType  = AT_MUX1_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode      = AT_DATA_MODE;

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, aucData, usDataLen);

    EXPECT_EQ(ulRlst, AT_SUCCESS);

    GlobalMockObject::verify();
}
#endif


class Test_AT_DisplayResultData: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_001)
{
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    gastAtClientTab[ucIndex].UserType = AT_COM_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    AT_DisplayResultData(ucIndex, 0);
}


TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_002)
{
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    gastAtClientTab[ucIndex].UserType = AT_USBCOM_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    /* ��������1�� */
    MOCKER(Sock_Send)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)0));

    AT_DisplayResultData(ucIndex, 0);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_003)
{
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    gastAtClientTab[ucIndex].UserType = AT_CTR_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    /* ��������1�� */
    MOCKER(DMS_WriteData)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_OK));

    AT_DisplayResultData(ucIndex, 0);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_004)
{
    VOS_UINT8                           ucIndex;
    TTF_MEM_ST                stDataMem;

    stDataMem.pData = (VOS_UINT8 *)malloc(1);

    ucIndex = 0;

    gastAtClientTab[ucIndex].UserType = AT_MODEM_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    /* ��������1�� */
    MOCKER(AT_SendDataToModem)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    AT_DisplayResultData(ucIndex, 0);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_005)
{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    g_alAtUdiHandle[ucIndex] = UDI_INVALID_HANDLE;

    /* ��������1�� */
    MOCKER(AT_HSUART_SendDlData)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    AT_DisplayResultData(ucIndex, 0);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_006)
{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_NDIS_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_NDIS_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    /* ��������1�� */

    AT_DisplayResultData(ucIndex, 0);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_007)
{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_APP1_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_APP_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    /* ��������1�� */
    MOCKER(APP_VCOM_Send)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_DisplayResultData(ucIndex, 0);

    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_AT_HSIC)
TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_008)

{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_HSIC1_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_HSIC1_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    /* ��������1�� */
   // MOCKER(APP_VCOM_Send)
     //   .expects(never());

    AT_DisplayResultData(ucIndex, 0);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_009)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucMuxSupportFlg;
    VOS_UINT16                          usNvId;
    VOS_UINT16                          usLen;
    VOS_UINT8                           aucData[3] = {'O', 'K', 0};

    ucMuxSupportFlg = VOS_TRUE;

    ucIndex = AT_CLIENT_TAB_MUX1_INDEX;
    usNvId  = en_NV_Item_Mux_Support_Flg;
    usLen   = 2;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(usNvId), outBoundP(&ucMuxSupportFlg, sizeof(ucMuxSupportFlg)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(MUX_DlciDlDataSend)
        .stubs()
        .with(any(), mirror(aucData), eq(usLen))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(VOS_SmBCreate)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(NV_GetLength)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));


    /* AT PID INIT*/
    At_PidInit(VOS_IP_INITIAL);

    gastAtClientTab[ucIndex].UserType = AT_MUX1_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    gstAtSendDataBuffer[0] = 'O';
    gstAtSendDataBuffer[1] = 'K';

    AT_DisplayResultData(ucIndex, 2);

    GlobalMockObject::verify();
}
#endif
TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_010)
{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_UART_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_UART_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    g_alAtUdiHandle[ucIndex] = UDI_INVALID_HANDLE;

    /* ��������1�� */
    MOCKER(AT_UART_SendDlData)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    AT_DisplayResultData(ucIndex, 0);

    GlobalMockObject::verify();
}
class Test_AT_DisplaySelResultData: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();
    }

    void TearDown()
    {
    }

};

TEST_F(Test_AT_DisplaySelResultData,Test_AT_DisplaySelResultData_01)
{
    gastAtClientTab[0].Mode     = AT_CMD_MODE;
    gastAtClientTab[0].UserType = AT_USBCOM_USER;

    gucAtPortSel = 0;

    /* ��������һ�� */
    MOCKER(Sock_Send)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_OK));

    AT_DisplaySelResultData(0, 0);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_DisplaySelResultData,Test_AT_DisplaySelResultData_02)
{
    gastAtClientTab[0].Mode     = AT_CMD_MODE;
    gastAtClientTab[0].UserType = AT_CTR_USER;

    gucAtPortSel = 0;

    /* ��������һ�� */
    MOCKER(DMS_WriteData)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_OK));

    AT_DisplaySelResultData(0, 0);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_DisplaySelResultData,Test_AT_DisplaySelResultData_03)
{
    TTF_MEM_ST                          stDataMem;

    stDataMem.pData = (VOS_UINT8 *)malloc(1);

    gastAtClientTab[0].Mode     = AT_CMD_MODE;
    gastAtClientTab[0].UserType = AT_MODEM_USER;

    gucAtPortSel = 1;

    /* ��������һ�� */
    MOCKER(AT_SendDataToModem)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    AT_DisplaySelResultData(0, 0);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_DisplaySelResultData,Test_AT_DisplaySelResultData_04)
{
    gastAtClientTab[0].Mode     = AT_CMD_MODE;
    gastAtClientTab[0].UserType = AT_APP_USER;

    /* ��������һ�� */
    MOCKER(APP_VCOM_Send)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_DisplaySelResultData(0, 0);

    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_NDIS)
TEST_F(Test_AT_DisplaySelResultData,Test_AT_DisplaySelResultData_05)
{
    gastAtClientTab[0].Mode     = AT_CMD_MODE;
    gastAtClientTab[0].UserType = AT_NDIS_USER;

    /* ��������һ�� */
    MOCKER(DMS_WriteData)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_DisplaySelResultData(0, 0);

    GlobalMockObject::verify();
}
#endif

#if((FEATURE_ON == FEATURE_GNA)||(FEATURE_ON == FEATURE_RNIC))
TEST_F(Test_AT_DisplaySelResultData,Test_AT_DisplaySelResultData_06)
{
    gastAtClientTab[0].Mode     = AT_CMD_MODE;
    gastAtClientTab[0].UserType = AT_APP_USER;

    /* ��������һ�� */
    MOCKER(APP_VCOM_Send)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_DisplaySelResultData(0, 0);

    GlobalMockObject::verify();
}
#endif
TEST_F(Test_AT_DisplaySelResultData,Test_AT_DisplaySelResultData_07)
{
    gastAtClientTab[0].Mode     = AT_CMD_MODE;
    gastAtClientTab[0].UserType = AT_HSIC3_USER;


    AT_DisplaySelResultData(1, 0);

    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_AT_HSIC)

TEST_F(Test_AT_DisplaySelResultData, Test_AT_DisplaySelResultData_08)
{
    gastAtClientTab[0].Mode     = AT_CMD_MODE;
    gastAtClientTab[0].UserType = AT_HSIC4_USER;

    /* ��������1�� */
    MOCKER(AT_SendDataToHsic)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    AT_DisplaySelResultData(1, 0);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_DisplaySelResultData,Test_AT_DisplaySelResultData_09)
{
    VOS_UINT32                          ulNvId;
    VOS_UINT16                          usLen;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucMuxSupportFlg;
    VOS_UINT8                           aucData[3] = {'O', 'K', 0};

    ucMuxSupportFlg = VOS_TRUE;

    ucIndex = AT_CLIENT_TAB_MUX1_INDEX;
    ulNvId  = en_NV_Item_Mux_Support_Flg;
    usLen   = 2;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(ulNvId), outBoundP(&ucMuxSupportFlg))
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(MUX_DlciDlDataSend)
        .stubs()
        .with(any(), mirror(aucData), eq(usLen))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_CheckHsicUser)
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(VOS_SmBCreate)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(NV_GetLength)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    /* AT PID INIT*/
    At_PidInit(VOS_IP_INITIAL);

    gastAtClientTab[ucIndex].Mode     = AT_CMD_MODE;
    gastAtClientTab[ucIndex].UserType = AT_MUX1_USER;

    gstAtSendDataBuffer[0] = 'O';
    gstAtSendDataBuffer[1] = 'K';

    AT_DisplaySelResultData(2, ucIndex);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_DisplaySelResultData, Test_AT_DisplaySelResultData_010)
{
    // ��������
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].Mode = AT_CMD_MODE;
    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;

    // MOCKER����
    MOCKER(AT_HSUART_SendDlData)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // ���ñ��⺯��
    AT_DisplaySelResultData(4, ucIndex);

    // ִ�м��
    GlobalMockObject::verify();
}
#endif


class Test_At_FormatResultData: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(VOS_SmP)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(VOS_SmV)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_FormatResultData, Test_At_FormatResultData_001)
{
    // ��������
    VOS_CHAR                           *pcExpectStr = (VOS_CHAR *)"\r\nNO CARRIER\r\n";
    VOS_UINT32                          ulReturnCode;
    VOS_UINT8                           unIndex;

    // ������ʼ��
    ulReturnCode = AT_NO_CARRIER;
    unIndex      = AT_CLIENT_TAB_HSUART_INDEX;

    // ��ʼ��ȫ�ֱ���
    gstAtCombineSendData[unIndex].usBufLen = 0;
    gstAtSendData.usBufLen  = 0;
    gucAtVType              = AT_V_ENTIRE_TYPE;
    gucAtXType              = 1;

    // MOCKER����
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_FINISH));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(unIndex), any(), eq((VOS_UINT16)VOS_StrLen(pcExpectStr)));

    MOCKER(AT_ProcFormatResultMsc)
        .expects(exactly(1))
        .with(eq(unIndex), eq(ulReturnCode));

    // ���ñ��⺯��
    At_FormatResultData(unIndex, ulReturnCode);

    // ִ�м��

    GlobalMockObject::verify();
}

#if 1

TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_002)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_RRETURN_CODE_BUTT + 1;

    //���ȫ�ֱ�����ʼ��

    // MOCKER����
    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_003)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_CMD_NOT_SUPPORT;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;

    // MOCKER����
    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_004)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_TOO_MANY_PARA;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;

    // MOCKER����
    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_005)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_WAIT_SMS_INPUT;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;

    // MOCKER����
    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_006)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_CMS_UNASSIGNED_UNALLOCATED_NUMBER;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_ENTIRE_TYPE;

    // MOCKER����
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_FINISH));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_007)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_CMS_UNASSIGNED_UNALLOCATED_NUMBER;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ERROR_CODE;
    gucAtVType = AT_V_BREVITE_TYPE;

    // MOCKER����
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_FINISH));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_008)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_CMS_UNASSIGNED_UNALLOCATED_NUMBER;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ERROR_CONTENT;
    gucAtVType = AT_V_BREVITE_TYPE;

    // MOCKER����
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_FINISH));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_010)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_CONNECT;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtVType = AT_V_ENTIRE_TYPE;
    gastAtClientTab[1].Mode = AT_DATA_MODE;
    gastAtClientTab[1].DataMode = AT_PPP_DATA_MODE;
    gucAtXType = 1;

    // MOCKER����
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_FINISH));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(AT_ProcFormatResultMsc)
        .expects(exactly(1));

    MOCKER(AT_EventReport)
        .stubs()
        .with(eq(WUEPS_PID_AT), eq(NAS_OM_EVENT_DCE_UP_DCD),eq(VOS_NULL_PTR), eq(NAS_OM_EVENT_NO_PARA));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}



TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_011)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_NO_CARRIER;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtVType = AT_V_ENTIRE_TYPE;
    gastAtClientTab[1].Mode = AT_DATA_MODE;
    gastAtClientTab[1].DataMode = AT_PPP_DATA_MODE;
    gastAtClientTab[1].UserType = AT_MODEM_USER;
    gucAtXType = 1;

    // MOCKER����
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_FINISH));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(AT_ProcFormatResultMsc)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_012)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_CONNECT;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtVType = AT_V_ENTIRE_TYPE;
    gastAtClientTab[1].Mode = AT_DATA_MODE;
    gastAtClientTab[1].DataMode = AT_CSD_DATA_MODE;
    gastAtClientTab[1].UserType = AT_MODEM_USER;
    gucAtXType = 1;

    // MOCKER����
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_FINISH));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(AT_ProcFormatResultMsc)
        .expects(exactly(1));

    MOCKER(AT_EventReport)
        .stubs()
        .with(eq(WUEPS_PID_AT), eq(NAS_OM_EVENT_DCE_UP_DCD),eq(VOS_NULL_PTR), eq(NAS_OM_EVENT_NO_PARA));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_013)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_CME_SIM_BUSY;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_ENTIRE_TYPE;

    // MOCKER����
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_ABORT));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));
    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_014)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_CME_SIM_BUSY;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ERROR_CODE;
    gucAtVType = AT_V_ENTIRE_TYPE;

    // MOCKER����
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_ABORT));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}



TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_015)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_CME_SIM_BUSY;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ERROR_CONTENT;
    gucAtVType = AT_V_ENTIRE_TYPE;

    // MOCKER����
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_ABORT));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_016)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_CMS_UNASSIGNED_UNALLOCATED_NUMBER;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_ENTIRE_TYPE;

    // MOCKER����
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_CONTINUE));

    MOCKER(AT_ParseCmdOver)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_017)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_CMS_UNASSIGNED_UNALLOCATED_NUMBER;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_ENTIRE_TYPE;

    // MOCKER����
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_CONTINUE));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_018)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_OK;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_BREVITE_TYPE;

    // MOCKER����
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_FINISH));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_019)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_CME_SIM_FAILURE;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_BREVITE_TYPE;

    // MOCKER����
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_ABORT));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_020)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_OK;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_BREVITE_TYPE;

    // MOCKER����
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_CONTINUE));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_021)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_OK;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_ENTIRE_TYPE;

    // MOCKER����
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_CONTINUE));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_022)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_OK;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_ENTIRE_TYPE;

    // MOCKER����
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_CONTINUE));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_023)
{
    //��������
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //������ʼ��
    ucIndex = 1;
    ReturnCode = AT_WAIT_XML_INPUT;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[1].usBufLen = 10;

    // MOCKER����
    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //ִ�м��
    At_FormatResultData(ucIndex, ReturnCode);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

#endif


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_024)
{
    VOS_UINT8                           aucDataAt[50];
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;
    VOS_UINT8                           ucAtCmdNotSupportStr2[]   = "COMMAND NOT SUPPORT";

    usLength  = 0;
    ulTmp     = 0;


    /* ��ʼ��ȫ�ֱ��� */
    MOCKER(V_StopRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)0));

    AT_STOP_TIMER_CMD_READY(0);
    At_ResetCombinParseInfo(0);

    PS_MEM_CPY((VOS_CHAR*)gaucAtCmdNotSupportStr,
               (VOS_CHAR*)ucAtCmdNotSupportStr2,
               sizeof(ucAtCmdNotSupportStr2));

    PS_MEM_SET(&gstAtSendData, 0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));
    pgucAtSndCodeAddr = &gstAtSendData.aucBuffer[3];

    /* ���������� */
    PS_MEM_SET(aucDataAt, 0x00, sizeof(aucDataAt));

    pucDataAt = aucDataAt;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    ulTmp = VOS_StrLen((VOS_CHAR *)ucAtCmdNotSupportStr2);
    PS_MEM_CPY( (pucDataAt + usLength), (VOS_CHAR *)ucAtCmdNotSupportStr2, ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    PS_MEM_SET(&gstAtSendData,    0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));

    PS_MEM_SET(&g_stParseContext, 0x00, sizeof(g_stParseContext));

    At_FormatResultData(0, AT_CMD_NOT_SUPPORT);

    EXPECT_STREQ((char*)pgucAtSndCodeAddr, (char*)aucDataAt);
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_025)
{
    VOS_UINT8                           aucDataAt[50];
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;

    usLength  = 0;
    ulTmp     = 0;


    /* ��ʼ��ȫ�ֱ��� */
    AT_STOP_TIMER_CMD_READY(0);
    At_ResetCombinParseInfo(0);
    PS_MEM_SET(&gstAtSendData, 0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));
    pgucAtSndCodeAddr = &gstAtSendData.aucBuffer[3];


    /* ���������� */
    PS_MEM_SET(aucDataAt, 0x00, sizeof(aucDataAt));

    pucDataAt = aucDataAt;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    ulTmp = VOS_StrLen((VOS_CHAR *)gaucAtTooManyParaStr);
    PS_MEM_CPY( (pucDataAt + usLength), (VOS_CHAR *)gaucAtTooManyParaStr, ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    PS_MEM_SET(&gstAtSendData,    0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));

    PS_MEM_SET(&g_stParseContext, 0x00, sizeof(g_stParseContext));

    At_FormatResultData(0, AT_TOO_MANY_PARA);

    EXPECT_STREQ((char*)pgucAtSndCodeAddr, (char*)aucDataAt);
}



TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_026)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    TAF_AGENT_SYS_MODE_STRU             stSysMode;

    usLength  = 0;
    ucIndex   = 0;

    /* ��ʼ��ȫ�ֱ��� */
    AT_STOP_TIMER_CMD_READY(0);
    At_ResetCombinParseInfo(0);
    PS_MEM_SET(&gstAtSendData, 0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));
    PS_MEM_SET(&g_stParseContext, 0x00, sizeof(g_stParseContext));
    gucAtVType        = AT_V_ENTIRE_TYPE;
    gucAtXType        = 1;
    g_stParseContext[ucIndex].stCombineCmdInfo.usTotalNum = 0;
    gastAtClientTab[ucIndex].Mode                         = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode                     = AT_PPP_DATA_MODE;
    g_stDialConnectDisplayRate.ucDpaConnectRate           = 7;

    PS_MEM_SET(&stSysMode, 0x00, sizeof(stSysMode));
	/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    stSysMode.enRatType     = TAF_MMA_RAT_GSM;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    stSysMode.enSysSubMode  = TAF_SYS_SUBMODE_EDGE;

    /* MOCKER���� */
    MOCKER(TAF_AGENT_GetSysMode)
        .expects(exactly(1))
        /*.with(eq((VOS_UINT16)ucIndex), outBoundP((void *)&stSysMode, (VOS_UINT32)sizeof(stSysMode)))*/
        .will(returnValue((VOS_UINT32)VOS_OK));

    At_FormatResultData(ucIndex, AT_CONNECT);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}


class Test_At_BufferorSendResultData: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();
    }

    void TearDown()
    {
    }

};

TEST_F(Test_At_BufferorSendResultData,Test_At_BufferorSendResultData_01)
{
    VOS_UINT8                           ucIndex = 0;
    VOS_UINT8                           aucData[5000];
    VOS_UINT16                          usLength = 4001;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[ucIndex].usBufLen = 1000;

    //MOCKER
    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //���ñ��⺯��
    At_BufferorSendResultData(ucIndex, aucData, usLength);

    //ִ�м��
    EXPECT_EQ(4001, gstAtCombineSendData[ucIndex].usBufLen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_BufferorSendResultData,Test_At_BufferorSendResultData_02)
{
    VOS_UINT8                           ucIndex = 0;
    VOS_UINT8                           aucData[5000];
    VOS_UINT16                          usLength = 200;

    //���ȫ�ֱ�����ʼ��
    gstAtCombineSendData[ucIndex].usBufLen = 1000;

    //MOCKER
    MOCKER(At_SendResultData)
        .expects(never());

    //���ñ��⺯��
    At_BufferorSendResultData(ucIndex, aucData, usLength);

    //ִ�м��
    EXPECT_EQ(1200, gstAtCombineSendData[ucIndex].usBufLen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}



#ifdef NAS_STUB

class Test_At_SndResult_Stub: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();
    }

    void TearDown()
    {
    }

};

TEST_F(Test_At_SndResult_Stub, Test_At_SndResult_Stub_01)
{
    const char          cWarning[] = "At_SndResult_Stub :pData is null ptr!";
    TAF_UINT8 ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;
    VOS_UINT32  ulRet;

    MOCKER(DIAG_LogReport)
        .stubs()
        .with(any(), any(), any(), any(), any(), mirror(cWarning,strlen(cWarning) + 1));

    MOCKER(Ps_SendMsg)
        .expects(never());

    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue(VOS_NULL_PTR));

/*  pData = aucCmdString;
    usLen = sizeof(aucCmdString);*/

    At_SndResult_Stub(ucIndex, pData, usLen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_SndResult_Stub, Test_At_SndResult_Stub_02)
{
    const char          cWarning[] = "At_SndResult_Stub ulLength = 0";
    TAF_UINT8 ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;
    VOS_UINT32  ulRet;

    MOCKER(DIAG_LogReport)
        .stubs()
        .with(any(), any(), any(), any(), any(), mirror(cWarning,strlen(cWarning) + 1));

    MOCKER(Ps_SendMsg)
        .expects(never());

/*  pData = aucCmdString;
    usLen = sizeof(aucCmdString);*/

    At_SndResult_Stub(ucIndex, pData, usLen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_SndResult_Stub, Test_At_SndResult_Stub_03)
{
    const char          cWarning[] = "At_SndResult_Stub ulLength > AT_COM_BUFF_LEN";
    TAF_UINT8 ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen = AT_COM_BUFF_LEN + 1;
    VOS_UINT32  ulRet;

    MOCKER(DIAG_LogReport)
        .stubs()
        .with(any(), any(), any(), any(), any(), mirror(cWarning,strlen(cWarning) + 1));

    MOCKER(Ps_SendMsg)
        .expects(never());

/*  pData = aucCmdString;
    usLen = sizeof(aucCmdString);*/

    At_SndResult_Stub(ucIndex, pData, usLen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_SndResult_Stub, Test_At_SndResult_Stub_04)
{
    const char          cWarning[] = "At_SndResult_Stub:ERROR:Alloc Msg";
    TAF_UINT8           ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;
    VOS_UINT32  ulRet;

    MOCKER(DIAG_LogReport)
        .stubs()
        .with(any(), any(), any(), any(), any(), mirror(cWarning,strlen(cWarning) + 1));

    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue(VOS_NULL_PTR));

    MOCKER(Ps_SendMsg)
        .expects(never());

    pData = aucCmdString;
    usLen = sizeof(aucCmdString);

    At_SndResult_Stub(ucIndex, pData, usLen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_SndResult_Stub, Test_At_SndResult_Stub_05)
{
    const char          cWarning[] = "At_SndResult_Stub:ERROR:VOS_SendMsg";
    TAF_UINT8           ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;
    VOS_UINT32  ulRet;

    MOCKER(DIAG_LogReport)
        .stubs()
        .with(any(), any(), any(), any(), any(), mirror(cWarning,strlen(cWarning) + 1));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    pData = aucCmdString;
    usLen = sizeof(aucCmdString);

    At_SndResult_Stub(ucIndex, pData, usLen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_SndResult_Stub, Test_At_SndResult_Stub_06)
{
    TAF_UINT8           ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;
    VOS_UINT32  ulRet;

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    pData = aucCmdString;
    usLen = sizeof(aucCmdString);

    At_SndResult_Stub(ucIndex, pData, usLen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}



TEST_F(Test_At_SendResultData,Test_At_SendResultData_001)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                          *pData;
    VOS_UINT16                          usLen;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    pData = (VOS_UINT8*)malloc(sizeof(VOS_UINT8));
    usLen = 9;

    MOCKER(AT_SendBroadCastResultData).expects(exactly(1)).with(eq(ucIndex),any(),any());

    At_SendResultData(ucIndex, pData, usLen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

#endif

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

class Test_AT_SendBroadCastResultData: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();
    }

    void TearDown()
    {
    }

};

TEST_F(Test_AT_SendBroadCastResultData,Test_AT_SendBroadCastResultData_001)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                          *pData;
    VOS_UINT16                          usLen;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_1;
    pData = (VOS_UINT8*)malloc(sizeof(VOS_UINT8));
    usLen = 9;

    MOCKER(VOS_SmBCreate)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_GetLength)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    At_PidInit(VOS_IP_INITIAL);
    pstAtClientCtx = AT_GetClientCtxAddr(AT_CLIENT_TAB_PCUI_INDEX);
    pstAtClientCtx->stClientConfiguration.ucReportFlg = VOS_FALSE;

    pstAtClientCtx = AT_GetClientCtxAddr(AT_CLIENT_TAB_CTRL_INDEX);
    pstAtClientCtx->stClientConfiguration.ucReportFlg = VOS_FALSE;

    pstAtClientCtx = AT_GetClientCtxAddr(AT_CLIENT_TAB_APP5_INDEX);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    AT_SendBroadCastResultData(ucIndex, pData, usLen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif


class Test_AT_SmsStartRingTe: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitUartCtx();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_SmsStartRingTe, Test_AT_SmsStartRingTe_001)
{
    // ��������
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;

    // ������ʼ��
    pstRiStateInfo                      = AT_GetUartRiStateInfo();

    // ��ʼ��ȫ�ֱ���
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;;
    pstRiStateInfo->ulSmsRiOutputCount  = 0;

    // MOCKER����

    // ���ñ��⺯��
    AT_SmsStartRingTe(VOS_TRUE);

    // ִ�м��
    EXPECT_EQ(1, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SmsStartRingTe, Test_AT_SmsStartRingTe_002)
{
    // ��������
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    // ��ʼ��ȫ�ֱ���
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_FALSE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_BUTT;;
    pstRiStateInfo->ulSmsRiOutputCount  = 1;

    // MOCKER����
    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hSmsRiTmrHdl)),
              eq(pstRiCfgInfo->ulSmsRiOnInterval),
              eq(ulTmrName),
              eq(ulTmrParam),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    AT_SmsStartRingTe(VOS_FALSE);

    // ִ�м��
    EXPECT_EQ(1, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_SMS, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


class Test_AT_SmsStopRingTe: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitUartCtx();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_SmsStopRingTe, Test_AT_SmsStopRingTe_001)
{
    // ��������
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    // ��ʼ��ȫ�ֱ���
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_SMS;
    pstRiStateInfo->enSmsRiTmrStatus    = AT_TIMER_STATUS_RUNNING;
    pstRiStateInfo->ulSmsRiOutputCount  = 1;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER����
    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq(ulTmrName), eq(&(pstRiStateInfo->hSmsRiTmrHdl)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    AT_SmsStopRingTe();

    // ִ�м��
    EXPECT_EQ(1, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(VOS_FALSE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_BUTT, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_STOP, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SmsStopRingTe, Test_AT_SmsStopRingTe_002)
{
    // ��������
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    // ��ʼ��ȫ�ֱ���
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_SMS;
    pstRiStateInfo->enSmsRiTmrStatus    = AT_TIMER_STATUS_STOP;
    pstRiStateInfo->ulSmsRiOutputCount  = 1;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_LOW);

    // MOCKER����
    MOCKER(AT_StopRelTimer)
        .expects(never());

    // ���ñ��⺯��
    AT_SmsStopRingTe();

    // ִ�м��
    EXPECT_EQ(0, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(VOS_FALSE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_BUTT, pstRiStateInfo->enType);
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


class Test_AT_RcvTiSmsRiExpired: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitUartCtx();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_RcvTiSmsRiExpired, Test_AT_RcvTiSmsRiExpired_001)
{
    // ��������
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    stMsg.ulName                        = ulTmrName;
    stMsg.ulPara                        = ulTmrParam;

    // ��ʼ��ȫ�ֱ���
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_FALSE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_BUTT;;
    pstRiStateInfo->ulSmsRiOutputCount  = 0;
    pstRiStateInfo->enSmsRiTmrStatus    = AT_TIMER_STATUS_STOP;;

    // MOCKER����
    MOCKER(AT_SmsRingOff)
        .expects(never());
    MOCKER(AT_SmsStopRingTe)
        .expects(never());

    // ���ñ��⺯��
    At_TimeOutProc(&stMsg);

    // ִ�м��
    EXPECT_EQ(VOS_FALSE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_BUTT, pstRiStateInfo->enType);
    EXPECT_EQ(0, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(AT_TIMER_STATUS_STOP, pstRiStateInfo->enSmsRiTmrStatus);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTiSmsRiExpired, Test_AT_RcvTiSmsRiExpired_002)
{
    // ��������
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    stMsg.ulName                        = ulTmrName;
    stMsg.ulPara                        = ulTmrParam;

    // ��ʼ��ȫ�ֱ���
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_SMS;;
    pstRiStateInfo->ulSmsRiOutputCount  = 1;
    pstRiStateInfo->enSmsRiTmrStatus    = AT_TIMER_STATUS_RUNNING;;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER����
    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hSmsRiTmrHdl)),
              eq(pstRiCfgInfo->ulSmsRiOffInterval),
              eq(ulTmrName),
              eq(ulTmrParam),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    At_TimeOutProc(&stMsg);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_SMS, pstRiStateInfo->enType);
    EXPECT_EQ(1, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTiSmsRiExpired, Test_AT_RcvTiSmsRiExpired_003)
{
    // ��������
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    stMsg.ulName                        = ulTmrName;
    stMsg.ulPara                        = 0;

    // ��ʼ��ȫ�ֱ���
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_SMS;;
    pstRiStateInfo->ulSmsRiOutputCount  = 1;
    pstRiStateInfo->enSmsRiTmrStatus    = AT_TIMER_STATUS_RUNNING;;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_LOW);

    // MOCKER����
    MOCKER(AT_StopRelTimer)
        .stubs()
        .with(eq(ulTmrName), eq(&(pstRiStateInfo->hSmsRiTmrHdl)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    At_TimeOutProc(&stMsg);

    // ִ�м��
    EXPECT_EQ(VOS_FALSE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_BUTT, pstRiStateInfo->enType);
    EXPECT_EQ(0, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(AT_TIMER_STATUS_STOP, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTiSmsRiExpired, Test_AT_RcvTiSmsRiExpired_004)
{
    // ��������
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    stMsg.ulName                        = ulTmrName;
    stMsg.ulPara                        = ulTmrParam;

    // ��ʼ��ȫ�ֱ���
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_SMS;;
    pstRiStateInfo->ulSmsRiOutputCount  = 2;
    pstRiStateInfo->enSmsRiTmrStatus    = AT_TIMER_STATUS_RUNNING;;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_LOW);

    // MOCKER����
    MOCKER(AT_StopRelTimer)
        .stubs()
        .with(eq(ulTmrName), eq(&(pstRiStateInfo->hSmsRiTmrHdl)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hSmsRiTmrHdl)),
              eq(pstRiCfgInfo->ulSmsRiOnInterval),
              eq(ulTmrName),
              eq(ulTmrParam),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    At_TimeOutProc(&stMsg);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_SMS, pstRiStateInfo->enType);
    EXPECT_EQ(1, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTiSmsRiExpired, Test_AT_RcvTiSmsRiExpired_005)
{
    // ��������
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    stMsg.ulName                        = ulTmrName;
    stMsg.ulPara                        = ulTmrParam;

    // ��ʼ��ȫ�ֱ���
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    pstRiCfgInfo->ulSmsRiOffInterval    = 0;
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_SMS;;
    pstRiStateInfo->ulSmsRiOutputCount  = 2;
    pstRiStateInfo->enSmsRiTmrStatus      = AT_TIMER_STATUS_RUNNING;;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER����
    MOCKER(AT_StopRelTimer)
        .stubs()
        .with(eq(ulTmrName), eq(&(pstRiStateInfo->hSmsRiTmrHdl)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hSmsRiTmrHdl)),
              eq(pstRiCfgInfo->ulSmsRiOnInterval),
              eq(ulTmrName),
              eq(ulTmrParam),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    At_TimeOutProc(&stMsg);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_SMS, pstRiStateInfo->enType);
    EXPECT_EQ(1, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


class Test_AT_GetRiStatusByCallId: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitUartCtx();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_GetRiStatusByCallId, Test_AT_GetRiStatusByCallId_001)
{
    // ��������
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    AT_UART_RI_STATUS_ENUM_UINT8        enRiStatus;
    VOS_UINT8                           ucCallId;

    // ������ʼ��
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    ucCallId                            = 1;

    // ��ʼ��ȫ�ֱ���
    pstRiStateInfo->aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_RINGING;

    // MOCKER����

    // ���ñ��⺯��
    enRiStatus = AT_GetRiStatusByCallId(ucCallId);

    // ִ�м��
    EXPECT_EQ(AT_UART_RI_STATUS_RINGING, enRiStatus);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetRiStatusByCallId, Test_AT_GetRiStatusByCallId_002)
{
    // ��������
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    AT_UART_RI_STATUS_ENUM_UINT8        enRiStatus;
    VOS_UINT8                           ucCallId;

    // ������ʼ��
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    ucCallId                            = 8;

    // ��ʼ��ȫ�ֱ���
    pstRiStateInfo->aenVoiceRiStatus[1] = AT_UART_RI_STATUS_RINGING;

    // MOCKER����

    // ���ñ��⺯��
    enRiStatus = AT_GetRiStatusByCallId(ucCallId);

    // ִ�м��
    EXPECT_EQ(AT_UART_RI_STATUS_STOP, enRiStatus);

    GlobalMockObject::verify();
}


class Test_AT_VoiceStartRingTe: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(V_StartRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(V_StopRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        AT_InitUartCtx();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_VoiceStartRingTe, Test_AT_VoiceStartRingTe_001)
{
    // ��������
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;

    // ������ʼ��
    ucCallId                            = 8;

    // ��ʼ��ȫ�ֱ���
    pstRiStateInfo                      = AT_GetUartRiStateInfo();

    // MOCKER����
    MOCKER(AT_SmsStopRingTe)
        .expects(never());
    MOCKER(AT_VoiceRingOn)
        .expects(never());

    // ���ñ��⺯��
    AT_VoiceStartRingTe(ucCallId);

    // ִ�м��
    EXPECT_EQ(VOS_FALSE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_BUTT, pstRiStateInfo->enType);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_VoiceStartRingTe, Test_AT_VoiceStartRingTe_002)
{
    // ��������
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;

    // ������ʼ��
    ucCallId                            = 1;

    // ��ʼ��ȫ�ֱ���
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;;
    pstRiStateInfo->aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_RINGING;
    pstRiStateInfo->ulSmsRiOutputCount  = 0;

    // MOCKER����
    MOCKER(AT_VoiceRingOn)
        .expects(never());

    // ���ñ��⺯��
    AT_VoiceStartRingTe(ucCallId);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);
    EXPECT_EQ(AT_UART_RI_STATUS_RINGING, pstRiStateInfo->aenVoiceRiStatus[ucCallId]);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_VoiceStartRingTe, Test_AT_VoiceStartRingTe_003)
{
    // ��������
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    ucCallId                            = 1;
    AT_SET_VOICE_RI_TMR_NAME(ulTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulTmrParam, ucIndex, ucCallId);

    // ��ʼ��ȫ�ֱ���
    pstRiStateInfo                      = AT_GetUartRiStateInfo();

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER����
    MOCKER(AT_SmsStopRingTe)
        .expects(never());
    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hVoiceRiTmrHdl)),
              eq(pstRiCfgInfo->ulVoiceRiOnInterval),
              eq(ulTmrName),
              eq(ulTmrParam),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    AT_VoiceStartRingTe(ucCallId);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_VoiceStartRingTe, Test_AT_VoiceStartRingTe_004)
{
    // ��������
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    ucCallId                            = 1;
    AT_SET_VOICE_RI_TMR_NAME(ulTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulTmrParam, ucIndex, ucCallId);

    // ��ʼ��ȫ�ֱ���
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_SMS;;
    pstRiStateInfo->ulSmsRiOutputCount  = 1;
    pstRiStateInfo->enSmsRiTmrStatus    = AT_TIMER_STATUS_RUNNING;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER����
    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hVoiceRiTmrHdl)),
              eq(pstRiCfgInfo->ulVoiceRiOnInterval),
              eq(ulTmrName),
              eq(ulTmrParam),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    AT_VoiceStartRingTe(ucCallId);

    // ִ�м��
    EXPECT_EQ(1, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_STOP, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enVoiceRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


class Test_AT_VoiceStopRingTe: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(V_StartRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(V_StopRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        AT_InitUartCtx();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_VoiceStopRingTe, Test_AT_VoiceStopRingTe_001)
{
    // ��������
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucCallId                            = 8;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // ��ʼ��ȫ�ֱ���
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;;
    pstRiStateInfo->enVoiceRiTmrStatus  = AT_TIMER_STATUS_RUNNING;;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER����
    MOCKER(AT_StopRelTimer)
        .expects(never());
    MOCKER(AT_SmsStartRingTe)
        .expects(never());

    // ���ñ��⺯��
    AT_VoiceStopRingTe(ucCallId);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enVoiceRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_VoiceStopRingTe, Test_AT_VoiceStopRingTe_002)
{
    // ��������
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucCallId                            = 8;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // ��ʼ��ȫ�ֱ���
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_SMS;;
    pstRiStateInfo->enSmsRiTmrStatus    = AT_TIMER_STATUS_RUNNING;;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER����
    MOCKER(AT_StopRelTimer)
        .expects(never());
    MOCKER(AT_SmsStartRingTe)
        .expects(never());

    // ���ñ��⺯��
    AT_VoiceStopRingTe(ucCallId);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_SMS, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_VoiceStopRingTe, Test_AT_VoiceStopRingTe_003)
{
    // ��������
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucCallId                            = 1;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // ��ʼ��ȫ�ֱ���
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;;
    pstRiStateInfo->enVoiceRiTmrStatus  = AT_TIMER_STATUS_RUNNING;
    pstRiStateInfo->aenVoiceRiStatus[2] = AT_UART_RI_STATUS_RINGING;;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER����
    MOCKER(AT_StopRelTimer)
        .expects(never());
    MOCKER(AT_SmsStartRingTe)
        .expects(never());

    // ���ñ��⺯��
    AT_VoiceStopRingTe(ucCallId);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enVoiceRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_VoiceStopRingTe, Test_AT_VoiceStopRingTe_004)
{
    // ��������
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulVoiceTmrName;
    VOS_UINT32                          ulVoiceTmrPara;
    VOS_UINT32                          ulSmsTmrName;
    VOS_UINT32                          ulSmsTmrPara;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    ucCallId                            = 1;

    AT_SET_VOICE_RI_TMR_NAME(ulVoiceTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulVoiceTmrPara, ucIndex, ucCallId);
    AT_SET_SMS_RI_TMR_NAME(ulSmsTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulSmsTmrPara, ucIndex);

    // ��ʼ��ȫ�ֱ���
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;;
    pstRiStateInfo->enVoiceRiTmrStatus  = AT_TIMER_STATUS_RUNNING;;
    pstRiStateInfo->aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_RINGING;;
    pstRiStateInfo->ulSmsRiOutputCount  = 1;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER����
    MOCKER(AT_StopRelTimer)
        .stubs()
        .with(eq(ulVoiceTmrName),
              eq(&(pstRiStateInfo->hVoiceRiTmrHdl)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hSmsRiTmrHdl)),
              eq(pstRiCfgInfo->ulSmsRiOnInterval),
              eq(ulSmsTmrName),
              eq(ulSmsTmrPara),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    AT_VoiceStopRingTe(ucCallId);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_SMS, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_TIMER_STATUS_STOP, pstRiStateInfo->enVoiceRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


class Test_AT_RcvTiVoiceRiExpired: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitUartCtx();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_RcvTiVoiceRiExpired, Test_AT_RcvTiVoiceRiExpired_001)
{
    // ��������
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    ucCallId                            = 1;

    AT_SET_VOICE_RI_TMR_NAME(ulTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulTmrParam, ucIndex, ucCallId);

    stMsg.ulName                        = ulTmrName;
    stMsg.ulPara                        = ucCallId;

    AT_SET_VOICE_RI_TMR_NAME(ulTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulTmrParam, ucIndex, ucCallId);

    // ��ʼ��ȫ�ֱ���
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_FALSE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_BUTT;;
    pstRiStateInfo->enVoiceRiTmrStatus  = AT_TIMER_STATUS_STOP;;
    pstRiStateInfo->aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_STOP;
    pstRiStateInfo->ulVoiceRiCycleCount = 0;

    // MOCKER����
    MOCKER(AT_VoiceRingOff)
        .expects(never());
    MOCKER(AT_VoiceStopRingTe)
        .expects(never());
    MOCKER(AT_VoiceRingOn)
        .expects(never());

    // ���ñ��⺯��
    At_TimeOutProc(&stMsg);

    // ִ�м��
    EXPECT_EQ(VOS_FALSE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_BUTT, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_STOP, pstRiStateInfo->enVoiceRiTmrStatus);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTiVoiceRiExpired, Test_AT_RcvTiVoiceRiExpired_002)
{
    // ��������
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    ucCallId                            = 1;

    AT_SET_VOICE_RI_TMR_NAME(ulTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulTmrParam, ucIndex, ucCallId);

    stMsg.ulName                        = ulTmrName;
    stMsg.ulPara                        = ucCallId;

    // ��ʼ��ȫ�ֱ���
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;;
    pstRiStateInfo->enVoiceRiTmrStatus  = AT_TIMER_STATUS_RUNNING;
    pstRiStateInfo->aenVoiceRiStatus[2] = AT_UART_RI_STATUS_RINGING;
    pstRiStateInfo->ulVoiceRiCycleCount = 0;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER����
    MOCKER(AT_VoiceRingOff)
        .expects(never());
    MOCKER(AT_VoiceStopRingTe)
        .expects(never());
    MOCKER(AT_VoiceRingOn)
        .expects(never());

    // ���ñ��⺯��
    At_TimeOutProc(&stMsg);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enVoiceRiTmrStatus);
    EXPECT_EQ(AT_UART_RI_STATUS_RINGING, pstRiStateInfo->aenVoiceRiStatus[2]);
    EXPECT_EQ(0, pstRiStateInfo->ulVoiceRiCycleCount);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTiVoiceRiExpired, Test_AT_RcvTiVoiceRiExpired_003)
{
    // ��������
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulVoiceTmrName;
    VOS_UINT32                          ulVoiceTmrPara;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    ucCallId                            = 1;

    AT_SET_VOICE_RI_TMR_NAME(ulVoiceTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulVoiceTmrPara, ucIndex, ucCallId);

    stMsg.ulName                        = ulVoiceTmrName;
    stMsg.ulPara                        = ulVoiceTmrPara;

    // ��ʼ��ȫ�ֱ���
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    pstRiCfgInfo->ucVoiceRiCycleTimes   = 10;
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;;
    pstRiStateInfo->enVoiceRiTmrStatus  = AT_TIMER_STATUS_RUNNING;
    pstRiStateInfo->aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_RINGING;
    pstRiStateInfo->ulVoiceRiCycleCount = 0;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER����
    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hVoiceRiTmrHdl)),
              eq(pstRiCfgInfo->ulVoiceRiOffInterval),
              eq(ulVoiceTmrName),
              eq(ulVoiceTmrPara),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    At_TimeOutProc(&stMsg);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enVoiceRiTmrStatus);
    EXPECT_EQ(AT_UART_RI_STATUS_RINGING, pstRiStateInfo->aenVoiceRiStatus[ucCallId]);
    EXPECT_EQ(0, pstRiStateInfo->ulVoiceRiCycleCount);
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTiVoiceRiExpired, Test_AT_RcvTiVoiceRiExpired_004)
{
    // ��������
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulVoiceTmrName;
    VOS_UINT32                          ulVoiceTmrPara;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    ucCallId                            = 1;
    AT_SET_VOICE_RI_TMR_NAME(ulVoiceTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulVoiceTmrPara, ucIndex, ucCallId);

    stMsg.ulName                        = ulVoiceTmrName;
    stMsg.ulPara                        = ulVoiceTmrPara;

    // ��ʼ��ȫ�ֱ���
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    pstRiCfgInfo->ucVoiceRiCycleTimes   = 10;
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;
    pstRiStateInfo->aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_RINGING;
    pstRiStateInfo->enVoiceRiTmrStatus  = AT_TIMER_STATUS_RUNNING;
    pstRiStateInfo->ulVoiceRiCycleCount = 0;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_LOW);

    // MOCKER����
    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hVoiceRiTmrHdl)),
              eq(pstRiCfgInfo->ulVoiceRiOnInterval),
              eq(ulVoiceTmrName),
              eq(ulVoiceTmrPara),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    At_TimeOutProc(&stMsg);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enVoiceRiTmrStatus);
    EXPECT_EQ(AT_UART_RI_STATUS_RINGING, pstRiStateInfo->aenVoiceRiStatus[ucCallId]);
    EXPECT_EQ(1, pstRiStateInfo->ulVoiceRiCycleCount);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTiVoiceRiExpired, Test_AT_RcvTiVoiceRiExpired_005)
{
    // ��������
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulVoiceTmrName;
    VOS_UINT32                          ulVoiceTmrPara;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    ucCallId                            = 1;

    AT_SET_VOICE_RI_TMR_NAME(ulVoiceTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulVoiceTmrPara, ucIndex, ucCallId);

    stMsg.ulName                        = ulVoiceTmrName;
    stMsg.ulPara                        = ulVoiceTmrPara;

    // ��ʼ��ȫ�ֱ���
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    pstRiCfgInfo->ucVoiceRiCycleTimes   = 10;
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;
    pstRiStateInfo->enVoiceRiTmrStatus  = AT_TIMER_STATUS_RUNNING;
    pstRiStateInfo->aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_RINGING;
    pstRiStateInfo->ulVoiceRiCycleCount = 9;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_LOW);

    // MOCKER����
    MOCKER(AT_StopRelTimer)
        .stubs()
        .with(eq(ulVoiceTmrName),
              eq(&(pstRiStateInfo->hVoiceRiTmrHdl)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    At_TimeOutProc(&stMsg);

    // ִ�м��
    EXPECT_EQ(VOS_FALSE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_BUTT, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_STOP, pstRiStateInfo->enVoiceRiTmrStatus);
    EXPECT_EQ(AT_UART_RI_STATUS_STOP, pstRiStateInfo->aenVoiceRiStatus[ucCallId]);
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


class Test_AT_ProcFormatResultMsc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitUartCtx();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_ProcFormatResultMsc, Test_AT_ProcFormatResultMsc_001)
{
    // ��������
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ulRet   = AT_CONNECT;
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    AT_ProcFormatResultMsc(ucIndex, ulRet);

    // ִ�м��
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_DCD));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ProcFormatResultMsc, Test_AT_ProcFormatResultMsc_002)
{
    // ��������
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ulRet   = AT_NO_CARRIER;
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    AT_ProcFormatResultMsc(ucIndex, ulRet);

    // ִ�м��
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_DCD));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ProcFormatResultMsc, Test_AT_ProcFormatResultMsc_003)
{
    // ��������
    AT_UART_CTX_STRU                   *pstUartCtx;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ulRet                               = AT_CONNECT;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // ��ʼ��ȫ�ֱ���
    pstUartCtx                          = AT_GetUartCtxAddr();
    pstUartCtx->stLineCtrl.enDsrMode    = AT_UART_DSR_MODE_CONNECT_ON;
    pstUartCtx->stLineCtrl.enDcdMode    = AT_UART_DCD_MODE_CONNECT_ON;

    // MOCKER����

    // ���ñ��⺯��
    AT_ProcFormatResultMsc(ucIndex, ulRet);

    // ִ�м��
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_DCD));
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_DSR));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ProcFormatResultMsc, Test_AT_ProcFormatResultMsc_004)
{
    // ��������
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_UART_CTX_STRU                   *pstUartCtx;

    // ������ʼ��
    ulRet                               = AT_NO_CARRIER;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // ��ʼ��ȫ�ֱ���
    pstUartCtx                          = AT_GetUartCtxAddr();
    pstUartCtx->stLineCtrl.enDsrMode    = AT_UART_DSR_MODE_CONNECT_ON;
    pstUartCtx->stLineCtrl.enDcdMode    = AT_UART_DCD_MODE_CONNECT_ON;

    // MOCKER����

    // ���ñ��⺯��
    AT_ProcFormatResultMsc(ucIndex, ulRet);

    // ִ�м��
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_DCD));
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_DSR));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ProcFormatResultMsc, Test_AT_ProcFormatResultMsc_005)
{
    // ��������
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ulRet   = AT_NO_CARRIER;
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    AT_ProcFormatResultMsc(ucIndex, ulRet);

    // ִ�м��
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_DCD));

    GlobalMockObject::verify();
}

