/**
 * \file IfxDmu_reg.h
 * \brief
 * \copyright Copyright (c) 2020 Infineon Technologies AG. All rights reserved.
 *
 *
 * Version: TC33X32X_UM_V1.4.0.R0
 * Specification: TC3xx User Manual.V1.4.0
 * MAY BE CHANGED BY USER [yes/no]: No
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Use of this file is subject to the terms of use agreed between (i) you or 
 * the company in which ordinary course of business you are acting and (ii) 
 * Infineon Technologies AG or its licensees. If and as long as no such 
 * terms of use are agreed, use of this file is subject to following:


 * Boost Software License - Version 1.0 - August 17th, 2003

 * Permission is hereby granted, free of charge, to any person or 
 * organization obtaining a copy of the software and accompanying 
 * documentation covered by this license (the "Software") to use, reproduce,
 * display, distribute, execute, and transmit the Software, and to prepare
 * derivative works of the Software, and to permit third-parties to whom the 
 * Software is furnished to do so, all subject to the following:

 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE 
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * \defgroup IfxSfr_Dmu_Registers_Cfg Dmu address
 * \ingroup IfxSfr_Dmu_Registers
 * 
 * \defgroup IfxSfr_Dmu_Registers_Cfg_BaseAddress Base address
 * \ingroup IfxSfr_Dmu_Registers_Cfg
 *
 * \defgroup IfxSfr_Dmu_Registers_Cfg_Dmu 2-DMU
 * \ingroup IfxSfr_Dmu_Registers_Cfg
 *
 *
 */
#ifndef IFXDMU_REG_H
#define IFXDMU_REG_H 1
/******************************************************************************/
#include "IfxDmu_regdef.h"
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/

/** \addtogroup IfxSfr_Dmu_Registers_Cfg_BaseAddress
 * \{  */

/** \brief DMU object */
#define MODULE_DMU /*lint --e(923, 9078)*/ ((*(Ifx_DMU*)0xF8040000u))
/** \}  */


