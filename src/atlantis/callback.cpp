#include "callback.h"
#include <cstdio>
#include <stdint.h>

/*
 * signals.h
 */

void (*autosave_callback)(void) = NULL;
void (*shutdown_callback)(void) = NULL;
void (*startup_callback)(void) = NULL;
void (*gba_load_callback)(void) = NULL;
void (*gb_load_callback)(void) = NULL;

void atlantis_signal_autosave() {
	if (autosave_callback)
		autosave_callback();
}

void atlantis_signal_shutdown() {
	if (shutdown_callback)
		shutdown_callback();
}

void atlantis_signal_startup() {
	if (startup_callback)
		startup_callback();
}

void atlantis_signal_gba_load() {
	if (gba_load_callback)
		gba_load_callback();
}

void atlantis_signal_gb_load() {
	if (gb_load_callback)
		gb_load_callback();
}

/*
 * debugger.h
 */

void (*debug_ioreg_callback)(uint32_t, uint32_t) = NULL;
void (*debug_readword_callback)(uint32_t, uint32_t) = NULL;
void (*debug_readhword_callback)(uint32_t, uint16_t) = NULL;
void (*debug_readshword_callback)(uint32_t, int16_t) = NULL;
void (*debug_readbyte_callback)(uint32_t, uint8_t) = NULL;
void (*debug_writebyte_callback)(uint32_t, uint8_t) = NULL;
void (*debug_writehword_callback)(uint32_t, uint16_t) = NULL;
void (*debug_writeword_callback)(uint32_t, uint32_t) = NULL;
void (*debug_instruction_callback)(bool, uint32_t) = NULL;

void atlantis_debug_io_reg(uint32_t address, uint32_t value) {
	if (debug_ioreg_callback)
		debug_ioreg_callback(address, value);
}

void atlantis_debug_read_word(uint32_t address, uint32_t value) {
	if (debug_readword_callback)
		debug_readword_callback(address, value);
}

void atlantis_debug_read_halfword(uint32_t address, uint16_t value) {
	if (debug_readhword_callback)
		debug_readhword_callback(address, value);
}

void atlantis_debug_read_signed_halfword(uint32_t address, int16_t value) {
	if (debug_readshword_callback)
		debug_readshword_callback(address, value);
}

void atlantis_debug_read_byte(uint32_t address, uint8_t value) {
	if (debug_readbyte_callback)
		debug_readbyte_callback(address, value);
}

void atlantis_debug_write_byte(uint32_t address, uint8_t value) {
	if (debug_writebyte_callback)
		debug_writebyte_callback(address, value);
}

void atlantis_debug_write_halfword(uint32_t address, uint16_t value) {
	if (debug_writehword_callback)
		debug_writehword_callback(address, value);
}

void atlantis_debug_write_word(uint32_t address, uint32_t value) {
	if (debug_writeword_callback)
		debug_writeword_callback(address, value);
}

void atlantis_debug_instruction(bool arm, uint32_t pc) {
	if (debug_instruction_callback)
		debug_instruction_callback(arm, pc);
}

/*
 * logger.h
 */

void atlantis_logger_window_title(const char *title) {
}

void atlantis_logger_speed(int speed, int frameskip, int frames) {
}

void atlantis_logger_console(const char *message) {
}

void atlantis_logger_screen(const char *message) {
}

void atlantis_logger_format(const char *format, va_list args) {
}

void atlantis_logger_system(int code, const char *format, va_list args) {
}

/*
 * video.h
 */

void (*video_frame_callback)(uint32_t*, int, int) = NULL;

void atlantis_video_frame(uint32_t *pixels, int width, int height) {
	if (video_frame_callback)
		video_frame_callback(pixels, width, height);
}

/*
 * audio.h
 */

bool (*audio_init_callback)(long) = NULL;
void (*audio_pause_callback)() = NULL;
void (*audio_reset_callback)() = NULL;
void (*audio_resume_callback)() = NULL;
void (*audio_frame_callback)(float*, int) = NULL;
void (*audio_throttle_callback)(unsigned short) = NULL;

bool atlantis_audio_init(long sampleRate) {
	if (audio_init_callback)
		return audio_init_callback(sampleRate);
	return true;
}

void atlantis_audio_pause() {
	if (audio_pause_callback)
		audio_pause_callback();
}

void atlantis_audio_reset() {
	if (audio_reset_callback)
		audio_reset_callback();
}

void atlantis_audio_resume() {
	if (audio_resume_callback)
		audio_resume_callback();
}

void atlantis_audio_write(float *frame, int length) {
	if (audio_frame_callback)
		audio_frame_callback(frame, length);
}

void atlantis_audio_set_throttle(unsigned short throttle) {
	if (audio_throttle_callback)
		audio_throttle_callback(throttle);
}

/*
 * C API
 */

extern "C" {

void atlantisOnStartup(void (*callback)(void)) {
	startup_callback = callback;
}
void atlantisOnShutdown(void (*callback)(void)) {
	shutdown_callback = callback;
}
void atlantisAutosave(void (*callback)(void)) {
	autosave_callback = callback;
}
void atlantisOnGBAStart(void (*callback)(void)) {
	gba_load_callback = callback;
}
void atlantisOnGBStart(void (*callback)(void)) {
	gb_load_callback = callback;
}

void atlantisDebugIOReg(void (*callback)(uint32_t, uint32_t)) {
	debug_ioreg_callback = callback;
}

void atlantisDebugReadWord(void (*callback)(uint32_t, uint32_t)) {
	debug_readword_callback = callback;
}

void atlantisDebugReadHalfword(void (*callback)(uint32_t, uint16_t)) {
	debug_readhword_callback = callback;
}

void atlantisDebugReadSignedHalfword(void (*callback)(uint32_t, int16_t)) {
	debug_readshword_callback = callback;
}

void atlantisDebugReadByte(void (*callback)(uint32_t, uint8_t)) {
	debug_readbyte_callback = callback;
}

void atlantisDebugWriteByte(void (*callback)(uint32_t, uint8_t)) {
	debug_writebyte_callback = callback;
}

void atlantisDebugWriteHalfword(void (*callback)(uint32_t, uint16_t)) {
	debug_writehword_callback = callback;
}

void atlantisDebugWriteWord(void (*callback)(uint32_t, uint32_t)) {
	debug_writeword_callback = callback;
}

void atlantisDebugInstruction(void (*callback)(bool, uint32_t)) {
	debug_instruction_callback = callback;
}

void atlantisVideoOnFrame(void (*callback)(uint32_t*, int, int)) {
	video_frame_callback = callback;
}

void atlantisAudioOnInit(bool (*callback)(long)) {
	audio_init_callback = callback;
}

void atlantisAudioOnPause(void (*callback)()) {
	audio_pause_callback = callback;
}

void atlantisAudioOnReset(void (*callback)()) {
	audio_reset_callback = callback;
}

void atlantisAudioOnResume(void (*callback)()) {
	audio_resume_callback = callback;
}

void atlantisAudioOnFrame(void (*callback)(float*, int)) {
	audio_frame_callback = callback;
}

void atlantisAudioOnSetThrottle(void (*callback)(unsigned short)) {
	audio_throttle_callback = callback;
}

}

