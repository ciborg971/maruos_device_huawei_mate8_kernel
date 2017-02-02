

#include "AtOamInterface.h"
#include "TafOamInterface.h"
#include "MnErrorCode.h"
#include "si_stk.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_STK_ATPRINTF_C



VOS_UINT8 g_aucCrLf[] = "\r\n";              /*�س�����*/
VOS_UINT8 gaucAtStin[] = "^STIN:";
VOS_UINT8 gaucAtStmn[] = "^STMN:";
VOS_UINT8 gaucAtStgi[] = "^STGI:";
VOS_UINT8 gaucAtStsf[] = "^STSF:";
VOS_UINT8 gaucAtCsin[] = "^CSIN:";
VOS_UINT8 gaucAtCstr[] = "^CSTR:";
VOS_UINT8 gaucAtCsen[] = "^CSEN:";
VOS_UINT8 gaucAtCsmn[] = "^CSMN:";
VOS_INT32 At_sprintf(VOS_INT32 MaxLength,VOS_CHAR *pHeadAddr,VOS_CHAR *pCurrAddr,const VOS_CHAR *fmt,...)
{
    VOS_INT32 slLength = 0;
    VOS_UINT32 ulNum = 0;
    VOS_INT32 lNumSrc = 0;      /* ԭʼ����*/
    VOS_INT32 slNum = 0;        /* ת���������*/
    VOS_CHAR *pData = NULL;
    VOS_CHAR *sc = NULL;
    VOS_CHAR *s = NULL;

    /*lint -e530 -e830 */
    va_list args;

    VOS_UINT32 ulLen1 = 0, ulLen2 = 0;   /* ulLen1:%�����õĳ���; ulLen2:ʵ�ʶ�ȡ�ĳ���*/

    if(pCurrAddr < pHeadAddr)
    {
        return 0;
    }

    /*lint -e586*/
    va_start(args, fmt);
    /*lint +e586*/
    for (pData = (VOS_CHAR *)fmt; '\0' != *pData ; ++pData)
    {
        if('%' == *pData)
        {
            ulLen1 = 0;
            ulLen2 = 0;

            pData++;

            if('0' == (*pData))
            {
                pData++;
                ulLen1 = 0;     /* ָ���Ŀ�ȣ������*/
            }

            /* Ŀǰ��ֻ֧��С�ڵ���9λ�Ŀ��*/
            if(('0' <= (*pData)) && ('9' >= (*pData)))
            {
                ulLen1 = (VOS_UINT32)(VOS_INT32)((*pData) - '0');     /* ָ���Ŀ��*/
                pData++;
            }

            /* Ŀǰ��ֻ���õ�d,s,X,���֣�����һ����Ϊ����*/
            switch(*pData)
            {
            case 'c':
                {
                    slLength++;
                    break;
                }

            case 's':
                /*lint -e147 -e662 -e586*/
                s = va_arg(args, VOS_CHAR *);
                /*lint +e147 +e662 +e586*/
                if(NULL == s)
                {
                    slLength += (VOS_INT32)strlen("(null)");
                    break;
                }

                for (sc = s; *sc != '\0'; ++sc)
                {
                    slLength++;
                }
                break;

            case 'd':
                /*lint -e147 -e662 -e586*/
                lNumSrc = va_arg(args, VOS_INT32);
                /*lint +e147 +e662 +e586*/
                slNum = lNumSrc;

                slLength++;
                ulLen2++;                   /* ʵ�ʵĿ��*/

                while ((slNum > 9) || (slNum < (-9)))
                {
                    slNum = slNum / 10;
                    slLength++;
                    ulLen2++;               /* ʵ�ʵĿ��*/
                }

                if(ulLen2 < ulLen1)
                {
                    slLength += (VOS_INT32)(ulLen1- ulLen2);
                }
                else if(lNumSrc < 0)    /* ���ulLen2 >= ulLen1,��lNumSrc<0����Ҫ���ϸ��ŵ�һ���ռ�*/
                {
                    slLength++;
                }
                else
                {
                }
                break;

            case 'u':
                /*lint -e147 -e662 -e586*/
                ulNum = va_arg(args, VOS_UINT32);
                /*lint +e147 +e662 +e586*/

                slLength++;
                ulLen2++;                   /* ʵ�ʵĿ��*/
                while (ulNum > 9)
                {
                    ulNum = ulNum / 10;
                    slLength++;
                    ulLen2++;               /* ʵ�ʵĿ��*/
                }

                if(ulLen2 < ulLen1)
                {
                    slLength += (VOS_INT32)(ulLen1- ulLen2);
                }
                break;

            case 'X':
                /* continue*/
            case 'x':
                /*lint -e147 -e662 -e586*/
                ulNum = va_arg(args, VOS_UINT32);
                /*lint +e147 +e662 +e586*/

                slLength++;
                ulLen2++;                   /* ʵ�ʵĿ��*/

                while (ulNum > 0x0f)
                {
                    ulNum = ulNum / 16;
                    slLength++;
                    ulLen2++;               /* ʵ�ʵĿ��*/
                }

                if(ulLen2 < ulLen1)
                {
                    slLength += (VOS_INT32)(ulLen1- ulLen2);
                }
                break;

            default:
                /*lint -e586*/
                va_end(args);
                /*lint +e586*/
                return 0;
            }
        }
        else
        {
            slLength++;     /* ��1 */
        }
    }
    /*lint -e586*/
    va_end(args);
    /*lint +e586*/

    if(pCurrAddr - pHeadAddr + slLength >= (VOS_INT32)(MaxLength))
    {
        return 0;
    }

    /*lint -e586*/
    va_start(args, fmt);
    /*lint +e586*/

    if(slLength != VOS_vsprintf(pCurrAddr,fmt,args))
    {
        return 0;
    }

    /*lint -e586*/
    va_end(args);
    /*lint +e586*/

    return slLength;
    /*lint +e530 +e830 */
}


