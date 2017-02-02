#ifndef _TRNG_API_H_
#define _TRNG_API_H_


#ifdef __cplusplus
extern "C"
{
#endif


/* ʱ������ֵ���󳤶� */


/* ���ֿռ��"��ֵ" */
#define ACL_TRNG_MAXBUCKET 4099

#define ACL_ABSOLUTEMAX 4102444799  /* 23:59:59 31 Sep 2099 4134067140 23:59:00 31 12 2100 */


/* ��ǰʱ�����ݽṹ */
/* ����ʱ�����ʹ�õĺ� */
#define ACL_PERIODIC_SUN   0x1        /* 0000 0001 */
#define ACL_PERIODIC_MON   0x2        /* 0000 0010 */
#define ACL_PERIODIC_TUE   0x4        /* 0000 0100 */
#define ACL_PERIODIC_WED   0x8        /* 0000 1000 */
#define ACL_PERIODIC_THU   0x10       /* 0001 0000 */
#define ACL_PERIODIC_FRI   0x20       /* 0010 0000 */
#define ACL_PERIODIC_SAT   0x40       /* 0100 0000 */
#define ACL_PERIODIC_DAILY (ACL_PERIODIC_MON|ACL_PERIODIC_TUE|ACL_PERIODIC_WED|\
    ACL_PERIODIC_THU|ACL_PERIODIC_FRI|ACL_PERIODIC_SAT|ACL_PERIODIC_SUN)
                                  /* 0111 1111 */
#define ACL_PERIODIC_WEEKDAY (ACL_PERIODIC_MON|ACL_PERIODIC_TUE|ACL_PERIODIC_WED|\
    ACL_PERIODIC_THU|ACL_PERIODIC_FRI)
                                  /* 0011 1110 */
#define ACL_PERIODIC_WEEKEND (ACL_PERIODIC_SAT|ACL_PERIODIC_SUN)
                                  /* 0100 0001 */
#define ACL_PERIODIC_DAY_TO_DAY 0x80  /* 1000 0000 */

/*
typedef struct tagStrToWeekday
{
    CHAR * szName;
    LONG lHelp;
    LONG lVal;
} STRTOWEEKDAY;
*/

/*  ����ʱ������ݽṹ
    ģ��֧�ֵ���ʼʱ��Ϊ�� 00:00  1 jan 1993
    ģ��֧�ֵ���ֹʱ��Ϊ�� 23:59 31 dec 2035
*/

/**
* @defgroup ACLS ACL Structures
* @ingroup accss ACL API Reference
*/

/**
* @defgroup tagAbsoluteTimeRange ACL_ABSOLUTETIMERANGE_S/PACL_ABSOLUTETIMERANGE_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagAbsoluteTimeRange
* {
*     ULONG m_ulStart;
*     ULONG m_ulEnd;
*     ULONG m_ulIndex;
*     struct tagAbsoluteTimeRange *m_pNext;
* }ACL_ABSOLUTETIMERANGE_S, *PACL_ABSOLUTETIMERANGE_S;
* @endcode
*
* @par Description
* This structure is for absolute time range. It is used in the structure ACL_TIMERANGE_S. This defines 
* the absolute time period for which the timer should be active.
*
* @datastruct m_ulStart The timer should be active from this time. This value will be calculated from 
* the number of seconds since "1970-1-1 0:0:0", till the mentioned time.
* @datastruct m_ulEnd The timer should be inactive after this time. This value will be calculated from 
* the number of seconds since "1970-1-1 0:0:0", till the mentioned time.
* @datastruct m_ulIndex This is the absolute timer index and ranges from 1 - 12.
* @datastruct m_pNext Pointer to next absolute timer.
*/
typedef struct tagAbsoluteTimeRange
{
    ULONG m_ulStart;/*��������ʾ*/
    ULONG m_ulEnd;    /*��������ʾ*/
    ULONG m_ulIndex;        /*add by wangning for TRNG MIB*/
    struct tagAbsoluteTimeRange *m_pNext;
}ACL_ABSOLUTETIMERANGE_S, *PACL_ABSOLUTETIMERANGE_S;



