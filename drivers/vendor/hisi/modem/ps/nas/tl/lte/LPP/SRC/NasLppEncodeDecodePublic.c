


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "vos.h"
#include  "NasLppEncodeDecodePublic.h"
#include  "PsLogdef.h"

#define    THIS_FILE_ID            PS_FILE_ID_NASLPPENCODEDECODEPUBLIC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPENCODEDECODEPUBLIC_C

/*lint -e701*/
#if (FEATURE_LPP == FEATURE_ON)

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
VOS_UINT8  g_aucLppEncodeMask[8][8] =
                        {{0x00, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01},
                        {0x80, 0x00, 0xbf, 0x9f, 0x8f, 0x87, 0x83, 0x81},
                        {0xc0, 0x00, 0x00, 0xdf, 0xcf, 0xc7, 0xc3, 0xc1},
                        {0xe0, 0x00, 0x00, 0x00, 0xef, 0xe7, 0xe3, 0xe1},
                        {0xf0, 0x00, 0x00, 0x00, 0x00, 0xf7, 0xf3, 0xf1},
                        {0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xf9},
                        {0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd},
                        {0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
VOS_UINT8  g_aucMask[8][8] =
                        {{0x00, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01},
                        {0x80, 0x00, 0xbf, 0x9f, 0x8f, 0x87, 0x83, 0x81},
                        {0xc0, 0x00, 0x00, 0xdf, 0xcf, 0xc7, 0xc3, 0xc1},
                        {0xe0, 0x00, 0x00, 0x00, 0xef, 0xe7, 0xe3, 0xe1},
                        {0xf0, 0x00, 0x00, 0x00, 0x00, 0xf7, 0xf3, 0xf1},
                        {0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xf9},
                        {0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd},
                        {0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

/*****************************************************************************
  3 Function
*****************************************************************************/




//#ifndef PS_ITT_PC_TEST_NAS
//VOS_UINT32 LTE_MsgHook(VOS_VOID * pMsg);
/*{
    return 0;
}*/
//#endif

VOS_VOID NAS_Lpp_AsnInit(VOS_VOID)
{
    NAS_LPP_MEM_CPY(g_aucLppEncodeMask, g_aucMask, 64);
}




VOS_VOID NAS_Lpp_PrintfMsg(VOS_UINT8 *pucEncodeBuff, char * EncodeIe, VOS_UINT32 ulMsgLength)
{
    VOS_UINT32 i;
    VOS_UINT32 ulMsgSize;
    vos_printf("Encode %s bit = %d Msg:\n", EncodeIe, ulMsgLength);
    vos_printf("Msg %s\n", pucEncodeBuff);
    vos_printf("========================================================1\n");

    if((ulMsgLength % 8 != 0) || (ulMsgLength == 0))
    {
        ulMsgSize = ulMsgLength + (8 - ulMsgLength % 8);
    }
    else
    {
        ulMsgSize = ulMsgLength;
    }

    for(i = 0; i < ulMsgSize/8; i++)
    {
        vos_printf("%-4x", pucEncodeBuff[i]);
        if((i%16 == 0) && (i != 0))
        {
            vos_printf("\n");
        }
    }
    vos_printf("\n");
    vos_printf("========================================================2\n\n");
}


VOS_VOID  NAS_LPP_GetParaToOctet(
                                VOS_UINT16      *pusTar,
                                VOS_UINT8       *pArr,
                                VOS_UINT16      usPos,
                                VOS_UINT16      usLen)
{
    VOS_UINT32  ulVTemp1 = 0;
    VOS_UINT32  ulVTemp2 = 0;
    VOS_UINT32  ulVTemp3 = 0;

    ulVTemp1 = usPos >> 3;
    ulVTemp2 = usPos & 0x07;
    ulVTemp3 = usPos + usLen - 1;
    ulVTemp3 = ulVTemp3 >> 3;

    /*��������Ŀ���ǽ�����Ҫ���������ȡ�����ŵ�usTar��ȥ�����ұ�֤�Ҷ���*/
    /*����0��ʾ��Ҫ���������С��һ��byte*/


    if(0 == ulVTemp3 - ulVTemp1)
    {
        *pusTar = (VOS_UINT16)((pArr[ulVTemp1] >> (8 - ulVTemp2 - usLen)) & (0xff >> (8 - usLen)));
    }

    else
    {
        /*��Ҫ��������ݴ���һ��byte*/
        *pusTar = (VOS_UINT16)(((((VOS_UINT32)(pArr[ulVTemp1] & (0xff >> ulVTemp2))) << 8)
                + ((VOS_UINT32)(pArr[ulVTemp1+1]))) >> (16 - ulVTemp2 - usLen));
    }


    return;
}
VOS_UINT16 NAS_LPP_EncodeExtBit(
                        VOS_UINT16      *pBitPos,
                        VOS_UINT8       *pEncodeOutMsg)

{
    VOS_UINT8   ucExtIe = 1;

    /*������չλ*/
    NAS_LPP_EncodeBitSteam(pEncodeOutMsg, pBitPos, 1, &ucExtIe);

    return NAS_LPP_ENCODE_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_LPP_Encode_EncodeLongData
 Description     : lpp����bitλ����0λС��32λ����������
 Input           : pEncodeOutMsg ��ʾ������ɺ�洢������buffer
                   pBitPos  ��ʾ��ǰ����ĵ�һ��λ��
                   usLen   ��ʾʵ��Ҫ����ĳ���
                   ulSource ��ʾʵ��Ҫ���������
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lifuxin  2015-6-2    Draft Enact
*****************************************************************************/
VOS_VOID NAS_LPP_EncodeEncodeLongData(
                                    VOS_UINT8       *pEncodeOutMsg,
                                    VOS_UINT16      *pBitPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT32      ulSource)
{
    VOS_UINT8       ucTemp = 0;
    VOS_UINT16      usTemp = 0;

    if((usLen > 0) && (usLen <= 8))
    {
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, usLen, (VOS_UINT8)ulSource);
    }
    else if((usLen > 8) && (usLen <= 16))
    {
        usTemp = (VOS_UINT16)ulSource;
        /*��8bit*/
        ucTemp = (VOS_UINT8)(usTemp >> 8);
        if(usLen == 16)
        {
            NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, 8, ucTemp);
        }
        else
        {
            NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, usLen%8, ucTemp);
        }
        /*��8bit*/
        ucTemp = (VOS_UINT8)usTemp;
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, 8, ucTemp);
    }
    else if((usLen > 16) && (usLen <= 24))
    {
        /*��8bit*/
        ucTemp = (VOS_UINT8)(ulSource >> 16);
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, usLen%16, ucTemp);
        /*��bit*/
        ucTemp = (VOS_UINT8)(ulSource >> 8);
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, 8, ucTemp);
        /*��8bit*/
        ucTemp = (VOS_UINT8)ulSource;
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, 8, ucTemp);
    }
    else
    {
        /*��ߵ�8bit*/
        ucTemp = (VOS_UINT8)(ulSource >> 24);
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, usLen%24, ucTemp);
        /*�θ�8bit*/
        ucTemp = (VOS_UINT8)(ulSource >> 16);
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, 8, ucTemp);
        /*��16bit�ĸ�8bit*/
        ucTemp = (VOS_UINT8)(ulSource >> 8);
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, 8, ucTemp);
        /*��8bit*/
        ucTemp = (VOS_UINT8)ulSource;
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, 8, ucTemp);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeBitsLess8
 Description     : LPP����Ҫ������������Ƶ����λ��Ȼ�����
 Input           : pTarget ��ʾ������ɺ�洢������buffer
                   pulPos  ��ʾ��ǰ����ĵ�һ��λ��
                   usLen   ��ʾʵ��Ҫ����ĳ���
                   pSource ��ʾʵ��Ҫ���������
 Output          : None
 Return          : VOS_VOID

 History         :
    1.WANGENSHENG  2015-05-15    Draft Enact
