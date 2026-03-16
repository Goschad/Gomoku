#pragma once

#include <array>
#include <optional>
#include <string>
#include <algorithm>
#include <iostream>

constexpr const char* WINDOW_TITLE = "Gomoku";

constexpr int WIDTH = 1200;
constexpr int HEIGHT = 800;

constexpr int WINDOW_MARGIN = 30;
constexpr int SIDE_PANEL_WIDTH = 300;

constexpr int MIN_BOARD_PIXEL_SIZE = 200;

constexpr int FPS_LIMIT = 60;

constexpr float STONE_RADIUS_FACTOR = 0.38;

constexpr const char* FONT_PATH = "assets/fonts/Geist.ttf";
constexpr const char* ICON_PATH = "assets/images/icons/app.png";