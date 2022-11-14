[!/*****************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Can_17_McmCan_Externals.h                                     **
**                                                                            **
**  VERSION   : 1.40.0_1.0.0                                                  **
**                                                                            **
**  DATE      : 2020-01-07                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Can_17_McmCan.bmd                                 **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={C888B967-1D42-4b89-8253-F1360DFCB567}]    **
**                 [cover parentID={8BF6A45D-185F-4433-9D57-F2E7D8DAE22C}]    **
**                                                                            **
**  DESCRIPTION  : Contains callout function prototype                        **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CAN Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*************************************************************************/!][!//
[!//
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2018)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Can_17_McmCan_Externals.h                                     **
**                                                                            **
**  VERSION   : 1.40.0_1.0.0                                                  **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]          !!!IGNORE-LINE!!!               **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]            !!!IGNORE-LINE!!!               **
**                                                                            **
**  BSW MODULE DECRIPTION : Can_17_McmCan.bmd                                 **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Contains callout function prototype                        **
**                                                                            **
**  SPECIFICATION(S) : Specification of CAN Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef CAN_17_MCMCAN_EXTERNALS_H
#define CAN_17_MCMCAN_EXTERNALS_H
[!NOCODE!]
[!//
[!/* Include Code Generator Macros */!][!//
[!INCLUDE "Can_17_McmCan.m"!][!//
[!//
[!ENDNOCODE!][!//
[!//
[!CALL "CAN_CG_IsCalloutEnabled"!][!//
[!IF "$CanRxCalloutFnExists = num:i(1)"!][!//

/******************************************************************************/
                  /* CAN L-PDU Receive Callout Function */
/******************************************************************************/
[!/* [cover parentID={5CFC2F51-1629-4b86-BFAD-03480CB43CCF}]
[/cover] */!][!//
[!/* [cover parentID={7D0C9AE8-9FDB-4dfc-8041-E215916A9198}]
[/cover] */!][!//
extern boolean [!"$RxLPduCallout"!] (const uint8 Hrh,
                      const Can_IdType CanId,
                      const uint8 CanDlc,
                      const uint8 *CanSduPtr);
[!ENDIF!][!//
#endif  /* CAN_17_MCMCAN_EXTERNALS_H */
