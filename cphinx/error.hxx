#pragma once
#include <stdexcept>

namespace cphinx {

	class unit_error : public std::runtime_error {
	public:
		unit_error(const auto & err_msg) :
			std::runtime_error { std::string{err_msg} } {}
	};
}