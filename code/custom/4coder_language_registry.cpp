/*
4coder_language_registry.cpp - Language support plugin system implementation
*/

// TOP

////////////////////////////////
// Global Language Registry

global Language_Registry global_language_registry = {};

////////////////////////////////
// Language Registry Implementation

function void
language_registry_init(Application_Links *app){
    if (global_language_registry.arena.base_allocator == 0){
        global_language_registry.arena = make_arena_system();
        global_language_registry.first = 0;
        global_language_registry.last = 0;
        global_language_registry.count = 0;
    }
}

function void
language_register(Language_Support language){
    if (global_language_registry.arena.base_allocator == 0){
        // Registry not initialized - this is an error condition
        // In a production system, you might want to log this
        return;
    }
    
    // Check for duplicate registration by name
    for (Language_Registration_Node *existing = global_language_registry.first;
         existing != 0;
         existing = existing->next){
        if (string_match(existing->language.name, language.name)){
            // Language already registered, skip duplicate
            return;
        }
    }
    
    Arena *arena = &global_language_registry.arena;
    Language_Registration_Node *node = push_array(arena, Language_Registration_Node, 1);
    
    // Deep copy the language support struct
    node->language.name = push_string_copy(arena, language.name);
    
    // Copy extensions array
    node->language.extensions.count = language.extensions.count;
    node->language.extensions.strings = push_array(arena, String_Const_u8, language.extensions.count);
    for (i32 i = 0; i < language.extensions.count; ++i){
        node->language.extensions.strings[i] = push_string_copy(arena, language.extensions.strings[i]);
    }
    
    node->language.init_fn = language.init_fn;
    node->language.use_generic_lexer = language.use_generic_lexer;
    
    // Add to linked list
    node->next = 0;
    if (global_language_registry.last != 0){
        global_language_registry.last->next = node;
    }
    else{
        global_language_registry.first = node;
    }
    global_language_registry.last = node;
    global_language_registry.count += 1;
}

function Language_Support*
language_find_by_extension(String_Const_u8 extension){
    if (global_language_registry.arena.base_allocator == 0){
        // Registry not initialized
        return(0);
    }
    
    for (Language_Registration_Node *node = global_language_registry.first;
         node != 0;
         node = node->next){
        for (i32 i = 0; i < node->language.extensions.count; ++i){
            if (string_match(extension, node->language.extensions.strings[i])){
                return(&node->language);
            }
        }
    }
    return(0);
}

function Language_Registration_Node*
language_get_all(void){
    return(global_language_registry.first);
}

function i32
language_get_count(void){
    return(global_language_registry.count);
}

////////////////////////////////
// Built-in Language Registration

function void
language_register_cpp(Application_Links *app){
    Scratch_Block scratch(app);
    
    Language_Support cpp = {};
    cpp.name = string_u8_litexpr("C++");
    
    String_Const_u8 *ext_array = push_array(scratch, String_Const_u8, 5);
    ext_array[0] = string_u8_litexpr("cpp");
    ext_array[1] = string_u8_litexpr("h");
    ext_array[2] = string_u8_litexpr("c");
    ext_array[3] = string_u8_litexpr("hpp");
    ext_array[4] = string_u8_litexpr("cc");
    
    cpp.extensions.count = 5;
    cpp.extensions.strings = ext_array;
    cpp.init_fn = 0;  // No special init needed for C++
    cpp.use_generic_lexer = true;  // Use the C++ lexer
    
    language_register(cpp);
}

function void
language_register_python(Application_Links *app){
    Scratch_Block scratch(app);
    
    Language_Support python = {};
    python.name = string_u8_litexpr("Python");
    
    String_Const_u8 *ext_array = push_array(scratch, String_Const_u8, 1);
    ext_array[0] = string_u8_litexpr("py");
    
    python.extensions.count = 1;
    python.extensions.strings = ext_array;
    python.init_fn = 0;  // No special init for now
    python.use_generic_lexer = true;  // Use C++ lexer as fallback
    
    language_register(python);
}

function void
language_register_defaults(Application_Links *app){
    language_registry_init(app);
    language_register_cpp(app);
    language_register_python(app);
    
    // Can add more languages here:
    // language_register_javascript(app);
    // language_register_rust(app);
    // language_register_go(app);
    // etc.
}

// BOTTOM
