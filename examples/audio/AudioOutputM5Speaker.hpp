/*
  This source was taken from M5Unified's example(WebRadio_with_ESP8266Audio.ino).
  https://github.com/m5stack/M5Unified
 */


#include <AudioOutput.h>
#include <M5Unified.h>

class AudioOutputM5Speaker : public AudioOutput
{
  public:
    AudioOutputM5Speaker(m5::Speaker_Class* m5sound, uint8_t virtual_sound_channel = 0)
    {
      _m5sound = m5sound;
      _virtual_ch = virtual_sound_channel;
    }
    virtual ~AudioOutputM5Speaker(void) {};
    virtual bool begin(void) override { return true; }
    virtual bool ConsumeSample(int16_t sample[2]) override
    {
      if (_tri_buffer_index < tri_buf_size)
      {
        _tri_buffer[_tri_index][_tri_buffer_index  ] = sample[0];
        _tri_buffer[_tri_index][_tri_buffer_index+1] = sample[1];
        _tri_buffer_index += 2;

        return true;
      }

      flush();
      return false;
    }
    virtual void flush(void) override
    {
      if (_tri_buffer_index)
      {
        _m5sound->playRaw(_tri_buffer[_tri_index], _tri_buffer_index, hertz, true, 1, _virtual_ch);
        _tri_index = _tri_index < 2 ? _tri_index + 1 : 0;
        _tri_buffer_index = 0;
        ++_update_count;
      }
    }
    virtual bool stop(void) override
    {
      flush();
      _m5sound->stop(_virtual_ch);
      for (size_t i = 0; i < 3; ++i)
      {
        memset(_tri_buffer[i], 0, tri_buf_size);
      }
      ++_update_count;
      return true;
    }

    const int16_t* getBuffer(void) const { return _tri_buffer[(_tri_index + 2) % 3]; }
    const uint32_t getUpdateCount(void) const { return _update_count; }

  protected:
    m5::Speaker_Class* _m5sound;
    uint8_t _virtual_ch;
    static constexpr size_t tri_buf_size = 640;
    int16_t _tri_buffer[3][tri_buf_size];
    size_t _tri_buffer_index = 0;
    size_t _tri_index = 0;
    size_t _update_count = 0;
};

#define FFT_SIZE 256
class fft_t
{
  float _wr[FFT_SIZE + 1];
  float _wi[FFT_SIZE + 1];
  float _fr[FFT_SIZE + 1];
  float _fi[FFT_SIZE + 1];
  uint16_t _br[FFT_SIZE + 1];
  size_t _ie;

public:
  fft_t(void)
  {
#ifndef M_PI
#define M_PI 3.141592653
#endif
    _ie = logf( (float)FFT_SIZE ) / log(2.0) + 0.5;
    static constexpr float omega = 2.0f * M_PI / FFT_SIZE;
    static constexpr int s4 = FFT_SIZE / 4;
    static constexpr int s2 = FFT_SIZE / 2;
    for ( int i = 1 ; i < s4 ; ++i)
    {
    float f = cosf(omega * i);
      _wi[s4 + i] = f;
      _wi[s4 - i] = f;
      _wr[     i] = f;
      _wr[s2 - i] = -f;
    }
    _wi[s4] = _wr[0] = 1;

    size_t je = 1;
    _br[0] = 0;
    _br[1] = FFT_SIZE / 2;
    for ( size_t i = 0 ; i < _ie - 1 ; ++i )
    {
      _br[ je << 1 ] = _br[ je ] >> 1;
      je = je << 1;
      for ( size_t j = 1 ; j < je ; ++j )
      {
        _br[je + j] = _br[je] + _br[j];
      }
    }
  }

  void exec(const int16_t* in)
  {
    memset(_fi, 0, sizeof(_fi));
    for ( size_t j = 0 ; j < FFT_SIZE / 2 ; ++j )
    {
      float basej = 0.25 * (1.0-_wr[j]);
      size_t r = FFT_SIZE - j - 1;

      /// perform han window and stereo to mono convert.
      _fr[_br[j]] = basej * (in[j * 2] + in[j * 2 + 1]);
      _fr[_br[r]] = basej * (in[r * 2] + in[r * 2 + 1]);
    }

    size_t s = 1;
    size_t i = 0;
    do
    {
      size_t ke = s;
      s <<= 1;
      size_t je = FFT_SIZE / s;
      size_t j = 0;
      do
      {
        size_t k = 0;
        do
        {
          size_t l = s * j + k;
          size_t m = ke * (2 * j + 1) + k;
          size_t p = je * k;
          float Wxmr = _fr[m] * _wr[p] + _fi[m] * _wi[p];
          float Wxmi = _fi[m] * _wr[p] - _fr[m] * _wi[p];
          _fr[m] = _fr[l] - Wxmr;
          _fi[m] = _fi[l] - Wxmi;
          _fr[l] += Wxmr;
          _fi[l] += Wxmi;
        } while ( ++k < ke) ;
      } while ( ++j < je );
    } while ( ++i < _ie );
  }

  uint32_t get(size_t index)
  {
    return (index < FFT_SIZE / 2) ? (uint32_t)sqrtf(_fr[ index ] * _fr[ index ] + _fi[ index ] * _fi[ index ]) : 0u;
  }
};