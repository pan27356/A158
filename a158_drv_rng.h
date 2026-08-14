/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd
 ******************************************************************************
 *  @File Name        : kf32a158sf_drv_rng.h
 *  @Date             : 2025-07-08
 *  @Version          : {{VersionDate}}
 *  @Description      : This file provides RNG driver.
 ******************************************************************************
 *  Copyright (C) by Shanghai ChipON Micro-Electronic Co.,Ltd
 *  All rights reserved.
 *
 *  This software is copyright protected and proprietary to
 *  Shanghai ChipON Micro-Electronic Co.,Ltd.
 *****************************************************************************/
/******************************************************************************
 *  |Date        |Version  |Author       |Description
 *******************************************************************************
 *  |2025-07-08  |V1.0     |AE Group     |New create
 ******************************************************************************/
#ifndef KF32A158SF_DRV_RNG_H
#define KF32A158SF_DRV_RNG_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *                      QAC Warnings
 ******************************************************************************/
/* PRQA S 0288 EOF #KQR000288 */
/* PRQA S 3205 EOF #KQR003205 */
/* PRQA S 3219 EOF #KQR003219 */
/* PRQA S 0303,0306 EOF #KQR100303 */
/* PRQA S 1006,3006 EOF #KQR101006 */

/******************************************************************************
 *                      Include Files
 ******************************************************************************/
#include "kf32a158sf_reg_rng.h"

/******************************************************************************
 *                      Macro or Inline
 ******************************************************************************/

#ifdef KF_DRV_RNG_ASSERT
#include "dev_assert.h"
#define KF_RNG_ASSERT(x) KF_DEV_ASSERT(x)
#else
#define KF_RNG_ASSERT(x) ((void)0U)
#endif

/**
 * @defgroup RNG_INTR_SET_MASK
 * @brief Rng 中断使能掩码
 * @{
 */
/** @brief 数据错误中断 */
#define RNG_INTR_SET_MASK_DEIE (1UL << 2U)
/** @brief 数据就绪中断 */
#define RNG_INTR_SET_MASK_DRIE (1UL << 1U)
#define CHECK_RNG_INTR_SET_MASK(MASK)                                                                                  \
    ((uint32_t)(MASK) == (uint32_t)RNG_INTR_SET_MASK_DEIE || (uint32_t)(MASK) == (uint32_t)RNG_INTR_SET_MASK_DRIE)
/**@} */

/**
 * @defgroup RNG_INTR_CLEAR_MASK
 * @brief Rng 中断清除掩码
 * @{
 */
/** @brief 数据错误中断 */
#define RNG_INTR_CLEAR_MASK_DEIC (1UL << 0U)
/** @brief 数据就绪中断 */
#define RNG_INTR_CLEAR_MASK_DRIC (1UL << 1U)
#define CHECK_RNG_INTR_CLEAR_MASK(MASK)                                                                                \
    ((uint32_t)(MASK) == (uint32_t)RNG_INTR_CLEAR_MASK_DEIC || (uint32_t)(MASK) == (uint32_t)RNG_INTR_CLEAR_MASK_DRIC)
/**@} */

/**
 * @defgroup RNG_ERR_MASK
 * @brief Rng 错误信息
 * @{
 */
/** @brief 错误信息掩码 */
#define RNG_ERR_INFO_MASK (0x3EU)
/** @brief repcnt 健康检测算法错误掩码 */
#define RNG_ERR_REPCNT_MASK (1UL << 5U)
/** @brief adapt 健康检测算法高阈值错误掩码 */
#define RNG_ERR_ADAPT_HI_MASK (1UL << 4U)
/** @brief adapt 健康检测算法低阈值错误掩码 */
#define RNG_ERR_ADAPT_LO_MASK (1UL << 3U)
/** @brief markvo 健康检测算法高阈值错误掩码 */
#define RNG_ERR_MARKVO_HI_MASK (1UL << 2U)
/** @brief markvo 健康检测算法低阈值错误掩码 */
#define RNG_ERR_MARKVO_LO_MASK (1UL << 1U)
/**@} */

/******************************************************************************
 *                      Type definitions
 ******************************************************************************/

/**
 * @brief 随机数监测窗口大小
 */
