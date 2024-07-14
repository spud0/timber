# pragma once 

#include <chrono>
#include <string>
#include <mutex>
#include <source_location>
#include <filesystem>
#include <expected>
#include <unordered_map>
#include <fmt/color.h>

// For TOML parsing
#include "./ext/toml.hh"

namespace timber {
	
	enum class level { WARN, DEBUG, INFO, FATAL, };
	enum class destn { STDOUT, NET, DISK, };

	// The config for the logger
	class config {
	  public:
		static std::expected<config, std::system_error> read_from_toml(const std::filesystem::path& file_path) noexcept;

		[[nodiscard("Must capture TOML table to configure logger.")]] const toml::table& get_config_table(void) const noexcept;

		[[nodiscard]] const std::string_view get_color (level lvl) const noexcept; 

		[[nodiscard]] const config build_from_table(const toml::table& table) const noexcept;
		
		
	  private:

		std::filesystem::path file_path;
		toml::table config_table;	

		inline static const std::unordered_map<std::string, fmt::color> level_color_map = {
			{"black", fmt::color::black }, {"red",     fmt::color::red},
			{"green", fmt::color::green} , {"yellow",  fmt::color::yellow},
			{"blue",  fmt::color::blue}  , {"magenta", fmt::color::magenta},
			{"cyan",  fmt::color::cyan}  , {"white",   fmt::color::white}, 
		};

		// Some reasonable default settings
		std::string_view destn = "stdout";		
		bool defaults_enabled = false;
		bool buffer_enabled = false; 

		size_t buffer_size = 15;
			
		[[noreturn]] void parse_toml_table() const noexcept; 
			
	};

	// Does the logging with log_message
	class log {	
	  public:
		[[nodiscard]] std::string_view to_string (const log& logger) const noexcept;
		[[noreturn]]  void log_message (timber::level current,
										std::string_view message, 
										const std::source_location loc = std::source_location::current()) const;
		
		log (const config& conf);
		~log() = default;
	
	  private:
		std::mutex _mtx;	
		level current_level;			
		config conf;
	};

 }
