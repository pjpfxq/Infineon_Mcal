/*******************************************************************************
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
**  FILENAME     : Dsadc.c                                                    **
**                                                                            **
**  VERSION      : 1.40.0_21.0.0                                              **
**                                                                            **
**  DATE         : 2020-03-03                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={66CB20D2-C5FC-4052-9F35-784F8829DF70}]    **
**                                                                            **
**  DESCRIPTION  : Dsadc Driver source file                                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of DSADC Driver                          **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "McalLib.h"
#include "Mcal_Compiler.h"
#include "Dsadc.h"
#include "Dsadc_Cbk.h"
#include "IfxEdsadc_reg.h"
#include "IfxEdsadc_bf.h"
#include "IfxScu_reg.h"
#include "IfxScu_bf.h"
#include "SchM_Dsadc.h"
#if ((DSADC_CLC_FAILURE_DEM_NOTIF == DSADC_ENABLE_DEM_REPORT) ||\
    (DSADC_FIFO_FAILURE_DEM_NOTIF == DSADC_ENABLE_DEM_REPORT))
#include "Dem.h"
#endif
#if (DSADC_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
/* [cover parentID={20260F65-F7B9-4325-9643-294F9D7C0C81}]
    Safety Mechanism for reporting errors in ASIL B usecase [/cover] */
#if (DSADC_SAFETY_ENABLE == STD_ON)
#include "Mcal_SafetyError.h"
#endif
#if( (DSADC_INIT_DEINIT_API_MODE != DSADC_SUPERVISOR_MODE)||\
     (DSADC_RUN_TIME_API_MODE != DSADC_SUPERVISOR_MODE) )
#include "McalLib_OsStub.h"
#endif

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
#ifndef DSADC_SW_MAJOR_VERSION
  #error "DSADC_SW_MAJOR_VERSION is not defined."
#endif

#ifndef DSADC_SW_MINOR_VERSION
  #error "DSADC_SW_MINOR_VERSION is not defined."
#endif

#ifndef DSADC_SW_PATCH_VERSION
  #error "DSADC_SW_PATCH_VERSION is not defined."
#endif

/*[cover parentID={6D3107C6-D6DE-4e37-936E-A4D070411E1F}] 
  Modules version consistency check [/cover]*/
#if ( DSADC_SW_MAJOR_VERSION != 10U )
  #error "DSADC_SW_MAJOR_VERSION does not match."
#endif

#if ( DSADC_SW_MINOR_VERSION != 40U )
  #error "DSADC_SW_MINOR_VERSION does not match."
#endif

#if ( DSADC_SW_PATCH_VERSION != 1U )
  #error "DSADC_SW_PATCH_VERSION does not match."
#endif


/*[cover parentID={56921211-582D-4425-8894-4C419DA4EEAC}] Version Check for DET
[/cover]*/
#if (DSADC_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
  #error "DET_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

#if ( DET_AR_RELEASE_MAJOR_VERSION != 4U )
  #error "DET_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#endif /* End for DSADC_DEV_ERROR_DETECT */

#if ((DSADC_CLC_FAILURE_DEM_NOTIF == DSADC_ENABLE_DEM_REPORT) ||\
   (DSADC_FIFO_FAILURE_DEM_NOTIF == DSADC_ENABLE_DEM_REPORT))

/*[cover parentID={56921211-582D-4425-8894-4C419DA4EEAC}] Version Check for DEM
[/cover]*/
#ifndef DEM_AR_RELEASE_MAJOR_VERSION
  #error "DEM_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

#if ( DEM_AR_RELEASE_MAJOR_VERSION != 4U )
  #error "DEM_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#endif /*End For DSADC_CLC_FAILURE_DEM_NOTIF and DSADC_FIFO_FAILURE_DEM_NOTIF*/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/* Macro for the fixed value */
#define DSADC_ONE_U                          (0x1U)


/* Macro for Impplausible channel ID*/
#if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
#define DSADC_IMPLAUSIBLE_CHANNEL_ID        (0xFFU)
#endif

/*Macro for DSADC Notification*/
#define DSADC_NOTIFICATION_ENABLE            (0x1U)
#define DSADC_NOTIFICATION_DISABLE           (0x0U)
#define DSADC_NOTIFICATION_LEN               (1)

/*Macro for CSRWC enable*/
#define DSADC_CH_FCFGM_CSRWC_ENABLE          (0x1U)

/*Macro for Module clock*/
#define DSADC_MODULE_CLK_ENABLE              (0x0U)
#if(DSADC_DEINIT_API == STD_ON)
#define DSADC_MODULE_CLK_DISABLE             (0x1U)
#endif

#if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
/*Macro for DSADC Buffer*/
#define DSADC_MAX_BUFFER_LENGTH              (0xFFFEU)
#define DSADC_READSTREAM_ERROR               (0xFFFFU)
#endif

/* Macros for DSADC Registers Reset value */
#if(DSADC_DEINIT_API == STD_ON)
#define DSADC_RESET_CLC_REG                  ((uint32)0x00000001U)
#endif
#define DSADC_GLOBCFG_REG_RESET_VALUE        ((uint32)0x80008000U)
#define DSADC_GLOBRC_REG_RESET_VALUE         ((uint32)0x00000000U)
#define DSADC_CGCFG_REG_RESET_VALUE          ((uint32)0x00000000U)
#define DSADC_CLR_ALL_EDSADC_CH_EVENTS       ((uint32)0x3FFF3FFFU)
#define DSADC_MODCFG_RESET_VALUE             ((uint32)0x80008000U)
#define DSADC_DICFG_RESET_VALUE              ((uint32)0x80008000U)
#define DSADC_VCM_RESET_VALUE                ((uint32)0x00000000U)
#define DSADC_GAINCAL_RESET_VALUE            ((uint32)0x61A81000U)
#define DSADC_GAINCTR_RESET_VALUE            ((uint32)0x00001000U)
#define DSADC_GAINCORR_RESET_VALUE           ((uint32)0x00001000U)
#define DSADC_OFFCOMP_RESET_VALUE            ((uint32)0x00000000U)
#define DSADC_IWCTR_RESET_VALUE              ((uint32)0X00000000U)
#define DSADC_FCFGM_RESET_VALUE              ((uint32)0x80008000U)
#define DSADC_FCFGC_RESET_VALUE              ((uint32)0x00000000U)
#define DSADC_FCFGA_RESET_VALUE              ((uint32)0x00000000U)
#define DSADC_TSTCNT_RESET_VALUE             ((uint32)0x00000000U)
#define DSADC_RFC_RESET_VALUE                ((uint32)0x00000070U)
#define DSADC_BOUNDSEL_RESET_VALUE           ((uint32)0x00000000U)
#define DSADC_CGSYNC_RESET_VALUE             ((uint32)0x00000000U)
#define DSADC_RECTCFG_RESET_VALUE            ((uint32)0x00000000U)
#define DSADC_OVSCFG_RESET_VALUE             ((uint32)0x00000000U)

#if(DSADC_ERUTRIGGER_USED == STD_ON)
/* Macros for ERU-ERS channel configuration */
#define DSADC_ERS_CH_EICR_SHIFT              (0x4U)
#define DSADC_ERS_CH_RESET                   (0x0U)

/* Macros for ERU-OGU channel configuration */
#define DSADC_OGU_CH_IGCR_SHIFT              (0x4U)
#define DSADC_OGU_CH_RESET                   (0x0U)
#define DSADC_OGU_INTERRUPT_MASK             (0x3FFFU)
#define DSADC_ERU_WR_MASK                    ((uint32)0x0000FFFFU)
#endif

/* Macros for Modulator and Demodulator control */
#define DSADC_MODULATOR_RUN_CFG              (0x10U)
#define DSADC_CH_MOD_START                   (0x1U)
#define DSADC_CH_DEMOD_START                 (0x1U)
#define DSADC_GLOBRC_MxRUN_LEN               (1)
#define DSADC_GLOBRC_CHxRUN_LEN              (1)

/*Macro for Calibration algorithm*/
#define DSADC_START_CALIB_ALGO               (0x9U)
#define DSADC_CH_FCFGM_CALIB_CSRWC_LEN       (4)

/*Macro for Main Service Request disable*/
#define DSADC_MAIN_SERVICE_DISABLE           (0x0U)

/*Macro for DSADC HW FIFO Error*/
#define DSADC_NO_FIFO_ERROR                  ((uint8)0x0U)
#define DSADC_FIFO_ERROR                     ((uint8)0x1U)
#define DSADC_WRITE_ERROR_CHECK              (0x1U)
#define DSADC_READ_ERROR_CHECK               (0x1U)
#define DSADC_CLEAR_FIFO_ERROR               (0x1U)
#define DSADC_CH_FIFO_NOT_USED               (0x1U)

#if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
/*Macro for Linear buffer handling*/
#define DSADC_CH_BUFFER_FULL                 (0x1U)
#endif

/*Macro for Carrier generator*/
#define DSADC_CGCFG_CGMOD_LEN                (2)
#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
#define DSADC_CARR_SIG_RUN                   (0x1U)
#endif


#if(DSADC_GTMTRIGGER_USED == STD_ON)
/*Macro for GTM Gate control*/
#define DSADC_GTM_CCU0_EVNT_MSK              (0x0U)
#define DSADC_GTM_CCU1_EVNT_MSK              (0x1U)
#define DSADC_GATE_GTM_MSK_LEN               (0x1U)
#if(DSADC_SAFETY_ENABLE == STD_ON)
#define DSADC_GTM_ISR_MSK                    (0x3U)
#endif
#endif

#if(DSADC_ERUTRIGGER_USED == STD_ON)
/*Macro for ERU Gate control*/
#define DSADC_ERU_GATE_PD_MATCH_MASK         (0x1U)
#define DSADC_ERU_GATE_PD_MISS_MASK          (0x0U)
#if(DSADC_SAFETY_ENABLE == STD_ON)
#define DSADC_ERU_ISR_MSK                    (0x1U)
#endif
#endif

#if (DSADC_INITCHECK_API == STD_ON)
/*Macro for Write Protect Mask*/
#define DSADC_GLOBCFG_WRITE_PROTECT_MSK      ((uint32)0xFFFF7FFFU)
#define DSADC_MODCFG_WRITE_PROTECT_MSK       ((uint32)0x7FFF7FFFU)
#define DSADC_DICFG_WRITE_PROTECT_MSK        ((uint32)0x7FFF7FFFU)
#define DSADC_FCFGM_WRITE_PROTECT_MSK        ((uint32)0x7FFF7FFFU)
#define DSADC_CGCFG_READONLY_MSK             ((uint32)0x000000FFU)
#define DSADC_RECTCFG_READONLY_MSK           ((uint32)0x00000F31U)
#define DSADC_MODCFG_READONLY_MSK            ((uint32)0x0C7773FFU)
#define DSADC_TSCNT_READONLY_MSK             ((uint32)0x001B0000U)
#define DSADC_RFC_READONLY_MSK               ((uint32)0x00000073U)
#define DSADC_CGSYNC_READONLY_MSK            ((uint32)0xFFFF0000U)
#define DSADC_FCFGA_READONLY_MSK             ((uint32)0x00000003U)
#define DSADC_OFFCOMP_DISABLED               (0x0U)
#endif

/*******************************************************************************
**                         User Mode Macros                                   **
*******************************************************************************/
/*[cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}] User Mode Support via
OS function calls Macros [/cover] */

/* [cover parentID={8BB0CB09-F581-45fe-81B1-79BEA080CC23}]
Precompile Time support for User Mode
[/cover] */

#if(DSADC_INIT_DEINIT_API_MODE == DSADC_SUPERVISOR_MODE)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
  #define DSADC_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)   \
    Mcal_WritePeripEndInitProtReg(RegAdd,Data)

  #if(DSADC_ERUTRIGGER_USED == STD_ON)
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
     User mode support in code. No side effects foreseen by violating this MISRA
     rule. */
  #define DSADC_INIT_DEINIT_WRITE_SAFETY_ENDINIT_PROTREGMASK(RegAdd,Data,Mask) \
    Mcal_WriteSafetyEndInitProtRegMask(RegAdd,Data,Mask)
  #endif

#else

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
  #define DSADC_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)   \
    MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)
  #if(DSADC_ERUTRIGGER_USED == STD_ON)
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
     User mode support in code. No side effects foreseen by violating this MISRA
     rule. */
    #define DSADC_INIT_DEINIT_WRITE_SAFETY_ENDINIT_PROTREGMASK(RegAdd,Data,Mask) \
      MCAL_LIB_WRITESAFETYENDINITPROTREGMASK(RegAdd,Data,Mask)
  #endif
#endif

#if(DSADC_RUN_TIME_API_MODE == DSADC_SUPERVISOR_MODE)
  #if(DSADC_ERUTRIGGER_USED == STD_ON)
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
     User mode support in code. No side effects foreseen by violating this MISRA
     rule. */
    #define DSADC_RUNTIME_WRITE_SAFETY_ENDINIT_PROTREGMASK(RegAdd,Data,Mask)    \
    Mcal_WriteSafetyEndInitProtRegMask(RegAdd,Data,Mask)
  #endif
#else
  #if(DSADC_ERUTRIGGER_USED == STD_ON)
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
     User mode support in code. No side effects foreseen by violating this MISRA
     rule. */
    #define DSADC_RUNTIME_WRITE_SAFETY_ENDINIT_PROTREGMASK(RegAdd,Data,Mask)    \
    MCAL_LIB_WRITESAFETYENDINITPROTREGMASK(RegAdd,Data,Mask)
  #endif
#endif

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   'DSADC_GET_HW_CH_NUM' defined for easy readability in code.
   No side effects foreseen by violating this MISRA rule. */
#define DSADC_GET_HW_CH_NUM(ChannelId) \
               (Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].\
                HwAssignedChannelNum);

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/* [cover parentID={3CC22D40-8338-4118-A302-3C6759974FD1}]
   Type Definition for Dsadc_ChannelDataType [/cover] */
typedef struct
{
  #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
  Dsadc_ResultType *ChannelResBuffer;
  Dsadc_SizeType NumofValidConRes;
  Dsadc_SizeType ReadPtrCircularBuf;
  Dsadc_SizeType WritePtrCircularBuf;
  Dsadc_SizeType ChannelBufferSize;
  uint8 FifoErrorStatus;
  uint8 BufferFull;
  #endif
  Dsadc_TimeStampType TimestampCount;
  Dsadc_ChannelstatusType ChannelStatus;
  Dsadc_CalibrationStatusType CalibrationStatus;
}Dsadc_ChannelDataType;

#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON) ||\
                                           (DSADC_INITCHECK_API == STD_ON))
/* [cover parentID={A9A92A95-D115-4eb9-A90D-6719DCFE0BD3}]
   Type Definition for Dsadc_InitStateType [/cover] */
typedef enum
{
  DSADC_UNINIT_COMPLETED=0U,
  DSADC_UNINIT_STARTED=1U,
  DSADC_INITIALIZED=2U
}Dsadc_InitStateType;
#endif

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Code Memory section naming as per AS [/cover]*/
/*[cover parentID={4818BF36-0345-4005-A786-15587C80B789}]
MemMap_h file to be developed by user [/cover]*/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}] Memory mapping
support [/cover] */
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define DSADC_START_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline.*/
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
  without safegaurd. It complies to Autosar guidelines. */
#include "Dsadc_MemMap.h"

/*** Local functions for Initialization and DeInitialization ***/
static void Dsadc_lResetSfr (const Dsadc_ConfigType * const ConfigPtr);
LOCAL_INLINE void Dsadc_lConfigSfr (const Dsadc_ConfigType * const ConfigPtr);

#if(DSADC_ERUTRIGGER_USED == STD_ON)
LOCAL_INLINE void Dsadc_lDeInitErsChannels(\
        const Dsadc_EruErsConfigType * const ErsChannelConfigPtr);
LOCAL_INLINE void Dsadc_lConfigErsChannels(\
        const Dsadc_EruErsConfigType * const ErsChannelConfigPtr);
#endif
/*** Local functions for Initialization check ***/
#if(DSADC_INITCHECK_API == STD_ON)
LOCAL_INLINE Std_ReturnType Dsadc_lInitCheck(void);
#if(DSADC_ERUTRIGGER_USED == STD_ON)
LOCAL_INLINE uint32 Dsadc_lCheckConfigErsChannels(
        const Dsadc_EruErsConfigType * const ErsChannelConfigPtr,\
        const uint32 CompareFlag);
#endif
LOCAL_INLINE uint32 Dsadc_lCheckGlobalVars(const uint32 CompareFlag);
#endif/*End for DSADC_INITCHECK_API*/

#if(DSADC_ERUTRIGGER_USED == STD_ON)
/*** Local functions for Trigger Enable/Disable ***/
LOCAL_INLINE void Dsadc_lDisableEruTrigger(\
        const Dsadc_ChannelConfigType * const DsadcChannelConfigPtr);
LOCAL_INLINE void Dsadc_lEnableEruTrigger(\
        const Dsadc_ChannelConfigType * const DsadcChannelConfigPtr);
LOCAL_INLINE void Dsadc_lEnableEruInterrupt(\
        const Dsadc_ChannelConfigType * const DsadcChannelConfigPtr);
#endif

/*** Local function for HW error Check and Clear ***/
static uint8 Dsadc_lHwFifoErrorHandling(const Dsadc_ChannelType ChannelId);

/*** Local function for Modulator and Demodulator Enable ***/
LOCAL_INLINE void Dsadc_lEnableModulation(const Dsadc_ChannelType HwChannelId);

#if((DSADC_GTMTRIGGER_USED == STD_ON) || (DSADC_ERUTRIGGER_USED == STD_ON) \
                              || (DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON))
/*** Local function for Channel Notification ***/
LOCAL_INLINE uint32 Dsadc_lGetChanNotifStatus(\
                                     const Dsadc_ChannelType ChannelId);
#endif                                     

/*** Local functions for the window events ***/
#if(DSADC_GTMTRIGGER_USED == STD_ON)
LOCAL_INLINE void Dsadc_lGtmIsr(const Dsadc_ChannelType ChannelId,\
                                            const uint32 StatusFlag);
#endif
#if(DSADC_ERUTRIGGER_USED == STD_ON)
LOCAL_INLINE void Dsadc_lEruIsr(const Dsadc_ChannelType ChannelId,\
                                            const uint32 StatusFlag);
#endif

#if((DSADC_GTMTRIGGER_USED == STD_ON) || (DSADC_ERUTRIGGER_USED == STD_ON))
LOCAL_INLINE void Dsadc_lWindowOpenEvnt(const Dsadc_ChannelType ChannelId);
LOCAL_INLINE void Dsadc_lWindowCloseEvnt(const Dsadc_ChannelType ChannelId);
#endif

/*** Local functions for DET Check ***/
#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
LOCAL_INLINE uint8 Dsadc_lInitDetCheck(const Dsadc_ConfigType *ConfigPtr);

#if(DSADC_DEINIT_API == STD_ON)
LOCAL_INLINE uint8 Dsadc_lDeInitDetCheck(void);
#endif

LOCAL_INLINE uint8 Dsadc_lStartModDetCheck(const Dsadc_ChannelType ChannelId);
LOCAL_INLINE uint8 Dsadc_lStopModDetCheck(const Dsadc_ChannelType ChannelId);

#if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
LOCAL_INLINE uint8 Dsadc_lReadResultDetCheck(const Dsadc_ChannelType ChannelId,\
                                      const Dsadc_ResultType * const ResultPtr);  
LOCAL_INLINE uint8 Dsadc_lReadStreamResDetCheck(\
         const Dsadc_ChannelType ChannelId,\
         const Dsadc_ResultType * const ResultLinearBufferPtr);
LOCAL_INLINE uint8 Dsadc_lSetupResBufDetCheck(\
             const Dsadc_ChannelType ChannelId,\
             const Dsadc_ResultType * const DataBufferPtr);            
LOCAL_INLINE uint8 Dsadc_lCheckBufferPointerDet(const Dsadc_ChannelType \
  ChannelId,const Dsadc_ResultType * const DataPtr,const uint8 ServiceId);
#endif

#if((DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON) || \
                                          (DSADC_VERSION_INFO_API == STD_ON))
LOCAL_INLINE uint8 Dsadc_lCheckParamPointerDet( const void * const DataPtr,\
                                                       const uint8 ServiceId);
#endif

LOCAL_INLINE uint8 Dsadc_lGetStatusDetCheck(const Dsadc_ChannelType ChannelId);
LOCAL_INLINE uint8 Dsadc_lStartCarrSigDetCheck(void);
LOCAL_INLINE uint8 Dsadc_lStopCarrSigDetCheck(void);
LOCAL_INLINE uint8 Dsadc_lEnNotifDetCheck(const Dsadc_ChannelType ChannelId);
LOCAL_INLINE uint8 Dsadc_lDisNotifDetCheck(const Dsadc_ChannelType ChannelId);
LOCAL_INLINE uint8 Dsadc_lGetTimestampDetCheck(\
             const Dsadc_ChannelType ChannelId);
LOCAL_INLINE uint8 Dsadc_lStartCalibDetCheck(\
             const Dsadc_ChannelType ChannelId);
LOCAL_INLINE uint8 Dsadc_lGetCalibStatusDetCheck(\
             const Dsadc_ChannelType ChannelId);
LOCAL_INLINE uint8 Dsadc_lCheckUnInitDet(const uint8 ServiceId);
LOCAL_INLINE uint8 Dsadc_lCheckChanDet(const Dsadc_ChannelType ChannelId, \
                          const uint8 ServiceId);
LOCAL_INLINE uint8 Dsadc_lCheckNotifCapableDet(const Dsadc_ChannelType\
                                         ChannelId,const uint8 ServiceId);
LOCAL_INLINE void Dsadc_lReportError(const uint8 ServiceId, \
                                               const uint8 ErrorId);
#endif /*End for DSADC_DEV_ERROR_DETECT == STD_ON or
                     DSADC_SAFETY_ENABLE == STD_ON)*/

/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Code Memory section naming as per AS [/cover]*/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define DSADC_STOP_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline.*/
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
  without safegaurd. It complies to Autosar guidelines. */
#include "Dsadc_MemMap.h"

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/*[cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
Variables Memory section as per AS
[/cover]*/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define DSADC_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline.*/
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
  without safegaurd. It complies to Autosar guidelines. */
#include "Dsadc_MemMap.h"

static const Dsadc_ConfigType *Dsadc_ConfigPtr;
static Dsadc_ChannelDataType Dsadc_ChannelData[DSADC_MAX_CHANNELS_CONFIGURED];
#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON) ||\
                                           (DSADC_INITCHECK_API == STD_ON))
static Dsadc_InitStateType Dsadc_InitStatus;
#endif
/*MISRA2012_RULE_8_9_JUSTIFICATION: Variable not defined at block scope.
  No side effects foreseen by violating this MISRA rule, as the variable 
  is accessed by different APIs*/
static uint32 Dsadc_ChanNotifstatus;

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define DSADC_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline.*/
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
  without safegaurd. It complies to Autosar guidelines. */
#include "Dsadc_MemMap.h"
/*[cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
Variables Memory section as per AS
[/cover]*/

#if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
/*[cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
Variables Memory section as per AS
[/cover]*/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define DSADC_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_8
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline.*/
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
  without safegaurd. It complies to Autosar guidelines. */
#include "Dsadc_MemMap.h"

static uint8 Dsadc_ChannelId_Map[DSADC_NUM_OF_CHANNELS];

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define DSADC_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_8
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline.*/
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
  without safegaurd. It complies to Autosar guidelines. */
#include "Dsadc_MemMap.h"
/*[cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
Variables Memory section as per AS
[/cover]*/
#endif

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Code Memory section naming as per AS [/cover]*/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define DSADC_START_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline.*/
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
  without safegaurd. It complies to Autosar guidelines. */
#include "Dsadc_MemMap.h"

