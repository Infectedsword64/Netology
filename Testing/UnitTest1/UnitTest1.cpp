#include "pch.h"
#include "CppUnitTest.h"
#include "../Testing/extended_array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(ExtendedArrayTest) {
public:
		TEST_METHOD(Mean) {
			ExtArray<int> v1{ 4, 2, 7, 3, -5, 0, -3, 1 };
			Assert::AreEqual(v1.mean(), 1.125);

			ExtArray<int> v2{ };
			Assert::AreEqual(v2.mean(), 0.0);

			ExtArray<int> v3{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			Assert::AreEqual(v3.mean(3, 5), 0.0);
			Assert::ExpectException<std::invalid_argument>(v3.mean(8, 3));
			Assert::ExpectException<std::invalid_argument>(v3.mean(4, 4));
		}
		TEST_METHOD(Median) {
			ExtArray<double> v1{ 4.5, 0.7, 10.8, -3.5 };
			Assert::AreEqual(2.6, v1.median());

			ExtArray<int> v2{ };
			Assert::AreEqual(0.0, v2.median());
		}
		TEST_METHOD(Mode) {
			ExtArray<int> v1{ 4, 2, 7, 2, 5, -5, 0, 5, 5 };
			Assert::AreEqual(5, v1.mode().first);

			ExtArray<int> v2{ };
			Assert::AreEqual(0, v2.mode().first);
		}
	};
}