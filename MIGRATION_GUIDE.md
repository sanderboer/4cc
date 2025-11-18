# 4coder Refactoring Migration Guide

**Version**: November 2025 Refactoring  
**Compatibility**: Fully backward compatible  
**Action Required**: None (optional updates recommended)

---

## Overview

This guide helps users migrate to the refactored 4coder codebase. **All changes are backward compatible** - your existing setup will continue to work without modifications.

---

## What Changed

### 1. Language Support System

**Old System**: Hardcoded language detection in core hooks  
**New System**: Plugin-based language registry

**Impact**: None - all existing languages work as before  
**Benefit**: Can now add custom languages without modifying core code

### 2. Keybinding System

**Old System**: Separate `4coder_default_map.cpp` and `4coder_mac_map.cpp`  
**New System**: Unified `4coder_unified_map.cpp` with platform abstraction

**Impact**: None - all keybindings work identically  
**Benefit**: Fixed macOS Cmd+P conflict, easier to customize

### 3. ARM64 Mac Support

**Old System**: Intel-only builds (Rosetta translation on Apple Silicon)  
**New System**: Native ARM64 builds with auto-detection

**Impact**: Automatic - builds detect your CPU architecture  
**Benefit**: Better performance on Apple Silicon Macs

---

## Do I Need to Do Anything?

### For Most Users: **No Action Required**

Everything works exactly as before. Your existing:
- Configuration files (`.4coder`) work unchanged
- Custom keybindings work unchanged
- Plugins and customizations work unchanged
- Build scripts work unchanged

### For Customizers: **Optional Updates**

If you've customized 4coder, consider these optional improvements:

---

## Optional: Migrate to Unified Keybindings

If you've created custom keybindings in `4coder_default_map.cpp` or `4coder_mac_map.cpp`:

### Before (Old System)
```cpp
// Had to edit TWO files:
// 4coder_default_map.cpp:
Bind(my_custom_command, KeyCode_K, KeyCode_Control);

// 4coder_mac_map.cpp:
Bind(my_custom_command, KeyCode_K, KeyCode_Command);
```

### After (New System)
```cpp
// Edit ONE file (4coder_unified_map.cpp):
Bind(my_custom_command, KeyCode_K, Mod_Primary);
// Works correctly on all platforms!
```

**Benefits**:
- Edit one file instead of two
- Automatic platform adaptation
- Fewer merge conflicts

---

## Optional: Add Custom Language Support

If you want to add support for a new programming language:

### Before (Old System)
You had to modify `4coder_default_hooks.cpp` and add hardcoded checks:

```cpp
// Modify core file - risky and hard to maintain
if (string_match(ext, "myext")) {
    treat_as_code = true;
}
```

### After (New System)
Add a simple registration function in `4coder_language_registry.cpp`:

```cpp
function void language_register_mylang(Application_Links *app){
    Scratch_Block scratch(app);
    Language_Support mylang = {};
    mylang.name = string_u8_litexpr("MyLanguage");
    
    String_Const_u8 *ext = push_array(scratch, String_Const_u8, 1);
    ext[0] = string_u8_litexpr("myext");
    
    mylang.extensions.count = 1;
    mylang.extensions.strings = ext;
    mylang.use_generic_lexer = true;
    
    language_register(mylang);
}

// Then call in language_register_defaults():
function void language_register_defaults(Application_Links *app){
    language_registry_init(app);
    language_register_cpp(app);
    language_register_python(app);
    language_register_mylang(app);  // Add your language
}
```

**Benefits**:
- No modification to core hooks
- Cleaner separation of concerns
- Easy to maintain and update

**Alternative**: Just add to `config.4coder` without recompiling:
```
treat_as_code = ".cpp.c.hpp.h.cc.myext";
```

---

## Building for Apple Silicon (ARM64)

### Automatic Detection

The build system now auto-detects your CPU:

```bash
cd code/bin
./build-mac.sh  # Automatically builds ARM64 on Apple Silicon
```

### Manual ARM64 Build

If auto-detection fails, you can force ARM64:

```bash
cd code/custom/bin
./buildsuper_arm64-mac.sh
```

---

## Configuration Files

### No Changes Required

Your existing `config.4coder` works unchanged:

```
mapping = "default";         # Still works
treat_as_code = ".cpp.c..."; # Still works
```

### New Features Available

The config now supports `.py` by default:

```
treat_as_code = ".cpp.c.hpp.h.cc.cs.java.rs.glsl.m.mm.py";
```

---

## Custom Commands

If you've added custom commands, they work unchanged. Example:

### Your Custom Command File
```cpp
// my_custom_commands.cpp
CUSTOM_COMMAND_SIG(my_command)
CUSTOM_DOC("My custom functionality")
{
    // Your code here
}
```

### Include It
```cpp
// 4coder_default_include.cpp
#include "my_custom_commands.cpp"
```

**No changes needed** - custom commands work exactly as before.

---

## Troubleshooting

### Issue: Build fails on Apple Silicon

**Solution**: Make sure you have the ARM64 freetype library:

```bash
brew install freetype
```

The build system will automatically find it at `/opt/homebrew/lib`.

### Issue: Custom keybindings not working

**Check**: Are you still using the old map files?

**Solution**: Either:
1. Continue using old files (they still work)
2. Migrate to `4coder_unified_map.cpp` (recommended)

### Issue: Language not recognized

**Check**: Is it in your `config.4coder`?

```
treat_as_code = ".cpp.c.hpp.h...your_extension";
```

**Or**: Add it to the language registry (see above).

---

## Testing Your Setup

### 1. Build Test
```bash
cd code/bin
./build-mac.sh
# Should complete with no errors
```

### 2. Python File Test
```bash
# Open any .py file in 4coder
# Should be recognized as code (syntax highlighting, etc.)
```

### 3. Keybinding Test
On macOS:
- `Cmd+P` should toggle second panel (not open file)
- `Cmd+O` should open file

On Windows/Linux:
- `Ctrl+P` should toggle second panel
- `Ctrl+O` should open file

---

## Rollback Instructions

If you need to rollback (though backward compatible):

### Option 1: Use Old Map Files

In `4coder_default_bindings.cpp`:

```cpp
// Old way - still works:
#if OS_MAC
    setup_mac_mapping(mapping);
#else
    setup_default_mapping(mapping);
#endif

// New way (current):
setup_unified_mapping(mapping, global_map_id, file_map_id, code_map_id);
```

### Option 2: Git Revert

```bash
git revert <commit-hash>
```

Commits to potentially revert:
- `26c54c08` - Documentation updates
- `11077cb5` - ARM64 support
- `b9500fab` - Code quality improvements
- `3ae11b76` - Main refactoring

---

## Getting Help

### Check Documentation
- `REFACTOR_SUMMARY.md` - Detailed technical changes
- `CODE_REVIEW.md` - Architecture review
- `BUILD_VERIFICATION.md` - Build instructions

### Issues

If you encounter problems:
1. Check this migration guide
2. Verify your setup matches the troubleshooting section
3. File an issue with:
   - Your OS and architecture (Intel vs ARM64)
   - Build output
   - Error messages

---

## Summary

**Good News**: Everything is backward compatible!

**No action required** unless you want to:
- ✅ Simplify custom keybindings (use unified map)
- ✅ Add new language support (use registry)
- ✅ Get better ARM64 performance (automatic)

**Bottom line**: Update when convenient, or keep using your existing setup.

---

**Questions?** Check `REFACTOR_SUMMARY.md` for technical details.
