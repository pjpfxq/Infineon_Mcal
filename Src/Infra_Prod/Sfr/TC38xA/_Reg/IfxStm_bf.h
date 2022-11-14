/**
 * \file IfxStm_bf.h
 * \brief
 * \copyright Copyright (c) 2020 Infineon Technologies AG. All rights reserved.
 *
 *
 * Version: TC38XA_UM_V1.4.0.R0
 * Specification: TC3xx User Manual V1.4.0
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
 * \defgroup IfxSfr_Stm_Registers_BitfieldsMask Bitfields mask and offset
 * \ingroup IfxSfr_Stm_Registers
 * 
 */
#ifndef IFXSTM_BF_H
#define IFXSTM_BF_H 1

/******************************************************************************/

/******************************************************************************/

/** \addtogroup IfxSfr_Stm_Registers_BitfieldsMask
 * \{  */
/** \brief Length for Ifx_STM_CLC_Bits.DISR */
#define IFX_STM_CLC_DISR_LEN (1u)

/** \brief Mask for Ifx_STM_CLC_Bits.DISR */
#define IFX_STM_CLC_DISR_MSK (0x1u)

/** \brief Offset for Ifx_STM_CLC_Bits.DISR */
#define IFX_STM_CLC_DISR_OFF (0u)

/** \brief Length for Ifx_STM_CLC_Bits.DISS */
#define IFX_STM_CLC_DISS_LEN (1u)

/** \brief Mask for Ifx_STM_CLC_Bits.DISS */
#define IFX_STM_CLC_DISS_MSK (0x1u)

/** \brief Offset for Ifx_STM_CLC_Bits.DISS */
#define IFX_STM_CLC_DISS_OFF (1u)

/** \brief Length for Ifx_STM_CLC_Bits.EDIS */
#define IFX_STM_CLC_EDIS_LEN (1u)

/** \brief Mask for Ifx_STM_CLC_Bits.EDIS */
#define IFX_STM_CLC_EDIS_MSK (0x1u)

/** \brief Offset for Ifx_STM_CLC_Bits.EDIS */
#define IFX_STM_CLC_EDIS_OFF (3u)

/** \brief Length for Ifx_STM_ID_Bits.MODREV */
#define IFX_STM_ID_MODREV_LEN (8u)

/** \brief Mask for Ifx_STM_ID_Bits.MODREV */
#define IFX_STM_ID_MODREV_MSK (0xffu)

/** \brief Offset for Ifx_STM_ID_Bits.MODREV */
#define IFX_STM_ID_MODREV_OFF (0u)

/** \brief Length for Ifx_STM_ID_Bits.MODTYPE */
#define IFX_STM_ID_MODTYPE_LEN (8u)

/** \brief Mask for Ifx_STM_ID_Bits.MODTYPE */
#define IFX_STM_ID_MODTYPE_MSK (0xffu)

/** \brief Offset for Ifx_STM_ID_Bits.MODTYPE */
#define IFX_STM_ID_MODTYPE_OFF (8u)

/** \brief Length for Ifx_STM_ID_Bits.MODNUM */
#define IFX_STM_ID_MODNUM_LEN (16u)

/** \brief Mask for Ifx_STM_ID_Bits.MODNUM */
#define IFX_STM_ID_MODNUM_MSK (0xffffu)

/** \brief Offset for Ifx_STM_ID_Bits.MODNUM */
#define IFX_STM_ID_MODNUM_OFF (16u)

/** \brief Length for Ifx_STM_TIM0_Bits.STM_31_0 */
#define IFX_STM_TIM0_STM_31_0_LEN (32u)

/** \brief Mask for Ifx_STM_TIM0_Bits.STM_31_0 */
#define IFX_STM_TIM0_STM_31_0_MSK (0xffffffffu)

/** \brief Offset for Ifx_STM_TIM0_Bits.STM_31_0 */
#define IFX_STM_TIM0_STM_31_0_OFF (0u)

/** \brief Length for Ifx_STM_TIM1_Bits.STM_35_4 */
#define IFX_STM_TIM1_STM_35_4_LEN (32u)

/** \brief Mask for Ifx_STM_TIM1_Bits.STM_35_4 */
#define IFX_STM_TIM1_STM_35_4_MSK (0xffffffffu)

