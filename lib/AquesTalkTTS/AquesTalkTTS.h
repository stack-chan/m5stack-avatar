/**
 * \par Copyright (C), 2018, AQUEST
 * \class AquesTalkTTS
 * \brief   Text-to-Sppech library. uses AquesTalk-ESP, I2S, intenal-DAC.
 * @file    AquesTalkTTS.h
 * @author  AQUEST
 * @version V0.2.0
 * @date    2018/08/08
 * @brief   Header for AquesTalkTTS.cpp module
 *
 * \par Description
 * This file is a TTS class for ESP32.
 *
 * \par Method List:
 *    
 *
        TTS.create();
        TTS.createK();
        TTS.release();
        TTS.play(const char *koe, int speed);
        TTS.playK(const char *koe, int speed);
        TTS.isPlay();
        TTS.stop();
        TTS.getLavel();
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Nobuhide Yamazaki    2018/03/29        0.1.0          Creation.
 * Nobuhide Yamazaki    2018/08/08        0.2.0          add AqKanji2Roman-M.
 * </pre>
 *
 */

#ifndef _AQUESTALK_TTS_H_
#define _AQUESTALK_TTS_H_

class AquesTalkTTS {
	public:
		int create(const char *licencekey);//heap:400B
		int createK(const char *licencekey);//heap:21KB
		void release();

		int play(const char *koe, int speed);//koe: onsei-kigouretu(roman)
		int playK(const char *kanji, int speed);//kanji: kanji-text (UTF8)

		void stop();
		bool isPlay();
		int getLevel();
};
extern AquesTalkTTS TTS;

#endif // !defined(_AQUESTALK_TTS_H_)
