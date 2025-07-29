#include "bsr.h"

typedef struct 
{
    struct mfb_window *window; // window pointer
    char *title; // window title
    char* buffer;
    uint8_t keys[350]; // key states
    uint8_t key_mods[6]; // shift, ctrl, alt, super, caps lock, num lock
    float mouse_scroll_delta_x; // mouse scroll x
    float mouse_scroll_delta_y; // mouse scroll y
    char character; // last character input
    int width; // window width
    int height; // window height
    uint8_t flags;

} BSRWindow;

BruterList *bsr_windows = NULL;

// callbacks

static void resize(struct mfb_window *window, int width, int height)
{
    uint32_t x = 0;
    uint32_t y = 0;
    BSRWindow *current_window = (BSRWindow *)mfb_get_user_data(window);


    if(width > current_window->width)
    {
        x = (width - current_window->width) >> 1;
        width = current_window->width;
    }
    if(height > current_window->height)
    {
        y = (height - current_window->height) >> 1;
        height = current_window->height;
    }
    current_window->buffer = realloc(current_window->buffer, width * height * 4); // reallocate buffer for the new window size
    if (current_window->buffer == NULL) {
        printf("Failed to reallocate buffer for window\n");
        return;
    }
    current_window->width = width;
    current_window->height = height;
    mfb_set_viewport(window, x, y, width, height);
}

static void keyboard(struct mfb_window *window, mfb_key key, mfb_key_mod mod, bool isPressed) 
{
    BSRWindow *current_window = (BSRWindow *)mfb_get_user_data(window);
    current_window->keys[key] = isPressed ? 1 : 0;
    current_window->key_mods[0] = (mod & KB_MOD_SHIFT) ? 1 : 0;
    current_window->key_mods[1] = (mod & KB_MOD_CONTROL) ? 1 : 0;
    current_window->key_mods[2] = (mod & KB_MOD_ALT) ? 1 : 0;
    current_window->key_mods[3] = (mod & KB_MOD_SUPER) ? 1 : 0;
    current_window->key_mods[4] = (mod & KB_MOD_CAPS_LOCK) ? 1 : 0;
    current_window->key_mods[5] = (mod & KB_MOD_NUM_LOCK) ? 1 : 0;
}

static void char_input(struct mfb_window *window, unsigned int charCode) 
{
    BSRWindow *current_window = (BSRWindow *)mfb_get_user_data(window);
    current_window->character = (char)charCode;
}

static void mouse_btn(struct mfb_window *window, mfb_mouse_button button, mfb_key_mod mod, bool isPressed) 
{
    BSRWindow *current_window = (BSRWindow *)mfb_get_user_data(window);
    if (button == MOUSE_LEFT) 
    {
        current_window->keys[MOUSE_BTN_1] = isPressed ? 1 : 0;
    } 
    else if (button == MOUSE_RIGHT) 
    {
        current_window->keys[MOUSE_BTN_2] = isPressed ? 1 : 0;
    } 
    else if (button == MOUSE_MIDDLE) 
    {
        current_window->keys[MOUSE_BTN_3] = isPressed ? 1 : 0;
    } 
    else if (button >= MOUSE_BTN_4 && button <= MOUSE_BTN_7) 
    {
        current_window->keys[button] = isPressed ? 1 : 0;
    }

    current_window->key_mods[0] = (mod & KB_MOD_SHIFT) ? 1 : 0;
    current_window->key_mods[1] = (mod & KB_MOD_CONTROL) ? 1 : 0;
    current_window->key_mods[2] = (mod & KB_MOD_ALT) ? 1 : 0;
    current_window->key_mods[3] = (mod & KB_MOD_SUPER) ? 1 : 0;
    current_window->key_mods[4] = (mod & KB_MOD_CAPS_LOCK) ? 1 : 0;
    current_window->key_mods[5] = (mod & KB_MOD_NUM_LOCK) ? 1 : 0;
}