/*******************************************************************************
** Traceability     : [cover parentID={DCD29062-A107-4816-B56F-35CF18654526}] **
**                                                                            **
** Syntax           : void Dsadc_Init                                         **
**                    (                                                       **
**                      const Dsadc_ConfigType  * const ConfigPtr             **
**                    )                                                       **
**                                                                            **
** Description      : This API initializes the DSADC Hardware as per the      **
**                    configuration pointer passed and sets all the Global    **
**                    variables to their required initial values.The          **
**                    SFR's of DSADC Hardware resets to its default values    **
**                    and then it is configured with the given configuration  **
**                    data.This API will set the DSADC module state to        **
**                    DSADC_INITIALIZED if the initialization was successful. **
**                                                                            **
**                    It also enables the DSADC module by writing into the    **
**                    CLC register and Enable the Modulator and Demodulator   **
**                    for the configured channels                             **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1A                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to the DSADC Driver configuration   **
**                                structure                                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Dsadc_Init(const Dsadc_ConfigType * const ConfigPtr)
{
  uint8 ChannelId;
  uint8 HwChannelNum;
  
  /*[cover parentID={64BB0CF9-CBDE-46e9-A471-3234D678976F}]
    DET is ON or SAFETY is ON  [/cover]*/
  #if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;

  /*check DET for the API*/
  lDetVal = Dsadc_lInitDetCheck(ConfigPtr);
  /*[cover parentID={5D6AE13F-F19B-42a9-B939-9648AC706E97}]
  Check if there is no Error [/cover]*/
  if(lDetVal == DSADC_E_NO_ERR)
  #endif
  {
    /*[cover parentID={8DC1E37C-3777-424a-8279-BB8ADD44D614}]
  Enable DSADC module clock and Sleep mode configuration [/cover]*/
    DSADC_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&MODULE_EDSADC.CLC.U,\
                ((uint32)ConfigPtr->DsadcClcCtrlReg));

    /*[cover parentID={E2089BD3-5ECE-4cc3-A1DD-F3A3D1C0FE6E}]
    Check if the EDSADC module clock enabled [/cover]*/
    if(Mcal_GetBitAtomic(MODULE_EDSADC.CLC.U,IFX_EDSADC_CLC_DISS_OFF, \
                          IFX_EDSADC_CLC_DISS_LEN) == DSADC_MODULE_CLK_ENABLE)
    {
    /*[cover parentID={51E14600-3218-445a-9A00-305005A7F4AF}]
        DEM Notify is ON for CLC [/cover]*/
      #if (DSADC_CLC_FAILURE_DEM_NOTIF == DSADC_ENABLE_DEM_REPORT)
      /*[cover parentID={269B7FD8-0DBC-4fac-BEF7-26145668117D}]
        Raise DEM Pass, when CLC enabling is successful [/cover]*/
      Dem_ReportErrorStatus(DSADC_E_CLC_FAILURE, DEM_EVENT_STATUS_PASSED);
      #endif
      /*[cover parentID={A82E517B-B232-4d93-89DC-BCAE01102743}]
         Not all the channels using DMA [/cover]*/
      #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
      /*Initialize the HW channel Mapping array with implausible value*/
      for(ChannelId = 0; ChannelId < DSADC_NUM_OF_CHANNELS;ChannelId++)
      {
        /*Initialize the Channel mapping array with implausible value*/
        Dsadc_ChannelId_Map[ChannelId] = DSADC_IMPLAUSIBLE_CHANNEL_ID;
      }
      #endif
      /*Copy the configuration data to the Local Pointer.*/
      Dsadc_ConfigPtr = ConfigPtr;
      /*[cover parentID={6B27BED5-D148-4300-B849-41F1E95BAB34}]
      Reset the DSADC and trigger source registers [/cover]*/
      Dsadc_lResetSfr(Dsadc_ConfigPtr);
      /*[cover parentID={F6626AEF-511D-40f8-8155-A1F138B241F7}]
      Configure the DSADC registers and channel trigger source registers
      [/cover]*/
      Dsadc_lConfigSfr(Dsadc_ConfigPtr);
      /*[cover parentID={442E6720-BA0B-404e-B085-5F51CF643992}]
      Initialize the Global Channel Data [/cover] */
      for(ChannelId = 0; ChannelId < DSADC_MAX_CHANNELS_CONFIGURED; \
                                                              ChannelId++)
      {
        /* Obtain the DSDAC HW channel assigned to ChannelId */
        HwChannelNum = DSADC_GET_HW_CH_NUM(ChannelId);
        /*[cover parentID={424715AD-10BC-447e-BEC0-75AFE3889939}]
           Not all the channels using DMA [/cover]*/
        #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
        /* Map the Logical Channel Id to the Hardware channel ID */
        Dsadc_ChannelId_Map[HwChannelNum] = ChannelId;
        #endif
        /*[cover parentID={EDF69D9D-CD44-4c52-BBEA-B11C28CBD473}]
          Set the calibration status to Not Started  [/cover]*/
        Dsadc_ChannelData[ChannelId].CalibrationStatus = \
                                      DSADC_CALIBRATION_NOT_STARTED;
        /*[cover parentID={AA4D9EA7-173D-4064-B448-7D0F3AFD95FC}]
        Set the channel status to IDLE  [/cover]*/
        Dsadc_ChannelData[ChannelId].ChannelStatus = DSADC_IDLE;
        /*[cover parentID={14C17B08-9DC3-438d-A34A-4D31E7D7C759}]
           Not all the channels using DMA [/cover]*/
        #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
        /*Initialize the Number of Valid Result to 0*/
        Dsadc_ChannelData[ChannelId].NumofValidConRes = (uint16)0U;
        /* Set no error for the FIFO Error Status*/
        Dsadc_ChannelData[ChannelId].FifoErrorStatus = DSADC_NO_FIFO_ERROR;
        /*Reset the Buffer full status*/
        Dsadc_ChannelData[ChannelId].BufferFull = (uint8)0U;
        /*Initialize the circular buffer Read Pointer*/
        Dsadc_ChannelData[ChannelId].ReadPtrCircularBuf = (uint16)0U;
        /*Initialize the circular buffer Write Pointer*/
        Dsadc_ChannelData[ChannelId].WritePtrCircularBuf = (uint16)0U;
        #endif
         /*Enable the Modulator and Demodulator*/
        Dsadc_lEnableModulation(HwChannelNum);
      }
      /* Reset Dsadc Channel Notification status for all Channel */
      Dsadc_ChanNotifstatus = (uint32)0U;
      /*[cover parentID={2E352509-BF95-4f02-8BA3-7B452D518215}]
        DET or SAFETY or Initcheck API is ON [/cover]*/
      #if ((DSADC_DEV_ERROR_DETECT == STD_ON) ||\
          (DSADC_SAFETY_ENABLE == STD_ON) || (DSADC_INITCHECK_API == STD_ON))
    /*[cover parentID={70A1C0B8-243A-4160-9671-690E89EE83E4}]
          Set the DSADC driver status to initialized  [/cover]*/
      Dsadc_InitStatus = DSADC_INITIALIZED;
      #endif
    }
    /*[cover parentID={625576A7-3176-49cb-974B-62D86C2E86D5}]
       DEM Notify is ON for CLC [/cover]*/
    #if (DSADC_CLC_FAILURE_DEM_NOTIF == DSADC_ENABLE_DEM_REPORT)
    else
    {
      /*[cover parentID={982E9348-962F-483f-8D0B-48C9AEBB1552}]
        Raise DEM failure, when CLC enabling fails [/cover]*/
      Dem_ReportErrorStatus(DSADC_E_CLC_FAILURE, DEM_EVENT_STATUS_FAILED);
    }
    #endif
  }
}

/* [cover parentID={BA2883BE-E25F-42a9-8AD5-C4EAB9D40613}]
   Interrupt Control Registers.
   [/cover] */

#if(DSADC_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={E66B4C7C-DA26-4900-800E-971628712B48}] **
**                                                                            **
** Syntax           : void Dsadc_DeInit(void)                                 **
**                                                                            **
** Description      : This API resets all SFRs of the DSADC Module configured **
**                    during Initialization to their reset values.It sets the **
**                    DSADC state to DSADC_UNINIT_COMPLETED after successful  **
**                    De-Initialization. It also disables the DSADC Module by **
**                    writing into the CLC Register.                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1B                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Dsadc_DeInit(void)
{
  const Dsadc_ConfigType *LocalConfigPtr;
  uint8 ChannelId;
  
  /*[cover parentID={631100D2-C5B7-4712-B2E1-AA6A3597380A}]
  DET is ON or SAFETY is ON  [/cover]*/
  #if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;

  /*check DET for the API*/
  lDetVal = Dsadc_lDeInitDetCheck();
  /* [cover parentID={6475FD3E-3F73-4698-9CF8-D4A77E88FFD2}]
     check if there is no error [/cover]*/
  if(lDetVal == DSADC_E_NO_ERR)
  #endif
  {
    /*[cover parentID={AE701B23-A45E-4874-9492-A943E98AF793}]
      DET or SAFETY or Initcheck API is ON [/cover]*/
    #if ((DSADC_DEV_ERROR_DETECT == STD_ON) || \
         (DSADC_SAFETY_ENABLE == STD_ON) || (DSADC_INITCHECK_API == STD_ON))
    /*[cover parentID={7A68EF24-ADAD-4d0e-9395-6BF2247EFB00}]
      set the driver state to DeInit Started state [/cover]*/
    Dsadc_InitStatus = DSADC_UNINIT_STARTED;
    #endif
    /*Store the Configuration data to local pointer */
    LocalConfigPtr = Dsadc_ConfigPtr;
    /*Reset Configuration Pointer to NULL */
    Dsadc_ConfigPtr = NULL_PTR;
    /*[cover parentID={48C7BDDB-8209-48db-85D5-5F27E7CDE721}]
      Reset the DSADC and trigger source registers [/cover]*/
    Dsadc_lResetSfr(LocalConfigPtr);
    /*[cover parentID={86B98902-6339-4b85-9A75-99D691BF602C}]
      De-Initialize the Global channel data [/cover]*/
    for(ChannelId = 0; ChannelId < DSADC_MAX_CHANNELS_CONFIGURED; \
                                                            ChannelId++)
    {
      /*Set the calibration status to Not Started*/
      Dsadc_ChannelData[ChannelId].CalibrationStatus = \
                                    DSADC_CALIBRATION_NOT_STARTED;
      /*Set the channel status to IDLE*/
      Dsadc_ChannelData[ChannelId].ChannelStatus = DSADC_IDLE;
      /*[cover parentID={D7D582AC-F79D-4910-893F-ACC617E94EE9}]
         Not all the channels using DMA [/cover]*/
      #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
      /*Initialize the Number of Valid Result*/
      Dsadc_ChannelData[ChannelId].NumofValidConRes = (uint16)0U;
      /* Set no error for the FIFO Error status*/
      Dsadc_ChannelData[ChannelId].FifoErrorStatus = DSADC_NO_FIFO_ERROR;
      /*Reset the Buffer full status*/
      Dsadc_ChannelData[ChannelId].BufferFull = (uint8)0U;
      /*Initialize the circular buffer Read Pointer*/
      Dsadc_ChannelData[ChannelId].ReadPtrCircularBuf = (uint16)0U;
      /*Initialize the circular buffer Write Pointer*/
      Dsadc_ChannelData[ChannelId].WritePtrCircularBuf = (uint16)0U;
      #endif
    }
    /* Reset Dsadc Channel Notification status for all Channel */
    Dsadc_ChanNotifstatus = (uint32)0U;
    /*[cover parentID={4DD52896-AE34-464a-B59C-7321C30588F6}]
    Disable DSADC module clock and reset Sleep mode configuration [/cover]*/
    DSADC_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&MODULE_EDSADC.CLC.U,\
              ((uint32)DSADC_RESET_CLC_REG));
    /*[cover parentID={7FAFB1F8-B517-427f-85E6-AC476D96E940}]
     Check If the EDSADC module clock is disabled [/cover]*/
     if(Mcal_GetBitAtomic(MODULE_EDSADC.CLC.U,IFX_EDSADC_CLC_DISS_OFF, \
                         IFX_EDSADC_CLC_DISS_LEN) == DSADC_MODULE_CLK_DISABLE)
    {
    /*[cover parentID={28C01A0D-43B2-4e9e-A8BC-0B7175A365DC}]
        DEM Notify is ON for CLC [/cover]*/
      #if (DSADC_CLC_FAILURE_DEM_NOTIF == DSADC_ENABLE_DEM_REPORT)
      /*[cover parentID={11F464F8-568D-4443-8954-CD8DE4794FBE}]
        Raise DEM Pass, when CLC Disabling is successful [/cover]*/
      Dem_ReportErrorStatus(DSADC_E_CLC_FAILURE, DEM_EVENT_STATUS_PASSED);
      #endif
    }
    else
    {
    /*[cover parentID={DBB1F5BF-E4D0-46a3-9A4C-093321A93FAD}]
      DEM Notify is ON for CLC [/cover]*/
      #if (DSADC_CLC_FAILURE_DEM_NOTIF == DSADC_ENABLE_DEM_REPORT)
      /*[cover parentID={38BF4EBD-FC5C-4074-BCF5-F9BF0AE37231}]
        Raise DEM failure, when CLC enabling is fails [/cover]*/
      Dem_ReportErrorStatus(DSADC_E_CLC_FAILURE, DEM_EVENT_STATUS_FAILED);
      #endif
    }
    /*[cover parentID={A86D4BDA-548F-498d-ACF6-F37B285A576A}]
      DET or SAFETY or Initcheck API is ON [/cover]*/
    #if ((DSADC_DEV_ERROR_DETECT == STD_ON) || \
       (DSADC_SAFETY_ENABLE == STD_ON) || (DSADC_INITCHECK_API == STD_ON))
    /*[cover parentID={345E761A-71D8-4974-B3FB-E6CA63643925}]
      set the driver state to DeInit Completed state [/cover]*/
    Dsadc_InitStatus = DSADC_UNINIT_COMPLETED;
    #endif
  }
}
#endif /* End for DSADC_DEINIT_API */
/* [cover parentID={BA2883BE-E25F-42a9-8AD5-C4EAB9D40613}]
   Interrupt Control Registers.
   [/cover] */
/*******************************************************************************
** Traceability     : [cover parentID={A07BA2EC-4ED4-43b3-B2E3-EC3BF5A817CB}, **
**                                    {A0233A9C-8854-4495-BCAD-3496F60137C7}] **
**                                                                            **
** Syntax           : Std_ReturnType Dsadc_StartModulation                    **
**                    (const Dsadc_ChannelType ChannelId)                     **
**                                                                            **
** Description      : This API Enables the Result data acquisition for the    **
**                    given channel and enables the Trigger source if it is   **
**                    configured. It sets the Channel status to DSADC_BUSY.   **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric Id of  the requested DSADC Channel  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK : DSADC channel Result data acquisition is         **
**                           enabled                                          **
**                    E_NOT_OK: DSADC channel Result data acquisition is      **
**                              not enabled                                   **
*******************************************************************************/
Std_ReturnType Dsadc_StartModulation (const Dsadc_ChannelType ChannelId)
{
  uint32 LocalFcfgmValue;
  Std_ReturnType RetVal;
  uint8 HwChannelNum;

  /*[cover parentID={D57FF600-A9DA-4860-85F2-71AA2C837B0D}]
  DET is ON or SAFETY is ON [/cover]*/
  #if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;
  /*Initialize the return value as E_NOT_OK*/
  RetVal= E_NOT_OK;
  /*check DET for the API*/
  lDetVal = Dsadc_lStartModDetCheck(ChannelId);
  /*[cover parentID={66BAA50D-CE31-4d84-9F6E-D60265D66315}]
    Check if there is no error [/cover]*/
  if(lDetVal == DSADC_E_NO_ERR)
  #endif
  {
    /*[cover parentID={FCC8F2E9-55FE-4bc0-8C16-73519F933E9B}]
      Any one of the Channel is using ERU Trigger[/cover]*/
    #if(DSADC_ERUTRIGGER_USED == STD_ON)
    /*[cover parentID={1EC9188C-EED9-4de2-A809-377E2EA9C140}]
      Check if the configured Trigger Source is ERU[/cover]*/
    if(Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].TriggerSource == \
                                                          DSADC_TRIGGER_ERU)
    {
      /*[cover parentID={29843822-C31C-4e3b-B8D7-94829D7A19E8}]
         Configure the ERU OGU channel[/cover]*/
      Dsadc_lEnableEruTrigger \
            (&Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId]);
    }
    #endif
    /*Obtain the DSDAC HW channel assigned to ChannelId */
    HwChannelNum = DSADC_GET_HW_CH_NUM(ChannelId);
    /*[cover parentID={0C58EDE5-CCE6-4b0f-B7A5-64589B58F64C}]
      Get the Interrupt mode to be programed for main service request [/cover]*/
    /* Obtain the local copy of the filter configuration register and also
     * enable the write access for upper 16 bits of the register in the
     * local copy by setting the CSRWC bitfield as 1. The lower 16 bits
     * need not be modified, hence the write access for the lower 16 bits
     * are not enabled */
    LocalFcfgmValue = ((MODULE_EDSADC.CH[HwChannelNum].FCFGM.U) | \
                        (uint32)((uint32)DSADC_CH_FCFGM_CSRWC_ENABLE << \
                                     IFX_EDSADC_CH_FCFGM_CSRWC_OFF));

    /* Reset the current configured value of main service request
     * in the local copy*/
    LocalFcfgmValue &= (~((uint32)IFX_EDSADC_CH_FCFGM_SRGM_MSK << \
                       IFX_EDSADC_CH_FCFGM_SRGM_OFF));

    /* Copy the type of main service request in the local value of
       filter configuration register*/
    LocalFcfgmValue |= ((uint32)Dsadc_ConfigPtr->DsadcChannelConfiguration \
              [ChannelId].ChannelIntMode << IFX_EDSADC_CH_FCFGM_SRGM_OFF);

    /*[cover parentID={3AE93B60-544F-424e-8C7D-06447D9063E2}]
      Critical Section[/cover]*/
    /*[cover parentID={53FA56F6-183E-45f5-8651-D8E080CA073C}]
     Check if the DET is OFF and SAFETY is OFF[/cover]*/
    #if((DSADC_DEV_ERROR_DETECT == STD_OFF) && (DSADC_SAFETY_ENABLE == STD_OFF))
    /*[cover parentID={B2A91BE8-1AA7-47c8-B63E-61F175AF93D1}]
      Start of Critical section [/cover]*/
    SchM_Enter_Dsadc_ChannelData();
    #endif
    /*[cover parentID={BA11FBF8-735D-46ce-B6B8-E8EE38474810}]
      Not all the channels using DMA [/cover]*/
    #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
    /*[cover parentID={072A2961-C018-44c7-8FDF-273A3E411898}]
      Initialize the Number of Valid Result to 0 [/cover]*/
    Dsadc_ChannelData[ChannelId].NumofValidConRes = (uint16)0U;
    /*[cover parentID={828EA25D-ECE5-4331-92E3-FDE6BF6417F7}]
      set the FIFO Error status as No Error[/cover]*/
    Dsadc_ChannelData[ChannelId].FifoErrorStatus = DSADC_NO_FIFO_ERROR;
    /*Reset the Buffer full status*/
    Dsadc_ChannelData[ChannelId].BufferFull = (uint8)0U;
    /*Initialize the circular buffer Read Pointer*/
    Dsadc_ChannelData[ChannelId].ReadPtrCircularBuf = (uint16)0U;
    /*Initialize the circular buffer Write Pointer*/
    Dsadc_ChannelData[ChannelId].WritePtrCircularBuf = (uint16)0U;
    #endif
    /*[cover parentID={04D909F8-DC9D-431d-854E-41D55B4B4F82}]
      Check and clear the DSADC FIFO Error[/cover]*/
    (void)Dsadc_lHwFifoErrorHandling(ChannelId);
     /*[cover parentID={B053A746-47C3-4936-BF8E-D26E5BD5BE0D}]
      Any one of the Channel is using ERU Trigger[/cover]*/
    #if(DSADC_ERUTRIGGER_USED == STD_ON)
    /*[cover parentID={8E22A784-02B9-46b8-B973-79EEAE11CB16}]
      Check if the configured Trigger Source is ERU[/cover]*/
    if(Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].TriggerSource == \
                                                          DSADC_TRIGGER_ERU)
    {
      /*[cover parentID={7BD52DD4-D3BC-494d-B94D-95792A6D720E}]
         Enable the DSADC channel ERU trigger source[/cover]*/
      Dsadc_lEnableEruInterrupt \
            (&Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId]);
    }
    #endif
    /*[cover parentID={D689A9F8-19F0-4da5-9016-2A8C1655BD61}]
      Clear the pending Event [/cover]*/
    MODULE_EDSADC.EVFLAGCLR.U = ((uint32)DSADC_ONE_U<<HwChannelNum);
    /*[cover parentID={1FF53607-4C48-4c16-8F2C-4E5AE7DA72E0},
      {8EE8E4F8-A3C2-4eb8-814E-3321B9B1FFEC}]
      Write the local copy of filter configuration register in
      FCFGM register[/cover]*/
    MODULE_EDSADC.CH[HwChannelNum].FCFGM.U = LocalFcfgmValue;
    /*[cover parentID={C0E3242C-33AF-4fd3-B23C-74DFF79116AB}]
      Set the channel status to Busy [/cover]*/
    Dsadc_ChannelData[ChannelId].ChannelStatus = DSADC_BUSY;
    /*[cover parentID={3B459D7B-16FA-4d7b-86A5-72F4E7FEC609}]
      Check if the DET is OFF and SAFETY is OFF[/cover]*/
    #if((DSADC_DEV_ERROR_DETECT == STD_OFF) && (DSADC_SAFETY_ENABLE == STD_OFF))
    /*[cover parentID={B6E6EF5D-DEBA-4074-93E5-265DFB80F43B}]
      End of Critical section[/cover]*/
    SchM_Exit_Dsadc_ChannelData();
    #endif
    /*set the return value as OK*/
    RetVal = E_OK;
  }
  return(RetVal);
}
/* [cover parentID={BA2883BE-E25F-42a9-8AD5-C4EAB9D40613}]
   Interrupt Control Registers.
   [/cover] */
/*******************************************************************************
** Traceability     : [cover parentID={59D7576A-34D9-49bc-9C5C-F64ADBF9C251}] **
**                                                                            **
** Syntax           : Std_ReturnType Dsadc_StopModulation                     **
**                        (const Dsadc_ChannelType ChannelId)                 **
**                                                                            **
** Description      : This API Disables the Result data acquisition           **
**                    for the given channel and disables the Trigger source   **
**                    if it is configured. It sets the Dsadc Channel status   **
**                    to DSADC_IDLE.                                          **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1D                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric Id of  the requested DSADC Channel  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK : DSADC channel Result data acquisition is         **
**                           stopped                                          **
**                    E_NOT_OK: DSADC channel Result data acquisition is      **
**                              not disabled                                  **
*******************************************************************************/
Std_ReturnType Dsadc_StopModulation (const Dsadc_ChannelType ChannelId)
{
  uint32 LocalFcfgmValue;
  Std_ReturnType RetVal;
  uint8 HwChannelNum;

  /*[cover parentID={5CA11A0A-DE51-4bce-A22E-8E95DC49A52C}]
  DET is ON or SAFETY is ON [/cover]*/
  #if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;
  /*Initialize the return value to NOT OK*/
  RetVal = E_NOT_OK;
  /*check DET for the API*/
  lDetVal = Dsadc_lStopModDetCheck(ChannelId);
  /*[cover parentID={76AF3C6E-2C0C-4e98-A04E-FE728FAE8401}]
    check if there is no error[/cover]*/
  if(lDetVal == DSADC_E_NO_ERR)
  #endif
  {
    /* Obtain the DSDAC HW channel assigned to ChannelId */
    HwChannelNum = DSADC_GET_HW_CH_NUM(ChannelId);
    /*[cover parentID={29B220CE-E9E0-495d-8AB2-1AD616C0E9D1}]
      Any one of the channel is using ERU as a Trigger source[/cover]*/
    #if(DSADC_ERUTRIGGER_USED == STD_ON)
    /*[cover parentID={A1C818B2-EA49-4346-9CE8-E510AE605E8E}]
      Check if the configured Trigger mode is Window[/cover]*/
    if(Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].TriggerSource == \
                                                         DSADC_TRIGGER_ERU)
    {
      /*[cover parentID={ED9DECDD-B2DE-4f55-8FAE-41C62684847E}]
         Disable the DSADC channel ERU trigger source[/cover]*/
      Dsadc_lDisableEruTrigger \
                  (&Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId]);
    }
    #endif

    /*[cover parentID={7C65DDAF-6495-4159-ABCB-14ACD71B06B0}]
      Disable the Main service request[/cover]*/
    /* Obtain the local copy of the filter configuration register and also
     * enable the write access for upper 16 bits of the register in the
     * local copy by setting the CSRWC bitfield as 1. The lower 16 bits
     * need not be modified, hence the write access for the lower 16 bits
     *  are not enabled */
    LocalFcfgmValue = ((MODULE_EDSADC.CH[HwChannelNum].FCFGM.U) | \
                           (uint32)((uint32)DSADC_CH_FCFGM_CSRWC_ENABLE << \
                                        IFX_EDSADC_CH_FCFGM_CSRWC_OFF));

    /* Reset the current configured value of main service request
     * in the local copy*/
    LocalFcfgmValue &= (~((uint32)IFX_EDSADC_CH_FCFGM_SRGM_MSK << \
                       IFX_EDSADC_CH_FCFGM_SRGM_OFF));

    /* Disable the main service request in the local value of
       filter configuration register*/
    LocalFcfgmValue |= \
          ((uint32)DSADC_MAIN_SERVICE_DISABLE << IFX_EDSADC_CH_FCFGM_SRGM_OFF);
    /*Disable the Main service request*/
    MODULE_EDSADC.CH[HwChannelNum].FCFGM.U = LocalFcfgmValue;
    /*[cover parentID={4D9D65DA-4075-4b0f-980D-297241959F20}]
      Set the channel status to Idle [/cover]*/
    Dsadc_ChannelData[ChannelId].ChannelStatus = DSADC_IDLE;
    /*set the return value as OK*/
    RetVal = E_OK;
  }
  return(RetVal);
}
/* [cover parentID={BA2883BE-E25F-42a9-8AD5-C4EAB9D40613}]
   Interrupt Control Registers.
   [/cover] */
