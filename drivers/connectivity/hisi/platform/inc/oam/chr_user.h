/*
 * =====================================================================================
 *
 *       Filename:  chrdrv.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  09/18/2014 02:53:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifdef __cpluscplus
	#if __cplusplus
	extern "C" {
	#endif
#endif

#ifndef __CHR_USER_H__
#define __CHR_USER_H__

/*
 * 1 Other Include Head File
 */

typedef enum chr_LogPriority{
	CHR_LOG_DEBUG = 0,
	CHR_LOG_INFO,
	CHR_LOG_WARN,
	CHR_LOG_ERROR,
}CHR_LOGPRIORITY;

typedef enum chr_LogTag{	
	CHR_LOG_TAG_PLAT = 0,
	CHR_LOG_TAG_WIFI,
	CHR_LOG_TAG_GNSS,
	CHR_LOG_TAG_BT,
	CHR_LOG_TAG_FM,
	CHR_LOG_TAG_NFC,
}CHR_LOG_TAG;

#define CHR_LOG(prio, tag, fmt...) __chr_printLog(prio, tag, ##fmt)
extern int __chr_printLog(CHR_LOGPRIORITY prio, CHR_LOG_TAG tag, const char *fmt,...);

#endif

#ifdef __cpluscplus
	#if __cplusplus
		}
	#endif
#endif
