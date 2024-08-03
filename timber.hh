# pragma once 

#include <chrono>
#include <string>
#include <sstream>
#include <fstream>
#include <mutex>
#include <experimental/source_location>
#include <unordered_map>
#include <iostream>
#include <iomanip>


namespace timber {
	
	enum class level { WARN, DEBUG, INFO, FATAL, };
	enum class destn { STDOUT, DISK, };
	enum class color { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, RESET, };	

	class logger {	
	  public:
		
		[[nodiscard]] std::string to_string (const level& current_level) const noexcept {

			switch (current_level) {
				case level::WARN:   return "[warning]";
				case level::DEBUG:  return "[debug]";
				case level::INFO:   return "[info]";
				case level::FATAL:  return "[fatal]";	
			} 		
			
			// somehow something else
			return "[unknown state]";
		}


		
        void set_color_for_log(color c) const noexcept {
            switch (c) {
                case color::BLACK:   std::cout << "\033[30m"; break;
                case color::RED:     std::cout << "\033[31m"; break;
                case color::GREEN:   std::cout << "\033[32m"; break;
                case color::YELLOW:  std::cout << "\033[33m"; break;
                case color::BLUE:    std::cout << "\033[34m"; break;
                case color::MAGENTA: std::cout << "\033[35m"; break;
                case color::CYAN:    std::cout << "\033[36m"; break;
                case color::WHITE:   std::cout << "\033[37m"; break;
				case color::RESET: 	 std::cout << "\033[0m";  break;
				default: 			 std::cout << "..."; 	  break;
            }
        }


		// Can remove nodiscard attribute if time isn't necessary for logs
		[[nodiscard]] std::string time_to_string () const noexcept {

			// Used :: instead of std:: for stuff from C-land? 
			::time_t current_time = std::chrono::system_clock::to_time_t (
											std::chrono::system_clock::now()
									);

			::tm* local_time = ::localtime(&current_time);
			std::stringstream ss;
			ss << std::put_time(local_time, "%Y-%m-%d, %H:%M:%S");
			return ss.str();
		}

	
		// do the logging
		void log (timber::level current_level,
				  timber::destn where,	
				  std::string_view message, 
				  const std::experimental::source_location loc 
					= std::experimental::source_location::current()) noexcept {
			
			std::lock_guard<std::mutex> lock(_mtx);

            std::string timestamp = time_to_string();
            std::string level_str = std::string(to_string(current_level));
            std::string location = "(FILE: " + std::string(loc.file_name()) + " @ LINE:" + std::string(std::to_string(loc.line())) +  ", in FUNC: " + std::string(loc.function_name()) + ")";

            if (where == destn::STDOUT) {
                std::cout << timestamp << " ";
                
                set_color_for_log(level_color_map.at(current_level));
                std::cout << level_str;
                
                // Reset to white for the rest of the message
                set_color_for_log(color::RESET);
                std::cout << " " << message << " " << location << std::endl;
            } else if (where == destn::DISK) {
                std::ofstream log_file("logfile", std::ios_base::app);
                if (log_file.is_open()) {
                    log_file << timestamp << " " << level_str << " " << message << " " << location << std::endl;
                }
            }
	

		}
	
		// To use this implement the << operator for a class, kinda like Debug trait in Rust
		template <class T>
		void log (timber::level current_level,
				  const T& thing, 
				  const std::experimental::source_location loc 
					= std::experimental::source_location::current()) noexcept {
		
			// Call the non-template function	
			std::stringstream ss;
			ss << thing;
			log(current_level, timber::destn::STDOUT, ss.str(), loc); 
		}
	
		logger  () = default;
		~logger () = default;
	
	  private:
		std::mutex _mtx;	
	
		// Colors can be changed through this map	
		inline static const std::unordered_map<level, color> level_color_map = {
			{level::WARN, color::YELLOW }, 
			{level::FATAL, color::RED} ,
			{level::INFO, color::MAGENTA} ,
			{level::DEBUG, color::BLUE} ,
		
		};	


	};
 }
