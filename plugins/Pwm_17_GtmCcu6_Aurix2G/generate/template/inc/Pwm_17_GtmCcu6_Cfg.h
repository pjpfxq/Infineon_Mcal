[!AUTOSPACING!]
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
**  FILENAME  : Pwm_17_GtmCcu6_Cfg.h                                          **
**                                                                            **
**  VERSION   : 1.30.0_10.0.0                                                  **
**                                                                            **
**  DATE      : 2019-06-19                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Pwm.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY :                                                            **
**                                                                            **
**  DESCRIPTION  : Code template header file for Pwm Driver                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of Pwm Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!][!//
/*******************************************************************************
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
**  FILENAME  : Pwm_17_GtmCcu6_Cfg.h                                          **
**                                                                            **
**  VERSION   : 1.30.0_10.0.0                                                  **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]       !!!IGNORE-LINE !!!                 **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]         !!!IGNORE-LINE !!!                 **
**                                                                            **
**  BSW MODULE DECRIPTION : Pwm.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Pwm configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Pwm Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef PWM_17_GTMCCU6_CFG_H
#define PWM_17_GTMCCU6_CFG_H
[!/* [cover parentID={75A26C19-B4C5-46bb-BA8C-4F0198C370B0}]
Header file (Generated) containing constants and pre-processor macros
[/cover] */!]
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*******************************************************************************
**                      Global Macro Definitions                              **
** Traceabilty      :                                                         **
*******************************************************************************/
[!NOCODE!][!//
  [!INCLUDE "Pwm_17_GtmCcu6.m"!][!//
[!ENDNOCODE!][!//
[!//
[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
[!INDENT "0"!][!//
  [!/* [cover parentID={C571A22A-3EF6-477a-8648-79A8C21D850F}][/cover] */!]
  #define PWM_17_GTMCCU6_AR_RELEASE_MAJOR_VERSION  ([!"$MajorVersion"!]U)
  [!/* [cover parentID={D17DFAEF-85AB-4dc6-90A8-49B69098E25D}][/cover] */!]
  #define PWM_17_GTMCCU6_AR_RELEASE_MINOR_VERSION  ([!"$MinorVersion"!]U)
  [!/* [cover parentID={CAFDBCBE-E70D-49f2-AF9E-1E85E5A481C4}][/cover] */!]
  #define PWM_17_GTMCCU6_AR_RELEASE_REVISION_VERSION  ([!"$RevisionVersion"!]U)
  [!VAR "MajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
  [!VAR "MinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
  [!VAR "RevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
  [!VAR "NewString" = "text:replaceAll($moduleSoftwareVer,"\.",'')"!][!//
  [!/* [cover parentID={EB74CCBD-846E-435c-BA6C-A7759C149D46}][/cover] */!]
  #define PWM_17_GTMCCU6_SW_MAJOR_VERSION  ([!"$MajorVersion"!]U)
  [!/* [cover parentID={2C1E2FBF-57DC-47ff-A2F9-F399FCDDFD66}][/cover] */!]
  #define PWM_17_GTMCCU6_SW_MINOR_VERSION  ([!"$MinorVersion"!]U)
  [!/* [cover parentID={FBEE6F6A-7D2A-4fb3-A024-82EB7640C6ED}][/cover] */!]
  #define PWM_17_GTMCCU6_SW_PATCH_VERSION  ([!"$RevisionVersion"!]U)
[!ENDINDENT!][!//
[!SELECT "as:modconf('Pwm')[1]"!][!//
  [!INDENT "0"!][!//
    /*
    -------------------- Container:PwmGeneral --------------------
    */
    /*
      Configuration: PWM_17_GTMCCU6_DEV_ERROR_DETECT :
      Configuration of Development Error Detection 
      API Parameter Checking is enabled if this compiler
      switch is STD_ON.
      All errors are reported to Det_ReportError if the
      switch is STD_ON.
      Adds/removes the Development error detection 
      from the code 
      - if STD_ON, Development error detection is enabled
      - if STD_OFF, Development error detection is disabled
    */
      [!/* [cover parentID={61CA5D14-580B-423d-8BD3-028AC621166B}]
      PWM_17_GTMCCU6_DEV_ERROR_DETECT
      [/cover] */!]
    #define PWM_17_GTMCCU6_DEV_ERROR_DETECT                 [!CALL "PWM_ConfigSwitch", "nodeval" = "./PwmGeneral/PwmDevErrorDetect"!]
    /*
      Configuration: PWM_17_GTMCCU6_MULTICORE_ERROR_DETECT :
      Adds/removes the Multicore error detection and reporting 
      from the code 
      - if STD_ON, Multicore error detection and reporting is enabled
      - if STD_OFF, Multicore error detection and reporting is disabled
    */
      [!/* [cover parentID={D3464E1D-0C54-42a7-9281-A62CE32EABCA}]
      PWM_17_GTMCCU6_MULTICORE_ERROR_DETECT
      [/cover] */!]
    [!IF "node:exists(./PwmGeneral/PwmMultiCoreErrorDetect)"!][!//
      #define PWM_17_GTMCCU6_MULTICORE_ERROR_DETECT                 [!CALL "PWM_ConfigSwitch", "nodeval" = "./PwmGeneral/PwmMultiCoreErrorDetect"!]
    [!ELSE!][!//
      #define PWM_17_GTMCCU6_MULTICORE_ERROR_DETECT           (STD_OFF)
    [!ENDIF!][!//
      [!/* [cover parentID={279C0376-DFB7-40d8-8117-44CEA7A69219}]
      PWM_17_GTMCCU6_INSTANCE_ID
      [/cover] */!]
    /* Instance ID for PWM_17_Gtm module */
    #define PWM_17_GTMCCU6_INSTANCE_ID         ((uint8)[!"num:i(PwmGeneral/PwmIndex)"!]U)
    /*
      Configuration: PWM_17_GTMCCU6_DE_INIT_API
      Configuration of Pwm_DeInit API
      Adds/removes the service Pwm_DeInit() 
      from the code 
      - if STD_ON, Pwm_DeInit() can be used
      - if STD_OFF, Pwm_DeInit() cannot be used
    */
      [!/* [cover parentID={FAD51E9B-6B1E-48be-B874-ACB3458C745D}]
      PWM_17_GTMCCU6_DE_INIT_API
      [/cover] */!]
    #define PWM_17_GTMCCU6_DE_INIT_API                      [!CALL "PWM_ConfigSwitch", "nodeval" = "./PwmConfigurationOfOptApiServices/PwmDeInitApi"!]
    /*
      Configuration: PWM_17_GTMCCU6_GET_OUTPUT_STATE_API
      Configuration of PWM_17_GTMCCU6_GET_OUTPUT_STATE_API
      Adds/removes the service Pwm_GetOutputState() 
      from the code 
      - if STD_ON, Pwm_GetOutputState() can be used
      - if STD_OFF, Pwm_GetOutputState() cannot be used
    */
      [!/* [cover parentID={4C591A61-3B15-424d-B2B0-0833F3285274}]
      PWM_17_GTMCCU6_GET_OUTPUT_STATE_API
      [/cover] */!]
    #define PWM_17_GTMCCU6_GET_OUTPUT_STATE_API                       [!CALL "PWM_ConfigSwitch", "nodeval" = "./PwmConfigurationOfOptApiServices/PwmGetOutputState"!]
    /*
      Configuration: PWM_17_GTMCCU6_SET_DUTY_CYCLE_API
      Configuration of PWM_17_GTMCCU6_SET_DUTY_CYCLE_API
      Adds/removes the service Pwm_GetOutputState() 
      from the code 
      - if STD_ON, Pwm_SetDutyCycle() can be used
      - if STD_OFF,Pwm_SetDutyCycle() cannot be used
    */
      [!/* [cover parentID={3F1AA295-573E-4121-A3C8-0F2C52A1B6FD}]
      PWM_17_GTMCCU6_SET_DUTY_CYCLE_API
      [/cover] */!]
    #define PWM_17_GTMCCU6_SET_DUTY_CYCLE_API                       [!CALL "PWM_ConfigSwitch", "nodeval" = "./PwmConfigurationOfOptApiServices/PwmSetDutyCycle"!]
    /*
      Configuration: PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API
      Configuration of PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API
      Adds/removes the service Pwm_SetOutputToIdle() 
      from the code 
      - if STD_ON, Pwm_SetOutputToIdle() can be used
      - if STD_OFF,Pwm_SetOutputToIdle() cannot be used
    */
      [!/* [cover parentID={25FD5FD2-F693-46ce-B492-CA3151EDC1DB}]
      PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API
      [/cover] */!]
    #define PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API                       [!CALL "PWM_ConfigSwitch", "nodeval" = "./PwmConfigurationOfOptApiServices/PwmSetOutputToIdle"!]
    /*
      Configuration: PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API
      Configuration of PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API
      Adds/removes the service Pwm_SetPeriodAndDuty() 
      from the code 
      - if STD_ON, Pwm_SetPeriodAndDuty() can be used
      - if STD_OFF,Pwm_SetPeriodAndDuty() cannot be used
    */
      [!/* [cover parentID={78791071-59C8-4edd-BD07-D53A4811D6DE}]
      PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API
      [/cover] */!]
    #define PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API                       [!CALL "PWM_ConfigSwitch", "nodeval" = "./PwmConfigurationOfOptApiServices/PwmSetPeriodAndDuty"!]
    /* Enables the handling of Shifted channel by offset
      - if STD_ON, Shifted channel is handled by offset
      - if STD_OFF, Shifted channel andled by trigger from 
                   referenced Fixed period channel
    */
      [!/* [cover parentID={2EB84631-8771-4449-A4F2-D9BF6DFA185D}]
      PWM_17_GTMCCU6_HANDLE_SHIFT_BY_OFFSET
      [/cover] */!]
    #define PWM_17_GTMCCU6_HANDLE_SHIFT_BY_OFFSET                       [!CALL "PWM_ConfigSwitch", "nodeval" = "./PwmGeneral/PwmHandleShiftByOffset"!]
    /*
      Configuration: PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED
      Adds/removes the service Pwm_EnableNotification()
      and Pwm_DisableNotification() from the code 
      - if STD_ON, Notification API's can be used
      - if STD_OFF, Notification API's cannot be used
    */
      [!/* [cover parentID={FCCD9183-235F-45b5-82E4-B604C1B328E8}]
      PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED
      [/cover] */!]
    #define PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED           [!CALL "PWM_ConfigSwitch", "nodeval" = "./PwmGeneral/PwmNotificationSupported"!]
    /*
      Configuration: PWM_NOTIFICATION_FOR_0_AND_100
      Enable Notification for 0% and 100% duty 
      - if STD_ON, Notification for 0% and 100% duty is supported
      - if STD_OFF, Notification for 0% and 100% duty is not supported
    */
      [!/* [cover parentID={D1BDA65B-2277-4ddc-A3C8-81BFBC272A68}]
      PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE  
      [/cover] */!]
    [!VAR "notif_support" = "./PwmGeneral/PwmNotificationSupported"!][!//
    [!IF "$notif_support = 'false'"!][!//
      #define PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE           (STD_OFF)
    [!ELSE!][!//
      #define PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE           [!CALL "PWM_ConfigSwitch", "nodeval" = "./PwmGeneral/PwmEnable0Or100DutyNotification"!]
    [!ENDIF!][!//
    /*
    Configuration: PWM_17_GTMCCU6_DUTYCYCLE_UPDATED_ENDPERIOD
    Feature to have the duty cycle change, whether to update
    the duty at the end period or not.
    */
      [!/* [cover parentID={3C49FFF3-4799-4fad-842A-A8ACA763E9C6}]
      PWM_17_GTMCCU6_DUTYCYCLE_UPDATED_ENDPERIOD
      [/cover] */!]
    [!IF "node:exists(./PwmGeneral/PwmDutycycleUpdatedEndperiod)"!][!//
      #define PWM_17_GTMCCU6_DUTYCYCLE_UPDATED_ENDPERIOD      [!CALL "PWM_ConfigSwitch", "nodeval" = "./PwmGeneral/PwmDutycycleUpdatedEndperiod"!]
    [!ELSE!][!//
      #define PWM_17_GTMCCU6_DUTYCYCLE_UPDATED_ENDPERIOD      (STD_OFF)
    [!ENDIF!][!//
      [!/* [cover parentID={96181217-BA79-41ac-A491-22C12491A0DF}]
      PWM_17_GTMCCU6_DUTY_PERIOD_UPDATED_ENDPERIOD
      [/cover] */!]
    [!IF "node:exists(./PwmGeneral/PwmPeriodUpdatedEndperiod)"!][!//
      [!VAR "DutyPeriodUpdate" = "./PwmGeneral/PwmPeriodUpdatedEndperiod"!][!//
      [!CALL "PWM_PrintPeriodUpdateEndPeriodComments"!][!//
      #define PWM_17_GTMCCU6_DUTY_PERIOD_UPDATED_ENDPERIOD    [!CALL "PWM_ConfigSwitch", "nodeval" = "./PwmGeneral/PwmPeriodUpdatedEndperiod"!]
    [!ELSE!][!//
      #define PWM_17_GTMCCU6_DUTY_PERIOD_UPDATED_ENDPERIOD    (STD_OFF)
    [!ENDIF!][!//
    [!/* [cover parentID={30CB4BB9-57C4-4cd6-8ED5-543788510CE4}]
    PWM_17_GTMCCU6_SAFETY_ENABLE
    [/cover] */!]
    #define PWM_17_GTMCCU6_SAFETY_ENABLE    [!CALL "PWM_ConfigSwitch", "nodeval" = "./PwmGeneral/PwmSafetyEnable"!]
    [!/* [cover parentID={1B4A7B8C-C6A8-456b-9A19-53DF826ABC68}]
    PWM_17_GTMCCU6_INITCHECK_API
    [/cover] */!]
    #define PWM_17_GTMCCU6_INITCHECK_API    [!CALL "PWM_ConfigSwitch", "nodeval" = "./PwmGeneral/PwmInitCheckApi"!]
    /*
    Configuration: PWM_17_GTMCCU6_VERSION_INFO_API
    Adds/removes the service Pwm_GetVersionInfo() 
    from the code 
    - if STD_ON, Pwm_GetVersionInfo() can be used
    - if STD_OFF, Pwm_GetVersionInfo() cannot be used
    */
    [!/* [cover parentID={4F0F6D7D-4008-4899-A89D-3B61AC92032B}]
    PWM_17_GTMCCU6_DUTY_SHIFT_IN_TICKS
    [/cover] */!]
    #define PWM_17_GTMCCU6_VERSION_INFO_API                 [!CALL "PWM_ConfigSwitch", "nodeval" = "./PwmConfigurationOfOptApiServices/PwmVersionInfoApi"!]
    /* Configuration : PwmDutyShiftInTicks
    This parameter enables the user to enter the duty cycle and 
    shift value in absolute ticks, instead of percentage
    */
    [!/* [cover parentID={9707B448-7679-4bc6-9E89-A837B095B432}]
    PWM_17_GTMCCU6_DUTY_SHIFT_IN_TICKS 
    [/cover] */!]
    #define PWM_17_GTMCCU6_DUTY_SHIFT_IN_TICKS     [!CALL "PWM_ConfigSwitch", "nodeval" = "./PwmGeneral/PwmDutyShiftInTicks"!]
    /* Configured PWM Channels Symbolic Names */
    [!/* [cover parentID={FA5C1AE8-85B2-4b7d-859B-38DC49C1C268}][/cover] */!]
    [!LOOP "PwmChannelConfigSet/PwmChannel/*"!][!//
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      #ifndef Pwm_17_GtmCcu6Conf_PwmChannel_[!"node:name(.)"!]
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      #define Pwm_17_GtmCcu6Conf_PwmChannel_[!"node:name(.)"!]     ((Pwm_17_GtmCcu6_ChannelType)[!"PwmChannelId"!])
      #endif
    [!ENDLOOP!][!//

    /*
    Configuration:Max channels configured for Pwm, max channelas are same across
    variants.
    */
    [!NOCODE!][!//
      [!SELECT "as:modconf('Pwm')[1]"!][!//
        [!VAR "MaxChannels"= "num:i(0)"!][!//
        [!VAR "PwmSetPeriodApi" = "./PwmConfigurationOfOptApiServices/PwmSetPeriodAndDuty"!][!//
        [!VAR "MaxChannels"= "num:i(count(PwmChannelConfigSet/PwmChannel/*))"!][!//
      [!ENDSELECT!][!//
    [!ENDNOCODE!][!//
    [!/* [cover parentID={995E2C8C-C822-4607-A21E-DFBF8C0BF9EC}]
    Pwm Max Channels macro
    [/cover] */!]
    #define PWM_17_GTMCCU6_MAX_CHANNELS         ((Pwm_17_GtmCcu6_ChannelType)[!"$MaxChannels"!])
    [!/* [cover parentID={15AF1FE1-2C23-40c3-AAD0-DBCF55243C9F}]
    PWM_17_GTMCCU6_MAX_CORES
    [/cover] */!]
    #define PWM_17_GTMCCU6_MAX_CORES            ([!"ecu:get('Mcu.NoOfCoreAvailable')"!]U)
    [!VAR "PwmGtmUsed" = "'false'"!][!//
    [!VAR "PwmCcu6Used" = "'false'"!][!//
    [!CALL "PWM_GenerateModuleMap", "Module" = "'PWM'"!][!//
    /* Loop for all the cores */
    [!FOR "CoreId" = "num:i(0)" TO "num:i(6) - num:i(1)"!][!//
      [!VAR "MaxChannelsCore" = "num:i(255)"!][!//
      [!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
      [!CALL "PWM_GetMasterCoreID"!][!//
      [!IF "(text:contains( text:split($CGAllocatedCores,','), $TempCoreId)) or ($CGMasterCoreId = $TempCoreId) or ($CoreId < ecu:get('Mcu.NoOfCoreAvailable'))"!][!//
        [!VAR "MaxChannelsCore" = "num:i(0)"!][!//
        [!VAR "GtmChannelIndex" = "num:i(0)"!][!//
        [!VAR "Ccu6ChannelIndex" = "num:i(0)"!][!//
        [!FOR "ChannelId" = "num:i(0)" TO "num:i($MaxChannels) - num:i(1)"!][!//
          [!SELECT "PwmChannelConfigSet/PwmChannel/*[PwmChannelId = num:i($ChannelId)]"!][!//
            [!VAR "NodeName" = "node:name(.)"!][!//
            [!VAR "PwmLogicalChId" = "./PwmChannelId"!][!//
            [!CALL "PWM_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
            [!IF "$CGAllocationResult = 'TRUE'"!][!//
              [!VAR "MaxChannelsCore" = "$MaxChannelsCore + num:i(1)"!][!//
              [!VAR "PwmTimerUsed" = "./PwmAssignedHwUnit"!][!//
              [!IF "$PwmTimerUsed = 'GTM'"!][!//
                [!VAR "GtmChannelIndex" = "$GtmChannelIndex + num:i(1)"!][!//
                [!VAR "PwmGtmUsed" = "'true'"!][!//
              [!ELSE!][!//
                [!VAR "Ccu6ChannelIndex" = "$Ccu6ChannelIndex + num:i(1)"!][!//
                [!VAR "PwmCcu6Used" = "'true'"!][!//
              [!ENDIF!][!//
            [!ENDIF!][!//
          [!ENDSELECT!][!//
        [!ENDFOR!][!//
      [!ENDIF!][!//
      [!/* [cover parentID={6191409D-6AB2-4ca6-A5D5-8A80CEAC1611}]
      PWM_17_GTMCCU6_MAX_CHANNELS_CORE
      [/cover] */!]
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
      in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
      in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
      in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
      in generated code due to Autosar Naming constraints.*/
      #define PWM_17_GTMCCU6_MAX_CHANNELS_CORE[!"$CoreId"!]               ([!"num:i($MaxChannelsCore)"!]U)
    [!ENDFOR!][!//
    [!/* [cover parentID={AD9BF8EC-C4D4-4dec-A59C-46EB5ED6502B}]
    PWM_17_GTMCCU6_GTM_TIMER_USED
    [/cover] */!]
    [!IF "$PwmGtmUsed = 'true'"!][!//
      #define PWM_17_GTMCCU6_GTM_TIMER_USED              (STD_ON)
    [!ELSE!][!//
      #define PWM_17_GTMCCU6_GTM_TIMER_USED              (STD_OFF)
    [!ENDIF!][!//
    [!/* [cover parentID={00ACF3E4-45EC-43c2-88F8-33426B424F23}]
    PWM_17_GTMCCU6_CCU6_TIMER_USED
    [/cover] */!]
    [!IF "$PwmCcu6Used = 'true'"!][!//
      #define PWM_17_GTMCCU6_CCU6_TIMER_USED             (STD_ON)
    [!ELSE!][!//
      #define PWM_17_GTMCCU6_CCU6_TIMER_USED             (STD_OFF)
    [!ENDIF!][!//
    /*******************************************************************************
    **                      Global Constant Declarations                          **
    *******************************************************************************/
  [!ENDINDENT!][!//
[!ENDSELECT!][!//
#endif
