


#define BOOST_TEST_DYN_LINK
#define NVERBOSE // to suppress our messages when throwing

#define BOOST_TEST_MODULE ColumnExtractTest
#include <boost/test/unit_test.hpp>
#include <opm/core/ColumnExtract.hpp>
#include <opm/core/GridManager.hpp>

BOOST_AUTO_TEST_CASE(SingleColumnTest)
{
    const int size_x = 1, size_y = 1, size_z = 10;
    using namespace Opm;
    GridManager manager(size_x, size_y, size_z);

    std::vector<std::vector<int> > columns;
    extractColumn(*manager.c_grid(), columns);

    std::vector<int> correct_answer;
    for(int i = 0; i < 10; i++) {
        correct_answer.push_back(i);
    }
    BOOST_CHECK_EQUAL_COLLECTIONS(correct_answer.begin(), correct_answer.end(),
                                  columns[0].begin(), columns[0].end());

}


BOOST_AUTO_TEST_CASE(FourByFourColumnTest)
{
    const int size_x = 4, size_y = 4, size_z = 10;
    using namespace Opm;
    GridManager manager(size_x, size_y, size_z);

    std::vector<std::vector<int> > columns;
    extractColumn(*manager.c_grid(), columns);

    std::vector<std::vector<int> > correct_answer;
    correct_answer.resize(size_x * size_y);
    for(int i = 0; i < size_x * size_y; i++) {
        for(int j = 0; j < 10; j++) {
            correct_answer[i].push_back( i + j*size_x*size_y);
        }
    }

    for(int i = 0; i < size_x * size_y; i++) {
        BOOST_CHECK_EQUAL_COLLECTIONS(correct_answer[i].begin(), correct_answer[i].end(),
                                      columns[i].begin(), columns[i].end());
    }

}