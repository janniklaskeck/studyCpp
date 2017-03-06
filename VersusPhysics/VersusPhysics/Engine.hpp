#pragma once

#include <stdio.h>

#define LOG(Msg, ...) printf(Msg, ##__VA_ARGS__);
