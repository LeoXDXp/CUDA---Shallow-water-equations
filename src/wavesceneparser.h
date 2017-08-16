#pragma once

#include <yaml-cpp03/yaml.h>

#include "types.h"

void parse_wavescene(const char* filename, std::string &landscape_filename, std::string &landscape_color_filename, std::string &wave_filename, float &running_time);
