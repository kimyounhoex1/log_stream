#include <gtest/gtest.h>
#include <fstream>
#include <unistd.h>
#include "../client/Config.hpp"

// 현재 구현이 파일 내용을 그대로 읽어오는지 검증
TEST(ConfigTest, ReadFileContentsReturnsString) {
    std::string path = CONFIG_JSON_PATH;

    std::string contents = R"(
{
    "dbname": "logs",
    "user": "postgres",
    "password": "postgres",
    "host": "log_postgres",
    "port": "5432"
}
)";

    std::ofstream ofs(path);
    ofs << contents;
    ofs.close();

    Config cfg;
    std::string read = cfg.readFileContents(path);
    EXPECT_EQ(read, contents);

    EXPECT_FALSE(read.empty());

    std::remove(path.c_str());
}

