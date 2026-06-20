#include "spslr_env.h"

#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/random.h>
#include <linux/memblock.h>

#ifdef CONFIG_X86

#include <asm/text-patching.h>

static __always_inline int spslr_env_poke_text(void *dst, const void *src, size_t n)
{
	text_poke_early(dst, src, n);
	return 0;
}

#endif

int spslr_env_poke_text_8(void *dst, u8 value)
{
	return spslr_env_poke_text(dst, &value, sizeof(value));
}

int spslr_env_poke_text_16(void *dst, u16 value)
{
	return spslr_env_poke_text(dst, &value, sizeof(value));
}

int spslr_env_poke_text_32(void *dst, u32 value)
{
	return spslr_env_poke_text(dst, &value, sizeof(value));
}

int spslr_env_poke_text_64(void *dst, u64 value)
{
	return spslr_env_poke_text(dst, &value, sizeof(value));
}

/*
 * Hook runs before slab allocators are available.
 * memblock_alloc() is the correct early-boot allocator.
 */
void* __init spslr_env_malloc(spslr_u64 n) {
	size_t size = PAGE_ALIGN(n ? n : 1);
	return memblock_alloc(size, SMP_CACHE_BYTES);
}

void __init spslr_env_free(void *ptr, spslr_u64 n) {
	if (ptr)
		memblock_free(ptr, PAGE_ALIGN(n ? n : 1));
}

int spslr_env_poke_data(void* dst, const void* src, spslr_u64 n) {
	memcpy(dst, src, n);
	return 0;
}

void spslr_env_memset(void* dst, int v, spslr_u64 n) {
	memset(dst, v, n);
}

void spslr_env_memcpy(void* dst, const void* src, spslr_u64 n) {
	memcpy(dst, src, n);
}

int spslr_env_memcmp(const void *x, const void *y, spslr_u64 n) {
	return memcmp(x, y, n);
}

spslr_u64 __init spslr_env_random_u64(void) {
	return get_random_u64(); // Hook runs after random_init_early()
}

