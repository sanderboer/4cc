/*
4coder_language_registry.h - Language support plugin system
*/

// TOP

#if !defined(FCODER_LANGUAGE_REGISTRY_H)
#define FCODER_LANGUAGE_REGISTRY_H

////////////////////////////////
// Language Support Types

typedef void Language_Init_Function(Application_Links *app);

struct Language_Support {
    String_Const_u8 name;
    String_Const_u8_Array extensions;
    Language_Init_Function *init_fn;
    b32 use_generic_lexer;  // If true, use the C++ lexer as fallback
};

struct Language_Registration_Node {
    Language_Registration_Node *next;
    Language_Support language;
};

struct Language_Registry {
    Arena arena;
    Language_Registration_Node *first;
    Language_Registration_Node *last;
    i32 count;
};

////////////////////////////////
// Language Registry API

// Initialize the global language registry
function void language_registry_init(Application_Links *app);

// Register a new language
function void language_register(Language_Support language);

// Find language support by file extension
function Language_Support* language_find_by_extension(String_Const_u8 extension);

// Get all registered languages
function Language_Registration_Node* language_get_all(void);

// Get language count
function i32 language_get_count(void);

////////////////////////////////
// Built-in Language Registration

// Register core languages (C++, Python, etc.)
function void language_register_defaults(Application_Links *app);

#endif

// BOTTOM
