# pragma once 
#include <chrono>
#include <string>
#include <mutex>
#include <source_location>

// For TOML parsing
#include "./ext/toml.hh"

namespace timber {
	
	// The config for the logger
	class config {
	  public:
		std::string file_path;
		std::stringstream sstr; 
	  private:
		toml::table config_table;	
	};


	// The level of the logger 
	enum class level {
		WARN,
		DEBUG,
		INFO,
		FATAL,
	};


	// Where to write the logs
	enum class loc {
		STDOUT,
		NET,
		DISK,
	};

	class log {	
	  public:
		[[nodiscard]] constexpr std::string to_string (const log& logger) const noexcept;
		[[nodiscard]] std::string log_message (std::string_view message, std::source_location loc) const;
		
		log (const config& conf);
		~log() = default;
	
	  private:
		std::mutex _mtx;	
		level current_level;			
	};


 }
