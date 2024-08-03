#include "../timber.hh" // Assuming the header file is named timber.hh
#include <thread>
#include <chrono>

// Simulating a simple task
void perform_task(timber::logger& log, int task_id) {
    log.log(timber::level::INFO, timber::destn::STDOUT, "Starting task " + std::to_string(task_id));
    
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    if (task_id % 3 == 0) {
        log.log(timber::level::WARN, timber::destn::STDOUT, "Task " + std::to_string(task_id) + " encountered a warning");
    } else {
        log.log(timber::level::DEBUG, timber::destn::STDOUT, "Task " + std::to_string(task_id) + " completed successfully");
    }
}

int main() {
    timber::logger log;

    log.log(timber::level::INFO, timber::destn::STDOUT, "Application started");

    for (int i = 1; i <= 5; ++i) {
        perform_task(log, i);
    }

    try {
        throw std::runtime_error("Simulated error");
    } catch (const std::exception& e) {
        log.log(timber::level::FATAL, timber::destn::STDOUT, "Caught exception: " + std::string(e.what()));
    }

    log.log(timber::level::INFO, timber::destn::STDOUT, "Application finished");

    return 0;
}

