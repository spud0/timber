# pragma once 

#include <chrono>
#include <string>
#include <mutex>
#include <source_location>
#include <filesystem>
#include <expected>
#include <unordered_map>

// For TOML parsing
#include "./ext/toml.hh"

namespace timber {
	
	enum class level { WARN, DEBUG, INFO, FATAL, };
	enum class loc   { STDOUT, NET, DISK, };
	enum class color { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, };

	// The config for the logger
	class config {
	  public:
		static std::expected<config, std::system_error> read_from_toml(const std::filesystem::path& file_path);
		[[nodiscard]] const toml::table& get_config_table(void) const noexcept;
		
	  private:
		std::filesystem::path file_path;
		inline static const std::unordered_map<std::string, color> level_color_map = {
			{"\u001b[40m", color::BLACK }, {"\u001b[41m", color::RED},
			{"\u001b[42m", color::GREEN} , {"\u001b[43m", color::YELLOW},
			{"\u001b[44m", color::BLUE}  , {"\u001b[45m", color::MAGENTA},
			{"\u001b[46m", color::CYAN}  , {"\u001b[47m", color::WHITE}, 
		};
		toml::table config_table;	
	};

	// may have too much responsibility
	class log {	
	  public:
		[[nodiscard]] std::string_view to_string (const log& logger) const noexcept;
		[[nodiscard]] std::string log_message (std::string_view message, timber::level current, std::source_location loc) const;
		
		log (const config& conf);
		~log() = default;
	
	  private:
		std::mutex _mtx;	
		level current_level;			
		config conf;
	};

 }
