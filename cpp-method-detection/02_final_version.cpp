#include "response_structs.h"

#include <iostream>
#include <string_view>
#include <utility>

using std::void_t;
using std::true_type;
using std::false_type;
using std::cout;
using std::endl;
using std::string_view;
using std::declval;

// Define hasStatus helpers
template <typename T, typename = void_t<>>
struct hasStatus: false_type {
};

template <typename T>
struct hasStatus<T, void_t<decltype(declval<T>().status())>>: true_type {
};

// setStatus() helpers
void setStatus(Status& status, const string_view result, const string_view message) {
    cout << "invoked setStatus<Status>" << endl;
    status.result() = result;
    status.message() = message;
}

template <typename T>
void setStatus(T& resp, const string_view result, const string_view message) {
    if constexpr (hasStatus<T>::value) {
        cout << "invoked setStatus<T.status>" << endl;
        setStatus(resp.status(), result, message);
    } else {
        cout << "invoked setStatus<T>" << endl;
    }
}

int main() {
    {
        cout << "============ Testing Response\n"
            << "hasStatus? " << hasStatus<Response>::value
            << endl;
        Response r;
        setStatus(r, "ok", "all good");
    }
    {
        cout << "============ Testing Status\n"
            << "hasStatus? " << hasStatus<Status>::value
            << endl;
        Status s;
        setStatus(s, "ok", "all good");
    }
    {
        cout << "============ Testing ResponseWithStatus\n"
            << "hasStatus? " << hasStatus<ResponseWithStatus>::value
            << endl;
        ResponseWithStatus rs;
        setStatus(rs, "ok", "all good");
    }
    {
        cout << "============ Testing ResponseWithTwoStatuses\n"
            << "hasStatus? " << hasStatus<ResponseWithTwoStatuses>::value
            << endl;
        ResponseWithTwoStatuses rs;
        setStatus(rs, "ok", "all good");
    }

    return 0;
}
