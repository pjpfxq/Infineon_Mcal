[!/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2020)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME    : Uart_PBcfg.c                                                **
**                                                                            **
**  VERSION     : 1.40.0_13.0.0                                               **
**                                                                            **
**  DATE        : 2020-02-14                                                  **
**                                                                            **
**  BSW MODULE DECRIPTION : Uart.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR      : DL-AUTOSAR-Engineering                                      **
**                                                                            **
**  VENDOR      : Infineon Technologies                                       **
**                                                                            **
**                                                                            **
**  TRACEABILITY : [cover parentID]                                           **
**                                                                            **
**  DESCRIPTION  : Code template source file for Uart Driver                  **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Uart Driver, AUTOSAR Release 4.2.2    **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
******************************************************************************/!]
/******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2020)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Uart_PBcfg.c                                                  **
**                                                                            **
**  VERSION   : 1.40.0_13.0.0                                                 **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]  !!!IGNORE-LINE!!!                       **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]      !!!IGNORE-LINE!!!                     **
**                                                                            **
**  BSW MODULE DECRIPTION : Uart.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Uart configuration generated out of ECUC file              **
**                                                                            **
**  SPECIFICATION(S) : Specification of Uart Driver, AUTOSAR Release 4.2.2    **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={708D1F23-55ED-4ea8-9FC9-11E6F663FDEF}]
[/cover] */
/******************************************************************************
**                      Includes                                             **
******************************************************************************/
/* Include UART Module File */
#include "Uart.h"