/** \brief Offset for Ifx_STM_TIM1_Bits.STM_35_4 */
#define IFX_STM_TIM1_STM_35_4_OFF (0u)

/** \brief Length for Ifx_STM_TIM2_Bits.STM_39_8 */
#define IFX_STM_TIM2_STM_39_8_LEN (32u)

/** \brief Mask for Ifx_STM_TIM2_Bits.STM_39_8 */
#define IFX_STM_TIM2_STM_39_8_MSK (0xffffffffu)

/** \brief Offset for Ifx_STM_TIM2_Bits.STM_39_8 */
#define IFX_STM_TIM2_STM_39_8_OFF (0u)

/** \brief Length for Ifx_STM_TIM3_Bits.STM_43_12 */
#define IFX_STM_TIM3_STM_43_12_LEN (32u)

/** \brief Mask for Ifx_STM_TIM3_Bits.STM_43_12 */
#define IFX_STM_TIM3_STM_43_12_MSK (0xffffffffu)

/** \brief Offset for Ifx_STM_TIM3_Bits.STM_43_12 */
#define IFX_STM_TIM3_STM_43_12_OFF (0u)

/** \brief Length for Ifx_STM_TIM4_Bits.STM_47_16 */
#define IFX_STM_TIM4_STM_47_16_LEN (32u)

/** \brief Mask for Ifx_STM_TIM4_Bits.STM_47_16 */
#define IFX_STM_TIM4_STM_47_16_MSK (0xffffffffu)

/** \brief Offset for Ifx_STM_TIM4_Bits.STM_47_16 */
#define IFX_STM_TIM4_STM_47_16_OFF (0u)

/** \brief Length for Ifx_STM_TIM5_Bits.STM_51_20 */
#define IFX_STM_TIM5_STM_51_20_LEN (32u)

/** \brief Mask for Ifx_STM_TIM5_Bits.STM_51_20 */
#define IFX_STM_TIM5_STM_51_20_MSK (0xffffffffu)

/** \brief Offset for Ifx_STM_TIM5_Bits.STM_51_20 */
#define IFX_STM_TIM5_STM_51_20_OFF (0u)

/** \brief Length for Ifx_STM_TIM6_Bits.STM_63_32 */
#define IFX_STM_TIM6_STM_63_32_LEN (32u)

/** \brief Mask for Ifx_STM_TIM6_Bits.STM_63_32 */
#define IFX_STM_TIM6_STM_63_32_MSK (0xffffffffu)

/** \brief Offset for Ifx_STM_TIM6_Bits.STM_63_32 */
#define IFX_STM_TIM6_STM_63_32_OFF (0u)

/** \brief Length for Ifx_STM_CAP_Bits.STMCAP_63_32 */
#define IFX_STM_CAP_STMCAP_63_32_LEN (32u)

/** \brief Mask for Ifx_STM_CAP_Bits.STMCAP_63_32 */
#define IFX_STM_CAP_STMCAP_63_32_MSK (0xffffffffu)

/** \brief Offset for Ifx_STM_CAP_Bits.STMCAP_63_32 */
#define IFX_STM_CAP_STMCAP_63_32_OFF (0u)

/** \brief Length for Ifx_STM_CMP_Bits.CMPVAL */
#define IFX_STM_CMP_CMPVAL_LEN (32u)

/** \brief Mask for Ifx_STM_CMP_Bits.CMPVAL */
#define IFX_STM_CMP_CMPVAL_MSK (0xffffffffu)

/** \brief Offset for Ifx_STM_CMP_Bits.CMPVAL */
#define IFX_STM_CMP_CMPVAL_OFF (0u)

/** \brief Length for Ifx_STM_CMCON_Bits.MSIZE0 */
#define IFX_STM_CMCON_MSIZE0_LEN (5u)

/** \brief Mask for Ifx_STM_CMCON_Bits.MSIZE0 */
#define IFX_STM_CMCON_MSIZE0_MSK (0x1fu)

/** \brief Offset for Ifx_STM_CMCON_Bits.MSIZE0 */
#define IFX_STM_CMCON_MSIZE0_OFF (0u)

/** \brief Length for Ifx_STM_CMCON_Bits.MSTART0 */
#define IFX_STM_CMCON_MSTART0_LEN (5u)

/** \brief Mask for Ifx_STM_CMCON_Bits.MSTART0 */
#define IFX_STM_CMCON_MSTART0_MSK (0x1fu)

