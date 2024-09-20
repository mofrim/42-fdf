#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <string.h>

int main() {
    // Open the X11 display
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Failed to open display\n");
        return 1;
    }

    // Get the root window
    Window root = RootWindow(display, 0);

    // Create a new window
    Window window = XCreateWindow(
        display,
        root,
        100, 100,  // x, y coordinates
        200, 200,  // width, height
        1,          // border width
        CopyFromParent,  // depth
        InputOutput,     // class
        CopyFromParent,  // visual
        0,              // value mask
        NULL             // attributes
    );

    // Set the window background color
    XSetWindowBackground(display, window, WhitePixel(display, 0));

    // Set the window border color
    XSetWindowBorder(display, window, BlackPixel(display, 0));

    // Map the window (make it visible)
    XMapWindow(display, window);

    // Set the window title
    XTextProperty name;
    name.value = (unsigned char *)"My X11 Window";
    name.encoding = XA_STRING;
    name.format = 8;
    name.nitems = strlen((char *)name.value);
    XSetWMName(display, window, &name);

    // Event loop
    XEvent event;
    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            // Handle expose events (e.g., redraw the window)
        } else if (event.type == KeyPress) {
            // Handle key press events (e.g., exit on 'q' key)
            if (event.xkey.keycode == 24) { // 'q' key
                break;
            }
        }
    }

    // Close the window and display
    XCloseDisplay(display);
    return 0;
}