VOS_UINT32 At_HexText2AsciiString(VOS_UINT32 MaxLength,VOS_INT8 *headaddr,VOS_UINT8 *pucDst,SI_STK_TEXT_STRING_STRU *pTextStr)
{
    VOS_UINT16 usLen = 0;
    VOS_UINT16 usChkLen = 0;
    VOS_UINT8 *pWrite = pucDst;
    VOS_UINT8 *pRead = pTextStr->pucText;
    VOS_UINT8  ucHigh = 0;
    VOS_UINT8  ucLow = 0;

    if(((VOS_UINT32)(pucDst - (VOS_UINT8 *)headaddr) + (2 * pTextStr->ucLen)) >= MaxLength)
    {
        STK_ERROR_LOG("At_HexText2AsciiString too long");
        return 0;
    }

    if(0 != pTextStr->ucLen)
    {
        usLen += 1;

        *pWrite++ = '\"';

        /* ɨ�������ִ� */
        while( usChkLen++ < pTextStr->ucLen )
        {
            ucHigh = 0x0F & (*pRead >> 4);
            ucLow = 0x0F & *pRead;
            usLen += 2;    /* ��¼���� */

            if(0x09 >= ucHigh)   /* 0-9 */
            {
                *pWrite++ = ucHigh + 0x30;
            }
            else if(0x0A <= ucHigh)    /* A-F */
            {
                *pWrite++ = ucHigh + 0x37;
            }
            else
            {

            }

            if(0x09 >= ucLow)   /* 0-9 */
            {
                *pWrite++ = ucLow + 0x30;
            }
            else if(0x0A <= ucLow)    /* A-F */
            {
                *pWrite++ = ucLow + 0x37;
            }
            else
            {

            }
            /* ��һ���ַ� */
            pRead++;
        }

        usLen += 2;

        *pWrite++ = '\"';

        *pWrite++ = ',';

        usLen ++;    /* ��¼���� */

        *pWrite++ = 0x30+(0x0F&pTextStr->ucDCS); /* ȡDCS�ֶεĵ�4bit */

        *pWrite++ = '\0';
    }

    return usLen;
}
VOS_UINT32 At_HexAlpha2AsciiString(VOS_UINT32 MaxLength,VOS_INT8 *headaddr,VOS_UINT8 *pucDst,VOS_UINT8 *pucSrc,VOS_UINT16 usSrcLen)
{
    VOS_UINT16 usLen = 0;
    VOS_UINT16 usChkLen = 0;
    VOS_UINT8 *pWrite = pucDst;
    VOS_UINT8 *pRead = pucSrc;
    VOS_UINT8  ucHigh = 0;
    VOS_UINT8  ucLow = 0;

    if(((VOS_UINT32)(pucDst - (VOS_UINT8 *)headaddr) + (2 * usSrcLen)) >= MaxLength)
    {
        STK_ERROR_LOG("At_HexAlpha2AsciiString too long");
        return 0;
    }

    if(0 != usSrcLen)
    {
        /* ɨ�������ִ� */
        while( usChkLen++ < usSrcLen )
        {
            ucHigh = 0x0F & (*pRead >> 4);
            ucLow = 0x0F & *pRead;

            usLen += 2;    /* ��¼���� */

            if(0x09 >= ucHigh)   /* 0-9 */
            {
                *pWrite++ = ucHigh + 0x30;
            }
            else if(0x0A <= ucHigh)    /* A-F */
            {
                *pWrite++ = ucHigh + 0x37;
            }
            else
            {

            }

            if(0x09 >= ucLow)   /* 0-9 */
            {
                *pWrite++ = ucLow + 0x30;
            }
            else if(0x0A <= ucLow)    /* A-F */
            {
                *pWrite++ = ucLow + 0x37;
            }
            else
            {

            }

            /* ��һ���ַ� */
            pRead++;
        }

    }
    return usLen;
}
VOS_VOID At_UsimGsm7bit2AsciiTransfer(VOS_UINT8 *pucData, VOS_UINT32 *pulDataLen)
{
    VOS_UINT32  i,j;
    VOS_UINT32  ulDataLen;
    VOS_UINT8   *pDest;
    VOS_UINT8   aucData[256];/* Ŀǰ���֧��ת��Ϊ256����ASCII���� */

    ulDataLen = *pulDataLen;
    pDest      = aucData;

    for((i = 0), (j = 0); (i < ulDataLen)&&(j < sizeof(aucData)); i++, j++)
    {
        switch(pucData[i])
        {
            case 0x0:
                *pDest++ = '@';
                break;
            case 0x2:
                *pDest++ = '$';
                break;
            case 0x11:
                *pDest++ = '_';
                break;
            case SI_PB_ALPHATAG_TRANSFER_TAG:
                i++;

                /* EMAIL�����һ���ֽ���1Bʱ���������������� */
                if(i >=  ulDataLen)
                {
                    j--;
                    break;
                }

                switch(pucData[i])
                {
                    case 0x14:
                        *pDest++ = '^';
                        break;
                    case 0x28:
                        *pDest++ = '{';
                        break;
                    case 0x29:
                        *pDest++ = '}';
                        break;
                    case 0x2F:
                        *pDest++ = '\\';
                        break;
                    case 0x3C:
                        *pDest++ = '[';
                        break;
                    case 0x3D:
                        *pDest++ = '~';
                        break;
                    case 0x3E:
                        *pDest++ = ']';
                        break;
                    case 0x40:
                        *pDest++ = '|';
                        break;
                    default :
                        *pDest++ = pucData[i];
                        break;
                }

                break;
            default:
                *pDest++ = pucData[i];
                break;
        }
    }

    /*lint -e534*/
    VOS_MemCpy(pucData, aucData, j);
    /*lint +e534*/

    *pulDataLen = j;

}

