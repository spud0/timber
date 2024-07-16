#include ...

// Path to the logger header file
#include "../include/log.hh"

const timber::log logger();


[[noreturn]] 
void doing_some_work () {
	
	// Some stuff 

	if (0) {

	} else if () {


	} else {
		// reaching here is fatal
		logger.log(timber::level::FATAL, "fatal op, terminating program");
	} 

}

int main (void) {
	
	logger.log(timber::level::INFO, "Started the logger");

	// Some application logic	
	

	for (const auto&& thing: iterable) {
		// Some thing here	
		logger.log(timber::level::DEBUG, "Looping over iterable object");
	}

	return 0;		
}
