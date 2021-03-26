/*
 * my_game.h
 *
 *  Created on: 2021Äê3ÔÂ24ÈÕ
 *      Author: Woodman
 */

#ifndef MY_GAME_H_
#define MY_GAME_H_

#define birdSpeed game_para[0]
#define birdPositionV game_para[1]
#define birdScore game_para[2]
#define birdPositionH game_para[3]
#define birdSpeedCount game_para[4]

void DelayMs(uint16_t x);
void FlappyBird();
void GameInit();
void Game();
void GameOver();
void ImageMove(uint8_t count);
void ImageAddPillar(uint8_t pillarPosition);
void ImageGet(uint8_t image_want[][8]);
uint8_t ReadBit(uint8_t x, uint8_t xnumber);
void WriteBit(uint8_t* x, uint8_t xnumber, uint8_t want);
void WriteImage(uint8_t horizontal, uint8_t vertical, uint8_t want);
uint8_t ReadImage(uint8_t horizontal, uint8_t vertical);
void ImageAddBird(uint8_t image_want[][1]);
uint8_t Dead();
uint8_t GetSignal();
void ImageAddEdge();
void TwoLine(uint8_t up[][4], uint8_t down[][4]);
void ImageAddNumber(int16_t number);
void OverWriteNumber(uint16_t number, uint8_t mod);

#endif /* MY_GAME_H_ */
