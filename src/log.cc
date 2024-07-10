#include "../include/log.hh"
#include <source_location>

timber::log::log (const config& conf) {
	
	// Do something with inital state of logger
	auto config_file = toml::parse_file(conf.file_path);
	for (auto&& [key, value] : config_file) {
	
	}	
	
}
                                                                               

std::string timber::log::to_string (const log& logger) const {
	level current = logger.current_level;

	switch (current) {
		case level::WARN:  
			return std::string("[warning]");
		case level::DEBUG:  
			return std::string("[debug]");
		case level::INFO:  
			return std::string("[info]");
		case level::FATAL:  
			return std::string("[fatal]");
		
	} 
}

