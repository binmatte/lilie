### Documentation for `colie.h`

**`colie.h`** provides ANSI escape codes for color manipulation in terminal output, along with functions for setting text attributes.

#### Constants

- **Foreground Colors:**
    - `ANSI_FG_BLACK`
    - `ANSI_FG_RED`
    - `ANSI_FG_GREEN`
    - `ANSI_FG_YELLOW`
    - `ANSI_FG_BLUE`
    - `ANSI_FG_MAGENTA`
    - `ANSI_FG_CYAN`
    - `ANSI_FG_WHITE`

- **Background Colors:**
    - `ANSI_BG_BLACK`
    - `ANSI_BG_RED`
    - `ANSI_BG_GREEN`
    - `ANSI_BG_YELLOW`
    - `ANSI_BG_BLUE`
    - `ANSI_BG_MAGENTA`
    - `ANSI_BG_CYAN`
    - `ANSI_BG_WHITE`

- **Text Attributes:**
    - `ANSI_RESET`
    - `ANSI_BOLD`
    - `ANSI_DIM`
    - `ANSI_ITALIC`
    - `ANSI_UNDERLINE`
    - `ANSI_BLINK`
    - `ANSI_INVERT`
    - `ANSI_HIDDEN`
    - `ANSI_STRIKE`

#### Enumerations

- `ColieColor`: Enum for basic colors.
  ```c
  typedef enum {
      COLIE_BLACK,
      COLIE_RED,
      COLIE_GREEN,
      COLIE_YELLOW,
      COLIE_BLUE,
      COLIE_MAGENTA,
      COLIE_CYAN,
      COLIE_WHITE
  } ColieColor;
  ```

- `ColieAttr`: Enum for text attributes.
  ```c
  typedef enum {
      COLIE_RESET,
      COLIE_BOLD,
      COLIE_DIM,
      COLIE_ITALIC,
      COLIE_UNDERLINE,
      COLIE_BLINK,
      COLIE_INVERT,
      COLIE_HIDDEN,
      COLIE_STRIKE,
  } ColieAttr;
  ```

#### Functions

- **Basic Color Functions:**
    - `const char * colieFG(ColieColor color);`
    - `const char * colieBG(ColieColor color);`

- **Extended Color Functions (256 Colors):**
    - `const char * colieFGExtended(unsigned char color);`
    - `const char * colieBGExtended(unsigned char color);`

- **RGB Color Functions:**
    - `const char * colieFGRGB(unsigned char r, unsigned char g, unsigned char b);`
    - `const char * colieBGRGB(unsigned char r, unsigned char g, unsigned char b);`

- **Text Attribute Functions:**
    - `const char * colieAttr(ColieAttr attr);`

### Documentation for `bugie.h`

**`bugie.h`** is a simple logging library with customizable log levels, time formatting, color support, and output stream control.

#### Constants

- **Buffer Size:**
    - `#define BUGIE_LOG_BUFFER_SIZE 4096`

#### Enumerations

- `BugieLogLevel`: Enum for log levels.
  ```c
  typedef enum BugieLogLevel {
      BUGIE_LOG_LEVEL_TRACE,
      BUGIE_LOG_LEVEL_DEBUG,
      BUGIE_LOG_LEVEL_INFO,
      BUGIE_LOG_LEVEL_WARN,
      BUGIE_LOG_LEVEL_ERROR,
      BUGIE_LOG_LEVEL_FATAL
  } BugieLogLevel;
  ```

- `BugieTimeFormat`: Enum for time formats.
  ```c
  typedef enum BugieTimeFormat {
      BUGIE_TIME_FORMAT_HHMMSS,
      BUGIE_TIME_FORMAT_YYYYMMDDHHMMSS,
      BUGIE_TIME_FORMAT_DDMMYYYYHHMMSS,
      BUGIE_TIME_FORMAT_CUSTOM,
  } BugieTimeFormat;
  ```

#### Global Variables

- `static BugieTimeFormat bugie_time_format`: Holds the current time format.
- `static const char * bugie_time_format_string`: Holds the custom time format string.
- `static bool bugie_use_color`: Flag to enable/disable color in logs.
- `static FILE * bugie_stream`: Holds the current output stream.

#### Functions

- **Initialization:**
    - `void bugieInit(void);`: Initializes the logging library with default settings.

- **Configuration:**
    - `void bugieSetTimeFormat(BugieTimeFormat time_format, const char * time_format_string);`: Sets the time format for log entries.
    - `void bugieSetStream(FILE * stream);`: Sets the output stream for log entries.
    - `void bugieEnableColor(bool state);`: Enables or disables color in log entries.

- **Logging:**
    - `void bugieLog(BugieLogLevel level, const char * context, const char * message);`: Logs a simple message.
    - `void bugieLogF(BugieLogLevel level, const char * context, const char * format, ...);`: Logs a formatted message with `printf`-style format specifiers.

### Example Usage

#### Logging with Bugie:

```c
#include "bugie.h"
#include "colie.h"

int main() {
    bugieInit(); // Initialize the logging library
    bugieSetTimeFormat(BUGIE_TIME_FORMAT_YYYYMMDDHHMMSS, NULL); // Set time format

    bugieLog(BUGIE_LOG_LEVEL_INFO, "MyModule", "Starting application...");
    bugieLogF(BUGIE_LOG_LEVEL_ERROR, "MyModule", "Error: %s at line %d", error_message, line_number); 
    // ...
    return 0;
}
```

#### Coloring Output with Colie:

```c
#include "colie.h"

int main() {
    printf("%sHello, world!%s\n", colieFG(COLIE_GREEN), ANSI_RESET); 
    // ...
    return 0;
}
```

### License

This library is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

### Contribution

Contributions are welcome! Please feel free to submit pull requests or open issues.