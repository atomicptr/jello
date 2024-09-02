#include "../src/jello.hpp"

int main() {
    jello::configure(
        jello::Level::Info, // the debug message will no longer be shown :)
        "./test.log"        // the logs are now also printed to a file
    );

    jello::debug("Hello, World!");
    jello::info("Hello, World!");
    jello::warning("Hello, World!");
    jello::error("Hello, World!");
    jello::fatal("Hello, World!");

    return 0;
}
