#pragma once
#include <ostream>

namespace cphinx {
	namespace internal {
		template <typename T>
		concept ostreamable = requires(std::ostream & os, T a) { os << a; };
	}
}