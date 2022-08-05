#pragma once
#include <stdexcept>
#include <vector>
#include <ostream>
#include <sstream>
#include "ostreamable.hxx"
#include "error.hxx"

namespace cphinx {
	class validator {
	public:
		validator(const std::string & name) : name { name } {}



		void assert_true(bool b, const std::string & err_msg = "") {
			if(!assert(b, true)) {
				std::ostringstream oss;
				oss << "Expected true. " << err_msg;
				error(oss.str());
			}
		}



		void assert_false(bool b, const std::string & err_msg = "") {
			if(!assert(b, false)) {
				std::ostringstream oss;
				oss << "Expected false. " << err_msg;
				error(oss.str());
			}
		}



		template <typename Ta, typename Tb>
		void assert_equal(const Ta & got, const Tb & expected, const std::string & err_msg = "Not equal.") {
			if(!assert(got, expected)) {
				std::ostringstream oss;
				oss << err_msg;
				if constexpr(internal::ostreamable<Ta> && internal::ostreamable<Tb>) {
					oss << " " << "Got " << got << " expected " << expected;
				}
				error(oss.str());
			}
		}



		void dignostics(std::ostream & out) const {
			out << "Test: " << name;
			if(errors.empty()) {
				out << " -> Successful!\n";
			}
			else {
				out << " -> Failed!\n";
			}
			for(const auto & error : errors) {
				out << "[ERROR] " << error.what() << "\n";
			}
			out << "\n";
		}



		std::size_t error_count() const {
			return errors.size();
		}



		std::size_t case_count() const {
			return cases;
		}

	private:

		template <typename Ta, typename Tb>
		bool assert(const Ta & a, const Tb & b) {
			++cases;
			return a == b;
		}



		void error(const auto & err_msg) {
			errors.push_back(unit_error{ err_msg });
		}



		std::string name;
		std::vector<unit_error> errors;
		std::size_t cases = 0;
	};
}