static void mouse_scroll(struct mfb_window *window, mfb_key_mod mod, float deltaX, float deltaY) 
{
    BSRWindow *current_window = (BSRWindow *)mfb_get_user_data(window);
    current_window->mouse_scroll_delta_x += deltaX;
    current_window->mouse_scroll_delta_y += deltaY;

    current_window->key_mods[0] = (mod & KB_MOD_SHIFT) ? 1 : 0;
    current_window->key_mods[1] = (mod & KB_MOD_CONTROL) ? 1 : 0;
    current_window->key_mods[2] = (mod & KB_MOD_ALT) ? 1 : 0;
    current_window->key_mods[3] = (mod & KB_MOD_SUPER) ? 1 : 0;
    current_window->key_mods[4] = (mod & KB_MOD_CAPS_LOCK) ? 1 : 0;
    current_window->key_mods[5] = (mod & KB_MOD_NUM_LOCK) ? 1 : 0;
}

// functions

BR_FUNCTION(bsr_new_window) 
{
    char *title = br_arg_get(context, args, 0).p;
    int width = br_arg_get(context, args, 1).i;
    int height = br_arg_get(context, args, 2).i;
    int flags = 0;
    for (int i = 3; i < br_arg_get_count(args); i++) {
        flags |= br_arg_get(context, args, i).i;
    };

    struct mfb_window *window = mfb_open_ex(title, width, height, flags);
    if (window == NULL) 
    {
        printf("Failed to create window\n");
        return -1;
    }
    BSRWindow *bsr_window = (BSRWindow*)malloc(sizeof(BSRWindow));
    if (bsr_window == NULL) 
    {
        printf("Failed to allocate memory for BSRWindow\n");
        mfb_close(window);
        return -1;
    }
    bsr_window->window = window;
    bsr_window->title = title;
    bsr_window->buffer = (char*)malloc(width * height * 4); // allocate buffer for the window
    if (bsr_window->buffer == NULL) 
    {
        printf("Failed to allocate buffer for window\n");
        free(bsr_window);
        mfb_close(window);
        return -1;
    }
    bsr_window->width = width;
    bsr_window->height = height;
    bsr_window->flags = flags;
    memset(bsr_window->keys, 0, sizeof(bsr_window->keys));
    memset(bsr_window->key_mods, 0, sizeof(bsr_window->key_mods));
    bsr_window->mouse_scroll_delta_x = 0.0f;
    bsr_window->mouse_scroll_delta_y = 0.0f;
    bsr_window->character = 0;
    mfb_set_user_data(window, bsr_window);
    mfb_set_resize_callback(window, resize);
    mfb_set_keyboard_callback(window, keyboard);
    mfb_set_char_input_callback(window, char_input);
    mfb_set_mouse_button_callback(window, mouse_btn);
    mfb_set_mouse_scroll_callback(window, mouse_scroll);
    
    mfb_set_viewport(window, 0, 0, width, height);

    bruter_push(bsr_windows, (BruterValue){.p = bsr_window}, NULL, 0);

    BruterInt result = br_new_var(context, bruter_value_pointer(bsr_window), NULL, BR_TYPE_ANY);
    return result;
}

BR_FUNCTION(bsr_close_window)
{
    struct mfb_window *window = (struct mfb_window*)((BSRWindow*)(br_arg_get(context, args, 0).p))->window;

    if (window == NULL)
    {
        printf("Window is NULL\n");
        return -1;
    }
    
    for (BruterInt i = 0; i < bsr_windows->size; i++)
    {
        BSRWindow *bsr_window = (BSRWindow*)bsr_windows->data[i].p;
        if (bsr_window && bsr_window->window == window)
        {
            free(bsr_window);
            free(bsr_window->buffer);
            bsr_windows->data[i].p = NULL; // mark as removed
            bruter_remove(bsr_windows, i);
            break;
        }
    }

    mfb_close(window);
    return 0;
}

BR_FUNCTION(bsr_update_window) 
{
    BSRWindow *current_window = (BSRWindow*)(br_arg_get(context, args, 0).p);
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    uint8_t *buffer = (uint8_t*)(current_window)->buffer;
    int width = current_window->width;
    int height = current_window->height;
    if (window == NULL || buffer == NULL)
    {
        printf("Window or buffer is NULL\n");
    }
    if (mfb_update_ex(window, buffer, width, height) < 0)
    {
        printf("Failed to update window\n");
    }
    return -1;
}