/*****************************************************************************
 Prototype      : At_CountDurationTime
 Description    : Sat��Ϣ������
 Input          :
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---

*****************************************************************************/
VOS_UINT32 At_CountDurationTime(VOS_UINT8 ucUint, VOS_UINT8 ucInternal)
{
    VOS_UINT32 ulResult;

    switch(ucUint)
    {
        case 0x00:
            ulResult = ucUint * 60 * ucInternal;
            break;
        case 0x01:
            ulResult = ucUint * ucInternal;
            break;
        case 0x02:
            ulResult = ucUint * 10 * ucInternal;
            break;
        default:
            ulResult = 0;
            break;
    }

    return ulResult;
}

/*****************************************************************************
 Prototype      : At_ChangeSATCMDNo
 Description    : Sat��Ϣ������
 Input          :
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---

*****************************************************************************/
VOS_UINT32 At_ChangeSTKCmdNo(VOS_UINT32 ulCmdType, VOS_UINT8 *ucCmdNo )
{
    switch(ulCmdType)
    {
        case SI_STK_REFRESH:
            *ucCmdNo = SI_AT_CMD_REFRESH;
            break;
        case SI_STK_DISPLAYTET:
            *ucCmdNo = SI_AT_CMD_DISPLAY_TEXT;
            break;
        case SI_STK_GETINKEY:
            *ucCmdNo = SI_AT_CMD_GET_INKEY;
             break;
        case SI_STK_GETINPUT:
            *ucCmdNo = SI_AT_CMD_GET_INPUT;
            break;
        case SI_STK_PLAYTONE:
            *ucCmdNo = SI_AT_CMD_PLAY_TONE;
            break;
        case SI_STK_SELECTITEM:
            *ucCmdNo = SI_AT_CMD_SELECT_ITEM;
            break;
        case SI_STK_SETUPMENU:
            *ucCmdNo = SI_AT_CMD_SETUP_MENU;
            break;
        case SI_STK_SETUPIDLETEXT:
            *ucCmdNo = SI_AT_CMD_SETUP_IDLE_MODE_TEXT;
            break;
        case SI_STK_LAUNCHBROWSER:
            *ucCmdNo = SI_AT_CMD_LAUNCH_BROWSER;
            break;
        case SI_STK_SENDSS:
            *ucCmdNo = SI_AT_CMD_SEND_SS;
            break;
        case SI_STK_LANGUAGENOTIFICATION:
            *ucCmdNo = SI_AT_CMD_LANGUAGENOTIFICATION;
            break;
        case SI_STK_SETFRAMES:
            *ucCmdNo = SI_AT_CMD_SETFRAMES;
            break;
        case SI_STK_GETFRAMESSTATUS:
            *ucCmdNo = SI_AT_CMD_GETFRAMESSTATUS;
            break;
        default:
            return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 Prototype      : At_SatCallBackFunc
 Description    : Sat��Ϣ������
 Input          :
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-07-04
    Author      : zhuli
    Modification: Created function
*****************************************************************************/
VOS_VOID At_STKDisplayTextCmdPrint(VOS_UINT16* pusDataLen, SI_STK_DATA_INFO_STRU * pEvent)
{
    VOS_UINT16 usLength;
    VOS_UINT32 ulTemp;

    usLength = *pusDataLen;

    usLength += (VOS_UINT16)At_HexText2AsciiString(STK_PRINT_MAX_LEN,(VOS_INT8 *)g_pucSTKSndCodeAddr,(VOS_UINT8 *)g_pucSTKSndCodeAddr + usLength,&pEvent->CmdStru.DisplayText.TextStr);

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr + usLength,
                                    ",%d",((pEvent->CmdDetail.ucCommandQua&0x80)>>7));

    if(1 == pEvent->CmdStru.DisplayText.OP_Duration)
    {
        ulTemp = At_CountDurationTime(pEvent->CmdStru.DisplayText.Duration.ucUnit,pEvent->CmdStru.DisplayText.Duration.ucInternal);

        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr + usLength,
                                    ",%d",ulTemp);
    }

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        "%s",g_aucCrLf);

    *pusDataLen = usLength;

    return;
}

