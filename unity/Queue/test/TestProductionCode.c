#include "ProductionCode.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(ProductionCode);

//sometimes you may want to get at local data in a module.
//for example: If you plan to pass by reference, this could be useful
//however, it should often be avoided
void * voidpool[10]={(void *)12345678,};
char charpool[10];
char * out;
int i;
TEST_SETUP(ProductionCode)
{
  //This is run before EACH TEST
	ResetQueue();
    out = &charpool[0];
	i=0;
}

TEST_TEAR_DOWN(ProductionCode)
{
}

TEST(ProductionCode, PushQueue_PopQueue_Index_Check_Return_lastWidx)
{
  //All of these should pass
  TEST_ASSERT_EQUAL(0, PushQueue(voidpool[0]));
  TEST_ASSERT_EQUAL(1, PushQueue(voidpool[0]));
  TEST_ASSERT_EQUAL(2, PushQueue(voidpool[0]));
  TEST_ASSERT_EQUAL(3, PushQueue(voidpool[0]));
  TEST_ASSERT_EQUAL(3, PopQueue(&out));
  TEST_ASSERT_EQUAL(4, PushQueue(voidpool[0]));
  TEST_ASSERT_EQUAL(4, PopQueue(&out));
}

TEST(ProductionCode, PushQueue_PopQueue_CorrectData)
{
  //All of these should pass
  TEST_ASSERT_EQUAL(0, PushQueue(voidpool[0]));
  //printf("%p\n", out);
  TEST_ASSERT_EQUAL(0, PopQueue(&out));
  TEST_ASSERT_EQUAL(voidpool[0], out);
  //printf("%p %p\n",voidpool[0], out);
}

TEST(ProductionCode, PushQueue_PopQueue_Index_CorrectData_Check)
{
  //All of these should fail
  TEST_ASSERT_EQUAL(i%NODE_POOL_MAX, PushQueue(voidpool[8])); i++;
  TEST_ASSERT_EQUAL(i%NODE_POOL_MAX, PushQueue(voidpool[8])); i++;
  TEST_ASSERT_EQUAL(i%NODE_POOL_MAX, PushQueue(voidpool[8])); i++;
  TEST_ASSERT_EQUAL(i%NODE_POOL_MAX, PushQueue(voidpool[8])); i++;
  TEST_ASSERT_EQUAL(i%NODE_POOL_MAX, PushQueue(voidpool[8])); i++;
  TEST_ASSERT_EQUAL(i%NODE_POOL_MAX, PushQueue(voidpool[8])); i++;
  TEST_ASSERT_EQUAL(i%NODE_POOL_MAX, PushQueue(voidpool[8])); i++;
  TEST_ASSERT_EQUAL(i%NODE_POOL_MAX, PushQueue(voidpool[8])); i++;
  TEST_ASSERT_EQUAL(i%NODE_POOL_MAX, PushQueue(voidpool[8])); i++;
  TEST_ASSERT_EQUAL(i%NODE_POOL_MAX, PushQueue(voidpool[8])); i++;
  TEST_ASSERT_EQUAL(i%NODE_POOL_MAX, PushQueue(voidpool[8])); i++;
  TEST_ASSERT_EQUAL(i%NODE_POOL_MAX, PushQueue(voidpool[8])); i++;
  TEST_ASSERT_EQUAL(i%NODE_POOL_MAX, PushQueue(voidpool[8])); i++;
  TEST_ASSERT_EQUAL(i%NODE_POOL_MAX, PushQueue(voidpool[8])); i++;
  TEST_ASSERT_EQUAL(i%NODE_POOL_MAX, PushQueue(voidpool[8])); i++;

}

