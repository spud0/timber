# pragma once 
#include <chrono>
#include <string>
#include <mutex>

// For TOML parsing
#include "./ext/toml.hh"


namespace timber {
	
	// The config for the logger
	class config {};


	// The level of the logger 
	enum class Level {
		WARN = 0,
		DEBUG,
		INFO,
		FATAL,
	};


	class log {	
	  public:
		std::string to_string (const log& logger) const;
		log (const config& conf);
		~log();
	
	  private:
		std::mutex _mut;	
		Level current_level;	
			
	};


	// Where to write the logs
	enum class Loc {
		STDOUT = 0,
		NET,
		DISK,
	};

 }