#if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={5E7794EE-6704-408a-98DB-DD57A9615E3D}] **
**                                                                            **
** Syntax           : Dsadc_SizeType Dsadc_ReadStreamResults                  **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId,                    **
**                      Dsadc_ResultType * const ResultLinearBufferPtr        **
**                    )                                                       **
**                                                                            **
** Description      : This API reads the conversion results stored in         **
**                    the linear buffer. If the ResultLinearBufferPtr is not  **
**                    the channel Buffer what was configured in the           **
**                    Dsadc_SetupResultBuffer API call, then this API copies  **
**                    the conversion results from channel buffer to the       **
**                    ResultLinearBufferPtr.This API returns the number of    **
**                    valid conversion results. The starting location of the  **
**                    conversion results are always 0 in the buffer.          **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1E                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric Id of  the requested DSADC Channel  **
**                                                                            **
** Parameters(in-out) : ResultLinearBufferPtr -> Location to store the        **
**                                 requested channel Result buffer            **
** Return value     : Dsadc_SizeType -> Number of valid conversion result in  **
**                                      the channel buffer                    **
**                    65535 -> Read Stream Result Failed                      **
**                    0 -> No Failure in the ReadStream Result, but no data   **
**                         available for read                                 **
*******************************************************************************/
Dsadc_SizeType Dsadc_ReadStreamResults(const Dsadc_ChannelType ChannelId,\
                               Dsadc_ResultType  * const ResultLinearBufferPtr)
{
  Dsadc_SizeType Size = DSADC_READSTREAM_ERROR;
  Dsadc_SizeType BufferCount;
  uint8 FifoErrorStatus;

  /*[cover parentID={6360E858-BAD5-4a36-92DC-EDFC1011FF41}]
  DET is ON or SAFETY is ON [/cover]*/
  #if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;
  /*check DET for the API*/
  lDetVal = Dsadc_lReadStreamResDetCheck(ChannelId,ResultLinearBufferPtr);
  /*[cover parentID={5D989019-7498-4ff5-A86E-5F0EA5BDF1DC}]
    check if there is no error[/cover]*/
  if(lDetVal == DSADC_E_NO_ERR)
  #endif
  {
    /*[cover parentID={9EC52DCC-672E-4b13-BC5A-1F1CD023B2BE}]
      check if the Channel configured for Access mode Linear Buffer [/cover]*/
    if(Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].AccessMode \
                                                 == DSADC_STREAM_LINEAR_BUFFER)
    {
      /*[cover parentID={6011D99B-D9A2-4155-83E3-116A3F0A3CF6}]
        check if the Result is Ready [/cover]*/
      if(Dsadc_ChannelData[ChannelId].ChannelStatus == DSADC_RESULT_READY)
      {
      /*[cover parentID={508BBC01-5DBE-481b-AA9C-C161215ECB5F}]
          Critical section [/cover]*/
        /*[cover parentID={B3C2ADD2-EF3C-46c1-997C-FE24849760FF}]
        Start of Critical section [/cover]*/
        SchM_Enter_Dsadc_ChannelData();
        /*Copy the Number of valid Entries */
        Size = Dsadc_ChannelData[ChannelId].NumofValidConRes;
        /*Reset the Number of valid Entries*/
        Dsadc_ChannelData[ChannelId].NumofValidConRes = (Dsadc_SizeType)0;
        /*[cover parentID={BB2631B0-1402-462b-AD71-5F2082F32E44}]
          Set the DSADC Driver state to Busy [/cover]*/
        Dsadc_ChannelData[ChannelId].ChannelStatus = DSADC_BUSY;
        /*Reset the Buffer full status*/
        Dsadc_ChannelData[ChannelId].BufferFull = (uint8)0U;
        /*[cover parentID={855B132C-3572-47f8-BC6F-090157B7429B}]
          Check if the Result buffer is same as the channel buffer[/cover]*/
        if(ResultLinearBufferPtr != Dsadc_ChannelData[ChannelId].ChannelResBuffer)
        {
          /* Copy the Conversion result from Channel buffer to Result buffer */
          for(BufferCount = 0; BufferCount < Size; BufferCount++)
          {
            /*Copy the conversion results of channel buffer to the
              Result buffer*/
            ResultLinearBufferPtr[BufferCount] =
                  (Dsadc_ChannelData[ChannelId].ChannelResBuffer[BufferCount]);
          }
        }
        /*copy the FIFO Error status to the local variable */
        FifoErrorStatus = Dsadc_ChannelData[ChannelId].FifoErrorStatus;
        /*[cover parentID={37A63BE8-B70C-45f5-BCF7-77C4F7B69321}]
          End of Critical section [/cover]*/
        SchM_Exit_Dsadc_ChannelData();
        /*[cover parentID={8DE2B78E-EAD7-49c3-BF0D-3443CE484B96}]
          Check if the HW FIFO error is present[/cover]*/
        if(FifoErrorStatus == DSADC_FIFO_ERROR)
        {
          /* Update the size of the Buffer valid entries as 65535 */
          Size = DSADC_READSTREAM_ERROR;
          /*[cover parentID={513F8CA9-6D62-4e6f-B8CA-DF556AED5005}]
            DEM Notify is ON for HW FIFO [/cover]*/
          #if (DSADC_FIFO_FAILURE_DEM_NOTIF == DSADC_ENABLE_DEM_REPORT)
          /*[cover parentID={C1A10B06-BE48-403b-B21B-40161404B814}]
            Raise DEM Fail, when FIFO Error is present [/cover]*/
          Dem_ReportErrorStatus(DSADC_E_FIFO_FAILURE, DEM_EVENT_STATUS_FAILED);
          #endif
        }
        else
        {
          #if (DSADC_FIFO_FAILURE_DEM_NOTIF == DSADC_ENABLE_DEM_REPORT)
          /*[cover parentID={2553EAA9-9F58-422d-B11C-158A4AB7AFA1}]
            Raise DEM Pass, when FIFO Error not present [/cover]*/
          Dem_ReportErrorStatus(DSADC_E_FIFO_FAILURE, DEM_EVENT_STATUS_PASSED);
          #endif
        }
      }
      else
      {
        /*[cover parentID={35380768-2240-47c9-A86F-7AEDA6E31DF7}]
        Update the the size of the Buffer valid entries as 0[/cover]*/
        Size = (Dsadc_SizeType)0U;
      }
    }
    /*[cover parentID={D3A29307-8A4A-4766-B19B-09319C3CC6AA}]
      DET is ON or SAFETY is ON [/cover]*/
    #if ((DSADC_DEV_ERROR_DETECT == STD_ON)|| (DSADC_SAFETY_ENABLE == STD_ON))
    else
    {
      /*[cover parentID={7E43F904-28DD-4701-9D47-E38C52DD879A}]
        Raise DET failure, since the Configured buffer is not Linear buffer 
       [/cover]*/
      Dsadc_lReportError(DSADC_SID_READ_STREAM_RESULTS,\
                                        DSADC_E_INV_LINEAR_BUFFER_CONFIG);
    }
    #endif
  }
  /*[cover parentID={83E9DCB7-A132-428e-8251-A318987177DA}]
  Return the number of valid Results on the buffer [/cover]*/
  return(Size);
}
#endif

#if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={6CA2D92D-260A-4120-A07C-F31D3AD5D3E9}] **
**                                                                            **
** Syntax           : Std_ReturnType Dsadc_ReadResult                         **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId,                    **
**                      Dsadc_ResultType * const ResultPtr                    **
**                    )                                                       **
**                                                                            **
** Description      : This API read the Result data for given DSADC channel.  **
**                    If the Access mode is single then this API read the     **
**                    DSADC Hardware result Register to update ResultPtr.     **
**                    If the Access mode is configured as Circular buffer     **
**                    then this API update the ResultPtr with the circular    **
**                    Buffer data.                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1F                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric Id of  the requested DSADC Channel  **
**                                                                            **
** Parameters (out) : Access mode single: ResultPtr-> Result from the DSADC   **
**                                                  Hardware result register  **
**                    Access mode circular Buffer : ResultPtr -> Result from  **
**                      the Circular buffer current read Pointer location.    **
**                                                                            **
** Return value     : E_OK : Requested DSADC channel result is read           **
**                    E_NOT_OK: Failed to read the requested DSADC channel    **
**                              result                                        **
*******************************************************************************/
Std_ReturnType Dsadc_ReadResult(const Dsadc_ChannelType ChannelId,\
                                           Dsadc_ResultType  * const ResultPtr)
{
  uint32 Result;
  uint16 ResultData;
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 HwChannelId;
  uint8 FifoErrorStatus;

  /*[cover parentID={E8841164-8301-49fa-8E82-C8998D4BB29E}]
    DET is ON or SAFETY is ON [/cover]*/
  #if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;

  /*check DET for the API*/
  lDetVal = Dsadc_lReadResultDetCheck(ChannelId,ResultPtr);
  /*[cover parentID={A5DD804E-6900-4bab-8DD4-5B5AF65AD43F}]
    check if there is no error[/cover]*/
  if(lDetVal ==DSADC_E_NO_ERR)
  #endif
  {
    /*[cover parentID={90914BA4-0EEC-4b0a-AB42-67F4CE9F596D}]
      Check if the Access mode is not configured as Linear Buffer
      and not configured for DMA Access[/cover]*/
    if ((Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].AccessMode \
                                             != DSADC_STREAM_LINEAR_BUFFER) &&
          (Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].AccessMode
                                    != DSADC_DMA_ACCESS))
    {
      /*[cover parentID={E864D219-F886-4ae2-B42E-5F470D47C762}]
        Check the Channel status is DSADC_RESULT_READY [/cover]*/
      if(Dsadc_ChannelData[ChannelId].ChannelStatus == DSADC_RESULT_READY)
      {
        /*[cover parentID={EEC1A5B0-12AD-40a8-A8C1-2537993D8FC6}]
          Check if the Access mode is configured as Single Access Mode 
          [/cover]*/
        if(Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].AccessMode \
                                                        == DSADC_SINGLE_READ)
        {
          /*Get the Hardware ID from the Logical Channel ID*/
          HwChannelId = DSADC_GET_HW_CH_NUM(ChannelId);
          /*[cover parentID={AAC64BA6-C246-445a-8489-D08CACFFB09D}]
            Critical Section [/cover]*/
          /*[cover parentID={896AB91F-C7F0-4b7a-A513-8ADCD0E39866}]
            Start of Critical section [/cover]*/
          SchM_Enter_Dsadc_ChannelData();
          /*Copy the Result register content to the Local variable*/
          Result = MODULE_EDSADC.CH[HwChannelId].RESM.U;
          /*[cover parentID={7432B594-813C-447c-85CF-66865EBC38E5}]
            Set the Channel Status to Busy [/cover]*/
          Dsadc_ChannelData[ChannelId].ChannelStatus = DSADC_BUSY;
          /*Check for DSADC FIFO Error*/
          FifoErrorStatus = Dsadc_lHwFifoErrorHandling(ChannelId);
          /*[cover parentID={F1C93319-86E8-484f-ABF7-64E763DA913A}]
            End of Critical section [/cover]*/
          SchM_Exit_Dsadc_ChannelData();
          /*[cover parentID={5B7AC33D-A225-4e27-8EAE-82793B1A3F9B}]
            check if there is HW FIFO Error[/cover]*/
          if(FifoErrorStatus == DSADC_FIFO_ERROR)
          {
            /*[cover parentID={4C7A1D2F-5F37-4496-BE38-17C4E0428A12}]
              DEM Notify is ON for HW FIFO[/cover]*/
            #if (DSADC_FIFO_FAILURE_DEM_NOTIF == DSADC_ENABLE_DEM_REPORT)
            /*[cover parentID={C89EE10B-9209-407c-9185-E9C58E484AD5}]
              Raise DEM Pass, when FIFO Error not present [/cover]*/
            Dem_ReportErrorStatus(DSADC_E_FIFO_FAILURE,DEM_EVENT_STATUS_FAILED);
            #endif
          }
          else
          {
            /*[cover parentID={50F4DE8B-E691-4b6b-8081-DDCCA8C3A108}]
              Set the Return value as E_OK [/cover]*/
            RetVal = E_OK;
            #if (DSADC_FIFO_FAILURE_DEM_NOTIF == DSADC_ENABLE_DEM_REPORT)
            /*[cover parentID={105C5C33-0BD9-42cc-BC89-55AC8A2E60BA}]
              Raise DEM Fail, when FIFO Error is present [/cover]*/
            Dem_ReportErrorStatus(DSADC_E_FIFO_FAILURE,DEM_EVENT_STATUS_PASSED);
            #endif
          }
          /*Extract the Result value and store it to the the memory
            location pointed by the result pointer*/
          ResultData = ((uint16)Result\
                              &(uint16)IFX_EDSADC_CH_RESM_RESULTLO_MSK);

          *ResultPtr = (Dsadc_ResultType)ResultData;
          
          /*[cover parentID={000B88D9-D42B-421e-B2EE-EDFE24BEF00E}]
            check if the timestamp is enabled and the Trigger mode is Normal 
            [/cover]*/
          if((Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].\
                               TimestampMode == DSADC_TIMESTAMP_ENABLED) &&
             (Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].\
                               TriggerMode == DSADC_TRIGGER_MODE_NORMAL))
          {
            /*Extract the Timestamp information and store it to the Global
              variable*/
            Dsadc_ChannelData[ChannelId].TimestampCount = (Dsadc_TimeStampType)\
                           ((Result >> IFX_EDSADC_CH_RESM_RESULTHI_LEN) & \
                                      (IFX_EDSADC_CH_RESM_RESULTHI_MSK));
          }
        }
        /*[cover parentID={C20E997E-E240-4836-B714-681FC8DC808D}]
          Not all the channel is configured for DMA Access [/cover]*/
        #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
        else
        {
          /*[cover parentID={9C5DCB19-03B7-4832-909B-F8A62C7070D2}]
            Critical section [/cover]*/
          /*[cover parentID={42CCC992-7BBC-442a-BE2B-D95792E2C72F}]
            Start of Critical section [/cover]*/
          SchM_Enter_Dsadc_ChannelData();
          /*[cover parentID={9A3F705B-ECC7-4b83-A46D-9C4FBDD66DD9}]
            Copy the data from the Circular Result buffer to the Memory
            location pointed by result Pointer[/cover]*/
          *ResultPtr = (Dsadc_ResultType)Dsadc_ChannelData[ChannelId].\
                        ChannelResBuffer[Dsadc_ChannelData[ChannelId].\
                                         ReadPtrCircularBuf];
          /*Increment the Read Pointer and reset to zero
            in case of overflows*/
          Dsadc_ChannelData[ChannelId].ReadPtrCircularBuf =\
                        (((Dsadc_ChannelData[ChannelId].ReadPtrCircularBuf)+\
                        (Dsadc_SizeType)DSADC_ONE_U)\
                        %(Dsadc_ChannelData[ChannelId].ChannelBufferSize));
          /*[cover parentID={A659D1C8-889E-4250-B5C9-D46D79C410C8}]
            check if the Buffer is Empty [/cover]*/
          if(Dsadc_ChannelData[ChannelId].ReadPtrCircularBuf ==       \
                              Dsadc_ChannelData[ChannelId].WritePtrCircularBuf)
          {
            /*[cover parentID={1EBAE553-A255-4d12-9C70-CD1F98D4BFE7}]
              Set the Status to DSADC_BUSY [/cover]*/
            Dsadc_ChannelData[ChannelId].ChannelStatus = DSADC_BUSY;
          }
          /*[cover parentID={F242CE0F-8B8A-435a-867A-38F880D2C399}]
            End of Critical section [/cover]*/
          SchM_Exit_Dsadc_ChannelData();
          /*[cover parentID={CE70785A-F2A5-455e-90B6-4BD54E0D53DD}]
            Set the Return value as E_OK [/cover]*/
          RetVal = E_OK;
        }
        #endif
      }
      else
      {
        /*[cover parentID={9C4479A0-12C5-472e-BAC8-F9A024A95785}]
          set the value as 0 to Memory location pointer by result pointer 
      [/cover]*/
        *ResultPtr = (Dsadc_ResultType)0;
      }
    }
    /*[cover parentID={C732D87B-53DB-403b-8DE4-A97ADF3ACB1B}]
      DET is ON or SAFETY is ON [/cover]*/
    #if ((DSADC_DEV_ERROR_DETECT == STD_ON)|| (DSADC_SAFETY_ENABLE == STD_ON))
    else
    {
      /*[cover parentID={15117CD8-EB38-49d9-AD40-314A5292326F}]
      Raise DET failure, since the Access mode is configured as
      Linear Buffer which is not allowed in ReadResult API [/cover]*/
      Dsadc_lReportError(DSADC_SID_READ_RESULT,\
                                        DSADC_E_INV_CIRCULAR_BUFFER_CONFIG);
    }
    #endif
  }
  return(RetVal);
}
#endif
/*******************************************************************************
** Traceability     : [cover parentID={EFA5827F-7B51-40f1-9EF3-F10FBD6F34BB}] **
**                                                                            **
** Syntax           : Dsadc_ChannelstatusType Dsadc_GetStatus                 **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId                     **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used to return the current status     **
**                    of the given DSADC channel.                             **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x20                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric Id of  the requested DSADC Channel  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : current status of the DSADC Channel                     **
**                    DSADC_IDLE -> DSADC Channel is in Idle State            **
**                    DSADC_BUSY -> DSADC Channel is doing conversion         **
**                    DSADC_RESULT_READY -> result is available to read       **
*******************************************************************************/
Dsadc_ChannelstatusType Dsadc_GetStatus(const Dsadc_ChannelType ChannelId)
{
  Dsadc_ChannelstatusType RetVal;

  /*[cover parentID={3B6ED634-3CE2-4c0c-8EBE-E1C551CF23CA}]
  DET is ON or SAFETY is ON [/cover]*/
  #if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;
  /*Initialize the return value to DSADC_IDLE*/
  RetVal = DSADC_IDLE;
  /*check DET for the API*/
  lDetVal = Dsadc_lGetStatusDetCheck(ChannelId);
  /*[cover parentID={31789581-9F6E-47be-8F6D-980607F09B0D}]
    check if there is no error[/cover]*/
  if(lDetVal == DSADC_E_NO_ERR)
  #endif
  {
    /*[cover parentID={82399DC5-ECF1-4297-9BB2-0108B1A01E39}]
      Read the current status for the given channel [/cover]*/
    RetVal =  Dsadc_ChannelData[ChannelId].ChannelStatus;
  }
  return(RetVal);
}

#if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={C0BBD666-15C9-4253-B107-32DEB9428DFE}] **
**                                                                            **
** Syntax           : Std_ReturnType Dsadc_SetupResultBuffer                  **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId,                    **
**                      const Dsadc_ResultType  * const DataBufferPtr,        **
**                      const Dsadc_SizeType Size                             **
**                    )                                                       **
**                                                                            **
** Description      : This API sets up the start address of Channel specific  **
**                    result buffers, where the conversion results will be    **
**                    stored.This API setup the buffer only if the Access mode**
**                    is configured as Linear Buffer or Circular Buffer.      **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x21                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC channel       **
**                    DataBufferPtr - Pointer to the start of result          **
**                                    data buffer which is channel buffer     **
**                    Size - Result Buffer size which defines the number of   **
**                           result can store in the result buffer. Maximum   **
**                           size of the buffer shall be 65534.               **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK : Result buffer(Channel Buffer)initialization      **
**                           is successful                                    **
**                    E_NOT_OK: Result buffer Initialization failed           **
**                                                                            **
*******************************************************************************/
Std_ReturnType Dsadc_SetupResultBuffer(const Dsadc_ChannelType ChannelId, \
      const Dsadc_ResultType * const DataBufferPtr,  const Dsadc_SizeType Size)
{

  Std_ReturnType RetVal = E_NOT_OK;

  /*[cover parentID={8CA58719-2641-46c5-B1D7-1C84328D7F2D}]
  DET is ON or SAFETY is ON [/cover]*/
  #if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))

  uint8 lDetVal;

  /* Check DET's for the API */
  lDetVal = Dsadc_lSetupResBufDetCheck(ChannelId,DataBufferPtr);

  /*[cover parentID={47829E13-A37A-4954-B631-4BCDFF88D5D3}]
    Check if there is no Error[/cover]*/
  if(lDetVal == DSADC_E_NO_ERR)
  #endif /* End for DSADC_DEV_ERROR_DETECT*/
  {
    /*[cover parentID={C951887A-4F5A-4f6a-AAA1-F8B28C8D42FC}]
      check if the Channel status is Idle [/cover]*/
    if(Dsadc_ChannelData[ChannelId].ChannelStatus == DSADC_IDLE)
    {
      /*[cover parentID={ED05ABB1-B2DA-440f-9990-F52515612C90}]
        Check if the Access mode is not configured as Single and not
        configured as DMA Access [/cover]*/
      if((Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].AccessMode!= \
                                                       DSADC_SINGLE_READ) &&
         (Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].AccessMode!= \
                                                       DSADC_DMA_ACCESS))
      {
        /*[cover parentID={6E39E58F-575C-41c9-BFF0-E2933A85156D}]
        Check if the size of the buffer requested is not zero and not
        more than max length[/cover]*/
        if((Size != (Dsadc_SizeType)0U) && (Size <=  \
                                      (Dsadc_SizeType)DSADC_MAX_BUFFER_LENGTH))
        {
          /*MISRA2012_RULE_11_8_JUSTIFICATION: The address of the buffer pointer
            is received as a const, so that it cannot be modified in the APIs
            context.The address is stored to a pointer variable, and the pointer
            is later used in the ISR to update the results to the intial buffer
            address passed.Hence, the pointer variable cannot be made as a
            pointer to a const and the type cast is required*/
          /*Assign the address of the DatabufferPtr passed to the 
            Channel buffer*/
          Dsadc_ChannelData[ChannelId].ChannelResBuffer = \
                                         (Dsadc_ResultType *)DataBufferPtr;
          /* set the size of the channel buffer*/
          Dsadc_ChannelData[ChannelId].ChannelBufferSize = Size;
          /* Initialize the number of valid result data to zero*/
          Dsadc_ChannelData[ChannelId].NumofValidConRes = 0x0U;

          /* Return value as E_OK */
          RetVal = E_OK;
        }
        /*[cover parentID={F5AFC2BA-2052-4f71-A9C1-E263A2625787}]
          DET or SAFETY is Enable[/cover]*/
        #if((DSADC_DEV_ERROR_DETECT == STD_ON)||(DSADC_SAFETY_ENABLE == STD_ON))
        else
        {
         /*[cover parentID={E86FA99F-87F9-4265-8108-555B18A9756A}]
          Raise DET failure, since the buffer size is not valid [/cover] */
          Dsadc_lReportError(DSADC_SID_SETUP_RESULT_BUFFER,\
                                                   DSADC_E_INV_BUFFER_SIZE);
        }
        #endif
      }
      #if((DSADC_DEV_ERROR_DETECT == STD_ON)||(DSADC_SAFETY_ENABLE == STD_ON))
      else
      {
        /*[cover parentID={F52C2C06-1D0C-40d8-8487-E4700F88AB64}]
          Raise DET failure, since the Access Mode is configured as 
          Single Access [/cover]*/
        Dsadc_lReportError(DSADC_SID_SETUP_RESULT_BUFFER,\
                                            DSADC_E_INVALID_BUFFER_CONFIG);
      }
      #endif
    }
    /*[cover parentID={F5AFC2BA-2052-4f71-A9C1-E263A2625787}]
      DET is ON or SAFETY is ON[/cover]*/
    #if ((DSADC_DEV_ERROR_DETECT == STD_ON)|| (DSADC_SAFETY_ENABLE == STD_ON))
    else
    {
      /*[cover parentID={28FFCF3E-FFE9-4cc4-B0C4-D7D8CA40B064}]
        Raise DET failure, since the Channel status is not IDLE [/cover]*/
      Dsadc_lReportError(DSADC_SID_SETUP_RESULT_BUFFER,DSADC_E_UNIDLE);
    }
    #endif
  }
  return(RetVal);
}
#endif

/*******************************************************************************
** Traceability     : [cover parentID={AF5F8C25-ECD4-4ac0-8E45-9A29AD82E7CB}] **
**                                                                            **
** Syntax           : Std_ReturnType Dsadc_StartCarrierSignal(void)           **
**                                                                            **
** Description      : This API is used to start the generation of the carrier **
**                    signal from the carrier generator based on the          **
**                    configured waveform properties for exciting the Resolver**
**                    coils.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x22                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK : The Carrier Generator is Started                 **
**                    E_NOT_OK: The Carrier Generator is not Started          **
*******************************************************************************/
Std_ReturnType Dsadc_StartCarrierSignal(void)
{
  Std_ReturnType RetVal = E_NOT_OK;

  /*[cover parentID={9D1FEBFE-C937-4165-BF92-84ADB97E84C3}]
  DET is ON or SAFETY is ON [/cover]*/
  #if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;

  /*check DET for the API*/
  lDetVal = Dsadc_lStartCarrSigDetCheck();
  /*[cover parentID={B38FD3BC-9C2F-4e5a-AC24-7C55F3CA09CE}]
    check if there is no error[/cover]*/
  if(lDetVal == DSADC_E_NO_ERR)
  #endif
  {
    /*[cover parentID={E2FE2D62-F6F1-4aae-86FE-9BEAA6D53201}]
    check if the carrier signal waveform is stopped[/cover]*/
    if(Mcal_GetBitAtomic(MODULE_EDSADC.CGCFG.U, \
                         IFX_EDSADC_CGCFG_CGMOD_OFF, \
                         IFX_EDSADC_CGCFG_CGMOD_LEN) == \
                         DSADC_CARR_SIG_STOPPED)
    {
      /* [cover parentID={F4A483A9-9FDC-405a-B0AE-FCA61E0E9FA1}]
       Set the waveform from the configuration pointer[/cover]*/
      Mcal_SetBitAtomic(&MODULE_EDSADC.CGCFG.U , \
                        IFX_EDSADC_CGCFG_CGMOD_OFF, \
                        DSADC_CGCFG_CGMOD_LEN, \
                        Dsadc_ConfigPtr->CGWaveform);
      /*set the Return value to E_OK*/
      RetVal = E_OK;
    }
  }
  return(RetVal);
}

/*******************************************************************************
** Traceability     : [cover parentID={4184A4A0-2D3A-4b2f-9E28-BDD291A026ED}] **
**                                                                            **
** Syntax           : Std_ReturnType Dsadc_StopCarrierSignal (void)           **
**                                                                            **
** Description      : The interface is used to stop the generation of carrier **
**                    signal from the carrier generator                       **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x23                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK : The Carrier Generator is stopped                 **
**                    E_NOT_OK: The Carrier Generator is not stopped          **
*******************************************************************************/
Std_ReturnType Dsadc_StopCarrierSignal(void)
{
  Std_ReturnType RetVal;

  /*[cover parentID={6ADC65B2-E4E1-43d4-9763-0ED30CD5C156}]
  DET is ON or SAFETY is ON [/cover]*/
  #if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;
  /*set the Return value as NOT OK*/
  RetVal = E_NOT_OK;
  /*check DET for the API*/
  lDetVal = Dsadc_lStopCarrSigDetCheck();
  /*[cover parentID={7B04080B-B10B-4e92-AE38-260991324D0C}]
    check if there is no Error[/cover]*/
  if(lDetVal == DSADC_E_NO_ERR)
  #endif
  {
    /* [cover parentID={69C051B5-E61E-44d9-B1B1-CFCD4274A507}]
     Stop the waveform from the Carrier generator [/cover]*/
    Mcal_SetBitAtomic(&MODULE_EDSADC.CGCFG.U , \
                     IFX_EDSADC_CGCFG_CGMOD_OFF, \
                     DSADC_CGCFG_CGMOD_LEN, \
                     DSADC_CARR_SIG_STOPPED);
    /*set the return value as OK */
    RetVal = E_OK;
  }
  return RetVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={1AA33028-E855-4ecc-A038-3BE920FAA954}] **
**                                                                            **
** Syntax           : void Dsadc_EnableNotification                           **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId                     **
**                    )                                                       **
**                                                                            **
** Description      : This API enables the notification mechanism for the     **
**                    requested DSADC Channel.                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x24                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant for other     **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC Channel       **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Dsadc_EnableNotifications(const Dsadc_ChannelType ChannelId)
{
  
  /*[cover parentID={FCD12BF8-3EDF-4144-9662-80E68C29CD07}]
  DET is ON or SAFETY is ON [/cover]*/
  #if((DSADC_DEV_ERROR_DETECT == STD_ON)||(DSADC_SAFETY_ENABLE == STD_ON))

  uint8 lDetVal;
  /* Check DET's for the API */
  lDetVal = Dsadc_lEnNotifDetCheck(ChannelId);
  /*[cover parentID={7AD2F270-3441-473e-9BF8-6531FC8B9314}]
    Check if there is no Error[/cover]*/
  if(DSADC_E_NO_ERR == lDetVal)
  #endif
  {
    /* [cover parentID={521FA337-029E-4d63-8B06-1C0CEF2D86B9}]
    Enable the notification capability for the given channel [/cover]*/
    Mcal_SetBitAtomic(&(Dsadc_ChanNotifstatus),(uint8)ChannelId,\
                      DSADC_NOTIFICATION_LEN,DSADC_NOTIFICATION_ENABLE);
  }
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter ChannelId is used via
     Tricore Atomic instruction, hence they are not unreferenced.*/
}

