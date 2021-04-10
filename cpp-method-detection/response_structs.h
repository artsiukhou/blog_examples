#include <string>

using std::string;

class Status {
public:
    string& result() { return _result; }
    string& message() { return _message; }
private:
    string _result;
    string _message;
};

class Response {
};

class ResponseWithStatus {
public:
    Status& status() { return _status; }
private:
    Status _status;
};

class ResponseWithTwoStatuses {
public:
    Status& status() { return _status; }
    const Status& status() const { return _status; }
private:
    Status _status;
};