/** \brief Offset for Ifx_STM_CMCON_Bits.MSTART0 */
#define IFX_STM_CMCON_MSTART0_OFF (8u)

/** \brief Length for Ifx_STM_CMCON_Bits.MSIZE1 */
#define IFX_STM_CMCON_MSIZE1_LEN (5u)

/** \brief Mask for Ifx_STM_CMCON_Bits.MSIZE1 */
#define IFX_STM_CMCON_MSIZE1_MSK (0x1fu)

/** \brief Offset for Ifx_STM_CMCON_Bits.MSIZE1 */
#define IFX_STM_CMCON_MSIZE1_OFF (16u)

/** \brief Length for Ifx_STM_CMCON_Bits.MSTART1 */
#define IFX_STM_CMCON_MSTART1_LEN (5u)

/** \brief Mask for Ifx_STM_CMCON_Bits.MSTART1 */
#define IFX_STM_CMCON_MSTART1_MSK (0x1fu)

/** \brief Offset for Ifx_STM_CMCON_Bits.MSTART1 */
#define IFX_STM_CMCON_MSTART1_OFF (24u)

/** \brief Length for Ifx_STM_ICR_Bits.CMP0EN */
#define IFX_STM_ICR_CMP0EN_LEN (1u)

/** \brief Mask for Ifx_STM_ICR_Bits.CMP0EN */
#define IFX_STM_ICR_CMP0EN_MSK (0x1u)

/** \brief Offset for Ifx_STM_ICR_Bits.CMP0EN */
#define IFX_STM_ICR_CMP0EN_OFF (0u)

/** \brief Length for Ifx_STM_ICR_Bits.CMP0IR */
#define IFX_STM_ICR_CMP0IR_LEN (1u)

/** \brief Mask for Ifx_STM_ICR_Bits.CMP0IR */
#define IFX_STM_ICR_CMP0IR_MSK (0x1u)

/** \brief Offset for Ifx_STM_ICR_Bits.CMP0IR */
#define IFX_STM_ICR_CMP0IR_OFF (1u)

/** \brief Length for Ifx_STM_ICR_Bits.CMP0OS */
#define IFX_STM_ICR_CMP0OS_LEN (1u)

/** \brief Mask for Ifx_STM_ICR_Bits.CMP0OS */
#define IFX_STM_ICR_CMP0OS_MSK (0x1u)

/** \brief Offset for Ifx_STM_ICR_Bits.CMP0OS */
#define IFX_STM_ICR_CMP0OS_OFF (2u)

/** \brief Length for Ifx_STM_ICR_Bits.CMP1EN */
#define IFX_STM_ICR_CMP1EN_LEN (1u)

/** \brief Mask for Ifx_STM_ICR_Bits.CMP1EN */
#define IFX_STM_ICR_CMP1EN_MSK (0x1u)

/** \brief Offset for Ifx_STM_ICR_Bits.CMP1EN */
#define IFX_STM_ICR_CMP1EN_OFF (4u)

/** \brief Length for Ifx_STM_ICR_Bits.CMP1IR */
#define IFX_STM_ICR_CMP1IR_LEN (1u)

/** \brief Mask for Ifx_STM_ICR_Bits.CMP1IR */
#define IFX_STM_ICR_CMP1IR_MSK (0x1u)

/** \brief Offset for Ifx_STM_ICR_Bits.CMP1IR */
#define IFX_STM_ICR_CMP1IR_OFF (5u)

/** \brief Length for Ifx_STM_ICR_Bits.CMP1OS */
#define IFX_STM_ICR_CMP1OS_LEN (1u)

/** \brief Mask for Ifx_STM_ICR_Bits.CMP1OS */
#define IFX_STM_ICR_CMP1OS_MSK (0x1u)

/** \brief Offset for Ifx_STM_ICR_Bits.CMP1OS */
#define IFX_STM_ICR_CMP1OS_OFF (6u)

/** \brief Length for Ifx_STM_ISCR_Bits.CMP0IRR */
#define IFX_STM_ISCR_CMP0IRR_LEN (1u)

/** \brief Mask for Ifx_STM_ISCR_Bits.CMP0IRR */
#define IFX_STM_ISCR_CMP0IRR_MSK (0x1u)

