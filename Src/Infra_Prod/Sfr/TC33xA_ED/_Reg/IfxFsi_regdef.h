/**
 * \file IfxFsi_regdef.h
 * \brief
 * \copyright Copyright (c) 2020 Infineon Technologies AG. All rights reserved.
 *
 *
 * Version: TC33XED_UM_V1.4.0.R0
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
 * \defgroup IfxSfr_Fsi_Registers Fsi Registers
 * \ingroup IfxSfr
 * 
 * \defgroup IfxSfr_Fsi_Registers_Bitfields Bitfields
 * \ingroup IfxSfr_Fsi_Registers
 * 
 * \defgroup IfxSfr_Fsi_Registers_union Register unions
 * \ingroup IfxSfr_Fsi_Registers
 * 
 * \defgroup IfxSfr_Fsi_Registers_struct Memory map
 * \ingroup IfxSfr_Fsi_Registers
 */
#ifndef IFXFSI_REGDEF_H
#define IFXFSI_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/


/** \addtogroup IfxSfr_Fsi_Registers_Bitfields
 * \{  */
/** \brief Communication Register 1 */
typedef struct _Ifx_FSI_COMM_1_Bits
{
    Ifx_UReg_8Bit COMM1:8;            /**< \brief [7:0] FSI Communication 1 - COMM1 (rw) */
} Ifx_FSI_COMM_1_Bits;

/** \brief Communication Register 2 */
typedef struct _Ifx_FSI_COMM_2_Bits
{
    Ifx_UReg_8Bit COMM2:8;            /**< \brief [7:0] FSI Communication 2 - COMM2 (rw) */
} Ifx_FSI_COMM_2_Bits;

/** \brief HSM Communication Register 1 */
typedef struct _Ifx_FSI_HSMCOMM_1_Bits
{
    Ifx_UReg_8Bit HSMCOMM1:8;         /**< \brief [7:0] HSM FSI Communication 1 - HSMCOMM1 (rw) */
} Ifx_FSI_HSMCOMM_1_Bits;

/** \brief HSM Communication Register 2 */
typedef struct _Ifx_FSI_HSMCOMM_2_Bits
{
    Ifx_UReg_8Bit HSMCOMM2:8;         /**< \brief [7:0] HSM FSI Communication 2 - HSMCOMM2 (rw) */
} Ifx_FSI_HSMCOMM_2_Bits;

/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxSfr_fsi_Registers_union
 * \{   */
/** \brief Communication Register 1   */
typedef union
{
    Ifx_UReg_8Bit U;                  /**< \brief Unsigned access */
    Ifx_SReg_8Bit I;                  /**< \brief Signed access */
    Ifx_FSI_COMM_1_Bits B;            /**< \brief Bitfield access */
} Ifx_FSI_COMM_1;

/** \brief Communication Register 2   */
typedef union
{
    Ifx_UReg_8Bit U;                  /**< \brief Unsigned access */
    Ifx_SReg_8Bit I;                  /**< \brief Signed access */
    Ifx_FSI_COMM_2_Bits B;            /**< \brief Bitfield access */
} Ifx_FSI_COMM_2;

/** \brief HSM Communication Register 1   */
typedef union
{
    Ifx_UReg_8Bit U;                  /**< \brief Unsigned access */
    Ifx_SReg_8Bit I;                  /**< \brief Signed access */
    Ifx_FSI_HSMCOMM_1_Bits B;         /**< \brief Bitfield access */
} Ifx_FSI_HSMCOMM_1;

/** \brief HSM Communication Register 2   */
typedef union
{
    Ifx_UReg_8Bit U;                  /**< \brief Unsigned access */
    Ifx_SReg_8Bit I;                  /**< \brief Signed access */
    Ifx_FSI_HSMCOMM_2_Bits B;         /**< \brief Bitfield access */
} Ifx_FSI_HSMCOMM_2;

/** \}  */

/******************************************************************************/
/** \addtogroup IfxSfr_Fsi_Registers_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief FSI object */
typedef volatile struct _Ifx_FSI
{
       Ifx_UReg_8Bit                       reserved_0[4];          /**< \brief 0, \internal Reserved */
       Ifx_FSI_COMM_1                      COMM_1;                 /**< \brief 4, Communication Register 1*/
       Ifx_FSI_COMM_2                      COMM_2;                 /**< \brief 5, Communication Register 2*/
       Ifx_FSI_HSMCOMM_1                   HSMCOMM_1;              /**< \brief 6, HSM Communication Register 1*/
       Ifx_FSI_HSMCOMM_2                   HSMCOMM_2;              /**< \brief 7, HSM Communication Register 2*/
       Ifx_UReg_8Bit                       reserved_8[248];        /**< \brief 8, \internal Reserved */
} Ifx_FSI;

/** \}  */
/******************************************************************************/
/** \}  */


/******************************************************************************/

/******************************************************************************/

#endif /* IFXFSI_REGDEF_H */
