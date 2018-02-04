#ifndef ASSERTION_HELPER_HPP

#define ASSERTION_HELPER_HPP

#define ASSERT_EQUAL(a,b) AssertionHelper::assertEquals(a, b);
#define PRINT_ASSERTION_STATISTICS() AssertionHelper::printAssertionStatistics();
#define RESET_ASSERTION_STATISTICS() successes=failures=0;
#define HAVE_FAILURE() (failures>0)

static volatile unsigned int failures;
static volatile unsigned int successes;

class AssertionHelper{

	public:

		static void printAssertionStatistics(){
			std::cout << "Successes: " << successes << " | Failures: " << failures << std::endl << std::endl;
		}

		static void assertEquals(std::string a, std::string b){

			if(a.compare(b) == 0){
				successes++;
			}else{
				failures++;
				std::cout << std::endl << "ASSERTION FAILURE (Test " << successes+failures << "): " << std::endl;
				std::cout << "Writing currently reads: " << a << std::endl;
				std::cout << "    Writing should read: " << b << std::endl  << std::endl;
			}

		}

};


#endif