/*  ����ʱ������ݽṹ
    ��m_ucDayofWeekΪ"1000 0000"ʱ��
      m_ulStart��m_ulEndΪ���"����00:00"ʱ�̵ľ���ʱ�䣻
      ���磺
        m_ulStart = 1950 = ��N_day * 24HOUR) * 60 MINUTE + N_hour * 60 MINUTE + N_minute ��
        1950 / 60 = 32��Сʱ���� + 1/5������������
                    32 / 24 = 1�������� + 1/3��Сʱ������
    ��m_ucDayofWeek��Ϊ"1000 0000"ʱ��
      m_ulStart��m_ulEndΪ���"����00:00"ʱ�̵ľ���ʱ�䣻
*/



typedef struct tagPeriodicTimeRange
{
    UCHAR m_ucDayofWeek;
    UCHAR m_aucPadding[3];  /*Padding - ARM Byte Allignment*/
    ULONG m_ulStart;
    ULONG m_ulEnd;
    ULONG m_ulIndex;        /*add by wangning for TRNG MIB*/
    struct tagPeriodicTimeRange *m_pNext;
} ACL_PERIODICTIMERANGE_S, * PACL_PERIODICTIMERANGE_S;



/* ʱ������ݽṹ*/
/**
* @defgroup tagTimeRange ACL_TIMERANGE_S/PACL_TIMERANGE_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagTimeRange
* {
*     CHAR m_szName[ACL_MAX_TR_NAME_LEN];
*     ULONG ulTrngIndex;
*     BOOL_T m_bInFlag;
*     PACL_ABSOLUTETIMERANGE_S m_pstAbsoluteTimeRange;
*     PACL_PERIODICTIMERANGE_S m_pstPeriodicTimeRange;
*     struct tagTimeRange * m_pNext;
* } ACL_TIMERANGE_S, *PACL_TIMERANGE_S;
* @endcode
*
* @par Description
* This is timer structure, which contains pointers to ACL_ABSOLUTETIMERANGE_S and ACL_PERIODICTIMERANGE_S. This 
* timer determines when this timer is active. A timer can be identified by its name.
* 
* @datastruct m_szName Timer name.
* @datastruct ulTrngIndex Timer index.
* @datastruct m_bInFlag Flag to indicate if timer is active or not. A timer is said to be active when current time 
* satisfies both periodic and absolute configured times. It can have the following values:
*	- BOOL_TRUE - Active
*	- BOOL_FALSE - Inactive
* @datastruct m_pstAbsoluteTimeRange Pointer to first absolute timer.
* @datastruct m_pstPeriodicTimeRange Pointer to first periodic timer.
* @datastruct m_pNext Pointer to next timer.
*/
typedef struct tagTimeRange
{
    /*This structure is not 4Byte aligned, No need to align it
    as this will be used only Control Plane and not in Data Plane*/
    CHAR m_szName[ACL_MAX_TR_NAME_LEN];              /* ʱ����� */
    UCHAR m_ucPadding;                                /*Padding - ARM Byte Allignment*/
    BOOL_T m_bInFlag;                                 /* ��ǰʱ���Ƿ��ڸ�ʱ����� */
    ULONG ulTrngIndex;                              /*ʱ�����������add by wangning for TRNG MIB*/
    PACL_ABSOLUTETIMERANGE_S m_pstAbsoluteTimeRange; /* ָ��һ������ʱ��� */
    PACL_PERIODICTIMERANGE_S m_pstPeriodicTimeRange; /* ָ��һ������ʱ����б� */
    struct tagTimeRange * m_pNext;               /* ָ����һ��ʱ��ε�ָ�� */
} ACL_TIMERANGE_S, *PACL_TIMERANGE_S;



/* ʱ������ֿռ� */