BR_FUNCTION(bsr_update_window_events) 
{
    struct mfb_window *window = (struct mfb_window*)((BSRWindow*)(br_arg_get(context, args, 0).p))->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return -1;
    }
    mfb_update_events(window);
    return 0;
}

BR_FUNCTION(bsr_is_window_active)
{
    return mfb_is_window_active(br_arg_get(context, args, 0).p);
}

BR_FUNCTION(bsr_get_window_width)
{
    struct mfb_window *window = (struct mfb_window*)((BSRWindow*)(br_arg_get(context, args, 0).p))->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return -1;
    }

    BruterInt result = br_new_var(context, bruter_value_int(mfb_get_window_width(window)), NULL, BR_TYPE_ANY);

    return result;
}

BR_FUNCTION(bsr_get_window_height)
{
    struct mfb_window *window = (struct mfb_window*)((BSRWindow*)(br_arg_get(context, args, 0).p))->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return -1;
    }

    BruterInt result = br_new_var(context, bruter_value_int(mfb_get_window_height(window)), NULL, BR_TYPE_ANY);

    return result;
}

BruterInt bsr_get_mouse_x(BruterList *context, BruterList *args)
{
    struct mfb_window *window = (struct mfb_window*)((BSRWindow*)(br_arg_get(context, args, 0).p))->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return -1;
    }

    BruterInt result = br_new_var(context, bruter_value_int(mfb_get_mouse_x(window)), NULL, BR_TYPE_ANY);

    return result;
}

BruterInt bsr_get_mouse_y(BruterList *context, BruterList *args)
{
    struct mfb_window *window = (struct mfb_window*)((BSRWindow*)(br_arg_get(context, args, 0).p))->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return -1;
    }

    BruterInt result = br_new_var(context, bruter_value_int(mfb_get_mouse_y(window)), NULL, BR_TYPE_ANY);

    return result;
}

BruterInt bsr_get_mouse_scroll_x(BruterList *context, BruterList *args)
{
    struct mfb_window *window = (struct mfb_window*)((BSRWindow*)(br_arg_get(context, args, 0).p))->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return -1;
    }

    BruterInt result = br_new_var(context, bruter_value_int(mfb_get_mouse_scroll_x(window)), NULL, BR_TYPE_ANY);

    return result;
}

BruterInt bsr_get_mouse_scroll_y(BruterList *context, BruterList *args)
{
    struct mfb_window *window = (struct mfb_window*)((BSRWindow*)(br_arg_get(context, args, 0).p))->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return -1;
    }

    BruterInt result = br_new_var(context, bruter_value_int(mfb_get_mouse_scroll_y(window)), NULL, BR_TYPE_ANY);

    return result;
}

BruterInt bsr_wait_sync(BruterList *context, BruterList *args)
{
    struct mfb_window *window = (struct mfb_window*)((BSRWindow*)(br_arg_get(context, args, 0).p))->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return -1;
    }
    return mfb_wait_sync(window);
}

// io functions

BR_FUNCTION(bsr_is_key_pressed)
{
    BSRWindow *current_window = (BSRWindow*)(br_arg_get(context, args, 0).p);
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return -1;
    }
    mfb_key key = br_arg_get(context, args, 1).i;
    return current_window->keys[key];
}

BR_FUNCTION(bsr_get_framebuffer)
{
    BSRWindow *current_window = (BSRWindow*)(br_arg_get(context, args, 0).p);
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return -1;
    }
    uint8_t *buffer = (uint8_t*)(current_window)->buffer;
    if (buffer == NULL)
    {
        printf("Buffer is NULL\n");
        return -1;
    }
    
    BruterInt result = br_new_var(context, bruter_value_pointer(buffer), NULL, BR_TYPE_BUFFER);
    return result;
}


// drawing functions
BR_FUNCTION(bsr_fill)
{
    BSRWindow *current_window = (BSRWindow*)(br_arg_get(context, args, 0).p);
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return -1;
    }
    
    uint32_t color = br_arg_get(context, args, 1).i;

    Olivec_Canvas canvas = (Olivec_Canvas){
        .pixels = (uint32_t*)(current_window)->buffer,
        .width = current_window->width,
        .height = current_window->height,
        .stride = current_window->width
    };

    olivec_fill(canvas, color);

    return -1; // no return value
}

