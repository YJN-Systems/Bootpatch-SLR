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

void* __init spslr_env_malloc(spslr_u32 n) {
	if (!n)
		n = 1;

	/*
	 * Hook runs before slab allocators are available.
	 * memblock_alloc() is the correct early-boot allocator.
	 * Reserve the memory to ensure it is not freed when handed to later allocator.
	 */
	void* res = memblock_alloc(n, SMP_CACHE_BYTES);

	if (!res)
		return res;

	memblock_reserve(__pa(res), n);
	return res;
}

int spslr_env_poke_data(void* dst, const void* src, spslr_u32 n) {
	memcpy(dst, src, n);
	return 0;
}

void spslr_env_memset(void* dst, int v, spslr_u32 n) {
	memset(dst, v, n);
}

void spslr_env_memcpy(void* dst, const void* src, spslr_u32 n) {
	memcpy(dst, src, n);
}

spslr_u32 __init spslr_env_random_u32(void) {
	return get_random_u32(); // Hook runs after random_init_early() 
}

