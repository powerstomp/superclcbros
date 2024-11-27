#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>
#include "../Observer/Signal.h"
#include <iostream>
#include <fstream>
#include <array>

enum class Action {
    MOVE_LEFT,
    MOVE_RIGHT,
    JUMP,
    FIRE,
    DUCK,
    MAX
};

class Keyboard {
private:
    // Map of key bindings
    std::unordered_map<sf::Keyboard::Key, Action> keyMap;
public:
    // Signal to amit when an action is triggered
    std::array<Signal<>, static_cast<size_t>(Action::MAX)> onAction;

    // Initialize default key bindings
    Keyboard();

 
    void BindKey(sf::Keyboard::Key key, Action action);
    void UnbindKey(sf::Keyboard::Key key);
    void HandleKeyPress(sf::Keyboard::Key key);
    void SaveKeyBindings(const std::string& filePath);
    void LoadKeyBindings(const std::string& filePath);
};

#endif