/*PACL_TIMERANGE_S ACL_TRNG_GetByName(CHAR *szName)*/
/**
* @defgroup ACL_TRNG_GetByName ACL_TRNG_GetByName
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* PACL_TIMERANGE_S ACL_TRNG_GetByName(CHAR *szName);
* @endcode
*
* @par Description
* This function is used to get the timer pointer based on the timer name.
*
* @param[in] szName Timer name []
* @param[out]   []
*
* @retval PACL_TIMERANGE_S Indicates timer pointer [|]
* @retval PACL_TIMERANGE_S Indicates no timer exist [NULL|]
*
* @par Dependency
* acl_trng_api.h
*
*
* @par Note
* \n
*
* None
*
*
* @par Related Topics
* None
*/
extern PACL_TIMERANGE_S ACL_TRNG_GetByName(CHAR *szName);

/*ULONG ACL_TRNG_AddTimeRange(CHAR * szName)*/
/**
* @defgroup ACL_TRNG_AddTimeRange ACL_TRNG_AddTimeRange
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_TRNG_AddTimeRange(CHAR * szName);
* @endcode
*
* @par Description
* This function is used to add a timer. You can add a maximum of 256 timers.
* 
* @param[in] szName It is the timer name. Maximum length of timer is 32. The name should 
* not be "ALL" (any cases that is, all or All). []
* @param[out]   []
*
* @retval ULONG In case of success ACL_TRNG_OK is returned. In error scenarios, corresponding
* unique error code is returned. [ACL_TRNG_OK |]
*
* @par Dependency
* acl_trng_api.h
*
*
* @par Note
* \n
*
* None
*
*
* @par Related Topics
* ACL_TRNG_DelTimeRange
*/
extern ULONG ACL_TRNG_AddTimeRange(CHAR * szName);


/*ULONG ACL_TRNG_DelTimeRange(CHAR * szName)*/
/**
* @defgroup ACL_TRNG_DelTimeRange ACL_TRNG_DelTimeRange
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_TRNG_DelTimeRange(CHAR * szName);
* @endcode
*
* @par Description
* This function deletes the timer name.
*
* @param[in] szName Timer name to be deleted []
* @param[out]   []
*
*
* @retval ULONG In case of success ACL_TRNG_OK is returned. In error scenarios, corresponding
* unique error code is returned. [ACL_TRNG_OK |]
*
* @par Dependency
* acl_trng_api.h
*
*
* @par Note
* \n
*
* None
*
*
* @par Related Topics
* ACL_TRNG_AddTimeRange
*/
extern ULONG ACL_TRNG_DelTimeRange(CHAR * szName);


extern ULONG ACL_TRNG_AddPeriodic(PACL_TIMERANGE_S pThis, UCHAR ucDayofWeek, ULONG ulStartTime,
    ULONG ulEndTime, ULONG ulSubIndex);

/*ULONG ACL_TRNG_DelPeriodic(PACL_TIMERANGE_S pThis, UCHAR ucDayofWeek,
    ULONG ulStartTime, ULONG ulEndTime)*/
/**
* @defgroup ACL_TRNG_DelPeriodic ACL_TRNG_DelPeriodic
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_TRNG_DelPeriodic(PACL_TIMERANGE_S pThis, UCHAR ucDayofWeek,
*     ULONG ulStartTime, ULONG ulEndTime);
* @endcode
*
* @par Description
* This function deletes a periodic timer from a specified timer. A periodic timer can be identified by its periodicity. 
* The periodic timer can be deleted by providing the periodicity.
*
* @param[in] pThis Timer from which the periodic timer should be deleted. []
* @param[in] ucDayofWeek Same as used in ACL_TRNG_AddPeriodic. []
* @param[in] ulStartTime Same as used in ACL_TRNG_AddPeriodic []
* @param[in] ulEndTime Same as used in ACL_TRNG_AddPeriodic []
* @param[out]   []
*
* @retval ULONG In case of success ACL_TRNG_OK is returned. In error scenarios, corresponding
* unique error code is returned. [ACL_TRNG_OK |]
*
* @par Dependency
* acl_trng_api.h
*
*
* @par Note
* \n
*
* None
*
*
* @par Related Topics
* ACL_TRNG_AddPeriodic
*/
extern ULONG ACL_TRNG_DelPeriodic(PACL_TIMERANGE_S pThis, UCHAR ucDayofWeek,
    ULONG ulStartTime, ULONG ulEndTime);

