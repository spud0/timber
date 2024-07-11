#include <source_location>
#include <expected>
#include <system_error>
#include <mutex>

#include "../include/log.hh"

[[nodiscard]] const toml::table timber::config::get_config_table(void) const noexcept {
	
}

// Use because opening the file can cause a problem
std::expected<config, std::system_error> timber::config::read_from_toml (const std::filesystem::path& path) {
	
}

timber::log::log (const config& conf) {
	
	// Do something with inital state of logger
	auto config_table = conf.get_config_table;
	for (auto&& [key, value] : config_file) {
		
	}	
	
}
                                                                               

[[nodiscard]]
std::string_view constexpr timber::log::to_string (const log& logger) const noexcept {

	level current = logger.current_level;
	switch (current) {
		case level::WARN:   return "[warning]";
		case level::DEBUG:  return "[debug]";
		case level::INFO:   return "[info]";
		case level::FATAL:  return "[fatal]";
		
	} 
	
	return ""; 
}


[[nodiscard]]
std::expected<std::string, std::system_error> timber::log::log_message (std::string_view mess,
						 std::source_location loc = std::source_location::current()
) const {

	std::lock_guard<std::mutex> lock (_mtx);
	
	return "";
}