/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxSfr_Dmu_Registers_Cfg_Dmu
 * \{  */
/** \brief 8, Module Identification Register */
#define DMU_HF_ID /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_ID*)0xF8040008u)

/** \brief 10, Flash Status Register */
#define DMU_HF_STATUS /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_STATUS*)0xF8040010u)

/** \brief 14, Flash Control Register */
#define DMU_HF_CONTROL /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_CONTROL*)0xF8040014u)

/** \brief 18, Flash Operation Register */
#define DMU_HF_OPERATION /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_OPERATION*)0xF8040018u)

/** \brief 1C, Flash Protection Status Register */
#define DMU_HF_PROTECT /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_PROTECT*)0xF804001Cu)

/** \brief 20, Flash Confirm Status Register 0 */
#define DMU_HF_CONFIRM0 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_CONFIRM0*)0xF8040020u)

/** \brief 24, Flash Confirm Status Register 1 */
#define DMU_HF_CONFIRM1 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_CONFIRM1*)0xF8040024u)

/** \brief 28, Flash Confirm Status Register 2 */
#define DMU_HF_CONFIRM2 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_CONFIRM2*)0xF8040028u)

/** \brief 30, Enable Error Interrupt Control Register */
#define DMU_HF_EER /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_EER*)0xF8040030u)

/** \brief 34, Error Status Register */
#define DMU_HF_ERRSR /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_ERRSR*)0xF8040034u)

/** \brief 38, Clear Error Register */
#define DMU_HF_CLRE /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_CLRE*)0xF8040038u)

/** \brief 40, DF0 ECC Read Register */
#define DMU_HF_ECCR /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_ECCR*)0xF8040040u)

/** \brief 44, DF0 ECC Status Register */
#define DMU_HF_ECCS /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_ECCS*)0xF8040044u)

/** \brief 48, DF0 ECC Control Register */
#define DMU_HF_ECCC /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_ECCC*)0xF8040048u)

/** \brief 4C, DF0 ECC Write Register */
#define DMU_HF_ECCW /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_ECCW*)0xF804004Cu)

/** \brief 50, Cranking Control Register */
#define DMU_HF_CCONTROL /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_CCONTROL*)0xF8040050u)

/** \brief 60, Power Status Register */
#define DMU_HF_PSTATUS /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_PSTATUS*)0xF8040060u)

/** \brief 64, Power Control Register */
#define DMU_HF_PCONTROL /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_PCONTROL*)0xF8040064u)

/** \brief 68, PFLASH Wait Cycle Register */
#define DMU_HF_PWAIT /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_PWAIT*)0xF8040068u)

/** \brief 6C, DFLASH Wait Cycle Register */
#define DMU_HF_DWAIT /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_DWAIT*)0xF804006Cu)

/** \brief 74, DF0 User Mode Control */
#define DMU_HF_PROCONUSR /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_PROCONUSR*)0xF8040074u)

/** \brief 80, PFLASH Protection Configuration */
#define DMU_HF_PROCONPF /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_PROCONPF*)0xF8040080u)

/** \brief 84, Tuning Protection Configuration */
#define DMU_HF_PROCONTP /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_PROCONTP*)0xF8040084u)

/** \brief 88, DFLASH Protection Configuration */
#define DMU_HF_PROCONDF /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_PROCONDF*)0xF8040088u)

/** \brief 8C, RAM Configuration */
#define DMU_HF_PROCONRAM /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_PROCONRAM*)0xF804008Cu)

/** \brief 90, Debug Interface Protection Configuration */
#define DMU_HF_PROCONDBG /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_PROCONDBG*)0xF8040090u)

/** \brief F0, Suspend Control Register */
#define DMU_HF_SUSPEND /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_SUSPEND*)0xF80400F0u)

/** \brief F4, Margin Control Register */
#define DMU_HF_MARGIN /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_MARGIN*)0xF80400F4u)

/** \brief F8, Access Enable Register 1 */
#define DMU_HF_ACCEN1 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_ACCEN1*)0xF80400F8u)

/** \brief FC, Access Enable Register 0 */
#define DMU_HF_ACCEN0 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HF_ACCEN0*)0xF80400FCu)

/** \brief 10000, PFLASH Bank 0 Protection Configuration 0 */
#define DMU_HP0_PROCON_P0 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_P0*)0xF8050000u)
/** Alias (User Manual Name) for DMU_HP0_PROCON_P0.
* To use register names with standard convension, please use DMU_HP0_PROCON_P0.
*/
#define DMU_HP_PROCONP00 (DMU_HP0_PROCON_P0)

/** \brief 10004, PFLASH Bank 0 Protection Configuration 1 */
#define DMU_HP0_PROCON_P1 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_P1*)0xF8050004u)
/** Alias (User Manual Name) for DMU_HP0_PROCON_P1.
* To use register names with standard convension, please use DMU_HP0_PROCON_P1.
*/
#define DMU_HP_PROCONP01 (DMU_HP0_PROCON_P1)

/** \brief 10008, PFLASH Bank 0 Protection Configuration 2 */
#define DMU_HP0_PROCON_P2 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_P2*)0xF8050008u)
/** Alias (User Manual Name) for DMU_HP0_PROCON_P2.
* To use register names with standard convension, please use DMU_HP0_PROCON_P2.
*/
#define DMU_HP_PROCONP02 (DMU_HP0_PROCON_P2)

/** \brief 1000C, PFLASH Bank 0 Protection Configuration 3 */
#define DMU_HP0_PROCON_P3 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_P3*)0xF805000Cu)
/** Alias (User Manual Name) for DMU_HP0_PROCON_P3.
* To use register names with standard convension, please use DMU_HP0_PROCON_P3.
*/
#define DMU_HP_PROCONP03 (DMU_HP0_PROCON_P3)

/** \brief 10010, PFLASH Bank 0 Protection Configuration 4 */
#define DMU_HP0_PROCON_P4 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_P4*)0xF8050010u)
/** Alias (User Manual Name) for DMU_HP0_PROCON_P4.
* To use register names with standard convension, please use DMU_HP0_PROCON_P4.
*/
#define DMU_HP_PROCONP04 (DMU_HP0_PROCON_P4)

/** \brief 10014, PFLASH Bank 0 Protection Configuration 5 */
#define DMU_HP0_PROCON_P5 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_P5*)0xF8050014u)
/** Alias (User Manual Name) for DMU_HP0_PROCON_P5.
* To use register names with standard convension, please use DMU_HP0_PROCON_P5.
*/
#define DMU_HP_PROCONP05 (DMU_HP0_PROCON_P5)

/** \brief 10040, PFLASH Bank 0 OTP Protection Configuration 0 */
#define DMU_HP0_PROCON_OTP0 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_OTP0*)0xF8050040u)
/** Alias (User Manual Name) for DMU_HP0_PROCON_OTP0.
* To use register names with standard convension, please use DMU_HP0_PROCON_OTP0.
*/
#define DMU_HP_PROCONOTP00 (DMU_HP0_PROCON_OTP0)

/** \brief 10044, PFLASH Bank 0 OTP Protection Configuration 1 */
#define DMU_HP0_PROCON_OTP1 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_OTP1*)0xF8050044u)
/** Alias (User Manual Name) for DMU_HP0_PROCON_OTP1.
* To use register names with standard convension, please use DMU_HP0_PROCON_OTP1.
*/
#define DMU_HP_PROCONOTP01 (DMU_HP0_PROCON_OTP1)

/** \brief 10048, PFLASH Bank 0 OTP Protection Configuration 2 */
#define DMU_HP0_PROCON_OTP2 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_OTP2*)0xF8050048u)
/** Alias (User Manual Name) for DMU_HP0_PROCON_OTP2.
* To use register names with standard convension, please use DMU_HP0_PROCON_OTP2.
*/
#define DMU_HP_PROCONOTP02 (DMU_HP0_PROCON_OTP2)

/** \brief 1004C, PFLASH Bank 0 OTP Protection Configuration 3 */
#define DMU_HP0_PROCON_OTP3 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_OTP3*)0xF805004Cu)
/** Alias (User Manual Name) for DMU_HP0_PROCON_OTP3.
* To use register names with standard convension, please use DMU_HP0_PROCON_OTP3.
*/
#define DMU_HP_PROCONOTP03 (DMU_HP0_PROCON_OTP3)

/** \brief 10050, PFLASH Bank 0 OTP Protection Configuration 4 */
#define DMU_HP0_PROCON_OTP4 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_OTP4*)0xF8050050u)
/** Alias (User Manual Name) for DMU_HP0_PROCON_OTP4.
* To use register names with standard convension, please use DMU_HP0_PROCON_OTP4.
*/
#define DMU_HP_PROCONOTP04 (DMU_HP0_PROCON_OTP4)

/** \brief 10054, PFLASH Bank 0 OTP Protection Configuration 5 */
#define DMU_HP0_PROCON_OTP5 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_OTP5*)0xF8050054u)
/** Alias (User Manual Name) for DMU_HP0_PROCON_OTP5.
* To use register names with standard convension, please use DMU_HP0_PROCON_OTP5.
*/
#define DMU_HP_PROCONOTP05 (DMU_HP0_PROCON_OTP5)

/** \brief 10080, PFLASH Bank 0 WOP Configuration 0 */
#define DMU_HP0_PROCON_WOP0 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_WOP0*)0xF8050080u)
/** Alias (User Manual Name) for DMU_HP0_PROCON_WOP0.
* To use register names with standard convension, please use DMU_HP0_PROCON_WOP0.
*/
#define DMU_HP_PROCONWOP00 (DMU_HP0_PROCON_WOP0)

/** \brief 10084, PFLASH Bank 0 WOP Configuration 1 */
#define DMU_HP0_PROCON_WOP1 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_WOP1*)0xF8050084u)
/** Alias (User Manual Name) for DMU_HP0_PROCON_WOP1.
* To use register names with standard convension, please use DMU_HP0_PROCON_WOP1.
*/
#define DMU_HP_PROCONWOP01 (DMU_HP0_PROCON_WOP1)

/** \brief 10088, PFLASH Bank 0 WOP Configuration 2 */
#define DMU_HP0_PROCON_WOP2 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_WOP2*)0xF8050088u)
/** Alias (User Manual Name) for DMU_HP0_PROCON_WOP2.
* To use register names with standard convension, please use DMU_HP0_PROCON_WOP2.
*/
#define DMU_HP_PROCONWOP02 (DMU_HP0_PROCON_WOP2)

/** \brief 1008C, PFLASH Bank 0 WOP Configuration 3 */
#define DMU_HP0_PROCON_WOP3 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_WOP3*)0xF805008Cu)
/** Alias (User Manual Name) for DMU_HP0_PROCON_WOP3.
* To use register names with standard convension, please use DMU_HP0_PROCON_WOP3.
*/
#define DMU_HP_PROCONWOP03 (DMU_HP0_PROCON_WOP3)

/** \brief 10090, PFLASH Bank 0 WOP Configuration 4 */
#define DMU_HP0_PROCON_WOP4 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_WOP4*)0xF8050090u)
/** Alias (User Manual Name) for DMU_HP0_PROCON_WOP4.
* To use register names with standard convension, please use DMU_HP0_PROCON_WOP4.
*/
#define DMU_HP_PROCONWOP04 (DMU_HP0_PROCON_WOP4)

/** \brief 10094, PFLASH Bank 0 WOP Configuration 5 */
#define DMU_HP0_PROCON_WOP5 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_PROCON_WOP5*)0xF8050094u)
/** Alias (User Manual Name) for DMU_HP0_PROCON_WOP5.
* To use register names with standard convension, please use DMU_HP0_PROCON_WOP5.
*/
#define DMU_HP_PROCONWOP05 (DMU_HP0_PROCON_WOP5)

/** \brief 100A0, PFLASH Bank 0 Erase Counter Priority configuration 0 */
#define DMU_HP0_ECPRIO_P0 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_ECPRIO_P0*)0xF80500A0u)
/** Alias (User Manual Name) for DMU_HP0_ECPRIO_P0.
* To use register names with standard convension, please use DMU_HP0_ECPRIO_P0.
*/
#define DMU_HP_ECPRIO00 (DMU_HP0_ECPRIO_P0)

/** \brief 100A4, PFLASH Bank 0 Erase Counter Priority Configuration 1 */
#define DMU_HP0_ECPRIO_P1 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_ECPRIO_P1*)0xF80500A4u)
/** Alias (User Manual Name) for DMU_HP0_ECPRIO_P1.
* To use register names with standard convension, please use DMU_HP0_ECPRIO_P1.
*/
#define DMU_HP_ECPRIO01 (DMU_HP0_ECPRIO_P1)

/** \brief 100A8, PFLASH Bank 0 Erase Counter Priority Configuration 2 */
#define DMU_HP0_ECPRIO_P2 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_ECPRIO_P2*)0xF80500A8u)
/** Alias (User Manual Name) for DMU_HP0_ECPRIO_P2.
* To use register names with standard convension, please use DMU_HP0_ECPRIO_P2.
*/
#define DMU_HP_ECPRIO02 (DMU_HP0_ECPRIO_P2)

/** \brief 100AC, PFLASH Bank 0 Erase Counter Priority Configuration 3 */
#define DMU_HP0_ECPRIO_P3 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_ECPRIO_P3*)0xF80500ACu)
/** Alias (User Manual Name) for DMU_HP0_ECPRIO_P3.
* To use register names with standard convension, please use DMU_HP0_ECPRIO_P3.
*/
#define DMU_HP_ECPRIO03 (DMU_HP0_ECPRIO_P3)

/** \brief 100B0, PFLASH Bank 0 Erase Counter Priority Configuration 4 */
#define DMU_HP0_ECPRIO_P4 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_ECPRIO_P4*)0xF80500B0u)
/** Alias (User Manual Name) for DMU_HP0_ECPRIO_P4.
* To use register names with standard convension, please use DMU_HP0_ECPRIO_P4.
*/
#define DMU_HP_ECPRIO04 (DMU_HP0_ECPRIO_P4)

/** \brief 100B4, PFLASH Bank 0 Erase Counter Priority Configuration 5 */
#define DMU_HP0_ECPRIO_P5 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_HP_ECPRIO_P5*)0xF80500B4u)
/** Alias (User Manual Name) for DMU_HP0_ECPRIO_P5.
* To use register names with standard convension, please use DMU_HP0_ECPRIO_P5.
*/
#define DMU_HP_ECPRIO05 (DMU_HP0_ECPRIO_P5)

/** \brief 20010, HSM Flash Status Register */
#define DMU_SF_STATUS /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SF_STATUS*)0xF8060010u)

/** \brief 20014, HSM Flash Configuration Register */
#define DMU_SF_CONTROL /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SF_CONTROL*)0xF8060014u)

/** \brief 20018, HSM Flash Operation Register */
#define DMU_SF_OPERATION /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SF_OPERATION*)0xF8060018u)

/** \brief 20030, HSM Enable Error Interrupt Control Register */
#define DMU_SF_EER /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SF_EER*)0xF8060030u)

/** \brief 20034, HSM Error Status Register */
#define DMU_SF_ERRSR /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SF_ERRSR*)0xF8060034u)

/** \brief 20038, HSM Clear Error Register */
#define DMU_SF_CLRE /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SF_CLRE*)0xF8060038u)

/** \brief 20040, HSM DF1 ECC Read Register */
#define DMU_SF_ECCR /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SF_ECCR*)0xF8060040u)

/** \brief 20044, HSM DF1 ECC Status Register */
#define DMU_SF_ECCS /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SF_ECCS*)0xF8060044u)

/** \brief 20048, HSM DF1 ECC Control Register */
#define DMU_SF_ECCC /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SF_ECCC*)0xF8060048u)

/** \brief 2004C, HSM DF1 ECC Write Register */
#define DMU_SF_ECCW /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SF_ECCW*)0xF806004Cu)

/** \brief 20074, HSM DF1 User Mode Control */
#define DMU_SF_PROCONUSR /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SF_PROCONUSR*)0xF8060074u)

/** \brief 200E8, HSM Suspend Control Register */
#define DMU_SF_SUSPEND /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SF_SUSPEND*)0xF80600E8u)

/** \brief 200EC, HSM DF1 Margin Control Register */
#define DMU_SF_MARGIN /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SF_MARGIN*)0xF80600ECu)

/** \brief 30000, HSM Protection Configuration */
#define DMU_SP_PROCONHSMCFG /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SP_PROCONHSMCFG*)0xF8070000u)

/** \brief 30004, HSM Code Boot Sector */
#define DMU_SP_PROCONHSMCBS /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SP_PROCONHSMCBS*)0xF8070004u)

/** \brief 30008, HSM Code Exclusive Protection Configuration */
#define DMU_SP_PROCONHSMCX0 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SP_PROCONHSMCX0*)0xF8070008u)

/** \brief 3000C, HSM Code Exclusive Protection Configuration */
#define DMU_SP_PROCONHSMCX1 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SP_PROCONHSMCX1*)0xF807000Cu)

/** \brief 30010, HSM Code OTP Protection Configuration */
#define DMU_SP_PROCONHSMCOTP0 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SP_PROCONHSMCOTP0*)0xF8070010u)

/** \brief 30014, HSM Code OTP Protection Configuration */
#define DMU_SP_PROCONHSMCOTP1 /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SP_PROCONHSMCOTP1*)0xF8070014u)

/** \brief 30040, HSM Interface Protection Configuration */
#define DMU_SP_PROCONHSM /*lint --e(923, 9078)*/ (*(volatile Ifx_DMU_SP_PROCONHSM*)0xF8070040u)


/** \}  */

/******************************************************************************/

/******************************************************************************/

#endif /* IFXDMU_REG_H */