/*ULONG ACL_TRNG_AddAbsolute(PACL_TIMERANGE_S pThis, ULONG ulStartTime, ULONG ulEndTime, ULONG ulSubIndex)*/
/**
* @defgroup ACL_TRNG_AddAbsolute ACL_TRNG_AddAbsolute
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_TRNG_AddAbsolute( PACL_TIMERANGE_S pThis, 
*                             ULONG ulStartTime, 
*                             ULONG ulEndTime, 
*                             ULONG ulSubIndex);
* @endcode
*
* @par Description
* This function is used to configure the absolute time in a timer. That is, absolute period when a timer should be 
* active. Maximum of 12 absolute timers can be added in a timer. Two absolute timers with same period cannot be added.
*
* @param[in] pThis Pointer to the timer to which the periodic timer has to be configured. []
* @param[in] ulStartTime Start time in seconds (Calculated from from "1970-1-1 0:0:0"). Maximum value is 
* ACL_ABSOLUTEMAX. For calculating the time in seconds for the parameters, the function "ACL_TRNG_TimeToSeconds" 
* can be used. []
* @param[in] ulEndTime End time in seconds (Calculated from from "1970-1-1 0:0:0"). Maximum value is ACL_ABSOLUTEMAX.
* For calculating the time in seconds for the parameters, the function "ACL_TRNG_TimeToSeconds" can be used. []
* @param[in] ulSubIndex Absolute timer index, the value ranges from 1 to 12. One cannot add two absolute 
* timers at same index until existing one at that index is deleted. If value "0" is used for index, index is 
* assigned automatically. []
* @param[out]   []
*
*
*
* @retval Adding absolute timer is success [ULONGACL_TRNG_OK | ]
* @retval Timer pointer is Null [ULONGACL_TRNG_ADD_ABS_TMR_NULL_POINTER_FOR_TIMER | ]
* @retval Invalid index for absolute timer [ULONGACL_TRNG_ADD_ABS_TMR_INVALID_INDEX | ]
* @retval Start time should not be greater than End time [ULONGACL_TRNG_ADD_ABS_TMR_START_TIME_MORE_THAN_END_TIME | ]
* @retval Start/End time cannot maximum time period supported [ULONGACL_TRNG_ADD_ABS_TMR_TIME_OUT_OF_RANGE | ]
* @retval Memory allocation failed [ULONGACL_TRNG_ADD_ABS_TMR_CREATION_FAILED | ]
* @retval Duplicate Time Range [ULONGACL_TRNG_ADD_ABS_TMR_DUPLICATE_TIME_RANGE | ]
* @retval Wrong timer index [ULONGACL_TRNG_ADD_ABS_TMR_WRONG_TMR_INDEX | ]
* @retval Maximum timer reached [ULONGACL_TRNG_ADD_ABS_TMR_MAX_TIMERS_REACHED | ]
* @retval Timer insert failed [ULONGACL_TRNG_ADD_ABS_TMR_FIRST_INSERT_FAILED | ]
* @retval Duplicate timer ID [ULONGACL_TRNG_ADD_ABS_TMR_DUPLICATE_FAILED | ]
* @retval Inserting absolute timer failed [ULONGACL_TRNG_ADD_ABS_TMR_INSERT_FAILED | ]
*
* @par Dependency
* acl_trng_api.h
*
*
* @par Note
* \n
*
* None
*
*
* @par Related Topics
* ACL_TRNG_DelAbsolute
*/

extern ULONG ACL_TRNG_AddAbsolute(PACL_TIMERANGE_S pThis, ULONG ulStartTime, ULONG ulEndTime, ULONG ulSubIndex);

