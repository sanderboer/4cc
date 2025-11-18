/*
4coder_unified_map.cpp - Platform-unified keyboard bindings
*/

// TOP

// Platform-aware modifier key abstractions
// These macros resolve to the correct modifier key based on the platform
#if OS_MAC
    #define Mod_Primary   KeyCode_Command  // Cmd on Mac
    #define Mod_Secondary KeyCode_Control  // Ctrl on Mac (secondary operations)
    #define Mod_Tertiary  KeyCode_Alt      // Alt on Mac
#else
    #define Mod_Primary   KeyCode_Control  // Ctrl on Windows/Linux
    #define Mod_Secondary KeyCode_Alt      // Alt on Windows/Linux
    #define Mod_Tertiary  KeyCode_Alt      // Alt on Windows/Linux
#endif

function void
setup_unified_mapping(Mapping *mapping, i64 global_id, i64 file_id, i64 code_id){
    MappingScope();
    SelectMapping(mapping);
    
    ////////////////////////////////
    // Global Map
    SelectMap(global_id);
    
    // Keyboard macros
    Bind(keyboard_macro_start_recording , KeyCode_U, Mod_Primary);
    Bind(keyboard_macro_finish_recording, KeyCode_U, Mod_Primary, KeyCode_Shift);
#if OS_MAC
    Bind(keyboard_macro_replay,           KeyCode_U, Mod_Secondary);
#else
    Bind(keyboard_macro_replay,           KeyCode_U, Mod_Secondary);
#endif
    
    // Panel management
    Bind(change_active_panel,           KeyCode_Comma, Mod_Primary);
    Bind(change_active_panel_backwards, KeyCode_Comma, Mod_Primary, KeyCode_Shift);
    Bind(toggle_second_panel,           KeyCode_P, Mod_Primary);
    
    // File operations
    Bind(interactive_new,               KeyCode_N, Mod_Primary);
    Bind(interactive_open_or_new,       KeyCode_O, Mod_Primary);
#if OS_MAC
    Bind(open_in_other,                 KeyCode_O, Mod_Secondary);
#else
    Bind(open_in_other,                 KeyCode_O, Mod_Secondary);
#endif
    Bind(interactive_kill_buffer,       KeyCode_K, Mod_Primary);
    Bind(interactive_switch_buffer,     KeyCode_I, Mod_Primary);
    Bind(project_go_to_root_directory,  KeyCode_H, Mod_Primary);
    Bind(save_all_dirty_buffers,        KeyCode_S, Mod_Primary, KeyCode_Shift);
    
    // Build panel
#if OS_MAC
    Bind(change_to_build_panel,         KeyCode_Period, Mod_Secondary);
    Bind(close_build_panel,             KeyCode_Comma, Mod_Secondary);
    Bind(goto_next_jump,                KeyCode_N, Mod_Secondary);
    Bind(goto_prev_jump,                KeyCode_N, Mod_Secondary, KeyCode_Shift);
    Bind(build_in_build_panel,          KeyCode_M, Mod_Secondary);
    Bind(goto_first_jump,               KeyCode_M, Mod_Secondary, KeyCode_Shift);
    Bind(toggle_filebar,                KeyCode_B, Mod_Secondary);
#else
    Bind(change_to_build_panel,         KeyCode_Period, Mod_Secondary);
    Bind(close_build_panel,             KeyCode_Comma, Mod_Secondary);
    Bind(goto_next_jump,                KeyCode_N, Mod_Secondary);
    Bind(goto_prev_jump,                KeyCode_N, Mod_Secondary, KeyCode_Shift);
    Bind(build_in_build_panel,          KeyCode_M, Mod_Secondary);
    Bind(goto_first_jump,               KeyCode_M, Mod_Secondary, KeyCode_Shift);
    Bind(toggle_filebar,                KeyCode_B, Mod_Secondary);
#endif
    
    // CLI commands
#if OS_MAC
    Bind(execute_any_cli,               KeyCode_Z, Mod_Secondary);
    Bind(execute_previous_cli,          KeyCode_Z, Mod_Secondary, KeyCode_Shift);
    Bind(command_lister,                KeyCode_X, Mod_Secondary);
    Bind(project_command_lister,        KeyCode_X, Mod_Secondary, KeyCode_Shift);
#else
    Bind(execute_any_cli,               KeyCode_Z, Mod_Secondary);
    Bind(execute_previous_cli,          KeyCode_Z, Mod_Secondary, KeyCode_Shift);
    Bind(command_lister,                KeyCode_X, Mod_Secondary);
    Bind(project_command_lister,        KeyCode_X, Mod_Secondary, KeyCode_Shift);
#endif
    
    // Navigation
    Bind(quick_swap_buffer,             KeyCode_BackwardSlash, Mod_Primary);
#if OS_MAC
    Bind(jump_to_last_point,            KeyCode_P, Mod_Primary);
    Bind(list_all_functions_current_buffer, KeyCode_I, Mod_Primary, KeyCode_Shift);
#else
    Bind(jump_to_last_point,            KeyCode_P, Mod_Primary);
    Bind(list_all_functions_current_buffer_lister, KeyCode_I, Mod_Primary, KeyCode_Shift);
#endif
    
    // Function keys
    Bind(exit_4coder,          KeyCode_F4, Mod_Tertiary);
    Bind(project_fkey_command, KeyCode_F1);
    Bind(project_fkey_command, KeyCode_F2);
    Bind(project_fkey_command, KeyCode_F3);
    Bind(project_fkey_command, KeyCode_F4);
    Bind(project_fkey_command, KeyCode_F5);
    Bind(project_fkey_command, KeyCode_F6);
    Bind(project_fkey_command, KeyCode_F7);
    Bind(project_fkey_command, KeyCode_F8);
    Bind(project_fkey_command, KeyCode_F9);
    Bind(project_fkey_command, KeyCode_F10);
    Bind(project_fkey_command, KeyCode_F11);
    Bind(project_fkey_command, KeyCode_F12);
    Bind(project_fkey_command, KeyCode_F13);
    Bind(project_fkey_command, KeyCode_F14);
    Bind(project_fkey_command, KeyCode_F15);
    Bind(project_fkey_command, KeyCode_F16);
    
    ////////////////////////////////
    // File Map
    SelectMap(file_id);
    
    // Basic navigation
    Bind(delete_char,            KeyCode_Delete);
    Bind(backspace_char,         KeyCode_Backspace);
    Bind(move_up,                KeyCode_Up);
    Bind(move_down,              KeyCode_Down);
    Bind(move_left,              KeyCode_Left);
    Bind(move_right,             KeyCode_Right);
    Bind(seek_end_of_line,       KeyCode_End);
    Bind(seek_beginning_of_line, KeyCode_Home);
    Bind(page_up,                KeyCode_PageUp);
    Bind(page_down,              KeyCode_PageDown);
    
    // File-level navigation
#if OS_MAC
    Bind(goto_beginning_of_file, KeyCode_PageUp, Mod_Primary);
    Bind(goto_end_of_file,       KeyCode_PageDown, Mod_Primary);
    Bind(move_up_to_blank_line_end,        KeyCode_Up, Mod_Primary);
    Bind(move_down_to_blank_line_end,      KeyCode_Down, Mod_Primary);
    Bind(move_left_whitespace_boundary,    KeyCode_Left, Mod_Primary);
    Bind(move_right_whitespace_boundary,   KeyCode_Right, Mod_Primary);
#else
    Bind(goto_beginning_of_file, KeyCode_PageUp, Mod_Primary);
    Bind(goto_end_of_file,       KeyCode_PageDown, Mod_Primary);
    Bind(move_up_to_blank_line_end,        KeyCode_Up, Mod_Primary);
    Bind(move_down_to_blank_line_end,      KeyCode_Down, Mod_Primary);
    Bind(move_left_whitespace_boundary,    KeyCode_Left, Mod_Primary);
    Bind(move_right_whitespace_boundary,   KeyCode_Right, Mod_Primary);
#endif
    
    // Line movement
#if OS_MAC
    Bind(move_line_up,                     KeyCode_Up, Mod_Tertiary);
    Bind(move_line_down,                   KeyCode_Down, Mod_Tertiary);
#else
    Bind(move_line_up,                     KeyCode_Up, Mod_Tertiary);
    Bind(move_line_down,                   KeyCode_Down, Mod_Tertiary);
#endif
    
    // Delete operations
#if OS_MAC
    Bind(backspace_alpha_numeric_boundary, KeyCode_Backspace, Mod_Primary);
    Bind(delete_alpha_numeric_boundary,    KeyCode_Delete, Mod_Primary);
    Bind(snipe_backward_whitespace_or_token_boundary, KeyCode_Backspace, Mod_Secondary);
    Bind(snipe_forward_whitespace_or_token_boundary,  KeyCode_Delete, Mod_Secondary);
#else
    Bind(backspace_alpha_numeric_boundary, KeyCode_Backspace, Mod_Primary);
    Bind(delete_alpha_numeric_boundary,    KeyCode_Delete, Mod_Primary);
    Bind(snipe_backward_whitespace_or_token_boundary, KeyCode_Backspace, Mod_Secondary);
    Bind(snipe_forward_whitespace_or_token_boundary,  KeyCode_Delete, Mod_Secondary);
#endif
    
    // Mark and editing
#if OS_MAC
    Bind(set_mark,                    KeyCode_Space, Mod_Secondary);
    Bind(set_mark,                    KeyCode_ForwardSlash, Mod_Primary);
#else
    Bind(set_mark,                    KeyCode_Space, Mod_Primary);
#endif
    
    // Standard editing commands (Cmd on Mac, Ctrl elsewhere)
    Bind(replace_in_range,            KeyCode_A, Mod_Primary);
    Bind(copy,                        KeyCode_C, Mod_Primary);
    Bind(delete_range,                KeyCode_D, Mod_Primary);
    Bind(delete_line,                 KeyCode_D, Mod_Primary, KeyCode_Shift);
    Bind(center_view,                 KeyCode_E, Mod_Primary);
    Bind(left_adjust_view,            KeyCode_E, Mod_Primary, KeyCode_Shift);
    Bind(search,                      KeyCode_F, Mod_Primary);
    Bind(list_all_locations,          KeyCode_F, Mod_Primary, KeyCode_Shift);
#if OS_MAC
    Bind(list_all_substring_locations_case_insensitive, KeyCode_F, Mod_Secondary);
#else
    Bind(list_all_substring_locations_case_insensitive, KeyCode_F, Mod_Secondary);
#endif
    Bind(goto_line,                   KeyCode_G, Mod_Primary);
    Bind(list_all_locations_of_selection,  KeyCode_G, Mod_Primary, KeyCode_Shift);
    Bind(snippet_lister,              KeyCode_J, Mod_Primary);
    Bind(kill_buffer,                 KeyCode_K, Mod_Primary, KeyCode_Shift);
    Bind(duplicate_line,              KeyCode_L, Mod_Primary);
    Bind(cursor_mark_swap,            KeyCode_M, Mod_Primary);
    Bind(reopen,                      KeyCode_O, Mod_Primary, KeyCode_Shift);
    Bind(query_replace,               KeyCode_Q, Mod_Primary);
    Bind(query_replace_identifier,    KeyCode_Q, Mod_Primary, KeyCode_Shift);
#if OS_MAC
    Bind(query_replace_selection,     KeyCode_Q, Mod_Secondary);
#else
    Bind(query_replace_selection,     KeyCode_Q, Mod_Secondary);
#endif
    Bind(reverse_search,              KeyCode_R, Mod_Primary);
    Bind(save,                        KeyCode_S, Mod_Primary);
    Bind(save_all_dirty_buffers,      KeyCode_S, Mod_Primary, KeyCode_Shift);
    Bind(search_identifier,           KeyCode_T, Mod_Primary);
    Bind(list_all_locations_of_identifier, KeyCode_T, Mod_Primary, KeyCode_Shift);
    Bind(paste_and_indent,            KeyCode_V, Mod_Primary);
    Bind(paste_next_and_indent,       KeyCode_V, Mod_Primary, KeyCode_Shift);
    Bind(cut,                         KeyCode_X, Mod_Primary);
    Bind(redo,                        KeyCode_Y, Mod_Primary);
    Bind(undo,                        KeyCode_Z, Mod_Primary);
    Bind(view_buffer_other_panel,     KeyCode_1, Mod_Primary);
    Bind(swap_panels,                 KeyCode_2, Mod_Primary);
    Bind(if_read_only_goto_position,  KeyCode_Return);
    Bind(if_read_only_goto_position_same_panel, KeyCode_Return, KeyCode_Shift);
    Bind(view_jump_list_with_lister,  KeyCode_Period, Mod_Primary, KeyCode_Shift);
    
    ////////////////////////////////
    // Code Map
    SelectMap(code_id);
    ParentMap(file_id);
    
    // Code-specific navigation
#if OS_MAC
    Bind(move_left_alpha_numeric_boundary,           KeyCode_Left, Mod_Primary);
    Bind(move_right_alpha_numeric_boundary,          KeyCode_Right, Mod_Primary);
    Bind(move_left_alpha_numeric_or_camel_boundary,  KeyCode_Left, Mod_Secondary);
    Bind(move_right_alpha_numeric_or_camel_boundary, KeyCode_Right, Mod_Secondary);
#else
    Bind(move_left_alpha_numeric_boundary,           KeyCode_Left, Mod_Primary);
    Bind(move_right_alpha_numeric_boundary,          KeyCode_Right, Mod_Primary);
    Bind(move_left_alpha_numeric_or_camel_boundary,  KeyCode_Left, Mod_Secondary);
    Bind(move_right_alpha_numeric_or_camel_boundary, KeyCode_Right, Mod_Secondary);
#endif
    
    // Code editing
    Bind(comment_line_toggle,        KeyCode_Semicolon, Mod_Primary);
    Bind(word_complete,              KeyCode_Tab);
    Bind(auto_indent_range,          KeyCode_Tab, Mod_Primary);
    Bind(auto_indent_line_at_cursor, KeyCode_Tab, KeyCode_Shift);
    Bind(word_complete_drop_down,    KeyCode_Tab, KeyCode_Shift, Mod_Primary);
    
    // Code snippets and templates
#if OS_MAC
    Bind(write_block,                KeyCode_R, Mod_Secondary);
    Bind(write_todo,                 KeyCode_T, Mod_Secondary);
    Bind(write_note,                 KeyCode_Y, Mod_Secondary);
    Bind(list_all_locations_of_type_definition,               KeyCode_D, Mod_Secondary);
    Bind(list_all_locations_of_type_definition_of_identifier, KeyCode_T, Mod_Secondary, KeyCode_Shift);
#else
    Bind(write_block,                KeyCode_R, Mod_Secondary);
    Bind(write_todo,                 KeyCode_T, Mod_Secondary);
    Bind(write_note,                 KeyCode_Y, Mod_Secondary);
    Bind(list_all_locations_of_type_definition,               KeyCode_D, Mod_Secondary);
    Bind(list_all_locations_of_type_definition_of_identifier, KeyCode_T, Mod_Secondary, KeyCode_Shift);
#endif
    
    // Scope operations
    Bind(open_long_braces,           KeyCode_LeftBracket, Mod_Primary);
    Bind(open_long_braces_semicolon, KeyCode_LeftBracket, Mod_Primary, KeyCode_Shift);
    Bind(open_long_braces_break,     KeyCode_RightBracket, Mod_Primary, KeyCode_Shift);
#if OS_MAC
    Bind(select_surrounding_scope,   KeyCode_LeftBracket, Mod_Secondary);
    Bind(select_surrounding_scope_maximal, KeyCode_LeftBracket, Mod_Secondary, KeyCode_Shift);
    Bind(select_prev_scope_absolute, KeyCode_RightBracket, Mod_Secondary);
    Bind(select_prev_top_most_scope, KeyCode_RightBracket, Mod_Secondary, KeyCode_Shift);
    Bind(select_next_scope_absolute, KeyCode_Quote, Mod_Secondary);
    Bind(select_next_scope_after_current, KeyCode_Quote, Mod_Secondary, KeyCode_Shift);
    Bind(place_in_scope,             KeyCode_ForwardSlash, Mod_Secondary);
    Bind(delete_current_scope,       KeyCode_Minus, Mod_Secondary);
    Bind(if0_off,                    KeyCode_I, Mod_Secondary);
    Bind(open_file_in_quotes,        KeyCode_1, Mod_Secondary);
    Bind(open_matching_file_cpp,     KeyCode_2, Mod_Secondary);
#else
    Bind(select_surrounding_scope,   KeyCode_LeftBracket, Mod_Secondary);
    Bind(select_surrounding_scope_maximal, KeyCode_LeftBracket, Mod_Secondary, KeyCode_Shift);
    Bind(select_prev_scope_absolute, KeyCode_RightBracket, Mod_Secondary);
    Bind(select_prev_top_most_scope, KeyCode_RightBracket, Mod_Secondary, KeyCode_Shift);
    Bind(select_next_scope_absolute, KeyCode_Quote, Mod_Secondary);
    Bind(select_next_scope_after_current, KeyCode_Quote, Mod_Secondary, KeyCode_Shift);
    Bind(place_in_scope,             KeyCode_ForwardSlash, Mod_Secondary);
    Bind(delete_current_scope,       KeyCode_Minus, Mod_Secondary);
    Bind(if0_off,                    KeyCode_I, Mod_Secondary);
    Bind(open_file_in_quotes,        KeyCode_1, Mod_Secondary);
    Bind(open_matching_file_cpp,     KeyCode_2, Mod_Secondary);
#endif
    
    // Code utilities
    Bind(write_zero_struct,          KeyCode_0, Mod_Primary);
    Bind(jump_to_definition_at_cursor, KeyCode_W, Mod_Primary);
}

// BOTTOM
