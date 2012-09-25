/*
 * SrvComm.h
 *
 * Created: 31/05/2012 16:04:46
 *  Author: berryer
 */ 


#ifndef SRVCOMM_H_
#define SRVCOMM_H_

#include "Conf/conf_hard.h"
#include "Tools/tools_typedefs.h"

#include "Drv/DrvEvent.h"

#define WHO		0U
#define PARAM_1	1U
#define PARAM_2	2U
#define PARAM_3	3U
#define PARAM_4	4U

typedef struct SSCommParam
{
	Int16U val;
}SCommParam;


typedef struct SSCommTrame
{
	SCommParam param[5U];
}SCommTrame;


//init des moteurs
void SrvCommInit (void)  ;
//dispatcher d'evenements
void SrvCommDispatcher (Event_t in_event) ;

#endif /* SRVCOMM_H_ */