/*ULONG ACL_TRNG_DelAbsolute(PACL_TIMERANGE_S pThis, ULONG ulStartTime, ULONG ulEndTime)*/
/**
* @defgroup ACL_TRNG_DelAbsolute ACL_TRNG_DelAbsolute
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_TRNG_DelAbsolute(PACL_TIMERANGE_S pThis, 
*                            ULONG ulStartTime, 
*                            ULONG ulEndTime);
* @endcode
*
* @par Description
* This function deletes an absolute timer from a specified timer. An absolute timer can be identified by its absolute 
* period. The absolute timer can be deleted by providing the absolute period.
* 
* @param[in] pThis Timer from which the absolute timer should be deleted. []
* @param[in] ulStartTime Same as used in ACL_TRNG_AddAbsolute. []
* @param[in] ulEndTime Same as used in ACL_TRNG_AddAbsolute. []
* @param[out]   []
*
*
* @retval ULONG Delete absolute timer is success [ACL_TRNG_OK | ]
* @retval ULONG Null timer range [ACL_TRNG_DEL_ABS_TMR_NULL_PTR | ]
* @retval ULONG No absolute timers are present [ACL_TRNG_DEL_ABS_TMR_NO_ABSOLUTE_TIMERS | ]
* @retval ULONG Absolute timer does not exist [ACL_TRNG_DEL_ABS_TMR_NO_TIMER_EXIST | ]
*
* @par Dependency
* acl_trng_api.h
*
*
* @par Note
* \n
*
* None
*
*
* @par Related Topics
* ACL_TRNG_AddAbsolute
*/
extern ULONG ACL_TRNG_DelAbsolute(PACL_TIMERANGE_S pThis, ULONG ulStartTime, ULONG ulEndTime);

/*ULONG ACL_TRNG_TimeToSeconds (ULONG ulMin, ULONG ulHour, ULONG ulDate, ULONG ulMonth, ULONG ulYear,
    ULONG *pulRetTimeInSeconds)*/
/**
* @defgroup ACL_TRNG_TimeToSeconds ACL_TRNG_TimeToSeconds
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_TRNG_TimeToSeconds (ULONG ulMin, ULONG ulHour, ULONG ulDate, ULONG ulMonth,
*     ULONG ulYear, ULONG *pulRetTimeInSeconds);
* @endcode
*
* @par Description
* This function calculates the time in seconds from "1970-1-1 0:0:0" till the date and time provided.
*
* @param[in] ulMin The minutes [0-59]
* @param[in] ulHour The hours [0-23]
* @param[in] ulDate The date. The maximum value varies with the specified month and year [1-31]
* @param[in] ulMonth The month [1-12]
* @param[in] ulYear The year [1970-2099]
* @param[in,out] pulRetTimeInSeconds The calculated seconds for the specified time will be placed in this 
* variable. []
*
* @retval ULONG In case of success ACL_TRNG_OK is returned. In error scenarios, corresponding
* unique error code is returned. [ACL_TRNG_OK |]
*
* @par Dependency
* acl_trng_api.h
*
*
* @par Note
* \n
*
* None
*
*
* @par Related Topics
* None
*/
extern ULONG ACL_TRNG_TimeToSeconds (ULONG ulMin, ULONG ulHour, ULONG ulDate, ULONG ulMonth,
    ULONG ulYear, ULONG *pulRetTimeInSeconds);


/**
* @defgroup ACL_TRNG_ShowTimeRange ACL_TRNG_ShowTimeRange
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACL_TRNG_ShowTimeRange (CHAR * szName);
* @endcode
*
* @par Description
* This function displays the timer configuration including the following:
*	- Absolute timer details
*	- Periodic timer details
*	- Active OR Inactive
* \n\n
* A timer is active only if current time satisfies both Absolute and Periodic timer configurations.
* The state change of timer (Active or Inactive) happens when timer is refreshed. The refresh is done 
* with maximum delay of one minute. If the timer name is provided as "ALL", (irrespective of cases) the function 
* displays all timer status with details specified above.
* 
* @param[in] szName Pointer to the timer name for which the configuration needs to be displayed. []
* @param[out]   []
*
* @retval ULONG In case of success ACL_TRNG_OK is returned. In error scenarios, corresponding
* unique error code is returned. [ACL_TRNG_OK |]
*
* @par Dependency
* acl_trng_api.h
*
*
* @par Note
* \n
*
* None
*
*
* @par Related Topics
* None
*/
VOID ACL_TRNG_ShowTimeRange (CHAR * szName);



#ifdef __cplusplus
}
#endif


#endif