/*****************************************************************************
 Prototype      : At_SatCallBackFunc
 Description    : Sat��Ϣ������
 Input          :
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-07-04
    Author      : zhuli
    Modification: Created function
*****************************************************************************/
VOS_VOID At_STKGetInKeyCmdPrint(VOS_UINT16* pusDataLen, SI_STK_DATA_INFO_STRU* pEvent)
{
    VOS_UINT16 usLength;
    VOS_UINT32 ulTemp;

    usLength = *pusDataLen;

    if(pEvent->CmdStru.GetInput.TextStr.ucLen != 0)
    {
        usLength += (VOS_UINT16)At_HexText2AsciiString(STK_PRINT_MAX_LEN,(VOS_INT8 *)g_pucSTKSndCodeAddr,(VOS_UINT8 *)g_pucSTKSndCodeAddr+usLength,
                                                    &pEvent->CmdStru.GetInput.TextStr);
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+usLength,
                                    "\"\",");
    }

    if((pEvent->CmdDetail.ucCommandQua&0x04) ==  0x04)
    {
        ulTemp = 1;
    }
    else if((pEvent->CmdDetail.ucCommandQua&0x01) ==  0x00)
    {
        ulTemp = 2;
    }
    else if((pEvent->CmdDetail.ucCommandQua&0x02) ==  0x02)
    {
        ulTemp = 3;
    }
    else
    {
        ulTemp = 0;
    }

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr + usLength,
                                        ",%d",ulTemp);

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr + usLength,
                                        ",%d",
                                        (pEvent->CmdDetail.ucCommandQua&0x80)>>7);

    if(1 == pEvent->CmdStru.GetInkey.OP_Duration)
    {
        ulTemp = At_CountDurationTime(pEvent->CmdStru.GetInkey.Duration.ucUnit,pEvent->CmdStru.GetInkey.Duration.ucInternal);

        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        ",%d",ulTemp);
    }
    else
    {
        if(1 == pEvent->CmdStru.GetInkey.OP_IconId)
        {
            usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr + usLength,
                                            ",,%X",pEvent->CmdStru.GetInkey.IconId.ucId);
        }
    }

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        "%s",g_aucCrLf);

    *pusDataLen = usLength;

    return;
}

/*****************************************************************************
 Prototype      : At_SatCallBackFunc
 Description    : Sat��Ϣ������
 Input          :
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-07-04
    Author      : zhuli
    Modification: Created function
*****************************************************************************/
VOS_VOID At_STKGetInputCmdPrint(VOS_UINT16* pusDataLen, SI_STK_DATA_INFO_STRU* pEvent)
{
    VOS_UINT16 usLength;
    VOS_UINT32 ulTemp;

    usLength = *pusDataLen;

    if(pEvent->CmdStru.GetInput.TextStr.ucLen != 0)
    {
        usLength += (VOS_UINT16)At_HexText2AsciiString(STK_PRINT_MAX_LEN,(VOS_INT8 *)g_pucSTKSndCodeAddr,(VOS_UINT8 *)g_pucSTKSndCodeAddr+usLength,
                                                    &pEvent->CmdStru.GetInput.TextStr);
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+usLength,
                                    "\"\",");
    }

    if((pEvent->CmdDetail.ucCommandQua&0x01) ==  0x00)
    {
        ulTemp = 2;
    }
    else if((pEvent->CmdDetail.ucCommandQua&0x02) ==  0x00)
    {
        ulTemp = 0;
    }
    else
    {
        ulTemp = 3;
    }

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+usLength,
                                    ",%d",ulTemp);

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+usLength,
                                    ",%d",(pEvent->CmdDetail.ucCommandQua&0x08)>>3);

    if((pEvent->CmdDetail.ucCommandQua&0x04) ==  0x00)
    {
        ulTemp = 1;
    }
    else
    {
        ulTemp = 0;
    }

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+usLength,
                                    ",%d,%d,%d",ulTemp,
                                    pEvent->CmdStru.GetInput.RspLen.ucMinLen,
                                    pEvent->CmdStru.GetInput.RspLen.ucMaxLen);

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                    ",%d",(pEvent->CmdDetail.ucCommandQua&0x80)>>7);

    if(1 == pEvent->CmdStru.GetInput.OP_DefaultText)
    {
        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                                    ",");

        usLength += (VOS_UINT16)At_HexText2AsciiString(STK_PRINT_MAX_LEN,
                                                    (VOS_INT8 *)g_pucSTKSndCodeAddr,
                                                    (VOS_UINT8 *)g_pucSTKSndCodeAddr+usLength,
                                                    &pEvent->CmdStru.GetInput.DefaultText);
    }

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        "%s",g_aucCrLf);

    *pusDataLen = usLength;

    return;
}

