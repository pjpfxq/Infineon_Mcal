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
**  FILENAME  : I2c_PBcfg.h                                                   **
**                                                                            **
**  VERSION   : 1.30.0_5.0.0                                                  **
**                                                                            **
**  DATE      : 2019-08-22                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : I2c.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Code template header file for I2c Driver                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of I2c Driver, AUTOSAR Release 4.2.2     **
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
**  FILENAME  : I2c_PBcfg.h                                                   **
**                                                                            **
**  VERSION   : 1.30.0_5.0.0                                                  **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]    !!!IGNORE-LINE!!!                     **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]    !!!IGNORE-LINE!!!                       **
**                                                                            **
**  BSW MODULE DECRIPTION : I2c.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : I2c configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of I2c Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef I2C_PBCFG_H
#define I2C_PBCFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
#define I2C_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
 /* MISRA2012_RULE_8_4_JUSTIFICATION: Module configuration data structure
   declaration is as per Autosar guidelines. This data structure is needed
   by SW units using I2c Driver APIs hence it should be declared as extern in
   the SW unit from where it is used */
#include "I2c_MemMap.h"
[!AUTOSPACING!]
[!INDENT "0"!][!//
  [!VAR "EcucModuleExist" = "num:i(0)"!][!//
  [!SELECT "as:modconf('EcuC')[1]"!][!//
    [!IF "node:exists(EcucPostBuildVariants/*[1]/EcucPostBuildVariantRef/*[1])"!][!//
      [!VAR "EcucModuleExist" = "num:i(1)"!][!//
      [!LOOP "EcucPostBuildVariants/*[1]/EcucPostBuildVariantRef/*"!][!//
        [!VAR "Variantname"="''"!][!//
        [!VAR "Variantname" = "text:split(.,'/')[4]"!]
        [!WS"0"!]/* Extern declaration of I2c Config Root for [!"$Variantname"!] */
        [!WS"0"!]extern const I2c_ConfigType I2c_Config_[!"$Variantname"!];
      [!ENDLOOP!][!//
    [!ENDIF!][!//
  [!ENDSELECT!][!//
  [!IF "$EcucModuleExist = num:i(0)"!][!//
    /* Extern declaration of I2c Config Root */

    extern const I2c_ConfigType I2c_Config;
  [!ENDIF!][!//
[!ENDINDENT!][!//
#define I2C_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "I2c_MemMap.h"
#endif