*****************************************************************************/
VOS_VOID NAS_LPP_EncodeBitsLess8(
                                    VOS_UINT8       *pucEncodeOutMsg,
                                    VOS_UINT16      *pusBitPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT8       ucSource)
{
    VOS_UINT8 aucTmp[1];

    aucTmp[0] = ucSource;

    if((usLen == 0) ||(usLen > 8))
    {

        return;
    }
    if(usLen != 8)
    {
        aucTmp[0] = (VOS_UINT8)(aucTmp[0] << (8 - usLen));
    }
    NAS_LPP_SetBitStreamFromStream(pucEncodeOutMsg, *pusBitPos, usLen, aucTmp);
    *pusBitPos += usLen;

    return;
}


VOS_VOID NAS_LPP_EncodeBitSteam(
                                    VOS_UINT8       *pTarget,
                                    VOS_UINT16      *pulPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT8       *pSource)
{
    NAS_LPP_SetBitStreamFromStream(pTarget, *pulPos, usLen, pSource);
    *pulPos += usLen;

    return;
}


VOS_VOID NAS_LPP_SetBitStreamFromStream(
                                    VOS_UINT8       *pTarget,
                                    VOS_UINT16      ulPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT8       *pucSource)
{
    VOS_UINT32      ulTargetOctetPos = 0;
    VOS_UINT16      usTargetBitLen = 0;
    VOS_UINT16      usVdata = 0;
    VOS_UINT16      usSourceBitLen = 0;
    VOS_UINT8       ucVlen = 0;
    VOS_UINT8       ucVMoveLen = 0;

    /*�õ���ǰ��Ҫ�洢���ֽ�����λ��*/
    ulTargetOctetPos = ulPos >> 3;

    /*�õ���ǰ��Ҫ�洢���ֽڴ�������ʣ���ٸ�bit���Դ洢*/
    usTargetBitLen = 8 - (ulPos & 0x07);

    /*��˼����Ҫ�洢�����ݳ���С�ڵ��ڻ�ʣ���bit���ȣ�
      ��ʣ��ĳ�����Ϊ��Ҫ����ĳ���*/
    if(usTargetBitLen >= usLen)
    {
        usTargetBitLen = usLen;
    }

    /*���ñ���λ�õĳ�ֵbitλ��*/
    usSourceBitLen = 0;

    /*���洢����֮�����ݵ�bufferָ���Ƶ����Ա�����ֽڵ��׵�ַ*/
    pTarget += ulTargetOctetPos;

    while (usLen != 0)
    {
        /*��Ҫ�����targetBitlen �洢��usVdata�У����ұ����Ҷ���*/
        NAS_LPP_GetParaToOctet(&usVdata, pucSource, usSourceBitLen, usTargetBitLen);

        /*��ʾ��ǰ�ֽڣ��洢��v_targetBitLen�����ȵ�bit֮��ռ�ø�byte���ܵ�bit����
          ���磬��ǰbit��2��ʼ�洢3��bit�����ݣ���ô��ǰbyte�ܹ�����5��bit*/
        ucVlen = ((ulPos + usTargetBitLen) & 0x07);

        /*ucVlen����0������һ���ǵ�ǰ�洢��POS+��Ҫ�洢��bit����ӵ���8��Ҳ���ǵ�ǰλ�øպô���*/
        if(ucVlen != 0)
        {
            /*�����ǰ��ǰλ��û�д���8��bit�������pos2��ʼ�洢3��bit����ô�ܹ�ռ�ø�byte 5��bit��
              �Ǹ���vdata���� 8-5��bit�� Ҳ���Ǹ���λ��bit��ǰ��λ����һ����Ԫռ�õ�bit��������
              ��3��bit�����Ǽ���Ҫ�����3��bit������3��bit����Чλ�� bit��ʼ������2��bit�� 10��
              ����Ҫ�����bit��101����ǰbyte��Чʹ��5��bit�����Խ�5��bit�Ƶ�����˱��ڱ��룬Ҳ��
              ��vdata��0000 0101 �����00101 000*/
              ucVMoveLen = 8 - ucVlen;
            usVdata = (VOS_UINT16)(usVdata << ucVMoveLen);
        }


        *pTarget = ((*pTarget) & g_aucLppEncodeMask[(ulPos&0x07)][ucVlen]) | ((VOS_UINT8)usVdata);

        usSourceBitLen = usSourceBitLen + usTargetBitLen;
        /*����ǰ����λ�ü���targetBitLen�������ܵı��������λ��������len��ô��*/
        ulPos = ulPos + usTargetBitLen;
        /*����ʣ���δ�����bits*/
        usLen = usLen - usTargetBitLen;
        /*���len����0��˵���Ѿ����������*/
        if(usLen != 0)
        {
            /*ָ����һ��byte��λ�ã������û�б�����ɣ���ָ�����Ƶ���һ��λ�ã���������ʣ�������*/
            pTarget++;

            /*����ʣ���bit��������һ������bit��ʵ�ʳ��ȣ�������߼��������ǰ��ʣ���bit������bit��
              ���������8bit���룬���ʣ���bit��С��8bit����ʣ���bit�����꼴�ɣ�����ѭ����
              ֻҪ�������*/
            if(usLen >= 8)
            {
                usTargetBitLen = 8;
            }
            else
            {
                usTargetBitLen = usLen;
            }
        }
    }
}