typedef enum
{
    RNG_WIN_1024,
    RNG_WIN_512,
    RNG_WIN_256,
    RNG_WIN_128,
} Rng_WindowSize_t;
#define CHECK_RNG_WINDOW(WIN) ((uint32_t)(WIN) <= (uint32_t)RNG_WIN_128)

/**
 * @brief 初始化丢弃比特数
 */
typedef enum
{
    RNG_DROP_0_BIT,
    RNG_DROP_128_BIT,
    RNG_DROP_256_BIT,
    RNG_DROP_512_BIT,
} Rng_DropBit_t;
#define CHECK_RNG_DROP_BIT(BIT) ((uint32_t)(BIT) <= (uint32_t)RNG_DROP_512_BIT)

/**
 * @brief LFSR 后处理初始值
 */
typedef enum
{
    /** @brief seed 为 0xffff_ffff_ffff_ffff, 表示LFSR关闭 */
    RNG_LFSR_SEED_0,
    /** @brief seed 为 0xf2cd_dc7a_9e8f_6b4f */
    RNG_LFSR_SEED_1,
    /** @brief seed 为 0xad6f_e011_4220_3927 */
    RNG_LFSR_SEED_2,
    /** @brief seed 为 0xb237_fb1f_d8c0_a2f4 */
    RNG_LFSR_SEED_3,
} Rng_LfsrSeed_t;
#define CHECK_RNG_LFSR_SEED(SEED) ((uint32_t)(SEED) <= (uint32_t)RNG_LFSR_SEED_3)

/**
 * @brief xor 后处理参数选择
 */
typedef enum
{
    /** @brief xor 后处理关闭 */
    RNG_XOR_CHAIN_0,
    /** @brief xor 后处理开启, 阈值为 5 */
    RNG_XOR_CHAIN_1,
    /** @brief xor 后处理开启, 阈值为 7 */
    RNG_XOR_CHAIN_2,
    /** @brief xor 后处理开启, 阈值为 9 */
    RNG_XOR_CHAIN_3,
    /** @brief xor 后处理开启, 阈值为 11 */
    RNG_XOR_CHAIN_4,
} Rng_XorChain_t;
#define CHECK_RNG_XOR_CHAIN(CHAIN) ((uint32_t)(CHAIN) <= (uint32_t)RNG_XOR_CHAIN_4)

/**
 * @brief Repcnt 健康检测算法阈值
 * @note 检测窗口内连续 1 或连续 0 的个数超出该值时报错
 */
typedef enum
{
    RNG_REPCNT_8,
    RNG_REPCNT_12,
    RNG_REPCNT_16,
    RNG_REPCNT_20,
    RNG_REPCNT_24,
    RNG_REPCNT_28,
    RNG_REPCNT_32,
    RNG_REPCNT_36,
} Rng_Repcnt_t;
#define CHECK_RNG_REPCNT(CNT) ((uint32_t)(CNT) <= (uint32_t)RNG_REPCNT_36)

/**
 * @brief adapt 健康检测算法阈值
 * @note 检测窗口内的原始数据的 0-1 分布超出该范围时, 报告错误
 */
typedef enum
{
    RNG_ADAPT_LOOSE,
    RNG_ADAPT_NORMAL,
    RNG_ADAPT_STRICT,
} Rng_Adapt_t;
#define CHECK_RNG_ADAPT(ADAPT) ((uint32_t)(ADAPT) <= (uint32_t)RNG_ADAPT_STRICT)

/**
 * @brief markov 健康检测算法阈值
 * @note 检测窗口内的原始数据的跳变超出该范围时, 报告错误
 */
typedef enum
{
    RNG_MARKOV_LOOSE,
    RNG_MARKOV_NORMAL,
    RNG_MARKOV_STRICT,
} Rng_Markov_t;
#define CHECK_RNG_MARKOV(MARKOV) ((uint32_t)(MARKOV) <= (uint32_t)RNG_MARKOV_STRICT)

/**
 * @brief Rng 中断获取索引
 */
