# jello

A tiny single file header only logging library for C++23

This library makes use of std::print and std::format so make sure your compiler supports this!

## Example

```cpp
// this is optional, will default to logging everything and not writing to log files
jello::configure(
    jello::Level::Info, // the debug message will no longer be shown :)
    "./test.log"        // the logs are now also printed to a file
);

jello::debug("Hello, World!");
jello::info("Hello, World!");
jello::warning("Hello, World!");
jello::error("Hello, World!");
jello::fatal("Hello, World!");
```

## Install

Just copy the file into your project and adjust accordingly

## License

BSD 0-Clause