/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/
/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/
/******************************************************************************
**                      Private Type Definitions                             **
******************************************************************************/
/******************************************************************************
**                      Private Function Declarations                        **
******************************************************************************/
/******************************************************************************
**                      Global Constant Definitions                          **
******************************************************************************/
/******************************************************************************
**                      Extern Declaration                                   **
******************************************************************************/
/* [cover parentID={DB6AEAF8-1942-4dab-BAA6-C3A0AA2FC308}]
[/cover] */
[!AUTOSPACING!]
[!INDENT "0"!]
  [!NOCODE!][!//
    [!IF "not(node:exists(as:modconf('ResourceM')[1]))"!]
      [!ERROR!][!//
        UART needs ResourceM module.
      [!ENDERROR!][!//
    [!ENDIF!]

    [!IF "not(node:exists(as:modconf('Mcu')[1]))"!]
      [!ERROR!][!//
        UART needs MCU module.
      [!ENDERROR!][!//
    [!ENDIF!]
  [!ENDNOCODE!][!//
  [!SELECT "as:modconf('Uart')[1]"!][!//
    [!VAR "Uart_MasterCallBackJobLstNum" = "''"!][!//
    [!LOOP "UartConfigSet/UartChannel/*"!][!//
      [!VAR "TxUartNotify" = "UartNotification/UartTransmitNotifPtr"!][!//
      [!IF "num:isnumber($TxUartNotify) !=  'true' and $TxUartNotify != 'NULL_PTR'"!]
        /* Transmit notification function of [!"node:name(.)"!] */
        [!IF "not(text:contains(text:split($Uart_MasterCallBackJobLstNum,','),$TxUartNotify))"!]
          extern void [!"$TxUartNotify"!](Uart_ErrorIdType ErrorId);
          [!VAR "Uart_MasterCallBackJobLstNum" = "concat($Uart_MasterCallBackJobLstNum,$TxUartNotify,',')"!]
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!VAR "RxUartNotify" = "UartNotification/UartReceiveNotifPtr"!][!//
      [!IF "num:isnumber($RxUartNotify) !=  'true' and $RxUartNotify != 'NULL_PTR'"!]
        /* Receive notification function of [!"node:name(.)"!] */
        [!IF "not(text:contains(text:split($Uart_MasterCallBackJobLstNum,','),$RxUartNotify))"!]
          extern void [!"$RxUartNotify"!](Uart_ErrorIdType ErrorId);
          [!VAR "Uart_MasterCallBackJobLstNum" = "concat($Uart_MasterCallBackJobLstNum,$RxUartNotify,',')"!]
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!VAR "RxAbortNotify" = "UartNotification/UartAbortReceiveNotifPtr"!][!//
      [!IF "num:isnumber($RxAbortNotify) !=  'true' and $RxAbortNotify != 'NULL_PTR'"!]
        /* Receive abort notification function of [!"node:name(.)"!] */
        [!IF "not(text:contains(text:split($Uart_MasterCallBackJobLstNum,','),$RxAbortNotify))"!]
          extern void [!"$RxAbortNotify"!](Uart_ErrorIdType ErrorId);
          [!VAR "Uart_MasterCallBackJobLstNum" = "concat($Uart_MasterCallBackJobLstNum,$RxAbortNotify,',')"!]
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!VAR "TxAbortNotify" = "UartNotification/UartAbortTransmitNotifPtr"!][!//
      [!IF "num:isnumber($TxAbortNotify) !=  'true' and $TxAbortNotify != 'NULL_PTR'"!]
        /* Transmit abort notification function of [!"node:name(.)"!] */
        [!IF "not(text:contains(text:split($Uart_MasterCallBackJobLstNum,','),$TxAbortNotify))"!]
          extern void [!"$TxAbortNotify"!](Uart_ErrorIdType ErrorId);
          [!VAR "Uart_MasterCallBackJobLstNum" = "concat($Uart_MasterCallBackJobLstNum,$TxAbortNotify,',')"!]
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDSELECT!][!//
  /*
               Container: UartConfigSet
  */
  #define UART_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  /* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
  /*  [/cover] */
  /* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
  * Const Section
  * [/cover]*/
  /* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
   * Const Section
  * [/cover]*/
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
     without safegaurd. It complies to Autosar guidelines. */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
   * this is due to inclusion of memmap.h to specify the location to which
   * the variable has to be placed. */
  #include "Uart_MemMap.h"
  [!//
  [!VAR "VariantsConfigured" = "num:i(0)"!]
  [!SELECT "as:modconf('EcuC')[1]"!][!//
    [!IF "node:exists(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!][!//
      [!VAR "PredefinedVarName1" = "(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!]
      [!VAR "PredefinedVarName2" = "substring-after($PredefinedVarName1, "/")"!][!//
      [!VAR "PredefinedVarName3" = "substring-after($PredefinedVarName2, "/")"!][!//
      [!VAR "PredefinedVarName" = "substring-after($PredefinedVarName3, "/")"!][!//
      [!VAR "VariantsConfigured" = "num:i(1)"!]
    [!ENDIF!][!//
  [!ENDSELECT!]
  [!//
  [!//
  [!/* Select MODULE-CONFIGURATION as context-node */!][!//
  [!SELECT "as:modconf('Uart')[1]"!][!//
    [!//
    [!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
    [!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
    [!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
    [!/*****************************************************************************
    MACRO: Uart_ConfigurationCheck
    Macro to verify if the configuration for Uart module is valid or not.
    ******************************************************************************/!]
    [!MACRO "Uart_ConfigurationCheck"!][!//
      [!NOCODE!][!//
        /* [cover parentID={C6D96345-E215-4528-B9E7-6E2A34477B57}]
        [/cover] */
        [!FOR "ASCLIN" = "0" TO "num:i(ecu:get('AscLin.MaxNoOfAscLinModules')) - 1"!][!//
          [!LOOP "UartConfigSet/UartChannel/*"!][!//
            [!VAR "tmp" = "num:i(count(./../*[UartHwUnit = text:concat('ASCLIN',$ASCLIN)]))"!][!//
            [!VAR "McuAscLinRef" = "node:path(node:ref(./../../../UartGeneral/UartClockRef)/../../../../McuHardwareResourceAllocationConf/*[1]/McuAscLinAllocationConf/*[$ASCLIN + num:i(1)]/McuAscLinChannelAllocationConf/McuAscLinChannelAllocationConf)"!][!//
            [!VAR "McuAscLin" = "node:ref($McuAscLinRef)"!]
            [!IF "num:i($tmp) > num:i(1)"!][!//
            [!ERROR!][!//
              ASCLIN[!"$ASCLIN"!] module shouldn't be configured for more than 1 Uart Channel
            [!ENDERROR!][!//
            [!ELSEIF "num:i($tmp) = num:i(1)"!][!//
              [!IF "$McuAscLin != 'ASCLIN_CH_USED_BY_UART_DRIVER'"!][!//
                [!ERROR!][!//
                  Configure the ASCLIN[!"$ASCLIN"!] Channel for UART in Mcu Configuration container McuAscLinAllocationConf node name = [!"node:name(node:ref(./../../../UartGeneral/UartClockRef)/../../../../McuHardwareResourceAllocationConf/*[1]/McuAscLinAllocationConf/*[$ASCLIN + num:i(1)])"!]
                [!ENDERROR!][!//
              [!ENDIF!] [!//
            [!ENDIF!] [!//
          [!ENDLOOP!][!//
        [!ENDFOR!][!//
      [!ENDNOCODE!][!//
    [!ENDMACRO!][!//
    [!//
    [!NOCODE!][!//
    [!/*Max Baud rate is Frequency / 16*/!][!//
    [!ENDNOCODE!][!//
    [!MACRO "Uart_ValidateBaudRate", "InputBaudRate" = "", "InputFrequency3" = ""!][!//
      [!VAR "MaxBaudRate" = "num:i(($InputFrequency3) div (16))"!][!//
      [!IF "$MaxBaudRate < $InputBaudRate"!][!//
        [!ERROR!]
          CONFIG ERROR: Maximum baud rate allowed for the frequency [!"$InputFrequency3"!]Hz is [!"$MaxBaudRate"!]Hz reconfigure the baud rate parameters(UartChanBaudNumerator, UartChanBaudDenominator, UartChanBaudPrescalar UartChanBaudOversampling or UartBaudRate).
        [!ENDERROR!]
      [!ENDIF!][!//
    [!ENDMACRO!][!//
    [!/*
    MACRO: Uart_CalcBaudParams.
    Baudrate Parameter is calculated using the below formula
    fPD = fA / (BRG.PRESCALER + 1)
    fOVS = fPD * BRG.NUMERATOR / BRG.DENOMINATOR
    fSHIFT or Baudrate= fOVS / (BITCON.OVERSAMPLING + 1)
    */!][!//
    /* [cover parentID={A876E15E-2536-4fe5-8E1B-C8BDD6893BDA}]
    [/cover] */
    [!MACRO "Uart_CalcBaudParams", "BaudRate" = "", "InputFrequency2" = ""!][!//
      [!NOCODE!][!//
        [!CALL "Uart_ValidateBaudRate", "InputBaudRate" = "$BaudRate", "InputFrequency3" = "$InputFrequency2"!][!//
        [!VAR "BaudConfigDone" = "num:i(2)"!][!//
        /* Init numerator to denominator value */
        [!VAR "NumTODenoRatio" = "num:f(0.001)"!][!//
        [!FOR "inc" = "num:i(0)" TO "num:i(1000)"!][!//
          /* Loop for oversampling */
          [!FOR "OverSample" = "num:i(9)" TO "num:i(16)"!][!//
            /* Calculate prescalar value */
            [!VAR "TempPrescalar" = "(num:i($InputFrequency2) * num:f($NumTODenoRatio) ) div ( ($BaudRate) * ($OverSample))"!][!//
              /* Check prescalar and numerator to denominator are satify baud rate condition */
            [!IF "num:i($TempPrescalar) < num:i(4096) and num:i($TempPrescalar) >= num:i(1) and num:f($NumTODenoRatio) <=num:f(1)"!][!//
              [!VAR "temp_baud" = "(num:i($InputFrequency2) * num:f($NumTODenoRatio) ) div ( num:i($TempPrescalar) * ($OverSample))"!][!//
              [!IF "num:i($temp_baud) = num:i($BaudRate)"!][!//
                /* Calculate all baud rate param */
                [!VAR "Numerator" = "num:i(num:f($NumTODenoRatio) * 1000)"!][!//
                [!VAR "Denominator" = "num:i(1000)"!][!//
                [!VAR "Prescalar" = "num:i(($TempPrescalar)-1)"!][!//
                [!VAR "Oversampling" = "num:i(($OverSample)-1)"!][!//
                [!VAR "BaudConfigDone" = "num:i(1)"!][!//
                [!BREAK!][!//
              [!ENDIF!][!//
            [!ENDIF!][!//
          [!ENDFOR!][!//
          [!IF "$BaudConfigDone = num:i(1)"!][!//
            [!BREAK!][!//
          [!ENDIF!][!//
          [!VAR "NumTODenoRatio" = "($NumTODenoRatio)+ num:f(0.001)"!][!//
        [!ENDFOR!][!//
      [!ENDNOCODE!][!//
    [!ENDMACRO!][!//
    [!NOCODE!][!//
      [!IF "UartGeneral/UartCsrClksel = 'ASCLINF'"!][!//
        [!VAR "InputFrequency" = "num:i(node:ref(UartGeneral/UartClockRef)/McuPllDistributionSettingConfig/McuAscLinFastFrequency)"!][!//
      [!ELSE!][!//
        [!VAR "InputFrequency" = "num:i(node:ref(UartGeneral/UartClockRef)/McuPllDistributionSettingConfig/McuAscLinSlowFrequency)"!][!//
      [!ENDIF!][!//
      [!//
      [!VAR "TotalChannel" = "num:i(count(UartConfigSet/UartChannel/*))"!][!//
      [!VAR "ConfigIdx" = "@index"!][!//
      [!CALL "Uart_ConfigurationCheck"!][!//
      [!IF "$InputFrequency = num:i(0)"!][!//
        [!ERROR!][!//
          ERROR: Module input frequency should not be zero. Please configure valid frequency for UartClockRef.
        [!ENDERROR!][!//
      [!ENDIF!][!//
    [!ENDNOCODE!][!//
    /* [cover parentID={C13F0984-A501-47cd-AE26-25AA4A4DE269}]
    [/cover] */
    [!IF "$VariantsConfigured = num:i(1)"!][!//
      static const Uart_ChannelConfigType  Uart_ChannelConfig_[!"$PredefinedVarName"!][[!"string(num:i($TotalChannel))"!]] =
    [!ELSE!][!//
      static const Uart_ChannelConfigType  Uart_ChannelConfig[[!"string(num:i($TotalChannel))"!]] =
    [!ENDIF!][!//
    {
    [!INDENT "2"!]
      [!VAR "Count" = "num:i(0)"!][!//
      [!LOOP "node:order(UartConfigSet/UartChannel/*, './UartChannelId')"!][!//
        [!//
        [!NOCODE!][!//
          [!IF "UartAutoCalcBaudParams = 'true'"!][!//
            [!CALL "Uart_CalcBaudParams", "BaudRate" = "UartBaudRate", "InputFrequency2" = "$InputFrequency"!][!//
            [!VAR "BaudRate" = "num:i(UartBaudRate)"!][!//
            [!IF "num:i($BaudConfigDone) = num:i(1)"!][!//
            [!ELSE!][!//
              [!ERROR!][!//
                ERROR: BaudRate could not be calculated automatically.Enter Baud parameters manually.
              [!ENDERROR!][!//
            [!ENDIF!][!//
            [!VAR "New_Baud" = "( ($InputFrequency2 * $Numerator) div  (($Prescalar+1) * ($Oversampling+1) * ($Denominator)))"!][!//
            /* Check calculated baud rate and expected baud rate matching */
            [!IF "num:i($New_Baud) = num:i($BaudRate)"!][!//
            [!ELSE!][!//
              [!ERROR!][!//
                ERROR: BaudRate could not be calculated automatically.Enter Baud parameters manually.
              [!ENDERROR!][!//
            [!ENDIF!][!//
          [!ELSE!][!//
            [!VAR "Numerator" = "num:i(UartChanBaudNumerator)"!][!//
            [!VAR "Denominator" = "num:i(UartChanBaudDenominator)"!][!//
            [!VAR "Prescalar" = "num:i(UartChanBaudPrescalar)"!][!//
            [!VAR "Oversampling" = "num:i((UartChanBaudOverSampling))"!][!//Bitcon.oversampling register field value
            [!IF "$Numerator > $Denominator"!][!// manual value
              [!ERROR!][!//
                ERROR: Numerator value should be less than Denominator.
              [!ENDERROR!][!//
            [!ENDIF!][!//
            [!VAR "fPD" = "num:i($InputFrequency) div (num:i($Prescalar) + 1)"!][!//
            [!VAR "fOVS" = "num:i($fPD) * num:i($Numerator) div num:i($Denominator)"!][!//
            [!VAR "BaudRate" = "num:i($fOVS) div (num:i($Oversampling) + 1)"!][!//
            [!/* check for the value of Baudrate */!][!//
            [!CALL "Uart_ValidateBaudRate", "InputBaudRate" = "$BaudRate", "InputFrequency3" = "$InputFrequency"!][!//
          [!ENDIF!][!//
        [!ENDNOCODE!][!//
        [!//
        /* UART Channel ID: [!"UartChannelId"!] Configuration */
        { /* Notification function */
        [!INDENT "4"!]
          {
          [!INDENT "6"!]
            /* Call-back notification function for write operation */
            [!VAR "SymbolicName" = "UartNotification/UartTransmitNotifPtr"!][!//
            [!IF "num:isnumber($SymbolicName) = 'true'"!][!//
              [!"concat('(Uart_NotificationPtrType)',num:inttohex(num:radixtoint($SymbolicName),8),'U')"!],
            [!ELSE!][!//
              [!IF "($SymbolicName != 'NULL_PTR')"!][!//
                &[!"$SymbolicName"!],
              [!ELSE!][!//
                [!"$SymbolicName"!],
              [!ENDIF!][!//
            [!ENDIF!][!//
            /* Call-back notification function for read operation */
            [!VAR "SymbolicName" = "UartNotification/UartReceiveNotifPtr"!][!//
            [!IF "num:isnumber($SymbolicName) = 'true'"!][!//
                [!"concat('(Uart_NotificationPtrType)',num:inttohex(num:radixtoint($SymbolicName),8),'U')"!],
            [!ELSE!][!//
              [!IF "($SymbolicName != 'NULL_PTR')"!][!//
                &[!"$SymbolicName"!],
              [!ELSE!][!//
                [!"$SymbolicName"!],
              [!ENDIF!][!//
            [!ENDIF!][!//
            /* Call-back notification function for abort write operation */
            [!VAR "SymbolicName" = "UartNotification/UartAbortTransmitNotifPtr"!][!//
            [!IF "num:isnumber($SymbolicName) = 'true'"!][!//
              [!"concat('(Uart_NotificationPtrType)',num:inttohex(num:radixtoint($SymbolicName),8),'U')"!],
            [!ELSE!][!//
              [!IF "($SymbolicName != 'NULL_PTR')"!][!//
                &[!"$SymbolicName"!],
              [!ELSE!][!//
                [!"$SymbolicName"!],
              [!ENDIF!][!//
            [!ENDIF!][!//
            /* Call-back notification function for abort read operation */
            [!VAR "SymbolicName" = "UartNotification/UartAbortReceiveNotifPtr"!][!//
            [!IF "num:isnumber($SymbolicName) = 'true'"!][!//
              [!"concat('(Uart_NotificationPtrType)',num:inttohex(num:radixtoint($SymbolicName),8),'U')"!],
            [!ELSE!][!//
              [!IF "($SymbolicName != 'NULL_PTR')"!][!//
                &[!"$SymbolicName"!],
              [!ELSE!][!//
                [!"$SymbolicName"!],
              [!ENDIF!][!//
            [!ENDIF!][!//
          [!ENDINDENT!]
          },
          /* BaudRate : [!"$BaudRate"!] Hz  */
          /* Channel baud rate numerator */
          [!"$Numerator"!]U,
          /* Channel baud rate denominator */
          [!"$Denominator"!]U,
          /* Channel baud rate prescalar */
          [!"$Prescalar"!]U,
          /* Channel oversampling */
          [!"$Oversampling"!]U,
          /* Hardware channel id */
          UART_[!"UartHwUnit"!],
          /* Number of stop Bits */
          [!"UartStopBits"!]U,
          /* Frame length */
          [!"UartDataLength"!]U,
          /* Alternate receive pin */
          [!VAR "Dataline" = "UartRxPinSelection"!][!//
          [!IF "contains($Dataline, 'GN') or contains($Dataline, 'GP')"!][!//
            UART_SELECT_G,
          [!ELSE!]
            UART_[!"substring-before($Dataline, '_P')"!],
          [!ENDIF!]
          [!IF "contains(UartParityBit,'NOPARITY') = 'true'"!][!//
            [!VAR "UartParityEnable" = "num:i(0)"!][!//
            [!VAR "UartParity" = "num:i(0)"!][!//
          [!ELSEIF "contains(UartParityBit,'ODDPARITY') = 'true'"!][!//
            [!VAR "UartParityEnable" = "num:i(1)"!][!//
            [!VAR "UartParity" = "num:i(1)"!][!//
          [!ELSEIF "contains(UartParityBit,'EVENPARITY') = 'true'"!][!//
            [!VAR "UartParityEnable" = "num:i(1)"!][!//
            [!VAR "UartParity" = "num:i(0)"!][!//
          [!ELSE!][!//
          [!ENDIF!][!//
          /* Identifies the parity is enabled */
          [!"$UartParityEnable"!]U,
          /* Identifies the parity is even or odd */
          [!"$UartParity"!]U,
          /* Alternate CTS pin */
          [!VAR "Dataline" = "UartCTSPinSelection"!][!//
          [!IF "contains($Dataline, 'NONE')"!][!//
            UART_SELECT_CTS_NONE,
          [!ELSE!]
            UART_[!"substring-before($Dataline, '_P')"!],
          [!ENDIF!]

          [!IF "UartCTSEnable = 'true'"!][!//
            [!VAR "UartCtsEnable" = "num:i(1)"!][!//
            [!IF "contains(UartCTSPolarity,'HIGH') = 'true'"!][!//
              [!VAR "UartCtsPolarity" = "num:i(0)"!][!//
            [!ELSEIF "contains(UartCTSPolarity,'LOW') = 'true'"!][!//
              [!VAR "UartCtsPolarity" = "num:i(1)"!][!//
            [!ENDIF!][!//
          [!ELSE!][!//
            [!VAR "UartCtsEnable" = "num:i(0)"!][!//
            [!VAR "UartCtsPolarity" = "num:i(0)"!][!//
          [!ENDIF!][!//
          /* CTS is enabled */
          [!"$UartCtsEnable"!]U,
          /* RTS/CTS polarity if CTS is enabled */
          [!"$UartCtsPolarity"!]U,
          /* Receive operation mode polling/interrupt */
          [!IF "contains(UartRxChannelMode,'POLLING') = 'true'"!][!//
            UART_POLLING_MODE,
          [!ELSE!][!//
            UART_INTERRUPT_MODE,
          [!ENDIF!][!//
          /* Transmit operation mode polling/interrupt  */
          [!IF "contains(UartTxChannelMode,'POLLING') = 'true'"!][!//
            UART_POLLING_MODE
          [!ELSE!][!//
            UART_INTERRUPT_MODE
          [!ENDIF!][!//
          [!VAR "Count" = "$Count + 1"!][!//
        [!ENDINDENT!]
        [!IF "$Count < $TotalChannel"!][!//
          },
        [!ELSE!][!//
          }
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDINDENT!]
    };
    /* [cover parentID={1614ABEB-C055-42f9-90C1-009D55C1699C}]
    [/cover] */
    [!VAR "UartLastIndex" = "num:i(ecu:get('AscLin.LastIndexOfAscLinModules'))"!][!//
    [!IF "$VariantsConfigured = num:i(1)"!][!//
      static const uint8 Uart_ChannelIdLookup_[!"$PredefinedVarName"!][UART_MAX_HW_UNIT] =
    [!ELSE!][!//
      static const uint8 Uart_ChannelIdLookup[UART_MAX_HW_UNIT] =
    [!ENDIF!][!//
    {
    [!INDENT "2"!]
      [!FOR "UartCounter" = "0" TO "num:i($UartLastIndex)"!][!//
        [!IF "num:i(count(UartConfigSet/UartChannel/*[UartHwUnit = concat('ASCLIN',$UartCounter)])) = num:i(0)"!][!//
          0xFFU[!//
        [!ELSE!][!//
          [!LOOP "UartConfigSet/UartChannel/*[UartHwUnit = concat('ASCLIN',$UartCounter)]"!][!//
            [!"node:value(./UartChannelId)"!]U[!//
          [!ENDLOOP!]
        [!ENDIF!][!//
        [!IF "num:i($UartCounter) != num:i($UartLastIndex)"!][!//
          ,
        [!ELSE!]
        [!ENDIF!][!//
      [!ENDFOR!][!//
    [!ENDINDENT!]
    };
    /* [cover parentID={59DF25D6-EA51-4428-A68D-B42F8D3ACE82}]
    [/cover] */
    /* Uart configuration set */
    [!SELECT "UartConfigSet/*[1]"!][!//
      [!IF "$VariantsConfigured = num:i(1)"!]
        const Uart_ConfigType Uart_Config_[!"$PredefinedVarName"!] =
      [!ELSE!]
        const Uart_ConfigType Uart_Config =
      [!ENDIF!]
    [!ENDSELECT!][!//
    {
    [!INDENT "2"!]
      [!IF "$VariantsConfigured = num:i(1)"!][!//
        &Uart_ChannelConfig_[!"$PredefinedVarName"!][0],
      [!ELSE!][!//
        &Uart_ChannelConfig[0],
      [!ENDIF!][!//
      [!IF "$VariantsConfigured = num:i(1)"!][!//
        &Uart_ChannelIdLookup_[!"$PredefinedVarName"!][0],
      [!ELSE!][!//
        &Uart_ChannelIdLookup[0],
      [!ENDIF!][!//
      [!"$TotalChannel"!]U
    [!ENDINDENT!]
    };
  [!ENDSELECT!][!//
  [!//
  #define UART_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  /* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
  /*  [/cover] */
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
     without safegaurd. It complies to Autosar guidelines. */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
   * this is due to inclusion of memmap.h to specify the location to which
   * the variable has to be placed. */
  #include "Uart_MemMap.h"

  /******************************************************************************
  **                      Global Variable Definitions                           *
  ******************************************************************************/
  /******************************************************************************
  **                      Private Constant Definitions                         **
  ******************************************************************************/
  /******************************************************************************
  **                      Private Variable Definitions                         **
  ******************************************************************************/
  /******************************************************************************
  **                      Global Function Definitions                          **
  ******************************************************************************/
  /******************************************************************************
  **                      Private Function Definitions                         **
  ******************************************************************************/
[!ENDINDENT!]