typedef enum
{
    /** @brief 数据错误中断索引 */
    RNG_INTR_GET_INDEX_DEIF = 0U,
    /** @brief 数据就绪中断索引 */
    RNG_INTR_GET_INDEX_DRIF = 6U,
} Rng_IntrGetIndex_t;
#define CHECK_RNG_INTR_GET_INDEX(INDEX)                                                                                \
    ((uint32_t)(INDEX) == (uint32_t)RNG_INTR_GET_INDEX_DEIF || (uint32_t)(INDEX) == (uint32_t)RNG_INTR_GET_INDEX_DRIF)

/******************************************************************************
 *                      Export Variables
 ******************************************************************************/

/******************************************************************************
 *                      Export Functions
 ******************************************************************************/

/**
 * @brief 设置 RNG 检测窗口大小
 *
 * @param Window 窗口大小
 * @return void
 */
KF_INLINE void Rng_LL_SetWindowSize(Rng_WindowSize_t Window)
{
    KF_RNG_ASSERT(CHECK_RNG_WINDOW(Window));

    RNG_PTR->CTL1.bits.WINDOW_SEL = (uint32_t)Window;
}

/**
 * @brief 设置 RNG 初始化丢弃比特数
 *
 * @param DropBit 丢弃比特数
 * @return void
 */
KF_INLINE void Rng_LL_SetDropBit(Rng_DropBit_t DropBit)
{
    KF_RNG_ASSERT(CHECK_RNG_DROP_BIT(DropBit));

    RNG_PTR->CTL1.bits.DROP_BIT_SEL = (uint32_t)DropBit;
}

/**
 * @brief 设置 冯·诺依曼后处理使能状态
 *
 * @param State 使能状态
 *        true: 使能
 *        false: 关闭
 * @return void
 */
KF_INLINE void Rng_LL_SetVNPostProcessEnabled(bool State)
{
    RNG_PTR->CTL1.bits.VN_EN = (true == State) ? 1U : 0U;
}

/**
 * @brief 设置 LFSR 后处理初始值
 *
 * @param LfsrSeed LFSR 后处理初始值
 * @return void
 */
KF_INLINE void Rng_LL_SetLfsrPostProcessSeed(Rng_LfsrSeed_t LfsrSeed)
{
    KF_RNG_ASSERT(CHECK_RNG_LFSR_SEED(LfsrSeed));

    RNG_PTR->CTL1.bits.SEED_SEL = (uint32_t)LfsrSeed;
}

/**
 * @brief 设置信道参数阈值
 *
 * @param XorChain 信道参数阈值
 * @return void
 */
KF_INLINE void Rng_LL_SetXorChainThreshold(Rng_XorChain_t XorChain)
{
    KF_RNG_ASSERT(CHECK_RNG_XOR_CHAIN(XorChain));

    RNG_PTR->CTL1.bits.XOR_CHAIN_SEL = (uint32_t)XorChain;
}

/**
 * @brief 设置 Repcnt 阈值
 *
 * @param Repcnt Repcnt 阈值
 * @return void
 */
KF_INLINE void Rng_LL_SetRepcntThreshold(Rng_Repcnt_t Repcnt)
{
    KF_RNG_ASSERT(CHECK_RNG_REPCNT(Repcnt));

    RNG_PTR->CTL1.bits.HT_REPCNT_SEL = (uint32_t)Repcnt;
}

/**
 * @brief 设置 Adapt 阈值
 *
 * @param Adapt Adapt 阈值
 * @return void
 */
KF_INLINE void Rng_LL_SetAdaptThreshold(Rng_Adapt_t Adapt)
{
    KF_RNG_ASSERT(CHECK_RNG_ADAPT(Adapt));

    RNG_PTR->CTL1.bits.HT_ADAPT_SEL = (uint32_t)Adapt;
}

/**
 * @brief 设置 Markov 阈值
 *
 * @param Markov Markov 阈值
 * @return void
 */
KF_INLINE void Rng_LL_SetMarkovThreshold(Rng_Markov_t Markov)
{
    KF_RNG_ASSERT(CHECK_RNG_MARKOV(Markov));

    RNG_PTR->CTL1.bits.HT_MARK_SEL = (uint32_t)Markov;
}

/**
 * @brief 清除 RNG 中断标志位
 *
 * @param IntrMask 中断标志位掩码, 可选值见 RNG_INTR_CLEAR_MASK
 * @return void
 */