/*******************************************************************************
** Traceability     : [cover parentID={3C46B8FE-BCC4-41d6-83B9-26FA8876C7F8}] **
**                                                                            **
** Syntax           : void Dsadc_DisableNotifications                         **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId                     **
**                    )                                                       **
**                                                                            **
** Description      : This API disables the notification mechanism for the    **
**                    requested DSADC Channel.                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x25                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant for other     **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC Channel       **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Dsadc_DisableNotifications(const Dsadc_ChannelType ChannelId)
{
  
  /*[cover parentID={17637F8B-6460-4e7c-9633-08A8649B6621}]
  DET is ON or SAFETY is ON [/cover]*/
  #if((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))

  uint8 lDetVal;
  /* Check DET's for the API */
  lDetVal = Dsadc_lDisNotifDetCheck(ChannelId);
  /*[cover parentID={61115E9D-A53C-4215-A23E-57D321346145}]
    check if there is no error[/cover]*/
  if(DSADC_E_NO_ERR == lDetVal)
  #endif
  {
    /* [cover parentID={F12D018F-4D71-4b94-B3BB-C75CDCA7A3B5}]
    Disable the notification capability for the given channel [/cover]*/
    Mcal_SetBitAtomic(&(Dsadc_ChanNotifstatus), (uint8)ChannelId,\
                      DSADC_NOTIFICATION_LEN,DSADC_NOTIFICATION_DISABLE);
  }
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter ChannelId is used via
     Tricore Atomic instruction, hence they are not unreferenced.*/
}

/*******************************************************************************
** Traceability     : [cover parentID={28F32E72-205C-455e-8AAE-F04040FDD0E6}] **
**                                                                            **
** Syntax           : Dsadc_TimeStampType Dsadc_GetTimestamp                  **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId                     **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the Timestamp count value for the Read **
**                    Result Event. This timestamp count is the time from the **
**                    HW result event untill the ReadResult API reads the     **
**                    result value from the HW Result register.               **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x26                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant for other     **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC Channel       **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : Timestamp count value                                   **
**                                                                            **
*******************************************************************************/
Dsadc_TimeStampType Dsadc_GetTimestamp(const Dsadc_ChannelType ChannelId)
{

  Dsadc_TimeStampType TimestampCount = 0;

  /*[cover parentID={9DDFAEE8-67A3-419d-B625-F4A1BF269380}]
  DET is ON or SAFETY is ON [/cover]*/
  #if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;

  /*check DET for the API*/
  lDetVal = Dsadc_lGetTimestampDetCheck(ChannelId);
  /*[cover parentID={5B57C21E-9289-4b01-B2E3-CC4CD78EF985}]
    check if there is no error[/cover]*/
  if(lDetVal ==DSADC_E_NO_ERR)
  #endif
  {
    /*[cover parentID={AE7E2D05-3745-476f-8F14-A39EF0D7CB38}]
       Check if the Configuration valid for GetTimestamp API[/cover]*/
    if((Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].AccessMode == \
                                                    DSADC_SINGLE_READ) &&
     (Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].TimestampMode == \
                                                    DSADC_TIMESTAMP_ENABLED) &&
     (Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].TriggerMode == \
                                                    DSADC_TRIGGER_MODE_NORMAL))
    {
      /*[cover parentID={83E80A0B-A177-4bf2-A2C2-65E5C723DF37}]
      copy the TimestampCount stored during the last ReadResult API call
      for the requested channel[/cover]*/
      TimestampCount = Dsadc_ChannelData[ChannelId].TimestampCount;
    }
      /*[cover parentID={8DBD4AAA-CD44-48a3-B4CB-44C34FDEC2F3}]
      DET is ON or SAFETY is ON [/cover]*/
    #if ((DSADC_DEV_ERROR_DETECT == STD_ON)|| (DSADC_SAFETY_ENABLE == STD_ON))
    else
    {
      /*[cover parentID={CBF2AEF3-A2A8-413d-9464-6D23D1ACC241}]
        Raise DET failure, since the configuration is invalid
        for get timestamp API call [/cover]*/
      Dsadc_lReportError(DSADC_SID_GET_TIMESTAMP, \
                                         DSADC_E_SINGLE_ACCESSMODE_TIMESTAMP);
    }
    #endif
  }
  return(TimestampCount);
}

/*******************************************************************************
** Traceability     : [cover parentID={887A2039-AD2D-4bec-A4DD-828C9EB05224}] **
**                                                                            **
** Syntax           : Std_ReturnType  Dsadc_StartCalibration                  **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId                     **
**                    )                                                       **
**                                                                            **
** Description      : This API triggers the calibration algorithm. The        **
**                    calibration algorithm will be triggered only when the   **
**                    current status of the channel is DSADC_IDLE.            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x27                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - DSADC channel ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK: Calibration Algorithm has now started             **
**                    E_NOT_OK: Calibration Algorithm has not been triggered  **
******************************************************************************/
Std_ReturnType Dsadc_StartCalibration(const Dsadc_ChannelType ChannelId)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 HwChannelNum;

  /*[cover parentID={CBB0916E-0FA7-4ec5-AA84-B60F99A37C5F}]
    DET is ON or SAFETY is ON [/cover]*/
  #if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;

  /*check DET for the API*/
  lDetVal = Dsadc_lStartCalibDetCheck(ChannelId);
  /*[cover parentID={1CA37B6D-3685-410a-97A6-53310080C61A}]
    check if there is any Error[/cover]*/
  if(lDetVal == DSADC_E_NO_ERR)
  #endif
  {
    /*[cover parentID={9F674ED4-8002-4565-AFB6-4E98E8C637DE}]
      Check if the channel status is IDLE [/cover]*/
    if(Dsadc_ChannelData[ChannelId].ChannelStatus == DSADC_IDLE)
    {
      /* Obtain the DSDAC HW channel assigned to ChannelId */
      HwChannelNum = DSADC_GET_HW_CH_NUM(ChannelId);
      /*[cover parentID={49B5F6FE-E474-4cd9-93F3-77E9952C778F},
        {8EE8E4F8-A3C2-4eb8-814E-3321B9B1FFEC}]
        Start the calibration algorithm [/cover]*/
      Mcal_SetBitAtomic(&MODULE_EDSADC.CH[HwChannelNum].FCFGM.U, \
                         IFX_EDSADC_CH_FCFGM_CALIB_OFF, \
                         DSADC_CH_FCFGM_CALIB_CSRWC_LEN, \
                         DSADC_START_CALIB_ALGO);
      /*set the calibration status to Running*/
      Dsadc_ChannelData[ChannelId].CalibrationStatus = \
                                          DSADC_CALIBRATION_RUNNING;
      /*set the return value as OK*/
      RetVal = E_OK;
    }
      /*[cover parentID={6774FAE9-398F-45fe-81D3-2E4B0D60E44F}]
      DET is ON or SAFETY is ON [/cover]*/
    #if((DSADC_DEV_ERROR_DETECT == STD_ON)||(DSADC_SAFETY_ENABLE == STD_ON))
    else
    {
      /*[cover parentID={19D78090-BFB4-4f24-9F9A-5F4E51309B7D}]
        Raise DET failure, since the channel status is not IDLE [/cover]*/
      Dsadc_lReportError(DSADC_SID_START_CALIBRATION,DSADC_E_UNIDLE);
    }
    #endif
  }
  /* MISRA2012_RULE_2_2_JUSTIFICATION: The variable HwChannelNum is used in the
     Tricore Atomic instructions,which is not detected by MISRA. Hence,
     this variable is not unused*/
  return(RetVal);
}

/*******************************************************************************
** Traceability     : [cover parentID={B53F5AC2-8996-4d20-BFF9-38126A754E9F}] **
**                                                                            **
** Syntax           : Dsadc_CalibrationStatusType Dsadc_GetCalibrationStatus  **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId                     **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used to get the current status of the **
**                    calibration algorithm for the given input channel.when  **
**                    the Calibration status is DSADC_CALIBRATION_DONE then   **
**                    the status will change to DSADC_CALIBRATION_NOT_STARTED.**
**                    So that when this function is called next time          **
**                    DSADC_CALIBRATION_NOT_STARTED is returned               **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x28                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - DSADC channel ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Calibration status for the requested channel            **
**                    DSADC_CALIBRATION_NOT_STARTED ->Calibration algorithm   **
**                                                    not started             **
**                    DSADC_CALIBRATION_RUNNING -> calibration algorithm is   **
**                                                 currently running          **
**                    DSADC_CALIBRATION_DONE -> Calibration algorithm   is    **
**                                              finished and it is success    **
**                    DSADC_CALIBRATION_ERROR -> calibration algorithm is     **
**                                               finished and it is Failed    **
*******************************************************************************/
Dsadc_CalibrationStatusType Dsadc_GetCalibrationStatus(\
                                             const Dsadc_ChannelType ChannelId)
{
  Dsadc_CalibrationStatusType RetVal;
  uint8 HwChannelNum;
  uint8 CalibStatus;

  /*[cover parentID={0BD5E77E-8D99-4218-8851-3FB6861BEF7C}]
  DET is ON or SAFETY is ON [/cover]*/
  #if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;
  /*set the calibration status as Not Started*/
  RetVal = DSADC_CALIBRATION_NOT_STARTED;
  /*check DET for the API*/
  lDetVal = Dsadc_lGetCalibStatusDetCheck(ChannelId);
  /*[cover parentID={C056F8FA-14FF-41d7-865C-13586433F3CC}]
     check if there is any Error[/cover]*/
  if(lDetVal ==DSADC_E_NO_ERR)
  #endif
  {
    /*[cover parentID={F3D3F619-7F0F-43fb-94AE-B6A7425EAE0F}]
      check if the calibration algorithm is currently running[/cover]*/
    if(Dsadc_ChannelData[ChannelId].CalibrationStatus == \
                    (Dsadc_CalibrationStatusType)DSADC_CALIBRATION_RUNNING)
    {
      /* Obtain the DSDAC HW channel assigned to ChannelId */
      HwChannelNum = DSADC_GET_HW_CH_NUM(ChannelId);
      /*Read the Actual status of the Calibration algorithm from the
        Hardware Register */
      CalibStatus = (Dsadc_CalibrationStatusType)Mcal_GetBitAtomic \
                                      (MODULE_EDSADC.CH[HwChannelNum].FCNTC.U, \
                                      IFX_EDSADC_CH_FCNTC_CAL_OFF, \
                                      IFX_EDSADC_CH_FCNTC_CAL_LEN);
      /*[cover parentID={FFC3E9B6-4ED3-4802-BB7C-7A84D9BFA6A4}]
        check if the calibration status is Running[/cover]*/
      if(CalibStatus == (uint8)DSADC_CALIBRATION_RUNNING)
      {
        /*set the return value as calibration running*/
        RetVal = DSADC_CALIBRATION_RUNNING;
        /*copy the return value to the calibration status*/
        Dsadc_ChannelData[ChannelId].CalibrationStatus = RetVal;
      }
      /*[cover parentID={4933C166-6F50-412a-B3D9-8B93D324D6D6}]
        check if the calibration status is Done[/cover]*/
      else if(CalibStatus == (uint8)DSADC_CALIBRATION_DONE)
      {
        /*set the return value as calibration Done*/
        RetVal = DSADC_CALIBRATION_DONE;
        /*[cover parentID={4E2A7F45-2CF3-4c74-BDA6-B6882C40F44A}]
          set the calibration status as Not Started[/cover]*/
        Dsadc_ChannelData[ChannelId].CalibrationStatus = \
                                            DSADC_CALIBRATION_NOT_STARTED;
      }
      /*[cover parentID={1362430C-7E4D-415c-B92B-FA176D14D554}]
        check if the calibration status is Calibration Error[/cover]*/
      else if(CalibStatus == (uint8)DSADC_CALIBRATION_ERROR)
      {
        /*set the return value as calibration Error*/
        RetVal = DSADC_CALIBRATION_ERROR;
        /*copy the return value to the calibration status*/
        Dsadc_ChannelData[ChannelId].CalibrationStatus = RetVal;
      }
      /*[cover parentID={78DE4415-9D0D-4024-ACA2-173D78A2B576}]
       Calibration status is not matching all other check[/cover]*/
      else
      {
        /*set the return value as calibration not Started*/
        RetVal = DSADC_CALIBRATION_NOT_STARTED;
        /*copy the return value to the calibration status*/
        Dsadc_ChannelData[ChannelId].CalibrationStatus = RetVal;
      }
    }
    else
    {
      /*[cover parentID={1DECAE4C-057E-4a61-BD41-1D46DD001ADA}]
        copy the current status to the Return value[/cover]*/
      RetVal = Dsadc_ChannelData[ChannelId].CalibrationStatus;
    }
  }
  return(RetVal);
}

#if(DSADC_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={FA8CE70F-21E8-46f1-876F-9694692267C0}] **
**                                                                            **
** Syntax           : Std_ReturnType Dsadc_InitCheck                          **
**                    (                                                       **
**                      const Dsadc_ConfigType  * const ConfigPtr             **
**                    )                                                       **
**                                                                            **
** Description      : This Function verifies the Initialization of DSADC      **
**                    driver.                                                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x29                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to DSADC configuration Set          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK - Initialization verification passed               **
**                    E_NOT_OK - Initialization verification failed           **
**                                                                            **
*******************************************************************************/
Std_ReturnType Dsadc_InitCheck(const Dsadc_ConfigType * const ConfigPtr)
{
  uint32 SfrVal,CfgVal;
  uint32 CompareFlag = 0xFFFFFFFFU;
  Std_ReturnType RetVal;

  /*[cover parentID={5643057B-8824-4473-A3FE-70EE0B29B42C}]
     Check if Config Ptr is NULL or DSADC module is not initialized[/cover]*/
  if((ConfigPtr == NULL_PTR) || (Dsadc_InitStatus != DSADC_INITIALIZED))
  {
    /* Update return value with E_NOT_OK */
    RetVal = E_NOT_OK;
  }
  else
  {
    /*Compare global clock control register with configuration value & Update
    flag as per result */
    SfrVal = ((uint32)MODULE_EDSADC.CLC.U);
    CfgVal = (uint32)ConfigPtr->DsadcClcCtrlReg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*[cover parentID={7D461400-9D2F-4de2-B541-0D4C5B1FA512}]
      check if global clock control register initialized properly [/cover]*/
    if (CompareFlag == 0xFFFFFFFFU)
    {
      /* Perform Initialization check for all configured SFRs */
      RetVal = Dsadc_lInitCheck();
    }
    else
    {
      /* Update return value as E_NOT_OK */
      RetVal = E_NOT_OK;
    }
  }
  return(RetVal);
}
#endif

#if(DSADC_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {1B003EBD-65F5-4bb6-9FD4-D4D7F24DABD2}]     **
**                                                                            **
** Syntax           : void Dsadc_GetVersionInfo                               **
**                    (                                                       **
**                      Std_VersionInfoType * const versioninfo               **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the version information of this module.**
**                    Note: This API is available only when                   **
**                          DsadcVersionInfoApi is configured as true.        **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x2C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : versioninfo -  Pointer to where to store the version    **
**                    information of this module                              **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Dsadc_GetVersionInfo(Std_VersionInfoType * const versioninfo)
{
  /* [cover parentID= {2F1DA544-7AA4-4baf-9C2B-8203821D15CB}]
  DET is ON or SAFETY is ON [/cover] */
  #if((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
  uint8 lErrVal;
  lErrVal = Dsadc_lCheckParamPointerDet(versioninfo,\
                                              DSADC_SID_GET_VERSION_INFO);
  /* [cover parentID= {5AA04A27-F00A-4a3f-B629-7FC703AEA8D8}]
  Param Pointer DET Error  [/cover] */
  if (DSADC_E_NO_ERR == lErrVal)
  #endif
  {
    /* [cover parentID= {EFA4C4D8-534D-4fe1-AE43-3E72E42DD24D}]
    Update Version Information in the location referenced by versioninfo
    [/cover] */
    /* [cover parentID= {AC29D732-484A-4efe-AEDA-481EBE5FFB96}]
    Dsadc_GetVersionInfo [/cover] */
    versioninfo->moduleID = (uint16)DSADC_MODULE_ID;
    versioninfo->vendorID = (uint16)DSADC_VENDOR_ID;
    versioninfo->sw_major_version = (uint8)DSADC_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = (uint8)DSADC_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = (uint8)DSADC_SW_PATCH_VERSION;
  }
}
#endif

#if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={C174AB12-A425-4b42-94BD-6CF0F46F5352}] **
**                                                                            **
** Syntax           : void Dsadc_Isr                                          **
**                    (                                                       **
**                      const Dsadc_ChannelType HwChannelId                   **
**                    )                                                       **
**                                                                            **
** Description      : Handles the interrupts from Main Service Request for    **
**                    the given DSADC HW Channel Id                           **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x2A                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : HwChannelId - DSADC Hardware channel ID                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
*******************************************************************************/
/*CYCLOMATIC_Dsadc_Isr_JUSTIFICATION:In DSADC ISR all possible safety error 
  check is performed and seperate control loops for each access mode leads to 
  increase of cyclomatic complexity.*/
void Dsadc_Isr(const Dsadc_ChannelType HwChannelId)
{
  Dsadc_ChannelType ChannelId;
  uint8 FifoErrorStatus;

  /*[cover parentID={83DB3E05-B5A5-4799-BF6A-366D32484064}]
    Is Configuration pointer not equal to NULL Pointer[/cover]*/
  if(Dsadc_ConfigPtr != NULL_PTR)
  {
    /*[cover parentID={DB414121-06F5-4f4d-8283-5A7EDD9369A6}]
    Check if the hardware ID passed is not beyond the available range in the 
    hardware[/cover]*/
    if(HwChannelId < DSADC_NUM_OF_CHANNELS)
    {
      /*Get the Logical Channel Id from the Hardware ID */
      ChannelId = Dsadc_ChannelId_Map[HwChannelId];
      /*[cover parentID={9FD94D9F-BF32-4c93-B144-98144062BB91}]
       Check if the Passed Hardware ID is Configured [/cover]*/
      if(ChannelId != DSADC_IMPLAUSIBLE_CHANNEL_ID)
      {
        /*[cover parentID={66561A47-CC76-4bc5-8907-5D13F4F03C84}]
          Check if the channel status is not IDLE [/cover]*/
        if(Dsadc_ChannelData[ChannelId].ChannelStatus != DSADC_IDLE)
        {
          /*[cover parentID={5BC52F60-AA10-44fa-86A8-898883E01626}]
          Check validity of interrupt using Hardware Event Flag[/cover]*/
          if(Mcal_GetBitAtomic(MODULE_EDSADC.EVFLAG.U,HwChannelId, \
                                          DSADC_ONE_U) == DSADC_ONE_U)
          {
            /*[cover parentID={8097279E-6478-421e-A0A1-0FCACFC8AB03}]
            Perform the Linear Buffer filling only if the access mode is
            configured as Access Mode Linear Buffer[/cover]*/
            if(Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId]. \
                                   AccessMode == DSADC_STREAM_LINEAR_BUFFER)
            {
              /*[cover parentID={36A01DF9-811E-41c2-8C23-78477B51DE7B}]
                Fill the Linear Buffer [/cover]*/
              /*[cover parentID={83FD2855-3DE1-4ee6-BE2F-C93243AA3B59}]
                Check the channel Result Buffer is not full [/cover]*/
              if(Dsadc_ChannelData[ChannelId].NumofValidConRes <       \
                              Dsadc_ChannelData[ChannelId].ChannelBufferSize)
              {
                /*[cover parentID={60EE598B-5FF1-4295-B8CF-E656E909C70B}]
                Extract the Result data from the RESULT Register Lower 16 bit
                [/cover]*/
                Dsadc_ChannelData[ChannelId].ChannelResBuffer \
                  [Dsadc_ChannelData[ChannelId].NumofValidConRes] =\
                    (Dsadc_ResultType)MODULE_EDSADC.CH[HwChannelId].RESM.U;
                /* [cover parentID={60BA9081-A2DF-406d-8E31-40046C95D8CE}]
                Increment the Valid result counter  [/cover] */
                Dsadc_ChannelData[ChannelId].NumofValidConRes++;
                /*check and clear FIFO error*/
                FifoErrorStatus = Dsadc_lHwFifoErrorHandling(ChannelId);
                /*[cover parentID={D2DB54A0-576F-4799-B4F3-3ADDFBFB39E4}]
                check if there is a FIFO error[/cover]*/
                if(FifoErrorStatus == DSADC_FIFO_ERROR)
                {
                  /*[cover parentID={ACAAB70B-E250-49b3-9DE2-76691D2AA480}]
                  Copy the local Fifo error status to channel data.[/cover]*/
                  Dsadc_ChannelData[ChannelId].FifoErrorStatus = \
                                                            FifoErrorStatus;
                }
                /*[cover parentID={13A0978A-4D76-4778-9349-B6F737161BB3}]
                  Check if the number of valid result is more than channel
                  buffer size[/cover]*/
                if(Dsadc_ChannelData[ChannelId].NumofValidConRes >= \
                                Dsadc_ChannelData[ChannelId].ChannelBufferSize)
                {
                  /*[cover parentID={DE5C95F7-2A33-4f50-8347-060BEE039B39}]
                  Set the Buffer Full Status[/cover]*/
                  Dsadc_ChannelData[ChannelId].BufferFull = \
                                                        DSADC_CH_BUFFER_FULL;
                }
              }
            }
            /* [cover parentID={839F31E0-9F68-4aad-ADFD-57B21A5765C6}]
            Perform the Circular Buffer filling only if the access mode is
            configured as Access Mode Circular Buffer [/cover]*/
            else if(Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId]. \
                                           AccessMode == DSADC_CIRCULAR_BUFFER)
            {
              /*[cover parentID={71695E57-21D8-4897-A3CC-CAD3CAEC7E57}]
              Fill the Circular Buffer [/cover]*/
              /*Extract the Result data from the RESULT Register Lower 16 bit */
              Dsadc_ChannelData[ChannelId].ChannelResBuffer \
                 [Dsadc_ChannelData[ChannelId].WritePtrCircularBuf] = \
                     (Dsadc_ResultType)MODULE_EDSADC.CH[HwChannelId].RESM.U;
              /*[cover parentID={264633C9-E18E-435b-A1A6-99657DABDAD7}]
              Check is there a buffer Full.[/cover]*/
              if((Dsadc_ChannelData[ChannelId].WritePtrCircularBuf == \
                    Dsadc_ChannelData[ChannelId].ReadPtrCircularBuf) && \
                      (Dsadc_ChannelData[ChannelId].ChannelStatus == \
                                               DSADC_RESULT_READY))
              {
                /*[cover parentID={4BA76BC9-9038-4532-9E6D-DAACCBBBC8BB}]
                Increment the read pointer and reset to 0 in case of Overflow
                [/cover]*/
                Dsadc_ChannelData[ChannelId].ReadPtrCircularBuf =     \
                        (((Dsadc_ChannelData[ChannelId].ReadPtrCircularBuf)+\
                           ((Dsadc_SizeType)DSADC_ONE_U))\
                           %(Dsadc_ChannelData[ChannelId].ChannelBufferSize));
              }
              /*[cover parentID={D8801047-591F-4f89-8308-233DD7AA2829}]
              Increment the Write Pointer and Reset to 0 in case of overflows
              [/cover]*/
              Dsadc_ChannelData[ChannelId].WritePtrCircularBuf =     \
                         (((Dsadc_ChannelData[ChannelId].WritePtrCircularBuf)+ \
                          ((Dsadc_SizeType)DSADC_ONE_U))\
                          %(Dsadc_ChannelData[ChannelId].ChannelBufferSize));
            }
            /*[cover parentID={13BAAB0E-04F2-4d98-B36F-27AA01714DA7}]
              Check if the Access mode is configured as single
              [/cover]*/
            else if(Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId]. \
                                           AccessMode == DSADC_SINGLE_READ)
            {
              /*[cover parentID={296669DD-2332-446f-88C3-44036A9235D3}]
              Clear the event flag
              [/cover]*/
              MODULE_EDSADC.EVFLAGCLR.U = ((uint32)DSADC_ONE_U<<HwChannelId);
            }
            else
            {
              /* Dummy else */
            }
            /*[cover parentID={DB0960E7-8BCE-4281-A06D-F083B5F2B106}]
            Set the Channel Status to Result ready[/cover]*/
            Dsadc_ChannelData[ChannelId].ChannelStatus = DSADC_RESULT_READY;
            /*[cover parentID={1AAE444B-7645-4ac6-BB02-69C051D7E7E5}]
            Check if the notification is enabled for this Channel[/cover]*/
            if(Dsadc_lGetChanNotifStatus(ChannelId) == \
                               (uint32)DSADC_NOTIFICATION_ENABLE)
            {
              /*[cover parentID={AB9D6E51-9C4A-4ae8-AFB1-E5430D90B6C0}]
              Check if the notification function pointer for New Result event
              is not a NULL Pointer[/cover]*/
              if (Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].\
                                            NewResultNotifyPtr != NULL_PTR)
              {
                /* Call Notification function */
                Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].\
                                                         NewResultNotifyPtr();
              }
              /*[cover parentID={EBDCF33B-8B83-44e3-B09A-55A09FAE182F}]
              Check if the Buffer is Full[/cover]*/
              if(Dsadc_ChannelData[ChannelId].BufferFull == \
                                                        DSADC_CH_BUFFER_FULL)
              {
                /*[cover parentID={84DB9A9D-06A0-4dc0-A95C-C3D5EADB2C48}]
                Check if the notification function pointer is not a
                NULL Pointer[/cover]*/
                if (Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].\
                                          BufferFullNotifyPtr != NULL_PTR)
                {
                  /*[cover parentID={B70C13C7-B7E9-47cd-8BB2-A5962C826DCD}]
                  Call the Buffer Full notification[/cover]*/
                  Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].\
                                                         BufferFullNotifyPtr();
                  Dsadc_ChannelData[ChannelId].BufferFull = (uint8)0U;
                }
              }
            }
          }
          /*[cover parentID={C8B2B9CF-4115-4653-AC0C-FB8AB87010DD}]
          SAFETY is ON[/cover]*/
          #if (DSADC_SAFETY_ENABLE == STD_ON)
          else
          {
            /* Spurious Interrupt */
            /*[cover parentID={0118D55F-1FD9-4693-872C-ACFC43E1AC09}]
            Report Safety Error DSADC_SE_INVALID_ISR [/cover]*/
            Mcal_ReportSafetyError(DSADC_MODULE_ID,DSADC_MODULE_INSTANCE, \
                                        DSADC_SID_ISR,DSADC_SE_INVALID_ISR);
          }
          #endif
        }
      }
      /*[cover parentID={5C942256-6BAD-46c8-BBCE-9459ED5C08DE}]
       SAFETY is ON[/cover]*/
      #if (DSADC_SAFETY_ENABLE == STD_ON)
      else
      {
        /*[cover parentID={63E82FB7-5243-4535-9E2D-3A871C2DBE1A}]
        Report Safety Error DSADC_SE_PARAM_HW_CHANNEL [/cover]*/
        Mcal_ReportSafetyError(DSADC_MODULE_ID,DSADC_MODULE_INSTANCE, \
              DSADC_SID_ISR,DSADC_SE_PARAM_HW_CHANNEL);
      }
      #endif
    }
    /*[cover parentID={5C942256-6BAD-46c8-BBCE-9459ED5C08DE}]
    SAFETY is ON[/cover]*/
    #if (DSADC_SAFETY_ENABLE == STD_ON)
    else
    {
      /*[cover parentID={63E82FB7-5243-4535-9E2D-3A871C2DBE1A}]
      Report Safety Error DSADC_SE_PARAM_HW_CHANNEL [/cover]*/
      Mcal_ReportSafetyError(DSADC_MODULE_ID,DSADC_MODULE_INSTANCE, \
            DSADC_SID_ISR,DSADC_SE_PARAM_HW_CHANNEL);
    }
    #endif
  }
}
#endif/*End for DSADC_ALL_CH_RESULT_HANDLING_DMA*/
/* [cover parentID={BA2883BE-E25F-42a9-8AD5-C4EAB9D40613}]
   Interrupt Control Registers.
   [/cover] */