/** \brief Offset for Ifx_STM_ISCR_Bits.CMP0IRR */
#define IFX_STM_ISCR_CMP0IRR_OFF (0u)

/** \brief Length for Ifx_STM_ISCR_Bits.CMP0IRS */
#define IFX_STM_ISCR_CMP0IRS_LEN (1u)

/** \brief Mask for Ifx_STM_ISCR_Bits.CMP0IRS */
#define IFX_STM_ISCR_CMP0IRS_MSK (0x1u)

/** \brief Offset for Ifx_STM_ISCR_Bits.CMP0IRS */
#define IFX_STM_ISCR_CMP0IRS_OFF (1u)

/** \brief Length for Ifx_STM_ISCR_Bits.CMP1IRR */
#define IFX_STM_ISCR_CMP1IRR_LEN (1u)

/** \brief Mask for Ifx_STM_ISCR_Bits.CMP1IRR */
#define IFX_STM_ISCR_CMP1IRR_MSK (0x1u)

/** \brief Offset for Ifx_STM_ISCR_Bits.CMP1IRR */
#define IFX_STM_ISCR_CMP1IRR_OFF (2u)

/** \brief Length for Ifx_STM_ISCR_Bits.CMP1IRS */
#define IFX_STM_ISCR_CMP1IRS_LEN (1u)

/** \brief Mask for Ifx_STM_ISCR_Bits.CMP1IRS */
#define IFX_STM_ISCR_CMP1IRS_MSK (0x1u)

/** \brief Offset for Ifx_STM_ISCR_Bits.CMP1IRS */
#define IFX_STM_ISCR_CMP1IRS_OFF (3u)

/** \brief Length for Ifx_STM_TIM0SV_Bits.STM_31_0 */
#define IFX_STM_TIM0SV_STM_31_0_LEN (32u)

/** \brief Mask for Ifx_STM_TIM0SV_Bits.STM_31_0 */
#define IFX_STM_TIM0SV_STM_31_0_MSK (0xffffffffu)

/** \brief Offset for Ifx_STM_TIM0SV_Bits.STM_31_0 */
#define IFX_STM_TIM0SV_STM_31_0_OFF (0u)

/** \brief Length for Ifx_STM_CAPSV_Bits.STMCAP_63_32 */
#define IFX_STM_CAPSV_STMCAP_63_32_LEN (32u)

/** \brief Mask for Ifx_STM_CAPSV_Bits.STMCAP_63_32 */
#define IFX_STM_CAPSV_STMCAP_63_32_MSK (0xffffffffu)

/** \brief Offset for Ifx_STM_CAPSV_Bits.STMCAP_63_32 */
#define IFX_STM_CAPSV_STMCAP_63_32_OFF (0u)

/** \brief Length for Ifx_STM_OCS_Bits.SUS */
#define IFX_STM_OCS_SUS_LEN (4u)

/** \brief Mask for Ifx_STM_OCS_Bits.SUS */
#define IFX_STM_OCS_SUS_MSK (0xfu)

/** \brief Offset for Ifx_STM_OCS_Bits.SUS */
#define IFX_STM_OCS_SUS_OFF (24u)

/** \brief Length for Ifx_STM_OCS_Bits.SUS_P */
#define IFX_STM_OCS_SUS_P_LEN (1u)

/** \brief Mask for Ifx_STM_OCS_Bits.SUS_P */
#define IFX_STM_OCS_SUS_P_MSK (0x1u)

/** \brief Offset for Ifx_STM_OCS_Bits.SUS_P */
#define IFX_STM_OCS_SUS_P_OFF (28u)

/** \brief Length for Ifx_STM_OCS_Bits.SUSSTA */
#define IFX_STM_OCS_SUSSTA_LEN (1u)

/** \brief Mask for Ifx_STM_OCS_Bits.SUSSTA */
#define IFX_STM_OCS_SUSSTA_MSK (0x1u)

/** \brief Offset for Ifx_STM_OCS_Bits.SUSSTA */
#define IFX_STM_OCS_SUSSTA_OFF (29u)

/** \brief Length for Ifx_STM_KRSTCLR_Bits.CLR */
#define IFX_STM_KRSTCLR_CLR_LEN (1u)

/** \brief Mask for Ifx_STM_KRSTCLR_Bits.CLR */
#define IFX_STM_KRSTCLR_CLR_MSK (0x1u)

