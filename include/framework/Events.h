#pragma once

#include "Dependency.h"
#include "Callback.h"
#include <memory>
#include <framework/EventCallback.h>

namespace Cppelix {
    class ILifecycleManager;

    struct Event {
        Event(uint64_t _type, uint64_t _id, uint64_t _originatingService) noexcept : type{_type}, id{_id}, originatingService{_originatingService} {}
        virtual ~Event() = default;
        const uint64_t type;
        const uint64_t id;
        const uint64_t originatingService;
    };

    struct DependencyOnlineEvent final : public Event {
        explicit DependencyOnlineEvent(uint64_t _id, uint64_t _originatingService, const std::shared_ptr<ILifecycleManager> _manager) noexcept :
            Event(TYPE, _id, _originatingService), manager(std::move(_manager)) {}
        ~DependencyOnlineEvent() final = default;

        const std::shared_ptr<ILifecycleManager> manager;
        static constexpr uint64_t TYPE = typeNameHash<DependencyOnlineEvent>();
    };

    struct DependencyOfflineEvent final : public Event {
        explicit DependencyOfflineEvent(uint64_t _id, uint64_t _originatingService, const std::shared_ptr<ILifecycleManager> _manager) noexcept :
            Event(TYPE, _id, _originatingService), manager(std::move(_manager)) {}
        ~DependencyOfflineEvent() final = default;

        const std::shared_ptr<ILifecycleManager> manager;
        static constexpr uint64_t TYPE = typeNameHash<DependencyOfflineEvent>();
    };

    struct DependencyRequestEvent final : public Event {
        explicit DependencyRequestEvent(uint64_t _id, uint64_t _originatingService, std::shared_ptr<ILifecycleManager> _manager, Dependency _dependency, CppelixProperties const * _properties) noexcept :
                Event(TYPE, _id, _originatingService), manager(std::move(_manager)), dependency(std::move(_dependency)), properties{_properties} {}
        ~DependencyRequestEvent() final = default;

        const std::shared_ptr<ILifecycleManager> manager;
        const Dependency dependency;
        const CppelixProperties * properties;
        static constexpr uint64_t TYPE = typeNameHash<DependencyRequestEvent>();
    };

    struct DependencyUndoRequestEvent final : public Event {
        explicit DependencyUndoRequestEvent(uint64_t _id, uint64_t _originatingService, std::shared_ptr<ILifecycleManager> _manager, Dependency _dependency, CppelixProperties const * _properties) noexcept :
                Event(TYPE, _id, _originatingService), manager(std::move(_manager)), dependency(std::move(_dependency)), properties{_properties} {}
        ~DependencyUndoRequestEvent() final = default;

        const std::shared_ptr<ILifecycleManager> manager;
        const Dependency dependency;
        const CppelixProperties * properties;
        static constexpr uint64_t TYPE = typeNameHash<DependencyUndoRequestEvent>();
    };

    struct QuitEvent final : public Event {
        QuitEvent(uint64_t _id, uint64_t _originatingService, bool _dependenciesStopped = false) noexcept : Event(TYPE, _id, _originatingService), dependenciesStopped(_dependenciesStopped) {}
        ~QuitEvent() final = default;

        const bool dependenciesStopped;
        static constexpr uint64_t TYPE = typeNameHash<QuitEvent>();
    };

    struct StopServiceEvent final : public Event {
        StopServiceEvent(uint64_t _id, uint64_t _originatingService, uint64_t _serviceId, bool _dependenciesStopped = false) noexcept : Event(TYPE, _id, _originatingService), serviceId(_serviceId), dependenciesStopped(_dependenciesStopped) {}
        ~StopServiceEvent() final = default;

        const uint64_t serviceId;
        const bool dependenciesStopped;
        static constexpr uint64_t TYPE = typeNameHash<StopServiceEvent>();
    };

    struct StartServiceEvent final : public Event {
        StartServiceEvent(uint64_t _id, uint64_t _originatingService, uint64_t _serviceId) noexcept : Event(TYPE, _id, _originatingService), serviceId(_serviceId) {}
        ~StartServiceEvent() final = default;

        const uint64_t serviceId;
        static constexpr uint64_t TYPE = typeNameHash<StartServiceEvent>();
    };

    struct RemoveServiceEvent final : public Event {
        RemoveServiceEvent(uint64_t _id, uint64_t _originatingService, uint64_t _serviceId, bool _dependenciesStopped = false) noexcept : Event(TYPE, _id, _originatingService), serviceId(_serviceId), dependenciesStopped(_dependenciesStopped) {}
        ~RemoveServiceEvent() final = default;

        const uint64_t serviceId;
        const bool dependenciesStopped;
        static constexpr uint64_t TYPE = typeNameHash<RemoveServiceEvent>();
    };

    struct DoWorkEvent final : public Event {
        DoWorkEvent(uint64_t _id, uint64_t _originatingService) noexcept : Event(TYPE, _id, _originatingService) {}
        ~DoWorkEvent() final = default;

        static constexpr uint64_t TYPE = typeNameHash<DoWorkEvent>();
    };

    struct RemoveCompletionCallbacksEvent final : public Event {
        RemoveCompletionCallbacksEvent(uint64_t _id, uint64_t _originatingService, CallbackKey _key) noexcept : Event(TYPE, _id, _originatingService), key(_key) {}
        ~RemoveCompletionCallbacksEvent() final = default;

        const CallbackKey key;
        static constexpr uint64_t TYPE = typeNameHash<RemoveCompletionCallbacksEvent>();
    };

    struct RemoveEventHandlerEvent final : public Event {
        RemoveEventHandlerEvent(uint64_t _id, uint64_t _originatingService, CallbackKey _key) noexcept : Event(TYPE, _id, _originatingService), key(_key) {}
        ~RemoveEventHandlerEvent() final = default;

        const CallbackKey key;
        static constexpr uint64_t TYPE = typeNameHash<RemoveEventHandlerEvent>();
    };

    struct RemoveTrackerEvent final : public Event {
        RemoveTrackerEvent(uint64_t _id, uint64_t _originatingService, uint64_t _interfaceNameHash) noexcept : Event(TYPE, _id, _originatingService), interfaceNameHash(_interfaceNameHash) {}
        ~RemoveTrackerEvent() final = default;

        const uint64_t interfaceNameHash;
        static constexpr uint64_t TYPE = typeNameHash<RemoveTrackerEvent>();
    };

    struct ContinuableEvent final : public Event {
        ContinuableEvent(uint64_t _id, uint64_t _originatingService, Generator<bool> _generator) noexcept : Event(TYPE, _id, _originatingService), generator(std::move(_generator)) {}
        ~ContinuableEvent() final = default;

        Generator<bool> generator;
        static constexpr uint64_t TYPE = typeNameHash<ContinuableEvent>();
    };
}