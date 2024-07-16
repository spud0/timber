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

	#if 0
	// Use because opening the file can cause a problem
	toml::table config::read_from_toml (const std::filesystem::path& path) noexcept {
		
		if (path.string().empty()) {
			return std::unexpected("No filepath provided");
		}
	
		// should this be in a try except??	 does throw I think
		auto tbl = toml::parse_file(path.string());	
		return tbl;
	}
	#endif

	[[nodiscard("Must capture config to configure logger.")]] 
	const config config::build_from_table(const toml::table& table) const noexcept {
	
		config conf{};

		// Return an empty congif if the table is empty	
		if (table.empty())	{
			return conf;			
		}

		if (table.contains("logger")) {
			const auto& logger = config_table["logger"];

			bool use_defaults = logger["defaults"].value_or(false).as_boolean();
			if (use_defaults) {
				// Do something for default configuration values?
				// Defaults already baked into the class 
			} else {
				destn = logger["destination"].value_or("stdout").as_string();
				format_string = logger["format"].value_or("{timestamp} [{level}] {message}").as_string();

				if (logger.contains("buffer")) {
					const auto& buffer = logger["buffer"];
					buffer_enabled = buffer["enabled"].value_or(true).as_boolean();
					buffer_size = buffer["buffer_size"].value_or(10).as_integer();
				}

				if (logger.contains("colors")) {
					const auto& colors = logger["colors"];
					debug_color = colors["debug"].value_or("blue").as_string();
					info_color = colors["info"].value_or("green").as_string();
					warn_color = colors["warn"].value_or("yellow").as_string();
					error_color = colors["error"].value_or("red").as_string();
				}

				if (logger.contains("file")) {
					const auto& file = logger["file"];
					conf.set_fp(file["path"].as_string());
					conf.set_rot_size(file["rotation_size"].value_or(10485760).as_integer());
				}

				if (logger.contains("stdout")) {
					const auto& stdout_section = logger["stdout"];
					stdout_enabled = stdout_section["enabled"].value_or(true).as_boolean();
				}
			}	

		return conf;
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
