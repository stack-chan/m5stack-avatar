/**
 * \par Copyright (C), 2018, AQUEST
 * \class AquesTalkTTS
 * \brief   Text-to-Sppech library. uses AquesTalk-ESP, I2S, intenal-DAC.
 * @file    AquesTalkTTS.h
 * @author  AQUEST
 * @version V0.1.0
 * @date    2018/03/29
 * @brief   Header for AquesTalkTTS.cpp module
 *
 * \par Description
 * This file is a TTS class for ESP32.
 *
 * \par Method List:
 *    
 *
        TTS.create();
        TTS.release();
        TTS.play(const char *koe, int speed);
        TTS.stop();
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Nobuhide Yamazaki    2018/03/29        0.0.1          Creation.
 * </pre>
 *
 */

#ifndef _AQUESTALK_TTS_H_
#define _AQUESTALK_TTS_H_

class AquesTalkTTS {
	public:
		int create(const char *licencekey);
		void release();

		int play(const char *koe, int speed);
		void stop();
	int getLevel();
};
extern AquesTalkTTS TTS;

#endif // !defined(_AQUESTALK_TTS_H_)