#if((DSADC_GTMTRIGGER_USED == STD_ON) || (DSADC_ERUTRIGGER_USED == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={CCE9D6F7-E253-40c2-9217-D9E36A78E639}] **
**                                                                            **
** Syntax           : void Dsadc_TimerIsr                                     **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId,                    **
**                      const uint32 StatusFlag                               **
**                    )                                                       **
**                                                                            **
** Description      : Callback function from MCU to Service the Timer         **
**                    interrupts. Both GTM and ERU interrupts are serviced in **
**                    this callback function.                                 **
**                                                                            **
** Service ID       : 0x2B                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant for same channel, reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - DSADC channel ID                            **
**                    StatusFlag - Source for this Callback                   **
**                    For GTM -> (CCU0 or CCU1 from GTM TOM or ATOM)          **
**                    For ERU -> Pattern Match(1) or Pattern Miss(0)          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
*******************************************************************************/
void Dsadc_TimerIsr(const Dsadc_ChannelType ChannelId, const uint32 StatusFlag)
{
  /*[cover parentID={FA6D2B51-1D84-40ad-BB70-094E5C8A085F}]
  SAFETY is ON [/cover]*/
  #if (DSADC_SAFETY_ENABLE == STD_ON)
  /*[cover parentID={4B743FA3-7B10-4882-892E-95C6E779452F}]
   Check if the channel Id less than the maximum channel Configured[/cover]*/
  if(ChannelId < DSADC_MAX_CHANNELS_CONFIGURED)
  {
    /*[cover parentID={B56A84B6-73A2-46a8-A69A-9138BDE53DBB}]
      Check if the Dsadc channel is not in the IDLE State[/cover]*/
    if(Dsadc_ChannelData[ChannelId].ChannelStatus != DSADC_IDLE)
    {
      /*[cover parentID={D342D9D5-E190-4d0f-9789-ECA6AD93FC5C}]
        Check if the channel configured for Trigger mode window[/cover]*/
      if(Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].TriggerMode == \
                                                      DSADC_TRIGGER_MODE_WINDOW)
  #endif
      {
        /*[cover parentID={4E193875-12CF-40fb-A88F-EF0A4C83C0BD}]
        Any one of the Channel is using GTM Trigger source[/cover]*/
        #if(DSADC_GTMTRIGGER_USED == STD_ON)
        /*[cover parentID={8A2289D8-5B74-4296-A69C-956080CD1BA4}]
          Check if the trigger source is configured as GTM[/cover]*/
        if(Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].\
                          TriggerSource == DSADC_TRIGGER_GTM)
        {
          /*Call the GTM ISR*/
          Dsadc_lGtmIsr(ChannelId,StatusFlag);
        }
        else
        #endif
        /*[cover parentID={3D886F6E-C66F-49f3-B3AF-F1EBBFE51DEA}]
           Any one of the Channel is using GTM Trigger source[/cover]*/
        #if(DSADC_ERUTRIGGER_USED == STD_ON)
        {
        /*[cover parentID={5E10CB9C-7C12-4961-93EE-FF61CF19B762}]
          Check if the trigger source is configured as ERU [/cover]*/
        if(Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].\
                        TriggerSource == DSADC_TRIGGER_ERU)
        {
          /*Call the ERU ISR*/
          Dsadc_lEruIsr(ChannelId,StatusFlag);
        }
        else
        #endif
        {
          /*[cover parentID={12EDD4E0-5C49-4908-9997-586E2E03AB16}]
            Safety Error is Enabled[/cover]*/
          #if (DSADC_SAFETY_ENABLE == STD_ON)
          /*[cover parentID={53F3AAA4-468A-43be-9B5B-39DF492A18B1}]
          Report Safety Error DSADC_SE_INVALID_ISR[/cover] */
          Mcal_ReportSafetyError(DSADC_MODULE_ID,DSADC_MODULE_INSTANCE, \
                DSADC_SID_TIMERISR,DSADC_SE_INVALID_ISR);
          #endif
        }
        #if(DSADC_ERUTRIGGER_USED == STD_ON)
        }
        #endif
      }
      /*[cover parentID={12EDD4E0-5C49-4908-9997-586E2E03AB16}]
      SAFETY is ON [/cover]*/
      #if (DSADC_SAFETY_ENABLE == STD_ON)
      else
      {
        /*[cover parentID={53F3AAA4-468A-43be-9B5B-39DF492A18B1}]
          Report Safety Error DSADC_SE_INVALID_ISR[/cover] */
        Mcal_ReportSafetyError(DSADC_MODULE_ID,DSADC_MODULE_INSTANCE, \
          DSADC_SID_TIMERISR,DSADC_SE_INVALID_ISR);
      }
    }
    else
    {
      /*[cover parentID={2947490C-145D-4a96-9A2E-C364980FC4E6}]
        Report Safety Error for DSADC_SE_EARLY_WINDOW_ISR [/cover]*/
      Mcal_ReportSafetyError(DSADC_MODULE_ID,DSADC_MODULE_INSTANCE, \
        DSADC_SID_TIMERISR,DSADC_SE_EARLY_WINDOW_ISR);
    }
  }
  else
  {
    /*[cover parentID={53F3AAA4-468A-43be-9B5B-39DF492A18B1}]
      Report Safety Error for INVALID ISR [/cover]*/
      Mcal_ReportSafetyError(DSADC_MODULE_ID,DSADC_MODULE_INSTANCE, \
        DSADC_SID_TIMERISR,DSADC_SE_INVALID_ISR);
  }
  #endif
}
#endif
/* [cover parentID={BA2883BE-E25F-42a9-8AD5-C4EAB9D40613}]
   Interrupt Control Registers.
   [/cover] */

   
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/


#if(DSADC_GTMTRIGGER_USED == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={ED7977C7-CD5B-4b60-9872-026C99A5A5A0}] **
**                                                                            **
** Syntax           : LOCAL_INLINE void Dsadc_lGtmIsr                         **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId,                    **
**                      const uint32 StatusFlag                               **
**                    )                                                       **
**                                                                            **
** Description      : This API Handles the Interrupts from GTM for Window     **
**                    events(Open and Close).                                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric Id of  the DSADC Channel            **
**                    StatusFlag - The source for this Event(CCU0 or CCU1     **
**                    from GTM TOM or ATOM)                                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
*******************************************************************************/
LOCAL_INLINE void Dsadc_lGtmIsr(const Dsadc_ChannelType ChannelId, \
                                                   const uint32 StatusFlag)
{
  /*[cover parentID={AD0DDF32-C246-4ec7-80DA-6ED03436D8A8}]
  SAFETY is ON [/cover]*/
  #if (DSADC_SAFETY_ENABLE == STD_ON)
  /*[cover parentID={28E37EFD-73E8-421d-BABA-F72CB3E6BB20}]
    Check if the status flag is valid[/cover]*/
  if(StatusFlag <= DSADC_GTM_ISR_MSK)
  #endif
  {
    /*[cover parentID={DCA25C11-E573-4c2c-8356-57DBAB069DF2}]
      Check if the Interrupt due to Window Close Event[/cover]*/
    if(Mcal_GetBitAtomic(StatusFlag,DSADC_GTM_CCU1_EVNT_MSK,\
                                             DSADC_GATE_GTM_MSK_LEN) == TRUE)
    {
      /*[cover parentID={71AEBC70-CBAF-4d49-A301-FAEA767262C7}]
        Call window close event function[/cover]*/
      Dsadc_lWindowCloseEvnt(ChannelId);
    }
    /*[cover parentID={AF00C07D-8485-482d-B04A-03443DEE419C}]
      Check if the Interrupt due to Window Open event[/cover]*/
    if(Mcal_GetBitAtomic(StatusFlag,DSADC_GTM_CCU0_EVNT_MSK,\
                                             DSADC_GATE_GTM_MSK_LEN) == TRUE)
    {
      /*[cover parentID={B0E9D7BA-D9A9-4204-B022-F05D73E74B23}]
        Call window open event function[/cover]*/
      Dsadc_lWindowOpenEvnt(ChannelId);
    }
  }
  #if (DSADC_SAFETY_ENABLE == STD_ON)
  else
  {
    /*[cover parentID={38D0181C-F6E1-46d8-AB45-D68F164142DE}]
      Report Safety Error DSADC_SE_INVALID_ISR [/cover]*/
    Mcal_ReportSafetyError(DSADC_MODULE_ID,DSADC_MODULE_INSTANCE, \
                         DSADC_SID_TIMERISR,DSADC_SE_INVALID_ISR);
  }
  #endif
}
#endif

#if(DSADC_ERUTRIGGER_USED == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={BE7A3004-FFBB-4f4c-A66F-BD38F24C93A3}] **
**                                                                            **
** Syntax           : LOCAL_INLINE void Dsadc_lEruIsr                         **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId,                    **
**                      const uint32 StatusFlag                               **
**                    )                                                       **
**                                                                            **
** Description      : This API Handles the Interrupts from ERU for Window     **
**                    events(Open and Close).                                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - DSADC channel ID                            **
**                    StatusFlag - The source of the interrupt(Pattern match  **
**                                 or Pattern miss)                           **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
*******************************************************************************/
LOCAL_INLINE void Dsadc_lEruIsr(const Dsadc_ChannelType ChannelId,
                                                        const uint32 StatusFlag)
{
  /*[cover parentID={28FBF368-B732-4300-9648-13CAB8EA0F54}]
  SAFETY is ON [/cover]*/
  #if (DSADC_SAFETY_ENABLE == STD_ON)
  /*[cover parentID={1DCAC50A-540E-429c-8020-5A42148254F5}]
    Check if the status flag is valid[/cover]*/
  if(StatusFlag <= DSADC_ERU_ISR_MSK)
  #endif
  {
    /*[cover parentID={BE36FDB6-5834-4fd1-BFB7-0949D77B5511}]
      Check if the window signal active level is high[/cover]*/
    if(Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].GateActiveLevel \
                                                   == DSADC_GATE_HIGH_LEVEL)
    {
      /*[cover parentID={239F5444-DE78-4376-BC88-70FB36C364EA}]
        Check if the Interrupt due to Window Open event[/cover]*/
      if(StatusFlag == (uint8)DSADC_ERU_GATE_PD_MATCH_MASK)
      {
        /*[cover parentID={446E486B-6DE1-4a9a-B71A-5064B06F4513}]
          Call window open event function[/cover]*/
        Dsadc_lWindowOpenEvnt(ChannelId);
      }
      /*[cover parentID={761E61E1-8B65-4cea-BA41-00F86FF28F48}]
        check if the Interrupt due to Window Close Event[/cover]*/
      if(StatusFlag == (uint8)DSADC_ERU_GATE_PD_MISS_MASK)
      {
        /*[cover parentID={757179C0-B9F0-407e-934D-B8E1E01E4183}]
          Call window close event function[/cover]*/
        Dsadc_lWindowCloseEvnt(ChannelId);
      }
    }
    /*[cover parentID={16BF4C4C-4836-4a4b-B3A0-7E2395955E99}]
      Check if the window signal active level is Low[/cover]*/
    else if(Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId]. \
                                      GateActiveLevel == DSADC_GATE_LOW_LEVEL)
    {
      /*[cover parentID={1666E815-3C0D-43ee-9612-62C32F1CAA48}]
        Check if the Interrupt due to Window Open Event[/cover]*/
      if(StatusFlag == (uint8)DSADC_ERU_GATE_PD_MISS_MASK)
      {
        /*[cover parentID={BE56777E-EFE5-43cf-B65E-DC1FF87839B4}]
          Call window open event function[/cover]*/
        Dsadc_lWindowOpenEvnt(ChannelId);
      }
      /*[cover parentID={34CC7874-1A48-43a7-AC98-B6CFC6057215}]
        check if the Interrupt due to Window Close Event[/cover]*/
      if(StatusFlag == (uint8)DSADC_ERU_GATE_PD_MATCH_MASK)
      {
        /*[cover parentID={DAE42793-8CE1-4328-A02C-850B614CC93C}]
          Call window close event function[/cover]*/
        Dsadc_lWindowCloseEvnt(ChannelId);
      }
    }
    else
    {
      /* Do Nothing */
    }
  }
  #if (DSADC_SAFETY_ENABLE == STD_ON)
  else
  {
    /*[cover parentID={FD82E91D-63B3-4962-82B4-F0BDFF51C937}]
      Report Safety Error DSADC_SE_INVALID_ISR [/cover]*/
    Mcal_ReportSafetyError(DSADC_MODULE_ID,DSADC_MODULE_INSTANCE, \
                           DSADC_SID_TIMERISR,DSADC_SE_INVALID_ISR);
  }
  #endif
}
#endif

/*******************************************************************************
** Traceability     : [cover parentID={0B63CBD2-1B1B-47e6-9ACE-F883DD4F7B37}] **
**                                                                            **
** Syntax           : static void Dsadc_lResetSfr                             **
**                    (const Dsadc_ConfigType * const ConfigPtr)              **
**                                                                            **
** Description      : This function resets the DSADC global and configured    **
**                    channels registers (based on ConfigPtr) to their reset  **
**                    value, by manually writing these registers with their   **
**                    default values                                          **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to the DSADC Driver configuration   **
**                                Structure                                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Dsadc_lResetSfr (const Dsadc_ConfigType * const ConfigPtr)

{
  uint8 ChannelIndex;
  uint8 HwChannelNum;

  /* Reset the Global Run Control register */
  MODULE_EDSADC.GLOBRC.U  = DSADC_GLOBRC_REG_RESET_VALUE;

  /* Reset the Global Configuration register */
  MODULE_EDSADC.GLOBCFG.U = DSADC_GLOBCFG_REG_RESET_VALUE;

  /* Reset the Carrier Generator Configuration register */
  MODULE_EDSADC.CGCFG.U   = DSADC_CGCFG_REG_RESET_VALUE;

  /* Clear any result or alarm events of the EDSADC channels */
  MODULE_EDSADC.EVFLAGCLR.U = DSADC_CLR_ALL_EDSADC_CH_EVENTS;

  /*[cover parentID={7BA730CF-B343-4016-BF3F-CB138846BCD6}]
  Any one of the channel is configured Trigger source as ERU[/cover]*/
  #if(DSADC_ERUTRIGGER_USED == STD_ON)
  /*[cover parentID={DD4D2138-897E-4281-BE09-88644A0EB372}]
    Check if any ERU ERS input channels are configured[/cover]*/
  if(ConfigPtr->DsadcEruErsConfig != NULL_PTR)
  {
    /* Reset the ERU ERS input channels to their default values */
    Dsadc_lDeInitErsChannels(ConfigPtr->DsadcEruErsConfig);
  }
  #endif

  /*Loop until the Maximum configured channel to reset the channel
    specific SFR's*/
  for(ChannelIndex = 0; ChannelIndex < DSADC_MAX_CHANNELS_CONFIGURED; \
                                                             ChannelIndex++)
  {
    /* Obtain the DSDAC HW channel assigned to ChannelId */
    HwChannelNum = (ConfigPtr->DsadcChannelConfiguration[ChannelIndex].\
                              HwAssignedChannelNum);

    /* Reset the Modulator Configuration register */
    MODULE_EDSADC.CH[HwChannelNum].MODCFG.U  = DSADC_MODCFG_RESET_VALUE;

    /* Reset the Demodulator Configuration register */
    MODULE_EDSADC.CH[HwChannelNum].DICFG.U   = DSADC_DICFG_RESET_VALUE;

    /* Reset the Common Mode Voltage Configuration register */
    MODULE_EDSADC.CH[HwChannelNum].VCM.U     = DSADC_VCM_RESET_VALUE;

    /* Reset Gain calibration register */
    MODULE_EDSADC.CH[HwChannelNum].GAINCAL.U = DSADC_GAINCAL_RESET_VALUE;

    /* Reset Gain control register */
    MODULE_EDSADC.CH[HwChannelNum].GAINCTR.U = DSADC_GAINCTR_RESET_VALUE;

    /* Reset Gain correction register */
    MODULE_EDSADC.CH[HwChannelNum].GAINCORR.U = DSADC_GAINCORR_RESET_VALUE;

    /* Reset Offset Compensation register */
    MODULE_EDSADC.CH[HwChannelNum].OFFCOMP.U  = DSADC_OFFCOMP_RESET_VALUE;

    /* Reset Integration window control register */
    MODULE_EDSADC.CH[HwChannelNum].IWCTR.U  =   DSADC_IWCTR_RESET_VALUE;

    /* Reset filter configuration register */
    MODULE_EDSADC.CH[HwChannelNum].FCFGM.U  =   DSADC_FCFGM_RESET_VALUE;

    /* Reset CIC filter configuration register */
    MODULE_EDSADC.CH[HwChannelNum].FCFGC.U  =   DSADC_FCFGC_RESET_VALUE;

    /* Reset Auxiliary CIC filter configuration register */
    MODULE_EDSADC.CH[HwChannelNum].FCFGA.U  =   DSADC_FCFGA_RESET_VALUE;

    /* Reset Time Stamp Counter Register */
    MODULE_EDSADC.CH[HwChannelNum].TSCNT.U    = DSADC_TSTCNT_RESET_VALUE;

    /* Reset Result register FIFO control register */
    MODULE_EDSADC.CH[HwChannelNum].RFC.U      = DSADC_RFC_RESET_VALUE;

    /* Reset Limit checking configuration register  */
    MODULE_EDSADC.CH[HwChannelNum].BOUNDSEL.U = DSADC_BOUNDSEL_RESET_VALUE;

    /* Reset Overshoot Compensation configuration register  */
    MODULE_EDSADC.CH[HwChannelNum].OVSCFG.U =   DSADC_OVSCFG_RESET_VALUE;

    /* Reset Carrier Generator Synchronization register  */
    MODULE_EDSADC.CH[HwChannelNum].CGSYNC.U =   DSADC_CGSYNC_RESET_VALUE;

    /* Reset Rectification configuration register  */
    MODULE_EDSADC.CH[HwChannelNum].RECTCFG.U =  DSADC_RECTCFG_RESET_VALUE;
    /*[cover parentID={FF160AD8-1203-4ed5-ABB1-0A6096A5614B}]
    Any one of the channel is configured Trigger source as ERU[/cover]*/
    #if(DSADC_ERUTRIGGER_USED == STD_ON)
    /*[cover parentID={35322615-C75E-4553-B55E-4ADD8153C516}]
      Check if the Trigger source is configured as ERU[/cover]*/
    if(ConfigPtr->DsadcChannelConfiguration[ChannelIndex]. \
                                  TriggerSource == DSADC_TRIGGER_ERU)
    {
      /* Disable the ERU trigger source */
      Dsadc_lDisableEruTrigger \
                   (&ConfigPtr->DsadcChannelConfiguration[ChannelIndex]);
    }
    #endif

  }
}

/*******************************************************************************
** Traceability     : [cover parentID={82338FB3-CEE3-4d74-8631-2A9452750532}] **
**                                                                            **
** Syntax           : LOCAL_INLINE void Dsadc_lConfigSfr                      **
**                    (const Dsadc_ConfigType * const ConfigPtr)              **
**                                                                            **
** Description      : This function writes the DSADC global and configured    **
**                    channel registers (based on ConfigPtr) to their         **
**                    configured value. It also configures the channels       **
**                    associated trigger sources(GTM/ERU channels)            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to the DSADC Driver configuration   **
**                                structure                                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Dsadc_lConfigSfr(const Dsadc_ConfigType * const ConfigPtr)

{
  uint8 ChannelIndex;
  uint8 HwChannelNum;

  /* Configure the Global Configuration register */
  MODULE_EDSADC.GLOBCFG.U = ConfigPtr->GlobalConfigReg;

  /* Reset the Carrier Generator Configuration register */
  MODULE_EDSADC.CGCFG.U   = ConfigPtr->CarrierGenConfigReg;

  /*[cover parentID={C7CB0BEC-8352-4173-9595-7A55F716D9EF}]
  Any one of the channel is configured Trigger source as ERU[/cover]*/
  #if(DSADC_ERUTRIGGER_USED == STD_ON)
  /*[cover parentID={F72A8D2F-D196-48bc-9D02-27663B121560}]
     Check if any ERU ERS input channels are configured[/cover]*/
  if(ConfigPtr->DsadcEruErsConfig != NULL_PTR)
  {
    /* configure the ERU-ERS input channel from the ConfigPtr */
    Dsadc_lConfigErsChannels(ConfigPtr->DsadcEruErsConfig);
  }
  #endif
  /*Loop till the Maximum configured channel to configure channel SFR's*/
  for(ChannelIndex = 0; ChannelIndex < DSADC_MAX_CHANNELS_CONFIGURED ; \
                                                               ChannelIndex++)
  {
    /* Obtain the DSDAC HW channel assigned to ChannelId */
    HwChannelNum = DSADC_GET_HW_CH_NUM(ChannelIndex);

    /* Configure the Modulator Configuration register */
    MODULE_EDSADC.CH[HwChannelNum].MODCFG.U  = \
          ConfigPtr->DsadcChannelConfiguration[ChannelIndex].ModulatorConfigReg;

    /* Configure the Demodulator Configuration register */
    MODULE_EDSADC.CH[HwChannelNum].DICFG.U   = \
        ConfigPtr->DsadcChannelConfiguration[ChannelIndex].DemodulatorConfigReg;

    /* Configure the Common Mode Voltage Configuration register */
    MODULE_EDSADC.CH[HwChannelNum].VCM.U     = \
     ConfigPtr->DsadcChannelConfiguration[ChannelIndex].CommonModeVoltConfigReg;

    /* Configure Gain calibration register */
    MODULE_EDSADC.CH[HwChannelNum].GAINCAL.U = \
        ConfigPtr->DsadcChannelConfiguration[ChannelIndex].GainCalibConfigReg;

    /* Configure Gain control register */
    MODULE_EDSADC.CH[HwChannelNum].GAINCTR.U = \
       ConfigPtr->DsadcChannelConfiguration[ChannelIndex].GainControlConfigReg;

    /* Configure Gain correction register */
    MODULE_EDSADC.CH[HwChannelNum].GAINCORR.U = \
         ConfigPtr->DsadcChannelConfiguration[ChannelIndex].GainCorrConfigReg;

    /* Configure Offset Compensation register */
    MODULE_EDSADC.CH[HwChannelNum].OFFCOMP.U  = \
        ConfigPtr->DsadcChannelConfiguration[ChannelIndex].OffsetCompConfigReg;

    /* Configure Integration window control register */
    MODULE_EDSADC.CH[HwChannelNum].IWCTR.U  =   \
        ConfigPtr->DsadcChannelConfiguration[ChannelIndex].IntegratorConfigReg;

    /* Configure filter configuration register */
    MODULE_EDSADC.CH[HwChannelNum].FCFGM.U  =   \
        ConfigPtr->DsadcChannelConfiguration[ChannelIndex].FilterConfigReg;

    /* Configure CIC filter configuration register */
    MODULE_EDSADC.CH[HwChannelNum].FCFGC.U  =   \
        ConfigPtr->DsadcChannelConfiguration[ChannelIndex].CICFilterConfigReg;

    /* Configure Auxiliary CIC filter configuration register */
    MODULE_EDSADC.CH[HwChannelNum].FCFGA.U  =   \
       ConfigPtr->DsadcChannelConfiguration[ChannelIndex].AuxCICFilterConfigReg;

    /* Configure Time Stamp Counter Register */
    MODULE_EDSADC.CH[HwChannelNum].TSCNT.U    =   \
        ConfigPtr->DsadcChannelConfiguration[ChannelIndex].TimeStampConfigReg;

    /* Configure Result register FIFO control register */
    MODULE_EDSADC.CH[HwChannelNum].RFC.U      =   \
      ConfigPtr->DsadcChannelConfiguration[ChannelIndex].ResultFifoConfigReg;

    /* Configure Limit checking configuration register  */
    MODULE_EDSADC.CH[HwChannelNum].BOUNDSEL.U =  \
      ConfigPtr->DsadcChannelConfiguration[ChannelIndex].LimitCheckingConfigReg;

    /* Configure the Overshoot compensation configuration register  */
    MODULE_EDSADC.CH[HwChannelNum].OVSCFG.U =  \
    ConfigPtr->DsadcChannelConfiguration[ChannelIndex].OvershootCompenconfigReg;

    /* Configure Carrier Generator Synchronization register  */
    MODULE_EDSADC.CH[HwChannelNum].CGSYNC.U =   \
    ConfigPtr->DsadcChannelConfiguration[ChannelIndex].CarrierGenSyncConfigReg;

    /* Configure the Rectification configuration register  */
    MODULE_EDSADC.CH[HwChannelNum].RECTCFG.U =  \
      ConfigPtr->DsadcChannelConfiguration[ChannelIndex].RectificationConfigReg;

  }
}

