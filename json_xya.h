#include <map>
#include <memory>
#include <vector>
#include <sstream>

#define KEY(X) "((X)):"
#define STRINGIFY(X) "((X))"
namespace Xyah {
    enum CanonicalType {
        STRING,
        NON_STRING,
    };

    struct JSONType {
    private:
    public:
        virtual std::string toString();
    };

    struct JSONCanonicalType : public JSONType {
    private:
        CanonicalType __type = NON_STRING;
        std::string value;
        std::stringstream stream;
    public:
        JSONCanonicalType() = delete;

        JSONCanonicalType(int val) {
            stream << val;
            this->value = stream.str();
        }

        JSONCanonicalType(unsigned val) {
            stream << val;
            this->value = stream.str();
        }

        JSONCanonicalType(float val) {
            stream << val;
            this->value = stream.str();
        }

        JSONCanonicalType(bool val) {
            stream << val;
            this->value = stream.str();
        }

        JSONCanonicalType(std::string &val) {
            this->__type = CanonicalType::STRING;
            this->value = val;
        }

        JSONCanonicalType(std::string &&val) {
            this->__type = CanonicalType::STRING;
            this->value = val;
        }

        std::string toString() override {
            if (__type != CanonicalType::STRING) {
                return value;
            } else {
                return STRINGIFY(value);
            }
        }
    };

    struct JSONObject : public JSONType {
    private:
        std::map<std::string, JSONType> data;
    private:
        std::string toString() override {
            std::string _ending = "{";
            for (auto &_elpair : data) {
                _ending += KEY(_elpair.first) + _elpair.second.toString();
            }
            _ending += "}";
        };
    };

    struct JSONArray : JSONType {
    private:
        std::vector<JSONType> data;
    public:

        void emplaceValue(int val) {
            data.emplace_back(val);
        }

        void emplaceValue(unsigned val) {
            data.emplace_back(val);
        }

        void emplaceValue(float val) {
            data.emplace_back(val);
        }

        void emplaceValue(bool val) {
            data.emplace_back(val);
        }


        void emplaceValue(std::string &val) {
            data.emplace_back(val);
        }

        void emplaceValue(std::string &&val) {
            data.emplace_back(val);
        }

        JSONType &operator[](size_t index) {
            if (index > 0 && index < data.size()) {
                return data[index];
            } else {
                throw "[StackTrace: JSONArray] - invalid index";
            }
        }

        std::string toString() override {
            std::string _ending = "[";
            for (auto &_elpair : data) {
                _ending += _elpair.toString();
            }
            _ending += "]";
        };
    };
}

int main() {
    Xyah::JSONCanonicalType type(1);
}