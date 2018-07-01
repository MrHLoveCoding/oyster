#ifndef __OYS_COCONTEXT_X86_64_H__
#define __OYS_COCONTEXT_X86_64_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <oys_types.h>
#include <oys_attribute.h>
#include <oys_builtin.h>

struct oys_cocontext
{
    oys_u64_t rsp;
    oys_u64_t rip;
    oys_u64_t rdi;
    oys_u64_t rsi;
    oys_u64_t rdx;
    oys_u64_t rcx;
    oys_u64_t r8;
    oys_u64_t r9;
    oys_u64_t rbp;
    oys_u64_t rbx;
    oys_u64_t r12;
    oys_u64_t r13;
    oys_u64_t r14;
    oys_u64_t r15;
} oys_attr_cacheline_aligned;


/*************************************
 * Brief: Restore coroutine context
 * Return: Void
 * Param: ctx - Coroutine context
 *************************************/
static inline void
oys_attr_inline_always
oys_cocontext_restore(const struct oys_cocontext *ctx)
{
    /* Store ctx in r10 temporarily */
    asm volatile ( \
        "movq %0,%%r10;"
        : : "r"(ctx));

    /* Restore rsp */
    asm volatile ( \
        "movq %c0(%%r10),%%rsp;"
        : : "i"(oys_offsetof(struct oys_cocontext, rsp)));

    /* Push rip in stack */
    asm volatile ( \
        "movq %c0(%%r10),%%r11;"
        "pushq %%r11;"
        : : "i"(oys_offsetof(struct oys_cocontext, rip)));

    /* Restore rdi */
    asm volatile ( \
        "movq %c0(%%r10),%%rdi;"
        : : "i"(oys_offsetof(struct oys_cocontext, rdi)));

    /* Restore rsi */
    asm volatile ( \
        "movq %c0(%%r10),%%rsi;"
        : : "i"(oys_offsetof(struct oys_cocontext, rsi)));

    /* Restore rdx */
    asm volatile ( \
        "movq %c0(%%r10),%%rdx;"
        : : "i"(oys_offsetof(struct oys_cocontext, rdx)));

    /* Restore rcx */
    asm volatile ( \
        "movq %c0(%%r10),%%rcx;"
        : : "i"(oys_offsetof(struct oys_cocontext, rcx)));

    /* Restore r8 */
    asm volatile ( \
        "movq %c0(%%r10),%%r8;"
        : : "i"(oys_offsetof(struct oys_cocontext, r8)));

    /* Restore r9 */
    asm volatile ( \
        "movq %c0(%%r10),%%r9;"
        : : "i"(oys_offsetof(struct oys_cocontext, r9)));

    /* Restore rbp */
    asm volatile ( \
        "movq %c0(%%r10),%%rbp;"
        : : "i"(oys_offsetof(struct oys_cocontext, rbp)));

    /* Restore rbx */
    asm volatile ( \
        "movq %c0(%%r10),%%rbx;"
        : : "i"(oys_offsetof(struct oys_cocontext, rbx)));

    /* Restore r12 */
    asm volatile ( \
        "movq %c0(%%r10),%%r12;"
        : : "i"(oys_offsetof(struct oys_cocontext, r12)));

    /* Restore r13 */
    asm volatile ( \
        "movq %c0(%%r10),%%r13;"
        : : "i"(oys_offsetof(struct oys_cocontext, r13)));

    /* Restore r14 */
    asm volatile ( \
        "movq %c0(%%r10),%%r14;"
        : : "i"(oys_offsetof(struct oys_cocontext, r14)));

    /* Restore r15 */
    asm volatile ( \
        "movq %c0(%%r10),%%r15;"
        : : "i"(oys_offsetof(struct oys_cocontext, r15)));

    /* Return to new address */
    asm volatile ( \
        "xorl %eax,%eax;"
        "ret;");
}

/*************************************
 * Brief: Construct coroutine context
 * Return: Void
 * Param: ctx - Number of coroutines
 *      stack - 
 *      entry - Lcore id
 *      arg1 - 
 *      arg2 - 
 *      arg3 - 
 *************************************/
static inline void
oys_attr_inline_always
oys_cocontext_construct(struct oys_cocontext *ctx,
    oys_u64_t stack, oys_u64_t entry, oys_u64_t arg1, oys_u64_t arg2, oys_u64_t arg3)
{
    //eel_memset(ctx, 0, sizeof(struct eel_cocontext));
    ctx->rsp = stack;
    ctx->rip = entry;
    ctx->rdi = arg1;
    ctx->rsi = arg2;
    ctx->rdx = arg3;
}

/*************************************
 * Brief: Save coroutine context
 * Return: Void
 * Param: ctx - Coroutine context
 *************************************/
void
oys_cocontext_save(struct oys_cocontext *ctx);

/*************************************
 * Brief: Swap current coroutine to new coroutine
 * Return: Void
 * Param: curr_ctx - Current coroutine context
 *      new_ctx - New coroutine context
 *************************************/
void
oys_cocontext_swap(struct oys_cocontext *curr_ctx,
    const struct oys_cocontext *new_ctx);

#ifdef __cplusplus
}
#endif

#endif
