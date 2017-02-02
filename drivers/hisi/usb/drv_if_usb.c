

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  <linux/slab.h>
#include  <linux/kernel.h>
#include  <linux/module.h>
#include  <drv_usb_if.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
PNP_CALLBACK_STACK* pEnableStack = NULL;
PNP_CALLBACK_STACK* pDisableStack = NULL;
DEFINE_SPINLOCK(enable_lock);
DEFINE_SPINLOCK(disable_lock);
static ACM_HANDLE_COMMAND_CB_T pAcmHandleCmdCB= NULL;
int g_ul_reg_enable_count = 0;
int g_ul_reg_disable_count = 0;
int g_usb_enum_complete = 0;


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
   ��NAS�Ľӿ�ʵ�֣�������׮ʵ��
*****************************************************************************/

void BSP_USB_Dump_EnableCBStack(void)
{
    PNP_CALLBACK_STACK* pEnableFunc = NULL;
    USB_API_DBG("BSP_USB_Dump_EnableCBStack enter:%d\n",g_ul_reg_enable_count);

    pEnableFunc = pEnableStack;
    while (pEnableFunc)
    {
        USB_API_DBG("BSP_USB_Dump_EnableCBStack :%p\n",pEnableFunc->pCallback);
        pEnableFunc = pEnableFunc->pPre;
    }

    USB_API_DBG("BSP_USB_Dump_EnableCBStack leave:\n");
}

void BSP_USB_Dump_DisableCBStack(void)
{
    PNP_CALLBACK_STACK* pDisableFunc = NULL;
    USB_API_DBG("BSP_USB_Dump_DisableCBStack enter:%d\n",g_ul_reg_disable_count);

    pDisableFunc = pDisableStack;
    while (pDisableFunc)
    {
        USB_API_DBG("BSP_USB_Dump_DisableCBStack :%p\n",pDisableFunc->pCallback);
        pDisableFunc = pDisableFunc->pPre;
    }

    USB_API_DBG("BSP_USB_Dump_DisableCBStack leave:\n");
}


unsigned int BSP_USB_RegUdiEnableCB(USB_UDI_ENABLE_CB_T pFunc)
{
    PNP_CALLBACK_STACK* tmp = NULL;
    PNP_CALLBACK_STACK* new_stack = NULL;
    USB_API_DBG(" BSP_USB_RegUdiEnableCB :%p\n",pFunc);

    g_ul_reg_enable_count++;
    if (NULL == pFunc) {
        USB_API_DBG("pFunc NULL\n");
        return 1;
    }

    new_stack = (PNP_CALLBACK_STACK*) kmalloc(sizeof(PNP_CALLBACK_STACK), M_ZERO);
    if (NULL == new_stack) {
        USB_API_DBG("BSP_USB_RegUdiEnableCB new_stack NULL\n");
        return 1;
    }

    spin_lock(&enable_lock);
    tmp = pEnableStack;
    pEnableStack = new_stack;
    pEnableStack->pPre = tmp;
    pEnableStack->pCallback = pFunc;

    if(g_usb_enum_complete) {
        spin_unlock(&enable_lock);
        pEnableStack->pCallback();
    } else {
        spin_unlock(&enable_lock);
    }

    return 0;
}


unsigned int BSP_USB_RegUdiDisableCB(USB_UDI_DISABLE_CB_T pFunc)
{
    PNP_CALLBACK_STACK* tmp = NULL;
    PNP_CALLBACK_STACK* new_stack = NULL;
    USB_API_DBG("BSP_USB_RegUdiDisableCB :%p\n",pFunc);

    g_ul_reg_disable_count++;
    if (NULL == pFunc) {
        USB_API_DBG("pFunc NULL\n");
        return 1;
    }
    new_stack = (PNP_CALLBACK_STACK*) kmalloc(sizeof(PNP_CALLBACK_STACK), M_ZERO);
    if (NULL == new_stack) {
        USB_API_DBG("BSP_USB_RegUdiDisableCB new_stack NULL\n");
        return 1;
    }

    spin_lock(&disable_lock);
    tmp = pDisableStack;
    pDisableStack = new_stack;
    pDisableStack->pPre = tmp;
    pDisableStack->pCallback = pFunc;
    spin_unlock(&disable_lock);
    return 0;
}


void BSP_USB_UdiEnableNotify (void)
{
    PNP_CALLBACK_STACK* pEnableFunc = NULL;
    USB_API_DBG("BSP_USB_UdiEnableNotify enter:\n");

    /* ģ��USB����֪ͨ */
    spin_lock(&enable_lock);
    g_usb_enum_complete = 1;
    pEnableFunc = pEnableStack;
    while (pEnableFunc)
    {
        spin_unlock(&enable_lock);
        pEnableFunc->pCallback();
        spin_lock(&enable_lock);
        pEnableFunc = pEnableFunc->pPre;
    }
    spin_unlock(&enable_lock);

    USB_API_DBG("BSP_USB_UdiEnableNotify leave:\n");
}
void BSP_USB_UdiDisableNotify (void)
{
    PNP_CALLBACK_STACK* pDisableFunc = NULL;
    USB_API_DBG("BSP_USB_UdiDisableNotify enter:\n");
    /* ģ��USB����֪ͨ */
    spin_lock(&disable_lock);
    pDisableFunc = pDisableStack;
    while (pDisableFunc)
    {
        spin_unlock(&disable_lock);
        pDisableFunc->pCallback();
        spin_lock(&disable_lock);
        pDisableFunc = pDisableFunc->pPre;
    }
    spin_unlock(&disable_lock);
    g_usb_enum_complete = 0;
    USB_API_DBG("BSP_USB_UdiDisableNotify leave:\n");
}

/*****************************************************************************
 �� �� ��  : BSP_USB_RegUdiEnableCB
 ��������  : ����ע��acm����ͨ�������ӿڣ�ע��ӿ���gser_request_complete
             �б�����
 �������  : ACM_HANDLE_COMMAND_CB_T pFunc  : acm����ͨ�������ص�����ָ��
 �������  : ��
 �� �� ֵ  : unsigned int: 0��ʾ�ɹ� 1��ʾʧ��,��VOS����ķ���ֵ����һ��
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int BSP_ACM_RegCmdHandle(ACM_HANDLE_COMMAND_CB_T pFunc)
{
    if (NULL == pFunc)
    {
        USB_API_DBG("pFunc NULL\n");
        return 1;
    }

    pAcmHandleCmdCB = pFunc;

    return 0;
}

/*****************************************************************************
 �� �� ��  : BSP_ACM_CmdHandle
 ��������  : ִ��acm����ͨ�������ص��ӿ�
 �������  : cmd        ����ͨ������
             interface  ��������Ľӿں�
             buf        ����������
             size       ���������ݴ�С

 �������  : ��
 �� �� ֵ  : int
 ���ú���  :
 ��������  :gser_request_complete
*****************************************************************************/
int BSP_ACM_CmdHandle(int cmd, int tty_idx, char *buf, int size)
{
    int ret = 0;
    if (NULL == pAcmHandleCmdCB)
    {
        USB_API_DBG("pFunc NULL\n");
        return -1;
    }

    ret = pAcmHandleCmdCB(cmd, tty_idx, buf, size);
    return ret;
}



/*�ṩ��NAS�Ľӿ�*/
EXPORT_SYMBOL(BSP_USB_RegUdiEnableCB);
EXPORT_SYMBOL(BSP_USB_RegUdiDisableCB);
EXPORT_SYMBOL(BSP_USB_UdiEnableNotify);
EXPORT_SYMBOL(BSP_USB_UdiDisableNotify);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
