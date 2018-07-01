#include <oys_cocontext.h>

static inline void
oys_attr_inline_always
__save_cocontext(struct oys_cocontext *ctx)
{
    /* Save rsp */
    asm volatile ( \
        "leaq 0x8(%%rsp),%%r10;"
        "movq %%r10,%0;"
        : "=m"(ctx->rsp));

    /* Save rip */
    asm volatile ( \
        "movq (%%rsp),%%r10;"
        "movq %%r10,%0;"
        : "=m"(ctx->rip));

    /* Save rdi */
    asm volatile ( \
        "movq %%rdi,%0;"
        : "=m"(ctx->rdi));

    /* Save rsi */
    asm volatile ( \
        "movq %%rsi,%0;"
        : "=m"(ctx->rsi));

    /* Save rdx */
    asm volatile ( \
        "movq %%rdx,%0;"
        : "=m"(ctx->rdx));

    /* Save rcx */
    asm volatile ( \
        "movq %%rcx,%0;"
        : "=m"(ctx->rcx));

    /* Save r8 */
    asm volatile ( \
        "movq %%r8,%0;"
        : "=m"(ctx->r8));

    /* Save r9 */
    asm volatile ( \
        "movq %%r9,%0;"
        : "=m"(ctx->r9));

    /* Save rbp */
    asm volatile ( \
        "movq %%rbp,%0;"
        : "=m"(ctx->rbp));

    /* Save rbx */
    asm volatile ( \
        "movq %%rbx,%0;"
        : "=m"(ctx->rbx));

    /* Save r12 */
    asm volatile ( \
        "movq %%r12,%0;"
        : "=m"(ctx->r12));

    /* Save r13 */
    asm volatile ( \
        "movq %%r13,%0;"
        : "=m"(ctx->r13));

    /* Save r14 */
    asm volatile ( \
        "movq %%r14,%0;"
        : "=m"(ctx->r14));

    /* Save r15 */
    asm volatile ( \
        "movq %%r15,%0;"
        : "=m"(ctx->r15));
}

void
oys_cocontext_save(struct oys_cocontext *ctx)
{
    __save_cocontext(ctx);
}

void
oys_cocontext_swap(struct oys_cocontext *curr_ctx,
    const struct oys_cocontext *new_ctx)
{
    __save_cocontext(curr_ctx);
    oys_cocontext_restore(new_ctx);
}
