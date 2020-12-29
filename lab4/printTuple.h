#ifndef CSV_PRINTTUPLE_H
#define CSV_PRINTTUPLE_H
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <tuple>
#include <sstream>


template<typename... Args>
auto &operator<<(std::ostream& stream, std::tuple<Args...> const& theTuple) {
    std::apply (
            [&stream](Args const&... args) {
                stream << '[';
                std::size_t n{0};
                ((stream << args << (++n != sizeof...(Args) ? "; " : "")), ...);
                stream << ']';
            }, theTuple
    );
    return stream;
}
#endif //CSV_PRINTTUPLE_H
