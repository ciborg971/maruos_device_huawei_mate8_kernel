#include <osl_common.h>
#define DPM_OK 0
#define DPM_ERROR (-1)
enum dpm_status{
	  PMSG_SUSPEND,
	  PMSG_RESUME,
  };

enum dpm_debug_e{
	DPM_IPF,
	DPM_SOCP,
	DPM_TEM,
	DPM_PMU,
	DPM_PASTAR,
	DPM_BUTTON,
	};
/*****************************************************************************
* �� �� ��     : dpm_suspend
*
* ��������  : �ص�m3�������suspend�ص�����
*
* �������  : ��
* �������  : ��
*
* �� �� ֵ     : DPM_OK & DPM_ERROR
*
* �޸ļ�¼  : 2013��6��14��   lixiaojie

*****************************************************************************/
 s32 dpm_suspend(void);
/*****************************************************************************
* �� �� ��     : dpm_resume
*
* ��������  : �ص�m3�������resume�ص�����
*
* �������  : ��
* �������  : ��
*
* �� �� ֵ     : DPM_OK & DPM_ERROR
*
* �޸ļ�¼  : 2013��6��14��   lixiaojie

*****************************************************************************/
 s32 dpm_resume(void);

 s32 dpm_suspend_buck3off(void);
 s32 dpm_resume_buck3off(void);

