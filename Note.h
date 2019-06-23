#define AUDIO_BLOCK_SIZE   ((uint32_t)5400)
#define AUDIO_BUFFER_IN     SDRAM_DEVICE_ADDR     /* In SDRAM */
#define AUDIO_BUFFER_OUT    (SDRAM_DEVICE_ADDR + (AUDIO_BLOCK_SIZE))  /* In SDRAM */

    int note(double frequence);
    void Init_note(void);
