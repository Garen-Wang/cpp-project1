
#include "animation.hpp"
// time unit: frame, 33333 milliseconds per frame
// use terminal.print, terminal.flush, terminal.clear
// as for position, use percent to expand scalibility


MoveAnimation::MoveAnimation(Terminal *terminal, std::vector<std::string> &image, Direction direction, unsigned int x=0, unsigned int y=0, unsigned int start_frame=0, unsigned int duration=120, bool keep=false):
terminal(terminal), image(image), direction(direction), x(x), y(y), start_frame(start_frame), duration(duration), keep(keep) {}


StillAnimation::StillAnimation(Terminal *terminal, std::vector<std::string> &image, unsigned int x=0, unsigned int y=0, unsigned int start_frame=0, unsigned int duration=120, bool keep=false):
terminal(terminal), image(image), x(x), y(y), start_frame(start_frame), duration(duration), keep(keep) {}


SequencialAnimations::SequencialAnimations(std::vector<Animation> animations, unsigned int duration=120) : animations(animations), duration(duration) {}


ParallelAnimations::ParallelAnimations(std::vector<Animation> animations, unsigned int duration=120) : animations(animations), duration(duration) {}
