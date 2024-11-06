#include <gtest/gtest.h>

#include <limits>
#include <random>
#include <vector>

//#include "core/task/func_tests/test_task.hpp"
//#include "core/task/include/task.hpp"
#include "seq/agafeev_s_max_of_vector_elements/include/header.hpp"

TEST(agafeev_s_max_of_vector_elements, find_max_in_10x10_matrix) {
  const int rows = 10;
  const int columns = 10;
  auto rand_gen = std::mt19937(1337);

  // Create data
  std::vector<int> in_matrix = agafeev_s_max_of_vector_elements_sequental::genRandMatr<int>(rows, columns);
  std::vector<int> out(1, 0);
  const int right_answer = std::numeric_limits<int>::max();
  int index = rand_gen() % (rows * columns);
  in_matrix[index] = std::numeric_limits<int>::max();

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_matrix.data()));
  taskData->inputs_count.emplace_back(in_matrix.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskData->outputs_count.emplace_back(out.size());

  // Create Task
  agafeev_s_max_of_vector_elements_sequental::MaxMatrixSequential<int> testTask(taskData);
  bool isValid = testTask.validation();
  ASSERT_EQ(isValid, true);
  testTask.pre_processing();
  testTask.run();
  testTask.post_processing();
  ASSERT_EQ(right_answer, out[0]);
}
/*
TEST(task_tests, check_validate_func) {
  // Create data
  std::vector<int32_t> in(20, 1);
  std::vector<int32_t> out(2, 0);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskData->outputs_count.emplace_back(out.size());

  // Create Task
  ppc::test::TestTask<int32_t> testTask(taskData);
  bool isValid = testTask.validation();
  ASSERT_EQ(isValid, false);
}

TEST(task_tests, check_double) {
  // Create data
  std::vector<double> in(20, 1);
  std::vector<double> out(1, 0);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskData->outputs_count.emplace_back(out.size());

  // Create Task
  ppc::test::TestTask<double> testTask(taskData);
  bool isValid = testTask.validation();
  ASSERT_EQ(isValid, true);
  testTask.pre_processing();
  testTask.run();
  testTask.post_processing();
  EXPECT_NEAR(out[0], static_cast<double>(in.size()), 1e-6);
}

TEST(task_tests, check_uint8_t) {
  // Create data
  std::vector<uint8_t> in(20, 1);
  std::vector<uint8_t> out(1, 0);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskData->outputs_count.emplace_back(out.size());

  // Create Task
  ppc::test::TestTask<uint8_t> testTask(taskData);
  bool isValid = testTask.validation();
  ASSERT_EQ(isValid, true);
  testTask.pre_processing();
  testTask.run();
  testTask.post_processing();
  ASSERT_EQ(static_cast<size_t>(out[0]), in.size());
}

TEST(task_tests, check_int64_t) {
  // Create data
  std::vector<int64_t> in(20, 1);
  std::vector<int64_t> out(1, 0);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskData->outputs_count.emplace_back(out.size());

  // Create Task
  ppc::test::TestTask<int64_t> testTask(taskData);
  bool isValid = testTask.validation();
  ASSERT_EQ(isValid, true);
  testTask.pre_processing();
  testTask.run();
  testTask.post_processing();
  ASSERT_EQ(static_cast<size_t>(out[0]), in.size());
}

TEST(task_tests, check_float) {
  // Create data
  std::vector<float> in(20, 1);
  std::vector<float> out(1, 0);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskData->outputs_count.emplace_back(out.size());

  // Create Task
  ppc::test::TestTask<float> testTask(taskData);
  bool isValid = testTask.validation();
  ASSERT_EQ(isValid, true);
  testTask.pre_processing();
  testTask.run();
  testTask.post_processing();
  EXPECT_NEAR(out[0], in.size(), 1e-3);
}

TEST(task_tests, check_wrong_order) {
  // Create data
  std::vector<float> in(20, 1);
  std::vector<float> out(1, 0);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskData->outputs_count.emplace_back(out.size());

  // Create Task
  ppc::test::TestTask<float> testTask(taskData);
  bool isValid = testTask.validation();
  ASSERT_EQ(isValid, true);
  testTask.pre_processing();
  ASSERT_ANY_THROW(testTask.post_processing());
}*/