#if(DSADC_ERUTRIGGER_USED == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={E8E5AF21-6478-4d17-8362-3BEAA5C3C03B}] **
**                                                                            **
** Syntax           : LOCAL_INLINE void Dsadc_lDeInitErsChannels              **
**                    (                                                       **
**                     const Dsadc_EruErsConfigType* const ErsChannelConfigPtr**
**                    )                                                       **
**                                                                            **
** Description      : This function de-initializes the ERS input channels     **
**                    registers, which is used as input sources for pattern   **
**                    detection of OGU channels.                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ErsChannelConfigPtr - Pointer to the ERS channel        **
**                    configuration structure                                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Dsadc_lDeInitErsChannels(\
                      const Dsadc_EruErsConfigType * const ErsChannelConfigPtr)
{
  uint8 ErsChIndex;
  uint8 ErsChNum;
  uint8 EicrChIndex;
  uint8 EicrChPos;
  /* The variable 'ErsChConfigured' is made volatile to suppress a tasking
   * compilation warning that arises from comparing
   * DSADC_MAX_ERS_CHANNELS_CONFIGURED with ErsChIndex. In the scenario none
   * of the configured DSADC channel use OGU channels for triggers,
   * DSADC_MAX_ERS_CHANNELS_CONFIGURED is set to 0. Hence a condition
   * ErsChIndex < DSADC_MAX_ERS_CHANNELS_CONFIGURED always returns false
   */
  volatile uint8 ErsChConfigured = DSADC_MAX_ERS_CHANNELS_CONFIGURED;
  for(ErsChIndex = 0U; ErsChIndex < ErsChConfigured; ErsChIndex++)
  {
    /* Obtain the ERS input channel number*/
    ErsChNum = ErsChannelConfigPtr[ErsChIndex].ErsChannelNo;

    /*Obtain the EICR register Index by dividing the ERS channel number by 2*/
    EicrChIndex = ErsChNum >> DSADC_ONE_U;

    /* ERS Odd Channels are at bit position 16 in EICR register.
       ERS Even Channels are at bit position 0 in EICR register.*/
    /* Obtain the ERS Channel Position in the EICR Register */
    EicrChPos =  ((ErsChNum & DSADC_ONE_U) << DSADC_ERS_CH_EICR_SHIFT);
    /*[cover parentID={BF47225B-E9ED-4110-9483-DDFF6305AF6F}]
       Reset the ERS input channel configuration in EICR register[/cover]*/
    DSADC_INIT_DEINIT_WRITE_SAFETY_ENDINIT_PROTREGMASK(\
                                       (&MODULE_SCU.EICR[EicrChIndex]),\
                                       ((uint32)DSADC_ERS_CH_RESET),\
                                       ((uint32)DSADC_ERU_WR_MASK<<EicrChPos));
  }
}
#endif

#if(DSADC_ERUTRIGGER_USED == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={A4B9CFA9-013B-421c-8E2E-572C910751CC}] **
**                                                                            **
** Syntax           : LOCAL_INLINE void Dsadc_lConfigErsChannels              **
**                    (                                                       **
**                     const Dsadc_EruErsConfigType* const ErsChannelConfigPtr**
**                    )                                                       **
**                                                                            **
** Description      : This function configures the ERS input channels         **
**                    registers, which is used as input sources for pattern   **
**                    detection of OGU channels.                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ErsChannelConfigPtr - Pointer to the ERS channel        **
**                    configuration structure                                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Dsadc_lConfigErsChannels(\
                      const Dsadc_EruErsConfigType * const ErsChannelConfigPtr)
{
  uint8 ErsChIndex;
  uint8 ErsChNum;
  uint8 EicrChIndex;
  uint8 EicrChPos;
  /* The variable 'ErsChConfigured' is made volatile to suppress a tasking
   * compilation warning that arises from comparing
   * DSADC_MAX_ERS_CHANNELS_CONFIGURED with ErsChIndex. In the scenario none
   * of the configured DSADC channel use OGU channels for triggers,
   * DSADC_MAX_ERS_CHANNELS_CONFIGURED is set to 0. Hence a condition
   * ErsChIndex < DSADC_MAX_ERS_CHANNELS_CONFIGURED always returns false
   */
  volatile uint8 ErsChConfigured = DSADC_MAX_ERS_CHANNELS_CONFIGURED;
  for(ErsChIndex = 0U; ErsChIndex < ErsChConfigured; ErsChIndex++)
  {
    /* Obtain the ERS input channel number*/
    ErsChNum = ErsChannelConfigPtr[ErsChIndex].ErsChannelNo;

    /*Obtain the EICR register Index by dividing the ERS channel number by 2*/
    EicrChIndex = ErsChNum >> DSADC_ONE_U;

    /* ERS Odd Channels are at bit position is 16 in EICR register.
       ERS Even Channels are at bit position is 0 in EICR register.*/
    /* Obtain the ERS Channel Position in the EICR Register */
    EicrChPos =  ((ErsChNum & DSADC_ONE_U) << DSADC_ERS_CH_EICR_SHIFT);

    /*[cover parentID={1E98E617-FA93-40b3-8039-1587C5616CD8}]
       Configure the ERS input channel configuration in EICR register[/cover]*/
    DSADC_INIT_DEINIT_WRITE_SAFETY_ENDINIT_PROTREGMASK(\
                         (&MODULE_SCU.EICR[EicrChIndex]),\
                         ((uint32)ErsChannelConfigPtr[ErsChIndex].EruErsEicr \
                          <<EicrChPos),((uint32)DSADC_ERU_WR_MASK<<EicrChPos));
  }
}
#endif

#if(DSADC_ERUTRIGGER_USED == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={1FFFD14F-E6B8-4139-9308-22ECB739753D}] **
**                                                                            **
** Syntax           : LOCAL_INLINE void Dsadc_lDisableEruTrigger              **
**                    (                                                       **
**                      const Dsadc_ChannelConfigType                         **
**                                       * const DsadcChannelConfigPtr        **
**                    )                                                       **
**                                                                            **
** Description      : This function disables the GTM/OGU trigger source for   **
**                    the configured DSADC channel.                           **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : DsadcChannelConfigPtr - Pointer to the DSADC channel    **
**                    configuration structure                                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Dsadc_lDisableEruTrigger(\
                   const Dsadc_ChannelConfigType * const DsadcChannelConfigPtr)
{

  uint8 OguChNum;
  uint8 IgcrChIndex;
  uint8 IgcrChPos;

  /*[cover parentID={CD822814-0264-4ed9-A013-613D7B495AC4}]
     Check if the DSADC channel trigger source an OGU channel
       (pattern detection) and it is not a NULL Pointer[/cover]*/
  if(DsadcChannelConfigPtr->Dsadc_EruOguConf != NULL_PTR)
  {
    /* Obtain the OGU output channel number*/
    OguChNum = DsadcChannelConfigPtr->Dsadc_EruOguConf->OguChannelNo;

    /* Obtain the IGCR register Index by dividing the
       OGU channel number by 2 */
    IgcrChIndex = OguChNum >> DSADC_ONE_U;

    /* OGU Odd Channels are at bit position is 16 in IGCR register.
       OGU Even Channels are at bit position is 0 in IGCR register.*/
    /* Obtain the OGU Channel Position in the IGCr register*/
    IgcrChPos =  ((OguChNum & DSADC_ONE_U) << DSADC_OGU_CH_IGCR_SHIFT);
    /*[cover parentID={9AD12CCF-33ED-49d1-8EE0-36768CD8F251}]
      Reset the OGU output channel configuration in IGCR register[/cover]*/
    DSADC_RUNTIME_WRITE_SAFETY_ENDINIT_PROTREGMASK(\
                                    (&MODULE_SCU.IGCR[IgcrChIndex]),\
                                    ((uint32)DSADC_OGU_CH_RESET),\
                                    ((uint32)DSADC_ERU_WR_MASK<<IgcrChPos));
  }
}
#endif

#if(DSADC_ERUTRIGGER_USED == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={31590486-C15A-4bf8-97E6-D7347504B77C}] **
**                                                                            **
** Syntax           : LOCAL_INLINE void Dsadc_lEnableEruTrigger               **
**                    (                                                       **
**                      const Dsadc_ChannelConfigType                         **
**                                          * const DsadcChannelConfigPtr     **
**                    )                                                       **
**                                                                            **
** Description      : This function enables the ERU OGU trigger source for    **
**                    the configured DSADC channel.                           **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : DsadcChannelConfigPtr - Pointer to the DSADC channel    **
**                    configuration structure                                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Dsadc_lEnableEruTrigger(\
                  const Dsadc_ChannelConfigType * const DsadcChannelConfigPtr)
{

  uint8 OguChNum;
  uint8 IgcrChIndex;
  uint8 IgcrChPos;

  /*[cover parentID={A92245C8-E532-4165-A0F3-21D8E7747878}]
    Check if the DSADC channel trigger source an OGU channel
    (pattern detection) and it is not a NULL Pointer[/cover]*/
  if(DsadcChannelConfigPtr->Dsadc_EruOguConf != NULL_PTR)
  {
    /* Obtain the OGU output channel number*/
    OguChNum = DsadcChannelConfigPtr->Dsadc_EruOguConf->OguChannelNo;

    /* Obtain the IGCR register Index by dividing the
       OGU channel number by 2 */
    IgcrChIndex = OguChNum >> DSADC_ONE_U;

    /* OGU Odd Channels are at bit position is 16 in IGCR register.
       OGU Even Channels are at bit position is 0 in IGCR register.*/
    /* Obtain the OGU Channel Position in the IGCR register*/
    IgcrChPos =  ((OguChNum & DSADC_ONE_U) << DSADC_OGU_CH_IGCR_SHIFT);

    /*[cover parentID={34D39AC7-EFF8-4156-82DB-1D4B0ABA96A1}]
      Configure the OGU channel configuration in IGCR register without 
      enabling the ERU OGU Interrupt[/cover]*/
    DSADC_RUNTIME_WRITE_SAFETY_ENDINIT_PROTREGMASK(\
      (&MODULE_SCU.IGCR[IgcrChIndex]),\
      ((uint32)((DsadcChannelConfigPtr->Dsadc_EruOguConf->EruOguIgcr)& \
                            (uint32)DSADC_OGU_INTERRUPT_MASK)<<IgcrChPos),\
      ((uint32)DSADC_ERU_WR_MASK<<IgcrChPos));
  }
}
#endif

#if(DSADC_ERUTRIGGER_USED == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={8E2D12AC-DD2E-451e-BA8E-D1DF94EBEDD1}] **
**                                                                            **
** Syntax           : LOCAL_INLINE void Dsadc_lEnableEruInterrupt             **
**                    (                                                       **
**                      const Dsadc_ChannelConfigType                         **
**                                          * const DsadcChannelConfigPtr     **
**                    )                                                       **
**                                                                            **
** Description      : This function enables the interrupt for the ERU trigger **
                      source which is configured for the DSADC channel.       **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : DsadcChannelConfigPtr - Pointer to the DSADC channel    **
**                    configuration structure                                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Dsadc_lEnableEruInterrupt(\
                  const Dsadc_ChannelConfigType * const DsadcChannelConfigPtr)
{

  uint8 OguChNum;
  uint8 IgcrChIndex;
  uint8 IgcrChPos;

  /*[cover parentID={C99B373F-780A-43aa-8C4F-399A9B1014F3}]
    Check if the DSADC channel trigger source an OGU channel
    (pattern detection) and it is not a NULL Pointer[/cover]*/
  if(DsadcChannelConfigPtr->Dsadc_EruOguConf != NULL_PTR)
  {
    /* Obtain the OGU output channel number*/
    OguChNum = DsadcChannelConfigPtr->Dsadc_EruOguConf->OguChannelNo;

    /* Obtain the IGCR register Index by dividing the
       OGU channel number by 2 */
    IgcrChIndex = OguChNum >> DSADC_ONE_U;

    /* OGU Odd Channels are at bit position is 16 in IGCR register.
       OGU Even Channels are at bit position is 0 in IGCR register.*/
    /* Obtain the OGU Channel Position in the IGCR register*/
    IgcrChPos =  ((OguChNum & DSADC_ONE_U) << DSADC_OGU_CH_IGCR_SHIFT);

    /*[cover parentID={AE7607FC-9C33-4622-A41F-89B13766339D}]
      Enable the OGU channel interrupt[/cover]*/
    DSADC_RUNTIME_WRITE_SAFETY_ENDINIT_PROTREGMASK(\
      (&MODULE_SCU.IGCR[IgcrChIndex]),\
      ((uint32)DsadcChannelConfigPtr->Dsadc_EruOguConf->EruOguIgcr<<IgcrChPos),\
      ((uint32)DSADC_ERU_WR_MASK<<IgcrChPos));
  }
}
#endif

/*******************************************************************************
** Traceability     : [cover parentID={FD947BA6-9227-4af5-BF8B-BE4F27B1ABFC}] **
**                                                                            **
** Syntax           : LOCAL_INLINE void Dsadc_lEnableModulation               **
**                    (const Dsadc_ChannelType HwChannelId)                   **
**                                                                            **
** Description      : This function Enable the Modulator and Demodulator      **
**                    for the given Hardware channel number.                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : HwChannelId - DSADC Hardware channel ID                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Dsadc_lEnableModulation(const Dsadc_ChannelType HwChannelId)
{
  uint8 ModulatorBitPos;
  /* Obtain the modulator bit position in GLOBRC register*/
  ModulatorBitPos = (uint8)(HwChannelId + DSADC_MODULATOR_RUN_CFG);
  /* [cover parentID={469E7286-427B-4a67-9BA8-D0BC9F15D20E}]
     Enable the channel modulator [/cover] */
  Mcal_SetBitAtomic(&MODULE_EDSADC.GLOBRC,ModulatorBitPos,\
                     DSADC_GLOBRC_MxRUN_LEN,DSADC_CH_MOD_START);
  /*[cover parentID={E909A662-2CF5-40f7-ACFC-0401A7584015}]
    Enable the channel demodulator [/cover] */
  Mcal_SetBitAtomic(&MODULE_EDSADC.GLOBRC.U,HwChannelId,\
                     DSADC_GLOBRC_CHxRUN_LEN,DSADC_CH_DEMOD_START);
  /* MISRA2012_RULE_2_2_JUSTIFICATION: The variable ModulatorBitPos is used
     in the Tricore Atomic instructions,which is not detected by MISRA. Hence,
     this variable is not unused*/
}
#if((DSADC_GTMTRIGGER_USED == STD_ON) || (DSADC_ERUTRIGGER_USED == STD_ON) \
                              || (DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={2516176C-1BFF-42cc-B433-FD61A99891F3}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32 Dsadc_lGetChanNotifStatus           **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId                     **
**                    )                                                       **
** Description      : This function returns the notification enabled status   **
**                    for the channel Id                                      **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric Id of  the requested DSADC Channel  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0U:Dsadc channel notification is disabled               **
**                    1U:Dsadc channel notification is enabled                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Dsadc_lGetChanNotifStatus(const Dsadc_ChannelType ChannelId)
{
  /*[cover parentID={83522BD4-4045-4d71-9B20-F70F3F4BFEFA}]
    Get the notificaiton enabled status for the given channel[/cover] */
  return((uint32)(Mcal_GetBitAtomic(Dsadc_ChanNotifstatus,ChannelId,\
                                                 DSADC_NOTIFICATION_LEN)));
}
#endif
/*******************************************************************************
** Traceability     : [cover parentID={0E1E7422-850D-4eea-8503-C12D834B8D0B}] **
**                                                                            **
** Syntax           : static uint8 Dsadc_lHwFifoErrorHandling                 **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId                     **
**                    )                                                       **
**                                                                            **
** Description      : This function is to check HW FIFO Error and clear the   **
**                    error if it is present                                  **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric Id for the DSADC Channel            **
**                                                                            **
** Parameters (out) : None.                                                   **
**                                                                            **
** Return value     : HW FIFO Error Status                                    **
**                                                                            **
*******************************************************************************/
static uint8 Dsadc_lHwFifoErrorHandling(const Dsadc_ChannelType ChannelId)
{
  uint8 HwChannelNum;
  uint8 RetVal = DSADC_NO_FIFO_ERROR;
  uint8 DataReadMode;
  uint32 Result_FIFO_Control;

  /*Obtain the DSDAC HW channel assigned to ChannelId */
  HwChannelNum = DSADC_GET_HW_CH_NUM(ChannelId);
  /*Extract the Data read mode Configured*/
  DataReadMode = (uint8)((MODULE_EDSADC.CH[HwChannelNum].DICFG.U >>\
      IFX_EDSADC_CH_DICFG_DRM_OFF) & IFX_EDSADC_CH_DICFG_DRM_MSK);
  /*[cover parentID={4839DF52-BE83-42b6-B869-87E4F213894D}]
    Check if FIFO is used for the channel[/cover] */
  if(DataReadMode != DSADC_CH_FIFO_NOT_USED)
  {
    /* Read the Result FIFO Control Register*/
    Result_FIFO_Control = MODULE_EDSADC.CH[HwChannelNum].RFC.U;
    /*[cover parentID={14DDC8F4-8433-4826-8E6F-15A94162B675}]
      check if the Write FIFO Error set[/cover] */
    if(((Result_FIFO_Control >> IFX_EDSADC_CH_RFC_WRERR_OFF)\
         & IFX_EDSADC_CH_RFC_WRERR_MSK) == DSADC_WRITE_ERROR_CHECK)
    {     
     /* Clear the Result register FIFO Write error*/
      MODULE_EDSADC.CH[HwChannelNum].RFC.U = Result_FIFO_Control | \
       (uint32)((uint32)DSADC_CLEAR_FIFO_ERROR<< IFX_EDSADC_CH_RFC_WREC_OFF);
      /*[cover parentID={085E1727-45EB-455c-B331-0997E528C8CA}]
        Set the Return value as FIFO error[/cover] */
      RetVal = DSADC_FIFO_ERROR;
    }
    /*[cover parentID={B9EAF3E9-924C-48aa-8165-72095F2D94FE}]
      Check if the FIFO Read Error is set[/cover] */
    if(((Result_FIFO_Control >> IFX_EDSADC_CH_RFC_RDERR_OFF)\
         & IFX_EDSADC_CH_RFC_RDERR_MSK) == DSADC_READ_ERROR_CHECK)
    {
      /* Clear the Result register FIFO Write error */
      MODULE_EDSADC.CH[HwChannelNum].RFC.U = Result_FIFO_Control | \
         (uint32)((uint32)DSADC_CLEAR_FIFO_ERROR<< IFX_EDSADC_CH_RFC_RDEC_OFF);
      /*[cover parentID={4405B896-1C4C-4a4c-B1D4-9BDCDBADF50C}]
        Set the Return value as FIFO error[/cover] */
      RetVal = DSADC_FIFO_ERROR;
    }
  }
  return(RetVal);
}

#if((DSADC_GTMTRIGGER_USED == STD_ON) || (DSADC_ERUTRIGGER_USED == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={A692066C-E354-4ced-915F-ABE14DCB89CA}] **
**                                                                            **
** Syntax           : LOCAL_INLINE void Dsadc_lWindowOpenEvnt                 **
**                    (const Dsadc_ChannelType ChannelId)                     **
**                                                                            **
** Description      : This function is called when there is a window open     **
**                    Event and it changes the channel status to Busy and     **
**                    reset the Buffer.                                       **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric Id for the DSADC Channel            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Dsadc_lWindowOpenEvnt(const Dsadc_ChannelType ChannelId)
{
  /*[cover parentID={66F37A6F-4FFD-49ae-B3B2-61C88EA86126}]
    Set the Channel Status to Busy[/cover] */
  Dsadc_ChannelData[ChannelId].ChannelStatus = DSADC_BUSY;
  /*[cover parentID={63F9B263-ADF7-4287-92E3-242B9E519921}]
  Any one of the channel is not configured for DMA Access[/cover] */
  #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
  /*Set the number of valid entries to 0, so that buffer start from Beginning*/
  Dsadc_ChannelData[ChannelId].NumofValidConRes = (Dsadc_SizeType)0U;
  /*[cover parentID={34FD10DC-76ED-4119-B739-DA201F25939A}]
    Set the FIFO Error status as NO_FIFO_ERROR[/cover] */
  Dsadc_ChannelData[ChannelId].FifoErrorStatus = DSADC_NO_FIFO_ERROR;
  /*Reset the Buffer full status*/
  Dsadc_ChannelData[ChannelId].BufferFull = (uint8)0U;
  #endif
}
#endif

#if((DSADC_GTMTRIGGER_USED == STD_ON) || (DSADC_ERUTRIGGER_USED == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={4BD0486F-6A26-417b-8C0F-3C27B6B6DE77}] **
**                                                                            **
** Syntax           : LOCAL_INLINE void Dsadc_lWindowCloseEvnt                **
**                    (const Dsadc_ChannelType ChannelId)                     **
**                                                                            **
** Description      : This function is called when there is a window close    **
**                    Event and it calls the Window close notification        **
**                    function if the notification capability is set.         **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric Id for the DSADC Channel            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Dsadc_lWindowCloseEvnt(const Dsadc_ChannelType ChannelId)
{
  /*[cover parentID={BE491BAC-7B7F-409f-9D84-54D4959FE624}]
    Check if the notification is enabled for this Channel[/cover] */
  if(Dsadc_lGetChanNotifStatus(ChannelId) == (uint32)DSADC_NOTIFICATION_ENABLE)
  {
    /*[cover parentID={ECFF474C-263D-489c-BD87-8AA95BD47A6A}]
       Check if the Window close notification function pointer is not a NULL
       Pointer[/cover] */
    if (Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].\
                                          WindowCloseNotifyPtr != NULL_PTR)
    {
      /*[cover parentID={3264F736-C344-4d09-9873-BE7012945D0C}]
        Call Notification function[/cover] */
      Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].\
                                                  WindowCloseNotifyPtr();
    }
  }
  /*[cover parentID={870F3C16-F6B7-4aa4-8965-C89E666D3C7C}]
    Heal the HW FIFO Error if it is present[/cover] */
  (void)Dsadc_lHwFifoErrorHandling(ChannelId);
}
#endif

