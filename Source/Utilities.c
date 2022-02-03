#include "File.h"

void CPUCheck() {
  u32 eax, ebx, ecx, edx;
  
  u32 Output = __get_cpuid (7,
			    &eax, &ebx,
			    &ecx, &edx);
}

u64 GetStringSize(i8 *String) { // assuming null-terminated
  u64 StringSize = 0;
  u64 Index = 0;
  __m128i LoadedString = _mm_loadu_si128((__m128i *) String);
  __m128i ZeroMask = _mm_cmpeq_epi8(LoadedString, SIMD_ZERO);

  __m128i StringWithMask = _mm_cmpeq_epi8(LoadedString, ZeroMask);

  while (!StringWithMask[0] && !StringWithMask[1]) {
    Index += 16;
    LoadedString = _mm_loadu_si128((__m128i *) &String[Index]);
    StringWithMask = _mm_cmpeq_epi8(LoadedString, ZeroMask);
  } 

  u64 TrailingZeroesTop = _tzcnt_u64(StringWithMask[0]);
  u64 TrailingZeroesBottom  = _tzcnt_u64(StringWithMask[1]);

  u64 Add = 0;
  if (TrailingZeroesTop == 64) {
    Add += 8 + (TrailingZeroesBottom / 8);
  } else {
    Add += (TrailingZeroesTop / 8);
  }
  
  printf("Index: %llu\n", Index);
  printf("Top: %llu - Bottom: %llu\n", TrailingZeroesTop, TrailingZeroesBottom);
  return Index + Add;
}