KF_INLINE void Rng_LL_ClearIntrFlag(uint32_t IntrMask)
{
    KF_RNG_ASSERT(CHECK_RNG_INTR_CLEAR_MASK(IntrMask));

    /* PRQA S 3473 ++ #KQR003473 */
    REG_BIT_SET(RNG_PTR->ESRCLR.reg, IntrMask);
    NOP();
    NOP();
    NOP();
    NOP();
    REG_BIT_CLR(RNG_PTR->ESRCLR.reg, IntrMask);
    /* PRQA S 3473 -- #KQR003473 */
}

/**
 * @brief 设置 RNG 中断使能状态
 *
 * @param IntrMask 中断标志位掩码, 可选值 RNG_INTR_SET_MASK
 * @return void
 */
KF_INLINE void Rng_LL_SetIntrEnabled(uint32_t IntrMask, bool State)
{
    KF_RNG_ASSERT(CHECK_RNG_INTR_SET_MASK(IntrMask));

    /* PRQA S 3473 ++ #KQR003473 */
    if (State)
    {
        REG_BIT_SET(RNG_PTR->CTL2.reg, IntrMask);
    }
    else
    {
        REG_BIT_CLR(RNG_PTR->CTL2.reg, IntrMask);
    }
    /* PRQA S 3473 -- #KQR003473 */
}

/**
 * @brief 设置 Rng 使能状态
 *
 * @param State 使能状态
 *        true: 使能
 *        false: 关闭
 * @return void
 */
KF_INLINE void Rng_LL_SetEnabled(bool State)
{
    RNG_PTR->CTL2.bits.TRNG_EN = (true == State) ? 1U : 0U;
}

/**
 * @brief 获取 Rng 中断状态
 *
 * @param IntrIndex 中断索引
 * @return bool
 * @retval true: 中断触发
 * @retval false: 中断未触发
 */
KF_INLINE bool Rng_LL_GetIntrFlag(Rng_IntrGetIndex_t IntrIndex)
{
    KF_RNG_ASSERT(CHECK_RNG_INTR_GET_INDEX(IntrIndex));

    /* PRQA S 3469 1 #KQR003469 */
    return (REG_BIT_BOOLED(RNG_PTR->ESR.reg, (1UL << (uint32_t)IntrIndex)));
}

/**
 * @brief 获取 RNG 错误信息
 *
 * @return uint32_t 错误信息, 可使用 RNG_ERR_MASK 中的掩码获取指定错误信息
 */
KF_INLINE uint32_t Rng_LL_GetErrorInformation(void)
{
    return (RNG_PTR->ESR.reg & RNG_ERR_INFO_MASK);
}

/**
 * @brief 获取 repcnt 错误信息
 *
 * @return uint32_t repcnt 错误信息
 */
KF_INLINE uint32_t Rng_LL_GetRepcntErrorResult(void)
{
    return (RNG_PTR->ERR1.bits.REPCNTS_ERR);
}

/**
 * @brief 获取 adapt 错误信息
 *
 * @return uint32_t adapt 错误信息
 */
KF_INLINE uint32_t Rng_LL_GetAdaptErrorResult(void)
{
    return (RNG_PTR->ERR2.bits.ADAPTP_ERR);
}

/**
 * @brief 获取 markov 错误信息
 *
 * @return uint32_t markov 错误信息
 */
KF_INLINE uint32_t Rng_LL_GetMarkovErrorResult(void)
{
    return (RNG_PTR->ERR3.bits.MARKOV_ERR);
}

/**
 * @brief 获取随机数
 *
 * @return uint32_t 随机数
 */
KF_INLINE uint32_t Rng_LL_GetRandom(void)
{
    return (RNG_PTR->RDATA);
}

/**
 * @brief 获取 fifo 深度
 *
 * @return uint32_t
 */
KF_INLINE uint32_t Rng_LL_GetFifoDepth(void)
{
    return (RNG_PTR->FIFODEPTH.bits.FIFO_DEPTH);
}

#ifdef __cplusplus
}
#endif /*End of __cplusplus*/
#endif /*End of KF32A158SF_DRV_RNG_H*/
/* EOF */