/*****************************************************************************
 Prototype      : At_SatCallBackFunc
 Description    : Sat��Ϣ������
 Input          :
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-07-04
    Author      : zhuli
    Modification: Created function
*****************************************************************************/
VOS_VOID At_STKPlayToneCmdPrint(VOS_UINT16* pusDataLen, SI_STK_DATA_INFO_STRU* pEvent)
{
    VOS_UINT16 usLength;
    VOS_UINT32 ulTemp;

    usLength = *pusDataLen;

    if(1 == pEvent->CmdStru.PlayTone.OP_Tone)
    {
        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        "%d",pEvent->CmdStru.PlayTone.Tone.ucTone);
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        ",");
    }


    if(1 == pEvent->CmdStru.PlayTone.OP_Duration)
    {
        ulTemp = At_CountDurationTime(pEvent->CmdStru.PlayTone.Duration.ucUnit,pEvent->CmdStru.PlayTone.Duration.ucInternal);

        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        ",%d",ulTemp);
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        ",");
    }

    if(1 == pEvent->CmdStru.PlayTone.OP_AlphaId)
    {
        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        ",\"");

        if((pEvent->CmdStru.PlayTone.AlphaId.pucAlphabet[0]&0x80) == 0x80)
        {
            ulTemp = 8;
        }
        else
        {
            ulTemp = 4;
        }

        usLength += (VOS_UINT16)At_HexAlpha2AsciiString(STK_PRINT_MAX_LEN,
                                                (VOS_INT8 *)g_pucSTKSndCodeAddr,
                                                (VOS_UINT8 *)g_pucSTKSndCodeAddr+usLength,
                                                pEvent->CmdStru.PlayTone.AlphaId.pucAlphabet,
                                                (VOS_UINT16)pEvent->CmdStru.PlayTone.AlphaId.ulLen);

        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        "\",%d",ulTemp);
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        ",");
    }

    if(1 == pEvent->CmdStru.PlayTone.OP_IconId)
    {
        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        ",%d",pEvent->CmdStru.PlayTone.IconId.ucId);
    }

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        "%s",g_aucCrLf);

    *pusDataLen = usLength;

    return;
}

/*****************************************************************************
 Prototype      : At_SatCallBackFunc
 Description    : Sat��Ϣ������
 Input          :
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-07-04
    Author      : zhuli
    Modification: Created function
*****************************************************************************/
VOS_VOID At_STKSelItemCmdPrint(VOS_UINT16* pusDataLen, SI_STK_DATA_INFO_STRU* pEvent)
{
    VOS_UINT8  ucHelpInfo;
    VOS_UINT16 usLength;
    VOS_UINT32 ulTemp;

    usLength = *pusDataLen;

    ucHelpInfo = (pEvent->CmdDetail.ucCommandQua&0x80)>>7;

    if(1 == pEvent->CmdStru.SelectItem.OP_ItemIDTag)
    {
        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        ",0");
    }

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        ",%d,\"",pEvent->CmdStru.SelectItem.ItemNum);

    if(1 == pEvent->CmdStru.SelectItem.OP_AlphaId)
    {
        usLength += (VOS_UINT16)At_HexAlpha2AsciiString(STK_PRINT_MAX_LEN,
                                    (VOS_INT8 *)g_pucSTKSndCodeAddr,
                                    (VOS_UINT8 *)g_pucSTKSndCodeAddr+ usLength,
                                    pEvent->CmdStru.SelectItem.AlphaId.pucAlphabet,
                                    (VOS_UINT16)pEvent->CmdStru.SelectItem.AlphaId.ulLen);
    }

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                    "\"");

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                    "%s",g_aucCrLf);

    for(ulTemp = 0; ulTemp < pEvent->CmdStru.SelectItem.ItemNum; ulTemp++)
    {
        /* �������Ϊ0���򲻴�ӡ��ITEM */
        if (0 == pEvent->CmdStru.SelectItem.Item[ulTemp].ucLen)
        {
            continue;
        }

        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                                   "%s%d,%d,\"",gaucAtStgi,
                                                    pEvent->CmdStru.SelectItem.Item[ulTemp].ucItemId,
                                                    pEvent->CmdStru.SelectItem.ItemNum);

        usLength += (VOS_UINT16)At_HexAlpha2AsciiString(STK_PRINT_MAX_LEN,
                                                    (VOS_INT8 *)g_pucSTKSndCodeAddr,
                                                    (VOS_UINT8 *)g_pucSTKSndCodeAddr + usLength,
                                                    pEvent->CmdStru.SelectItem.Item[ulTemp].pucItemText,
                                                    pEvent->CmdStru.SelectItem.Item[ulTemp].ucLen);

        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                                "\",%d",ucHelpInfo);

        if(1 == pEvent->CmdStru.SelectItem.OP_INAIndicator)
        {
            usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                                ",%d",pEvent->CmdStru.SelectItem.INAIndicator.pucINAIl[ulTemp]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                                ",");
        }

        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                            "%s",g_aucCrLf);
    }

    *pusDataLen = usLength;

    return;
}

