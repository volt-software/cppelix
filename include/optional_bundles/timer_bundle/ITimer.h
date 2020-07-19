#pragma once

#include "framework/Events.h"

namespace Cppelix {
    struct TimerEvent final : public Event {
        TimerEvent(uint64_t _id, uint64_t _originatingService) noexcept : Event(TYPE, _id, _originatingService) {}
        ~TimerEvent() final = default;

        static constexpr uint64_t TYPE = typeNameHash<TimerEvent>();
    };

    struct ITimer : virtual public IService {
        static constexpr InterfaceVersion version = InterfaceVersion{1, 0, 0};

        virtual void startTimer() = 0;
        virtual void stopTimer() = 0;
        [[nodiscard]] virtual bool running() const = 0;
        virtual void setInterval(uint64_t nanoseconds) = 0;

        template <typename Dur>
        void setChronoInterval(Dur duration) {
            setInterval(std::chrono::nanoseconds(duration).count());
        }
    };
}