#if (DSADC_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={BC0D0566-2CEF-4961-BD65-AE1E7D2C8A1C}] **
**                                                                            **
** Syntax           : LOCAL_INLINE Std_ReturnType Dsadc_lInitCheck(void)      **
**                                                                            **
** Description      : This function checks the value of initialized global    **
**                    and channel specific SFRs with configured value         **
**                                                                            **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK: Initialization verification passed                **
**                    E_NOT_OK: Initialization verification failed            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Dsadc_lInitCheck(void)
{
  uint32 SfrVal,CfgVal;
  uint32 CompareFlag = 0xFFFFFFFFU;
  uint32 GlobrcVal = 0;
  Std_ReturnType ErrVal = E_OK;
  uint8 ChannelIndex;
  uint8 HwChannelNum;

  /*Compare Global Configuration register with configuration value & Update
    flag as per result*/
  SfrVal = MODULE_EDSADC.GLOBCFG.U;
  CfgVal = ((Dsadc_ConfigPtr->GlobalConfigReg)& \
                             (DSADC_GLOBCFG_WRITE_PROTECT_MSK));
  CompareFlag &= ~(SfrVal ^ CfgVal);

  /*Compare Carrier Generator Configuration register with configuration value
    & Update flag as per result*/
  SfrVal = ((MODULE_EDSADC.CGCFG.U) & (DSADC_CGCFG_READONLY_MSK));
  CfgVal = (Dsadc_ConfigPtr->CarrierGenConfigReg);
  CompareFlag &= ~(SfrVal ^ CfgVal);

  /*[cover parentID={5BE29855-A2C0-496e-A762-31A16905DD32}]
  any one of the Channel is configured ERU as a Trigger source[/cover] */
  #if(DSADC_ERUTRIGGER_USED == STD_ON)
  /*[cover parentID={1EB3A345-6F2D-4819-85C9-8ECEA289D564}]
    Check if any ERU ERS input channels are configured[/cover] */
  if(Dsadc_ConfigPtr->DsadcEruErsConfig != NULL_PTR)
  {
    /* Verify Initialized value for ERU-ERS Channels.*/
    CompareFlag = Dsadc_lCheckConfigErsChannels  \
                       (Dsadc_ConfigPtr->DsadcEruErsConfig,CompareFlag);
  }
  #endif

  /*Loop till the Maximum configured channel to check the channel SFR's*/
  for(ChannelIndex = 0; ChannelIndex < DSADC_MAX_CHANNELS_CONFIGURED ; \
                                                               ChannelIndex++)
  {
    /* Obtain the DSDAC HW channel assigned to ChannelId */
    HwChannelNum = DSADC_GET_HW_CH_NUM(ChannelIndex);

    /*Set the current channel Modulator and Demodulator  enable bit in the
      local variables. */
    GlobrcVal |= ((uint32)(DSADC_CH_MOD_START)<<\
                      (HwChannelNum +IFX_EDSADC_GLOBRC_CH0RUN_OFF));
    GlobrcVal |= ((uint32)(DSADC_CH_DEMOD_START)<<\
                      (HwChannelNum +IFX_EDSADC_GLOBRC_M0RUN_OFF));

    /*Compare Modulator Configuration register with configuration value
      & Update flag as per result*/
    SfrVal = ((MODULE_EDSADC.CH[HwChannelNum].MODCFG.U)& \
                                         (DSADC_MODCFG_READONLY_MSK));
    CfgVal = ((Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelIndex]. \
                   ModulatorConfigReg)&(DSADC_MODCFG_WRITE_PROTECT_MSK));
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare Demodulator Configuration register with configuration value
      & Update flag as per result*/
    SfrVal = MODULE_EDSADC.CH[HwChannelNum].DICFG.U;
    CfgVal = ((Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelIndex]. \
                  DemodulatorConfigReg)&(DSADC_DICFG_WRITE_PROTECT_MSK));
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare Common Mode Voltage Configuration register with configuration
      value & Update flag as per result*/
    SfrVal = MODULE_EDSADC.CH[HwChannelNum].VCM.U;
    CfgVal = Dsadc_ConfigPtr->DsadcChannelConfiguration  \
                                      [ChannelIndex].CommonModeVoltConfigReg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare Gain calibration register with configuration value & Update
      flag as per result*/
    SfrVal = MODULE_EDSADC.CH[HwChannelNum].GAINCAL.U;
    CfgVal = Dsadc_ConfigPtr->DsadcChannelConfiguration  \
                                          [ChannelIndex].GainCalibConfigReg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare Gain control register with configuration value & Update
      flag as per result*/
    SfrVal = MODULE_EDSADC.CH[HwChannelNum].GAINCTR.U;
    CfgVal = Dsadc_ConfigPtr->DsadcChannelConfiguration  \
                                        [ChannelIndex].GainControlConfigReg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare Gain correction register with configuration value & Update
      flag as per result*/
    SfrVal = MODULE_EDSADC.CH[HwChannelNum].GAINCORR.U;
    CfgVal = Dsadc_ConfigPtr->DsadcChannelConfiguration  \
                                           [ChannelIndex].GainCorrConfigReg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare Offset Compensation register with configuration value & Update
      flag as per result*/
    if((MODULE_EDSADC.CH[HwChannelNum].FCFGM.U &
       ((uint32)IFX_EDSADC_CH_FCFGM_OCEN_MSK << IFX_EDSADC_CH_FCFGM_OCEN_OFF))
                                                     == DSADC_OFFCOMP_DISABLED)
    {
      SfrVal = MODULE_EDSADC.CH[HwChannelNum].OFFCOMP.U;
      CfgVal = Dsadc_ConfigPtr->DsadcChannelConfiguration  \
                                           [ChannelIndex].OffsetCompConfigReg;
      CompareFlag &= ~(SfrVal ^ CfgVal);
    }

    /*Compare Integration window control register with configuration value
      & Update flag as per result*/
    SfrVal = MODULE_EDSADC.CH[HwChannelNum].IWCTR.U;
    CfgVal = Dsadc_ConfigPtr->DsadcChannelConfiguration  \
                                         [ChannelIndex].IntegratorConfigReg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare Configure filter configuration register with configuration value
      & Update flag as per result*/
    SfrVal = MODULE_EDSADC.CH[HwChannelNum].FCFGM.U;
    CfgVal = ((Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelIndex]. \
                        FilterConfigReg)&(DSADC_FCFGM_WRITE_PROTECT_MSK));
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare CIC filter configuration register with configuration value
      & Update flag as per result*/
    SfrVal = MODULE_EDSADC.CH[HwChannelNum].FCFGC.U;
    CfgVal = Dsadc_ConfigPtr->DsadcChannelConfiguration  \
                                          [ChannelIndex].CICFilterConfigReg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare Auxiliary CIC filter configuration register with configuration
      value & Update flag as per result*/
    SfrVal = ((MODULE_EDSADC.CH[HwChannelNum].FCFGA.U) & \
                                               (DSADC_FCFGA_READONLY_MSK));
    CfgVal = Dsadc_ConfigPtr->DsadcChannelConfiguration  \
                                       [ChannelIndex].AuxCICFilterConfigReg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare Time Stamp Counter register with configuration value
      & Update flag as per result*/
    SfrVal = ((MODULE_EDSADC.CH[HwChannelNum].TSCNT.U)& \
                                              (DSADC_TSCNT_READONLY_MSK));
    CfgVal = Dsadc_ConfigPtr->DsadcChannelConfiguration  \
                                          [ChannelIndex].TimeStampConfigReg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare Result register FIFO control register with configuration value
      & Update flag as per result*/
    SfrVal = ((MODULE_EDSADC.CH[HwChannelNum].RFC.U)&(DSADC_RFC_READONLY_MSK));
    CfgVal = Dsadc_ConfigPtr->DsadcChannelConfiguration  \
                                         [ChannelIndex].ResultFifoConfigReg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare Limit checking configuration register with configuration value
      & Update flag as per result*/
    SfrVal = MODULE_EDSADC.CH[HwChannelNum].BOUNDSEL.U;
    CfgVal = Dsadc_ConfigPtr->DsadcChannelConfiguration  \
                                      [ChannelIndex].LimitCheckingConfigReg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare Overshoot compensation configuration register with configuration
      value & Update flag as per result*/
    SfrVal = MODULE_EDSADC.CH[HwChannelNum].OVSCFG.U;
    CfgVal = Dsadc_ConfigPtr->DsadcChannelConfiguration  \
                                      [ChannelIndex].OvershootCompenconfigReg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare Carrier Generator Synchronization register with configuration
      value & Update flag as per result*/
    SfrVal = ((MODULE_EDSADC.CH[HwChannelNum].CGSYNC.U)& \
                                              (DSADC_CGSYNC_READONLY_MSK));
    CfgVal = Dsadc_ConfigPtr->DsadcChannelConfiguration  \
                                     [ChannelIndex].CarrierGenSyncConfigReg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare Rectification configuration register with configuration
      value & Update flag as per result*/
    SfrVal = ((MODULE_EDSADC.CH[HwChannelNum].RECTCFG.U)& \
                                          (DSADC_RECTCFG_READONLY_MSK));
    CfgVal = Dsadc_ConfigPtr->DsadcChannelConfiguration  \
                                      [ChannelIndex].RectificationConfigReg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

  }

  /*Compare GLOBRC register with the configured channel value which was updated
    in the loop and Update flag as per result*/
  SfrVal = MODULE_EDSADC.GLOBRC.U;
  CfgVal = GlobrcVal;
  CompareFlag &= ~(SfrVal ^ CfgVal);

 /* Verify Initialized values of global variables */
  CompareFlag = Dsadc_lCheckGlobalVars(CompareFlag);

  /*[cover parentID={3C6654A3-018B-4d49-8B6E-5CC6E94E825B}]
    Check if any bit is not as per configured value [/cover]*/
  if (CompareFlag != 0xFFFFFFFFU)
  {
    /* Update the return value as E_NOT_OK */
    ErrVal = E_NOT_OK;
  }
  return(ErrVal);
}
#endif

#if ((DSADC_INITCHECK_API == STD_ON) && (DSADC_ERUTRIGGER_USED == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={5E60982E-4E1D-4fda-A996-0F7F61104569}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32 Dsadc_lCheckConfigErsChannels       **
**                    (                                                       **
**                     const Dsadc_EruErsConfigType *                         **
**                                   const ErsChannelConfigPtr,               **
**                     const uint32 CompareFlag                               **
**                    )                                                       **
**                                                                            **
** Description      : This function checks the value of initialized ERU ERS   **
**                    channel specific SFRs with configured value             **
**                                                                            **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : ErsChannelConfigPtr - Pointer to the ERS channel        **
**                                          configuration Structure           **
**                    CompareFlag - Flag to compare with configured SFRs or   **
**                    Variables                                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Compare flag value - all bits as 1 indicates a pass case**
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Dsadc_lCheckConfigErsChannels(\
                     const Dsadc_EruErsConfigType * const ErsChannelConfigPtr,\
                     const uint32 CompareFlag)
{
  uint32 SfrVal,CfgVal;
  uint32 lCompareFlag = CompareFlag;
  uint8 ErsChIndex;
  uint8 ErsChNum;
  uint8 EicrChIndex;
  uint8 EicrChPos;
  /* The variable 'ErsChConfigured' is made volatile to suppress a tasking
   * compilation warning that arises from comparing
   * DSADC_MAX_ERS_CHANNELS_CONFIGURED with ErsChIndex. In the scenario none
   * of the configured DSADC channel use OGu channels for triggers,
   * DSADC_MAX_ERS_CHANNELS_CONFIGURED is set to 0. Hence a condition
   * ErsChIndex < DSADC_MAX_ERS_CHANNELS_CONFIGURED always returns false
  */
  volatile uint8 ErsChConfigured = DSADC_MAX_ERS_CHANNELS_CONFIGURED;
  /*Verify ERU-ERS SFRs for all configured ERS Channel*/
  for(ErsChIndex = 0; ErsChIndex < ErsChConfigured; ErsChIndex++)
  {
    /* Obtain the ERS input channel number*/
    ErsChNum = ErsChannelConfigPtr[ErsChIndex].ErsChannelNo;

    /* Obtain the EICR register Index by dividing the ERS channel number by 2 */
    EicrChIndex = ErsChNum >> DSADC_ONE_U;

    /* ERS Odd Channels are at bit position is 16 in EICR register.
      ERS Even Channels are at bit position is 0 in EICR register.*/
    /* Obtain the ERS Channel Position in the EICR Register */
    EicrChPos =  ((ErsChNum & DSADC_ONE_U) << DSADC_ERS_CH_EICR_SHIFT);

    /*[cover parentID={F9D528A2-88C4-45c3-AA7C-71E07C8BA135}]Compare EICR 
    register with configuration value & Update flag as per result[/cover]*/
    SfrVal = (((MODULE_SCU.EICR[EicrChIndex].U)&(DSADC_ERU_WR_MASK<<EicrChPos))\
                                                              >>EicrChPos);
    CfgVal = (uint32)ErsChannelConfigPtr[ErsChIndex].EruErsEicr;
    lCompareFlag &= ~(SfrVal ^ CfgVal);
  }
  return(lCompareFlag);
}
#endif

#if (DSADC_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={7C92690D-E1E3-42fb-99B8-9220D594DB13}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32 Dsadc_lCheckGlobalVars              **
**                    (                                                       **
                        const uint32 CompareFlag                              **
**                    )                                                       **
**                                                                            **
** Description      : This function checks the initialized value for the      **
**                    global variables                                        **
**                                                                            **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : CompareFlag - Flag to compare with configured SFRs or   **
**                    Variables                                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Compare flag value - all bits as 1 indicates a pass case**
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Dsadc_lCheckGlobalVars(const uint32 CompareFlag)
{
  uint32 GlobVal;
  uint32 DefaultVal;
  uint32 CompareFlagLoc = CompareFlag;
  uint8 ChannelId;

  /*verify the Channel specific global Variables*/
  for(ChannelId = 0; ChannelId < DSADC_MAX_CHANNELS_CONFIGURED; \
                                                          ChannelId++)
  {
    /*check if the Channel CalibrationStatus is
      DSADC_CALIBRATION_NOT_STARTED & Update flag as per result*/
    GlobVal = (uint32)Dsadc_ChannelData[ChannelId].CalibrationStatus;
    DefaultVal = (uint32)DSADC_CALIBRATION_NOT_STARTED;
    CompareFlagLoc &= ~(GlobVal ^ DefaultVal);

    /*check if the Channel status is DSADC_IDLE & Update flag as per result*/
    GlobVal = (uint32)Dsadc_ChannelData[ChannelId].ChannelStatus;
    DefaultVal = (uint32)DSADC_IDLE;
    CompareFlagLoc &= ~(GlobVal ^ DefaultVal);

    /*[cover parentID={EC57A2A3-3664-4e41-8213-F5B6B2A676CB}]
    Any one of the channel is not configured for DMA Access[/cover] */
    #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
    /*check if the NumofValidConRes is 0 & update flag
      as per the result*/
    GlobVal = (uint32)Dsadc_ChannelData[ChannelId].NumofValidConRes;
    DefaultVal = (uint32)0;
    CompareFlagLoc &= ~(GlobVal ^ DefaultVal);

    /*check if the FIFO error status is DSADC_NO_FIFO_ERROR & update flag
      as per the result*/
    GlobVal = (uint32)Dsadc_ChannelData[ChannelId].FifoErrorStatus;
    DefaultVal = (uint32)DSADC_NO_FIFO_ERROR;
    CompareFlagLoc &= ~(GlobVal ^ DefaultVal);
    #endif
  }

  /*check if Dsadc_ChanNotifStatus is 0 & Update flag as per result*/
  GlobVal = (uint32)Dsadc_ChanNotifstatus;
  DefaultVal = (uint32)0U;
  CompareFlagLoc &= ~(GlobVal ^ DefaultVal);

  /*check if Dsadc_InitStatus is DSADC_INITIALIZED & Update flag as per result*/
  GlobVal = (uint32)Dsadc_InitStatus;
  DefaultVal = (uint32)DSADC_INITIALIZED;
  CompareFlagLoc &= ~(GlobVal ^ DefaultVal);

  return(CompareFlagLoc);
}
#endif

#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={6863531F-E84A-422f-9878-4DD7AD2AF86E}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lInitDetCheck                  **
**                    (                                                       **
**                      const Dsadc_ConfigType * const ConfigPtr              **
**                    )                                                       **
**                                                                            **
** Description      : This function is to check all DET's for Dsadc_Init API. **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to DSADC configuration Set          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lInitDetCheck(const Dsadc_ConfigType * const ConfigPtr)
{
  /*Initialize the Error value as No Error */
  uint8 ErrVal = DSADC_E_NO_ERR;
  /*[cover parentID={0A57A4B4-5B7C-4ad6-B8C4-0339FB89FDCE}]
    Check if the config pointer is a NULL Pointer [/cover]*/
  if(ConfigPtr == NULL_PTR)
  {
    /*set the Error value as DSADC_E_PARAM_CONFIG*/
    ErrVal = DSADC_E_PARAM_CONFIG;
    /*[cover parentID={BDE6634B-4B78-4fba-A0BE-2B02BFDE0AED}]
      Report DSADC_E_PARAM_CONFIG DET [/cover]*/
    Dsadc_lReportError(DSADC_SID_INIT,DSADC_E_PARAM_CONFIG);
  }
  /*[cover parentID={63B4277C-A430-432e-B892-EF20C83AB56B}]
    check if the DSADC is in Initialized state[/cover]*/
  else if(Dsadc_InitStatus == DSADC_INITIALIZED)
  {  
    /* set the Error value as DSADC_E_ALREADY_INITIALIZED */
    ErrVal = DSADC_E_ALREADY_INITIALIZED;
     /*[cover parentID={91EC39B3-7C51-4cf8-9253-C80959F1EB24}]
       Report DSADC_E_ALREADY_INITIALIZED DET [/cover]*/
    Dsadc_lReportError(DSADC_SID_INIT,DSADC_E_ALREADY_INITIALIZED);
  }
  else
  {
    /*Dummy else added for MISRA.*/
  }
  return(ErrVal);
}
#endif

#if(((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON)) &&\
    (DSADC_DEINIT_API == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={5AF6DD30-43C5-4a52-B15A-F0289EDE4125}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lDeInitDetCheck(void)          **
**                                                                            **
** Description      : This function is to check all DET's for Dsadc_DeInit API**
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : void                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lDeInitDetCheck(void)
{
  /*Initialize the Error value as No Error */
  uint8 ErrVal = DSADC_E_NO_ERR;
  /*[cover parentID={38FC63B1-416C-49a3-BDE6-08E3430512D5}]
    Check if the DSADC is not in the Initialized state [/cover]*/
  if(Dsadc_InitStatus != DSADC_INITIALIZED)
  {
    /*set the Error value as DSADC_E_UNINIT*/
    ErrVal = DSADC_E_UNINIT;
    /*[cover parentID={49300FF2-85AC-4a3b-931D-3E499889FC2B}]
      Report DSADC_E_UNINIT DET [/cover]*/
    Dsadc_lReportError(DSADC_SID_DEINIT,DSADC_E_UNINIT);
  }
  return(ErrVal);
}
#endif

#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={6F9BBFCE-2B77-4a7e-B3CD-398E233C0BA0}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lStartModDetCheck              **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId                     **
**                    )                                                       **
**                                                                            **
** Description      : This function is to check all DET's for the             **
**                    Dsadc_StartModulation API.                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC channel       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lStartModDetCheck(const Dsadc_ChannelType ChannelId)
{
  uint8 ErrVal;
  uint8 HwChannelNum;
  /*[cover parentID={1B035268-5259-45d3-B6F7-A6D39066A751}]
    Check DET for UnInit[/cover]*/
  ErrVal = Dsadc_lCheckUnInitDet(DSADC_SID_START_MODULATION);
  /*[cover parentID={25AF8F83-31D0-4e6c-97FA-72B13611B2F1}]
    check if there is No Error[/cover]*/
  if(ErrVal == DSADC_E_NO_ERR)
  {
    /*[cover parentID={E5EB350E-0685-4cbc-8479-49D1C62E0586}]
     Check if DET for Channel ID[/cover]*/
    ErrVal = Dsadc_lCheckChanDet(ChannelId,DSADC_SID_START_MODULATION);
    /*[cover parentID={48ECE7A3-D526-4ed2-9172-263BA30C3768}]
      check if there is No Error[/cover]*/
    if(ErrVal == DSADC_E_NO_ERR)
    {
      /*[cover parentID={21738BDC-8F14-478e-8F2B-71CAF9E20B26}]
        Check if the Modulation is already running by checking the channel
       is not IDLE[/cover]*/
      if(Dsadc_ChannelData[ChannelId].ChannelStatus != DSADC_IDLE)
      {
        /*[cover parentID={6CD2D21D-1404-409a-8C03-3D80F49367F1}]
          Report Report DSADC_E_BUSY DET [/cover]*/
        Dsadc_lReportError(DSADC_SID_START_MODULATION,DSADC_E_BUSY);
        /* Update return value as DSADC_E_BUSY */
        ErrVal = DSADC_E_BUSY;
      }
      /*[cover parentID={FF7BB652-E9AB-4d7f-97CB-667493D6B870}]
        check if there is No Error[/cover]*/
      if(ErrVal == DSADC_E_NO_ERR)
      {
        /* Obtain the DSDAC HW channel assigned to ChannelId */
        HwChannelNum = DSADC_GET_HW_CH_NUM(ChannelId);
        /*[cover parentID={C4D10ED4-F63C-40f4-A6CE-A2CB1338AEA6}]
          check if the calibration algorithm is currently running[/cover]*/
        if((Dsadc_CalibrationStatusType)Mcal_GetBitAtomic \
                              (MODULE_EDSADC.CH[HwChannelNum].FCNTC.U, \
                              IFX_EDSADC_CH_FCNTC_CAL_OFF, \
                              IFX_EDSADC_CH_FCNTC_CAL_LEN) \
                                                  == DSADC_CALIBRATION_RUNNING)
        {
         /*[cover parentID={9FA67750-D5A1-4f14-95FF-A37A32B7A49E}]
          Report DSADC_E_CALIB_RUNNING DET  [/cover] */
          Dsadc_lReportError(DSADC_SID_START_MODULATION,DSADC_E_CALIB_RUNNING);
          /* Update return value as DSADC_E_CALIB_RUNNING */
          ErrVal = DSADC_E_CALIB_RUNNING;
        }
      }
    }
  }
 return(ErrVal);
}
#endif

#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={83CF0A8E-E53E-4541-89AC-2093E4E6A7D0}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lStopModDetCheck               **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId                     **
**                    )                                                       **
**                                                                            **
** Description      : This function is to check all DET's for the             **
**                    Dsadc_StopModulation API.                               **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC channel       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lStopModDetCheck(const Dsadc_ChannelType ChannelId)
{
  uint8 ErrVal;
  /*[cover parentID={6A4BE8F6-0A56-462e-9AEE-6467C267BC89}]
    Check DET for DSADC Driver Initialization state[/cover] */
  ErrVal = Dsadc_lCheckUnInitDet(DSADC_SID_STOP_MODULATION);
  /*[cover parentID={C12BD000-2847-4441-B6D4-D6D30C163F71}]
     check if there is No Error[/cover] */
  if(ErrVal == DSADC_E_NO_ERR)
  {
    /*[cover parentID={88BA0DB0-9F73-41b3-A0D7-3508AB80D64D}]
       Check DET for Channel ID [/cover] */
    ErrVal = Dsadc_lCheckChanDet(ChannelId,DSADC_SID_STOP_MODULATION);
  }
  return(ErrVal);
}
#endif

#if(((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON)) &&\
    (DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={0712329F-3B3B-4541-BE1E-8C8B58A3769D}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lReadStreamResDetCheck         **
**                    (                                                       **
**                       const Dsadc_ChannelType ChannelId,                   **
**                       const Dsadc_ResultType  * const ResultLinearBufferPtr**
**                    )                                                       **
**                                                                            **
** Description      : This function is to check all the DETs for              **
**                    Dsadc_ReadStreamResults API                             **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC channel       **
**                    ResultLinearBufferPtr -> Location to store the DSADC    **
**                                             channel Linear buffer.         **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lReadStreamResDetCheck(const Dsadc_ChannelType \
            ChannelId,const Dsadc_ResultType * const ResultLinearBufferPtr)
{
  uint8 ErrVal;
  /*[cover parentID={B0EC6B28-B569-400a-BF88-0040B176EC0C}]
    Check DET for DSADC Driver Initialization state[/cover] */
  ErrVal = Dsadc_lCheckUnInitDet(DSADC_SID_READ_STREAM_RESULTS);
  /*[cover parentID={CC92A540-219B-4ef7-948F-4B85DDF0BC02}]
    check if there is No Error[/cover] */
  if(ErrVal == DSADC_E_NO_ERR)
  {
    /*[cover parentID={09FC26BF-E9E4-4e88-962A-5FD5CAEDC59A}]
      Check DET for Parameter Pointer[/cover] */
    ErrVal = Dsadc_lCheckParamPointerDet(ResultLinearBufferPtr,\
                                              DSADC_SID_READ_STREAM_RESULTS);
    /*[cover parentID={DC1ACE3B-F5D1-45e4-AEB2-0CD387C23F58}]                                          
      check if there is No Error[/cover] */
    if(ErrVal == DSADC_E_NO_ERR)
    {
      /*[cover parentID={A7F0159E-C4E1-4093-95FC-F6436924E180}] 
        Check DET for Channel ID[/cover] */
      ErrVal = Dsadc_lCheckChanDet(ChannelId,DSADC_SID_READ_STREAM_RESULTS);
      /*[cover parentID={D32CADF9-F6C3-4b8a-A6D9-5902D6A4C799}] 
        check if there is No Error[/cover] */
      if(ErrVal == DSADC_E_NO_ERR)
      {
        /*[cover parentID={8231F987-B4F5-49f6-8B23-84163A881077}] 
          Check DET for valid Pointer range[/cover] */
        ErrVal = Dsadc_lCheckBufferPointerDet(ChannelId,ResultLinearBufferPtr,\
                                         DSADC_SID_READ_STREAM_RESULTS);
      }
    }
  }
  return(ErrVal);
}
#endif

#if(((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON)) &&\
    (DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={6B574A7E-E7B5-4446-A7BA-E09C6469A053}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lReadResultCheck               **
**                    (                                                       **
**                     const Dsadc_ChannelType ChannelId ,                    **
**                     const Dsadc_ResultType * const ResultPtr               **
**                    )                                                       **
**                                                                            **
** Description      : This function is to check all the DETs for              **
**                    Dsadc_ReadResult API                                    **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC channel       **
**                    ResultPtr - Memory Location where the Result will be    **
**                                stored.                                     **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lReadResultDetCheck(const Dsadc_ChannelType       \
                         ChannelId,const Dsadc_ResultType * const ResultPtr)
{
  uint8 ErrVal;
  /*[cover parentID={55DD85D1-F7C4-48f4-B5F9-BDAFA66BBD8D}]
    Check DET for UnInit[/cover] */
  ErrVal = Dsadc_lCheckUnInitDet(DSADC_SID_READ_RESULT);
  /*[cover parentID={228D6633-D46B-4a47-A15F-92D6D0615F17}]
    check if there is No Error[/cover] */
  if(ErrVal == DSADC_E_NO_ERR)
  {
    /*[cover parentID={F6AF1455-2D8E-44f2-A822-884971800600}]
      Check DET for Channel ID[/cover] */
    ErrVal = Dsadc_lCheckChanDet(ChannelId, DSADC_SID_READ_RESULT);
    /*[cover parentID={923B9A0A-052A-4183-98E4-ECE482321E4B}]
      check if there is No Error[/cover] */
    if(ErrVal == DSADC_E_NO_ERR)
    {
      /*[cover parentID={00E48668-939F-446a-8B63-E6D6BDFC1379}]
        Check DET for Parameter Pointer[/cover] */
      ErrVal = Dsadc_lCheckParamPointerDet(ResultPtr,DSADC_SID_READ_RESULT);
      /*[cover parentID={15473CE7-9FDD-4eaa-BDC9-AEBA33F55DDE}]
        check if there is No Error[/cover] */
      if(ErrVal == DSADC_E_NO_ERR)
      {
        /*[cover parentID={DEA7544C-F048-47f2-BB8B-FCA2B1B79E82}]
          Check if the access mode is configured as Circular Buffer[/cover] */
        if(Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].AccessMode \
                                                     == DSADC_CIRCULAR_BUFFER)
        {
          /*[cover parentID={11F8AC89-9254-4e58-A8D3-7FE2D5AE295C}]
            Check DET for valid Pointer range[/cover] */
          ErrVal = Dsadc_lCheckBufferPointerDet(ChannelId,ResultPtr,\
                                                   DSADC_SID_READ_RESULT);
        }
      }
    }
  }
  return(ErrVal);
}
#endif

#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={D147435E-662D-4e6f-ABB3-93EB6D31571E}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lGetStatusDetCheck             **
**                    (                                                       **
**                     const Dsadc_ChannelType ChannelId)                     **
**                    )                                                       **
**                                                                            **
** Description      : This function is to check all the DETs for              **
**                    Dsadc_GetStatus API                                     **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC channel       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lGetStatusDetCheck(const Dsadc_ChannelType ChannelId)
{
  uint8 ErrVal;
  /*[cover parentID={3C7ACF06-56A3-48fe-A0E6-A5FB626C924B}]
    Check DET for UnInit[/cover] */
  ErrVal = Dsadc_lCheckUnInitDet(DSADC_SID_GET_STATUS);
  /*[cover parentID={0FE6F4E3-7AAA-454b-BF20-FC470BC64DFF}]
    check if there is No Error[/cover] */
  if(ErrVal == DSADC_E_NO_ERR)
  {
    /*[cover parentID={255CEF60-2050-456f-83D3-B7EB9F6AAD24}]
      Check DET for Channel Number[/cover] */
    ErrVal = Dsadc_lCheckChanDet(ChannelId, DSADC_SID_GET_STATUS);
  }
  return(ErrVal);
}
#endif

