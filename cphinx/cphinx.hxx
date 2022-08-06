#pragma once
#include <vector>
#include <ostream>
#include <iostream>
#include "validator.hxx"

namespace cphinx {
	class cphinx {
	public:
		void run(auto & fx, const std::string & name) {
			this->validators.push_back(validator{name});
			return fx(this->validators.back());
		}



		void dignostics(std::ostream & out) {
			out << "=== Test diagnostics ===\n\n";
			for(const auto & validator : validators) {
				validator.dignostics(out);
			}

			out << "=== Test conclusion ===\n\n";
			out << "test: " << test_count() << "\n";
			out << "cases: " << case_count() << "\n";


			const std::size_t err_count = this->error_count();
			out << "errors: " << err_count << "\n";
			if(err_count) {
				out << "ERRORS FOUND!!!\n";
			}
			else {
				out << "All tests successful :)\n";
			}
		}

	private:

		std::size_t test_count() const {
			return validators.size();
		}
		


		std::size_t case_count() const {
			std::size_t count = 0;
			for(const auto & validator : validators) {
				count += validator.case_count();
			}
			return count;
		}



		std::size_t error_count() const {
			std::size_t count = 0;
			for(const auto & validator : validators) {
				count += validator.error_count();
			}
			return count;
		}
		std::vector<validator> validators;
	};


	namespace internal {
		inline cphinx & get_framework() {
			struct AutoDestroy {
				AutoDestroy() { std::ios_base::Init(); }
				cphinx framework;
				~AutoDestroy() { framework.dignostics(std::cout); }
			};
			static AutoDestroy framework;
			return framework.framework;
		}
	}

	bool auto_run(auto & test, const std::string & name) {
		internal::get_framework().run(test, name);
		return true;
	}

	#define CPHINX_TEST(FUNC, NAME)\
		void FUNC(::cphinx::validator & validator);\
		namespace internal {\
			inline const auto dummy##_##FUNC = ::cphinx::auto_run(FUNC, NAME);\
		}
}
