#pragma once

#include <stdint.h>

#include "vector2.h"

using string = std::string;

/// 8bit unsigned integer
using byte = uint8_t;

/// 8bit unsigned integer, using the "fast" option (memory at least 8 bits)
using uint8 = uint_fast8_t;

/// 16bit unsigned integer, using the "fast" option (memory at least 16 bits)
using uint16 = uint_fast16_t;

/// 32bit unsigned integer, using the "fast" option (memory at least 32 bits)
using uint32 = uint_fast32_t;

/// 64bit unsigned integer, using the "fast" option (memory at least 64 bits)
using uint64 = uint_fast64_t;

/// 8bit unsigned integer, strictly sized
using uint8bit = uint8_t;

/// 16bit unsigned integer, strictly sized
using uint16bit = uint16_t;

/// 32bit unsigned integer, strictly sized
using uint32bit = uint32_t;

/// 64bit unsigned integer, strictly sized
using uint64bit = uint64_t;

/// Alias of uint32 for easier readability
using uint = uint32;


/// 8bit signed integer, using the "fast" option (memory at least 8 bits)
using int8 = int_fast8_t;

/// 16bit signed integer, using the "fast" option (memory at least 16 bits)
using int16 = int_fast16_t;

/// 32bit signed integer, using the "fast" option (memory at least 32 bits)
using int32 = int_fast32_t;

/// 64bit signed integer, using the "fast" option (memory at least 64 bits)
using int64 = int_fast64_t;

/// 8bit signed integer, strictly sized
using int8bit = int8_t;

/// 16bit signed integer, strictly sized
using int16bit = int16_t;

/// 32bit signed integer, strictly sized
using int32bit = int32_t;

/// 64bit signed integer, strictly sized
using int64bit = int64_t;


/// 32bit floating point number, alias of "float"
using float32 = float;

/// 64bit floating point number, alias of "double"
using float64 = double;

/// Calculates a single bit at given position "X"
#define BIT(x) (1 << x)

using vec2u = crux::vector2<uint>;
using vec2i = crux::vector2<int>;
using vec2f = crux::vector2<float>;