/*****************************************************************************
 Prototype      : At_SatCallBackFunc
 Description    : Sat��Ϣ������
 Input          :
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-07-04
    Author      : zhuli
    Modification: Created function
*****************************************************************************/
VOS_VOID At_STKSetupMenuCmdPrint(VOS_UINT16* pusDataLen, SI_STK_DATA_INFO_STRU* pEvent)
{
    VOS_UINT8  ucHelpInfo;
    VOS_UINT16 usLength;
    VOS_UINT32 ulTemp;

    usLength = *pusDataLen;

    ucHelpInfo = (pEvent->CmdDetail.ucCommandQua&0x80)>>7;

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                                    "0");

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                                    ",%d,\"",
                                                    pEvent->CmdStru.SetupMenu.ulItemNum);

    usLength += (VOS_UINT16)At_HexAlpha2AsciiString(STK_PRINT_MAX_LEN,(VOS_INT8 *)g_pucSTKSndCodeAddr,(VOS_UINT8 *)g_pucSTKSndCodeAddr+ usLength,
                                                    pEvent->CmdStru.SetupMenu.AlphaId.pucAlphabet,
                                                    (VOS_UINT16)pEvent->CmdStru.SetupMenu.AlphaId.ulLen);

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                                    "\"");

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                                    "%s",g_aucCrLf);

    for(ulTemp= 0; ulTemp < pEvent->CmdStru.SetupMenu.ulItemNum; ulTemp++)
    {
        if (0 == pEvent->CmdStru.SetupMenu.Item[ulTemp].ucLen)
        {
            continue;
        }

        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                                    "%s%d,%d,\"",gaucAtStgi,
                                                    pEvent->CmdStru.SetupMenu.Item[ulTemp].ucItemId,
                                                    pEvent->CmdStru.SetupMenu.ulItemNum);

        usLength += (VOS_UINT16)At_HexAlpha2AsciiString(STK_PRINT_MAX_LEN,(VOS_INT8 *)g_pucSTKSndCodeAddr,(VOS_UINT8 *)g_pucSTKSndCodeAddr+ usLength,
                                                    pEvent->CmdStru.SetupMenu.Item[ulTemp].pucItemText,
                                                    pEvent->CmdStru.SetupMenu.Item[ulTemp].ucLen);

        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                                    "\",%d",ucHelpInfo);

        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                                ",");

        if(1 == pEvent->CmdStru.SetupMenu.OP_INAIndicator)
        {
            usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                                    "%d",
                                                    pEvent->CmdStru.SetupMenu.INAIndicator.pucINAIl[ulTemp]);
        }

        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                                "%s",g_aucCrLf);
    }

    *pusDataLen = usLength;

    return;
}

/*****************************************************************************
 Prototype      : At_SatCallBackFunc
 Description    : Sat��Ϣ������
 Input          :
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-07-04
    Author      : zhuli
    Modification: Created function
*****************************************************************************/
VOS_VOID At_STKSetupIdleTCmdPrint(VOS_UINT16* pusDataLen, SI_STK_DATA_INFO_STRU* pEvent)
{
    VOS_UINT16 usLength;

    usLength = *pusDataLen;

    usLength += (VOS_UINT16)At_HexText2AsciiString(STK_PRINT_MAX_LEN,(VOS_INT8 *)g_pucSTKSndCodeAddr,(VOS_UINT8 *)g_pucSTKSndCodeAddr+ usLength,
                                &pEvent->CmdStru.IdleText.TextStr);

    if(1 == pEvent->CmdStru.IdleText.OP_IconId)
    {
        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        ",%d",pEvent->CmdStru.IdleText.IconId.ucId);
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        ",");
    }

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        "%s",g_aucCrLf);

    *pusDataLen = usLength;

    return;
}

/*****************************************************************************
 Prototype      : At_SatCallBackFunc
 Description    : Sat��Ϣ������
 Input          :
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-07-04
    Author      : zhuli
    Modification: Created function
*****************************************************************************/
VOS_VOID At_STKLBrowserCmdPrint(VOS_UINT16* pusDataLen, SI_STK_DATA_INFO_STRU* pEvent)
{
    VOS_UINT16 usLength;
    VOS_UINT32 ulTemp;
    VOS_UINT8  *pucURL;

    usLength = *pusDataLen;

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                    "\"");

    if (0 < pEvent->CmdStru.LaunchBrowser.URL.ulLen)
    {
        At_UsimGsm7bit2AsciiTransfer(pEvent->CmdStru.LaunchBrowser.URL.pucURL,
                                    &pEvent->CmdStru.LaunchBrowser.URL.ulLen);

        pucURL = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_AT, DYNAMIC_MEM_PT,
                              pEvent->CmdStru.LaunchBrowser.URL.ulLen + sizeof(VOS_UINT8));/* ����ĩβ'\0' */

        if (VOS_NULL_PTR == pucURL)
        {
            STK_ERROR_LOG("At_STKLBrowserCmdPrint:VOS_MemAlloc Fail!");

            return;
        }

        /*lint -e534*/
        VOS_MemCpy(pucURL, pEvent->CmdStru.LaunchBrowser.URL.pucURL,
                    pEvent->CmdStru.LaunchBrowser.URL.ulLen);
        /*lint +e534*/

        pucURL[pEvent->CmdStru.LaunchBrowser.URL.ulLen] = '\0';

        usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        "%s", pucURL);

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_AT, pucURL);
        /*lint +e534*/
    }

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                    "\"");

    ulTemp = pEvent->CmdDetail.ucCommandQua;

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                                ",%d%s",ulTemp,g_aucCrLf);

    *pusDataLen = usLength;

    return;
}