VOS_UINT32 NAS_LPP_GetParamFromBitStream(
                                            VOS_UINT8       aArr[],
                                            VOS_UINT32      ulPos,
                                            VOS_UINT8       usLen)
{
    VOS_UINT32      uLVtemp1 = 0;
    VOS_UINT8       ucVtemp2 = 0;
    VOS_UINT32      ulVtemp3 = 0;
    VOS_UINT32      ulReturnvalue = 0;
    VOS_UINT8       ucMaskvalue = 0xFF;
    VOS_UINT32      ulVexpend1 = 0;/*used to expend u8 to u32 high part*/
    VOS_UINT32      ulVexpend2 = 0;/*used to expend u8 to u32 mid-high part*/
    VOS_UINT32      ulVexpend3 = 0;/*used to expend u8 to u32 mid-low part*/
    VOS_UINT32      ulVexpend4 = 0;/*used to expend u8 to u32 low part*/

    /*��ʾ��ʼ����ĵ�һ��byte����ڴ�����������ʼ��ַ���ֽ���*/
    uLVtemp1 = ulPos >> 3;
    /*��ʾ��ʼ����ĵ�һ��byte��ʼ�����λ��*/
    ucVtemp2 = (VOS_UINT8)(ulPos & 0x07);
    /*��Ϊ���ܴ�����Ҫ��������������ֽڣ����μ�����Եó���Ҫ��������ݵĽ�����byteλ��*/
    ulVtemp3 = (ulPos + usLen - 1) >> 3;

    switch(ulVtemp3 - uLVtemp1)
    {
        /*��ʾ��Ҫ�����������һ��byte�ڲ�*/
        case 0:
          /*����������һ��byte�������������ȡ����ǰ��Ҫ����ĵ�һ��byte��Ȼ��������8��ȥ��byte�Ѿ����������������
            �ټ�ȥʵ��Ҫ����ĳ��ȣ�ʵ���ϵ������Ǳ�֤����������������λ��Ч���ҿ��룬���統ǰ��Ҫ�����byte�Ѿ�����6
            ��bit��Ҳ����pos��6����Ҫ����1��bit��Ҳ����len��1����ô��Ҫ����byte���� 8-6-1=1��bit��Ҳ���ǽ�������Ҫ���������
            �ŵ����λ�� ���� ��0xFF����8-1=7��bit����������ȡ����Ҫ����ĳ��ȣ�����Ӧ�����ó�1��Ȼ���������룬������ȡ��
            ��Ӧ��bitλ��Ҳ�����������
          */
          ulReturnvalue
            =(VOS_UINT32)((aArr[uLVtemp1] >> (8 - ucVtemp2 - usLen)) & (ucMaskvalue >> (8 - usLen)));
          break;

        /*��ʾ��Ҫ��������ݿ�Խ����byte*/
        case 1:
          /*�ѵ�ǰbyte������ȡ�������ϣ���byte����Ҫ��������룬�����byte��ռ��2��bit���Ǹ�����xxxx xx10��
           0000 0011���������ǰbyt�е�bit�������������8��bit��Ҳ����10 0000 0000���������������bit�ŵ������
           λ*/
          ulVexpend1 = ((VOS_UINT32)(aArr[uLVtemp1] & (ucMaskvalue >> ucVtemp2))) << 8;
          /*ȡ����һ��ǰbyte����һ�ֽ�*/
          ulVexpend2 = (VOS_UINT32)(aArr[uLVtemp1+1]);
          /*���ﴦ���൱����ƴ��Ȼ���ٲü��� ƴ���Ƚ���һ��byte����������ݼ��ϵڶ���byte�е��������ݣ�
          Ȼ���ٽ��ڶ���byte��ʵ��û���õ���bit�Ƴ�����������������Ҫ��������ݣ� ���磬 ��һ��byteռ��6��bit��
          ��Ҫ������ܳ�����len 4���Ǹ�˵���ڶ���byte����Ч����bit���� 16-6-4��Ҳ������Ҫ����6��bit���õ�������
          ������ʵ������*/
          ulReturnvalue = (VOS_UINT32)((ulVexpend1 + ulVexpend2) >> (16 - ucVtemp2 - usLen));
          break;

        case 2:
          /*��ǰ��Ҫ��������ݵĳ��ȿ�Խ������byte��ʵ�������������case1���ƣ�����ԭ��������ȡ�����λ
          �θ�byte���Լ���͵�byteʣ���bit����ͬ�����õ���������Ҫ�����õ�bit�����ƣ��õ���ʵ��������
          ������ϸ����*/
          ulVexpend1 = ((VOS_UINT32)(aArr[uLVtemp1] & (ucMaskvalue >> ucVtemp2))) << 16;
          ulVexpend2 = ((VOS_UINT32)(aArr[uLVtemp1+1])) << 8;
          ulVexpend3 = (VOS_UINT32)(aArr[uLVtemp1+2]);
          ulReturnvalue = (ulVexpend1 + ulVexpend2 + ulVexpend3) >> (24 - ucVtemp2 - usLen);
          break;

        case 3:
          ulVexpend1 = ((VOS_UINT32)(aArr[uLVtemp1] & (ucMaskvalue >> ucVtemp2))) << 24;
          ulVexpend2 = ((VOS_UINT32)(aArr[uLVtemp1+1])) << 16;
          ulVexpend3 = ((VOS_UINT32)(aArr[uLVtemp1+2])) << 8;
          ulVexpend4 = (VOS_UINT32)(aArr[uLVtemp1+3]);
          ulReturnvalue
            = (ulVexpend1 + ulVexpend2 + ulVexpend3 + ulVexpend4) >> (32 - ucVtemp2 - usLen);
          break;

        case 4:
          ulVexpend1 = ((VOS_UINT32)(aArr[uLVtemp1+1])) << 24;
          ulVexpend2 = ((VOS_UINT32)(aArr[uLVtemp1+2])) << 16;
          ulVexpend3 = ((VOS_UINT32)(aArr[uLVtemp1+3])) << 8;
          ulVexpend4 = (VOS_UINT32)(aArr[uLVtemp1+4]);
          ulVexpend2
            = (ulVexpend1 + ulVexpend2 + ulVexpend3 + ulVexpend4) >> (40 - ucVtemp2 - usLen);
          ulVexpend1
            =((VOS_UINT32)(aArr[uLVtemp1] & (ucMaskvalue >> ucVtemp2))) << (ucVtemp2 + usLen - 8);
          ulReturnvalue = ulVexpend1 + ulVexpend2;
          break;

        default:
          ;
      }
  return ulReturnvalue;
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetDataFromBitStream
 Description     : LPP����������ĺ���,
 Input           : aArr  ��ʾ�����������
                   ulPos ��ʾ��������ĳ�ʼλ��
                   usLen ��ʾ�����ʵ�ʳ���
 Output          : None
 Return          : VOS_UINT32
                   ���ؽ���֮�������
 History         :
    1.wangensheng 00324863  2015-05-04    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LPP_GetDataFromBitStream(
                                            VOS_UINT8                       *pDecodeBitStream,
                                            VOS_UINT32                      *pCurrentBitPos,
                                            VOS_UINT8       usLen)
{
    VOS_UINT32      ulReturnValue;

    ulReturnValue = NAS_LPP_GetParamFromBitStream(pDecodeBitStream,*pCurrentBitPos,usLen);
    *pCurrentBitPos = *pCurrentBitPos + usLen;

    return  ulReturnValue;
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetLongDataFromBitStream
 Description     : LPP�����ȡ����32bit���ݵĺ���
 Input           : aArr  ��ʾ�����������
                   ulPos ��ʾ��������ĳ�ʼλ��
                   usLen ��ʾ�����ʵ�ʳ���
                   pllDestData ��ʾ�洢���ݵı���
 Output          : None
 Return          : VOS_UINT32
                   �ɹ����� NAS_LPP_DECODE_SUCC ʧ�� ���� NAS_LPP_DECODE_FAIL
 History         :
    1.wangensheng 00324863  2015-05-04    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LPP_GetLongDataFromBitStream(
                                                VOS_UINT8       aArr[],
                                                VOS_UINT32      *ulPos,
                                                VOS_UINT8       usLen,
                                                VOS_UINT64      *pllDestData)
{
    /*��ȡ����32bitС�ڵ���64bit��ֵ����ƴ�ӳ�64bit������64bit��ֵ��Ҫ���ⲿȥѭ������*/
    VOS_UINT64      ullTargetValue;
    VOS_UINT64      ullTempData1 = 0;
    VOS_UINT8       ucTempLen = 0;
    /*�������*/

    if(usLen <= 32 )
    {
        ullTargetValue = (VOS_UINT64)NAS_LPP_GetDataFromBitStream(aArr,ulPos,usLen);
        *pllDestData = ullTargetValue;
        return NAS_LPP_DECODE_SUCC;
    }
    ucTempLen = usLen % 32;
    /*�����64bit�����*/
    if(ucTempLen == 0)
    {
        ucTempLen = 32;
    }
    ullTempData1 = (VOS_UINT64)NAS_LPP_GetDataFromBitStream(aArr,ulPos,ucTempLen);
    ullTargetValue = NAS_LPP_GetDataFromBitStream(aArr,ulPos,32);
    ullTargetValue += (ullTempData1) << 32;
    *pllDestData = ullTargetValue;
    return NAS_LPP_DECODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetLongBitFromBitStream
 Description     : LPP�����ȡ����32bit���ݵĺ���
 Input           : aArr  ��ʾ�����������
                   ulPos ��ʾ��������ĳ�ʼλ��
                   usLen ��ʾ�����ʵ�ʳ���
                   pllDestData ��ʾ�洢���ݵı���
 Output          : None
 Return          : VOS_UINT32
                   �ɹ����� NAS_LPP_DECODE_SUCC ʧ�� ���� NAS_LPP_DECODE_FAIL
 History         :
    1.wangensheng 00324863  2015-05-04    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LPP_GetLongBitFromBitStream(
                                                VOS_UINT8       aArr[],
                                                VOS_UINT32      *ulPos,
                                                VOS_UINT16       usLen,
                                                VOS_UINT8      *pllDestData)
{
    VOS_UINT8   ucTempLen = 0;
    VOS_UINT8   ucTempValue = 0;
    if(usLen == 0)
        return NAS_LPP_DECODE_SUCC;
    ucTempLen = usLen % 8;
    if(ucTempLen == 0)
    {
        ucTempLen = 8;
    }
    while(usLen != 0)
    {
        usLen -=ucTempLen;
        ucTempValue = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(aArr,ulPos,ucTempLen);
        *pllDestData = ucTempValue;
        pllDestData++;
        ucTempLen = 8;
    }
    return NAS_LPP_DECODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_ASN_FAIL_Message
 Description     : LPP������ά�ɲ���Ϣ
 Input           :��ά�ɲ���Ϣͷ
 Output          : None
 Return          : VOS_UINT32
                   �ɹ�����
 History         :
    1.wangensheng 00324863  2015-05-04    Draft Enact
****************************************************************************
VOS_VOID NAS_LPP_Hook(VOS_VOID* pstMsg)
{
    return  ;
}*/
/*****************************************************************************
 Function Name   : NAS_LPP_ASN_FAIL_Message
 Description     : LPP������ά�ɲ���Ϣ
 Input           :
 Output          : None
 Return          : VOS_UINT32
                   �ɹ����� NAS_LPP_DECODE_SUCC ʧ�� ���� NAS_LPP_DECODE_FAIL
 History         :
    1.wangensheng 00324863  2015-05-04    Draft Enact
*****************************************************************************/
VOS_VOID    NAS_LPP_ASN_FAIL_Message(
                                    VOS_UINT32          ulIEType,
                                    VOS_UINT32          ulIEErrorType,
                                    VOS_UINT32          ulBitPos,
                                    VOS_UINT32          ulLineNum,
                                    VOS_UINT32          ulRsv)
{
    NAS_LPP_ASN_FAIL_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LPP_ASN_FAIL_STRU*)NAS_LPP_MEM_ALLOC(sizeof(NAS_LPP_ASN_FAIL_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LPP_LOG_ERR("NAS_LMM_SndOmLogStateChange: mem alloc fail!.");
        return;
    }

    NAS_LPP_MEM_SET(pstMsg, 0, sizeof(NAS_LPP_ASN_FAIL_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LPP_ASN_FAIL_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName = NAS_LPP_TO_OM_MSG_ASN_FAIL;
    pstMsg->enIeType = ulIEType;
    pstMsg->enCause = ulIEErrorType;
    pstMsg->ulBitPosValue = ulBitPos;
    pstMsg->ulLineNum = ulLineNum;
    pstMsg->ulRsvData = ulRsv;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LPP_MEM_FREE(pstMsg);
    return;
}

/*lint +e701*/
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

