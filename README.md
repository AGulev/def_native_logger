# def_native_logger

Defold native logging extension for release builds. Works on **Android**, **iOS**, **macOS**, and **HTML5** (Emscripten).

## Supported Platforms

- **Android** - Uses Android's native logging system (`__android_log_print`)
- **iOS** - Uses `NSLog` for native iOS logging
- **macOS** - Uses `NSLog` for native macOS logging  
- **HTML5** - Uses browser console functions via Emscripten

## API

### `native_logger.log(log_level, message)`

Prints a message to the platform's native console.

**Parameters:**
- `log_level` (integer) - Log severity level
- `message` (string) - Message to log

**Log Levels:**
- `0` - DEBUG
- `1` - USER_DEBUG  
- `2` - INFO
- `3` - WARN
- `4` - ERROR
- `5` - FATAL

## Configuration

You can enable automatic logging of all Defold engine logs by adding this to your `game.project`:

```
[native_logger]
regular_logs = true
```

When enabled, all engine logs will be automatically forwarded to the native logging system.

## Example Usage

```lua
-- Log a debug message
native_logger.log(1, "Debug: Player position updated")

-- Log a warning
native_logger.log(3, "Warning: Low memory detected")

-- Log an error
native_logger.log(4, "Error: Failed to load texture")
```

## Platform-Specific Output

- **Android**: Logs appear in `adb logcat` with tag "defold"
- **iOS**: Logs appear in Xcode console and iOS Console.app
- **macOS**: Logs appear in Xcode console and macOS Console.app
- **HTML5**: Logs appear in browser developer console
