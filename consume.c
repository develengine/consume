#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <xcb/xcb_aux.h>

int main(int argc, char *argv[])
{
    int screen;
    char **command;
    xcb_connection_t *connection;
    xcb_ewmh_connection_t *ewmh;
    xcb_window_t window;

    connection = xcb_connect(NULL, &screen);
    if (xcb_connection_has_error(connection)) {
        fprintf(stderr, "failed to establish connection!\n");
        exit(-1);
    }
    
    ewmh = malloc(sizeof(xcb_ewmh_connection_t));
    if (xcb_ewmh_init_atoms_replies(ewmh, xcb_ewmh_init_atoms(connection, ewmh), NULL) == 0) {
        fprintf(stderr, "failed to initialize EWMH atoms!\n");
        exit(-1);
    }

    if (xcb_ewmh_get_active_window_reply(ewmh, xcb_ewmh_get_active_window(ewmh, screen), &window, NULL) != 1) {
        fprintf(stderr, "failed to determine the active window!\n");
        exit(-1);
    }

    xcb_unmap_window(connection, window);
    xcb_flush(connection);

    command = calloc(argc, sizeof(char*));
    memcpy(command, argv+1, sizeof(char*) * (argc - 1));

    if (fork() == 0)
        execvp(command[0], command);
    wait(NULL);

    xcb_map_window(connection, window);
    xcb_aux_sync(connection);

    free(command);
    xcb_ewmh_connection_wipe(ewmh);
    free(ewmh);
    xcb_disconnect(connection);
    return 0;
}
