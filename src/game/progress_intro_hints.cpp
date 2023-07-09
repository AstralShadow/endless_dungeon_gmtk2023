#include "game/hints.hpp"
#include "game/tick.hpp"


bool game::progress_intro_hints()
{
    auto active = active_hints();
    if(active.size()) {
        auto& hint = get_hint(active[0]);

        float visible = hint.lifetime * text_speed
            / (hint.text.size() * 1000.0f);
        size_t characters = std::max(0.0f, visible)
            * hint.text.size();


        if(characters < hint.text.size()) {
            hint.lifetime += 5000;
        } else {
            if(active[0] == H_LEVEL_EDITING) {
                static int level_edit_counter = 3;
                if(level_edit_counter-- > 0)
                    return false;
            }

            if(active[0] == H_TIME_CONTROL_2) {
                speed_mode = 1;
            }

            hint.done = true;
            if(next_hint <= last_intro_hint)
                activate_hint
                    (static_cast<HintKey>
                        (next_hint++));
        }

        return true;
    }

    return false;
}

