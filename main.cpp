
#include <string>
#include <vector>
#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"
#include "boost/serialization/map.hpp"
#include "boost/serialization/vector.hpp"
#include "boost/serialization/base_object.hpp"

namespace jerry
{
struct Position
{
    std::string from;
    std::string to;

    inline bool operator<(const Position& other) const
    {
        return (from < other.from || to < other.to);
    }
};

}  // namespace jerry

namespace tom
{
struct Base
{
    int a;
    float b;
};

struct Drive : public Base
{
    int c;
    std::string d;
};

}  // namespace tom

// non-intrusive implementaion
namespace boost
{
namespace serialization
{
template <class Archive>
void serialize(Archive& ar, jerry::Position& t, const unsigned int file_version)
{
    ar& t.from;
    ar& t.to;
}

template <class Archive>
void serialize(Archive& ar, tom::Base& t, const unsigned int file_version)
{
    ar& t.a;
    ar& t.b;
}

template <class Archive>
void serialize(Archive& ar, tom::Drive& t, const unsigned int file_version)
{
    ar& boost::serialization::base_object<tom::Base>(t);
    ar& t.c;
    ar& t.d;
}

}  // namespace serialization
}  // namespace boost

BOOST_CLASS_VERSION(jerry::Position, 0xff);

int main(int argc, char* argv[])
{
    using namespace jerry;
    Position ti1{"src", "dest"};

    using namespace tom;
    std::vector<Drive> datas;
    Drive d;
    d.a = 0;
    d.b = 0.3f;
    d.c = 1;
    d.d = "test";
    datas.push_back(d);
    datas.push_back(d);
    datas.push_back(d);

    std::map<Position, std::vector<Drive>> test_out;
    test_out.insert(std::make_pair(ti1, datas));

    std::ofstream output("fake_positions.txt");
    boost::archive::text_oarchive oa(output);
    oa << test_out;
    output.close();
    std::cout << "save map size: " << test_out.size() << std::endl;

    std::map<Position, std::vector<Drive>> test_in;
    std::ifstream input("fake_positions.txt");
    boost::archive::text_iarchive ia(input);
    ia >> test_in;
    input.close();
    std::cout << "load map size: " << test_in.size() << std::endl;

    return 0;
}
