/* Copyright (c) 2022, Arvid Juskaitis (arvydas.juskaitis@gmail.com)

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1335  USA */

#pragma once

// basic
static const unsigned int SCORE_PIECE = 60;
static const unsigned int SCORE_KING = 100;
static const unsigned int SCORE_POSSIBLE_CAPTURE = 20;

// early
static const unsigned int SCORE_BACK_ROW_POSITIONS = 40;
static const unsigned int SCORE_MIDDLE_POSITIONS = 40;

// later
static const unsigned int SCORE_OPPONENT_DISTANCES = 2;
static const unsigned int SCORE_DOUBLE_CORNER_DISTANCES = 1;
static const unsigned int SCORE_SINGLE_CORNER_DISTANCES = 1;
