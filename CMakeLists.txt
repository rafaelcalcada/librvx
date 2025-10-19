# SPDX-License-Identifier: MIT
# Copyright (c) 2020-2025 RVX Project Contributors

cmake_minimum_required(VERSION 3.15)

project(rvx LANGUAGES C)

add_library(rvx INTERFACE rvx.h)

target_include_directories(rvx
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
