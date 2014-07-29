#ifndef ATLANTIS_LOGGER_H_
#define ATLANTIS_LOGGER_H_

extern void atlantis_logger_window_title(const char *title);
extern void atlantis_logger_speed(int speed, int frameskip, int frames);
extern void atlantis_logger_console(const char *message);
extern void atlantis_logger_screen(const char *message);
extern void atlantis_logger_format(const char *format, va_list args);
extern void atlantis_logger_system(int code, const char *format, va_list args);

#endif /* ATLANTIS_LOGGER_H_ */