/*****************************************************************************
 Prototype      : At_STKUndifinedCmdPrint
 Description    : Sat��Ϣ������,δ��APP����ӿڵ�����
 Input          :
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-07-04
    Author      : zhuli
    Modification: Created function
*****************************************************************************/
VOS_VOID At_STKUndifinedCmdPrint(VOS_UINT16 *pusDataLen, SI_STK_DATA_INFO_STRU* pEvent)
{
    VOS_UINT16 usLength;

    usLength = *pusDataLen;

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                    "%s", "Cmd Undifined");

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        "%s",g_aucCrLf);

    *pusDataLen = usLength;
}

/*****************************************************************************
 Prototype      : At_SatCallBackFunc
 Description    : Sat��Ϣ������
 Input          :
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-07-04
    Author      : zhuli
    Modification: Created function
*****************************************************************************/
VOS_VOID At_STKRefreshCmdPrint(VOS_UINT16* pusDataLen, SI_STK_DATA_INFO_STRU * pEvent)
{
    VOS_UINT16 usLength;

    /* ���ݱ�˲��Խ����ȷ��Qualiti���ת�� */
    if (pEvent->CmdDetail.ucCommandQua <= 4)
    {
        pEvent->CmdDetail.ucCommandQua = 4 - pEvent->CmdDetail.ucCommandQua;
    }

    usLength = *pusDataLen;

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,
                                        (VOS_CHAR *)g_pucSTKSndCodeAddr,
                                        (VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        "%d",pEvent->CmdDetail.ucCommandQua);

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr+ usLength,
                                        "%s",g_aucCrLf);

    *pusDataLen = usLength;

    return;
}

/*****************************************************************************
 Prototype      : At_SatCallBackFunc
 Description    : Sat��Ϣ������
 Input          :
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-07-04
    Author      : zhuli
    Modification: Created function
*****************************************************************************/

SI_STK_ATPRINT_STRU gAtSTKCmdPrint[] =
{
    {SI_STK_DISPLAYTET,             At_STKDisplayTextCmdPrint},
    {SI_STK_GETINKEY,               At_STKGetInKeyCmdPrint},
    {SI_STK_GETINPUT,               At_STKGetInputCmdPrint},
    {SI_STK_PLAYTONE,               At_STKPlayToneCmdPrint},
    {SI_STK_SELECTITEM,             At_STKSelItemCmdPrint},
    {SI_STK_SETUPMENU,              At_STKSetupMenuCmdPrint},
    {SI_STK_SETUPIDLETEXT,          At_STKSetupIdleTCmdPrint},
    {SI_STK_LAUNCHBROWSER,          At_STKLBrowserCmdPrint},
    {SI_STK_LANGUAGENOTIFICATION,   At_STKUndifinedCmdPrint},
    {SI_STK_SETFRAMES,              At_STKUndifinedCmdPrint},
    {SI_STK_GETFRAMESSTATUS,        At_STKUndifinedCmdPrint},
    {SI_STK_REFRESH,                At_STKRefreshCmdPrint}
};

