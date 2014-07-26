#include <cstddef>
#include "System.h"

#include "Video.h"
#include "Audio.h"
#include "Input.h"

namespace test {

System::System() {
	video = new Video;
	sound = new Audio;
	input = new Input;
}

System::~System() {
}

atlantis::Video* System::video_driver() {
	return video;
}

atlantis::Audio* System::sound_driver() {
	return sound;
}

atlantis::Input* System::input_driver() {
	return input;
}

} /* namespace test */
