// 4coder_custom_commands.cpp - Custom user commands

CUSTOM_COMMAND_SIG(toggle_second_panel)
CUSTOM_DOC("Toggle between single panel and two-panel vertical split view.")
{
    // Count the number of open views/panels
    i32 view_count = 0;
    View_ID first_view = 0;
    for (View_ID view = get_view_next(app, 0, Access_Always);
         view != 0;
         view = get_view_next(app, view, Access_Always)){
        view_count++;
        if (first_view == 0){
            first_view = view;
        }
    }
    
    if (view_count == 1){
        // Only one panel open, create a vertical split
        open_panel_vsplit(app);
    }
    else if (view_count > 1){
        // Multiple panels open, close the current panel
        View_ID active_view = get_active_view(app, Access_Always);
        view_close(app, active_view);
    }
}
