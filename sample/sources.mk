samples: ./functional/functional ./functional/bind ./mutex/recursive_mutex ./mutex/call_once ./thread/thread ./type_traits/type_traits ./future/enums ./numeric/iota

./functional/functional: ./functional/functional.o
./functional/bind: ./functional/bind.o
./mutex/recursive_mutex: ./mutex/recursive_mutex.o
./mutex/call_once: ./mutex/call_once.o
./thread/thread: ./thread/thread.o
./type_traits/type_traits: ./type_traits/type_traits.o
./future/enums: ./future/enums.o
./numeric/iota: ./numeric/iota.o
functional/functional.o: functional/functional.cpp ../include/std11/functional.hpp \
 ../include/std11/_config.hpp ../include/std11/utility.hpp \
 ../include/std11/type_traits.hpp ../include/std11/memory.hpp \
 ../include/std11/internal/functional/bind.hpp \
 ../include/std11/internal/functional/mem_fn.hpp
functional/bind.o: functional/bind.cpp ../include/std11/functional.hpp \
 ../include/std11/_config.hpp ../include/std11/utility.hpp \
 ../include/std11/type_traits.hpp ../include/std11/memory.hpp \
 ../include/std11/internal/functional/bind.hpp \
 ../include/std11/internal/functional/mem_fn.hpp
mutex/recursive_mutex.o: mutex/recursive_mutex.cpp ../include/std11/mutex.hpp \
 ../include/std11/_config.hpp ../include/std11/chrono.hpp \
 ../include/std11/ratio.hpp ../include/std11/type_traits.hpp \
 ../include/std11/utility.hpp ../include/std11/thread.hpp \
 ../include/std11/functional.hpp ../include/std11/memory.hpp \
 ../include/std11/internal/functional/bind.hpp \
 ../include/std11/internal/functional/mem_fn.hpp \
 ../include/std11/internal/thread_worker.hpp \
 ../include/std11/internal/noncopyable.hpp \
 ../include/std11/internal/once_caller.hpp
mutex/call_once.o: mutex/call_once.cpp ../include/std11/thread.hpp \
 ../include/std11/_config.hpp ../include/std11/functional.hpp \
 ../include/std11/utility.hpp ../include/std11/type_traits.hpp \
 ../include/std11/memory.hpp \
 ../include/std11/internal/functional/bind.hpp \
 ../include/std11/internal/functional/mem_fn.hpp \
 ../include/std11/internal/thread_worker.hpp \
 ../include/std11/internal/noncopyable.hpp ../include/std11/mutex.hpp \
 ../include/std11/chrono.hpp ../include/std11/ratio.hpp \
 ../include/std11/internal/once_caller.hpp
thread/thread.o: thread/thread.cpp ../include/std11/thread.hpp \
 ../include/std11/_config.hpp ../include/std11/functional.hpp \
 ../include/std11/utility.hpp ../include/std11/type_traits.hpp \
 ../include/std11/memory.hpp \
 ../include/std11/internal/functional/bind.hpp \
 ../include/std11/internal/functional/mem_fn.hpp \
 ../include/std11/internal/thread_worker.hpp \
 ../include/std11/internal/noncopyable.hpp
type_traits/type_traits.o: type_traits/type_traits.cpp \
 ../include/std11/type_traits.hpp ../include/std11/_config.hpp \
 ../include/std11/utility.hpp
future/enums.o: future/enums.cpp ../include/std11/type_traits.hpp \
 ../include/std11/_config.hpp ../include/std11/utility.hpp \
 ../include/std11/future.hpp ../include/std11/system_err.hpp \
 ../include/std11/language_extension/enum_class.hpp \
 ../include/std11/internal/noncopyable.hpp
numeric/iota.o: numeric/iota.cpp ../include/std11/numeric.hpp \
 ../include/std11/algorithm.hpp ../include/std11/type_traits.hpp \
 ../include/std11/_config.hpp ../include/std11/utility.hpp \
 ../include/std11/random.hpp
