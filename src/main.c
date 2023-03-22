#include "prework.h"
#include "interact.h"

int main(int argc, char *argv[]) {
    int reset = argc > 1;
    // get msqid
    if (connect(argv[0], reset) == -1) return -1;
    // clear type 1
    clear_exitmsg();
    // set sighandler
    if (set_sighandler() == -1) return -1;
    // create listener
    if (run_listener() == -1) return -1;
    // main process
    S.ready = 1;
    interactor();
    return 0;
}