BR_FUNCTION(bsr_draw_rect)
{
    BSRWindow *current_window = (BSRWindow*)(br_arg_get(context, args, 0).p);
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return -1;
    }
    
    int x = br_arg_get(context, args, 1).i;
    int y = br_arg_get(context, args, 2).i;
    int width = br_arg_get(context, args, 3).i;
    int height = br_arg_get(context, args, 4).i;
    uint32_t color = br_arg_get(context, args, 5).i;

    Olivec_Canvas canvas = (Olivec_Canvas){
        .pixels = (uint32_t*)(current_window)->buffer,
        .width = current_window->width,
        .height = current_window->height,
        .stride = current_window->width
    };

    olivec_rect(canvas, x, y, width, height, color);

    return -1; // no return value
}

BR_FUNCTION(bsr_draw_frame)
{
    BSRWindow *current_window = (BSRWindow*)(br_arg_get(context, args, 0).p);
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return -1;
    }
    
    int x = br_arg_get(context, args, 1).i;
    int y = br_arg_get(context, args, 2).i;
    int width = br_arg_get(context, args, 3).i;
    int height = br_arg_get(context, args, 4).i;
    int thickness = br_arg_get(context, args, 5).i;
    uint32_t color = br_arg_get(context, args, 6).i;

    Olivec_Canvas canvas = (Olivec_Canvas){
        .pixels = (uint32_t*)(current_window)->buffer,
        .width = current_window->width,
        .height = current_window->height,
        .stride = current_window->width
    };

    olivec_frame(canvas, x, y, width, height, thickness, color);

    return -1; // no return value
}

BR_FUNCTION(bsr_draw_circle)
{
    BSRWindow *current_window = (BSRWindow*)(br_arg_get(context, args, 0).p);
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return -1;
    }
    
    int x = br_arg_get(context, args, 1).i;
    int y = br_arg_get(context, args, 2).i;
    int radius = br_arg_get(context, args, 3).i;
    uint32_t color = br_arg_get(context, args, 4).i;

    Olivec_Canvas canvas = (Olivec_Canvas){
        .pixels = (uint32_t*)(current_window)->buffer,
        .width = current_window->width,
        .height = current_window->height,
        .stride = current_window->width
    };

    olivec_circle(canvas, x, y, radius, color);

    return -1; // no return value
}

BR_FUNCTION(bsr_draw_ellipse)
{
    BSRWindow *current_window = (BSRWindow*)(br_arg_get(context, args, 0).p);
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return -1;
    }
    
    int x = br_arg_get(context, args, 1).i;
    int y = br_arg_get(context, args, 2).i;
    int radius_x = br_arg_get(context, args, 3).i;
    int radius_y = br_arg_get(context, args, 4).i;
    uint32_t color = br_arg_get(context, args, 5).i;

    Olivec_Canvas canvas = (Olivec_Canvas){
        .pixels = (uint32_t*)(current_window)->buffer,
        .width = current_window->width,
        .height = current_window->height,
        .stride = current_window->width
    };

    olivec_ellipse(canvas, x, y, radius_x, radius_y, color);

    return -1; // no return value
}

BR_FUNCTION(bsr_draw_line)
{
    BSRWindow *current_window = (BSRWindow*)(br_arg_get(context, args, 0).p);
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return -1;
    }
    
    int x1 = br_arg_get(context, args, 1).i;
    int y1 = br_arg_get(context, args, 2).i;
    int x2 = br_arg_get(context, args, 3).i;
    int y2 = br_arg_get(context, args, 4).i;
    uint32_t color = br_arg_get(context, args, 5).i;

    Olivec_Canvas canvas = (Olivec_Canvas){
        .pixels = (uint32_t*)(current_window)->buffer,
        .width = current_window->width,
        .height = current_window->height,
        .stride = current_window->width
    };

    olivec_line(canvas, x1, y1, x2, y2, color);

    return -1; // no return value
}

void __bsr_at_exit(void)
{
    if (bsr_windows != NULL)
    {
        for (BruterInt i = 0; i < bsr_windows->size; i++)
        {
            BSRWindow *bsr_window = (BSRWindow*)bsr_windows->data[i].p;
            if (bsr_window != NULL)
            {
                mfb_close(bsr_window->window);
                free(bsr_window);
            }
        }
        bruter_free(bsr_windows);
    }
}