VOS_UINT32 At_STKCMDDataPrint(SI_STK_DATA_INFO_STRU *pEvent, VOS_UINT32 EventType)
{
    VOS_UINT16 usLength = 0;
    VOS_UINT32 ulResult;
    VOS_UINT8  ucCmdType;
    VOS_UINT32 i;

    ulResult = At_ChangeSTKCmdNo(pEvent->SatType, &ucCmdType);

    if(VOS_ERR == ulResult)
    {
        return VOS_ERR;
    }

    usLength += (VOS_UINT16)At_sprintf(STK_PRINT_MAX_LEN,(VOS_CHAR *)g_pucSTKSndCodeAddr,(VOS_CHAR *)g_pucSTKSndCodeAddr + usLength,
                                    "%s",gaucAtStgi);

    for(i=0; i<(sizeof(gAtSTKCmdPrint)/sizeof(SI_STK_ATPRINT_STRU)); i++)
    {
        if(pEvent->SatType == gAtSTKCmdPrint[i].CmdType)
        {
            gAtSTKCmdPrint[i].pfATPrint(&usLength,pEvent);

            break;
        }
    }

    if(i == (sizeof(gAtSTKCmdPrint)/sizeof(SI_STK_ATPRINT_STRU)))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 Prototype      : SI_STK_SendATMsg
 Description    : STK���͸�AT��Ϣ����
 Input          : pstData:��Ϣ����
 Output         : ��
 Return Value   : ��

 History        : ---
  1.Date        : 2011-10-04
    Author      : zhuli
    Modification: Created function
*****************************************************************************/
/*lint -e550*/
/*lint -e830*/
VOS_VOID SI_STK_SendATMsg(SI_STK_EVENT_INFO_STRU* pstData)
{
    MN_APP_STK_AT_CNF_STRU *pstMsg;

    pstMsg = (MN_APP_STK_AT_CNF_STRU*)VOS_AllocMsg(MAPS_STK_PID, sizeof(MN_APP_STK_AT_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)  /*�����ڴ�ʧ�ܻ�����*/
    {
        return;
    }

    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ulMsgId         = STK_AT_EVENT_CNF;

    /*lint -e534*/
    VOS_MemCpy(&pstMsg->stSTKAtCnf, pstData, sizeof(SI_STK_EVENT_INFO_STRU));
    /*lint +e534*/

    if(VOS_OK != VOS_SendMsg(MAPS_STK_PID, pstMsg))
    {
        STK_ERROR_LOG1("SI_STK_SendReportMsg: Send Msg %d to AT Error", (VOS_INT32)STK_AT_EVENT_CNF);
    }

    return;
}
/*lint +e550*/
/*lint +e830*/

/*****************************************************************************
 Prototype      : SI_STK_SendATPrintMsg
 Description    : STK���͸�AT��Ϣ����
 Input          : pstData:��Ϣ����
 Output         : ��
 Return Value   : ��

 History        : ---
  1.Date        : 2011-10-04
    Author      : zhuli
    Modification: Created function
*****************************************************************************/
/*lint -e550*/
/*lint -e830*/
VOS_VOID SI_STK_SendATPrintMsg(VOS_UINT16 usClinetID, VOS_UINT8 *pucData, VOS_UINT32 ulDataLen, VOS_UINT8 ucCmdQualify)
{
    MN_APP_STK_AT_DATAPRINT_STRU *pstMsg;

    pstMsg = (MN_APP_STK_AT_DATAPRINT_STRU*)VOS_AllocMsg(MAPS_STK_PID, sizeof(MN_APP_STK_AT_DATAPRINT_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)  /*�����ڴ�ʧ�ܻ�����*/
    {
        return;
    }

    pstMsg->ulReceiverPid           = WUEPS_PID_AT;
    pstMsg->ulMsgId                 = STK_AT_DATAPRINT_CNF;
    pstMsg->stSTKAtPrint.ClientId   = usClinetID;
    pstMsg->stSTKAtPrint.OpId       = STK_OPID_VALUE;
    pstMsg->stSTKAtPrint.DataLen    = ulDataLen;
    pstMsg->stSTKAtPrint.CmdQualify = ucCmdQualify;

    /*lint -e534*/
    VOS_MemCpy(pstMsg->stSTKAtPrint.aucData, pucData, ulDataLen);
    /*lint +e534*/

    if(VOS_OK != VOS_SendMsg(MAPS_STK_PID, pstMsg))
    {
        STK_ERROR_LOG1("SI_STK_SendReportMsg: Send Msg %d to AT Error", (VOS_INT32)STK_AT_DATAPRINT_CNF);
    }

    return;
}
/*lint +e550*/
/*lint +e830*/

/*****************************************************************************
 Prototype      : At_SatCallBackFunc
 Description    : Sat��Ϣ������
 Input          : pEvent:s�ϱ����¼�����
 Output         : ��
 Return Value   : ��

 History        : ---
  1.Date        : 2011-10-04
    Author      : zhuli
    Modification: Created function
*****************************************************************************/
VOS_VOID At_STKCallBackFunc(SI_STK_EVENT_INFO_STRU *pstEvent)
{
    VOS_UINT32              ulResult = VOS_OK;
    VOS_UINT8               ucCommandQua;

    if(VOS_OK != pstEvent->STKErrorNo)
    {
        SI_STK_SendATMsg(pstEvent);

        return;
    }

    ucCommandQua = pstEvent->STKCmdStru.CmdDetail.ucCommandQua;


    if ((VOS_FALSE == SI_STK_CheckSupportAP())
        &&(SI_STK_GET_CMD_RSP_EVENT == pstEvent->STKCBEvent))
    {
        ulResult = At_STKCMDDataPrint(&pstEvent->STKCmdStru,pstEvent->STKCBEvent);

        if(VOS_OK == ulResult)
        {
            SI_STK_SendATPrintMsg(pstEvent->ClientId,g_pucSTKSndCodeAddr,VOS_StrLen((VOS_CHAR*)g_pucSTKSndCodeAddr), ucCommandQua);

            return;
        }
        else
        {
            STK_ERROR_LOG("At_STKCallBackFunc: Print STK Data Error");

            pstEvent->STKErrorNo  = ulResult;
        }
    }

    SI_STK_SendATMsg(pstEvent);

    return;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


