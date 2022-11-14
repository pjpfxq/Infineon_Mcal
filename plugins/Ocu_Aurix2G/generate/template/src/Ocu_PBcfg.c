[!AUTOSPACING!]
[!INDENT "0"!]  
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
  **  FILENAME  : Ocu_PBcfg.c                                                   **
  **                                                                            **
  **  VERSION   : 1.40.0_9.0.0                                                  **
  **                                                                            **
  **  DATE      : 2019-12-20                                                    **
  **                                                                            **
  **  BSW MODULE DECRIPTION : NA                                                **
  **                                                                            **
  **  VARIANT   : Variant PB                                                    **
  **                                                                            **
  **  PLATFORM  : Infineon AURIX2G                                              **
  **                                                                            **
  **  AUTHOR    : DL-AUTOSAR-Engineering                                        **
  **                                                                            **
  **  VENDOR    : Infineon Technologies                                         **
  **                                                                            **
  **  TRACEABILITY : [cover parentID={8B9A5B09-F90A-456f-872E-CE6AEC5276A1}]    **
  **                                                                            **
  **  DESCRIPTION  : Code template source file for Ocu Driver                   **
  **                                                                            **
  **  [/cover]                                                                  **
  **                                                                            **
  **  SPECIFICATION(S) : NA                                                     **
  **                                                                            **
  **  MAY BE CHANGED BY USER : no                                               **
  **                                                                            **
  *****************************************************************************/!]
  [!//
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
  **  FILENAME  : Ocu_PBcfg.c                                                   **
  **                                                                            **
  **  VERSION   : 1.40.0_9.0.0                                                  **
  **                                                                            **
  **  DATE, TIME: [!"$date"!], [!"$time"!]             !!!IGNORE-LINE!!!        **
  **                                                                            **
  **  GENERATOR : Build [!"$buildnr"!]               !!!IGNORE-LINE!!!          **
  **                                                                            **
  **  BSW MODULE DECRIPTION : NA                                                **
  **                                                                            **
  **  VARIANT   : Variant PB                                                    **
  **                                                                            **
  **  PLATFORM  : Infineon AURIX2G                                              **
  **                                                                            **
  **  AUTHOR    : DL-AUTOSAR-Engineering                                        **
  **                                                                            **
  **  VENDOR    : Infineon Technologies                                         **
  **                                                                            **
  **  DESCRIPTION  : Ocu configuration generated out of ECUC file               **
  **                                                                            **
  **  SPECIFICATION(S) : NA                                                     **
  **                                                                            **
  **  MAY BE CHANGED BY USER : no                                               **
  **                                                                            **
  *******************************************************************************/
  [!/*-- [cover parentID={0FBBC7B0-CA28-4744-B26D-5BFE7B8163AD}] OCU Variant support [/cover] --*/!][!//
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
  
  /*******************************************************************************
  **                       Includes                                             **
  *******************************************************************************/
  
  /* Include module header File */
  #include "Ocu.h"
  
  /*******************************************************************************
  **                      Private Macro Definitions                             **
  *******************************************************************************/
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_GTM_INTERRUPT_LEVEL_MODE          (0U)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_GTM_INTERRUPT_PULSE_MODE          (1U)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_GTM_INTERRUPT_PULSE_NOTIFY_MODE   (2U)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_GTM_INTERRUPT_SINGLE_PULSE_MODE   (3U)
  
  /*
  Define for Core identification 
  */
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_CORE0   (0U)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_CORE1   (0x100U)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_CORE2   (0x200U)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_CORE3   (0x300U)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_CORE4   (0x400U)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_CORE5   (0x500U)
  
  /* Alternate port pin selection  */
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_ALT_SELA ((uint32)0x00)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_ALT_SELB ((uint32)0x01)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_ALT_SELC ((uint32)0x02)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_ALT_SELD ((uint32)0x03)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_ALT_SELE ((uint32)0x04)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_ALT_SELF ((uint32)0x05)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_ALT_SELG ((uint32)0x06)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_ALT_SELH ((uint32)0x07)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_ALT_SELI ((uint32)0x08)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_ALT_SELJ ((uint32)0x09)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_ALT_SELK ((uint32)0x0A)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_ALT_SELL ((uint32)0x0B)
  
  /* Pin Used */
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_FALSE (0U)
  /*MISRA2012_RULE_2_5_JUSTIFICATION:
    Uses depends upon configuration done in configuration tool*/
  #define OCU_TRUE  (1U)
[!ENDINDENT!]  
[!NOCODE!][!//
  [!INCLUDE "Ocu.m"!][!//
[!ENDNOCODE!][!//
[!SELECT "as:modconf('Ocu')[1]"!][!//
  [!VAR "TBUTS0Used" = "count(./OcuConfigSet/OcuChannel/*/GtmTimerOutputModuleConfiguration/*/*[../GtmTimerClockSelect='GTM_TBU_TS0'])"!][!//
  [!VAR "TBUTS1Used" = "count(./OcuConfigSet/OcuChannel/*/GtmTimerOutputModuleConfiguration/*/*[../GtmTimerClockSelect='GTM_TBU_TS1'])"!][!//
  [!VAR "TBUTS2Used" = "count(./OcuConfigSet/OcuChannel/*/GtmTimerOutputModuleConfiguration/*/*[../GtmTimerClockSelect='GTM_TBU_TS2'])"!][!//
  
  [!INDENT "0"!]
    [!/*-- [cover parentID={24FE7174-DF2C-466f-979F-A7DAB6230767}]  [/cover] --*/!][!// 
    /* MCU code generation dependency */
  
    [!SELECT "as:modconf('Mcu')[1]"!][!//
      [!IF "num:i($TBUTS0Used) > 0"!]
        [!IF "./McuModuleConfiguration/GtmGlobalConfiguration/GtmGlobalConfiguration_0/GtmTbuChannelConf/GtmTbuChannelConf_0/GtmTbuChannelEnable = 'false'"!]
          [!ERROR!][!//
            OCU: Wrong Configuration. TBU_TS0 is selected for atleast one OCU channel but not configured in MCU.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!IF "num:i($TBUTS1Used) > 0"!]
        [!IF "./McuModuleConfiguration/GtmGlobalConfiguration/GtmGlobalConfiguration_0/GtmTbuChannelConf/GtmTbuChannelConf_1/GtmTbuChannelEnable = 'false'"!]
          [!ERROR!][!//
            OCU: Wrong Configuration. TBU_TS1 is selected for atleast one OCU channel but not configured in MCU.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      
      [!IF "num:i($TBUTS2Used) > 0"!]
        [!IF "./McuModuleConfiguration/GtmGlobalConfiguration/GtmGlobalConfiguration_0/GtmTbuChannelConf/GtmTbuChannelConf_2/GtmTbuChannelEnable = 'false'"!]
          [!ERROR!][!//
            OCU: Wrong Configuration. TBU_TS2 is selected for atleast one OCU channel but not configured in MCU.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDSELECT!][!//
    /*******************************************************************************
    **                       Function Declarations                                **
    *******************************************************************************/
    
    /******************************************************************************/

    [!NOCODE!][!//
      [!VAR "NotifyFunctionDatabase" = "''"!][!//
      [!LOOP "node:order(./OcuConfigSet/OcuChannel/*)"!][!//
        /*****BEGIN of Notification function definition from configuration**********/
        [!VAR "NotifyFunction" = "'(Ocu_NotifiPtrType)(0)'"!][!//
        [!IF "node:exists(./OcuNotification/*[1]) = 'true'"!][!//
          [!VAR "NotifyFunction" = "./OcuNotification/*[1]"!][!//
        [!ENDIF!][!//
        
        [!IF "string-length($NotifyFunction) = 0"!][!//
          [!VAR "NotifyFunction" = "'(Ocu_NotifiPtrType)(0)'"!][!//
        [!ENDIF!][!//
        
        [!IF "num:isnumber($NotifyFunction)= 'true'"!][!//
          [!VAR "NotifyFunction" = "'(Ocu_NotifiPtrType)(0)'"!][!//
        [!ENDIF!][!//
        
        [!IF "$NotifyFunction = '"NULL"' or $NotifyFunction = 'NULL'"!][!//
          [!VAR "NotifyFunction" = "'(Ocu_NotifiPtrType)(0)'"!][!//
        [!ENDIF!][!//
        
        /*****END of Notification function definition from configuration**********/
        [!IF "$NotifyFunction != '(Ocu_NotifiPtrType)(0)'"!][!//
          [!VAR "NotifyFunctionDatabase" = "concat($NotifyFunctionDatabase,$NotifyFunction,',')"!][!//
          [!IF "'true' = text:uniq(text:split($NotifyFunctionDatabase,','),$NotifyFunction)"!]
            [!CODE!]
              extern void [!"$NotifyFunction"!] (void);
            [!ENDCODE!]
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDNOCODE!][!//
  
  
    /******************************************************************************/
    
    /*******************************************************************************
    **                      Global Constant Definitions                           **
    *******************************************************************************/
  [!ENDINDENT!]
  [!NOCODE!][!//
    /**************************************************************/
    /*************** Channel configuration logic ******************/
    /**************************************************************/
  [!ENDNOCODE!][!//
  [!SELECT "as:modconf('Ocu')[1]"!][!//
    [!VAR "MaxChannelsCore0"= "num:i(0)"!][!//
    [!VAR "MaxChannelsCore1"= "num:i(0)"!][!//
    [!VAR "MaxChannelsCore2"= "num:i(0)"!][!//
    [!VAR "MaxChannelsCore3"= "num:i(0)"!][!//
    [!VAR "MaxChannelsCore4"= "num:i(0)"!][!//
    [!VAR "MaxChannelsCore5"= "num:i(0)"!][!//
    [!NOCODE!][!//
      [!CALL "OCU_CG_GenerateModuleMap"!][!//
      [!VAR "MaxChannels"= "num:i(count(./OcuConfigSet/OcuChannel/*))"!][!//
    [!ENDNOCODE!][!//

    [!NOCODE!][!//
      [!FOR "ChannelId" = "num:i(1)" TO "num:i($MaxChannels)"!][!//
        [!SELECT "./OcuConfigSet/OcuChannel/*[OcuChannelId = num:i($ChannelId) - num:i(1)]"!][!//
          [!VAR "ChannelATOM_TOM" = "substring-after(substring-after(substring-after(substring-before(GtmTimerOutputModuleConfiguration/*[1]/GtmTimerUsed,'ChannelAllocationConf_'),'/McuGtm'),'/McuGtm'),'/McuGtm')"!][!//
          [!VAR "Module_Number" = "substring-after(substring-before(substring-after(substring-after(GtmTimerOutputModuleConfiguration/*[1]/GtmTimerUsed,'/McuGtm'),'/McuGtm'),'/McuGtm'),'AllocationConf_')"!][!//
          [!VAR "Channel_Number" = "substring-after(GtmTimerOutputModuleConfiguration/*[1]/GtmTimerUsed,'ChannelAllocationConf_')"!][!//
          [!IF "$ChannelATOM_TOM = 'Tom'"!][!//
            [!VAR "ToutValue_Path" = "concat(concat(concat(concat('/AUTOSAR/TOP-LEVEL-PACKAGES/Mcu/ELEMENTS/Mcu/McuModuleConfiguration/GtmGlobalConfiguration/GtmGlobalConfiguration_0/GtmTomGlobalConf/GtmTomGlobalConf_',$Module_Number),'/GtmTomChannelConf/GtmTomChannelConf_'),$Channel_Number),'/GtmTimerPortPinSelect')"!][!//
          [!ELSE!]
            [!VAR "ToutValue_Path" = "concat(concat(concat(concat('/AUTOSAR/TOP-LEVEL-PACKAGES/Mcu/ELEMENTS/Mcu/McuModuleConfiguration/GtmGlobalConfiguration/GtmGlobalConfiguration_0/GtmAtomGlobalConf/GtmAtomGlobalConf_',$Module_Number),'/GtmAtomChannelConf/GtmAtomChannelConf_'),$Channel_Number),'/GtmTimerPortPinSelect')"!][!//
          [!ENDIF!][!// 
          [!VAR "ToutValue" = "node:value($ToutValue_Path)"!][!//
          [!IF "OcuOuptutPinUsed = 'true'"!]
            [!IF "$ToutValue = 'NONE'"!]
              [!ERROR!][!//
                Ocu:Error - For OcuChannel number [!"num:i($ChannelId)- num:i(1)"!] - [!"$ChannelATOM_TOM"!][!"$Module_Number"!].[!"$Channel_Number"!],
                OcuOuptutPinUsed is selected true but TOUT configurations are missing. Select the TOUT configurations in MCU module. 
                (EG. For AtOM0 channel 0 - Select TOUT configurations in ./GtmGlobalConfiguration/GtmGlobalConfiguration_0/GtmAtomGlobalConf/
                GtmAtomGlobalConf_0/GtmAtomChannelConf/GtmAtomChannelConf_0/GtmTimerPortPinSelect
              [!ENDERROR!][!//     
            [!ENDIF!][!//             
          [!ELSE!][!// 
            [!IF "$ToutValue != 'NONE'"!]
              [!ERROR!][!//
                Ocu:Error - For OcuChannel number [!"num:i($ChannelId)- num:i(1)"!] [!"$ChannelATOM_TOM"!][!"$Module_Number"!].[!"$Channel_Number"!], OcuOuptutPinUsed is selected false but TOUT configurations are not 'NONE'.
                (EG.For AtOM0 channel 0, Modify TOUT configurations in ./GtmGlobalConfiguration/GtmGlobalConfiguration_0/
                GtmAtomGlobalConf/GtmAtomGlobalConf_0/GtmAtomChannelConf/GtmAtomChannelConf_0/GtmTimerPortPinSelect 
              [!ENDERROR!][!//     
            [!ENDIF!][!//            
          [!ENDIF!][!//          
        [!ENDSELECT!][!//
      [!ENDFOR!][!//  
    [!ENDNOCODE!][!//
      


 
    [!FOR "CoreId" = "num:i(1)" TO "num:i(6)"!][!//
      [!NOCODE!][!//
        [!VAR "MaxChannelsCorex"= "num:i(0)"!][!//
      [!ENDNOCODE!][!//
      [!INDENT "0"!]      
         /* 
           Channel Configuration 
         */
        /***********Start of CORE [!"num:i(num:i($CoreId) - num:i(1))"!] configurations**************/
      [!ENDINDENT!]
      [!IF "contains($CGCoreMap,concat('CORE',num:i($CoreId) - num:i(1))) or num:i($CGMasterCoreId_Extract) = (num:i($CoreId) - num:i(1))"!][!//
        [!INDENT "0"!]
          [!/*-- [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]  [/cover] --*/!][!// 
          /* Memory mapping for constants */
          /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
             in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
             in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
             in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
             in generated code due to Autosar Naming constraints.*/
          #define OCU_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i(num:i($CoreId) - num:i(1))"!]_UNSPECIFIED
          /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
             guideline.*/
          /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
             guideline. */
          #include "Ocu_MemMap.h"
          [!/*-- [cover parentID={6D370FF5-8475-45d0-9896-C3DA19D1B457}]  [/cover] --*/!][!// 
          /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
             in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
             in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
             in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
             in generated code due to Autosar Naming constraints.*/
        
          [!IF "$VariantsConfigured = num:i(1)"!]
            static const Ocu_ChannelConfigType Ocu_kChannelConfigCore_[!"num:i(num:i($CoreId) - num:i(1))"!]_[!"$PredefinedVarName"!][ ] =
            [!ELSE!]
            static const Ocu_ChannelConfigType Ocu_kChannelConfigCore_[!"num:i(num:i($CoreId) - num:i(1))"!][ ] =
          [!ENDIF!]
          {
        [!ENDINDENT!]   
        [!FOR "ChannelId" = "num:i(1)" TO "num:i($MaxChannels)"!][!//
          [!SELECT "./OcuConfigSet/OcuChannel/*[OcuChannelId = num:i($ChannelId) - num:i(1)]"!][!//
            [!NOCODE!][!//
              [!CALL "OCU_CG_ValidateChAllocation", "CoreNumber" = "num:i($CoreId) - num:i(1)", "Channel" = "node:name(node:current())"!][!//
            [!ENDNOCODE!][!//
            [!IF "$CGAllocationResult = 'TRUE'"!][!//
              [!NOCODE!][!//
                [!VAR "MaxChannelsCorex"= "num:i($MaxChannelsCorex + 1)"!]
                [!IF "node:exists(./OcuNotification/*[1]) = 'true'"!][!// 
                  [!VAR "NotifyFunction" = "./OcuNotification/*[1]"!][!//
                [!ELSE!][!// 
                  [!VAR "NotifyFunction" = "''"!][!//
                [!ENDIF!][!//
                
                [!IF "string-length($NotifyFunction) = 0 or $NotifyFunction = '"NULL"' or $NotifyFunction = 'NULL' "!][!//
                  [!VAR "NotifyFunction" = "'(Ocu_NotifiPtrType)0'"!][!//
                [!ELSE!][!//
                  [!IF "num:isnumber($NotifyFunction)= 'true'"!][!//
                    [!VAR "NotifyFunction" = "concat('(Ocu_NotifiPtrType)',$NotifyFunction,'U')"!]
                  [!ELSE!][!//
                    [!VAR "NotifyFunction" = "concat('&',$NotifyFunction)"!]
                  [!ENDIF!][!//
                [!ENDIF!][!//
                [!VAR "OcuAssignedHardwareModule" = "number(substring-before(substring-after(./GtmTimerOutputModuleConfiguration/*[1]/GtmTimerUsed,'omAllocationConf_'),'/'))"!][!//
                [!VAR "OcuAssignedHardwareChannel" = "number(substring-after(./GtmTimerOutputModuleConfiguration/*[1]/GtmTimerUsed,'ChannelAllocationConf_'))"!][!//
                [!VAR "Cell" = "num:inttohex((num:i($OcuAssignedHardwareModule) * num:i(256)) + num:i($OcuAssignedHardwareChannel),4)"!][!//
                [!VAR "CellOption" = "concat('OCU_GTM_',text:toupper(substring-after(substring-after(substring-after(substring-before(./GtmTimerOutputModuleConfiguration/*[1]/GtmTimerUsed,'ChannelAllocationConf_'),'/McuGtm'),'/McuGtm'),'/McuGtm')))"!][!//
                [!VAR "OuptutPinUsed" = "concat('OCU_',text:toupper(OcuOuptutPinUsed))"!][!//
                [!VAR "DmaUsed" = "concat('OCU_',text:toupper(OcuOuptutPinUsed))"!][!//
                
                [!IF "num:i(count(./OcuHardwareTriggeredDMA/*)) = num:i(0)"!][!// ))"!][!//
                  [!VAR "DmaUsed" = "'OCU_FALSE'"!][!//
                [!ELSE!][!// ))"!][!//
                  [!VAR "DmaUsed" = "'OCU_TRUE'"!][!//
                [!ENDIF!][!//
                
                [!IF "num:i(count(./OcuHardwareTriggeredAdc/*)) = num:i(0)"!][!// ))"!][!//
                  [!VAR "AdcUsed" = "'OCU_FALSE'"!][!//
                [!ELSE!][!// ))"!][!//
                  [!VAR "AdcUsed" = "'OCU_TRUE'"!][!//
                [!ENDIF!][!//
                
                
                [!IF "node:exists(./OcuOutputPinDefaultState/*[1]) = 'true'"!][!// 
                  [!VAR "OutputPinDefaultState" = "./OcuOutputPinDefaultState/*[1]"!][!//
                [!ELSE!][!// 
                  [!VAR "OutputPinDefaultState" = "'OCU_LOW'"!][!//
                [!ENDIF!][!//
                
                
                [!VAR "MaxCounterValue" = "num:i(OcuMaxCounterValue)"!][!//
                
                [!SELECT "GtmTimerOutputModuleConfiguration/*[1]"!][!//
                  [!VAR "ClockSelect" = "concat('OCU_',GtmTimerClockSelect)"!][!//
                  [!IF "contains($ClockSelect,'TBU')"!][!//
                    [!VAR "CellOption" = "concat($CellOption,'_SHARED')"!][!//
                    [!VAR "MaxCounterValue" = "'0xFFFFFFU'"!][!//
                  [!ENDIF!][!// 
                [!ENDSELECT!][!// 
              [!ENDNOCODE!][!//
              [!INDENT "2"!] 
                {
              [!ENDINDENT!]
              [!INDENT "4"!]  
                /* OCU Channel [!"OcuChannelId"!] */
                [!"$NotifyFunction"!],/*Notification-function name*/
                (uint32)[!"num:i(OcuDefaultThreshold)"!],/*DefaultThreshold*/
                (uint32)[!"$MaxCounterValue"!],/*MaxCounterValue*/
                {
              [!ENDINDENT!]     
              [!INDENT "6"!]        
                [!"$CellOption"!], /* Assigned Hw Unit */
                [!"$Cell"!], /* Assigned Hw Unit Number */
                (uint8)[!"$OutputPinDefaultState"!], /* Pin default state */
                [!"$OuptutPinUsed"!], /* Pin Used */
                [!"$DmaUsed"!], /* Dma Used */
                [!"$AdcUsed"!], /* Adc Used */
                [!"$ClockSelect"!], /* Clock Select */
                0 /* Reserved and padded to 32 bits */
              [!ENDINDENT!]   
              [!INDENT "4"!]
                },
              [!ENDINDENT!]  
              [!INDENT "2"!]  
                }[!IF "$ChannelId != $MaxChannels"!],[!ENDIF!]
              [!ENDINDENT!]
              
            [!ENDIF!][!//
          [!ENDSELECT!][!//
        [!ENDFOR!][!// loop for all channels
        [!INDENT "0"!]
          };
          [!/*-- [cover parentID={2854FCF0-D9E7-40cb-84AC-1543FA89B889}]  [/cover] --*/!][!// 
          /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
             in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
             in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
             in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
             in generated code due to Autosar Naming constraints.*/
          [!IF "$VariantsConfigured = num:i(1)"!]
            static const Ocu_CoreConfigType Ocu_kConfigCore_[!"num:i(num:i($CoreId) - num:i(1))"!]_[!"$PredefinedVarName"!] =
          [!ELSE!]
            static const Ocu_CoreConfigType Ocu_kConfigCore_[!"num:i(num:i($CoreId) - num:i(1))"!] =
          [!ENDIF!]
          {
        [!ENDINDENT!] 
        [!INDENT "2"!]
          /* Pointer to Channel Configuration structure */
          [!IF "num:i($MaxChannelsCorex) != num:i(0)"!]
            [!IF "$VariantsConfigured = num:i(1)"!]
              &Ocu_kChannelConfigCore_[!"num:i(num:i($CoreId) - num:i(1))"!]_[!"$PredefinedVarName"!][0],
            [!ELSE!]
              &Ocu_kChannelConfigCore_[!"num:i(num:i($CoreId) - num:i(1))"!][0],
            [!ENDIF!]
          [!ELSE!][!//
            NULL_PTR,
          [!ENDIF!][!//   
          /* MaxChannelCore */
          [!/*-- [cover parentID={42324794-74EC-45cc-B1FA-307B25E225B4}]  [/cover] --*/!][!//
          [!"$MaxChannelsCorex"!]
          [!NOCODE!][!//
            [!IF "num:i($CoreId) = num:i(1)"!]
              [!VAR "MaxChannelsCore0"= "num:i($MaxChannelsCorex)"!]
            [!ELSEIF "num:i($CoreId) = num:i(2)"!]
              [!VAR "MaxChannelsCore1"= "num:i($MaxChannelsCorex)"!]
            [!ELSEIF "num:i($CoreId) = num:i(3)"!]
              [!VAR "MaxChannelsCore2"= "num:i($MaxChannelsCorex)"!]
            [!ELSEIF "num:i($CoreId) = num:i(4)"!]
              [!VAR "MaxChannelsCore3"= "num:i($MaxChannelsCorex)"!]
            [!ELSEIF "num:i($CoreId) = num:i(5)"!]
              [!VAR "MaxChannelsCore4"= "num:i($MaxChannelsCorex)"!]
            [!ELSEIF "num:i($CoreId) = num:i(6)"!]
              [!VAR "MaxChannelsCore5"= "num:i($MaxChannelsCorex)"!]
            [!ENDIF!]
          [!ENDNOCODE!][!//
        [!ENDINDENT!]
        [!INDENT "0"!]
          };
          /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
             in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
             in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
             in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
             in generated code due to Autosar Naming constraints.*/
          #define OCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i(num:i($CoreId) - num:i(1))"!]_UNSPECIFIED
          /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
             guideline.*/
          /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
             guideline. */
          #include "Ocu_MemMap.h"
        [!ENDINDENT!] 
      [!ENDIF!][!//
      [!INDENT "0"!]
        /***********End of CORE [!"num:i(num:i($CoreId) - num:i(1))"!] configurations**************/
      [!ENDINDENT!]
    [!ENDFOR!][!// loop of all cores
  [!ENDSELECT!][!//
  [!INDENT "0"!]
    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
       in generated code due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
       in generated code due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
       in generated code due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
       in generated code due to Autosar Naming constraints.*/
    #define OCU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
    /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
       guideline.*/
    /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
       guideline. */
    #include "Ocu_MemMap.h"
    /* MISRA2012_RULE_8_7_JUSTIFICATION: Module configuration data structure
       declaration as per Autosar guidelines. This data structure may be needed
       by SW units using Ocu Driver APIs */
    /* MISRA2012_RULE_8_4_JUSTIFICATION: Definition is as per Autosar guidelines */
    [!/*-- [cover parentID={D6B963D0-DE4D-4704-BB5C-D0D7E3DB24CB}]  [/cover] --*/!][!// 
    [!IF "$VariantsConfigured = num:i(1)"!]
      const Ocu_ConfigType Ocu_Config_[!"$PredefinedVarName"!] =
    [!ELSE!]
      const Ocu_ConfigType Ocu_Config =
    [!ENDIF!]
    {
  [!ENDINDENT!]       
  [!SELECT "OcuConfigSet"!][!//
    [!INDENT "2"!]
      /* Pointer to channel configuration set per core */
      {
    [!ENDINDENT!]
    [!INDENT "4"!]
      [!IF "num:i($MaxChannelsCore0) != num:i(0)"!]
        [!IF "$VariantsConfigured = num:i(1)"!]
          &Ocu_kConfigCore_0_[!"$PredefinedVarName"!],
        [!ELSE!]
          &Ocu_kConfigCore_0,
        [!ENDIF!]
      [!ELSE!][!//
        NULL_PTR,
      [!ENDIF!][!//   
      [!IF "num:i($MaxChannelsCore1) != num:i(0)"!]
        [!IF "$VariantsConfigured = num:i(1)"!]
          &Ocu_kConfigCore_1_[!"$PredefinedVarName"!],
        [!ELSE!]
          &Ocu_kConfigCore_1,
        [!ENDIF!]
      [!ELSE!][!//
        NULL_PTR,
      [!ENDIF!][!//   
      [!IF "num:i($MaxChannelsCore2) != num:i(0)"!]
        [!IF "$VariantsConfigured = num:i(1)"!]
          &Ocu_kConfigCore_2_[!"$PredefinedVarName"!],
        [!ELSE!]
          &Ocu_kConfigCore_2,
        [!ENDIF!]
      [!ELSE!][!//
        NULL_PTR,
      [!ENDIF!][!//   
      [!IF "num:i($MaxChannelsCore3) != num:i(0)"!]
        [!IF "$VariantsConfigured = num:i(1)"!]
          &Ocu_kConfigCore_3_[!"$PredefinedVarName"!],
        [!ELSE!]
          &Ocu_kConfigCore_3,
        [!ENDIF!]
      [!ELSE!][!//
        NULL_PTR,
      [!ENDIF!][!//   
      [!IF "num:i($MaxChannelsCore4) != num:i(0)"!]
        [!IF "$VariantsConfigured = num:i(1)"!]
          &Ocu_kConfigCore_4_[!"$PredefinedVarName"!],
        [!ELSE!]
          &Ocu_kConfigCore_4,
        [!ENDIF!]
      [!ELSE!][!//
        NULL_PTR,
      [!ENDIF!][!//   
      [!IF "num:i($MaxChannelsCore5) != num:i(0)"!]
        [!IF "$VariantsConfigured = num:i(1)"!]
          &Ocu_kConfigCore_5_[!"$PredefinedVarName"!]
        [!ELSE!]
          &Ocu_kConfigCore_5
        [!ENDIF!]
      [!ELSE!][!//
        NULL_PTR
      [!ENDIF!][!// 
    [!ENDINDENT!]
    [!INDENT "2"!]
      },
      #if (OCU_SINGLE_CORE == STD_OFF)
      [!NOCODE!]
        [!VAR "MaxChannelsCore0"= "num:i(0)"!][!//
        [!VAR "MaxChannelsCore1"= "num:i(0)"!][!//
        [!VAR "MaxChannelsCore2"= "num:i(0)"!][!//
        [!VAR "MaxChannelsCore3"= "num:i(0)"!][!//
        [!VAR "MaxChannelsCore4"= "num:i(0)"!][!//
        [!VAR "MaxChannelsCore5"= "num:i(0)"!][!//
        [!VAR "MappingValue"= "num:i(0)"!][!//
      [!ENDNOCODE!][!//
      {
    [!ENDINDENT!]   
    [!INDENT "4"!]
      [!VAR "MaxChannels"= "num:i(count(OcuChannel/*))"!][!//
      [!FOR "ChannelId" = "num:i(1)" TO "num:i($MaxChannels)"!][!//
        [!SELECT "OcuChannel/*[OcuChannelId = num:i($ChannelId) - num:i(1)]"!][!//
          [!NOCODE!][!//
            [!CALL "OCU_CG_GetCore", "Channel" = "node:name(node:current())"!][!//
          [!ENDNOCODE!][!//
          [!NOCODE!][!//
            [!IF "num:i($CGCoreId_Extract) = num:i(0)"!]
              [!VAR "MappingValue" = "concat('(OCU_CORE0 | ','(uint8)',$MaxChannelsCore0, ')')"!][!//
              [!VAR "MaxChannelsCore0"= "num:i($MaxChannelsCore0 + 1)"!][!//
            [!ELSEIF "num:i($CGCoreId_Extract) = num:i(1)"!]
              [!VAR "MappingValue" = "concat('(OCU_CORE1 | ','(uint8)',$MaxChannelsCore1, ')')"!][!//
              [!VAR "MaxChannelsCore1"= "num:i($MaxChannelsCore1 + 1)"!][!//
            [!ELSEIF "num:i($CGCoreId_Extract) = num:i(2)"!]
              [!VAR "MappingValue" = "concat('(OCU_CORE2 | ','(uint8)',$MaxChannelsCore2, ')')"!][!//
              [!VAR "MaxChannelsCore2"= "num:i($MaxChannelsCore2 + 1)"!][!//
            [!ELSEIF "num:i($CGCoreId_Extract) = num:i(3)"!]
              [!VAR "MappingValue" = "concat('(OCU_CORE3 | ','(uint8)',$MaxChannelsCore3, ')')"!][!//
              [!VAR "MaxChannelsCore3"= "num:i($MaxChannelsCore3 + 1)"!][!//
            [!ELSEIF "num:i($CGCoreId_Extract) = num:i(4)"!]
              [!VAR "MappingValue" = "concat('(OCU_CORE4 | ','(uint8)',$MaxChannelsCore4, ')')"!][!//
              [!VAR "MaxChannelsCore4"= "num:i($MaxChannelsCore4 + 1)"!][!//
            [!ELSEIF "num:i($CGCoreId_Extract) = num:i(5)"!]
              [!VAR "MappingValue" = "concat('(OCU_CORE5 | ','(uint8)',$MaxChannelsCore5, ')')"!][!//
              [!VAR "MaxChannelsCore5"= "num:i($MaxChannelsCore5 + 1)"!][!//
            [!ENDIF!][!// 
          [!ENDNOCODE!][!//
          (uint16)[!"$MappingValue"!][!IF "$ChannelId != $MaxChannels"!],[!ENDIF!]   
          
        [!ENDSELECT!][!//
      [!ENDFOR!][!//
    [!ENDINDENT!]
    [!INDENT "2"!]
      }
      #endif
    [!ENDINDENT!]
  [!ENDSELECT!][!//
  [!INDENT "0"!]
    };
    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
       in generated code due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
       in generated code due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
       in generated code due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
       in generated code due to Autosar Naming constraints.*/
    #define OCU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
    /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
       guideline.*/
    /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
       guideline. */
    #include "Ocu_MemMap.h"
  [!ENDINDENT!]
[!ENDSELECT!][!//
  