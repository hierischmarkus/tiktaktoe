/*
 * tiktaktoe - a game using SnodeC
 * Copyright (C) 2021 Volker Christian <me@vchrist.at>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "TikTakToeGameModel.h"

#include <map>               // for operator==
#include <nlohmann/json.hpp> // for basic_json<>::object_t, basic_json<>::v...
#include <iostream>
#include <easylogging++.h>

TikTakToeGameModel TikTakToeGameModel::gameModel;

void TikTakToeGameModel::playersMove(const std::string& player, int cellID) {
    if (player == players[whosNext]) {
        int cellValue = 0;

        if (player == "red") {
            cellValue = 1;
        } else if (player == "blue") {
            cellValue = -1;
        }

        board[cellID] = cellValue;

        if (whosNext >= 1) {
            whosNext = 0;
        } else {
            whosNext += 1;
        }
    }
}

bool TikTakToeGameModel::isGameOver(const std::string& player)
{
    int cellValue;
    if (player == "red") {
            cellValue = 1;
        } else {
            cellValue = -1;
    }
    
    if((board[0] == cellValue && board[1] == cellValue && board[2] == cellValue) ||
       (board[3] == cellValue && board[4] == cellValue && board[5] == cellValue) ||
       (board[6] == cellValue && board[7] == cellValue && board[8] == cellValue) ||
       (board[0] == cellValue && board[3] == cellValue && board[6] == cellValue) ||
       (board[1] == cellValue && board[4] == cellValue && board[7] == cellValue) ||
       (board[2] == cellValue && board[5] == cellValue && board[8] == cellValue) ||
       (board[0] == cellValue && board[4] == cellValue && board[8] == cellValue) ||
       (board[2] == cellValue && board[4] == cellValue && board[6] == cellValue)
    ){
        VLOG(0) << "Juhu gewonnen JA juhu jaa jaaa";
        return true;
    }
    return false;
}

void TikTakToeGameModel::resetBoard() {
    whosNext = 0;
    for (int i = 0; i < 9; i++) {
        board[i] = 0;
    }
}

nlohmann::json TikTakToeGameModel::setGameOver() {
    nlohmann::json message;

    message["type"] = "gameOver";
    message["board"] = board;

    return message;
}


nlohmann::json TikTakToeGameModel::updateClientState() {
    nlohmann::json message;

    message["type"] = "update";
    message["whosTurn"] = players[whosNext];
    message["board"] = board;

    return message;
}

TikTakToeGameModel& TikTakToeGameModel::getGameModel() {
    return gameModel;
}
