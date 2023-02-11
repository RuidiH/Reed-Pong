#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

/**
 * Configuration for page display and game mode.
 */

struct Configuration
{
    /*
     *   0 -- > Menu
     *   1 --> Game
     *   ..
     */
    int page = 0;

    bool quitGame = false;

    /* Game mode 0 -- Eternity: No winning/losing condition */
    /* Game mode 1 -- Accelerate: Ball speed increase each time it resets */
    /* Game mode 2 -- One Punch: The player that scores first win! */
    /* Game mode 3 -- Misfortune: One of the player's catcher/paddle's height will be reduced by half. Who's the (un)lucky one? */
    bool gameModes[4] = {false, false, false, false};

};

#endif