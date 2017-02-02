/*******************************************************************************
*
*
*                Copyright 2014, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              Iatk_fac.h
*
*  Project Code: VISPV3R2
*   Module Name: ATK Module  
*  Date Created: 2014-08-07
*        Author: a00900892
*   Description: Implements Component factory creation and Query
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2014-08-07  a00900892            Create
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _I_ATK_FAC_H_
#define _I_ATK_FAC_H_


/* For implement of QuerfyInstance() */
typedef struct tag_ATK_INT_OBJ_S
{
    IIF_COMP_ATK_ComIntFUN   *ComInt_Atk_FUN ;
    IIF_COMP_ATK_ComIntCFG   *ComInt_Atk_CFG;
}ATK_INT_OBJ_S;

ULONG ImplAtkFactoryQueryInterface(IUnknown * This, COMP_IID iid, LPVOID * ppvObj);
ULONG ImplAtkFactoryCreateInstance(IComponentFactory *This,  COMP_IID iid, VOID **ppvObj );

/* atk component Instance */
extern ATK_INT_OBJ_S   g_stIP_ATK_INT_OBJ;
/* Component interface of function */
extern IIF_COMP_ATK_ComIntFUN g_IComInt_Atk_FUN ;
/* Component interface of configration */
extern IIF_COMP_ATK_ComIntCFG g_IComInt_Atk_CFG;

#endif  /* _I_ATK_FAC_H_ */

#ifdef  __cplusplus
}
#endif