/** \brief Offset for Ifx_STM_KRSTCLR_Bits.CLR */
#define IFX_STM_KRSTCLR_CLR_OFF (0u)

/** \brief Length for Ifx_STM_KRST1_Bits.RST */
#define IFX_STM_KRST1_RST_LEN (1u)

/** \brief Mask for Ifx_STM_KRST1_Bits.RST */
#define IFX_STM_KRST1_RST_MSK (0x1u)

/** \brief Offset for Ifx_STM_KRST1_Bits.RST */
#define IFX_STM_KRST1_RST_OFF (0u)

/** \brief Length for Ifx_STM_KRST0_Bits.RST */
#define IFX_STM_KRST0_RST_LEN (1u)

/** \brief Mask for Ifx_STM_KRST0_Bits.RST */
#define IFX_STM_KRST0_RST_MSK (0x1u)

/** \brief Offset for Ifx_STM_KRST0_Bits.RST */
#define IFX_STM_KRST0_RST_OFF (0u)

/** \brief Length for Ifx_STM_KRST0_Bits.RSTSTAT */
#define IFX_STM_KRST0_RSTSTAT_LEN (1u)

/** \brief Mask for Ifx_STM_KRST0_Bits.RSTSTAT */
#define IFX_STM_KRST0_RSTSTAT_MSK (0x1u)

