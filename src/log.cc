#include <source_location>
#include <expected>
#include <system_error>
#include <mutex>
#include <fmt/core.h>

#include "../include/log.hh"

namespace timber {

	[[nodiscard]] 
	const toml::table& timber::config::get_config_table(void) const noexcept {
		return config_table;	
	}

	// Use because opening the file can cause a problem
	std::expected<toml::table, std::string> config::read_from_toml (const std::filesystem::path& path) noexcept {
		
		if (path.string().empty()) {
			return std::unexpected("No filepath provided");
		}
	
		// should this be in a try except??	 does throw I think
		auto tbl= toml::parse_file(path.string());	
		return tbl.table();
	}


	[[nodiscard]] 
	const std::expected<config, std::string> config::build_from_table(toml::table table) const noexcept {
	
		if (!table.empty())	{
							
		}
	}

	log::log (const config& conf) {
		
		// Do something with inital state of logger
		auto config_table = conf.get_config_table();
		for (auto&& [key, value] : config_table) {
			
		}	
		
	}
																				   

	[[nodiscard]]
	std::string_view log::to_string (const log& logger) const noexcept {

		level current = logger.current_level;
		switch (current) {
			case level::WARN:   return "[warning]";
			case level::DEBUG:  return "[debug]";
			case level::INFO:   return "[info]";
			case level::FATAL:  return "[fatal]";	
		} 
		
		return ""; 
	}


	[[noreturn]]
	void log::log_message (
			level current,
			std::string_view mess,
			const std::source_location loc = std::source_location::current()
	) const {

		std::lock_guard<std::mutex> lock (_mtx);
		fmt::format_args();
		
		std::string_view local_ctx = loc.file_name() + " : " + loc.line() + " : " + loc.function_name();
		
	}

}
