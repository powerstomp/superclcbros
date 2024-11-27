#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>
#include "../Observer/Signal.h"
#include <iostream>
#include <fstream>

enum class Action {
    MOVE_LEFT,
    MOVE_RIGHT,
    JUMP,
    FIRE,
    DUCK
};

class Keyboard {
private:
    // Map of key bindings
    std::unordered_map<sf::Keyboard::Key, Action> keyMap;
public:
    // Signal to amit when an action is triggered
    Signal<Action> onAction;

    // Initialize default key bindings
    Keyboard();

    // Bind a key to an action
    void BindKey(sf::Keyboard::Key key, Action action);

    // Handle keypress events
    void HandleKeyPress(sf::Keyboard::Key key);

    // Save key bindings to a file
    void SaveKeyBindings(const std::string& filePath);

    // Load key bindings from a file
    void LoadKeyBindings(const std::string& filePath);
};

#endif




