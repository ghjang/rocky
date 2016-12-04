#include "../catch.hpp"

#include <iostream>

#include "rocky/et/DoubleDispatch.h"


enum states : int { Empty, Open, Stopped, Playing, Paused };

// events
struct play { };
struct open_close { };
struct cd_detected { };
struct pause { };
struct stop { };

// state machine
struct player
{
private:
    states state_ = Stopped;

    states get_state() const { return state_; }
    void set_state(states s) { state_ = s; }

    friend class if_t;

public:
    void start_playback(play const& e)
    {
        std::cout << "start_playback is called.\n";
    }
    
    void resume_playback(play const& e)
    {
        std::cout << "resume_playback is called.\n";
    }

    void process_event_by_switch(play const& e)
    {
        switch (this->state_) {
        case Stopped:
            this->start_playback(e);
            this->state_ = Playing;
            break;
        case Paused:
            this->resume_playback(e);
            this->state_ = Playing;
            break;
        default:
            std::cout << "no transition.\n";
            break;
        }
    }

    void process_event_by_if_else(play const& e)
    {
        if (this->state_ == Stopped) {
            this->start_playback(e);
            this->state_ = Playing;
        } else if (this->state_ == Paused) {
            this->resume_playback(e);
            this->state_ = Playing;            
        } else {
            std::cout << "no transition.\n";
        }
    }

    void process_event_by_folding(play const& e)
    {
        foldl(
            if_t{},     // binary op
            this,       // init
            if_condition(Stopped, [&e](auto t) { t->start_playback(e); }, Playing),
            if_condition(Paused, [&e](auto t) { t->resume_playback(e); }, Playing),
            else_final([]{ std::cout << "no transition.\n"; })
        );
    }
};

TEST_CASE("double dispatch by using 'switch'", "[et]")
{
    player p;
    p.process_event_by_switch(play{});
}

TEST_CASE("double dispatch by using 'if ~ else'", "[et]")
{
    player p;
    p.process_event_by_if_else(play{});
}

TEST_CASE("double dispatch by using folding", "[et]")
{
    player p;
    p.process_event_by_folding(play{});
}