void init_bsr(BruterList *context)
{

    bsr_windows = bruter_new(sizeof(BSRWindow), true, false);
    bruter_push(context, (BruterValue){.p = bsr_windows}, "bsr.windows", 0);

    // window flags (minifb)
    br_new_var(context, bruter_value_int(WF_ALWAYS_ON_TOP), "bsr.flag.always_on_top", BR_TYPE_ANY);
    br_new_var(context, bruter_value_int(WF_RESIZABLE), "bsr.flag.resizable", BR_TYPE_ANY);
    br_new_var(context, bruter_value_int(WF_FULLSCREEN), "bsr.flag.fullscreen", BR_TYPE_ANY);
    br_new_var(context, bruter_value_int(WF_BORDERLESS), "bsr.flag.borderless", BR_TYPE_ANY);
    br_new_var(context, bruter_value_int(WF_FULLSCREEN_DESKTOP), "bsr.flag.fullscreen_desktop", BR_TYPE_ANY);

    // window functions (minifb)
    br_new_var(context, bruter_value_pointer(bsr_new_window), "bsr.new", BR_TYPE_FUNCTION);
    br_new_var(context, bruter_value_pointer(bsr_close_window), "bsr.close", BR_TYPE_FUNCTION);
    br_new_var(context, bruter_value_pointer(bsr_update_window), "bsr.update", BR_TYPE_FUNCTION);
    br_new_var(context, bruter_value_pointer(bsr_update_window_events), "bsr.update_events", BR_TYPE_FUNCTION);
    br_new_var(context, bruter_value_pointer(bsr_is_window_active), "bsr.is_active", BR_TYPE_FUNCTION);
    br_new_var(context, bruter_value_pointer(bsr_get_window_width), "bsr.get_width", BR_TYPE_FUNCTION);
    br_new_var(context, bruter_value_pointer(bsr_get_window_height), "bsr.get_height", BR_TYPE_FUNCTION);
    br_new_var(context, bruter_value_pointer(bsr_get_mouse_x), "bsr.get_mouse_x", BR_TYPE_FUNCTION);
    br_new_var(context, bruter_value_pointer(bsr_get_mouse_y), "bsr.get_mouse_y", BR_TYPE_FUNCTION);
    br_new_var(context, bruter_value_pointer(bsr_get_mouse_scroll_x), "bsr.get_mouse_scroll_x", BR_TYPE_FUNCTION);
    br_new_var(context, bruter_value_pointer(bsr_get_mouse_scroll_y), "bsr.get_mouse_scroll_y", BR_TYPE_FUNCTION);
    br_new_var(context, bruter_value_pointer(bsr_wait_sync), "bsr.wait_sync", BR_TYPE_FUNCTION);

    // io functions (minifb)
    br_new_var(context, bruter_value_pointer(bsr_is_key_pressed), "bsr.is_key_pressed", BR_TYPE_FUNCTION);
    br_new_var(context, bruter_value_pointer(bsr_get_framebuffer), "bsr.get_framebuffer", BR_TYPE_FUNCTION);

    // drawing functions (olivec)
    br_new_var(context, bruter_value_pointer(bsr_fill), "bsr.fill", BR_TYPE_FUNCTION);
    br_new_var(context, bruter_value_pointer(bsr_draw_rect), "bsr.rect", BR_TYPE_FUNCTION);
    br_new_var(context, bruter_value_pointer(bsr_draw_frame), "bsr.frame", BR_TYPE_FUNCTION);
    br_new_var(context, bruter_value_pointer(bsr_draw_circle), "bsr.circle", BR_TYPE_FUNCTION);
    br_new_var(context, bruter_value_pointer(bsr_draw_ellipse), "bsr.ellipse", BR_TYPE_FUNCTION);
    br_new_var(context, bruter_value_pointer(bsr_draw_line), "bsr.line", BR_TYPE_FUNCTION);


    // add bsr_windows to context
    br_new_var(context, bruter_value_pointer(bsr_windows), "bsr.windows", BR_TYPE_LIST);
    

    // register at exit function
    atexit(__bsr_at_exit);
}