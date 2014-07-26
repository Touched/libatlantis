/*
 * logger.h
 *
 *  Created on: 26 Jul 2014
 *      Author: james
 */

#ifndef ATLANTIS_LOGGER_H_
#define ATLANTIS_LOGGER_H_

#ifdef ENABLE_ATLANTIS_LOGGER
extern void atlantis_logger_window_title(const char *title);
extern void atlantis_logger_speed(int speed);
extern void atlantis_logger_console(const char *message);
extern void atlantis_logger_screen(const char *message);
extern void atlantis_logger_format(const char *format, va_list args);
extern void atlantis_logger_system(int code, const char *format, va_list args);
#else
inline void atlantis_logger_window_title(const char *title) {}
inline void atlantis_logger_speed(int speed, int frame_skip, int frames) {}
inline void atlantis_logger_console(const char *message) {}
inline void atlantis_logger_screen(const char *message) {}
inline void atlantis_logger_format(const char *format, va_list args) {}
inline void atlantis_logger_system(int code, const char *format, va_list args) {}
#endif

#endif /* ATLANTIS_LOGGER_H_ */
