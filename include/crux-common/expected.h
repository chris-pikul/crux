#pragma once

/*
 * Wraps up the expected from either STD, or if too early, a third-party version
 */

#include <vendor/expected.hpp>

namespace crux {
	template <typename T, class E>
	using expected = tl::expected<T, E>;
}
