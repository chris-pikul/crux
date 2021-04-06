#pragma once

/*
 * Wraps up the optional from either STD, or if too early, a third-party version
 */

#if __cplusplus >= 201701L //CPP-17+
	#include <optional>
	namespace crux {
		template <typename T>
		using optional = std::optional<T>;
		using nullopt_t = std::nullopt_t;
		constexpr auto nullopt = std::nullopt;
	}
#else
	#if __cplusplus >= 201402L //CPP-14
		#include <experimental/optional>
		namespace crux {
			template <typename T>
			using optional = std::experimental::optional<T>;
			using nullopt_t = std::experimental::nullopt_t;
			constexpr auto nullopt = std::experimental::nullopt;
		}
	#else //CPP-11 and below
		#include <vendor/optional.hpp>
		namespace crux {
			template <typename T>
			using optional = std::experimental::optional<T>;
			using nullopt_t = std::experimental::nullopt_t;
			constexpr auto nullopt = std::experimental::nullopt;
		}
	#endif
#endif
