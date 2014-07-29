#ifndef CALLBACK_H_
#define CALLBACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/*
 * signal.h
 */

/*
 * Signals
 */
void atlantisOnStartup(void (*callback)(void));
void atlantisOnShutdown(void (*callback)(void));
void atlantisAutosave(void (*callback)(void));
void atlantisOnGBAStart(void (*callback)(void));
void atlantisOnGBStart(void (*callback)(void));

/*
 * Debugging callbacks
 */
void atlantisDebugIOReg(void (*callback)(uint32_t, uint32_t));
void atlantisDebugReadWord(void (*callback)(uint32_t, uint32_t));
void atlantisDebugReadHalfword(void (*callback)(uint32_t, uint16_t));
void atlantisDebugReadSignedHalfword(void (*callback)(uint32_t, int16_t));
void atlantisDebugReadByte(void (*callback)(uint32_t, uint8_t));
void atlantisDebugWriteByte(void (*callback)(uint32_t, uint8_t));
void atlantisDebugWriteHalfword(void (*callback)(uint32_t, uint16_t));
void atlantisDebugWriteWord(void (*callback)(uint32_t, uint32_t));
void atlantisDebugInstruction(void (*callback)(bool, uint32_t));

/*
 * Video callbacks
 */

void atlantisVideoOnFrame(void (*callback)(uint32_t*, int, int));

/*
 *  Audio callbacks
 */
void atlantisAudioOnInit(bool (*callback)(long));
void atlantisAudioOnPause(void (*callback)());
void atlantisAudioOnReset(void (*callback)());
void atlantisAudioOnResume(void (*callback)());
void atlantisAudioOnFrame(void (*callback)(float*, int));
void atlantisAudioOnSetThrottle(void (*callback)(unsigned short));

#ifdef __cplusplus
}
#endif

#endif /* CALLBACK_H_ */