#if(((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON)) &&\
    (DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={CCB1B8F8-CC98-4461-9228-4DD9DB906682}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lSetupResBufDetCheck           **
**                    (                                                       **
**                       const Dsadc_ChannelType ChannelId,                   **
**                       const Dsadc_ResultType * const DataBufferPtr         **
**                    )                                                       **
**                                                                            **
** Description      : This function is to check all the DETs for              **
**                    Dsadc_SetupResultBuffer  API                            **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC channel       **
**                    DataBufferPtr -> Pointer to the Result data buffer      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lSetupResBufDetCheck( \
 const Dsadc_ChannelType ChannelId,const Dsadc_ResultType * const DataBufferPtr)
{
  uint8 ErrVal;
  /*[cover parentID={3F2081DB-BA36-490a-8FAE-903F7A3FCF1B}]
    Check DET for DSADC Driver Initialization state[/cover] */
  ErrVal = Dsadc_lCheckUnInitDet(DSADC_SID_SETUP_RESULT_BUFFER);
  /*[cover parentID={7DE04B00-7D81-4fde-92E6-E1FB948FADED}]
    check if there is No Error[/cover] */
  if(ErrVal == DSADC_E_NO_ERR)
  {
    /*[cover parentID={BF56E535-643C-47d4-A0D6-ADC273D6814E}]
      check DET for Parameter pointer[/cover] */
    ErrVal = Dsadc_lCheckParamPointerDet(DataBufferPtr,\
                                     DSADC_SID_SETUP_RESULT_BUFFER);
    /*[cover parentID={0BF34051-7CAE-492c-BFEF-2CC4999ABB07}]
      check if there is No Error[/cover] */
    if(ErrVal == DSADC_E_NO_ERR)
    {
      /*[cover parentID={5500D8DC-1925-47f1-B402-CA7BBA14A7A5}]
        Check DET for Channel ID[/cover] */
      ErrVal = Dsadc_lCheckChanDet(ChannelId,DSADC_SID_SETUP_RESULT_BUFFER);
    }
  }
  return(ErrVal);
}
#endif

#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={65D262FC-ED79-44cf-941B-EED83B71C5BA}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lStartCarrSigDetCheck(void)    **
**                                                                            **
** Description      : This function is to check all the DETs for              **
**                    Dsadc_StartCarrierSignal API                            **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                              **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lStartCarrSigDetCheck(void)
{
  uint8 ErrVal;
  /*[cover parentID={6E481238-0390-44b6-9D4C-3D1DCC57DE85}]
    Check DET for UnInit[/cover]*/
  ErrVal = Dsadc_lCheckUnInitDet(DSADC_SID_START_CARRIER_SIGNAL);
  /*[cover parentID={E6E30D8D-416F-4463-AA83-8BFD1C9C7DA8}]
    Check If there is No Error[/cover]*/
  if(ErrVal == DSADC_E_NO_ERR)
  {
    /*[cover parentID={32D5A3A9-862C-4f5b-BB47-436F8D8D8C93}]
      Check if the Carrier Signal already running[/cover]*/
    if(Mcal_GetBitAtomic(MODULE_EDSADC.CGCFG.U,IFX_EDSADC_CGCFG_RUN_OFF,  \
                       IFX_EDSADC_CGCFG_RUN_LEN) == DSADC_CARR_SIG_RUN)
    {
      /*[cover parentID={6BE89CF1-F3BB-4f30-8F6F-FC1A6972DECF}]
        Report DSADC_E_CARRIER_ALREADY_RUNNING DET [/cover]*/
      Dsadc_lReportError(DSADC_SID_START_CARRIER_SIGNAL, \
                    DSADC_E_CARRIER_ALREADY_RUNNING);
      /*Set the error Value as DSADC_E_CARRIER_ALREADY_RUNNING*/
      ErrVal = DSADC_E_CARRIER_ALREADY_RUNNING;
    }
  }
  return(ErrVal);
}
#endif

#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={31A1D33B-8D67-49ff-B923-DC02BEB6DAD1}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lStopCarrSigDetCheck(void)     **
**                                                                            **
** Description      : This function is to check all the DETs for              **
**                    Dsadc_StopCarrierSignal API                             **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                              **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lStopCarrSigDetCheck(void)
{
  uint8 ErrVal;
  /*[cover parentID={F42D81CB-C46B-44df-99F8-9CE473689C64}]
    Check DET for UnInit[/cover]*/
  ErrVal = Dsadc_lCheckUnInitDet(DSADC_SID_STOP_CARRIER_SIGNAL);
  return(ErrVal);
}
#endif

#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={D84DD278-F50A-43e1-8F9A-F9AAA8BFB838}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lEnNotifDetCheck               **
**                    (                                                       **
**                     const Dsadc_ChannelType ChannelId                      **
**                    )                                                       **
**                                                                            **
** Description      : This function is to check all the DETs for              **
 **                   Dsadc_EnableNotifications API                           **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC channel       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lEnNotifDetCheck(const Dsadc_ChannelType ChannelId)
{
  uint8 ErrVal;
  /*[cover parentID={BB15E941-0EF8-4145-ACF0-ED0D14185781}]
    Check DET for DSADC Driver Initialization state[/cover]*/
  ErrVal = Dsadc_lCheckUnInitDet(DSADC_SID_ENABLE_NOTIFICATIONS);
  /*[cover parentID={0D45193D-958B-4539-825C-FB69B64B21B5}]
    check if there is No Error[/cover]*/
  if(ErrVal == DSADC_E_NO_ERR)
  {
    /*[cover parentID={5A1735B6-E5C7-4fae-9C87-B428DEB2D293}]
      Check DET for Channel ID[/cover]*/
    ErrVal = Dsadc_lCheckChanDet(ChannelId, DSADC_SID_ENABLE_NOTIFICATIONS);
    /*[cover parentID={A8A0B6EB-28E4-4edb-A711-794D15036846}]
      check if there is No Error[/cover]*/
    if(ErrVal == DSADC_E_NO_ERR)
    {
      /*[cover parentID={EB3A13CF-CFC7-4462-B2AD-B27C67B7BF11}]
        Check DET for notification capability[/cover]*/
      ErrVal = Dsadc_lCheckNotifCapableDet(ChannelId,\
                                            DSADC_SID_ENABLE_NOTIFICATIONS);
    }
  }
  return(ErrVal);
}
#endif

#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={AB509BB8-4017-41f8-B52B-90F29E430B7A}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lDisNotifDetCheck              **
**                    (                                                       **
**                     const Dsadc_ChannelType ChannelId                      **
**                    )                                                       **
**                                                                            **
** Description      : This function is to check all the DETs for              **
**                    Dsadc_DisableNotification API                           **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                              **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC channel       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lDisNotifDetCheck(const Dsadc_ChannelType ChannelId)
{
  uint8 ErrVal;
  /*[cover parentID={D21D4F07-0038-46d4-A3CF-1B3F518ED691}]
    Check DET for DSADC Driver Initialization state[/cover]*/
  ErrVal = Dsadc_lCheckUnInitDet(DSADC_SID_DISABLE_NOTIFICATIONS);
  /*[cover parentID={B3749748-E602-4631-9850-C6A2BDEB034A}]
    check if there is No Error[/cover]*/
  if(ErrVal == DSADC_E_NO_ERR)
  {
    /*[cover parentID={F8FB2621-D623-460e-88EC-904967A6C0D1}]
      Check DET for Channel ID[/cover]*/
    ErrVal = Dsadc_lCheckChanDet(ChannelId, DSADC_SID_DISABLE_NOTIFICATIONS);
    /*[cover parentID={C8A5730A-A2FF-451c-B462-BD38F3384344}]
      check if there is No Error[/cover]*/
    if(ErrVal == DSADC_E_NO_ERR)
    {
      /*[cover parentID={320D3113-C2B9-4a9e-98F6-C59C2DC9B711}]
        Check DET for notification capability[/cover]*/
      ErrVal = Dsadc_lCheckNotifCapableDet(ChannelId,\
                                            DSADC_SID_DISABLE_NOTIFICATIONS);
    }
  }
  return(ErrVal);
}
#endif

#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={1EE197F5-26B0-4329-9B51-78BB2D3C64CD}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lGetTimestampDetCheck          **
**                    (                                                       **
**                       const Dsadc_ChannelType ChannelId                    **
**                    )                                                       **
**                                                                            **
** Description      : This function is to check all the DETs for              **
**                    Dsadc_GetTimestamp API                                  **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                              **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC channel       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lGetTimestampDetCheck( \
                                       const Dsadc_ChannelType ChannelId)
{
  uint8 ErrVal;
  /*[cover parentID={338DA52F-95D1-4673-9B68-4B8D11C11469}]
    Check DET for DSADC Driver Initialization state[/cover]*/
  ErrVal = Dsadc_lCheckUnInitDet(DSADC_SID_GET_TIMESTAMP);
  /*[cover parentID={01F372B3-BC3E-4d14-878B-DA810D6272B4}]
    check if there is No Error[/cover]*/
  if(ErrVal == DSADC_E_NO_ERR)
  {
    /*[cover parentID={34B34555-18BE-4e9d-A26E-25E4F52E7A04}]
      Check DET for Channel ID[/cover]*/
    ErrVal = Dsadc_lCheckChanDet(ChannelId,DSADC_SID_GET_TIMESTAMP);
  }
  return(ErrVal);
}
#endif

#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={C4E8A7A6-25CC-46f8-B530-AA2E173F96FC}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lStartCalibDetCheck            **
**                    (                                                       **
**                       const Dsadc_ChannelType ChannelId                    **
**                    )                                                       **
**                                                                            **
** Description      : This function is to check all the DETs for              **
**                    Dsadc_StartCalibration API                              **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC channel       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lStartCalibDetCheck(const Dsadc_ChannelType ChannelId)
{
  uint8 ErrVal;
  uint8 HwChannelNum;
  /*[cover parentID={33885AC0-110D-4b44-975C-7C90229CFF78}]
    Check DET for DSADC Driver Initialization state[/cover]*/
  ErrVal = Dsadc_lCheckUnInitDet(DSADC_SID_START_CALIBRATION);
  /*[cover parentID={E5C2B7AF-9866-4bea-B391-92D1E9FAEAED}]
    check if there is No Error[/cover] */
  if(ErrVal == DSADC_E_NO_ERR)
  {
    /*[cover parentID={1ABC7A4E-CDB9-4820-824D-BD4E65E817A2}]
      Check DET for Channel ID[/cover] */
    ErrVal = Dsadc_lCheckChanDet(ChannelId,DSADC_SID_START_CALIBRATION);
    /*[cover parentID={A5459343-90A2-4986-85E9-1996C8D44728}]
      check if there is No Error[/cover] */
    if(ErrVal == DSADC_E_NO_ERR)
    {
      /* Obtain the DSDAC HW channel assigned to ChannelId */
      HwChannelNum = DSADC_GET_HW_CH_NUM(ChannelId);
      /*[cover parentID={67502FD8-7C58-4bd0-BEE6-4C2BD89B9913}]
        check if the calibration status is already running[/cover] */
      if((Dsadc_CalibrationStatusType)Mcal_GetBitAtomic \
                            (MODULE_EDSADC.CH[HwChannelNum].FCNTC.U, \
                            IFX_EDSADC_CH_FCNTC_CAL_OFF, \
                            IFX_EDSADC_CH_FCNTC_CAL_LEN) \
                                                == DSADC_CALIBRATION_RUNNING)
      {
        /*[cover parentID={A6A25FAF-1AE8-4e24-9F75-EC317376D602}]
        Report DSADC_E_CALIB_RUNNING DET  [/cover] */
        Dsadc_lReportError(DSADC_SID_START_CALIBRATION, \
                                                DSADC_E_CALIB_RUNNING);
        /* Update return value as DSADC_E_CALIB_RUNNING */
        ErrVal = DSADC_E_CALIB_RUNNING;
      }
    }
  }
  return(ErrVal);
}
#endif

#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={8A13AB05-5D45-4993-867E-C0CBC1E13882}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lGetCalibStatusDetCheck        **
**                    (                                                       **
**                       const Dsadc_ChannelType ChannelId,                   **
**                    )                                                       **
**                                                                            **
** Description      : This function is to check all the DETs for              **
**                    Dsadc_GetCalibrationStatus  API                         **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC channel       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lGetCalibStatusDetCheck(\
                                             const Dsadc_ChannelType ChannelId)
{
  uint8 ErrVal;
  /*[cover parentID={AB207A52-853A-4415-849C-B0A8E057048B}]
    Check DET for DSADC Driver Initialization state[/cover] */
  ErrVal = Dsadc_lCheckUnInitDet(DSADC_SID_GET_CALIBRATION_STATUS);
  /*[cover parentID={4853BBB7-1DC4-453a-94EA-8B275BE00779}]
    check if there is No Error[/cover] */
  if(ErrVal == DSADC_E_NO_ERR)
  {
    /*[cover parentID={D929676B-D3A2-4559-87AA-892FBC9C3812}]
      Check DET for Channel ID[/cover] */
    ErrVal = Dsadc_lCheckChanDet(ChannelId,DSADC_SID_GET_CALIBRATION_STATUS);
  }
  return(ErrVal);
}
#endif

#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={75526B47-3B80-46fe-8816-47A54124E84F}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lCheckUnInitDet                **
**                    (                                                       **
**                      const uint8 ServiceId                                 **
**                    )                                                       **
**                                                                            **
** Description      : This function is to check DSADC_E_UNINIT DET for the    **
**                    ServiceId(API).                                         **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ServiceId - Service ID of the API                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lCheckUnInitDet(const uint8 ServiceId)
{
  uint8 ErrVal = DSADC_E_NO_ERR;
  /*[cover parentID={AA7214B4-42CD-42ea-845D-E063D79E1BFB}]
    Check if the Dsadc is not in Initialized state or Dsadc config pointer
    is equal to NULL pointer[/cover] */
  if((Dsadc_InitStatus != DSADC_INITIALIZED) ||
      (Dsadc_ConfigPtr == NULL_PTR))
  {
    /*[cover parentID={894FD586-9B76-47dc-B511-CDB4179E5F99}]
      Report DSADC_E_UNINIT DET [/cover]*/
    Dsadc_lReportError(ServiceId,DSADC_E_UNINIT);
    /* Update return value as DSADC_E_UNINIT */
    ErrVal = DSADC_E_UNINIT;
  }
  return(ErrVal);
}
#endif

#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={D920EF7B-7F14-4042-A532-37D066FD16AF}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lCheckChanDet                  **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId,                    **
**                      const uint8 ServiceId                                 **
**                    )                                                       **
**                                                                            **
** Description      : This function is to check the channel number validity   **
**                    and report error if it is invalid                       **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC channel       **
**                    ServiceId - Service ID of the API                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lCheckChanDet(const Dsadc_ChannelType ChannelId,
                                                         const uint8 ServiceId)
{
  uint8 ErrVal = DSADC_E_NO_ERR;
  /*[cover parentID={162371F0-0A40-4fbf-8B66-CEF1079FA341}]
    Check if the channel Id greater than the maximum channel Configured 
  [/cover]*/
  if(ChannelId >= DSADC_MAX_CHANNELS_CONFIGURED)
  {
    /*[cover parentID={2DC51A39-CDE0-40f7-AE3E-A7FCADB16114}]
      Report DSADC_E_PARAM_CHANNEL DET [/cover]*/
    Dsadc_lReportError(ServiceId,DSADC_E_PARAM_CHANNEL);
    /* Update return value as DSADC_E_PARAM_CHANNEL */
    ErrVal = DSADC_E_PARAM_CHANNEL;
  }
 return(ErrVal);
}
#endif

#if(((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))&& \
    ((DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON) || \
    (DSADC_VERSION_INFO_API == STD_ON)))
/*******************************************************************************
** Traceability     : [cover parentID={AD2504AE-3A6B-4f79-89F4-1B0B970C2EE2}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lCheckParamPointerDet          **
**                    (                                                       **
**                      const void *const DataPtr                             **
**                      const uint8 ServiceId                                 **
**                    )                                                       **
**                                                                            **
** Description      : This function is to check DSADC_E_PARAM_POINTER DET for **
**                    the ServiceId(API).                                     **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : DataPtr - Parameter Pointer                             **
**                    ServiceId - Service ID of the API                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lCheckParamPointerDet(const void * const DataPtr,\
                                                       const uint8 ServiceId)
{
  uint8 ErrVal = DSADC_E_NO_ERR;
  /*[cover parentID={2FDAA2CA-A296-4d59-AFC4-2C105FB32B01}]
    Received pointer is equal to NULL Pointer [/cover]*/
  if(NULL_PTR == DataPtr)
  {
    /*[cover parentID={558A1B69-3CE8-4382-9846-46B150A28CA0}]
      Report DSADC_E_PARAM_POINTER DET [/cover]*/
    Dsadc_lReportError(ServiceId,DSADC_E_PARAM_POINTER);
    /*Update return value as DSADC_E_PARAM_POINTER*/
    ErrVal = DSADC_E_PARAM_POINTER;
  }
  return(ErrVal);
}
#endif

#if(((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON)) && \
    (DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={289300EF-3A05-478f-914B-BED5D791713E}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lCheckBufferPointerDet         **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId,                    **
**                      const Dsadc_ResultType *const DataPtr,                **
**                      const uint8 ServiceId                                 **
**                    )                                                       **
**                                                                            **
** Description      : This function is to check DSADC_E_INVALID_BUFFER_POINTER**
**                    for the ServiceId(API).                                 **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : DataPtr - Parameter Pointer                             **
**                    ServiceId - Service ID of the API                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lCheckBufferPointerDet(const Dsadc_ChannelType \
       ChannelId, const Dsadc_ResultType * const DataPtr,const uint8 ServiceId)
{
 Dsadc_SizeType BufferSizeLocal;
 uint8 ErrVal = DSADC_E_NO_ERR;
 /* Read the Size of the Buffer */
 BufferSizeLocal = Dsadc_ChannelData[ChannelId].ChannelBufferSize;
 /*[cover parentID={BE3E6CDB-FC13-4396-A681-35D8988B30F5}]
   Check if the access mode is configured as Linear Buffer[/cover]*/
 if(Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].AccessMode \
                                                  == DSADC_STREAM_LINEAR_BUFFER)
 {
   /*[cover parentID={9CE339F4-BB5E-4b29-849F-5B6DBDD8F030}]
   check if the address of Received pointer is within the channel buffer range
   [/cover]*/
   /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
   Calculate the end address of the Buffer. Validated and no side effects are
   foreseen */
   /* MISRA2012_RULE_18_2_JUSTIFICATION: Buffer address comparison is used to
   identify the Result buffer range within the channel buffer range.
   Validated and no side effects are foreseen  */
   /* MISRA2012_RULE_18_3_JUSTIFICATION: Buffer address comparison is used to
   identify the Result buffer range within the channel buffer range.
   Validated and no side effects are foreseen  */
  if(((DataPtr >= Dsadc_ChannelData[ChannelId].ChannelResBuffer) && (DataPtr <=\
    (Dsadc_ChannelData[ChannelId].ChannelResBuffer + BufferSizeLocal))) || \
   (((DataPtr + BufferSizeLocal) >= Dsadc_ChannelData[ChannelId]. \
     ChannelResBuffer)&&((DataPtr + BufferSizeLocal) <= \
     (Dsadc_ChannelData[ChannelId].ChannelResBuffer+BufferSizeLocal))))
  {
    /*[cover parentID={3E781183-5C81-49fb-B1FD-0899D244F982}]
      Report DSADC_E_INVALID_BUFFER_POINTER DET [/cover]*/
    Dsadc_lReportError(ServiceId,DSADC_E_INVALID_BUFFER_POINTER);
    /*Update return value as DSADC_E_INVALID_BUFFER_POINTER*/
    ErrVal = DSADC_E_INVALID_BUFFER_POINTER;
  }
 }
 /*[cover parentID={8ED362F9-3B0C-4f47-9EFE-90F61CF72CED}]
   Check if the access mode is configured as Circular Buffer[/cover]*/
 else if(Dsadc_ConfigPtr->DsadcChannelConfiguration[ChannelId].AccessMode \
                                                 == DSADC_CIRCULAR_BUFFER)
 {
   /*[cover parentID={003FB7CA-F93C-4d22-9214-9F5AA7ECCD37}]
   check if the address of Received pointer is within the channel buffer range
  [/cover]*/
  /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
  Calculate the end address of the Buffer. Validated and no side effects are
  foreseen */
  /* MISRA2012_RULE_18_2_JUSTIFICATION: Buffer address comparison is used to
  identify the Result buffer range within the channel buffer range.
  Validated and no side effects are foreseen  */
  /* MISRA2012_RULE_18_3_JUSTIFICATION: Buffer address comparison is used to
  identify the Result buffer range within the channel buffer range.
  Validated and no side effects are foreseen  */
  if((DataPtr >= Dsadc_ChannelData[ChannelId].ChannelResBuffer) && (DataPtr <=\
      (Dsadc_ChannelData[ChannelId].ChannelResBuffer + BufferSizeLocal)))

  {
  /*[cover parentID={CFD5B2C0-0D7E-43d7-9B21-B7A7B4871359}]
    Report DSADC_E_INVALID_BUFFER_POINTER DET [/cover]*/
  Dsadc_lReportError(ServiceId,DSADC_E_INVALID_BUFFER_POINTER);
  /*Update return value as DSADC_E_INVALID_BUFFER_POINTER*/
  ErrVal = DSADC_E_INVALID_BUFFER_POINTER;
  }
 }
 else
 {
   /* Dummy else*/
 }
  return(ErrVal);
}
#endif

#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={FB893660-00A6-42f0-A5D9-73B30317B8DB}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Dsadc_lCheckNotifCapableDet          **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId,                    **
**                      const uint8 ServiceId                                 **
**                    )                                                       **
**                                                                            **
** Description      : This function is to check DSADC_E_NOTIF_CAPABILITY DET  **
**                    for the ServiceId(API).                                 **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC channel       **
**                    ServiceId - Service ID of the API                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Dsadc_lCheckNotifCapableDet(const Dsadc_ChannelType\
                                            ChannelId,const uint8 ServiceId)
{
  uint8 ErrVal = DSADC_E_NO_ERR;
  Dsadc_NotifyFnPtrType NotificationFnBuffFull;
  Dsadc_NotifyFnPtrType NotificationFnWindowClose;
  Dsadc_NotifyFnPtrType NotificationFnNewResult;

  /* Read the Bufferfull Notification function pointer from the
     configuration pointer */
  NotificationFnBuffFull = Dsadc_ConfigPtr->DsadcChannelConfiguration \
                                       [ChannelId].BufferFullNotifyPtr;
  /* Read the Window Close Notification function pointer from the
     configuration pointer */
  NotificationFnWindowClose = Dsadc_ConfigPtr->DsadcChannelConfiguration \
                                       [ChannelId].WindowCloseNotifyPtr;
  /* Read the New Result Notification function pointer from the
     configuration pointer */
  NotificationFnNewResult = Dsadc_ConfigPtr->DsadcChannelConfiguration \
                                       [ChannelId].NewResultNotifyPtr;
  /*[cover parentID={8520707A-4833-4169-B60B-C81DAED6BFF2}]
    check if all the Notification function pointer is NULL[/cover]*/
  if(((Dsadc_NotifyFnPtrType)0U == NotificationFnBuffFull) && \
      ((Dsadc_NotifyFnPtrType)0U == NotificationFnWindowClose) && \
      ((Dsadc_NotifyFnPtrType)0U == NotificationFnNewResult))
  {
    /*[cover parentID={20BD6AC8-DFBB-40d7-ADB5-6DD0CFC49EF3}]
      Report DSADC_E_NOTIF_CAPABILITY DET [/cover]*/
    Dsadc_lReportError(ServiceId,DSADC_E_NOTIF_CAPABILITY);
    /* Update return value as DSADC_E_NOTIF_CAPABILITY */
    ErrVal = DSADC_E_NOTIF_CAPABILITY;
  }
  return(ErrVal);
}
#endif

#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={7376D822-EC25-4675-BD3C-F76FBAFBFA35}] **
**                                                                            **
** Syntax           : LOCAL_INLINE void Dsadc_lReportError                    **
**                    (                                                       **
**                      const uint8 ServiceId,const uint8 ErrorId)            **
**                    )                                                       **
**                                                                            **
** Description      : Function to report Safety Error and DET                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : ServiceId - Service ID of the API                       **
**                    ErrorId - ID of the error reported                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*                                                                             **
*******************************************************************************/
LOCAL_INLINE void Dsadc_lReportError(const uint8 ServiceId, const uint8 ErrorId)
{
  /*[cover parentID={586F35AD-4983-45c1-8F46-D72BE32F403A}]
  DET is ON [/cover]*/
  #if (DSADC_DEV_ERROR_DETECT == STD_ON)
  /*[cover parentID={530EDAF3-CF9E-4850-AC49-B16773683F3E}]
  Report development error [/cover]*/
  Det_ReportError(DSADC_MODULE_ID,DSADC_MODULE_INSTANCE,ServiceId,ErrorId);
  #endif
  /*[cover parentID={DFE0E5DB-77FB-4066-89BF-C35341B5F2D4}]
  SAFETY is ON [/cover]*/
  #if (DSADC_SAFETY_ENABLE == STD_ON)
  /*[cover parentID={E82E7EAE-0FA0-4879-831E-864BF4434E3D},
     {195D68C6-4A20-4283-AC6D-3F272A43EC47}]
    Report Safety Error [/cover]*/
  Mcal_ReportSafetyError(DSADC_MODULE_ID,DSADC_MODULE_INSTANCE, \
                          ServiceId,ErrorId);
  #endif
}
#endif

/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
Callout Memory section not used in DSADC driver
[/cover]*/
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Code Memory section naming as per AS [/cover]*/

/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
const data memory section is not used in DSADC driver
[/cover]*/

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define DSADC_STOP_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline.*/
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
  without safegaurd. It complies to Autosar guidelines. */
#include "Dsadc_MemMap.h"