/** \brief Offset for Ifx_STM_KRST0_Bits.RSTSTAT */
#define IFX_STM_KRST0_RSTSTAT_OFF (1u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN0 */
#define IFX_STM_ACCEN0_EN0_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN0 */
#define IFX_STM_ACCEN0_EN0_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN0 */
#define IFX_STM_ACCEN0_EN0_OFF (0u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN1 */
#define IFX_STM_ACCEN0_EN1_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN1 */
#define IFX_STM_ACCEN0_EN1_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN1 */
#define IFX_STM_ACCEN0_EN1_OFF (1u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN2 */
#define IFX_STM_ACCEN0_EN2_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN2 */
#define IFX_STM_ACCEN0_EN2_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN2 */
#define IFX_STM_ACCEN0_EN2_OFF (2u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN3 */
#define IFX_STM_ACCEN0_EN3_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN3 */
#define IFX_STM_ACCEN0_EN3_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN3 */
#define IFX_STM_ACCEN0_EN3_OFF (3u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN4 */
#define IFX_STM_ACCEN0_EN4_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN4 */
#define IFX_STM_ACCEN0_EN4_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN4 */
#define IFX_STM_ACCEN0_EN4_OFF (4u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN5 */
#define IFX_STM_ACCEN0_EN5_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN5 */
#define IFX_STM_ACCEN0_EN5_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN5 */
#define IFX_STM_ACCEN0_EN5_OFF (5u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN6 */
#define IFX_STM_ACCEN0_EN6_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN6 */
#define IFX_STM_ACCEN0_EN6_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN6 */
#define IFX_STM_ACCEN0_EN6_OFF (6u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN7 */
#define IFX_STM_ACCEN0_EN7_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN7 */
#define IFX_STM_ACCEN0_EN7_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN7 */
#define IFX_STM_ACCEN0_EN7_OFF (7u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN8 */
#define IFX_STM_ACCEN0_EN8_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN8 */
#define IFX_STM_ACCEN0_EN8_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN8 */
#define IFX_STM_ACCEN0_EN8_OFF (8u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN9 */
#define IFX_STM_ACCEN0_EN9_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN9 */
#define IFX_STM_ACCEN0_EN9_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN9 */
#define IFX_STM_ACCEN0_EN9_OFF (9u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN10 */
#define IFX_STM_ACCEN0_EN10_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN10 */
#define IFX_STM_ACCEN0_EN10_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN10 */
#define IFX_STM_ACCEN0_EN10_OFF (10u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN11 */
#define IFX_STM_ACCEN0_EN11_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN11 */
#define IFX_STM_ACCEN0_EN11_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN11 */
#define IFX_STM_ACCEN0_EN11_OFF (11u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN12 */
#define IFX_STM_ACCEN0_EN12_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN12 */
#define IFX_STM_ACCEN0_EN12_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN12 */
#define IFX_STM_ACCEN0_EN12_OFF (12u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN13 */
#define IFX_STM_ACCEN0_EN13_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN13 */
#define IFX_STM_ACCEN0_EN13_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN13 */
#define IFX_STM_ACCEN0_EN13_OFF (13u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN14 */
#define IFX_STM_ACCEN0_EN14_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN14 */
#define IFX_STM_ACCEN0_EN14_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN14 */
#define IFX_STM_ACCEN0_EN14_OFF (14u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN15 */
#define IFX_STM_ACCEN0_EN15_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN15 */
#define IFX_STM_ACCEN0_EN15_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN15 */
#define IFX_STM_ACCEN0_EN15_OFF (15u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN16 */
#define IFX_STM_ACCEN0_EN16_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN16 */
#define IFX_STM_ACCEN0_EN16_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN16 */
#define IFX_STM_ACCEN0_EN16_OFF (16u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN17 */
#define IFX_STM_ACCEN0_EN17_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN17 */
#define IFX_STM_ACCEN0_EN17_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN17 */
#define IFX_STM_ACCEN0_EN17_OFF (17u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN18 */
#define IFX_STM_ACCEN0_EN18_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN18 */
#define IFX_STM_ACCEN0_EN18_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN18 */
#define IFX_STM_ACCEN0_EN18_OFF (18u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN19 */
#define IFX_STM_ACCEN0_EN19_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN19 */
#define IFX_STM_ACCEN0_EN19_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN19 */
#define IFX_STM_ACCEN0_EN19_OFF (19u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN20 */
#define IFX_STM_ACCEN0_EN20_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN20 */
#define IFX_STM_ACCEN0_EN20_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN20 */
#define IFX_STM_ACCEN0_EN20_OFF (20u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN21 */
#define IFX_STM_ACCEN0_EN21_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN21 */
#define IFX_STM_ACCEN0_EN21_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN21 */
#define IFX_STM_ACCEN0_EN21_OFF (21u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN22 */
#define IFX_STM_ACCEN0_EN22_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN22 */
#define IFX_STM_ACCEN0_EN22_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN22 */
#define IFX_STM_ACCEN0_EN22_OFF (22u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN23 */
#define IFX_STM_ACCEN0_EN23_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN23 */
#define IFX_STM_ACCEN0_EN23_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN23 */
#define IFX_STM_ACCEN0_EN23_OFF (23u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN24 */
#define IFX_STM_ACCEN0_EN24_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN24 */
#define IFX_STM_ACCEN0_EN24_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN24 */
#define IFX_STM_ACCEN0_EN24_OFF (24u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN25 */
#define IFX_STM_ACCEN0_EN25_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN25 */
#define IFX_STM_ACCEN0_EN25_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN25 */
#define IFX_STM_ACCEN0_EN25_OFF (25u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN26 */
#define IFX_STM_ACCEN0_EN26_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN26 */
#define IFX_STM_ACCEN0_EN26_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN26 */
#define IFX_STM_ACCEN0_EN26_OFF (26u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN27 */
#define IFX_STM_ACCEN0_EN27_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN27 */
#define IFX_STM_ACCEN0_EN27_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN27 */
#define IFX_STM_ACCEN0_EN27_OFF (27u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN28 */
#define IFX_STM_ACCEN0_EN28_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN28 */
#define IFX_STM_ACCEN0_EN28_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN28 */
#define IFX_STM_ACCEN0_EN28_OFF (28u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN29 */
#define IFX_STM_ACCEN0_EN29_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN29 */
#define IFX_STM_ACCEN0_EN29_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN29 */
#define IFX_STM_ACCEN0_EN29_OFF (29u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN30 */
#define IFX_STM_ACCEN0_EN30_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN30 */
#define IFX_STM_ACCEN0_EN30_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN30 */
#define IFX_STM_ACCEN0_EN30_OFF (30u)

/** \brief Length for Ifx_STM_ACCEN0_Bits.EN31 */
#define IFX_STM_ACCEN0_EN31_LEN (1u)

/** \brief Mask for Ifx_STM_ACCEN0_Bits.EN31 */
#define IFX_STM_ACCEN0_EN31_MSK (0x1u)

/** \brief Offset for Ifx_STM_ACCEN0_Bits.EN31 */
#define IFX_STM_ACCEN0_EN31_OFF (31u)

/** \}  */

/******************************************************************************/

/******************************************************************************/

#endif /* IFXSTM_BF_H */
